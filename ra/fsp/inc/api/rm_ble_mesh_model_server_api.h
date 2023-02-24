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

#ifndef RM_BLE_MESH_MODEL_SERVER_API_H
#define RM_BLE_MESH_MODEL_SERVER_API_H

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
 * @defgroup  RM_BLE_MESH_MODEL_SERVER_API BLE Mesh Model Server Interface
 * @brief     Interface for Bluetooth Low Energy Mesh Model Server functions.
 *
 * @section   RM_BLE_MESH_MODEL_SERVER_API_Summary Summary
 * The BLE Mesh interface for the Bluetooth Low Energy Mesh Model Server (BLE MESH MODEL SERVER) middleware provides Bluetooth Low Energy Mesh Model Server functionality.
 *
 * The Bluetooth Low Energy Mesh Model Server interface can be implemented by:
 * - @ref RM_MESH_CONFIG_SRV
 * - @ref RM_MESH_GENERIC_BATTERY_SRV
 * - @ref RM_MESH_GENERIC_DTT_SRV
 * - @ref RM_MESH_GENERIC_LEVEL_SRV
 * - @ref RM_MESH_GENERIC_LOC_SRV
 * - @ref RM_MESH_GENERIC_ON_OFF_SRV
 * - @ref RM_MESH_GENERIC_PL_SRV
 * - @ref RM_MESH_GENERIC_POO_SRV
 * - @ref RM_MESH_GENERIC_ADMIN_PROP_SRV
 * - @ref RM_MESH_GENERIC_MFR_PROP_SRV
 * - @ref RM_MESH_GENERIC_USER_PROP_SRV
 * - @ref RM_MESH_GENERIC_CLIENT_PROP_SRV
 * - @ref RM_MESH_LIGHT_CTL_SRV
 * - @ref RM_MESH_LIGHT_HSL_SRV
 * - @ref RM_MESH_LIGHT_LC_SRV
 * - @ref RM_MESH_LIGHT_LIGHTNESS_SRV
 * - @ref RM_MESH_LIGHT_XYL_SRV
 * - @ref RM_MESH_SCHEDULER_SRV
 * - @ref RM_MESH_TIME_SRV
 * - @ref RM_MESH_SENSOR_SRV
 *
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

typedef enum e_rm_ble_mesh_model_server_generic_server_property
{
    /** Generic Manufacturer Properties */
    RM_BLE_MESH_MODEL_SERVER_GENERIC_SERVER_PROPERTY_MANUFACTURER = 0x00,

    /** Generic Admin Properties */
    RM_BLE_MESH_MODEL_SERVER_GENERIC_SERVER_PROPERTY_ADMIN = 0x01,

    /** Generic User Properties */
    RM_BLE_MESH_MODEL_SERVER_GENERIC_SERVER_PROPERTY_USER = 0x02,
} rm_ble_mesh_model_server_generic_server_property_t;

/** User Access field values */
typedef enum e_rm_ble_mesh_model_server_user_access
{
    /** User Access - Prohibited */
    RM_BLE_MESH_MODEL_SERVER_USER_ACCESS_PROHIBITED = 0x00,

    /** User Access - the device property can be read */
    RM_BLE_MESH_MODEL_SERVER_USER_ACCESS_READ = 0x01,

    /** User Access - the device property can be written */
    RM_BLE_MESH_MODEL_SERVER_USER_ACCESS_WRITE = 0x02,

    /** User Access - the device property can be read and written */
    RM_BLE_MESH_MODEL_SERVER_USER_ACCESS_READ_WRITE = 0x03,

    /** User Access - the invalid device property id */
    RM_BLE_MESH_MODEL_SERVER_USER_ACCESS_INVALID_PROPERTY_ID = 0xFF,
} rm_ble_mesh_model_server_user_access_t;

