/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 * @file zmod4410_config_iaq1.h
 * @brief This is the configuration for zmod4410 module - iaq_1st_gen library
 * @version 2.1.2
 * @author Renesas Electronics Corporation
 */

#ifndef _ZMOD4410_CONFIG_IAQ1_H
#define _ZMOD4410_CONFIG_IAQ1_H

#include <stdio.h>
#include "../zmod4xxx_types.h"

#define ZMOD4410_H_ADDR           0x40
#define ZMOD4410_D_ADDR           0x50
#define ZMOD4410_M_ADDR           0x60
#define ZMOD4410_S_ADDR           0x68

#define ZMOD4410_PROD_DATA_LEN    6

static uint8_t data_set_4410i[] =
{
    0x00, 0x50,
    0x00, 0x28,0xC3,  0xE3,
    0x00, 0x00,0x80,  0x40
};

static uint8_t data_set_4410_cont[] =
{
    0xFD, 0xA8,
    0x20, 0x04,0x20,  0x04,
    0x03,
    0x00, 0x00,0x80,  0x08
};

static uint8_t data_set_4410_lpow[] =
{
    0x00, 0x50, 0xFD, 0XA8,
    0x00, 0xCD, 0x01, 0x9A,0x03,  0x34,
    0x23, 0x03,
    0x00, 0x00, 0x0A, 0x41,0x0A,  0x41,
    0x00, 0x41, 0x00, 0x41,0x00,  0x49,
    0x00, 0x49, 0x00, 0x51,0x00,  0x09,
    0x00, 0x49, 0x00, 0x40,0x00,  0x40,
    0x00, 0x40, 0x80, 0x40
};

zmod4xxx_conf g_zmod4410_iaq_1st_gen_sensor_type[] =
{
    {
        .start = 0x80,
        .h     = {.addr = ZMOD4410_H_ADDR, .len = 2,  .data_buf = &data_set_4410i[0]     },
        .d     = {.addr = ZMOD4410_D_ADDR, .len = 2,  .data_buf = &data_set_4410i[2]     },
        .m     = {.addr = ZMOD4410_M_ADDR, .len = 2,  .data_buf = &data_set_4410i[4]     },
        .s     = {.addr = ZMOD4410_S_ADDR, .len = 4,  .data_buf = &data_set_4410i[6]     },
        .r     = {.addr = 0x97,            .len = 4},
    },

    {
        .start         = 0xC0,
        .h             = {.addr = ZMOD4410_H_ADDR, .len = 2, .data_buf = &data_set_4410_cont[0]},
        .d             = {.addr = ZMOD4410_D_ADDR, .len = 4, .data_buf = &data_set_4410_cont[2]},
        .m             = {.addr = ZMOD4410_M_ADDR, .len = 1, .data_buf = &data_set_4410_cont[6]},
        .s             = {.addr = ZMOD4410_S_ADDR, .len = 4, .data_buf = &data_set_4410_cont[7]},
        .r             = {.addr = 0x99,    .len = 2},
        .prod_data_len = ZMOD4410_PROD_DATA_LEN,
    },
    {
        .start         = 0x80,
        .h             = {.addr = ZMOD4410_H_ADDR, .len = 4, .data_buf = &data_set_4410_lpow[0]},
        .d             = {.addr = ZMOD4410_D_ADDR, .len = 6, .data_buf = &data_set_4410_lpow[4]},
        .m             = {.addr = ZMOD4410_M_ADDR, .len = 2, .data_buf = &data_set_4410_lpow[10]},
        .s             = {.addr = ZMOD4410_S_ADDR, .len = 28, .data_buf = &data_set_4410_lpow[12]},
        .r             = {.addr = 0xA9,    .len = 2},
        .prod_data_len = ZMOD4410_PROD_DATA_LEN,
    }
};

#endif                                 // _ZMOD4410_CONFIG_IAQ1_H
