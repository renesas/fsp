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

/* Guards against multiple inclusion */
#ifndef RM_ZMOD4XXX_LIB_SPECIFIC_CONFIGURATION_H_
#define RM_ZMOD4XXX_LIB_SPECIFIC_CONFIGURATION_H_

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_zmod4xxx.h"
#include "zmod4xxx_types.h"

/* Algorithm Relevant Headers and Macro Definitions */
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2)
 #include "iaq_1st_gen.h"
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 3)
 #include "iaq_2nd_gen.h"
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 5)
 #include "sulfur_odor.h"
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4)
 #include "odor.h"
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6)
 #include "oaq_1st_gen.h"
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7)
 #include "oaq_2nd_gen.h"
#else
#endif

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Sampling periods */
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 1)
 #define RM_ZMOD4XXX_SAMPLE_PERIOD    (2)
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2)
 #define RM_ZMOD4XXX_SAMPLE_PERIOD    (6)
#endif

/* Definitions of ZMOD4XXX specific data */
#define RM_ZMOD4XXX_H_ADDR            (0x40)
#define RM_ZMOD4XXX_D_ADDR            (0x50)
#define RM_ZMOD4XXX_M_ADDR            (0x60)
#define RM_ZMOD4XXX_S_ADDR            (0x68)

#if (RM_ZMOD4XXX_CFG_OPERATION_MODE <= 5)
 #define RM_ZMOD4XXX_PID              (0x2310)
 #define RM_ZMOD4XXX_PROD_DATA_LEN    (6)
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6) // OAQ 1st gen
 #define RM_ZMOD4XXX_PID              (0x6320)
 #define RM_ZMOD4XXX_PROD_DATA_LEN    (9)
 #define D_RISING_M1                  (4.9601944386079566e-05)
 #define D_FALLING_M1                 (0.3934693402873666)
 #define D_CLASS_M1                   (0.024690087971667385)
 #define STABILIZATION_SAMPLES        (60)
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7) // OAQ 2nd gen
 #define RM_ZMOD4XXX_PID              (0x6320)
 #define RM_ZMOD4XXX_PROD_DATA_LEN    (10)
#endif

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/* Data set for initialization */
static uint8_t gs_zmod4xxx_data_set_init[] =
{
// REMOVE                       heater
    0x00, 0x50,

// REMOVE                       delay     , measurement
    0x00, 0x28,0xC3,  0xE3,

// REMOVE                       sequencer
    0x00, 0x00,0x80,  0x40
};

/* Data set for measurement */
static uint8_t gs_zmod4xxx_data_set_meas[] =
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4) // IAQ 1st gen. continuous mode and Odor
// REMOVE                       heater
    0xFD, 0xA8,

// REMOVE                       delay
    0x20, 0x04,0x20,  0x04,

// REMOVE                       measurement
    0x03,

// REMOVE                       sequencer
    0x00, 0x00,0x80,  0x08
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2) // IAQ 1st gen. low power mode
// REMOVE                       heater
    0x00, 0x50,0xFD,  0XA8,

// REMOVE                       delay
    0x00, 0xCD,0x01,  0x9A,0x03,  0x34,

// REMOVE                       measurement
    0x23, 0x03,

// REMOVE                       sequencer
    0x00, 0x00,0x0A,  0x41,0x0A,  0x41,
    0x00, 0x41,0x00,  0x41,0x00,  0x49,
    0x00, 0x49,0x00,  0x51,0x00,  0x09,
    0x00, 0x49,0x00,  0x40,0x00,  0x40,
    0x00, 0x40,0x80,  0x40
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 3) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 5) // IAQ 2nd gen. and Sulfur odor
// REMOVE                              heater
    0x00, 0x50,0xFF,  0x38,
    0xFE, 0xD4,0xFE,  0x70,
    0xFE, 0x0C,0xFD,  0xA8,
    0xFD, 0x44,0xFC,  0xE0,

// REMOVE                              delay
    0x00, 0x52,0x02,  0x67,
    0x00, 0xCD,0x03,  0x34,

// REMOVE                              measurement
    0x23, 0x03,0xA3,  0x43,

// REMOVE                              sequencer
    0x00, 0x00,0x06,  0x49,
    0x06, 0x4A,0x06,  0x4B,
    0x06, 0x4C,0x06,  0x4D,
    0x06, 0x4E,0x06,  0x97,
    0x06, 0xD7,0x06,  0x57,
    0x06, 0x4E,0x06,  0x4D,
    0x06, 0x4C,0x06,  0x4B,
    0x06, 0x4A,0x86,  0x59
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6) // OAQ 1st gen
// REMOVE                        heater
    0xFE, 0x48,0xFE,  0X16,
    0xFD, 0xE4,0XFD,  0xB2,
    0xFD, 0x80,

// REMOVE                        delay
    0x20, 0x05,0xA0,  0x18,
    0xC0, 0x1C,

// REMOVE                        measurement
    0x03,

