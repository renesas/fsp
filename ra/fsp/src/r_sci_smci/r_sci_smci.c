/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_smci.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "SMCI" in ASCII.  Used to determine if the control block is open. */
#define SCI_SMCI_OPEN                          (0x534D4349U) /*literal ascii 'SMCI'*/

#define SCI_SMCI_SCI_REG_SIZE                  (R_SCI1_BASE - R_SCI0_BASE)

/* The bit rate register is 8-bits, so the maximum value is 255. */
#define SCI_SMCI_BRR_MAX                       (255U)

/* Number of divisors in input clock calculation. */
#define SCI_SMCI_NUM_DIVISORS                  (4U)

#define SCI_SMCI_SSR_ERR_MASK                  (R_SCI0_SSR_SMCI_PER_Msk | R_SCI0_SSR_SMCI_ERS_Msk | \
                                                R_SCI0_SSR_SMCI_ORER_Msk)

#define SCI_SMCI_100_PERCENT_X_1000            (100000)

#define SCI_SMCI_MAX_BAUD_RATE_ERROR_X_1000    (20000) /* 20 percent Error */

#define SCI_SMCI_S_LOOKUP_TABLE_ENTRIES        (8)
#define SCI_SMCI_CKS_MASK                      (0x03)  /* only two bits*/

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_sci_smci_bcp_setting_const_t
{
    uint8_t  smr_smci_bcp01 : 2;
    uint8_t  scmr_bcp2      : 1;
    uint16_t bit_clock_conversion_number_s; /* number of base clock cycles S in a 1-bit data transfer,
                                             * referred to as S in HW Manual*/
} sci_smci_bcp_setting_const_t;

typedef struct st_sci_smci_ffmax_lut_const_t
{
    uint16_t f_value;
    uint32_t freq_max;
} sci_smci_ffmax_lut_const_t;

typedef enum e_smci_clock_conversion_ratio_s
{
    SMCI_CLOCK_CONVERSION_RATIO_32          = 0U, ///< 32 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_64          = 1U, ///< 64 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_93          = 2U, ///< 93 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_128         = 3U, ///< 128 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_186         = 4U, ///< 186 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_256         = 5U, ///< 256 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_372         = 6U, ///< 372 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_512         = 7U, ///< 512 base clock cycles for 1-bit period
    SMCI_CLOCK_CONVERSION_RATIO_UNSUPPORTED = 8U, ///< Unsupported Clock Cycles
} smci_clock_conversion_ratio_s_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_sci_irqs_cfg(sci_smci_instance_ctrl_t * const p_ctrl, smci_cfg_t const * const p_cfg);
static void r_sci_smci_config_set(sci_smci_instance_ctrl_t * const p_ctrl,
                                  smci_transfer_mode_t           * p_transfer_mode_params);
static fsp_err_t r_sci_smci_brr_calculate(smci_speed_params_t const * const p_speed_params,
                                          uint32_t                          baud_rate_error_x_1000,
                                          smci_baud_setting_t * const       p_baud_setting);
static void r_sci_smci_baud_set(R_SCI0_Type * p_sci_reg, smci_baud_setting_t const * const p_baud_setting);

void sci_smci_rxi_isr(void);
void sci_smci_txi_isr(void);
void sci_smci_eri_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Base Clock Cycles for 1-bit transfer period information (Smart Card mode) */

/* this is just a lookup table for S (which is different than F)*/

/* This table is the "Combinations of the SCMR.BCP2 and SMR_SMCI.BCP[1:0] bits" table from the
 * HW user manual */
static const sci_smci_bcp_setting_const_t g_bit_clock_conversion_setting_lut[SCI_SMCI_S_LOOKUP_TABLE_ENTRIES] =
{
    /*bcp01,bcp2,S*/
    {0U, 1U, 32 },
    {1U, 1U, 64 },
    {0U, 0U, 93 },
    {1U, 0U, 128},
    {2U, 0U, 186},
    {3U, 1U, 256},
    {2U, 1U, 372},
    {3U, 0U, 512}
};

/* This is "Table 7 — Fi and f (max.) Bits" & from ISO/IEC7816-3  Third edition
 * 2006-11-01".. NOTE only the F values that can yield at last one possible supported
 * S value are listed. */
static const sci_smci_ffmax_lut_const_t g_f_value_lut[SMCI_CLOCK_CONVERSION_INTEGER_MAX] =
{
    [0]  = {372,  4000000       },
    [1]  = {372,  5000000       },
    [2]  = {0,    0             },     /* there is no value of the associated f value (558) that the SMCI hardware will support*/
    [3]  = {744,  8000000       },
    [4]  = {1116, 1200000       },
    [5]  = {1488, 1600000       },
    [6]  = {1860, 2000000       },
    [7]  = {0,    0             },
    [8]  = {0,    0             },
    [9]  = {512,  5000000       },
    [10] = {768,  7500000       },
    [11] = {1024, 10000000      },
    [12] = {1536, 15000000      },
    [13] = {2048, 20000000      },
    [14] = {0,    0             },
    [15] = {0,    0             }
};

