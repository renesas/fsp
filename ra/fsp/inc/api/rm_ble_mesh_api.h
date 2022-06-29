/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/** BLE MESH error code. */
typedef enum e_rm_ble_mesh_error_code
{
    RM_BLE_MESH_SUCCESS = 0x0000,

    /** Invalid Address */
    RM_BLE_MESH_INVALID_ADDRESS = 0x0001,

    /** Invalid Model */
    RM_BLE_MESH_INVALID_MODEL = 0x0002,

    /** Invalid AppKey Index */
    RM_BLE_MESH_INVALID_APPKEY_INDEX = 0x0003,

    /** Invalid NetKey Index */
    RM_BLE_MESH_INVALID_NETKEY_INDEX = 0x0004,

    /** Insufficient Resources */
    RM_BLE_MESH_INSUFFICIENT_RESOURCES = 0x0005,

    /** Key Index Already Stored */
    RM_BLE_MESH_KEY_INDEX_ALREADY_STORED = 0x0006,

    /** Invalid Publish Parameters */
    RM_BLE_MESH_INVALID_PUBLISH_PARAMETER = 0x0007,

    /** Not a Subscribe Model */
    RM_BLE_MESH_NOT_A_SUBSCRIBE_MODEL = 0x0008,

    /** Storage Failure */
    RM_BLE_MESH_STORAGE_FAILURE = 0x0009,

    /** Feature Not Supported */
    RM_BLE_MESH_FEATURE_NOT_SUPPORTED = 0x000A,

    /** Cannot Update */
    RM_BLE_MESH_CANNOT_UPDATE = 0x000B,

    /** Cannot Remove */
    RM_BLE_MESH_CANNOT_REMOVE = 0x000C,

    /** Cannot Bind */
    RM_BLE_MESH_CANNOT_BIND = 0x000D,

    /** Temporarily Unable to Change State */
    RM_BLE_MESH_TEMP_UNABLE_TO_CHANGE_STATE = 0x000E,

    /** Cannot Set */
    RM_BLE_MESH_CANNOT_SET = 0x000F,

    /** Unspecified Error */
    RM_BLE_MESH_UNSPECIFIED_ERROR = 0x0010,

    /** Invalid Binding */
    RM_BLE_MESH_INVALID_BINDING = 0x0011,
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
