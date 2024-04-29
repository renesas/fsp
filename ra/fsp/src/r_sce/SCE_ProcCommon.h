/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef  __SCE_ProcCommon_h__
#define  __SCE_ProcCommon_h__

#include  <stdint.h>

#include "bsp_api.h"                   /* For Crypto Error codes */
#include "SCE_module.h"

/* ================================================================================ */
/* ================                      SCE                      ================ */
/* ================================================================================ */

/**
 * @brief Trusted Security IP (SCE)
 */
typedef struct
{
    union
    {
        __IOM uint32_t REG_00H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_00H_b;
    };
    union
    {
        __IOM uint32_t REG_04H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_04H_b;
    };
    union
    {
        __IOM uint32_t REG_08H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_08H_b;
    };
    union
    {
        __IOM uint32_t REG_0CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_0CH_b;
    };
    union
    {
        __IOM uint32_t REG_10H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_10H_b;
    };
    union
    {
        __IOM uint32_t REG_14H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_14H_b;
    };
    union
    {
        __IOM uint32_t REG_18H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_18H_b;
    };
    union
    {
        __IOM uint32_t REG_1CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1CH_b;
    };
    union
    {
        __IOM uint32_t REG_20H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_20H_b;
    };
    union
    {
        __IOM uint32_t REG_24H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_24H_b;
    };
    union
    {
        __IOM uint32_t REG_28H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_28H_b;
    };
    union
    {
        __IOM uint32_t REG_2CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_2CH_b;
    };
    union
    {
        __IOM uint32_t REG_30H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_30H_b;
    };
    union
    {
        __IOM uint32_t REG_34H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_34H_b;
    };
    union
    {
        __IOM uint32_t REG_38H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_38H_b;
    };
    union
    {
        __IOM uint32_t REG_3CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_3CH_b;
    };
    union
    {
        __IOM uint32_t REG_40H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_40H_b;
    };
    union
    {
        __IOM uint32_t REG_44H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_44H_b;
    };
    union
    {
        __IOM uint32_t REG_48H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_48H_b;
    };
    union
    {
        __IOM uint32_t REG_4CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_4CH_b;
    };
    union
    {
        __IOM uint32_t REG_50H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_50H_b;
    };
    union
    {
        __IOM uint32_t REG_54H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_54H_b;
    };
    union
    {
        __IOM uint32_t REG_58H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_58H_b;
    };
    union
    {
        __IOM uint32_t REG_5CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_5CH_b;
    };
    union
    {
        __IOM uint32_t REG_60H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_60H_b;
    };
    union
    {
        __IOM uint32_t REG_64H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_64H_b;
    };
    union
    {
        __IOM uint32_t REG_68H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_68H_b;
    };
    union
    {
        __IOM uint32_t REG_6CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_6CH_b;
    };
    union
    {
        __IOM uint32_t REG_70H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_70H_b;
    };
    union
    {
        __IOM uint32_t REG_74H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_74H_b;
    };
    union
    {
        __IOM uint32_t REG_78H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_78H_b;
    };
    union
    {
        __IOM uint32_t REG_7CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_7CH_b;
    };
    union
    {
        __IOM uint32_t REG_80H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_80H_b;
    };
    union
    {
        __IOM uint32_t REG_84H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_84H_b;
    };
    union
    {
        __IOM uint32_t REG_88H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_88H_b;
    };
    union
    {
        __IOM uint32_t REG_8CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_8CH_b;
    };
    union
    {
        __IOM uint32_t REG_90H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_90H_b;
    };
    union
    {
        __IOM uint32_t REG_94H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_94H_b;
    };
    union
    {
        __IOM uint32_t REG_98H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_98H_b;
    };
    union
    {
        __IOM uint32_t REG_9CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_9CH_b;
    };
    union
    {
        __IOM uint32_t REG_A0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_A0H_b;
    };
    union
    {
        __IOM uint32_t REG_A4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_A4H_b;
    };
    union
    {
        __IOM uint32_t REG_A8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_A8H_b;
    };
    union
    {
        __IOM uint32_t REG_ACH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_ACH_b;
    };
    union
    {
        __IOM uint32_t REG_B0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_B0H_b;
    };
    union
    {
        __IOM uint32_t REG_B4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_B4H_b;
    };
    union
    {
        __IOM uint32_t REG_B8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_B8H_b;
    };
    union
    {
        __IOM uint32_t REG_BCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_BCH_b;
    };
    union
    {
        __IOM uint32_t REG_C0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_C0H_b;
    };
    union
    {
        __IOM uint32_t REG_C4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_C4H_b;
    };
    union
    {
        __IOM uint32_t REG_C8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_C8H_b;
    };
    union
    {
        __IOM uint32_t REG_CCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_CCH_b;
    };
    union
    {
        __IOM uint32_t REG_D0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_D0H_b;
    };
    union
    {
        __IOM uint32_t REG_D4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_D4H_b;
    };
    union
    {
        __IOM uint32_t REG_D8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_D8H_b;
    };
    union
    {
        __IOM uint32_t REG_DCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_DCH_b;
    };
    union
    {
        __IOM uint32_t REG_E0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_E0H_b;
    };
    union
    {
        __IOM uint32_t REG_E4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_E4H_b;
    };
    union
    {
        __IOM uint32_t REG_E8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_E8H_b;
    };
    union
    {
        __IOM uint32_t REG_ECH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_ECH_b;
    };
    union
    {
        __IOM uint32_t REG_F0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_F0H_b;
    };
    union
    {
        __IOM uint32_t REG_F4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_F4H_b;
    };
    union
    {
        __IOM uint32_t REG_F8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_F8H_b;
    };
    union
    {
        __IOM uint32_t REG_FCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_FCH_b;
    };
    union
    {
        __IOM uint32_t REG_100H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_100H_b;
    };
    union
    {
        __IOM uint32_t REG_104H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_104H_b;
    };
    union
    {
        __IOM uint32_t REG_108H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_108H_b;
    };
    union
    {
        __IOM uint32_t REG_10CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_10CH_b;
    };
    union
    {
        __IOM uint32_t REG_110H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_110H_b;
    };
    union
    {
        __IOM uint32_t REG_114H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_114H_b;
    };
    union
    {
        __IOM uint32_t REG_118H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_118H_b;
    };
    union
    {
        __IOM uint32_t REG_11CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_11CH_b;
    };
    union
    {
        __IOM uint32_t REG_120H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_120H_b;
    };
    union
    {
        __IOM uint32_t REG_124H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_124H_b;
    };
    union
    {
        __IOM uint32_t REG_128H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_128H_b;
    };
    union
    {
        __IOM uint32_t REG_12CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_12CH_b;
    };
    union
    {
        __IOM uint32_t REG_130H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_130H_b;
    };
    union
    {
        __IOM uint32_t REG_134H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_134H_b;
    };
    union
    {
        __IOM uint32_t REG_138H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_138H_b;
    };
    union
    {
        __IOM uint32_t REG_13CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_13CH_b;
    };
    union
    {
        __IOM uint32_t REG_140H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_140H_b;
    };
    union
    {
        __IOM uint32_t REG_144H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_144H_b;
    };
    union
    {
        __IOM uint32_t REG_148H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_148H_b;
    };
    union
    {
        __IOM uint32_t REG_14CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_14CH_b;
    };
    union
    {
        __IOM uint32_t REG_150H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_150H_b;
    };
    union
    {
        __IOM uint32_t REG_154H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_154H_b;
    };
    union
    {
        __IOM uint32_t REG_158H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_158H_b;
    };
    union
    {
        __IOM uint32_t REG_15CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_15CH_b;
    };
    union
    {
        __IOM uint32_t REG_160H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_160H_b;
    };
    union
    {
        __IOM uint32_t REG_164H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_164H_b;
    };
    union
    {
        __IOM uint32_t REG_168H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_168H_b;
    };
    union
    {
        __IOM uint32_t REG_16CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_16CH_b;
    };
    union
    {
        __IOM uint32_t REG_170H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_170H_b;
    };
    union
    {
        __IOM uint32_t REG_174H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_174H_b;
    };
    union
    {
        __IOM uint32_t REG_178H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_178H_b;
    };
    union
    {
        __IOM uint32_t REG_17CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_17CH_b;
    };
    union
    {
        __IOM uint32_t REG_180H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_180H_b;
    };
    union
    {
        __IOM uint32_t REG_184H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_184H_b;
    };
    union
    {
        __IOM uint32_t REG_188H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_188H_b;
    };
    union
    {
        __IOM uint32_t REG_18CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_18CH_b;
    };
    union
    {
        __IOM uint32_t REG_190H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_190H_b;
    };
    union
    {
        __IOM uint32_t REG_194H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_194H_b;
    };
    union
    {
        __IOM uint32_t REG_198H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_198H_b;
    };
    union
    {
        __IOM uint32_t REG_19CH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_19CH_b;
    };
    union
    {
        __IOM uint32_t REG_1A0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1A0H_b;
    };
    union
    {
        __IOM uint32_t REG_1A4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1A4H_b;
    };
    union
    {
        __IOM uint32_t REG_1A8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1A8H_b;
    };
    union
    {
        __IOM uint32_t REG_1ACH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1ACH_b;
    };
    union
    {
        __IOM uint32_t REG_1B0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1B0H_b;
    };
    union
    {
        __IOM uint32_t REG_1B4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1B4H_b;
    };
    union
    {
        __IOM uint32_t REG_1B8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1B8H_b;
    };
    union
    {
        __IOM uint32_t REG_1BCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1BCH_b;
    };
    union
    {
        __IOM uint32_t REG_1C0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1C0H_b;
    };
    union
    {
        __IOM uint32_t REG_1C4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1C4H_b;
    };
    union
    {
        __IOM uint32_t REG_1C8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1C8H_b;
    };
    union
    {
        __IOM uint32_t REG_1CCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1CCH_b;
    };
    union
    {
        __IOM uint32_t REG_1D0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1D0H_b;
    };
    union
    {
        __IOM uint32_t REG_1D4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1D4H_b;
    };
    union
    {
        __IOM uint32_t REG_1D8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1D8H_b;
    };
    union
    {
        __IOM uint32_t REG_1DCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1DCH_b;
    };
    union
    {
        __IOM uint32_t REG_1E0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1E0H_b;
    };
    union
    {
        __IOM uint32_t REG_1E4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1E4H_b;
    };
    union
    {
        __IOM uint32_t REG_1E8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1E8H_b;
    };
    union
    {
        __IOM uint32_t REG_1ECH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1ECH_b;
    };
    union
    {
        __IOM uint32_t REG_1F0H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1F0H_b;
    };
    union
    {
        __IOM uint32_t REG_1F4H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1F4H_b;
    };
    union
    {
        __IOM uint32_t REG_1F8H;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1F8H_b;
    };
    union
    {
        __IOM uint32_t REG_1FCH;
        struct
        {
            __IOM uint32_t B0  : 1;
            __IOM uint32_t B1  : 1;
            __IOM uint32_t B2  : 1;
            __IOM uint32_t B3  : 1;
            __IOM uint32_t B4  : 1;
            __IOM uint32_t B5  : 1;
            __IOM uint32_t B6  : 1;
            __IOM uint32_t B7  : 1;
            __IOM uint32_t B8  : 1;
            __IOM uint32_t B9  : 1;
            __IOM uint32_t B10 : 1;
            __IOM uint32_t B11 : 1;
            __IOM uint32_t B12 : 1;
            __IOM uint32_t B13 : 1;
            __IOM uint32_t B14 : 1;
            __IOM uint32_t B15 : 1;
            __IOM uint32_t B16 : 1;
            __IOM uint32_t B17 : 1;
            __IOM uint32_t B18 : 1;
            __IOM uint32_t B19 : 1;
            __IOM uint32_t B20 : 1;
            __IOM uint32_t B21 : 1;
            __IOM uint32_t B22 : 1;
            __IOM uint32_t B23 : 1;
            __IOM uint32_t B24 : 1;
            __IOM uint32_t B25 : 1;
            __IOM uint32_t B26 : 1;
            __IOM uint32_t B27 : 1;
            __IOM uint32_t B28 : 1;
            __IOM uint32_t B29 : 1;
            __IOM uint32_t B30 : 1;
            __IOM uint32_t B31 : 1;
        } REG_1FCH_b;
    };
} SCE_Type;

