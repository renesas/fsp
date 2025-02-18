/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_GENERIC_ON_OFF_SRV_H
#define RM_MESH_GENERIC_ON_OFF_SRV_H

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
 * @addtogroup RM_MESH_GENERIC_ON_OFF_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Generic OnOff state is a Boolean value that represents the state of an
 * element
 */
typedef struct st_rm_mesh_generic_on_off_srv_info
{
    /** Generic On/Off */
    uint8_t onoff;

    /** Target On/Off - Used in response path */
    uint8_t target_onoff;

    /** Last On/Off */
    uint8_t last_onoff;

    /** TID - Used in request path */
    uint8_t tid;

    /**
     * Transition Time - Used in request path.
     * Used as remaining time in response path.
     */
    uint8_t transition_time;

    /** Delay - Used in request path */
    uint8_t delay;

    /** Transition Timer Handle */
    uint16_t transition_time_handle;
} rm_mesh_generic_on_off_srv_info_t;

/** BLE mesh generic on off instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_ON_OFF_SRV_Open() is called. */
typedef struct st_rm_mesh_generic_on_off_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_generic_on_off_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_generic_on_off_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_ON_OFF_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                          rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_ON_OFF_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_ON_OFF_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                 rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_ON_OFF_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_ON_OFF_SRV_H
