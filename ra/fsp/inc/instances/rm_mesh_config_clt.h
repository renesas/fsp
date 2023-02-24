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

#ifndef RM_MESH_CONFIG_CLT_H
#define RM_MESH_CONFIG_CLT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_config_client_api.h"
#include "rm_ble_mesh_access.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**
 * Beacon Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_beacon_set_parameter
{
    /** New Secure Network Beacon state */
    uint8_t beacon;
} rm_mesh_config_clt_beacon_set_parameter_t;

/**
 * Composition Data Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_composition_data_get_parameter
{
    /** Page number of the Composition Data */
    uint8_t page;
} rm_mesh_config_clt_composition_data_get_parameter_t;

/**
 * Default TTL Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_default_ttl_set_parameter
{
    /** New Default TTL value */
    uint8_t ttl;
} rm_mesh_config_clt_default_ttl_set_parameter_t;

/**
 * GATT Proxy Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_gatt_proxy_set_parameter
{
    /** New GATT Proxy state */
    uint8_t proxy;
} rm_mesh_config_clt_gatt_proxy_set_parameter_t;

/**
 * Relay Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_relay_set_parameter
{
    /** Relay */
    uint8_t relay;

    /**
     * Number of retransmissions on advertising bearer for
     * each Network PDU relayed by the node
     * - 3 bits validity
     */
    uint8_t relay_rtx_count;

    /**
     * Number of 10-millisecond steps between retransmissions
     * - 5 bits validity
     */
    uint8_t relay_rtx_interval_steps;
} rm_mesh_config_clt_relay_set_parameter_t;

/**
 * Model Publication Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_publication_get_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_publication_get_parameter_t;

/**
 * Model Publication Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_publication_set_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the publish address */
    uint16_t publish_address;

    /**
     * Index of the application key
     * - 12 bits validity
     */
    uint16_t appkey_index;

    /**
     * Value of the Friendship Credential Flag
     * - 1 bit validity
     */
    uint8_t credential_flag;

    /** Default TTL value for the outgoing messages */
    uint8_t publish_ttl;

    /** Period for periodic status publishing */
    uint8_t publish_period;

    /**
     * Number of retransmissions for each published message
     * - 3 bits validity
     */
    uint8_t publish_rtx_count;

    /**
     * Number of 50-millisecond steps between retransmissions
     * - 5 bits validity
     */
    uint8_t publish_rtx_interval_steps;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_publication_set_parameter_t;

/**
 * Model Publication Virtual Address Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_publication_virtual_address_set_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the Label UUID publish address */
    uint8_t publish_address[RM_BLE_MESH_ACCESS_VADDR_LABEL_UUID_SIZE];

    /**
     * Index of the application key
     * - 12 bits validity
     */
    uint16_t appkey_index;

    /**
     * Value of the Friendship Credential Flag
     * - 1 bit validity
     */
    uint8_t credential_flag;

    /** Default TTL value for the outgoing messages */
    uint8_t publish_ttl;

    /** Period for periodic status publishing */
    uint8_t publish_period;

    /**
     * Number of retransmissions for each published message
     * - 3 bits validity
     */
    uint8_t publish_rtx_count;

    /**
     * Number of 50-millisecond steps between retransmissions
     * - 5 bits validity
     */
    uint8_t publish_rtx_interval_steps;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_publication_virtual_address_set_parameter_t;

/**
 * Model Subscription Add parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_add_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the address */
    uint16_t address;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_add_parameter_t;

/**
 * Model Subscription Virtual Address Add parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_virtual_address_add_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the Label UUID */
    uint8_t label[RM_BLE_MESH_ACCESS_VADDR_LABEL_UUID_SIZE];

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_virtual_address_add_parameter_t;

/**
 * Model Subscription Delete parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_delete_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the address */
    uint16_t address;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_delete_parameter_t;

/**
 * Model Subscription Virtual Address Delete parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_virtual_address_delete_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the Label UUID */
    uint8_t label[RM_BLE_MESH_ACCESS_VADDR_LABEL_UUID_SIZE];

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_virtual_address_delete_parameter_t;

/**
 * Model Subscription Overwrite parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_overwrite_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the address */
    uint16_t address;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_overwrite_parameter_t;

/**
 * Model Subscription Virtual Address Overwrite parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_virtual_address_overwrite_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Value of the Label UUID */
    uint8_t label[RM_BLE_MESH_ACCESS_VADDR_LABEL_UUID_SIZE];

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_virtual_address_overwrite_parameter_t;

/**
 * Model Subscription Delete All parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_subscription_delete_all_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;
} rm_mesh_config_clt_model_subscription_delete_all_parameter_t;

/**
 * SIG Model Subscription Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_sig_model_subscription_get_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** SIG Model ID */
    rm_ble_mesh_access_model_id_sig_t model_id;
} rm_mesh_config_clt_sig_model_subscription_get_parameter_t;

/**
 * Vendor Model Subscription Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_vendor_model_subscription_get_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Vendor Model ID */
    rm_ble_mesh_access_model_id_vendor_t model_id;
} rm_mesh_config_clt_vendor_model_subscription_get_parameter_t;

