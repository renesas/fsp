/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_DSMIF_H
#define R_DSMIF_H

/*******************************************************************************************************************//**
 * @addtogroup DSMIF
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_adc_api.h"
#include "r_dsmif_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define DSMIF_MAX_NUM_CHANNELS    (3U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DSMIF clock selection. */
typedef enum e_dsmif_clock_selection
{
    DSMIF_CLOCK_SELECTION_PCLKA    = 0, ///< Select PCLKA as the DSMIF clock
    DSMIF_CLOCK_SELECTION_DSMIFCLK = 1, ///< Select DSMIFCLK as the DSMIF clock
    DSMIF_CLOCK_SELECTION_GPTCLK   = 2, ///< Select GPTCLK as the DSMIF clock
} dsmif_clock_selection_t;

/** Select the channel(s) for overcurrent sum error detection. */
typedef enum e_dsmif_overcurrent_sum_error_channel
{
    DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0_2 = 0, ///< Detects error of sum value of overcurrent data of CH0, CH1, CH2
    DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0_1 = 1, ///< Detects error of sum value of overcurrent data of CH0, CH1
    DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0   = 2, ///< Detects error of overcurrent data of CH0
    DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_1   = 3, ///< Detects error of overcurrent data of CH1
    DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_2   = 4, ///< Detects error of overcurrent data of CH2
} dsmif_overcurrent_sum_error_channel_t;

/** Select the channel(s) that are synchronized. */
typedef enum e_dsmif_channel_synchronization_mode
{
    DSMIF_CHANNEL_SYNCHRONIZATION_MODE_DISABLED    = 0, ///< Channels are not synchronized
    DSMIF_CHANNEL_SYNCHRONIZATION_MODE_CHANNEL_0_2 = 1, ///< Channel 0 and Channel 1 and Channel 2 are synchronized
    DSMIF_CHANNEL_SYNCHRONIZATION_MODE_CHANNEL_0_1 = 2, ///< Channel 0 and Channel 1 are synchronized
} dsmif_channel_synchronization_mode_t;

/* Select if the DSMIF clock signal is an input or output. */
typedef enum e_dsmif_clock_direction
{
    DSMIF_CLOCK_DIRECTION_SLAVE  = 0,  ///< Clock signal is input (slave operation)
    DSMIF_CLOCK_DIRECTION_MASTER = 1,  ///< Clock signal is output (master operation)
} dsmif_clock_direction_t;

/** Select the clock edge for sampling DSMIF data. */
typedef enum e_dsmif_clock_edge
{
    DSMIF_CLOCK_EDGE_NEGATIVE = 0,     ///< Data is sampled on the negative edge of clock signal
    DSMIF_CLOCK_EDGE_POSITIVE = 1,     ///< Data is sampled on the positive edge of clock signal
} dsmif_clock_edge_t;

/** Select the DSMIF filter order. */
typedef enum e_dsmif_filter_order
{
    DSMIF_FILTER_ORDER_3RD = 0,        ///< Filter order setting 3rd order
    DSMIF_FILTER_ORDER_1ST = 1,        ///< Filter order setting 1st order
    DSMIF_FILTER_ORDER_2ND = 2,        ///< Filter order setting 2nd order
} dsmif_filter_order_t;

