/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @addtogroup BLE_ABS BLE_ABS
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_ABS_H
#define RM_BLE_ABS_H

#include "bsp_api.h"

#include "rm_ble_abs_cfg.h"
#include "rm_ble_abs_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BLE_ABS_CODE_VERSION_MAJOR                    (1U)
#define BLE_ABS_CODE_VERSION_MINOR                    (0U)

#define BLE_ABS_EVENT_NOTIFY_CONNECTION_START_POS     (0)
#define BLE_ABS_EVENT_NOTIFY_ADVERTISING_POS          (1)
#define BLE_ABS_EVENT_NOTIFY_SCANNING_POS             (2)
#define BLE_ABS_EVENT_NOTIFY_INITIATING_START_POS     (3)
#define BLE_ABS_EVENT_NOTIFY_CONNECTION_CLOSE_POS     (4)
#define BLE_ABS_EVENT_NOTIFY_ADVERTISING_CLOSE_POS    (5)
#define BLE_ABS_EVENT_NOTIFY_SCANNING_CLOSE_POS       (6)
#define BLE_ABS_EVENT_NOTIFY_INITIATING_CLOSE_POS     (7)
#define BLE_ABS_EVENT_NOTIFY_DEEP_SLEEP_START_POS     (8)
#define BLE_ABS_EVENT_NOTIFY_DEEP_SLEEP_WAKEUP_POS    (9)

#define BLE_EVENT_NOTIFY_ENABLE_VAL                   (                                                       \
        ((BLE_ABS_CFG_EVENT_NOTIFY_CONNECTION_START & 0x1U) << BLE_ABS_EVENT_NOTIFY_CONNECTION_START_POS) |   \
        ((BLE_ABS_CFG_EVENT_NOTIFY_CONNECTION_CLOSE & 0x1U) << BLE_ABS_EVENT_NOTIFY_CONNECTION_CLOSE_POS) |   \
        ((BLE_ABS_CFG_EVENT_NOTIFY_ADVERTISING_START & 0x1U) << BLE_ABS_EVENT_NOTIFY_ADVERTISING_POS) |       \
        ((BLE_ABS_CFG_EVENT_NOTIFY_ADVERTISING_CLOSE & 0x1U) << BLE_ABS_EVENT_NOTIFY_ADVERTISING_CLOSE_POS) | \
        ((BLE_ABS_CFG_EVENT_NOTIFY_SCANNING_START & 0x1U) << BLE_ABS_EVENT_NOTIFY_SCANNING_POS) |             \
        ((BLE_ABS_CFG_EVENT_NOTIFY_SCANNING_CLOSE & 0x1U) << BLE_ABS_EVENT_NOTIFY_SCANNING_CLOSE_POS) |       \
        ((BLE_ABS_CFG_EVENT_NOTIFY_INITIATING_START & 0x1U) << BLE_ABS_EVENT_NOTIFY_INITIATING_START_POS) |   \
        ((BLE_ABS_CFG_EVENT_NOTIFY_INITIATING_CLOSE & 0x1U) << BLE_ABS_EVENT_NOTIFY_INITIATING_CLOSE_POS) |   \
        ((BLE_ABS_CFG_EVENT_NOTIFY_DEEP_SLEEP_START & 0x1U) << BLE_ABS_EVENT_NOTIFY_DEEP_SLEEP_START_POS) |   \
        ((BLE_ABS_CFG_EVENT_NOTIFY_DEEP_SLEEP_WAKEUP & 0x1U) << BLE_ABS_EVENT_NOTIFY_DEEP_SLEEP_WAKEUP_POS) | \
        (0x0))

/** The timer type. */
typedef enum
{
    BLE_TIMER_ONE_SHOT,                /**< One shot timer type  */
    BLE_TIMER_PERIODIC                 /**< Periodic timer type */
} e_ble_timer_type_t;

