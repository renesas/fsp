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

#ifndef RM_BLE_MESH_NETWORK_API_H
#define RM_BLE_MESH_NETWORK_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_NETWORK_API BLE Mesh Network Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Network functions.
 *
 * @section   RM_BLE_MESH_NETWORK_API_Summary Summary
 * The BLE Mesh Network interface for the Bluetooth Low Energy Mesh Network (BLE MESH NETWORK) peripheral provides Bluetooth Low Energy Mesh Network functionality.
 *
 * The Bluetooth Low Energy Mesh interface can be implemented by:
 * - @ref RM_BLE_MESH_NETWORK
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

#include "rm_ble_mesh_bearer_api.h"
#include "rm_ble_mesh_provision_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Unassigned Address. */
#define RM_BLE_MESH_NETWORK_UNASSIGNED_ADDRESS       0x0000

/** Primary Subnet - NetKey Index is 0x000 */
#define RM_BLE_MESH_NETWORK_PRIMARY_SUBNET           0x000

/** Invalid Subnet Handle */
#define RM_BLE_MESH_NETWORK_INVALID_SUBNET_HANDLE    0xFFFF

/** Invalid AppKey Handle */
#define RM_BLE_MESH_NETWORK_INVALID_APPKEY_HANDLE    0xFFFF

/**
 * Invalid NID Identifier.
 * The NID is a 7-bit value that identifies the security material that is used
 * to secure Network PDUs.
 * Treating 0xFF as Invalid NID value.
 */
#define RM_BLE_MESH_NETWORK_INVALID_NID              0xFF

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Ignore network cache wrapping. */
typedef  enum e_rm_ble_mesh_network_old_packet_treatment
{
    /** Old packets will be dropped. */
    RM_BLE_MESH_NETWORK_OLD_PACKET_TREATMENT_DROPPED = 0,

    /** Ignores cache wrapping. Old packets will be processed. */
    RM_BLE_MESH_NETWORK_OLD_PACKET_TREATMENT_PROCESSED = 1,
} rm_ble_mesh_network_old_packet_treatment_t;

/** Whether to enable the RX callback event or not. */
typedef  enum e_rm_ble_mesh_network_rx_state_event
{
    RM_BLE_MESH_NETWORK_RX_STATE_EVENT_DISABLE = 0, ///< RX state callback disable
    RM_BLE_MESH_NETWORK_RX_STATE_EVENT_ENABLE  = 1, ///< RX state callback enable
} rm_ble_mesh_network_rx_state_event_t;

/** Whether to enable the TX callback event or not. */
typedef  enum e_rm_ble_mesh_network_tx_state_event
{
    RM_BLE_MESH_NETWORK_TX_STATE_EVENT_DISABLE = 0, ///< TX state callback disable
    RM_BLE_MESH_NETWORK_TX_STATE_EVENT_ENABLE  = 1, ///< TX state callback enable
} rm_ble_mesh_network_tx_state_event_t;

/** Address Type */
typedef enum e_rm_ble_mesh_network_address_type
{
    /** Invalid address type */
    RM_BLE_MESH_NETWORK_ADDRESS_TYPE_INVALID = 0,

    /** Unicast address type */
    RM_BLE_MESH_NETWORK_ADDRESS_TYPE_UNICAST = 1,

    /** Virtual address type */
    RM_BLE_MESH_NETWORK_ADDRESS_TYPE_VIRTUAL = 2,

    /** Group address type */
    RM_BLE_MESH_NETWORK_ADDRESS_TYPE_GROUP = 3,
} rm_ble_mesh_network_address_type_t;

/** Data structures for filter type and address list */
typedef  enum e_rm_ble_mesh_network_proxy_filter_type
{
    /** GATT Proxy Filter Types - Whitelist */
    RM_BLE_MESH_NETWORK_PROXY_FILTER_TYPE_WHITELIST = 0,

    /** GATT Proxy Filter Type - Blacklist */
    RM_BLE_MESH_NETWORK_PROXY_FILTER_TYPE_BLACKLIST = 1,
} rm_ble_mesh_proxy_filter_type_t;