/** Select the [MSB,LSB] that are copied from the filter output into the data register.  */
typedef enum e_dsmif_data_shift
{
    DSMIF_DATA_SHIFT_23_8 = 0,         ///< Data shift setting [23:8]
    DSMIF_DATA_SHIFT_22_7 = 1,         ///< Data shift setting [22:7]
    DSMIF_DATA_SHIFT_21_6 = 2,         ///< Data shift setting [21:6]
    DSMIF_DATA_SHIFT_20_5 = 3,         ///< Data shift setting [20:5]
    DSMIF_DATA_SHIFT_19_4 = 4,         ///< Data shift setting [19:4]
    DSMIF_DATA_SHIFT_18_3 = 5,         ///< Data shift setting [18:3]
    DSMIF_DATA_SHIFT_17_2 = 6,         ///< Data shift setting [17:2]
    DSMIF_DATA_SHIFT_16_1 = 7,         ///< Data shift setting [16:1]
    DSMIF_DATA_SHIFT_15_0 = 8,         ///< Data shift setting [15:0]
    DSMIF_DATA_SHIFT_14_0 = 9,         ///< Data shift setting [14:0]
    DSMIF_DATA_SHIFT_13_0 = 10,        ///< Data shift setting [13:0]
    DSMIF_DATA_SHIFT_12_0 = 11,        ///< Data shift setting [12:0]
    DSMIF_DATA_SHIFT_11_0 = 12,        ///< Data shift setting [11:0]
    DSMIF_DATA_SHIFT_10_0 = 13,        ///< Data shift setting [10:0]
    DSMIF_DATA_SHIFT_9_0  = 14,        ///< Data shift setting [9:0]
    DSMIF_DATA_SHIFT_8_0  = 15,        ///< Data shift setting [8:0]
    DSMIF_DATA_SHIFT_7_0  = 16,        ///< Data shift setting [7:0]
    DSMIF_DATA_SHIFT_6_0  = 17,        ///< Data shift setting [6:0]
    DSMIF_DATA_SHIFT_5_0  = 18,        ///< Data shift setting [5:0]
    DSMIF_DATA_SHIFT_4_0  = 19,        ///< Data shift setting [4:0]
} dsmif_data_shift_t;

/* Select the current data capture trigger. */
typedef enum e_dsmif_capture_trigger
{
    DSMIF_CAPTURE_TRIGGER_NONE = 0,    ///< Do not capture
    DSMIF_CAPTURE_TRIGGER_0    = 1,    ///< Select current data capture trigger 0
    DSMIF_CAPTURE_TRIGGER_1    = 2,    ///< Select current data capture trigger 1
    DSMIF_CAPTURE_TRIGGER_2    = 3,    ///< Select current data capture trigger 2
    DSMIF_CAPTURE_TRIGGER_3    = 4,    ///< Select current data capture trigger 3
    DSMIF_CAPTURE_TRIGGER_4    = 5,    ///< Select current data capture trigger 4
    DSMIF_CAPTURE_TRIGGER_5    = 6,    ///< Select current data capture trigger 5
} dsmif_capture_trigger_t;

/* Select the filter initialization trigger. */
typedef enum e_dsmif_filter_initialization_trigger
{
    DSMIF_FILTER_INITIALIZATION_TRIGGER_NONE = 0, ///< Do not initialize
    DSMIF_FILTER_INITIALIZATION_TRIGGER_0    = 1, ///< Select decimation dividing counter initialization trigger 0
    DSMIF_FILTER_INITIALIZATION_TRIGGER_1    = 2, ///< Select decimation dividing counter initialization trigger 1
    DSMIF_FILTER_INITIALIZATION_TRIGGER_2    = 3, ///< Select decimation dividing counter initialization trigger 2
} dsmif_filter_initialization_trigger_t;

/** Overcurrent window notification window mode setting [0,2]. */
typedef enum e_dsmif_overcurrent_window_notification_mode
{
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE_OUTSIDE = 0, ///< Overcurrent data <= lower limit, upper limit <= overcurrent data.
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE_INSIDE  = 1, ///< lower limit < overcurrent data < upper limit.
} dsmif_overcurrent_window_notification_mode_t;

/** Overcurrent window detection window mode setting for window notification 3. */
typedef enum e_dsmif_overcurrent_window_notification_mode3
{
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0             = 0x0, ///< Overcurrent detection window notification 0
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_1             = 0x1, ///< Overcurrent detection window notification 1
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_2             = 0x2, ///< Overcurrent detection window notification 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_OR_1        = 0x3, ///< Overcurrent detection window notification 0 OR 1
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_AND_1       = 0x4, ///< Overcurrent detection window notification 0 AND 1
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_OR_2        = 0x5, ///< Overcurrent detection window notification 0 OR 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_AND_2       = 0x6, ///< Overcurrent detection window notification 0 AND 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_1_OR_2        = 0x7, ///< Overcurrent detection window notification 1 OR 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_1_AND_2       = 0x8, ///< Overcurrent detection window notification 1 AND 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_OR_1_OR_2   = 0x9, ///< Overcurrent detection window notification 0 OR 1 OR 2
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_MODE3_0_AND_1_AND_2 = 0xA, ///< Overcurrent detection window notification 0 AND 1 AND 2
} dsmif_overcurrent_window_notification_mode3_t;

