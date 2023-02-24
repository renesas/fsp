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

#ifndef RM_MESH_GENERIC_PROP_CLT_H
#define RM_MESH_GENERIC_PROP_CLT_H

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
 * Generic User Properties Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_user_properties_status_info
{
    /**
     * A sequence of N User Property IDs present within an element,
     * where N is the number of device property IDs included in the message.
     */
    uint16_t * user_property_ids;

    /** Number of User Property IDs */
    uint16_t user_property_ids_count;
} rm_mesh_generic_prop_user_properties_status_info_t;

/**
 * Generic User Property Get message parameters.
 */
typedef struct st_rm_mesh_generic_prop_user_property_get_info
{
    /** Property ID identifying a Generic User Property. */
    uint16_t user_property_id;
} rm_mesh_generic_prop_user_property_get_info_t;

/**
 * Generic User Property Set message parameters.
 */
typedef struct st_rm_mesh_generic_prop_user_property_set_info
{
    /** Property ID identifying a Generic User Property */
    uint16_t user_property_id;

    /** Raw value for the User Property */
    uint8_t * user_property_value;

    /** Raw value length for the User Property */
    uint16_t user_property_value_length;
} rm_mesh_generic_prop_user_property_set_info_t;

/**
 * Generic User Property Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_user_property_status_info
{
    /** Property ID identifying a Generic User Property. */
    uint16_t user_property_id;

    /** Enumeration indicating user access. */
    uint8_t user_access;

    /** Raw value for the User Property */
    uint8_t * user_property_value;

    /** Raw value length for the User Property */
    uint16_t user_property_value_length;

    /** Flag: To represent if optional fields User Access and Raw Value are valid */
    uint8_t optional_fields_present;
} rm_mesh_generic_prop_user_property_status_info_t;

/**
 * Generic Admin Properties Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_admin_properties_status_info
{
    /**
     * A sequence of N Admin Property IDs present within an element,
     * where N is the number of device property IDs included in the message.
     */
    uint16_t * admin_property_ids;

    /** Number of Admin Property IDs */
    uint16_t admin_property_ids_count;
} rm_mesh_generic_prop_admin_properties_status_info_t;

/**
 * Generic Admin Property Get message parameters.
 */
typedef struct st_rm_mesh_generic_prop_admin_property_get_info
{
    /** Property ID identifying a Generic Admin Property. */
    uint16_t admin_property_id;
} rm_mesh_generic_prop_admin_property_get_info_t;

/**
 * Generic Admin Property Set message parameters.
 */
typedef struct st_rm_mesh_generic_prop_admin_property_set_info
{
    /** Property ID identifying a Generic Admin Property. */
    uint16_t admin_property_id;

    /** Enumeration indicating user access. */
    uint8_t admin_user_access;

    /** Raw value for the Admin Property */
    uint8_t * admin_property_value;

    /** Raw value length for the Admin Property */
    uint16_t admin_property_value_length;
} rm_mesh_generic_prop_admin_property_set_info_t;

/**
 * Generic Admin Property Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_admin_property_status_info
{
    /** Property ID identifying a Generic Admin Property */
    uint16_t admin_property_id;

    /** Enumeration indicating user access (Optional) */
    uint8_t admin_user_access;

    /** Raw value for the Admin Property */
    uint8_t * admin_property_value;

    /** Raw value length for the Admin Property */
    uint16_t admin_property_value_length;
} rm_mesh_generic_prop_admin_property_status_info_t;

/**
 * Generic Manufacturer Properties Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_manufacturer_properties_status_info
{
    /**
     * A sequence of N Manufacturer Property IDs present within an element,
     * where N is the number of device property IDs included in the message.
     */
    uint16_t * manufacturer_property_ids;

    /** Number of Manufacturer Property IDs */
    uint16_t manufacturer_property_ids_count;
} rm_mesh_generic_prop_manufacturer_properties_status_info_t;

/**
 * Generic Manufacturer Property Get message parameters.
 */
