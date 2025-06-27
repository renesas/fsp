/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6T2
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA6T2) */

#ifndef R_ADC_DEVICE_TYPES
#define R_ADC_DEVICE_TYPES

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define ADC_B_CHANNEL_MASK_EXT_OFFSET    (32U)

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_ADC_CHANNEL_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ADC Clock source selection */
typedef enum e_adc_b_clock_source
{
    ADC_B_CLOCK_SOURCE_PCLKC = 0,      ///< ADC Clock Source PCLKC
    ADC_B_CLOCK_SOURCE_GPT   = 1,      ///< ADC Clock Source GPT
    ADC_B_CLOCK_SOURCE_PCLKA = 2       ///< ADC Clock Source PCLKA
} adc_b_clock_source_t;

/** ADC channels */
typedef enum e_adc_b_virtual_channel
{
    ADC_B_VIRTUAL_CHANNEL_0  = 0,      ///< ADC B virtual channel 0
    ADC_B_VIRTUAL_CHANNEL_1  = 1,      ///< ADC B virtual channel 1
    ADC_B_VIRTUAL_CHANNEL_2  = 2,      ///< ADC B virtual channel 2
    ADC_B_VIRTUAL_CHANNEL_3  = 3,      ///< ADC B virtual channel 3
    ADC_B_VIRTUAL_CHANNEL_4  = 4,      ///< ADC B virtual channel 4
    ADC_B_VIRTUAL_CHANNEL_5  = 5,      ///< ADC B virtual channel 5
    ADC_B_VIRTUAL_CHANNEL_6  = 6,      ///< ADC B virtual channel 6
    ADC_B_VIRTUAL_CHANNEL_7  = 7,      ///< ADC B virtual channel 7
    ADC_B_VIRTUAL_CHANNEL_8  = 8,      ///< ADC B virtual channel 8
    ADC_B_VIRTUAL_CHANNEL_9  = 9,      ///< ADC B virtual channel 9
    ADC_B_VIRTUAL_CHANNEL_10 = 10,     ///< ADC B virtual channel 10
    ADC_B_VIRTUAL_CHANNEL_11 = 11,     ///< ADC B virtual channel 11
    ADC_B_VIRTUAL_CHANNEL_12 = 12,     ///< ADC B virtual channel 12
    ADC_B_VIRTUAL_CHANNEL_13 = 13,     ///< ADC B virtual channel 13
    ADC_B_VIRTUAL_CHANNEL_14 = 14,     ///< ADC B virtual channel 14
    ADC_B_VIRTUAL_CHANNEL_15 = 15,     ///< ADC B virtual channel 15
    ADC_B_VIRTUAL_CHANNEL_16 = 16,     ///< ADC B virtual channel 16
    ADC_B_VIRTUAL_CHANNEL_17 = 17,     ///< ADC B virtual channel 17
    ADC_B_VIRTUAL_CHANNEL_18 = 18,     ///< ADC B virtual channel 18
    ADC_B_VIRTUAL_CHANNEL_19 = 19,     ///< ADC B virtual channel 19
    ADC_B_VIRTUAL_CHANNEL_20 = 20,     ///< ADC B virtual channel 20
    ADC_B_VIRTUAL_CHANNEL_21 = 21,     ///< ADC B virtual channel 21
    ADC_B_VIRTUAL_CHANNEL_22 = 22,     ///< ADC B virtual channel 22
    ADC_B_VIRTUAL_CHANNEL_23 = 23,     ///< ADC B virtual channel 23
    ADC_B_VIRTUAL_CHANNEL_24 = 24,     ///< ADC B virtual channel 24
    ADC_B_VIRTUAL_CHANNEL_25 = 25,     ///< ADC B virtual channel 25
    ADC_B_VIRTUAL_CHANNEL_26 = 26,     ///< ADC B virtual channel 26
    ADC_B_VIRTUAL_CHANNEL_27 = 27,     ///< ADC B virtual channel 27
    ADC_B_VIRTUAL_CHANNEL_28 = 28,     ///< ADC B virtual channel 28
    ADC_B_VIRTUAL_CHANNEL_29 = 29,     ///< ADC B virtual channel 29
    ADC_B_VIRTUAL_CHANNEL_30 = 30,     ///< ADC B virtual channel 30
    ADC_B_VIRTUAL_CHANNEL_31 = 31,     ///< ADC B virtual channel 31
    ADC_B_VIRTUAL_CHANNEL_32 = 32,     ///< ADC B virtual channel 32
    ADC_B_VIRTUAL_CHANNEL_33 = 33,     ///< ADC B virtual channel 33
    ADC_B_VIRTUAL_CHANNEL_34 = 34,     ///< ADC B virtual channel 34
    ADC_B_VIRTUAL_CHANNEL_35 = 35,     ///< ADC B virtual channel 35
    ADC_B_VIRTUAL_CHANNEL_36 = 36,     ///< ADC B virtual channel 36
    ADC_B_VIRTUAL_CHANNEL_COUNT        // Number of available ADC B virtual channels
} adc_b_virtual_channel_t;

