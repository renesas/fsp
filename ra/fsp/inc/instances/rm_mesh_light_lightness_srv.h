/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef RM_MESH_LIGHT_LIGHTNESS_SRV_H
#define RM_MESH_LIGHT_LIGHTNESS_SRV_H

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
 * @addtogroup RM_MESH_LIGHT_LIGHTNESS_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Light Lightness Linear state represents the lightness of a light on a linear
 * scale
 */
typedef struct st_rm_mesh_light_lightness_srv_linear_info
{
    /** Light Lightness Linear */
    uint16_t lightness_linear;

    /** Light Lightness Target - Used in response path. */
    uint16_t lightness_target;

    /** TID - Used in request path */
    uint8_t tid;

    /**
     * Transition Time - Used in request path.
     * Used as remaining time in response path.
     */
    uint8_t transition_time;

    /** Delay - Used in request path */
    uint8_t delay;
} rm_mesh_light_lightness_srv_linear_info_t;

/**
 * Light Lightness Actual state represents the lightness of a light on a
 * perceptually uniform lightness scale
 */
typedef struct st_rm_mesh_light_lightness_srv_actual_info
{
    /** Light Lightness Actual */
    uint16_t lightness_actual;

    /** Light Lightness Target - Used in response path. */
    uint16_t lightness_target;

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
} rm_mesh_light_lightness_srv_actual_info_t;

/**
 * Light Lightness Last state represents the lightness of a light on a
 * perceptually uniform lightness scale
 */
typedef struct st_rm_mesh_light_lightness_srv_last_info
{
    /** Light Lightness Last */
    uint16_t lightness_last;
} rm_mesh_light_lightness_srv_last_info_t;

/**
 * Light Lightness Default state is a value ranging from 0x0000 to 0xFFFF,
 * representing a default lightness level for the Light Lightness Actual state
 */
typedef struct st_rm_mesh_light_lightness_srv_default_info
{
    /** Light Lightness Default */
    uint16_t lightness_default;
} rm_mesh_light_lightness_srv_default_info_t;

/**
 * Light Lightness Range state determines the minimum and maximum lightness of
 * an element
 */
typedef struct st_rm_mesh_light_lightness_srv_range_info
{
    /** Light Lightness Range Min */
    uint16_t lightness_range_min;

    /** Light Lightness Range Max */
    uint16_t lightness_range_max;
} rm_mesh_light_lightness_srv_range_info_t;

/**
 * Light Lightness state is a composite state that includes the Light Lightness
 * Linear, the Light Lightness Actual, the Light Lightness Last, and the Light
 * Lightness Default states
 */
typedef struct st_rm_mesh_light_lightness_srv_info
{
    /**
     * Light Lightness Linear state represents the lightness of a light on a linear
     * scale
     */
    rm_mesh_light_lightness_srv_linear_info_t light_lightness_linear;

    /**
     * Light Lightness Actual state represents the lightness of a light on a
     * perceptually uniform lightness scale
     */
    rm_mesh_light_lightness_srv_actual_info_t light_lightness_actual;

    /**
     * Light Lightness Last state represents the lightness of a light on a
     * perceptually uniform lightness scale
     */
    rm_mesh_light_lightness_srv_last_info_t light_lightness_last;

    /**
     * Light Lightness Default state is a value ranging from 0x0000 to 0xFFFF,
     * representing a default lightness level for the Light Lightness Actual state
     */
    rm_mesh_light_lightness_srv_default_info_t light_lightness_default;

    /**
     * Light Lightness Range state.
     */
    rm_mesh_light_lightness_srv_range_info_t light_lightness_range;

    /** Status field used only for the Range Status */
    uint8_t range_status;
} rm_mesh_light_lightness_srv_info_t;

/** BLE mesh light lightness instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_LIGHT_LIGHTNESS_SRV_Open() is called. */
typedef struct st_rm_mesh_light_lightness_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_light_lightness_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_light_lightness_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                           rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                  rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_SRV_SetupServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                             rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_LIGHT_LIGHTNESS_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_LIGHT_LIGHTNESS_SRV_H