// for bit access

/* --------------------------------  SCE.REG_xxxH  -------------------------------- */
#define SCE_REG_0_Pos     0                          /*!< SCE REG_xxxH: bit 0 Position       */
#define SCE_REG_0_Msk     (0x01UL << SCE_REG_0_Pos)  /*!< SCE REG_xxxH: bit 0 Mask           */
#define SCE_REG_1_Pos     1                          /*!< SCE REG_xxxH: bit 1 Position       */
#define SCE_REG_1_Msk     (0x01UL << SCE_REG_1_Pos)  /*!< SCE REG_xxxH: bit 1 Mask           */
#define SCE_REG_2_Pos     2                          /*!< SCE REG_xxxH: bit 2 Position       */
#define SCE_REG_2_Msk     (0x01UL << SCE_REG_2_Pos)  /*!< SCE REG_xxxH: bit 2 Mask           */
#define SCE_REG_3_Pos     3                          /*!< SCE REG_xxxH: bit 3 Position       */
#define SCE_REG_3_Msk     (0x01UL << SCE_REG_3_Pos)  /*!< SCE REG_xxxH: bit 3 Mask           */
#define SCE_REG_4_Pos     4                          /*!< SCE REG_xxxH: bit 4 Position       */
#define SCE_REG_4_Msk     (0x01UL << SCE_REG_4_Pos)  /*!< SCE REG_xxxH: bit 4 Mask           */
#define SCE_REG_5_Pos     5                          /*!< SCE REG_xxxH: bit 5 Position       */
#define SCE_REG_5_Msk     (0x01UL << SCE_REG_5_Pos)  /*!< SCE REG_xxxH: bit 5 Mask           */
#define SCE_REG_6_Pos     6                          /*!< SCE REG_xxxH: bit 6 Position       */
#define SCE_REG_6_Msk     (0x01UL << SCE_REG_6_Pos)  /*!< SCE REG_xxxH: bit 6 Mask           */
#define SCE_REG_7_Pos     7                          /*!< SCE REG_xxxH: bit 7 Position       */
#define SCE_REG_7_Msk     (0x01UL << SCE_REG_7_Pos)  /*!< SCE REG_xxxH: bit 7 Mask           */
#define SCE_REG_8_Pos     8                          /*!< SCE REG_xxxH: bit 8 Position       */
#define SCE_REG_8_Msk     (0x01UL << SCE_REG_8_Pos)  /*!< SCE REG_xxxH: bit 8 Mask           */
#define SCE_REG_9_Pos     9                          /*!< SCE REG_xxxH: bit 9 Position       */
#define SCE_REG_9_Msk     (0x01UL << SCE_REG_9_Pos)  /*!< SCE REG_xxxH: bit 9 Mask           */
#define SCE_REG_10_Pos    10                         /*!< SCE REG_xxxH: bit 10 Position       */
#define SCE_REG_10_Msk    (0x01UL << SCE_REG_10_Pos) /*!< SCE REG_xxxH: bit 10 Mask           */
#define SCE_REG_11_Pos    11                         /*!< SCE REG_xxxH: bit 11 Position       */
#define SCE_REG_11_Msk    (0x01UL << SCE_REG_11_Pos) /*!< SCE REG_xxxH: bit 11 Mask           */
#define SCE_REG_12_Pos    12                         /*!< SCE REG_xxxH: bit 12 Position       */
#define SCE_REG_12_Msk    (0x01UL << SCE_REG_12_Pos) /*!< SCE REG_xxxH: bit 12 Mask           */
#define SCE_REG_13_Pos    13                         /*!< SCE REG_xxxH: bit 13 Position       */
#define SCE_REG_13_Msk    (0x01UL << SCE_REG_13_Pos) /*!< SCE REG_xxxH: bit 13 Mask           */
#define SCE_REG_14_Pos    14                         /*!< SCE REG_xxxH: bit 14 Position       */
#define SCE_REG_14_Msk    (0x01UL << SCE_REG_14_Pos) /*!< SCE REG_xxxH: bit 14 Mask           */
#define SCE_REG_15_Pos    15                         /*!< SCE REG_xxxH: bit 15 Position       */
#define SCE_REG_15_Msk    (0x01UL << SCE_REG_15_Pos) /*!< SCE REG_xxxH: bit 15 Mask           */
#define SCE_REG_16_Pos    16                         /*!< SCE REG_xxxH: bit 16 Position       */
#define SCE_REG_16_Msk    (0x01UL << SCE_REG_16_Pos) /*!< SCE REG_xxxH: bit 16 Mask           */
#define SCE_REG_17_Pos    17                         /*!< SCE REG_xxxH: bit 17 Position       */
#define SCE_REG_17_Msk    (0x01UL << SCE_REG_17_Pos) /*!< SCE REG_xxxH: bit 17 Mask           */
#define SCE_REG_18_Pos    18                         /*!< SCE REG_xxxH: bit 18 Position       */
#define SCE_REG_18_Msk    (0x01UL << SCE_REG_18_Pos) /*!< SCE REG_xxxH: bit 18 Mask           */
#define SCE_REG_19_Pos    19                         /*!< SCE REG_xxxH: bit 19 Position       */
#define SCE_REG_19_Msk    (0x01UL << SCE_REG_19_Pos) /*!< SCE REG_xxxH: bit 19 Mask           */
#define SCE_REG_20_Pos    20                         /*!< SCE REG_xxxH: bit 20 Position       */
#define SCE_REG_20_Msk    (0x01UL << SCE_REG_20_Pos) /*!< SCE REG_xxxH: bit 20 Mask           */
#define SCE_REG_21_Pos    21                         /*!< SCE REG_xxxH: bit 21 Position       */
#define SCE_REG_21_Msk    (0x01UL << SCE_REG_21_Pos) /*!< SCE REG_xxxH: bit 21 Mask           */
#define SCE_REG_22_Pos    22                         /*!< SCE REG_xxxH: bit 22 Position       */
#define SCE_REG_22_Msk    (0x01UL << SCE_REG_22_Pos) /*!< SCE REG_xxxH: bit 22 Mask           */
#define SCE_REG_23_Pos    23                         /*!< SCE REG_xxxH: bit 23 Position       */
#define SCE_REG_23_Msk    (0x01UL << SCE_REG_23_Pos) /*!< SCE REG_xxxH: bit 23 Mask           */
#define SCE_REG_24_Pos    24                         /*!< SCE REG_xxxH: bit 24 Position       */
#define SCE_REG_24_Msk    (0x01UL << SCE_REG_24_Pos) /*!< SCE REG_xxxH: bit 24 Mask           */
#define SCE_REG_25_Pos    25                         /*!< SCE REG_xxxH: bit 25 Position       */
#define SCE_REG_25_Msk    (0x01UL << SCE_REG_25_Pos) /*!< SCE REG_xxxH: bit 25 Mask           */
#define SCE_REG_26_Pos    26                         /*!< SCE REG_xxxH: bit 26 Position       */
#define SCE_REG_26_Msk    (0x01UL << SCE_REG_26_Pos) /*!< SCE REG_xxxH: bit 26 Mask           */
#define SCE_REG_27_Pos    27                         /*!< SCE REG_xxxH: bit 27 Position       */
#define SCE_REG_27_Msk    (0x01UL << SCE_REG_27_Pos) /*!< SCE REG_xxxH: bit 27 Mask           */
#define SCE_REG_28_Pos    28                         /*!< SCE REG_xxxH: bit 28 Position       */
#define SCE_REG_28_Msk    (0x01UL << SCE_REG_28_Pos) /*!< SCE REG_xxxH: bit 28 Mask           */
#define SCE_REG_29_Pos    29                         /*!< SCE REG_xxxH: bit 29 Position       */
#define SCE_REG_29_Msk    (0x01UL << SCE_REG_29_Pos) /*!< SCE REG_xxxH: bit 29 Mask           */
#define SCE_REG_30_Pos    30                         /*!< SCE REG_xxxH: bit 30 Position       */
#define SCE_REG_30_Msk    (0x01UL << SCE_REG_30_Pos) /*!< SCE REG_xxxH: bit 30 Mask           */
#define SCE_REG_31_Pos    31                         /*!< SCE REG_xxxH: bit 31 Position       */
#define SCE_REG_31_Msk    (0x01UL << SCE_REG_31_Pos) /*!< SCE REG_xxxH: bit 31 Mask           */

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define SCE    ((SCE_Type *) SCE_BASE)