/** ADC channels */
typedef enum e_adc_channel
{
    /* These channels map to physical pins */
    ADC_CHANNEL_0  = 0,                                      ///< ADC channel 0
    ADC_CHANNEL_1  = 1,                                      ///< ADC channel 1
    ADC_CHANNEL_2  = 2,                                      ///< ADC channel 2
    ADC_CHANNEL_3  = 3,                                      ///< ADC channel 3
    ADC_CHANNEL_4  = 4,                                      ///< ADC channel 4
    ADC_CHANNEL_5  = 5,                                      ///< ADC channel 5
    ADC_CHANNEL_6  = 6,                                      ///< ADC channel 6
    ADC_CHANNEL_7  = 7,                                      ///< ADC channel 7
    ADC_CHANNEL_8  = 8,                                      ///< ADC channel 8
    ADC_CHANNEL_9  = 9,                                      ///< ADC channel 9
    ADC_CHANNEL_10 = 10,                                     ///< ADC channel 10
    ADC_CHANNEL_11 = 11,                                     ///< ADC channel 11
    ADC_CHANNEL_12 = 12,                                     ///< ADC channel 12
    ADC_CHANNEL_13 = 13,                                     ///< ADC channel 13
    ADC_CHANNEL_14 = 14,                                     ///< ADC channel 14
    ADC_CHANNEL_15 = 15,                                     ///< ADC channel 15
    ADC_CHANNEL_16 = 16,                                     ///< ADC channel 16
    ADC_CHANNEL_17 = 17,                                     ///< ADC channel 17
    ADC_CHANNEL_18 = 18,                                     ///< ADC channel 18
    ADC_CHANNEL_19 = 19,                                     ///< ADC channel 19
    ADC_CHANNEL_20 = 20,                                     ///< ADC channel 20
    ADC_CHANNEL_21 = 21,                                     ///< ADC channel 21
    ADC_CHANNEL_22 = 22,                                     ///< ADC channel 22
    ADC_CHANNEL_23 = 23,                                     ///< ADC channel 23
    ADC_CHANNEL_24 = 24,                                     ///< ADC channel 24
    ADC_CHANNEL_25 = 25,                                     ///< ADC channel 25
    ADC_CHANNEL_26 = 26,                                     ///< ADC channel 26
    ADC_CHANNEL_27 = 27,                                     ///< ADC channel 27
    ADC_CHANNEL_28 = 28,                                     ///< ADC channel 28

    /* Extended Channels, See implementation for details */
    /* Implementation specific extended channels */
    ADC_CHANNEL_SELF_DIAGNOSIS = (0x60),                     ///< Self-Diagnosis channel
    ADC_CHANNEL_TEMPERATURE    = (0x61),                     ///< Temperature sensor output
    ADC_CHANNEL_VOLT           = (0x62),                     ///< Internal reference voltage
    ADC_CHANNEL_DA0            = (0x65),                     ///< D/A Converter Channel 0
    ADC_CHANNEL_DA1            = (0x66),                     ///< D/A Converter Channel 1
    ADC_CHANNEL_DA2            = (0x67),                     ///< D/A Converter Channel 2
    ADC_CHANNEL_DA3            = (0x68),                     ///< D/A Converter Channel 3

    ADC_CHANNEL_LAST_EXTERNAL  = ADC_CHANNEL_28,             /// Highest physical channel
    ADC_CHANNEL_FIRST_INTERNAL = ADC_CHANNEL_SELF_DIAGNOSIS, /// First internal channel
    ADC_CHANNEL_LAST_INTERNAL  = ADC_CHANNEL_DA3,            /// Last internal channel
} adc_channel_t;