/**
 * Netkey Add parameter structure
 */
typedef struct st_rm_mesh_config_clt_netkey_add_parameter
{
    /** Netkey */
    uint8_t netkey[RM_BLE_MESH_ACCESS_NETKEY_SIZE];

    /** Netkey Index */
    uint16_t netkey_index;
} rm_mesh_config_clt_netkey_add_parameter_t;

/**
 * Netkey Update parameter structure
 */
typedef struct st_rm_mesh_config_clt_netkey_update_parameter
{
    /** New Netkey */
    uint8_t netkey[RM_BLE_MESH_ACCESS_NETKEY_SIZE];

    /** Netkey Index */
    uint16_t netkey_index;
} rm_mesh_config_clt_netkey_update_parameter_t;

/**
 * Netkey Delete parameter structure
 */
typedef struct st_rm_mesh_config_clt_netkey_delete_parameter
{
    /** Netkey Index */
    uint16_t netkey_index;
} rm_mesh_config_clt_netkey_delete_parameter_t;

/**
 * Appkey Add parameter structure
 */
typedef struct st_rm_mesh_config_clt_appkey_add_parameter
{
    /** Appkey value */
    uint8_t appkey[RM_BLE_MESH_ACCESS_APPKEY_SIZE];

    /**
     * Index of the NetKey and index of the AppKey
     * - 24 bits valid
     */
    uint16_t netkey_index;
    uint16_t appkey_index;
} rm_mesh_config_clt_appkey_add_parameter_t;

/**
 * Appkey Update parameter structure
 */
typedef struct st_rm_mesh_config_clt_appkey_update_parameter
{
    /** New Appkey value */
    uint8_t appkey[RM_BLE_MESH_ACCESS_APPKEY_SIZE];

    /**
     * Index of the NetKey and index of the AppKey
     * - 24 bits valid
     */
    uint16_t netkey_index;
    uint16_t appkey_index;
} rm_mesh_config_clt_appkey_update_parameter_t;

/**
 * Appkey Delete parameter structure
 */
typedef struct st_rm_mesh_config_clt_appkey_delete_parameter
{
    /**
     * Index of the NetKey and index of the AppKey
     * - 24 bits valid
     * */
    uint16_t netkey_index;
    uint16_t appkey_index;
} rm_mesh_config_clt_appkey_delete_parameter_t;

/**
 * Appkey Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_appkey_get_parameter
{
    /** Index of the NetKey */
    uint16_t netkey_index;
} rm_mesh_config_clt_appkey_get_parameter_t;

/**
 * Node Identity Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_node_id_get_parameter
{
    /** Index of the NetKey */
    uint16_t netkey_index;
} rm_mesh_config_clt_node_id_get_parameter_t;

/**
 * Node Identity Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_node_id_set_parameter
{
    /** Index of the NetKey */
    uint16_t netkey_index;

    /** New Node Identity state */
    uint8_t identity;
} rm_mesh_config_clt_node_id_set_parameter_t;

/**
 * Model App Bind parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_app_bind_parameter
{
    /** Remote Element Address */
    uint16_t element_address;

    /** Index of the AppKey */
    uint16_t appkey_index;

    /** Remote SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;

    /**
     * Local SIG Model ID or Vendor Model ID.
     * Used only for MS_config_client_model_app_bind().
     */
    rm_ble_mesh_access_model_id_t client_model;

    /**
     * Local Element Handle where the above Client Model ID
     * is to be searched.
     */
    rm_ble_mesh_access_element_handle_t element_handle;
} rm_mesh_config_clt_model_app_bind_parameter_t;

/**
 * Model App Unbind parameter structure
 */
typedef struct st_rm_mesh_config_clt_model_app_unbind_parameter
{
    /** Remote Element Address */
    uint16_t element_address;

    /** Index of the AppKey */
    uint16_t appkey_index;

    /** Remote SIG Model ID or Vendor Model ID */
    rm_ble_mesh_access_model_id_t model;

    /**
     * Local SIG Model ID or Vendor Model ID.
     * Used only for MS_config_client_model_app_unbind().
     */
    rm_ble_mesh_access_model_id_t client_model;

    /**
     * Local Element Handle where the above Client Model ID
     * is to be searched.
     */
    rm_ble_mesh_access_element_handle_t element_handle;
} rm_mesh_config_clt_model_app_unbind_parameter_t;

/**
 * SIG Model App Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_sig_model_app_get_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** SIG Model ID */
    rm_ble_mesh_access_model_id_sig_t model_id;
} rm_mesh_config_clt_sig_model_app_get_parameter_t;

/**
 * Vendor Model App Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_vendor_model_app_get_parameter
{
    /** Address of the element */
    uint16_t element_address;

    /** Vendor Model ID */
    rm_ble_mesh_access_model_id_vendor_t model_id;
} rm_mesh_config_clt_vendor_model_app_get_parameter_t;