// macro definishion

#define SCE_DELAY(delay)                                      \
    for (volatile uint32_t count = 0; count < delay; count++) \
    {                                                         \
        ;                                                     \
    }

// [R RD 1 B]
#define  RD1_PROG(regName) \
    (SCE->regName)

// [R WR 1 B]
#define  WR1_PROG(regName, value) \
    SCE->regName = value

// [R WR 2 B0 B1]
#define  WR2_PROG(regName, value0, value1) \
    WR1_PROG(regName, value0);             \
    WR1_PROG(regName, value1);

// [R WR 3 B0 B1 B2]
#define  WR3_PROG(regName, value0, value1, value2) \
    WR1_PROG(regName, value0);                     \
    WR1_PROG(regName, value1);                     \
    WR1_PROG(regName, value2)

// [R WR 4 B0 B1 B2 B3]
#define  WR4_PROG(regName, value0, value1, value2, value3) \
    WR1_PROG(regName, value0);                             \
    WR1_PROG(regName, value1);                             \
    WR1_PROG(regName, value2);                             \
    WR1_PROG(regName, value3)

// [R WR 16 B0 B1 B2 B3 B4 B5 B6 B7 B8 B9 B10 B11 B12 B13 B14 B15]
#define  WR16_PROG(regName,     \
                   value0,      \
                   value1,      \
                   value2,      \
                   value3,      \
                   value4,      \
                   value5,      \
                   value6,      \
                   value7,      \
                   value8,      \
                   value9,      \
                   value10,     \
                   value11,     \
                   value12,     \
                   value13,     \
                   value14,     \
                   value15)     \
    WR1_PROG(regName, value0);  \
    WR1_PROG(regName, value1);  \
    WR1_PROG(regName, value2);  \
    WR1_PROG(regName, value3);  \
    WR1_PROG(regName, value4);  \
    WR1_PROG(regName, value5);  \
    WR1_PROG(regName, value6);  \
    WR1_PROG(regName, value7);  \
    WR1_PROG(regName, value8);  \
    WR1_PROG(regName, value9);  \
    WR1_PROG(regName, value10); \
    WR1_PROG(regName, value11); \
    WR1_PROG(regName, value12); \
    WR1_PROG(regName, value13); \
    WR1_PROG(regName, value14); \
    WR1_PROG(regName, value15)