static const uint8_t g_d_value_lut[SMCI_BAUDRATE_ADJUSTMENT_INTEGER_MAX] =
{
    [0]  = 0,
    [1]  = 1,
    [2]  = 2,
    [3]  = 4,
    [4]  = 8,
    [5]  = 16,
    [6]  = 32,
    [7]  = 64,
    [8]  = 12,
    [9]  = 20,
    [10] = 0,
    [11] = 0,
    [12] = 0,
    [13] = 0,
    [14] = 0,
    [15] = 0
};

/* This is the divisor 2^(2n+1) as defined in Table 27.6 "Relationship between N setting in BRR and bit rate B" in the RA4M2 manual
 * R01UH0892EJ0110 or the relevant section for the MCU being used. */
static const uint8_t g_clock_div_setting[SCI_SMCI_NUM_DIVISORS] =
{
    2U,
    8U,
    32U,
    128U
};

/* SMCI on SCI HAL API mapping for SMCI interface */
const smci_api_t g_smci_on_sci =
{
    .open            = R_SCI_SMCI_Open,
    .close           = R_SCI_SMCI_Close,
    .write           = R_SCI_SMCI_Write,
    .read            = R_SCI_SMCI_Read,
    .transferModeSet = R_SCI_SMCI_TransferModeSet,
    .baudSet         = R_SCI_SMCI_BaudSet,
    .statusGet       = R_SCI_SMCI_StatusGet,
    .clockControl    = R_SCI_SMCI_ClockControl,
    .callbackSet     = R_SCI_SMCI_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup SCI_SMCI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the Smart Card Interface driver based on the input configurations. The interface stays in the clock-off
 * state without enabling reception at the end of this function. ISO7816-3 default communication parameters are used to initial
 * ize SMCI port speed and parameters, as the ATR message is always sent in that format.  Only if Inverse convention is
 * expected should the transfer mode be changed after reset.  Implements @ref smci_api_t::open
 *
 * @param[inout]  p_api_ctrl               Pointer to SMCI control block that is to be opened
 * @param[in] p_cfg                        Pointer to the config structure that shall be used to set parameters of the SMCI
 *                                         baud calculations needed to be have done and set into
 *                                         p_cfg->p_extend->p_smci_baud_setting
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to SMCI control block or configuration structure is NULL.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT The requested channel does not exist on this MCU.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_Open (smci_ctrl_t * const p_api_ctrl, smci_cfg_t const * const p_cfg)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;
    sci_smci_extended_cfg_t  * p_ext;
    smci_transfer_mode_t       comm_params;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    FSP_ERROR_RETURN(SCI_SMCI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);
#endif

    p_ext = (sci_smci_extended_cfg_t *) p_cfg->p_extend;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_cfg->p_callback);
    FSP_ASSERT(p_ext);
    FSP_ASSERT(p_ext->p_smci_baud_setting);

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    p_ctrl->p_reg = ((R_SCI0_Type *) (R_SCI0_BASE + (SCI_SMCI_SCI_REG_SIZE * p_cfg->channel)));
    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    comm_params.protocol   = SMCI_PROTOCOL_TYPE_T0;
    comm_params.convention = SMCI_CONVENTION_TYPE_DIRECT;
    comm_params.gsm_mode   = false;

    /* Configure the interrupts. */
    r_sci_irqs_cfg(p_ctrl, p_cfg);

    /* Enable the SCI channel */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Initialize registers as defined in section 34.6.5 "SCI Initialization in Smart Card Mode" in the RA6M3 manual
     * R01UH0886EJ0100 or the relevant section for the MCU being used. */
    r_sci_smci_config_set(p_ctrl, &comm_params);

    p_ctrl->p_tx_src          = NULL;
    p_ctrl->tx_src_bytes      = 0U;
    p_ctrl->p_rx_dest         = NULL;
    p_ctrl->rx_dest_bytes     = 0;
    p_ctrl->rx_bytes_received = 0;

    /* NOTE: Receiver and its interrupt are enabled at clock out. */
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqEnable(p_ctrl->p_cfg->eri_irq);

    /* NOTE: Transmitter and its interrupt are enabled in SCI_SMCI_Write(). */
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);

    r_sci_smci_baud_set(p_ctrl->p_reg, p_ext->p_smci_baud_setting);

    p_ctrl->open       = SCI_SMCI_OPEN;
    p_ctrl->smci_state = SMCI_STATE_IDLE_CLOCK_OFF;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Transmits user specified number of bytes from the source buffer pointer. Implements @ref smci_api_t::write
 *
 * @param[inout]  p_api_ctrl             Pointer to SMCI control block that is to be opened
 * @param[in]     p_src                  Pointer to buffer that will be written out
 * @param[in]     bytes                  Number of bytes to be transferred
 *
 * @retval  FSP_SUCCESS                  Data transmission started successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to SMCI control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A SMCI transmission is in progress
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_Write (smci_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;
    uint8_t scr;
#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_src);
    FSP_ASSERT(0U != bytes);
    FSP_ERROR_RETURN(0U == p_ctrl->tx_src_bytes, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    scr = p_ctrl->p_reg->SCR_SMCI;

    /* disable the receiver ,and enable the receiver*/
    scr &= (uint8_t) ~(R_SCI0_SCR_SMCI_RE_Msk | R_SCI0_SCR_SMCI_RIE_Msk);
    scr |= R_SCI0_SCR_SMCI_TE_Msk;

    p_ctrl->p_reg->SCR_SMCI = scr;

    /* The FIFO is not used, so the first write will be done from this function. Subsequent writes will be done
     * from txi_isr */
    p_ctrl->tx_src_bytes = bytes - 1;
    p_ctrl->p_tx_src     = p_src + 1;

    p_ctrl->smci_state = SMCI_STATE_TX_PROGRESSING;

    /* Enable the TX interrupt before putting data in TDR.. also enable RIE as it enables the error intterupts
     *  that may occur */
    p_ctrl->p_reg->SCR_SMCI |= (R_SCI0_SCR_SMCI_TIE_Msk | R_SCI0_SCR_SMCI_RIE_Msk);

    p_ctrl->p_reg->TDR = *(p_src);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Receiving is done at the isr level as
 *  there is no FIFO.  If 0 is passed in as the length, reception will always invoke the user callback.
 * Implements @ref smci_api_t::read
 *
 * @param[inout]  p_api_ctrl             Pointer to SMCI control block that is to be opened
 * @param[inout] p_dest                  Pointer to the buffer top be read into
 * @param[in] bytes                      Number of bytes to copy from the SMCI receive register
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to SMCI control block or read buffer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_Read (smci_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;
#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT((p_dest) || (bytes == 0));
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((bytes == 0) || (0U == p_ctrl->rx_dest_bytes - p_ctrl->rx_bytes_received), FSP_ERR_IN_USE);
#endif
    if (0 == bytes)                    /* 0 bytes indicate a reset of the read states */
    {
        p_ctrl->smci_state = SMCI_STATE_TX_RX_IDLE;
    }

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN((SMCI_STATE_TX_RX_IDLE == p_ctrl->smci_state), FSP_ERR_IN_USE);
#endif

    /* Transmit and receive interrupts must be disabled to start with */
    /* Disable transmit */
    p_ctrl->p_reg->SCR_SMCI &= (uint8_t) ~(R_SCI0_SCR_SMCI_TIE_Msk | R_SCI0_SCR_SMCI_TE_Msk | R_SCI0_SCR_SMCI_RIE_Msk);

    /* Save the destination address and size for use in rxi_isr. */
    p_ctrl->p_rx_dest         = p_dest;
    p_ctrl->rx_dest_bytes     = bytes;
    p_ctrl->rx_bytes_received = 0;

    /* Enable receiver and its interrupt */
    p_ctrl->p_reg->SCR_SMCI |= (R_SCI0_SCR_SMCI_RIE_Msk | R_SCI0_SCR_SMCI_RE_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the settings of block transfer mode and data transfer convention. The SCMR and SMR_SMCI registers
 * will be set according to the input arguments of protocol type, data convention type, and mode.
 * Implements @ref smci_api_t::transferModeSet
 *
 * @param[inout] p_api_ctrl             Pointer to SMCI control block that is to be modified
 * @param[in]    p_transfer_mode_params Pointer to SMCI settings like protocol, convention, and gsm_mode
 *
 * @warning This terminates any in-progress transmission and reception.
 *
 * @retval  FSP_SUCCESS                  Transfer mode and data transfer direction was successfully changed.
 * @retval  FSP_ERR_IN_USE               Unable to change transfer mode as device has clock off or is actively RX or TX
 * @retval  FSP_ERR_ASSERTION            Null pointer was passed as a parameter
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_TransferModeSet (smci_ctrl_t * const                p_api_ctrl,
                                      smci_transfer_mode_t const * const p_transfer_mode_params)

{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_transfer_mode_params);

    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    FSP_ERROR_RETURN((SMCI_STATE_IDLE_CLOCK_OFF == p_ctrl->smci_state) ||
                     (SMCI_STATE_TX_RX_IDLE == p_ctrl->smci_state),
                     FSP_ERR_IN_USE);
#endif

    /* Save SCR configurations except transmit interrupts. Resuming transmission after reconfiguring transfer mode is
     * not supported. */
    uint8_t preserved_scr_smci = p_ctrl->p_reg->SCR_SMCI &
                                 (uint8_t) ~((R_SCI0_SCR_SMCI_TIE_Msk) | (R_SCI0_SCR_SMCI_TE_Msk));

    /* If TX and RX arent disable writing to speed and mode registers wont occure according to datasheet*/
    p_ctrl->p_reg->SCR_SMCI = preserved_scr_smci & (uint8_t) ~(R_SCI0_SCR_SMCI_TE_Msk | R_SCI0_SCR_SMCI_RE_Msk);
    p_ctrl->p_tx_src        = NULL;

    uint8_t smr_smci = 0;
    uint8_t scmr     = 0;

    smr_smci = p_ctrl->p_reg->SMR_SMCI;
    scmr     = p_ctrl->p_reg->SCMR;

    /* Enable parity for SMCI mode */
    smr_smci |= (uint8_t) (R_SCI0_SMR_SMCI_PE_Msk);

    if (SMCI_PROTOCOL_TYPE_T1 == p_transfer_mode_params->protocol)
    {
        smr_smci |= (uint8_t) (SMCI_PROTOCOL_TYPE_T1 << R_SCI0_SMR_SMCI_BLK_Pos);
    }
    else
    {
        smr_smci &= (uint8_t) (~(SMCI_PROTOCOL_TYPE_T1 << R_SCI0_SMR_SMCI_BLK_Pos));
    }

    if (SMCI_CONVENTION_TYPE_DIRECT == p_transfer_mode_params->convention)
    {
        smr_smci &= (uint8_t) (~R_SCI0_SMR_SMCI_PM_Msk);
        scmr     &= (uint8_t) (~R_SCI0_SCMR_SINV_Msk);
        scmr     &= (uint8_t) (~R_SCI0_SCMR_SDIR_Msk);
    }
    else if (SMCI_CONVENTION_TYPE_INVERSE == p_transfer_mode_params->convention)
    {
        smr_smci |= R_SCI0_SMR_SMCI_PM_Msk; /* Because the SINV bit of the MCU only inverts data bits D7 to D0, */
                                            /* write 1 to the PM bit in SMR_SMCI to invert the parity bit for */
                                            /* both transmission and reception.*/
        scmr |= R_SCI0_SCMR_SINV_Msk;
        scmr |= R_SCI0_SCMR_SDIR_Msk;
    }
    else
    {
        /* unhandled convention type*/
    }

    /* save off and set thwe GSM mode */
    if (p_transfer_mode_params->gsm_mode)
    {
        smr_smci |= (uint8_t) (R_SCI0_SMR_SMCI_GM_Msk);
    }
    else
    {
        smr_smci &= (uint8_t) (~R_SCI0_SMR_SMCI_GM_Msk);
    }

    p_ctrl->p_reg->SMR_SMCI = smr_smci;
    p_ctrl->p_reg->SCMR     = scmr;

    /* Restore all settings except transmit enable interrupts. */
    /*  Keep the receiver on, thats the normal idle state */
    p_ctrl->p_reg->SCR_SMCI = (preserved_scr_smci | R_SCI0_SCR_SMCI_RE_Msk | R_SCI0_SCR_SMCI_RIE_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the baud rate and clock output. p_baud_setting is a pointer to a smci_baud_setting_t structure that needs
 * to have already been filled by R_SCI_SMCI_BaudCalculate
 * Implements @ref smci_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 *
 * @param[inout] p_api_ctrl              Pointer to SMCI control block that is to be modified
 * @param[in]    p_baud_setting          Pointer to baud setting information to be written to the SMCI hardware registers
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to SMCI control block or p_baud_setting is NUL
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_INVALID_ARGUMENT     The p_baud_setting does not seem to be set correctly
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_BaudSet (smci_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(((smci_baud_setting_t *) p_baud_setting)->computed_baud_rate != 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Save SCR configurations except transmit interrupts. Resuming transmission after reconfiguring baud settings is
     * not supported. */
    uint8_t preserved_scr_smci = p_ctrl->p_reg->SCR_SMCI & (uint8_t) ~(R_SCI0_SCR_SMCI_TIE_Msk);

    /* If TX and RX arent disable writing to speed and mode registers wont occure according to datasheet*/
    p_ctrl->p_reg->SCR_SMCI = preserved_scr_smci & (uint8_t) ~(R_SCI0_SCR_SMCI_TE_Msk | R_SCI0_SCR_SMCI_RE_Msk);

    p_ctrl->p_tx_src = NULL;

    /* Apply new baud rate register settings. */
    r_sci_smci_baud_set(p_ctrl->p_reg, p_baud_setting);

    /* Restore all settings except transmit enable interrupts. */
    /*  Keep the receiver on, thats the normal idle state */
    p_ctrl->p_reg->SCR_SMCI = (preserved_scr_smci | R_SCI0_SCR_SMCI_RE_Msk | R_SCI0_SCR_SMCI_RIE_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the state of the driver and the # of bytes received since read was called
 * Implements @ref smci_api_t::statusGet
 *
 * @param[in]  p_api_ctrl     Pointer to SMCI control block of this SMCI instance
 * @param[out] p_status       Pointer structure that will be filled in with status info
 *
 * @retval  FSP_SUCCESS                  Information stored in provided p_info.
 * @retval  FSP_ERR_ASSERTION            Pointer to SMCI control block, or info structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_StatusGet (smci_ctrl_t * const p_api_ctrl, smci_status_t * const p_status)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_status);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_status->smci_state = p_ctrl->smci_state;

    /* the number of bytes received */
    p_status->bytes_recvd = p_ctrl->rx_bytes_received;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable or disable the clock signal that is provided by interface the baud rate. When the clock is enabled, reception
 * is enabled at the end of this function. "Clock output control as defined in section 34.6.8 "Clock Output Control in
 * Smart Card Interface Mode" in the RA6M3 manual R01UH0886EJ0100 or the relevant section for the MCU being used.
 * Implements @ref smci_api_t::clockControl
 *
 * @warning This terminates any in-progress transmission and reception.
 *
 * @param[inout]  p_api_ctrl             Pointer to SMCI control block
 * @param[in]     clock_enable           true=Enable or false=disable the Smart Card Interface clock
 *
 * @retval  FSP_SUCCESS                  Clock output setting was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to SMCI control block is NULL
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_INVALID_MODE         Clock cannot be disabled if GSM mode isnt active
 *
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_ClockControl (smci_ctrl_t * const p_api_ctrl, bool clock_enable)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;
    uint8_t smci_temp;
#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* only allow clock off in GSM Mode */
    if (clock_enable == false)
    {
        FSP_ERROR_RETURN((1 == p_ctrl->p_reg->SMR_SMCI_b.GM), FSP_ERR_INVALID_MODE);
    }
#endif
    smci_temp = p_ctrl->p_reg->SCR_SMCI;

    /* Clock Enable control bit can be written only when TE=0 and RE=0
     * The setting of RIE and TIE are reset because resuming reception or transmission after clock state change is not supported */
    p_ctrl->p_reg->SCR_SMCI = smci_temp & (uint8_t) ~(R_SCI0_SCR_SMCI_RE_Msk |
                                                      R_SCI0_SCR_SMCI_TE_Msk | R_SCI0_SCR_SMCI_RIE_Msk |
                                                      R_SCI0_SCR_SMCI_TIE_Msk);

    if (clock_enable)
    {
        /* output clock */
        p_ctrl->p_reg->SCR_SMCI_b.CKE = 1;

        /* enable received transfer as default */
        p_ctrl->p_reg->SCR_SMCI |= R_SCI0_SCR_SMCI_RIE_Msk | R_SCI0_SCR_SMCI_RE_Msk;
        p_ctrl->p_reg->SCR_SMCI &= (uint8_t) ~(R_SCI0_SCR_SMCI_TIE_Msk | R_SCI0_SCR_SMCI_TE_Msk);

        /* indicate we are ready to transmit*/
        p_ctrl->smci_state = SMCI_STATE_TX_RX_IDLE;
    }
    else
    {
        /* stop clock */
        p_ctrl->p_reg->SCR_SMCI_b.CKE = 0;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements smci_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_CallbackSet (smci_ctrl_t * const          p_api_ctrl,
                                  void (                     * p_callback)(smci_callback_args_t *),
                                  void * const                 p_context,
                                  smci_callback_args_t * const p_callback_memory)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_SMCI_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    smci_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(smci_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter.
 * Implements @ref smci_api_t::close
 *
 * @param[in]  p_api_ctrl            Pointer to SMCI control block that is reqested to close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to SMCI control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_Close (smci_ctrl_t * const p_api_ctrl)
{
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) p_api_ctrl;
#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_SMCI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    /* Disable interrupts, receiver, and transmitter. Disable baud clock output.*/
    p_ctrl->p_reg->SCR_SMCI = 0U;

    /* Disable reception irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);

    /* Disable transmission irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    /* Enter module stop mode */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates baud rate register settings. Evaluates and determines the best possible settings set to the baud rate
 * related registers. And then updates the SCI registers.
 *
 * @param[in]  p_speed_params            structure including speed defining paramets, baud, F, D, and max frequency
 * @param[in]  baud_rate_error_x_1000    &lt;baud_rate_percent_error&gt; x 1000 required for module to function.
 *                                       Absolute max baud_rate_error is 20000 (20%) according to the ISO spec.
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate setting calculation successful
 * @retval     FSP_ERR_ASSERTION         p_speed params or p_baud is a null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Baud rate is '0', freq is '0', or error in
 *                                       calculated baud rate is larger than 20%.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SMCI_BaudCalculate (smci_speed_params_t const * const p_speed_params,
                                    uint32_t                          baud_rate_error_x_1000,
                                    void * const                      p_baud_setting)
{
    smci_baud_setting_t * p_baud = (smci_baud_setting_t *) p_baud_setting;

#if (SCI_SMCI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_speed_params);
    FSP_ERROR_RETURN((0U != p_speed_params->baudrate), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != g_f_value_lut[p_speed_params->fi].freq_max), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(SCI_SMCI_MAX_BAUD_RATE_ERROR_X_1000 > baud_rate_error_x_1000, FSP_ERR_INVALID_ARGUMENT);
    FSP_ASSERT(p_baud);
#endif

    fsp_err_t err;

    /* Update the SCI baudrate registers configuration. The TE, RE should be set to 0 prior to this step */
    err = r_sci_smci_brr_calculate(p_speed_params, baud_rate_error_x_1000, p_baud);

    if (FSP_SUCCESS != err)
    {
        p_baud->computed_baud_rate = 0;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_SMCI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info for all interrupts.
 *
 * @param[in]  p_ctrl                    Pointer to SMCI control block
 * @param[in]  p_cfg                     Pointer to SMCI specific configuration structure
 **********************************************************************************************************************/
static void r_sci_irqs_cfg (sci_smci_instance_ctrl_t * const p_ctrl, smci_cfg_t const * const p_cfg)
{
    R_BSP_IrqCfg(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);
    R_BSP_IrqCfg(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
    R_BSP_IrqCfg(p_cfg->txi_irq, p_cfg->txi_ipl, p_ctrl);
}

/*******************************************************************************************************************//**
 * computes the brr register value required for the given input params
 * @param[in]  p_speed_params              Pointer to structure containing etu definition params
 * @param[in]  baud_rate_error_x_1000      Allowable baud rate error
 * @param[out] p_baud_setting              Pointer to structure containing computed values to achieve baud/error rate
 *
 * @retval  FSP_SUCCESS                  Register settings updated in provided p_baud_setting
 * @retval  FSP_ERR_INVALID_ARGUMENT     Cant achieve output etu/freq with given params
 **********************************************************************************************************************/
static fsp_err_t r_sci_smci_brr_calculate (smci_speed_params_t const * const p_speed_params,
                                           uint32_t                          baud_rate_error_x_1000,
                                           smci_baud_setting_t * const       p_baud_setting)
{
    uint32_t        max_baudrate    = 0U;
    static uint32_t actual_baudrate = 0U;
    int32_t         hit_bit_err     = SCI_SMCI_100_PERCENT_X_1000;
    static uint32_t divisor         = 0U;
    uint32_t        f_value         = 0U;
    uint32_t        freq_hz         = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);
    int32_t         err_divisor     = 0;
    int32_t         bit_err         = 0;
    uint32_t        temp_brr        = 0;
    uint32_t        s_value         = 0U;
    uint8_t         s_index         = 0;
    uint32_t        target_baudrate = 0U;

    target_baudrate = p_speed_params->baudrate;

    /* Find the best BRR (bit rate register) value in Smart Card mode */

    /* first determine if we can get to the spec'd baudrate withe params given*/
    f_value = (uint32_t) g_f_value_lut[p_speed_params->fi].f_value;

    max_baudrate = (g_d_value_lut[p_speed_params->di] * g_f_value_lut[p_speed_params->fi].freq_max) / f_value;

    s_value = f_value / g_d_value_lut[p_speed_params->di];
    if (target_baudrate > max_baudrate)
    {
        /* Error out if the parameters supplied will not allow the baud rate generated to be within error range */
        FSP_ERROR_RETURN(((((target_baudrate - max_baudrate) * 100000) / max_baudrate) < baud_rate_error_x_1000),
                         FSP_ERR_INVALID_ARGUMENT);
        target_baudrate = max_baudrate;
    }

    /* validate that a S value for the  given F and D exists on the SMCI hardware*/
    /* find the S value that corresponds, from our look up table */
    while ((s_index < SCI_SMCI_S_LOOKUP_TABLE_ENTRIES) &&
           (s_value != g_bit_clock_conversion_setting_lut[s_index].bit_clock_conversion_number_s))
    {
        s_index++;
    }

    FSP_ERROR_RETURN((s_index != SCI_SMCI_S_LOOKUP_TABLE_ENTRIES), FSP_ERR_INVALID_ARGUMENT);

    for (uint8_t cks_value = 0U;
         cks_value < (SCI_SMCI_NUM_DIVISORS) && (hit_bit_err > ((int32_t) baud_rate_error_x_1000));
         cks_value++)
    {
        /* This is the based on smci brr setting as defined in Table 27.6 "Relationship between N setting in BRR and bit rate B" in the RA4M2 manual
         * R01UH0892EJ0110 or the relevant section for the MCU being used. */
        divisor = (uint32_t) g_clock_div_setting[cks_value] * target_baudrate *
                  s_value;
        temp_brr = freq_hz / divisor;

        if (temp_brr <= (SCI_SMCI_BRR_MAX + 1U))
        {
            if (temp_brr > 0U)
            {
                temp_brr -= 1U;

                /* Calculate the bit rate error. The formula is as follows:
                 *  bit rate error[%] = {(PCLK / (baud * div_coefficient * (BRR + 1)) - 1} x 100
                 *  calculates bit rate error[%] to three decimal places
                 */
                err_divisor = (int32_t) (divisor * (temp_brr + 1U));

                /* Promoting to 64 bits for calculation, but the final value can never be more than 32 bits, as
                 * described below, so this cast is safe.
                 *    1. (temp_brr + 1) can be off by an upper limit of 1 due to rounding from the calculation:
                 *       freq_hz / divisor, or:
                 *       freq_hz / divisor <= (temp_brr + 1) < (freq_hz / divisor) + 1
                 *    2. Solving for err_divisor:
                 *       freq_hz <= err_divisor < freq_hz + divisor
                 *    3. Solving for bit_err:
                 *       0 >= bit_err >= (freq_hz * 100000 / (freq_hz + divisor)) - 100000
                 *    4. freq_hz >= divisor (or temp_brr would be -1 and we would never enter this while loop), so:
                 *       0 >= bit_err >= 100000 / freq_hz - 100000
                 *    5. Larger frequencies yield larger bit errors (absolute value).  As the frequency grows,
                 *       the bit_err approaches -100000, so:
                 *       0 >= bit_err >= -100000
                 *    6. bit_err is between -100000 and 0.  This entire range fits in an int32_t type, so the cast
                 *       to (int32_t) is safe.
                 */
                bit_err = (int32_t) (((((int64_t) freq_hz) * SCI_SMCI_100_PERCENT_X_1000) /
                                      err_divisor) - SCI_SMCI_100_PERCENT_X_1000);

                /* Bit error will always be > 0 because we are effectively rouding down brr, so we dont need to
                 *  do absolute value */

                actual_baudrate =
                    (uint32_t) (freq_hz /
                                (g_clock_div_setting[cks_value] * s_value *
                                 (temp_brr + 1U)));

                /* If the absolute value of the bit rate error is less than the previous lowest absolute value of
                 *  bit rate error, then store these settings as the best value.
                 */
                if (bit_err < hit_bit_err)
                {
                    /* look up the settings based on the s_index we found above*/
                    p_baud_setting->smr_smci_clock_bits_b.bcp01 =
                        g_bit_clock_conversion_setting_lut[s_index].smr_smci_bcp01;
                    p_baud_setting->smr_smci_clock_bits_b.cks = (uint8_t) (cks_value & SCI_SMCI_CKS_MASK);
                    p_baud_setting->scmr_bcp2                 = g_bit_clock_conversion_setting_lut[s_index].scmr_bcp2;
                    p_baud_setting->brr = (uint8_t) temp_brr;
                    hit_bit_err         = bit_err;
                }
            }
        }
    }

    p_baud_setting->computed_baud_rate = actual_baudrate;
    FSP_ERROR_RETURN((p_baud_setting->brr > 0), FSP_ERR_INVALID_ARGUMENT);

    /* Return an error if the percent error is larger than the maximum percent error allowed for this instance */
    FSP_ERROR_RETURN((hit_bit_err <= (int32_t) baud_rate_error_x_1000), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Changes baud rate based on predetermined register settings.
 *
 * @param[in]  p_sci_reg       Base pointer for SCI registers
 * @param[in]  p_baud_setting  Pointer to other divisor related settings
 *
 * @note       The transmitter and receiver (TE and RE bits in SCR) must be disabled prior to calling this function.
 **********************************************************************************************************************/
static void r_sci_smci_baud_set (R_SCI0_Type * p_sci_reg, smci_baud_setting_t const * const p_baud_setting)
{
    uint8_t smr_smci =
        (p_sci_reg->SMR_SMCI) & (uint8_t)
        ~((R_SCI0_SMR_SMCI_BCP_Msk | R_SCI0_SMR_SMCI_CKS_Msk));

    /* Set Base Clock Pulse 0, 1 */
    /* and Clock Select */
    smr_smci |=
        (uint8_t) (((uint8_t) ((p_baud_setting->smr_smci_clock_bits_b.bcp01 << R_SCI0_SMR_SMCI_BCP_Pos) &
                               (uint8_t) R_SCI0_SMR_SMCI_BCP_Msk) |
                    ((uint8_t) ((p_baud_setting->smr_smci_clock_bits_b.cks << R_SCI0_SMR_SMCI_CKS_Pos) &
                                (uint8_t) R_SCI0_SMR_SMCI_CKS_Msk))));

    p_sci_reg->SMR_SMCI = smr_smci;

    /* Set Base Clock Pulse 2 */
    p_sci_reg->SCMR_b.BCP2 = p_baud_setting->scmr_bcp2;

    /* Set the BRR */
    p_sci_reg->BRR = p_baud_setting->brr;
}

/*******************************************************************************************************************//**
 * Configures SCI related registers for Smart Card mode.
 *
 * @param[in]     p_ctrl  Pointer to SMCI control structure
 * @param[in]     p_transfer_mode_params   Pointer to SMCI specific comm parameters
 **********************************************************************************************************************/
static void r_sci_smci_config_set (sci_smci_instance_ctrl_t * const p_ctrl,
                                   smci_transfer_mode_t           * p_transfer_mode_params)
{
    /* Stop communication and initialize CKE - Set TIE, RIE, TE, RE, TEIE, CKE to 0 */
    p_ctrl->p_reg->SCR_SMCI = 0U;

    p_ctrl->p_reg->SIMR1 = 0U;         /* ensure iic  mode is not selected */

    /* Set to smart card interface mode. */
    p_ctrl->p_reg->SIMR1_b.IICM = 0U;
    p_ctrl->p_reg->SCMR_b.SMIF  = 1;

    /* Write to SSR_SMCI after read SSR_SMCI - Set SSR_SMCI.ORER, ERS, PER to 0*/
    p_ctrl->p_reg->SSR_SMCI =
        (p_ctrl->p_reg->SSR_SMCI &
         (uint8_t) (~(R_SCI0_SSR_SMCI_ORER_Msk | R_SCI0_SSR_SMCI_ERS_Msk | R_SCI0_SSR_SMCI_PER_Msk)));

    /* Set the transmission or reception format in SPMR - Set SPMR.CKPH, CKPOL */
    p_ctrl->p_reg->SPMR_b.CKPOL = 0U;
    p_ctrl->p_reg->SPMR_b.CKPH  = 0U;

    /* Set the operation mode and the transmission or reception format in SMR_SMCI. */
    uint8_t smr_smci = p_ctrl->p_reg->SMR_SMCI;
    uint8_t scmr     = p_ctrl->p_reg->SCMR;

    /* Enable parity for SMCI mode */
    smr_smci |= (uint8_t) (R_SCI0_SMR_SMCI_PE_Msk);

    if (true == p_transfer_mode_params->gsm_mode)
    {
        smr_smci |= (uint8_t) (R_SCI0_SMR_SMCI_GM_Msk);
    }
    else
    {
        smr_smci &= (uint8_t) (~R_SCI0_SMR_SMCI_GM_Msk);
    }

    if (SMCI_PROTOCOL_TYPE_T1 == p_transfer_mode_params->protocol)
    {
        smr_smci |= (uint8_t) (SMCI_PROTOCOL_TYPE_T1 << R_SCI0_SMR_SMCI_BLK_Pos);
    }
    else
    {
        smr_smci &= (uint8_t) (~(SMCI_PROTOCOL_TYPE_T1 << R_SCI0_SMR_SMCI_BLK_Pos));
    }

    if (SMCI_CONVENTION_TYPE_DIRECT == p_transfer_mode_params->convention)
    {
        smr_smci &= (uint8_t) (~R_SCI0_SMR_SMCI_PM_Msk);
        scmr     &= (uint8_t) (~R_SCI0_SCMR_SINV_Msk);
        scmr     &= (uint8_t) (~R_SCI0_SCMR_SDIR_Msk);
    }
    else if (SMCI_CONVENTION_TYPE_INVERSE == p_transfer_mode_params->convention)
    {
        smr_smci |= (uint8_t) (R_SCI0_SMR_SMCI_PM_Msk); /* need to invert parity as well */
        scmr     |= R_SCI0_SCMR_SINV_Msk;
        scmr     |= R_SCI0_SCMR_SDIR_Msk;
    }
    else
    {
        /* unhandled convention type*/
    }

    p_ctrl->p_reg->SEMR = 0;

    p_ctrl->p_reg->SMR_SMCI = smr_smci;

    /* Set the transmission or reception format in to 8-bit mode */
    scmr               |= R_SCI0_SCMR_CHR1_Msk;
    p_ctrl->p_reg->SCMR = scmr;

    /* Set SPTR to initial value */
    p_ctrl->p_reg->SPTR = (uint8_t) ~(R_SCI0_SPTR_SPB2IO_Msk | R_SCI0_SPTR_RINV_Msk | R_SCI0_SPTR_TINV_Msk);
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to SMCI instance control block
 * @param[in]     data       See smci_callback_args_t in r_smci_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sci_smci_call_callback (sci_smci_instance_ctrl_t * p_ctrl, uint8_t data, smci_event_t event)
{
    smci_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    smci_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->channel   = p_ctrl->p_cfg->channel;
    p_args->data      = data;
    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        sci_smci_prv_ns_callback p_callback = (sci_smci_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Receiver ISR receives data into the receive buffer or initiates user callback.
 *
 **********************************************************************************************************************/
void sci_smci_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint8_t data;

    data = p_ctrl->p_reg->RDR;

    if (0 == (p_ctrl->rx_dest_bytes - p_ctrl->rx_bytes_received))
    {
        /* Call user callback with the data. */
        r_sci_smci_call_callback(p_ctrl, data, SMCI_EVENT_RX_CHAR);
    }
    else
    {
        *p_ctrl->p_rx_dest         = data;
        p_ctrl->p_rx_dest         += 1;
        p_ctrl->rx_bytes_received += 1;
        p_ctrl->smci_state         = SMCI_STATE_RX_PROGRESSING;
        if (0 == p_ctrl->rx_dest_bytes - p_ctrl->rx_bytes_received)
        {
            p_ctrl->smci_state = SMCI_STATE_TX_RX_IDLE;
            r_sci_smci_call_callback(p_ctrl, 0U, SMCI_EVENT_RX_COMPLETE);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Transmit ISR, loads the transmit register from the transmit buffer, until all data is sent
 *  after which callback is initiated
 *
 **********************************************************************************************************************/
void sci_smci_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (0U != p_ctrl->tx_src_bytes)
    {
        /* Write 1byte (uint8_t) data to (uint8_t) data register */
        p_ctrl->p_reg->TDR = *(p_ctrl->p_tx_src);

        /* Update pointer to the next data and number of remaining bytes in the control block. */
        p_ctrl->tx_src_bytes -= 1;
        p_ctrl->p_tx_src     += 1;
    }
    else
    {
        p_ctrl->p_tx_src   = NULL;
        p_ctrl->smci_state = SMCI_STATE_TX_RX_IDLE;

        uint8_t scr_temp = p_ctrl->p_reg->SCR_SMCI;
        scr_temp               &= (uint8_t) ~(R_SCI0_SCR_SMCI_TIE_Msk | R_SCI0_SCR_SMCI_TE_Msk);
        scr_temp               |= (R_SCI0_SCR_SMCI_RE_Msk);
        p_ctrl->p_reg->SCR_SMCI = scr_temp;

        r_sci_smci_call_callback(p_ctrl, 0U, SMCI_EVENT_TX_COMPLETE);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Error ISR, clears all three error Error Signal Status, Parity Error Flag, and Overrun Error Flag, then initiates
 *  the callback with an event code
 **********************************************************************************************************************/

void sci_smci_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_smci_instance_ctrl_t * p_ctrl = (sci_smci_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint8_t          data = 0U;
    volatile uint8_t forceRead;
    smci_event_t     event;

    /* Read data. */
    data = p_ctrl->p_reg->RDR;

    event = (smci_event_t) (p_ctrl->p_reg->SSR_SMCI & SCI_SMCI_SSR_ERR_MASK);

    p_ctrl->p_reg->SSR_SMCI &=
        (uint8_t) ~(R_SCI0_SSR_SMCI_ORER_Msk | R_SCI0_SSR_SMCI_ERS_Msk | R_SCI0_SSR_SMCI_PER_Msk);

    /* The data sheet says after writing you should readback 0 from the error bit */
    forceRead = p_ctrl->p_reg->SSR_SMCI;
    forceRead++;

    /* Call callback. */
    r_sci_smci_call_callback(p_ctrl, data, event);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
