/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef RM_BLE_ABS_API_H
#define RM_BLE_ABS_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup BLE_ABS_API BLE ABS Interface
 * @brief Interface for Bluetooth Low Energy Abstraction functions.
 *
 * @section BLE_ABS_API_Summary Summary
 * The BLE ABS interface for the Bluetooth Low Energy Abstraction (BLE ABS) peripheral provides Bluetooth Low Energy Abstraction functionality.
 *
 * The Bluetooth Low Energy Abstraction interface can be implemented by:
 * - @ref BLE_ABS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_ble_api.h"
#include "r_flash_api.h"
#include "r_timer_api.h"

#include "fsp_common_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BLE_ABS_API_VERSION_MAJOR         (1U)
#define BLE_ABS_API_VERSION_MINOR         (0U)

#define BLE_ABS_ADVERTISING_PHY_LEGACY    (0x00) ///< Non-Connectable Legacy Advertising phy setting.

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Advertising Filter Policy */
typedef enum e_ble_abs_advertising_filter
{
    BLE_ABS_ADVERTISING_FILTER_ALLOW_ANY        = 0x00, ///< Receive a connect request from all devices.
    BLE_ABS_ADVERTISING_FILTER_ALLOW_WHITE_LIST = 0x01, ///< Receive a connect request from only the devices registered in White List.
} ble_abs_advertising_filter_t;

#define BLE_BD_ADDR_LEN    (0x06)

/** st_ble_device_address is the type of bluetooth device address(BD_ADDR). */
typedef struct st_ble_device_address
{
    uint8_t addr[BLE_BD_ADDR_LEN];     ///< bluetooth device address.
    uint8_t type;                      ///< the type of bluetooth device address.
} ble_device_address_t;

/** ble_gap_application_callback_t is the GAP Event callback function type. */
typedef void (* ble_gap_application_callback_t)(uint16_t event_type, ble_status_t event_result,
                                                st_ble_evt_data_t * p_event_data);

/** ble_vendor_specific_application_callback_t is the Vendor Specific Event callback function type. */
typedef void (* ble_vendor_specific_application_callback_t)(uint16_t event_type, ble_status_t event_result,
                                                            st_ble_vs_evt_data_t * p_event_data);

/** ble_gatt_server_application_callback_t is the GATT Server Event callback function type. */
typedef void (* ble_gatt_server_application_callback_t)(uint16_t event_type, ble_status_t event_result,
                                                        st_ble_gatts_evt_data_t * p_event_data);

/** ble_gatt_client_application_callback_t is the GATT Server Event callback function type. */
typedef void (* ble_gatt_client_application_callback_t)(uint16_t event_type, ble_status_t event_result,
                                                        st_ble_gattc_evt_data_t * p_event_data);

/** ble_gap_connection_parameter_t is Connection parameters included in connection interval, slave latency, supervision timeout, ce length. */
typedef struct st_ble_gap_connection_parameter
{
    uint16_t conn_intv_min;            ///< Minimum connection interval.
    uint16_t conn_intv_max;            ///< Maximum connection interval.
    uint16_t conn_latency;             ///< Slave latency.
    uint16_t sup_to;                   ///< Supervision timeout.
    uint16_t min_ce_length;            ///< Minimum CE Length.
    uint16_t max_ce_length;            ///< Maximum CE Length.
} ble_gap_connection_parameter_t;

/** ble_gap_connection_phy_parameter_t is Connection parameters per PHY. */
typedef struct st_ble_gap_connection_phy_parameter
{
    uint16_t scan_intv;                            ///< Scan interval.
    uint16_t scan_window;                          ///< Scan window.
    ble_gap_connection_parameter_t * p_conn_param; ///< Connection interval, slave latency, supervision timeout, and CE length.
} ble_gap_connection_phy_parameter_t;

/** Scan parameters per scan PHY. */
typedef struct st_ble_gap_scan_phy_parameter
{
    uint8_t  scan_type;                ///< Scan type.
    uint16_t scan_intv;                ///< Scan interval.
    uint16_t scan_window;              ///< Scan window.
} ble_gap_scan_phy_parameter_t;

/**  Parameters configured when scanning starts. */
typedef struct st_ble_gap_scan_on
{
    uint8_t  proc_type;                ///< Procedure type.
    uint8_t  filter_dups;              ///< Filter duplicates.
    uint16_t duration;                 ///< Scan duration.
    uint16_t period;                   ///< Scan period.
} ble_gap_scan_on_t;

/** Callback function parameter data */
typedef struct st_ble_abs_callback_args
{
    uint32_t       channel;            ///< Select a channel corresponding to the channel number of the hardware.
    ble_event_cb_t ble_abs_event;      ///< The event can be used to identify what caused the callback.
    void const   * p_context;          ///< Placeholder for user data.  Set in ble_abs_api_t::open function in ::ble_abs_cfg_t.
} ble_abs_callback_args_t;