// [R RD 1 B]
#define  RD1_EVAL(regName, value) \
    if (SCE->regname != value)    \
        return FSP_ERR_CRYPTO_SCE_FAIL

// [R CHK_STATUS A B]
#define  CHCK_STS(regName, bitPos, value) \
    (((SCE->regName & (0x01UL << bitPos)) >> bitPos) == value)

// [R CHK_REG A (!= B)]
#define  RD1_MASK(regName, maskValue) \
    (SCE->regName & maskValue)

// [R WAIT_STATUS A B]
#define  WAIT_STS(regName, bitPos, value) \
    while (!CHCK_STS(regName, bitPos, value))

// [R WR 1 MEM[Ofs]]
#define  WR1_ADDR(regName, addr) \
    SCE->regName = *(addr)

// [R WR 2 MEM[Ofs]]
#define  WR2_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1);

// [R WR 3 MEM[Ofs]]
#define  WR3_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2);

// [R WR 4 MEM[Ofs]]
#define  WR4_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3)

// [R WR 5 MEM[Ofs]]
#define  WR5_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4)

// [R WR 6 MEM[Ofs]]
#define  WR6_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5)

// [R WR 7 MEM[Ofs]]
#define  WR7_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5); \
    WR1_ADDR(regName, (addr) + 6)

