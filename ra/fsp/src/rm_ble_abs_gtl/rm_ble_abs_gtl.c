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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <rm_ble_abs.h>
#include <rm_ble_abs_api.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "fsp_common_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "BLE_ABS" in ASCII, used to determine if module is open. */
#define BLE_ABS_OPEN    (0X00424C45ULL)

/* Advertising handles */
typedef enum e_ble_abs_handle_type
{
    BLE_ABS_LEGACY_HDL   = 0x00,       // Advertising Handle for Legacy Advertising
    BLE_ABS_NON_CONN_HDL = 0x02,       // Advertising Handle for Non-Connectable Advertising
} ble_abs_handle_type_t;

/* Advertising status */
typedef enum e_ble_abs_adv_status
{
    BLE_ABS_ADV_STATUS_PARAM_FAST     = 0x00000001, // Set fast advertising parameters
    BLE_ABS_ADV_STATUS_PARAM_SLOW     = 0x00000002, // Set slow advertising parameters
    BLE_ABS_ADV_STATUS_ADV_DATA       = 0x00000010, // Set advertising data
    BLE_ABS_ADV_STATUS_SRES_DATA      = 0x00000020, // Set scan response data
    BLE_ABS_ADV_STATUS_PERD_DATA      = 0x00000040, // Set periodic advertising data
    BLE_ABS_ADV_STATUS_ADV_FAST_START = 0x00000100, // Start fast advertising
    BLE_ABS_ADV_STATUS_ADV_SLOW_START = 0x00000200, // Start slow advertising
    BLE_ABS_ADV_STATUS_PERD_PARAM     = 0x00001000, // Set periodic advertising parameters
    BLE_ABS_ADV_STATUS_PERD_START     = 0x00010000, // Start periodic advertising
} ble_abs_adv_status_t;

/* Scan status */
typedef enum e_ble_abs_scan_status
{
    BLE_ABS_SCAN_STATUS_FAST_START = 0x00000001, // Start fast scan
    BLE_ABS_SCAN_STATUS_SLOW_START = 0x00000002, // Start slow scan
} ble_abs_scan_status_t;

/* Privacy status */
typedef enum e_ble_abs_pv_status
{
    BLE_ABS_PV_STATUS_CREATE_IRK = 0x00000001, // Create irk
    BLE_ABS_PV_STATUS_ADD_RSLV   = 0x00000002, // Add irk to resolving list
    BLE_ABS_PV_STATUS_SET_MODE   = 0x00000004, // Set privacy mode
    BLE_ABS_PV_STATUS_EN_RPA     = 0x00000008, // Enable resolvable private address function
} ble_abs_pv_status_t;

/*********************************/
/* Define for create connection  */
/*********************************/

/* Minimum advertising data length */
#define BLE_ABS_LEGACY_ADV_DATA_LEN    (31)

/* The invalid timer handle. */
#define BLE_TIMER_INVALID_HDL          (0xFF)

/***********************************************************************************************************************
 * Local Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static fsp_err_t ble_abs_convert_legacy_advertising_parameter(
    ble_abs_legacy_advertising_parameter_t * p_legacy_advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter);

static fsp_err_t ble_abs_advertising_report_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                    st_ble_evt_data_t             * p_event_data);

static void ble_abs_gap_callback(uint16_t event_type, ble_status_t event_result, st_ble_evt_data_t * p_event_data);
static void ble_abs_set_abs_callback(ble_abs_instance_ctrl_t * const            p_instance_ctrl,
                                     ble_gap_application_callback_t             gap_callback,
                                     ble_vendor_specific_application_callback_t vendor_specific_callback);
static void ble_abs_set_advertising_status(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                           uint8_t                         advertising_handle,
                                           uint32_t                        set,
                                           uint32_t                        clear);
static void ble_abs_set_advertising_parameter(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                              void                          * p_advertising_parameter,
                                              uint8_t                         advertising_handle);

static void ble_abs_update_data_status(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                       uint32_t                        advertising_status,
                                       uint8_t                       * p_advertising_data,
                                       uint16_t                        advertising_data_len,
                                       uint8_t                         advertising_handle);

static void ble_abs_advertising_parameter_set_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                      st_ble_evt_data_t             * p_event_data);
static void ble_abs_advertising_data_set_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                 st_ble_evt_data_t             * p_event_data);

static void ble_abs_advertising_start(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t advertising_handle);
static void ble_abs_advertising_set_data(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                         uint8_t                         advertising_handle,
                                         uint8_t                         data_type);
static void ble_abs_set_legacy_scan_response_data(ble_abs_instance_ctrl_t * const p_instance_ctrl);

static void ble_abs_set_connection_advertising_interval(st_ble_gap_adv_param_t * p_advertising_parameter,
                                                        uint32_t                 fast_advertising_interval,
                                                        uint32_t                 slow_advertising_interval,
                                                        uint16_t                 fast_period);

/* BLE ABS on BLE HAL API mapping for BLE ABS interface */
const ble_abs_api_t g_ble_abs_on_ble =
{
    .open  = RM_BLE_ABS_Open,
    .close = RM_BLE_ABS_Close,
    .reset = RM_BLE_ABS_Reset,
    .startLegacyAdvertising         = RM_BLE_ABS_StartLegacyAdvertising,
    .startExtendedAdvertising       = RM_BLE_ABS_StartExtendedAdvertising,
    .startNonConnectableAdvertising = RM_BLE_ABS_StartNonConnectableAdvertising,
    .startPeriodicAdvertising       = RM_BLE_ABS_StartPeriodicAdvertising,
    .startScanning         = RM_BLE_ABS_StartScanning,
    .createConnection      = RM_BLE_ABS_CreateConnection,
    .setLocalPrivacy       = RM_BLE_ABS_SetLocalPrivacy,
    .startAuthentication   = RM_BLE_ABS_StartAuthentication,
    .deleteBondInformation = RM_BLE_ABS_DeleteBondInformation,
};

