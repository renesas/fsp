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

#ifndef RM_BLE_MESH_BEARER_API_H
#define RM_BLE_MESH_BEARER_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_BEARER_API BLE Mesh Bearer Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Bearer functions.
 *
 * @section   RM_BLE_MESH_BEARER_API_Summary Summary
 * The BLE Mesh Bearer interface for the Bluetooth Low Energy Mesh Bearer (BLE MESH BEARER) peripheral provides Bluetooth Low Energy Mesh Bearer functionality.
 *
 * The Bluetooth Low Energy Mesh Bearer interface can be implemented by:
 * - @ref RM_BLE_MESH_BEARER
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

#include "rm_ble_mesh_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Invalid Bearer handle identifier */
#define RM_BLE_MESH_BEARER_HANDLE_INVALID                    0xFF

/** Maximum PDU size for data received over bearer */
#define RM_BLE_MESH_BEARER_MAX_PDU_SIZE                      65

/** GATT Bearer Message Type Masks */
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK_BIT_OFFSET    6
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK               (0xC0)
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_NETWORK_T_MASK       ((MESH_GATT_TYPE_NETWORK <<                            \
                                                               RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK_BIT_OFFSET) & \
                                                              (BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK))
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_BEACON_T_MASK        ((MESH_GATT_TYPE_BEACON <<                             \
                                                               RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK_BIT_OFFSET) & \
                                                              (BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK))
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_PROXY_T_MASK         ((MESH_GATT_TYPE_PROXY <<                              \
                                                               RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK_BIT_OFFSET) & \
                                                              (BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK))
#define RM_BLE_MESH_BEARER_SUBTYPE_GATT_PROV_T_MASK          ((MESH_GATT_TYPE_PROV <<                               \
                                                               RM_BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK_BIT_OFFSET) & \
                                                              (BLE_MESH_BEARER_SUBTYPE_GATT_T_MASK))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Bearer Interface Event */
typedef enum e_rm_ble_mesh_bearer_interface_event
{
    /** Bearer Interface Event - Down */
    RM_BLE_MESH_BEARER_INTERFACE_EVENT_DOWN = 0x00,

    /** Bearer Interface Event - Up */
    RM_BLE_MESH_BEARER_INTERFACE_EVENT_UP = 0x01,

    /** Bearer Interface Event - Data */
    RM_BLE_MESH_BEARER_INTERFACE_EVENT_DATA = 0x02,

    /** Bearer Interface Event - Proxy Data */
    RM_BLE_MESH_BEARER_INTERFACE_EVENT_PROXY_DATA = 0x03,
} rm_ble_mesh_bearer_interface_event_t;

/** Bearer Beacon Operations */
typedef enum e_rm_ble_mesh_bearer_beacon_operation
{
    /** Bearer Beacon Operations - Broadcast */
    RM_BLE_MESH_BEARER_BEACON_OPERATION_BROADCAST = 0x00,

    /** Bearer Beacon Operations - Observe */
    RM_BLE_MESH_BEARER_BEACON_OPERATION_OBSERVE = 0x01,
} rm_ble_mesh_bearer_beacon_operation_t;

/** Bearer Beacon Actions */
typedef enum e_rm_ble_mesh_bearer_beacon_action
{
    /** Bearer Beacon Actions - Disable */
    RM_BLE_MESH_BEARER_BEACON_ACTION_DISABLE = 0x00,

    /** Bearer Beacon Actions - Enable */
    RM_BLE_MESH_BEARER_BEACON_ACTION_ENABLE = 0x01,
} rm_ble_mesh_bearer_beacon_action_t;

/** Bearer Server Client Roles */
typedef enum e_rm_ble_mesh_bearer_role
{
    /** Bearer Client Role */
    RM_BLE_MESH_BEARER_ROLE_CLIENT = 0x00,

    /** Bearer Server Role */
    RM_BLE_MESH_BEARER_ROLE_SERVER = 0x01,

    /** Bearer Role - Invalid */
    RM_BLE_MESH_BEARER_ROLE_INVALID = 0xFF,
} rm_ble_mesh_bearer_role_t;

