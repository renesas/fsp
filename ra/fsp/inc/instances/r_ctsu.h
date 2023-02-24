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

/*******************************************************************************************************************//**
 * @addtogroup CTSU 
 * @{
 **********************************************************************************************************************/

#ifndef R_CTSU_H
#define R_CTSU_H

#include "bsp_api.h"
#ifdef QE_TOUCH_CONFIGURATION
 #include "qe_touch_define.h"
#endif
#include "r_ctsu_cfg.h"
#include "r_ctsu_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER


/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #define CTSU_CORRECTION_POINT_NUM        (12) ///< number of correction table
 #define CTSU_CORRCFC_POINT_NUM           (5)  ///< number of CFC correction table

 #define CTSU_DIAG_HIGH_CURRENT_SOURCE    (16) ///< number of high current source table at Diagnosis
 #define CTSU_DIAG_LOW_CURRENT_SOURCE     (10) ///< number of low current source table at Diagnosis
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CTSU run state */
typedef enum e_ctsu_state
{
    CTSU_STATE_INIT,                   ///< Not open.
    CTSU_STATE_IDLE,                   ///< Opened.
    CTSU_STATE_SCANNING,               ///< Scanning now.
    CTSU_STATE_SCANNED                 ///< Scan end.
} ctsu_state_t;

/** CTSU Initial offset tuning status */
typedef enum e_ctsu_tuning
{
    CTSU_TUNING_INCOMPLETE,            ///< Initial offset tuning incomplete
    CTSU_TUNING_COMPLETE               ///< Initial offset tuning complete
} ctsu_tuning_t;

/** CTSU Correction status */
typedef enum e_ctsu_correction_status
{
    CTSU_CORRECTION_INIT,              ///< Correction initial status.
    CTSU_CORRECTION_RUN,               ///< Correction scan running.
    CTSU_CORRECTION_COMPLETE,          ///< Correction complete.
    CTSU_CORRECTION_ERROR              ///< Correction error.
} ctsu_correction_status_t;

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** CTSU Diagnosis status */
typedef enum e_ctsu_diagnosis_status
{
    CTSU_DIAG_INIT,                    ///< Diagnosis initial status.
    CTSU_DIAG_OVER_VOLTAGE,            ///< Diagnosis of over_voltage running.
    CTSU_DIAG_CCO_HIGH,                ///< Diagnosis of oscillator 19.2uA running.
    CTSU_DIAG_CCO_LOW,                 ///< Diagnosis of oscillator 2.4uA running.
    CTSU_DIAG_SSCG,                    ///< Diagnosis of sscg_oscillator running.
    CTSU_DIAG_DAC,                     ///< Diagnosis of dac running.
    CTSU_DIAG_COMPLETE                 ///< Diagnosis complete.
} ctsu_diagnosis_status_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** CTSU Diagnosis status */
typedef enum e_ctsu_diagnosis_state
{
    CTSU_DIAG_INIT,                    ///< Diagnosis initial status.
    CTSU_DIAG_OUTPUT_VOLTAGE,          ///< Diagnosis of output voltage running.
    CTSU_DIAG_OVER_VOLTAGE,            ///< Diagnosis of over voltage running.
    CTSU_DIAG_OVER_CURRENT,            ///< Diagnosis of over current running.
    CTSU_DIAG_LOAD_RESISTANCE,         ///< Diagnosis of load resistance running.
    CTSU_DIAG_CURRENT_SOURCE,          ///< Diagnosis of current source running.
    CTSU_DIAG_SENSCLK,                 ///< Diagnosis of SENCLK running.
    CTSU_DIAG_SUCLK,                   ///< Diagnosis of SUCLK running.
    CTSU_DIAG_CLOCK_RECOVERY,          ///< Diagnosis of clock recovery running.
    CTSU_DIAG_CFC,                     ///< Diagnosis of CFC running.
    CTSU_DIAG_COMPLETE                 ///< Diagnosis complete.
} ctsu_diagnosis_state_t;
 #endif