ble_abs_instance_ctrl_t * gp_instance_ctrl;

/***********************************************************************************************************************
 * Exported global functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Host stack is initialized with this function. Before using All the R_BLE APIs,
 * it's necessary to call this function. A callback functions are registered with this function.
 * In order to receive the GAP, GATT, Vendor specific event,
 * it's necessary to register a callback function.
 * The result of this API call is notified in BLE_GAP_EVENT_STACK_ON event.
 * Implements @ref ble_abs_api_t::open.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_Open
 *
 * @retval FSP_SUCCESS                                 Channel opened successfully.
 * @retval FSP_ERR_ASSERTION                           Null pointer presented.
 * @retval FSP_ERR_ALREADY_OPEN                        Requested channel is already open in a different configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Invalid input parameter.
 * @retval FSP_ERR_INVALID_MODE                        Invalid mode during open call
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Open (ble_abs_ctrl_t * const p_ctrl, ble_abs_cfg_t const * const p_cfg)
{
    int32_t      i;
    ble_status_t ble_status = BLE_SUCCESS;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->gap_callback);
#endif

    FSP_ERROR_RETURN(BLE_ABS_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    gp_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    p_instance_ctrl->abs_gap_callback             = NULL;
    p_instance_ctrl->abs_vendor_specific_callback = NULL;
    p_instance_ctrl->privacy_mode                 = BLE_GAP_NET_PRIV_MODE;
    p_instance_ctrl->set_privacy_status           = 0;
    p_instance_ctrl->p_cfg = p_cfg;

    ble_status = R_BLE_Open();
    FSP_ERROR_RETURN(BLE_SUCCESS == ble_status, FSP_ERR_INVALID_MODE);

    ble_abs_set_abs_callback(p_instance_ctrl, p_cfg->gap_callback, p_cfg->vendor_specific_callback);

    FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_VS_Init(p_instance_ctrl->abs_vendor_specific_callback),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Initialize GAP layer */
    ble_status = R_BLE_GAP_Init(ble_abs_gap_callback);
    FSP_ERROR_RETURN(BLE_SUCCESS == ble_status, FSP_ERR_INVALID_ARGUMENT);

    p_instance_ctrl->advertising_sets[0].advertising_status = 0;

    p_instance_ctrl->abs_scan.scan_status    = 0;
    p_instance_ctrl->connection_timer_handle = BLE_TIMER_INVALID_HDL;
    p_instance_ctrl->set_privacy_status      = 0;

    if ((0 < p_cfg->gatt_server_callback_list_number) && (NULL != p_cfg->p_gatt_server_callback_list))
    {
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTS_Init(p_cfg->gatt_server_callback_list_number),
                         FSP_ERR_INVALID_ARGUMENT);

        for (i = 0; i < p_cfg->gatt_server_callback_list_number; i++)
        {
            if (NULL != p_cfg->p_gatt_server_callback_list[i].gatt_server_callback_function)
            {
                FSP_ERROR_RETURN(BLE_SUCCESS ==
                                 R_BLE_GATTS_RegisterCb(p_cfg->p_gatt_server_callback_list[i].
                                                        gatt_server_callback_function,
                                                        p_cfg->p_gatt_server_callback_list[i].
                                                        gatt_server_callback_priority),
                                 FSP_ERR_INVALID_ARGUMENT);
            }
            else
            {
                break;
            }
        }
    }

    if ((0 < p_cfg->gatt_client_callback_list_number) && (NULL != p_cfg->p_gatt_client_callback_list))
    {
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTC_Init(p_cfg->gatt_client_callback_list_number),
                         FSP_ERR_INVALID_ARGUMENT);

        for (i = 0; i < p_cfg->gatt_client_callback_list_number; i++)
        {
            ble_abs_gatt_client_callback_set_t   * p_cb_list = &(p_cfg->p_gatt_client_callback_list[i]);
            ble_gatt_client_application_callback_t callback  = p_cb_list->gatt_client_callback_function;

            if (NULL != callback)
            {
                FSP_ERROR_RETURN(BLE_SUCCESS ==
                                 R_BLE_GATTC_RegisterCb(callback, p_cb_list->gatt_client_callback_priority),
                                 FSP_ERR_INVALID_ARGUMENT);
            }
            else
            {
                break;
            }
        }
    }

    p_instance_ctrl->open = BLE_ABS_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_Open() */