/** BLE ABS control block.  Allocate an instance specific control block to pass into the BLE ABS API calls.
 * @par Implemented as
 * - ble_abs_instance_ctrl_t
 */
typedef void ble_abs_ctrl_t;

/** st_ble_abs_pairing_parameter_t includes the pairing parameters. */
typedef struct st_ble_abs_pairing_parameter
{
    uint8_t io_capabilitie_local_device; ///< IO capabilities of local device.
    uint8_t mitm_protection_policy;      ///< MITM protection policy.
    uint8_t secure_connection_only;      ///< Determine whether to accept only Secure Connections or not.
    uint8_t local_key_distribute;        ///< Type of keys to be distributed from local device.
    uint8_t remote_key_distribute;       ///< Type of keys which local device requests a remote device to distribute.
    uint8_t maximum_key_size;            ///< Maximum LTK size.
    uint8_t padding[2];                  ///< padding
} ble_abs_pairing_parameter_t;

/** GATT Server callback function and the priority. */
typedef struct st_ble_abs_gatt_server_callback_set
{
    ble_gatt_server_application_callback_t gatt_server_callback_function; ///< GATT Server callback function.
    uint8_t gatt_server_callback_priority;                                ///< The priority number of GATT Server callback function.
} ble_abs_gatt_server_callback_set_t;

/** GATT Client callback function and the priority. */
typedef struct st_ble_abs_gatt_client_callback_set
{
    ble_gatt_client_application_callback_t gatt_client_callback_function; ///< GATT Client callback function.
    uint8_t gatt_client_callback_priority;                                ///< The priority number of GATT Client callback function.
} ble_abs_gatt_client_callback_set_t;

/** st_ble_abs_legacy_advertising_parameter_t is the parameters for legacy advertising. */
typedef struct st_ble_abs_legacy_advertising_parameter
{
    /**
     *  @brief The remote device address.\n
     *  If the p_peer_address parameter is not NULL, Direct Connectable Advertising is performed to the remote address. \n
     *  If the p_peer_address parameter is NULL, Undirect Connectable Advertising is performed according to \n
     *  the advertising filter policy specified by the filter parameter.
     */
    ble_device_address_t * p_peer_address;

    /**
     *  @brief Advertising Data. \n
     *  If the p_advertising_data is specified as NULL, Advertising Data is not included in the advertising PDU.
     */
    uint8_t * p_advertising_data;

    /**
     *  @brief Scan Response Data. \n
     *  If the p_scan_response_data is specified as NULL, Scan Response Data is not included in the advertising PDU.
     */
    uint8_t * p_scan_response_data;

    /**
     *  @brief  Advertising with the fast_advertising_interval parameter continues for the period specified \n
     *  by the fast_period parameter.\n
     *  Time(ms) = fast_advertising_interval * 0.625. \n
     *  If the fast_period parameter is 0, this parameter is ignored.\n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t fast_advertising_interval;

    /**
     *  @brief After the elapse of the fast_period, advertising with the slow_advertising_interval parameter continues \n
     *  for the period specified by the slow_advertising_interval parameter.\n
     *  Time(ms) = slow_advertising_interval * 0.625. \n
     *  If the slow_advertising_interval parameter is 0, this parameter is ignored.\n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t slow_advertising_interval;

    /**
     *  @brief The period which advertising with the fast_advertising_interval parameter continues for. \n
     *  Time = duration * 10ms.\n
     *  After the elapse of the fast_advertising_period, @ref BLE_GAP_EVENT_ADV_OFF event notifies that the advertising has stopped.\n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the fast_advertising_period parameter is 0x0000, advertising with the fast_advertising_interval parameter is not performed.
     */
    uint16_t fast_advertising_period;

    /**
     *  @brief The period which advertising with the slow_advertising_interval parameter continues for. Time = duration * 10ms. \n
     *  After the elapse of the slow_advertising_period, @ref BLE_GAP_EVENT_ADV_OFF event notifies that the advertising has stopped. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the slow_advertising_period parameter is 0x0000, the advertising continues.
     */
    uint16_t slow_advertising_period;

    /**
     *  @brief Advertising data length(byte). \n
     *  Valid range is 0-31.  \n
     *  If the advertising_data_length is 0, Advertising Data is not included in the advertising PDU.
     */
    uint16_t advertising_data_length;

    /**
     *  @brief Scan response data length (in bytes). \n
     *  Scan Response Data(byte). \n
     *  Valid range is 0-31. \n
     *  If the scan_response_data_length is 0, Scan Response Data is not included in the advertising PDU.
     */
    uint16_t scan_response_data_length;

    /**
     *  @brief The channel map used for the advertising packet transmission. \n
     *  It is a bitwise OR of the following values.\n
     *    |  macro                    |   description   |
     *    |:--------------------------|:--------------- |
     *    | BLE_GAP_ADV_CH_37(0x01)   | Use 37 CH.      |
     *    | BLE_GAP_ADV_CH_38(0x02)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_39(0x04)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_ALL(0x07)  | Use 37 - 39 CH. |
     */
    uint8_t advertising_channel_map;

    /**
     *  @brief Advertising filter policy. \n
     *  If the p_peer_address parameter is NULL, the advertising is performed according to the advertising filter policy. \n
     *  If the p_peer_address parameter is not NULL, this parameter is ignored. \n
     *    |  macro                                              |   description                                                             |
     *    |:----------------------------------------------------|:------------------------------------------------------------------------- |
     *    | BLE_ABS_ADVERTISING_FILTER_ALLOW_ANY(0x00)          | Process scan and connection requests from all devices.                    |
     *    | BLE_ABS_ADVERTISING_FILTER_ALLOW_WHITE_LIST(0x01)   | Process scan and connection requests from only devices in the White List. |
     */
    uint8_t advertising_filter_policy;

    /**
     *  @brief  Own Bluetooth address type. \n Select one of the following.
     *    |  macro                              |   description                                                                                                                |
     *    |:------------------------------------|:---------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADDR_PUBLIC(0x00)           | Public Address                                                                                                               |
     *    | BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)    | Resolvable Private Address. \n If the IRK of local device has not been registered in Resolving List, public address is used. |
     */
    uint8_t own_bluetooth_address_type;
    uint8_t own_bluetooth_address[6];  ///< Own Bluetooth address.
    uint8_t padding[3];                ///< padding
} ble_abs_legacy_advertising_parameter_t;

