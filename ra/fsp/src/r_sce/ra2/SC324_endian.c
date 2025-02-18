/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hw_sce_private.h"

static crypto_word_endian_t s1_endian_flag = CRYPTO_WORD_ENDIAN_BIG;

void HW_SCE_EndianSetBig (void)
{
    s1_endian_flag = CRYPTO_WORD_ENDIAN_BIG;
}

void HW_SCE_EndianSetLittle (void)
{
    s1_endian_flag = CRYPTO_WORD_ENDIAN_LITTLE;
}

crypto_word_endian_t HW_SCE_EndianFlagGet (void)
{
    return s1_endian_flag;
}
