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

#ifndef RM_MESH_LIGHT_LC_SRV_H
#define RM_MESH_LIGHT_LC_SRV_H

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
 * @addtogroup RM_MESH_LIGHT_LC_SRV
 * @{
 **********************************************************************************************************************/

/** Light LC light event */
typedef enum e_rm_ble_mesh_light_lc_srv_event
{
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_OFF                 = 0x01, ///< Light LC Server Event Off
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_STANDBY             = 0x02, ///< Light LC Server Event Standby
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_FADE_ON             = 0x03, ///< Light LC Server Event Fade On
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_RUN                 = 0x04, ///< Light LC Server Event Run
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_FADE                = 0x05, ///< Light LC Server Event Fade
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_PROLONG             = 0x06, ///< Light LC Server Event Prolong
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_FADE_STANDBY_AUTO   = 0x07, ///< Light LC Server Event Standby Auto
    RM_MESH_LIGHT_LC_SRV_LIGHT_EVENT_FADE_STANDBY_MANUAL = 0x08, ///< Light LC Server Event Standby Manual
} rm_ble_mesh_light_lc_srv_event_t;

/** Light LC state */
typedef enum e_rm_ble_mesh_light_lc_srv_state
{
    RM_MESH_LIGHT_LC_SRV_STATE_OFF                 = 0x01, ///< Light LC Server State Off
    RM_MESH_LIGHT_LC_SRV_STATE_STANDBY             = 0x02, ///< Light LC Server State Standby
    RM_MESH_LIGHT_LC_SRV_STATE_FADE_ON             = 0x04, ///< Light LC Server State Fade On
    RM_MESH_LIGHT_LC_SRV_STATE_RUN                 = 0x08, ///< Light LC Server State Run
    RM_MESH_LIGHT_LC_SRV_STATE_FADE                = 0x10, ///< Light LC Server State Fade
    RM_MESH_LIGHT_LC_SRV_STATE_PROLONG             = 0x20, ///< Light LC Server State Prolong
    RM_MESH_LIGHT_LC_SRV_STATE_FADE_STANDBY_AUTO   = 0x40, ///< Light LC Server State Standby Auto
    RM_MESH_LIGHT_LC_SRV_STATE_FADE_STANDBY_MANUAL = 0x80, ///< Light LC Server State Standby Manual
} rm_ble_mesh_light_lc_srv_state_t;

/** Light LC light state */
typedef enum e_rm_mesh_light_lc_srv_light_state
{
    RM_MESH_LIGHT_LC_SRV_LIGHT_STATE_OFF = 0, ///< Light state Off
    RM_MESH_LIGHT_LC_SRV_LIGHT_STATE_ON  = 1  ///< Light state ON
} rm_mesh_light_lc_srv_light_state_t;

/**
 * Light LC Server State Info
 */
typedef struct st_rm_mesh_light_lc_srv_scenario
{
    /** Light LC Server Current Scenario */
    rm_ble_mesh_light_lc_srv_state_t state;

    /** Remaining Time in current scenario */
    uint32_t remaining_time_in_ms;

    /** Light LC Occupancy Mode Value */
    uint8_t occupancy_mode;

    /** Light LC Mode Value */
    uint8_t mode;

    /** Current Light LC ONOFF State */
    rm_mesh_light_lc_srv_light_state_t present_light_state;

    /** Target Light LC ONOFF State */
    rm_mesh_light_lc_srv_light_state_t target_light_state;
} rm_mesh_light_lc_srv_scenario_t;

/** Light LC Mode state */
typedef struct st_rm_mesh_light_lc_srv_mode_info
{
    /** Light LC Mode state - present */
    uint8_t present_mode;

    /** Light LC Mode state - target */
    uint8_t target_mode;
} rm_mesh_light_lc_srv_mode_info_t;

/** Light LC Occupancy Mode state */
typedef struct st_rm_mesh_light_lc_srv_om_info
{
    /** Light LC Occupancy Mode state - present */
    uint8_t present_mode;

    /** Light LC Occupancy Mode state - target */
    uint8_t target_mode;
} rm_mesh_light_lc_srv_om_info_t;

/** Light LC Light OnOff State */
typedef struct st_rm_mesh_light_lc_srv_light_onoff_info
{
    /** Light LC Light OnOff State */
    uint8_t present_light_onoff;

    /** Light LC Light OnOff State */
    uint8_t target_light_onoff;

    /** TID - Used in request path */
    uint8_t tid;

    /**
     * Transition Time - Used in request path.
     * Used as remaining time in response path.
     */
    uint8_t transition_time;

    /** Delay - Used in request path */
    uint8_t delay;

    /** Transition Timer Handle */
    uint16_t transition_time_handle;
} rm_mesh_light_lc_srv_light_onoff_info_t;

/** Property ID identifying a Light LC Property */
typedef struct st_rm_mesh_light_lc_srv_property_id_info
{
    /** Property ID identifying a Light LC Property */
    uint16_t property_id;
} rm_mesh_light_lc_srv_property_id_info_t;

/** Light LC Property state */
typedef struct st_rm_mesh_light_lc_srv_property_info
{
    /** Property ID identifying a Light LC Property */
    uint16_t property_id;

    /** Raw value for the Light LC Property */
    uint8_t * property_value;
    uint16_t  property_value_len;
} rm_mesh_light_lc_srv_property_info_t;

/** Light LC Property state */
typedef struct st_rm_mesh_light_lc_srv_extended_callback_args
{
    rm_ble_mesh_access_model_handle_t * p_handle;   ///< Access model handle.
    rm_ble_mesh_light_lc_srv_event_t    event_type; ///< Application events defined for Light LC Server Model.
    uint8_t * p_event_data;                         ///< Event data.
    uint16_t  event_data_length;                    ///< Event data length.
} rm_mesh_light_lc_srv_extended_callback_args_t;

/** BLE mesh light lc instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_LIGHT_LC_SRV_Open() is called. */
typedef struct st_rm_mesh_light_lc_srv_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_model_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_light_lc_srv_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_server_api_t g_rm_ble_mesh_model_server_on_rm_mesh_light_lc_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_LIGHT_LC_SRV_Open(rm_ble_mesh_model_server_ctrl_t * const      p_ctrl,
                                    rm_ble_mesh_model_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_LIGHT_LC_SRV_Close(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LC_SRV_StateUpdate(rm_ble_mesh_model_server_ctrl_t * const   p_ctrl,
                                           rm_ble_mesh_access_server_state_t const * p_state);
fsp_err_t RM_MESH_LIGHT_LC_SRV_SetTimeProperty(rm_ble_mesh_model_server_ctrl_t * const    p_ctrl,
                                               rm_ble_mesh_model_server_device_property_t property,
                                               uint32_t                                   time_in_ms);
fsp_err_t RM_MESH_LIGHT_LC_SRV_SetScenario(rm_ble_mesh_model_server_ctrl_t * const       p_ctrl,
                                           rm_mesh_light_lc_srv_scenario_t const * const p_scenario);
fsp_err_t RM_MESH_LIGHT_LC_SRV_GetCurrentScenario(rm_ble_mesh_model_server_ctrl_t * const p_ctrl,
                                                  rm_mesh_light_lc_srv_scenario_t * const p_scenario);
fsp_err_t RM_MESH_LIGHT_LC_SRV_ReportOccupancy(rm_ble_mesh_model_server_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_LIGHT_LC_SRV_ReportLightOnOff(rm_ble_mesh_model_server_ctrl_t * const p_ctrl,
                                                rm_mesh_light_lc_srv_light_state_t      state);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_LIGHT_LC_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_LIGHT_LC_SRV_H