// [R WR 8 MEM[Ofs]]
#define  WR8_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5); \
    WR1_ADDR(regName, (addr) + 6); \
    WR1_ADDR(regName, (addr) + 7)

// [R WR 12 MEM[Ofs]]
#define  WR12_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11)

// [R WR 16 MEM[Ofs]]
#define  WR16_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15)

// [R WR 32 MEM[Ofs]]
#define  WR32_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15); \
    WR1_ADDR(regName, (addr) + 16); \
    WR1_ADDR(regName, (addr) + 17); \
    WR1_ADDR(regName, (addr) + 18); \
    WR1_ADDR(regName, (addr) + 19); \
    WR1_ADDR(regName, (addr) + 20); \
    WR1_ADDR(regName, (addr) + 21); \
    WR1_ADDR(regName, (addr) + 22); \
    WR1_ADDR(regName, (addr) + 23); \
    WR1_ADDR(regName, (addr) + 24); \
    WR1_ADDR(regName, (addr) + 25); \
    WR1_ADDR(regName, (addr) + 26); \
    WR1_ADDR(regName, (addr) + 27); \
    WR1_ADDR(regName, (addr) + 28); \
    WR1_ADDR(regName, (addr) + 29); \
    WR1_ADDR(regName, (addr) + 30); \
    WR1_ADDR(regName, (addr) + 31)

