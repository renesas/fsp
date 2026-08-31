/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Sha256HmacUpdateSub (uint32_t InData_PaddedMsg[], uint32_t MAX_CNT)
{
    HW_SCE_p_func000(InData_PaddedMsg, MAX_CNT);
    static const uint32_t Param_p76u_func101_001[] =
    {
        0x04493113U, 0xd0a36523U, 0x247a2f8fU, 0x9bf01b74U,
    };
    HW_SCE_p_func101(Param_p76u_func101_001);
}
