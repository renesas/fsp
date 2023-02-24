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

#ifndef RM_MESH_SENSOR_CLT_H
#define RM_MESH_SENSOR_CLT_H

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
 * Sensor Descriptor Get message parameters.
 */
typedef struct st_rm_mesh_sensor_descriptor_get_info
{
    /** Property ID for the sensor (Optional) */
    uint16_t property_id;

    /** Flag: To represent if optional field Property ID is valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_descriptor_get_info_t;

/**
 * Sensor Descriptor Status message parameters.
 */
typedef struct st_rm_mesh_sensor_descriptor_status_info
{
    /** Sequence of 8-octet Sensor Descriptors (Optional) */
    uint8_t * descriptor;

    /** Flag: To represent if optional field Descriptors are valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_descriptor_status_info_t;

/**
 * Sensor Get message parameters.
 */
typedef struct st_rm_mesh_sensor_get_info
{
    /** Property for the sensor. */
    uint16_t property_id;

    /** Flag: To represent if optional field Property ID is valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_get_info_t;

/**
 * Sensor Status message parameters.
 */
typedef struct st_rm_mesh_sensor_status_info
{
    /** The Marshaled Sensor Data. */
    uint8_t * marshalled_sensor_data;

    /** The Marshaled Sensor Data Length . */
    uint16_t marshalled_sensor_data_length;

    /** Flag: To represent if optional field Marshaled Sensor Data is valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_status_info_t;

/**
 * Sensor Column Get message parameters.
 */
typedef struct st_rm_mesh_sensor_column_get_info
{
    /** Property identifying a sensor */
    uint16_t property_id;

    /** Raw value identifying a column */
    uint8_t * raw_value_x;

    /** Raw value length identifying a column */
    uint16_t raw_value_x_length;
} rm_mesh_sensor_column_get_info_t;

/**
 * Sensor Column Status message parameters.
 */
typedef struct st_rm_mesh_sensor_column_status_info
{
    /** Property identifying a sensor and the Y axis. */
    uint16_t property_id;

    /** Raw value representing the left corner of the column on the X axis. */
    uint8_t * raw_value_x;

    /** Raw value length representing the left corner of the column on the X axis. */
    uint16_t raw_value_x_length;

    /** Raw value representing the width of the column. (Optional) */
    uint8_t * column_width;

    /** Raw value length representing the width of the column. (Optional) */
    uint16_t column_width_length;

    /** Raw value representing the height of the column on the Y axis. */
    uint8_t * raw_value_y;

    /** Raw value length representing the height of the column on the Y axis. */
    uint16_t raw_value_y_length;

    /** Flag: To represent if optional fields Column Width and Raw Value Y are valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_column_status_info_t;

/**
 * Sensor Series Get message parameters.
 */
typedef struct st_rm_mesh_sensor_series_get_info
{
    /** Property identifying a sensor. */
    uint16_t property_id;

    /** Raw value identifying a starting column. (Optional) */
    uint8_t * raw_value_x1;

    /** Raw value length identifying a starting column. (Optional) */
    uint16_t raw_value_x1_length;

    /** Raw value identifying an ending column. */
    uint8_t * raw_value_x2;

    /** Raw value length identifying an ending column. */
    uint16_t raw_value_x2_length;

    /** Flag: To represent if optional fields Raw Value X1 and X2 are valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_series_get_info_t;

/**
 * Sensor Series Status message parameters.
 */
typedef struct st_rm_mesh_sensor_series_status_info
{
    /** Property identifying a sensor and the Y axis. */
    uint16_t property_id;

    /** Raw value representing the left corner of the nth column on the X axis. */
    uint8_t * raw_value_x;

    /** Number of values in raw_value_x */
    uint16_t raw_value_x_length;

    /** Raw value representing the width of the nth column. */
    uint8_t * column_width;

    /** Number of values in column_width */
    uint16_t column_width_length;

    /** Raw value representing the height of the nth column on the Y axis. */
    uint8_t * raw_value_y;

    /** Number of values in raw_value_y */
    uint16_t raw_value_y_length;
} rm_mesh_sensor_series_status_info_t;

/**
 * Sensor Cadence Get message parameters.
 */
typedef struct st_rm_mesh_sensor_cadence_get_info
{
    /** Property ID for the sensor. */
    uint16_t property_id;
} rm_mesh_sensor_cadence_get_info_t;

/**
 * Sensor Cadence Set message parameters.
 */
typedef struct st_rm_mesh_sensor_cadence_set_info
{
    /** Property ID for the sensor. */
    uint16_t property_id;

    /** Divisor for the Publish Period */
    uint8_t fast_cadence_period_divisor;

    /** Defines the unit and format of the Status Trigger Delta fields. */
    uint8_t status_trigger_type;

    /** Delta down value that triggers a status message. */
    uint8_t * status_trigger_delta_down;

    /** Delta down value length that triggers a status message. */
    uint16_t status_trigger_delta_down_length;

    /** Delta up value that triggers a status message. */
    uint8_t * status_trigger_delta_up;

    /** Delta up value length that triggers a status message. */
    uint16_t status_trigger_delta_up_length;

    /** Minimum interval between two consecutive Status messages. */
    uint8_t status_min_interval;

    /** Low value for the fast cadence range. */
    uint8_t * fast_cadence_low;

    /** Low value length for the fast cadence range. */
    uint16_t fast_cadence_low_length;

    /** High value for the fast cadence range. */
    uint8_t * fast_cadence_high;

    /** High value length for the fast cadence range. */
    uint16_t fast_cadence_high_length;
} rm_mesh_sensor_cadence_set_info_t;

/**
 * Sensor Cadence Status message parameters.
 */
typedef struct st_rm_mesh_sensor_cadence_status_info
{
    /** Property ID for the sensor. */
    uint16_t property_id;

    /** Divisor for the Publish Period */
    uint8_t fast_cadence_period_divisor;

    /** Defines the unit and format of the Status Trigger Delta fields. */
    uint8_t status_trigger_type;

    /** Delta down value that triggers a status message. */
    uint8_t * status_trigger_delta_down;

    /** Delta down value length that triggers a status message. */
    uint16_t status_trigger_delta_down_length;

    /** Delta up value that triggers a status message. */
    uint8_t * status_trigger_delta_up;

    /** Delta up value length that triggers a status message. */
    uint16_t status_trigger_delta_up_length;

    /** Minimum interval between two consecutive Status messages. */

    /**
     * APPLICATION NOTE:
     * The Current Sensor Server Model implementation does not inherantly
     * check for the time interval between two consecutive status messages.
     * The application layer which manages the data for the Sensor Server
     * Model holds the responsibility for interleaving consecutive status
     * messages with the configured Minimum time interval for statuses.
     */
    uint8_t status_min_interval;

    /** Low value for the fast cadence range. */
    uint8_t * fast_cadence_low;

    /** Low value length for the fast cadence range. */
    uint16_t fast_cadence_low_length;

    /** High value for the fast cadence range. */
    uint8_t * fast_cadence_high;

    /** High value length for the fast cadence range. */
    uint16_t fast_cadence_high_length;
} rm_mesh_sensor_cadence_status_info_t;

/**
 * Sensor Settings Get message parameters.
 */
typedef struct st_rm_mesh_sensor_settings_get_info
{
    /** Property ID identifying a sensor. */
    uint16_t sensor_property_id;
} rm_mesh_sensor_settings_get_info_t;

/**
 * Sensor Setting Status message parameters.
 */
typedef struct st_rm_mesh_sensor_settings_status_info
{
    /** Property ID identifying a sensor. */
    uint16_t sensor_property_id;

    /**
     * A sequence of N Sensor Setting Property IDs identifying settings within a sensor,
     * where N is the number of property IDs included in the message. (Optional)
     */
    uint16_t * sensor_setting_property_ids;

    /** Number of Sensor Setting Property IDs */
    uint16_t sensor_setting_property_ids_count;
} rm_mesh_sensor_settings_status_info_t;

/**
 * Sensor Setting Get message parameters.
 */
typedef struct st_rm_mesh_sensor_setting_get_info
{
    /** Property ID identifying a sensor. */
    uint16_t sensor_property_id;

    /** Setting Property ID identifying a setting within a sensor. */
    uint16_t sensor_setting_property_id;
} rm_mesh_sensor_setting_get_info_t;

/**
 * Sensor Setting Set message parameters.
 */
typedef struct st_rm_mesh_sensor_setting_set_info
{
    /** Property ID identifying a sensor. */
    uint16_t sensor_property_id;

    /** Setting ID identifying a setting within a sensor. */
    uint16_t sensor_setting_property_id;

    /** Raw value for the setting. */
    uint8_t * sensor_setting_raw;

    /** Raw value length for the setting. */
    uint16_t sensor_setting_raw_length;
} rm_mesh_sensor_setting_set_info_t;

/**
 * Sensor Setting Status message parameters.
 */
typedef struct st_rm_mesh_sensor_setting_status_info
{
    /** Property ID identifying a sensor. */
    uint16_t sensor_property_id;

    /** Setting ID identifying a setting within a sensor. */
    uint16_t sensor_setting_property_id;

    /** Read / Write access rights for the setting. (Optional) */
    uint8_t sensor_setting_access;

    /** Raw value for the setting. */
    uint8_t * sensor_setting_raw;

    /** Raw value length for the setting. */
    uint16_t sensor_setting_raw_length;

    /** Flag: To represent if optional fields Access and Setting Raw are valid */
    uint8_t optional_fields_present;
} rm_mesh_sensor_setting_status_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_SENSOR_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh sensor instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_SENSOR_CLT_Open() is called. */
typedef struct st_rm_mesh_sensor_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_sensor_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_sensor_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_SENSOR_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                  rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_SENSOR_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SENSOR_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                            rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_SENSOR_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                            rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_SENSOR_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                             uint32_t                                req_opcode,
                                             void const * const                      parameter,
                                             uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_SENSOR_CLT_DescriptorGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                           void const * const                      p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_Get(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_ColumnGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_SeriesGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_CadenceGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_CadenceSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_CadenceSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                      void const * const                      p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_SettingsGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                         void const * const                      p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_SettingGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_SettingSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_SENSOR_CLT_SettingSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                      void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_SENSOR_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_SENSOR_CLT_H