typedef struct st_rm_mesh_generic_prop_manufacturer_property_get_info
{
    /** Property ID identifying a Generic Manufacturer Property */
    uint16_t manufacturer_property_id;
} rm_mesh_generic_prop_manufacturer_property_get_info_t;

/**
 * Generic Manufacturer Property Set message parameters.
 */
typedef struct st_rm_mesh_generic_prop_manufacturer_property_set_info
{
    /** Property ID identifying a Generic Manufacturer Property */
    uint16_t manufacturer_property_id;

    /** Enumeration indicating user access */
    uint8_t manufacturer_user_access;
} rm_mesh_generic_prop_manufacturer_property_set_info_t;

/**
 * Generic Manufacturer Property Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_manufacturer_property_status_info
{
    /** Property ID identifying a Generic Manufacturer Property */
    uint16_t manufacturer_property_id;

    /** Enumeration indicating user access */
    uint8_t manufacturer_user_access;

    /** Raw value for the Manufacturer Property */
    uint8_t * manufacturer_property_value;

    /** Raw value length for the Manufacturer Property */
    uint16_t manufacturer_property_value_length;
} rm_mesh_generic_prop_manufacturer_property_status_info_t;

/**
 * Generic Client Properties Get message parameters.
 */
typedef struct st_rm_mesh_generic_prop_client_properties_get_info
{
    /** A starting Client Property ID present within an element */
    uint16_t client_property_id;
} rm_mesh_generic_prop_client_properties_get_info_t;

/**
 * Generic Client Properties Status message parameters.
 */
typedef struct st_rm_mesh_generic_prop_client_properties_status_info
{
    /**
     * A sequence of N Client Property IDs present within an element,
     * where N is the number of device property IDs included in the message.
     */
    uint16_t * client_property_ids;

    /** Number of Client Property IDs */
    uint16_t client_property_ids_count;
} rm_mesh_generic_prop_client_properties_status_info_t;

/*******************************************************************************************************************//**
 * @addtogroup RM_MESH_GENERIC_PROP_CLT
 * @{
 **********************************************************************************************************************/

/** BLE mesh generic prop instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_GENERIC_PROP_CLT_Open() is called. */
typedef struct st_rm_mesh_generic_prop_clt_instance_ctrl
{
    uint32_t open;                                // To check whether api has been opened or not.
    rm_ble_mesh_model_client_cfg_t const * p_cfg; // Pointer to initial configurations.
    rm_ble_mesh_access_model_handle_t      model_handle;
} rm_mesh_generic_prop_clt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_model_client_api_t g_rm_ble_mesh_model_client_on_rm_mesh_generic_prop_clt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_GENERIC_PROP_CLT_Open(rm_ble_mesh_model_client_ctrl_t * const      p_ctrl,
                                        rm_ble_mesh_model_client_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_Close(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_GetModelHandle(rm_ble_mesh_model_client_ctrl_t * const   p_ctrl,
                                                  rm_ble_mesh_access_model_handle_t * const model_handle);

fsp_err_t RM_MESH_GENERIC_PROP_CLT_SetModelHandle(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                  rm_ble_mesh_access_model_handle_t       model_handle);

fsp_err_t RM_MESH_GENERIC_PROP_CLT_SendReliablePdu(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                   uint32_t                                req_opcode,
                                                   void const * const                      parameter,
                                                   uint32_t                                rsp_opcode);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_UserPropertiesGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_UserPropertyGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                   void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_UserPropertySet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                   void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_UserPropertySetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                                 void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_AdminPropertiesGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_AdminPropertyGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                    void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_AdminPropertySet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                    void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_AdminPropertySetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                                  void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_ManufacturerPropertiesGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_ManufacturerPropertyGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                           void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_ManufacturerPropertySet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                           void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_ManufacturerPropertySetUnacknowledged(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                                         void const * const                      p_parameter);
fsp_err_t RM_MESH_GENERIC_PROP_CLT_ClientPropertiesGet(rm_ble_mesh_model_client_ctrl_t * const p_ctrl,
                                                       void const * const                      p_parameter);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_GENERIC_PROP_CLT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MESH_GENERIC_PROP_CLT_H
