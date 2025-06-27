/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_BLE_MESH_LOWER_TRANS_API_H
#define RM_BLE_MESH_LOWER_TRANS_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_BLE_MESH_INTERFACES
 * @defgroup  RM_BLE_MESH_LOWER_TRANS_API BLE Mesh Lower Trans Interface
 * @brief     Interface for BLE Mesh Lower Trans functions.
 *
 * @section   RM_BLE_MESH_LOWER_TRANS_API_Summary Summary
 * The BLE Mesh Lower Trans middleware provides a lower-level transfer interface for BLE Mesh services.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

#include "rm_ble_mesh_network_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Transport Message Type */
typedef enum e_rm_ble_mesh_lower_trans_message_type
{
    /** Access Layer Packet */
    RM_BLE_MESH_LOWER_TRANS_MESSAGE_TYPE_ACCESS = 0x00,

    /** Transport Layer Control Packet */
    RM_BLE_MESH_LOWER_TRANS_MESSAGE_TYPE_CTRL = 0x01,
} rm_ble_mesh_lower_trans_message_type_t;

/** If requires lower transport ACK */
typedef  enum e_rm_ble_mesh_lower_trans_reliable
{
    RM_BLE_MESH_LOWER_TRANS_RELIABLE_DISABLE = 0x0, ///< ACK enable
    RM_BLE_MESH_LOWER_TRANS_RELIABLE_ENABLE  = 0x1, ///< ACK disable
} rm_ble_mesh_lower_trans_reliable_t;

/** LPN handle */
typedef uint8_t rm_ble_mesh_lower_trans_lpn_handle_t;

/** transport PDUs setting to peer device. */
typedef struct st_rm_ble_mesh_lower_trans_transmit_setting
{
    rm_ble_mesh_network_address_t          src_addr;      ///< Source address
    rm_ble_mesh_network_address_t          dst_addr;      ///< Destination address
    rm_ble_mesh_network_subnet_handle_t    subnet_handle; ///< Handle identifying the subnet
    rm_ble_mesh_lower_trans_message_type_t msg_type;      ///< Transport message type
    uint8_t ttl;                                          ///< Time to Live
    uint8_t akf;                                          ///< Application key flag
    uint8_t aid;                                          ///< Application key identifier
    uint8_t seq_num;                                      ///< Sequence number
} rm_ble_mesh_lower_trans_transmit_setting_t;

/** Callback event  */
typedef  enum e_rm_ble_mesh_lower_trans_event
{
    RM_BLE_MESH_LOWER_TRANS_EVENT_RX_COMPLETED              = 0x00, ///< BLE Mesh Lower Trans event - RX completed
    RM_BLE_MESH_LOWER_TRANS_EVENT_RX_FROM_FRIEND            = 0x01, ///< BLE Mesh Lower Trans event - RX from friend
    RM_BLE_MESH_LOWER_TRANS_EVENT_ADD_UPPER_TRANS_COMPLETED = 0x02, ///< BLE Mesh Lower Trans event - Add Upper Trans completed
    RM_BLE_MESH_LOWER_TRANS_EVENT_SEG_TX_CANCELED           = 0x03, ///< BLE Mesh Lower Trans event - TX canceled
    RM_BLE_MESH_LOWER_TRANS_EVENT_SEG_TX_COMPLETED          = 0x04, ///< BLE Mesh Lower Trans event - TX completed
} rm_ble_mesh_lower_trans_event_t;

/** Whether to enable the event or not. */
typedef  enum e_rm_ble_mesh_lower_trans_notification
{
    RM_BLE_MESH_LOWER_TRANS_NOTIFICATION_DISABLE = 0, ///< Callback disable
    RM_BLE_MESH_LOWER_TRANS_NOTIFICATION_ENABLE  = 1, ///< Callback enable
} rm_ble_mesh_lower_trans_notification_t;

/** BLE Mesh lower trans callback parameter definition */
typedef struct st_rm_ble_mesh_lower_trans_callback_args
{
    rm_ble_mesh_lower_trans_event_t     event;         ///< Event code.
    rm_ble_mesh_network_header_t      * p_header;      ///< Network header
    rm_ble_mesh_network_subnet_handle_t subnet_handle; ///< Subnet handle
    uint8_t trans_mic_size;                            ///< TransMIC size
    rm_ble_mesh_lower_trans_lpn_handle_t lpn_handle;   ///< LPM Size
    uint8_t              packet_type;                  ///< packet type
    rm_ble_mesh_buffer_t event_data;                   ///< Event data
    void               * p_context;                    ///< Context provided to user during callback.
} rm_ble_mesh_lower_trans_callback_args_t;

/** BLE MESH control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 */
typedef void rm_ble_mesh_lower_trans_ctrl_t;

/** BLE MESH configuration parameters. */
typedef struct st_rm_ble_mesh_lower_trans_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                      ///< Select a channel corresponding to the channel number of the hardware.
    rm_ble_mesh_lower_trans_notification_t notification;
    rm_ble_mesh_network_instance_t const * p_mesh_network_instance;        ///< Instance structure of BLE Mesh network
    void (* p_callback)(rm_ble_mesh_lower_trans_callback_args_t * p_args); ///< Callback function

    void       * p_context;                                                ///< Placeholder for user data.
    void const * p_extend;                                                 ///< Placeholder for extension data.
} rm_ble_mesh_lower_trans_cfg_t;

/** BLE MESH functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_lower_trans_api
{
    /** Register Interface with Lower Transport Layer.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_lower_trans_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_lower_trans_cfg_t const * const p_cfg);

    /** Unregister Interface with Lower Transport Layer.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl);

    /** API to send transport PDUs.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  p_transmit_setting  Pointer to transmit setting structure.
     * @param[in]  p_buffer            Pointer to payload and payload length structure.
     * @param[in]  reliable            If requires lower transport ACK, set reliable as RM_BLE_MESH_LOWER_TRANS_RELIABLE_ENABLE.
     */
    fsp_err_t (* sendPdu)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl,
                          rm_ble_mesh_lower_trans_transmit_setting_t const * const p_transmit_setting,
                          rm_ble_mesh_buffer_t const * const p_buffer, rm_ble_mesh_lower_trans_reliable_t reliable);

    /** To clear all segmentation and reassembly contexts.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     */
    fsp_err_t (* clearSarContexts)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl);

    /** To clear all segmentation and reassembly contexts for a given subnet.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  subnet_handle       Subnet Handle whose respective SAR Contexts are to be cleared.
     */
    fsp_err_t (* clearSubnetSarContexts)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl,
                                         rm_ble_mesh_network_subnet_handle_t    subnet_handle);

    /** To reinitialize all Lower Transport replay cache entries.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     */
    fsp_err_t (* reinitReplayCache)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl);

    /** To trigger any Lower Transport pending transmissions.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     */
    fsp_err_t (* triggerPendingTransmits)(rm_ble_mesh_lower_trans_ctrl_t * const p_ctrl);
} rm_ble_mesh_lower_trans_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_lower_trans_instance
{
    rm_ble_mesh_lower_trans_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_lower_trans_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_lower_trans_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_lower_trans_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_LOWER_TRANS_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_LOWER_TRANS_API_H