typedef enum e_rm_ble_mesh_model_server_device_property
{
    /** Device Property - Light Control Time Occupancy Delay */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_OCCUPANCY_DELAY = 0x003A,

    /** Device Property -  Light Control Time Fade On */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_FADE_ON = 0x0037,

    /** Device Property - Light Control Time Run On */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_RUN_ON = 0x003C,

    /** Device Property - Light Control Time Fade */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_FADE = 0x0036,

    /** Device Property - Light Control Time Prolong */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_PROLONG = 0x003B,

    /** Device Property - Light Control Time Fade Standby Auto */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_FADE_STANDBY_AUTO = 0x0038,

    /** Device Property - Light Control Time Fade Standby Manual */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_TIME_FADE_STANDBY_MANUAL = 0x0039,

    /** Device Property - Light Control Lightness On */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_LIGHTNESS_ON = 0x002E,

    /** Device Property - Light Control Lightness Prolong */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_LIGHTNESS_PROLONG = 0x002F,

    /** Device Property - Light Control Lightness Standby */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_LIGHTNESS_STANDBY = 0x0030,

    /** Device Property - Light Control Ambient LuxLevel On */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_AMBIENT_LUXLEVEL_ON = 0x002B,

    /** Device Property - Light Control Ambient LuxLevel Prolong */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_AMBIENT_LUXLEVEL_PROLONG = 0x002C,

    /** Device Property - Light Control Ambient LuxLevel Standby */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_AMBIENT_LUXLEVEL_STANDBY = 0x002D,

    /** Device Property - Light Control Regulator Kiu */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_REGULATOR_KIU = 0x0033,

    /** Device Property - Light Control Regulator Kid */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_REGULATOR_KID = 0x0032,

    /** Device Property - Light Control Regulator Kpu */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_REGULATOR_KPU = 0x0035,

    /** Device Property - Light Control Regulator Kpd */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_REGULATOR_KPD = 0x0034,

    /** Device Property - Light Control Regulator Accuracy */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_LIGHT_CONTROL_REGULATOR_ACCURACY = 0x0031,

    /** Device Property - Motion Sensed */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_MOTION_SENSED = 0x0042,

    /** Device Property - Time Since Motion Sensed */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_TIME_SINCE_MOTION_SENSED = 0x0068,

    /** Device Property - People Count */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_PEOPLE_COUNT = 0x004C,

    /** Device Property - Presence Detected */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_PRESENCE_DETECTED = 0x004D,

    /** Device Property - Present Ambient Light Level */
    RM_BLE_MESH_MODEL_SERVER_DEVICE_PROPERTY_PRESENT_AMBIENT_LIGHT_LEVEL = 0x004E,
} rm_ble_mesh_model_server_device_property_t;

