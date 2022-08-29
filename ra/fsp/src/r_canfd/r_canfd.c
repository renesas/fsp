/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_canfd.h"
#include "r_canfd_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define CANFD_OPEN                        (0x52434644U) // "RCFD" in ASCII

#define CANFD_BAUD_RATE_PRESCALER_MIN     (1U)
#define CANFD_BAUD_RATE_PRESCALER_MAX     (1024U)

#define CANFD_PRV_CTR_MODE_MASK           (R_CANFD_CFDGCTR_GSLPR_Msk + R_CANFD_CFDGCTR_GMDC_Msk)
#define CANFD_PRV_CTR_RESET_BIT           (1U)
#define CANFD_PRV_RXMB_MAX                (32U)
#define CANFD_PRV_TXMB_OFFSET             (32U)
#define CANFD_PRV_TXMB_CHANNEL_OFFSET     (64U)
#define CANFD_PRV_STANDARD_ID_MAX         (0x7FFU)

#if BSP_FEATURE_CANFD_LITE
 #define CANFD_PRV_RXMB_PTR(buffer)    ((volatile R_CANFD_CFDRM_Type *) &R_CANFD->CFDRMC[buffer >> 3].RM[buffer & 7U])
 #define CANFD_PRV_RX_FIFO_MAX            (2U)
 #define CANFD_PRV_RX_FIFO_STATUS_MASK    (R_CANFDL_CFDFESTS_RFXEMP_Msk)
 #define CANFD_PRV_AFL_CAST               (volatile R_CANFD_CFDGAFL_Type *)
 #define CANFD_PRV_CFDTMIEC_LENGTH        (1)
#else
 #define CANFD_PRV_RXMB_PTR(buffer)    (&R_CANFD->CFDRM[buffer])
 #define CANFD_PRV_RX_FIFO_MAX            (8U)
 #define CANFD_PRV_RX_FIFO_STATUS_MASK    (R_CANFD_CFDFESTS_RFXEMP_Msk)
 #define CANFD_PRV_AFL_CAST
 #define CANFD_PRV_CFDTMIEC_LENGTH        (2)
#endif

/***********************************************************************************************************************
 * Const data
 **********************************************************************************************************************/

/* LUT to convert DLC values to payload size in bytes */
static const uint8_t dlc_to_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

#if CANFD_CFG_PARAM_CHECKING_ENABLE