/** Bearer Transmit and Receive operation modes */
typedef enum e_rm_ble_mesh_bearer_operation_mode
{
    /** Bearer transmit operation mode */
    RM_BLE_MESH_BEARER_OPERATION_MODE_TX = 0x01,

    /** Bearer receive operation mode */
    RM_BLE_MESH_BEARER_OPERATION_MODE_RX = 0x02,
} rm_ble_mesh_bearer_operation_mode_t;

/** Bearer Transmit and Receive operation modes */
typedef enum e_rm_ble_mesh_bearer_ntf_callback_result
{
    /** Callback success*/
    RM_BLE_MESH_BEARER_NTF_CALLBACK_RESULT_SUCCESS = 0x0,

    /** Callback failure*/
    RM_BLE_MESH_BEARER_NTF_CALLBACK_RESULT_FAILURE = 0xFFFFFFFF,
} rm_ble_mesh_bearer_ntf_callback_result_t;

/** Bearer handle identifier */
typedef uint8_t rm_ble_mesh_bearer_handle_t;

/** Bearer Type definitions */
typedef enum e_rm_ble_mesh_bearer_type
{
    /** Beacon Bearer */
    RM_BLE_MESH_BEARER_TYPE_BCON,

    /** Advertising Bearer */
    RM_BLE_MESH_BEARER_TYPE_ADV,

    /** Provisioning Advertising Bearer */
    RM_BLE_MESH_BEARER_TYPE_PB_ADV,

    /** GATT Bearer */
    RM_BLE_MESH_BEARER_TYPE_GATT,

    /** Provisioning GATT Bearer */
    RM_BLE_MESH_BEARER_TYPE_PB_GATT,

    /** Number of bearers supported */
    RM_BLE_MESH_BEARER_COUNT
} rm_ble_mesh_bearer_type_t;

/** Bearer Beacon type definitions */
typedef enum e_rm_ble_mesh_bearer_beacon_type
{
    /** Unprovisioned Device Beacon */
    RM_BLE_MESH_BEARER_BEACON_TYPE_UNPROV_DEVICE,

    /** Secure Network Beacon */
    RM_BLE_MESH_BEARER_BEACON_TYPE_SECURE_NET,

    /** Unprovisioned Device Beacon over GATT bearer */
    RM_BLE_MESH_BEARER_BEACON_TYPE_GATT_UNPROV_DEVICE,

    /** Proxy beacon with Network ID */
    RM_BLE_MESH_BEARER_BEACON_TYPE_PROXY_NETID,

    /** Proxy beacon with Node Identity */
    RM_BLE_MESH_BEARER_BEACON_TYPE_PROXY_NODEID,

    /** Number of Beacon types */
    RM_BLE_MESH_BEARER_BEACON_COUNT
} rm_ble_mesh_bearer_beacon_type_t;

/** Bearer information to register */
typedef struct st_rm_ble_mesh_bearer_info
{
    /** Bearer Information */
    rm_ble_mesh_buffer_t * binfo;

    /** Data Send routine */
    fsp_err_t (* bearer_send)(rm_ble_mesh_bearer_handle_t *, uint8_t, void *, uint16_t);

    /** Data Receive routine */
    void (* bearer_recv)(rm_ble_mesh_bearer_handle_t *, uint8_t *, uint16_t, rm_ble_mesh_buffer_t * info);

    /** Bearer Sleep Interface */
    void (* bearer_sleep)(rm_ble_mesh_bearer_handle_t *);

    /** Bearer Wakeup Interface */
    void (* bearer_wakeup)(rm_ble_mesh_bearer_handle_t *, uint8_t mode);
} rm_ble_mesh_bearer_info_t;

/** Bearer Beacon type data structure */
typedef struct st_rm_ble_mesh_bearer_beacon_info
{
    /**
     * Beacon Action
     * - Lower Nibble:
     *   > BRR_OBSERVE
     *   > BRR_BROADCAST
     *
     * - Higher Nibble:
     *   > BRR_ENABLE
     *   > BRR_DISABLE
     */
    uint8_t action;

    /**
     * Beacon type
     * - Lower Nibble:
     *   > BRR_BCON_PASSIVE - Non Connectable beacon
     *   > BRR_BCON_ACTIVE  - Connectable beacon
     *
     * - Higher Nibble (Valid only when Passive)
     *   > BRR_BCON_TYPE_UNPROV_DEVICE
     *   > BRR_BCON_TYPE_SECURE_NET
     */
    uint8_t type;

    /** Beacon Broadcast Data */
    uint8_t * bcon_data;

    /** Beacon Broadcast Data length */
    uint16_t bcon_datalen;

    /** URI information in case of Unprovisioned Beacons */
    rm_ble_mesh_buffer_t * uri;
} rm_ble_mesh_bearer_beacon_info_t;

