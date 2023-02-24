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

#ifndef RM_BLE_MESH_ACCESS_API_H
#define RM_BLE_MESH_ACCESS_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_ACCESS_API BLE Mesh Access Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Access functions.
 *
 * @section   RM_BLE_MESH_ACCESS_API_Summary Summary
 * The BLE Mesh Access interface for the Bluetooth Low Energy Mesh Network Access (BLE MESH ACCESS) peripheral provides Bluetooth Low Energy Mesh Network Access functionality.
 *
 * The Bluetooth Low Energy Mesh Network Access interface can be implemented by:
 * - @ref RM_BLE_MESH_ACCESS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "rm_ble_mesh_upper_trans_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define RM_BLE_MESH_ACCESS_LABEL_UUID_LENGTH        16

/** Array sizes for use in the Access layer */
/** Size of Virtual Address (Label UUID) */
#define RM_BLE_MESH_ACCESS_VADDR_LABEL_UUID_SIZE    16

/** Size of NetKey */
#define RM_BLE_MESH_ACCESS_NETKEY_SIZE              16

/** Size of AppKey */
#define RM_BLE_MESH_ACCESS_APPKEY_SIZE              16

/** Size of Key */
#define RM_BLE_MESH_ACCESS_KEY_SIZE                 16

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Access Node ID */
typedef uint8_t rm_ble_mesh_access_node_id_t;

/** Access Element Handle */
typedef uint8_t rm_ble_mesh_access_element_handle_t;

/** Access Model Handle */
typedef uint16_t rm_ble_mesh_access_model_handle_t;

/** SIG Model ID */
typedef uint16_t rm_ble_mesh_access_model_id_sig_t;

/** Vendor Model ID */
typedef uint32_t rm_ble_mesh_access_model_id_vendor_t;

/** Access Address Handle */
typedef uint32_t rm_ble_mesh_access_address_handle_t;

/** Device Key Handle */
typedef uint32_t rm_ble_mesh_access_device_key_handle_t;

/** Model Specific Request Message Type: Get, Set or Others */
typedef enum e_rm_ble_mesh_access_model_req_msg_type
{
    /** Model Specific Request Message Type: Get */
    RM_BLE_MESH_ACCESS_MODEL_REQ_MSG_TYPE_GET = 0,

    /** Model Specific Request Message Type: Set */
    RM_BLE_MESH_ACCESS_MODEL_REQ_MSG_TYPE_SET = 1,

    /** Model Specific Request Message Type: Others */
    RM_BLE_MESH_ACCESS_MODEL_REQ_MSG_TYPE_OTHERS = 2,
} rm_ble_mesh_access_model_req_msg_type_t;

/** Test modes */
typedef enum e_rm_ble_mesh_access_iv_update_test_mode
{
    RM_BLE_MESH_ACCESS_IV_UPDATE_TEST_MODE_DISABLE = 0, ///< Test mode disable
    RM_BLE_MESH_ACCESS_IV_UPDATE_TEST_MODE_ENABLE  = 1, ///< Test mode enable
} rm_ble_mesh_access_iv_update_test_mode_t;

