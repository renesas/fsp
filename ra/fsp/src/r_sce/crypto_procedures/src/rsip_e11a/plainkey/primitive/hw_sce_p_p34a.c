/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    static const uint32_t Param_p34a_func101_001[] =
    {
        0x744d192aU, 0xc2cc649eU, 0x4da8c0acU, 0x379102c4U,
    };
    HW_SCE_p_func101(Param_p34a_func101_001);
}