/** Bearer GATT Channel information related data structure */
typedef struct st_rm_ble_mesh_bearer_ch_info
{
    /** Identifies the MTU for the Bearer Channel */
    uint16_t mtu;

    /** Identifies the role for the Bearer channel */
    uint8_t role;
} rm_ble_mesh_bearer_ch_info_t;

/**
 * BEARER Application Asynchronous Notification Callback.
 *
 * BEARER calls the registered callback to indicate events occurred to the
 * application.
 */
typedef struct st_rm_ble_mesh_bearer_ntf_callback_args
{
    rm_ble_mesh_bearer_handle_t        * p_handle; ///< Bearer handle identifier.
    rm_ble_mesh_bearer_interface_event_t event;    ///< Bearer interface event.
    uint8_t * p_data;                              ///< Data associated with the event if any or NULL.
    uint16_t  data_length;                         ///< Size of the event data. 0 if event data is NULL.
} rm_ble_mesh_bearer_ntf_callback_args_t;

/**
 * BEARER Application Asynchronous Notification Callback for Beacons.
 *
 * Application registers callback for beacon notification with bearer.
 *
 */
typedef struct st_rm_ble_mesh_bearer_beacon_callback_args
{
    uint8_t * p_data;                  ///< Data associated with the event if any or NULL.
    uint16_t  data_length;             ///< Size of the event data. 0 if event data is NULL.
} rm_ble_mesh_bearer_beacon_callback_args_t;

/** BLE MESH BEARER control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_ble_mesh_bearer_instance_ctrl_t
 */
typedef void rm_ble_mesh_bearer_ctrl_t;

/** BLE MESH BEARER configuration parameters. */
typedef struct st_rm_ble_mesh_bearer_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                               ///< Select a channel corresponding to the channel number of the hardware.
    rm_ble_mesh_instance_t const * p_mesh_instance; ///< Instance structure of BLE Mesh
    void const * p_context;                         ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                          ///< Placeholder for user extension.
} rm_ble_mesh_bearer_cfg_t;

