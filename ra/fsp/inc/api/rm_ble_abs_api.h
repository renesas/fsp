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
    ble_device_address_t * p_peer_address;             ///< Peer address.
    uint8_t              * p_advertising_data;         ///< Advertising data. If p_advertising_data is specified as NULL, advertising data is not set.
    uint8_t              * p_scan_response_data;       ///< Scan response data. If p_scan_response_data is specified as NULL, scan response data is not set.
    uint32_t               fast_advertising_interval;  ///< Fast advertising interval.
    uint32_t               slow_advertising_interval;  ///< Slow advertising interval.
    uint16_t               fast_advertising_period;    ///< Fast advertising period.
    uint16_t               slow_advertising_period;    ///< Slow advertising period.
    uint16_t               advertising_data_length;    ///< Advertising data length (in bytes).
    uint16_t               scan_response_data_length;  ///< Scan response data length (in bytes).
    uint8_t                advertising_channel_map;    ///< Channel Map.
    uint8_t                advertising_filter_policy;  ///< Advertising Filter Policy.
    uint8_t                own_bluetooth_address_type; ///< Own Bluetooth address type.
    uint8_t                own_bluetooth_address[6];   ///< Own Bluetooth address.
    uint8_t                padding[3];                 ///< padding
} ble_abs_legacy_advertising_parameter_t;

/** st_ble_abs_extend_advertising_parameter_t is the parameters for extended advertising. */
typedef struct st_ble_abs_extend_advertising_parameter
{
    ble_device_address_t * p_peer_address;             ///< Peer address.
    uint8_t              * p_advertising_data;         ///< Advertising data. If p_advertising_data is specified as NULL, advertising data is not set.
    uint32_t               fast_advertising_interval;  ///< Fast advertising interval.
    uint32_t               slow_advertising_interval;  ///< Slow advertising interval.
    uint16_t               fast_advertising_period;    ///< Fast advertising period.
    uint16_t               slow_advertising_period;    ///< Slow advertising period.
    uint16_t               advertising_data_length;    ///< Advertising data length (in bytes).
    uint8_t                advertising_channel_map;    ///< Channel Map.
    uint8_t                advertising_filter_policy;  ///< Advertising Filter Policy.
    uint8_t                own_bluetooth_address_type; ///< Own Bluetooth address type.
    uint8_t                own_bluetooth_address[6];   ///< Own Bluetooth address.
    uint8_t                primary_advertising_phy;    ///< Primary ADV PHY.
    uint8_t                secondary_advertising_phy;  ///< Secondary ADV Max Skip.
    uint8_t                padding[3];                 ///< padding
} ble_abs_extend_advertising_parameter_t;

/** st_ble_abs_non_connectable_advertising_parameter_t is the parameters for non-connectable advertising. */
typedef struct st_ble_abs_non_connectable_advertising_parameter
{
    /** Peer address. */
    ble_device_address_t * p_peer_address;             ///< Peer address.
    uint8_t              * p_advertising_data;         ///< Advertising data. If p_advertising_data is specified as NULL, advertising data is not set.
    uint32_t               advertising_interval;       ///< Advertising interval.
    uint16_t               advertising_duration;       ///< Advertising duration.
    uint16_t               advertising_data_length;    ///< Advertising data length (in bytes).
    uint8_t                advertising_channel_map;    ///< Channel Map.
    uint8_t                own_bluetooth_address_type; ///< Own Bluetooth address type.
    uint8_t                own_bluetooth_address[6];   ///< Own Bluetooth address.
    uint8_t                primary_advertising_phy;    ///< Primary ADV PHY.
    uint8_t                secondary_advertising_phy;  ///< Secondary ADV Max Skip.
    uint8_t                padding[2];                 ///< padding
} ble_abs_non_connectable_advertising_parameter_t;

/** st_ble_abs_periodic_advertising_parameter_t is the parameters for periodic advertising. */
typedef struct st_ble_abs_periodic_advertising_parameter
{
    ble_abs_non_connectable_advertising_parameter_t advertising_parameter; ///< Advertising parameters.
    uint8_t * p_periodic_advertising_data;                                 ///< Periodic advertising data. If p_perd_adv_data is specified as NULL, periodic advertising data is not set.
    uint16_t  periodic_advertising_interval;                               ///< Periodic advertising interval. Time(ms) = perd_intv_min * 1.25.
    uint16_t  periodic_advertising_data_length;                            ///< Periodic advertising data length (in bytes).
} ble_abs_periodic_advertising_parameter_t;

/** st_ble_abs_scan_phy_parameter_t is the phy parameters for scan. */
typedef struct st_ble_abs_scan_phy_parameter
{
    uint16_t fast_scan_interval;       ///< Fast scan interval. Interval(ms) = fast_scan_interval * 0.625.
    uint16_t slow_scan_interval;       ///< Slow scan interval. Interval(ms) = slow_scan_interval * 0.625.
    uint16_t fast_scan_window;         ///< Fast scan window. Window(ms) = fast_scan_window * 0.625.
    uint16_t slow_scan_window;         ///< Slow scan window. Window(ms) = slow_scan_window * 0.625.
    uint8_t  scan_type;                ///< Scan type.
    uint8_t  padding[3];               ///< padding.
} ble_abs_scan_phy_parameter_t;

/** st_ble_abs_scan_parameter_t is the parameters for scan. */
typedef struct st_ble_abs_scan_parameter
{
    ble_abs_scan_phy_parameter_t * p_phy_parameter_1M;    ///< 1M phy parameters for scan.
    ble_abs_scan_phy_parameter_t * p_phy_parameter_coded; ///< Coded phy parameters for scan.
    uint8_t * p_filter_data;                              ///< Filter data.
    uint16_t  fast_scan_period;                           ///< Fast scan period (in sec).
    uint16_t  slow_scan_period;                           ///< Slow scan period (in sec).
    uint16_t  filter_data_length;                         ///< Filter data length.
    uint8_t   device_scan_filter_policy;                  ///< Scan Filter Policy.
    uint8_t   filter_duplicate;                           ///< Filter duplicates.
    uint8_t   filter_ad_type;                             ///< The AD type of the data specified by the p_filter_data parameter.
    uint8_t   padding[3];                                 ///< Padding
} ble_abs_scan_parameter_t;

/** st_ble_abs_connection_phy_parameter_t is the phy parameters for create connection. */
typedef struct st_ble_abs_connection_phy_parameter
{
    uint16_t connection_interval;      ///< Connection interval. Time(ms) = connection_interval * 1.25.
    uint16_t connection_slave_latency; ///< Slave latency.
    uint16_t supervision_timeout;      ///< Supervision timeout.
    uint8_t  padding[2];               ///< Padding
} ble_abs_connection_phy_parameter_t;

/** st_ble_abs_connection_parameter_t is the parameters for create connection. */
typedef struct st_ble_abs_connection_parameter
{
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_1M;    ///< 1M phy parameters for create connection.
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_2M;    ///< 2M phy parameters for create connection.
    ble_abs_connection_phy_parameter_t * p_connection_phy_parameter_coded; ///< Coded phy parameters for create connection.
    ble_device_address_t               * p_device_address;                 ///< Remote device address.
    uint8_t filter_parameter;                                              ///< The filter parameter specifies whether the White List is used or not.
    uint8_t connection_timeout;                                            ///< GAP Event parameters. This parameter differs in each GAP Event.
    uint8_t padding[2];                                                    ///< Padding
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
