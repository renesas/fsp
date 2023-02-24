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

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_BLE_MESH_ACCESS RM_BLE_MESH_ACCESS
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_MESH_ACCESS_H
#define RM_BLE_MESH_ACCESS_H

#include "bsp_api.h"

#include "rm_ble_mesh_access_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RM_BLE_MESH_ACCESS private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_ACCESS_Open() is called. */
typedef struct st_rm_ble_mesh_access_instance_ctrl
{
    uint32_t open;                                      // Indicates whether the open() API has been successfully called.
    rm_ble_mesh_access_node_id_t        node_id;        // Node ID
    rm_ble_mesh_access_element_handle_t element_handle; // DEPRECATED Element handle
    rm_ble_mesh_access_cfg_t const    * p_cfg;          // Pointer to initial configurations.
    void const * p_context;                             // Placeholder for user data.
} rm_ble_mesh_access_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_access_api_t g_rm_ble_mesh_access_on_rm_ble_mesh_access;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_MESH_ACCESS_Open(rm_ble_mesh_access_ctrl_t * const      p_ctrl,
                                  rm_ble_mesh_access_cfg_t const * const p_cfg);
fsp_err_t RM_BLE_MESH_ACCESS_Close(rm_ble_mesh_access_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_ACCESS_RegisterModel(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                           rm_ble_mesh_access_model_t const * const  p_model,
                                           rm_ble_mesh_access_model_handle_t * const p_model_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetElementHandle(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                              rm_ble_mesh_network_address_t               elem_addr,
                                              rm_ble_mesh_access_element_handle_t * const p_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetElementHandleForModelHandle(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                                            rm_ble_mesh_access_model_handle_t           model_handle,
                                                            rm_ble_mesh_access_element_handle_t * const p_elem_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetModelHandle(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                            rm_ble_mesh_access_element_handle_t       elem_handle,
                                            rm_ble_mesh_access_model_id_t             model_id,
                                            rm_ble_mesh_access_model_handle_t * const p_handle);
fsp_err_t RM_BLE_MESH_ACCESS_Publish(rm_ble_mesh_access_ctrl_t * const               p_ctrl,
                                     rm_ble_mesh_access_model_handle_t const * const p_handle,
                                     rm_ble_mesh_access_req_msg_raw_t const * const  p_publish_message,
                                     uint8_t                                         reliable);
fsp_err_t RM_BLE_MESH_ACCESS_ReliablePublish(rm_ble_mesh_access_ctrl_t * const               p_ctrl,
                                             rm_ble_mesh_access_model_handle_t const * const p_handle,
                                             rm_ble_mesh_access_req_msg_raw_t const * const  p_publish_message,
                                             uint32_t                                        rsp_opcode);
fsp_err_t RM_BLE_MESH_ACCESS_Reply(rm_ble_mesh_access_ctrl_t * const                        p_ctrl,
                                   rm_ble_mesh_access_model_req_msg_context_t const * const p_req_msg_context,
                                   uint8_t                                                  ttl,
                                   rm_ble_mesh_access_req_msg_raw_t const * const           p_req_msg_raw);
fsp_err_t RM_BLE_MESH_ACCESS_ReplyAndPublish(rm_ble_mesh_access_ctrl_t * const                        p_ctrl,
                                             rm_ble_mesh_access_model_req_msg_context_t const * const p_req_msg_context,
                                             rm_ble_mesh_access_req_msg_raw_t const * const           p_req_msg_raw,
                                             rm_ble_mesh_access_publish_setting_t const * const       p_publish_setting);
fsp_err_t RM_BLE_MESH_ACCESS_SendPdu(rm_ble_mesh_access_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_access_pdu_t const * const p_pdu,
                                     uint8_t                                reliable);
fsp_err_t RM_BLE_MESH_ACCESS_GetCompositionData(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                rm_ble_mesh_buffer_t * const      p_buffer);
fsp_err_t RM_BLE_MESH_ACCESS_Reset(rm_ble_mesh_access_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_ACCESS_GetElementCount(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_count);
fsp_err_t RM_BLE_MESH_ACCESS_SetPrimaryUnicastAddress(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                      rm_ble_mesh_network_address_t     addr);
fsp_err_t RM_BLE_MESH_ACCESS_GetPrimaryUnicastAddress(rm_ble_mesh_access_ctrl_t * const     p_ctrl,
                                                      rm_ble_mesh_network_address_t * const p_addr);
fsp_err_t RM_BLE_MESH_ACCESS_SetDefaultTtl(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t ttl);
fsp_err_t RM_BLE_MESH_ACCESS_GetDefaultTtl(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t const * const p_ttl);
fsp_err_t RM_BLE_MESH_ACCESS_SetIvIndex(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                        uint32_t                          iv_index,
                                        uint8_t                           iv_update_flag);
fsp_err_t RM_BLE_MESH_ACCESS_GetIvIndex(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                        uint32_t * const                  p_iv_index,
                                        uint8_t * const                   p_iv_update_flag);
fsp_err_t RM_BLE_MESH_ACCESS_GetIvIndexByIvi(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                             uint8_t                           ivi,
                                             uint32_t * const                  p_iv_index);
fsp_err_t RM_BLE_MESH_ACCESS_SetFeaturesField(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t enable,
                                              uint8_t feature);
fsp_err_t RM_BLE_MESH_ACCESS_GetFeaturesField(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                              uint8_t * const                   p_enable,
                                              uint8_t                           feature);
fsp_err_t RM_BLE_MESH_ACCESS_GetFeatures(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_features);
fsp_err_t RM_BLE_MESH_ACCESS_GetFriendshipRole(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_friend_role);
fsp_err_t RM_BLE_MESH_ACCESS_SetFriendshipRole(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t friend_role);
fsp_err_t RM_BLE_MESH_ACCESS_AddDeviceKey(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                          uint8_t const * const             p_dev_key,
                                          rm_ble_mesh_network_address_t     uaddr,
                                          uint8_t                           num_elements);
fsp_err_t RM_BLE_MESH_ACCESS_GetDeviceKey(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                          uint8_t                           dev_key_index,
                                          uint8_t ** const                  p_dev_key);
fsp_err_t RM_BLE_MESH_ACCESS_RemoveAllDeviceKeys(rm_ble_mesh_access_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_ACCESS_GetProvisionedDeviceList(
    rm_ble_mesh_access_ctrl_t * const                           p_ctrl,
    rm_ble_mesh_access_provisioned_device_entry_t const * const p_prov_dev_list,
    uint16_t * const                                            p_num_entries);
fsp_err_t RM_BLE_MESH_ACCESS_GetDeviceKeyHandle(rm_ble_mesh_access_ctrl_t * const              p_ctrl,
                                                rm_ble_mesh_network_address_t                  prim_elem_uaddr,
                                                rm_ble_mesh_access_device_key_handle_t * const p_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetAppKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                       rm_ble_mesh_network_appkey_handle_t appkey_handle,
                                       uint8_t ** const                    p_app_key,
                                       uint8_t * const                     p_aid);
fsp_err_t RM_BLE_MESH_ACCESS_AddUpdateNetkey(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                             uint16_t                          netkey_index,
                                             uint32_t                          opcode,
                                             uint8_t const * const             p_net_key);
fsp_err_t RM_BLE_MESH_ACCESS_AddFriendSecurityCredential(rm_ble_mesh_access_ctrl_t * const                    p_ctrl,
                                                         rm_ble_mesh_network_subnet_handle_t                  subnet_handle,
                                                         uint16_t                                             friend_index,
                                                         rm_ble_mesh_access_friend_security_credential_info_t info);
fsp_err_t RM_BLE_MESH_ACCESS_DeleteFriendSecurityCredential(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                            rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                                            uint16_t                            friend_index);
fsp_err_t RM_BLE_MESH_ACCESS_FindSubnet(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                        uint16_t                                    netkey_index,
                                        rm_ble_mesh_network_subnet_handle_t * const p_subnet_handle);
fsp_err_t RM_BLE_MESH_ACCESS_FindMasterSubnet(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                              rm_ble_mesh_network_subnet_handle_t         friend_subnet_handle,
                                              rm_ble_mesh_network_subnet_handle_t * const p_master_subnet_handle);
fsp_err_t RM_BLE_MESH_ACCESS_DeleteNetKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                          rm_ble_mesh_network_subnet_handle_t subnet_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetNetKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                       rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                       uint8_t * const                     p_net_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetNetKeyIndexList(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                uint16_t * const                  p_netkey_count,
                                                uint16_t * const                  p_netkey_index_list);
fsp_err_t RM_BLE_MESH_ACCESS_LookUpNid(rm_ble_mesh_access_ctrl_t * const            p_ctrl,
                                       uint8_t                                      nid,
                                       rm_ble_mesh_network_subnet_handle_t * const  p_subnet_handle,
                                       rm_ble_mesh_access_associated_keys_t * const p_key_set);
fsp_err_t RM_BLE_MESH_ACCESS_LookUpNetworkId(rm_ble_mesh_access_ctrl_t * const            p_ctrl,
                                             uint8_t const * const                        p_network_id,
                                             rm_ble_mesh_network_subnet_handle_t * const  p_subnet_handle,
                                             rm_ble_mesh_access_associated_keys_t * const p_key_set);
fsp_err_t RM_BLE_MESH_ACCESS_LookUpAid(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                       uint8_t                                     aid,
                                       rm_ble_mesh_network_appkey_handle_t * const p_appkey_handle,
                                       uint8_t * const                             p_app_key);
fsp_err_t RM_BLE_MESH_ACCESS_SetProvisioningData(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                                 rm_ble_mesh_provision_data_t const * const p_prov_data);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetNid(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                          rm_ble_mesh_network_subnet_handle_t handle,
                                          uint8_t * const                     p_nid);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetPrivacyKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                 rm_ble_mesh_network_subnet_handle_t handle,
                                                 uint8_t * const                     p_privacy_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetNetworkId(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_network_subnet_handle_t handle,
                                                uint8_t * const                     p_network_id);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetBeaconKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_network_subnet_handle_t handle,
                                                uint8_t * const                     p_beacon_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetIdentityKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                  rm_ble_mesh_network_subnet_handle_t handle,
                                                  uint8_t * const                     p_identity_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetSubnetEncryptionKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                    rm_ble_mesh_network_subnet_handle_t handle,
                                                    uint8_t * const                     p_encrypt_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetNodeIdentity(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                             rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                             uint8_t * const                     p_id_state);
fsp_err_t RM_BLE_MESH_ACCESS_SetNodeIdentity(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                             rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                             uint8_t * const                     p_id_state);
fsp_err_t RM_BLE_MESH_ACCESS_GetKeyRefreshPhase(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                                uint8_t * const                     p_key_refresh_state);
fsp_err_t RM_BLE_MESH_ACCESS_SetKeyRefreshPhase(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                                uint8_t const * const               p_key_refresh_state);
fsp_err_t RM_BLE_MESH_ACCESS_SetTransmitState(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                              uint8_t                           tx_state_type,
                                              uint8_t                           tx_state);
fsp_err_t RM_BLE_MESH_ACCESS_GetTransmitState(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                              uint8_t                           tx_state_type,
                                              uint8_t * const                   p_tx_state);
fsp_err_t RM_BLE_MESH_ACCESS_AddAppKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                       rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                       uint16_t                            appkey_index,
                                       uint8_t const * const               p_app_key);
fsp_err_t RM_BLE_MESH_ACCESS_UpdateAppKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                          rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                          uint16_t                            appkey_index,
                                          uint8_t const * const               p_app_key);
fsp_err_t RM_BLE_MESH_ACCESS_DeleteAppKey(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                          rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                          uint16_t                            appkey_index,
                                          uint8_t const * const               p_app_key);
fsp_err_t RM_BLE_MESH_ACCESS_GetAppKeyHandle(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                             rm_ble_mesh_network_subnet_handle_t         subnet_handle,
                                             uint16_t                                    appkey_index,
                                             uint8_t const * const                       p_app_key,
                                             rm_ble_mesh_network_appkey_handle_t * const p_appkey_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetAppKeyIndexList(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                                uint16_t * const                    p_appkey_count,
                                                uint16_t * const                    p_appkey_index_list);
fsp_err_t RM_BLE_MESH_ACCESS_BindModelWithAppKey(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t model_handle,
                                                 uint16_t                          appkey_index);
fsp_err_t RM_BLE_MESH_ACCESS_UnbindModelWithAppKey(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                   rm_ble_mesh_access_model_handle_t model_handle,
                                                   uint16_t                          appkey_index);
fsp_err_t RM_BLE_MESH_ACCESS_GetModelAppKeyList(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                rm_ble_mesh_access_model_handle_t model_handle,
                                                uint16_t * const                  p_appkey_count,
                                                uint16_t * const                  p_appkey_index_list);
fsp_err_t RM_BLE_MESH_ACCESS_SetModelPublication(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t         model_handle,
                                                 rm_ble_mesh_access_publish_info_t * const p_publish_info);
fsp_err_t RM_BLE_MESH_ACCESS_SetModelPublicationPeriodDivisor(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                              rm_ble_mesh_access_model_handle_t model_handle,
                                                              uint8_t                           period_divisor);
fsp_err_t RM_BLE_MESH_ACCESS_GetModelPublication(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t         model_handle,
                                                 rm_ble_mesh_access_publish_info_t * const p_publish_info);
fsp_err_t RM_BLE_MESH_ACCESS_AddModelSubscription(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                                  rm_ble_mesh_access_model_handle_t          model_handle,
                                                  rm_ble_mesh_access_address_t const * const p_sub_addr);
fsp_err_t RM_BLE_MESH_ACCESS_DeleteModelSubscription(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                                     rm_ble_mesh_access_model_handle_t          model_handle,
                                                     rm_ble_mesh_access_address_t const * const p_sub_addr);
fsp_err_t RM_BLE_MESH_ACCESS_DeleteAllModelSubscription(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                        rm_ble_mesh_access_model_handle_t model_handle);
fsp_err_t RM_BLE_MESH_ACCESS_GetModelSubscriptionList(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                      rm_ble_mesh_access_model_handle_t model_handle,
                                                      uint16_t * const                  p_sub_addr_count,
                                                      uint16_t * const                  p_sub_addr_list);
fsp_err_t RM_BLE_MESH_ACCESS_GetAllModelSubscriptionList(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                         uint16_t * const                  p_sub_addr_count,
                                                         uint16_t * const                  p_sub_addr_list);
fsp_err_t RM_BLE_MESH_ACCESS_IsValidElementAddress(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                   rm_ble_mesh_network_address_t     addr);
fsp_err_t RM_BLE_MESH_ACCESS_IsFixedGroupAddressToBeProcessed(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                              rm_ble_mesh_network_address_t     addr);
fsp_err_t RM_BLE_MESH_ACCESS_IsValidSubscriptionAddress(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                        rm_ble_mesh_network_address_t     addr);
fsp_err_t RM_BLE_MESH_ACCESS_EnableIvUpdateTestMode(rm_ble_mesh_access_ctrl_t * const        p_ctrl,
                                                    rm_ble_mesh_access_iv_update_test_mode_t mode);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_ACCESS_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLE_MESH_ACCESS)
 **********************************************************************************************************************/