/** Opcodes of Model specific messages */
typedef enum e_rm_ble_mesh_access_message_opcode
{
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_ADD                   = 0x00,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_UPDATE                = 0x01,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_COMPOSITION_DATA_STATUS      = 0x02,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_PUBLICATION_SET        = 0x03,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_CURRENT_STATUS               = 0x04,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_STATUS                 = 0x05,
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_PUBLICATION_STATUS = 0x06,

    /** Config AppKey Delete Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_DELETE = 0x8000,

    /** Config AppKey Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_GET = 0x8001,

    /** Config AppKey List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_LIST = 0x8002,

    /** Config AppKey Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_APPKEY_STATUS = 0x8003,

    /** Health Attention Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_ATTENTION_GET = 0x8004,

    /** Health Attention Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_ATTENTION_SET = 0x8005,

    /** Health Attention Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_ATTENTION_SET_UNACKNOWLEDGED = 0x8006,

    /** Health Attention Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_ATTENTION_STATUS = 0x8007,

    /** Config Composition Data Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_COMPOSITION_DATA_GET = 0x8008,

    /** Config Beacon Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_BEACON_GET = 0x8009,

    /** Config Beacon Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_BEACON_SET = 0x800A,

    /** Config Beacon Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_BEACON_STATUS = 0x800B,

    /** Config Deafault TTL Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_DEFAULT_TTL_GET = 0x800C,

    /** Config Deafault TTL Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_DEFAULT_TTL_SET = 0x800D,

    /** Config Deafault TTL Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_DEFAULT_TTL_STATUS = 0x800E,

    /** Config Friend Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_FRIEND_GET = 0x800F,

    /** Config Friend Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_FRIEND_SET = 0x8010,

    /** Config Friend Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_FRIEND_STATUS = 0x8011,

    /** Config GATT Proxy Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_GATT_PROXY_GET = 0x8012,

    /** Config GATT Proxy Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_GATT_PROXY_SET = 0x8013,

    /** Config GATT Proxy Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_GATT_PROXY_STATUS = 0x8014,

    /** Config Key Refresh Phase Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_KEY_REFRESH_PHASE_GET = 0x8015,

    /** Config Key Refresh Phase Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_KEY_REFRESH_PHASE_SET = 0x8016,

    /** Config Key Refresh Phase Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_KEY_REFRESH_PHASE_STATUS = 0x8017,

    /** Config Model Publication Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_PUBLICATION_GET = 0x8018,

    /** Config Model Publication Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_PUBLICATION_STATUS = 0x8019,

    /** Config Model Publication Virtual Address Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET = 0x801A,

    /** Config Model Subscription Add Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_ADD = 0x801B,

    /** Config Model Subscription Delete Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_DELETE = 0x801C,

    /** Config Model Subscription Delete All Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_DELETE_ALL = 0x801D,

    /** Config Model Subscription Overwrite Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_OVERWRITE = 0x801E,

    /** Config Model Subscription Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_STATUS = 0x801F,

    /** Config Model Subscription Virtual Address Add Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD = 0x8020,

    /** Config Model Subscription Virtual Address Delete Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE = 0x8021,

    /** Config Model Subscription Virtual Address Overwrite Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE = 0x8022,

    /** Config Network Transmit Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETWORK_TRANSMIT_GET = 0x8023,

    /** Config Network Transmit Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETWORK_TRANSMIT_SET = 0x8024,

    /** Config Network Transmit Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETWORK_TRANSMIT_STATUS = 0x8025,

    /** Config Relay Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_RELAY_GET = 0x8026,

    /** Config Relay Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_RELAY_SET = 0x8027,

    /** Config Relay Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_RELAY_STATUS = 0x8028,

    /** Config SIG Model Subscription Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_SIG_MODEL_SUBSCRIPTION_GET = 0x8029,

    /** Config SIG Model Subscription List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_SIG_MODEL_SUBSCRIPTION_LIST = 0x802A,

    /** Config Vendor Model Subscription Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_VENDOR_MODEL_SUBSCRIPTION_GET = 0x802B,

    /** Config Vendor Model Subscription List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_VENDOR_MODEL_SUBSCRIPTION_LIST = 0x802C,

    /** Config Low Power Node PollTimeout Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_LOW_POWER_NODE_POLLTIMEOUT_GET = 0x802D,

    /** Config Low Power Node PollTimeout Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_LOW_POWER_NODE_POLLTIMEOUT_STATUS = 0x802E,

    /** Health Fault Clear Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_CLEAR = 0x802F,

    /** Health Fault Clear Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_CLEAR_UNACKNOWLEDGED = 0x8030,

    /** Health Fault Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_GET = 0x8031,

    /** Health Fault Test Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_TEST = 0x8032,

    /** Health Fault Test Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_FAULT_TEST_UNACKNOWLEDGED = 0x8033,

    /** Health Period Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_PERIOD_GET = 0x8034,

    /** Health Period Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_PERIOD_SET = 0x8035,

    /** Health Period Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_PERIOD_SET_UNACKNOWLEDGED = 0x8036,

    /** Health Period Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_HEALTH_PERIOD_STATUS = 0x8037,

    /** Config Heartbeat Publication Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_PUBLICATION_GET = 0x8038,

    /** Config Heartbeat Publication Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_PUBLICATION_SET = 0x8039,

    /** Config Heartbeat Subscription Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_SUBSCRIPTION_GET = 0x803A,

    /** Config Heartbeat Subscription Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_SUBSCRIPTION_SET = 0x803B,

    /** Config Heartbeat Subscription Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_HEARTBEAT_SUBSCRIPTION_STATUS = 0x803C,

    /** Config Model App Bind Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_APP_BIND = 0x803D,

    /** Config Model App Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_APP_STATUS = 0x803E,

    /** Config Model App Unbind Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_MODEL_APP_UNBIND = 0x803F,

    /** Config NetKey Add Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_ADD = 0x8040,

    /** Config NetKey Delete Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_DELETE = 0x8041,

    /** Config NetKey Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_GET = 0x8042,

    /** Config NetKey List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_LIST = 0x8043,

    /** Config NetKey Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_STATUS = 0x8044,

    /** Config NetKey Update Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NETKEY_UPDATE = 0x8045,

    /** Config Node Identity Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NODE_IDENTITY_GET = 0x8046,

    /** Config Node Identity Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NODE_IDENTITY_SET = 0x8047,

    /** Config Node Identity Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NODE_IDENTITY_STATUS = 0x8048,

    /** Config Node Reset Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NODE_RESET = 0x8049,

    /** Config Node Reset Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_NODE_RESET_STATUS = 0x804A,

    /** Config SIG Model App Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_SIG_MODEL_APP_GET = 0x804B,

    /** Config SIG Model App List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_SIG_MODEL_APP_LIST = 0x804C,

    /** Config Vendor Model App Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_VENDOR_MODEL_APP_GET = 0x804D,

    /** Config Vendor Model App List Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_CONFIG_VENDOR_MODEL_APP_LIST = 0x804E,

    /** Generic OnOff */
    /** Generic OnOff Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONOFF_GET = 0x8201,

    /** Generic OnOff Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONOFF_SET = 0x8202,

    /** Generic OnOff Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONOFF_SET_UNACKNOWLEDGED = 0x8203,

    /** Generic OnOff Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONOFF_STATUS = 0x8204,

    /** Generic Level */
    /** Generic Level Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LEVEL_GET = 0x8205,

    /** Generic Level Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LEVEL_SET = 0x8206,

    /** Generic Level Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LEVEL_SET_UNACKNOWLEDGED = 0x8207,

    /** Generic Level Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LEVEL_STATUS = 0x8208,

    /** Generic Delta Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DELTA_SET = 0x8209,

    /** Generic Delta Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DELTA_SET_UNACKNOWLEDGED = 0x820A,

    /** Generic Move Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MOVE_SET = 0x820B,

    /** Generic Move Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MOVE_SET_UNACKNOWLEDGED = 0x820C,

    /** Generic Default Transition Time */
    /** Generic Default Transition Time Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DEFAULT_TRANSITION_TIME_GET = 0x820D,

    /** Generic Default Transition Time Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DEFAULT_TRANSITION_TIME_SET = 0x820E,

    /** Generic Default Transition Time Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DEFAULT_TRANSITION_TIME_SET_UNACKNOWLEDGED = 0x820F,

    /** Generic Default Transition Time Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_DEFAULT_TRANSITION_TIME_STATUS = 0x8210,

    /** Generic Power OnOff */
    /** Generic Power OnOff Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONPOWERUP_GET = 0x8211,

    /** Generic Power OnOff Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONPOWERUP_STATUS = 0x8212,

    /** Generic Power OnOff Setup */
    /** Generic Power OnOff Setup Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONPOWERUP_SET = 0x8213,

    /** Generic Power OnOff Setup Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ONPOWERUP_SET_UNACKNOWLEDGED = 0x8214,

    /** Generic Power Level */
    /** Generic Power Level Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LEVEL_GET = 0x8215,

    /** Generic Power Level Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LEVEL_SET = 0x8216,

    /** Generic Power Level Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LEVEL_SET_UNACKNOWLEDGED = 0x8217,

    /** Generic Power Level Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LEVEL_STATUS = 0x8218,

    /** Generic Power Last Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LAST_GET = 0x8219,

    /** Generic Power Last Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_LAST_STATUS = 0x821A,

    /** Generic Power Default Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_DEFAULT_GET = 0x821B,

    /** Generic Power Default Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_DEFAULT_STATUS = 0x821C,

    /** Generic Power Range Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_RANGE_GET = 0x821D,

    /** Generic Power Range Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_RANGE_STATUS = 0x821E,

    /** Generic Power Level Setup */
    /** Generic Power Default Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_DEFAULT_SET = 0x821F,

    /** Generic Power Default Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_DEFAULT_SET_UNACKNOWLEDGED = 0x8220,

    /** Generic Power Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_RANGE_SET = 0x8221,

    /** Generic Power Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_POWER_RANGE_SET_UNACKNOWLEDGED = 0x8222,

    /** Generic Battery */
    /** Generic Battery Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_BATTERY_GET = 0x8223,

    /** Generic Battery Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_BATTERY_STATUS = 0x8224,

    /** Generic Location */
    /** Generic Location Global Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_GLOBAL_GET = 0x8225,

    /** Generic Location Global Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_GLOBAL_STATUS = 0x40,

    /** Generic Location Local Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_LOCAL_GET = 0x8226,

    /** Generic Location Local Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_LOCAL_STATUS = 0x8227,

    /** Generic Location Setup */
    /** Generic Location Global Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_GLOBAL_SET = 0x41,

    /** Generic Location Global Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_GLOBAL_SET_UNACKNOWLEDGED = 0x42,

    /** Generic Location Local Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_LOCAL_SET = 0x8228,

    /** Generic Location Local Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_LOCATION_LOCAL_SET_UNACKNOWLEDGED = 0x8229,

    /** Generic Manufacturer Property */
    /** Generic Manufacturer Properties Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTIES_GET = 0x822A,

    /** Generic Manufacturer Properties Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTIES_STATUS = 0x43,

    /** Generic Manufacturer Property Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTY_GET = 0x822B,

    /** Generic Manufacturer Property Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTY_SET = 0x44,

    /** Generic Manufacturer Property Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTY_SET_UNACKNOWLEDGED = 0x45,

    /** Generic Manufacturer Property Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_MANUFACTURER_PROPERTY_STATUS = 0x46,

    /** Generic Admin Property */
    /** Generic Admin Properties Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTIES_GET = 0x822C,

    /** Generic Admin Properties Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTIES_STATUS = 0x47,

    /** Generic Admin Property Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTY_GET = 0x822D,

    /** Generic Admin Property Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTY_SET = 0x48,

    /** Generic Admin Property Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTY_SET_UNACKNOWLEDGED = 0x49,

    /** Generic Admin Property Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_ADMIN_PROPERTY_STATUS = 0x4A,

    /** Generic User Property */
    /** Generic User Properties Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTIES_GET = 0x822E,

    /** Generic User Properties Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTIES_STATUS = 0x4B,

    /** Generic User Property Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTY_GET = 0x822F,

    /** Generic User Property Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTY_SET = 0x4C,

    /** Generic User Property Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTY_SET_UNACKNOWLEDGED = 0x4D,

    /** Generic User Property Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_USER_PROPERTY_STATUS = 0x4E,

    /** Generic Client Property */
    /** Generic Client Properties Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_CLIENT_PROPERTIES_GET = 0x4F,

    /** Generic Client Properties Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_GENERIC_CLIENT_PROPERTIES_STATUS = 0x50,

    /** Sensor */
    /** Sensor Descriptor Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_DESCRIPTOR_GET = 0x8230,

    /** Sensor Descriptor Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_DESCRIPTOR_STATUS = 0x51,

    /** Sensor Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_GET = 0x8231,

    /** Sensor Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_STATUS = 0x52,

    /** Sensor Column Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_COLUMN_GET = 0x8232,

    /** Sensor Column Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_COLUMN_STATUS = 0x53,

    /** Sensor Series Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SERIES_GET = 0x8233,

    /** Sensor Series Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SERIES_STATUS = 0x54,

    /** Sensor Setup */
    /** Sensor Cadence Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_CADENCE_GET = 0x8234,

    /** Sensor Cadence Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_CADENCE_SET = 0x55,

    /** Sensor Cadence Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_CADENCE_SET_UNACKNOWLEDGED = 0x56,

    /** Sensor Cadence Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_CADENCE_STATUS = 0x57,

    /** Sensor Settings Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTINGS_GET = 0x8235,

    /** Sensor Settings Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTINGS_STATUS = 0x58,

    /** Sensor Setting Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTING_GET = 0x8236,

    /** Sensor Setting Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTING_SET = 0x59,

    /** Sensor Setting Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTING_SET_UNACKNOWLEDGED = 0x5A,

    /** Sensor Setting Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SENSOR_SETTING_STATUS = 0x5B,

    /** Time */
    /** Time Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_GET = 0x8237,

    /** Time Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_SET = 0x5C,

    /** Time Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_STATUS = 0x5D,

    /** Time Role Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ROLE_GET = 0x8238,

    /** Time Role Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ROLE_SET = 0x8239,

    /** Time Role Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ROLE_STATUS = 0x823A,

    /** Time Zone Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ZONE_GET = 0x823B,

    /** Time Zone Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ZONE_SET = 0x823C,

    /** Time Zone Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TIME_ZONE_STATUS = 0x823D,

    /** Time - TAI UTC Delta Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TAI_UTC_DELTA_GET = 0x823E,

    /** Time - TAI UTC Delta Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TAI_UTC_DELTA_SET = 0x823F,

    /** Time - TAI UTC Delta Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_TAI_UTC_DELTA_STATUS = 0x8240,

    /** Scene */
    /** Scene Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_GET = 0x8241,

    /** Scene Recall Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_RECALL = 0x8242,

    /** Scene Recall Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_RECALL_UNACKNOWLEDGED = 0x8243,

    /** Scene Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_STATUS = 0x5E,

    /** Scene Register Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_REGISTER_GET = 0x8244,

    /** Scene Register Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_REGISTER_STATUS = 0x8245,

    /** Scene Setup */
    /** Scene Store Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_STORE = 0x8246,

    /** Scene Store Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_STORE_UNACKNOWLEDGED = 0x8247,

    /** Scene Delete Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_DELETE = 0x829E,

    /** Scene Delete Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCENE_DELETE_UNACKNOWLEDGED = 0x829F,

    /** Scheduler */
    /** Scheduler Action Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_ACTION_GET = 0x8248,

    /** Scheduler Action Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_ACTION_STATUS = 0x5F,

    /** Scheduler Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_GET = 0x8249,

    /** Scheduler Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_STATUS = 0x824A,

    /** Scheduler Setup */
    /** Scheduler Action Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_ACTION_SET = 0x60,

    /** Scheduler Action Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_SCHEDULER_ACTION_SET_UNACKNOWLEDGED = 0x61,

    /** Light Lightness */
    /** Light Lightness Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_GET = 0x824B,

    /** Light Lightness Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_SET = 0x824C,

    /** Light Lightness Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_SET_UNACKNOWLEDGED = 0x824D,

    /** Light Lightness Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_STATUS = 0x824E,

    /** Light Lightness Linear Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LINEAR_GET = 0x824F,

    /** Light Lightness Linear Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LINEAR_SET = 0x8250,

    /** Light Lightness Linear Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LINEAR_SET_UNACKNOWLEDGED = 0x8251,

    /** Light Lightness Linear Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LINEAR_STATUS = 0x8252,

    /** Light Lightness Last Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LAST_GET = 0x8253,

    /** Light Lightness Last Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_LAST_STATUS = 0x8254,

    /** Light Lightness Default Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_DEFAULT_GET = 0x8255,

    /** Light Lightness Default Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_DEFAULT_STATUS = 0x8256,

    /** Light Lightness Range Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_RANGE_GET = 0x8257,

    /** Light Lightness Range Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_RANGE_STATUS = 0x8258,

    /** Light Lightness Setup */
    /** Light Lightness Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_DEFAULT_SET = 0x8259,

    /** Light Lightness Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_DEFAULT_SET_UNACKNOWLEDGED = 0x825A,

    /** Light Lightness Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_RANGE_SET = 0x825B,

    /** Light Lightness Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LIGHTNESS_RANGE_SET_UNACKNOWLEDGED = 0x825C,

    /** Light CTL */
    /** Light CTL Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_GET = 0x825D,

    /** Light CTL Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_SET = 0x825E,

    /** Light CTL Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_SET_UNACKNOWLEDGED = 0x825F,

    /** Light CTL Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_STATUS = 0x8260,

    /** Light CTL Temperature Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_GET = 0x8261,

    /** Light CTL Temperature Range Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_RANGE_GET = 0x8262,

    /** Light CTL Temperature Range Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_RANGE_STATUS = 0x8263,

    /** Light CTL Temperature Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_SET = 0x8264,

    /** Light CTL Temperature Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_SET_UNACKNOWLEDGED = 0x8265,

    /** Light CTL Temperature Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_STATUS = 0x8266,

    /** Light CTL Default Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_DEFAULT_GET = 0x8267,

    /** Light CTL Default Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_DEFAULT_STATUS = 0x8268,

    /** Light CTL Setup */
    /** Light CTL Default Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_DEFAULT_SET = 0x8269,

    /** Light CTL Default Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_DEFAULT_SET_UNACKNOWLEDGED = 0x826A,

    /** Light CTL Default Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_RANGE_SET = 0x826B,

    /** Light CTL Default Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_CTL_TEMPERATURE_RANGE_SET_UNACKNOWLEDGED = 0x826C,

    /** Light HSL */
    /** Light HSL Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_GET = 0x826D,

    /** Light HSL HUE Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_HUE_GET = 0x826E,

    /** Light HSL HUE Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_HUE_SET = 0x826F,

    /** Light HSL HUE Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_HUE_SET_UNACKNOWLEDGED = 0x8270,

    /** Light HSL HUE Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_HUE_STATUS = 0x8271,

    /** Light HSL Saturation Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SATURATION_GET = 0x8272,

    /** Light HSL Saturation Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SATURATION_SET = 0x8273,

    /** Light HSL Saturation Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SATURATION_SET_UNACKNOWLEDGED = 0x8274,

    /** Light HSL Saturation Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SATURATION_STATUS = 0x8275,

    /** Light HSL Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SET = 0x8276,

    /** Light HSL Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_SET_UNACKNOWLEDGED = 0x8277,

    /** Light HSL Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_STATUS = 0x8278,

    /** Light HSL Target Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_TARGET_GET = 0x8279,

    /** Light HSL Target Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_TARGET_STATUS = 0x827A,

    /** Light HSL Default Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_DEFAULT_GET = 0x827B,

    /** Light HSL Default Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_DEFAULT_STATUS = 0x827C,

    /** Light HSL Range Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_RANGE_GET = 0x827D,

    /** Light HSL Range Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_RANGE_STATUS = 0x827E,

    /** Light HSL Setup */
    /** Light HSL Default Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_DEFAULT_SET = 0x827F,

    /** Light HSL Default Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_DEFAULT_SET_UNACKNOWLEDGED = 0x8280,

    /** Light HSL Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_RANGE_SET = 0x8281,

    /** Light HSL Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_HSL_RANGE_SET_UNACKNOWLEDGED = 0x8282,

    /** Light xyL */
    /** Light xyL Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_GET = 0x8283,

    /** Light xyL Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_SET = 0x8284,

    /** Light xyL Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_SET_UNACKNOWLEDGED = 0x8285,

    /** Light xyL Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_STATUS = 0x8286,

    /** Light xyL Target Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_TARGET_GET = 0x8287,

    /** Light xyL Target Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_TARGET_STATUS = 0x8288,

    /** Light xyL Default Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_DEFAULT_GET = 0x8289,

    /** Light xyL Default Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_DEFAULT_STATUS = 0x828A,

    /** Light xyL Range Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_RANGE_GET = 0x828B,

    /** Light xyL Range Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_RANGE_STATUS = 0x828C,

    /** Light xyL Setup */
    /** Light xyL Default Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_DEFAULT_SET = 0x828D,

    /** Light xyL Default Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_DEFAULT_SET_UNACKNOWLEDGED = 0x828E,

    /** Light xyL Range Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_RANGE_SET = 0x828F,

    /** Light xyL Range Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_XYL_RANGE_SET_UNACKNOWLEDGED = 0x8290,

    /** Light Control */
    /** Light LC Mode Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_MODE_GET = 0x8291,

    /** Light LC Mode Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_MODE_SET = 0x8292,

    /** Light LC Mode Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_MODE_SET_UNACKNOWLEDGED = 0x8293,

    /** Light LC Mode Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_MODE_STATUS = 0x8294,

    /** Light LC Occupancy Mode Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_OM_GET = 0x8295,

    /** Light LC Occupancy Mode Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_OM_SET = 0x8296,

    /** Light LC Occupancy Mode Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_OM_SET_UNACKNOWLEDGED = 0x8297,

    /** Light LC Occupancy Mode Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_OM_STATUS = 0x8298,

    /** Light LC Light OnOff Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_LIGHT_ONOFF_GET = 0x8299,

    /** Light LC Light OnOff Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_LIGHT_ONOFF_SET = 0x829A,

    /** Light LC Light OnOff Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_LIGHT_ONOFF_SET_UNACKNOWLEDGED = 0x829B,

    /** Light LC Light OnOff Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_LIGHT_ONOFF_STATUS = 0x829C,

    /** Light LC Property Get Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_PROPERTY_GET = 0x829D,

    /** Light LC Property Set Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_PROPERTY_SET = 0x62,

    /** Light LC Property Set Unacknowledged Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_PROPERTY_SET_UNACKNOWLEDGED = 0x63,

    /** Light LC Property Status Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_LIGHT_LC_PROPERTY_STATUS = 0x64,

    /** Invalid Opcode */
    RM_BLE_MESH_ACCESS_MESSAGE_OPCODE_INVALID = 0xFFFFFFFF,
} rm_ble_mesh_access_message_opcode_t;

