/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_nfc_reader_ptx.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define NFC_READER_PTX_ZERO                       (0)
#define NFC_READER_PTX_SHUTDOWN_TEMP              (223U)

#define RM_NFC_READER_NATIVE_TAG_OFFSET           (0x100)
#define RM_NFC_READER_NATIVE_TAG_EXTENDED_SIZE    (0xFF)

/* ASCII conversion from string of "NFC" */
#define NFC_READER_PTX_OPEN                       (0x4e4643ULL)
#define NFC_READER_PTX_CLOSED                     (0)

/* Default timeout-values for for RAW-protocols (e.g. T2T, T3T, ...) and standard-protocols (ISO-/NFC-DEP) */
#define NFC_READER_PTX_TIMEOUT_RAW                (200U)   // Application-timeout for raw-protocols
#define NFC_READER_PTX_TIMEOUT_PROTOCOL           (50000U) // Application-timeout for standard-protocols

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/

/* Only perform calibration once per power cycle */
static bool g_start_temperature_sensor_calibration = true;

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_NFC_READER_PTX
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Initializes the NFC IoT Reader.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_cfg                Pointer to NFC IoT Reader configuration structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already opened.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Open (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                  nfc_reader_ptx_cfg_t const * const     p_cfg)
{
    /* Do parameter checking */
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;

    /* Define IoT Reader parameters */
    ptxIoTRd_InitPars_t            nfc_reader_init_params;
    ptxIoTRd_TempSense_Params_t    nfc_reader_temp_sensor;
    ptxIoTRd_ComInterface_Params_t nfc_reader_interface;

    /* Set all initial values to 0 */
    memset(&nfc_reader_init_params, NFC_READER_PTX_ZERO, sizeof(ptxIoTRd_InitPars_t));
    memset(&nfc_reader_temp_sensor, NFC_READER_PTX_ZERO, sizeof(ptxIoTRd_TempSense_Params_t));
    memset(&nfc_reader_interface, NFC_READER_PTX_ZERO, sizeof(ptxIoTRd_ComInterface_Params_t));

    /* Check if temperature calibration was performed yet */
    if (true == g_start_temperature_sensor_calibration)
    {
        /* Calibration required. Set ambient temperature and expected shutdown temperature threshold. */
        nfc_reader_temp_sensor.Calibrate = p_cfg->temp_sensor_calibrate;
        nfc_reader_temp_sensor.Tambient  = p_cfg->temp_sensor_ambient;
        nfc_reader_temp_sensor.Tshutdown = p_cfg->temp_sensor_shutdown;

        /* Calibration will take place now. Doesn't need to be done anymore if Open is successful. */
        g_start_temperature_sensor_calibration = false;
    }
    else
    {
        /* Calibration not needed, it has already been done. Provide compensated threshold temperature word. */
        nfc_reader_temp_sensor.Tshutdown = NFC_READER_PTX_SHUTDOWN_TEMP;
    }

    /* Initial parameters for temperature sensor are ready. */
    nfc_reader_init_params.TemperatureSensor = &nfc_reader_temp_sensor;
    nfc_reader_init_params.ComInterface      = &nfc_reader_interface;

    /* Initialize low-level peripherals */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxPLAT_GPIO_Open(p_cfg->p_gpio_context, p_cfg->p_irq_context, p_cfg->interrupt_pin),
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(ptxStatus_Success == ptxPLAT_TIMER_Open(p_cfg->p_timer_context), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(ptxStatus_Success == ptxPERIPH_APPTIMER_Open(p_cfg->p_app_timer), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxPLAT_SPI_Open(p_cfg->p_comms_instance_ctrl, p_cfg->p_gpio_context),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Initiate IoT-Reader System. */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Init(p_cfg->iot_reader_context, &nfc_reader_init_params),
                     FSP_ERR_INVALID_DATA);

    p_ctrl->open       = NFC_READER_PTX_OPEN;
    p_ctrl->state_flag = NFC_READER_PTX_IDLE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Initiates discovery of NFC tags.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the idle state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_DiscoveryStart (nfc_reader_ptx_instance_ctrl_t * const p_ctrl)
{
    /* Do parameter checking */
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check device is idle before initiating discovery */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_IDLE, FSP_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* RF-Discover configuration */
    ptxIoTRd_DiscConfig_t nfc_reader_disc_config;
    memset(&nfc_reader_disc_config, NFC_READER_PTX_ZERO, sizeof(ptxIoTRd_DiscConfig_t));

    nfc_reader_disc_config.PollTypeA            = p_cfg->poll_type_a;
    nfc_reader_disc_config.PollTypeB            = p_cfg->poll_type_b;
    nfc_reader_disc_config.PollTypeF212         = p_cfg->poll_type_f;
    nfc_reader_disc_config.PollTypeV            = p_cfg->poll_type_v;
    nfc_reader_disc_config.IdleTime             = p_cfg->idle_time_ms;
    nfc_reader_disc_config.PollTypeADeviceLimit = p_cfg->device_limit;
    nfc_reader_disc_config.PollTypeBDeviceLimit = p_cfg->device_limit;
    nfc_reader_disc_config.PollTypeVDeviceLimit = p_cfg->device_limit;
    nfc_reader_disc_config.PollTypeFDeviceLimit = p_cfg->device_limit;
    nfc_reader_disc_config.Discover_Mode        = p_cfg->discover_mode;

    /* Check that at least one poll type option was selected (e.g. Type-A) */
    FSP_ERROR_RETURN(
        nfc_reader_disc_config.PollTypeA || nfc_reader_disc_config.PollTypeB || nfc_reader_disc_config.PollTypeF212 || nfc_reader_disc_config.PollTypeV,
        FSP_ERR_INVALID_DATA);

    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Initiate_Discovery(p_cfg->iot_reader_context, &nfc_reader_disc_config),
                     FSP_ERR_INVALID_DATA);

    p_ctrl->state_flag = NFC_READER_PTX_POLLING;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the status information on the provided status identifier (system, discovery, etc.).
 *  Used during polling to confirm a card was discovered.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  status_type          Status identifier for target info.
 * @param[in]  p_status             Pointer to location to store NFC chip status flag.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the polling state.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_StatusGet (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                       ptxIoTRd_StatusType_t                  status_type,
                                       uint8_t * const                        p_status)
{
    /* Do parameter checking */
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    if (StatusType_Discover == status_type)
    {
        /* Check device is polling before checking for discovery */
        FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_POLLING, FSP_ERR_INVALID_STATE);
    }
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Get_Status_Info(p_cfg->iot_reader_context, status_type, p_status),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Confirm results if discovery status is being checked */
    if (StatusType_Discover == status_type)
    {
        switch (*p_status)
        {
            case RF_DISCOVER_STATUS_NO_CARD:
            {
                /* If there is no card, do nothing */
                break;
            }

            case RF_DISCOVER_STATUS_CARD_ACTIVE:
            {
                /* If a single card was discovered, set state to Activated */
                p_ctrl->state_flag = NFC_READER_PTX_ACTIVATED;
                break;
            }

            case RF_DISCOVER_STATUS_DISCOVER_RUNNING:
            {
                /* Wait for discovery to finish */
                break;
            }

            case RF_DISCOVER_STATUS_DISCOVER_DONE:
            {
                /* If multiple cards were detected, set to Discovered */
                p_ctrl->state_flag = NFC_READER_PTX_DISCOVERED;
                break;
            }

            default:
            {
                return FSP_ERR_INVALID_STATE;
                break;
            }
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the internal card registry.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  pp_card_registry     Pointer to card registry for discovered cards.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_CardRegistryGet (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                             ptxIoTRd_CardRegistry_t             ** pp_card_registry)
{
    /* Do parameter checking */
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != pp_card_registry);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Get reference to the internal card registry */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Get_Card_Registry(p_cfg->iot_reader_context, pp_card_registry),
                     FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the details of the discovered card and connects to it.
 *  Not required if only a single tag was discovered.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_card_params        Parameters of the card to be activated.
 * @param[in]  protocol             The NFC protocol of the card to be activated.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the discovered/selection state.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_CardActivate (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                          ptxIoTRd_CardParams_t * const          p_card_params,
                                          ptxIoTRd_CardProtocol_t                protocol)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_card_params);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check device is polling before checking for discovery */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_DISCOVERED, FSP_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Activate the card that was discovered */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Activate_Card(p_cfg->iot_reader_context, p_card_params, protocol),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Update state flag to Activated if successful */
    p_ctrl->state_flag = NFC_READER_PTX_ACTIVATED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Sends and receives data to/from the activated card.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_DataExchange (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                          nfc_reader_ptx_data_info_t * const     p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Exchange data with the activated tag */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Data_Exchange(p_cfg->iot_reader_context, p_data_info->p_tx_buf, p_data_info->tx_length,
                                            p_data_info->p_rx_buf, &p_data_info->rx_length, NFC_READER_PTX_TIMEOUT_RAW),
                     FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Deactivates the activated card to return to the desired state (idle, discovery, etc.).
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  return_state         Expectation for end state of NFC state machine.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_ReaderDeactivation (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                                nfc_reader_ptx_return_state_t          return_state)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check device is active before deactivation */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Deactivate the activated card */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Reader_Deactivation(p_cfg->iot_reader_context, (uint8_t) return_state),
                     FSP_ERR_INVALID_DATA);

    /* Change the state depending on expected return state */
    switch (return_state)
    {
        case NFC_READER_PTX_RETURN_IDLE:
        {
            /* Set the state flag to idle */
            p_ctrl->state_flag = NFC_READER_PTX_IDLE;
            break;
        }

        case NFC_READER_PTX_RETURN_DISCOVER:
        {
            /* Set the state flag to discover */
            p_ctrl->state_flag = NFC_READER_PTX_POLLING;
            break;
        }

        case NFC_READER_PTX_RETURN_SLEEP:
        {
            /* Handled internally by IoT Reader */
            break;
        }

        case NFC_READER_PTX_RETURN_NO_RF_RESET:
        {
            /* Handled internally by IoT Reader */
            break;
        }

        default:
        {
            return FSP_ERR_INVALID_STATE;
            break;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Puts the device into either Active (all features) or Stand-by mode (most features off), to cut down energy consumption.
 * RF communication is not possible from Stand-by mode, and Wake-up is possible only via communication interface.
 * This function is only available exclusively before starting discovery.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  power_mode           Flag to indicate if setting to Active or Stand-by mode.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the idle/polling state.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_PowerModeSet (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                          nfc_reader_ptx_power_mode_t            power_mode)
{
    /* Do parameter checking */
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check device is idle before changing the power mode */
    FSP_ERROR_RETURN((p_ctrl->state_flag == NFC_READER_PTX_IDLE), FSP_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Set the device to Active or Stand-by power mode */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Set_Power_Mode(p_cfg->iot_reader_context, (uint8_t) power_mode),
                     FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Initializes the optional NDEF API add-on. Must be done after NFC stack is initialized.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_ALREADY_OPEN     NDEF API add-on was already initialized.
 * @retval FSP_ERR_UNSUPPORTED      NDEF API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_NDEF_Init (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                       nfc_reader_ptx_data_info_t * const     p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN != p_ctrl->ndef_open, FSP_ERR_ALREADY_OPEN);
#endif

#if (!RM_NFC_READER_NDEF_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Generic NDEF-OP Component (Tag-independent) */
    ptxNDEF_InitParams_t nfc_reader_ndef_init_params;

    /* initialize generic NDEF-OP component */
    memset(&nfc_reader_ndef_init_params, NFC_READER_PTX_ZERO, sizeof(ptxNDEF_InitParams_t));

    nfc_reader_ndef_init_params.IotRd          = p_cfg->iot_reader_context;
    nfc_reader_ndef_init_params.TxBuffer       = &p_data_info->p_tx_buf[0];
    nfc_reader_ndef_init_params.TxBufferSize   = p_data_info->tx_length;
    nfc_reader_ndef_init_params.RxBuffer       = &p_data_info->p_rx_buf[0];
    nfc_reader_ndef_init_params.RxBufferSize   = p_data_info->rx_length;
    nfc_reader_ndef_init_params.WorkBuffer     = (uint8_t *) p_ctrl->ndef_work_buf;
    nfc_reader_ndef_init_params.WorkBufferSize = NFC_READER_PTX_NDEF_WORK_BUF_SIZE;

    /* Initialize NDEF API */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_Open(p_cfg->p_ndef_context, &nfc_reader_ndef_init_params),
                     FSP_ERR_INVALID_DATA);

    p_ctrl->ndef_open = NFC_READER_PTX_OPEN;

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Exchanges NDEF data with an NFC tag by reading from or writing to it.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_ndef_message       Pointer to the buffer to transmit or receive a message.
 * @param[in]  message_length       Length of the NDEF message buffer.
 * @param[in]  ndef_read_write_flag Flag to control if the data exchange is a read or a write.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_NOT_INITIALIZED  NDEF add-on is not initialized yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_UNSUPPORTED      NDEF API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_NDEF_DataExchange (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                               uint8_t                              * p_ndef_message,
                                               uint32_t                               message_length,
                                               nfc_reader_ptx_ndef_read_write_t       ndef_read_write_flag)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_ndef_message);
    FSP_ASSERT(0 != message_length);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->ndef_open, FSP_ERR_NOT_INITIALIZED);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NDEF_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_ndef_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(ndef_read_write_flag);

    return FSP_ERR_UNSUPPORTED;
#else
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Check is required before all NDEF operations */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_CheckMessage(p_cfg->p_ndef_context), FSP_ERR_INVALID_DATA);

    /* Check if the NDEF exchange is read or write */
    if (NFC_READER_PTX_NDEF_READ == ndef_read_write_flag)
    {
        FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_ReadMessage(p_cfg->p_ndef_context, p_ndef_message,
                                                                  &message_length),
                         FSP_ERR_INVALID_DATA);
    }
    else
    {
        FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_WriteMessage(p_cfg->p_ndef_context, p_ndef_message,
                                                                   message_length),
                         FSP_ERR_INVALID_DATA);
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Locks an NFC tag to prevent writing to it, making it read-only.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_NOT_INITIALIZED  NDEF add-on is not initialized yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_UNSUPPORTED      NDEF API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_NDEF_Lock (nfc_reader_ptx_instance_ctrl_t * const p_ctrl)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->ndef_open, FSP_ERR_NOT_INITIALIZED);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NDEF_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#else
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Check is required before all NDEF operations */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_CheckMessage(p_cfg->p_ndef_context), FSP_ERR_INVALID_DATA);

    /* Lock the tag if it is supported */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_LockTag(p_cfg->p_ndef_context), FSP_ERR_INVALID_DATA);

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Initializes the optional Native-Tag API add-on. Must be done after NFC stack is initialized.
 *  For each tag type to be initialized, the tag type bit values must be set in the tag select parameter.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 * @param[in]  tag_select           User-provided bitmask of tags to be initialized.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_ALREADY_OPEN     Native-Tag API add-on was already initialized.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Init (nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                             nfc_reader_ptx_data_info_t * const     p_data_info,
                                             uint8_t                                tag_select)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_select);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN != p_ctrl->native_tag_open, FSP_ERR_ALREADY_OPEN);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_data_info);
    FSP_PARAMETER_NOT_USED(tag_select);

    return FSP_ERR_UNSUPPORTED;