/*******************************************************************************************************************//**
 * @brief Close the BLE channel.
 * Implements @ref ble_abs_api_t::close.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_Close
 *
 * @retval  FSP_SUCCESS              Channel closed successfully.
 * @retval  FSP_ERR_ASSERTION        Null pointer presented.
 * @retval  FSP_ERR_NOT_OPEN         Control block not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Close (ble_abs_ctrl_t * const p_ctrl)
{
    ble_abs_instance_ctrl_t * p_ble_abs_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ble_abs_ctrl);
#endif
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_ble_abs_ctrl->open, FSP_ERR_NOT_OPEN);

    R_BLE_Close();

    p_ble_abs_ctrl->open = 0;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_Close() */

/*******************************************************************************************************************//**
 * This function is not implemented. To perform this function call R_BLE_Close followed by R_BLE_Open.
 * Implements @ref ble_abs_api_t::reset.
 *
 * @retval  FSP_ERR_UNSUPPORTED     Function is not supported
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Reset (ble_abs_ctrl_t * const p_ctrl, ble_event_cb_t init_callback)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(init_callback);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Start Legacy Advertising after setting advertising parameters, advertising data and scan response data.
 * The legacy advertising uses the advertising set whose advertising handle is 0.
 * The advertising type is connectable and scannable(ADV_IND).
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Implements @ref ble_abs_api_t::startLegacyAdvertising
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_StartLegacyAdvertising
 *
 * @retval FSP_SUCCESS                                 Operation succeeded
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_STATE                       Host stack hasn't been initialized.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartLegacyAdvertising (ble_abs_ctrl_t * const                               p_ctrl,
                                             ble_abs_legacy_advertising_parameter_t const * const p_advertising_parameter)
{
    st_ble_gap_adv_param_t    advertising_parameter;
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    uint8_t advertising_handle = BLE_ABS_LEGACY_HDL;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
#endif

    /* Status check */
    FSP_ERROR_RETURN(0 == (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status &
                           (BLE_ABS_ADV_STATUS_ADV_FAST_START | BLE_ABS_ADV_STATUS_ADV_SLOW_START)),
                     FSP_ERR_INVALID_STATE);

    ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, 0,
                                   (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW));

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_convert_legacy_advertising_parameter((ble_abs_legacy_advertising_parameter_t *)
                                                                  p_advertising_parameter,
                                                                  &advertising_parameter),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Check data length */
    FSP_ERROR_RETURN((BLE_ABS_LEGACY_ADV_DATA_LEN >= p_advertising_parameter->advertising_data_length) &&
                     (BLE_ABS_LEGACY_ADV_DATA_LEN >= p_advertising_parameter->scan_response_data_length),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Check advertising interval */
    ble_abs_set_connection_advertising_interval(&advertising_parameter,
                                                p_advertising_parameter->fast_advertising_interval,
                                                p_advertising_parameter->slow_advertising_interval,
                                                p_advertising_parameter->fast_advertising_period);

    /* Advertising data update check */
    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_ADV_DATA,
                               p_advertising_parameter->p_advertising_data,
                               p_advertising_parameter->advertising_data_length,
                               advertising_handle);

    /* Scan response data update check */
    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_SRES_DATA,
                               p_advertising_parameter->p_scan_response_data,
                               p_advertising_parameter->scan_response_data_length,
                               advertising_handle);

    ble_abs_set_advertising_parameter(p_instance_ctrl,
                                      (ble_abs_legacy_advertising_parameter_t *) p_advertising_parameter,
                                      BLE_ABS_LEGACY_HDL);

    /* Do NOT set the MAC address because it clears the current attribute database */
    /* MAC Address set at boot only */

    FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GAP_SetAdvParam(&advertising_parameter), FSP_ERR_INVALID_ARGUMENT);

    if ((NULL != p_advertising_parameter->p_advertising_data) && (0 < p_advertising_parameter->advertising_data_length))
    {
        /* Configure the GAP Advertisment Payload. */
        st_ble_gap_adv_data_t advertising_data = {0};
        advertising_data.data_type   = (uint8_t) (BLE_GAP_ADV_DATA_MODE);
        advertising_data.data_length = p_advertising_parameter->advertising_data_length;
        advertising_data.p_data      = p_advertising_parameter->p_advertising_data;
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GAP_SetAdvSresData(&advertising_data), FSP_ERR_INVALID_ARGUMENT);
    }

    if ((NULL != p_advertising_parameter->p_scan_response_data) &&
        (0 < p_advertising_parameter->scan_response_data_length))
    {
        /* Configure the GAP Scan Response Payload. */
        st_ble_gap_adv_data_t advertising_data = {0};
        advertising_data.data_type   = (uint8_t) (BLE_GAP_SCAN_RSP_DATA_MODE);
        advertising_data.data_length = p_advertising_parameter->scan_response_data_length;
        advertising_data.p_data      = p_advertising_parameter->p_scan_response_data;
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GAP_SetAdvSresData(&advertising_data), FSP_ERR_INVALID_ARGUMENT);
    }

    /* Start Legacy Advertisment. */
    FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GAP_StartAdv(0, 0, 0), FSP_ERR_INVALID_ARGUMENT);

    /* Set the internal status flags to indicate the advertisment mode. */
    uint32_t status =
        p_advertising_parameter->fast_advertising_period ? BLE_ABS_ADV_STATUS_PARAM_FAST : BLE_ABS_ADV_STATUS_PARAM_SLOW;
    ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_StartLegacyAdvertising() */

