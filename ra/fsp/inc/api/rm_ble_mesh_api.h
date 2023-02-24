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

#ifndef RM_BLE_MESH_API_H
#define RM_BLE_MESH_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_API BLE Mesh Interface
 * @brief     Interface for Bluetooth Low Energy Abstraction functions.
 *
 * @section   RM_BLE_MESH_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh (BLE MESH) peripheral provides Bluetooth Low Energy Mesh functionality.
 *
 * The Bluetooth Low Energy Mesh interface can be implemented by:
 * - @ref RM_BLE_MESH
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Device UUID Size */
#define RM_BLE_MESH_DEVICE_UUID_SIZE    16

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Timer handle */
typedef void * rm_ble_mesh_timer_handle_t;

/** Error group mask for BLE MESH Module */
#define RM_BLE_MESH_ERROR_GROUP_MASK                  0x0000

/** Error group mask for Common */
#define RM_BLE_MESH_ERROR_GROUP_MASK_COMMON           0x1000

/** Error group mask for Bearer */
#define RM_BLE_MESH_ERROR_GROUP_MASK_BEARER           0x2000

/** Error group mask for Network */
#define RM_BLE_MESH_ERROR_GROUP_MASK_NETWORK          0x2100

/** Error group mask for Lower Transport */
#define RM_BLE_MESH_ERROR_GROUP_MASK_LOWER_TRANS      0x2200

/** Error group mask for Upper Transport */
#define RM_BLE_MESH_ERROR_GROUP_MASK_UPPER_TRANS      0x2300

/** Error group mask for Access */
#define RM_BLE_MESH_ERROR_GROUP_MASK_ACCESS           0x2400

/** Error group mask for Provisioning */
#define RM_BLE_MESH_ERROR_GROUP_MASK_PROVISION        0x3000

/** Error group mask for Generic Models */
#define RM_BLE_MESH_ERROR_GROUP_MASK_GENERIC_MODEL    0x4000

/** Error group mask for Config Model */
#define RM_BLE_MESH_ERROR_GROUP_MASK_CONFIG_MODEL     0x4100

/** Error group mask for Health Model */
#define RM_BLE_MESH_ERROR_GROUP_MASK_HEALTH_MODEL     0x4200

