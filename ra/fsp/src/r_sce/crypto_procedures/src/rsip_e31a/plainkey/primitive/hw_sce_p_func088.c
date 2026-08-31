/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func088 (void)
{
    static const uint32_t Param_func088_func100_001[] =
    {
        0x2f66279aU, 0x56fa515dU, 0x79478b59U, 0xcd519b1aU,
    };
    HW_SCE_p_func100(Param_func088_func100_001);
    WR1_PROG(REG_B0H, 0x00001428U);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B8H, 0x00000005U);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub012();

    HW_SCE_p_func_sub002(0x00280037U, 0x00230005U, 0x04040002U);

    WR1_PROG(REG_B0H, 0x0000143cU);
    HW_SCE_p_func_sub003(0x00c00021U);

    HW_SCE_p_func_sub002(0x003c005fU, 0x00280000U, 0x04040009U);

    HW_SCE_p_func_sub002(0x003c0005U, 0x002d0000U, 0x04040009U);

    HW_SCE_p_func_sub002(0x00320023U, 0x0055002dU, 0x04040015U);
    WR1_PROG(REG_40H, 0x00000d00U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x000f0055U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func088_func100_002[] =
    {
        0x45a85d56U, 0x1f863c30U, 0x2340d668U, 0xda5e0768U,
    };
    HW_SCE_p_func100(Param_func088_func100_002);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func088_func101_001[] =
        {
            0xc0a5100dU, 0xb66dcd42U, 0xfdbf22d8U, 0x36879875U,
        };
        HW_SCE_p_func101(Param_func088_func101_001);
    }
    else
    {
        static const uint32_t Param_func088_func100_003[] =
        {
            0xe45a3d6eU, 0xfe626de6U, 0xd1d9278eU, 0xa943a9ffU,
        };
        HW_SCE_p_func100(Param_func088_func100_003);
        HW_SCE_p_func_sub002(0x000f0055U, 0x00230005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

        HW_SCE_p_func_sub002(0x00140005U, 0x000f0000U, 0x0404000aU);

        HW_SCE_p_func_sub019(0x000f0023U, 0x00140005U, 0x04040000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub002(0x0014004bU, 0x00280005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x00140050U, 0x002d0005U, 0x04040002U);

        WR1_PROG(REG_94H, 0x0000b400U);
        WR1_PROG(REG_94H, 0xd4355ee4U);

        static const uint32_t Param_func088_func101_002[] =
        {
            0x11cc47faU, 0xa07d3908U, 0xc2abb153U, 0x80559232U,
        };
        HW_SCE_p_func101(Param_func088_func101_002);
    }

    HW_SCE_p_func_sub006(0x38008800U, 0xd4355ee4U, 0x00A70000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
