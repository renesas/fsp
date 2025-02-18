/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    zmod4510_config_ulp_o3.h
 * @brief   This is the configuration for ZMOD4510 module - ulp_o3 library
 * @author Renesas Electronics Corporation
 * @version 5.0.0
 */

#ifndef _ZMOD4510_CONFIG_ULP_O3_H_
#define _ZMOD4510_CONFIG_ULP_O3_H_

#include <stdio.h>

#if TEST_RM_ZMOD4XXX  // For RA FSP test
 #include "../../../../../fsp/src/rm_zmod4xxx/zmod4xxx_types.h"
#else
 #include "../zmod4xxx_types.h"
#endif

#define INIT        0
#define MEASUREMENT 1

/**********************************/
/* < Define product ID > */
#define ZMOD4510_PID 0x6320

/**********************************/
/* < Define I2C slase address > */
#define ZMOD4510_I2C_ADDR 0x33

/**********************************/
/* < Define product data length > */
#define ZMOD4510_PROD_DATA_LEN 10

/*************************************/
/* < Define ADC result data length > */
#define ZMOD4510_ADC_DATA_LEN 18

// time between samples
#define ZMOD4510_ULP_O3_SAMPLE_TIME (2000U)

// REMOVE Sequencer adresses
#define ZMOD4XXX_H_ADDR 0x40
#define ZMOD4XXX_D_ADDR 0x50
#define ZMOD4XXX_M_ADDR 0x60
#define ZMOD4XXX_S_ADDR 0x68

// clang-format off
static uint8_t data_set_4510_init[] = {
// REMOVE                       heater
                                0x00, 0x50,
// REMOVE                       delay     , measurement
                                0x00, 0x28, 0xC3, 0xE3,
// REMOVE                       sequencer
                                0x00, 0x00, 0x80, 0x40};

static uint8_t data_set_4510_ulp_o3[] = {
// REMOVE this implements the ULP_NN_05.xml sequence
// REMOVE                       heater
                                0x00, 0x50, 0xFE, 0x70,
// REMOVE                       delay
                                0x00, 0x10,
// REMOVE                       measurement
                                0x23, 0x03,
// REMOVE                       sequencer
                                0x00, 0x00, 0x06, 0x41,
                                0x06, 0x41, 0x06, 0x41,
                                0x06, 0x41, 0x06, 0x41,
                                0x06, 0x41, 0x06, 0x41,
                                0x86, 0x41
                                };

// clang-format on
zmod4xxx_conf g_zmod4510_ulp_o3_sensor_type[] = 
{
    [INIT] = {
        .start = 0x80,
        .h = { .addr = ZMOD4XXX_H_ADDR, .len = 2, .data_buf = &data_set_4510_init[0]},
        .d = { .addr = ZMOD4XXX_D_ADDR, .len = 2, .data_buf = &data_set_4510_init[2]},
        .m = { .addr = ZMOD4XXX_M_ADDR, .len = 2, .data_buf = &data_set_4510_init[4]},
        .s = { .addr = ZMOD4XXX_S_ADDR, .len = 4, .data_buf = &data_set_4510_init[6]},
        .r = { .addr = 0x97, .len = 4},
    },

    [MEASUREMENT] = {
        .start = 0x80,
        .h = {.addr = ZMOD4XXX_H_ADDR, .len = 4, .data_buf = &data_set_4510_ulp_o3[0]},
        .d = {.addr = ZMOD4XXX_D_ADDR, .len = 2, .data_buf = &data_set_4510_ulp_o3[4]},
        .m = {.addr = ZMOD4XXX_M_ADDR, .len = 2, .data_buf = &data_set_4510_ulp_o3[6]},
        .s = {.addr = ZMOD4XXX_S_ADDR, .len = 18, .data_buf = &data_set_4510_ulp_o3[8]},
        .r = {.addr = 0x97, .len = 18},
        .prod_data_len = ZMOD4510_PROD_DATA_LEN,
    },
};

#endif //_ZMOD4510_CONFIG_ULP_O3_H_