/*******************************************************************************************************************//**
 * Start Extended Advertising after setting advertising parameters, advertising data.
 * The extended advertising uses the advertising set whose advertising handle is 1.
 * The advertising type is connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Implements @ref ble_abs_api_t::startExtendedAdvertising
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_UNSUPPORTED                         Subordinate modules do not support this feature.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartExtendedAdvertising (ble_abs_ctrl_t * const                               p_ctrl,
                                               ble_abs_extend_advertising_parameter_t const * const p_advertising_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_advertising_parameter);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_StartExtendedAdvertising() */

/*******************************************************************************************************************//**
 * Start Non-Connectable Advertising after setting advertising parameters, advertising data.
 * The non-connectable advertising uses the advertising set whose advertising handle is 2.
 * The advertising type is non-connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Secondary Advertising Max Skip is 0.
 * Implements @ref ble_abs_api_t::startNonConnectableAdvertising.
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_UNSUPPORTED                         Feature not yet supported.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartNonConnectableAdvertising (
    ble_abs_ctrl_t * const                                        p_ctrl,
    ble_abs_non_connectable_advertising_parameter_t const * const p_advertising_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_advertising_parameter);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_StartNonConnectableAdvertising() */

/*******************************************************************************************************************//**
 * Start Periodic Advertising after setting advertising parameters, periodic advertising parameters,
 * advertising data and periodic advertising data.
 * The periodic advertising uses the advertising set whose advertising handle is 3.
 * The advertising type is non-connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Secondary Advertising Max Skip is 0.
 * Implements @ref ble_abs_api_t::startPeriodicAdvertising
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_UNSUPPORTED                         Subordinate modules do not support this feature.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartPeriodicAdvertising (ble_abs_ctrl_t * const                                 p_ctrl,
                                               ble_abs_periodic_advertising_parameter_t const * const p_advertising_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_advertising_parameter);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_StartPeriodicAdvertising() */

/*******************************************************************************************************************//**
 * Start scanning after setting scan parameters.
 * The scanner address type is Public Identity Address.
 * Fast scan is followed by slow scan.
 * The end of fast scan or slow scan is notified with BLE_GAP_EVENT_SCAN_TO event.
 * If fast_period is 0, only slow scan is carried out.
 * If scan_period is 0, slow scan continues.
 * Implements @ref ble_abs_api_t::startScanning.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_StartScanning
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_scan_parameter is specified as NULL.
 * @retval FSP_ERR_UNSUPPORTED                         Function is not supported
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartScanning (ble_abs_ctrl_t * const                 p_ctrl,
                                    ble_abs_scan_parameter_t const * const p_scan_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_scan_parameter, FSP_ERR_INVALID_POINTER);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_scan_parameter);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_StartScanning() */

/*******************************************************************************************************************//**
 * Generate a IRK, add it to the resolving list, set privacy mode and enable RPA function.
 * Register vendor specific callback function, if IRK is generated by this function.
 * After configuring local device privacy,
 * BLE_GAP_ADDR_RPA_ID_PUBLIC is specified as own device address
 * in theadvertising/scan/create connection API.
 * Implements @ref ble_abs_api_t::setLocalPrivacy
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The privacy_mode parameter is out of range.
 * @retval FSP_ERR_UNSUPPORTED                         Function is not supported
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_SetLocalPrivacy (ble_abs_ctrl_t * const p_ctrl,
                                      uint8_t const * const  p_lc_irk,
                                      uint8_t                privacy_mode)
{
    FSP_PARAMETER_NOT_USED(p_lc_irk);

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BLE_GAP_DEV_PRIV_MODE >= privacy_mode, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(privacy_mode);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_SetLocalPrivacy() */