#endif

/** CTSU range definition */
typedef enum e_ctsu_range
{
    CTSU_RANGE_20UA,                   ///< 20uA mode
    CTSU_RANGE_40UA,                   ///< 40uA mode
    CTSU_RANGE_80UA,                   ///< 80uA mode
    CTSU_RANGE_160UA,                  ///< 160uA mode
    CTSU_RANGE_NUM                     ///< number of range
} ctsu_range_t;

/** CTSUWR write register value */
typedef struct st_ctsu_wr
{
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t ctsuso;                   ///< Copy from ((sdpa << 24) | (ssdiv << 20) | (snum << 10) | so) by Open API.
#else
    uint16_t ctsussc;                  ///< Copy from (ssdiv << 8) by Open API.
    uint16_t ctsuso0;                  ///< Copy from ((snum << 10) | so) by Open API.
    uint16_t ctsuso1;                  ///< Copy from (sdpa << 8) by Open API. ICOG and RICOA is set recommend value.
#endif
} ctsu_ctsuwr_t;

/** Scan buffer data formats (Self) */
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_self_buf_t;
#else
typedef struct st_ctsu_self_buf
{
    uint16_t sen;                      ///< Sensor counter data
    uint16_t ref;                      ///< Reference counter data (Not used)
} ctsu_self_buf_t;
#endif

typedef struct st_ctsu_data
{
    uint16_t decimal_point_data;
    uint16_t int_data;
} ctsu_data_t;

/** Scan buffer data formats (Mutual) */
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_mutual_buf_t;
#else
typedef struct st_ctsu_mutual_buf
{
    uint16_t pri_sen;                  ///< Primary sensor data
    uint16_t pri_ref;                  ///< Primary reference data (Not used)
    uint16_t snd_sen;                  ///< Secondary sensor data
    uint16_t snd_ref;                  ///< Secondary reference data (Not used)
} ctsu_mutual_buf_t;
#endif

/** Correction information */
typedef struct st_ctsu_correction_info
{
    ctsu_correction_status_t status;                               ///< Correction status
    ctsu_ctsuwr_t            ctsuwr;                               ///< Correction scan parameter
    volatile ctsu_self_buf_t scanbuf;                              ///< Correction scan buffer
#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    uint16_t scan_index;                                           ///< Scan point index
    uint16_t update_counter;                                       ///< Coefficient update counter
    uint16_t ex_base_value;                                        ///< Value of external registance measurement
    uint8_t  suadj0;                                               ///< Stored SUADJ0 value
 #endif
    uint16_t base_value[CTSU_RANGE_NUM];                           ///< Value of internal registance measurement
    uint16_t error_rate[CTSU_RANGE_NUM];                           ///< Error rate of base vs DAC
    uint16_t range_ratio[CTSU_RANGE_NUM - 1];                      ///< Ratio between 160uA range and other ranges
    uint16_t dac_value[CTSU_CORRECTION_POINT_NUM];                 ///< Value of internal DAC measurement
    uint16_t ref_value[CTSU_RANGE_NUM][CTSU_CORRECTION_POINT_NUM]; ///< Value of reference
#else
    uint16_t first_val;                                            ///< 1st correction value
    uint16_t second_val;                                           ///< 2nd correction value
    uint32_t first_coefficient;                                    ///< 1st correction coefficient
    uint32_t second_coefficient;                                   ///< 2nd correction coefficient
    uint32_t ctsu_clock;                                           ///< CTSU clock [MHz]
#endif
} ctsu_correction_info_t;

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)