/** Model type information */
typedef enum e_rm_ble_mesh_access_model_type_info
{
    /** Model type - SIG */
    RM_BLE_MESH_ACCESS_MODEL_TYPE_INFO_SIG = 0x00,

    /** Model type - VENDOR  */
    RM_BLE_MESH_ACCESS_MODEL_TYPE_INFO_VENDOR = 0x01,
} rm_ble_mesh_access_model_type_info_t;

/** Model ID information */
typedef enum e_rm_ble_mesh_access_model_id_info
{
    /** Model ID - Config Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_CONFIG_SERVER = 0x0000,

    /** Model ID - Config Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_CONFIG_CLIENT = 0x0001,

    /** Model ID - Health Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_HEALTH_SERVER = 0x0002,

    /** Model ID - Health Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_HEALTH_CLIENT = 0x0003,

    /** Generic */
    /** Model ID - Generic OnOff Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_ONOFF_SERVER = 0x1000,

    /** Model ID - Generic OnOff Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_ONOFF_CLIENT = 0x1001,

    /** Model ID - Generic Level Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_LEVEL_SERVER = 0x1002,

    /** Model ID - Generic Level Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_LEVEL_CLIENT = 0x1003,

    /** Model ID - Generic Default Transition Time Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_DEFAULT_TRANSITION_TIME_SERVER = 0x1004,

    /** Model ID - Generic Default Transition Time Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_DEFAULT_TRANSITION_TIME_CLIENT = 0x1005,

    /** Model ID - Generic Power OnOff Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_ONOFF_SERVER = 0x1006,

    /** Model ID - Generic Power OnOff Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_ONOFF_SETUP_SERVER = 0x1007,

    /** Model ID - Generic Power OnOff Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_ONOFF_CLIENT = 0x1008,

    /** Model ID - Generic Power Level Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_LEVEL_SERVER = 0x1009,

    /** Model ID - Generic Power Level Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_LEVEL_SETUP_SERVER = 0x100A,

    /** Model ID - Generic Power Level Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_POWER_LEVEL_CLIENT = 0x100B,

    /** Model ID - Generic Battery Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_BATTERY_SERVER = 0x100C,

    /** Model ID - Generic Battery Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_BATTERY_CLIENT = 0x100D,

    /** Model ID - Generic Location Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_LOCATION_SERVER = 0x100E,

    /** Model ID - Generic Location Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_LOCATION_SETUP_SERVER = 0x100F,

    /** Model ID - Generic Location Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_LOCATION_CLIENT = 0x1010,

    /** Model ID - Generic Admin Property Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_ADMIN_PROPERTY_SERVER = 0x1011,

    /** Model ID - Generic Manufacturer Property Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_MANUFACTURER_PROPERTY_SERVER = 0x1012,

    /** Model ID - Generic User Property Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_USER_PROPERTY_SERVER = 0x1013,

    /** Model ID - Generic Client Property Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_CLIENT_PROPERTY_SERVER = 0x1014,

    /** Model ID - Generic Property Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_GENERIC_PROPERTY_CLIENT = 0x1015,

    /** Sensors */
    /** Model ID - Sensor Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SENSOR_SERVER = 0x1100,

    /** Model ID - Sensor Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SENSOR_SETUP_SERVER = 0x1101,

    /** Model ID - Sensor Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SENSOR_CLIENT = 0x1102,

    /** Time and Scenes */
    /** Model ID - Time Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_TIME_SERVER = 0x1200,

    /** Model ID - Time Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_TIME_SETUP_SERVER = 0x1201,

    /** Model ID - Time Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_TIME_CLIENT = 0x1202,

    /** Model ID - Scene Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCENE_SERVER = 0x1203,

    /** Model ID - Scene Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCENE_SETUP_SERVER = 0x1204,

    /** Model ID - Scene Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCENE_CLIENT = 0x1205,

    /** Model ID - Scheduler Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCHEDULER_SERVER = 0x1206,

    /** Model ID - Scheduler Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCHEDULER_SETUP_SERVER = 0x1207,

    /** Model ID - Scheduler Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_SCHEDULER_CLIENT = 0x1208,

    /** Lighting */
    /** Model ID - Light Lightness Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LIGHTNESS_SERVER = 0x1300,

    /** Model ID - Light Lightness Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LIGHTNESS_SETUP_SERVER = 0x1301,

    /** Model ID - Light Lightness Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LIGHTNESS_CLIENT = 0x1302,

    /** Model ID - Light CTL Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_CTL_SERVER = 0x1303,

    /** Model ID - Light CTL Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_CTL_SETUP_SERVER = 0x1304,

    /** Model ID - Light CTL Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_CTL_CLIENT = 0x1305,

    /** Model ID - Light CTL Temperature Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_CTL_TEMPERATURE_SERVER = 0x1306,

    /** Model ID - Light HSL Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_HSL_SERVER = 0x1307,

    /** Model ID - Light HSL Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_HSL_SETUP_SERVER = 0x1308,

    /** Model ID - Light HSL Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_HSL_CLIENT = 0x1309,

    /** Model ID - Light HSL HUE Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_HSL_HUE_SERVER = 0x130A,

    /** Model ID - Light HSL Saturation Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_HSL_SATURATION_SERVER = 0x130B,

    /** Model ID - Light xyL Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_XYL_SERVER = 0x130C,

    /** Model ID - Light xyL Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_XYL_SETUP_SERVER = 0x130D,

    /** Model ID - Light xyL Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_XYL_CLIENT = 0x130E,

    /** Model ID - Light LC Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LC_SERVER = 0x130F,

    /** Model ID - Light LC Setup Server */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LC_SETUP_SERVER = 0x1310,

    /** Model ID - Light LC Client */
    RM_BLE_MESH_ACCESS_MODEL_INFO_LIGHT_LC_CLIENT = 0x1311,
} rm_ble_mesh_access_model_id_info_t;