// [R WR 64 MEM[Ofs]]
#define  WR64_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15); \
    WR1_ADDR(regName, (addr) + 16); \
    WR1_ADDR(regName, (addr) + 17); \
    WR1_ADDR(regName, (addr) + 18); \
    WR1_ADDR(regName, (addr) + 19); \
    WR1_ADDR(regName, (addr) + 20); \
    WR1_ADDR(regName, (addr) + 21); \
    WR1_ADDR(regName, (addr) + 22); \
    WR1_ADDR(regName, (addr) + 23); \
    WR1_ADDR(regName, (addr) + 24); \
    WR1_ADDR(regName, (addr) + 25); \
    WR1_ADDR(regName, (addr) + 26); \
    WR1_ADDR(regName, (addr) + 27); \
    WR1_ADDR(regName, (addr) + 28); \
    WR1_ADDR(regName, (addr) + 29); \
    WR1_ADDR(regName, (addr) + 30); \
    WR1_ADDR(regName, (addr) + 31); \
    WR1_ADDR(regName, (addr) + 32); \
    WR1_ADDR(regName, (addr) + 33); \
    WR1_ADDR(regName, (addr) + 34); \
    WR1_ADDR(regName, (addr) + 35); \
    WR1_ADDR(regName, (addr) + 36); \
    WR1_ADDR(regName, (addr) + 37); \
    WR1_ADDR(regName, (addr) + 38); \
    WR1_ADDR(regName, (addr) + 39); \
    WR1_ADDR(regName, (addr) + 40); \
    WR1_ADDR(regName, (addr) + 41); \
    WR1_ADDR(regName, (addr) + 42); \
    WR1_ADDR(regName, (addr) + 43); \
    WR1_ADDR(regName, (addr) + 44); \
    WR1_ADDR(regName, (addr) + 45); \
    WR1_ADDR(regName, (addr) + 46); \
    WR1_ADDR(regName, (addr) + 47); \
    WR1_ADDR(regName, (addr) + 48); \
    WR1_ADDR(regName, (addr) + 49); \
    WR1_ADDR(regName, (addr) + 50); \
    WR1_ADDR(regName, (addr) + 51); \
    WR1_ADDR(regName, (addr) + 52); \
    WR1_ADDR(regName, (addr) + 53); \
    WR1_ADDR(regName, (addr) + 54); \
    WR1_ADDR(regName, (addr) + 55); \
    WR1_ADDR(regName, (addr) + 56); \
    WR1_ADDR(regName, (addr) + 57); \
    WR1_ADDR(regName, (addr) + 58); \
    WR1_ADDR(regName, (addr) + 59); \
    WR1_ADDR(regName, (addr) + 60); \
    WR1_ADDR(regName, (addr) + 61); \
    WR1_ADDR(regName, (addr) + 62); \
    WR1_ADDR(regName, (addr) + 63)

// [R RD 1 MEM[Ofs]]
#define  RD1_ADDR(regName, addr) \
    *((addr) + 0) = SCE->regName;

// [R RD 2 MEM[Ofs]]
#define  RD2_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName;

// [R RD 3 MEM[Ofs]]
#define  RD3_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName;

// [R RD 4 MEM[Ofs]]
#define  RD4_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName; \
    *((addr) + 3) = SCE->regName

// [R RD 5 MEM[Ofs]]
#define  RD5_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName; \
    *((addr) + 3) = SCE->regName; \
    *((addr) + 4) = SCE->regName

// [R RD 6 MEM[Ofs]]
#define  RD6_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName; \
    *((addr) + 3) = SCE->regName; \
    *((addr) + 4) = SCE->regName; \
    *((addr) + 5) = SCE->regName

// [R RD 7 MEM[Ofs]]
#define  RD7_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName; \
    *((addr) + 3) = SCE->regName; \
    *((addr) + 4) = SCE->regName; \
    *((addr) + 5) = SCE->regName; \
    *((addr) + 6) = SCE->regName

// [R RD 8 MEM[Ofs]]
#define  RD8_ADDR(regName, addr)  \
    *((addr) + 0) = SCE->regName; \
    *((addr) + 1) = SCE->regName; \
    *((addr) + 2) = SCE->regName; \
    *((addr) + 3) = SCE->regName; \
    *((addr) + 4) = SCE->regName; \
    *((addr) + 5) = SCE->regName; \
    *((addr) + 6) = SCE->regName; \
    *((addr) + 7) = SCE->regName

