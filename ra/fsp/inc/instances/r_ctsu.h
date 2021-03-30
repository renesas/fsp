/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#define CTSU_CODE_VERSION_MAJOR       (1U) // DEPRECATED
#define CTSU_CODE_VERSION_MINOR       (2U) // DEPRECATED

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #define CTSU_CORRECTION_POINT_NUM    (12) ///< number of correction table
 #define CTSU_CORRCFC_POINT_NUM       (5)  ///< number of CFC correction table
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

/** CTSU private control block. DO NOT MODIFY. Initialization occurs when R_CTSU_Open() is called. */
typedef struct st_ctsu_instance_ctrl
{
    uint32_t                 open;               ///< Whether or not driver is open.
    ctsu_state_t             state;              ///< CTSU run state.
    ctsu_tuning_t            tuning;             ///< CTSU Initial offset tuning status.
    uint16_t                 num_elements;       ///< Number of elements to scan
    uint16_t                 wr_index;           ///< Word index into ctsuwr register array.
    uint16_t                 rd_index;           ///< Word index into scan data buffer.
    uint8_t                * p_tuning_count;     ///< Pointer to tuning count of each element. g_ctsu_tuning_count[] is set by Open API.
    int32_t                * p_tuning_diff;      ///< Pointer to difference from base value of each element. g_ctsu_tuning_diff[] is set by Open API.
    uint16_t                 average;            ///< CTSU Moving average counter.
    uint16_t                 num_moving_average; ///< Copy from config by Open API.
    uint8_t                  ctsucr1;            ///< Copy from (atune1 << 3, md << 6) by Open API. CLK, ATUNE0, CSW, and PON is set by HAL driver.
    ctsu_ctsuwr_t          * p_ctsuwr;           ///< CTSUWR write register value. g_ctsu_ctsuwr[] is set by Open API.
    ctsu_self_buf_t        * p_self_raw;         ///< Pointer to Self raw data. g_ctsu_self_raw[] is set by Open API.
    uint16_t               * p_self_data;        ///< Pointer to Self moving average data. g_ctsu_self_data[] is set by Open API.
    ctsu_mutual_buf_t      * p_mutual_raw;       ///< Pointer to Mutual raw data. g_ctsu_mutual_raw[] is set by Open API.
    uint16_t               * p_mutual_pri_data;  ///< Pointer to Mutual primary moving average data. g_ctsu_mutual_pri_data[] is set by Open API.
    uint16_t               * p_mutual_snd_data;  ///< Pointer to Mutual secondary moving average data. g_ctsu_mutual_snd_data[] is set by Open API.
    ctsu_correction_info_t * p_correction_info;  ///< Pointer to correction info
#if (BSP_FEATURE_CTSU_VERSION == 2)
    ctsu_range_t range;                          ///< According to atune12. (20uA : 0, 40uA : 1, 80uA : 2, 160uA : 3)
    uint8_t      ctsucr2;                        ///< Copy from (posel, atune1, md) by Open API. FCMODE and SDPSEL and LOAD is set by HAL driver.
 #if (CTSU_CFG_NUM_CFC != 0)
    uint64_t              cfc_rx_bitmap;         ///< Bitmap of CFC receive terminal.
    ctsu_corrcfc_info_t * p_corrcfc_info;        ///< pointer to CFC correction info
 #endif
#endif
    ctsu_cfg_t const * p_ctsu_cfg;               ///< Pointer to initial configurations.
    IRQn_Type          write_irq;                ///< Copy from config by Open API. CTSU_CTSUWR interrupt vector
    IRQn_Type          read_irq;                 ///< Copy from config by Open API. CTSU_CTSURD interrupt vector
    IRQn_Type          end_irq;                  ///< Copy from config by Open API. CTSU_CTSUFN interrupt vector
    void (* p_callback)(ctsu_callback_args_t *); ///< Callback provided when a CTSUFN occurs.
    ctsu_callback_args_t * p_callback_memory;    ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void const           * p_context;            ///< Placeholder for user data.
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
fsp_err_t R_CTSU_CallbackSet(ctsu_ctrl_t * const          p_api_ctrl,
                             void (                     * p_callback)(ctsu_callback_args_t *),
                             void const * const           p_context,
                             ctsu_callback_args_t * const p_callback_memory);
fsp_err_t R_CTSU_Close(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_VersionGet(fsp_version_t * const p_version);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_CTSU_H

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU)
 **********************************************************************************************************************/