/** DSMIF Channel Overcurrent detect status. */
typedef enum e_dsmif_overcurrent_status
{
    DSMIF_OVERCURRENT_STATUS_CH0_LOWER_LIMIT_0 = 1 << 0U,  ///< Channel 0 overcurrent lower limit detection 0  flag
    DSMIF_OVERCURRENT_STATUS_CH1_LOWER_LIMIT_0 = 1 << 1U,  ///< Channel 1 overcurrent lower limit detection 0 flag
    DSMIF_OVERCURRENT_STATUS_CH2_LOWER_LIMIT_0 = 1 << 2U,  ///< Channel 2 overcurrent lower limit detection 0 flag
    DSMIF_OVERCURRENT_STATUS_CH0_UPPER_LIMIT_0 = 1 << 4U,  ///< Channel 0 overcurrent upper limit exceeded 0 flag
    DSMIF_OVERCURRENT_STATUS_CH1_UPPER_LIMIT_0 = 1 << 5U,  ///< Channel 1 overcurrent upper limit exceeded 0 flag
    DSMIF_OVERCURRENT_STATUS_CH2_UPPER_LIMIT_0 = 1 << 6U,  ///< Channel 2 overcurrent upper limit exceeded 0 flag
    DSMIF_OVERCURRENT_STATUS_CH0_LOWER_LIMIT_1 = 1 << 8U,  ///< Channel 0 overcurrent lower limit detection 1 flag
    DSMIF_OVERCURRENT_STATUS_CH1_LOWER_LIMIT_1 = 1 << 9U,  ///< Channel 1 overcurrent lower limit detection 1 flag
    DSMIF_OVERCURRENT_STATUS_CH2_LOWER_LIMIT_1 = 1 << 10U, ///< Channel 2 overcurrent lower limit detection 1 flag
    DSMIF_OVERCURRENT_STATUS_CH0_UPPER_LIMIT_1 = 1 << 12U, ///< Channel 0 overcurrent upper limit exceeded 1 flag
    DSMIF_OVERCURRENT_STATUS_CH1_UPPER_LIMIT_1 = 1 << 13U, ///< Channel 1 overcurrent upper limit exceeded 1 flag
    DSMIF_OVERCURRENT_STATUS_CH2_UPPER_LIMIT_1 = 1 << 14U, ///< Channel 2 overcurrent upper limit exceeded 1 flag
    DSMIF_OVERCURRENT_STATUS_CH0_LOWER_LIMIT_2 = 1 << 16U, ///< Channel 0 overcurrent lower limit detection 2 flag
    DSMIF_OVERCURRENT_STATUS_CH1_LOWER_LIMIT_2 = 1 << 17U, ///< Channel 1 overcurrent lower limit detection 2 flag
    DSMIF_OVERCURRENT_STATUS_CH2_LOWER_LIMIT_2 = 1 << 18U, ///< Channel 2 overcurrent lower limit detection 2 flag
    DSMIF_OVERCURRENT_STATUS_CH0_UPPER_LIMIT_2 = 1 << 20U, ///< Channel 0 overcurrent upper limit exceeded 2 flag
    DSMIF_OVERCURRENT_STATUS_CH1_UPPER_LIMIT_2 = 1 << 21U, ///< Channel 1 overcurrent upper limit exceeded 2 flag
    DSMIF_OVERCURRENT_STATUS_CH2_UPPER_LIMIT_2 = 1 << 22U, ///< Channel 2 overcurrent upper limit exceeded 2 flag
} dsmif_overcurrent_status_t;

