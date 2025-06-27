/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Sha256HmacUpdateSub (const uint32_t InData_PaddedMsg[], const uint32_t MAX_CNT)
{
    HW_SCE_p_func000(InData_PaddedMsg, MAX_CNT);
    HW_SCE_p_func101(0x4a0f48ecU, 0x757e9554U, 0x8f254402U, 0x32fa9161U);
}