/** st_ble_abs_extend_advertising_parameter_t is the parameters for extended advertising. */
typedef struct st_ble_abs_extend_advertising_parameter
{
    /**
     *  @brief The remote device address. \n
     *  If the p_addr parameter is not NULL, Direct Connectable Advertising is performed to the remote address. \n
     *  If the p_addr parameter is NULL, Undirect Connectable Advertising is performed \n
     *  according to the advertising filter policy specified by the filter parameter.
     */
    ble_device_address_t * p_peer_address;

    /**
     *  @brief Advertising data. If p_adv_data is specified as NULL, advertising data is not set.
     */
    uint8_t * p_advertising_data;

    /**
     *  @brief Advertising with the fast_advertising_interval parameter continues for \n
     *  the period specified by the fast_advertising_period parameter. \n
     *  Time(ms) = fast_advertising_interval * 0.625. \n
     *  If the fast_advertising_period parameter is 0, this parameter is ignored. \n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t fast_advertising_interval;

    /**
     *  @brief After the elapse of the fast_advertising_period, advertising with the slow_advertising_interval parameter \n
     *  continues for the period specified by the slow_advertising_period parameter. \n
     *  Time(ms) = fast_advertising_interval * 0.625. \n
     *  If the fast_advertising_period parameter is 0, this parameter is ignored. \n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t slow_advertising_interval;

    /**
     *  @brief The period which advertising with the fast_advertising_interval parameter continues for. \n
     *  Time = duration * 10ms. \n
     *  After the elapse of the fast_advertising_period, @ref BLE_GAP_EVENT_ADV_OFF event notifies that the advertising has stopped. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the fast_advertising_period parameter is 0x0000, the fast_advertising_interval parameter is ignored.
     */
    uint16_t fast_advertising_period;

    /**
     *  @brief The period which advertising with the slow_advertising_interval parameter continues for. \n
     *  Time = duration * 10ms. \n
     *  After the elapse of the slow_advertising_period, @ref BLE_GAP_EVENT_ADV_OFF event notifies that the advertising has stopped. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the slow_advertising_period parameter is 0x0000, the advertising continues.
     */
    uint16_t slow_advertising_period;

    /**
     *  @brief Advertising data length (in bytes). \n
     *  Valid range is 0-229. \n
     *  If the adv_data_length is 0, Advertising Data is not included in the advertising PDU.
     */
    uint16_t advertising_data_length;

    /**
     *  @brief The channel map used for the advertising packet transmission. \n
     *  It is a bitwise OR of the following values.
     *    |  macro                    |   description   |
     *    |:--------------------------|:--------------- |
     *    | BLE_GAP_ADV_CH_37(0x01)   | Use 37 CH.      |
     *    | BLE_GAP_ADV_CH_38(0x02)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_39(0x04)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_ALL(0x07)  | Use 37 - 39 CH. |
     */
    uint8_t advertising_channel_map;

    /**
     *  @brief Advertising filter policy. \n
     *  If the p_peer_address parameter is NULL, the advertising is performed according to the advertising filter policy. \n
     *  If the p_peer_address parameter is not NULL, this parameter is ignored. \n
     *    |  macro                                              |   description                                                             |
     *    |:----------------------------------------------------|:------------------------------------------------------------------------- |
     *    | BLE_ABS_ADVERTISING_FILTER_ALLOW_ANY(0x00)          | Process scan and connection requests from all devices.                    |
     *    | BLE_ABS_ADVERTISING_FILTER_ALLOW_WHITE_LIST(0x01)   | Process scan and connection requests from only devices in the White List. |
     */
    uint8_t advertising_filter_policy;

    /**
     *  @brief  Own Bluetooth address type. Select one of the following. \n
     *    |  macro                              |   description                                                                                                                |
     *    |:------------------------------------|:---------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADDR_PUBLIC(0x00)           | Public Address                                                                                                               |
     *    | BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)    | Resolvable Private Address. \n If the IRK of local device has not been registered in Resolving List, public address is used. |
     */
    uint8_t own_bluetooth_address_type;
    uint8_t own_bluetooth_address[6];  ///< Own Bluetooth address.

    /**
     *  @brief Primary advertising PHY. \n
     *  In this parameter, only 1M PHY and Coded PHY can be specified, and 2M PHY cannot be specified. \n
     *    |  macro                   |   description                                                                                                                                        |
     *    |:-------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADV_PHY_1M(0x01) | Use 1M PHY as Primary Advertising PHY. \n When the adv_prop_type field is Legacy Advertising PDU type, this field shall be set to BLE_GAP_ADV_PHY_1M.|
     *    | BLE_GAP_ADV_PHY_CD(0x03) | Use Coded PHY as Primary Advertising PHY. \n Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme().                                         |
     *
     */
    uint8_t primary_advertising_phy;

    /**
     *  @brief  Secondary advertising Phy. Select one of the following.
     *    |  macro                     |   description                                                                                                       |
     *    |:---------------------------|:------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADV_PHY_1M(0x01)   | Use 1M PHY as Secondary Advertising PHY.                                                                            |
     *    | BLE_GAP_ADV_PHY_2M(0x02)   | Use 2M PHY as Secondary Advertising PHY.                                                                            |
     *    | BLE_GAP_ADV_PHY_CD(0x03)   | Use Coded PHY(S=8) as Secondary Advertising PHY. \n Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme(). |
     */
    uint8_t secondary_advertising_phy;
    uint8_t padding[3];                ///< padding
} ble_abs_extend_advertising_parameter_t;