/** DSMIF Channel Short circuit detect status. */
typedef enum e_dsmif_short_circuit_status
{
    DSMIF_SHORT_CIRCUIT_STATUS_CH0 = 1 << 0U, ///< Channel 0 short circuit detection flag
    DSMIF_SHORT_CIRCUIT_STATUS_CH1 = 1 << 1U, ///< Channel 1 short circuit detection flag
    DSMIF_SHORT_CIRCUIT_STATUS_CH2 = 1 << 2U, ///< Channel 2 short circuit detection flag
} dsmif_short_circuit_status_t;

/** DSMIF Overcurrent Sum detect status. */
typedef enum e_dsmif_overcurrent_sum_status
{
    DSMIF_OVERCURRENT_SUM_STATUS_LOWER_LIMIT = 1 << 0U, ///< Overcurrent sum error lower limit detection flag
    DSMIF_OVERCURRENT_SUM_STATUS_UPPER_LIMIT = 1 << 1U, ///< Overcurrent sum error upper limit detection flag
} dsmif_overcurrent_sum_status_t;

/** DSMIF Overcurrent Window detect status. */
typedef enum e_dsmif_overcurrent_window_notification_status
{
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH0_0 = 1 << 0U,  ///< Channel 0 overcurrent detection window notification 0 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH1_0 = 1 << 1U,  ///< Channel 1 overcurrent detection window notification 0 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH2_0 = 1 << 2U,  ///< Channel 2 overcurrent detection window notification 0 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH0_1 = 1 << 4U,  ///< Channel 0 overcurrent detection window notification 1 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH1_1 = 1 << 5U,  ///< Channel 1 overcurrent detection window notification 1 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH2_1 = 1 << 6U,  ///< Channel 2 overcurrent detection window notification 1 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH0_2 = 1 << 8U,  ///< Channel 0 overcurrent detection window notification 2 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH1_2 = 1 << 9U,  ///< Channel 1 overcurrent detection window notification 2 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH2_2 = 1 << 10U, ///< Channel 2 overcurrent detection window notification 2 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH0_3 = 1 << 12U, ///< Channel 0 overcurrent detection window notification 3 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH1_3 = 1 << 13U, ///< Channel 1 overcurrent detection window notification 3 flag
    DSMIF_OVERCURRENT_WINDOW_NOTIFICATION_STATUS_CH2_3 = 1 << 14U, ///< Channel 2 overcurrent detection window notification 3 flag
} dsmif_overcurrent_window_notification_status_t;

/** Channel clock configuration */
typedef struct st_dsmif_clock_cfg
{
    dsmif_clock_direction_t direction; ///< A/D conversion clock master/slave switching
    dsmif_clock_edge_t      edge;      ///< Sampling edge selection
    uint8_t                 divider;   ///< A/D conversion clock division ratio
} dsmif_clock_cfg_t;

/** Filter configuration */
typedef struct st_dsmif_filter_cfg
{
    dsmif_filter_order_t filter_order;     ///< Sinc filter order (1st, 2nd, or 3rd)
    dsmif_data_shift_t   data_shift;       ///< Data shift setting
    uint8_t              decimation_count; ///< Decimation count [0,255]
} dsmif_filter_cfg_t;

/** Event trigger configuration.  */
typedef struct st_dsmif_trigger_cfg
{
    dsmif_capture_trigger_t               capture_trigger_a;             ///< Current capture trigger A selection.
    dsmif_capture_trigger_t               capture_trigger_b;             ///< Current capture trigger B selection.
    dsmif_filter_initialization_trigger_t filter_initialization_trigger; ///< Current measurement filter initialization trigger selection.
    dsmif_clock_edge_t filter_initialization_edge;                       ///< Current measurement filter initialization trigger edge selection.
} dsmif_trigger_cfg_t;

