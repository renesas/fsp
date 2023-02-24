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

#ifndef RM_MESH_SENSOR_SRV_H
#define RM_MESH_SENSOR_SRV_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_model_server_api.h"
#include "rm_ble_mesh_access.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_MESH_SENSOR_SRV
 * @{
 **********************************************************************************************************************/

/** Sensor Descriptor state represents the attributes describing the sensor data */
typedef struct st_rm_mesh_sensor_srv_descriptor_info
{
    /**
     * Sensor Property ID field is a 2-octet value referencing a device property
     * that describes the meaning and the format of data reported by a sensor
     */
    uint16_t sensor_property_id;

    /**
     * Sensor Positive Tolerance field is a 12-bit value representing the magnitude
     * of a possible positive error associated with the measurements that the sensor
     * is reporting
     */
    uint16_t sensor_positive_tolerance;

    /**
     * Sensor Negative Tolerance field is a 12-bit value representing the magnitude
     * of a possible negative error associated with the measurements that the sensor
     * is reporting
     */
    uint16_t sensor_negative_tolerance;

    /**
     * Sensor Sampling Function field specifies the averaging operation or type of
     * sampling function applied to the measured value
     */
    uint8_t sensor_sampling_function;

    /**
     * Sensor Measurement Period field specifies a uint8 value n that represents the
     * averaging time span, accumulation time, or measurement period in seconds over
     * which the measurement is taken
     */
    uint8_t sensor_measurement_period;

    /**
     * measurement reported by a sensor is internally refreshed at the frequency
     * indicated in the Sensor Update Interval field
     */
    uint8_t sensor_update_interval;

    /** Status - used in response to indicate if other fields to be included */
    uint8_t status;
} rm_mesh_sensor_srv_descriptor_info_t;

/** Sensor Settings state controls parameters of a sensor */
typedef struct st_rm_mesh_sensor_srv_settings_info
{
    /** Property ID of a sensor */
    uint16_t sensor_property_id;

    /** Property ID of a setting within a sensor */
    uint16_t * setting_property_ids;
    uint16_t   setting_property_ids_count;
} rm_mesh_sensor_srv_settings_info_t;

/** Sensor Setting state controls parameters of a sensor */
typedef struct st_rm_mesh_sensor_srv_setting_info
{
    /** Property ID of a sensor */
    uint16_t sensor_property_id;

    /** Property ID of a setting within a sensor */
    uint16_t sensor_setting_property_id;

    /** Read/Write access rights for the setting */
    uint8_t sensor_setting_access;

    /** Raw value of a setting within a sensor */
    uint8_t * sensor_setting_raw;
    uint16_t  sensor_setting_raw_len;

    /* Status - used in response path */
    uint8_t status;
} rm_mesh_sensor_srv_setting_info_t;

/** Sensor Cadence state controls the cadence of sensor reports */
typedef struct st_rm_mesh_sensor_srv_cadence_info
{
    /** Property ID of a sensor */
    uint16_t sensor_property_id;

    /** Divisor for the Publish Period */
    uint8_t fast_cadence_period_divisor;

    /** Defines the unit and format of the Status Trigger Delta fields */
    uint8_t status_trigger_type;

    /** Delta down value that triggers a status message */
    uint8_t * status_trigger_delta_down;
    uint16_t  status_trigger_delta_down_len;

    /** Delta up value that triggers a status message */
    uint8_t * status_trigger_delta_up;
    uint16_t  status_trigger_delta_up_len;

    /** Minimum interval between two consecutive Status messages */

    /**
     * APPLICATION NOTE:
     * The Current Sensor Server Model implementation does not inherantly
     * check for the time interval between two consecutive status messages.
     * The application layer which manages the data for the Sensor Server
     * Model holds the responsibility for interleaving consecutive status
     * messages with the configured Minimum time interval for statuses.
     */
    uint8_t status_min_interval;

    /** Low value for the fast cadence range */
    uint8_t * fast_cadence_low;
    uint16_t  fast_cadence_low_len;

    /** High value for the fast cadence range */
    uint8_t * fast_cadence_high;
    uint16_t  fast_cadence_high_len;

    /** Status - used in response path */
    uint8_t status;
} rm_mesh_sensor_srv_cadence_info_t;

/**
 * The Sensor Data state is a sequence of one or more pairs of Sensor Property
 * ID and Raw Value fields, with each Raw Value field size and representation
 * defined by the characteristics referenced by the Sensor Property ID
 */
typedef struct st_rm_mesh_sensor_srv_data_info
{
    /** ID of the 1st device property of the sensor */
    uint16_t property_id_1;

    /**
     * Raw Value field with a size and representation defined by the 1st device
     * property
     */
    uint8_t * raw_value_1;
    uint16_t  raw_value_1_len;

    /** ID of the 2nd device property of the sensor */
    uint16_t property_id_2;

    /**
     * Raw Value field with a size and representation defined by the 2nd device
     * property
     */
    uint8_t * raw_value_2;
    uint16_t  raw_value_2_len;

    /** ID of the nth device property of the sensor */
    uint16_t property_id_n;

    /**
     * Raw Value field with a size and representation defined by the nth device
     * property
     */
    uint8_t * raw_value_n;
    uint16_t  raw_value_n_len;

    /** Status - used in response path */
    uint8_t status;
} rm_mesh_sensor_srv_data_info_t;

/**
 * Values measured by sensors may be organized as arrays (and represented as
 * series of columns, such as histograms
 */
typedef struct st_rm_mesh_sensor_srv_series_column_info
{
    /** Property describing the data series of the sensor */
    uint16_t sensor_property_id;

    /** Raw value representing the left corner of a column on the X axis */
    uint8_t * sensor_raw_value_x;
    uint16_t  sensor_raw_value_x_len;

    /** Raw value representing the width of the column */
    uint8_t * sensor_column_width;
    uint16_t  sensor_column_width_len;

    /** Raw value representing the height of the column on the Y axis */
    uint8_t * sensor_raw_value_y;
    uint16_t  sensor_raw_value_y_len;

    /** Status - used in response path */
    uint8_t status;
} rm_mesh_sensor_srv_series_column_info_t;

/** BLE mesh sensor instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_SENSOR_SRV_Open() is called. */
typedef struct st_rm_mesh_sensor_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_sensor_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_sensor_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_SENSOR_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                  rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_SENSOR_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_SENSOR_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                         rm_ble_mesh_access_server_state_t const * const p_state);
fsp_err_t RM_MESH_SENSOR_SRV_SetupServerStateUpdate(rm_ble_mesh_model_server_ctrl_t * const         p_ctrl,
                                                    rm_ble_mesh_access_server_state_t const * const p_state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_SENSOR_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_SENSOR_SRV_H
