/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func402 (void)
{
    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_func402_func100_001[] =
    {
        0x0a7e5650U, 0x7db344ebU, 0x884120e3U, 0x079da04fU,
    };
    HW_SCE_p_func100(Param_func402_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub002(0x0087008cU, 0x00730000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x00870091U, 0x00780000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x00870096U, 0x007d0000U, 0x0404000aU);

        static const uint32_t Param_func402_func101_001[] =
        {
            0x6a0a3633U, 0xd1ca35d1U, 0x4e730591U, 0xafc62c11U,
        };
        HW_SCE_p_func101(Param_func402_func101_001);
    }
    else
    {
        HW_SCE_p_func_sub002(0x00870046U, 0x00730000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x0087004bU, 0x00780000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x00870050U, 0x007d0000U, 0x0404000aU);

        static const uint32_t Param_func402_func101_002[] =
        {
            0x6a7965b1U, 0x3f0c6455U, 0x573ff158U, 0xad0a4a04U,
        };
        HW_SCE_p_func101(Param_func402_func101_002);
    }

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