/** CFC correction information */
typedef struct st_ctsu_corrcfc_info
{
    ctsu_correction_status_t status;                                              ///< Correction status
    ctsu_ctsuwr_t            ctsuwr;                                              ///< Correction scan parameter
    volatile ctsu_self_buf_t scanbuf[CTSU_CFG_NUM_CFC];                           ///< Correction scan buffer
    uint16_t                 base_value[CTSU_CFG_NUM_CFC];                        ///< Value of CFC circuit measurement
    uint16_t                 error_rate[CTSU_CFG_NUM_CFC];                        ///< Error rate of base vs DAC
    uint16_t                 dac_value[CTSU_CFG_NUM_CFC][CTSU_CORRCFC_POINT_NUM]; ///< Value of internal DAC measurement
    uint16_t                 ref_value[CTSU_CFG_NUM_CFC][CTSU_CORRCFC_POINT_NUM]; ///< Value of reference
    uint8_t  ts_table[CTSU_CFG_NUM_CFC];                                          ///< Number of TS terminal
    uint8_t  index;                                                               ///< Index of ts_table
    uint8_t  num_ts;                                                              ///< Number of CFC-TS for instance
    uint64_t stored_rx_bitmap;                                                    ///< Bitmap of registered CFC terminal
} ctsu_corrcfc_info_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** Correction information */
typedef struct st_ctsu_diag_info
{
    volatile ctsu_diagnosis_status_t state; ///< Diagnosis state
    ctsu_ctsuwr_t            ctsuwr;        ///< Correction scan parameter
    uint8_t                  loop_count;    ///< Diagnosis loop counter
    volatile ctsu_self_buf_t scanbuf;       ///< Diagnosis scan buffer
    uint16_t                 correct_data;  ///< Diagnosis correct value
    volatile uint8_t         icomp;         ///< Diagnosis icomp flag
    uint16_t                 cco_high;      ///< Diagnosis cco high count
    uint16_t                 cco_low;       ///< Diagnosis cco low count
    uint16_t                 sscg;          ///< Diagnosis sscg count
    uint16_t                 dac_cnt[6];    ///< Diagnosis dac count
    uint16_t                 so0_4uc_val;   ///< Diagnosis dac value
    uint16_t                 dac_init;      ///< Diagnosis dac
    ctsu_tuning_t            tuning;        ///< Diagnosis dac initial tuning flag
    int32_t                  tuning_diff;   ///< Diagnosis
} ctsu_diag_info_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** Correction information */
typedef struct st_ctsu_diag_info
{
    volatile ctsu_diagnosis_state_t state;                                                      ///< Diagnosis state
    ctsu_ctsuwr_t ctsuwr;                                                                       ///< Correction scan parameter
    uint8_t       lvmode;                                                                       ///< Diagnosis lv mode flag
    uint8_t       loop_count;                                                                   ///< Diagnosis loop counter
    uint32_t      ctsuscnt[3];                                                                  ///< Diagnosis raw data (suclk count value & sens count value)
    uint32_t      error_registance[CTSU_RANGE_NUM];                                             ///< Diagnosis error regista
    uint16_t      output_voltage_cnt[CTSU_RANGE_NUM * 2];                                       ///< Diagnosis load resistance count value
    uint16_t      icomp0_value;                                                                 ///< Diagnosis icomp0 register value in over voltage test
    uint16_t      icomp1_value;                                                                 ///< Diagnosis icomp1 register value in over current test
    uint16_t      load_resistance[CTSU_RANGE_NUM];                                              ///< Diagnosis load resistance count value
    uint16_t      current_source[CTSU_DIAG_HIGH_CURRENT_SOURCE + CTSU_DIAG_LOW_CURRENT_SOURCE]; ///< Diagnosis current source count value
    uint16_t      sensclk_cnt[CTSU_CORRECTION_POINT_NUM];                                       ///< Diagnosis sensclk count value
    uint16_t      suclk_cnt[CTSU_CORRECTION_POINT_NUM];                                         ///< Diagnosis suclk count value
    uint16_t      suclk_count_clk_recv[3];                                                      ///< Diagnosis clock recovery suclk count value
    uint16_t      cfc_cnt[CTSU_CORRCFC_POINT_NUM];                                              ///< Diagnosis cfc count value
    uint32_t      chaca;                                                                        ///< Diagnosis CHACA
    uint32_t      chacb;                                                                        ///< Diagnosis CHACB
} ctsu_diag_info_t;
 #endif