#else
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Use this variable to track which tags were initialized */
    p_ctrl->enabled_tag_mask = NFC_READER_PTX_NATIVE_TAG_TYPE_NONE;

    /* For each tag type, initialize if the tag select was set */
    if (tag_select & NFC_READER_PTX_NATIVE_TAG_TYPE_T2T)
    {
        /* Assign the IoT Reader context and TX buffer, which is common to all tag types */
        p_ctrl->t2t_params.IotRd        = p_cfg->iot_reader_context;
        p_ctrl->t2t_params.TxBuffer     = p_data_info->p_tx_buf;
        p_ctrl->t2t_params.TxBufferSize = p_data_info->tx_length;

        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T2TOpen(&p_ctrl->t2t_comp, &p_ctrl->t2t_params),
                         FSP_ERR_INVALID_ARGUMENT);

        /* Update the tag mask to signal that T2T was initialized */
        p_ctrl->enabled_tag_mask |= NFC_READER_PTX_NATIVE_TAG_TYPE_T2T;
    }

    if (tag_select & NFC_READER_PTX_NATIVE_TAG_TYPE_T3T)
    {
        /* Assign the IoT Reader context and TX buffer, which is common to all tag types */
        p_ctrl->t3t_params.IotRd        = p_cfg->iot_reader_context;
        p_ctrl->t3t_params.TxBuffer     = p_data_info->p_tx_buf;
        p_ctrl->t3t_params.TxBufferSize = p_data_info->tx_length;

        /* T3T parameters includes NFCID2, but this can be set later if no card is active  */

        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T3TOpen(&p_ctrl->t3t_comp, &p_ctrl->t3t_params),
                         FSP_ERR_INVALID_ARGUMENT);

        /* Update the tag mask to signal that T3T was initialized */
        p_ctrl->enabled_tag_mask |= NFC_READER_PTX_NATIVE_TAG_TYPE_T3T;
    }

    if (tag_select & NFC_READER_PTX_NATIVE_TAG_TYPE_T4T)
    {
        /* Assign the IoT Reader context and TX buffer, which is common to all tag types */
        p_ctrl->t4t_params.IotRd        = p_cfg->iot_reader_context;
        p_ctrl->t4t_params.TxBuffer     = p_data_info->p_tx_buf;
        p_ctrl->t4t_params.TxBufferSize = p_data_info->tx_length;

        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T4TOpen(&p_ctrl->t4t_comp, &p_ctrl->t4t_params),
                         FSP_ERR_INVALID_ARGUMENT);

        /* Update the tag mask to signal that T4T was initialized */
        p_ctrl->enabled_tag_mask |= NFC_READER_PTX_NATIVE_TAG_TYPE_T4T;
    }

    if (tag_select & NFC_READER_PTX_NATIVE_TAG_TYPE_T5T)
    {
        /* Assign the IoT Reader context and TX buffer, which is common to all tag types */
        p_ctrl->t5t_params.IotRd        = p_cfg->iot_reader_context;
        p_ctrl->t5t_params.TxBuffer     = p_data_info->p_tx_buf;
        p_ctrl->t5t_params.TxBufferSize = p_data_info->tx_length;
        p_ctrl->t5t_params.UID          = NULL;
        p_ctrl->t5t_params.UIDLen       = 0;

        /* T5T parameters includes UID, but this can be set later if no card is active  */

        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T5TOpen(&p_ctrl->t5t_comp, &p_ctrl->t5t_params),
                         FSP_ERR_INVALID_ARGUMENT);

        /* Update the tag mask to signal that T5T was initialized */
        p_ctrl->enabled_tag_mask |= NFC_READER_PTX_NATIVE_TAG_TYPE_T5T;
    }

    /* Return an error if no tags were initialized */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != 0U, FSP_ERR_INVALID_MODE);

    p_ctrl->native_tag_open = NFC_READER_PTX_OPEN;

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Performs a read operation using the Native-Tag API add-on.
 *  Optional configurations must be set for the required tag type based on the command to be used.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_read_params        Pointer to optional parameter structure for read operation.
 * @param[in]  tag_type             The target tag type for the operation.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_INVALID_MODE     One of the available tag types was not selected.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Read (nfc_reader_ptx_instance_ctrl_t * const          p_ctrl,
                                             nfc_reader_ptx_native_tag_read_params_t * const p_read_params,
                                             nfc_reader_ptx_native_tag_type_t                tag_type,
                                             nfc_reader_ptx_data_info_t * const              p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_read_params);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_type);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->native_tag_open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_read_params);
    FSP_PARAMETER_NOT_USED(tag_type);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else

    /* Check that at least one tag type was enabled */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != NFC_READER_PTX_NATIVE_TAG_TYPE_NONE, FSP_ERR_INVALID_MODE);

    switch (tag_type)
    {
        case NFC_READER_PTX_NATIVE_TAG_TYPE_T2T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T2TRead(&p_ctrl->t2t_comp, p_read_params->t2t_block_number,
                                                  p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                                  NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T3T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T3TCheck(&p_ctrl->t3t_comp, p_read_params->t3t_nfcid2,
                                                   p_read_params->t3t_nfcid2_len, p_read_params->t3t_service_info,
                                                   p_read_params->t3t_block_info,
                                                   p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                                   NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T4T:
        {
            /* Check for larger offset to use ODO or not */
            if (p_read_params->t4t_file_offset < RM_NFC_READER_NATIVE_TAG_OFFSET)
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T4TReadBinary(&p_ctrl->t4t_comp,
                                                            (uint16_t) p_read_params->t4t_file_offset,
                                                            p_read_params->t4t_data_num_bytes, p_data_info->p_rx_buf,
                                                            (size_t *) &p_data_info->rx_length,
                                                            NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }
            else
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T4TReadBinaryODO(&p_ctrl->t4t_comp, p_read_params->t4t_file_offset,
                                                               p_read_params->t4t_data_num_bytes, p_data_info->p_rx_buf,
                                                               (size_t *) &p_data_info->rx_length,
                                                               NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }

            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T5T:
        {
            /* Check for multiple blocks to be read */
            if (0 == p_read_params->t5t_num_blocks)
            {
                /* Check if an extended read is needed based on block number selected */
                if (p_read_params->t5t_block_number <= RM_NFC_READER_NATIVE_TAG_EXTENDED_SIZE)
                {
                    FSP_ERROR_RETURN(ptxStatus_Success ==
                                     ptxNativeTag_T5TReadSingleBlock(&p_ctrl->t5t_comp, p_read_params->t5t_option_flag,
                                                                     (uint8_t) p_read_params->t5t_block_number,
                                                                     p_data_info->p_rx_buf,
                                                                     (size_t *) &p_data_info->rx_length,
                                                                     NFC_READER_PTX_TIMEOUT_RAW),
                                     FSP_ERR_INVALID_DATA);
                }
                else
                {
                    FSP_ERROR_RETURN(ptxStatus_Success ==
                                     ptxNativeTag_T5TExtReadSingleBlock(&p_ctrl->t5t_comp,
                                                                        p_read_params->t5t_option_flag,
                                                                        p_read_params->t5t_block_number,
                                                                        p_data_info->p_rx_buf,
                                                                        (size_t *) &p_data_info->rx_length,
                                                                        NFC_READER_PTX_TIMEOUT_RAW),
                                     FSP_ERR_INVALID_DATA);
                }
            }
            else
            {
                /* Check if an extended read is needed based on block number selected */
                if (p_read_params->t5t_block_number <= RM_NFC_READER_NATIVE_TAG_EXTENDED_SIZE)
                {
                    FSP_ERROR_RETURN(ptxStatus_Success ==
                                     ptxNativeTag_T5TReadMultipleBlock(&p_ctrl->t5t_comp,
                                                                       p_read_params->t5t_option_flag,
                                                                       (uint8_t) p_read_params->t5t_block_number,
                                                                       p_read_params->t5t_num_blocks,
                                                                       p_data_info->p_rx_buf,
                                                                       (size_t *) &p_data_info->rx_length,
                                                                       NFC_READER_PTX_TIMEOUT_RAW),
                                     FSP_ERR_INVALID_DATA);
                }
                else
                {
                    FSP_ERROR_RETURN(ptxStatus_Success ==
                                     ptxNativeTag_T5TExtReadMultipleBlock(&p_ctrl->t5t_comp,
                                                                          p_read_params->t5t_option_flag,
                                                                          p_read_params->t5t_block_number,
                                                                          p_read_params->t5t_num_blocks,
                                                                          p_data_info->p_rx_buf,
                                                                          (size_t *) &p_data_info->rx_length,
                                                                          NFC_READER_PTX_TIMEOUT_RAW),
                                     FSP_ERR_INVALID_DATA);
                }
            }

            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Performs a write operation using the Native-Tag API add-on.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_write_params       Pointer to optional parameter structure for write operation.
 * @param[in]  tag_type             The target tag type for the operation.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_INVALID_MODE     One of the available tag types was not selected.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on was not included in project configuration.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Write (nfc_reader_ptx_instance_ctrl_t * const           p_ctrl,
                                              nfc_reader_ptx_native_tag_write_params_t * const p_write_params,
                                              nfc_reader_ptx_native_tag_type_t                 tag_type,
                                              nfc_reader_ptx_data_info_t * const               p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_write_params);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_type);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->native_tag_open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_write_params);
    FSP_PARAMETER_NOT_USED(tag_type);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else

    /* Check that at least one tag type was enabled */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != NFC_READER_PTX_NATIVE_TAG_TYPE_NONE, FSP_ERR_INVALID_MODE);

    switch (tag_type)
    {
        case NFC_READER_PTX_NATIVE_TAG_TYPE_T2T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T2TWrite(&p_ctrl->t2t_comp, p_write_params->t2t_block_number,
                                                   p_data_info->p_tx_buf, (uint8_t) p_data_info->tx_length,
                                                   p_data_info->p_rx_buf,
                                                   (size_t *) &p_data_info->rx_length, NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T3T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T3TUpdate(&p_ctrl->t3t_comp, p_write_params->t3t_nfcid2,
                                                    p_write_params->t3t_nfcid2_len, p_write_params->t3t_service_info,
                                                    p_write_params->t3t_block_info,
                                                    p_data_info->p_tx_buf, (uint8_t) p_data_info->tx_length,
                                                    p_data_info->p_rx_buf,
                                                    (size_t *) &p_data_info->rx_length, NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T4T:
        {
            /* Check for larger offset to use ODO or not */
            if (p_write_params->t4t_file_offset < RM_NFC_READER_NATIVE_TAG_OFFSET)
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T4TUpdateBinary(&p_ctrl->t4t_comp,
                                                              (uint16_t) p_write_params->t4t_file_offset,
                                                              p_data_info->p_tx_buf, (uint8_t) p_data_info->tx_length,
                                                              p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                                              NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }
            else
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T4TUpdateBinaryODO(&p_ctrl->t4t_comp, p_write_params->t4t_file_offset,
                                                                 p_data_info->p_tx_buf,
                                                                 (uint8_t) p_data_info->tx_length,
                                                                 p_data_info->p_rx_buf,
                                                                 (size_t *) &p_data_info->rx_length,
                                                                 NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }

            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T5T:
        {
            /* Check if an extended write is needed based on block number selected */
            if (p_write_params->t5t_block_number <= RM_NFC_READER_NATIVE_TAG_EXTENDED_SIZE)
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T5TWriteSingleBlock(&p_ctrl->t5t_comp, p_write_params->t5t_option_flag,
                                                                  (uint8_t) p_write_params->t5t_block_number,
                                                                  p_data_info->p_tx_buf,
                                                                  (uint8_t) p_data_info->tx_length,
                                                                  p_data_info->p_rx_buf,
                                                                  (size_t *) &p_data_info->rx_length,
                                                                  NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }
            else
            {
                FSP_ERROR_RETURN(ptxStatus_Success ==
                                 ptxNativeTag_T5TExtWriteSingleBlock(&p_ctrl->t5t_comp, p_write_params->t5t_option_flag,
                                                                     p_write_params->t5t_block_number,
                                                                     p_data_info->p_tx_buf,
                                                                     (uint8_t) p_data_info->tx_length,
                                                                     p_data_info->p_rx_buf,
                                                                     (size_t *) &p_data_info->rx_length,
                                                                     NFC_READER_PTX_TIMEOUT_RAW),
                                 FSP_ERR_INVALID_DATA);
            }

            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
            break;
        }
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Performs a Select operation using the Native-Tag API add-on, which is different for each tag type.
 *  For Type 2 tags, this selects a different sector (memory page).
 *  For Type 3 tags, they do not use a Select function (returns unsupported).
 *  For Type 4 tags, it selects a different File and/or Application on the tag.
 *  For Type 5 tags, this sets a tag as selected, allowing a reader to communicate with a specific tag without its UID.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_select_params      Pointer to optional parameter structure for select operation.
 * @param[in]  tag_type             The target tag type for the operation.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_INVALID_MODE     One of the available tag types was not selected.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on not enabled, or tag type not supported.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Select (nfc_reader_ptx_instance_ctrl_t * const            p_ctrl,
                                               nfc_reader_ptx_native_tag_select_params_t * const p_select_params,
                                               nfc_reader_ptx_native_tag_type_t                  tag_type,
                                               nfc_reader_ptx_data_info_t * const                p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_select_params);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_type);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->native_tag_open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_select_params);
    FSP_PARAMETER_NOT_USED(tag_type);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else

    /* Check that at least one tag type was enabled */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != NFC_READER_PTX_NATIVE_TAG_TYPE_NONE, FSP_ERR_INVALID_MODE);

    switch (tag_type)
    {
        case NFC_READER_PTX_NATIVE_TAG_TYPE_T2T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T2TSectorSelect(&p_ctrl->t2t_comp, p_select_params->t2t_sector_number,
                                                          p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                                          NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T3T:
        {
            return FSP_ERR_UNSUPPORTED;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T4T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T4TSelect(&p_ctrl->t4t_comp, p_select_params->t4t_apdu_byte_1,
                                                    p_select_params->t4t_apdu_byte_2, p_data_info->p_tx_buf,
                                                    (uint8_t) p_data_info->tx_length,
                                                    p_select_params->t4t_expected_len, p_data_info->p_rx_buf,
                                                    (size_t *) &p_data_info->rx_length,
                                                    NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
            break;
        }

        case NFC_READER_PTX_NATIVE_TAG_TYPE_T5T:
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T5TSelect(&p_ctrl->t5t_comp, p_select_params->t5t_option_flag,
                                                    p_select_params->t5t_uid, p_select_params->t5t_uid_len,
                                                    p_data_info->p_rx_buf,
                                                    (size_t *) &p_data_info->rx_length, NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);

            /* Sets / Updates the UID to be used after Select */
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T5TSetUID(&p_ctrl->t5t_comp, p_select_params->t5t_uid,
                                                    p_select_params->t5t_uid_len),
                             FSP_ERR_INVALID_DATA);

            break;
        }

        default:
        {
            return FSP_ERR_INVALID_MODE;
        }
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Performs a Lock operation using the Native-Tag API add-on.
 *  This function is exclusive to Type 5 tags.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_lock_params        Pointer to optional parameter structure for lock operation.
 * @param[in]  tag_type             The target tag type for the operation.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_DATA     Problem with input parameters or data transmission.
 * @retval FSP_ERR_INVALID_MODE     One of the available tag types was not selected.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on not enabled, or tag type not supported.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Lock (nfc_reader_ptx_instance_ctrl_t * const          p_ctrl,
                                             nfc_reader_ptx_native_tag_lock_params_t * const p_lock_params,
                                             nfc_reader_ptx_native_tag_type_t                tag_type,
                                             nfc_reader_ptx_data_info_t * const              p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_lock_params);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_type);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->native_tag_open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_lock_params);
    FSP_PARAMETER_NOT_USED(tag_type);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else

    /* Check that at least one tag type was enabled */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != NFC_READER_PTX_NATIVE_TAG_TYPE_NONE, FSP_ERR_INVALID_MODE);

    if (NFC_READER_PTX_NATIVE_TAG_TYPE_T5T == tag_type)
    {
        /* Check if an extended write is needed based on block number selected */
        if (p_lock_params->t5t_block_number <= RM_NFC_READER_NATIVE_TAG_EXTENDED_SIZE)
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T5TLockSingleBlock(&p_ctrl->t5t_comp, p_lock_params->t5t_option_flag,
                                                             (uint8_t) p_lock_params->t5t_block_number,
                                                             p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                                             NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
        }
        else
        {
            FSP_ERROR_RETURN(ptxStatus_Success ==
                             ptxNativeTag_T5TExtLockSingleBlock(&p_ctrl->t5t_comp, p_lock_params->t5t_option_flag,
                                                                p_lock_params->t5t_block_number, p_data_info->p_rx_buf,
                                                                (size_t *) &p_data_info->rx_length,
                                                                NFC_READER_PTX_TIMEOUT_RAW),
                             FSP_ERR_INVALID_DATA);
        }
    }
    else
    {
        return FSP_ERR_UNSUPPORTED;
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Performs a Sleep operation using the Native-Tag API add-on.
 *  This function is exclusive to Type 5 tags.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_sleep_params       Pointer to optional parameter structure for sleep operation.
 * @param[in]  tag_type             The target tag type for the operation.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened yet.
 * @retval FSP_ERR_INVALID_STATE    NFC module is not in the activated state.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to the function.
 * @retval FSP_ERR_UNSUPPORTED      Native-Tag API add-on not enabled, or tag type not supported.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Sleep (nfc_reader_ptx_instance_ctrl_t * const           p_ctrl,
                                              nfc_reader_ptx_native_tag_sleep_params_t * const p_sleep_params,
                                              nfc_reader_ptx_native_tag_type_t                 tag_type,
                                              nfc_reader_ptx_data_info_t * const               p_data_info)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_sleep_params);
    FSP_ASSERT(NULL != p_data_info);
    FSP_ASSERT(NFC_READER_PTX_NATIVE_TAG_TYPE_NONE != tag_type);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->native_tag_open, FSP_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_READER_PTX_ACTIVATED, FSP_ERR_INVALID_STATE);
