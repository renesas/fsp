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

#ifndef RM_BLE_MESH_MODEL_CLIENT_API_H
#define RM_BLE_MESH_MODEL_CLIENT_API_H

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
 * @defgroup  RM_BLE_MESH_MODEL_CLIENT_API BLE Mesh Model Client Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Model Client functions.
 *
 * @section   RM_BLE_MESH_MODEL_CLIENT_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Model Client (BLE MESH MODEL CLIENT) middleware provides Bluetooth Low Energy Mesh Model Client functionality.
 *
 * The Bluetooth Low Energy Mesh Model Client interface can be implemented by:
 * - @ref  RM_MESH_GENERIC_BATTERY_CLT
 * - @ref  RM_MESH_GENERIC_DTT_CLT
 * - @ref  RM_MESH_GENERIC_LEVEL_CLT
 * - @ref  RM_MESH_GENERIC_LOC_CLT
 * - @ref  RM_MESH_GENERIC_ON_OFF_CLT
 * - @ref  RM_MESH_GENERIC_PL_CLT
 * - @ref  RM_MESH_GENERIC_POO_CLT
 * - @ref  RM_MESH_GENERIC_PROP_CLT
 * - @ref  RM_MESH_HEALTH_CLT
 * - @ref  RM_MESH_LIGHT_CTL_CLT
 * - @ref  RM_MESH_LIGHT_HSL_CLT
 * - @ref  RM_MESH_LIGHT_LC_CLT
 * - @ref  RM_MESH_LIGHT_LIGHTNESS_CLT
 * - @ref  RM_MESH_LIGHT_XYL_CLT
 * - @ref  RM_MESH_SCENE_CLT
 * - @ref  RM_MESH_SCHEDULER_CLT
 * - @ref  RM_MESH_TIME_CLT
 * - @ref  RM_MESH_SENSOR_CLT
 *
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Mesh model client callback parameter definition */
typedef struct st_rm_ble_mesh_model_client_callback_args
{
    void const * p_context;                                     ///< Placeholder for user data.
    rm_ble_mesh_access_model_req_msg_context_t * p_msg_context; ///< Context of message received for a specific model instance.
    rm_ble_mesh_access_req_msg_raw_t           * p_msg_raw;     ///< Uninterpreted/raw received message for a specific model instance.
} rm_ble_mesh_model_client_callback_args_t;

/** BLE MESH MODEL CLIENT control block.  Allocate an instance specific control block to pass into the BLE mesh model health client API calls.
 * @par Implemented as
 * - rm_ble_mesh_health_client_instance_ctrl_t
 */
typedef void rm_ble_mesh_model_client_ctrl_t;

/** BLE mesh model health client configuration parameters. */
typedef struct st_rm_ble_mesh_model_client_cfg
{
    /** the parameters for initialization. */
    rm_ble_mesh_access_instance_t const * p_access_instance;                ///< Access Layer instance structure.

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_ble_mesh_model_client_callback_args_t * p_args); ///< Mesh model client callback.
    void const * p_context;                                                 ///< Placeholder for user data.
    void const * p_extend;                                                  ///< Placeholder for user extension.
} rm_ble_mesh_model_client_cfg_t;

