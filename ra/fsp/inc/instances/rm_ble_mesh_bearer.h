/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_BLE_MESH_BEARER RM_BLE_MESH_BEARER
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_MESH_BEARER_H
#define RM_BLE_MESH_BEARER_H

#include "bsp_api.h"

#include "rm_ble_mesh_bearer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RM_BLE_MESH_BEARER private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_BEARER_Open() is called. */
typedef struct st_rm_ble_mesh_bearer_instance_ctrl
{
    uint32_t open;                          // Indicates whether the open() API has been successfully called.
    rm_ble_mesh_bearer_cfg_t const * p_cfg; // Pointer to initial configurations.
    void * p_context;                       // Placeholder for user data.
} rm_ble_mesh_bearer_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_bearer_api_t g_rm_ble_mesh_bearer_on_rm_ble_mesh_bearer;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_MESH_BEARER_Open(rm_ble_mesh_bearer_ctrl_t * const      p_ctrl,
                                  rm_ble_mesh_bearer_cfg_t const * const p_cfg);
fsp_err_t RM_BLE_MESH_BEARER_Close(rm_ble_mesh_bearer_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_BEARER_RegisterInterface(rm_ble_mesh_bearer_ctrl_t * const            p_ctrl,
                                               rm_ble_mesh_bearer_type_t                    brr_type,
                                               rm_ble_mesh_bearer_ntf_callback_result_t ( * p_callback)(
                                                   rm_ble_mesh_bearer_ntf_callback_args_t * p_args));
fsp_err_t RM_BLE_MESH_BEARER_RegisterBeaconHandler(rm_ble_mesh_bearer_ctrl_t * const               p_ctrl,
                                                   rm_ble_mesh_bearer_beacon_type_t                bcon_type,
                                                   void (                                        * p_handler)(
                                                       rm_ble_mesh_bearer_beacon_callback_args_t * p_args));
fsp_err_t RM_BLE_MESH_BEARER_AddBearer(rm_ble_mesh_bearer_ctrl_t * const       p_ctrl,
                                       rm_ble_mesh_bearer_type_t               brr_type,
                                       rm_ble_mesh_bearer_info_t const * const p_brr_info,
                                       rm_ble_mesh_bearer_handle_t * const     p_brr_handle);
fsp_err_t RM_BLE_MESH_BEARER_RemoveBearer(rm_ble_mesh_bearer_ctrl_t * const         p_ctrl,
                                          rm_ble_mesh_bearer_type_t                 brr_type,
                                          rm_ble_mesh_bearer_handle_t const * const p_brr_handle);
fsp_err_t RM_BLE_MESH_BEARER_ObserveBeacon(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t bcon_type, uint8_t enable);
fsp_err_t RM_BLE_MESH_BEARER_BcastUnprovisionedBeacon(rm_ble_mesh_bearer_ctrl_t * const  p_ctrl,
                                                      uint8_t                            type,
                                                      uint8_t const * const              p_dev_uuid,
                                                      uint16_t                           oob_info,
                                                      rm_ble_mesh_buffer_t const * const p_uri);
fsp_err_t RM_BLE_MESH_BEARER_BroadcastBeacon(rm_ble_mesh_bearer_ctrl_t * const p_ctrl,
                                             uint8_t                           type,
                                             uint8_t const * const             p_packet,
                                             uint16_t                          length);
fsp_err_t RM_BLE_MESH_BEARER_StartProxyAdv(rm_ble_mesh_bearer_ctrl_t * const p_ctrl,
                                           uint8_t                           type,
                                           uint8_t const * const             p_data,
                                           uint16_t                          datalen);
fsp_err_t RM_BLE_MESH_BEARER_SendPdu(rm_ble_mesh_bearer_ctrl_t * const         p_ctrl,
                                     rm_ble_mesh_bearer_handle_t const * const p_brr_handle,
                                     rm_ble_mesh_bearer_type_t                 brr_type,
                                     rm_ble_mesh_buffer_t const * const        p_buffer);
fsp_err_t RM_BLE_MESH_BEARER_GetPacketRssi(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t * p_rssi_value);
fsp_err_t RM_BLE_MESH_BEARER_Sleep(rm_ble_mesh_bearer_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_BEARER_Wakeup(rm_ble_mesh_bearer_ctrl_t * const p_ctrl, uint8_t mode);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_BEARER

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLE_MESH_BEARER)
 **********************************************************************************************************************/
