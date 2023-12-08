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
#include <string.h>
#include "r_mipi_dsi.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MIPI_DSI_OPEN                (0x4D504944)
#define MIPI_MAX_CH0_CMD             (128)
#define MIPI_MAX_CH1_CMD             (1024)
#define MIPI_DSI_RSRST_RESET_BITS    (R_DSILINK_RSTSR_RSTHS_Msk |  \
                                      R_DSILINK_RSTSR_RSTLP_Msk |  \
                                      R_DSILINK_RSTSR_RSTAPB_Msk | \
                                      R_DSILINK_RSTSR_RSTAXI_Msk | \
                                      R_DSILINK_RSTSR_RSTV_Msk)

#define DSI_PACKET_FORMAT_IS_SHORT(cmd_id)    ((cmd_id & 0x0F) <= 0x08)
#define DSI_PACKET_FORMAT_IS_LONG(cmd_id)     ((cmd_id & 0x0F) > 0x08)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * mipi_dsi_prv_ns_callback)(mipi_dsi_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile mipi_dsi_prv_ns_callback)(mipi_dsi_callback_args_t * p_args);
#endif

typedef enum e_mipi_dsi_clock_state
{
    MIPI_DSI_CLOCK_STATE_IDLE,         ///< MIPI DSI Clock is off
    MIPI_DSI_CLOCK_STATE_STARTING,     ///< MIPI DSI Clock starting
    MIPI_DSI_CLOCK_STATE_STARTED,      ///< MIPI DSI Clock is started
    MIPI_DSI_CLOCK_STATE_STOPPING,     ///< MIPI DSI Clock is stopping
} mipi_dsi_clock_state_t;

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
static volatile mipi_dsi_clock_state_t g_clock_state;
static volatile bool g_video_started;