typedef enum e_rm_ble_mesh_model_server_state_types
{
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_ONOFF = 0,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_LEVEL = 1,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_DEFAULT_TRANSITION_TIME = 2,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_ONPOWERUP               = 3,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_POWER_ACTUAL            = 4,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_POWER_LAST              = 5,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_POWER_DEFAULT           = 6,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_POWER_RANGE             = 7,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_POWER_LEVEL             = 8,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_BATTERY                 = 9,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_LOCATION_GLOBAL         = 10,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_LOCATION_LOCAL          = 11,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_LOCATION                = 12,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_USER_PROPERTY           = 13,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_ADMIN_PROPERTY          = 14,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_MANUFACTURER_PROPERTY   = 15,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_PROPERTY_ID             = 16,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_PROPERTY_IDS            = 17,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_PROPERTY_ID              = 18,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_DESCRIPTOR               = 19,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_SETTINGS                 = 20,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_SETTING              = 21,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_CADENCE              = 22,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_DATA                 = 23,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_SERIES_COLUMN        = 24,
    RM_BLE_MESH_MODEL_SERVER_STATE_TIME                        = 25,
    RM_BLE_MESH_MODEL_SERVER_STATE_TIME_ZONE                   = 26,
    RM_BLE_MESH_MODEL_SERVER_STATE_TIME_TAI_UTC_DELTA          = 27,
    RM_BLE_MESH_MODEL_SERVER_STATE_TIME_ROLE                   = 28,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_NUMBER                = 29,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_STATUS                = 30,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_REGISTER_STATUS       = 31,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCHEDULER_SCHEDULES         = 32,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCHEDULER_ENTRY_INDEX       = 33,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCHEDULER_ENTRY             = 34,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS_LINEAR      = 35,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS_ACTUAL      = 36,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS_LAST        = 37,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS_DEFAULT     = 38,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS_RANGE       = 39,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LIGHTNESS             = 40,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_CTL                   = 41,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_CTL_DEFAULT           = 42,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_CTL_TEMPERATURE       = 43,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_CTL_TEMPERATURE_RANGE = 44,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL                   = 45,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL_TARGET            = 46,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL_DEFAULT           = 47,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL_HUE               = 48,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL_SATURATION        = 49,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_HSL_RANGE             = 50,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_XYL                   = 51,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_XYL_TARGET            = 52,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_XYL_DEFAULT           = 53,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_XYL_RANGE             = 54,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LC_MODE               = 55,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LC_OM                 = 56,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LC_LIGHT_ONOFF        = 57,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LC_PROPERTY_ID        = 58,
    RM_BLE_MESH_MODEL_SERVER_STATE_LIGHT_LC_PROPERTY           = 59,

    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_USER_PROPERTY_IDS         = 60,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_ADMIN_PROPERTY_IDS        = 61,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_MANUFACTURER_PROPERTY_IDS = 62,
    RM_BLE_MESH_MODEL_SERVER_STATE_GENERIC_CLIENT_PROPERTY_IDS       = 63,

    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_STORE  = 64,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_RECALL = 65,
    RM_BLE_MESH_MODEL_SERVER_STATE_SCENE_DELETE = 66,

    RM_BLE_MESH_MODEL_SERVER_STATE_DELTA_LEVEL = 67,
    RM_BLE_MESH_MODEL_SERVER_STATE_MOVE_LEVEL  = 68,

    RM_BLE_MESH_MODEL_SERVER_MAX_NUM_OF_STATES = (RM_BLE_MESH_MODEL_SERVER_STATE_MOVE_LEVEL + 1),

    /* Additional supporting structure type defines */
    RM_BLE_MESH_MODEL_SERVER_EXT_TID_AND_TRANSITION_STRUCT = 128,
    RM_BLE_MESH_MODEL_SERVER_EXT_STATUS_STRUCT             = 129,
    RM_BLE_MESH_MODEL_SERVER_STATE_SENSOR_SERIES           = 130,
} rm_ble_mesh_model_server_state_types_t;

/**
 * Generic Property is a state representing a device property of an element.
 * The properties can be one of the following
 * - Manufacturer Properties
 * - Admin Properties
 * - User Properties
 */
typedef struct st_rm_ble_mesh_model_server_generic_prop_srv_state_info
{
    /**
     * User Property ID field is a 2-octet Assigned Number value referencing a
     * property
     */
    uint16_t property_id;

    /** Property Type - Manufacturer/Admin/User */
    uint8_t property_type;

    /**
     * User Access field is an enumeration indicating whether the device property
     * can be read or written as a Generic Admin/User Property
     */
    uint8_t access;

    /** User Property Value field is a conditional field */
    uint8_t * property_value;
    uint16_t  property_value_len;
} rm_ble_mesh_model_server_generic_prop_srv_state_info_t;

/**
 * Generic Property ID a read-only state representing a device property that an
 * element supports
 */
typedef struct st_rm_ble_mesh_model_server_generic_prop_srv_id_info
{
    /**
     * Property ID field is a 2-octet Assigned Number value that references a device
     * property
     */
    uint16_t property_id;
} rm_ble_mesh_model_server_generic_prop_srv_id_info_t;

