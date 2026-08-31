/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func405 (void)
{
    HW_SCE_p_func_sub001(0x00003466U, 0x00056863U, 0x00026c63U, 0x00003803U);

    HW_SCE_p_func_sub001(0x00003466U, 0x00003481U, 0x00000c61U, 0x00002883U);
    HW_SCE_p_func_sub022(0x00004404U, 0x00007400U, 0x00000c02U);
}