/** The timer callback invoked when the timer expired. */
typedef void (* ble_abs_timer_cb_t)(uint32_t timer_hdl);

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** advertising set parameters structure */
typedef struct st_abs_advertising_parameter
{
    union
    {
        ble_abs_legacy_advertising_parameter_t          legacy_advertising_parameter;          ///< Legacy advertising parameters.
        ble_abs_extend_advertising_parameter_t          extend_advertising_parameter;          ///< Extended advertising parameters.
        ble_abs_non_connectable_advertising_parameter_t non_connectable_advertising_parameter; ///< Non-Connectable advertising parameters.
        ble_abs_periodic_advertising_parameter_t        periodic_advertising_parameter;        ///< Periodic advertising parameters.
    } advertising_parameter;                                                                   ///< Advertising parameters.

    uint32_t advertising_status;                                                               ///< Advertising status.

    ble_device_address_t remote_device_address;                                                ///< Remote device address for direct advertising.
} abs_advertising_parameter_t;

/** scan parameters structure */
typedef struct st_abs_scan_parameter
{
    ble_abs_scan_parameter_t     scan_parameter;           ///< Scan parameters.
    ble_abs_scan_phy_parameter_t scan_phy_parameter_1M;    ///< 1M phy parameters for scan.
    ble_abs_scan_phy_parameter_t scan_phy_parameter_coded; ///< Coded phy parameters for scan. */
    uint32_t scan_status;                                  /* Scan status. */
} abs_scan_parameter_t;

typedef enum
{
    BLE_TIMER_STATUS_FREE,
    BLE_TIMER_STATUS_IDLE,
    BLE_TIMER_STATUS_STARTED,
    BLE_TIMER_STATUS_EXPIRED,
} ble_abs_timer_status_t;

typedef struct st_ble_abs_timer
{
    uint8_t            status;
    uint32_t           timer_hdl;
    uint32_t           timeout_ms;
    uint32_t           remaining_time_ms;
    uint8_t            type;
    ble_abs_timer_cb_t cb;
} ble_abs_timer_t;

/** BLE ABS private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_ABS_Open() is called. */
typedef struct st_ble_abs_instance_ctrl
{
    uint32_t     open;                                                              ///< Indicates whether the open() API has been successfully called.
    void const * p_context;                                                         ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    ble_gap_application_callback_t             abs_gap_callback;                    ///< GAP callback function
    ble_vendor_specific_application_callback_t abs_vendor_specific_callback;        ///< Vendor specific callback function
    uint32_t connection_timer_handle;                                               ///< Cancel a request for connection timer.
    uint32_t advertising_timer_handle;                                              ///< Advertising timer for legacy advertising
    abs_advertising_parameter_t advertising_sets[BLE_MAX_NO_OF_ADV_SETS_SUPPORTED]; ///< Advertising set information.
    abs_scan_parameter_t        abs_scan;                                           ///< Scan information.
    st_ble_dev_addr_t           loc_bd_addr;                                        ///< Local device address.
    uint8_t         privacy_mode;                                                   ///< Privacy mode.
    uint32_t        set_privacy_status;                                             ///< Local privacy status.
    ble_abs_timer_t timer[BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT];

    uint32_t current_timeout_ms;                                                    ///< Current timeout.
    uint32_t elapsed_timeout_ms;                                                    ///< Elapsed timeout.

    ble_abs_cfg_t const * p_cfg;                                                    ///< Pointer to the BLE ABS configuration block.
} ble_abs_instance_ctrl_t;

