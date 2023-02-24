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

#ifndef RM_MESH_HEALTH_SERVER_H
#define RM_MESH_HEALTH_SERVER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ble_mesh_health_server_api.h"
#include "rm_ble_mesh_access.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** This section lists the Fault Values defined for Health Model */
/** Health Model - Fault Values */
/** No Fault */
typedef enum e_rm_mesh_health_server_fault_value
{
    RM_MESH_HEALTH_SERVER_FAULT_NO_FAULT = 0x00,

    /** Battery Low Warning */
    RM_MESH_HEALTH_SERVER_FAULT_BATTERY_LOW_WARNING = 0x01,

    /** Battery Low Error */
    RM_MESH_HEALTH_SERVER_FAULT_BATTERY_LOW_ERROR = 0x02,

    /** Supply Voltage Too Low Warning */
    RM_MESH_HEALTH_SERVER_FAULT_SUPPLY_VOLTAGE_TOO_LOW_WARNING = 0x03,

    /** Supply Voltage Too Low Error */
    RM_MESH_HEALTH_SERVER_FAULT_SUPPLY_VOLTAGE_TOO_LOW_ERROR = 0x04,

    /** Supply Voltage Too High Warning */
    RM_MESH_HEALTH_SERVER_FAULT_SUPPLY_VOLTAGE_TOO_HIGH_WARNING = 0x05,

    /** Supply Voltage Too High Error */
    RM_MESH_HEALTH_SERVER_FAULT_SUPPLY_VOLTAGE_TOO_HIGH_ERROR = 0x06,

    /** Power Supply Interrupted Warning */
    RM_MESH_HEALTH_SERVER_FAULT_POWER_SUPPLY_INTERRUPTED_WARNING = 0x07,

    /** Power Supply Interrupted Error */
    RM_MESH_HEALTH_SERVER_FAULT_POWER_SUPPLY_INTERRUPTED_ERROR = 0x08,

    /** No Load Warning */
    RM_MESH_HEALTH_SERVER_FAULT_NO_LOAD_WARNING = 0x09,

    /** No Load Error */
    RM_MESH_HEALTH_SERVER_FAULT_NO_LOAD_ERROR = 0x0A,

    /** Overload Warning */
    RM_MESH_HEALTH_SERVER_FAULT_OVERLOAD_WARNING = 0x0B,

    /** Overload Error */
    RM_MESH_HEALTH_SERVER_FAULT_OVERLOAD_ERROR = 0x0C,

    /** Overheat Warning */
    RM_MESH_HEALTH_SERVER_FAULT_OVERHEAT_WARNING = 0x0D,

    /** Overheat Error */
    RM_MESH_HEALTH_SERVER_FAULT_OVERHEAT_ERROR = 0x0E,

    /** Condensation Warning */
    RM_MESH_HEALTH_SERVER_FAULT_CONDENSATION_WARNING = 0x0F,

    /** Condensation Error */
    RM_MESH_HEALTH_SERVER_FAULT_CONDENSATION_ERROR = 0x10,

    /** Vibration Warning */
    RM_MESH_HEALTH_SERVER_FAULT_VIBRATION_WARNING = 0x11,

    /** Vibration Error */
    RM_MESH_HEALTH_SERVER_FAULT_VIBRATION_ERROR = 0x12,

    /** Configuration Warning */
    RM_MESH_HEALTH_SERVER_FAULT_CONFIGURATION_WARNING = 0x13,

    /** Configuration Error */
    RM_MESH_HEALTH_SERVER_FAULT_CONFIGURATION_ERROR = 0x14,

    /** Element Not Calibrated Warning */
    RM_MESH_HEALTH_SERVER_FAULT_ELEMENT_NOT_CALIBRATED_WARNING = 0x15,

    /** Element Not Calibrated Error */
    RM_MESH_HEALTH_SERVER_FAULT_ELEMENT_NOT_CALIBRATED_ERROR = 0x16,

    /** Memory Warning */
    RM_MESH_HEALTH_SERVER_FAULT_MEMORY_WARNING = 0x17,

    /** Memory Error */
    RM_MESH_HEALTH_SERVER_FAULT_MEMORY_ERROR = 0x18,

    /** Self-Test Warning */
    RM_MESH_HEALTH_SERVER_FAULT_SELF_TEST_WARNING = 0x19,

    /** Self-Test Error */
    RM_MESH_HEALTH_SERVER_FAULT_SELF_TEST_ERROR = 0x1A,

    /** Input Too Low Warning */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_TOO_LOW_WARNING = 0x1B,

    /** Input Too Low Error */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_TOO_LOW_ERROR = 0x1C,

    /** Input Too High Warning */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_TOO_HIGH_WARNING = 0x1D,

    /** Input Too High Error */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_TOO_HIGH_ERROR = 0x1E,

    /** Input No Change Warning */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_NO_CHANGE_WARNING = 0x1F,

    /** Input No Change Error */
    RM_MESH_HEALTH_SERVER_FAULT_INPUT_NO_CHANGE_ERROR = 0x20,

    /** Actuator Blocked Warning */
    RM_MESH_HEALTH_SERVER_FAULT_ACTUATOR_BLOCKED_WARNING = 0x21,

    /** Actuator Blocked Error */
    RM_MESH_HEALTH_SERVER_FAULT_ACTUATOR_BLOCKED_ERROR = 0x22,

    /** Housing Opened Warning */
    RM_MESH_HEALTH_SERVER_FAULT_HOUSING_OPENED_WARNING = 0x23,

    /** Housing Opened Error */
    RM_MESH_HEALTH_SERVER_FAULT_HOUSING_OPENED_ERROR = 0x24,

    /** Tamper Warning */
    RM_MESH_HEALTH_SERVER_FAULT_TAMPER_WARNING = 0x25,

    /** Tamper Error */
    RM_MESH_HEALTH_SERVER_FAULT_TAMPER_ERROR = 0x26,

    /** Device Moved Warning */
    RM_MESH_HEALTH_SERVER_FAULT_DEVICE_MOVED_WARNING = 0x27,

    /** Device Moved Error */
    RM_MESH_HEALTH_SERVER_FAULT_DEVICE_MOVED_ERROR = 0x28,

    /** Device Dropped Warning */
    RM_MESH_HEALTH_SERVER_FAULT_DEVICE_DROPPED_WARNING = 0x29,

    /** Device Dropped Error */
    RM_MESH_HEALTH_SERVER_FAULT_DEVICE_DROPPED_ERROR = 0x2A,

    /** Overflow Warning */
    RM_MESH_HEALTH_SERVER_FAULT_OVERFLOW_WARNING = 0x2B,

    /** Overflow Error */
    RM_MESH_HEALTH_SERVER_FAULT_OVERFLOW_ERROR = 0x2C,

    /** Empty Warning */
    RM_MESH_HEALTH_SERVER_FAULT_EMPTY_WARNING = 0x2D,

    /** Empty Error */
    RM_MESH_HEALTH_SERVER_FAULT_EMPTY_ERROR = 0x2E,

    /** Internal Bus Warning */
    RM_MESH_HEALTH_SERVER_FAULT_INTERNAL_BUS_WARNING = 0x2F,

    /** Internal Bus Error */
    RM_MESH_HEALTH_SERVER_FAULT_INTERNAL_BUS_ERROR = 0x30,

    /** Mechanism Jammed Warning */
    RM_MESH_HEALTH_SERVER_FAULT_MECHANISM_JAMMED_WARNING = 0x31,

    /** Mechanism Jammed Error*/
    RM_MESH_HEALTH_SERVER_FAULT_MECHANISM_JAMMED_ERROR = 0x32,

    /* 0x33 - 0x7F: Reserved for Future Use */
    /* 0x80 - 0xFF: Vendor Specific Warning / Error */
} rm_mesh_health_server_fault_value_t;

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_MESH_HEALTH_SRV
 * @{
 **********************************************************************************************************************/

/** BLE mesh health server instance control block. DO NOT INITIALIZE. Initialization occurs when RM_MESH_HEALTH_SERVER_Open() is called. */
typedef struct st_rm_mesh_health_server_instance_ctrl
{
    uint32_t open;                                 // To check whether api has been opened or not.
    rm_ble_mesh_access_model_handle_t model_handle;
    rm_ble_mesh_access_model_handle_t setup_server_handle;

    rm_ble_mesh_health_server_cfg_t const * p_cfg; // Pointer to initial configurations.
} rm_mesh_health_server_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_health_server_api_t g_rm_ble_mesh_health_server_on_rm_mesh_health_srv;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_MESH_HEALTH_SERVER_Open(rm_ble_mesh_health_server_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_health_server_cfg_t const * const p_cfg);
fsp_err_t RM_MESH_HEALTH_SERVER_Close(rm_ble_mesh_health_server_ctrl_t * const p_ctrl);

fsp_err_t RM_MESH_HEALTH_SERVER_ReportFault(rm_ble_mesh_health_server_ctrl_t * const        p_ctrl,
                                            const rm_ble_mesh_access_model_handle_t * const model_handle,
                                            uint8_t                                         test_id,
                                            uint16_t                                        company_id,
                                            uint8_t                                         fault_code);

fsp_err_t RM_MESH_HEALTH_SERVER_PublishCurrentStatus(rm_ble_mesh_health_server_ctrl_t * const p_ctrl,
                                                     uint8_t                                * status,
                                                     uint16_t                                 length);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_MESH_HEALTH_SRV)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_HEALTH_SERVER_H