/** BLE MESH error code. */
typedef enum e_rm_ble_mesh_error_code
{
    /* DEPRECATED Success */
    RM_BLE_MESH_SUCCESS = 0x0000,

    /** Success */
    RM_BLE_MESH_ERROR_CODE_SUCCESS = 0x0000,

    /* DEPRECATED Invalid Address */
    RM_BLE_MESH_INVALID_ADDRESS = 0x0001,

    /** Invalid Address */
    RM_BLE_MESH_ERROR_CODE_INVALID_ADDRESS = 0x0001,

    /* DEPRECATED Invalid Model */
    RM_BLE_MESH_INVALID_MODEL = 0x0002,

    /** Invalid Model */
    RM_BLE_MESH_ERROR_CODE_INVALID_MODEL = 0x0002,

    /* DEPRECATED Invalid AppKey Index */
    RM_BLE_MESH_INVALID_APPKEY_INDEX = 0x0003,

    /** Invalid AppKey Index */
    RM_BLE_MESH_ERROR_CODE_INVALID_APPKEY_INDEX = 0x0003,

    /* DEPRECATED Invalid NetKey Index */
    RM_BLE_MESH_INVALID_NETKEY_INDEX = 0x0004,

    /** Invalid NetKey Index */
    RM_BLE_MESH_ERROR_CODE_INVALID_NETKEY_INDEX = 0x0004,

    /* DEPRECATED Insufficient Resources */
    RM_BLE_MESH_INSUFFICIENT_RESOURCES = 0x0005,

    /** Insufficient Resources */
    RM_BLE_MESH_ERROR_CODE_INSUFFICIENT_RESOURCES = 0x0005,

    /* DEPRECATED Key Index Already Stored */
    RM_BLE_MESH_KEY_INDEX_ALREADY_STORED = 0x0006,

    /** Key Index Already Stored */
    RM_BLE_MESH_ERROR_CODE_KEY_INDEX_ALREADY_STORED = 0x0006,

    /* DEPRECATED Invalid Publish Parameters */
    RM_BLE_MESH_INVALID_PUBLISH_PARAMETER = 0x0007,

    /** Invalid Publish Parameters */
    RM_BLE_MESH_ERROR_CODE_INVALID_PUBLISH_PARAMETER = 0x0007,

    /* DEPRECATED Not a Subscribe Model */
    RM_BLE_MESH_NOT_A_SUBSCRIBE_MODEL = 0x0008,

    /** Not a Subscribe Model */
    RM_BLE_MESH_ERROR_CODE_NOT_A_SUBSCRIBE_MODEL = 0x0008,

    /* DEPRECATED Storage Failure */
    RM_BLE_MESH_STORAGE_FAILURE = 0x0009,

    /** Storage Failure */
    RM_BLE_MESH_ERROR_CODE_STORAGE_FAILURE = 0x0009,

    /* DEPRECATED Feature Not Supported */
    RM_BLE_MESH_FEATURE_NOT_SUPPORTED = 0x000A,

    /** Feature Not Supported */
    RM_BLE_MESH_ERROR_CODE_FEATURE_NOT_SUPPORTED = 0x000A,

    /* DEPRECATED Cannot Update */
    RM_BLE_MESH_CANNOT_UPDATE = 0x000B,

    /** Cannot Update */
    RM_BLE_MESH_ERROR_CODE_CANNOT_UPDATE = 0x000B,

    /* DEPRECATED Cannot Remove */
    RM_BLE_MESH_CANNOT_REMOVE = 0x000C,

    /** Cannot Remove */
    RM_BLE_MESH_ERROR_CODE_CANNOT_REMOVE = 0x000C,

    /* DEPRECATED Cannot Bind */
    RM_BLE_MESH_CANNOT_BIND = 0x000D,

    /** Cannot Bind */
    RM_BLE_MESH_ERROR_CODE_CANNOT_BIND = 0x000D,

    /* DEPRECATED Temporarily Unable to Change State */
    RM_BLE_MESH_TEMP_UNABLE_TO_CHANGE_STATE = 0x000E,

    /** Temporarily Unable to Change State */
    RM_BLE_MESH_ERROR_CODE_TEMP_UNABLE_TO_CHANGE_STATE = 0x000E,

    /* DEPRECATED Cannot Set */
    RM_BLE_MESH_CANNOT_SET = 0x000F,

    /** Cannot Set */
    RM_BLE_MESH_ERROR_CODE_CANNOT_SET = 0x000F,

    /* DEPRECATED Unspecified Error */
    RM_BLE_MESH_UNSPECIFIED_ERROR = 0x0010,

    /** Unspecified Error */
    RM_BLE_MESH_ERROR_CODE_UNSPECIFIED_ERROR = 0x0010,

    /* DEPRECATED Invalid Binding */
    RM_BLE_MESH_INVALID_BINDING = 0x0011,

    /** Invalid Binding */
    RM_BLE_MESH_ERROR_CODE_INVALID_BINDING = 0x0011,

    /** Bearer Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_BEARER_MUTEX_INIT_FAILED = 0x2001,

    /** Bearer Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_BEARER_COND_INIT_FAILED = 0x2002,

    /** Bearer Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_BEARER_MUTEX_LOCK_FAILED = 0x2003,

    /** Bearer Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_BEARER_MUTEX_UNLOCK_FAILED = 0x2004,

    /** Bearer Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_BEARER_MEMORY_ALLOCATION_FAILED = 0x2005,

    /** Bearer Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_BEARER_INVALID_PARAMETER_VALUE = 0x2011,

    /** Bearer Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_BEARER_PARAMETER_OUTSIDE_RANGE = 0x2012,

    /** Bearer Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_BEARER_NULL_PARAMETER_NOT_ALLOWED = 0x2013,

    /** Bearer Error Code for Interface Not Read */
    RM_BLE_MESH_ERROR_CODE_BEARER_INTERFACE_NOT_READY = 0x2014,

    /** Bearer Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_BEARER_API_NOT_SUPPORTED = 0x20FF,

    /** Network Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_NETWORK_MUTEX_INIT_FAILED = 0x2101,

    /** Network Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_NETWORK_COND_INIT_FAILED = 0x2102,

    /** Network Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_NETWORK_MUTEX_LOCK_FAILED = 0x2103,

    /** Network Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_NETWORK_MUTEX_UNLOCK_FAILED = 0x2104,

    /** Network Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_NETWORK_MEMORY_ALLOCATION_FAILED = 0x2105,

    /** Network Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_NETWORK_INVALID_PARAMETER_VALUE = 0x2111,

    /** Network Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_NETWORK_PARAMETER_OUTSIDE_RANGE = 0x2112,

    /** Network Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_NETWORK_NULL_PARAMETER_NOT_ALLOWED = 0x2113,

    /** Network Error Code for Transmit Queue Full */
    RM_BLE_MESH_ERROR_CODE_NETWORK_TX_QUEUE_FULL = 0x2114,

    /** Network Error Code for Transmit Queue Empty */
    RM_BLE_MESH_ERROR_CODE_NETWORK_TX_QUEUE_EMPTY = 0x2115,

    /**
     * Network Error Code returned by Network Callback, indicating if it
     * detected an invalid packet format or if the packet to be further
     * processed, by the network layer like to be relayed or proxied etc.
     */
    RM_BLE_MESH_ERROR_CODE_NETWORK_INVALID_RX_PACKET_FORMAT = 0x2116,

    /** Network Error Code for reception of locally sourced packet */
    RM_BLE_MESH_ERROR_CODE_NETWORK_RX_LOCAL_SRC_ADDR_PACKET = 0x2117,

    /**
     * Network Error Code returned by Network Callback, indicating if the
     * received packet needs further processing by the network layer like
     * to be relayed or proxied etc. after the control being returned by
     * the callback.
     */
    RM_BLE_MESH_ERROR_CODE_NETWORK_POST_PROCESS_RX_PACKET = 0x2118,

    /** Network Error Code for Already Relayed Packet */
    RM_BLE_MESH_ERROR_CODE_NETWORK_RX_ALREADY_RELAYED_PACKET = 0x2119,

    /**
     * Network Error Code returned by Network Callback, indicating if the
     * received packet is for a known LPN with an ongoing Friendship which
     * needs further processing by the network layer like to be relayed or
     * proxied etc. after the control being returned by the callback.
     */
    RM_BLE_MESH_ERROR_CODE_NETWORK_RX_LPN_SRC_ADDR_TO_RELAY_PACKET = 0x2120,

    /**
     * Network Error code to tag all errors returned by the Crypto Interface
     * to the Network layer.
     */
    RM_BLE_MESH_ERROR_CODE_NETWORK_CRYPTO_UNLIKELY_ERR = 0x2120,

    /** Network Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_NETWORK_API_NOT_SUPPORTED = 0x21FF,

    /** Lower Transport Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_MUTEX_INIT_FAILED = 0x2201,

    /** Lower Transport Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_COND_INIT_FAILED = 0x2202,

    /** Lower Transport Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_MUTEX_LOCK_FAILED = 0x2203,

    /** Lower Transport Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_MUTEX_UNLOCK_FAILED = 0x2204,

    /** Lower Transport Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_MEMORY_ALLOCATION_FAILED = 0x2205,

    /** Lower Transport Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_INVALID_PARAMETER_VALUE = 0x2211,

    /** Lower Transport Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_PARAMETER_OUTSIDE_RANGE = 0x2212,

    /** Lower Transport Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_NULL_PARAMETER_NOT_ALLOWED = 0x2213,

    /** Lower Transport Error Code for SAR Context Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_LOWER_TRANS_SAR_CTX_ALLOCATION_FAILED = 0x2214,

    /** Upper Transport Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_MUTEX_INIT_FAILED = 0x2301,

    /** Upper Transport Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_COND_INIT_FAILED = 0x2302,

    /** Upper Transport Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_MUTEX_LOCK_FAILED = 0x2303,

    /** Upper Transport Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_MUTEX_UNLOCK_FAILED = 0x2304,

    /** Upper Transport Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_MEMORY_ALLOCATION_FAILED = 0x2305,

    /** Upper Transport Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_INVALID_PARAMETER_VALUE = 0x2311,

    /** Upper Transport Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_PARAMETER_OUTSIDE_RANGE = 0x2312,

    /** Upper Transport Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_NULL_PARAMETER_NOT_ALLOWED = 0x2313,

    /** Upper Transport Error Code for Queue Full */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_QUEUE_FULL = 0x2314,

    /** Upper Transport Error Code for Queue Empty */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_QUEUE_EMPTY = 0x2315,

    /** Upper Transport Error Code for Incomplete Packet Reception */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_INCOMPLETE_PACKET_RECEIVED = 0x2316,

    /** Upper Transport Error Code for Invalid Friendship State */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_INVALID_FRNDSHIP_STATE = 0x2317,

    /** Upper Transport Error Code for Friendship Cleared on Timeout */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_FRNDSHIP_CLEARED_ON_TIMEOUT = 0x2318,

    /**
     * Upper Transport Error code to tag all errors returned by the Crypto Interface
     * to the Transport layer.
     */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_CRYPTO_UNLIKELY_ERR = 0x2318,

    /** Upper Transport Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_UPPER_TRANS_API_NOT_SUPPORTED = 0x23FF,

    /** Access Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MUTEX_INIT_FAILED = 0x2401,

    /** Access Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_ACCESS_COND_INIT_FAILED = 0x2402,

    /** Access Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MUTEX_LOCK_FAILED = 0x2403,

    /** Access Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MUTEX_UNLOCK_FAILED = 0x2404,

    /** Access Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MEMORY_ALLOCATION_FAILED = 0x2405,

    /** Access Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_ACCESS_INVALID_PARAMETER_VALUE = 0x2411,

    /** Access Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_ACCESS_PARAMETER_OUTSIDE_RANGE = 0x2412,

    /** Access Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_ACCESS_NULL_PARAMETER_NOT_ALLOWED = 0x2413,

    /** Access Error Code for No Resources */
    RM_BLE_MESH_ERROR_CODE_ACCESS_NO_RESOURCE = 0x2420,

    /** Access Error Code for No Match */
    RM_BLE_MESH_ERROR_CODE_ACCESS_NO_MATCH = 0x2421,

    /** Access Error Code for Invalid Handle */
    RM_BLE_MESH_ERROR_CODE_ACCESS_INVALID_HANDLE = 0x2422,

    /** Access Error Code for Model Already Registered */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MODEL_ALREADY_REGISTERED = 0x2423,

    /** Access Error Code for Invalid Source Address */
    RM_BLE_MESH_ERROR_CODE_ACCESS_INVALID_SRC_ADDR = 0x2424,

    /** Access Error Code for Device Key Table Full */
    RM_BLE_MESH_ERROR_CODE_ACCESS_DEV_KEY_TABLE_FULL = 0x2425,

    /**
     * Access Error Code when detecting Packets with Master Network
     * Credentials from a known address with ongoing Friendship
     */
    RM_BLE_MESH_ERROR_CODE_ACCESS_MASTER_NID_ON_LPN = 0x2426,

    /** Access Error Code for Invalid Publication State */
    RM_BLE_MESH_ERROR_CODE_ACCESS_INVALID_PUBLICATION_STATE = 0x2427,

    /** Access Error Code for Invalid Publication TTL */
    RM_BLE_MESH_ERROR_CODE_ACCESS_INVALID_PUBLICATION_TTL = 0x2428,

    /** Access Error Code for not permitted IV Index Value */
    RM_BLE_MESH_ERROR_CODE_ACCESS_IV_VAL_NOT_PERMITTED = 0x2430,

    /**
     * Access Error Code for IV Update occurring too soon within the
     * stipulated/specified Time Limit
     */
    RM_BLE_MESH_ERROR_CODE_ACCESS_IV_UPDATE_TOO_SOON = 0x2431,

    /** Access Error Code for IV Update in Incorrect State */
    RM_BLE_MESH_ERROR_CODE_ACCESS_IV_INCORRECT_STATE = 0x2432,

    /** Access Error Code for IV Update deferred due to currently Busy State */
    RM_BLE_MESH_ERROR_CODE_ACCESS_IV_UPDATE_DEFERRED_IN_BUSY = 0x2433,

    /** Access Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_ACCESS_API_NOT_SUPPORTED = 0x24FF,

    /** Provisioning Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_MUTEX_INIT_FAILED = 0x3001,

    /** Provisioning Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_COND_INIT_FAILED = 0x3002,

    /** Provisioning Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_MUTEX_LOCK_FAILED = 0x3003,

    /** Provisioning Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_MUTEX_UNLOCK_FAILED = 0x3004,

    /** Provisioning Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_MEMORY_ALLOCATION_FAILED = 0x3005,

    /** Provisioning Error Code for Invalid State */
    RM_BLE_MESH_ERROR_CODE_PROVISION_INVALID_STATE = 0x3011,

    /** Bearer Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_PROVISION_INVALID_PARAMETER = 0x3012,

    /** Provisioning Error Code for Context Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_CONTEXT_ALLOC_FAILED = 0x3013,

    /** Provisioning Error Code for Context Assertion Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_CONTEXT_ASSERT_FAILED = 0x3014,

    /** Provisioning Error Code for Context Link Open */
    RM_BLE_MESH_ERROR_CODE_PROVISION_CONTEXT_LINK_OPEN = 0x3015,

    /** Provisioning Error Code for Bearer Assertion Failure */
    RM_BLE_MESH_ERROR_CODE_PROVISION_BEARER_ASSERT_FAILED = 0x3016,

    /** Provisioning Error Code for Procedure Timeout */
    RM_BLE_MESH_ERROR_CODE_PROVISION_PROCEDURE_TIMEOUT = 0x3017,

    /** Generic Model Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_MUTEX_INIT_FAILED = 0x4001,

    /** Generic Model Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_COND_INIT_FAILED = 0x4002,

    /** Generic Model Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_MUTEX_LOCK_FAILED = 0x4003,

    /** Generic Model Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_MUTEX_UNLOCK_FAILED = 0x4004,

    /** Generic Model Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_MEMORY_ALLOCATION_FAILED = 0x4005,

    /** Generic Model Error Code for Invalid State */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_INVALID_STATE = 0x4011,

    /** Generic Model Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_INVALID_PARAMETER = 0x4012,

    /** Generic Model Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_PARAMETER_OUTSIDE_RANGE = 0x4013,

    /** Generic Model Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_NULL_PARAMETER_NOT_ALLOWED = 0x4014,

    /** Generic Model Error Code for Invalid Model Handle */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_INVALID_MODEL_HANDLE = 0x4015,

    /** Generic Model Error Code for Invalid Element Handle */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_INVALID_ELEMENT_HANDLE = 0x4016,

    /**
     * Generic Model Error Code when Operation is detected on a Node element which
     * is not Primary Element
     */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_NOT_PRIMARY_ELEMENT = 0x4017,

    /** Generic Model Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_GENERIC_MODEL_API_NOT_SUPPORTED = 0x40FF,

    /** Config Model Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_MUTEX_INIT_FAILED = 0x4101,

    /** Config Model Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_COND_INIT_FAILED = 0x4102,

    /** Config Model Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_MUTEX_LOCK_FAILED = 0x4103,

    /** Config Model Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_MUTEX_UNLOCK_FAILED = 0x4104,

    /** Config Model Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_MEMORY_ALLOCATION_FAILED = 0x4105,

    /** Config Model Error Code for Invalid State */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_INVALID_STATE = 0x4111,

    /** Config Model Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_INVALID_PARAMETER = 0x4112,

    /** Config Model Error Code for Parameter Outside Range */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_PARAMETER_OUTSIDE_RANGE = 0x4113,

    /** Config Model Error Code for NULL Parameter Not Allowed */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_NULL_PARAMETER_NOT_ALLOWED = 0x4114,

    /** Config Model Error Code for API Not Supported */
    RM_BLE_MESH_ERROR_CODE_CONFIG_MODEL_API_NOT_SUPPORTED = 0x41FF,

    /** Health Model Error Code for MUTEX Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_MUTEX_INIT_FAILED = 0x4201,

    /** Health Model Error Code for Conditional Variable Initialization Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_COND_INIT_FAILED = 0x4202,

    /** Health Model Error Code for MUTEX Lock Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_MUTEX_LOCK_FAILED = 0x4203,

    /** Health Model Error Code for MUTEX Unlock Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_MUTEX_UNLOCK_FAILED = 0x4204,

    /** Health Model Error Code for Memory Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_MEMORY_ALLOCATION_FAILED = 0x4205,

    /** Health Model Error Code for Invalid State */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_INVALID_STATE = 0x4211,

    /** Health Model Error Code for Invalid Parameter Value */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_INVALID_PARAMETER = 0x4212,

    /** Health Model Error Code for Context Allocation Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_CONTEXT_ALLOC_FAILED = 0x4213,

    /** Health Model Error Code for Context Assertion Failure */
    RM_BLE_MESH_ERROR_CODE_HEALTH_MODEL_CONTEXT_ASSERT_FAILED = 0x4214,

    /** A failure that does not match any other error code */
    RM_BLE_MESH_ERROR_CODE_FAILURE = 0xFFFF,
} rm_ble_mesh_error_code_t;

