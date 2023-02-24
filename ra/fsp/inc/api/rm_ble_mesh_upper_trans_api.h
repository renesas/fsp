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

#ifndef RM_BLE_MESH_UPPER_TRANS_API_H
#define RM_BLE_MESH_UPPER_TRANS_API_H

/*******************************************************************************************************************//**
 * @ingroup  RENESAS_INTERFACES
 * @defgroup RM_BLE_MESH_UPPER_TRANS_API BLE Mesh Upper Trans Interface
 * @brief    Interface for Bluetooth Low Energy Mesh Upper Trans functions.
 *
 * @section RM_BLE_MESH_UPPER_TRANS_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Upper Trans peripheral provides Bluetooth Low Energy Mesh Upper Trans functionality.
 *
 * The Bluetooth Low Energy Mesh interface can be implemented by:
 * - @ref RM_BLE_MESH_UPPER_TRANS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "rm_ble_mesh_lower_trans_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Whether to enable the access message event or not. */
typedef  enum e_rm_ble_mesh_upper_trans_access_message_evnet
{
    RM_BLE_MESH_UPPER_TRANS_ACCESS_MESSAGE_EVENT_DISABLE = 0, ///< Access state callback disable
    RM_BLE_MESH_UPPER_TRANS_ACCESS_MESSAGE_EVENT_ENABLE  = 1, ///< Access state callback enable
} rm_ble_mesh_upper_trans_access_message_evnet_t;

/** Whether to enable the control message event or not. */
typedef  enum e_rm_ble_mesh_upper_trans_control_message_evnet
{
    RM_BLE_MESH_UPPER_TRANS_CONTROL_MESSAGE_EVENT_DISABLE = 0, ///< Control state callback disable
    RM_BLE_MESH_UPPER_TRANS_CONTROL_MESSAGE_EVENT_ENABLE  = 1, ///< Control state callback enable
} rm_ble_mesh_upper_trans_control_message_evnet_t;

/**
 * Tranport Layer Control Packet Opcodes
 *
 * RFU: 0x02 - 0x0F
 */
typedef enum e_rm_ble_mesh_upper_trans_control_opcode
{
    /**
     * Sent by a Low Power node to its Friend node to request any messages
     * that it has cached for the Low Power node
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_POLL = 0x01,

    /**
     * Sent by a Friend node to a Low Power node to inform it about cache
     * and/or security updates
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_UPDATE = 0x02,

    /** Broadcast by a Low Power node to start to find a friend */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_REQ = 0x03,

    /** Sent by a Friend node to a Low Power node to offer to become its friend */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_OFFER = 0x04,

    /**
     * Sent to a Friend node to inform a previous friend of a Low Power node
     * about the removal of a friendship
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_CLEAR = 0x05,

    /**
     * Sent from a previous friend to Friend node to confirm that a prior friend
     * relationship has been removed
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_CLEAR_CNF = 0x06,

    /**
     * Sent to a Friend node to add one or more addresses
     * to the Friend Subscription List
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_SUBSCRN_LIST_ADD = 0x07,

    /**
     * Sent to a Friend node to remove one or more addresses
     * from the Friend Subscription List
     */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_SUBSCRN_LIST_REMOVE = 0x08,

    /** Sent by a Friend node to confirm Friend Subscription List updates */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_SUBSCRN_LIST_CNF = 0x09,

    /** Sent by a node to let other nodes determine topology of a Subnet */
    RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_HEARTBEAT = 0x0A,
} rm_ble_mesh_upper_trans_control_opcode_t;

/** Friend role */
typedef enum e_rm_ble_mesh_upper_trans_friend_role
{
    RM_BLE_MESH_UPPER_TRANS_FRIEND_ROLE_FRIEND = 0x01, ///< Friend role
    RM_BLE_MESH_UPPER_TRANS_FRIEND_ROLE_LPN    = 0x02, ///< LPN role
} rm_ble_mesh_upper_trans_friend_role_t;

