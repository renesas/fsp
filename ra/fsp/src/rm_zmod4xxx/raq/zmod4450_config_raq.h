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
 * @file    zmod4450_config_raq.h
 * @brief   This is the configuration for zmod4450 module - raq library
 * @author Renesas Electronics Corporation
 * @version 2.0.0
 */

#ifndef ZMOD4450_CONFIG_RAQ
#define ZMOD4450_CONFIG_RAQ

#include <stdio.h>
#if 0                                  // For multiple operations
 #include "zmod4xxx_types.h"
#else
 #include "../zmod4xxx_types.h"
#endif

#define INIT                      0
#define MEASURE                   1

/**********************************/
/* < Define prodoct data length > */
#define ZMOD4450_PID              0x7310

/**********************************/
/* < Define prodoct data length > */
#define ZMOD4450_I2C_ADDR         0x32

/**********************************/
/* < Define prodoct data length > */
#define ZMOD4450_PROD_DATA_LEN    5

/*************************************/
/* < Define ADC result data length > */
#define ZMOD4450_ADC_DATA_LEN     2

// REMOVE Sequencer adresses
#define ZMOD4450_H_ADDR           0x40
#define ZMOD4450_D_ADDR           0x50
#define ZMOD4450_M_ADDR           0x60
#define ZMOD4450_S_ADDR           0x68

// clang-format off
static uint8_t data_set_4450_init[] =
{
// REMOVE                       heater
    0x00, 0x50,

// REMOVE                       delay
    0x00, 0x28,

// REMOVE                       measurement
    0xC3, 0xE3,

// REMOVE                       sequencer
    0x00, 0x00,0x80, 0x40
};

static uint8_t data_set_4450[] =
{
// REMOVE                       heater
    0xFD, 0xA8,

// REMOVE                       delay
    0x20, 0x04,0x40,  0x09,

// REMOVE                       measurement
    0x03,

// REMOVE                       sequencer
    0x00, 0x00,0x80,  0x08
};

// clang-format on
zmod4xxx_conf g_zmod4450_raq_sensor_type[] =
{
    [INIT] =
    {
    .start = 0x80,
    .h     = {.addr = ZMOD4450_H_ADDR, .len   = 2, .data_buf = &data_set_4450_init[0]},
    .d     = {.addr = ZMOD4450_D_ADDR, .len   = 2, .data_buf = &data_set_4450_init[2]},
    .m     = {.addr = ZMOD4450_M_ADDR, .len   = 2, .data_buf = &data_set_4450_init[4]},
    .s     = {.addr = ZMOD4450_S_ADDR, .len   = 4, .data_buf = &data_set_4450_init[6]},
    .r     = {.addr = 0x97,  .len             = 4},
    },

    [MEASURE] =
    {
    .start         = 0xC0,
    .h             = {.addr = ZMOD4450_H_ADDR, .len          = 2, .data_buf = &data_set_4450[0]     },
    .d             = {.addr = ZMOD4450_D_ADDR, .len          = 4, .data_buf = &data_set_4450[2]     },
    .m             = {.addr = ZMOD4450_M_ADDR, .len          = 1, .data_buf = &data_set_4450[6]     },
    .s             = {.addr = ZMOD4450_S_ADDR, .len          = 4, .data_buf = &data_set_4450[7]     },
    .r             = {.addr = 0x99,         .len             = 2},
    .prod_data_len = ZMOD4450_PROD_DATA_LEN,
    },
};

#endif                                 /* ZMOD4450_CONFIG_RAQ */
