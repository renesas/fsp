/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    static const uint32_t Param_p29a_func101_001[] =
    {
        0x3f5e681dU, 0xeaa9c3f3U, 0x1411eb65U, 0x6f7c9297U,
    };
    HW_SCE_p_func101(Param_p29a_func101_001);
}
