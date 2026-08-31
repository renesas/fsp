/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func074_r1 (void)
{
    HW_SCE_p_func_sub022(0x30003340U, 0x00050020U, 0x0000b7c0U, 0x00000023U);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000b7c0U, 0x0000001dU, 0x00070040U);
    HW_SCE_p_func_sub022(0x30003380U, 0x00070020U, 0x0000b7c0U, 0x00000017U);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000b7c0U, 0x00000015U, 0x00050040U);
    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000013U, 0x00000080U, 0x00000080U);
}