// [R RD 12 MEM[Ofs]]
#define  RD12_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE->regName; \
    *((addr) + 1)  = SCE->regName; \
    *((addr) + 2)  = SCE->regName; \
    *((addr) + 3)  = SCE->regName; \
    *((addr) + 4)  = SCE->regName; \
    *((addr) + 5)  = SCE->regName; \
    *((addr) + 6)  = SCE->regName; \
    *((addr) + 7)  = SCE->regName; \
    *((addr) + 8)  = SCE->regName; \
    *((addr) + 9)  = SCE->regName; \
    *((addr) + 10) = SCE->regName; \
    *((addr) + 11) = SCE->regName

// [R RD 16 MEM[Ofs]]
#define  RD16_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE->regName; \
    *((addr) + 1)  = SCE->regName; \
    *((addr) + 2)  = SCE->regName; \
    *((addr) + 3)  = SCE->regName; \
    *((addr) + 4)  = SCE->regName; \
    *((addr) + 5)  = SCE->regName; \
    *((addr) + 6)  = SCE->regName; \
    *((addr) + 7)  = SCE->regName; \
    *((addr) + 8)  = SCE->regName; \
    *((addr) + 9)  = SCE->regName; \
    *((addr) + 10) = SCE->regName; \
    *((addr) + 11) = SCE->regName; \
    *((addr) + 12) = SCE->regName; \
    *((addr) + 13) = SCE->regName; \
    *((addr) + 14) = SCE->regName; \
    *((addr) + 15) = SCE->regName

// [R RD 32 MEM[Ofs]]
#define  RD32_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE->regName; \
    *((addr) + 1)  = SCE->regName; \
    *((addr) + 2)  = SCE->regName; \
    *((addr) + 3)  = SCE->regName; \
    *((addr) + 4)  = SCE->regName; \
    *((addr) + 5)  = SCE->regName; \
    *((addr) + 6)  = SCE->regName; \
    *((addr) + 7)  = SCE->regName; \
    *((addr) + 8)  = SCE->regName; \
    *((addr) + 9)  = SCE->regName; \
    *((addr) + 10) = SCE->regName; \
    *((addr) + 11) = SCE->regName; \
    *((addr) + 12) = SCE->regName; \
    *((addr) + 13) = SCE->regName; \
    *((addr) + 14) = SCE->regName; \
    *((addr) + 15) = SCE->regName; \
    *((addr) + 16) = SCE->regName; \
    *((addr) + 17) = SCE->regName; \
    *((addr) + 18) = SCE->regName; \
    *((addr) + 19) = SCE->regName; \
    *((addr) + 20) = SCE->regName; \
    *((addr) + 21) = SCE->regName; \
    *((addr) + 22) = SCE->regName; \
    *((addr) + 23) = SCE->regName; \
    *((addr) + 24) = SCE->regName; \
    *((addr) + 25) = SCE->regName; \
    *((addr) + 26) = SCE->regName; \
    *((addr) + 27) = SCE->regName; \
    *((addr) + 28) = SCE->regName; \
    *((addr) + 29) = SCE->regName; \
    *((addr) + 30) = SCE->regName; \
    *((addr) + 31) = SCE->regName

// [R RD 64 MEM[Ofs]]
#define  RD64_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE->regName; \
    *((addr) + 1)  = SCE->regName; \
    *((addr) + 2)  = SCE->regName; \
    *((addr) + 3)  = SCE->regName; \
    *((addr) + 4)  = SCE->regName; \
    *((addr) + 5)  = SCE->regName; \
    *((addr) + 6)  = SCE->regName; \
    *((addr) + 7)  = SCE->regName; \
    *((addr) + 8)  = SCE->regName; \
    *((addr) + 9)  = SCE->regName; \
    *((addr) + 10) = SCE->regName; \
    *((addr) + 11) = SCE->regName; \
    *((addr) + 12) = SCE->regName; \
    *((addr) + 13) = SCE->regName; \
    *((addr) + 14) = SCE->regName; \
    *((addr) + 15) = SCE->regName; \
    *((addr) + 16) = SCE->regName; \
    *((addr) + 17) = SCE->regName; \
    *((addr) + 18) = SCE->regName; \
    *((addr) + 19) = SCE->regName; \
    *((addr) + 20) = SCE->regName; \
    *((addr) + 21) = SCE->regName; \
    *((addr) + 22) = SCE->regName; \
    *((addr) + 23) = SCE->regName; \
    *((addr) + 24) = SCE->regName; \
    *((addr) + 25) = SCE->regName; \
    *((addr) + 26) = SCE->regName; \
    *((addr) + 27) = SCE->regName; \
    *((addr) + 28) = SCE->regName; \
    *((addr) + 29) = SCE->regName; \
    *((addr) + 30) = SCE->regName; \
    *((addr) + 31) = SCE->regName; \
    *((addr) + 32) = SCE->regName; \
    *((addr) + 33) = SCE->regName; \
    *((addr) + 34) = SCE->regName; \
    *((addr) + 35) = SCE->regName; \
    *((addr) + 36) = SCE->regName; \
    *((addr) + 37) = SCE->regName; \
    *((addr) + 38) = SCE->regName; \
    *((addr) + 39) = SCE->regName; \
    *((addr) + 40) = SCE->regName; \
    *((addr) + 41) = SCE->regName; \
    *((addr) + 42) = SCE->regName; \
    *((addr) + 43) = SCE->regName; \
    *((addr) + 44) = SCE->regName; \
    *((addr) + 45) = SCE->regName; \
    *((addr) + 46) = SCE->regName; \
    *((addr) + 47) = SCE->regName; \
    *((addr) + 48) = SCE->regName; \
    *((addr) + 49) = SCE->regName; \
    *((addr) + 50) = SCE->regName; \
    *((addr) + 51) = SCE->regName; \
    *((addr) + 52) = SCE->regName; \
    *((addr) + 53) = SCE->regName; \
    *((addr) + 54) = SCE->regName; \
    *((addr) + 55) = SCE->regName; \
    *((addr) + 56) = SCE->regName; \
    *((addr) + 57) = SCE->regName; \
    *((addr) + 58) = SCE->regName; \
    *((addr) + 59) = SCE->regName; \
    *((addr) + 60) = SCE->regName; \
    *((addr) + 61) = SCE->regName; \
    *((addr) + 62) = SCE->regName; \
    *((addr) + 63) = SCE->regName