/** Callback Event */
typedef enum e_rm_ble_mesh_upper_trans_event
{
    RM_BLE_MESH_UPPER_TRANS_EVENT_ACCESS                       = 0x00, ///< BLE Mesh Upper Trans Event - Access
    RM_BLE_MESH_UPPER_TRANS_EVENT_CONTROL                      = 0x01, ///< BLE Mesh Upper Trans Event - Control
    RM_BLE_MESH_UPPER_TRANS_EVENT_FRIENDSHIP_SETUP             = 0x02, ///< BLE Mesh Upper Trans Event - Friendship setup
    RM_BLE_MESH_UPPER_TRANS_EVENT_FRIENDSHIP_SUBSCRIPTION_LIST = 0x03, ///< BLE Mesh Upper Trans Event - Friendship subscription list
    RM_BLE_MESH_UPPER_TRANS_EVENT_FRIENDSHIP_CLEAR             = 0x04, ///< BLE Mesh Upper Trans Event - Friendship clear
    RM_BLE_MESH_UPPER_TRANS_EVENT_FRIENDSHIP_TERMINATE         = 0x05, ///< BLE Mesh Upper Trans Event - Friendship terminate
} rm_ble_mesh_upper_trans_event_t;

/** Access PDU */
typedef struct st_rm_ble_mesh_upper_trans_access_layer_pdu
{
    rm_ble_mesh_network_address_t src_addr;            ///< Source address
    rm_ble_mesh_network_address_t dst_addr;            ///< Destination address
    uint8_t * p_label;                                 ///< Label UUID, representing Virtual Address of Destination
    rm_ble_mesh_network_subnet_handle_t subnet_handle; ///< Handle identifying the subnet
    rm_ble_mesh_network_appkey_handle_t appkey_handle; ///< Handle identifying the AppKey to be used for Transport Layer encryption.
    uint8_t ttl;                                       ///< Time to Live
    void  * p_parameter;                               ///< Transport parameter, based on the type and header
} rm_ble_mesh_upper_trans_access_layer_pdu_t;

/** Control PDU */
typedef struct st_rm_ble_mesh_upper_trans_control_pdu
{
    rm_ble_mesh_network_address_t       src_addr;      ///< Source address
    rm_ble_mesh_network_address_t       dst_addr;      ///< Destination address
    rm_ble_mesh_network_subnet_handle_t subnet_handle; ///< Handle identifying the subnet
    uint8_t ttl;                                       ///< Time to Live
    rm_ble_mesh_upper_trans_control_opcode_t opcode;   ///< Control Packet Opcode
    void * p_parameter;                                ///< Transport parameter, based on the type and header
} rm_ble_mesh_upper_trans_control_pdu_t;

/** Low Power Node setting */
typedef struct st_rm_ble_mesh_upper_trans_friendship_setting
{
    /** The subnet to initiate the friendship procedure */
    rm_ble_mesh_network_subnet_handle_t subnet_handle;

    /** Friend criteria that is required. RSSI, Receive Window,
     *         MessageQueue size requirements can be established.*/
    uint8_t criteria;

    /** Receive delay in milliseconds that the LPN will wait before
     *         listening to response for any request.
     **/
    uint8_t rx_delay;

    /** Timeout in milliseconds after which the LPN will send Poll PDU
     *         to check for data from the friend. */
    uint32_t poll_timeout;

    /** Timeout in milliseconds for which the Friend Establishment
     *         procedure is to be tried.*/
    uint32_t setup_timeout;
} rm_ble_mesh_upper_trans_friendship_setting_t;

/** Low Power Node element information */
typedef struct st_rm_ble_mesh_upper_trans_friendship_info
{
    /** Main subnet handle of the element */
    rm_ble_mesh_network_subnet_handle_t subnet_handle;

    /** Peer LPN/Friend Address */
    rm_ble_mesh_network_address_t addr;

    /** Low Power Node Counter */
    uint16_t lpn_counter;

    /** Friend Counter */
    uint16_t friend_counter;
} rm_ble_mesh_upper_trans_friendship_info_t;