/** GATT Proxy Configuration Opcodes */
typedef  enum e_rm_ble_mesh_network_proxy_config_opcode
{
/** GATT Proxy Configuration - Set Filter Opcode */
    RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_SET_FILTER = 0x00,

/** GATT Proxy Configuration - Add to Filter Opcode */
    RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_ADD_TO_FILTER = 0x01,

/** GATT Proxy Configuration - Remove From Filter Opcode */
    RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_REM_FROM_FILTER = 0x02,

/** GATT Proxy Configuration - Filter Status Opcode */
    RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_FILTER_STATUS = 0x03,
} rm_ble_mesh_proxy_config_opcode_t;

/**
 * GATT Proxy States.
 *
 * | Proxy Callback   |  Proxy Iface |  Error Code
 * |------------------|--------------|-------------------
 * |  NULL            |  Down        | MS_PROXY_NULL
 * |  NULL            |  Up          | MS_PROXY_NULL
 * |  !NULL           |  Down        | MS_PROXY_READY
 * |  !NULL           |  UP          | MS_PROXY_CONNECTED
 */
typedef  enum e_rm_ble_mesh_network_gatt_proxy_state
{
    /** GATT Proxy State - Invalid/Not Initialized */
    RM_BLE_MESH_NETWORK_GATT_PROXY_STATE_NULL = 0x00,

    /** GATT Proxy State - Ready/Initialized */
    RM_BLE_MESH_NEgTWORK_GATT_PROXY_STATE_READY = 0x01,

    /** GATT Proxy State - Connected */
    RM_BLE_MESH_NETWORK_GATT_PROXY_STATE_CONNECTED = 0x02,
} rm_ble_mesh_network_gatt_proxy_state_t;

/** GATT Proxy ADV Modes */
typedef  enum e_rm_ble_mesh_network_gatt_proxy_adv_mode
{
    /** Network ID Type */
    RM_BLE_MESH_NETWORK_GATT_PROXY_ADV_MODE_NET_ID = 0x01,

    /** Node Identity Type */
    RM_BLE_MESH_NETWORK_GATT_PROXY_ADV_MODE_NODE_ID = 0x02,
} rm_ble_mesh_network_gatt_proxy_adv_mode_t;

/** GATT Proxy Events */
typedef  enum e_rm_ble_mesh_network_event
{
    /** GATT Proxy Event - Interface Up */
    RM_BLE_MESH_NETWORK_EVENT_PROXY_UP = 0x00,

    /** GATT Proxy Event - Interface Down */
    RM_BLE_MESH_NETWORK_EVENT_PROXY_DOWN = 0x01,

    /** GATT Proxy Event - Status */
    RM_BLE_MESH_NETWORK_EVENT_PROXY_STATUS = 0x02,

    /** GATT Proxy Event - Receive */
    RM_BLE_MESH_NETWORK_EVENT_RECIEVE = 0x03,

    /** GATT Proxy Event - TX queue empty */
    RM_BLE_MESH_NETWORK_EVENT_TX_QUEUE_EMPTY = 0x04,
} rm_ble_mesh_network_event_t;

/** Network Address Type */
typedef uint16_t rm_ble_mesh_network_address_t;

/** Subnet Handle */
typedef uint16_t rm_ble_mesh_network_subnet_handle_t;

/** AppKey Handle */
typedef uint16_t rm_ble_mesh_network_appkey_handle_t;

/** Proxy Address */
typedef uint16_t rm_ble_mesh_network_proxy_address_t;

/** Network Interface Handle */
typedef uint8_t rm_ble_mesh_network_interface_handle_t;

/** Network Header Type */
typedef struct st_rm_ble_mesh_network_header
{
    /** Least significant bit of IV Index - 1 bit */
    uint8_t ivi;

    /**
     * Value derived from the NetKey used to identify
     * the Encrytion Key and Privacy Key used to secure
     * this PDU - 7 bits
     */
    uint8_t nid;

    /**
     * Indicates use of a new NetKey to which the network
     * is being updated to.
     */
    uint8_t new_key;

    /** Network Control - 1 bit */
    uint8_t ctl;

    /** Time To Live - 7 bits */
    uint8_t ttl;

    /** 16 Bit Source Address */
    rm_ble_mesh_network_address_t src_addr;

    /** 16 Bit Destination Address */
    rm_ble_mesh_network_address_t dst_addr;

    /** 24 bit sequence number - currently filled only in reception path */
    uint32_t seq_num;
} rm_ble_mesh_network_header_t;

