/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
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

#include "r_ctsu_cfg.h"
#include "r_ctsu_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CTSU_CODE_VERSION_MAJOR     (1U)
#define CTSU_CODE_VERSION_MINOR     (0U)

#define CTSU_NUM_ELEMENTS           (CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CTSU run state */
typedef enum e_ctsu_state
{
    CTSU_STATE_INIT,            ///< Not open.
    CTSU_STATE_IDLE,            ///< Opened.
    CTSU_STATE_SCANNING,        ///< Scanning now.
    CTSU_STATE_SCANNED          ///< Scan end.
} ctsu_state_t;

/** CTSU Initial offset tuning status */
typedef enum e_ctsu_tuning
{
    CTSU_TUNING_INCOMPLETE,     ///< Initial offset tuning incomplete
    CTSU_TUNING_COMPLETE        ///< Initial offset tuning complete
} ctsu_tuning_t;

/** CTSUWR write register value */
typedef struct st_ctsu_wr
{
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t    ctsussc;        ///< Copy from (ssdiv << 8) by Open API.
    uint16_t    ctsuso0;        ///< Copy from ((snum << 10) | so) by Open API.
    uint16_t    ctsuso1;        ///< Copy from (sdpa << 8) by Open API. ICOG and RICOA is set recommend value.
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t    ctsuso;         ///< Copy from ((sdpa << 24) | (ssdiv << 20) | (snum << 10) | so) by Open API.
#endif
} ctsu_ctsuwr_t;

/** Scan buffer data formats (Self) */
#if (BSP_FEATURE_CTSU_VERSION == 1)
typedef struct st_ctsu_self_buf
{
    uint16_t    sen;            ///< Sensor counter data
    uint16_t    ref;            ///< Reference counter data (Not used)
} ctsu_self_buf_t;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_self_buf_t;
#endif

/** Scan buffer data formats (Mutual) */
#if (BSP_FEATURE_CTSU_VERSION == 1)
typedef struct st_ctsu_mutual_buf
{
    uint16_t    pri_sen;        ///< Primary sensor data
    uint16_t    pri_ref;        ///< Primary reference data (Not used)
    uint16_t    snd_sen;        ///< Secondary sensor data
    uint16_t    snd_ref;        ///< Secondary reference data (Not used)
} ctsu_mutual_buf_t;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_mutual_buf_t;
#endif

/** CTSU private control block. DO NOT MODIFY. Initialization occurs when R_CTSU_Open() is called. */
typedef struct st_ctsu_instance_ctrl
{
    uint32_t          open;                 ///< Whether or not driver is open.
    ctsu_state_t      state;                ///< CTSU run state.
    ctsu_tuning_t     tuning;               ///< CTSU Initial offset tuning status.
    uint16_t          num_elements;         ///< Number of elements to scan
    uint16_t          wr_index;             ///< Word index into ctsuwr register array.
    uint16_t          rd_index;             ///< Word index into scan data buffer.
    uint8_t           * p_tuning_complete;  ///< Pointer to tuning completion flag of each element. g_ctsu_tuning_complete[] is set by Open API.
    int32_t           * p_tuning_diff;      ///< Pointer to difference from base value of each element. g_ctsu_tuning_diff[] is set by Open API.
    uint16_t          average;              ///< CTSU Moving average counter.
    uint16_t          num_moving_average;   ///< Copy from config by Open API.
    uint8_t           ctsucr1;              ///< Copy from (atune0 << 2, atune1 << 3, clk << 4, md << 6) by Open API. CSW and PON is set by HAL driver.
    uint8_t           ctsucr2;              ///< Copy from (posel, atune1, md) by Open API. FCMODE and SDPSEL and LOAD is set by HAL driver.
    ctsu_ctsuwr_t     * p_ctsuwr;           ///< CTSUWR write register value. g_ctsu_ctsuwr[] is set by Open API.
    ctsu_self_buf_t   * p_self_raw;         ///< Pointer to Self raw data. g_ctsu_self_raw[] is set by Open API.
    uint16_t          * p_self_work;        ///< pointer to Self work buffer. g_ctsu_self_work[] is set by Open API.
    uint16_t          * p_self_data;        ///< pointer to Self moving average data. g_ctsu_self_data[] is set by Open API.
    ctsu_mutual_buf_t * p_mutual_raw;       ///< pointer to Mutual raw data. g_ctsu_mutual_raw[] is set by Open API.
    uint16_t          * p_mutual_pri_work;  ///< pointer to Mutual primary work buffer. g_ctsu_mutual_pri_work[] is set by Open API.
    uint16_t          * p_mutual_snd_work;  ///< pointer to Mutual secondary work buffer. g_ctsu_mutual_snd_work[] is set by Open API.
    uint16_t          * p_mutual_pri_data;  ///< pointer to Mutual primary moving average data. g_ctsu_mutual_pri_data[] is set by Open API.
    uint16_t          * p_mutual_snd_data;  ///< pointer to Mutual secondary moving average data. g_ctsu_mutual_snd_data[] is set by Open API.
    uint16_t          * p_mutual_data;      ///< pointer to Mutual subtract primary from secondary. g_ctsu_mutual_data[] is set by Open API.
    ctsu_cfg_t const  * p_ctsu_cfg;         ///< Pointer to initial configurations.
    IRQn_Type         write_irq;            ///< Copy from config by Open API. CTSU_CTSUWR interrupt vector
    IRQn_Type         read_irq;             ///< Copy from config by Open API. CTSU_CTSURD interrupt vector
    IRQn_Type         end_irq;              ///< Copy from config by Open API. CTSU_CTSUFN interrupt vector
    void const        * p_context;          ///< Placeholder for user data.
    void              (*p_callback)(ctsu_callback_args_t *p_args); ///< Callback provided when a CTSUFN occurs.
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
fsp_err_t R_CTSU_DataGet(ctsu_ctrl_t * const p_ctrl, uint16_t *p_data);
fsp_err_t R_CTSU_Close(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_VersionGet (fsp_version_t * const p_version);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_CTSU_H

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU)
 **********************************************************************************************************************/
