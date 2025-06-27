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
#define NFC_READER_PTX_ZERO                (0)
#define NFC_READER_PTX_SHUTDOWN_TEMP       (223U)

/* ASCII conversion from string of "NFC" */
#define NFC_READER_PTX_OPEN                (0x4e4643ULL)
#define NFC_READER_PTX_CLOSED              (0)

/* Default timeout-values for for RAW-protocols (e.g. T2T, T3T, ...) and standard-protocols (ISO-/NFC-DEP) */
#define NFC_READER_PTX_TIMEOUT_RAW         (200U)   // Application-timeout for raw-protocols
#define NFC_READER_PTX_TIMEOUT_PROTOCOL    (50000U) // Application-timeout for standard-protocols

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
 * @retval FSP_ERR_INVALID_DATA     NFC SDK initialization data was incomplete.
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
                     FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(ptxStatus_Success == ptxPLAT_TIMER_Open(p_cfg->p_timer_context), FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(ptxStatus_Success == ptxPERIPH_APPTIMER_Open(p_cfg->p_app_timer), FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxPLAT_SPI_Open(p_cfg->p_comms_instance_ctrl, p_cfg->p_gpio_context),
                     FSP_ERR_INVALID_DATA);

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
 * @retval FSP_ERR_INVALID_DATA     NFC Discovery parameters were invalid or discovery was not started.
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
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to NFC Status function.
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
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid input parameters to NFC registry function.
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
 * @retval FSP_ERR_INVALID_ARGUMENT Issue with input parameters (buffers) leading to failed transmission.
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
 * @retval FSP_ERR_INVALID_ARGUMENT Issue with input parameters or transmission.
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
                     FSP_ERR_INVALID_ARGUMENT);

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
        FSP_ERROR_RETURN(ptxStatus_Success == ptxNDEF_Close(p_cfg->p_ndef_context), FSP_ERR_INVALID_ARGUMENT);

        p_ctrl->ndef_open = NFC_READER_PTX_CLOSED;
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
