/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_GENERIC_LOC_SRV_H
#define RM_MESH_GENERIC_LOC_SRV_H

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
 * @addtogroup RM_MESH_GENERIC_LOC_SRV
 * @{
 **********************************************************************************************************************/

/** Generic Global Location state defines location information of an element */
typedef struct st_rm_mesh_generic_loc_srv_global_info
{
    /** Global Coordinates (Latitude) */
    uint32_t global_latitude;

    /** Global Coordinates (Longitude) */
    uint32_t global_longitude;

    /** Global Altitude */
    uint16_t global_altitude;
} rm_mesh_generic_loc_srv_global_info_t;

/** Generic Local Location state defines location information of an element */
typedef struct st_rm_mesh_generic_loc_srv_local_info
{
    /** Local Coordinates (North) */
    uint16_t local_north;

    /** Local Coordinates (East) */
    uint16_t local_east;

    /** Local Altitude */
    uint16_t local_altitude;

    /** Floor Number */
    uint8_t floor_number;

    /** Uncertainty */
    uint16_t uncertainty;
} rm_mesh_generic_loc_srv_local_info_t;

/**
 * Generic Location state is a composite state that includes a Generic Location
 * Global state and a Generic Location Local state
 */
typedef struct st_rm_mesh_generic_loc_srv_state_info
{
    /** Global Location */
    rm_mesh_generic_loc_srv_global_info_t global_location;

    /** Local Location */
    rm_mesh_generic_loc_srv_local_info_t local_location;
} rm_mesh_generic_loc_srv_state_info_t;

/** BLE mesh generic loc instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_LOC_SRV_Open() is called. */
typedef struct st_rm_mesh_generic_loc_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_generic_loc_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_generic_loc_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_LOC_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                       rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_LOC_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_LOC_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                              rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_GENERIC_LOC_SRV_SetupServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                         rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_LOC_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_LOC_SRV_H
