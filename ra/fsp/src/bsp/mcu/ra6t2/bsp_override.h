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
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
#define BSP_OVERRIDE_ADC_CHANNEL_T

/* Override definitions. */
#define ELC_PERIPHERAL_NUM    (30U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Possible peripherals to be linked to event signals (not all available on all MCUs) */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_GPT_A   = (0),
    ELC_PERIPHERAL_GPT_B   = (1),
    ELC_PERIPHERAL_GPT_C   = (2),
    ELC_PERIPHERAL_GPT_D   = (3),
    ELC_PERIPHERAL_GPT_E   = (4),
    ELC_PERIPHERAL_GPT_F   = (5),
    ELC_PERIPHERAL_GPT_G   = (6),
    ELC_PERIPHERAL_GPT_H   = (7),
    ELC_PERIPHERAL_DAC0    = (12),
    ELC_PERIPHERAL_DAC1    = (13),
    ELC_PERIPHERAL_IOPORTB = (14),
    ELC_PERIPHERAL_IOPORTC = (15),
    ELC_PERIPHERAL_IOPORTD = (16),
    ELC_PERIPHERAL_IOPORTE = (17),
    ELC_PERIPHERAL_ADC0    = (19),
    ELC_PERIPHERAL_ADC0_B  = (20),
    ELC_PERIPHERAL_ADC0_C  = (21),
    ELC_PERIPHERAL_ADC1    = (22),
    ELC_PERIPHERAL_ADC1_B  = (23),
    ELC_PERIPHERAL_ADC1_C  = (24),
    ELC_PERIPHERAL_DAC2    = (28),
    ELC_PERIPHERAL_DAC3    = (29),
} elc_peripheral_t;

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