/** Channel interrupt configuration. */
typedef struct st_dsmif_interrupt_cfg
{
    IRQn_Type current_data_update_irq; ///< Channel current data update interrupt request.
    uint8_t   current_data_update_ipl; ///< Channel current data update interrupt priority.
    IRQn_Type capture_data_a_irq;      ///< Channel capture data a interrupt request.
    uint8_t   capture_data_a_ipl;      ///< Channel capture data a interrupt priority.
    IRQn_Type capture_data_b_irq;      ///< Channel capture data b interrupt request.
    uint8_t   capture_data_b_ipl;      ///< Channel capture data b interrupt priority.
} dsmif_interrupt_cfg_t;

/** Channel error configuration:
 *  - Overcurrent upper/lower limit error detection 0,1,2
 *  - Overcurrent window notification 0,1,2,3
 *  - Short circuit low/high detection
 */
typedef struct st_dsmif_error_detection_cfg
{
    union
    {
        uint8_t overcurrent_detection_enable; ///< Overcurrent enable mask

        struct
        {
            uint8_t lower_limit_enable_0 : 1; ///< Overcurrent detection 0 lower limit enable
            uint8_t upper_limit_enable_0 : 1; ///< Overcurrent detection 0 upper limit enable
            uint8_t lower_limit_enable_1 : 1; ///< Overcurrent detection 1 lower limit enable
            uint8_t upper_limit_enable_1 : 1; ///< Overcurrent detection 1 upper limit enable
            uint8_t lower_limit_enable_2 : 1; ///< Overcurrent detection 2 lower limit enable
            uint8_t upper_limit_enable_2 : 1; ///< Overcurrent detection 2 upper limit enable
            uint8_t                      : 2; // Reserved
        } overcurrent_detection_enable_b;
    };

    union
    {
        uint8_t overcurrent_window_notification_enable; ///< Overcurrent window error enable mask

        struct
        {
            uint8_t enable_0 : 1;                       ///< Overcurrent window notification 0 enable
            uint8_t enable_1 : 1;                       ///< Overcurrent window notification 1 enable
            uint8_t enable_2 : 1;                       ///< Overcurrent window notification 2 enable
            uint8_t enable_3 : 1;                       ///< Overcurrent window notification 3 enable
            uint8_t          : 4;                       // Reserved
        } overcurrent_window_notification_enable_b;
    };

    union
    {
        uint8_t overcurrent_window_notification_mode; ///< Overcurrent window error mode mask

        struct
        {
            uint8_t mode_0 : 1;                       ///< Overcurrent window notification mode 0
            uint8_t mode_1 : 1;                       ///< Overcurrent window notification mode 1
            uint8_t mode_2 : 1;                       ///< Overcurrent window notification mode 2
            uint8_t mode_3 : 4;                       ///< Overcurrent window notification mode 3
            uint8_t        : 1;                       // Reserved
        } overcurrent_window_notification_mode_b;
    };

    bool     short_circuit_detection_enable;          ///< Enable short circuit detection
    uint32_t short_circuit_detection_low_count;       ///< Short circuit low count
    uint32_t short_circuit_detection_high_count;      ///< Short circuit high count

    uint32_t overcurrent_lower_limit[3];              ///< Overcurrent lower limit settings
    uint32_t overcurrent_upper_limit[3];              ///< Overcurrent upper limit settings

    dsmif_filter_cfg_t overcurrent_filter_cfg;        ///< Sinc filter configuration for overcurrent detection.
} dsmif_error_detection_cfg_t;

/** Error status. */
typedef struct st_dsmif_error_status
{
    dsmif_overcurrent_status_t                     channel_overcurrent_status;        ///< Channel Overcurrent state
    dsmif_short_circuit_status_t                   channel_short_circuit_status;      ///< Channel Short circuit state
    dsmif_overcurrent_sum_status_t                 overcurrent_sum_status;            ///< Overcurrent Sum state
    dsmif_overcurrent_window_notification_status_t channel_overcurrent_window_status; ///< Channel Overcurrent Window State
} dsmif_error_status_t;