/*******************************************************************************************************************//**
 * Request create connection.
 * The initiator address type is Public Identity Address.
 * The scan interval is 60ms and the scan window is 30ms in case of 1M PHY or 2M PHY.
 * The scan interval is 180ms and the scan window is 90ms in case of coded PHY.
 * The Minimum CE Length and the Maximum CE Length are 0xFFFF.
 * When the request for a connection has been received by the Controller,
 * BLE_GAP_EVENT_CREATE_CONN_COMP event is notified.
 * When a link has beens established, BLE_GAP_EVENT_CONN_IND event is notified.
 * Implements @ref ble_abs_api_t::createConnection.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_CreateConnection
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_connection_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The create connection parameter is out of range.
 * @retval FSP_ERR_UNSUPPORTED                         Function is not supported
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_CreateConnection (ble_abs_ctrl_t * const                       p_ctrl,
                                       ble_abs_connection_parameter_t const * const p_connection_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_connection_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(10 >= p_connection_parameter->connection_timeout, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_connection_parameter);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_CreateConnection() */

/*******************************************************************************************************************//**
 * Start pairing or encryption. If pairing has been done, start encryption.
 * The pairing parameters are configured by RM_BLE_ABS_Open() or R_BLE_GAP_SetPairingParams().
 * If the pairing parameters are configure by RM_BLE_ABS_Open(),
 *    - bonding policy is that bonding information is stored.
 *    - Key press notification is not supported.
 * Implements @ref ble_abs_api_t::startAuthentication.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_StartAuthentication
 *
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl or connection_handle are specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_UNSUPPORTED                         Function is not supported
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartAuthentication (ble_abs_ctrl_t * const p_ctrl, uint16_t connection_handle)
{
    FSP_PARAMETER_NOT_USED(connection_handle);

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function RM_BLE_ABS_StartAuthentication() */

/*******************************************************************************************************************//**
 * Delete bonding information from BLE stack and storage.
 * Implements @ref ble_abs_api_t::deleteBondInformation.
 *
 * Example:
 * @snippet rm_ble_abs_gtl_example.c RM_BLE_ABS_DeleteBondInformation
 *
 * @retval FSP_SUCCESS             Operation was successful
 * @retval FSP_ERR_ASSERTION       The parameter p_instance_ctrl is NULL.
 * @retval FSP_ERR_INVALID_POINTER The parameter p_bond_information_parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN        Control block not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_DeleteBondInformation (ble_abs_ctrl_t * const                             p_ctrl,
                                            ble_abs_bond_information_parameter_t const * const p_bond_information_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_bond_information_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_bond_information_parameter);
#endif

    return FSP_SUCCESS;
}

/************************************************
 *   Static function definitions                *
 ***********************************************/

/*******************************************************************************************************************//**
 * Configure scan response data and start legacy advertising.
 **********************************************************************************************************************/
static void ble_abs_set_legacy_scan_response_data (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    ble_abs_legacy_advertising_parameter_t * p_legacy_parameter =
        &(p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
          legacy_advertising_parameter);

    if (p_legacy_parameter->scan_response_data_length && p_legacy_parameter->p_scan_response_data)
    {
        if (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status & BLE_ABS_ADV_STATUS_SRES_DATA)
        {
            ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
        }
        else
        {
            ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_LEGACY_HDL, BLE_GAP_SCAN_RSP_DATA_MODE);
        }
    }
    else
    {
        ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
    }
}                                      /* End of function ble_abs_set_legacy_scan_response_data() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_PARAM_SET_COMP event.
 **********************************************************************************************************************/
static void ble_abs_advertising_parameter_set_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                       st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_set_evt_t * p_advertising_set_parameter;
    p_advertising_set_parameter = (st_ble_gap_adv_set_evt_t *) p_event_data->p_param;

    switch (p_advertising_set_parameter->adv_hdl)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status &
                 (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW)))
            {
                ble_abs_legacy_advertising_parameter_t * p_legacy_parameter =
                    &(p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                      legacy_advertising_parameter);

                if (p_legacy_parameter->advertising_data_length && p_legacy_parameter->p_advertising_data)
                {
                    if (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status &
                        BLE_ABS_ADV_STATUS_ADV_DATA)
                    {
                        ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
                    }
                    else
                    {
                        ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_LEGACY_HDL, BLE_GAP_ADV_DATA_MODE);
                    }
                }
                else
                {
                    ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
                }
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            if (p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_status &
                BLE_ABS_ADV_STATUS_PARAM_SLOW)
            {
                if ((p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                     non_connectable_advertising_parameter.advertising_data_length) &&
                    (p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                     non_connectable_advertising_parameter.p_advertising_data))
                {
                    ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_NON_CONN_HDL, BLE_GAP_ADV_DATA_MODE);
                }
                else
                {
                    ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_NON_CONN_HDL);
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function ble_abs_advertising_parameter_set_handler() */

