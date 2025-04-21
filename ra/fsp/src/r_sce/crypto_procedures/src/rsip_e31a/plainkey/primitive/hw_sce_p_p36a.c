/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    HW_SCE_p_func101(0x8ba1f712U, 0x1c712780U, 0x6f6e96b0U, 0xb35620eeU);
}
