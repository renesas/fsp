/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "r_i3c.h"
#include "r_i3c_cfg.h"

/* The address of the MCU Version Register on RA2E2 MCUs. Different error recovery procedures are used depending on the
 * version of the MCU (This is only used on RA2E2 devices). */
#define I3C_A2E2_VERSION    (*((uint8_t const *) 0x01001C20U))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_i3c_internal_state
{
    I3C_INTERNAL_STATE_DISABLED,
    I3C_INTERNAL_STATE_MASTER_IDLE,
    I3C_INTERNAL_STATE_MASTER_ENTDAA        = I3C_EVENT_ADDRESS_ASSIGNMENT_COMPLETE,
    I3C_INTERNAL_STATE_MASTER_WRITE         = I3C_EVENT_WRITE_COMPLETE,
    I3C_INTERNAL_STATE_MASTER_READ          = I3C_EVENT_READ_COMPLETE,
    I3C_INTERNAL_STATE_MASTER_COMMAND_WRITE = I3C_EVENT_COMMAND_COMPLETE,
    I3C_INTERNAL_STATE_MASTER_COMMAND_READ  = (I3C_EVENT_COMMAND_COMPLETE | (0x80U)),
    I3C_INTERNAL_STATE_SLAVE_IDLE,
    I3C_INTERNAL_STATE_SLAVE_IBI = I3C_EVENT_IBI_WRITE_COMPLETE,
} i3c_internal_state_t;

typedef enum e_i3c_slave_error_recovery_type
{
    I3C_SLAVE_ERROR_RECOVERY_TYPE_WRITE = 0,
    I3C_SLAVE_ERROR_RECOVERY_TYPE_READ  = 1,
    I3C_SLAVE_ERROR_RECOVERY_TYPE_IBI   = 2,
    I3C_SLAVE_ERROR_RECOVERY_TYPE_OTHER = 2,
} i3c_slave_error_recovery_type_t;

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define I3C_OPEN                                     (('I' << 16U) | ('3' << 8U) | ('C' << 0U))

/* Bitfield definitions for Command Descriptor fields. */
#define I3C_CMD_DESC_CMD_ATTR_Pos                    (0U)
#define I3C_CMD_DESC_CMD_ATTR_Msk                    (7U << I3C_CMD_DESC_CMD_ATTR_Pos)
#define I3C_CMD_DESC_CND_ATTR_XFER                   (0U)
#define I3C_CMD_DESC_CND_ATTR_IMMED_DATA_XFER        (1U)
#define I3C_CMD_DESC_CMD_ATTR_ADDR_ASSGN_CMD         (2U)
#define I3C_CMD_DESC_TID_Pos                         (3U)
#define I3C_CMD_DESC_TID_Msk                         (0x0FU << I3C_CMD_DESC_TID_Pos)
#define I3C_CMD_DESC_CMD_Pos                         (7U)
#define I3C_CMD_DESC_CMD_Msk                         (0xFFU << I3C_CMD_DESC_CMD_Pos)
#define I3C_CMD_DESC_DEV_INDEX_Pos                   (16U)
#define I3C_CMD_DESC_DEV_INDEX_Msk                   (0x01FFU << I3C_CMD_DESC_DEV_INDEX_Pos)
#define I3C_CMD_DESC_ROC_Pos                         (30U)
#define I3C_CMD_DESC_ROC_Msk                         (1U << I3C_CMD_DESC_ROC_Pos)
#define I3C_CMD_DESC_TOC_Pos                         (31U)
#define I3C_CMD_DESC_TOC_Msk                         (1U << I3C_CMD_DESC_TOC_Pos)

/* Command Descriptor definitions for Address Assign Commands. */
#define I3C_CMD_DESC_ADDR_ASSGN_DEV_COUNT_Pos        (26U)
#define I3C_CMD_DESC_ADDR_ASSGN_DEV_COUNT_Msk        (0x0FU << I3C_CMD_DESC_ADDR_ASSGN_DEV_COUNT_Pos)

/* Command Descriptor definitions for Regular Transfer Commands. */
#define I3C_CMD_DESC_XFER_CP_Pos                     (15U)
#define I3C_CMD_DESC_XFER_CP_Msk                     (1U << I3C_CMD_DESC_XFER_CP_Pos)
#define I3C_CMD_DESC_XFER_HJ_Pos                     (15U)
#define I3C_CMD_DESC_XFER_HJ_Msk                     (1U << I3C_CMD_DESC_XFER_HJ_Pos)
#define I3C_CMD_DESC_XFER_LENGTH_Pos                 (16U)
#define I3C_CMD_DESC_XFER_LENGTH_Msk                 (0xFFFFU << I3C_CMD_DESC_XFER_LENGTH_Pos)
#define I3C_CMD_DESC_XFER_MODE_Pos                   (26U)
#define I3C_CMD_DESC_XFER_MODE_Msk                   (0x07U << I3C_CMD_DESC_XFER_MODE_Pos)
#define I3C_CMD_DESC_XFER_RNW_Pos                    (29U)
#define I3C_CMD_DESC_XFER_RNW_Msk                    (1U << I3C_CMD_DESC_XFER_RNW_Pos)
#define I3C_CMD_DESC_XFER_MODE_I2C_STDBR             (0U)
#define I3C_CMD_DESC_XFER_MODE_I2C_EXDBR             (1U)
#define I3C_CMD_DESC_XFER_MODE_I3C_SDR_EXTBR_X2      (3U)
#define I3C_CMD_DESC_XFER_MODE_I3C_SDR_EXTBR_X4      (4U)

/* Command Descriptor definitions for Immediate Data Transfer Commands. */
#define I3C_CMD_DESC_IMMED_DATA_XFER_BYTE_CNT_Pos    (23U)

/* Bitfield definitions for the Response Status Descriptor fields. */
#define I3C_RESP_STATUS_DESC_DATA_LENGTH_Pos         (0U)
#define I3C_RESP_STATUS_DESC_DATA_LENGTH_Msk         (0xFFFFU << I3C_RESP_STATUS_DESC_DATA_LENGTH_Pos)
#define I3C_RESP_STATUS_DESC_TID_Pos                 (24U)
#define I3C_RESP_STATUS_DESC_TID_Msk                 (0x0FU << I3C_RESP_STATUS_DESC_TID_Pos)
#define I3C_RESP_STATUS_DESC_ERR_STATUS_Pos          (28U)
#define I3C_RESP_STATUS_DESC_ERR_STATUS_Msk          (0x0FU << I3C_RESP_STATUS_DESC_ERR_STATUS_Pos)

/* Bitfield definitions for Receive Status Descriptor fields. */
#define I3C_RECV_STATUS_DESC_DATA_LENGTH_Pos         (0U)
#define I3C_RECV_STATUS_DESC_DATA_LENGTH_Msk         (0xFFFFU << I3C_RECV_STATUS_DESC_DATA_LENGTH_Pos)
#define I3C_RECV_STATUS_DESC_CMD_Pos                 (16U)
#define I3C_RECV_STATUS_DESC_CMD_Msk                 (0xFFU << I3C_RECV_STATUS_DESC_CMD_Pos)
#define I3C_RECV_STATUS_DESC_SDR_R_W_TYPE_Pos        (23U)
#define I3C_RECV_STATUS_DESC_SDR_R_W_TYPE_Msk        (0x01U << I3C_RECV_STATUS_DESC_SDR_R_W_TYPE_Pos)
#define I3C_RECV_STATUS_DESC_ERR_STATUS_Pos          (24U)
#define I3C_RECV_STATUS_DESC_ERR_STATUS_Msk          (0x07U << I3C_RECV_STATUS_DESC_ERR_STATUS_Pos)
#define I3C_RECV_STATUS_DESC_TRANSFER_TYPE_Pos       (27U)
#define I3C_RECV_STATUS_DESC_TRANSFER_TYPE_Msk       (0x03U << I3C_RECV_STATUS_DESC_TRANSFER_TYPE_Pos)
#define I3C_RECV_STATUS_DESC_DEV_INDEX_Pos           (29U)
#define I3C_RECV_STATUS_DESC_DEV_INDEX_Msk           (0x07U << I3C_RECV_STATUS_DESC_DEV_INDEX_Pos)

/* Bitfield definitions for IBI Status Descriptor fields. */
#define I3C_IBI_STATUS_DESC_LENGTH_Pos               (0U)
#define I3C_IBI_STATUS_DESC_LENGTH_Msk               (0xFFU << I3C_IBI_STATUS_DESC_LENGTH_Pos)
#define I3C_IBI_STATUS_DESC_IBI_ID_Pos               (8U)
#define I3C_IBI_STATUS_DESC_IBI_ID_Msk               (0xFFU << I3C_IBI_STATUS_DESC_IBI_ID_Pos)
#define I3C_IBI_STATUS_DESC_LAST_STATUS_Pos          (24U)
#define I3C_IBI_STATUS_DESC_LAST_STATUS_Msk          (1U << I3C_IBI_STATUS_DESC_LAST_STATUS_Pos)
#define I3C_IBI_STATUS_DESC_TS_Pos                   (25U)
#define I3C_IBI_STATUS_DESC_TS_Msk                   (1U << I3C_IBI_STATUS_DESC_TS_Pos)
#define I3C_IBI_STATUS_DESC_ERR_STATUS_Pos           (26U)
#define I3C_IBI_STATUS_DESC_ERR_STATUS_Msk           (0x7U << I3C_IBI_STATUS_DESC_ERR_STATUS_Pos)
#define I3C_IBI_STATUS_DESC_IBI_ST_Pos               (31U)
#define I3C_IBI_STATUS_DESC_IBI_ST_Msk               (1U << I3C_IBI_STATUS_DESC_IBI_ST_Pos)

/* Address that is written by the slave during a Hot Join request. */
#define I3C_HOT_JOIN_ADDRESS                         (2U)

/* Mask for flushing the Read, Write, and Command FIFO. */
#define I3C_RSTCTRL_FIFO_FLUSH_Msk                   (R_I3C0_RSTCTL_CMDQRST_Msk | R_I3C0_RSTCTL_TDBRST_Msk | \
                                                      R_I3C0_RSTCTL_RDBRST_Msk)

#define I3C_MAX_PUSH_PULL_PERIOD                     (0x3FU)

/* Mask for converting the internal state into an I3C event. */
#define I3C_INTERNAL_EVENT_MASK                      (0x7FU)

/***********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

/* ISR function prototypes. */
void i3c_resp_isr(void);
void i3c_rx_isr(void);
void i3c_tx_isr(void);
void i3c_rcv_isr(void);
void i3c_ibi_isr(void);
void i3c_eei_isr(void);

static uint8_t i3c_address_parity(uint8_t address);

#if I3C_CFG_MASTER_SUPPORT
static uint32_t i3c_xfer_command_calculate(uint32_t dev_index, bool rnw, uint32_t bitrate_setting, bool restart);

#endif
static void i3c_fifo_read(i3c_instance_ctrl_t * p_ctrl, uint32_t bytes);
static void i3c_fifo_write(i3c_instance_ctrl_t * p_ctrl);
static void i3c_read_buffer_store(i3c_instance_ctrl_t * const    p_ctrl,
                                  i3c_read_buffer_descriptor_t * p_buffer_descriptor,
                                  uint32_t                       data_word,
                                  uint32_t                       num_bytes,
                                  i3c_event_t                    buffer_full_event);
static uint32_t     i3c_read_bytes_remaining_calculate(i3c_instance_ctrl_t * p_ctrl, uint32_t data_length);
static uint32_t     i3c_next_data_word_calculate(i3c_write_buffer_descriptor_t * p_buffer_descriptor);
static i3c_ctrl_t * i3c_isr_context_get(void);

#if I3C_CFG_MASTER_SUPPORT
static void i3c_master_error_recovery(i3c_instance_ctrl_t * p_ctrl, bool error_recovery_case_2);

#endif
#if I3C_CFG_SLAVE_SUPPORT
static void i3c_slave_error_recovery(i3c_instance_ctrl_t * p_ctrl, i3c_slave_error_recovery_type_t recovery_type);