/*******************************************************************************************************************//**
 * Start advertising.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_advertising_start (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t advertising_handle)
{
    ble_status_t retval = BLE_SUCCESS;

    uint32_t status      = 0;
    uint16_t fast_period = 0;

    if (BLE_ABS_LEGACY_HDL == advertising_handle)
    {
        fast_period = p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                      legacy_advertising_parameter.fast_advertising_period;
    }

    if (0x0000 == fast_period)
    {
        status = BLE_ABS_ADV_STATUS_ADV_SLOW_START;
    }
    else
    {
        if (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status & BLE_ABS_ADV_STATUS_PARAM_SLOW)
        {
            status = BLE_ABS_ADV_STATUS_ADV_SLOW_START;
        }
        else
        {
            status = BLE_ABS_ADV_STATUS_ADV_FAST_START;
        }
    }

    retval = R_BLE_GAP_StartAdv(0, 0, 0);
    if (BLE_SUCCESS == retval)
    {
        ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);
    }
}                                      /* End of function ble_abs_advertising_start() */

/*******************************************************************************************************************//**
 * Configure advertising data or scan response data or periodic advertising data.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_advertising_set_data (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                          uint8_t                         advertising_handle,
                                          uint8_t                         data_type)
{
    st_ble_gap_adv_data_t advertising_data;
    ble_status_t          retval = BLE_SUCCESS;
    uint32_t              status = 0;

    advertising_data.adv_hdl          = advertising_handle;
    advertising_data.zero_length_flag = BLE_GAP_DATA_0_CLEAR;

    switch (advertising_handle)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            ble_abs_legacy_advertising_parameter_t * p_legacy_parameter =
                &(p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                  legacy_advertising_parameter);

            if (BLE_GAP_ADV_DATA_MODE == data_type)
            {
                status = BLE_ABS_ADV_STATUS_ADV_DATA;
                advertising_data.data_type   = (uint8_t) (BLE_GAP_ADV_DATA_MODE);
                advertising_data.data_length = p_legacy_parameter->advertising_data_length;
                advertising_data.p_data      = p_legacy_parameter->p_advertising_data;
            }
            else
            {
                status = BLE_ABS_ADV_STATUS_SRES_DATA;
                advertising_data.data_type   = (uint8_t) (BLE_GAP_SCAN_RSP_DATA_MODE);
                advertising_data.data_length = p_legacy_parameter->scan_response_data_length;
                advertising_data.p_data      = p_legacy_parameter->p_scan_response_data;
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            status = BLE_ABS_ADV_STATUS_ADV_DATA;
            advertising_data.data_type = BLE_GAP_ADV_DATA_MODE;

            ble_abs_non_connectable_advertising_parameter_t * p_non_conn_parameter =
                &(p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].
                  advertising_parameter.non_connectable_advertising_parameter);

            advertising_data.data_length = p_non_conn_parameter->advertising_data_length;
            advertising_data.p_data      = p_non_conn_parameter->p_advertising_data;
            break;
        }

        default:
        {
            break;
        }
    }

    retval = R_BLE_GAP_SetAdvSresData(&advertising_data);
    if (BLE_SUCCESS == retval)
    {
        ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);
    }
}                                      /* End of function ble_abs_advertising_set_data() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_DATA_UPD_COMP event.
 **********************************************************************************************************************/
