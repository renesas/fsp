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

#ifndef RM_MESH_BEARER_PLATFORM_API_H
#define RM_MESH_BEARER_PLATFORM_API_H

/*******************************************************************************************************************//**
 * @ingroup  RENESAS_INTERFACES
 * @defgroup RM_MESH_BEARER_PLATFORM_API BLE Mesh Bearer Platform Interface
 * @brief    Interface for Bluetooth Low Energy Mesh Bearer Platform functions.
 *
 * @section RM_MESH_BEARER_PLATFORM_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Bearer Platform (BLE MESH BEARER PLATFORM) peripheral provides Bluetooth Low Energy Mesh Bearer Platform functionality.
 *
 * The Bluetooth Low Energy Mesh Bearer Platform interface can be implemented by:
 * - @ref RM_MESH_BEARER_PLATFORM
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

#include "rm_ble_mesh_bearer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Device address type*/
typedef enum e_rm_mesh_bearer_platform_device_address_type
{
    /** Public device address type */
    RM_MESH_BEARER_PLATFORM_DEVICE_ADDRESS_TYPE_PUBLIC,

    /** Random device address type */
    RM_MESH_BEARER_PLATFORM_DEVICE_ADDRESS_TYPE_RANDOM,
} rm_mesh_bearer_platform_device_address_type_t;

/** State*/
typedef enum e_rm_mesh_bearer_platform_state
{
    /** State enable */
    RM_MESH_BEARER_PLATFORM_STATE_ENABLE,

    /** state Disable */
    RM_MESH_BEARER_PLATFORM_STATE_DISABLE,
} rm_mesh_bearer_platform_state_t;

/** GATT mode */
typedef enum e_rm_mesh_bearer_platform_gatt_mode
{
    /** Provision GATT mode */
    RM_MESH_BEARER_PLATFORM_GATT_MODE_PROVISION,

    /** Proxy GATT mode */
    RM_MESH_BEARER_PLATFORM_GATT_MODE_PROXY,
} rm_mesh_bearer_platform_gatt_mode_t;

/** MESH BEARER PLATFORM control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_mesh_bearer_platform_instance_ctrl_t
 */
typedef void rm_mesh_bearer_platform_ctrl_t;

/** MESH BEARER PLATFORM configuration parameters. */
typedef struct st_rm_mesh_bearer_platform_cfg_t
{
    /** the parameters for initialization. */
    uint32_t channel;                                                  ///< Select a channel corresponding to the channel number of the hardware.
    rm_mesh_bearer_platform_device_address_type_t device_address_type; ///< Device address type.
    rm_ble_mesh_bearer_instance_t const         * p_bearer_instance;   ///< Instance structure of BLE Mesh Bearer.
    void const * p_context;                                            ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                             ///< Placeholder for user extension.
} rm_mesh_bearer_platform_cfg_t;

/** MESH BEARER PLATFORM functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_mesh_bearer_platform_api
{
    /** Open Bearer Platform middleware.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_mesh_bearer_platform_ctrl_t * const      p_ctrl,
                       rm_mesh_bearer_platform_cfg_t const * const p_cfg);

    /** Close Bearer Platform middleware.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl);

    /** Set scan response data in connectable and scannable undirected advertising event.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_SetScanResponseData()
     *
     * @param[in]   p_ctrl       Pointer to control structure.
     * @param[out]  p_data       Pointer to scan response data.
     * @param[in]   len          Data length.
     */
    fsp_err_t (* setScanResponseData)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint8_t * p_data, uint8_t len);

    /** Request to create connection.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_Connect()
     *
     * @param[in]  p_ctrl            Pointer to control structure.
     * @param[in]  p_remote_address  Pointer to remote device address.
     * @param[in]  address_type      Address type.
     * @param[in]  mode              GATT interface mode, either @ref RM_MESH_BEARER_PLATFORM_GATT_MODE_PROVISION or @ref RM_MESH_BEARER_PLATFORM_GATT_MODE_PROXY.
     */
    fsp_err_t (* connect)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint8_t * p_remote_address,
                          uint8_t address_type, rm_mesh_bearer_platform_gatt_mode_t mode);

    /** Start service discovery for Mesh GATT service.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_DiscoverService()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  handle  Connection handle to identify device.
     * @param[in]  mode    GATT interface mode, either RM_MESH_BEARER_PLATFORM_GATT_MODE_PROVISION or RM_MESH_BEARER_PLATFORM_GATT_MODE_PROXY.
     */
    fsp_err_t (* discoverService)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint16_t handle,
                                  rm_mesh_bearer_platform_gatt_mode_t mode);

    /** Configure GATT notification of Mesh GATT service.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_ConfigureNotification()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  handle  Connection handle to identify device.
     * @param[in]  state   Notification configuration flag; enable if RM_MESH_BEARER_PLATFORM_STATE_ENABLE, or disable if RM_MESH_BEARER_PLATFORM_STATE_DISABLE.
     * @param[in]  mode    GATT interface mode, either RM_MESH_BEARER_PLATFORM_GATT_MODE_PROVISION or RM_MESH_BEARER_PLATFORM_GATT_MODE_PROXY.
     */
    fsp_err_t (* configureNotification)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint16_t handle,
                                        rm_mesh_bearer_platform_state_t state,
                                        rm_mesh_bearer_platform_gatt_mode_t mode);

    /** Terminate Connection.
     * @par Implemented as
     * - @ref RM_MESH_BEARER_PLATFORM_Disconnect()
     *
     * @param[in]  p_ctrl  Pointer to control structure.
     * @param[in]  handle  Connection handle to identify device.
     */
    fsp_err_t (* disconnect)(rm_mesh_bearer_platform_ctrl_t * const p_ctrl, uint16_t handle);
} rm_mesh_bearer_platform_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_mesh_bearer_platform_instance
{
    rm_mesh_bearer_platform_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_mesh_bearer_platform_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_mesh_bearer_platform_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_mesh_bearer_platform_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_MESH_BEARER_PLATFORM_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_BEARER_PLATFORM_API_H
