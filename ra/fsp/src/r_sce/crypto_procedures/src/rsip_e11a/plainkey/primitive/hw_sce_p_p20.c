/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRandomNumberSub (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00200002U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p20_func100_001[] =
    {
        0x56354e4dU, 0x73681bfaU, 0xcceafa1fU, 0x06822720U,
    };
    HW_SCE_p_func100(Param_p20_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_p20_func100_002[] =
    {
        0xf14f56feU, 0xd8705df0U, 0xe1d6ef6fU, 0xc7223d71U,
    };
    HW_SCE_p_func100(Param_p20_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_Text[0]);

    static const uint32_t Param_p20_func102_001[] =
    {
        0x0e247ba8U, 0x4b4177beU, 0x27ceab9eU, 0xdbb4d6feU,
    };
    HW_SCE_p_func102(Param_p20_func102_001);

    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
