/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_SCHEDULER_SRV_H
#define RM_MESH_SCHEDULER_SRV_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_model_server_api.h"
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
 * @addtogroup RM_MESH_SCHEDULER_SRV
 * @{
 **********************************************************************************************************************/

/** The current Schedule Register state of an element. */
typedef struct st_rm_mesh_scheduler_srv_schedules_info
{
    /** Bit field indicating defined Actions in the Schedule Register */
    uint16_t schedules;
} rm_mesh_scheduler_srv_schedules_info_t;

/** The entry index of the Schedule Register state */
typedef struct st_rm_mesh_scheduler_srv_entry_index_info
{
    /** Index of the Schedule Register entry */
    uint8_t index;
} rm_mesh_scheduler_srv_entry_index_info_t;

/** The entry of the Schedule Register state */
typedef struct st_rm_mesh_scheduler_srv_entry_info
{
    /** Index of the Schedule Register entry */
    uint8_t index;

    /** Scheduled year for the action */
    uint8_t year;

    /** Scheduled month for the action */
    uint16_t month;

    /** Scheduled day of the month for the action */
    uint8_t day;

    /** Scheduled hour for the action */
    uint8_t hour;

    /** Scheduled minute for the action */
    uint8_t minute;

    /** Scheduled second for the action */
    uint8_t second;

    /** Schedule days of the week for the action */
    uint8_t dayofweek;

    /** Action to be performed at the scheduled time */
    uint8_t action;

    /** Transition time for this action */
    uint8_t transition_time;

    /** Scene number to be used for some actions */
    uint16_t scene_number;
} rm_mesh_scheduler_srv_entry_info_t;

/** BLE mesh scheduler instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_SCHEDULER_SRV_Open() is called. */
typedef struct st_rm_mesh_scheduler_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_scheduler_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_scheduler_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_SCHEDULER_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_SCHEDULER_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SCHEDULER_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                            rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_SCHEDULER_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_SCHEDULER_SRV_H