/** Shared Interface definition for BLE MESH */
typedef struct st_rm_ble_mesh_model_client_api
{
    /** API to open client model.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_CLT_Open()
     * - @ref RM_MESH_GENERIC_DTT_CLT_Open()
     * - @ref RM_MESH_GENERIC_LEVEL_CLT_Open()
     * - @ref RM_MESH_GENERIC_LOC_CLT_Open()
     * - @ref RM_MESH_GENERIC_ON_OFF_CLT_Open()
     * - @ref RM_MESH_GENERIC_PL_CLT_Open()
     * - @ref RM_MESH_GENERIC_POO_CLT_Open()
     * - @ref RM_MESH_GENERIC_PROP_CLT_Open()
     * - @ref RM_MESH_LIGHT_CTL_CLT_Open()
     * - @ref RM_MESH_LIGHT_HSL_CLT_Open()
     * - @ref RM_MESH_LIGHT_LC_CLT_Open()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_CLT_Open()
     * - @ref RM_MESH_LIGHT_XYL_CLT_Open()
     * - @ref RM_MESH_SCENE_CLT_Open()
     * - @ref RM_MESH_SCHEDULER_CLT_Open()
     * - @ref RM_MESH_TIME_CLT_Open()
     * - @ref RM_MESH_SENSOR_CLT_Open()
     * - @ref RM_MESH_HEALTH_CLIENT_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_model_client_cfg_t const * const p_cfg);

    /** API to close client model.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_CLT_Close()
     * - @ref RM_MESH_GENERIC_DTT_CLT_Close()
     * - @ref RM_MESH_GENERIC_LEVEL_CLT_Close()
     * - @ref RM_MESH_GENERIC_LOC_CLT_Close()
     * - @ref RM_MESH_GENERIC_ON_OFF_CLT_Close()
     * - @ref RM_MESH_GENERIC_PL_CLT_Close()
     * - @ref RM_MESH_GENERIC_POO_CLT_Close()
     * - @ref RM_MESH_GENERIC_PROP_CLT_Close()
     * - @ref RM_MESH_LIGHT_CTL_CLT_Close()
     * - @ref RM_MESH_LIGHT_HSL_CLT_Close()
     * - @ref RM_MESH_LIGHT_LC_CLT_Close()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_CLT_Close()
     * - @ref RM_MESH_LIGHT_XYL_CLT_Close()
     * - @ref RM_MESH_SCENE_CLT_Close()
     * - @ref RM_MESH_SCHEDULER_CLT_Close()
     * - @ref RM_MESH_TIME_CLT_Close()
     * - @ref RM_MESH_SENSOR_CLT_Close()
     * - @ref RM_MESH_HEALTH_CLIENT_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);

    /** DEPRECATED - API to set Model client model handle.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_DTT_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_LEVEL_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_LOC_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_ON_OFF_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_PL_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_POO_CLT_SetModelHandle()
     * - @ref RM_MESH_GENERIC_PROP_CLT_SetModelHandle()
     * - @ref RM_MESH_LIGHT_CTL_CLT_SetModelHandle()
     * - @ref RM_MESH_LIGHT_HSL_CLT_SetModelHandle()
     * - @ref RM_MESH_LIGHT_LC_CLT_SetModelHandle()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_CLT_SetModelHandle()
     * - @ref RM_MESH_LIGHT_XYL_CLT_SetModelHandle()
     * - @ref RM_MESH_SCENE_CLT_SetModelHandle()
     * - @ref RM_MESH_SCHEDULER_CLT_SetModelHandle()
     * - @ref RM_MESH_TIME_CLT_SetModelHandle()
     * - @ref RM_MESH_SENSOR_CLT_SetModelHandle()
     * - @ref RM_MESH_HEALTH_CLIENT_SetModelHandle()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  model_handle  Model handle to be assigned.
     */
    fsp_err_t (* setModelHandle)(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                 rm_ble_mesh_access_model_handle_t       model_handle);

    /** API to get Model client model handle.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_DTT_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_LEVEL_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_LOC_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_ON_OFF_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_PL_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_POO_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_PROP_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_CTL_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_HSL_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_LC_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_XYL_CLT_GetModelHandle()
     * - @ref RM_MESH_SCENE_CLT_GetModelHandle()
     * - @ref RM_MESH_SCHEDULER_CLT_GetModelHandle()
     * - @ref RM_MESH_TIME_CLT_GetModelHandle()
     * - @ref RM_MESH_SENSOR_CLT_GetModelHandle()
     * - @ref RM_MESH_HEALTH_CLIENT_GetModelHandle()
     *
     * @param[in]   p_ctrl          Pointer to control structure.
     * @param[out]  p_model_handle  Pointer to model handle to be filled/returned.
     */
    fsp_err_t (* getModelHandle)(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                 rm_ble_mesh_access_model_handle_t * const p_model_handle);

    /** API to send acknowledged commands.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_DTT_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_LEVEL_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_LOC_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_ON_OFF_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_PL_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_POO_CLT_GetModelHandle()
     * - @ref RM_MESH_GENERIC_PROP_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_CTL_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_HSL_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_LC_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_CLT_GetModelHandle()
     * - @ref RM_MESH_LIGHT_XYL_CLT_GetModelHandle()
     * - @ref RM_MESH_SCENE_CLT_GetModelHandle()
     * - @ref RM_MESH_SCHEDULER_CLT_GetModelHandle()
     * - @ref RM_MESH_TIME_CLT_GetModelHandle()
     * - @ref RM_MESH_SENSOR_CLT_GetModelHandle()
     * - @ref RM_MESH_HEALTH_CLIENT_GetModelHandle()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  req_opcode   Request Opcode.
     * @param[in]  p_parameter  Pointer to Parameter associated with Request Opcode.
     * @param[in]  rsp_opcode   Response Opcode.
     */
    fsp_err_t (* sendReliablePdu)(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, uint32_t req_opcode,
                                  void const * const p_parameter, uint32_t rsp_opcode);
} rm_ble_mesh_model_client_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_model_client_instance
{
    rm_ble_mesh_model_client_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_ble_mesh_model_client_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_ble_mesh_model_client_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_ble_mesh_model_client_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_MODEL_CLIENT_API_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_MODEL_CLIENT_API)
 **********************************************************************************************************************/