/** st_ble_abs_non_connectable_advertising_parameter_t is the parameters for non-connectable advertising. */
typedef struct st_ble_abs_non_connectable_advertising_parameter
{
    /**
     *  @brief The remote device address. \n
     *  If the p_peer_address parameter is not NULL, Direct Connectable Advertising is performed to the remote address. \n
     *  If the p_peer_address parameter is NULL, Undirect Connectable Advertising is performed \n
     *  according to the advertising filter policy specified by the filter parameter.
     */
    ble_device_address_t * p_peer_address;

    /**
     *  @brief Advertising data. If p_adv_data is specified as NULL, advertising data is not set.
     */
    uint8_t * p_advertising_data;

    /**
     *  @brief Advertising with the advertising_interval parameter continues for the period specified by the duration parameter.\n
     *  Time(ms) = advertising_interval * 0.625. \n
     *  If the duration parameter is 0x0000, the advertising with the advertising_interval parameter continue. \n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t advertising_interval;

    /**
     *  @brief The period which advertising with the advertising_interval parameter continues for. \n
     *  Time = advertising_duration * 10ms.\n
     *  After the elapse of the advertising_duration, @ref BLE_GAP_EVENT_ADV_OFF event notifies that the advertising has stopped. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the advertising_duration parameter is 0x0000, the advertising continues.
     */
    uint16_t advertising_duration;

    /**
     *  @brief Advertising data length (in bytes).\n
     *  If the primary_advertising_phy parameter is @ref BLE_ABS_ADVERTISING_PHY_LEGACY(0x00), the valid range is 0-31. \n
     *  If the primary_advertising_phy parameter is the other values, the valid range is 0-1650. \n
     *  If the advertising_data_length parameter is 0, Advertising Data is not included in the advertising PDU.
     */
    uint16_t advertising_data_length;

    /**
     *  @brief The channel map used for the advertising packet transmission. \n
     *  It is a bitwise OR of the following values.
     *    |  macro                    |   description   |
     *    |:--------------------------|:--------------- |
     *    | BLE_GAP_ADV_CH_37(0x01)   | Use 37 CH.      |
     *    | BLE_GAP_ADV_CH_38(0x02)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_39(0x04)   | Use 38 CH.      |
     *    | BLE_GAP_ADV_CH_ALL(0x07)  | Use 37 - 39 CH. |
     */
    uint8_t advertising_channel_map;

    /**
     *  @brief  Own Bluetooth address type. Select one of the following. \n
     *    |  macro                              |   description                                                                                                                |
     *    |:------------------------------------|:---------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADDR_PUBLIC(0x00)           | Public Address                                                                                                               |
     *    | BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)    | Resolvable Private Address. \n If the IRK of local device has not been registered in Resolving List, public address is used. |
     */
    uint8_t own_bluetooth_address_type;
    uint8_t own_bluetooth_address[6];  ///< Own Bluetooth address.

    /**
     *  @brief Primary advertising PHY. \n
     *  In this parameter, only 1M PHY and Coded PHY can be specified, and 2M PHY cannot be specified. \n
     *    |  macro                               |   description                                                                                                                                                             |
     *    |:-------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_ABS_ADVERTISING_PHY_LEGACY(0x00) | Use 1M PHY as Primary Advertising PHY for Non-Connectable Legacy Advertising. \n If Periodic Advertising is performed, this value shall not set to the adv_phy parameter. |
     *    | BLE_GAP_ADV_PHY_1M(0x01)             | Use 1M PHY as Primary Advertising PHY. \n When the adv_prop_type field is Legacy Advertising PDU type, this field shall be set to BLE_GAP_ADV_PHY_1M.                     |
     *    | BLE_GAP_ADV_PHY_CD(0x03)             | Use Coded PHY as Primary Advertising PHY. \n Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme().                                                              |
     */
    uint8_t primary_advertising_phy;

    /**
     *  @brief  Secondary advertising Phy. Select one of the following.
     *    |  macro                     |   description                                                                                                       |
     *    |:---------------------------|:------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_ADV_PHY_1M(0x01)   | Use 1M PHY as Secondary Advertising PHY.                                                                            |
     *    | BLE_GAP_ADV_PHY_2M(0x02)   | Use 2M PHY as Secondary Advertising PHY.                                                                            |
     *    | BLE_GAP_ADV_PHY_CD(0x03)   | Use Coded PHY(S=8) as Secondary Advertising PHY. \n Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme(). |
     */
    uint8_t secondary_advertising_phy;
    uint8_t padding[2];                ///< padding
} ble_abs_non_connectable_advertising_parameter_t;