const mipi_dsi_api_t g_mipi_dsi =
{
    .open      = R_MIPI_DSI_Open,
    .close     = R_MIPI_DSI_Close,
    .start     = R_MIPI_DSI_Start,
    .stop      = R_MIPI_DSI_Stop,
    .ulpsEnter = R_MIPI_DSI_UlpsEnter,
    .ulpsExit  = R_MIPI_DSI_UlpsExit,
    .command   = R_MIPI_DSI_Command,
    .statusGet = R_MIPI_DSI_StatusGet,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void mipi_dsi_seq0(void);
void mipi_dsi_seq1(void);
void mipi_dsi_vin1(void);
void mipi_dsi_rcv(void);
void mipi_dsi_ferr(void);
void mipi_dsi_ppi(void);

static void dsi_isr_enable(mipi_dsi_irq_cfg_t const * irq_cfg, mipi_dsi_instance_ctrl_t * p_ctrl);
static void dsi_isr_disable(mipi_dsi_irq_cfg_t const * irq_cfg);

static void dsi_enter_reset(void);
static void dsi_init_timing(mipi_dsi_cfg_t const * const p_cfg);
static void dsi_exit_reset(mipi_dsi_cfg_t const * const p_cfg);
static void dsi_hs_clock_start(mipi_dsi_instance_ctrl_t * p_ctrl);
static void dsi_hs_clock_stop(mipi_dsi_instance_ctrl_t * p_ctrl);

static void dsi_init_video(mipi_dsi_cfg_t const * p_cfg);

static void dsi_call_callback(mipi_dsi_instance_ctrl_t * p_ctrl, mipi_dsi_callback_args_t * p_args);

static fsp_err_t dsi_stop(mipi_dsi_instance_ctrl_t * p_ctrl);
static uint32_t  dsi_cmd_sequence_register_a(mipi_dsi_cmd_t * p_cmd);
static uint32_t  dsi_cmd_sequence_register_b(mipi_dsi_cmd_t * p_cmd);
static uint32_t  dsi_cmd_sequence_register_c(mipi_dsi_cmd_t * p_cmd);
static uint32_t  dsi_cmd_sequence_register_d(mipi_dsi_cmd_t * p_cmd);

/*******************************************************************************************************************//**
 * @addtogroup MIPI_DSI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Initialize the MIPI DSI peripheral.
 *
 * @retval FSP_SUCCESS                     The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION               One or both of the parameters was NULL.
 * @retval FSP_ERR_ALREADY_OPEN            The instance is already opened.
 * @retval FSP_ERR_INVALID_STATE           Display module must be opened before DSI.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_Open (mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_cfg_t const * const p_cfg)
{
    fsp_err_t err;
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    FSP_ERROR_RETURN(R_GLCDC->SYSCNT.PANEL_CLK_b.CLKEN, FSP_ERR_INVALID_STATE);

    /* Initialize internal state */
    g_clock_state   = MIPI_DSI_CLOCK_STATE_IDLE;
    g_video_started = false;
    p_ctrl->p_cfg   = p_cfg;

    /* Start clocks to the MIPI DSI peripheral */
    R_BSP_MODULE_START(FSP_IP_MIPI_DSI, 0);

    err = r_mipi_phy_open(p_cfg->p_mipi_phy_instance->p_ctrl, p_cfg->p_mipi_phy_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Perform sequence steps 5 to 9 from section 58.3.2 in RA8D1 hardware manual R01UH0995EJ0060. */
    dsi_enter_reset();
    dsi_init_timing(p_cfg);
    dsi_exit_reset(p_cfg);

    /* Configure interrupt sources */
    mipi_dsi_extended_cfg_t * p_extend = (mipi_dsi_extended_cfg_t *) p_cfg->p_extend;
    R_DSILINK->RXIER    = p_extend->dsi_rxie;
    R_DSILINK->FERRIER  = p_extend->dsi_ferrie;
    R_DSILINK->PLIER    = p_extend->dsi_plie;
    R_DSILINK->VMIER    = p_extend->dsi_vmie;
    R_DSILINK->SQCH0IER = p_extend->dsi_sqch0ie;
    R_DSILINK->SQCH1IER = p_extend->dsi_sqch1ie;

    /* Clear any active status bits */
    R_DSILINK->SQCH0SCR = R_DSILINK_SQCH0SCR_AACTFIN_Msk |
                          R_DSILINK_SQCH0SCR_ADESFIN_Msk |
                          R_DSILINK_SQCH0SCR_DABORT_Msk |
                          R_DSILINK_SQCH0SCR_SIZEERR_Msk |
                          R_DSILINK_SQCH0SCR_TXIBERR_Msk |
                          R_DSILINK_SQCH0SCR_RXFERR_Msk |
                          R_DSILINK_SQCH0SCR_RXFAIL_Msk |
                          R_DSILINK_SQCH0SCR_RXPFAIL_Msk |
                          R_DSILINK_SQCH0SCR_RXCORERR_Msk |
                          R_DSILINK_SQCH0SCR_RXAKE_Msk;
    R_DSILINK->SQCH1SCR = R_DSILINK_SQCH1SCR_AACTFIN_Msk |
                          R_DSILINK_SQCH1SCR_ADESFIN_Msk |
                          R_DSILINK_SQCH1SCR_DABORT_Msk |
                          R_DSILINK_SQCH1SCR_SIZEERR_Msk |
                          R_DSILINK_SQCH1SCR_TXIBERR_Msk |
                          R_DSILINK_SQCH1SCR_RXFERR_Msk |
                          R_DSILINK_SQCH1SCR_RXFAIL_Msk |
                          R_DSILINK_SQCH1SCR_RXPFAIL_Msk |
                          R_DSILINK_SQCH1SCR_RXCORERR_Msk |
                          R_DSILINK_SQCH1SCR_RXAKE_Msk;
    R_DSILINK->VMSCR = R_DSILINK_VMSCR_START_Msk |
                       R_DSILINK_VMSCR_STOP_Msk |
                       R_DSILINK_VMSCR_VIRDY_Msk |
                       R_DSILINK_VMSCR_TIMERR_Msk |
                       R_DSILINK_VMSCR_VBUFUDF_Msk |
                       R_DSILINK_VMSCR_VBUFOVF_Msk;
    R_DSILINK->RXSCR = R_DSILINK_RXSCR_BTAREND_Msk |
                       R_DSILINK_RXSCR_LRXHTO_Msk |
                       R_DSILINK_RXSCR_TATO_Msk |
                       R_DSILINK_RXSCR_RXRESP_Msk |
                       R_DSILINK_RXSCR_RXEOTP_Msk |
                       R_DSILINK_RXSCR_RXTE_Msk |
                       R_DSILINK_RXSCR_RXACK_Msk |
                       R_DSILINK_RXSCR_EXTEDET_Msk |
                       R_DSILINK_RXSCR_MLFERR_Msk |
                       R_DSILINK_RXSCR_ECCERRM_Msk |
                       R_DSILINK_RXSCR_UNEXERR_Msk |
                       R_DSILINK_RXSCR_WCERR_Msk |
                       R_DSILINK_RXSCR_CRCERR_Msk |
                       R_DSILINK_RXSCR_IBERR_Msk |
                       R_DSILINK_RXSCR_RXOVFERR_Msk |
                       R_DSILINK_RXSCR_PRTOERR_Msk |
                       R_DSILINK_RXSCR_NORESERR_Msk |
                       R_DSILINK_RXSCR_RSIZEERR_Msk |
                       R_DSILINK_RXSCR_ECCERRS_Msk |
                       R_DSILINK_RXSCR_RXAKE_Msk;

    p_ctrl->p_callback_memory = NULL;
    p_ctrl->p_callback        = p_cfg->p_callback;

    /* Enable interrupts */
    p_ctrl->p_context = p_cfg->p_context;
    dsi_isr_enable(&p_extend->dsi_seq0, p_ctrl);
    dsi_isr_enable(&p_extend->dsi_seq1, p_ctrl);
    dsi_isr_enable(&p_extend->dsi_ferr, p_ctrl);
    dsi_isr_enable(&p_extend->dsi_ppi, p_ctrl);
    dsi_isr_enable(&p_extend->dsi_rcv, p_ctrl);
    dsi_isr_enable(&p_extend->dsi_vin1, p_ctrl);

    /* Mark control block as opened */
    p_ctrl->open = MIPI_DSI_OPEN;

    /* Start high-speed clock and init video */
    dsi_hs_clock_start(p_ctrl);
    dsi_init_video(p_cfg);

    /* Notify application that DSI is now open */
    mipi_dsi_callback_args_t callback_args;
    callback_args.event     = MIPI_DSI_EVENT_POST_OPEN;
    callback_args.p_context = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &callback_args);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Close MIPI DSI and display data instances, disable interrupts, and power-off the module.
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Instance is not open.
 * @retval   FSP_ERR_IN_USE        Operation in progress and must be stopped before closing.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_Close (mipi_dsi_ctrl_t * const p_api_ctrl)
{
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Ensure video has stopped first */
    fsp_err_t err = dsi_stop(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    dsi_hs_clock_stop(p_ctrl);

    mipi_dsi_cfg_t const    * p_cfg    = p_ctrl->p_cfg;
    mipi_dsi_extended_cfg_t * p_extend = (mipi_dsi_extended_cfg_t *) p_cfg->p_extend;
    dsi_isr_disable(&p_extend->dsi_seq0);
    dsi_isr_disable(&p_extend->dsi_seq1);
    dsi_isr_disable(&p_extend->dsi_ferr);
    dsi_isr_disable(&p_extend->dsi_ppi);
    dsi_isr_disable(&p_extend->dsi_rcv);
    dsi_isr_disable(&p_extend->dsi_vin1);

    /* Close MIPI PHY */
    r_mipi_phy_close(p_cfg->p_mipi_phy_instance->p_ctrl);

    /* Set control block to closed */
    p_ctrl->open = 0U;

    /* Stop clocks to the MIPI DSI peripheral */
    R_BSP_MODULE_STOP(FSP_IP_MIPI_DSI, 0);

    return err;
}

/******************************************************************************************************************//**
 * Start video output.
 * Initialize Video Output Registers
 * Perform sequence steps 3 to 5 from section 58.3.6.1 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @retval   FSP_SUCCESS                Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_IN_USE             The physical interface is currently in use.
 * @retval   FSP_ERR_INVALID_STATE      DSI is already in video mode.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_Start (mipi_dsi_ctrl_t * const p_api_ctrl)
{
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!g_video_started, FSP_ERR_INVALID_STATE);
#endif

    /* Notify application that DSI is now open */
    mipi_dsi_callback_args_t callback_args;
    callback_args.event     = MIPI_DSI_EVENT_PRE_START;
    callback_args.p_context = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &callback_args);

    /* Do not start video if sequence operation is in progress */
    FSP_ERROR_RETURN(!(R_DSILINK->LINKSR_b.SQ0RUN) && !(R_DSILINK->LINKSR_b.SQ1RUN), FSP_ERR_IN_USE);

    mipi_dsi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    R_DSILINK->VMSET0R =
        (((uint32_t) p_cfg->hsa_no_lp << R_DSILINK_VMSET0R_HSANOLP_Pos) & R_DSILINK_VMSET0R_HSANOLP_Msk) |
        (((uint32_t) p_cfg->hbp_no_lp << R_DSILINK_VMSET0R_HBPNOLP_Pos) & R_DSILINK_VMSET0R_HBPNOLP_Msk) |
        (((uint32_t) p_cfg->hfp_no_lp << R_DSILINK_VMSET0R_HFPNOLP_Pos) & R_DSILINK_VMSET0R_HFPNOLP_Msk) |
        R_DSILINK_VMSET0R_VSTART_Msk;

    while ((R_DSILINK->VMSR_b.VIRDY != 1) && !g_video_started)
    {
        /* Wait for video mode ready status
         *  NOTE: VMSR may be modified in isr */
    }

    g_video_started = true;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop video output.
 *
 * @retval   FSP_SUCCESS                Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_IN_USE             DSI cannot be closed while ULPS is active.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_Stop (mipi_dsi_ctrl_t * const p_api_ctrl)
{
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    return dsi_stop(p_ctrl);
}

/******************************************************************************************************************//**
 * Enter Ultra-low Power State (ULPS).
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 * @retval   FSP_ERR_INVALID_MODE      Invalid mode for transition.
 *
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_UlpsEnter (mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_lane_t lane)
{
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Clock lane cannot enter ULPS when Continuous CLock mode is active */
    FSP_ERROR_RETURN(!((MIPI_DSI_LANE_CLOCK & lane) && R_DSILINK->HSCLKSETR_b.HSCLMD), FSP_ERR_INVALID_MODE);
#endif

    /* Do not set 'enter ULPS' bit if lane is already in ULPS */
    uint32_t ulpscr = ((MIPI_DSI_LANE_DATA_ALL & lane) && !p_ctrl->data_ulps_active) ? R_DSILINK_ULPSCR_DLENT_Msk : 0;
    ulpscr |=
        ((MIPI_DSI_LANE_CLOCK & lane) && !p_ctrl->clock_ulps_active) ? R_DSILINK_ULPSCR_CLENT_Msk : 0;
    p_ctrl->ulps_status |= lane;

    p_ctrl->clock_ulps_active = p_ctrl->clock_ulps_active || (MIPI_DSI_LANE_CLOCK & lane);
    p_ctrl->data_ulps_active  = p_ctrl->data_ulps_active || (MIPI_DSI_LANE_DATA_ALL & lane);

    R_DSILINK->ULPSCR = ulpscr;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Exit Ultra-low Power State (ULPS).
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 *
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_UlpsExit (mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_lane_t lane)
{
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;
#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Do not set 'exit ULPS' bit if lane is not in ULPS */
    uint32_t ulpscr = ((MIPI_DSI_LANE_DATA_ALL & lane) && p_ctrl->data_ulps_active) ? R_DSILINK_ULPSCR_DLEXIT_Msk : 0;
    ulpscr |=
        ((MIPI_DSI_LANE_CLOCK & lane) && p_ctrl->clock_ulps_active) ? R_DSILINK_ULPSCR_CLEXIT_Msk : 0;

    p_ctrl->clock_ulps_active = p_ctrl->clock_ulps_active && !(MIPI_DSI_LANE_CLOCK & lane);
    p_ctrl->data_ulps_active  = p_ctrl->data_ulps_active && !(MIPI_DSI_LANE_DATA_ALL & lane);

    R_DSILINK->ULPSCR    = ulpscr;
    p_ctrl->ulps_status &= ~lane;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Send a command to the peripheral device.
 *
 * @note p_data will be used as either write data or a read buffer depending on the data id.
 * @note p_data memory must not be updated until sequence operation is complete if byte_count is greater than 16.
 *
 * @retval   FSP_SUCCESS                Command(s) queued successfully.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 *                                      cmd_id specifies a long packet but p_data is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_IN_USE             The physical interface is currently in use or video mode is in operation.
 * @retval   FSP_ERR_INVALID_POINTER    Invalid pointer provided
 * @retval   FSP_ERR_INVALID_ARGUMENT   Invalid message configuration
 * @retval   FSP_ERR_INVALID_CHANNEL    Invalid channel for provided message configuration
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_Command (mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_cmd_t * p_cmd)
{
#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;

    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_cmd, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_cmd->p_tx_buffer || (p_cmd->tx_len == 0), FSP_ERR_INVALID_ARGUMENT);                     // Tx buffer must be supplied for non-zero Tx length

    FSP_ERROR_RETURN(!((p_cmd->channel == 0) && (p_cmd->tx_len > MIPI_MAX_CH0_CMD)), FSP_ERR_INVALID_ARGUMENT); // Max Tx size is 128 for channel 0
    FSP_ERROR_RETURN(!((p_cmd->channel == 1) && (p_cmd->tx_len > MIPI_MAX_CH1_CMD)), FSP_ERR_INVALID_ARGUMENT); // Max Tx size is 1k for channel 1

    /* AUX Operation */
    bool aux = (p_cmd->flags & MIPI_DSI_CMD_FLAG_AUX_OPERATION);
    if (aux)
    {
        bool bta = p_cmd->flags &
                   (MIPI_DSI_CMD_FLAG_BTA | MIPI_DSI_CMD_FLAG_BTA_READ | MIPI_DSI_CMD_FLAG_BTA_NO_WRITE);
        bool initial_skew  = (p_cmd->flags & MIPI_DSI_CMD_FLAG_ACT_CODE_INITIAL_SKEW_CAL);
        bool periodic_skew = (p_cmd->flags & MIPI_DSI_CMD_FLAG_ACT_CODE_PERIODIC_SKEW_CAL);
        FSP_ERROR_RETURN(!bta && !p_cmd->tx_len, FSP_ERR_INVALID_ARGUMENT);
        FSP_ERROR_RETURN(!R_DSILINK->LINKSR_b.VRUN, FSP_ERR_INVALID_ARGUMENT);                                 // Aux operation is prohibited when video mode is running
        FSP_ERROR_RETURN(!(initial_skew || periodic_skew) || (p_cmd->channel != 0), FSP_ERR_INVALID_ARGUMENT); // Periodic and Initial skew must be HS
    }

    uint8_t lp = (0 != (p_cmd->flags & MIPI_DSI_CMD_FLAG_LOW_POWER));

    FSP_ERROR_RETURN(!(lp && R_DSILINK->LINKSR_b.VRUN), FSP_ERR_IN_USE);       // LP not allowed during video mode operation. See RA8D1 UM 58.2.61 (R01UH0995EJ0060)
    FSP_ERROR_RETURN(!(lp && (p_cmd->channel != 0)), FSP_ERR_INVALID_CHANNEL); // LP only allowed on channel 0
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    /* Do not modify registers if sequence operation is currently in progress */
    FSP_ERROR_RETURN(!(R_DSILINK->LINKSR_b.SQ0RUN) && !(R_DSILINK->LINKSR_b.SQ1RUN), FSP_ERR_IN_USE);

    uint32_t * p_sequence_reg = (uint32_t *) (&R_DSILINK->SQCH0DSC0AR);
    p_sequence_reg   += (p_cmd->channel * 0x80) / 4; // NOLINT(readability-magic-numbers)
    *p_sequence_reg++ = dsi_cmd_sequence_register_a(p_cmd);
    *p_sequence_reg++ = dsi_cmd_sequence_register_b(p_cmd);
    *p_sequence_reg++ = dsi_cmd_sequence_register_c(p_cmd);
    *p_sequence_reg++ = dsi_cmd_sequence_register_d(p_cmd);

    /* Start sequence operation */
    R_DSILINK->SQCH0SET0R = (bool) (0 == p_cmd->channel);
    R_DSILINK->SQCH1SET0R = (bool) (1 == p_cmd->channel);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Provide information about current MIPI DSI status.
 *
 * Note: Acknowledge and Error Status is only cleared when read by calling this function.
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 *
 **********************************************************************************************************************/
fsp_err_t R_MIPI_DSI_StatusGet (mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_status_t * p_status)
{
#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(MIPI_DSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    p_status->link_status              = (mipi_dsi_link_status_t) R_DSILINK->LINKSR;
    p_status->ack_err_latest.bits      = R_DSILINK->AKEPLATIR;
    p_status->ack_err_accumulated.bits = R_DSILINK->AKEPACMSR;

    /* Clear accumulated error bits after reading */
    R_DSILINK->AKEPSCR = p_status->ack_err_accumulated.bits;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MIPI_DSI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Stop DSI operation. Basic parameter checking to be performed by caller.
 *
 * @param[in]     p_ctrl    Pointer to instance control structure
 *
 * @retval        FSP_SUCCESS               DSI stopped successfully.
 * @retval        FSP_ERR_IN_USE            DSI cannot be stopped in ULPS.
 **********************************************************************************************************************/
static fsp_err_t dsi_stop (mipi_dsi_instance_ctrl_t * p_ctrl)
{
#if MIPI_DSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(!p_ctrl->ulps_status, FSP_ERR_IN_USE);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Check if running first else the stop operation may stall indefinitely */
    if (R_DSILINK->VMSR_b.RUNNING)
    {
        /* Initiate stop video output and wait  */
        R_DSILINK->VMSET0R_b.VSTOP = 1U;

        while ((R_DSILINK->VMSR_b.STOP != 1) && g_video_started)
        {
            /* Wait for video mode stop
             *  - VMSR.STOP must be zero before proceeding to stop GLCDC
             *  NOTE: VMSR may be modified in isr */
        }

        g_video_started = false;

        /* Clear any stale VMSR status */
        R_DSILINK->VMSCR = R_DSILINK->VMSR;
    }

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * Returns configuration values for Sequence Register A
 *
 * @param[in]     p_cmd     Pointer to formatted message structure
 **********************************************************************************************************************/
static uint32_t dsi_cmd_sequence_register_a (mipi_dsi_cmd_t * p_cmd)
{
    /*
     * Long write packets contain the word count in header bytes 1 and 2.
     * The payload follows the header and is word count bytes long.
     *
     * Short write packets encode up to two parameters in header bytes 1
     * and 2.
     */
    uint8_t short_data[2];
    bool    long_packet = DSI_PACKET_FORMAT_IS_LONG(p_cmd->cmd_id);
    if (long_packet)
    {
        short_data[0] = (p_cmd->tx_len >> 0) & 0xFFU; // NOLINT(readability-magic-numbers)
        short_data[1] = (p_cmd->tx_len >> 8) & 0xFFU; // NOLINT(readability-magic-numbers)
    }
    else
    {
        short_data[0] = (p_cmd->tx_len > 0) ? p_cmd->p_tx_buffer[0] : 0U;
        short_data[1] = (p_cmd->tx_len > 1) ? p_cmd->p_tx_buffer[1] : 0U;
    }

    uint8_t bta =
        (p_cmd->flags & (MIPI_DSI_CMD_FLAG_BTA | MIPI_DSI_CMD_FLAG_BTA_READ | MIPI_DSI_CMD_FLAG_BTA_NO_WRITE));

    uint8_t  lp = (0 != (p_cmd->flags & MIPI_DSI_CMD_FLAG_LOW_POWER));
    uint32_t sequence_register_a =
        (((uint32_t) short_data[0] << R_DSILINK_SQCH0DSC0AR_DATA0_Pos) & R_DSILINK_SQCH0DSC0AR_DATA0_Msk) |
        (((uint32_t) short_data[1] << R_DSILINK_SQCH0DSC0AR_DATA1_Pos) & R_DSILINK_SQCH0DSC0AR_DATA1_Msk) |
        (((uint32_t) p_cmd->cmd_id << R_DSILINK_SQCH0DSC0AR_DT_Pos) & R_DSILINK_SQCH0DSC0AR_DT_Msk) |
        (((uint32_t) p_cmd->channel << R_DSILINK_SQCH0DSC0AR_VC_Pos) & R_DSILINK_SQCH0DSC0AR_VC_Msk) |
        (((uint32_t) long_packet << R_DSILINK_SQCH0DSC0AR_FMT_Pos) & R_DSILINK_SQCH0DSC0AR_FMT_Msk) |
        (((uint32_t) lp << R_DSILINK_SQCH0DSC0AR_SPD_Pos) & R_DSILINK_SQCH0DSC0AR_SPD_Msk) |
        (((uint32_t) bta << R_DSILINK_SQCH0DSC0AR_BTA_Pos) & R_DSILINK_SQCH0DSC0AR_BTA_Msk) |
        (((uint32_t) 0 << R_DSILINK_SQCH0DSC0AR_NXACT_Pos) & R_DSILINK_SQCH0DSC0AR_NXACT_Msk);

    return sequence_register_a;
}

/***********************************************************************************************************************
 * Returns configuration values for Sequence Register B
 *
 * @param[in]     p_cmd     Pointer to formatted message structure
 **********************************************************************************************************************/
static uint32_t dsi_cmd_sequence_register_b (mipi_dsi_cmd_t * p_cmd)
{
    FSP_PARAMETER_NOT_USED(p_cmd);

    /* Use sequence RAM */
    return (1 << R_DSILINK_SQCH0DSC0BR_DTSEL_Pos) & R_DSILINK_SQCH0DSC0BR_DTSEL_Msk;
}

/***********************************************************************************************************************
 * Returns configuration values for Sequence Register C
 *
 * @param[in]     p_cmd     Pointer to formatted message structure
 **********************************************************************************************************************/
static uint32_t dsi_cmd_sequence_register_c (mipi_dsi_cmd_t * p_cmd)
{
    bool     aux_operation       = (p_cmd->flags & MIPI_DSI_CMD_FLAG_AUX_OPERATION);
    bool     actcode             = aux_operation ? (p_cmd->flags & 0xF) : 0; // Always store Rx result in slot 0
    uint32_t sequence_register_c =
        (((uint32_t) 0 << R_DSILINK_SQCH0DSC0CR_FINACT_Pos) & R_DSILINK_SQCH0DSC0CR_FINACT_Msk) |
        (((uint32_t) aux_operation << R_DSILINK_SQCH0DSC0CR_AUXOP_Pos) & R_DSILINK_SQCH0DSC0CR_AUXOP_Msk) |
        (((uint32_t) actcode << R_DSILINK_SQCH0DSC0CR_ACTCODE_Pos) & R_DSILINK_SQCH0DSC0CR_ACTCODE_Msk);

    return sequence_register_c;
}

/***********************************************************************************************************************
 * Returns configuration values for Sequence Register D
 *
 * @param[in]     p_cmd     Pointer to formatted message structure
 **********************************************************************************************************************/
uint32_t dsi_cmd_sequence_register_d (mipi_dsi_cmd_t * p_cmd)
{
    uint8_t bta =
        (p_cmd->flags & (MIPI_DSI_CMD_FLAG_BTA | MIPI_DSI_CMD_FLAG_BTA_READ | MIPI_DSI_CMD_FLAG_BTA_NO_WRITE));

    return (uint32_t) (bta ? p_cmd->p_rx_buffer : p_cmd->p_tx_buffer); // This buffer address is used for both Tx and Rx.
}

/*******************************************************************************************************************//**
 * Calls user callback
 *
 * @param[in]     p_ctrl     Pointer to MIPI DSI instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void dsi_call_callback (mipi_dsi_instance_ctrl_t * p_ctrl, mipi_dsi_callback_args_t * p_args)
{
    mipi_dsi_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    mipi_dsi_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
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
        mipi_dsi_prv_ns_callback p_callback = (mipi_dsi_prv_ns_callback) (p_ctrl->p_callback);
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
 * Private helper functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enter Reset
 * Perform sequence steps 1 to 3 from section 58.3.2 in RA8D1 hardware manual R01UH0995EJ0060.
 **********************************************************************************************************************/
static void dsi_enter_reset ()
{
    /* Enable clock lane */
    R_DSILINK->TXSETR_b.CLEN = 1U;

    /* Enter the DSI Host software reset state */
    R_DSILINK->RSTCR_b.SWRST = 1;

    /* Wait for reset process to start - Polling RSTSR is okay since it's not updated in interrupt.*/
    FSP_HARDWARE_REGISTER_WAIT((R_DSILINK->RSTSR & MIPI_DSI_RSRST_RESET_BITS), MIPI_DSI_RSRST_RESET_BITS);
}

/*******************************************************************************************************************//**
 * Initialize timing registers from configuration data
 * - Perform sequence step 4 from section 58.3.2 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @param[in]     p_cfg     Pointer to MIPI DSI configuration structure
 **********************************************************************************************************************/
static void dsi_init_timing (mipi_dsi_cfg_t const * const p_cfg)
{
    /* Enable clock and data lanes and set number of lanes to use */
    R_DSILINK->TXSETR = R_DSILINK_TXSETR_DLEN_Msk | R_DSILINK_TXSETR_CLEN_Msk | (p_cfg->num_lanes - 1);

    /* Set ULPS wakeup period */
    R_DSILINK->ULPSSETR_b.WKUP = p_cfg->ulps_wakeup_period;

    /* Set data scrambling and/or EoTp transmission */
#define DSILINK_DSISETR_VCCRCEN_Msk    (R_DSILINK_DSISETR_VC0CRCEN_Msk | \
                                        R_DSILINK_DSISETR_VC1CRCEN_Msk | \
                                        R_DSILINK_DSISETR_VC2CRCEN_Msk | \
                                        R_DSILINK_DSISETR_VC3CRCEN_Msk)
    R_DSILINK->DSISETR =
        ((p_cfg->max_return_packet_size << R_DSILINK_DSISETR_MRPSZ_Pos) & R_DSILINK_DSISETR_MRPSZ_Msk) |
        (((uint32_t) p_cfg->ecc_enable << R_DSILINK_DSISETR_ECCEN_Pos) & R_DSILINK_DSISETR_ECCEN_Msk) |
        (((uint32_t) p_cfg->crc_check_mask << R_DSILINK_DSISETR_VC0CRCEN_Pos) & DSILINK_DSISETR_VCCRCEN_Msk) |
        (((uint32_t) p_cfg->scramble_enable << R_DSILINK_DSISETR_SCREN_Pos) & R_DSILINK_DSISETR_SCREN_Msk) |
        (((uint32_t) p_cfg->tearing_detect << R_DSILINK_DSISETR_EXTEMD_Pos) & R_DSILINK_DSISETR_EXTEMD_Msk) |
        (((uint32_t) p_cfg->eotp_enable << R_DSILINK_DSISETR_EOTPEN_Pos) & R_DSILINK_DSISETR_EOTPEN_Msk);

    /* Set LP lane transition timing */
    R_DSILINK->CLSTPTSETR =
        ((p_cfg->p_timing->clock_stop_time << R_DSILINK_CLSTPTSETR_CLKSTPT_Pos) &
         R_DSILINK_CLSTPTSETR_CLKSTPT_Msk) |
        ((p_cfg->p_timing->clock_beforehand_time << R_DSILINK_CLSTPTSETR_CLKBFHT_Pos) &
         R_DSILINK_CLSTPTSETR_CLKBFHT_Msk) |
        ((p_cfg->p_timing->clock_keep_time << R_DSILINK_CLSTPTSETR_CLKKPT_Pos) &
         R_DSILINK_CLSTPTSETR_CLKKPT_Msk);
    R_DSILINK->LPTRNSTSETR = p_cfg->p_timing->go_lp_and_back & R_DSILINK_LPTRNSTSETR_GOLPBKT_Msk;

    /* Set timeout values */
    R_DSILINK->PRESPTOBTASETR = p_cfg->bta_timeout;
    R_DSILINK->PRESPTOLPSETR  = p_cfg->lprw_timeout;
    R_DSILINK->PRESPTOHSSETR  = p_cfg->hsrw_timeout;
    R_DSILINK->HSTXTOSETR     = p_cfg->hs_tx_timeout;
    R_DSILINK->LRXHTOSETR     = p_cfg->lp_rx_timeout;
    R_DSILINK->TATOSETR       = p_cfg->turnaround_timeout;
}

/*******************************************************************************************************************//**
 * Exit Reset
 * Perform sequence steps 5 to 9 from section 58.3.2 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * NOTE: Calling this function is prohibited without first calling dsi_enter_reset(), which sets RSTCR.SWRST to 1
 *
 * @param[in]     p_cfg     Pointer to MIPI DSI configuration structure
 **********************************************************************************************************************/
static void dsi_exit_reset (mipi_dsi_cfg_t const * const p_cfg)
{
    /* Transition data lanes to stop state */
    R_DSILINK->RSTCR_b.FTXSTP = 1U;

    /* Wait for data lanes transition to stop state */
    FSP_HARDWARE_REGISTER_WAIT((R_DSILINK->RSTSR &
                                (R_DSILINK_RSTSR_DL0DIR_Msk | R_DSILINK_RSTSR_DL0STP_Msk | R_DSILINK_RSTSR_DL1STP_Msk)),
                               (((p_cfg->num_lanes * 2U) - 1U) << R_DSILINK_RSTSR_DL0STP_Pos));

    /* Clear the Force Tx Stop and Software Reset bits */
    R_DSILINK->RSTCR_b.FTXSTP = 0U;
    R_DSILINK->RSTCR_b.SWRST  = 0U;

    /* Wait for software reset to complete */
    FSP_HARDWARE_REGISTER_WAIT((R_DSILINK->RSTSR & MIPI_DSI_RSRST_RESET_BITS), 0);
}

/*******************************************************************************************************************//**
 * Initialize High Speed Clock
 * Perform sequence steps from section 58.3.3 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @param[in]     p_ctrl     Pointer to MIPI DSI instance control block
 **********************************************************************************************************************/
static void dsi_hs_clock_start (mipi_dsi_instance_ctrl_t * p_ctrl)
{
    mipi_dsi_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Enable clock lane */
    R_DSILINK->TXSETR_b.CLEN = 1U;
    g_clock_state            = MIPI_DSI_CLOCK_STATE_STARTING;

    /* Enable HS clock and set running mode */
    R_DSILINK->HSCLKSETR = R_DSILINK_HSCLKSETR_HSCLST_Msk |
                           (p_cfg->continuous_clock ? R_DSILINK_HSCLKSETR_HSCLMD_Msk : 0U);

    while ((R_DSILINK->PLSR_b.CLLP2HS != p_cfg->continuous_clock) &&
           (g_clock_state != MIPI_DSI_CLOCK_STATE_STARTED))
    {
        /* Wait for HS clock notification bit set to 1. (only in the continuous clock mode)
         * NOTE: PLSR may be modified in ISR */
    }

    g_clock_state = MIPI_DSI_CLOCK_STATE_STARTED;
}

/***********************************************************************************************************************
 * De-initialize High Speed Clock
 * Perform sequence steps from section 56.3.4 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @param[in]     p_ctrl     Pointer to MIPI DSI instance control block
 **********************************************************************************************************************/
static void dsi_hs_clock_stop (mipi_dsi_instance_ctrl_t * p_ctrl)
{
    mipi_dsi_cfg_t const * p_cfg = p_ctrl->p_cfg;

    R_DSILINK->HSCLKSETR_b.HSCLST = 0;
    g_clock_state                 = MIPI_DSI_CLOCK_STATE_STOPPING;

    while ((R_DSILINK->PLSR_b.CLHS2LP != p_cfg->continuous_clock) && (g_clock_state != MIPI_DSI_CLOCK_STATE_IDLE))
    {
        /* Wait for clock lane transition LP state.
         * NOTE: PLSR may be modified in ISR */
    }

    g_clock_state = MIPI_DSI_CLOCK_STATE_IDLE;
}

/***********************************************************************************************************************
 * Initialize Video Output Registers
 * Perform sequence steps 1 and 2 from section 58.3.6.1 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @param[in]     p_cfg     Pointer to MIPI DSI configuration structure
 **********************************************************************************************************************/
static void dsi_init_video (mipi_dsi_cfg_t const * p_cfg)
{
    R_DSILINK->VMPPSETR =
        (((uint32_t) p_cfg->sync_pulse << R_DSILINK_VMPPSETR_TXESYNC_Pos) & R_DSILINK_VMPPSETR_TXESYNC_Msk) |
        (((uint32_t) p_cfg->data_type << R_DSILINK_VMPPSETR_DT_Pos) & R_DSILINK_VMPPSETR_DT_Msk) |
        (((uint32_t) p_cfg->virtual_channel_id << R_DSILINK_VMPPSETR_VC_Pos) &
         R_DSILINK_VMPPSETR_VC_Msk);
    R_DSILINK->VMVSSETR =
        ((p_cfg->vertical_sync_lines << R_DSILINK_VMVSSETR_VSA_Pos) & R_DSILINK_VMVSSETR_VSA_Msk) |
        (((uint32_t) p_cfg->vertical_sync_polarity << R_DSILINK_VMVSSETR_VSPOL_Pos) &
         R_DSILINK_VMVSSETR_VSPOL_Msk) |
        ((p_cfg->vertical_active_lines << R_DSILINK_VMVSSETR_VACT_Pos) &
         R_DSILINK_VMVSSETR_VACT_Msk);
    R_DSILINK->VMVPSETR =
        ((p_cfg->vertical_back_porch << R_DSILINK_VMVPSETR_VBP_Pos) & R_DSILINK_VMVPSETR_VBP_Msk) |
        ((p_cfg->vertical_front_porch << R_DSILINK_VMVPSETR_VFP_Pos) &
         R_DSILINK_VMVPSETR_VFP_Msk);
    R_DSILINK->VMHSSETR =
        ((p_cfg->horizontal_sync_lines << R_DSILINK_VMHSSETR_HSA_Pos) & R_DSILINK_VMHSSETR_HSA_Msk) |
        (((uint32_t) p_cfg->horizontal_sync_polarity << R_DSILINK_VMHSSETR_HSPOL_Pos) &
         R_DSILINK_VMHSSETR_HSPOL_Msk) |
        ((p_cfg->horizontal_active_lines << R_DSILINK_VMHSSETR_HACT_Pos) &
         R_DSILINK_VMHSSETR_HACT_Msk);
    R_DSILINK->VMHPSETR =
        ((p_cfg->horizontal_back_porch << R_DSILINK_VMHPSETR_HBP_Pos) & R_DSILINK_VMHPSETR_HBP_Msk) |
        ((p_cfg->horizontal_front_porch << R_DSILINK_VMHPSETR_HFP_Pos) &
         R_DSILINK_VMHPSETR_HFP_Msk);
    R_DSILINK->VMSET1R =
        ((p_cfg->video_mode_delay << R_DSILINK_VMSET1R_DLY_Pos) & R_DSILINK_VMSET1R_DLY_Msk);
}

/***********************************************************************************************************************
 * Enable the specified ISR and add the control structure to the ISR context lookup table.
 *
 * @param[in]     irq_cfg    Pointer to interrupt configuration structure
 * @param[in]     p_ctrl     Pointer to MIPI DSI instance control block
 **********************************************************************************************************************/
static void dsi_isr_enable (mipi_dsi_irq_cfg_t const * irq_cfg, mipi_dsi_instance_ctrl_t * p_ctrl)
{
    R_BSP_IrqCfgEnable(irq_cfg->irq, irq_cfg->ipl, p_ctrl);
}

/***********************************************************************************************************************
 * Disable the specified ISR
 *
 * @param[in]     irq_cfg    Pointer to interrupt configuration structure
 **********************************************************************************************************************/
static void dsi_isr_disable (mipi_dsi_irq_cfg_t const * irq_cfg)
{
    R_BSP_IrqDisable(irq_cfg->irq);
    R_FSP_IsrContextSet(irq_cfg->irq, NULL);
}

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Sequence 0 ISR
 *  - Process LP sequence command events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_seq0 (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear sequence channel 0 status register bits */
    uint32_t sqch0sr_bits = R_DSILINK->SQCH0SR;
    R_DSILINK->SQCH0SCR = sqch0sr_bits; // SIZEERR is reserved for SQCH0SCR and should be read and written as zero

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    mipi_dsi_callback_args_t   args;
    args.event     = MIPI_DSI_EVENT_SEQUENCE_0;
    args.tx_status = (mipi_dsi_sequence_status_t) sqch0sr_bits;
    args.p_context = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/***********************************************************************************************************************
 * Sequence 1 ISR
 *  - Process HS sequence command events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_seq1 (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear sequence channel 1 status register bits */
    uint32_t sqch1sr_bits = R_DSILINK->SQCH1SR;
    R_DSILINK->SQCH1SCR = sqch1sr_bits;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    mipi_dsi_callback_args_t   args;
    args.event     = MIPI_DSI_EVENT_SEQUENCE_1;
    args.tx_status = (mipi_dsi_sequence_status_t) sqch1sr_bits;
    args.p_context = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/***********************************************************************************************************************
 * Video Input ISR
 *  - Process DSI Video Input Events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_vin1 (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear video mode status register bits */
    uint32_t vmsr_bits = R_DSILINK->VMSR;
    R_DSILINK->VMSCR = vmsr_bits;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    /* Update internal state */
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    if (vmsr_bits & R_DSILINK_VMSR_VIRDY_Msk)
    {
        g_video_started = true;
    }
    else if (vmsr_bits & R_DSILINK_VMSR_STOP_Msk)
    {
        g_video_started = false;
    }
    else
    {
        // Nothing
    }

    /* Pass data to user */
    mipi_dsi_callback_args_t args;
    args.event        = MIPI_DSI_EVENT_VIDEO;
    args.video_status = (mipi_dsi_video_status_t) vmsr_bits;
    args.p_context    = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    /* Perform reset according to RA8D1 UM 58.3.8.6 (R01UH0995EJ0060) */
    if (vmsr_bits & (R_DSILINK_VMSR_VBUFUDF_Msk | R_DSILINK_VMSR_VBUFOVF_Msk))
    {
        dsi_enter_reset();
        dsi_exit_reset(p_ctrl->p_cfg);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/***********************************************************************************************************************
 * Receive ISR
 *  - Process Receive Events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_rcv (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear recieve status register bits */
    uint32_t rxsr_bits = R_DSILINK->RXSR;
    R_DSILINK->RXSCR = rxsr_bits;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    mipi_dsi_callback_args_t   args;
    args.event     = MIPI_DSI_EVENT_RECEIVE;
    args.rx_status = (mipi_dsi_receive_status_t) rxsr_bits;
    args.p_result  = (mipi_dsi_receive_result_t *) &R_DSILINK->RXRSS0R;
    args.p_context = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    R_DSILINK->RXRINFOOWSCR = R_DSILINK_RXRINFOOWSCR_SL0OW_Msk; // Clear slot 0 after reading

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/***********************************************************************************************************************
 * Fatal Error ISR
 *  - Process Fatal Error Events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_ferr (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear recieve status register bits */
    uint32_t ferrsr_bits = R_DSILINK->FERRSR;
    R_DSILINK->FERRSCR = ferrsr_bits;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    mipi_dsi_callback_args_t   args;
    args.event        = MIPI_DSI_EVENT_FATAL;
    args.fatal_status = (mipi_dsi_fatal_status_t) ferrsr_bits;
    args.p_context    = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/***********************************************************************************************************************
 * PHY-Protocol Interface ISR
 *  - Process Phy-Protocol Events and forward them to the user callback
 **********************************************************************************************************************/
void mipi_dsi_ppi (void) {
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    /* Clear PLSR */
    uint32_t plsr_bits = R_DSILINK->PLSR;
    R_DSILINK->PLSCR = plsr_bits;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    /* Update internal state */
    mipi_dsi_instance_ctrl_t * p_ctrl = (mipi_dsi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    if ((g_clock_state == MIPI_DSI_CLOCK_STATE_STARTING) &&
        (plsr_bits & R_DSILINK_PLSR_CLLP2HS_Msk))
    {
        g_clock_state = MIPI_DSI_CLOCK_STATE_STARTED;
    }
    else if ((g_clock_state == MIPI_DSI_CLOCK_STATE_STOPPING) &&
             (plsr_bits & R_DSILINK_PLSR_CLHS2LP_Msk))
    {
        g_clock_state = MIPI_DSI_CLOCK_STATE_IDLE;
    }
    else
    {
        // Nothing
    }

    /* Pass data to user */
    mipi_dsi_callback_args_t args;
    args.event      = MIPI_DSI_EVENT_PHY;
    args.phy_status = (mipi_dsi_phy_status_t) plsr_bits;
    args.p_context  = p_ctrl->p_context;
    dsi_call_callback(p_ctrl, &args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
