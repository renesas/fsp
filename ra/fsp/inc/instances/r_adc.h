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

#ifndef R_ADC_H
#define R_ADC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>

/* Fixed width integer support. */
#include <stdint.h>

/* bool support */
#include <stdbool.h>
#include "bsp_api.h"
#include "r_adc_cfg.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup ADC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Version of code that implements the API defined in this file */
#define ADC_CODE_VERSION_MAJOR                 (1U)
#define ADC_CODE_VERSION_MINOR                 (0U)

/* Typical values that can be used to modify the sample states.
 * The minimum sample state count value is either 6 or 7 depending on the clock ratios.
 * It is fixed to 7 based on the fact that at the lowest ADC conversion clock supported (1 MHz)
 * this extra state will lead to at worst a "1 microsecond" increase in conversion time.
 * At 60 MHz the extra sample state will add 16.7 ns to the conversion time.
 */
#define ADC_SAMPLE_STATE_COUNT_MIN             (7U)
#define ADC_SAMPLE_STATE_COUNT_MAX             (255U)

/* Typical values that can be used for the sample and hold counts for the channels 0-2*/
/* Minimum sample and hold states */
#define ADC_SAMPLE_STATE_HOLD_COUNT_MIN        (4U)

/* Default sample and hold states */
#define ADC_SAMPLE_STATE_HOLD_COUNT_DEFAULT    (24U)

/* For ADC Scan configuration adc_channel_cfg_t::scan_mask, scan_mask_group_b,
 * add_mask and sample_hold_mask      */

/* Use bitwise OR to combine these masks for desired channels and sensors.    */
typedef enum e_adc_mask
{
    ADC_MASK_OFF         = (0U),
    ADC_MASK_CHANNEL_0   = (1U << 0U),
    ADC_MASK_CHANNEL_1   = (1U << 1U),
    ADC_MASK_CHANNEL_2   = (1U << 2U),
    ADC_MASK_CHANNEL_3   = (1U << 3U),
    ADC_MASK_CHANNEL_4   = (1U << 4U),
    ADC_MASK_CHANNEL_5   = (1U << 5U),
    ADC_MASK_CHANNEL_6   = (1U << 6U),
    ADC_MASK_CHANNEL_7   = (1U << 7U),
    ADC_MASK_CHANNEL_8   = (1U << 8U),
    ADC_MASK_CHANNEL_9   = (1U << 9U),
    ADC_MASK_CHANNEL_10  = (1U << 10U),
    ADC_MASK_CHANNEL_11  = (1U << 11U),
    ADC_MASK_CHANNEL_12  = (1U << 12U),
    ADC_MASK_CHANNEL_13  = (1U << 13U),
    ADC_MASK_CHANNEL_14  = (1U << 14U),
    ADC_MASK_CHANNEL_15  = (1U << 15U),
    ADC_MASK_CHANNEL_16  = (1U << 16U),
    ADC_MASK_CHANNEL_17  = (1U << 17U),
    ADC_MASK_CHANNEL_18  = (1U << 18U),
    ADC_MASK_CHANNEL_19  = (1U << 19U),
    ADC_MASK_CHANNEL_20  = (1U << 20U),
    ADC_MASK_CHANNEL_21  = (1U << 21U),
    ADC_MASK_CHANNEL_22  = (1U << 22U),
    ADC_MASK_CHANNEL_23  = (1U << 23U),
    ADC_MASK_CHANNEL_24  = (1U << 24U),
    ADC_MASK_CHANNEL_25  = (1U << 25U),
    ADC_MASK_CHANNEL_26  = (1U << 26U),
    ADC_MASK_CHANNEL_27  = (1U << 27U),
    ADC_MASK_TEMPERATURE = (1U << 28UL),
    ADC_MASK_VOLT        = (1U << 29UL),
    ADC_MASK_SENSORS     = (ADC_MASK_TEMPERATURE | ADC_MASK_VOLT),
} adc_mask_t;

/* Sample and hold Channel mask. Sample and hold is only available for channel 0,1,2*/
#define ADC_SAMPLE_HOLD_CHANNELS    (0x07U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ADC instance control block. DO NOT INITIALIZE.  Initialized in adc_api_t::open(). */
typedef struct
{
    R_ADC0_Type     * p_reg;           // Base register for this unit
    adc_cfg_t const * p_cfg;
    uint32_t          opened;          // Boolean to verify that the Unit has been initialized
    uint32_t          scan_mask;       // Scan mask used for Normal scan.
    uint16_t          scan_start_adcsr;
} adc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_adc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ADC_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_ADC_ScanCfg(adc_ctrl_t * p_ctrl, adc_channel_cfg_t const * const p_channel_cfg);
fsp_err_t R_ADC_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_ADC_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_ADC_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_ADC_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_ADC_SampleStateCountSet(adc_ctrl_t * p_ctrl, adc_sample_state_t * p_sample);
fsp_err_t R_ADC_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset);
fsp_err_t R_ADC_Calibrate(adc_ctrl_t * const p_ctrl, void * const p_extend);
fsp_err_t R_ADC_VersionGet(fsp_version_t * const p_version);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