static void ble_abs_advertising_data_set_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                  st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_data_evt_t * p_advertising_data_set_parameter;

    p_advertising_data_set_parameter = (st_ble_gap_adv_data_evt_t *) p_event_data->p_param;

    switch (p_advertising_data_set_parameter->adv_hdl)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            if (BLE_GAP_ADV_DATA_MODE == p_advertising_data_set_parameter->data_type)
            {
                ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
            }
            else
            {
                ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            ble_abs_advertising_start(p_instance_ctrl, p_advertising_data_set_parameter->adv_hdl);
            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function ble_abs_advertising_data_set_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_REPT_IND event.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                   Filtering data is not included in the advertising data.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_advertising_report_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                     st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_rept_evt_t * p_advertising_report_parameter;
    uint8_t * p_buf  = NULL;
    uint32_t  len    = 0;
    fsp_err_t retval = FSP_ERR_BLE_ABS_NOT_FOUND;

    if ((NULL == p_instance_ctrl->abs_scan.scan_parameter.p_filter_data) ||
        (0 == p_instance_ctrl->abs_scan.scan_parameter.filter_data_length))
    {
        retval = FSP_SUCCESS;
    }
    else
    {
        p_advertising_report_parameter = (st_ble_gap_adv_rept_evt_t *) p_event_data->p_param;

        /* Only Legacy advertising is supported */
        p_buf = p_advertising_report_parameter->param.p_adv_rpt->p_data;
        len   = p_advertising_report_parameter->param.p_adv_rpt->len;

        uint32_t cnt;

        if ((len + 1) >= (uint32_t) p_instance_ctrl->abs_scan.scan_parameter.filter_data_length)
        {
            cnt = len - (uint32_t) p_instance_ctrl->abs_scan.scan_parameter.filter_data_length + 1;
        }
        else
        {
            cnt = 0;
        }

        if (1 <= cnt)
        {
            uint32_t i;
            uint32_t pos = 0U;

            while (pos < len)
            {
                /* Each advertising structure have following constructs.
                 * - Lenght: 1 byte (The length of AD type + AD data)
                 * - AD type: 1 byte
                 * - AD data: variable
                 */
                uint8_t ad_len = (uint8_t) (p_buf[pos] - 1);
                uint8_t type   = p_buf[pos + 1];

                pos = (uint16_t) (pos + 2UL);

                if (type == p_instance_ctrl->abs_scan.scan_parameter.filter_ad_type)
                {
                    for (i = 0; i < ad_len; i++)
                    {
                        if (0 ==
                            memcmp(&p_buf[pos + i], p_instance_ctrl->abs_scan.scan_parameter.p_filter_data,
                                   (uint32_t) p_instance_ctrl->abs_scan.scan_parameter.filter_data_length))
                        {
                            return FSP_SUCCESS;
                        }
                    }
                }

                pos = (uint16_t) (pos + ad_len);
            }
        }
    }

    return retval;
}                                      /* End of function ble_abs_advertising_report_handler() */

/**********************************************************************************************************************
 * Set gap callback and vendor specific callback function.
 **********************************************************************************************************************/
static void ble_abs_set_abs_callback (ble_abs_instance_ctrl_t * const            p_instance_ctrl,
                                      ble_gap_application_callback_t             gap_callback,
                                      ble_vendor_specific_application_callback_t vendor_specific_callback)
{
    p_instance_ctrl->abs_gap_callback             = gap_callback;
    p_instance_ctrl->abs_vendor_specific_callback = vendor_specific_callback;
}                                      /* End of function ble_abs_set_abs_callback() */

/**********************************************************************************************************************
 * Set advertising interval.
 **********************************************************************************************************************/
static void ble_abs_set_connection_advertising_interval (st_ble_gap_adv_param_t * p_advertising_parameter,
                                                         uint32_t                 fast_advertising_interval,
                                                         uint32_t                 slow_advertising_interval,
                                                         uint16_t                 fast_period)
{
    /* Check advertising interval */
    if (fast_period)
    {
        p_advertising_parameter->adv_intv_min = fast_advertising_interval;
        p_advertising_parameter->adv_intv_max = fast_advertising_interval;
    }
    else
    {
        p_advertising_parameter->adv_intv_min = slow_advertising_interval;
        p_advertising_parameter->adv_intv_max = slow_advertising_interval;
    }
}                                      /* End of function ble_abs_set_connection_advertising_interval() */

/*******************************************************************************************************************//**
 * Update advertising data status.
 **********************************************************************************************************************/
static void ble_abs_update_data_status (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                        uint32_t                        advertising_status,
                                        uint8_t                       * p_advertising_data,
                                        uint16_t                        advertising_data_len,
                                        uint8_t                         advertising_handle)
{
    if (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status & advertising_status)
    {
        if ((0 != advertising_data_len) && (NULL != p_advertising_data))
        {
            ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, 0, advertising_status);
        }
    }
}                                      /* End of function ble_abs_update_data_status() */