/** Hearbeat Publication state */
typedef struct st_rm_ble_mesh_upper_trans_heartbeat_publication_info
{
    /**
     * Destination address for heartbeat messages
     */
    rm_ble_mesh_network_address_t daddr;

    /**
     * Count to control the number of periodic heartbeat
     * transport messages to be sent
     */
    uint8_t count_log;

    /**
     * Period to control the cadence of periodic heartbeat
     * transport messages
     */
    uint8_t period_log;

    /**
     * TTL value to be used when sending heartbeat messages
     */
    uint8_t ttl;

    /**
     * Features that trigger sending heartbeat messages when changed
     */
    uint16_t features;

    /**
     * Global NetKey index of the NetKey to be used to send heartbeat messages
     */
    uint16_t netkey_index;
} rm_ble_mesh_upper_trans_heartbeat_publication_info_t;

/** Hearbeat Subscription state */
typedef struct st_rm_ble_mesh_upper_trans_heartbeat_subscription_info
{
    /**
     * Source address for heartbeat messages that a node shall process
     */
    rm_ble_mesh_network_address_t saddr;

    /**
     * Destination address for heartbeat messages
     */
    rm_ble_mesh_network_address_t daddr;

    /**
     * Counter that tracks the number of periodic heartbeat transport message
     * received since receiving the most recent configure heartbeat Subscription
     * Set message
     */
    uint8_t count_log;

    /**
     * Period that controls the period for processing periodical heartbeat
     * transport control messages
     */
    uint8_t period_log;

    /**
     * Minimum hops value registered when receiving heartbeat messages since
     * receiving the most recent configure heartbeat Subscription Set message
     */
    uint16_t min_hops;

    /**
     * Maximum hops value registered when receiving heartbeat messages since
     * receiving the most recent configure heartbeat Subscription Set message
     */
    uint16_t max_hops;
} rm_ble_mesh_upper_trans_heartbeat_subscription_info_t;

/** BLE Mesh Network callback parameter definition */
typedef struct st_rm_ble_mesh_upper_trans_callback_args
{
    rm_ble_mesh_upper_trans_event_t     event;         ///< Event code.
    rm_ble_mesh_network_header_t      * p_header;      ///< Event code.
    rm_ble_mesh_network_subnet_handle_t subnet_handle; ///< Associated Subnet Handle.
    rm_ble_mesh_network_appkey_handle_t appkey_handle; ///< Associated AppKey Handle.
    rm_ble_mesh_error_code_t            result;        ///< Event result.
    rm_ble_mesh_buffer_t                event_data;
    void const * p_context;                            ///< Context provided to user during callback.
} rm_ble_mesh_upper_trans_callback_args_t;

/** BLE MESH control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_ble_mesh_upper_trans_instance_ctrl_t
 */
typedef void rm_ble_mesh_upper_trans_ctrl_t;

/** BLE MESH configuration parameters. */
typedef struct st_rm_ble_mesh_upper_trans_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                            ///< Select a channel corresponding to the channel number of the hardware.
    rm_ble_mesh_upper_trans_control_message_evnet_t control_message_evnet;       ///< Whether to enable the control message event or not.
    rm_ble_mesh_upper_trans_access_message_evnet_t  access_message_evnet;        ///< Whether to enable the access message event or not.
    rm_ble_mesh_lower_trans_instance_t const      * p_mesh_lower_trans_instance; ///< Instance structure of BLE Mesh Bearer
    void (* p_callback)(rm_ble_mesh_upper_trans_callback_args_t * p_args);       ///< Callback
    void const * p_context;                                                      ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                                       ///< Placeholder for user extension.
} rm_ble_mesh_upper_trans_cfg_t;