/**
 * Generic Property IDs a state representing a set of device properties that an
 * element supports
 */
typedef struct st_rm_ble_mesh_model_server_generic_prop_srv_ids_info
{
    /**
     * Property IDs field is a set of 2-octet Assigned Number value that references
     * a set of device properties
     */
    uint16_t * property_ids;

    /** Count of property_ids */
    uint16_t property_ids_count;
} rm_ble_mesh_model_server_generic_prop_srv_ids_info_t;

/** Mesh model server callback parameter definition */
typedef struct st_rm_ble_mesh_model_server_callback_args
{
    void const * p_context;
    rm_ble_mesh_access_model_req_msg_context_t * p_msg_context;        ///< Context of the message.
    rm_ble_mesh_access_req_msg_raw_t           * p_msg_raw;            ///< Uninterpreted/raw received message for a specific model instance.
    rm_ble_mesh_access_model_req_msg_t         * p_req_type;           ///< Requested message type for a specific model instance.
    rm_ble_mesh_access_model_state_parameter_t * p_state_parameter;    ///< Model specific state parameters in a request or response message.
    rm_ble_mesh_access_extended_parameter_t    * p_extended_parameter; ///< Additional parameters in a Model specific request or response message.
} rm_ble_mesh_model_server_callback_args_t;

/**
 * Access Layer Model Publication Timeout Callback.
 *
 * Access Layer calls the registered callback to indicate Publication Timeout
 * for the associated model.
 *
 * \param handle        Model Handle.
 * \param blob          Blob if any or NULL.
 */
typedef struct st_rm_ble_mesh_model_server_timeout_callback_args
{
    void const * p_context;                       ///< Placeholder for user data.
    rm_ble_mesh_access_model_handle_t * p_handle; ///< Access Model handle.
    void * p_blob;
} rm_ble_mesh_model_server_timeout_callback_args_t;

/** BLE MESH MODEL SERVER control block.  Allocate an instance specific control block to pass into the BLE mesh model server API calls.
 * @par Implemented as
 * - rm_ble_mesh_model_server_instance_ctrl_t
 */
typedef void rm_ble_mesh_model_server_ctrl_t;

/** BLE mesh model health server configuration parameters. */
typedef struct st_rm_ble_mesh_model_server_cfg
{
    /** the parameters for initialization. */
    rm_ble_mesh_access_instance_t const * p_access_instance;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_ble_mesh_model_server_callback_args_t * p_args);                 ///< Mesh model server callback.
    void (* p_timeout_callback)(rm_ble_mesh_model_server_timeout_callback_args_t * p_args); ///< Access Layer Model publication timeout callback.
    void const * p_context;                                                                 ///< Placeholder for user data.
    void const * p_extend;                                                                  ///< Placeholder for user extension.
} rm_ble_mesh_model_server_cfg_t;

