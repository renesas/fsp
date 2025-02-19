/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_LIGHT_CTL_SRV_H
#define RM_MESH_LIGHT_CTL_SRV_H

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
 * @addtogroup RM_MESH_LIGHT_CTL_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Light CTL state is a composite state that includes the Light CTL Lightness,
 * the Light CTL Temperature and the Light CTL Delta UV states
 */
typedef struct st_rm_mesh_light_ctl_srv_info
{
    /** Light CTL Lightness */
    uint16_t ctl_lightness;

    /** Target Light CTL Lightness - Used in response path */
    uint16_t target_ctl_lightness;

    /** Light CTL Temperature */
    uint16_t ctl_temperature;

    /** Terget Light CTL Temperature - Used in response path */
    uint16_t target_ctl_temperature;

    /** Light CTL Delta UV */
    uint16_t ctl_delta_uv;

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
} rm_mesh_light_ctl_srv_info_t;

/**
 * Light CTL Default state is a composite state that includes the Light CTL
 * Lightness, the Light CTL Temperature and the Light CTL Delta UV states
 */
typedef struct st_rm_mesh_light_ctl_srv_default_info
{
    /** Light CTL Lightness */
    uint16_t ctl_lightness;

    /** Light CTL Temperature */
    uint16_t ctl_temperature;

    /** Light CTL Delta UV */
    uint16_t ctl_delta_uv;
} rm_mesh_light_ctl_srv_default_info_t;

/**
 * Light CTL Temperature state is a composite state that includes the Light CTL
 * Temperature and the Light CTL Delta UV states
 */
typedef struct st_rm_mesh_light_ctl_srv_temperature_info
{
    /** Light CTL Temperature */
    uint16_t ctl_temperature;

    /** Target Light CTL Temperature - Used in response path */
    uint16_t target_ctl_temperature;

    /** Light CTL Delta UV */
    uint16_t ctl_delta_uv;

    /** Target Light CTL Delta UV - Used in response path */
    uint16_t target_ctl_delta_uv;

    /** TID - Used in request path */
    uint8_t tid;

    /**
     * Transition Time - Used in request path.
     * Used as remaining time in response path.
     */
    uint8_t transition_time;

    /** Delay - Used in request path */
    uint8_t delay;
} rm_mesh_light_ctl_srv_temperature_info_t;

/**
 * Light CTL Temperature Range state determines the minimum and maximum color
 * temperatures of tunable white light an element is capable of emitting
 */
typedef struct st_rm_mesh_light_ctl_srv_temperature_range_info
{
    /** CTL Temperature Range Min */
    uint16_t ctl_temperature_range_min;

    /** CTL Temperature Range Max */
    uint16_t ctl_temperature_range_max;

    /** Status - Used in response path */
    uint8_t status;
} rm_mesh_light_ctl_srv_temperature_range_info_t;

/** BLE mesh light ctl extension for BLE mesh light ctl. */
typedef struct st_rm_mesh_light_ctl_srv_extended_cfg
{
    rm_ble_mesh_access_instance_t const * p_temperature_access_instance; ///< Pointer to access instance for temperature model.
} rm_mesh_light_ctl_srv_extended_cfg_t;

/** BLE mesh light ctl instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_LIGHT_CTL_SRV_Open() is called. */
typedef struct st_rm_mesh_light_ctl_srv_instance_ctrl
{
    uint32_t open;                     // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;
    rm_ble_mesh_access_model_handle_t temperature_model_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_light_ctl_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_light_ctl_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_LIGHT_CTL_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_LIGHT_CTL_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_CTL_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                            rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_LIGHT_CTL_SRV_TemperatureServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                             rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_LIGHT_CTL_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_LIGHT_CTL_SRV_H