/******************************************************************************************************************//**
 * @typedef ble_mcu_clock_change_cb_t
 * @brief   ble_mcu_clock_change_cb_t is the callback function type to use CLKOUT_RF as the MCU main clock source.
 * @param none
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_mcu_clock_change_cb_t)(void);

/******************************************************************************************************************//**
 * @typedef ble_rf_notify_cb_t
 * @brief   ble_rf_notify_cb_t is the RF event notify callback function type.
 * @param[in] uint32_t     The infomation of RF event notification.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_rf_notify_cb_t)(uint32_t);

/******************************************************************************************************************//**
 *  @struct st_ble_rf_notify_t
 *  @brief  This structure is RF event notify management.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Set enable/disable of each RF event notification
     *  @details
     *      Bit0  Notify Connection event start(0:Disable/1:Enable)\n
     *      Bit1  Notify Advertising event start(0:Disable/1:Enable)\n
     *      Bit2  Notify Scanning event start(0:Disable/1:Enable)\n
     *      Bit3  Notify Initiating event start(0:Disable/1:Enable)\n
     *      Bit4  Notify Connection event close(0:Disable/1:Enable)\n
     *      Bit5  Notify Advertising event close(0:Disable/1:Enable)\n
     *      Bit6  Notify Scanning event close(0:Disable/1:Enable)\n
     *      Bit7  Notify Initiating event close(0:Disable/1:Enable)\n
     *      Bit8  Notify RF_DEEP_SLEEP event start(0:Disable/1:Enable)\n
     *      Bit9  Notify RF_DEEP_SLEEP event close(0:Disable/1:Enable)\n
     *      Other Bit: Reserved for future use.\n
     */
    uint32_t enable;

    /**
     *  @brief Set callback function pointer for RF event start
     */
    ble_rf_notify_cb_t start_cb;

    /**
     *  @brief Set callback function pointer for RF event close
     */
    ble_rf_notify_cb_t close_cb;

    /**
     *  @brief Set callback function pointer for RF_DEEP_SLEEP
     */
    ble_rf_notify_cb_t dsleep_cb;
} st_ble_rf_notify_t;

/* prototype */
void r_ble_rf_notify_event_start(uint32_t param);
void r_ble_rf_notify_event_close(uint32_t param);
void r_ble_rf_notify_deep_sleep(uint32_t param);

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ble_abs_api_t g_ble_abs_on_ble;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Open(ble_abs_ctrl_t * const p_ctrl, ble_abs_cfg_t const * const p_cfg);

fsp_err_t RM_BLE_ABS_Close(ble_abs_ctrl_t * const p_ctrl);

fsp_err_t RM_BLE_ABS_Reset(ble_abs_ctrl_t * const p_ctrl, ble_event_cb_t init_callback);

fsp_err_t RM_BLE_ABS_VersionGet(fsp_version_t * const p_version);

fsp_err_t RM_BLE_ABS_StartLegacyAdvertising(ble_abs_ctrl_t * const                               p_ctrl,
                                            ble_abs_legacy_advertising_parameter_t const * const p_advertising_parameter);

fsp_err_t RM_BLE_ABS_StartExtendedAdvertising(ble_abs_ctrl_t * const                               p_ctrl,
                                              ble_abs_extend_advertising_parameter_t const * const p_advertising_parameter);

fsp_err_t RM_BLE_ABS_StartNonConnectableAdvertising(
    ble_abs_ctrl_t * const                                        p_ctrl,
    ble_abs_non_connectable_advertising_parameter_t const * const p_advertising_parameter);

fsp_err_t RM_BLE_ABS_StartPeriodicAdvertising(ble_abs_ctrl_t * const                                 p_ctrl,
                                              ble_abs_periodic_advertising_parameter_t const * const p_advertising_parameter);

fsp_err_t RM_BLE_ABS_StartScanning(ble_abs_ctrl_t * const                 p_ctrl,
                                   ble_abs_scan_parameter_t const * const p_scan_parameter);

fsp_err_t RM_BLE_ABS_CreateConnection(ble_abs_ctrl_t * const                       p_ctrl,
                                      ble_abs_connection_parameter_t const * const p_connection_parameter);

fsp_err_t RM_BLE_ABS_SetLocalPrivacy(ble_abs_ctrl_t * const p_ctrl, uint8_t const * const p_lc_irk,
                                     uint8_t privacy_mode);

fsp_err_t RM_BLE_ABS_StartAuthentication(ble_abs_ctrl_t * const p_ctrl, uint16_t connection_handle);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_ABS_H

/*******************************************************************************************************************//**
 * @} (end addtogroup BLE_ABS)
 **********************************************************************************************************************/