/** Current Sequence Number and Block State */
typedef struct st_rm_ble_mesh_network_seq_number_state
{
    /** Current Sequence Number */
    uint32_t seq_num;

    /** Block Sequence number - maximum available */
    uint32_t block_seq_num_max;
} rm_ble_mesh_network_seq_number_state_t;

/** Network configuration information */
typedef struct st_rm_ble_mesh_network_route_info
{
    /** Pointer to list of address to be added/deleted */
    rm_ble_mesh_network_interface_handle_t * interface_handle;

    /**  Count of addresses present in the provided list */
    rm_ble_mesh_network_subnet_handle_t subnet_handle;
} rm_ble_mesh_network_route_info_t;

/** Proxy Server's filter List */
typedef struct st_rm_ble_mesh_network_proxy_address_list
{
    /** Pointer to list of address to be added/deleted */
    rm_ble_mesh_network_proxy_address_t * address;

    /**  Count of addresses present in the provided list */
    uint16_t count;
} rm_ble_mesh_network_proxy_address_list_t;

/** BLE Mesh Network callback parameter definition */
typedef struct st_rm_ble_mesh_network_callback_args
{
    rm_ble_mesh_network_event_t              event;               ///< Event code.
    rm_ble_mesh_network_header_t           * p_header;            ///< Network header type.
    rm_ble_mesh_network_subnet_handle_t      subnet_handle;       ///< Subnet handle.
    rm_ble_mesh_network_interface_handle_t * p_network_interface; ///< Network interface handle.
    rm_ble_mesh_buffer_t event_data;                              ///< Event data.
    void const         * p_context;                               ///< Context provided to user during callback.
} rm_ble_mesh_network_callback_args_t;

/** BLE MESH NETWORK control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_ble_mesh_network_instance_ctrl_t
 */
typedef void rm_ble_mesh_network_ctrl_t;

/** BLE MESH NETWORK configuration parameters. */
typedef struct st_rm_ble_mesh_network_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                     ///< Select a channel corresponding to the channel number of the hardware.
    rm_ble_mesh_network_old_packet_treatment_t old_packet_treatment;
    rm_ble_mesh_network_rx_state_event_t       rx_state_event;
    rm_ble_mesh_network_tx_state_event_t       tx_state_event;
    rm_ble_mesh_bearer_instance_t const      * p_mesh_bearer_instance;    ///< Instance structure of BLE Mesh Bearer
    rm_ble_mesh_provision_instance_t const   * p_mesh_provision_instance; ///< Instance structure of BLE Mesh Provision
    void (* p_callback)(rm_ble_mesh_network_callback_args_t * p_args);    ///< Callback function
    void const * p_context;                                               ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                                ///< Placeholder for user extension.
} rm_ble_mesh_network_cfg_t;