/* LUT to determine the hierarchy of can_operation_mode_t modes. */
static const uint8_t g_mode_order[] = {0, 2, 1, 0, 0, 3};
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * canfd_prv_ns_callback)(can_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile canfd_prv_ns_callback)(can_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if CANFD_CFG_PARAM_CHECKING_ENABLE
static bool r_canfd_bit_timing_parameter_check(can_bit_timing_cfg_t * p_bit_timing);

#endif

#if BSP_FEATURE_CANFD_FD_SUPPORT
static uint8_t r_canfd_bytes_to_dlc(uint8_t bytes);

#endif

static void r_canfd_mb_read(uint32_t buffer, can_frame_t * const frame);
static void r_canfd_call_callback(canfd_instance_ctrl_t * p_ctrl, can_callback_args_t * p_args);
static void r_canfd_mode_transition(canfd_instance_ctrl_t * p_ctrl, can_operation_mode_t operation_mode);
static void r_canfd_mode_ctr_set(volatile uint32_t * p_ctr_reg, can_operation_mode_t operation_mode);
void        canfd_error_isr(void);
void        canfd_rx_fifo_isr(void);
void        canfd_channel_tx_isr(void);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Channel control struct array */
static canfd_instance_ctrl_t * gp_ctrl[BSP_FEATURE_CANFD_NUM_CHANNELS] = {NULL};

/* CAN function pointers   */
const can_api_t g_canfd_on_canfd =
{
    .open           = R_CANFD_Open,
    .close          = R_CANFD_Close,
    .write          = R_CANFD_Write,
    .read           = R_CANFD_Read,
    .modeTransition = R_CANFD_ModeTransition,
    .infoGet        = R_CANFD_InfoGet,
    .callbackSet    = R_CANFD_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup CANFD
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***************************************************************************************************************//**
 * Open and configure the CANFD channel for operation.
 *
 * Example:
 * @snippet r_canfd_example.c R_CANFD_Open
 *
 * @retval FSP_SUCCESS                            Channel opened successfully.
 * @retval FSP_ERR_ALREADY_OPEN                   Driver already open.
 * @retval FSP_ERR_IN_USE                         Channel is already in use.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT         Channel does not exist on this MCU.
 * @retval FSP_ERR_ASSERTION                      A required pointer was NULL.
 * @retval FSP_ERR_CAN_INIT_FAILED                The provided nominal or data bitrate is invalid.
 * @retval FSP_ERR_CLOCK_INACTIVE                 CANFD source clock is disabled (PLL or PLL2).
 *****************************************************************************************************************/
fsp_err_t R_CANFD_Open (can_ctrl_t * const p_api_ctrl, can_cfg_t const * const p_cfg)
{
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;

#if CANFD_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(p_cfg->p_callback);
    FSP_ASSERT(p_cfg->p_bit_timing);

    uint32_t channel = p_cfg->channel;

    /* Check that the module is not open, the channel is present and that it is not in use */
    FSP_ERROR_RETURN(CANFD_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(channel < BSP_FEATURE_CANFD_NUM_CHANNELS, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(NULL == gp_ctrl[channel], FSP_ERR_IN_USE);

    /* Check that mandatory interrupts are enabled */
    FSP_ERROR_RETURN(VECTOR_NUMBER_CAN_RXF >= 0, FSP_ERR_CAN_INIT_FAILED);
    FSP_ERROR_RETURN(VECTOR_NUMBER_CAN_GLERR >= 0, FSP_ERR_CAN_INIT_FAILED);

    /* Check that the global config is present */
    canfd_extended_cfg_t * p_extend = (canfd_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(p_extend->p_global_cfg);

 #if BSP_CFG_CANFDCLK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC

    /* Check that PLL/PLL2 is running when it is selected as the DLL source clock */
    FSP_ERROR_RETURN(0U == (R_SYSTEM->CANFDCKCR == BSP_CLOCKS_SOURCE_CLOCK_PLL ? R_SYSTEM->PLLCR : R_SYSTEM->PLL2CR),
                     FSP_ERR_CLOCK_INACTIVE);
 #endif

    /* Check nominal bit timing parameters for correctness */
    FSP_ERROR_RETURN(r_canfd_bit_timing_parameter_check(p_cfg->p_bit_timing), FSP_ERR_CAN_INIT_FAILED);

 #if BSP_FEATURE_CANFD_FD_SUPPORT

    /* Check that bit timing for FD bitrate switching is present and correct */
    can_bit_timing_cfg_t * p_data_timing = p_extend->p_data_timing;
    FSP_ASSERT(p_data_timing);
    FSP_ERROR_RETURN(r_canfd_bit_timing_parameter_check(p_data_timing), FSP_ERR_CAN_INIT_FAILED);

    can_bit_timing_cfg_t * p_bit_timing = p_cfg->p_bit_timing;

    /* Check that data rate > nominal rate */
    uint32_t data_rate_clocks = p_data_timing->baud_rate_prescaler *
                                (p_data_timing->time_segment_1 + p_data_timing->time_segment_2 + 1U);
    uint32_t nominal_rate_clocks = p_bit_timing->baud_rate_prescaler *
                                   (p_bit_timing->time_segment_1 + p_bit_timing->time_segment_2 + 1U);
    FSP_ERROR_RETURN(data_rate_clocks <= nominal_rate_clocks, FSP_ERR_CAN_INIT_FAILED);
 #endif
#else
    uint32_t channel = p_cfg->channel;

    /* Get extended config */
    canfd_extended_cfg_t * p_extend = (canfd_extended_cfg_t *) p_cfg->p_extend;
#endif

    fsp_err_t err = FSP_SUCCESS;

    /* Initialize the control block */
    p_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Get global config */
    canfd_global_cfg_t * p_global_cfg = p_extend->p_global_cfg;

    /* Start module */
    R_BSP_MODULE_START(FSP_IP_CANFD, 0);

    /* Perform global config only if the module is in Global Sleep or Global Reset */
    if (R_CANFD->CFDGSTS & R_CANFD_CFDGSTS_GRSTSTS_Msk)
    {
        /* Wait for RAM initialization (see RA6M5 User's Manual (R01UH0891EJ0100) section 32.3.4.1 Note 2) */
        FSP_HARDWARE_REGISTER_WAIT((R_CANFD->CFDGSTS & R_CANFD_CFDGSTS_GRAMINIT_Msk), 0);

        /* Cancel Global Sleep and wait for transition to Global Reset */
        r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_GLOBAL_RESET);

        /* Configure global TX priority, DLC check/replace functions, external/internal clock select and payload
         * overflow behavior */
        R_CANFD->CFDGCFG = p_global_cfg->global_config;

        /* Configure rule count for both channels */
        R_CANFD->CFDGAFLCFG0 = (CANFD_CFG_AFL_CH0_RULE_NUM << R_CANFD_CFDGAFLCFG0_RNC0_Pos) |
                               CANFD_CFG_AFL_CH1_RULE_NUM;

        /* Set CAN FD Protocol Exception response (ISO exception state or send error frame) */
        R_CANFD->CFDGFDCFG = CANFD_CFG_FD_PROTOCOL_EXCEPTION;

#if !BSP_FEATURE_CANFD_LITE

        /* Set CAN FD standard (ISO or Bosch) */
        R_CANFD->CFDGCRCCFG = CANFD_CFG_FD_STANDARD;
#endif

        /* Set number and size of RX message buffers */
        R_CANFD->CFDRMNB = p_global_cfg->rx_mb_config;

        /* Configure RX FIFOs and interrupt */
        for (uint32_t i = 0; i < CANFD_PRV_RX_FIFO_MAX; i++)
        {
            R_CANFD->CFDRFCC[i] = p_global_cfg->rx_fifo_config[i];
        }

        R_BSP_IrqCfgEnable(VECTOR_NUMBER_CAN_RXF, p_global_cfg->rx_fifo_ipl, NULL);

        /* Set global error interrupts */
        R_CANFD->CFDGCTR = p_global_cfg->global_interrupts;
    }

    if (CANFD_CFG_GLOBAL_ERROR_CH == channel)
    {
        /* Configure global error interrupt */
        R_BSP_IrqCfgEnable(VECTOR_NUMBER_CAN_GLERR, p_global_cfg->global_err_ipl, NULL);
    }

    /* Track ctrl struct */
    gp_ctrl[channel] = p_ctrl;

    /* Get AFL entry and limit */
    uint32_t afl_entry = 0;
    uint32_t afl_max   = CANFD_CFG_AFL_CH0_RULE_NUM;
    if (1U == channel)
    {
        afl_entry += CANFD_CFG_AFL_CH0_RULE_NUM;
        afl_max   += CANFD_CFG_AFL_CH1_RULE_NUM;
    }

    /* Unlock AFL */
    R_CANFD->CFDGAFLECTR = R_CANFD_CFDGAFLECTR_AFLDAE_Msk;

    /* Write all configured AFL entries */
    R_CANFD_CFDGAFL_Type * p_afl = (R_CANFD_CFDGAFL_Type *) p_extend->p_afl;
    for ( ; afl_entry < afl_max; afl_entry++)
    {
        /* AFL register access is performed through a page window comprised of 16 entries. See Section 32.5.4 "Entering
         * Entries in the AFL" in the RA6M5 User's Manual (R01UH0891EJ010) for more details. */

        /* Set AFL page */
        R_CANFD->CFDGAFLECTR = (afl_entry >> 4) | R_CANFD_CFDGAFLECTR_AFLDAE_Msk;

        /* Get pointer to current AFL rule and set it to the rule pointed to by p_afl */
        volatile R_CANFD_CFDGAFL_Type * cfdgafl = CANFD_PRV_AFL_CAST & R_CANFD->CFDGAFL[afl_entry & 0xF];
        *cfdgafl = *p_afl++;

        /* Set Information Label 0 to the channel being configured */
        cfdgafl->P0_b.GAFLIFL0 = channel & 1U;
    }

    /* Lock AFL */
    R_CANFD->CFDGAFLECTR = 0;

    /* Cancel Channel Sleep and wait for transition to Channel Reset */
    r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_RESET);

    /* Configure bitrate */
    R_CANFD->CFDC[channel].NCFG =
        (uint32_t) (((p_cfg->p_bit_timing->baud_rate_prescaler - 1) & R_CANFD_CFDC_NCFG_NBRP_Msk) <<
                    R_CANFD_CFDC_NCFG_NBRP_Pos) |
        ((p_cfg->p_bit_timing->time_segment_1 - 1U) << R_CANFD_CFDC_NCFG_NTSEG1_Pos) |
        ((p_cfg->p_bit_timing->time_segment_2 - 1U) << R_CANFD_CFDC_NCFG_NTSEG2_Pos) |
        ((p_cfg->p_bit_timing->synchronization_jump_width - 1U) << R_CANFD_CFDC_NCFG_NSJW_Pos);

#if BSP_FEATURE_CANFD_FD_SUPPORT

    /* Configure data bitrate for rate switching on FD frames */
    R_CANFD->CFDC2[channel].DCFG =
        (uint32_t) (((p_extend->p_data_timing->baud_rate_prescaler - 1) & R_CANFD_CFDC2_DCFG_DBRP_Msk) <<
                    R_CANFD_CFDC2_DCFG_DBRP_Pos) |
        ((p_extend->p_data_timing->time_segment_1 - 1U) << R_CANFD_CFDC2_DCFG_DTSEG1_Pos) |
        ((p_extend->p_data_timing->time_segment_2 - 1U) << R_CANFD_CFDC2_DCFG_DTSEG2_Pos) |
        ((p_extend->p_data_timing->synchronization_jump_width - 1U) << R_CANFD_CFDC2_DCFG_DSJW_Pos);

    /* Ensure transceiver delay offset is not larger than 8 bits */
    uint32_t tdco = p_extend->p_data_timing->time_segment_1;
    if (tdco > UINT8_MAX)
    {
        tdco = UINT8_MAX;
    }

    /* Configure transceiver delay compensation; allow user to set ESI bit manually */
    R_CANFD->CFDC2[channel].FDCFG =
        (tdco << R_CANFD_CFDC2_FDCFG_TDCO_Pos) |
        (uint32_t) (p_extend->delay_compensation << R_CANFD_CFDC2_FDCFG_TDCE_Pos) |
        R_CANFD_CFDC2_FDCFG_ESIC_Msk | 1U;
#endif

    /* Write TX message buffer interrupt enable bits */
    memcpy((void *) &R_CANFD->CFDTMIEC[channel * CANFD_PRV_CFDTMIEC_LENGTH],
           &p_extend->txmb_txi_enable,
           CANFD_PRV_CFDTMIEC_LENGTH * sizeof(uint32_t));

    /* Configure channel error interrupts */
    R_CANFD->CFDC[channel].CTR = p_extend->error_interrupts | R_CANFD_CFDC_CTR_CHMDC_Msk;

    /* Enable channel interrupts */

    if (p_cfg->error_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->error_irq, p_cfg->ipl, p_ctrl);
    }

    if (p_cfg->tx_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->tx_irq, p_cfg->ipl, p_ctrl);
    }

    /* Set global mode to Operation and wait for transition */
    r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_GLOBAL_OPERATION);

    /* Transition to Channel Operation */
    r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_NORMAL);

    /* Set current operation modes */
    p_ctrl->operation_mode = CAN_OPERATION_MODE_NORMAL;
    p_ctrl->test_mode      = CAN_TEST_MODE_DISABLED;

    /* Set driver to open */
    p_ctrl->open = CANFD_OPEN;

    return err;
}

