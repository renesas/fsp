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

#ifndef RM_MESH_TIME_CLT_H
#define RM_MESH_TIME_CLT_H

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
 * Time Set message parameters.
 */
typedef struct st_rm_mesh_time_info
{
    /** The current TAI time in seconds */
    uint8_t tai_seconds[5];

    /** The sub-second time in units of 1/256th second */
    uint8_t subsecond;

    /** The estimated uncertainty in 10 millisecond steps */
    uint8_t uncertainty;

    /** 0 = No Time Authority, 1 = Time Authority */
    uint8_t time_authority;

    /** Current difference between TAI and UTC in seconds */
    uint16_t tai_utc_delta;

    /** The local time zone offset in 15-minute increments */
    uint8_t time_zone_offset;
} rm_mesh_time_info_t;

/**
 * Time Zone Set message parameters.
 */
typedef struct st_rm_mesh_time_zone_set_info
{
    /** Upcoming local time zone offset */
    uint8_t time_zone_offset_new;

    /** TAI Seconds time of the upcoming Time Zone Offset change */
    uint8_t tai_of_zone_change[5];
} rm_mesh_time_zone_set_info_t;

/**
 * Time Zone Status message parameters.
 */
typedef struct st_rm_mesh_time_zone_status_info
{
    /** Current local time zone offset */
    uint8_t time_zone_offset_current;

    /** Upcoming local time zone offset */
    uint8_t time_zone_offset_new;

    /** TAI Seconds time of the upcoming Time Zone Offset change */
    uint8_t tai_of_zone_change[5];
} rm_mesh_time_zone_status_info_t;

/**
 * TAI-UTC Delta Set message parameters.
 */
typedef struct st_rm_mesh_time_tai_utc_delta_set_info
{
    /** Upcoming difference between TAI and UTC in seconds */
    uint16_t tai_utc_delta_new;

    /** Always 0b0. Other values are Prohibited. */
    uint8_t padding;

    /** TAI Seconds time of the upcoming TAI-UTC Delta change */
    uint8_t tai_of_delta_change[5];
} rm_mesh_time_tai_utc_delta_set_info_t;

/**
 * TAI-UTC Delta Status message parameters.
 */
typedef struct st_rm_mesh_time_tai_utc_delta_status_info
{
    /** Current difference between TAI and UTC in seconds */
    uint16_t tai_utc_delta_current;

    /** Always 0b0. Other values are Prohibited. */
    uint8_t padding_1;

    /** Upcoming difference between TAI and UTC in seconds */
    uint16_t tai_utc_delta_new;

    /** Always 0b0. Other values are Prohibited. */
    uint8_t padding_2;

    /** TAI Seconds time of the upcoming TAI-UTC Delta change */
    uint8_t tai_of_delta_change[5];
} rm_mesh_time_tai_utc_delta_status_info_t;

/**
 * Time Role Set/Status message parameters.
 */
typedef struct st_rm_mesh_time_role_info
{
    /** The Time Role for the element */
    uint8_t time_role;
} rm_mesh_time_role_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_TIME_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh time instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_TIME_CLT_Open() is called. */
typedef struct st_rm_mesh_time_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_time_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_time_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_TIME_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_TIME_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_TIME_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                          rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_TIME_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_TIME_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                           uint32_t                                req_opcode,
                                           void const * const                      parameter,
                                           uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_TIME_CLT_Get(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_TIME_CLT_Set(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_TIME_CLT_ZoneGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_TIME_CLT_ZoneSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);
fsp_err_t RM_MESH_TIME_CLT_TaiUtcDeltaGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_TIME_CLT_TaiUtcDeltaSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                          void const * const                      p_parameter);
fsp_err_t RM_MESH_TIME_CLT_RoleGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_TIME_CLT_RoleSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl, void const * const p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_TIME_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_TIME_CLT_H