/** Node Feature */
typedef enum e_rm_ble_mesh_feature_select
{
    /** Relay Feature */
    RM_BLE_MESH_FEATURE_SELECT_RELAY = 0x0,

    /** Proxy Feature */
    RM_BLE_MESH_FEATURE_SELECT_PROXY = 0x1,

    /** Friend Feature */
    RM_BLE_MESH_FEATURE_SELECT_FRIEND = 0x2,

    /** Low Power Feature */
    RM_BLE_MESH_FEATURE_SELECT_LPN = 0x3,
} rm_ble_mesh_feature_select_t;

typedef enum e_rm_ble_mesh_feature_state
{
    /** BLE Mesh featre status - Disable */
    RM_BLE_MESH_FEATURE_STATE_DISABLE = 0x0,

    /** BLE Mesh featre status - Enable */
    RM_BLE_MESH_FEATURE_STATE_ENABLE = 0x1,
} rm_ble_mesh_feature_state_t;

/** Payload type */
typedef struct st_rm_ble_mesh_buffer
{
    /** Payload Pointer */
    uint8_t * payload;

    /** Payload Length */
    uint16_t length;
} rm_ble_mesh_buffer_t;

/** Access Status Transition Type */
typedef struct st_rm_ble_mesh_access_state_transition
{
    /** Transition Timer */
    rm_ble_mesh_timer_handle_t transition_timer_handle;

    /** Transition State. Initial/delay/transition */
    uint8_t transition_state;

    /** Delay */
    uint8_t delay;

    /** Transition Time */
    uint8_t transition_time;

    /** Transition Start Callback */
    void (* transition_start_callback)(void *);

    /** Transition Complete Callback */
    void (* transition_complete_callback)(void *);

    /** Blob/Context */
    void * p_context;
} rm_ble_mesh_access_state_transition_t;