#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* I3C implementation of I3C API. */
const i3c_api_t g_i3c_on_i3c =
{
    .open                          = R_I3C_Open,
    .enable                        = R_I3C_Enable,
    .deviceCfgSet                  = R_I3C_DeviceCfgSet,
    .masterDeviceTableSet          = R_I3C_MasterDeviceTableSet,
    .slaveStatusSet                = R_I3C_SlaveStatusSet,
    .deviceSelect                  = R_I3C_DeviceSelect,
    .dynamicAddressAssignmentStart = R_I3C_DynamicAddressAssignmentStart,
    .commandSend                   = R_I3C_CommandSend,
    .write                         = R_I3C_Write,
    .read                          = R_I3C_Read,
    .ibiWrite                      = R_I3C_IbiWrite,
    .ibiRead                       = R_I3C_IbiRead,
    .close                         = R_I3C_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup I3C
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure an I3C instance. Implements @ref i3c_api_t::open.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Open has already been called for this instance.
 * @retval FSP_ERR_UNSUPPORTED            A selected feature is not supported with the current configuration.
 **********************************************************************************************************************/
fsp_err_t R_I3C_Open (i3c_ctrl_t * const p_api_ctrl, i3c_cfg_t const * const p_cfg)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(I3C_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    i3c_extended_cfg_t const * p_extend = (i3c_extended_cfg_t const *) p_cfg->p_extend;
    FSP_ASSERT(0 <= p_extend->resp_irq);
    FSP_ASSERT(0 <= p_extend->rcv_irq);
    FSP_ASSERT(0 <= p_extend->tx_irq);
    FSP_ASSERT(0 <= p_extend->rx_irq);
    FSP_ASSERT(0 <= p_extend->ibi_irq);
    FSP_ASSERT(0 <= p_extend->eei_irq);
 #if 0U == I3C_CFG_MASTER_SUPPORT
    FSP_ERROR_RETURN(I3C_DEVICE_TYPE_MAIN_MASTER != p_cfg->device_type, FSP_ERR_UNSUPPORTED);
 #endif
 #if 0U == I3C_CFG_SLAVE_SUPPORT
    FSP_ERROR_RETURN(I3C_DEVICE_TYPE_SLAVE != p_cfg->device_type, FSP_ERR_UNSUPPORTED);
 #endif
#endif

    /* Initialize the internal state of the driver. */
    memset(p_ctrl, 0, sizeof(i3c_instance_ctrl_t));

    p_ctrl->open  = I3C_OPEN;
    p_ctrl->p_cfg = p_cfg;

    /* Clear the I3C Module Stop bit. */
    R_BSP_MODULE_START(FSP_IP_I3C, p_cfg->channel);

    /* Get a pointer to the I3C registers for this channel. */
#if BSP_FEATURE_I3C_NUM_CHANNELS > 1
    p_ctrl->p_reg = (R_I3C0_Type *) ((uint32_t) R_I3C0 + (p_cfg->channel * ((uint32_t) R_I3C1 - (uint32_t) R_I3C0)));
#else
    p_ctrl->p_reg = R_I3C0;
#endif

#if BSP_FEATURE_BSP_HAS_I3C_CLOCK
    p_ctrl->p_reg->CECTL = 1;
#endif

    /*
     * Reset the I3C Peripheral so that it is in a known state during initialization (See Figure 25.102 I3C Communication Flow
     * in the RA2E2 manual R01UH0919EJ0100).
     */
    p_ctrl->p_reg->BCTL_b.BUSE = 0;
    p_ctrl->p_reg->RSTCTL      = 1U;

    /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL, 0U);

    /* Set I3C mode. */
    p_ctrl->p_reg->PRTS = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable the I3C device.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_INVALID_MODE           This instance is already enabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_Enable (i3c_ctrl_t * const p_api_ctrl)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_DISABLED == p_ctrl->internal_state, FSP_ERR_INVALID_MODE);
#endif

    i3c_extended_cfg_t const * p_extend = (i3c_extended_cfg_t const *) p_ctrl->p_cfg->p_extend;

    /*
     * Write all remaining configuration settings (See Figure 25.102 I3C Communication Flow in the RA2E2
     * manual R01UH0919EJ0100).
     *
     * Configure the Normal IBI Data Segment Size used for receiving IBI data.
     */
    uint32_t nqthctl = 6U << R_I3C0_NQTHCTL_IBIDSSZ_Pos;

    /*
     * Enable Transfer Interrupts.
     * - Read Buffer Full Interrupt.
     * - Receive Status Queue Full Interrupt
     * - Response Queue Full Interrupt
     */
    uint32_t ntie = R_I3C0_NTIE_RDBFIE0_Msk |
                    R_I3C0_NTIE_RSPQFIE_Msk |
                    R_I3C0_NTIE_RSQFIE_Msk;

#if I3C_CFG_MASTER_SUPPORT
    if (I3C_DEVICE_TYPE_MAIN_MASTER == p_ctrl->p_cfg->device_type)
    {
        p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_IDLE;

        /* Enable the Queue Empty/Full Interrupt. */
        ntie |= R_I3C0_NTIE_IBIQEFIE_Msk;

        /* Write the standard and extended bitrate settings. */
        p_ctrl->p_reg->STDBR = p_extend->bitrate_settings.stdbr;
        p_ctrl->p_reg->EXTBR = p_extend->bitrate_settings.extbr;
    }
    else
#endif
    {
#if I3C_CFG_SLAVE_SUPPORT
        p_ctrl->internal_state = I3C_INTERNAL_STATE_SLAVE_IDLE;

        /*
         * Configure IBI queue threshold so that an IBI IRQ is generated when there is one empty entry in the
         * IBI transmit FIFO.
         */
        nqthctl |= 1U << R_I3C0_NQTHCTL_IBIQTH_Pos;

        /* Baudrate registers are not used in slave mode. */
        p_ctrl->p_reg->STDBR = 0;
        p_ctrl->p_reg->EXTBR = 0;
#endif
    }

    /*
     * Write settings to the Normal Queue Threshold Control Register.
     * - Normal Response Queue Threshold interrupt after one response is received.
     * - Normal IBI Queue Threshold interrupt after one IBI status is received.
     * - Normal IBI Data Segment Size set to 6 words.
     */
    p_ctrl->p_reg->NQTHCTL = nqthctl;

    /* Set the Normal Transfer Data Buffer threshold for transmit and receive (The only supported configuration
     * is two entries). */
    p_ctrl->p_reg->NTBTHCTL0 = 0;

    /* Set the Receive Status Queue Threshold to zero (Interrupt when there is one entry in the queue). */
    p_ctrl->p_reg->NRQTHCTL = 0;

    /* Enable the Internal Error Status Flag. */
    p_ctrl->p_reg->INSTE = R_I3C0_INSTE_INEE_Msk;

    /* Enable all Bus Status Flags. */
    p_ctrl->p_reg->BSTE = (R_I3C0_BSTE_STCNDDE_Msk |
                           R_I3C0_BSTE_SPCNDDE_Msk |
                           R_I3C0_BSTE_HDREXDE_Msk |
                           R_I3C0_BSTE_NACKDE_Msk |
                           R_I3C0_BSTE_TENDE_Msk |
                           R_I3C0_BSTE_ALE_Msk |
                           R_I3C0_BSTE_TODE_Msk);

    /* Enable all Transfer Status Flags. */
    p_ctrl->p_reg->NTSTE = (R_I3C0_NTSTE_TDBEE0_Msk |
                            R_I3C0_NTSTE_RDBFE0_Msk |
                            R_I3C0_NTSTE_IBIQEFE_Msk |
                            R_I3C0_NTSTE_CMDQEE_Msk |
                            R_I3C0_NTSTE_RSPQFE_Msk |
                            R_I3C0_NTSTE_TABTE_Msk |
                            R_I3C0_NTSTE_TEE_Msk |
                            R_I3C0_NTSTE_RSQFE_Msk);

    /* Enable the Internal Error Interrupt Requests. */
    p_ctrl->p_reg->INIE = R_I3C0_INIE_INEIE_Msk;

    /* Enable HDR exit pattern Interrupt Requests. */
    p_ctrl->p_reg->BIE = R_I3C0_BIE_HDREXDIE_Msk | R_I3C0_BIE_TODIE_Msk;

    /* Write settings to the Normal Transfer Interrupt Enable Register. */
    p_ctrl->p_reg->NTIE = ntie;

    /* Write the Hot-Join Ackowlege settings. */
    p_ctrl->p_reg->BCTL_b.HJACKCTL = !p_extend->ibi_control.hot_join_acknowledge;

    /* Calculate the value of the IBI Notify Control Register. */
    uint32_t ibinctl =
        (uint32_t) (p_extend->ibi_control.notify_rejected_hot_join_requests << R_I3C0_IBINCTL_NRHJCTL_Pos);
    ibinctl |= (uint32_t) (p_extend->ibi_control.notify_rejected_mastership_requests << R_I3C0_IBINCTL_NRMRCTL_Pos);
    ibinctl |= (uint32_t) (p_extend->ibi_control.notify_rejected_interrupt_requests << R_I3C0_IBINCTL_NRSIRCTL_Pos);

    /* Write settings to the IBI Notify Control Register. */
    p_ctrl->p_reg->IBINCTL = ibinctl;

    /* Calculate the value of the SCL Clock Stalling Control Register. */
    uint32_t scstlctl = (uint32_t) (p_extend->bitrate_settings.clock_stalling.assigned_address_phase_enable <<
                                    R_I3C0_SCSTLCTL_AAPE_Pos);
    scstlctl |= (uint32_t) (p_extend->bitrate_settings.clock_stalling.transition_phase_enable <<
                            R_I3C0_SCSTLCTL_TRAPE_Pos);
    scstlctl |= (uint32_t) (p_extend->bitrate_settings.clock_stalling.parity_phase_enable << R_I3C0_SCSTLCTL_PARPE_Pos);
    scstlctl |= (uint32_t) (p_extend->bitrate_settings.clock_stalling.ack_phase_enable << R_I3C0_SCSTLCTL_ACKPE_Pos);
    scstlctl |=
        (uint32_t) (p_extend->bitrate_settings.clock_stalling.clock_stalling_time << R_I3C0_SCSTLCTL_STLCYC_Pos);

    /* Write clock stalling settings to the SCL CLock Stalling Control Register. */
    p_ctrl->p_reg->SCSTLCTL = scstlctl;

    /* Write Bus Condition Detection Registers. */
    p_ctrl->p_reg->BFRECDT = p_extend->bus_free_detection_time;
    p_ctrl->p_reg->BAVLCDT = p_extend->bus_available_detection_time;
    p_ctrl->p_reg->BIDLCDT = p_extend->bus_idle_detection_time;

    if (!p_extend->timeout_detection_enable)
    {
        /* Disable Timeout Detection. */
        p_ctrl->p_reg->TMOCTL = 0U;
    }

#if I3C_CFG_SLAVE_SUPPORT

    /* Calculate the value of the CCC Slave Events Command Register. */
    uint32_t csecmd =
        (uint32_t) (p_extend->slave_command_response_info.inband_interrupt_enable << R_I3C0_CSECMD_SVIRQE_Pos);
    csecmd |= (uint32_t) (p_extend->slave_command_response_info.mastership_request_enable << R_I3C0_CSECMD_MSRQE_Pos);
    csecmd |= (uint32_t) (p_extend->slave_command_response_info.hotjoin_request_enable << R_I3C0_CSECMD_HJEVE_Pos);

    /* Calculate the value of the CCC Max Data Speed Read Register. */
    uint32_t cmdspr = (uint32_t) p_extend->slave_command_response_info.read_data_rate << R_I3C0_CMDSPR_MSRDR_Pos;
    cmdspr |= (uint32_t) p_extend->slave_command_response_info.clock_data_turnaround << R_I3C0_CMDSPR_CDTTIM_Pos;

    /* Calculate the value of the CCC Max Data Speed Rurnaround Register. */
    uint32_t cmdspt = p_extend->slave_command_response_info.read_turnaround_time << R_I3C0_CMDSPT_MRTTIM_Pos;
    cmdspt |= (uint32_t) p_extend->slave_command_response_info.read_turnaround_time_enable << R_I3C0_CMDSPT_MRTE_Pos;

    /* Calculate the value of the CCC Exchange Timing Support Information Register. */
    uint32_t cetsm = (uint32_t) (p_extend->slave_command_response_info.oscillator_frequency << R_I3C0_CETSM_FREQ_Pos) &
                     R_I3C0_CETSM_FREQ_Msk;
    cetsm |= (uint32_t) (p_extend->slave_command_response_info.oscillator_inaccuracy << R_I3C0_CETSM_INAC_Pos) &
             R_I3C0_CETSM_INAC_Msk;

    uint32_t cmrlg = (uint32_t) p_extend->slave_command_response_info.read_length;
    cmrlg |= (uint32_t) p_extend->slave_command_response_info.ibi_payload_length << R_I3C0_CMRLG_IBIPSZ_Pos;

    /* Write Slave Command Response Info. */
    p_ctrl->p_reg->CSECMD  = csecmd;
    p_ctrl->p_reg->CEACTST = (1U << p_extend->slave_command_response_info.activity_state);
    p_ctrl->p_reg->CMWLG   = (uint32_t) p_extend->slave_command_response_info.write_length;
    p_ctrl->p_reg->CMRLG   = cmrlg;
    p_ctrl->p_reg->CGDVST  =
        (uint32_t) (p_extend->slave_command_response_info.activity_state << R_I3C0_CGDVST_ACTMD_Pos);
    p_ctrl->p_reg->CMDSPW = (uint32_t) p_extend->slave_command_response_info.write_data_rate;
    p_ctrl->p_reg->CMDSPR = cmdspr;
    p_ctrl->p_reg->CMDSPT = cmdspt;
    p_ctrl->p_reg->CETSM  = cetsm;
#endif

    /* Enable the I3C Bus. */
    p_ctrl->p_reg->BCTL |= R_I3C0_BCTL_BUSE_Msk;

    /* Enable the command response status buffer full IRQ. */
    R_BSP_IrqCfgEnable(p_extend->resp_irq, p_extend->ipl, p_ctrl);

    /* Enable the receive data buffer full IRQ. */
    R_BSP_IrqCfgEnable(p_extend->rx_irq, p_extend->ipl, p_ctrl);

    /* Enable the transmit data buffer empty IRQ. */
    R_BSP_IrqCfgEnable(p_extend->tx_irq, p_extend->ipl, p_ctrl);

#if I3C_CFG_SLAVE_SUPPORT

    /* Enable the receive status buffer full IRQ. */
    R_BSP_IrqCfgEnable(p_extend->rcv_irq, p_extend->ipl, p_ctrl);