/***************************************************************************************************************//**
 * Close the CANFD channel.
 *
 * @retval FSP_SUCCESS               Channel closed successfully.
 * @retval FSP_ERR_NOT_OPEN          Control block not open.
 * @retval FSP_ERR_ASSERTION         Null pointer presented.
 *****************************************************************************************************************/
fsp_err_t R_CANFD_Close (can_ctrl_t * const p_api_ctrl)
{
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;

#if CANFD_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == CANFD_OPEN, FSP_ERR_NOT_OPEN);
#endif

    /* Set driver to closed */
    p_ctrl->open = 0U;

    /* Get config struct */
    can_cfg_t * p_cfg = (can_cfg_t *) p_ctrl->p_cfg;

    /* Disable channel interrupts */

    if (p_cfg->error_irq >= 0)
    {
        R_BSP_IrqDisable(p_cfg->error_irq);
    }

    if (p_cfg->tx_irq >= 0)
    {
        R_BSP_IrqDisable(p_cfg->tx_irq);
    }

    /* Disable Global Error interrupt if the handler channel is being closed */
    if (CANFD_CFG_GLOBAL_ERROR_CH == p_cfg->channel)
    {
        R_BSP_IrqDisable(VECTOR_NUMBER_CAN_GLERR);
    }

#if !BSP_FEATURE_CANFD_LITE

    /* Set channel to Sleep if other is open, otherwise reset/stop CANFD module */
    if (gp_ctrl[!p_cfg->channel])
    {
        r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_SLEEP);
    }
    else
