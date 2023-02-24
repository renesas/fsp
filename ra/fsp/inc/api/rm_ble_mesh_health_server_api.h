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

#ifndef RM_BLE_MESH_HEALTH_SERVER_API_H
#define RM_BLE_MESH_HEALTH_SERVER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_ble_mesh_access_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_HEALTH_SERVER_API BLE Mesh Health Server Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Model Health Server functions.
 *
 * @section   RM_BLE_MESH_HEALTH_SERVER_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Model Health Server (BLE MESH HEALTH SERVER) middleware provides Bluetooth Low Energy Mesh Model Health Server functionality.
 *
 * The Bluetooth Low Energy Mesh Model Health Server interface can be implemented by:
 * - @ref RM_MESH_HEALTH_SRV
 *
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** This section lists the Application Events defined for Health Server Model */

typedef enum e_rm_ble_mesh_health_server_events
{
    /** Attention Start */
    RM_BLE_MESH_HEALTH_SERVER_SERVER_ATTENTION_START = 0x01,

    /** Attention Restart */
    RM_BLE_MESH_HEALTH_SERVER_SERVER_ATTENTION_RESTART = 0x02,

    /** Attention Stop */
    RM_BLE_MESH_HEALTH_SERVER_SERVER_ATTENTION_STOP = 0x03,
} rm_ble_mesh_health_server_events_t;

/** Mesh model health server callback parameter definition */
typedef struct st_rm_ble_mesh_model_health_callback_args
{
    void const * p_context;
    rm_ble_mesh_access_model_handle_t * p_handle;   ///< Access model handle.
    rm_ble_mesh_health_server_events_t  event_type; ///< Application events defined for Health Server Model.
    uint8_t * p_event_data;                         ///< Event data.
    uint16_t  event_data_length;                    ///< Event data length.
} rm_ble_mesh_model_health_callback_args_t;

/**
 * Health Server Self Test Function.
 */

typedef void (* rm_ble_mesh_health_server_self_test_function)(uint8_t test_id, uint16_t company_id);

/**
 * Health Server Self Test Function Structure.
 */
typedef struct st_rm_ble_mesh_health_server_self_test
{
    /** Test ID */
    uint8_t test_id;

    /** Self Test Function */
    rm_ble_mesh_health_server_self_test_function self_test_fn;
} rm_ble_mesh_health_server_self_test_t;

/** BLE MESH HEALTH SERVER control block.  Allocate an instance specific control block to pass into the BLE mesh model health server API calls.
 * @par Implemented as
 * - rm_ble_mesh_health_server_instance_ctrl_t
 */
typedef void rm_ble_mesh_health_server_ctrl_t;

/** BLE mesh model health server configuration parameters. */
typedef struct st_rm_ble_mesh_health_server_cfg
{
    /** the parameters for initialization. */
    rm_ble_mesh_access_instance_t const   * p_access_instance; ///< Access Layer instance structure.
    rm_ble_mesh_health_server_self_test_t * p_self_tests;      ///< Health Server self test function structure.
    uint16_t company_id;                                       ///< Company ID.
    uint32_t num_self_tests;                                   ///< Number of self test.

    void (* p_callback)(rm_ble_mesh_model_health_callback_args_t * p_args);
    void const * p_context;                                    ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                     ///< Placeholder for user extension.
} rm_ble_mesh_health_server_cfg_t;

/** Shared Interface definition for BLE MESH */
typedef struct st_rm_ble_mesh_health_server_api
{
    /** API to open health server model.
     * @par Implemented as
     * - @ref RM_MESH_HEALTH_SERVER_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_health_server_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_health_server_cfg_t const * const p_cfg);

    /** API to close health server model.
     * @par Implemented as
     * - @ref RM_MESH_HEALTH_SERVER_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_health_server_ctrl_t * const p_ctrl);

    /** API to report self-test fault.
     * @par Implemented as
     * - @ref RM_MESH_HEALTH_SERVER_ReportFault()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  p_model_handle  Pointer to model handle identifying the health server model instance.
     * @param[in]  test_id         Identifier of the self-test.
     * @param[in]  company_id      Company identifier.
     * @param[in]  fault_code      Fault value indicating the error.
     */
    fsp_err_t (* reportFault)(rm_ble_mesh_health_server_ctrl_t * const p_ctrl,
                              const rm_ble_mesh_access_model_handle_t * const p_model_handle, uint8_t test_id,
                              uint16_t company_id,
                              uint8_t fault_code);

    /** API to publish current status.
     * @par Implemented as
     * - @ref RM_MESH_HEALTH_SERVER_PublishCurrentStatus()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  p_status        Pointer to current status.
     * @param[in]  length          Status data length.
     */
    fsp_err_t (* publishCurrentStatus)(rm_ble_mesh_health_server_ctrl_t * const p_ctrl, uint8_t * p_status,
                                       uint16_t length);
} rm_ble_mesh_health_server_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_health_server_instance
{
    rm_ble_mesh_health_server_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_health_server_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_health_server_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_health_server_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_HEALTH_SERVER_API_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_HEALTH_SERVER_API)
 **********************************************************************************************************************/