/**
 * Friend Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_friend_set_parameter
{
    /** New Friend state */
    uint8_t friend;
} rm_mesh_config_clt_friend_set_parameter_t;

/**
 * Key Refresh Phase Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_key_refresh_phase_get_parameter
{
    /** Netkey Index */
    uint16_t netkey_index;
} rm_mesh_config_clt_key_refresh_phase_get_parameter_t;

/**
 * Key Refresh Phase Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_key_refresh_phase_set_parameter
{
    /** Netkey Index */
    uint16_t netkey_index;

    /** New Key Refresh Phase Transition */
    uint8_t transition;
} rm_mesh_config_clt_key_refresh_phase_set_parameter_t;

/**
 * Heartbeat Publication Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_heartbeat_publication_set_parameter
{
    /** Destination address for Heartbeat messages */
    uint16_t destination;

    /** Number of Heartbeat messages to be sent */
    uint8_t countlog;

    /** Period for sending Heartbeat messages */
    uint8_t periodlog;

    /** TTL to be used when sending Heartbeat messages */
    uint8_t ttl;

    /**
     * Bit field indicating features that trigger
     * Heartbeat messages when changed
     */
    uint16_t features;

    /** Netkey Index */
    uint16_t netkey_index;
} rm_mesh_config_clt_heartbeat_publication_set_parameter_t;

/**
 * Heartbeat Subscription Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_heartbeat_subscription_set_parameter
{
    /** Source address for Heartbeat messages */
    uint16_t source;

    /** Destination address for Heartbeat messages */
    uint16_t destination;

    /** Period for receiving Heartbeat messages */
    uint8_t periodlog;
} rm_mesh_config_clt_heartbeat_subscription_set_parameter_t;

/**
 * Low Power Node PollTimeout Get parameter structure
 */
typedef struct st_rm_mesh_config_clt_low_power_node_polling_timeout_get_parameter
{
    /** The unicast address of the Low Power node */
    uint16_t lpn_address;
} rm_mesh_config_clt_low_power_node_polling_timeout_get_parameter_t;

/**
 * Network Transmit Set parameter structure
 */
typedef struct st_rm_mesh_config_clt_network_transmit_set_parameter
{
    /**
     * Number of transmissions for each Network PDU
     * originating from the node
     * - 3 bits validity
     */
    uint8_t net_tx_count;

    /**
     * Number of 10-millisecond steps between transmissions
     * - 5 bits validity
     */
    uint8_t net_tx_interval_steps;
} rm_mesh_config_clt_network_transmit_set_parameter_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_CONFIG_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh config instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_CONFIG_CLT_Open() is called. */
typedef struct st_rm_mesh_config_clt_clt_instance_ctrl
{
    uint32_t open;                                 // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;

    rm_ble_mesh_config_client_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_config_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_config_client_api_t g_rm_ble_mesh_config_client_on_rm_mesh_config_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_CONFIG_CLT_Open(rm_ble_mesh_config_client_ctrl_t * const      p_ctrl,
                                  rm_ble_mesh_config_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_CONFIG_CLT_Close(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_SetServer(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                       rm_ble_mesh_network_address_t            server_addr,
                                       uint8_t                                * p_dev_key);
fsp_err_t RM_MESH_CONFIG_CLT_SendReliablePdu(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                             uint32_t                                 req_opcode,
                                             void const * const                       parameter,
                                             uint32_t                                 rsp_opcode);
fsp_err_t RM_MESH_CONFIG_CLT_BeaconGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_BeaconSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_CompositionDataGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_DefaultTtlGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_DefaultTtlSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                           void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_GattProxyGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_GattProxySet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_RelayGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_RelaySet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelPublicationGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                 void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelPublicationSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                 void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelPublicationVaddrSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                      void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionAdd(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                  void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionVaddrAdd(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                       void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionDelete(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                     void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionVaddrDelete(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionOverwrite(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                        void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionVaddrOverwrite(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                             void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelSubscriptionDeleteAll(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                        void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_SigModelSubscriptionGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                     void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_VendorModelSubscriptionGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                        void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NetkeyAdd(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NetkeyUpdate(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NetkeyDelete(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NetkeyGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_AppkeyAdd(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_AppkeyUpdate(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_AppkeyDelete(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_AppkeyGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NodeIdentityGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                             void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NodeIdentitySet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                             void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelAppBind(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                          void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_ModelAppUnbind(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                            void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_SigModelAppGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                            void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_VendorModelAppGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                               void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NodeReset(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_FriendGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_FriendSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_KeyrefreshPhaseGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_KeyrefreshPhaseSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_HeartbeatPublicationGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_HeartbeatPublicationSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                     void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_HeartbeatSubscriptionGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_HeartbeatSubscriptionSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                      void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_LpnPolltimeoutGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                               void const * const                       p_parameter);
fsp_err_t RM_MESH_CONFIG_CLT_NetworkTransmitGet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_CONFIG_CLT_NetworkTransmitSet(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,
                                                void const * const                       p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_CONFIG_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_CONFIG_CLT_H
