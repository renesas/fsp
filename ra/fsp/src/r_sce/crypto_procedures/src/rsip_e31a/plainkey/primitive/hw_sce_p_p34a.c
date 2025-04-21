/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func430(InData_DataA, MAX_CNT);

    HW_SCE_p_func101(0xa04e32adU, 0xd38636ecU, 0xcbdb9f6aU, 0x5411f0baU);
}
