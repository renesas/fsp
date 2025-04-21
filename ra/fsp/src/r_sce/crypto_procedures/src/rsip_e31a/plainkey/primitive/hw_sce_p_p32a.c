/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    HW_SCE_p_func101(0xdaaabeebU, 0xc75083e9U, 0x44741fb8U, 0x4fd8ad5bU);
}
