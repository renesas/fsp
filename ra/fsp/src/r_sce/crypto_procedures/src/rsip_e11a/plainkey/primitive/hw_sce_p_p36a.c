/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    static const uint32_t Param_p36a_func101_001[] =
    {
        0xb3a96391U, 0xd8c1af1cU, 0x78e1b419U, 0xcbeb9ff5U,
    };
    HW_SCE_p_func101(Param_p36a_func101_001);
}
