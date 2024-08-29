/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6T2
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA6T2) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_ADC_CHANNEL_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/*==============================================
 * ADC Overrides
 *==============================================*/

/** ADC channels */
typedef enum e_adc_channel
{
    /* These channels map to physical pins */
    ADC_CHANNEL_0  = 0,                  ///< ADC channel 0
    ADC_CHANNEL_1  = 1,                  ///< ADC channel 1
    ADC_CHANNEL_2  = 2,                  ///< ADC channel 2
    ADC_CHANNEL_3  = 3,                  ///< ADC channel 3
    ADC_CHANNEL_4  = 4,                  ///< ADC channel 4
    ADC_CHANNEL_5  = 5,                  ///< ADC channel 5
    ADC_CHANNEL_6  = 6,                  ///< ADC channel 6
    ADC_CHANNEL_7  = 7,                  ///< ADC channel 7
    ADC_CHANNEL_8  = 8,                  ///< ADC channel 8
    ADC_CHANNEL_9  = 9,                  ///< ADC channel 9
    ADC_CHANNEL_10 = 10,                 ///< ADC channel 10
    ADC_CHANNEL_11 = 11,                 ///< ADC channel 11
    ADC_CHANNEL_12 = 12,                 ///< ADC channel 12
    ADC_CHANNEL_13 = 13,                 ///< ADC channel 13
    ADC_CHANNEL_14 = 14,                 ///< ADC channel 14
    ADC_CHANNEL_15 = 15,                 ///< ADC channel 15
    ADC_CHANNEL_16 = 16,                 ///< ADC channel 16
    ADC_CHANNEL_17 = 17,                 ///< ADC channel 17
    ADC_CHANNEL_18 = 18,                 ///< ADC channel 18
    ADC_CHANNEL_19 = 19,                 ///< ADC channel 19
    ADC_CHANNEL_20 = 20,                 ///< ADC channel 20
    ADC_CHANNEL_21 = 21,                 ///< ADC channel 21
    ADC_CHANNEL_22 = 22,                 ///< ADC channel 22
    ADC_CHANNEL_23 = 23,                 ///< ADC channel 23
    ADC_CHANNEL_24 = 24,                 ///< ADC channel 24
    ADC_CHANNEL_25 = 25,                 ///< ADC channel 25
    ADC_CHANNEL_26 = 26,                 ///< ADC channel 26
    ADC_CHANNEL_27 = 27,                 ///< ADC channel 27
    ADC_CHANNEL_28 = 28,                 ///< ADC channel 28

    /* Extended Channels, See implimentation for details */
    /* Implimentation specific extended channels */
    ADC_CHANNEL_SELF_DIAGNOSIS = (0x60), ///< Self-Diagnosis channel
    ADC_CHANNEL_TEMPERATURE    = (0x61), ///< Temperature sensor output
    ADC_CHANNEL_VOLT           = (0x62), ///< Internal reference voltage
    ADC_CHANNEL_DA0            = (0x65), ///< D/A Converter Channel 0
    ADC_CHANNEL_DA1            = (0x66), ///< D/A Converter Channel 1
    ADC_CHANNEL_DA2            = (0x67), ///< D/A Converter Channel 2
    ADC_CHANNEL_DA3            = (0x68)  ///< D/A Converter Channel 3
} adc_channel_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
