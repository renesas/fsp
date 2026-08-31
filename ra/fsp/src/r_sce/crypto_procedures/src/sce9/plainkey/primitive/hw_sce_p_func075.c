/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func075_r1 (void)
{
    HW_SCE_p_func_sub022(0x30003340U, 0x00050020U, 0x0000b7c0U, 0x00000022U);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000b7c0U, 0x0000001cU, 0x00070040U);
    HW_SCE_p_func_sub022(0x30003380U, 0x00070020U, 0x0000b7c0U, 0x00000016U);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000b7c0U, 0x00000014U, 0x00050040U);
    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000012U, 0x00000080U, 0x00000080U);
}