/** Model ID datatype */
typedef struct st_rm_ble_mesh_access_model_id
{
    /** Vendor/SIG ID */
    union
    {
        uint32_t vendor_id;
        rm_ble_mesh_access_model_id_info_t sig_id;
    };

    /** Model type - SIG or Vendor */
    rm_ble_mesh_access_model_type_info_t type;
} rm_ble_mesh_access_model_id_t;

/**
 * Element description format.
 */
typedef struct st_rm_ble_mesh_access_element_descriptor
{
    /** Location descriptor */
    uint16_t loc;
} rm_ble_mesh_access_element_descriptor_t;

/**
 * Unicast/Virtual/Group Address.
 */
typedef struct st_rm_ble_mesh_access_address
{
    /** Flag - which field to be used */
    uint8_t use_label;

    /** Address */
    rm_ble_mesh_network_address_t addr;

    /** Label UUID */
    uint8_t label[RM_BLE_MESH_ACCESS_LABEL_UUID_LENGTH];
} rm_ble_mesh_access_address_t;

/**
 * Access Publication related information
 */
typedef struct st_rm_ble_mesh_access_publish_info
{
    /** PublishAddress (Unicast/Virtual/Group) */
    rm_ble_mesh_access_address_t addr;

    /**
     * - AppKey Index  (when set from remote).
     * - AppKey Handle (when set from locally for Configuration Client).
     */
    uint16_t appkey_index;

    /** CredentialFlag */
    uint8_t crden_flag;

    /** PublishTTL */
    uint8_t ttl;

    /** PublishPeriod */
    uint8_t period;

    /** PublishRetransmitCount */
    uint8_t rtx_count;

    /** PublishRetransmitIntervalSteps */
    uint8_t rtx_interval_steps;

    /** Flag - if called from local or remote */
    uint8_t remote;
} rm_ble_mesh_access_publish_info_t;

/**
 * Context of message received for a specific model instance.
 * This is required to send response appropriately.
 */
typedef struct st_rm_ble_mesh_access_model_req_msg_context
{
    /** Model Handle - for which request is received */
    rm_ble_mesh_access_model_handle_t handle;

    /** Source Address - originator of request */

    rm_ble_mesh_network_address_t saddr;

    /** Destination Address - of the request */

    rm_ble_mesh_network_address_t daddr;

    /** Associated Subnet Identifier */

    rm_ble_mesh_network_subnet_handle_t subnet_handle;

    /** Associated AppKey Identifier */

    rm_ble_mesh_network_appkey_handle_t appkey_handle;
} rm_ble_mesh_access_model_req_msg_context_t;

/** Uninterpreted/raw received message for a specific model instance. */
typedef struct st_rm_ble_mesh_access_req_msg_raw
{
    /** Request Opcode */
    uint32_t opcode;

    /** Raw received message */
    uint8_t * data_param;

    /** Raw received message length */
    uint16_t data_len;
} rm_ble_mesh_access_req_msg_raw_t;

/** Requested message type for a specific model instance. */
typedef struct st_rm_ble_mesh_access_model_req_msg
{
    /** Flag: GET, SET or Others */
    rm_ble_mesh_access_model_req_msg_type_t type;

    /** Flag: True or False */
    uint8_t to_be_acked;
} rm_ble_mesh_access_model_req_msg_t;

/** Publish setting */
typedef struct st_rm_ble_mesh_access_publish_setting
{
    /** Time to Live */
    uint8_t ttl;

    /** Flag to indicate if the message also to be published */
    uint8_t to_publish;
} rm_ble_mesh_access_publish_setting_t;