#endif

    /* Enable the IBI IRQ. */
    R_BSP_IrqCfgEnable(p_extend->ibi_irq, p_extend->ipl, p_ctrl);

    /* Enable the Error and Event IRQ. */
    R_BSP_IrqCfgEnable(p_extend->eei_irq, p_extend->eei_ipl, p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the configuration for this device.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_UNSUPPORTED            The device cannot be a secondary master if master support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_DeviceCfgSet (i3c_ctrl_t * const p_api_ctrl, i3c_device_cfg_t const * const p_device_cfg)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_device_cfg);
#endif

#if I3C_CFG_MASTER_SUPPORT
    if (I3C_DEVICE_TYPE_MAIN_MASTER == p_ctrl->p_cfg->device_type)
    {
        /*
         * Configure the master dynamic address and set it to valid (See Figure 25.102 I3C Communication Flow
         * in the RA2E2 manual R01UH0919EJ0100).
         */
        uint32_t msdvad = (uint32_t) p_device_cfg->dynamic_address << R_I3C0_MSDVAD_MDYAD_Pos;
        msdvad               |= R_I3C0_MSDVAD_MDYADV_Msk;
        p_ctrl->p_reg->MSDVAD = msdvad;
    }
    else
#endif
    {
#if I3C_CFG_SLAVE_SUPPORT

        /* Secondary master device role is not supported. */
        FSP_ERROR_RETURN(1U != p_device_cfg->slave_info.bcr_b.device_role, FSP_ERR_UNSUPPORTED);

        /*
         * Configure slave device address table, Device Characteristics, Bus Characteristics, and
         * Provisional ID (See Figure 25.102 I3C Communication Flow in the RA2E2 manual R01UH0919EJ0100).
         *
         * Configure the device static address. */
        uint32_t sdatbas0 = (uint32_t) p_device_cfg->static_address & R_I3C0_SDATBAS0_SDSTAD_Msk;

        /* Configure the device dynamic address. */
        sdatbas0 |= (uint32_t) (i3c_address_parity(p_device_cfg->dynamic_address) << R_I3C0_SDATBAS0_SDDYAD_Pos) &
                    R_I3C0_SDATBAS0_SDDYAD_Msk;

        /* Configure the IBI payload setting based on the BCR register. */
        sdatbas0 |= (uint32_t) (p_device_cfg->slave_info.bcr_b.ibi_payload << R_I3C0_SDATBAS0_SDIBIPL_Pos) &
                    R_I3C0_SDATBAS0_SDIBIPL_Msk;

        /* Set the slave address to valid. */
        p_ctrl->p_reg->SVCTL_b.SVAEn = 1;

        /* Write settings to the Slave Device Address Table Register. */
        p_ctrl->p_reg->SDATBAS0 = sdatbas0;

        /* Write the BCR and DCR settings to the Slave Device Characteristic Table Register. */
        uint32_t svdct = (uint32_t) p_device_cfg->slave_info.dcr;
        svdct               |= (uint32_t) p_device_cfg->slave_info.bcr << R_I3C0_SVDCT_TBCR0_Pos;
        p_ctrl->p_reg->SVDCT = svdct;

        /* Write the PID setting to the Slave Device Characteristic Table PID Register. */
        uint8_t * pid = (uint8_t *) p_device_cfg->slave_info.pid;
        p_ctrl->p_reg->SDCTPIDL = (uint32_t) ((pid[4] << 8U) | (pid[5]));
        p_ctrl->p_reg->SDCTPIDH = (uint32_t) ((pid[0] << 24U) |
                                              (pid[1] << 16U) |
                                              (pid[2] << 8U) |
                                              (pid[3] << 0U));
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configure an entry in the master device table. This function is called in master mode in order to configure
 * the devices on the I3C bus. It may also be called in slave mode when the slave receives the DEFSVLS command.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_UNSUPPORTED            Mastership requests must be rejected is slave support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_MasterDeviceTableSet (i3c_ctrl_t * const                   p_api_ctrl,
                                      uint32_t                             device_index,
                                      i3c_device_table_cfg_t const * const p_device_table_cfg)
{
#if I3C_CFG_MASTER_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_device_table_cfg);
 #endif

    /* The driver does not support accepting mastership requests. */
    FSP_ERROR_RETURN(!p_device_table_cfg->master_request_accept, FSP_ERR_UNSUPPORTED);

    uint32_t volatile * p_datbasn_reg = NULL;
    uint32_t            datbasn       = 0;

    if (I3C_DEVICE_INDEX_EXTENDED_DEVICE == device_index)
    {
        p_datbasn_reg = &p_ctrl->p_reg->EXDATBAS;
    }
    else
    {
        /* Compute the address of the DATBASn register. */
        uint32_t address_offset = (uint32_t) (&p_ctrl->p_reg->DATBAS1 - &p_ctrl->p_reg->DATBAS0);
        p_datbasn_reg = (uint32_t *) (&p_ctrl->p_reg->DATBAS0 + device_index * address_offset);

        /* Configure the IBI settings for this device. */
        datbasn |= (uint32_t) (p_device_table_cfg->ibi_payload << R_I3C0_DATBAS0_DVIBIPL_Pos) &
                   R_I3C0_DATBAS0_DVIBIPL_Msk;
        datbasn |= (uint32_t) (!p_device_table_cfg->ibi_accept << R_I3C0_DATBAS0_DVSIRRJ_Pos) &
                   R_I3C0_DATBAS0_DVSIRRJ_Msk;
        datbasn |= (uint32_t) (!p_device_table_cfg->master_request_accept << R_I3C0_DATBAS0_DVMRRJ_Pos) &
                   R_I3C0_DATBAS0_DVMRRJ_Msk;
    }

    /* Configure the device static address. */
    datbasn |= (uint32_t) (p_device_table_cfg->static_address << R_I3C0_DATBAS0_DVSTAD_Pos) & R_I3C0_DATBAS0_DVSTAD_Msk;

    /* Configure the device dynamic address. */
    datbasn |= (uint32_t) (i3c_address_parity(p_device_table_cfg->dynamic_address) << R_I3C0_DATBAS0_DVDYAD_Pos) &
               R_I3C0_DATBAS0_DVDYAD_Msk;

    if (I3C_DEVICE_PROTOCOL_I2C == p_device_table_cfg->device_protocol)
    {
        /* Set the device type so that transfers with this device use the legacy I2C protocol. */
        datbasn |= R_I3C0_DATBAS0_DVTYP_Msk;
    }

    /* Write to the DATBASn register. */
    *p_datbasn_reg = datbasn;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(device_index);
    FSP_PARAMETER_NOT_USED(p_device_table_cfg);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Set the status returned to the master in response to a GETSTATUS command.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_INVALID_MODE           The instance is not in slave mode.
 * @retval FSP_ERR_UNSUPPORTED            Slave support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_SlaveStatusSet (i3c_ctrl_t * const p_api_ctrl, i3c_device_status_t status)
{
#if I3C_CFG_SLAVE_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* This function is only called in slave mode. */
    FSP_ERROR_RETURN(
        I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state || I3C_INTERNAL_STATE_SLAVE_IBI == p_ctrl->internal_state,
        FSP_ERR_INVALID_MODE);
 #endif

    /* Clear the Pending Interrupt and Vendor Reserved fields. */
    uint32_t cgdvst = p_ctrl->p_reg->CGDVST;
    cgdvst &= ~(R_I3C0_CGDVST_PNDINT_Msk | R_I3C0_CGDVST_VDRSV_Msk);

    /* Write the new Pending Interrupt and Vendor Reserved fields. */
    cgdvst |= (uint32_t) status.pending_interrupt & R_I3C0_CGDVST_PNDINT_Msk;
    cgdvst |= (uint32_t) (status.vendor_status << R_I3C0_CGDVST_VDRSV_Pos) & R_I3C0_CGDVST_VDRSV_Msk;

    p_ctrl->p_reg->CGDVST = cgdvst;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(status);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * In master mode, select the device for the next transfer.
 * This function is not used in slave mode.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_INVALID_MODE           This operation is prohibited in slave mode.
 * @retval FSP_ERR_UNSUPPORTED            Master support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_DeviceSelect (i3c_ctrl_t * const p_api_ctrl, uint32_t device_index, uint32_t bitrate_mode)
{
#if I3C_CFG_MASTER_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(I3C_BITRATE_MODE_I3C_SDR4_EXTBR_X4 >= bitrate_mode);
    FSP_ERROR_RETURN(
        I3C_INTERNAL_STATE_SLAVE_IDLE != p_ctrl->internal_state && I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state,
        FSP_ERR_INVALID_MODE);
    FSP_ASSERT(BSP_FEATURE_I3C_MAX_DEV_COUNT > device_index ||
               I3C_DEVICE_INDEX_EXTENDED_DEVICE == device_index);
 #endif

    p_ctrl->device_index        = device_index;
    p_ctrl->device_bitrate_mode = (i3c_bitrate_mode_t) bitrate_mode;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(device_index);
    FSP_PARAMETER_NOT_USED(bitrate_mode);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Start the Dynamic Address Assignment Process. Implements @ref i3c_api_t::dynamicAddressAssignmentStart.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL or invalid.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_INVALID_MODE           This operation is prohibited in slave mode.
 * @retval FSP_ERR_IN_USE                 The operation could not be completed because the driver is busy.
 * @retval FSP_ERR_UNSUPPORTED            Master support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_DynamicAddressAssignmentStart (i3c_ctrl_t * const            p_api_ctrl,
                                               i3c_address_assignment_mode_t address_assignment_mode,
                                               uint32_t                      starting_device_index,
                                               uint32_t                      device_count)
{
#if I3C_CFG_MASTER_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(
        I3C_INTERNAL_STATE_SLAVE_IDLE != p_ctrl->internal_state && I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state,
        FSP_ERR_INVALID_MODE);

    FSP_ASSERT(BSP_FEATURE_I3C_MAX_DEV_COUNT > starting_device_index ||
               I3C_DEVICE_INDEX_EXTENDED_DEVICE == starting_device_index);

    if (I3C_ADDRESS_ASSIGNMENT_MODE_ENTDAA == address_assignment_mode)
    {
        if (I3C_DEVICE_INDEX_EXTENDED_DEVICE == starting_device_index)
        {
            /* When the extended device index is selected, the device count must be 1. */
            FSP_ASSERT(1U == device_count);
        }
        else
        {
            /* The device count must be less than the remaining devices in the device table. */
            FSP_ASSERT(BSP_FEATURE_I3C_MAX_DEV_COUNT > device_count + starting_device_index);
        }
    }
    else
    {
        /* If the dynamic address is configured with SETDASA then the device count is not used and should be set to 0. */
        FSP_ASSERT(0U == device_count);
    }
 #endif

    /* Ensure that driver is in the idle state. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state, FSP_ERR_IN_USE);

    p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_ENTDAA;

    /* Set the transfer_data pointer to read the PID, DCR, and BCR registers for each device. */
    p_ctrl->read_buffer_descriptor.p_buffer    = (uint8_t *) &p_ctrl->current_slave_info;
    p_ctrl->read_buffer_descriptor.count       = 0;
    p_ctrl->read_buffer_descriptor.buffer_size = sizeof(i3c_slave_info_t);

    /* Setup the command descriptor to start the ENTDAA command starting at the selected device index. */
    uint32_t command_descriptor = 0;
    command_descriptor |= (I3C_CMD_DESC_CMD_ATTR_ADDR_ASSGN_CMD << I3C_CMD_DESC_CMD_ATTR_Pos);
    command_descriptor |= (uint32_t) (I3C_EVENT_ADDRESS_ASSIGNMENT_COMPLETE << I3C_CMD_DESC_TID_Pos);
    command_descriptor |= (uint32_t) (address_assignment_mode << I3C_CMD_DESC_CMD_Pos);
    command_descriptor |= (starting_device_index << I3C_CMD_DESC_DEV_INDEX_Pos);
    command_descriptor |= (device_count << I3C_CMD_DESC_ADDR_ASSGN_DEV_COUNT_Pos);
    command_descriptor |= I3C_CMD_DESC_ROC_Msk;
    command_descriptor |= I3C_CMD_DESC_TOC_Msk;

    /*
     * Write to the descriptor to the command queue.
     * Note that the command descriptor is two words. The least significant word must be written first followed by
     * the most significant word (See Section 25.3.1.1 in the RA2E2 manual R01UH0919EJ0100).
     */
    p_ctrl->p_reg->NCMDQP = command_descriptor;
    p_ctrl->p_reg->NCMDQP = 0U;

    /* Clear the command queue empty flag. */
    p_ctrl->p_reg->NTST_b.CMDQEF = 0;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(address_assignment_mode);
    FSP_PARAMETER_NOT_USED(starting_device_index);
    FSP_PARAMETER_NOT_USED(device_count);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Send a broadcast or direct command to slave devices on the bus. Implements @ref i3c_api_t::commandSend.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_IN_USE                 The operation could not be completed because the driver is busy.
 * @retval FSP_ERR_INVALID_MODE           This driver is not in master mode.
 * @retval FSP_ERR_INVALID_ALIGNMENT      The buffer must be aligned to 4 bytes. If it is a read operation, the length
 *                                        also be a multiple of 4 bytes.
 * @retval FSP_ERR_UNSUPPORTED            Master support must be enabled to call this function. Slave support must be
 *                                        enabled when sending the GETACCMST command.
 **********************************************************************************************************************/
fsp_err_t R_I3C_CommandSend (i3c_ctrl_t * const p_api_ctrl, i3c_command_descriptor_t * p_command_descriptor)
{
#if I3C_CFG_MASTER_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_command_descriptor);
    if (p_command_descriptor->length > 0)
    {
        FSP_ASSERT(NULL != p_command_descriptor->p_buffer);
    }

    FSP_ERROR_RETURN(
        I3C_INTERNAL_STATE_SLAVE_IDLE != p_ctrl->internal_state && I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state,
        FSP_ERR_INVALID_MODE);

  #if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* Verify that the buffer is aligned to 4 bytes. */
    FSP_ERROR_RETURN(0U == ((uint32_t) p_command_descriptor->p_buffer & 0x03U), FSP_ERR_INVALID_ALIGNMENT);
  #endif
 #endif

    /* The driver does not currently support relinquishing mastership to secondary masters. */
    FSP_ERROR_RETURN(I3C_CCC_DIRECT_GETACCMST != p_command_descriptor->command_code, FSP_ERR_UNSUPPORTED);

    /* Ensure that driver is in the idle state. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state, FSP_ERR_IN_USE);

    /* Save the current command code. */
    p_ctrl->current_command_code = p_command_descriptor->command_code;

    i3c_read_buffer_descriptor_t * p_transfer_descriptor;

 #if I3C_CFG_SLAVE_SUPPORT
    if (I3C_CCC_DIRECT_GETACCMST == p_command_descriptor->command_code)
    {
        /* Disable the IBI Write Buffer Empty/Full IRQ in case the driver transisitons to slave mode. */
        p_ctrl->p_reg->NTIE_b.IBIQEFIE = 0;
    }
 #endif

    if (p_command_descriptor->rnw)
    {
        /* If this is a read transfer, update the read buffer descriptor. */
        p_transfer_descriptor = &p_ctrl->read_buffer_descriptor;
        p_transfer_descriptor->read_request_issued = false;

        p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_COMMAND_READ;
    }
    else
    {
        /* If this is a write transfer, update the write buffer descriptor. */
        p_transfer_descriptor = (i3c_read_buffer_descriptor_t *) &p_ctrl->write_buffer_descriptor;

        p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_COMMAND_WRITE;
    }

    /* Update the buffer descriptor with the buffer provided in the command descriptor. */
    p_transfer_descriptor->p_buffer    = p_command_descriptor->p_buffer;
    p_transfer_descriptor->count       = 0;
    p_transfer_descriptor->buffer_size = p_command_descriptor->length;

    /* Calculate the command descriptor. */
    uint32_t cmd1 = 0;
    cmd1 |= (p_ctrl->device_index << I3C_CMD_DESC_DEV_INDEX_Pos) & I3C_CMD_DESC_DEV_INDEX_Msk;
    cmd1 |= (0 << I3C_CMD_DESC_XFER_MODE_Pos) & I3C_CMD_DESC_XFER_MODE_Msk;
    cmd1 |= (uint32_t) (p_command_descriptor->rnw << I3C_CMD_DESC_XFER_RNW_Pos);
    cmd1 |= I3C_CMD_DESC_ROC_Msk;
    cmd1 |= (uint32_t) (!p_command_descriptor->restart << I3C_CMD_DESC_TOC_Pos) & I3C_CMD_DESC_TOC_Msk;
    cmd1 |= (uint32_t) (p_command_descriptor->command_code << I3C_CMD_DESC_CMD_Pos);
    cmd1 |= I3C_CMD_DESC_XFER_CP_Msk;
    cmd1 |= (uint32_t) (I3C_EVENT_COMMAND_COMPLETE << I3C_CMD_DESC_TID_Pos);

    uint32_t cmd2;
    if ((4 >= p_command_descriptor->length) && !p_command_descriptor->rnw)
    {
        /* If the transfer length is less than or equal to 4 bytes, then use "Immediate Data Transfer".
         * See section "25.3.1.1.2 Immediate Transfer Command" in the RA2E2 manual R01UH0919EJ0100. */
        cmd1 |= I3C_CMD_DESC_CND_ATTR_IMMED_DATA_XFER;
        cmd1 |= (p_command_descriptor->length << I3C_CMD_DESC_IMMED_DATA_XFER_BYTE_CNT_Pos);
        cmd2  = i3c_next_data_word_calculate(&p_ctrl->write_buffer_descriptor);
        p_ctrl->write_buffer_descriptor.count = p_command_descriptor->length;
    }
    else
    {
        cmd2 = (p_command_descriptor->length << I3C_CMD_DESC_XFER_LENGTH_Pos) &
               I3C_CMD_DESC_XFER_LENGTH_Msk;
    }

    /*
     * Write the descriptor to the command queue.
     * Note that the command descriptor is two words. The least significant word must be written first followed by
     * the most significant word (See Section 25.3.1.1 in the RA2E2 manual R01UH0919EJ0100).
     */
    p_ctrl->p_reg->NCMDQP = cmd1;
    p_ctrl->p_reg->NCMDQP = cmd2;

    /* Clear the command queue empty flag. */
    p_ctrl->p_reg->NTST_b.CMDQEF = 0;

    if (!p_command_descriptor->rnw && (4 < p_command_descriptor->length))
    {
        /* Calculate the next data word that will be written to the FIFO. */
        p_ctrl->next_word = i3c_next_data_word_calculate(&p_ctrl->write_buffer_descriptor);

        /* Write data to the FIFO. */
        i3c_fifo_write(p_ctrl);

        /* If there is still data remaining in the transfer then it will be written in the Write Buffer Empty IRQ. */
        if ((BSP_FEATURE_I3C_NTDTBP0_DEPTH * sizeof(uint32_t)) < p_command_descriptor->length)
        {
            /* Enable the Write Buffer Empty IRQ. */
            p_ctrl->p_reg->NTIE_b.TDBEIE0 = 1;
        }
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_command_descriptor);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Set the write buffer for the transfer. In master mode, start the transfer. When the transfer is completed send a
 * stop condition or a repeated-start. Implements @ref i3c_api_t::write.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_IN_USE                 The operation could not be completed because the driver is busy.
 * @retval FSP_ERR_INVALID_MODE           This driver is disabled.
 * @retval FSP_ERR_INVALID_ALIGNMENT      The buffer must be aligned to 4 bytes.
 **********************************************************************************************************************/
fsp_err_t R_I3C_Write (i3c_ctrl_t * const p_api_ctrl, uint8_t const * const p_data, uint32_t length, bool restart)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if 0U == I3C_CFG_MASTER_SUPPORT
    FSP_PARAMETER_NOT_USED(restart);
#endif

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state, FSP_ERR_INVALID_MODE);
 #if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* Verify that the buffer is aligned to 4 bytes. */
    FSP_ERROR_RETURN(0U == ((uint32_t) p_data & 0x03U), FSP_ERR_INVALID_ALIGNMENT);
 #endif
#endif

#if I3C_CFG_SLAVE_SUPPORT
    if (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state)
    {
        /* In slave mode, ensure that a write transfer is not currently in progress. */
        FSP_ERROR_RETURN(0U == (p_ctrl->p_reg->PRSST & R_I3C0_PRSST_TRMD_Msk), FSP_ERR_IN_USE);
    }
    else
#endif
    {
#if I3C_CFG_MASTER_SUPPORT

        /* In master mode, ensure that driver is in the idle state. */
        FSP_ERROR_RETURN(I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state, FSP_ERR_IN_USE);
#endif
    }

    /* Set the internal transfer state for a write transfer. */
    p_ctrl->write_buffer_descriptor.count       = 0;
    p_ctrl->write_buffer_descriptor.buffer_size = length;
    p_ctrl->write_buffer_descriptor.p_buffer    = (uint8_t *) p_data;

    /* Calculate the next data word that will be written to the FIFO. */
    p_ctrl->next_word = i3c_next_data_word_calculate(&p_ctrl->write_buffer_descriptor);

#if I3C_CFG_SLAVE_SUPPORT
    if (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state)
    {
        if (p_ctrl->write_buffer_descriptor.p_buffer != NULL)
        {
            /*
             * If a write buffer has already been configured, then the FIFO needs to be reset before the new data
             * can be written.
             */
            p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_TDBRST_Msk;

            /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
            FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL, 0U);
        }

        /* Configure the number of bytes that the slave will write before ending the transfer via the T bit. */
        p_ctrl->p_reg->SVTDLG0 = (length << 16U);
    }
#endif

    if ((length > 4) || (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state))
    {
        /* Write data to the FIFO. Note that in master mode, if the legnth is less than or equal to 4 bytes,
         * the "Immediate Data Transfer" command must be used instead of the "Regular Transfer" command. */
        i3c_fifo_write(p_ctrl);

        /* If there is still data remaining in the transfer then it will be written in the Write Buffer Empty IRQ. */
        if ((BSP_FEATURE_I3C_NTDTBP0_DEPTH * sizeof(uint32_t)) < length)
        {
            /* Enable the Write Buffer Empty IRQ. */
            p_ctrl->p_reg->NTIE_b.TDBEIE0 = 1;
        }
    }

#if I3C_CFG_MASTER_SUPPORT
    if (I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state)
    {
        p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_WRITE;

        /*
         * Write the descriptor to the command queue.
         * Note that the command descriptor is two words. The least significant word must be written first followed by
         * the most significant word (See Section 25.3.1.1 in the RA2E2 manual R01UH0919EJ0100).
         */
        uint32_t cmd1 = i3c_xfer_command_calculate(p_ctrl->device_index, false, p_ctrl->device_bitrate_mode, restart);

        uint32_t cmd2;
        if (length <= 4)
        {
            /* If the transfer length is less than or equal to 4 bytes, then use "Immediate Data Transfer".
             * See section "25.3.1.1.2 Immediate Transfer Command" in the RA2E2 manual R01UH0919EJ0100. */
            cmd1 |= I3C_CMD_DESC_CND_ATTR_IMMED_DATA_XFER;
            cmd1 |= (length << I3C_CMD_DESC_IMMED_DATA_XFER_BYTE_CNT_Pos);
            cmd2  = p_ctrl->next_word;
            p_ctrl->write_buffer_descriptor.count = length;
        }
        else
        {
            cmd2 = (length << I3C_CMD_DESC_XFER_LENGTH_Pos) & I3C_CMD_DESC_XFER_LENGTH_Msk;
        }

        p_ctrl->p_reg->NCMDQP = cmd1;
        p_ctrl->p_reg->NCMDQP = cmd2;

        /* Clear the command queue empty flag. */
        p_ctrl->p_reg->NTST_b.CMDQEF = 0;
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the read buffer for the transfer. In master mode, start the transfer. When the transfer is completed send a
 * stop condition or a repeated-start. Implements @ref i3c_api_t::read.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_IN_USE                 The operation could not be completed because the driver is busy.
 * @retval FSP_ERR_INVALID_MODE           This driver is disabled.
 * @retval FSP_ERR_INVALID_ALIGNMENT      The buffer must be aligned to 4 bytes and the length must be a multiple of
 *                                        4 bytes.
 **********************************************************************************************************************/
fsp_err_t R_I3C_Read (i3c_ctrl_t * const p_api_ctrl, uint8_t * const p_data, uint32_t length, bool restart)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if 0U == I3C_CFG_MASTER_SUPPORT
    FSP_PARAMETER_NOT_USED(restart);
#endif

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state, FSP_ERR_INVALID_MODE);
 #if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* The buffer must be 4 byte aligned. */
    FSP_ERROR_RETURN(0U == ((uint32_t) p_data & 0x03U), FSP_ERR_INVALID_ALIGNMENT);

    if (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state)
    {
        /* The buffer size must be a multiple of 4 bytes in slave mode. */
        FSP_ERROR_RETURN(0U == ((uint32_t) length & 0x03U), FSP_ERR_INVALID_ALIGNMENT);
    }
 #endif
#endif

    /* In Master mode, ensure that driver is in the idle state. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state ||
                     I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state,
                     FSP_ERR_IN_USE);

    i3c_extended_cfg_t const * p_extend = (i3c_extended_cfg_t const *) p_ctrl->p_cfg->p_extend;

    /* Disable the Receive Buffer Full IRQ in order to ensure that updating the read buffer state is not interrupted. */
    R_BSP_IrqDisable(p_extend->rx_irq);

    /* Set the internal transfer state for a read transfer. */
    p_ctrl->read_buffer_descriptor.count               = 0;
    p_ctrl->read_buffer_descriptor.buffer_size         = length;
    p_ctrl->read_buffer_descriptor.p_buffer            = p_data;
    p_ctrl->read_buffer_descriptor.read_request_issued = false;

    R_BSP_IrqEnableNoClear(p_extend->rx_irq);

#if I3C_CFG_MASTER_SUPPORT
    if (I3C_INTERNAL_STATE_MASTER_IDLE == p_ctrl->internal_state)
    {
        p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_READ;

        /*
         * Write the descriptor to the command queue.
         * Note that the command descriptor is two words. The least significant word must be written first followed by
         * the most significant word (See Section 25.3.1.1 in the RA2E2 manual R01UH0919EJ0100).
         */
        p_ctrl->p_reg->NCMDQP = i3c_xfer_command_calculate(p_ctrl->device_index,
                                                           true,
                                                           p_ctrl->device_bitrate_mode,
                                                           restart);
        p_ctrl->p_reg->NCMDQP = (length << I3C_CMD_DESC_XFER_LENGTH_Pos) & I3C_CMD_DESC_XFER_LENGTH_Msk;

        /* Clear the command queue empty flag. */
        p_ctrl->p_reg->NTST_b.CMDQEF = 0;
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initiate an IBI write operation (This function is only used in slave mode).
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_IN_USE                 The operation could not be completed because the driver is busy.
 * @retval FSP_ERR_INVALID_MODE           This function is only called in slave mode.
 * @retval FSP_ERR_INVALID_ALIGNMENT      The buffer must be aligned to 4 bytes.
 * @retval FSP_ERR_UNSUPPORTED            Slave supoprt is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_IbiWrite (i3c_ctrl_t * const    p_api_ctrl,
                          i3c_ibi_type_t        ibi_type,
                          uint8_t const * const p_data,
                          uint32_t              length)
{
#if I3C_CFG_SLAVE_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;
 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* If the device has an IBI payload, then a buffer is required. */
    if ((I3C_IBI_TYPE_INTERRUPT == ibi_type) && (0 != (R_I3C0_SDATBAS0_SDIBIPL_Msk & p_ctrl->p_reg->SDATBAS0)))
    {
        FSP_ASSERT(NULL != p_data);
        FSP_ASSERT(0 != length);
    }

    /* This function is only called in slave mode. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state, FSP_ERR_INVALID_MODE);

  #if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* The buffer must be 4 byte aligned. */
    FSP_ERROR_RETURN(0U == ((uint32_t) p_data & 0x03U), FSP_ERR_INVALID_ALIGNMENT);
  #endif
 #endif

    /* An IBI can't be started if an IBI is already in progress. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_SLAVE_IBI != p_ctrl->internal_state, FSP_ERR_IN_USE);

    p_ctrl->internal_state = I3C_INTERNAL_STATE_SLAVE_IBI;

    /* Setup the buffer for writing the data portion of the IBI. */
    p_ctrl->ibi_buffer_descriptor.p_buffer    = (uint8_t *) p_data;
    p_ctrl->ibi_buffer_descriptor.count       = 0;
    p_ctrl->ibi_buffer_descriptor.buffer_size = length;

    /* Calculate the command descriptor for starting an IBI. */
    uint32_t command_descriptor = 0;
    command_descriptor |= I3C_CMD_DESC_ROC_Msk;
    command_descriptor |= (I3C_EVENT_IBI_WRITE_COMPLETE << I3C_CMD_DESC_TID_Pos);

    if (I3C_IBI_TYPE_HOT_JOIN == ibi_type)
    {
        command_descriptor |= I3C_CMD_DESC_XFER_HJ_Msk;
    }
    else if (I3C_IBI_TYPE_INTERRUPT == ibi_type)
    {
        command_descriptor |= I3C_CMD_DESC_XFER_RNW_Msk;
    }
    else
    {
        /* Mastership request. */
    }

    if (0 < length)
    {
        /* Write the data to the IBI queue. */
        p_ctrl->p_reg->NIBIQP = i3c_next_data_word_calculate(
            (i3c_write_buffer_descriptor_t *) &p_ctrl->ibi_buffer_descriptor);

        if (sizeof(uint32_t) < length)
        {
            /* If the transfer length is greater than 4 bytes, then prepare the next word to be written to the FIFO. */
            p_ctrl->ibi_next_word = i3c_next_data_word_calculate(
                (i3c_write_buffer_descriptor_t *) &p_ctrl->ibi_buffer_descriptor);

            /* Enable the IBI Write Buffer Empty/Full IRQ. */
            p_ctrl->p_reg->NTIE_b.IBIQEFIE = 1;
        }

        /* Clear the IBI Queue Empty/Full Flag (This will generate an IBI IRQ). */
        p_ctrl->p_reg->NTST_b.IBIQEFF = 0;
    }

    /*
     * Write the descriptor to the command queue.
     * Note that the command descriptor is two words. The least significant word must be written first followed by
     * the most significant word (See Section 25.3.1.1 in the RA2E2 manual R01UH0919EJ0100).
     */
    p_ctrl->p_reg->NCMDQP = command_descriptor;
    p_ctrl->p_reg->NCMDQP = (length << I3C_CMD_DESC_XFER_LENGTH_Pos) & I3C_CMD_DESC_XFER_LENGTH_Msk;

    /* Clear the command queue empty flag. */
    p_ctrl->p_reg->NTST_b.CMDQEF = 0;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(ibi_type);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(length);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Set the read buffer for storing received IBI data (This function is only used in master mode).
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 * @retval FSP_ERR_INVALID_MODE           This function is only called in master mode.
 * @retval FSP_ERR_INVALID_ALIGNMENT      The buffer must be aligned to 4 bytes and the length must be a multiple of
 *                                        4 bytes.
 * @retval FSP_ERR_UNSUPPORTED            Master support is disabled.
 **********************************************************************************************************************/
fsp_err_t R_I3C_IbiRead (i3c_ctrl_t * const p_api_ctrl, uint8_t * const p_data, uint32_t length)
{
#if I3C_CFG_MASTER_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

 #if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_data);
    FSP_ASSERT(0 != length);

    /* This function is not used in slave mode. */
    FSP_ERROR_RETURN(I3C_INTERNAL_STATE_SLAVE_IDLE != p_ctrl->internal_state &&
                     I3C_INTERNAL_STATE_SLAVE_IBI != p_ctrl->internal_state &&
                     I3C_INTERNAL_STATE_DISABLED != p_ctrl->internal_state,
                     FSP_ERR_INVALID_MODE);

  #if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* The buffer must be 4 byte aligned. */
    FSP_ERROR_RETURN(0U == ((uint32_t) p_data & 0x03U), FSP_ERR_INVALID_ALIGNMENT);

    /* The buffer size must be a multiple of 4 bytes. */
    FSP_ERROR_RETURN(0U == ((uint32_t) length & 0x03U), FSP_ERR_INVALID_ALIGNMENT);
  #endif
 #endif

    i3c_extended_cfg_t const * p_extend = (i3c_extended_cfg_t const *) p_ctrl->p_cfg->p_extend;

    /* Disable the IBI Buffer Full IRQ in order to ensure that updating the IBI buffer state is not interrupted. */
    R_BSP_IrqDisable(p_extend->ibi_irq);

    p_ctrl->ibi_buffer_descriptor.p_buffer            = p_data;
    p_ctrl->ibi_buffer_descriptor.count               = 0;
    p_ctrl->ibi_buffer_descriptor.buffer_size         = length;
    p_ctrl->ibi_buffer_descriptor.read_request_issued = false;

    R_BSP_IrqEnableNoClear(p_extend->ibi_irq);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(length);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Close the I3C instance. Implements @ref i3c_api_t::close.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An argument was NULL.
 * @retval FSP_ERR_NOT_OPEN               This instance has not been opened yet.
 **********************************************************************************************************************/
fsp_err_t R_I3C_Close (i3c_ctrl_t * const p_api_ctrl)
{
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) p_api_ctrl;

#if I3C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(I3C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Disable IRQs. */
    R_BSP_IrqDisable(p_extend->resp_irq);
    R_BSP_IrqDisable(p_extend->rx_irq);
    R_BSP_IrqDisable(p_extend->tx_irq);
    R_BSP_IrqDisable(p_extend->rcv_irq);
    R_BSP_IrqDisable(p_extend->ibi_irq);

    /* Reset the I3C Peripheral so that it is in a known state. */
    p_ctrl->p_reg->BCTL_b.BUSE = 0;
    p_ctrl->p_reg->RSTCTL      = 1U;

    /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL, 0U);

    /* Set the I3C Module Stop bit. */
    R_BSP_MODULE_STOP(FSP_IP_I3C, p_ctrl->p_cfg->channel);

    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup I3C)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Compute the odd parity of an I3C address and set the parity bit.
 * @param[in]  address           Number of loops to check bit (at least 1 us per loop).
 *
 * @return                       The address with the parity bit set.
 **********************************************************************************************************************/
static uint8_t i3c_address_parity (uint8_t address)
{
    /* Compute the parity of the dynamic address. */
    uint32_t parity = address;

    /* XOR the upper 4 bits with the lower 4 bits. */
    parity ^= (parity >> 4);

    /* XOR the upper 2 bits of the result with the lower 2 bits. */
    parity ^= (parity >> 2);

    /* XOR the upper bit of the result with the lower bit. */
    parity ^= (parity >> 1);

    /* The result of XOR of all bits is stored in the LSB. */
    parity &= 1;

    /* The ODD parity will be the inverse of the even parity. */
    parity = !parity;

    return (uint8_t) (address | (parity << 7));
}

#if I3C_CFG_MASTER_SUPPORT

/*******************************************************************************************************************//**
 * Setup the command descriptor for a read or write transfer to the selected device.
 *
 * @param[in]  dev_index         The selected index for the transfer.
 * @param[in]  rnw               Read not write.
 * @param[in]  bitrate_setting   The bitrate setting (See @ref i3c_bitrate_mode_t).
 * @param[in]  restart           Terminate the transfer with a repeated start condition.
 *
 * @return                       The calculated value for the command descriptor.
 **********************************************************************************************************************/
static uint32_t i3c_xfer_command_calculate (uint32_t dev_index, bool rnw, uint32_t bitrate_setting, bool restart)
{
    uint32_t command_descriptor = 0;
    if (rnw)
    {
        command_descriptor |= (I3C_EVENT_READ_COMPLETE << I3C_CMD_DESC_TID_Pos);
    }
    else
    {
        command_descriptor |= (I3C_EVENT_WRITE_COMPLETE << I3C_CMD_DESC_TID_Pos);
    }

    command_descriptor |= (dev_index << I3C_CMD_DESC_DEV_INDEX_Pos) & I3C_CMD_DESC_DEV_INDEX_Msk;
    command_descriptor |= (bitrate_setting << I3C_CMD_DESC_XFER_MODE_Pos) & I3C_CMD_DESC_XFER_MODE_Msk;
    command_descriptor |= (uint32_t) (rnw << I3C_CMD_DESC_XFER_RNW_Pos);
    command_descriptor |= I3C_CMD_DESC_ROC_Msk;
    command_descriptor |= (uint32_t) (!restart << I3C_CMD_DESC_TOC_Pos) & I3C_CMD_DESC_TOC_Msk;

    return command_descriptor;
}

#endif

/*******************************************************************************************************************//**
 * Read data from the Normal Transfer Data Buffer and write it into the user provided data buffer.
 * @param[in]  p_ctrl                Pointer to an instance's control structure.
 * @param[in]  bytes                 The number of bytes to read from the FIFO.
 **********************************************************************************************************************/
static inline void i3c_fifo_read (i3c_instance_ctrl_t * p_ctrl, uint32_t bytes)
{
    int bytes_remaining = (int) bytes;
    while (bytes_remaining > 0)
    {
        /* Each entry in the FIFO is 4 bytes. */
        uint32_t rx_data = p_ctrl->p_reg->NTDTBP0;

        /* Clear the Read Buffer Full status flag. */
        p_ctrl->p_reg->NTST_b.RDBFF0 = 0;

        /*
         * Store the next word of data into the read buffer. If there is not enough space, a I3C_EVENT_READ_BUFFER_FULL
         * event will be called to notify the application that a new read buffer is required.
         */
        i3c_read_buffer_store(p_ctrl,
                              &p_ctrl->read_buffer_descriptor,
                              rx_data,
                              (uint32_t) bytes_remaining,
                              I3C_EVENT_READ_BUFFER_FULL);

        bytes_remaining -= 4;

        p_ctrl->read_transfer_count_final += 4;
    }
}

/*******************************************************************************************************************//**
 * Write a word of data read from a FIFO into the read buffer.
 *
 * @param[in]  p_ctrl                Pointer to an instance's control structure.
 * @param[in]  p_buffer_descriptor   Pointer to a read buffer descriptor for storing the word of data.
 * @param[in]  data_word             Word of data read from a FIFO.
 * @param[in]  num_bytes             The number of valid data bytes in the data word.
 * @param[in]  buffer_full_event     The event to notify that application when their is no more space available in the
 *                                   buffer descriptor.
 **********************************************************************************************************************/
static inline void i3c_read_buffer_store (i3c_instance_ctrl_t * const    p_ctrl,
                                          i3c_read_buffer_descriptor_t * p_buffer_descriptor,
                                          uint32_t                       data_word,
                                          uint32_t                       num_bytes,
                                          i3c_event_t                    buffer_full_event)
{
#if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT
    FSP_PARAMETER_NOT_USED(num_bytes);
#endif

#if I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* If unaligned buffers are supported, the word must be written one byte at a time. */
    for (uint32_t i = 0; i < sizeof(uint32_t) && i < num_bytes; i++)
    {
#endif

    /* Check if the buffer descriptor has space available. */
    if (p_buffer_descriptor->count >= p_buffer_descriptor->buffer_size)
    {
        /* If there is no more space available, and the driver already notified the application,
         * then discard the data. */
        if (p_buffer_descriptor->read_request_issued)
        {
            return;
        }

        i3c_callback_args_t callback_args =
        {
            .event     = buffer_full_event,
            .p_context = p_ctrl->p_cfg->p_context,
        };

        /* Update the buffer descriptor state so that it will not notify the application again until a new buffer
         * is provided. */
        p_buffer_descriptor->read_request_issued = true;

        /* Notify the application that the read buffer is full. */
        p_ctrl->p_cfg->p_callback(&callback_args);

        /* If the application didn't provide a new read buffer, then discard the data. */
        if (p_buffer_descriptor->read_request_issued)
        {
            return;
        }
    }

#if I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* Write the data to the read buffer one byte at a time. */
    p_buffer_descriptor->p_buffer[p_buffer_descriptor->count++] = (uint8_t) (data_word >> (i * 8U)) & UINT8_MAX;
}
#endif

#if !I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* Write the data to the read buffer one word at a time. */
    *((uint32_t *) &p_buffer_descriptor->p_buffer[p_buffer_descriptor->count]) = data_word;
    p_buffer_descriptor->count += 4;
#endif
}

/*******************************************************************************************************************//**
 * Calculate the number of bytes left in the FIFO at the end of a transfer. If the buffer is aligned, then it is safe
 * to assume that the bytes remaining is a multiple of 4 bytes.
 *
 * @param[in]  p_ctrl                Pointer to an instance's control structure.
 * @param[in]  data_length           The total transfer length read from a status descriptor.
 **********************************************************************************************************************/
static inline uint32_t i3c_read_bytes_remaining_calculate (i3c_instance_ctrl_t * p_ctrl, uint32_t data_length)
{
    uint32_t bytes_remaining = 0;
    if (p_ctrl->p_reg->NDBSTLV0_b.RDBLV > 0)
    {
        bytes_remaining = data_length - p_ctrl->read_transfer_count_final;
    }

    return bytes_remaining;
}

/*******************************************************************************************************************//**
 * Fill the transmit FIFO with data from a write buffer descriptor. If there is no more data in the write buffer,
 * then disable the transmit IRQ, and return.
 *
 * @param[in]  p_ctrl                Pointer to an instance's control structure.
 **********************************************************************************************************************/
static inline void i3c_fifo_write (i3c_instance_ctrl_t * p_ctrl)
{
    bool transfer_complete = false;
    do
    {
        /* Write data to the transmit FIFO. */
        p_ctrl->p_reg->NTDTBP0 = p_ctrl->next_word;

        /* If there is no more data to write, disable the transmit IRQ and return. */
        if (p_ctrl->write_buffer_descriptor.count >= p_ctrl->write_buffer_descriptor.buffer_size)
        {
            p_ctrl->p_reg->NTIE_b.TDBEIE0 = 0;
            i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
            R_BSP_IrqClearPending(p_extend->tx_irq);
            transfer_complete = true;
        }
        else
        {
            /* Calculate the next word of data to write to the FIFO. */
            p_ctrl->next_word = i3c_next_data_word_calculate(&p_ctrl->write_buffer_descriptor);
        }

        /* Continue writing data until the transmit FIFO is full. */
    } while ((p_ctrl->p_reg->NDBSTLV0 & UINT8_MAX) && !transfer_complete);

    /* Clear the Transmit Buffer Empty status flag. */
    p_ctrl->p_reg->NTST_b.TDBEF0 = 0;
}

/*******************************************************************************************************************//**
 * Compute the value of the next data word in a write transfer.
 *
 * @param[in]  p_buffer_descriptor   Pointer to a write buffer descriptor.
 **********************************************************************************************************************/
static inline uint32_t i3c_next_data_word_calculate (i3c_write_buffer_descriptor_t * p_buffer_descriptor)
{
    uint32_t data_word = 0;

    /* Read the current transfer count. */
    uint32_t        count           = p_buffer_descriptor->count;
    uint8_t const * p_transfer_data = p_buffer_descriptor->p_buffer;

#if I3C_CFG_UNALIGNED_BUFFER_SUPPORT

    /* Compute the value of the next data word that will be written. */
    for (uint32_t i = 0; i < sizeof(uint32_t) && count < p_buffer_descriptor->buffer_size; i++)
    {
        /* If there is no more data to write, then exit. */
        data_word |= (uint32_t) (p_transfer_data[count++] << (i * 8));
    }

#else

    /* If the buffer is aligned, then read the data from the buffer using a word access. */
    data_word = *((uint32_t *) (&p_transfer_data[count]));
    count    += 4;
#endif

    /* Update the transfer count. */
    p_buffer_descriptor->count = count;

    return data_word;
}

/*******************************************************************************************************************//**
 * Get the control instance associated with the active IRQ.
 **********************************************************************************************************************/
static inline i3c_ctrl_t * i3c_isr_context_get (void)
{
    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    i3c_instance_ctrl_t * p_ctrl = (i3c_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    R_BSP_IrqStatusClear(irq);

    return p_ctrl;
}

/*******************************************************************************************************************//**
 * ISR for handling the Command Response IRQ. The Command Response IRQ occurs on completion of a command and
 * provides status information.
 **********************************************************************************************************************/
void i3c_resp_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();

    /* Get the response status from the Response Status Queue. */
    uint32_t response_status_descriptor = p_ctrl->p_reg->NRSPQP;

    /* Clear the Response Queue Full status flag. */
    p_ctrl->p_reg->NTST_b.RSPQFF = 0;

    /* Read the DATA_LENGTH field in the response descriptor. */
    uint32_t data_length = (response_status_descriptor & I3C_RESP_STATUS_DESC_DATA_LENGTH_Msk) >>
                           I3C_RESP_STATUS_DESC_DATA_LENGTH_Pos;

    /* Read the ERR_STATUS field in the response descriptor. */
    uint32_t err_status = (response_status_descriptor & I3C_RESP_STATUS_DESC_ERR_STATUS_Msk) >>
                          I3C_RESP_STATUS_DESC_ERR_STATUS_Pos;

    bool error_recovery_case_2 = false;

    uint32_t internal_state = p_ctrl->internal_state;

    i3c_callback_args_t callback_args;
    callback_args.event        = (i3c_event_t) (internal_state & I3C_INTERNAL_EVENT_MASK);
    callback_args.event_status = err_status;
    callback_args.p_context    = p_ctrl->p_cfg->p_context;

    p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_IDLE;

    switch (internal_state)
    {
#if I3C_CFG_MASTER_SUPPORT
        case I3C_INTERNAL_STATE_MASTER_ENTDAA:
        {
            /* Reset the read buffer descriptor that was used to read the slave info. */
            p_ctrl->read_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };

            break;
        }

        case I3C_INTERNAL_STATE_MASTER_WRITE:
        case I3C_INTERNAL_STATE_MASTER_COMMAND_WRITE:
        {
            /* Calculate the total transfer length. Note that for a write transfer, the DATA_LENGTH field in the response
             * descriptor provides the number of bytes remaining. */
            callback_args.transfer_size = p_ctrl->write_buffer_descriptor.buffer_size - data_length;

            /* Reset the write buffer descriptor that was used for the transfer. */
            p_ctrl->write_buffer_descriptor = (i3c_write_buffer_descriptor_t) {
                0
            };

            /* Disable the transmit IRQ if it hasn't been disabled already. */
            p_ctrl->p_reg->NTIE_b.TDBEIE0 = 0;
            i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
            R_BSP_IrqClearPending(p_extend->tx_irq);

            break;
        }

        case I3C_INTERNAL_STATE_MASTER_READ:
        case I3C_INTERNAL_STATE_MASTER_COMMAND_READ:
        {
            uint32_t bytes_remaining = i3c_read_bytes_remaining_calculate(p_ctrl, data_length);

            /* Read the remaining byte stored in the FIFO. */
            i3c_fifo_read(p_ctrl, bytes_remaining);

 #if I3C_ERROR_RECOVERY_VERSION_1 == I3C_CFG_ERROR_RECOVERY_SUPPORT || \
            I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
  #if I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
            if (1U == I3C_A2E2_VERSION)
  #endif
            {
                /* If the transfer length is less than expected, the driver must perform error recovery defined in
                 * Figure 25.96 in the RA2E2 manual R01UH0919EJ0100. */
                if (data_length != p_ctrl->read_buffer_descriptor.buffer_size)
                {
                    error_recovery_case_2 = true;
                }
            }
 #endif

            /*
             * For a read transfer, the DATA_LENGTH field in the response descriptor provides the total number of bytes
             * read.
             */
            callback_args.transfer_size = data_length;

            /* Reset the read buffer descriptor that was used for the read transfer. */
            p_ctrl->read_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };
 #if I3C_CFG_SLAVE_SUPPORT
            if (I3C_CCC_DIRECT_GETACCMST == p_ctrl->current_command_code)
            {
                if (0U == (p_ctrl->p_reg->PRSST & R_I3C0_PRSST_CRMS_Msk))
                {
                    /* If the GETACCMST command was successful, transition the driver to slave mode. */
                    p_ctrl->internal_state = I3C_INTERNAL_STATE_SLAVE_IDLE;

                    /*
                     * Configure IBI queue threshold so that an IBI IRQ is generated when there is one empty entry in the
                     * IBI transmit FIFO.
                     */
                    p_ctrl->p_reg->NQTHCTL_b.IBIQTH = 1;
                }
                else
                {
                    /* If the command was not successfull, re-enable the IBI Write Buffer Empty/Full IRQ. */
                    p_ctrl->p_reg->NTIE_b.IBIQEFIE = 1;
                }
            }
 #endif

            p_ctrl->current_command_code = 0;
            break;
        }
#endif

#if I3C_CFG_SLAVE_SUPPORT
        case I3C_INTERNAL_STATE_SLAVE_IBI:
        {
            /* Calculate the total transfer length. Note that for an IBI transfer, the DATA_LENGTH field in the response
             * descriptor provides the number of bytes remaining. */
            callback_args.transfer_size = p_ctrl->ibi_buffer_descriptor.buffer_size - data_length;

            /* Reset the buffer descriptor that was used for the IBI transfer. */
            p_ctrl->ibi_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };

            p_ctrl->internal_state = I3C_INTERNAL_STATE_SLAVE_IDLE;
        }
#endif
        default:
        {
            break;
        }
    }

    /* Reset the total bytes read. */
    p_ctrl->read_transfer_count_final = 0;

    uint32_t ntst = p_ctrl->p_reg->NTST;

    /*
     * If the transfer was aborted, then the abort flag must be cleared before notifying the application
     * that a transfer has completed.
     */
    if (0 != (ntst & R_I3C0_NTST_TABTF_Msk))
    {
        p_ctrl->p_reg->BCTL_b.ABT = 0;
    }

    /* If a transfer error occurs, follow the error recovery operation defined in Figure 25.96 and 25.97 in the RA2E2 manual R01UH0919EJ0100. */
    if ((0 != (ntst & R_I3C0_NTST_TEF_Msk)) || error_recovery_case_2)
    {
#if I3C_CFG_SLAVE_SUPPORT
        if (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state)
        {
            i3c_slave_error_recovery(p_ctrl, I3C_SLAVE_ERROR_RECOVERY_TYPE_IBI);
        }
        else
#endif
        {
#if I3C_CFG_MASTER_SUPPORT
            i3c_master_error_recovery(p_ctrl, error_recovery_case_2);
#endif
        }
    }

    /* Clear error status flags. */
    p_ctrl->p_reg->NTST &= ~(R_I3C0_NTST_TEF_Msk | R_I3C0_NTST_TABTF_Msk);

    /* Notify the application of the event. */
    p_ctrl->p_cfg->p_callback(&callback_args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for handling the Receive Buffer Full IRQ. The Receive Buffer Full IRQ is generated when the number of entries
 * in the Receive Data Buffer is greater than or equal to the configured threshold.
 **********************************************************************************************************************/
void i3c_rx_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();

    /*
     * If the transfer is complete, the remainder of the Read Data FIFO must be read in the Receive Status Queue Full,
     * or Response Status Queue Full ISRs.
     *
     * This is because in order to read the remaining data, the driver must know exactly how many total bytes were read
     * during the transfer.
     */
    if (0 == (p_ctrl->p_reg->NTST & (R_I3C0_NTST_RSQFF_Msk | R_I3C0_NTSTE_RSPQFE_Msk)))
    {
        i3c_fifo_read(p_ctrl, p_ctrl->p_reg->NDBSTLV0_b.RDBLV * sizeof(uint32_t));
    }

#if I3C_CFG_MASTER_SUPPORT
    if (I3C_INTERNAL_STATE_MASTER_ENTDAA == p_ctrl->internal_state)
    {
        /* The address phase during ENTDAA occurs after 8 bytes (PID, BCR, and DCR) are read. */
        if (8U == p_ctrl->read_buffer_descriptor.count)
        {
            /* Reset the data pointer after reading each device PID, BCR, and DCR. */
            p_ctrl->read_buffer_descriptor.count = 0;

            /* Notify the applciation that the ENTDAA Address Phase has started. */
            i3c_callback_args_t callback_args;
            callback_args.event        = I3C_EVENT_ENTDAA_ADDRESS_PHASE;
            callback_args.p_slave_info = &p_ctrl->current_slave_info;
            callback_args.p_context    = p_ctrl->p_cfg->p_context;

            p_ctrl->p_cfg->p_callback(&callback_args);
        }
    }
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for handling the Transmit Buffer Empty IRQ. The Transmit Buffer Empty IRQ is generated when the number of
 * empties in the Transmit Data Buffer is greater than or equal to the threshold.
 **********************************************************************************************************************/
void i3c_tx_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();

    /* Write data to the FIFO. */
    i3c_fifo_write(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for handling the Receive Status Buffer Full IRQ. The Receive Status Buffer Full IRQ is generated when the
 * number of Receive Status Queue entries is greater than the threshold.
 **********************************************************************************************************************/
void i3c_rcv_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

#if I3C_CFG_SLAVE_SUPPORT
    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();

    /* Get the receive status descriptor for the Receive Status Queue. */
    uint32_t receive_status_descriptor = p_ctrl->p_reg->NRSQP;

    /* Clear the Receive Status Queue Full Flag. */
    p_ctrl->p_reg->NTST_b.RSQFF = 0;

    /* Read the DATA_LENGTH field in the response descriptor. */
    uint32_t data_length = receive_status_descriptor & I3C_RECV_STATUS_DESC_DATA_LENGTH_Msk;

    /* Read the ERR_STATUS field in the response descriptor. */
    uint32_t err_status = (receive_status_descriptor & I3C_RECV_STATUS_DESC_ERR_STATUS_Msk) >>
                          I3C_RECV_STATUS_DESC_ERR_STATUS_Pos;

    i3c_callback_args_t callback_args;
    callback_args.p_context    = p_ctrl->p_cfg->p_context;
    callback_args.event_status = err_status;

    i3c_slave_error_recovery_type_t error_recovery_type = I3C_SLAVE_ERROR_RECOVERY_TYPE_OTHER;

    /* The transfer type is a normal SDR transfer. */
    if (0U == (receive_status_descriptor & I3C_RECV_STATUS_DESC_TRANSFER_TYPE_Msk))
    {
        /* If the transfer is a read transfer. */
        if (0U == (receive_status_descriptor & I3C_RECV_STATUS_DESC_SDR_R_W_TYPE_Msk))
        {
            /* Calculate the remaining number of bytes stored in the read FIFO. */
            uint32_t bytes_remaining = i3c_read_bytes_remaining_calculate(p_ctrl, data_length);

            /* Read the remaining bytes stored in the FIFO. */
            i3c_fifo_read(p_ctrl, bytes_remaining);

            /*
             * If the last transfer was a read, then the transfer length was stored in
             * the receive status descriptor.
             */
            callback_args.transfer_size = data_length;
            callback_args.event         = I3C_EVENT_READ_COMPLETE;

            /* Reset ther state for read transfers. */
            p_ctrl->read_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };

            /* Set the error recovery procedure to use if there was a transfer error. */
            error_recovery_type = I3C_SLAVE_ERROR_RECOVERY_TYPE_READ;
        }
        else
        {
            /* Calculate the total transfer length. Note that for a write transfer, the DATA_LENGTH field in the receive
             * descriptor provides the number of bytes remaining. */
            callback_args.transfer_size = data_length;
            callback_args.event         = I3C_EVENT_WRITE_COMPLETE;

            /* Reset the state for write transfers. */
            p_ctrl->write_buffer_descriptor = (i3c_write_buffer_descriptor_t) {
                0
            };

            /* Set the error recovery procedure to use if there was a transfer error. */
            error_recovery_type = I3C_SLAVE_ERROR_RECOVERY_TYPE_WRITE;

            /* Disable the transmit IRQ if it hasn't been disabled already. */
            i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
            p_ctrl->p_reg->NTIE_b.TDBEIE0 = 0;
            R_BSP_IrqClearPending(p_extend->tx_irq);
        }
    }
    else
    {
        /*
         * The transfer type is a command.
         *
         * Get the command code from the response status descriptor.
         */
        uint8_t command_code =
            (uint8_t) ((receive_status_descriptor & I3C_RECV_STATUS_DESC_CMD_Msk) >> I3C_RECV_STATUS_DESC_CMD_Pos);

        if ((I3C_CCC_BROADCAST_ENTDAA == command_code) ||
            (I3C_CCC_DIRECT_SETDASA == command_code))
        {
            uint32_t data_length_w = (data_length + sizeof(uint32_t) - 1) / sizeof(uint32_t);
            for (uint32_t i = 0; i < data_length_w; i++)
            {
                /*
                 * Perform dummy read.
                 * See 25.3.2.1 (2) I3C Slave Operation (b) Dynamic Address Assignment Procedure in the RA2E2 manual R01UH0919EJ0100.
                 */
                p_ctrl->p_reg->NTDTBP0;
            }

            /* Reset the state for read transfers. */
            p_ctrl->read_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };

            /* Notify the application that the ENTDAA command has completed. */
            callback_args.event = I3C_EVENT_ADDRESS_ASSIGNMENT_COMPLETE;

            /* Verify that the slave address is valid. */
            if (p_ctrl->p_reg->SVDVAD0_b.SDYADV)
            {
                /* Provide the assigned dynamic address in the callback. */
                uint32_t dynamic_address_w = (p_ctrl->p_reg->SVDVAD0 & R_I3C0_SVDVAD0_SVAD_Msk);
                callback_args.dynamic_address = (uint8_t) (dynamic_address_w >> R_I3C0_SVDVAD0_SVAD_Pos) & UINT8_MAX;
            }
        }
        else
        {
            /* Calculate the remaining number of bytes stored in the read FIFO. */
            uint32_t bytes_remaining = i3c_read_bytes_remaining_calculate(p_ctrl, data_length);

            /* Read the remaining byte stored in the FIFO. */
            i3c_fifo_read(p_ctrl, bytes_remaining);

            if (I3C_CCC_DIRECT_GETACCMST == command_code)
            {
                if (0 != (p_ctrl->p_reg->PRSST & R_I3C0_PRSST_CRMS_Msk))
                {
                    /* On success of the GETACCMST command, the driver will transition to master mode. */
                    p_ctrl->internal_state = I3C_INTERNAL_STATE_MASTER_IDLE;

                    /*
                     * Configure IBI queue threshold so that an IBI IRQ is generated when there is 1 IBI status descriptor in the FIFO.
                     */
                    p_ctrl->p_reg->NQTHCTL_b.IBIQTH = 0;

                    /*
                     * In slave mode the IBI Queue Empty/Full flag indicates that the queue is empty. After transitioning to
                     * master mode, this bit indicates if there is status information in the queue. If the IBI queue was empty
                     * before tranistioning to master mode, then it will be set and the status should be cleared.
                     */
                    p_ctrl->p_reg->NTST_b.IBIQEFF = 0;
                }

                /* Re-enable the IBI Status Buffer Full IRQ. */
                p_ctrl->p_reg->NTIE_b.IBIQEFIE = 1;
            }

            if (p_ctrl->read_buffer_descriptor.count > 0)
            {
                /* Reset the state for read transfers if data was read. */
                p_ctrl->read_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                    0
                };
            }

            callback_args.event         = I3C_EVENT_COMMAND_COMPLETE;
            callback_args.command_code  = command_code;
            callback_args.transfer_size = data_length;
        }
    }

    /* Reset the total bytes read. */
    p_ctrl->read_transfer_count_final = 0;

    uint32_t ntst = p_ctrl->p_reg->NTST;

    /* If an error occurred during the transfer, perform the error recovery operation defined in Figure 25.97 in the RA2E2 manual R01UH0919EJ0100. */
    if ((0 != (ntst & (R_I3C0_NTST_TEF_Msk | R_I3C0_NTST_TABTF_Msk))) && (0U == p_ctrl->p_reg->NRSQSTLV_b.RSQLV))
    {
        if (I3C_INTERNAL_STATE_SLAVE_IDLE == p_ctrl->internal_state)
        {
            i3c_slave_error_recovery(p_ctrl, error_recovery_type);
        }
    }

    /* Clear error status flags. */
    p_ctrl->p_reg->NTST &= ~(R_I3C0_NTST_TEF_Msk | R_I3C0_NTST_TABTF_Msk);

    /* Notify the application of the event. */
    p_ctrl->p_cfg->p_callback(&callback_args);
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for writing to the IBI Data Queue in slave mode, and reading from the IBI Status Queue in master mode.
 **********************************************************************************************************************/
void i3c_ibi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();
#if I3C_CFG_SLAVE_SUPPORT
    if (I3C_INTERNAL_STATE_SLAVE_IBI == p_ctrl->internal_state)
    {
        /* Write the data to the IBI queue. */
        p_ctrl->p_reg->NIBIQP = p_ctrl->ibi_next_word;

        /* Clear the IBI Queue Empty/Full Flag. */
        p_ctrl->p_reg->NTST_b.IBIQEFF = 0;

        if (p_ctrl->ibi_buffer_descriptor.count >= p_ctrl->ibi_buffer_descriptor.buffer_size)
        {
            /* If there is no more data to write, then disable the IBI IRQ. */
            p_ctrl->p_reg->NTIE_b.IBIQEFIE = 0;
            i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
            R_BSP_IrqClearPending(p_extend->ibi_irq);
        }
        else
        {
            /* Calcaulate the next word of data that will be written to the IBI FIFO. */
            p_ctrl->ibi_next_word = i3c_next_data_word_calculate(
                (i3c_write_buffer_descriptor_t *) &p_ctrl->ibi_buffer_descriptor);
        }
    }
    else
#endif
    {
#if I3C_CFG_MASTER_SUPPORT

        /* Read the IBI status descriptor. */
        uint32_t ibi_status = p_ctrl->p_reg->NIBIQP;

        /* Get the number of bytes following the status descriptor. */
        uint32_t ibi_data_length = (ibi_status & I3C_IBI_STATUS_DESC_LENGTH_Msk) >> I3C_IBI_STATUS_DESC_LENGTH_Pos;

        /* Update the total number of bytes read during the IBI transfer. */
        p_ctrl->ibi_transfer_count_final += ibi_data_length;

        /* Calculate the number of words that need to be read from the IBI Queue. */
        uint32_t ibi_data_length_w = (ibi_data_length + sizeof(uint32_t) - 1) / sizeof(uint32_t);

        for (uint32_t i = 0; i < ibi_data_length_w; i++)
        {
            /* Get the next word of data from the IBI Queue. */
            uint32_t read_data = p_ctrl->p_reg->NIBIQP;

            /*
             * Store the next word of data into the read buffer. If there is not enough space, a I3C_EVENT_IBI_READ_BUFFER_FULL
             * event will be called to notify the application that a new read buffer is required.
             */
            i3c_read_buffer_store(p_ctrl,
                                  &p_ctrl->ibi_buffer_descriptor,
                                  read_data,
                                  ibi_data_length,
                                  I3C_EVENT_IBI_READ_BUFFER_FULL);
            ibi_data_length -= 4;
        }

        /* Clear the IBI Queue Empty/Full Flag. */
        p_ctrl->p_reg->NTST_b.IBIQEFF = 0;

        /* If this is the last IBI status descriptor, then the IBI transfer is completed. */
        if (0U != (I3C_IBI_STATUS_DESC_LAST_STATUS_Msk & ibi_status))
        {
            /* Get the address of the IBI transfer. */
            uint8_t ibi_address = (ibi_status & I3C_IBI_STATUS_DESC_IBI_ID_Msk) >>
                                  (I3C_IBI_STATUS_DESC_IBI_ID_Pos + 1);

            /* Get the RNW bit of the IBI transfer. */
            uint8_t ibi_rnw = (ibi_status >> I3C_IBI_STATUS_DESC_IBI_ID_Pos) & 1U;

            uint32_t err_status =
                (ibi_status & (I3C_IBI_STATUS_DESC_IBI_ST_Msk | I3C_IBI_STATUS_DESC_ERR_STATUS_Msk)) >>
                I3C_IBI_STATUS_DESC_ERR_STATUS_Pos;
            i3c_callback_args_t callback_args =
            {
                .event         = I3C_EVENT_IBI_READ_COMPLETE,
                .event_status  = err_status,
                .ibi_type      = I3C_IBI_TYPE_INTERRUPT,
                .ibi_address   = ibi_address,
                .transfer_size = p_ctrl->ibi_transfer_count_final,
                .p_context     = p_ctrl->p_cfg->p_context
            };

            if (I3C_HOT_JOIN_ADDRESS == ibi_address)
            {
                callback_args.ibi_type = I3C_IBI_TYPE_HOT_JOIN;
            }
            else if (0U == ibi_rnw)
            {
                callback_args.ibi_type = I3C_IBI_TYPE_MASTERSHIP_REQUEST;
            }
            else
            {
                /* IBI type is I3C_IBI_TYPE_INTERRUPT. */
            }

            p_ctrl->ibi_buffer_descriptor = (i3c_read_buffer_descriptor_t) {
                0
            };
            p_ctrl->ibi_transfer_count_final = 0;

            /* Notify the application of the event. */
            p_ctrl->p_cfg->p_callback(&callback_args);
        }
#endif
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for providing the following events to the application:
 * - I3C_EVENT_INTERNAL_ERROR: An internal error can occur if too many transfers occur sequenctionally and overflow
 *                             the Receive Status Queue (See 25.2.7 INST: Internal Status Register in the RA2E2
 *                             manual R01UH0919EJ0100).
 * - I3C_EVENT_TIMEOUT_DETECTED
 * - I3C_EVENT_HDR_EXIT_PATTERN_DETECTED
 **********************************************************************************************************************/
void i3c_eei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    i3c_instance_ctrl_t * p_ctrl = i3c_isr_context_get();

    i3c_callback_args_t callback_args;
    callback_args.p_context = p_ctrl->p_cfg->p_context;

    /* Read the Internal Status Register. */
    uint32_t inst            = p_ctrl->p_reg->INST;
    uint32_t inst_clear_mask = 0;

    /* Read the Bus Status Register. */
    uint32_t bst            = p_ctrl->p_reg->BST;
    uint32_t bst_clear_mask = 0;

    if (0U != (inst & R_I3C0_INST_INEF_Msk))
    {
        /* Notify the application of the internal error. */
        callback_args.event = I3C_EVENT_INTERNAL_ERROR;
        p_ctrl->p_cfg->p_callback(&callback_args);

        inst_clear_mask |= R_I3C0_INST_INEF_Msk;

        /* Resume I3C operation. */
        p_ctrl->p_reg->BCTL_b.RSM = 1;
    }

    /* Check if a timeout occurred. */
    if (0U != (bst & R_I3C0_BST_TODF_Msk))
    {
        /* Notify that application that the timeout was detected. */
        callback_args.event = I3C_EVENT_TIMEOUT_DETECTED;
        p_ctrl->p_cfg->p_callback(&callback_args);

        bst_clear_mask |= R_I3C0_BST_TODF_Msk;
    }

    /* Check if the HDR Exit Pattern was detected. */
    if (0U != (bst & R_I3C0_BST_HDREXDF_Msk))
    {
        /* Notify that application that the HDR Exit pattern was detected. */
        callback_args.event = I3C_EVENT_HDR_EXIT_PATTERN_DETECTED;
        p_ctrl->p_cfg->p_callback(&callback_args);

        bst_clear_mask |= R_I3C0_BST_HDREXDF_Msk;
    }

    /* Clear the status flags that have been handled. */
    p_ctrl->p_reg->INST &= ~inst_clear_mask;
    p_ctrl->p_reg->BST  &= ~bst_clear_mask;

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if I3C_CFG_MASTER_SUPPORT

/*******************************************************************************************************************//**
 * Perform error recovery according to Figure 25.96 in the RA2E2 manual R01UH0919EJ0100
 **********************************************************************************************************************/
void i3c_master_error_recovery (i3c_instance_ctrl_t * p_ctrl, bool error_recovery_case_2)
{
 #if I3C_ERROR_RECOVERY_VERSION_1 == I3C_CFG_ERROR_RECOVERY_SUPPORT || \
    I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
  #if I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT

    /* For A2E2 version that has not been modified by ECO, the following error recovery procedure must be performed.
     * See Figure 25.96 in the RA2E2 manual R01UH0919EJ0100. */
    if (1U == I3C_A2E2_VERSION)
  #endif
    {
        /* Flush the Command, Rx and Tx Buffers. */
        p_ctrl->p_reg->RSTCTL = I3C_RSTCTRL_FIFO_FLUSH_Msk;

        /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
        FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->RSTCTL & I3C_RSTCTRL_FIFO_FLUSH_Msk), 0U);

        /* Wait for the bus available condition. */
        while (1)
        {
            /* If SDA is pulled low, then a slave device started an IBI during error recovery. */
            if (0U == p_ctrl->p_reg->PRSTDBG_b.SDILV)
            {
                break;
            }

            /* Check the bus available condition. */
            if (1 == p_ctrl->p_reg->BCST_b.BAVLF)
            {
                break;
            }
        }

        if (error_recovery_case_2)
        {
            /* Disable the IBI Status Buffer Full IRQ. */
            p_ctrl->p_reg->NTIE_b.IBIQEFIE = 0;

            /* When recovering from a read operation where the transfer length is less than expected, perform internal
             * software reset. */
            p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_INTLRST_Msk;
            p_ctrl->p_reg->RSTCTL = 0;

            /* Restore the current master setting. */
            p_ctrl->p_reg->PRSST = (uint32_t) (R_I3C0_PRSST_CRMS_Msk | R_I3C0_PRSST_PRSSTWP_Msk);

            /* After an internal reset, the CRMS bit is cleared which causes the IBI Queue Empty/Full Flag to be set indicating the queue is empty.
             * Since the driver is in master mode, this status should be discarded and the flag should be cleared. */
            p_ctrl->p_reg->NTST_b.IBIQEFF = 0;

            /* Enable the IBI Status Buffer Full IRQ. */
            p_ctrl->p_reg->NTIE_b.IBIQEFIE = 1;
        }
        else
        {
            /* Resume I3C operation. */
            p_ctrl->p_reg->BCTL_b.RSM = 1;
        }

        /* If a slave device started an IBI during error recovery, then it must be NACK'd or SDA will be held low indefinitely. */
        if (0U == p_ctrl->p_reg->PRSTDBG_b.SDILV)
        {
            /* Calculate the frequency of PCLKD. */
            uint32_t pclkd_frequency = (SystemCoreClock << R_SYSTEM->SCKDIVCR_b.ICK);
            pclkd_frequency >>= R_SYSTEM->SCKDIVCR_b.PCKD;

            i3c_extended_cfg_t * p_extend = (i3c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

            /* Get the low and high period in PCLKD ticks. */
            uint32_t pclkd_low_period = (p_extend->bitrate_settings.stdbr & R_I3C0_STDBR_SBRLO_Msk) >>
                                        R_I3C0_STDBR_SBRLO_Pos;
            uint32_t pclkd_high_period = (p_extend->bitrate_settings.stdbr & R_I3C0_STDBR_SBRHO_Msk) >>
                                         R_I3C0_STDBR_SBRHO_Pos;

            /* Calculate the high and low period for SCL. */
            uint32_t high_frequency = pclkd_frequency / pclkd_high_period;
            uint32_t low_frequency  = pclkd_frequency / pclkd_low_period;
            uint32_t high_delay_us  = (1000000U + high_frequency - 1) / high_frequency; // NOLINT(readability-magic-numbers)
            uint32_t low_delay_us   = (1000000U + low_frequency - 1) / low_frequency;   // NOLINT(readability-magic-numbers)

            /* Check if BITCNT is working correctly. */
            bool bcnt_zero = true;
            for (uint32_t i = 0; i < 4; i++)
            {
                R_BSP_SoftwareDelay(high_delay_us + low_delay_us, BSP_DELAY_UNITS_MICROSECONDS);
                if (0 != p_ctrl->p_reg->BITCNT_b.BCNT)
                {
                    bcnt_zero = false;
                }
            }

            /* If BITCNT is not incrementing, then the master is not aware of the IBI. */
            if (bcnt_zero)
            {
                /* Write SCL low in order to complete the start condition. */
                p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SDOC_Msk | R_I3C0_OUTCTL_SOCWP_Msk;

                R_BSP_SoftwareDelay(low_delay_us, BSP_DELAY_UNITS_MICROSECONDS);

                /* Complete 9 SCL clock cycles while holding SDA high in order to NACK the IBI. */
                for (uint32_t i = 0; i < 9; i++)
                {
                    /* Write SCL high. */
                    p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SDOC_Msk | R_I3C0_OUTCTL_SCOC_Msk | R_I3C0_OUTCTL_SOCWP_Msk;

                    R_BSP_SoftwareDelay(high_delay_us, BSP_DELAY_UNITS_MICROSECONDS);

                    /* Write SCL low. */
                    p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SDOC_Msk | R_I3C0_OUTCTL_SOCWP_Msk;

                    R_BSP_SoftwareDelay(low_delay_us, BSP_DELAY_UNITS_MICROSECONDS);
                }

                /* Write SCL and SDA low. */
                p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SOCWP_Msk;

                R_BSP_SoftwareDelay(low_delay_us, BSP_DELAY_UNITS_MICROSECONDS);

                /* Write SCL high. */
                p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SCOC_Msk | R_I3C0_OUTCTL_SOCWP_Msk;

                R_BSP_SoftwareDelay(high_delay_us, BSP_DELAY_UNITS_MICROSECONDS);

                /* Write SDA anb SCL high to complete the stop condition. */
                p_ctrl->p_reg->OUTCTL = R_I3C0_OUTCTL_SDOC_Msk | R_I3C0_OUTCTL_SCOC_Msk | R_I3C0_OUTCTL_SOCWP_Msk;
            }
        }
    }
 #endif

 #if I3C_ERROR_RECOVERY_VERSION_2 == I3C_CFG_ERROR_RECOVERY_SUPPORT || \
    I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
  #if I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT

    /* For A2E2 version that has been modified by ECO, simplified error recovery procedure can be performed. */
    if (2U == I3C_A2E2_VERSION)
  #endif
    {
        FSP_PARAMETER_NOT_USED(error_recovery_case_2);

        /* Flush the Command, Rx and Tx Buffers. */
        p_ctrl->p_reg->RSTCTL = I3C_RSTCTRL_FIFO_FLUSH_Msk;

        /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
        FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->RSTCTL & I3C_RSTCTRL_FIFO_FLUSH_Msk), 0U);

        /* Resume I3C operation. */
        p_ctrl->p_reg->BCTL_b.RSM = 1;
    }
 #endif
}

