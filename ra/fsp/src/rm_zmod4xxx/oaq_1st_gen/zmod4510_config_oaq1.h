/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file    zmod4510_config_oaq1.h
 * @brief   This is the configuration for zmod4510 module - oaq 1st gen library
 * @author  Renesas Electronics Corporation
 * @version 3.0.0
 */

#ifndef _ZMOD4510_CONFIG_OAQ1_H_
#define _ZMOD4510_CONFIG_OAQ1_H_

#include <stdio.h>
#include "../zmod4xxx_types.h"

#define ZMOD4510_PROD_DATA_LEN    9

#define ZMOD4510_H_ADDR           (0x40)
#define ZMOD4510_D_ADDR           (0x50)
#define ZMOD4510_M_ADDR           (0x60)
#define ZMOD4510_S_ADDR           (0x68)

/* Zmod4510 OAQ 1st Gen Parameters */
#define D_RISING_M1               4.9601944386079566e-05
#define D_FALLING_M1              0.3934693402873666
#define D_CLASS_M1                0.024690087971667385
#define STABILIZATION_SAMPLES     60

static uint8_t dataset_4510_init[] =
{
    0x00, 0x50,
    0x00, 0x28,
    0xC3, 0xE3,
    0x00, 0x00,0x80,  0x40,
};

static uint8_t dataset_4510_oaq_1st_gen[] =
{
    0xFE, 0x48, 0xFE, 0X16,
    0xFD, 0xE4, 0XFD, 0xB2,
    0xFD, 0x80,
    0x20, 0x05, 0xA0, 0x18,
    0xC0, 0x1C,
    0x03,
    0x00, 0x00, 0x00, 0x08,
    0x00, 0x10, 0x00, 0x01,
    0x00, 0x09, 0x00, 0x11,
    0x00, 0x02, 0x00, 0x0A,
    0x00, 0x12, 0x00, 0x03,
    0x00, 0x0B, 0x00, 0x13,
    0x00, 0x04, 0x00, 0x0C,
    0x80, 0x14,
};

zmod4xxx_conf g_zmod4510_oaq_1st_gen_sensor_type[] =
{
    {
        .start = 0x80,
        .h     = {.addr = ZMOD4510_H_ADDR, .len = 2,  .data_buf = &dataset_4510_init[0]        },
        .d     = {.addr = ZMOD4510_D_ADDR, .len = 2,  .data_buf = &dataset_4510_init[2]        },
        .m     = {.addr = ZMOD4510_M_ADDR, .len = 2,  .data_buf = &dataset_4510_init[4]        },
        .s     = {.addr = ZMOD4510_S_ADDR, .len = 4,  .data_buf = &dataset_4510_init[6]        },
        .r     = {.addr = 0x97,            .len = 4},
    },
    {
        .start         = 0x80,
        .h             = {.addr = ZMOD4510_H_ADDR, .len = 10, .data_buf = &dataset_4510_oaq_1st_gen[0]},
        .d             = {.addr = ZMOD4510_D_ADDR, .len = 6, .data_buf = &dataset_4510_oaq_1st_gen[10]},
        .m             = {.addr = ZMOD4510_M_ADDR, .len = 1, .data_buf = &dataset_4510_oaq_1st_gen[16]},
        .s             = {.addr = ZMOD4510_S_ADDR, .len = 30, .data_buf = &dataset_4510_oaq_1st_gen[17]},
        .r             = {.addr = 0x97,    .len = 30},
        .prod_data_len = ZMOD4510_PROD_DATA_LEN,
    },
};

#endif                                 // _ZMOD4510_CONFIG_OAQ1_H_