#endif

/** CTSU private control block. DO NOT MODIFY. Initialization occurs when R_CTSU_Open() is called. */
typedef struct st_ctsu_instance_ctrl
{
    uint32_t                 open;               ///< Whether or not driver is open.
    volatile ctsu_state_t    state;              ///< CTSU run state.
    ctsu_cap_t               cap;                ///< CTSU Scan Start Trigger Select
    ctsu_md_t                md;                 ///< CTSU Measurement Mode Select(copy to cfg)
    ctsu_tuning_t            tuning;             ///< CTSU Initial offset tuning status.
    uint16_t                 num_elements;       ///< Number of elements to scan
    uint16_t                 wr_index;           ///< Word index into ctsuwr register array.
    uint16_t                 rd_index;           ///< Word index into scan data buffer.
    uint8_t * p_element_complete_flag;           ///< Pointer to complete flag of each element. g_ctsu_element_complete_flag[] is set by Open API.
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t * p_frequency_complete_flag;         ///< Pointer to complete flag of each frequency. g_ctsu_frequency_complete_flag[] is set by Open API.
#endif
    int32_t                * p_tuning_diff;      ///< Pointer to difference from base value of each element. g_ctsu_tuning_diff[] is set by Open API.
    uint16_t                 average;            ///< CTSU Moving average counter.
    uint16_t                 num_moving_average; ///< Copy from config by Open API.
    uint8_t                  ctsucr1;            ///< Copy from (atune1 << 3, md << 6) by Open API. CLK, ATUNE0, CSW, and PON is set by HAL driver.
    ctsu_ctsuwr_t          * p_ctsuwr;           ///< CTSUWR write register value. g_ctsu_ctsuwr[] is set by Open API.
    ctsu_self_buf_t        * p_self_raw;         ///< Pointer to Self raw data. g_ctsu_self_raw[] is set by Open API.
    uint16_t               * p_self_corr;        ///< Pointer to Self correction data. g_ctsu_self_corr[] is set by Open API.
    ctsu_data_t            * p_self_data;        ///< Pointer to Self moving average data. g_ctsu_self_data[] is set by Open API.
    ctsu_mutual_buf_t      * p_mutual_raw;       ///< Pointer to Mutual raw data. g_ctsu_mutual_raw[] is set by Open API.
    uint16_t               * p_mutual_pri_corr;  ///< Pointer to Mutual primary correction data. g_ctsu_self_corr[] is set by Open API.
    uint16_t               * p_mutual_snd_corr;  ///< Pointer to Mutual secondary correction data. g_ctsu_self_corr[] is set by Open API.
    ctsu_data_t            * p_mutual_pri_data;  ///< Pointer to Mutual primary moving average data. g_ctsu_mutual_pri_data[] is set by Open API.
    ctsu_data_t            * p_mutual_snd_data;  ///< Pointer to Mutual secondary moving average data. g_ctsu_mutual_snd_data[] is set by Open API.
    ctsu_correction_info_t * p_correction_info;  ///< Pointer to correction info
    ctsu_txvsel_t            txvsel;             ///< CTSU Transmission Power Supply Select
    ctsu_txvsel2_t           txvsel2;            ///< CTSU Transmission Power Supply Select 2 (CTSU2 Only)
    uint8_t                  ctsuchac0;          ///< TS00-TS07 enable mask
    uint8_t                  ctsuchac1;          ///< TS08-TS15 enable mask
    uint8_t                  ctsuchac2;          ///< TS16-TS23 enable mask
    uint8_t                  ctsuchac3;          ///< TS24-TS31 enable mask
    uint8_t                  ctsuchac4;          ///< TS32-TS39 enable mask
    uint8_t                  ctsuchtrc0;         ///< TS00-TS07 mutual-tx mask
    uint8_t                  ctsuchtrc1;         ///< TS08-TS15 mutual-tx mask
    uint8_t                  ctsuchtrc2;         ///< TS16-TS23 mutual-tx mask
    uint8_t                  ctsuchtrc3;         ///< TS24-TS31 mutual-tx mask
    uint8_t                  ctsuchtrc4;         ///< TS32-TS39 mutual-tx mask
    uint16_t                 self_elem_index;    ///< self element index number for Current instance.
    uint16_t                 mutual_elem_index;  ///< mutual element index number for Current instance.
    uint16_t                 ctsu_elem_index;    ///< CTSU element index number for Current instance.
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t * p_selected_freq_self;              ///< Frequency selected by self-capacity
    uint8_t * p_selected_freq_mutual;            ///< Frequency selected by mutual-capacity
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    ctsu_diag_info_t * p_diag_info;              ///< pointer to diagnosis info
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
    ctsu_range_t range;                            ///< According to atune12. (20uA : 0, 40uA : 1, 80uA : 2, 160uA : 3)
    uint8_t      ctsucr2;                          ///< Copy from (posel, atune1, md) by Open API. FCMODE and SDPSEL and LOAD is set by HAL driver.
 #if (CTSU_CFG_NUM_CFC != 0)
    uint64_t              cfc_rx_bitmap;           ///< Bitmap of CFC receive terminal.
    ctsu_corrcfc_info_t * p_corrcfc_info;          ///< pointer to CFC correction info
 #endif
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    ctsu_diag_info_t * p_diag_info;                ///< pointer to diagnosis info
 #endif
#endif
    ctsu_cfg_t const * p_ctsu_cfg;                 ///< Pointer to initial configurations.
    IRQn_Type          write_irq;                  ///< Copy from config by Open API. CTSU_CTSUWR interrupt vector
    IRQn_Type          read_irq;                   ///< Copy from config by Open API. CTSU_CTSURD interrupt vector
    IRQn_Type          end_irq;                    ///< Copy from config by Open API. CTSU_CTSUFN interrupt vector
    void (* p_callback)(ctsu_callback_args_t *);   ///< Callback provided when a CTSUFN occurs.
    uint8_t                interrupt_reverse_flag; ///< Flag in which read interrupt and end interrupt are reversed
    ctsu_event_t           error_status;           ///< error status variable to send to QE for serial tuning.
    ctsu_callback_args_t * p_callback_memory;      ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void const           * p_context;              ///< Placeholder for user data.
    bool     serial_tuning_enable;                 ///< Flag of serial tuning status.
    uint16_t serial_tuning_mutual_cnt;             ///< Word index into ctsuwr register array.
    uint16_t tuning_self_target_value;             ///< Target self value for initial offset tuning
    uint16_t tuning_mutual_target_value;           ///< Target mutual value for initial offset tuning
} ctsu_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ctsu_api_t g_ctsu_on_ctsu;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_CTSU_Open(ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg);
fsp_err_t R_CTSU_ScanStart(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_DataGet(ctsu_ctrl_t * const p_ctrl, uint16_t * p_data);
fsp_err_t R_CTSU_ScanStop(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_CallbackSet(ctsu_ctrl_t * const          p_api_ctrl,
                             void (                     * p_callback)(ctsu_callback_args_t *),
                             void const * const           p_context,
                             ctsu_callback_args_t * const p_callback_memory);
fsp_err_t R_CTSU_Diagnosis(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_Close(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_SpecificDataGet(ctsu_ctrl_t * const       p_ctrl,
                                 uint16_t                * p_specific_data,
                                 ctsu_specific_data_type_t specific_data_type);
fsp_err_t R_CTSU_DataInsert(ctsu_ctrl_t * const p_ctrl, uint16_t * p_insert_data);
fsp_err_t R_CTSU_OffsetTuning (ctsu_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_CTSU_H

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU)
 **********************************************************************************************************************/