/** BLE MESH BEARER functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_bearer_api
{
    /** Open bearer middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, rm_ble_mesh_bearer_cfg_t const * const p_cfg);

    /** Close bearer middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_Close()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl);

    /** Register Interface with Bearer Layer
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_RegisterInterface()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  brr_type
     *             Bearer Type.
     *
     * @param[in]  p_callback
     *             Pointer to details describing application notification callback.
     */
    fsp_err_t (* registerInterface)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, rm_ble_mesh_bearer_type_t brr_type,
                                    rm_ble_mesh_bearer_ntf_callback_result_t (* p_callback)(
                                        rm_ble_mesh_bearer_ntf_callback_args_t * p_args));

    /** Register Beacon Interface with Bearer Layer
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_RegisterBeaconHandler()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  bcon_type
     *             Beacon type - Unprovisioned Device or Secure Network.
     *
     * @param[in]  p_handler
     *             Pointer to callback handler to be registered for the given beacon type.
     */
    fsp_err_t (* registerBeaconHandler)(rm_ble_mesh_bearer_ctrl_t * const               p_ctrl,
                                        rm_ble_mesh_bearer_beacon_type_t                bcon_type,
                                        void (                                        * p_handler)(
                                            rm_ble_mesh_bearer_beacon_callback_args_t * p_args));

    /** Add a bearer to Bearer Layer
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_AddBearer()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  brr_type
     *             Bearer Type.
     *
     * @param[in]  p_brr_info
     *             Pointer to details describing the Bearer being added.
     *
     * @param[out] p_brr_handle
     *             Pointer to handle to the bearer that is added. Used in data APIs.
     */
    fsp_err_t (* addBearer)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, rm_ble_mesh_bearer_type_t brr_type,
                            rm_ble_mesh_bearer_info_t const * const p_brr_info,
                            rm_ble_mesh_bearer_handle_t * const p_brr_handle);

    /** Remove a bearer from Bearer Layer
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_RemoveBearer()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  brr_type
     *             Bearer Type.
     *
     * @param[in]  p_brr_handle
     *             Pointer to handle to the bearer is removed. Used in data APIs.
     */
    fsp_err_t (* removeBearer)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, rm_ble_mesh_bearer_type_t brr_type,
                               rm_ble_mesh_bearer_handle_t const * const p_brr_handle);

    /** Observe ON/OFF for the beacon type
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_ObserveBeacon()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  bcon_type
     *             Type of beacon to observe - Active/Passive.
     *
     * @param[in]  enable
     *             Enable or Disable the observation procedure.
     */
    fsp_err_t (* observeBeacon)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t bcon_type, uint8_t enable);

    /** API to send Unprovisioned Device Beacon
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_BcastUnprovisionedBeacon()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  type
     *             Active or Passive Broadcast type.
     *
     * @param[in]  p_dev_uuid
     *             Pointer to device UUID uniquely identifying this device.
     *
     * @param[in]  oob_info
     *             OOB Information.
     *
     * @param[in]  p_uri
     *             Pointer to optional Parameter. NULL if not present.
     *             Points to the length and payload pointer of the URI string to be
     *             advertised interleaving with the unprovisioned beacon.
     */
    fsp_err_t (* bcastUnprovisionedBeacon)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t type,
                                           uint8_t const * const p_dev_uuid, uint16_t oob_info,
                                           rm_ble_mesh_buffer_t const * const p_uri);

    /** API to broadcast a beacon
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_BroadcastBeacon()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  type
     *             The type of beacon.
     *
     * @param[in]  p_packet
     *             Pointer to beacon data.
     *
     * @param[in]  length
     *             Beacon data length.
     */
    fsp_err_t (* broadcastBeacon)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t type,
                                  uint8_t const * const p_packet, uint16_t length);

    /** API to send Proxy Device ADV
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_StartProxyAdv()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  type
     *             Proxy ADV Type:
     *              0x00 - Network ID
     *              0x01 - Node Identity
     *
     * @param[in]  p_data
     *             Pointer to data to be advertised by Proxy.
     *             If the "type" is:
     *              0x00 - Network ID    - 8 Bytes of Network ID
     *              0x01 - Node Identity - 8 Bytes Hash, 8 Bytes Random number
     *
     * @param[in]  datalen
     *             Length of the data to be advertised by Proxy.
     *             If the "type" is:
     *              0x00 - Network ID    - 8 Bytes of Network ID
     *              0x01 - Node Identity - 8 Bytes Hash, 8 Bytes Random number
     */
    fsp_err_t (* startProxyAdv)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t type, uint8_t const * const p_data,
                                uint16_t datalen);

    /** Send a bearer PDU
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_SendPdu()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  p_brr_handle
     *             Pointer to bearer handle on which PDU is to be sent.
     *
     * @param[in]  brr_type
     *             Bearer Type.
     *
     * @param[in]  p_buffer
     *             Pointer to PDU data to be sent.
     */
    fsp_err_t (* sendPdu)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl,
                          rm_ble_mesh_bearer_handle_t const * const p_brr_handle, rm_ble_mesh_bearer_type_t brr_type,
                          rm_ble_mesh_buffer_t const * const p_buffer);

    /** Get the RSSI of current received packet being processed.
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_GetPacketRssi()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[out] p_rssi_value
     *             Pointer to RSSI value.
     *
     * @note       This applies only when the packet is received over ADV bearer.
     *
     */
    fsp_err_t (* getPacketRssi)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t * p_rssi_value);

    /** Put the bearer to sleep.
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_Sleep()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     */
    fsp_err_t (* sleep)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl);

    /** Wakeup the bearer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_BEARER_Wakeup()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  mode
     *             Identifies the mode (BRR_TX/BRR_RX) for which bearer is requested
     *             for wakeup.
     */
    fsp_err_t (* wakeup)(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t mode);
} rm_ble_mesh_bearer_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_bearer_instance
{
    rm_ble_mesh_bearer_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_bearer_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_bearer_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_bearer_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_BEARER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_BEARER_API_H
