/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
  * @file zmod4410_config_pbaq.h
  * @brief This is the configuration for zmod4410 module - pbaq library
  * @author  Renesas Electronics Corporation
  * @version 2.1.0
  */

#ifndef _ZMOD4410_CONFIG_PBAQ_H
#define _ZMOD4410_CONFIG_PBAQ_H

#include <stdio.h>

#if TEST_RM_ZMOD4XXX  // For RA FSP test
 #include "../../../../../fsp/src/rm_zmod4xxx/zmod4xxx_types.h"
#else
 #include "../zmod4xxx_types.h"
#endif

#define INIT        0
#define MEASUREMENT 1

#define ZMOD4410_PID      0x2310
#define ZMOD4410_I2C_ADDR 0x32

// REMOVE Sequencer adresses
#define ZMOD4410_H_ADDR 0x40
#define ZMOD4410_D_ADDR 0x50
#define ZMOD4410_M_ADDR 0x60
#define ZMOD4410_S_ADDR 0x68

#define ZMOD4410_PROD_DATA_LEN 7
#define ZMOD4410_ADC_DATA_LEN  32

// time between consecutive samples
#define ZMOD4410_PBAQ_SAMPLE_TIME (5000U)

// clang-format off
static uint8_t data_set_4410i[] = {
// REMOVE                       heater
                                0x00, 0x50,
// REMOVE                       delay     , measurement
                                0x00, 0x28, 0xC3, 0xE3,
// REMOVE                       sequencer
                                0x00, 0x00, 0x80, 0x40};

// REMOVE This implements "SelectiveOdor_03ext(0_25).xml".
static uint8_t data_set_4410_pbaq[] = {
// REMOVE                              heater
                                       0x00, 0x50, 0xFF, 0x38,
                                       0xFE, 0xD4, 0xFE, 0x70,
                                       0xFE, 0x0C, 0xFD, 0xA8,
                                       0xFD, 0x44, 0xFC, 0xE0,
// REMOVE                              delay
                                       0x00, 0x14, 0x00, 0x9C,
                                       0x00, 0x31, 0x00, 0x39,
                                       0x00, 0xCD,
// REMOVE                              measurement
                                       0x23, 0x03, 0xA3, 0x43,
// REMOVE                              sequencer
                                       0x00, 0x00, 0x06, 0x49,
                                       0x06, 0x4A, 0x06, 0x4B,
                                       0x06, 0x4C, 0x06, 0x4D,
                                       0x06, 0x4E, 0x06, 0x97,
                                       0x06, 0xD7, 0x06, 0x5F,
                                       0x06, 0x4E, 0x06, 0x4D,
                                       0x06, 0x4C, 0x06, 0x4B,
                                       0x06, 0x4A, 0x86, 0x61};

// clang-format on

zmod4xxx_conf g_zmod4410_pbaq_sensor_type[] = {
    [INIT] = {
        .start = 0x80,
        .h = { .addr = ZMOD4410_H_ADDR, .len = 2, .data_buf = &data_set_4410i[0]},
        .d = { .addr = ZMOD4410_D_ADDR, .len = 2, .data_buf = &data_set_4410i[2]},
        .m = { .addr = ZMOD4410_M_ADDR, .len = 2, .data_buf = &data_set_4410i[4]},
        .s = { .addr = ZMOD4410_S_ADDR, .len = 4, .data_buf = &data_set_4410i[6]},
        .r = { .addr = 0x97, .len = 4},
    },

    [MEASUREMENT] = {
        .start = 0x80,
        .h = {.addr = ZMOD4410_H_ADDR, .len = 16, .data_buf = &data_set_4410_pbaq[0]},
        .d = {.addr = ZMOD4410_D_ADDR, .len = 10, .data_buf = &data_set_4410_pbaq[16]},
        .m = {.addr = ZMOD4410_M_ADDR, .len = 4, .data_buf = &data_set_4410_pbaq[26]},
        .s = {.addr = ZMOD4410_S_ADDR, .len = 32, .data_buf = &data_set_4410_pbaq[30]},
        .r = {.addr = 0x97, .len = 32},
        .prod_data_len = ZMOD4410_PROD_DATA_LEN,
    },
};

#endif //_ZMOD4410_CONFIG_PBAQ_H