#endif

#if I3C_CFG_SLAVE_SUPPORT

/*******************************************************************************************************************//**
 * Perform error recovery according to Figure 25.97 in the RA2E2 manual R01UH0919EJ0100
 **********************************************************************************************************************/
void i3c_slave_error_recovery (i3c_instance_ctrl_t * p_ctrl, i3c_slave_error_recovery_type_t recovery_type)
{
    switch (recovery_type)
    {
        case I3C_SLAVE_ERROR_RECOVERY_TYPE_WRITE:
        {
            /* Flush the Command and Tx Data FIFO. */
            p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_TDBRST_Msk;
            break;
        }

        case I3C_SLAVE_ERROR_RECOVERY_TYPE_READ:
        {
            /* Flush the Command and Rx Data FIFO. */
            p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_RDBRST_Msk;
            break;
        }

        case I3C_SLAVE_ERROR_RECOVERY_TYPE_IBI:
        {
            /* Flush the Command and Rx Data FIFO. */
            p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_CMDQRST_Msk;
            break;
        }

        default:
        {
            break;
        }
    }

    /* The field will be cleared automatically upon reset completion (See section 25.2.5 in the RA2E2 manual R01UH0919EJ0100). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL, 0U);

 #if I3C_ERROR_RECOVERY_VERSION_1 == I3C_CFG_ERROR_RECOVERY_SUPPORT || \
    I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
  #if I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT

    /* For A2E2 version that has not been modified by ECO, the following error recovery procedure must be performed.
     * See Figure 25.97 in the RA2E2 manual R01UH0919EJ0100. */
    if (1U == I3C_A2E2_VERSION)
  #endif
    {
        /* Wait for Bus Available Condition (See Figure 25.97 in the RA2E2 manual R01UH0919EJ0100). */
        FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->BCST & R_I3C0_BCST_BAVLF_Msk), R_I3C0_BCST_BAVLF_Msk);

        /* Wait for start condition to be cleared (See Figure 25.97 in the RA2E2 manual R01UH0919EJ0100).. */
        FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->BST & R_I3C0_BST_STCNDDF_Msk), 0);

        /* Read the current value of SDDYAD. */
        uint32_t sdatbas0 = p_ctrl->p_reg->SDATBAS0;

        /* Perform internal software reset. */
        p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_INTLRST_Msk;
        p_ctrl->p_reg->RSTCTL = 0;

        /* Calculate the frequency of PCLKD. */
        uint32_t pclkd_frequency = (SystemCoreClock << R_SYSTEM->SCKDIVCR_b.ICK);
        pclkd_frequency >>= R_SYSTEM->SCKDIVCR_b.PCKD;

        /* Wait for the expected amount of time for the Bus Available Condition. */
        uint32_t expected_bus_available_time =
            (1000000U * p_ctrl->p_reg->BAVLCDT + pclkd_frequency - 1) / pclkd_frequency; // NOLINT(readability-magic-numbers)

        R_BSP_SoftwareDelay(expected_bus_available_time, BSP_DELAY_UNITS_MICROSECONDS);

        /* If the Bus is already available then error recovery is complete. */
        if (0 == (p_ctrl->p_reg->BCST & R_I3C0_BCST_BAVLF_Msk))
        {
            while (0 == (p_ctrl->p_reg->BST & R_I3C0_BST_STCNDDF_Msk))
            {
                /* Perform internal software reset. */
                p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_INTLRST_Msk;

                /* Wait for Bus Available Condition (See Figure 25.97 in the RA2E2 manual R01UH0919EJ0100).. */
                FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->BCST & R_I3C0_BCST_BAVLF_Msk), R_I3C0_BCST_BAVLF_Msk);

                p_ctrl->p_reg->RSTCTL = 0;
            }
        }

        /* Write back value of SDDYAD. */
        p_ctrl->p_reg->SDATBAS0 = sdatbas0;
    }
 #endif
 #if I3C_ERROR_RECOVERY_VERSION_2 == I3C_CFG_ERROR_RECOVERY_SUPPORT || \
    I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT
  #if I3C_ERROR_RECOVERY_VERSION_BOTH == I3C_CFG_ERROR_RECOVERY_SUPPORT

    /* For A2E2 version that has been modified by ECO, simplified error recovery procedure can be performed. */
    if (2U == I3C_A2E2_VERSION)
  #endif
    {
        /* Resume I3C operation. */
        p_ctrl->p_reg->BCTL_b.RSM = 1;
    }
 #endif
}

#endif