#endif

#if (!RM_NFC_READER_NATIVE_TAG_SUPPORT)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_sleep_params);
    FSP_PARAMETER_NOT_USED(tag_type);
    FSP_PARAMETER_NOT_USED(p_data_info);

    return FSP_ERR_UNSUPPORTED;
#else

    /* Check that at least one tag type was enabled */
    FSP_ERROR_RETURN(p_ctrl->enabled_tag_mask != NFC_READER_PTX_NATIVE_TAG_TYPE_NONE, FSP_ERR_INVALID_MODE);

    if (NFC_READER_PTX_NATIVE_TAG_TYPE_T5T == tag_type)
    {
        /* Optionally update the internal context with the activated card's UID */
        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T5TSetUID(&p_ctrl->t5t_comp, p_sleep_params->t5t_uid,
                                                p_sleep_params->t5t_uid_len),
                         FSP_ERR_INVALID_ARGUMENT);

        FSP_ERROR_RETURN(ptxStatus_Success ==
                         ptxNativeTag_T5TSleep(&p_ctrl->t5t_comp, p_sleep_params->t5t_option_flag,
                                               p_sleep_params->t5t_uid, p_sleep_params->t5t_uid_len,
                                               p_data_info->p_rx_buf, (size_t *) &p_data_info->rx_length,
                                               NFC_READER_PTX_TIMEOUT_RAW),
                         FSP_ERR_INVALID_ARGUMENT);
    }
    else
    {
        return FSP_ERR_UNSUPPORTED;
    }
    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 *  Closes the FSP NFC module and resets all variables.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_NOT_OPEN         Close being called before the module is Open.
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Close (nfc_reader_ptx_instance_ctrl_t * const p_ctrl)
{
#if (1 == NFC_READER_PTX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NFC_READER_PTX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

#if (RM_NFC_READER_NDEF_SUPPORT)
    if (NFC_READER_PTX_OPEN == p_ctrl->ndef_open)
    {
        /* De-initialize NDEF add-on API and reset flag to initial state */
        ptxNDEF_Close(p_cfg->p_ndef_context);

        p_ctrl->ndef_open = NFC_READER_PTX_CLOSED;
    }
#endif

#if (RM_NFC_READER_NATIVE_TAG_SUPPORT)
    if (NFC_READER_PTX_OPEN == p_ctrl->native_tag_open)
    {
        /* De-initialize Native-Tag add-on API for each open tag type and reset flag to initial state */
        if (p_ctrl->enabled_tag_mask & NFC_READER_PTX_NATIVE_TAG_TYPE_T2T)
        {
            ptxNativeTag_T2TClose(&p_ctrl->t2t_comp);
        }

        if (p_ctrl->enabled_tag_mask & NFC_READER_PTX_NATIVE_TAG_TYPE_T3T)
        {
            ptxNativeTag_T3TClose(&p_ctrl->t3t_comp);
        }

        if (p_ctrl->enabled_tag_mask & NFC_READER_PTX_NATIVE_TAG_TYPE_T4T)
        {
            ptxNativeTag_T4TClose(&p_ctrl->t4t_comp);
        }

        if (p_ctrl->enabled_tag_mask & NFC_READER_PTX_NATIVE_TAG_TYPE_T5T)
        {
            ptxNativeTag_T5TClose(&p_ctrl->t5t_comp);
        }

        p_ctrl->native_tag_open = NFC_READER_PTX_CLOSED;
    }
#endif

    /* Reset values to initial state */
    p_ctrl->open       = NFC_READER_PTX_CLOSED;
    p_ctrl->state_flag = NFC_READER_PTX_IDLE;

    ptxIoTRd_Deinit(p_cfg->iot_reader_context);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NFC_READER_PTX)
 **********************************************************************************************************************/
