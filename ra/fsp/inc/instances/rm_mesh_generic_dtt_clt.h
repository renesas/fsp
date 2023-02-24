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

#ifndef RM_MESH_GENERIC_DTT_CLT_H
#define RM_MESH_GENERIC_DTT_CLT_H

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
 *  The Generic Default Transition Time state determines how long an element shall take to transition
 *  from a present state to a new state.
 *  This is a 1-octet value that consists of two fields:
 *  - a 2-bit bit field representing the step resolution
 *  - a 6-bit bit field representing the number of transition steps.
 *
 *  This mechanism covers a wide range of times that may be required by different applications:
 *  - For 100 millisecond step resolution, the range is 0 through 6.2 seconds.
 *  - For 1 second step resolution, the range is 0 through 62 seconds.
 *  - For 10 seconds step resolution, the range is 0 through 620 seconds (10.5 minutes).
 *  -  For 10 minutes step resolution, the range is 0 through 620 minutes (10.5 hours).
 *
 *  The Generic Default Transition Time is calculated using the following formula:
 *  Generic Default Transition Time = Default Transition Step Resolution * Default Transition Number of Steps
 */
typedef struct st_rm_mesh_generic_dtt_clt_default_transition_time_info
{
    /**
     * The Default Transition Step Resolution field is a 2-bit bit field that determines
     * the resolution of the Generic Default Transition Time state.
     *
     * Value | Description
     * ------|------------
     * 0b00  | The Default Transition Step Resolution is 100 milliseconds
     * 0b01  | The Default Transition Step Resolution is 1 second
     * 0b10  | The Default Transition Step Resolution is 10 seconds
     * 0b11  | The Default Transition Step Resolution is 10 minutes
     */
    uint8_t transition_number_of_steps;

    /**
     * The Default Transition Number of Steps field is a 6-bit value representing
     * the number of transition steps.
     *
     * Value     | Description
     * ----------|------------
     * 0x00      | The Generic Default Transition Time is immediate.
     * 0x01-0x3E | The number of steps.
     * 0x3F      | The value is unknown. The state cannot be set to this value,
     *           | but an element may report an unknown value if a transition is higher than 0x3E
     *           | or not determined.
     */
    uint8_t transition_step_resolution;
} rm_mesh_generic_dtt_clt_default_transition_time_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_GENERIC_DTT_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh generic dtt instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_DTT_CLT_Open() is called. */
typedef struct st_rm_mesh_generic_dtt_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_generic_dtt_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_generic_dtt_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_DTT_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                       rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_DTT_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_DTT_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_GENERIC_DTT_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_GENERIC_DTT_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                  uint32_t                                req_opcode,
                                                  void const * const                      parameter,
                                                  uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_GENERIC_DTT_CLT_Get(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_DTT_CLT_Set(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_GENERIC_DTT_CLT_SetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                    void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_DTT_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_DTT_CLT_H