// [TEST_BUSY WAIT A]
#define  WAI_BUSY(value) \
    WAIT_STS(SCE->REG_00H, 31, value)

void SC32_function001(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void SC32_function002(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void SC32_function003(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);

void SC327_function001(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void SC327_function002(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void SC327_function003(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);

// [R WR 32 B0 B1 B2 B3 B4 .... B31]
#define  WR32_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31                                                                          \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31)

// [R WR 48 B0 B1 B2 B3 B4 .... B47]
#define  WR48_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31, value32, value33, value34, value35, value36, value37, value38, value39, \
                   value40, value41, value42, value43, value44, value45, value46, value47                    \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31);                                                                              \
    WR1_PROG(regName, value32);                                                                              \
    WR1_PROG(regName, value33);                                                                              \
    WR1_PROG(regName, value34);                                                                              \
    WR1_PROG(regName, value35);                                                                              \
    WR1_PROG(regName, value36);                                                                              \
    WR1_PROG(regName, value37);                                                                              \
    WR1_PROG(regName, value38);                                                                              \
    WR1_PROG(regName, value39);                                                                              \
    WR1_PROG(regName, value40);                                                                              \
    WR1_PROG(regName, value41);                                                                              \
    WR1_PROG(regName, value42);                                                                              \
    WR1_PROG(regName, value43);                                                                              \
    WR1_PROG(regName, value44);                                                                              \
    WR1_PROG(regName, value45);                                                                              \
    WR1_PROG(regName, value46);                                                                              \
    WR1_PROG(regName, value47)

// [R WR 48 B0 B1 B2 B3 B4 .... B47]
#define  WR64_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31, value32, value33, value34, value35, value36, value37, value38, value39, \
                   value40, value41, value42, value43, value44, value45, value46, value47, value48, value49, \
                   value50, value51, value52, value53, value54, value55, value56, value57, value58, value59, \
                   value60, value61, value62, value63                                                        \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31);                                                                              \
    WR1_PROG(regName, value32);                                                                              \
    WR1_PROG(regName, value33);                                                                              \
    WR1_PROG(regName, value34);                                                                              \
    WR1_PROG(regName, value35);                                                                              \
    WR1_PROG(regName, value36);                                                                              \
    WR1_PROG(regName, value37);                                                                              \
    WR1_PROG(regName, value38);                                                                              \
    WR1_PROG(regName, value39);                                                                              \
    WR1_PROG(regName, value40);                                                                              \
    WR1_PROG(regName, value41);                                                                              \
    WR1_PROG(regName, value42);                                                                              \
    WR1_PROG(regName, value43);                                                                              \
    WR1_PROG(regName, value44);                                                                              \
    WR1_PROG(regName, value45);                                                                              \
    WR1_PROG(regName, value46);                                                                              \
    WR1_PROG(regName, value47);                                                                              \
    WR1_PROG(regName, value48);                                                                              \
    WR1_PROG(regName, value49);                                                                              \
    WR1_PROG(regName, value50);                                                                              \
    WR1_PROG(regName, value51);                                                                              \
    WR1_PROG(regName, value52);                                                                              \
    WR1_PROG(regName, value53);                                                                              \
    WR1_PROG(regName, value54);                                                                              \
    WR1_PROG(regName, value55);                                                                              \
    WR1_PROG(regName, value56);                                                                              \
    WR1_PROG(regName, value57);                                                                              \
    WR1_PROG(regName, value58);                                                                              \
    WR1_PROG(regName, value59);                                                                              \
    WR1_PROG(regName, value60);                                                                              \
    WR1_PROG(regName, value61);                                                                              \
    WR1_PROG(regName, value62);                                                                              \
    WR1_PROG(regName, value63)

#endif                                 // __SCE_ProcCommon_h__