/** BLE MESH NETWORK functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_network_api
{
    /** Register Interface with Network Layer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_network_ctrl_t * const p_ctrl, rm_ble_mesh_network_cfg_t const * const p_cfg);

    /** Unregister Interface with Network Layer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_network_ctrl_t * const p_ctrl);

    /** API to send Secure Network Beacon.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_BroadcastSecureBeacon()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Subnet handle of the network to be broadcasted.
     */
    fsp_err_t (* broadcastSecureBeacon)(rm_ble_mesh_network_ctrl_t * const  p_ctrl,
                                        rm_ble_mesh_network_subnet_handle_t subnet_handle);

    /** Extension API to send network PDUs on selected network interfaces.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_SendPduOnInterface()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_route_info  Pointer to network configuration information.
     * @param[in]  p_header      Pointer to network Header.
     * @param[in]  p_buffer      Pointer to Lower Transport Payload.
     */
    fsp_err_t (* sendPduOnInterface)(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                     rm_ble_mesh_network_route_info_t const * const p_route_info,
                                     rm_ble_mesh_network_header_t const * const     p_header,
                                     rm_ble_mesh_buffer_t const * const             p_buffer);

    /** To get address type.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_GetAddressType()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  addr    Input network address.
     * @param[in]  p_type  One of the following address type
     *                     @ref RM_BLE_MESH_NETWORK_ADDRESS_TYPE_INVALID
     *                     @ref RM_BLE_MESH_NETWORK_ADDRESS_TYPE_UNICAST
     *                     @ref RM_BLE_MESH_NETWORK_ADDRESS_TYPE_GROUP
     */
    fsp_err_t (* getAddressType)(rm_ble_mesh_network_ctrl_t * const p_ctrl, rm_ble_mesh_network_address_t addr,
                                 rm_ble_mesh_network_address_type_t * const p_type);

    /** Check if the proxy module is ready to handle proxy messages/events.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_FetchProxyState()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[out]  p_proxy_state  Returns the current state of the proxy.
     */
    fsp_err_t (* fetchProxyState)(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                  rm_ble_mesh_network_gatt_proxy_state_t * const p_proxy_state);

    /** Set proxy server's filter type.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_SetProxyFilter()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_route_info  Pointer to network configuration information.
     * @param[in]  type          Type of the proxy filter to be set. Either
     *                           @ref RM_BLE_MESH_NETWORK_PROXY_FILTER_TYPE_WHITELIST or
     *                           @ref RM_BLE_MESH_NETWORK_PROXY_FILTER_TYPE_BLACKLIST
     */
    fsp_err_t (* setProxyFilter)(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                 rm_ble_mesh_network_route_info_t const * const p_route_info,
                                 rm_ble_mesh_proxy_filter_type_t                type);

    /** Add or Delete/Remove addresses to/from proxy filter list.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_ConfigProxyFilter()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_route_info  Pointer to network configuration information.
     * @param[in]  opcode        Operation to be performed. Either
     *                           @ref RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_ADD_TO_FILTER or
     *                           @ref RM_BLE_MESH_NETWORK_PROXY_CONFIG_OPECODE_REM_FROM_FILTER
     * @param[in]  p_addr_list   Pointer to list of address to be added/deleted.
     *                           And count of addresses present in the provided List.
     */
    fsp_err_t (* configProxyFilter)(rm_ble_mesh_network_ctrl_t * const               p_ctrl,
                                    rm_ble_mesh_network_route_info_t const * const   p_route_info,
                                    rm_ble_mesh_proxy_config_opcode_t                opcode,
                                    rm_ble_mesh_network_proxy_address_list_t * const p_addr_list);

    /** Start connectable advertisements for a proxy server.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_StartProxyServerAdv()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Subnet handle which the proxy server is part of network.
     * @param[in]  proxy_adv_mode Mode of proxy advertisements. This could be of two types
     *                            @ref RM_BLE_MESH_NETWORK_GATT_PROXY_ADV_MODE_NET_ID or
     *                            @ref RM_BLE_MESH_NETWORK_GATT_PROXY_ADV_MODE_NODE_ID
     */
    fsp_err_t (* startProxyServerAdv)(rm_ble_mesh_network_ctrl_t * const        p_ctrl,
                                      rm_ble_mesh_network_subnet_handle_t       subnet_handle,
                                      rm_ble_mesh_network_gatt_proxy_adv_mode_t proxy_adv_mode);

    /** Stop connectable advertisements for a proxy server.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_StopProxyServerAdv()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     */
    fsp_err_t (* stopProxyServerAdv)(rm_ble_mesh_network_ctrl_t * const p_ctrl);

    /** To allocate sequence number.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_AllocateSeqNumber()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[out] p_seq_num      Location where sequence number to be filled.
     */
    fsp_err_t (* allocateSeqNumber)(rm_ble_mesh_network_ctrl_t * const p_ctrl, uint32_t * const p_seq_num);

    /** To get current sequence number state.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_GetSeqNumberState()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_seq_num_state  Location where sequence number state to be filled.
     */
    fsp_err_t (* getSeqNumberState)(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                    rm_ble_mesh_network_seq_number_state_t * const p_seq_num_state);

    /** To set current sequence number state.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_SetSeqNumberState()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_seq_num_state  Location from where sequence number state to be taken.
     */
    fsp_err_t (* setSeqNumberState)(rm_ble_mesh_network_ctrl_t * const                   p_ctrl,
                                    rm_ble_mesh_network_seq_number_state_t const * const p_seq_num_state);

    /** To reinitialize all Network Layer cache entries.
     * @par Implemented as
     * - @ref RM_BLE_MESH_NETWORK_ResetNetCache()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     */
    fsp_err_t (* resetNetCache)(rm_ble_mesh_network_ctrl_t * const p_ctrl);
} rm_ble_mesh_network_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_network_instance
{
    rm_ble_mesh_network_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_network_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_network_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_network_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_NETWORK_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_NETWORK_API_H
