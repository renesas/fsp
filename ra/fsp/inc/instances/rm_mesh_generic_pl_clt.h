/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_MESH_GENERIC_PL_CLT_H
#define RM_MESH_GENERIC_PL_CLT_H

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
 * Generic Power Level Set message parameters.
 */
typedef struct st_rm_mesh_generic_pl_set_info
{
    /** The target value of the Generic Power Actual state */
    uint16_t power;

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
} rm_mesh_generic_pl_set_info_t;

/**
 * Generic Power Level Status message parameters.
 */
typedef struct st_rm_mesh_generic_pl_status_info
{
    /** The present value of the Generic Power Actual state. */
    uint16_t present_power;

    /** The target value of the Generic Power Actual state. */
    uint16_t target_power;

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

    /** Flag: To represent if optional fields Target Power and Remaining Time are valid */
    uint8_t optional_fields_present;
} rm_mesh_generic_pl_status_info_t;

/**
 * Generic Power Last Status message parameters.
 */
typedef struct st_rm_mesh_generic_pl_last_status_info
{
    /** The value of the Generic Power Last state. */
    uint16_t power;
} rm_mesh_generic_pl_last_status_info_t;

/**
 * Generic Power Default Status message parameters.
 */
typedef struct st_rm_mesh_generic_pl_default_status_info
{
    /** The value of the Generic Power Default state. */
    uint16_t power;
} rm_mesh_generic_pl_default_status_info_t;

/**
 * Generic Power Range Status message parameters.
 */
typedef struct st_rm_mesh_generic_pl_range_status_info
{
    /** Status Code for the requesting message. */
    uint8_t status;

    /** The value of the Generic Power Range Min field of the Generic Power Range state. */
    uint16_t range_min;

    /** The value of the Generic Power Range Max field of the Generic Power Range state. */
    uint16_t range_max;
} rm_mesh_generic_pl_range_status_info_t;

/**
 * Generic Power Default Status message parameters.
 */
typedef struct st_rm_mesh_generic_pl_default_set_info
{
    /** The value of the Generic Power Default state. */
    uint16_t power;
} rm_mesh_generic_pl_default_set_info_t;

/**
 * Generic Power Range Set message parameters.
 */
typedef struct st_rm_mesh_generic_pl_range_set_info
{
    /** The value of the Generic Power Min field of the Generic Power Range state. */
    uint16_t range_min;

    /** The value of the Generic Power Range Max field of the Generic Power Range state. */
    uint16_t range_max;
} rm_mesh_generic_pl_range_set_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_GENERIC_PL_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh generic pl instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_PL_CLT_Open() is called. */
typedef struct st_rm_mesh_generic_pl_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_generic_pl_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_generic_pl_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_PL_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                      rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_PL_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                                rm_ble_mesh_access_model_handle_t * const model_handle);
fsp_err_t RM_MESH_GENERIC_PL_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 uint32_t                                req_opcode,
                                                 void const * const                      parameter,
                                                 uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_GENERIC_PL_CLT_LevelGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_CLT_LevelSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PL_CLT_LevelSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                        void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PL_CLT_LastGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_CLT_DefaultGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_CLT_DefaultSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                            void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PL_CLT_DefaultSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PL_CLT_RangeGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PL_CLT_RangeSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PL_CLT_RangeSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                        void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_PL_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_PL_CLT_H