/** BLE MESH control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_ble_mesh_instance_ctrl_t
 */
typedef void rm_ble_mesh_ctrl_t;

/** BLE MESH configuration parameters. */
typedef struct st_rm_ble_mesh_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                  ///< Select a channel corresponding to the channel number of the hardware.

    /** Number of Network Interfaces */
    uint32_t network_interfaces_num;

    /** Number of Provisioning Interfaces */
    uint32_t provisioning_interfaces_num;

    /** Network Cache Size */
    uint32_t network_cache_size;

    /** Network Sequence Number Cache Size */
    uint32_t network_sequence_num_cache_size;

    /** Maximum number of subnets the device can store information about. */
    uint32_t maximum_subnets;

    /** Maximum number of device keys the device can store information about. */
    uint32_t maximum_device_keys;

    /** Maximum number of addresses present in each proxy filter list. */
    uint32_t proxy_filter_list_size;

    /** Maximum number of LPNs. */
    uint32_t maximum_lpn;

    /** The size of Reassembled Cache. */
    uint32_t reassembled_cache_size;

    /** Number of Segmentation and Reassembly contexts. */
    uint32_t maximum_ltrn_sar_context;

    /**
     *  Maximum number of messages that the friend is capable to queue
     *  for a single Low Power Node.
     */
    uint32_t maximum_friend_message_queue;

    /**
     *  Maximum number of subscription addresses that the friend
     *  is capable to store for a single Low Power Node.
     */
    uint32_t maximum_friend_subscription_list;

    /** Maximum number of elements. */
    uint32_t maximum_access_element_num;

    /** Maximum number of models. */
    uint32_t maximum_access_model_num;

    /**
     *  Maximum number of Applications (keys) the device can store
     *  information about.
     */
    uint32_t maximum_application;

    /**
     *  Maximum number of Virtual Addresses the device can store
     *  information about.
     */
    uint32_t maximum_virtual_address;

    /**
     *  Maximum number of Non-Virtual Addresses the device can store
     *  information about.
     */
    uint32_t maximum_non_virtual_address;

    /**
     *  The distance between the network sequence numbers, for every persistent
     *  storage write. If the device is powered cycled, it will resume transmission
     *  using the sequence number from start of next block.
     */
    uint32_t net_sequence_number_block_size;

    /** Network Transmit Count for network packets */
    uint32_t net_tx_count;

    /** Network Interval Steps for network packets */
    uint32_t net_tx_interval_steps;

    /** Network Transmit Count for relayed packets */
    uint32_t net_relay_tx_count;

    /** Network Interval Steps for relayed packets */
    uint32_t net_relay_tx_interval_steps;

    /** Secure Network Beacon Interval */
    uint32_t config_server_snb_timeout;

    /** Poxy ADV Network ID timeout for each Subnet in milliseconds. */
    uint32_t proxy_subnet_netid_adv_timeout;

    /** Poxy ADV Node Identity timeout for each Subnet in milliseconds. */
    uint32_t proxy_subnet_nodeid_adv_timeout;

    /** Poxy ADV Node Identity overall time period in milliseconds. */
    uint32_t proxy_nodeid_adv_timeout;

    /** Friend Poll Retry Count - default value */
    uint32_t frnd_poll_retry_count;

    /** Lower Transport Segment Transmission Timeout in milliseconds */
    uint32_t ltrn_rtx_timeout;

    /** Lower Transport Segment Transmission Count - default value */
    uint32_t ltrn_rtx_count;

    /** Lower Transport Acknowledgment Timeout in milliseconds */
    uint32_t ltrn_ack_timeout;

    /** Lower Transport Incomplete Timeout in milliseconds */
    uint32_t ltrn_incomplete_timeout;

    /** Friendship Receive Window - default value */
    uint32_t frnd_receive_window;

    /** Friend Clear Confirmation Timeout in milliseconds */
    uint32_t lpn_clear_retry_timeout_initial;

    /** LPN Friend Clear Retry Count */
    uint32_t lpn_clear_retry_count;

    /** Friendship Retry Timeout in milliseconds */
    uint32_t trn_frndreq_retry_timeout;

    /** Unprovisioned Device Beacon Interleaved Beacon Timeout */
    uint32_t unprov_device_beacon_timeout;

    /**
     * Maximum number of messages that can be queued in Network layer
     * for Transmission.
     */
    uint32_t net_tx_queue_size;

    /** Maximum number of Transition Timers */
    uint32_t max_num_transition_timers;

    /** Maximum number of Periodic Step Timers */
    uint32_t max_num_periodic_step_timers;

    /**
     *  Maximum number of Health Server Instances.
     */
    uint32_t maximum_health_server_num;

    /** Maximum number of Light Lightness Controller Server Instances. */
    uint32_t maximum_light_lc_server_num;

    /** The size of the Replay Protection cache. */
    uint32_t replay_cache_size;

    /** Company ID */
    uint32_t default_company_id;

    /** Product ID */
    uint32_t default_product_id;

    /** Vendor ID */
    uint32_t default_vendor_id;

    void const * p_context;            ///< Placeholder for user data.
    void const * p_extend;             ///< Placeholder for user extension.
} rm_ble_mesh_cfg_t;