/*******************************************************************************************************************//**
 * Convert the legacy advertising parameters to GAP advertising parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_convert_legacy_advertising_parameter (
    ble_abs_legacy_advertising_parameter_t * p_legacy_advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter)
{
    p_gap_advertising_parameter->adv_hdl       = BLE_ABS_LEGACY_HDL;
    p_gap_advertising_parameter->adv_prop_type = BLE_GAP_LEGACY_PROP_ADV_IND;
    p_gap_advertising_parameter->adv_ch_map    = p_legacy_advertising_parameter->advertising_channel_map;

    FSP_ERROR_RETURN((BLE_GAP_ADDR_RPA_ID_PUBLIC >= p_legacy_advertising_parameter->own_bluetooth_address_type),
                     FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_gap_advertising_parameter->o_addr,
           (void *) p_legacy_advertising_parameter->own_bluetooth_address,
           BLE_BD_ADDR_LEN);

    p_gap_advertising_parameter->o_addr_type = p_legacy_advertising_parameter->own_bluetooth_address_type;

    if (p_legacy_advertising_parameter->p_peer_address)
    {
        memcpy(p_gap_advertising_parameter->p_addr,
               p_legacy_advertising_parameter->p_peer_address->addr,
               BLE_BD_ADDR_LEN);
        p_gap_advertising_parameter->p_addr_type = p_legacy_advertising_parameter->p_peer_address->type;
    }
    else
    {
        p_gap_advertising_parameter->p_addr_type = BLE_GAP_ADDR_PUBLIC;
    }

    p_gap_advertising_parameter->filter_policy = p_legacy_advertising_parameter->advertising_filter_policy;

    p_gap_advertising_parameter->adv_phy           = BLE_GAP_ADV_PHY_1M;
    p_gap_advertising_parameter->sec_adv_max_skip  = 0x00;
    p_gap_advertising_parameter->sec_adv_phy       = BLE_GAP_ADV_PHY_1M;
    p_gap_advertising_parameter->scan_req_ntf_flag = BLE_GAP_SCAN_REQ_NTF_DISABLE;

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_convert_legacy_advertising_parameter() */

/*******************************************************************************************************************//**
 * Set advertising status.
 **********************************************************************************************************************/
static void ble_abs_set_advertising_status (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                            uint8_t                         advertising_handle,
                                            uint32_t                        set,
                                            uint32_t                        clear)
{
    p_instance_ctrl->advertising_sets[advertising_handle].advertising_status |= set;
    p_instance_ctrl->advertising_sets[advertising_handle].advertising_status &= ~clear;
}                                      /* End of function ble_abs_set_advertising_status() */

/*******************************************************************************************************************//**
 * Store advertising configuration.
 **********************************************************************************************************************/
static void ble_abs_set_advertising_parameter (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                               void                          * p_advertising_parameter,
                                               uint8_t                         advertising_handle)
{
    switch (advertising_handle)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            ble_abs_legacy_advertising_parameter_t * p_abs_legacy;
            p_abs_legacy = (ble_abs_legacy_advertising_parameter_t *) p_advertising_parameter;

            memcpy(
                &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.legacy_advertising_parameter,
                p_abs_legacy,
                sizeof(ble_abs_legacy_advertising_parameter_t));
            if (NULL != p_abs_legacy->p_peer_address)
            {
                memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                       p_abs_legacy->p_peer_address,
                       sizeof(ble_device_address_t));
                p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.legacy_advertising_parameter
                .p_peer_address = &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            ble_abs_non_connectable_advertising_parameter_t * p_abs_non_conn;
            p_abs_non_conn = (ble_abs_non_connectable_advertising_parameter_t *) p_advertising_parameter;

            memcpy(
                &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.non_connectable_advertising_parameter,
                p_abs_non_conn,
                sizeof(ble_abs_non_connectable_advertising_parameter_t));
            if (NULL != p_abs_non_conn->p_peer_address)
            {
                memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                       p_abs_non_conn->p_peer_address,
                       sizeof(ble_device_address_t));
                p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.
                non_connectable_advertising_parameter.p_peer_address =
                    &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
            }

            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function ble_abs_set_advertising_parameter() */

/*******************************************************************************************************************//**
 * GAP Event handler.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_gap_callback (uint16_t event_type, ble_status_t event_result, st_ble_evt_data_t * p_event_data)
{
    switch (event_type)
    {
        case BLE_GAP_EVENT_STACK_ON:
        {
            uint8_t              irk[BLE_GAP_IRK_SIZE];
            ble_device_address_t identity_address;

            R_BLE_GAP_SetLocIdInfo((st_ble_dev_addr_t *) (&identity_address), irk);

            break;
        }

        case BLE_GAP_EVENT_DISCONN_IND:
        {
            break;
        }

        case BLE_GAP_EVENT_ADV_REPT_IND:
        {
            if (FSP_SUCCESS != ble_abs_advertising_report_handler(gp_instance_ctrl, p_event_data))
            {
                return;
            }

            break;
        }

        case BLE_GAP_EVENT_ADV_PARAM_SET_COMP:
        {
            ble_abs_advertising_parameter_set_handler(gp_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_ADV_DATA_UPD_COMP:
        {
            ble_abs_advertising_data_set_handler(gp_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_CONN_IND:
        {
            ble_abs_set_advertising_status(gp_instance_ctrl, BLE_ABS_LEGACY_HDL, 0,
                                           (BLE_ABS_ADV_STATUS_ADV_FAST_START | BLE_ABS_ADV_STATUS_ADV_SLOW_START));

            R_BLE_GAP_StopAdv(0);

            break;
        }

        default:
        {
            break;
        }
    }

    gp_instance_ctrl->abs_gap_callback(event_type, event_result, p_event_data);
}                                      /* End of function ble_abs_gap_callback() */                                  /* End of function ble_abs_random_handler() */