#endif
    {
        /* Disable RX FIFO interrupt */
        R_BSP_IrqDisable(VECTOR_NUMBER_CAN_RXF);

        /* Transition to Global Sleep */
        r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_GLOBAL_RESET);
        r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_GLOBAL_SLEEP);

        /* Stop CANFD module */
        R_BSP_MODULE_STOP(FSP_IP_CANFD, 0);
    }

    /* Reset global control struct pointer */
    gp_ctrl[p_cfg->channel] = NULL;

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Write data to the CANFD channel.
 *
 * Example:
 * @snippet r_canfd_example.c R_CANFD_Write
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_CAN_TRANSMIT_NOT_READY   Transmit in progress, cannot write data at this time.
 * @retval FSP_ERR_INVALID_ARGUMENT         Data length or buffer number invalid.
 * @retval FSP_ERR_INVALID_MODE             An FD option was set on a non-FD frame.
 * @retval FSP_ERR_ASSERTION                One or more pointer arguments is NULL.
 * @retval FSP_ERR_UNSUPPORTED              FD is not supported on this MCU.
 *****************************************************************************************************************/
fsp_err_t R_CANFD_Write (can_ctrl_t * const p_api_ctrl, uint32_t buffer, can_frame_t * const p_frame)
{
#if CANFD_CFG_PARAM_CHECKING_ENABLE
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;

    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_frame);
    FSP_ERROR_RETURN(p_ctrl->open == CANFD_OPEN, FSP_ERR_NOT_OPEN);

 #if !BSP_FEATURE_CANFD_LITE

    /* CANFD channels have 16 TX message buffers each (0-7, 32-39) */
    FSP_ERROR_RETURN((buffer <= 7U) || (buffer - 32U <= 7U), FSP_ERR_INVALID_ARGUMENT);
 #else

    /* CANFD Lite has 4 TX message buffers */
    FSP_ERROR_RETURN(buffer <= 3U, FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* Check DLC field */
 #if BSP_FEATURE_CANFD_FD_SUPPORT
    if (!(p_frame->options & CANFD_FRAME_OPTION_FD))
    {
        FSP_ERROR_RETURN(p_frame->data_length_code <= 8, FSP_ERR_INVALID_ARGUMENT);
        FSP_ERROR_RETURN(p_frame->options == 0, FSP_ERR_INVALID_MODE);
    }
    else if (p_frame->data_length_code > 0)
    {
        /* Make sure the supplied data size corresponds to a valid DLC value */
        FSP_ERROR_RETURN(0U != r_canfd_bytes_to_dlc(p_frame->data_length_code), FSP_ERR_INVALID_ARGUMENT);
    }
    else
    {
        /* Do nothing. */
    }

 #else
    FSP_ERROR_RETURN(p_frame->data_length_code <= 8, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_frame->options == 0, FSP_ERR_UNSUPPORTED);
 #endif
#else
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;
#endif

    /* Calculate global TX message buffer number */
    uint32_t txmb = buffer + (p_ctrl->p_cfg->channel * CANFD_PRV_TXMB_CHANNEL_OFFSET);

    /* Ensure MB is ready */
    FSP_ERROR_RETURN(0U == R_CANFD->CFDTMSTS_b[txmb].TMTSTS, FSP_ERR_CAN_TRANSMIT_NOT_READY);

    /* Set ID */
    R_CANFD->CFDTM[txmb].ID = p_frame->id | ((uint32_t) p_frame->type << R_CANFD_CFDTM_ID_TMRTR_Pos) |
                              ((uint32_t) p_frame->id_mode << R_CANFD_CFDTM_ID_TMIDE_Pos);
#if BSP_FEATURE_CANFD_FD_SUPPORT

    /* Set DLC */
    R_CANFD->CFDTM[txmb].PTR = (uint32_t) r_canfd_bytes_to_dlc(p_frame->data_length_code) <<
                               R_CANFD_CFDTM_PTR_TMDLC_Pos;

    /* Set FD bits (ESI, BRS and FDF) */
    R_CANFD->CFDTM[txmb].FDCTR = p_frame->options & 7U;
#else

    /* Set DLC */
    R_CANFD->CFDTM[txmb].PTR = (uint32_t) p_frame->data_length_code << R_CANFD_CFDTM_PTR_TMDLC_Pos;
#endif

    /* Copy data to register buffer */
    uint32_t  len    = p_frame->data_length_code;
    uint8_t * p_dest = (uint8_t *) R_CANFD->CFDTM[txmb].DF;
    uint8_t * p_src  = p_frame->data;
    while (len--)
    {
        *p_dest++ = *p_src++;
    }

    /* Request transmission */
    R_CANFD->CFDTMC[txmb] = 1;

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Read data from a CANFD Message Buffer or FIFO.
 *
 * Example:
 * snippet r_canfd_example.c R_CANFD_Read
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_INVALID_ARGUMENT         Buffer number invalid.
 * @retval FSP_ERR_ASSERTION                p_api_ctrl or p_frame is NULL.
 * @retval FSP_ERR_BUFFER_EMPTY             Buffer or FIFO is empty.
 *****************************************************************************************************************/
fsp_err_t R_CANFD_Read (can_ctrl_t * const p_api_ctrl, uint32_t buffer, can_frame_t * const p_frame)
{
#if CANFD_CFG_PARAM_CHECKING_ENABLE
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_frame);
    FSP_ERROR_RETURN(p_ctrl->open == CANFD_OPEN, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(buffer < CANFD_PRV_RXMB_MAX + CANFD_PRV_RX_FIFO_MAX, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    uint32_t not_empty;

    /* Return an error if the buffer or FIFO is empty */
    if (buffer < CANFD_PRV_RXMB_MAX)
    {
        not_empty = R_CANFD->CFDRMND0 & (1U << buffer);
    }
    else
    {
        not_empty = !(R_CANFD->CFDFESTS & (1U << (buffer - CANFD_PRV_RXMB_MAX)));
    }

    FSP_ERROR_RETURN(not_empty, FSP_ERR_BUFFER_EMPTY);

    /* Retrieve message from buffer */
    r_canfd_mb_read(buffer, p_frame);

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Switch to a different channel, global or test mode.
 *
 * Example:
 * @snippet r_canfd_example.c R_CANFD_ModeTransition
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_ASSERTION                Null pointer presented
 * @retval FSP_ERR_INVALID_MODE             Cannot change to the requested mode from the current global mode.
 *****************************************************************************************************************/
fsp_err_t R_CANFD_ModeTransition (can_ctrl_t * const   p_api_ctrl,
                                  can_operation_mode_t operation_mode,
                                  can_test_mode_t      test_mode)
{
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;
#if CANFD_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == CANFD_OPEN, FSP_ERR_NOT_OPEN);

    /* Get Global Status */
    uint32_t cfdgsts = R_CANFD->CFDGSTS;

 #if !BSP_FEATURE_CANFD_LITE

    /* Check to ensure the current mode is Global Halt when transitioning into or out of Internal Bus mode */
    FSP_ERROR_RETURN((cfdgsts & R_CANFD_CFDGSTS_GHLTSTS_Msk) || !((p_ctrl->test_mode != test_mode) &&
                                                                  ((CAN_TEST_MODE_INTERNAL_BUS == p_ctrl->test_mode) ||
                                                                   (CAN_TEST_MODE_INTERNAL_BUS == test_mode))),
                     FSP_ERR_INVALID_MODE);
 #else

    /* Internal Bus mode is not supported on this MCU */
    FSP_ERROR_RETURN(CAN_TEST_MODE_INTERNAL_BUS != test_mode, FSP_ERR_INVALID_MODE);
 #endif

    /* Check to ensure the current mode is Global Reset when transitioning into or out of Global Sleep (see Section
     * 32.3.2 "Global Modes" in the RA6M5 User's Manual (R01UH0891EJ0100) for details) */
    FSP_ERROR_RETURN(((cfdgsts & R_CANFD_CFDGSTS_GRSTSTS_Msk) && (CAN_OPERATION_MODE_RESET & operation_mode)) ||
                     (!(cfdgsts & R_CANFD_CFDGSTS_GSLPSTS_Msk) && (CAN_OPERATION_MODE_GLOBAL_SLEEP != operation_mode)),
                     FSP_ERR_INVALID_MODE);

    /* Check to ensure the current Global mode supports the requested Channel mode, if applicable. The requested mode
     * and the current global mode are converted into a number 0-3 corresponding to Operation, Halt, Reset and Sleep
     * respectively. The channel mode cannot be switched to a mode with an index lower than the current global mode. */
    if (operation_mode < CAN_OPERATION_MODE_GLOBAL_OPERATION)
    {
        FSP_ERROR_RETURN(g_mode_order[operation_mode] >= g_mode_order[cfdgsts & CANFD_PRV_CTR_MODE_MASK],
                         FSP_ERR_INVALID_MODE);
    }
#endif

    uint32_t channel = p_ctrl->p_cfg->channel;

    if (p_ctrl->test_mode != test_mode)
    {
#if !BSP_FEATURE_CANFD_LITE

        /* Follow the procedure for switching to Internal Bus mode given in Section 32.9.2.2 "Internal CAN Bus
         * Communication Test Mode" of the RA6M5 User's Manual (R01UH0891EJ0100) */
        if (CAN_TEST_MODE_INTERNAL_BUS == test_mode)
        {
            /* Disable channel test mode */
            R_CANFD->CFDC[channel].CTR_b.CTME = 0;

            /* Link channel to internal bus */
            R_CANFD->CFDGTSTCFG |= 1U << channel;

            /* Enable internal bus test mode */
            R_CANFD->CFDGTSTCTR = 1;
        }
        else
#endif
        {
#if !BSP_FEATURE_CANFD_LITE
            if (p_ctrl->test_mode == CAN_TEST_MODE_INTERNAL_BUS)
            {
                /* Unlink channel from internal bus */
                R_CANFD->CFDGTSTCFG &= ~(1U << channel);

                /* Disable global test mode if no channels are linked */
                if (!R_CANFD->CFDGTSTCFG)
                {
                    R_CANFD->CFDGTSTCTR = 0;
                }
            }
#endif

            /* Transition to Channel Halt when changing test modes */
            r_canfd_mode_transition(p_ctrl, CAN_OPERATION_MODE_HALT);

            /* Set channel test mode */
            uint32_t cfdcnctr = R_CANFD->CFDC[channel].CTR;
            cfdcnctr &= ~(R_CANFD_CFDC_CTR_CTME_Msk | R_CANFD_CFDC_CTR_CTMS_Msk);
            R_CANFD->CFDC[channel].CTR = cfdcnctr | ((uint32_t) test_mode << R_CANFD_CFDC_CTR_CTME_Pos);
        }

        p_ctrl->test_mode = test_mode;
    }

    if (p_ctrl->operation_mode != operation_mode)
    {
        r_canfd_mode_transition(p_ctrl, operation_mode);
    }

    return err;
}

/***************************************************************************************************************//**
 * Get CANFD state and status information for the channel.
 *
 * @retval  FSP_SUCCESS                     Operation succeeded.
 * @retval  FSP_ERR_NOT_OPEN                Control block not open.
 * @retval  FSP_ERR_ASSERTION               Null pointer presented
 *****************************************************************************************************************/
fsp_err_t R_CANFD_InfoGet (can_ctrl_t * const p_api_ctrl, can_info_t * const p_info)
{
#if CANFD_CFG_PARAM_CHECKING_ENABLE
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;

    /* Check pointers for NULL values */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_info);

    /* If channel is not open, return an error */
    FSP_ERROR_RETURN(p_ctrl->open == CANFD_OPEN, FSP_ERR_NOT_OPEN);
#else
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;
#endif

    uint32_t channel = p_ctrl->p_cfg->channel;

    uint32_t cfdcnsts = R_CANFD->CFDC[channel].STS;
    p_info->status               = cfdcnsts & UINT16_MAX;
    p_info->error_count_receive  = (uint8_t) ((cfdcnsts & R_CANFD_CFDC_STS_REC_Msk) >> R_CANFD_CFDC_STS_REC_Pos);
    p_info->error_count_transmit = (uint8_t) ((cfdcnsts & R_CANFD_CFDC_STS_TEC_Msk) >> R_CANFD_CFDC_STS_TEC_Pos);
    p_info->error_code           = R_CANFD->CFDC[channel].ERFL & UINT16_MAX;
    p_info->rx_mb_status         = R_CANFD->CFDRMND0;
    p_info->rx_fifo_status       = (~R_CANFD->CFDFESTS) & CANFD_PRV_RX_FIFO_STATUS_MASK;

    /* Clear error flags */
    R_CANFD->CFDC[channel].ERFL &= ~((uint32_t) UINT16_MAX);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref can_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_CANFD_CallbackSet (can_ctrl_t * const          p_api_ctrl,
                               void (                    * p_callback)(can_callback_args_t *),
                               void const * const          p_context,
                               can_callback_args_t * const p_callback_memory)
{
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) p_api_ctrl;

#if CANFD_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(CANFD_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if CANFD_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    can_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(can_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CAN)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
#if CANFD_CFG_PARAM_CHECKING_ENABLE
static bool r_canfd_bit_timing_parameter_check (can_bit_timing_cfg_t * const p_bit_timing)
{
    /* Check that prescaler is in range */
    FSP_ERROR_RETURN((p_bit_timing->baud_rate_prescaler <= CANFD_BAUD_RATE_PRESCALER_MAX) &&
                     (p_bit_timing->baud_rate_prescaler >= CANFD_BAUD_RATE_PRESCALER_MIN),
                     false);

    /* Check that TSEG1 > TSEG2 >= SJW for nominal bitrate per section 32.4.1.1 "Bit Timing Conditions" in the RA6M5
     * User's Manual (R01UH0891EJ0100). */

    /* Check Time Segment 1 is greater than Time Segment 2 */
    FSP_ERROR_RETURN((uint32_t) p_bit_timing->time_segment_1 > (uint32_t) p_bit_timing->time_segment_2, false);

    /* Check Time Segment 2 is greater than or equal to the synchronization jump width */
    FSP_ERROR_RETURN((uint32_t) p_bit_timing->time_segment_2 >= (uint32_t) p_bit_timing->synchronization_jump_width,
                     false);

    return true;
}

#endif

/*******************************************************************************************************************//**
 * Read from a Message Buffer or FIFO.
 *
 * NOTE: Does not index FIFOs.
 *
 * @param[in]     buffer     Index of buffer to read from (MBs 0-31, FIFOs 32+)
 * @param[in]     frame      Pointer to CAN frame to write to
 **********************************************************************************************************************/
static void r_canfd_mb_read (uint32_t buffer, can_frame_t * const frame)
{
    bool is_mb = buffer < CANFD_PRV_RXMB_MAX;

    /* Get pointer to message buffer (FIFOs use the same buffer structure) */
    volatile R_CANFD_CFDRM_Type * mb_regs =
        (is_mb) ? CANFD_PRV_RXMB_PTR(buffer) :
        (volatile R_CANFD_CFDRM_Type *) &(R_CANFD->CFDRF[buffer - CANFD_PRV_RXMB_MAX]);

    /* Get frame data. */
    uint32_t id = mb_regs->ID;

    /* Get the frame type */
    frame->type = (can_frame_type_t) ((id & R_CANFD_CFDRM_ID_RMRTR_Msk) >> R_CANFD_CFDRM_ID_RMRTR_Pos);

#if BSP_FEATURE_CANFD_FD_SUPPORT

    /* Get FD status bits (ESI, BRS and FDF) */
    frame->options = mb_regs->FDSTS & 7U;
#else
    frame->options = 0U;
#endif

    /* Get the frame ID */
    frame->id = id & R_CANFD_CFDRM_ID_RMID_Msk;

    /* Get the frame ID mode (IDE bit) */
    frame->id_mode = (can_id_mode_t) (id >> R_CANFD_CFDRM_ID_RMIDE_Pos);

    /* Get the frame data length code */
    frame->data_length_code = dlc_to_bytes[mb_regs->PTR >> R_CANFD_CFDRM_PTR_RMDLC_Pos];

    /* Copy data to frame */
    uint32_t  len    = frame->data_length_code;
    uint8_t * p_dest = frame->data;
    uint8_t * p_src  = (uint8_t *) mb_regs->DF;
    while (len--)
    {
        *p_dest++ = *p_src++;
    }

    if (is_mb)
    {
        /* Clear RXMB New Data bit */
        R_CANFD->CFDRMND0 &= ~(1U << buffer);
    }
    else
    {
        /* Increment RX FIFO pointer */
        R_CANFD->CFDRFPCTR[buffer - CANFD_PRV_RXMB_MAX] = UINT8_MAX;
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to CAN instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void r_canfd_call_callback (canfd_instance_ctrl_t * p_ctrl, can_callback_args_t * p_args)
{
    can_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    can_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        canfd_prv_ns_callback p_callback = (canfd_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Error ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common error function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void canfd_error_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Get IRQ and context */
    IRQn_Type               irq    = R_FSP_CurrentIrqGet();
    canfd_instance_ctrl_t * p_ctrl = (canfd_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    can_callback_args_t     args = {0U};
    canfd_instance_ctrl_t * p_callback_ctrl;

    if (VECTOR_NUMBER_CAN_GLERR == irq)
    {
        args.event = CAN_EVENT_ERR_GLOBAL;

        /* Read global error flags. */
        uint32_t cfdgerfl = R_CANFD->CFDGERFL;

        /* Global errors are in the top halfword of canfd_error_t; move and preserve ECC error flags. */
        args.error = ((cfdgerfl & UINT16_MAX) << 16) + ((cfdgerfl >> 16) << 28);

        /* Clear global error flags. */
        R_CANFD->CFDGERFL = 0;

        if (args.error & CANFD_ERROR_GLOBAL_MESSAGE_LOST)
        {
            /* Get lowest RX FIFO with Message Lost condition and clear the flag */
            args.buffer = __CLZ(__RBIT(R_CANFD->CFDFMSTS));
            R_CANFD->CFDRFSTS[args.buffer] &= ~R_CANFD_CFDRFSTS_RFMLT_Msk;
        }

        /* Choose ctrl block for the selected global error handler channel. */
        p_callback_ctrl = gp_ctrl[CANFD_CFG_GLOBAL_ERROR_CH];

        /* Set channel and context based on selected global error handler channel. */
        args.channel   = CANFD_CFG_GLOBAL_ERROR_CH;
        args.p_context = p_callback_ctrl->p_context;
    }
    else
    {
        args.event = CAN_EVENT_ERR_CHANNEL;

        /* Read and clear channel error flags. */
        uint32_t channel = p_ctrl->p_cfg->channel;
        args.error = R_CANFD->CFDC[channel].ERFL & UINT16_MAX; // Upper halfword contains latest CRC
        R_CANFD->CFDC[channel].ERFL = 0;

        /* Choose the channel provided by the interrupt context. */
        p_callback_ctrl = p_ctrl;

        args.channel   = channel;
        args.p_context = p_ctrl->p_context;
        args.buffer    = 0U;
    }

    /* Set remaining arguments and call callback */
    r_canfd_call_callback(p_callback_ctrl, &args);

    /* Clear IRQ */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Receive ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common receive function
 * and restores context if RTOS is used.
 **********************************************************************************************************************/
void canfd_rx_fifo_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    can_callback_args_t args;

    /* Get lowest FIFO requesting interrupt */
    uint32_t fifo = __CLZ(__RBIT(R_CANFD->CFDRFISTS));

    /* Only perform ISR duties if a FIFO has requested it */
    if (fifo < CANFD_PRV_RX_FIFO_MAX)
    {
        /* Set static arguments */
        args.event  = CAN_EVENT_RX_COMPLETE;
        args.buffer = fifo + CANFD_PRV_RXMB_MAX;

        /* Read from the FIFO until it is empty */
        while (!(R_CANFD->CFDFESTS & (1U << fifo)))
        {
            /* Get channel associated with the AFL entry */
            args.channel = R_CANFD->CFDRF[fifo].FDSTS_b.RFIFL;

            /* Read and index FIFO */
            r_canfd_mb_read(fifo + CANFD_PRV_RXMB_MAX, &args.frame);

            /* Set the remaining callback arguments */
            args.p_context = gp_ctrl[args.channel]->p_context;
            r_canfd_call_callback(gp_ctrl[args.channel], &args);
        }

        /* Clear RX FIFO Interrupt Flag */
        R_CANFD->CFDRFSTS[fifo] &= ~R_CANFD_CFDRFSTS_RFIF_Msk;
    }

    if (!R_CANFD->CFDRFISTS)
    {
        /* Clear interrupt in NVIC if there are no pending RX FIFO IRQs */
        R_BSP_IrqStatusClear(VECTOR_NUMBER_CAN_RXF);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls common transmit function
 * and restores context if RTOS is used.
 **********************************************************************************************************************/
void canfd_channel_tx_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type               irq     = R_FSP_CurrentIrqGet();
    canfd_instance_ctrl_t * p_ctrl  = (canfd_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uint32_t                channel = p_ctrl->p_cfg->channel;

    /* Set static arguments */
    can_callback_args_t args;
    args.channel   = channel;
    args.p_context = p_ctrl->p_context;

    /* Check the byte of CFDGTINTSTS0 that corresponds to the interrupting channel */
    uint32_t cfdgtintsts = *((uint8_t *) (&R_CANFD->CFDGTINTSTS0) + channel);
    while (cfdgtintsts)
    {
        uint32_t            txmb;
        volatile uint32_t * cfdtm_sts;

        channel <<= 1;

        /* Get relevant TX status register bank */
        if (cfdgtintsts & R_CANFD_CFDGTINTSTS0_TSIF0_Msk)
        {
            cfdtm_sts  = (volatile uint32_t *) &R_CANFD->CFDTMTCSTS[channel];
            args.event = CAN_EVENT_TX_COMPLETE;
        }
        else
        {
            cfdtm_sts  = (volatile uint32_t *) &R_CANFD->CFDTMTASTS[channel];
            args.event = CAN_EVENT_TX_ABORTED;
        }

        channel >>= 1;

        /* Calculate lowest TXMB with the specified event */
        txmb = __CLZ(__RBIT(*cfdtm_sts));
        txmb = (txmb < 8) ? txmb : __CLZ(__RBIT(*(cfdtm_sts + 1))) + CANFD_PRV_TXMB_OFFSET;

        /* Clear TX complete/abort flags */
        R_CANFD->CFDTMSTS_b[txmb + (CANFD_PRV_TXMB_CHANNEL_OFFSET * channel)].TMTRF = 0;

        /* Set the callback arguments */
        args.buffer = txmb;
        r_canfd_call_callback(p_ctrl, &args);

        /* Check for more interrupts on this channel */
        cfdgtintsts = *((uint8_t *) (&R_CANFD->CFDGTINTSTS0) + channel);
    }

    /* Clear interrupt */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function is used to switch the CANFD peripheral operation mode.
 * @param[in]  p_ctrl            - pointer to control structure
 * @param[in]  operation_mode    - destination operation mode
 **********************************************************************************************************************/
static void r_canfd_mode_transition (canfd_instance_ctrl_t * p_ctrl, can_operation_mode_t operation_mode)
{
    uint32_t channel = p_ctrl->p_cfg->channel;

    /* Get bit 7 from operation_mode to determine if this is a global mode change request */
    bool global_mode = (bool) (operation_mode >> 7);
    operation_mode &= 0xF;

    if (global_mode)
    {
        uint32_t cfdgctr = R_CANFD->CFDGCTR;

        r_canfd_mode_ctr_set(&R_CANFD->CFDGCTR, operation_mode);

        /* If CANFD is transitioning out of Reset the FIFOs need to be enabled. */
        if ((cfdgctr & R_CANFD_CFDGSTS_GRSTSTS_Msk) && !(operation_mode & CAN_OPERATION_MODE_RESET))
        {
            /* Get global config */
            canfd_global_cfg_t * p_global_cfg =
                ((canfd_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_global_cfg;

            /* Enable RX FIFOs */
            for (uint32_t i = 0; i < CANFD_PRV_RX_FIFO_MAX; i++)
            {
                R_CANFD->CFDRFCC[i] = p_global_cfg->rx_fifo_config[i];
            }
        }
    }
    else
    {
        uint32_t cfdcnctr = R_CANFD->CFDC[channel].CTR;

        if (((cfdcnctr & R_CANFD_CFDC_CTR_CSLPR_Msk) && (!(CAN_OPERATION_MODE_RESET & operation_mode))) ||
            ((!(cfdcnctr & CANFD_PRV_CTR_RESET_BIT)) && (CAN_OPERATION_MODE_SLEEP == operation_mode)))
        {
            /* Transition channel to Reset if a transition to/from Sleep is requested (see Section 32.3.3 "Channel
             * Modes" in the RA6M5 User's Manual (R01UH0891EJ0100) for details) */
            r_canfd_mode_ctr_set(&R_CANFD->CFDC[channel].CTR, CAN_OPERATION_MODE_RESET);
        }

        /* Request transition to selected mode */
        r_canfd_mode_ctr_set(&R_CANFD->CFDC[channel].CTR, operation_mode);
    }

    p_ctrl->operation_mode = (can_operation_mode_t) (R_CANFD->CFDC[channel].CTR & CANFD_PRV_CTR_MODE_MASK);
}

/*******************************************************************************************************************//**
 * Sets the provided CTR register to the requested mode and waits for the associated STS register to reflect the change
 * @param[in]  p_ctr_reg            - pointer to control register
 * @param[in]  operation_mode       - requested mode (not including global bits)
 **********************************************************************************************************************/
static void r_canfd_mode_ctr_set (volatile uint32_t * p_ctr_reg, can_operation_mode_t operation_mode)
{
    volatile uint32_t * p_sts_reg = p_ctr_reg + 1;

    /* See definitions for CFDCnCTR, CFDCnSTS, CFDGCTR and CFDGSTS in the RA6M5 User's Manual (R01UH0891EJ0100) */
    *p_ctr_reg = (*p_ctr_reg & ~CANFD_PRV_CTR_MODE_MASK) | operation_mode;
    FSP_HARDWARE_REGISTER_WAIT((*p_sts_reg & CANFD_PRV_CTR_MODE_MASK), operation_mode);
}

#if BSP_FEATURE_CANFD_FD_SUPPORT

/*******************************************************************************************************************//**
 * Converts bytes into a DLC value
 * @param[in]  bytes       Number of payload bytes
 **********************************************************************************************************************/
static uint8_t r_canfd_bytes_to_dlc (uint8_t bytes)
{
    if (bytes <= 8)
    {
        return bytes;
    }

    if (bytes <= 24)
    {
        return (uint8_t) (8U + ((bytes - 8U) / 4U));
    }

    return (uint8_t) (0xDU + ((bytes / 16U) - 2U));
}

#endif
