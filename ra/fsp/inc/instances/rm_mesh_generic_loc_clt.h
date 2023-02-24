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

#ifndef RM_MESH_GENERIC_LOC_CLT_H
#define RM_MESH_GENERIC_LOC_CLT_H

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
 * Generic Location Global Set message parameters.
 */
typedef struct st_rm_mesh_generic_loc_global_info
{
    /**
     * Global Coordinates (Latitude).
     * The Global Latitude field describes the global WGS84 North coordinate of the element.
     */
    uint32_t global_latitude;

    /**
     * Global Coordinates (Longitude).
     * The Global Longitude field describes the global WGS84 East coordinate of the element.
     */
    uint32_t global_longitude;

    /**
     * Global Altitude.
     * The Global Altitude field determines the altitude of the device above the WGS84 datum.
     * It expresses the altitude beyond the WGS84 ellipsoid of the element that exposed its position.
     *
     * Value         | Description
     * --------------|------------
     * 0x7FFF        | Global Altitude is not configured.
     * 0x7FFE        | Global Altitude is greater than or equal to 32766 meters.
     * 0x8000-0x7FFD | Global Altitude is (field value) from -32768 meters through 32765 meters.
     */
    uint16_t global_altitude;
} rm_mesh_generic_loc_global_info_t;

/**
 * Generic Location Local Set message parameters.
 */
typedef struct st_rm_mesh_generic_loc_local_info
{
    /**
     * Local Coordinates (North).
     * The Local North field describes the North coordinate of the device using a local coordinate system.
     * It is relative to the north orientation on a predefined map.
     *
     * The Local North value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters.
     * The value 0x8000 means the Local North information is not configured.
     */
    uint16_t local_north;

    /**
     * Local Coordinates (East).
     * The Local East field describes the East coordinate of the device using a local coordinate system.
     * It is relative to the east orientation of a predefined map.
     *
     * The Local East value is encoded decimeters and it ranges from -32767 decimeters through 32767 decimeters.
     * The value 0x8000 means the Local East information is not configured.
     */
    uint16_t local_east;

    /**
     * Local Altitude.
     * The Local Altitude field determines the altitude of the device relative to the Generic Location Global Altitude.
     *
     * Value         | Description
     * --------------|------------
     * 0x7FFF        | Local Altitude is not configured.
     * 0x7FFE        | Local Altitude is greater than or equal to 32766 meters.
     * 0x8000-0x7FFD | Local Altitude is (field value) from -32768 meters through 32765 meters.
     */
    uint16_t local_altitude;

    /**
     * Floor Number.
     *
     * The Floor Number field describes the floor number where the element is installed.
     * The floor number, N, is encoded as X = N + 20, where X is the encoded floor number.
     * Floor number = -20 (X=0) has a special meaning, indicating the floor -20, and also any floor below that.
     * Floor number = 232 (X=252) has a special meaning, indicating the floor 232, and also any floor above that.
     *
     * Encoded Value X | Floor number N
     * ----------------|---------------
     * 0x00            | Floor -20 or any floor below -20.
     * 0x01-0xFB       | Floor number N, encoded as X = N + 20.
     * 0xFC            | Floor 232 or any floor above 232.
     * 0xFD            | Ground floor. Floor 0.
     * 0xFE            | Ground floor. Floor 1.
     * 0xFF            | Not configured
     *
     * Note: The reason for having two definitions of ground floor (0 or 1) is to allow for
     * different conventions applicable in different countries.
     */
    uint8_t floor_number;

    /**
     * Uncertainty.
     * The Uncertainty field is a 16-bit bit field that describes the uncertainty of
     * the location information the element exposes.
     *
     * bits  | Field       | Description
     * ------|-------------|------------
     * 0     | Stationary  | This bit indicates whether the device broadcasting the location information
     *                       has a stationary location or is mobile. (0 = Stationary, 1 = Mobile)
     * 1-7   | RFU         | Reserved for Future Use
     * 8-11  | Update Time | This value (x) is a 4-bit value ranging from 0 through 15.
     *                       It represents the time (t) elapsed since the last update of the device's position,
     *                       measured in seconds using the following formula: t=2^(x-3)
     *                       The represented range is from 0.125 seconds through 4096 seconds.
     *                       Note: If 'stationary' is set, this value can be ignored.
     * 12-15 | Precision   | This value (y) is a 4-bit value ranging from 0 through 15.
     *                       It represents a location precision with the formula: Precision = 2^(y-3)
     *                       The represented range is from 0.125 meters through 4096 meters.
     */
    uint16_t uncertainty;
} rm_mesh_generic_loc_local_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_GENERIC_LOC_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh generic loc instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_LOC_CLT_Open() is called. */
typedef struct st_rm_mesh_generic_loc_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_generic_loc_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_generic_loc_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_LOC_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                       rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_GENERIC_LOC_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                 rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_GENERIC_LOC_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                  uint32_t                                req_opcode,
                                                  void const * const                      parameter,
                                                  uint32_t                                rsp_opcode);

fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationGlobalGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationGlobalSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                    void const * const                      parameter);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationGlobalSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                                  void const * const                      parameter);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationLocalGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationLocalSet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                   void const * const                      parameter);
fsp_err_t RM_MESH_GENERIC_LOC_CLT_LocationLocalSetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                                 void const * const                      parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_LOC_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_LOC_CLT_H