/** Shared Interface definition for BLE MESH */
typedef struct st_rm_ble_mesh_model_server_api
{
    /** API to open server model.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_SRV_Open()
     * - @ref RM_MESH_GENERIC_DTT_SRV_Open()
     * - @ref RM_MESH_GENERIC_LEVEL_SRV_Open()
     * - @ref RM_MESH_GENERIC_LOC_SRV_Open()
     * - @ref RM_MESH_GENERIC_ON_OFF_SRV_Open()
     * - @ref RM_MESH_GENERIC_PL_SRV_Open()
     * - @ref RM_MESH_GENERIC_POO_SRV_Open()
     * - @ref RM_MESH_GENERIC_ADMIN_PROP_SRV_Open()
     * - @ref RM_MESH_GENERIC_CLIENT_PROP_SRV_Open()
     * - @ref RM_MESH_GENERIC_MFR_PROP_SRV_Open()
     * - @ref RM_MESH_GENERIC_USER_PROP_SRV_Open()
     * - @ref RM_MESH_LIGHT_CTL_SRV_Open()
     * - @ref RM_MESH_LIGHT_HSL_SRV_Open()
     * - @ref RM_MESH_LIGHT_LC_SRV_Open()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_SRV_Open()
     * - @ref RM_MESH_LIGHT_XYL_SRV_Open()
     * - @ref RM_MESH_SCHEDULER_SRV_Open()
     * - @ref RM_MESH_TIME_SRV_Open()
     * - @ref RM_MESH_SENSOR_SRV_Open()
     * - @ref RM_MESH_CONFIG_SRV_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_model_server_cfg_t const * const p_cfg);

    /** API to close server model.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_SRV_Close()
     * - @ref RM_MESH_GENERIC_DTT_SRV_Close()
     * - @ref RM_MESH_GENERIC_LEVEL_SRV_Close()
     * - @ref RM_MESH_GENERIC_LOC_SRV_Close()
     * - @ref RM_MESH_GENERIC_ON_OFF_SRV_Close()
     * - @ref RM_MESH_GENERIC_PL_SRV_Close()
     * - @ref RM_MESH_GENERIC_POO_SRV_Close()
     * - @ref RM_MESH_GENERIC_ADMIN_PROP_SRV_Close()
     * - @ref RM_MESH_GENERIC_CLIENT_PROP_SRV_Close()
     * - @ref RM_MESH_GENERIC_MFR_PROP_SRV_Close()
     * - @ref RM_MESH_GENERIC_USER_PROP_SRV_Close()
     * - @ref RM_MESH_LIGHT_CTL_SRV_Close()
     * - @ref RM_MESH_LIGHT_HSL_SRV_Close()
     * - @ref RM_MESH_LIGHT_LC_SRV_Close()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_SRV_Close()
     * - @ref RM_MESH_LIGHT_XYL_SRV_Close()
     * - @ref RM_MESH_SCHEDULER_SRV_Close()
     * - @ref RM_MESH_TIME_SRV_Close()
     * - @ref RM_MESH_SENSOR_SRV_Close()
     * - @ref RM_MESH_CONFIG_SRV_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);

    /** API to send reply or to update state change.
     * @par Implemented as
     * - @ref RM_MESH_GENERIC_BATTERY_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_LEVEL_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_LOC_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_ON_OFF_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_PL_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_POO_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_ADMIN_PROP_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_CLIENT_PROP_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_MFR_PROP_SRV_StateUpdate()
     * - @ref RM_MESH_GENERIC_USER_PROP_SRV_StateUpdate()
     * - @ref RM_MESH_LIGHT_CTL_SRV_StateUpdate()
     * - @ref RM_MESH_LIGHT_HSL_SRV_StateUpdate()
     * - @ref RM_MESH_LIGHT_LC_SRV_StateUpdate()
     * - @ref RM_MESH_LIGHT_LIGHTNESS_SRV_StateUpdate()
     * - @ref RM_MESH_LIGHT_XYL_SRV_StateUpdate()
     * - @ref RM_MESH_SCHEDULER_SRV_StateUpdate()
     * - @ref RM_MESH_TIME_SRV_StateUpdate()
     * - @ref RM_MESH_SENSOR_SRV_StateUpdate()
     * - @ref RM_MESH_CONFIG_SRV_StateUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_state      Pointer to model specific current/target state parameters.
     */
    fsp_err_t (* stateUpdate)(rm_ble_mesh_access_ctrl_t * const               p_ctrl,
                              rm_ble_mesh_access_server_state_t const * const p_state);
} rm_ble_mesh_model_server_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_model_server_instance
{
    rm_ble_mesh_model_server_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance.
    rm_ble_mesh_model_server_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance.
    rm_ble_mesh_model_server_api_t const * p_api;  ///< Pointer to the API structure for this instance.
} rm_ble_mesh_model_server_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_MODEL_SERVER_API_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_MODEL_SERVER_API)
 **********************************************************************************************************************/