/** st_ble_abs_periodic_advertising_parameter_t is the parameters for periodic advertising. */
typedef struct st_ble_abs_periodic_advertising_parameter
{
    /**
     *  @brief Advertising parameters.
     */
    ble_abs_non_connectable_advertising_parameter_t advertising_parameter;

    /**
     *  @brief Periodic advertising data. If p_perd_adv_data is specified as NULL, periodic advertising data is not set.
     */
    uint8_t * p_periodic_advertising_data;

    /**
     *  @brief Periodic advertising interval. \n
     *  Time(ms) = periodic_advertising_interval * 1.25. \n
     *  Valid range is 0x0006 - 0xFFFF.
     */
    uint16_t periodic_advertising_interval;

    /**
     *  @brief Periodic advertising data length (in bytes). \n
     *  Valid range is 0 - 1650. \n
     *  If the periodic_advertising_data_length is 0, Periodic Advertising Data is not included in the advertising PDU.
     */
    uint16_t periodic_advertising_data_length;
} ble_abs_periodic_advertising_parameter_t;

/** st_ble_abs_scan_phy_parameter_t is the phy parameters for scan. */
typedef struct st_ble_abs_scan_phy_parameter
{
    /**
     *  @brief Fast scan interval. \n
     *  Interval(ms) = fast_scan_interval * 0.625. \n
     *  Valid range is 0x0004 - 0xFFFF.
     *
     */
    uint16_t fast_scan_interval;

    /**
     *  @brief Slow Scan interval. \n
     *  Slow Scan interval(ms) = slow_scan_interval * 0.625. \n
     *  Valid range is 0x0004 - 0xFFFF.
     */
    uint16_t slow_scan_interval;

    /**
     *  @brief Fast Scan window. \n
     *  Fast Scan window(ms) = fast_scan_window * 0.625. \n
     *  Valid range is 0x0004 - 0xFFFF.
     */
    uint16_t fast_scan_window;

    /**
     *  @brief Slow Scan window. \n
     *  Slow Scan window(ms) = slow_scan_window * 0.625. \n
     *  Valid range is 0x0004 - 0xFFFF.
     */
    uint16_t slow_scan_window;

    /**
     *  @brief Scan type.
     *    |  macro                       |   description   |
     *    |:-----------------------------|:--------------- |
     *    | BLE_GAP_SCAN_PASSIVE(0x00)   | Passive Scan.   |
     *    | BLE_GAP_SCAN_ACTIVE(0x01)    | Active Scan.    |
     */
    uint8_t scan_type;

    /**
     *  @brief padding.
     */
    uint8_t padding[3];
} ble_abs_scan_phy_parameter_t;

