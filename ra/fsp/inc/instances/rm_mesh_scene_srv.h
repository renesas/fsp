/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_SCENE_SRV_H
#define RM_MESH_SCENE_SRV_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_scene_server_api.h"
#include "rm_ble_mesh_access.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_MESH_SCENE_SRV
 * @{
 **********************************************************************************************************************/

/** The state to identify a scene */
typedef struct st_rm_mesh_scene_srv_number_info
{
    /** The number to identify a scene */
    uint16_t number;
} rm_mesh_scene_srv_number_info_t;

/** The current status of a currently active scene */
typedef struct st_rm_mesh_scene_srv_status_info
{
    /** Status Code */
    uint8_t status_code;

    /** Scene Number of a current scene. */
    uint16_t current_scene;

    /** Scene Number of a target scene. */
    uint16_t target_scene;

    /* Remaining Time */
    uint8_t remaining_time;
} rm_mesh_scene_srv_status_info_t;

/** The current status of scene register */
typedef struct st_rm_mesh_scene_srv_register_status_info
{
    /** Status Code */
    uint8_t status_code;

    /** Scene Number of a current scene. */
    uint16_t current_scene;

    /** A list of scenes stored within an element */
    uint16_t * scenes;
    uint16_t   scenes_count;
} rm_mesh_scene_srv_register_status_info_t;

/**
 * TID and Transition is a structure which contains Transaction ID (TID) as mandatory field.
 * Other two fields, Transition Time and Delay are optional.
 *
 * TID field is a transaction identifier indicating whether the message is a new message or
 * a retransmission of a previously sent message.
 *
 * If present, the Transition Time field identifies the time that an element will take
 * to transition to the target state from the present state.
 *
 * The Delay field shall be present when the Transition Time field is present.
 * It identifies the message execution delay, representing a time interval between receiving
 * the message by a model and executing the associated model behaviors.
 */
typedef struct st_rm_mesh_scene_srv_ext_tid_and_transition_info
{
    uint8_t tid;
    uint8_t transition_time;
    uint8_t delay;
    uint8_t optional_fields_present;
} rm_mesh_scene_srv_ext_tid_and_transition_info_t;

/** BLE mesh scene instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_SCENE_SRV_Open() is called. */
typedef struct st_rm_mesh_scene_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_scene_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_scene_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_scene_server_api_t g_rm_ble_mesh_scene_server_on_rm_mesh_scene_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_SCENE_SRV_Open(rm_ble_mesh_scene_server_ctrl_t * const      p_ctrl,
                                 rm_ble_mesh_scene_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_SCENE_SRV_Close(rm_ble_mesh_scene_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SCENE_SRV_StateUpdate(rm_ble_mesh_scene_server_ctrl_t * const         p_ctrl,
                                        rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_SCENE_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_SCENE_SRV_H
