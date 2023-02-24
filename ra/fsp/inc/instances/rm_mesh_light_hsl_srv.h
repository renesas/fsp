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

#ifndef RM_MESH_LIGHT_HSL_SRV_H
#define RM_MESH_LIGHT_HSL_SRV_H

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
 * @addtogroup RM_MESH_LIGHT_HSL_SRV
 * @{
 **********************************************************************************************************************/

/**
 * Light HSL state is a composite state that includes the Light HSL Lighness,
 * the Light HSL Hue and the Light HSL Saturation states
 */
typedef struct st_rm_mesh_light_hsl_srv_info
{
    /** The perceived lightness of a light emitted by the element */
    uint16_t hsl_lightness;

    /** Target Perceived lightness - used in the response path */
    uint16_t target_hsl_lightness;

    /** The 16-bit value representing the hue */
    uint16_t hsl_hue;

    /** Target hue - used in the response path */
    uint16_t target_hsl_hue;

    /** The saturation of a color light */
    uint16_t hsl_saturation;

    /** Target saturation - used in the response path */
    uint16_t target_hsl_saturation;

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
} rm_mesh_light_hsl_srv_info_t;

/**
 * Light HSL Target state is a composite state that includes the Light HSL
 * Lighness, the Light HSL Hue and the Light HSL Saturation states
 */
typedef struct st_rm_mesh_light_hsl_srv_target_info
{
    /** The perceived lightness of a light emitted by the element */
    uint16_t hsl_lightness;

    /** The 16-bit value representing the hue */
    uint16_t hsl_hue;

    /** The saturation of a color light */
    uint16_t hsl_saturation;
} rm_mesh_light_hsl_srv_target_info_t;

/**
 * Light HSL Default state is a composite state that includes the Light HSL
 * Lighness, the Light HSL Hue and the Light HSL Saturation states
 */
typedef struct st_rm_mesh_light_hsl_srv_default_info
{
    /** The perceived lightness of a light emitted by the element */
    uint16_t hsl_lightness;

    /** The 16-bit value representing the hue */
    uint16_t hsl_hue;

    /** The saturation of a color light */
    uint16_t hsl_saturation;
} rm_mesh_light_hsl_srv_default_info_t;

/** Light HSL Hue */
typedef struct st_rm_mesh_light_hsl_srv_hue_info
{
    /** The 16-bit value representing the hue */
    uint16_t hsl_hue;
} rm_mesh_light_hsl_srv_hue_info_t;

/** Light HSL Saturation */
typedef struct st_rm_mesh_light_hsl_srv_saturation_info
{
    /** The saturation of a color light */
    uint16_t hsl_saturation;
} rm_mesh_light_hsl_srv_saturation_info_t;

/**
 * Light HSL Range state is a composite state that includes Minimum and Maximum
 * of the Light HSL Hue and the Light HSL Saturation states
 */
typedef struct st_rm_mesh_light_hsl_srv_range_info
{
    /** The value of the Hue Range Min field of the Light HSL Hue Range state */
    uint16_t hue_range_min;

    /** The value of the Hue Range Max field of the Light HSL Hue Range state */
    uint16_t hue_range_max;

    /**
     * The value of the Saturation Range Min field of the Light HSL Saturation Range
     * state
     */
    uint16_t saturation_range_min;

    /**
     * The value of the Saturation Range Max field of the Light HSL Saturation Range
     * state
     */
    uint16_t saturation_range_max;

    /** Status - Used only in response path */
    uint8_t status;
} rm_mesh_light_hsl_srv_range_info_t;

/** BLE mesh light hsl extension for BLE mesh light hsl. */
typedef struct st_rm_mesh_light_hsl_srv_extended_cfg
{
    rm_ble_mesh_access_instance_t const * p_hue_access_instance;        ///< Pointer to access instance for hue model.
    rm_ble_mesh_access_instance_t const * p_saturation_access_instance; ///< Pointer to access instance for saturation model.
} rm_mesh_light_hsl_srv_extended_cfg_t;

/** BLE mesh light hsl instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_LIGHT_HSL_SRV_Open() is called. */
typedef struct st_rm_mesh_light_hsl_srv_instance_ctrl
{
    uint32_t open;                     // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;
    rm_ble_mesh_access_model_handle_t hue_model_handle;
    rm_ble_mesh_access_model_handle_t saturation_model_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_light_hsl_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_light_hsl_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_LIGHT_HSL_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_LIGHT_HSL_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_HSL_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                            rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_LIGHT_HSL_SRV_HueServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                     rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_LIGHT_HSL_SRV_SaturationServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                            rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_LIGHT_HSL_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_LIGHT_HSL_SRV_H
