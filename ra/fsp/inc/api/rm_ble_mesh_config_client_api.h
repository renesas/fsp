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

#ifndef RM_BLE_MESH_CONFIG_CLIENT_API_H
#define RM_BLE_MESH_CONFIG_CLIENT_API_H

/*******************************************************************************************************************//**
 * @ingroup   RENESAS_INTERFACES
 * @defgroup  RM_BLE_MESH_CONFIG_CLIENT_API BLE Mesh Model Configuration Client Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Model Configuration Client functions.
 *
 * @section   RM_BLE_MESH_CONFIG_CLIENT_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Model Configuration Client (BLE MESH MODEL CONFIG CLIENT) middleware provides Bluetooth Low Energy Mesh Model Configuration Client functionality.
 *
 * The Bluetooth Low Energy Mesh Model Configuration Client interface can be implemented by:
 * - @ref RM_MESH_CONFIG_CLT
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_ble_mesh_access_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Mesh model client callback parameter definition */
typedef struct st_rm_ble_mesh_config_client_callback_args
{
    void const * p_context;
    rm_ble_mesh_access_model_req_msg_context_t * p_msg_context; ///< Context of message received for a specific model instance.
    rm_ble_mesh_access_req_msg_raw_t           * p_msg_raw;     ///< Uninterpreted/raw received message for a specific model instance.
} rm_ble_mesh_config_client_callback_args_t;

/** BLE MESH CONFIG CLIENT control block.  Allocate an instance specific control block to pass into the BLE mesh model health client API calls.
 * @par Implemented as
 * - rm_ble_mesh_health_client_instance_ctrl_t
 */
typedef void rm_ble_mesh_config_client_ctrl_t;

/** BLE mesh model health client configuration parameters. */
typedef struct st_rm_ble_mesh_config_client_cfg
{
    /** the parameters for initialization. */
    rm_ble_mesh_access_instance_t const * p_access_instance;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_ble_mesh_config_client_callback_args_t * p_args); ///< Callback function.
    void const * p_context;                                                  ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                                   ///< Placeholder for user extension.
} rm_ble_mesh_config_client_cfg_t;

/** Shared Interface definition for BLE MESH */
typedef struct st_rm_ble_mesh_config_client_api
{
    /** API to open configuration client model.
     * @par Implemented as
     * - @ref RM_MESH_CONFIG_CLT_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_config_client_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_config_client_cfg_t const * const p_cfg);

    /** API to close configuration client model.
     * @par Implemented as
     * - @ref RM_MESH_CONFIG_CLT_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_config_client_ctrl_t * const p_ctrl);

    /** API to set configuration server.
     * @par Implemented as
     * - @ref RM_MESH_CONFIG_CLT_SetServer()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  server_addr  Address of Configuration Server.
     * @param[in]  p_dev_key    Pointer to device Key of Configuration Server.
     */
    fsp_err_t (* setServer)(rm_ble_mesh_config_client_ctrl_t * const p_ctrl, rm_ble_mesh_network_address_t server_addr,
                            uint8_t * p_dev_key);

    /** API to send acknowledged commands.
     * @par Implemented as
     * - @ref RM_MESH_CONFIG_CLT_SendReliablePdu()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  req_opcode   Request Opcode.
     * @param[in]  p_parameter  Pointer to parameter associated with Request Opcode.
     * @param[in]  rsp_opcode   Response Opcode.
     */
    fsp_err_t (* sendReliablePdu)(rm_ble_mesh_config_client_ctrl_t * const p_ctrl,      ///< Pointer to control structure.
                                  uint32_t                                 req_opcode,  ///< Request opcode.
                                  void const * const                       p_parameter, ///< parameter associated with Request Opcode.
                                  uint32_t                                 rsp_opcode   ///< Response opcode.
                                  );
} rm_ble_mesh_config_client_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_config_client_instance
{
    rm_ble_mesh_config_client_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_config_client_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_config_client_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_config_client_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_CONFIG_CLIENT_API_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_CONFIG_CLIENT_API)
 **********************************************************************************************************************/
