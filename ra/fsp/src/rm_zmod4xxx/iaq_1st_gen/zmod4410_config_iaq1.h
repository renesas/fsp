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
