/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_SCENE_CLT_H
#define RM_MESH_SCENE_CLT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_model_client_api.h"
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
 * Scene Recall message parameters.
 */
typedef struct st_rm_mesh_scene_recall_info
{
    /** The number of the scene to be recalled. */
    uint16_t scene_number;

    /** Transaction Identifier */
    uint8_t transaction_id;

    /**
     * Transition Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    uint8_t transition_time;

    /** Message execution delay in 5 milliseconds steps */
    uint8_t delay;

    /** Flag: To represent if optional Transaction time and Delay fields are valid */
    uint8_t optional_fields_present;
} rm_mesh_scene_recall_info_t;

/**
 * Scene Status message parameters.
 */
typedef struct st_rm_mesh_scene_status_info
{
    /** Status Code */
    uint8_t status_code;

    /** Scene Number of a current scene. */
    uint16_t current_scene;

    /** Scene Number of a target scene. (Optional) */
    uint16_t target_scene;

    /**
     * Remaining Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    uint8_t remaining_time;

    /** Flag: To represent if optional fields Target Scene and Remaining Time are valid */
    uint8_t optional_fields_present;
} rm_mesh_scene_status_info_t;

/**
 * Scene Register Status message parameters.
 */
typedef struct st_rm_mesh_scene_register_status_info
{
    /** Status Code */
    uint8_t status_code;

    /** Scene Number of a current scene */
    uint16_t current_scene;

    /** A list of scenes stored within an element */
    uint8_t * scenes;

    /** Number of Scenes */
    uint16_t scenes_length;
} rm_mesh_scene_register_status_info_t;

/**
 * Scene Store message parameters.
 */
typedef struct st_rm_mesh_scene_info
{
    /** The number of the scene to be stored. */
    uint16_t scene_number;
} rm_mesh_scene_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_SCENE_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh scene instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_SCENE_CLT_Open() is called. */
typedef struct st_rm_mesh_scene_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_scene_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_scene_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_SCENE_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                 rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_SCENE_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SCENE_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                           rm_ble_mesh_access_model_handle_t * const model_handle);
fsp_err_t RM_MESH_SCENE_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                            uint32_t                                req_opcode,
                                            void const * const                      parameter,
                                            uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_SCENE_CLT_Get(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SCENE_CLT_Recall(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SCENE_CLT_RecallUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 void const * const                      p_parameter);
fsp_err_t RM_MESH_SCENE_CLT_RegisterGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SCENE_CLT_Store(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SCENE_CLT_StoreUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                void const * const                      p_parameter);
fsp_err_t RM_MESH_SCENE_CLT_Delete(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SCENE_CLT_DeleteUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_SCENE_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_SCENE_CLT_H