/** PDU setting */
typedef struct st_rm_ble_mesh_access_pdu
{
    /** 16 bit Source Address */
    rm_ble_mesh_network_address_t src_addr;

    /** 16 bit Destination Address */
    rm_ble_mesh_network_address_t dst_addr;

    /** Subnet Handle */
    rm_ble_mesh_network_subnet_handle_t subnet_handle;

    /** AppKey Handle */
    rm_ble_mesh_network_appkey_handle_t appkey_handle;

    /** Time to Live */
    uint8_t ttl;

    /** Request Opcode */
    uint32_t opcode;

    /** Raw received message */
    uint8_t * data_param;

    /** Raw received message length */
    uint16_t data_len;
} rm_ble_mesh_access_pdu_t;

/** Model specific state parameters in a request or response message */
typedef struct st_rm_ble_mesh_access_model_state_parameter
{
    /** State Type */
    uint8_t state_type;

    /** State pointer */
    void * state;
} rm_ble_mesh_access_model_state_parameter_t;

/** Additional parameters in a Model specific request or response message */
typedef struct st_rm_ble_mesh_access_extended_parameter
{
    /** State/Extended Type */
    uint8_t ext_type;

    /** State/Extended data structure pointer */
    void * ext;
} rm_ble_mesh_access_extended_parameter_t;

/**
 * Provisioned Device List Data Structure, containing Primary Element Address
 * and number of elements.
 */
typedef struct st_rm_ble_mesh_access_device_entry
{
    /** Unicast address of the first element */
    rm_ble_mesh_network_address_t uaddr;

    /** Number of Elements */
    uint8_t num_elements;
} rm_ble_mesh_access_device_entry_t;

/**
 *  \defgroup access_cb Application Callback
 *  \{
 *  This Section Describes the module Notification Callback interface offered
 *  to the application
 */

/** Access Layer Application Asynchronous Notification Callback Arguments. */
typedef struct st_rm_ble_mesh_access_model_callback_args
{
    void const * p_context;                                     ///< Placeholder for user data.
    rm_ble_mesh_access_model_req_msg_context_t * p_msg_context; ///< Context of message received for a specific model instance.
    rm_ble_mesh_access_req_msg_raw_t           * p_msg_raw;     ///< Uninterpreted/raw received message for a specific model instance.
} rm_ble_mesh_access_model_callback_args_t;

/**
 * Access Layer Model Publication Timeout Callback Arguments.
 *
 * Access Layer calls the registered callback to indicate Publication Timeout
 * for the associated model.
 *
 * \param p_context     Placeholder for user data.
 * \param handle        Model Handle.
 * \param blob          Blob if any or NULL.
 */
typedef struct st_rm_ble_mesh_access_timeout_callback_args
{
    void const * p_context;                   ///< Placeholder for user data.
    rm_ble_mesh_access_model_handle_t handle; ///< Model handle
    void * p_blob;                            ///< Blob if any or NULL.
} rm_ble_mesh_access_timeout_callback_args_t;

/**
 * Access Layer Application Asynchronous Notification Callback.
 *
 * Access Layer calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param p_args        Access Layer application asynchronous notification callback arguments.
 */
typedef void (* rm_ble_mesh_access_model_callback_t)(rm_ble_mesh_access_model_callback_args_t * p_args);

/**
 * Access Layer Model Publication Timeout Callback.
 *
 * Access Layer calls the registered callback to indicate Publication Timeout
 * for the associated model.
 *
 * \param p_args        Access Layer Model publication timeout callback arguments.
 */
typedef void (* rm_ble_mesh_access_timeout_callback_t)(rm_ble_mesh_access_timeout_callback_args_t * p_args);

/** \} */

/**
 * Data structure for model.
 *
 * Models could be bluetooth SIG defined or vendor defined.
 */
typedef struct st_rm_ble_mesh_access_model
{
    /** Model ID */
    rm_ble_mesh_access_model_id_t model_id;

    /**
     * Callback function pointer to receive packets from the underlying
     * protocol layers
     */
    rm_ble_mesh_access_model_callback_t model_callback;

    /**
     * Callback function called when Publication Timer expires.
     * Set to NULL if model does not support periodic publication.
     */
    rm_ble_mesh_access_timeout_callback_t timeout_callback;

    /** Number of Opcodes */
    uint16_t num_opcodes;

    /** List of Opcodes */
    const uint32_t * opcodes;
} rm_ble_mesh_access_model_t;

/** API to send reply or to update state change */
typedef struct st_rm_ble_mesh_access_server_state
{
    rm_ble_mesh_access_model_req_msg_context_t * p_context;                 ///< Context of the message.
    rm_ble_mesh_access_model_state_parameter_t * p_current_state_parameter; ///< Model specific current state parameters.
    rm_ble_mesh_access_model_state_parameter_t * p_target_state_parameter;  ///< Model specific target state parameters (NULL: to be ignored).
    uint16_t remaining_time;                                                ///< Time from current state to target state (0: to be ignored).
    rm_ble_mesh_access_extended_parameter_t * p_extended_parameter;         ///< Additional parameters (NULL: to be ignored).
    uint8_t reply;                                                          ///< If unicast response to be sent
    uint8_t publish;                                                        ///< If state to be published
} rm_ble_mesh_access_server_state_t;

/**
 * Provisioned Device List Data Structure, containing Primary Element Address
 * and number of elements.
 */
typedef struct st_rm_ble_mesh_access_provisioned_device_entry
{
    /** Unicast address of the first element */
    rm_ble_mesh_network_address_t uaddr;

    /** Number of Elements */
    uint8_t num_elements;
} rm_ble_mesh_access_provisioned_device_entry_t;

/** Associated key */
typedef struct st_rm_ble_mesh_access_associated_keys
{
    /** Privacy key */
    uint8_t privacy_key[RM_BLE_MESH_ACCESS_KEY_SIZE];

    /** Encryption key */
    uint8_t encrypt_key[RM_BLE_MESH_ACCESS_KEY_SIZE];

    /** Beacon key */
    uint8_t beacon_key[RM_BLE_MESH_ACCESS_KEY_SIZE];

    /** Whether new key or not */
    uint8_t is_new_key;
} rm_ble_mesh_access_associated_keys_t;

/** To add Security Credential of a LPN or the Friend. */
typedef struct st_rm_ble_mesh_access_friend_security_credential_info
{
    /** Address of the LPN. */
    rm_ble_mesh_network_address_t lpn_addr;

    /** Address of the Friend. */
    rm_ble_mesh_network_address_t friend_addr;

    /** Number of Friend Request messages the LPN has sent. */
    uint16_t lpn_counter;

    /** Number of Friend Offer messages the Friend has sent. */
    uint16_t friend_counter;
} rm_ble_mesh_access_friend_security_credential_info_t;

/** BLE MESH ACCESS control block.  Allocate an instance specific control block to pass into the BLE MESH ACCESS API calls.
 * @par Implemented as
 * - rm_ble_mesh_access_instance_ctrl_t
 */
typedef void rm_ble_mesh_access_ctrl_t;

/** BLE MESH ACCESS configuration parameters. */
typedef struct st_rm_ble_mesh_access_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                       ///< Select a channel corresponding to the channel number of the hardware.

    rm_ble_mesh_access_element_descriptor_t  * p_element_descriptor;        ///< Element description format
    rm_ble_mesh_upper_trans_instance_t const * p_mesh_upper_trans_instance; ///< Instance structure of upper trans
    rm_ble_mesh_access_element_handle_t        element_number;              ///< Element number

    void const * p_context;                                                 ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                                  ///< Placeholder for user extension.
} rm_ble_mesh_access_cfg_t;