/** Channel configuration. */
typedef struct st_dsmif_channel_cfg
{
    dsmif_clock_cfg_t     clock_cfg;                 ///< Channel clock configuration
    dsmif_filter_cfg_t    filter_cfg;                ///< Channel sinc filter configuration
    dsmif_trigger_cfg_t   trigger_cfg;               ///< Channel event trigger configuration
    dsmif_interrupt_cfg_t irq_cfg;                   ///< Channel interrupt configuration

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    dsmif_error_detection_cfg_t error_detection_cfg; ///< Channel error detection configuration
#endif
} dsmif_channel_cfg_t;

/** DSMIF configuration extension. This extension is required and must be provided in dsmif_cfg_t::p_extend. */
typedef struct st_dsmif_extended_cfg
{
    dsmif_clock_selection_t     clock_selection;                        ///< DSMIF core clock selection
    uint32_t                    channel_mask;                           ///< Channel bitmask
    dsmif_channel_cfg_t const * p_channel_cfgs[DSMIF_MAX_NUM_CHANNELS]; ///< Configuration for each channel, set to NULL if unused

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    union
    {
        uint8_t overcurrent_sum_error_enable;
        struct
        {
            uint8_t lower_limit_enable : 1;                              ///< Overcurrent sum error lower limit error
            uint8_t upper_limit_enable : 1;                              ///< Overcurrent sum error upper limit error
        } overcurrent_sum_error_enable_b;
    };

    dsmif_overcurrent_sum_error_channel_t overcurrent_sum_error_channel; ///< Overcurrent sum error detect mode setting bit

    uint32_t overcurrent_sum_error_lower_limit;                          ///< Overcurrent Sum Error Detect Low Threshold Register
    uint32_t overcurrent_sum_error_upper_limit;                          ///< Overcurrent Sum Error Detect High Threshold Register
#endif

    dsmif_channel_synchronization_mode_t synchronization_mode;           ///< Channel synchronization mode
    IRQn_Type common_current_data_irq;                                   ///< Common current data interrupt request
    uint8_t   common_current_data_ipl;                                   ///< Common current data interrupt priority
    IRQn_Type common_capture_data_a_irq;                                 ///< Channel capture data a interrupt request
    uint8_t   common_capture_data_a_ipl;                                 ///< Channel capture data a interrupt priority
    IRQn_Type common_capture_data_b_irq;                                 ///< Channel capture data b interrupt request
    uint8_t   common_capture_data_b_ipl;                                 ///< Channel capture data b interrupt priority

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    IRQn_Type common_error_irq;                                          ///< Common error interrupt request
    uint8_t   common_error_ipl;                                          ///< Common error interrupt priority
#endif
} dsmif_extended_cfg_t;

/** DSMIF instance control block. DO NOT INITIALIZE. */
typedef struct
{
    R_DSMIF0_Type   * p_reg;                    // Base register for this unit
    adc_cfg_t const * p_cfg;
    uint32_t          open;                     // Indicates whether the open() API has been successfully called.

    void (* p_callback)(adc_callback_args_t *); // Pointer to callback that is called when an dsmif_event_t occurs.
    adc_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void * p_context;
} dsmif_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_dsmif;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_DSMIF_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_extend);
fsp_err_t R_DSMIF_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask);
fsp_err_t R_DSMIF_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_ScanStatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_DSMIF_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_DSMIF_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_DSMIF_Calibrate(adc_ctrl_t * p_ctrl, void const * p_extend);
fsp_err_t R_DSMIF_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset);
fsp_err_t R_DSMIF_CallbackSet(adc_ctrl_t * const          p_ctrl,
                              void (                    * p_callback)(adc_callback_args_t *),
                              void * const                p_context,
                              adc_callback_args_t * const p_callback_memory);
fsp_err_t R_DSMIF_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_InfoGet(adc_ctrl_t * const p_ctrl, adc_info_t * const p_adc_info);

fsp_err_t R_DSMIF_ErrorDetectionEnable(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_ErrorStatusGet(adc_ctrl_t * p_ctrl, dsmif_error_status_t * p_error_status);

/*******************************************************************************************************************//**
 * @} (end defgroup DSMIF)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
