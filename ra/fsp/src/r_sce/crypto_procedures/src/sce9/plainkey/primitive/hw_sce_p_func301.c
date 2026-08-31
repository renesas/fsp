/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func301 (void)
{
    HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

    HW_SCE_p_func_sub001(0x00009004U, 0x00000008U, 0x800012c0U, 0x000040c2U);
    HW_SCE_p_func_sub023(0x00004804U, 0x0000282cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    HW_SCE_p_func_sub023(0x000040c1U, 0x0000282cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    HW_SCE_p_func_sub001(0x000040c1U, 0x00000008U, 0x800016c0U, 0x000060c2U);
    HW_SCE_p_func_sub023(0x00006c04U, 0x00002c2cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    HW_SCE_p_func_sub023(0x000060c1U, 0x00002c2cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    HW_SCE_p_func_sub023(0x000060c1U, 0x00002c2cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    HW_SCE_p_func_sub023(0x000060c1U, 0x00006c04U);
}