/** BLE MESH functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_api
{
    /** Open BLE mesh middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_ctrl_t * const p_ctrl, rm_ble_mesh_cfg_t const * const p_cfg);

    /** Close BLE mesh middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_ctrl_t * const p_ctrl);

    /** To start transition timer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_StartTransitionTimer()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  p_transition
     *             Pointer to state transition data structure, which includes the timeout,
     *             transition start and complete callback etc.
     *
     * @param[out] p_transition_time_handle
     *             Pointer to transition time handle, which can be used to stop the transition
     *             timer if required.
     */
    fsp_err_t (* startTransitionTimer)(rm_ble_mesh_ctrl_t * const                          p_ctrl,
                                       rm_ble_mesh_access_state_transition_t const * const p_transition,
                                       uint16_t * const                                    p_transition_time_handle);

    /** To stop transition timer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_StopTransitionTimer()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  transition_time_handle
     *             Transition time handle, returned by the Start Transition Timer
     *             interface.
     */
    fsp_err_t (* stopTransitionTimer)(rm_ble_mesh_ctrl_t * const p_ctrl, uint16_t transition_time_handle);

    /** To get remaining Transition Time.
     * @par Implemented as
     * - @ref RM_BLE_MESH_GetRemainingTransitionTime()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  transition_time_handle
     *             Transition time handle, returned by the Start Transition Timer
     *             interface.
     *
     * @param[out] p_remaining_transition_time
     *             Pointer to remaining transition time.
     */
    fsp_err_t (* getRemainingTransitionTime)(rm_ble_mesh_ctrl_t * const p_ctrl, uint16_t transition_time_handle,
                                             uint8_t * const p_remaining_transition_time);

    /** To get remaining Transition Time, with offset.
     * @par Implemented as
     * - @ref RM_BLE_MESH_GetRemainingTransitionTimeWithOffset()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  transition_time_handle
     *             Transition time handle, returned by the Start Transition Timer
     *             interface.
     *
     * @param[in]  offset_in_ms
     *             Offset in millisecond.
     *
     * @param[out] p_remaining_transition_time
     *             Pointer to remaining transition time.
     */
    fsp_err_t (* getRemainingTransitionTimeWithOffset)(rm_ble_mesh_ctrl_t * const p_ctrl,
                                                       uint16_t transition_time_handle, uint32_t offset_in_ms,
                                                       uint8_t * const p_remaining_transition_time);

    /** To convert transition time from millisecond.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ConvertTransitionTimeFromMs()
     *
     * @param[in]  p_ctrl
     *             Pointer to control structure.
     *
     * @param[in]  transition_time_in_ms
     *             Transition time in millisecond.
     *
     * @param[out] p_transition_time
     *             Pointer to converted value in Generic Default Transition Time state format.
     */
    fsp_err_t (* convertTransitionTimeFromMs)(rm_ble_mesh_ctrl_t * const p_ctrl, uint32_t transition_time_in_ms,
                                              uint8_t * const p_transition_time);

    /** To convert transition time to millisecond.
     * @par Implemented as
     * - @ref RM_BLE_MESH_ConvertTransitionTimeToMs()
     *
     * @param [in]  p_ctrl
     *              Pointer to control structure.
     *
     * @param [in]  transition_time
     *              Transition time in Generic Default Transition Time state format.
     *
     * @param [out] p_transition_time_in_ms
     *              Pointer to converted value of transition time in millisecond.
     */
    fsp_err_t (* convertTransitionTimeToMs)(rm_ble_mesh_ctrl_t * const p_ctrl, uint8_t transition_time,
                                            uint32_t * const p_transition_time_in_ms);
} rm_ble_mesh_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_instance
{
    rm_ble_mesh_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance.
    rm_ble_mesh_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_api_t const * p_api;   ///< Pointer to the API structure for this instance.
} rm_ble_mesh_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_API_H
