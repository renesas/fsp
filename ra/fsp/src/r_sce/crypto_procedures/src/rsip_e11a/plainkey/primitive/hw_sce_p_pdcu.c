/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Sha224HmacUpdateSub (const uint32_t InData_PaddedMsg[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func000(InData_PaddedMsg, MAX_CNT);
    HW_SCE_p_func101(0xdfe9b1cbU, 0x8b9fdf34U, 0x18977478U, 0x4b62bfecU);
}