/** BLE MESH ACCESS functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_access_api
{
    /** Open access middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_Open()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  p_cfg   Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_access_cfg_t const * const p_cfg);

    /** Close access middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_Close()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_access_ctrl_t * const p_ctrl);

    /** Register a model with the access layer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_RegisterModel()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_model          Pointer to model structure.
     * @param[out] p_model_handle   Pointer to model handle.
     */
    fsp_err_t (* registerModel)(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                rm_ble_mesh_access_model_t const * const  p_model,
                                rm_ble_mesh_access_model_handle_t * const p_model_handle);

    /** Get element handle.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetElementHandle()
     *
     * @param[in]  p_ctrl     Pointer to control structure.
     * @param[in]  elem_addr  Address of the corresponding element.
     * @param[out] p_handle   Pointer to model handle.
     */
    fsp_err_t (* getElementHandle)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_address_t elem_addr,
                                   rm_ble_mesh_access_element_handle_t * const p_handle);

    /** Get element handle for a given model handle
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetElementHandleForModelHandle()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  model_handle   Model handle.
     * @param[out] p_elem_handle  Pointer to element handle.
     */
    fsp_err_t (* getElementHandleForModelHandle)(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t           model_handle,
                                                 rm_ble_mesh_access_element_handle_t * const p_elem_handle);

    /** Get model handle.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetModelHandle()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  elem_handle  Element identifier associated with the Model.
     * @param[in]  model_id     Model identifier for which the model handle to be searched.
     * @param[out] p_handle     Pointer to model handle.
     */
    fsp_err_t (* getModelHandle)(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                 rm_ble_mesh_access_element_handle_t       elem_handle,
                                 rm_ble_mesh_access_model_id_t             model_id,
                                 rm_ble_mesh_access_model_handle_t * const p_handle);

    /** API to publish access layer message.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_Publish()
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  p_handl            Pointer to model handle.
     * @param[in]  p_publish_message  Pointer to received message structure.
     * @param[in]  reliable           MS_TRUE for reliable message. MS_FALSE otherwise.
     */
    fsp_err_t (* publish)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                          rm_ble_mesh_access_model_handle_t const * const p_handle,
                          rm_ble_mesh_access_req_msg_raw_t const * const p_publish_message, uint8_t reliable);

    /** API to reliably publish access layer message.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_ReliablePublish()
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  p_handl            Pointer to model handle.
     * @param[in]  p_publish_message  Pointer to raw received message structure.
     * @param[in]  rsp_opcode         Response opcode.
     */
    fsp_err_t (* reliablePublish)(rm_ble_mesh_access_ctrl_t * const               p_ctrl,
                                  rm_ble_mesh_access_model_handle_t const * const p_handle,
                                  rm_ble_mesh_access_req_msg_raw_t const * const  p_publish_message,
                                  uint32_t                                        rsp_opcode);

    /** API to reply to access layer message.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_Reply()
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  p_req_msg_context  Pointer to context of received message structure.
     * @param[in]  ttl                Time to live.
     * @param[in]  p_req_msg_raw      Pointer to received message structure.
     */
    fsp_err_t (* reply)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                        rm_ble_mesh_access_model_req_msg_context_t const * const p_req_msg_context, uint8_t ttl,
                        rm_ble_mesh_access_req_msg_raw_t const * const p_req_msg_raw);

    /** API to reply to access layer message and optionally also to publish.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_ReplyAndPublish()
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  p_req_msg_context  Pointer to context of received message structure.
     * @param[in]  p_req_msg_raw      Pointer to received message structure.
     * @param[in]  p_publish_setting  Pointer to publish setting structure.
     */
    fsp_err_t (* replyAndPublish)(rm_ble_mesh_access_ctrl_t * const                        p_ctrl,
                                  rm_ble_mesh_access_model_req_msg_context_t const * const p_req_msg_context,
                                  rm_ble_mesh_access_req_msg_raw_t const * const           p_req_msg_raw,
                                  rm_ble_mesh_access_publish_setting_t const * const       p_publish_setting);

    /** API to send access PDUs.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SendPdu()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  p_pdu    Pointer to PDU structure.
     * @param[in]  reliable If requires lower transport ACK, set reliable as TRUE.
     */
    fsp_err_t (* sendPdu)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_access_pdu_t const * const p_pdu,
                          uint8_t reliable);

    /** Get composition data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetCompositionData()
     *
     * @param[in]  p_ctrl    Pointer to control structure.
     * @param[out] p_buffer  Pointer to buffer structure.
     */
    fsp_err_t (* getCompositionData)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_buffer_t * const p_buffer);

    /**  To reset a node.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_Reset()
     *
     * @param[in]  p_ctrl    Pointer to control structure.
     */
    fsp_err_t (* reset)(rm_ble_mesh_access_ctrl_t * const p_ctrl);

    /**  To get the number of elements in local node.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetElementCount()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[out] p_count  Pointer to number of elements.
     */
    fsp_err_t (* getElementCount)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_count);

    /**  To set primary unicast address.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetPrimaryUnicastAddress()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  addr    Primary Unicast address to be set.
     */
    fsp_err_t (* setPrimaryUnicastAddress)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                           rm_ble_mesh_network_address_t     addr);

    /**  To get primary unicast address.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetPrimaryUnicastAddress()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[out] p_addr  Pointer to address.
     */
    fsp_err_t (* getPrimaryUnicastAddress)(rm_ble_mesh_access_ctrl_t * const     p_ctrl,
                                           rm_ble_mesh_network_address_t * const p_addr);

    /**  To set default TTL.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetDefaultTtl()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  ttl     Default TTL to be set.
     */
    fsp_err_t (* setDefaultTtl)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t ttl);

    /**  To get default TTL.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetDefaultTtl()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  p_ttl   Pointer to TTL.
     */
    fsp_err_t (* getDefaultTtl)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t const * const p_ttl);

    /**  To set IV Index.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetIvIndex()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  iv_index        IV index to be set.
     * @param[in]  iv_update_flag  IV update flag.
     */
    fsp_err_t (* setIvIndex)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint32_t iv_index, uint8_t iv_update_flag);

    /**  To get IV Index.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetIvIndex()
     *
     * @param[in]  p_ctrl            Pointer to control structure.
     * @param[out] p_iv_index        Pointer to index.
     * @param[out] p_iv_update_flag  Pointer to update flag.
     */
    fsp_err_t (* getIvIndex)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint32_t * const p_iv_index,
                             uint8_t * const p_iv_update_flag);

    /**  To get IV Index by IVI.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetIvIndexByIvi()
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[in]  ivi         Least significant bit of the IV index used in the once to authenticate and encrypt the network PDU.
     * @param[out] p_iv_index  Pointer to index.
     */
    fsp_err_t (* getIvIndexByIvi)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t ivi, uint32_t * const p_iv_index);

    /**  To enable/disable a feature.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetFeaturesField()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  enable   Enable or Disable.
     * @param[in]  feature  Relay, proxy, friend or low power.
     */
    fsp_err_t (* setFeaturesField)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t enable, uint8_t feature);

    /**  To get state of a feature.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetFeaturesField()
     *
     * @param[in]  p_ctrl    Pointer to control structure.
     * @param[in]  p_enable  Pointer to enable.
     * @param[in]  feature   Relay, proxy, friend or low power.
     */
    fsp_err_t (* getFeaturesField)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_enable, uint8_t feature);

    /**  To get state of all features.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetFeatures()
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[out] p_features  Pointer to features.
     */
    fsp_err_t (* getFeatures)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_features);

    /**  To get friendship role of the node.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetFriendshipRole()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[out] p_friend_role  Pointer to friend role.
     */
    fsp_err_t (* getFriendshipRole)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t * const p_friend_role);

    /**  To set friendship role of the node.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetFriendshipRole()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] friend_role  Friend role.
     */
    fsp_err_t (* setFriendshipRole)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t friend_role);

    /**  To add Device Key.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_AddDeviceKey()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_dev_key     Pointer to device Key.
     * @param[in]  uaddr         Unicast address of the first element.
     * @param[in]  num_elements  Number of elements.
     */
    fsp_err_t (* addDeviceKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t const * const p_dev_key,
                               rm_ble_mesh_network_address_t uaddr, uint8_t num_elements);

    /**  To get Device Key.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetDeviceKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  dev_key_index  Device key index.
     * @param[out] p_dev_key      Pointer to device key to be returned.
     */
    fsp_err_t (* getDeviceKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t dev_key_index,
                               uint8_t ** const p_dev_key);

    /**  To remove all Device Keys.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_RemoveAllDeviceKeys()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     */
    fsp_err_t (* removeAllDeviceKeys)(rm_ble_mesh_access_ctrl_t * const p_ctrl);

    /**  To get list of Provisioned Device List.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetProvisionedDeviceList()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_prov_dev_list  Pointer to provisioned device list structure.
     * @param[in]  p_num_entries    Pointer to number of entries.
     */
    fsp_err_t (* getProvisionedDeviceList)(rm_ble_mesh_access_ctrl_t * const                           p_ctrl,
                                           rm_ble_mesh_access_provisioned_device_entry_t const * const p_prov_dev_list,
                                           uint16_t * const                                            p_num_entries);

    /**  To get Device Key Handle.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetDeviceKeyHandle()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  prim_elem_uaddr  Primary element address to be searched.
     * @param[in]  p_handle         Pointer to handle.
     */
    fsp_err_t (* getDeviceKeyHandle)(rm_ble_mesh_access_ctrl_t * const              p_ctrl,
                                     rm_ble_mesh_network_address_t                  prim_elem_uaddr,
                                     rm_ble_mesh_access_device_key_handle_t * const p_handle);

    /**  To get AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetAppKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  appkey_handle  AppKey Handle.
     * @param[out] p_app_key      Pointer to AppKey to be returned.
     * @param[out] p_aid          Pointer to AID to be returned.
     */
    fsp_err_t (* getAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_appkey_handle_t appkey_handle,
                            uint8_t ** const p_app_key, uint8_t * const p_aid);

    /**  To add/update NetKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_AddUpdateNetkey()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  netkey_index  Identifies global index of NetKey. A 12bits value.
     * @param[in]  opcode        To identify Add or Update NetKey.
     * @param[out] p_net_key     Pointer to NetKey.
     */
    fsp_err_t (* addUpdateNetkey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint16_t netkey_index, uint32_t opcode,
                                  uint8_t const * const p_net_key);

    /**  To add Security Credential of a LPN or the Friend.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_AddFriendSecurityCredential()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Identifies associated subnet.
     * @param[in]  friend_index   Friend Index.
     * @param[in]  info           Security credential of a LPN or the friend.
     */
    fsp_err_t (* addFriendSecurityCredential)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                              rm_ble_mesh_network_subnet_handle_t subnet_handle, uint16_t friend_index,
                                              rm_ble_mesh_access_friend_security_credential_info_t info);

    /**  To delete the Security Credential of a LPN or the Friend.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_DeleteFriendSecurityCredential()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Identifies associated subnet.
     * @param[in]  friend_index   Friend index.
     */
    fsp_err_t (* deleteFriendSecurityCredential)(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                                 rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                                 uint16_t                            friend_index);

    /**  To find a Subnet associated with the NetKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_FindSubnet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  netkey_index     Identifies global Index of NetKey, corresponding Subnet to be returned.
     * @param[out] p_subnet_handle  Pointer to subnet handle.
     */
    fsp_err_t (* findSubnet)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint16_t netkey_index,
                             rm_ble_mesh_network_subnet_handle_t * const p_subnet_handle);

    /**  To find the Master Subnet associated with the friend security credential, identified by Friend Subnet Handle.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_FindMasterSubnet()
     *
     * @param[in]  p_ctrl                  Pointer to control structure.
     * @param[in]  friend_subnet_handle    Identifies the friend subnet handle, corresponding to friend subnet handle.
     * @param[out] p_master_subnet_handle  Pointer to master subnet handle.
     */
    fsp_err_t (* findMasterSubnet)(rm_ble_mesh_access_ctrl_t * const           p_ctrl,
                                   rm_ble_mesh_network_subnet_handle_t         friend_subnet_handle,
                                   rm_ble_mesh_network_subnet_handle_t * const p_master_subnet_handle);

    /**  To delete NetKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_DeleteNetKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle of the subnet for which NetKey to be deleted.
     */
    fsp_err_t (* deleteNetKey)(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                               rm_ble_mesh_network_subnet_handle_t subnet_handle);

    /**  To get NetKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetNetKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Target subnet handle to get net key.
     * @param[in]  p_net_key      Pointer to NetKey.
     */
    fsp_err_t (* getNetKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_subnet_handle_t subnet_handle,
                            uint8_t * const p_net_key);

    /**  To get list of all known NetKeys.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetNetKeyIndexList()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  p_netkey_count       Pointer to NetKey count.
     * @param[in]  p_netkey_index_list  Pointer to NetKey index list.
     */
    fsp_err_t (* getNetKeyIndexList)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint16_t * const p_netkey_count,
                                     uint16_t * const p_netkey_index_list);

    /**  To search for NID.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_LookUpNid()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  nid              NID to be searched in all known subnets for match.
     * @param[out] p_subnet_handle  Pointer to subnet handle.
     * @param[out] p_key_set        Pointer to key set.
     */
    fsp_err_t (* lookUpNid)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t nid,
                            rm_ble_mesh_network_subnet_handle_t * const p_subnet_handle,
                            rm_ble_mesh_access_associated_keys_t * const p_key_set);

    /**  To search for Network ID.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_LookUpNetworkId()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_network_id     Pointer to network ID to be searched in all known subnets for match.
     * @param[out] p_subnet_handle  Pointer to subnet handle.
     * @param[out] p_key_set        Pointer to key settings.
     */
    fsp_err_t (* lookUpNetworkId)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t const * const p_network_id,
                                  rm_ble_mesh_network_subnet_handle_t * const p_subnet_handle,
                                  rm_ble_mesh_access_associated_keys_t * const p_key_set);

    /**  To search for AID.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_LookUpAid()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  aid              AID to be searched in all known AppKeys for match.
     * @param[out] p_appkey_handle  Pointer to AppKey handle.
     * @param[out] p_app_key        Pointer to AppKey.
     */
    fsp_err_t (* lookUpAid)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t aid,
                            rm_ble_mesh_network_appkey_handle_t * const p_appkey_handle, uint8_t * const p_app_key);

    /**  Set Provisioning Data.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetProvisioningData()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_prov_data      Pointer to provisioning data structure.
     */
    fsp_err_t (* setProvisioningData)(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                      rm_ble_mesh_provision_data_t const * const p_prov_data);

    /**  To get NID associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetNid()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  handle  Handle identifying the subnet.
     * @param[out] p_nid   Pointer to NID.
     */
    fsp_err_t (* getSubnetNid)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_subnet_handle_t handle,
                               uint8_t * const p_nid);

    /**  To get privacy Key associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetPrivacyKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  handle         Handle identifying the subnet.
     * @param[out] p_privacy_key  Pointer to Privacy Key.
     */
    fsp_err_t (* getSubnetPrivacyKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                      rm_ble_mesh_network_subnet_handle_t handle, uint8_t * const p_privacy_key);

    /**  To get Network ID associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetNetworkId()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  handle        Handle identifying the subnet.
     * @param[out] p_network_id  Pointer to Network ID.
     */
    fsp_err_t (* getSubnetNetworkId)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                     rm_ble_mesh_network_subnet_handle_t handle, uint8_t * const p_network_id);

    /**  To get Beacon Key associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetBeaconKey()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  handle        Handle identifying the subnet.
     * @param[out] p_beacon_key  Pointer to Beacon Key.
     */
    fsp_err_t (* getSubnetBeaconKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                     rm_ble_mesh_network_subnet_handle_t handle, uint8_t * const p_beacon_key);

    /**  To get Identity Key associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetIdentityKey()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  handle          Handle identifying the subnet.
     * @param[out] p_identity_key  Pointer to Identity Key.
     */
    fsp_err_t (* getSubnetIdentityKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                       rm_ble_mesh_network_subnet_handle_t handle, uint8_t * const p_identity_key);

    /**  To get Encryption Key associated with a subnet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetSubnetEncryptionKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  handle         Handle identifying the subnet.
     * @param[out] p_encrypt_key  Pointer to Encryption Key.
     */
    fsp_err_t (* getSubnetEncryptionKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                         rm_ble_mesh_network_subnet_handle_t handle, uint8_t * const p_encrypt_key);

    /**  To get Node Identity.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetNodeIdentity()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle identifying the subnet.
     * @param[out] p_id_state     Pointer to node identity state.
     */
    fsp_err_t (* getNodeIdentity)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                  rm_ble_mesh_network_subnet_handle_t subnet_handle, uint8_t * const p_id_state);

    /**  To set Node Identity.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetNodeIdentity()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle identifying the subnet.
     * @param[out] p_id_state     Pointer to node identity state.
     */
    fsp_err_t (* setNodeIdentity)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                  rm_ble_mesh_network_subnet_handle_t subnet_handle, uint8_t * const p_id_state);

    /**  To get Key refresh phase.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetKeyRefreshPhase()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  subnet_handle        Handle identifying the subnet.
     * @param[out] p_key_refresh_state  Pointer to key refresh phase state.
     */
    fsp_err_t (* getKeyRefreshPhase)(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                     rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                     uint8_t * const                     p_key_refresh_state);

    /**  To set Key refresh phase.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetKeyRefreshPhase()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  subnet_handle        Handle identifying the subnet.
     * @param[in]  p_key_refresh_state  Pointer to key refresh phase state.
     */
    fsp_err_t (* setKeyRefreshPhase)(rm_ble_mesh_access_ctrl_t * const   p_ctrl,
                                     rm_ble_mesh_network_subnet_handle_t subnet_handle,
                                     uint8_t const * const               p_key_refresh_state);

    /**  To set Network/Relay Transmit state.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetTransmitState()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  tx_state_type  Transmit state type (Network or Relay).
     * @param[in]  tx_state       Composite state (3bits of TX count and 5bits of TX interval steps).
     */
    fsp_err_t (* setTransmitState)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t tx_state_type, uint8_t tx_state);

    /**  To get Network/Relay Transmit state.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetTransmitState()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  tx_state_type  Transmit State Type (Network or Relay).
     * @param[out] p_tx_state     Pointer to TX state.
     */
    fsp_err_t (* getTransmitState)(rm_ble_mesh_access_ctrl_t * const p_ctrl, uint8_t tx_state_type,
                                   uint8_t * const p_tx_state);

    /**  To add AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_AddAppKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle of the subnet for which AppKey to be added.
     * @param[in]  appkey_index   Identifies global Index of AppKey. A 12bits value.
     * @param[in]  p_app_key      Pointer to AppKey.
     */
    fsp_err_t (* addAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_subnet_handle_t subnet_handle,
                            uint16_t appkey_index, uint8_t const * const p_app_key);

    /**  To update/delete AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_UpdateAppKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle of the Subnet for which AppKey to be updated/deleted.
     * @param[in]  appkey_index   Identifies global Index of AppKey. A 12bits value.
     * @param[in]  p_app_key      Pointer to AppKey.
     */
    fsp_err_t (* updateAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                               rm_ble_mesh_network_subnet_handle_t subnet_handle, uint16_t appkey_index,
                               uint8_t const * const p_app_key);

    /**  To update/delete AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_DeleteAppKey()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  subnet_handle  Handle of the Subnet for which AppKey to be updated/deleted.
     * @param[in]  appkey_index   Identifies global index of AppKey. A 12bits value.
     * @param[in]  p_app_key      Pointer to AppKey.
     */
    fsp_err_t (* deleteAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                               rm_ble_mesh_network_subnet_handle_t subnet_handle, uint16_t appkey_index,
                               uint8_t const * const p_app_key);

    /**  To get AppKey Handle for a given AppKey Index.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetAppKeyHandle()
     *
     * @param[in]  p_ctrl            Pointer to control structure.
     * @param[in]  subnet_handle     Handle of the Subnet for which AppKey to be gotten.
     * @param[in]  appkey_index      Identifies global Index of AppKey. A 12bits value.
     * @param[in]  p_app_key         Pointer to AppKey.
     * @param[out] p_app_key_handle  Pointer to AppKey handle.
     */
    fsp_err_t (* getAppKeyHandle)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                  rm_ble_mesh_network_subnet_handle_t subnet_handle, uint16_t appkey_index,
                                  uint8_t const * const p_app_key,
                                  rm_ble_mesh_network_appkey_handle_t * const p_appkey_handle);

    /**  To get list of all known AppKeys.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetAppKeyIndexList()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  subnet_handle        Handle of the Subnet for which AppKey to be returned.
     * @param[out] p_appkey_count       Pointer to AppKey count.
     * @param[out] p_appkey_index_list  Pointer to AppKey index list.
     */
    fsp_err_t (* getAppKeyIndexList)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                     rm_ble_mesh_network_subnet_handle_t subnet_handle, uint16_t * const p_appkey_count,
                                     uint16_t * const p_appkey_index_list);

    /**  To bind a model with an AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_BindModelWithAppKey()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Model handle identifying the model.
     * @param[in]  appkey_index  Identifies global index of AppKey. A 12bits value.
     */
    fsp_err_t (* bindModelWithAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                      rm_ble_mesh_access_model_handle_t model_handle, uint16_t appkey_index);

    /**  To unbind a model with an AppKey.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_UnbindModelWithAppKey()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Model handle identifying the model.
     * @param[in]  appkey_index  Identifies global index of AppKey. A 12bits value.
     */
    fsp_err_t (* unbindModelWithAppKey)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                        rm_ble_mesh_access_model_handle_t model_handle, uint16_t appkey_index);

    /**  To get list of all AppKeys associated with a model.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetModelAppKeyList()
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[in]  model_handle         Handle of the Model for which AppKey to be returned.
     * @param[out] p_appkey_count       pointer to AppKey count.
     * @param[out] p_appkey_index_list  Pointer to AppKey index list.
     */
    fsp_err_t (* getModelAppKeyList)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                     rm_ble_mesh_access_model_handle_t model_handle, uint16_t * const p_appkey_count,
                                     uint16_t * const p_appkey_index_list);

    /**  To set Publication information associated with a model.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetModelPublication()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  model_handle    Handle of the Model for which Publication info to be set.
     * @param[in]  p_publish_info  Pointer to publication information structure.
     */
    fsp_err_t (* setModelPublication)(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                      rm_ble_mesh_access_model_handle_t         model_handle,
                                      rm_ble_mesh_access_publish_info_t * const p_publish_info);

    /**  To set Publication Fast Period Divisor information associated with a model.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_SetModelPublicationPeriodDivisor()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  model_handle    Handle of the Model for which Publication info to be set.
     * @param[in]  period_divisor  The value range for the Health Fast Period Divisor state is 0 through 15, all other values are prohibited.
     */
    fsp_err_t (* setModelPublicationPeriodDivisor)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                   rm_ble_mesh_access_model_handle_t model_handle,
                                                   uint8_t                           period_divisor);

    /**  To get Publication information associated with a model.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetModelPublication()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  model_handle    Handle of the Model for which Publication info to be returned.
     * @param[out] p_publish_info  Pointer to publication information structure.
     */
    fsp_err_t (* getModelPublication)(rm_ble_mesh_access_ctrl_t * const         p_ctrl,
                                      rm_ble_mesh_access_model_handle_t         model_handle,
                                      rm_ble_mesh_access_publish_info_t * const p_publish_info);

    /**  To add an address to a model subscription list.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_AddModelSubscription()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Handle of the Model for which address to be added in the subscription list.
     * @param[in]  p_sub_addr    Pointer to address structure.
     */
    fsp_err_t (* addModelSubscription)(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                       rm_ble_mesh_access_model_handle_t          model_handle,
                                       rm_ble_mesh_access_address_t const * const p_sub_addr);

    /**  To delete an address to a model subscription list.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_DeleteModelSubscription()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Handle of the Model for which address to be deleted in the subscription list.
     * @param[in]  p_sub_addr    Pointer to address structure.
     */
    fsp_err_t (* deleteModelSubscription)(rm_ble_mesh_access_ctrl_t * const          p_ctrl,
                                          rm_ble_mesh_access_model_handle_t          model_handle,
                                          rm_ble_mesh_access_address_t const * const p_sub_addr);

    /**  To discard a model subscription list.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_DeleteAllModelSubscription()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Handle of the Model for which the subscription list to be discarded.
     */
    fsp_err_t (* deleteAllModelSubscription)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                             rm_ble_mesh_access_model_handle_t model_handle);

    /**  To get list of subscription addresses of a model.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetModelSubscriptionList()
     *
     * @param[in]  p_ctrl            Pointer to control structure.
     * @param[in]  model_handle      Handle of the Model for which the subscription addresses to be returned.
     * @param[in]  p_sub_addr_count  Pointer to maximum number of subscription address.
     * @param[out] p_sub_addr_list   Pointer to subscription addresses.
     */
    fsp_err_t (* getModelSubscriptionList)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                           rm_ble_mesh_access_model_handle_t model_handle,
                                           uint16_t * const                  p_sub_addr_count,
                                           uint16_t * const                  p_sub_addr_list);

    /**  To get list of subscription addresses of all the models.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_GetAllModelSubscriptionList()
     *
     * @param[in]  p_ctrl            Pointer to control structure.
     * @param[in]  p_sub_addr_count  Pointer to maximum number of subscription address.
     * @param[out] p_sub_addr_list   Pointer to subscription addresses.
     */
    fsp_err_t (* getAllModelSubscriptionList)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                              uint16_t * const p_sub_addr_count, uint16_t * const p_sub_addr_list);

    /**  To check if valid element address to receive a packet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_IsValidElementAddress()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  addr    A valid element address, to be checked.
     */
    fsp_err_t (* isValidElementAddress)(rm_ble_mesh_access_ctrl_t * const p_ctrl, rm_ble_mesh_network_address_t addr);

    /**  To check if Fixed Group Address in receive packet to be processed.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_IsFixedGroupAddressToBeProcessed()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  addr    A valid fixed group address, to be checked.
     */
    fsp_err_t (* isFixedGroupAddressToBeProcessed)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                                   rm_ble_mesh_network_address_t     addr);

    /**  To check if valid subscription address to receive a packet.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_IsValidSubscriptionAddress()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  addr    A valid subscription address, to be checked.
     */
    fsp_err_t (* isValidSubscriptionAddress)(rm_ble_mesh_access_ctrl_t * const p_ctrl,
                                             rm_ble_mesh_network_address_t     addr);

    /**  To set the IV Update Test Mode feature.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ACCESS_EnableIvUpdateTestMode()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  mode    This flag is used to either enable or disable the IV update test mode feature.
     */
    fsp_err_t (* enableIvUpdateTestMode)(rm_ble_mesh_access_ctrl_t * const        p_ctrl,
                                         rm_ble_mesh_access_iv_update_test_mode_t mode);
} rm_ble_mesh_access_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_access_instance
{
    rm_ble_mesh_access_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_access_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_access_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_access_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_ACCESS_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_ACCESS_API_H