/** ADC channel mask */
typedef enum e_adc_b_channel_mask
{
    ADC_B_CHANNEL_MASK_NONE = 0ULL,
    ADC_B_CHANNEL_MASK_0    = (1ULL << 0),                                          ///< Channel 0
    ADC_B_CHANNEL_MASK_1    = (1ULL << 1),                                          ///< Channel 1
    ADC_B_CHANNEL_MASK_2    = (1ULL << 2),                                          ///< Channel 2
    ADC_B_CHANNEL_MASK_3    = (1ULL << 3),                                          ///< Channel 3
    ADC_B_CHANNEL_MASK_4    = (1ULL << 4),                                          ///< Channel 4
    ADC_B_CHANNEL_MASK_5    = (1ULL << 5),                                          ///< Channel 5
    ADC_B_CHANNEL_MASK_6    = (1ULL << 6),                                          ///< Channel 6
    ADC_B_CHANNEL_MASK_7    = (1ULL << 7),                                          ///< Channel 7
    ADC_B_CHANNEL_MASK_8    = (1ULL << 8),                                          ///< Channel 8
    ADC_B_CHANNEL_MASK_9    = (1ULL << 9),                                          ///< Channel 9
    ADC_B_CHANNEL_MASK_10   = (1ULL << 10),                                         ///< Channel 10
    ADC_B_CHANNEL_MASK_11   = (1ULL << 11),                                         ///< Channel 11
    ADC_B_CHANNEL_MASK_12   = (1ULL << 12),                                         ///< Channel 12
    ADC_B_CHANNEL_MASK_13   = (1ULL << 13),                                         ///< Channel 13
    ADC_B_CHANNEL_MASK_14   = (1ULL << 14),                                         ///< Channel 14
    ADC_B_CHANNEL_MASK_15   = (1ULL << 15),                                         ///< Channel 15
    ADC_B_CHANNEL_MASK_16   = (1ULL << 16),                                         ///< Channel 16
    ADC_B_CHANNEL_MASK_17   = (1ULL << 17),                                         ///< Channel 17
    ADC_B_CHANNEL_MASK_18   = (1ULL << 18),                                         ///< Channel 18
    ADC_B_CHANNEL_MASK_19   = (1ULL << 19),                                         ///< Channel 19
    ADC_B_CHANNEL_MASK_20   = (1ULL << 20),                                         ///< Channel 20
    ADC_B_CHANNEL_MASK_21   = (1ULL << 21),                                         ///< Channel 21
    ADC_B_CHANNEL_MASK_22   = (1ULL << 22),                                         ///< Channel 22
    ADC_B_CHANNEL_MASK_23   = (1ULL << 23),                                         ///< Channel 23
    ADC_B_CHANNEL_MASK_24   = (1ULL << 24),                                         ///< Channel 24
    ADC_B_CHANNEL_MASK_25   = (1ULL << 25),                                         ///< Channel 25
    ADC_B_CHANNEL_MASK_26   = (1ULL << 26),                                         ///< Channel 26
    ADC_B_CHANNEL_MASK_27   = (1ULL << 27),                                         ///< Channel 27
    ADC_B_CHANNEL_MASK_28   = (1ULL << 28),                                         ///< Channel 28

    ADC_B_CHANNEL_MASK_DIAGNOSIS   = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 0)), ///< Converter Self-Diagnosis Channel
    ADC_B_CHANNEL_MASK_TEMPERATURE = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 1)), ///< Temperature sensor channel
    ADC_B_CHANNEL_MASK_VOLT        = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 2)), ///< Voltage Reference channel
    ADC_B_CHANNEL_MASK_DAC0        = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 5)), ///< DAC 0 Channel
    ADC_B_CHANNEL_MASK_DAC1        = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 6)), ///< DAC 1 Channel
    ADC_B_CHANNEL_MASK_DAC2        = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 7)), ///< DAC 2 Channel
    ADC_B_CHANNEL_MASK_DAC3        = (1ULL << (ADC_B_CHANNEL_MASK_EXT_OFFSET + 8)), ///< DAC 3 Channel
} adc_b_channel_mask_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
