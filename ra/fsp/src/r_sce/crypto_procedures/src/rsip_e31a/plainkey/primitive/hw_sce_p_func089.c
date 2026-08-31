/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func089 (void)
{
    static const uint32_t Param_func089_func100_001[] =
    {
        0x53456a36U, 0x70cf1e61U, 0x42dbd0e9U, 0xadead2abU,
    };
    HW_SCE_p_func100(Param_func089_func100_001);

    WR1_PROG(REG_B0H, 0x00009438U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B8H, 0x00000007U);

    WR1_PROG(REG_A4H, 0x06060010U);

    HW_SCE_p_func_sub012();

    HW_SCE_p_func_sub002(0x0038004dU, 0x00310007U, 0x06060002U);

    WR1_PROG(REG_B0H, 0x00009454U);
    HW_SCE_p_func_sub003(0x00c00031U);

    HW_SCE_p_func_sub002(0x00540085U, 0x00380000U, 0x06060009U);

    HW_SCE_p_func_sub002(0x00540007U, 0x003f0000U, 0x06060009U);

    HW_SCE_p_func_sub002(0x00460031U, 0x0077003fU, 0x06060015U);
    WR1_PROG(REG_40H, 0x00000d00U);

    WR1_PROG(REG_B0H, 0x00009415U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x00150077U, 0x00230000U, 0x0606000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func089_func100_002[] =
    {
        0xc9d7e9d1U, 0x0f3a3742U, 0xc2d64ea9U, 0xdd9cfe98U,
    };
    HW_SCE_p_func100(Param_func089_func100_002);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func089_func101_001[] =
        {
            0xb74cc1c9U, 0x25421297U, 0x97202e89U, 0x6268e01cU,
        };
        HW_SCE_p_func101(Param_func089_func101_001);
    }
    else
    {
        static const uint32_t Param_func089_func100_003[] =
        {
            0x3f68ae83U, 0x7f650127U, 0x0cd1dfb1U, 0xe14c2718U,
        };
        HW_SCE_p_func100(Param_func089_func100_003);
        HW_SCE_p_func_sub002(0x00150077U, 0x00310007U, 0x06060002U);

        WR1_PROG(REG_B0H, 0x0000941cU);
        HW_SCE_p_func_sub003(0x00c0002dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

        HW_SCE_p_func_sub002(0x001c0007U, 0x00150000U, 0x0606000aU);

        HW_SCE_p_func_sub019(0x00150031U, 0x001c0007U, 0x06060000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub002(0x001c0069U, 0x00380007U, 0x06060002U);

        HW_SCE_p_func_sub002(0x001c0070U, 0x003f0007U, 0x06060002U);

        WR1_PROG(REG_94H, 0x0000b400U);
        WR1_PROG(REG_94H, 0x70f7359fU);

        static const uint32_t Param_func089_func101_002[] =
        {
            0x672c464dU, 0x947f5ad9U, 0x8592e67aU, 0x6f981feaU,
        };
        HW_SCE_p_func101(Param_func089_func101_002);
    }

    HW_SCE_p_func_sub006(0x38008800U, 0x70f7359fU, 0x00A70000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
