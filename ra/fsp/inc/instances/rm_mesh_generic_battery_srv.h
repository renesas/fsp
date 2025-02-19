/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_GENERIC_BATTERY_SRV_H
#define RM_MESH_GENERIC_BATTERY_SRV_H

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
 * @addtogroup RM_MESH_GENERIC_BATTERY_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Generic Battery state is a set of four values representing the state of a
 * battery
 */
typedef struct st_rm_mesh_generic_battery_srv_info
{
    /**
     * Generic Battery Level state is a value ranging from 0 percent through 100
     * percent
     */
    uint8_t generic_battery_level;

    /**
     * Generic Battery Time to Discharge state is a 24-bit unsigned value ranging
     * from 0 through 0xFFFFFF
     */
    uint32_t generic_battery_time_to_discharge;

    /**
     * Generic Battery Time to Charge state is a 24-bit unsigned value ranging from
     * 0 through 0xFFFFFF
     */
    uint32_t generic_battery_time_to_charge;

    /**
     * Generic Battery Flags state is a concatenation of four 2-bit bit fields:
     * Presence, Indicator, Charging, and Serviceability
     */
    uint8_t generic_battery_flags;
} rm_mesh_generic_battery_srv_info_t;

/** BLE mesh generic_battery instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_BATTERY_SRV_Open() is called. */
typedef struct st_rm_mesh_generic_battery_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_generic_battery_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_generic_battery_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_BATTERY_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                           rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_BATTERY_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_BATTERY_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                  rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_BATTERY_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_BATTERY_SRV_H
