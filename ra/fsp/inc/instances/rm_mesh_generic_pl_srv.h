/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_GENERIC_PL_SRV_H
#define RM_MESH_GENERIC_PL_SRV_H

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
 * @addtogroup RM_MESH_GENERIC_PL_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Generic Power Actual state determines the linear percentage of the maximum
 * power level of an element, representing a range from 0 percent through 100
 * percent
 */
typedef struct st_rm_mesh_generic_pl_srv_actual_state_info
{
    /** Generic Power Actual */
    uint16_t power_actual;

    /* TID - Used only in request path */
    uint8_t tid;

    /** Generic Power Target - Used only in response path */
    uint16_t power_target;

    /**
     * Transition Time - Used in request path
     * Used as Remaining Time in response path
     */
    uint8_t transition_time;

    /* Delay - Used only in request path */
    uint8_t delay;

    /** Transition Timer Handle */
    uint16_t transition_time_handle;
} rm_mesh_generic_pl_srv_actual_state_info_t;

/**
 * Generic Power Last state is a 16-bit value representing a percentage ranging
 * from (1/65535) percent to 100 percent
 */
typedef struct st_rm_mesh_generic_pl_srv_last_state_info
{
    /** Generic Power Last */
    uint16_t power_last;
} rm_mesh_generic_pl_srv_last_state_info_t;

/** Generic Power Default state is a 16-bit value ranging from 0 through 65535 */
typedef struct st_rm_mesh_generic_pl_srv_default_state_info
{
    /** Generic Power Default */
    uint16_t power_default;
} rm_mesh_generic_pl_srv_default_state_info_t;

/**
 * Generic Power Range state determines the minimum and maximum power levels of
 * an element relative to the maximum power level an element can output
 */
typedef struct st_rm_mesh_generic_pl_srv_range_state_info
{
    /** Generic Power Range - Minimum */
    uint16_t power_range_min;

    /** Generic Power Range - Maximum */
    uint16_t power_range_max;

    /** Status - Used only in the response path */
    uint8_t status;
} rm_mesh_generic_pl_srv_range_state_info_t;

/**
 * Generic Power Level state is a composite state that includes a Generic Power
 * Actual state, a Generic Power Last state, a Generic Power Default state, and
 * a Generic Power Range state
 */
typedef struct st_rm_mesh_generic_pl_srv_state_info
{
    /** Generic Power Actual */
    rm_mesh_generic_pl_srv_actual_state_info_t generic_power_actual;

    /** Generic Power Last */
    rm_mesh_generic_pl_srv_last_state_info_t generic_power_last;

    /** Generic Power Default */
    rm_mesh_generic_pl_srv_default_state_info_t generic_power_default;

    /** Generic Power Range */
    rm_mesh_generic_pl_srv_range_state_info_t generic_power_range;
} rm_mesh_generic_pl_srv_state_info_t;

/** BLE mesh generic pl instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_PL_SRV_Open() is called. */
typedef struct st_rm_mesh_generic_pl_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_generic_pl_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_generic_pl_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_PL_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                      rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_PL_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                             rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_GENERIC_PL_SRV_SetupServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                        rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_PL_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_PL_SRV_H
