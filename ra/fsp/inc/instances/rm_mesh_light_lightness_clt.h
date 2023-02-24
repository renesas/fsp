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

#ifndef RM_MESH_LIGHT_LIGHTNESS_CLT_H
#define RM_MESH_LIGHT_LIGHTNESS_CLT_H

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
 * Light Lightness Set message parameters.
 */
typedef struct st_rm_mesh_light_lightness_set_info
{
    /** The target value of the Light Lightness Actual state. */
    uint16_t lightness;

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
} rm_mesh_light_lightness_set_info_t;

/**
 * Light Lightness Status message parameters.
 */
typedef struct st_rm_mesh_light_lightness_status_info
{
    /** The present value of the Light Lightness Actual state. */
    uint16_t present_lightness;

    /** The target value of the Light Lightness Actual state. (Optional) */
    uint16_t target_lightness;

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

    /** Flag: To represent if optional fields Target Light Lightness Actual and Remaining Time are valid */
    uint8_t optional_fields_present;
} rm_mesh_light_lightness_status_info_t;

/**
 * Light Lightness Linear Set message parameters.
 */
typedef struct st_rm_mesh_light_lightness_linear_set_info
{
    /** The target value of the Light Lightness Linear state. */
    uint16_t lightness;

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
} rm_mesh_light_lightness_linear_set_info_t;

/**
 * Light Lightness Linear Status message parameters.
 */
typedef struct st_rm_mesh_light_lightness_linear_status_info
{
    /** The present value of the Light Lightness Linear state */
    uint16_t present_lightness;

    /** The target value of the Light Lightness Linear state (Optional) */
    uint16_t target_lightness;

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

    /** Flag: To represent if optional fields Target Light Lightness Linear and Remaining Time are valid */
    uint8_t optional_fields_present;
} rm_mesh_light_lightness_linear_status_info_t;

/**
 * Light Lightness Last Status message parameters.
 */
typedef struct st_rm_mesh_light_lightness_last_status_info
{
    /** The value of the Light Lightness Last */
    uint16_t lightness;
} rm_mesh_light_lightness_last_status_info_t;

/**
 * Light Lightness Default Set message parameters.
 */
typedef struct st_rm_mesh_light_lightness_default_set_info
{
    /** The value of the Light Lightness Default state */
    uint16_t lightness;
} rm_mesh_light_lightness_default_set_info_t;

/**
 * Light Lightness Range Set message parameters.
 */
typedef struct st_rm_mesh_light_lightness_range_set_info
{
    /** The value of the Lightness Range Min field of the Light Lightness Range state */
    uint16_t range_min;

    /** The value of the Lightness Range Max field of the Light Lightness Range state */
    uint16_t range_max;
} rm_mesh_light_lightness_range_set_info_t;

/**
 * Light Lightness Range Status message parameters.
 */
typedef struct st_rm_mesh_light_lightness_range_status_info
{
    /** Status Code for the requesting message. */
    uint8_t status_code;

    /** The value of the Lightness Range Min field of the Light Lightness Range state */
    uint16_t range_min;

    /** The value of the Lightness Range Max field of the Light Lightness Range state */
    uint16_t range_max;
} rm_mesh_light_lightness_range_status_info_t;

/**
 * Light Lightness Default Status message parameters.
 */
typedef struct st_rm_mesh_light_lightness_default_status_info
{
    /** The value of the Light Lightness Default state */
    uint16_t lightness;
} rm_mesh_light_lightness_default_status_info_t;

typedef struct st_rm_mesh_light_lightness_last_or_default_status_info
{
    uint16_t lightness;
} rm_mesh_light_lightness_last_or_default_status_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_LIGHT_LIGHTNESS_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh light lightness instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_LIGHT_LIGHTNESS_CLT_Open() is called. */
typedef struct st_rm_mesh_light_lightness_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_light_lightness_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_light_lightness_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                           rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                                     rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                     rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                      uint32_t                                req_opcode,
                                                      void const * const                      parameter,
                                                      uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_Get(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_Set(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_SetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                        void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_LinearGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_LinearSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_LinearSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                              void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_LastGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_DefaultGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_DefaultSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_DefaultSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                               void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_RangeGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_RangeSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                               void const * const                      p_parameter);
fsp_err_t RM_MESH_LIGHT_LIGHTNESS_CLT_RangeSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                             void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_LIGHT_LIGHTNESS_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_LIGHT_LIGHTNESS_CLT_H
