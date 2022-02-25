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

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_MESH_BEARER_PLATFORM RM_MESH_BEARER_PLATFORM
 * @{
 **********************************************************************************************************************/

#ifndef RM_MESH_BEARER_PLATFORM_H
#define RM_MESH_BEARER_PLATFORM_H

#include "bsp_api.h"

#include "rm_mesh_bearer_platform_cfg.h"
#include "rm_mesh_bearer_platform_api.h"
#include "r_ble_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef void (* rm_mesh_bearer_platform_gatt_iface_cb_t)(uint8_t event_name, uint8_t event_param, uint16_t conn_hdl,
                                                         st_ble_dev_addr_t * peer_addr);

typedef void (* rm_mesh_bearer_platform_vender_specific_cb_t)(uint16_t type, ble_status_t result,
                                                              st_ble_vs_evt_data_t * data);

typedef void (* rm_mesh_bearer_platform_gap_cb_t)(uint16_t type, ble_status_t result, st_ble_evt_data_t * data);

/** RM_BLE_MESH_BEARER private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_BEARER_Open() is called. */
typedef struct st_rm_mesh_bearer_platform_instance_ctrl
{
    uint32_t open;                         // Indicates whether the open() API has been successfully called.
    rm_mesh_bearer_platform_cfg_t * p_cfg; // Pointer to initial configurations.
    void const * p_context;                // Placeholder for user data.
} rm_mesh_bearer_platform_instance_ctrl_t;

/** Bearer port extension for renesas BLE stack. */
typedef struct st_rm_mesh_bearer_platform_extended_cfg
{
    uint8_t gatt_server_callback_num;                                      // Number of GATT server callback
    uint8_t gatt_client_callback_num;                                      // Number of GATT client callback
    rm_mesh_bearer_platform_vender_specific_cb_t vender_specific_callback; // Vender specific callback function
} rm_mesh_bearer_platform_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_mesh_bearer_platform_api_t g_rm_mesh_bearer_platform_on_rm_mesh_bearer_platform;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MESH_BEARER_PLATFORM_Open(rm_mesh_bearer_platform_ctrl_t * const      p_ctrl,
                                       rm_mesh_bearer_platform_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_BEARER_PLATFORM_Close(rm_mesh_bearer_platform_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_BEARER_PLATFORM_Setup(rm_mesh_bearer_platform_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_BEARER_PLATFORM_CallbackSet(rm_mesh_bearer_platform_ctrl_t * const  p_ctrl,
                                              rm_mesh_bearer_platform_gatt_iface_cb_t callback);
fsp_err_t RM_MESH_BEARER_PLATFORM_SetGattMode(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                              rm_mesh_bearer_platform_gatt_mode_t    mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_GetGattMode(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                              rm_mesh_bearer_platform_gatt_mode_t  * p_mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_SetScanResponseData(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                                      uint8_t                              * p_data,
                                                      uint8_t                                len);
fsp_err_t RM_MESH_BEARER_PLATFORM_ScanGattBearer(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                                 rm_mesh_bearer_platform_state_t        state,
                                                 rm_mesh_bearer_platform_gatt_mode_t    mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_Connect(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                          uint8_t                              * p_remote_address,
                                          uint8_t                                address_type,
                                          rm_mesh_bearer_platform_gatt_mode_t    mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_DiscoverService(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                                  uint16_t                               handle,
                                                  rm_mesh_bearer_platform_gatt_mode_t    mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_ConfigureNotification(rm_mesh_bearer_platform_ctrl_t * const p_ctrl,
                                                        uint16_t                               handle,
                                                        rm_mesh_bearer_platform_state_t        state,
                                                        rm_mesh_bearer_platform_gatt_mode_t    mode);
fsp_err_t RM_MESH_BEARER_PLATFORM_Disconnect(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint16_t handle);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_BEARER_PLATFORM_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_MESH_BEARER_PLATFORM)
 **********************************************************************************************************************/