// REMOVE                        sequencer
    0x00, 0x00,0x00,  0x08,
    0x00, 0x10,0x00,  0x01,
    0x00, 0x09,0x00,  0x11,
    0x00, 0x02,0x00,  0x0A,
    0x00, 0x12,0x00,  0x03,
    0x00, 0x0B,0x00,  0x13,
    0x00, 0x04,0x00,  0x0C,
    0x80, 0x14,
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7) // OAQ 2nd gen
// REMOVE this implements the ULP_NN_05.xml sequence
// REMOVE                       heater
    0x00, 0x50,0xFE,  0x70,

// REMOVE                       delay
    0x00, 0x10,

// REMOVE                       measurement
    0x23, 0x03,

// REMOVE                       sequencer
    0x00, 0x00,0x06,  0x41,
    0x06, 0x41,0x06,  0x41,
    0x06, 0x41,0x06,  0x41,
    0x06, 0x41,0x06,  0x41,
    0x86, 0x41
#else
#endif
};

/* Data set of ZMOD4XXX */
static zmod4xxx_conf gs_zmod4xxx_sensor_type[] =
{
    /* Initialization */
    {
        .start = 0x80,
        .h     = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 2,  .data_buf = &gs_zmod4xxx_data_set_init[0] },
        .d     = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 2,  .data_buf = &gs_zmod4xxx_data_set_init[2] },
        .m     = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 2,  .data_buf = &gs_zmod4xxx_data_set_init[4] },
        .s     = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 4,  .data_buf = &gs_zmod4xxx_data_set_init[6] },
        .r     = {.addr = 0x97,               .len = 4},
    },

    /* Measurement */
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4) // IAQ 1st gen. continuous mode and Odor
    {
        .start         = 0xC0,
        .h             = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 2, .data_buf = &gs_zmod4xxx_data_set_meas[0]},
        .d             = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 4, .data_buf = &gs_zmod4xxx_data_set_meas[2]},
        .m             = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 1, .data_buf = &gs_zmod4xxx_data_set_meas[6]},
        .s             = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 4, .data_buf = &gs_zmod4xxx_data_set_meas[7]},
        .r             = {.addr = 0x99,       .len = 2},
        .prod_data_len = RM_ZMOD4XXX_PROD_DATA_LEN,
    },
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2) // IAQ 1st gen. low power mode
    {
        .start         = 0x80,
        .h             = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 4, .data_buf = &gs_zmod4xxx_data_set_meas[0]},
        .d             = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 6, .data_buf = &gs_zmod4xxx_data_set_meas[4]},
        .m             = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 2, .data_buf = &gs_zmod4xxx_data_set_meas[10]},
        .s             = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 28, .data_buf = &gs_zmod4xxx_data_set_meas[12]},
        .r             = {.addr = 0xA9,       .len = 2},
        .prod_data_len = RM_ZMOD4XXX_PROD_DATA_LEN,
    },
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 3) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 5) // IAQ 2nd gen. and Sulfur odor
    {
        .start         = 0x80,
        .h             = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 16, .data_buf = &gs_zmod4xxx_data_set_meas[0]},
        .d             = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 8, .data_buf = &gs_zmod4xxx_data_set_meas[16]},
        .m             = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 4, .data_buf = &gs_zmod4xxx_data_set_meas[24]},
        .s             = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 32, .data_buf = &gs_zmod4xxx_data_set_meas[28]},
        .r             = {.addr = 0x97,       .len = 32},
        .prod_data_len = RM_ZMOD4XXX_PROD_DATA_LEN,
    },
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6) // OAQ 1st gen
    {
        .start         = 0x80,
        .h             = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 10, .data_buf = &gs_zmod4xxx_data_set_meas[0]},
        .d             = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 6, .data_buf = &gs_zmod4xxx_data_set_meas[10]},
        .m             = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 1, .data_buf = &gs_zmod4xxx_data_set_meas[16]},
        .s             = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 30, .data_buf = &gs_zmod4xxx_data_set_meas[17]},
        .r             = {.addr = 0x97,       .len = 30},
        .prod_data_len = RM_ZMOD4XXX_PROD_DATA_LEN,
    },
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7) // OAQ 2nd gen
    {
        .start         = 0x80,
        .h             = {.addr = RM_ZMOD4XXX_H_ADDR, .len = 4, .data_buf = &gs_zmod4xxx_data_set_meas[0]},
        .d             = {.addr = RM_ZMOD4XXX_D_ADDR, .len = 2, .data_buf = &gs_zmod4xxx_data_set_meas[4]},
        .m             = {.addr = RM_ZMOD4XXX_M_ADDR, .len = 2, .data_buf = &gs_zmod4xxx_data_set_meas[6]},
        .s             = {.addr = RM_ZMOD4XXX_S_ADDR, .len = 18, .data_buf = &gs_zmod4xxx_data_set_meas[8]},
        .r             = {.addr = 0x97,       .len = 18},
        .prod_data_len = RM_ZMOD4XXX_PROD_DATA_LEN,
    },
#else
#endif
};

#endif                                 // RM_ZMOD4XXX_LIB_SPECIFIC_CONFIGURATION_H_