/** st_ble_abs_scan_parameter_t is the parameters for scan. */
typedef struct st_ble_abs_scan_parameter
{
    /**
     *  @brief Scan parameters for receiving the advertising packets in 1M PHY. \n
     *  In case of not receiving the advertising packets in 1M PHY, this field is specified as NULL. \n
     *  p_phy_parameter_1M or p_phy_parameter_coded field shall be set to scan parameters.
     */
    ble_abs_scan_phy_parameter_t * p_phy_parameter_1M;

    /**
     *  @brief Scan parameters for receiving the advertising packets in Coded PHY. \n
     *  In case of not receiving the advertising packets in Coded PHY, this field is specified as NULL. \n
     *  p_phy_parameter_1M or p_phy_parameter_coded field shall be set to scan parameters.
     */
    ble_abs_scan_phy_parameter_t * p_phy_parameter_coded;

    /**
     *  @brief Data for Advertising Data filtering. \n
     *  The p_filter_data parameter is used for the advertising data in single advertising report. \n
     *  The advertising data composed of multiple advertising reports is not filtered by this parameter. \n
     *  If the p_filter_data parameter is specified as NULL, the filtering is not done.
     */
    uint8_t * p_filter_data;

    /**
     *  @brief The period which scan with the fast scan interval/fast scan window continues for. \n
     *  Time(ms) = fast_scan_period * 10. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the fast_scan_period parameter is 0x0000, scan with the fast scan interval/fast scan window is not performed. \n
     *  After the elapse of the fast_scan_period, @ref BLE_GAP_EVENT_SCAN_TO event notifies that the scan has stopped.
     */
    uint16_t fast_scan_period;

    /**
     *  @brief The period which scan with the slow scan interval/slow scan window continues for. \n
     *  Time = slow_scan_period * 10ms. \n
     *  Valid range is 0x0000 - 0xFFFF. \n
     *  If the slow_scan_period parameter is 0x0000, the scan continues. \n
     *  After the elapse of the slow_scan_period, @ref BLE_GAP_EVENT_SCAN_TO event notifies that the scan has stopped.
     */
    uint16_t slow_scan_period;

    /**
     *  @brief The length of the data specified by the p_filter_data parameter. \n
     *  Valid range is 0x0000-0x0010. \n
     *  If the filter_data_length parameter is 0, the filtering is not done.
     */
    uint16_t filter_data_length;

    /**
     *  @brief Scan Filter Policy. Select one of the following.
     *    |  macro                                            |   description                                                                                                                                                                                                                                                                                                                                                                                                               |
     *    |:--------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_SCAN_ALLOW_ADV_ALL(0x00)                  | Accept all advertising and scan response PDUs except directed advertising PDUs not addressed to local device.                                                                                                                                                                                                                                                                                                               |
     *    | BLE_GAP_SCAN_ALLOW_ADV_WLST(0x01)                 | Accept only advertising and scan response PDUs from remote devices whose address is registered in the White List. \n Directed advertising PDUs which are not addressed to local device is ignored.                                                                                                                                                                                                                          |
     *    | BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED(0x02)      | Accept all advertising and scan response PDUs except directed advertising PDUs whose the target address is identity address but doesn't address local device. However directed advertising PDUs whose the target address is the local resolvable private address are accepted.                                                                                                                                              |
     *    | BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED_WLST(0x03) | Accept all advertising and scan response PDUs. The following are excluded.  \n \arg Advertising and scan response PDUs where the advertiser's identity address is not in the White List. \n \arg Directed advertising PDUs whose the target address is identity address but doesn't address local device. However directed advertising PDUs whose the target address is the local resolvable private address are accepted.  |
     */
    uint8_t device_scan_filter_policy;

    /**
     *  @brief Filter duplicates. \n
     *  Maximum number of filtered devices is 8. \n
     *  The 9th and subsequent devices are not filtered by this parameter.  \n
     *    |  macro                                            |   description                                            |
     *    |:--------------------------------------------------|:-------------------------------------------------------- |
     *    | BLE_GAP_SCAN_FILT_DUPLIC_DISABLE(0x00)            | Duplicate filter disabled.                               |
     *    | BLE_GAP_SCAN_FILT_DUPLIC_ENABLE(0x01)             | Duplicate filter enabled.                                |
     *    | BLE_GAP_SCAN_FILT_DUPLIC_ENABLE_FOR_PERIOD(0x02)) | Duplicate filtering enabled, reset for each scan period. |
     *
     */
    uint8_t filter_duplicate;

    /**
     *  @brief The AD type of the data specified by the p_filter_data parameter.\n
     *  The AD type identifier values are defined in Bluetooth SIG Assigned Number \n
     *  (https://www.bluetooth.com/specifications/assigned-numbers).
     */
    uint8_t filter_ad_type;

    /**
     *  @brief Padding
     */
    uint8_t padding[3];
} ble_abs_scan_parameter_t;