/** BLE MESH functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_upper_trans_api
{
    /** Register interface with Transport Layer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_upper_trans_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_upper_trans_cfg_t const * const p_cfg);

    /** Unregister interface with Transport Layer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl);

    /** API to send Access Layer PDUs.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_SendAccessPdu()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  p_access_layer_pdu  Pointer to Access Layer PDUs.
     * @param[in]  reliable            If requires lower transport ACK, set reliable as @ref RM_BLE_MESH_LOWER_TRANS_RELIABLE_ENABLE.
     */
    fsp_err_t (* sendAccessPdu)(rm_ble_mesh_upper_trans_ctrl_t * const                   p_ctrl,
                                rm_ble_mesh_upper_trans_access_layer_pdu_t const * const p_access_layer_pdu,
                                rm_ble_mesh_lower_trans_reliable_t                       reliable);

    /** API to send transport Control PDUs.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_SendControlPdu()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_control_pdu  Pointer to control PDUs.
     */
    fsp_err_t (* sendControlPdu)(rm_ble_mesh_upper_trans_ctrl_t * const              p_ctrl,
                                 rm_ble_mesh_upper_trans_control_pdu_t const * const p_control_pdu);

    /** API to setup Friendship.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_LpnSetupFriendship()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_setting      Pointer to friendship settings.
     */
    fsp_err_t (* lpnSetupFriendship)(rm_ble_mesh_upper_trans_ctrl_t * const                     p_ctrl,
                                     rm_ble_mesh_upper_trans_friendship_setting_t const * const p_setting);

    /** API to terminate friendship.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_LpnClearFriendship()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     */
    fsp_err_t (* lpnClearFriendship)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl);

    /** API to manage friend subscription list.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_LpnManageSubscription()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  action         Will be one of @ref RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_SUBSCRN_LIST_ADD or @ref RM_BLE_MESH_UPPER_TRANS_CONTROL_OPCODE_FRIEND_SUBSCRN_LIST_REMOVE.
     * @param[in]  p_addr_list    Pointer to the packed list of addresses to be managed.
     * @param[in]  count          Number of addresses given.
     */
    fsp_err_t (* lpnManageSubscription)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl,
                                        rm_ble_mesh_upper_trans_control_opcode_t action,
                                        uint16_t const * const p_addr_list, uint16_t count);

    /** To trigger Friend Poll from application.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_LpnPoll()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     */
    fsp_err_t (* lpnPoll)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl);

    /** To check if address matches with any of the LPN.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_IsValidLpnElementAddress()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[in]   addr           Unicast address to search.
     * @param[out]  p_lpn_handle   Pointer to an LPN Handle, which will be filled if match found.
     */
    fsp_err_t (* isValidLpnElementAddress)(rm_ble_mesh_upper_trans_ctrl_t * const       p_ctrl,
                                           rm_ble_mesh_network_address_t                addr,
                                           rm_ble_mesh_lower_trans_lpn_handle_t * const p_lpn_handle);

    /** To check if valid subscription address of an LPN to receive a packet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_IsValidLpnSubscriptionAddress()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[in]   addr           Address to search.
     * @param[out]  p_lpn_handle   Pointer to an LPN Handle, which will be filled if match found.
     */
    fsp_err_t (* isValidLpnSubscriptionAddress)(rm_ble_mesh_upper_trans_ctrl_t * const       p_ctrl,
                                                rm_ble_mesh_network_address_t                addr,
                                                rm_ble_mesh_lower_trans_lpn_handle_t * const p_lpn_handle);

    /** To get Poll Timeout of an LPN.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_GetLpnPolltimeout()
     *
     * @param[in]   p_ctrl          Pointer to control structure.
     * @param[in]   lpn_addr        LPN address to search.
     * @param[out]  p_poll_timeout  Pointer to a memory where poll timeout of the LPN to be filled (if match found).
     */
    fsp_err_t (* getLpnPolltimeout)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl,
                                    rm_ble_mesh_network_address_t lpn_addr, uint32_t * const p_poll_timeout);

    /** To get the LPN node information.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_GetFriendshipInfo()
     *
     * @param[in]   p_ctrl     Pointer to control structure.
     * @param[in]   role       Local friendship role.
     * @param[in]   lpn_index  Index of the LPN element.
     * @param[out]  p_node     Pointer to copy the information.
     */
    fsp_err_t (* getFriendshipInfo)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl,
                                    rm_ble_mesh_upper_trans_friend_role_t role, uint16_t lpn_index,
                                    rm_ble_mesh_upper_trans_friendship_info_t * const p_node);

    /** To add the security update information.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_LpnRegisterSecurityUpdate()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle to identify the network.
     * @param[in]  flag           Flag indicating the Key Refresh and IV Update state.
     * @param[in]  ivindex        Current IV index of the network.
     */
    fsp_err_t (* lpnRegisterSecurityUpdate)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl,
                                            rm_ble_mesh_network_subnet_handle_t subnet_handle, uint8_t flag,
                                            uint32_t ivindex);

    /** To clear information related to all LPNs.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_ClearAllLpn()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     */
    fsp_err_t (* clearAllLpn)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl);

    /** To set the heartbeat publication data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_SetHeartbeatPublication()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[out]  p_info         Heartbeat Publication information data as in \ref rm_ble_mesh_upper_trans_heartbeat_publication_info_t.
     */
    fsp_err_t (* setHeartbeatPublication)(rm_ble_mesh_upper_trans_ctrl_t * const                       p_ctrl,
                                          rm_ble_mesh_upper_trans_heartbeat_publication_info_t * const p_info);

    /** To get the heartbeat publication data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_GetHeartbeatPublication()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[out]  p_info         Heartbeat Publication information data as in \ref rm_ble_mesh_upper_trans_heartbeat_publication_info_t.
     */
    fsp_err_t (* getHeartbeatPublication)(rm_ble_mesh_upper_trans_ctrl_t * const                       p_ctrl,
                                          rm_ble_mesh_upper_trans_heartbeat_publication_info_t * const p_info);

    /** To set the heartbeat subscription data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_SetHeartbeatSubscription()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[out]  p_info         Heartbeat Publication information data as in \ref rm_ble_mesh_upper_trans_heartbeat_subscription_info_t.
     */
    fsp_err_t (* setHeartbeatSubscription)(rm_ble_mesh_upper_trans_ctrl_t * const                        p_ctrl,
                                           rm_ble_mesh_upper_trans_heartbeat_subscription_info_t * const p_info);

    /** To get the heartbeat subscription data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_GetHeartbeatSubscription()
     *
     * @param[in]   p_ctrl         Pointer to control structure.
     * @param[out]  p_info         Heartbeat Publication information data as in \ref rm_ble_mesh_upper_trans_heartbeat_subscription_info_t.
     */
    fsp_err_t (* getHeartbeatSubscription)(rm_ble_mesh_upper_trans_ctrl_t * const                        p_ctrl,
                                           rm_ble_mesh_upper_trans_heartbeat_subscription_info_t * const p_info);

    /** To trigger heartbeat send on change in feature.
     * @par Implemented as
     * - @ref RM_BLE_MESH_UPPER_TRANS_GetHeartbeatSubscription()
     *
     * @param[in]  p_ctrl                 Pointer to control structure.
     * @param[in]  change_in_feature_bit  Bit mask of the changed feature field.
     */
    fsp_err_t (* triggerHeartbeat)(rm_ble_mesh_upper_trans_ctrl_t * const p_ctrl, uint8_t change_in_feature_bit);
} rm_ble_mesh_upper_trans_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_upper_trans_instance
{
    rm_ble_mesh_upper_trans_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_ble_mesh_upper_trans_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_ble_mesh_upper_trans_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_ble_mesh_upper_trans_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_UPPER_TRANS_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_UPPER_TRANS_API_H
