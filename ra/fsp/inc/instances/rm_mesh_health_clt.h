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

#ifndef RM_MESH_HEALTH_CLIENT_H
#define RM_MESH_HEALTH_CLIENT_H

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
 * Health Status message parameters
 */
typedef struct st_rm_mesh_health_clt_status_info
{
    /** Identifier of a performed test */
    uint8_t test_id;

    /** 16-bit Bluetooth assigned Company Identifier */
    uint16_t company_id;

    /** The FaultArray field contains a sequence of 1-octet fault values */
    uint8_t * fault_array;

    /** Number of fault values in the FaultArray */
    uint16_t fault_array_length;
} rm_mesh_health_clt_status_info_t;

/**
 * Health Fault Get clear message parameters
 */
typedef struct st_rm_mesh_health_clt_fault_get_clear_info
{
    /** 16-bit Bluetooth assigned Company Identifier */
    uint16_t company_id;
} rm_mesh_health_clt_fault_get_clear_info_t;

/**
 * Health Fault Test message parameters
 */
typedef struct st_rm_mesh_health_clt_fault_test_info
{
    /** Identifier of a performed test */
    uint8_t test_id;

    /** 16-bit Bluetooth assigned Company Identifier */
    uint16_t company_id;
} rm_mesh_health_clt_fault_test_info_t;

/**
 * Health Period message parameters
 */
typedef struct st_rm_mesh_health_clt_period_info
{
    /**
     * Divider for the Publish Period.
     * Modified Publish Period is used for sending Current Health Status messages
     * when there are active faults to communicate.
     */
    uint8_t fast_period_divisor;
} rm_mesh_health_clt_period_info_t;

/**
 * Health Attention message parameters
 */
typedef struct st_rm_mesh_health_clt_attention_info
{
    /** Value of the Attention Timer state */
    uint8_t attention;
} rm_mesh_health_clt_attention_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_HEALTH_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh health client instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_HEALTH_CLIENT_Open() is called. */
typedef struct st_rm_mesh_health_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_health_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_health_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_HEALTH_CLIENT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_HEALTH_CLIENT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);

fsp_err_t RM_MESH_HEALTH_CLIENT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                               rm_ble_mesh_access_model_handle_t * const p_model_handle);

fsp_err_t RM_MESH_HEALTH_CLIENT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                               rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_HEALTH_CLIENT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                uint32_t                                req_opcode,
                                                void const * const                      parameter,
                                                uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_HEALTH_CLIENT_FaultGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                         void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_FaultClearUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                         void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_FaultClear(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                           void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_FaultTest(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_FaultTestUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                        void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_PeriodGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_HEALTH_CLIENT_PeriodSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                        void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_PeriodSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_AttentionGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_HEALTH_CLIENT_AttentionSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                             void const * const                      p_parameter);
fsp_err_t RM_MESH_HEALTH_CLIENT_AttentionSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                           void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_HEALTH_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_HEALTH_CLIENT_H