/** st_ble_abs_connection_phy_parameter_t is the phy parameters for create connection. */
typedef struct st_ble_abs_connection_phy_parameter
{
    /**
     *  @brief Connection interval. \n
     *  Time(ms) = connection_interval * 1.25. \n
     *  Valid range is 0x0006 - 0x0C80.
     */
    uint16_t connection_interval;

    /**
     *  @brief Slave latency. \n
     *  Valid range is 0x0000 - 0x01F3.
     */
    uint16_t connection_slave_latency;

    /**
     *  @brief Supervision timeout. \n
     *  Time(ms) = supervision_timeout * 10. \n
     *  Valid range is 0x000A - 0x0C80.
     */
    uint16_t supervision_timeout;

    /**
     *  @brief Padding
     */
    uint8_t padding[2];
} ble_abs_connection_phy_parameter_t;

/** st_ble_abs_connection_parameter_t is the parameters for create connection. */
typedef struct st_ble_abs_connection_parameter
{
    /**
     *  @brief Connection interval, slave latency, supervision timeout for 1M PHY. \n
     *  The p_connection_phy_parameter_1M is specified as NULL, a connection request is not sent with 1M PHY.
     */
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_1M;

    /**
     *  @brief Connection interval, slave latency, supervision timeout for 2M PHY. \n
     *  The p_connection_phy_parameter_2M is specified as NULL, a connection request is not sent with 2M PHY.
     */
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_2M;

    /**
     *  @brief Connection interval, slave latency, supervision timeout for Coded PHY.  \n
     *  The p_connection_phy_parameter_coded is specified as NULL, a connection request is not sent with Coded PHY.
     */
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_coded;

    /**
     *  @brief Address of the device to be connected. \n
     *  If the filter field is @ref BLE_GAP_INIT_FILT_USE_WLST(0x01), this parameter is ignored.
     */
    ble_device_address_t * p_device_address;

    /**
     *  @brief The filter field specifies whether the White List is used or not, when connecting with a remote device.\n
     *    |  macro                           |   description                                                                                                                      |
     *    |:---------------------------------|:---------------------------------------------------------------------------------------------------------------------------------- |
     *    | BLE_GAP_INIT_FILT_USE_ADDR(0x00) | White List is not used. \n The remote device to be connected is specified by the p_addr field is used.                             |
     *    | BLE_GAP_INIT_FILT_USE_WLST(0x01) | White List is used. \n The remote device registered in White List is connected with local device. \n The p_addr field is ignored.  |
     */
    uint8_t filter_parameter;

    /**
     *  @brief The time(sec) to cancel the create connection request. \n
     *  Valid range is 0 <= connection_timeout <= 10. \n
     *  If the connection_timeout field is 0, the create connection request is not canceled. \n
     */
    uint8_t connection_timeout;

    /**
     *  @brief Padding
     */
    uint8_t padding[2];
} ble_abs_connection_parameter_t;

/** BLE ABS configuration parameters. */
typedef struct st_ble_abs_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                       ///< Select a channel corresponding to the channel number of the hardware.
    ble_gap_application_callback_t             gap_callback;                ///< GAP callback function.
    ble_vendor_specific_application_callback_t vendor_specific_callback;    ///< Vendor Specific callback function.
    ble_abs_gatt_server_callback_set_t       * p_gatt_server_callback_list; ///< GATT Server callback set.
    uint8_t gatt_server_callback_list_number;                               ///< The number of GATT Server callback functions.
    ble_abs_gatt_client_callback_set_t * p_gatt_client_callback_list;       ///< GATT Client callback set.
    uint8_t gatt_client_callback_list_number;                               ///< The number of GATT Client callback functions.
    ble_abs_pairing_parameter_t * p_pairing_parameter;                      ///< Pairing parameters.

    flash_instance_t const * p_flash_instance;                              ///< Pointer to flash instance.
    timer_instance_t const * p_timer_instance;                              ///< Pointer to timer instance.

    void (* p_callback)(ble_abs_callback_args_t * p_args);                  ///< Callback provided when a BLE ISR occurs.
    void const * p_context;                                                 ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                                  ///< Placeholder for user extension.
} ble_abs_cfg_t;

/** BLE ABS functions implemented at the HAL layer will follow this API. */
typedef struct st_ble_abs_api
{
    /** Initialize the BLE ABS in register start mode.
     * @par Implemented as
     * - RM_BLE_ABS_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ble_abs_ctrl_t * const p_ctrl, ble_abs_cfg_t const * const p_cfg);

    /** Close the BLE ABS.
     * @par Implemented as
     * - RM_BLE_ABS_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ble_abs_ctrl_t * const p_ctrl);

    /** Close the BLE ABS.
     * @par Implemented as
     * - RM_BLE_ABS_Reset()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  init_callback callback function to initialize Host Stack.
     */
    fsp_err_t (* reset)(ble_abs_ctrl_t * const p_ctrl, ble_event_cb_t init_callback);

    /** Return the version of the driver.
     * @par Implemented as
     * - RM_BLE_ABS_VersionGet()
     * @param[out] p_data       Memory address to return version information to.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_data);

    /** Start Legacy Connectable Advertising.
     * @par Implemented as
     * - RM_BLE_ABS_StartLegacyAdvertising()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_advertising_parameter        Pointer to Advertising parameters for Legacy Advertising.
     */
    fsp_err_t (* startLegacyAdvertising)(ble_abs_ctrl_t * const                               p_ctrl,
                                         ble_abs_legacy_advertising_parameter_t const * const p_advertising_parameter);

    /** Start Extended Connectable Advertising.
     * @par Implemented as
     * - RM_BLE_ABS_StartExtendedAdvertising()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_advertising_parameter        Pointer to Advertising parameters for extend Advertising.
     */
    fsp_err_t (* startExtendedAdvertising)(ble_abs_ctrl_t * const                               p_ctrl,
                                           ble_abs_extend_advertising_parameter_t const * const p_advertising_parameter);

    /** Start Non-Connectable Advertising.
     * @par Implemented as
     * - RM_BLE_ABS_StartNonConnectableAdvertising()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_advertising_parameter        Pointer to Advertising parameters for non-connectable Advertising.
     */
    fsp_err_t (* startNonConnectableAdvertising)(ble_abs_ctrl_t * const p_ctrl,
                                                 ble_abs_non_connectable_advertising_parameter_t const * const
                                                 p_advertising_parameter);

    /** Start Periodic Advertising.
     * @par Implemented as
     * - RM_BLE_ABS_StartPeriodicAdvertising()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_advertising_parameter        Pointer to Advertising parameters for periodic Advertising.
     */
    fsp_err_t (* startPeriodicAdvertising)(ble_abs_ctrl_t * const p_ctrl,
                                           ble_abs_periodic_advertising_parameter_t const * const
                                           p_advertising_parameter);

    /** Start scanning.
     * @par Implemented as
     * - RM_BLE_ABS_StartScanning()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_scan_parameter        Pointer to scan parameter.
     */
    fsp_err_t (* startScanning)(ble_abs_ctrl_t * const p_ctrl, ble_abs_scan_parameter_t const * const p_scan_parameter);

    /** Request create connection.
     * @par Implemented as
     * - RM_BLE_ABS_CreateConnection()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_connection_parameter        Pointer to connection parameter.
     */
    fsp_err_t (* createConnection)(ble_abs_ctrl_t * const                       p_ctrl,
                                   ble_abs_connection_parameter_t const * const p_connection_parameter);

    /** Configure local device privacy.
     * @par Implemented as
     * - RM_BLE_ABS_SetLocalPrivacy()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_lc_irk        Pointer to IRK to be registered in the resolving list.
     * @param[in]  privacy_mode        privacy_mode privacy mode.
     */
    fsp_err_t (* setLocalPrivacy)(ble_abs_ctrl_t * const p_ctrl, uint8_t const * const p_lc_irk, uint8_t privacy_mode);

    /** Start pairing or encryption.
     * @par Implemented as
     * - RM_BLE_ABS_StartAuthentication()
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  connection_handle        Connection handle identifying the remote device.
     */
    fsp_err_t (* startAuthentication)(ble_abs_ctrl_t * const p_ctrl, uint16_t connection_handle);
} ble_abs_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ble_abs_instance
{
    ble_abs_ctrl_t      * p_ctrl;      ///< Pointer to the control structure for this instance
    ble_abs_cfg_t const * p_cfg;       ///< Pointer to the configuration structure for this instance
    ble_abs_api_t const * p_api;       ///< Pointer to the API structure for this instance
} ble_abs_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup BLE_ABS_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
