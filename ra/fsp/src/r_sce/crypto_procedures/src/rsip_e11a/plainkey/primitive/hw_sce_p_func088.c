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
        0xc26c2c17U, 0x81c5a08bU, 0x5fe8a41fU, 0xedddf4a8U,
    };
    HW_SCE_p_func100(Param_func088_func100_001);
    WR1_PROG(REG_B0H, 0x00001428U);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B8H, 0x00000005U);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub017();

    HW_SCE_p_func_sub003(0x00280037U, 0x00230005U, 0x04040002U);

    WR1_PROG(REG_B0H, 0x0000143cU);
    HW_SCE_p_func_sub002(0x00c00021U);

    HW_SCE_p_func_sub003(0x003c005fU, 0x00280000U, 0x04040009U);

    HW_SCE_p_func_sub003(0x003c0005U, 0x002d0000U, 0x04040009U);

    HW_SCE_p_func_sub003(0x00320023U, 0x0055002dU, 0x04040015U);
    WR1_PROG(REG_40H, 0x00000d00U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub003(0x000f0055U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func088_func100_002[] =
    {
        0xba0b2e66U, 0x0052c35fU, 0x8674892aU, 0x952cad34U,
    };
    HW_SCE_p_func100(Param_func088_func100_002);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func088_func101_001[] =
        {
            0x8139d9c5U, 0x723cf07eU, 0x0db00ea9U, 0x277f3f2cU,
        };
        HW_SCE_p_func101(Param_func088_func101_001);
    }
    else
    {
        static const uint32_t Param_func088_func100_003[] =
        {
            0x154c81b6U, 0xf96842c4U, 0x63bfabddU, 0xf778ec0bU,
        };
        HW_SCE_p_func100(Param_func088_func100_003);
        HW_SCE_p_func_sub003(0x000f0055U, 0x00230005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub002(0x00c0001dU);
        HW_SCE_p_func_sub011(0x000000a5U, 0x00000002U);

        HW_SCE_p_func_sub003(0x00140005U, 0x000f0000U, 0x0404000aU);

        WR1_PROG(REG_B4H, 0x000f0023U);
        WR1_PROG(REG_B8H, 0x00140005U);

        WR1_PROG(REG_A4H, 0x04040000U);
        WR1_PROG(REG_08H, 0x00020000U);
        HW_SCE_p_func_sub017();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub003(0x0014004bU, 0x00280005U, 0x04040002U);

        HW_SCE_p_func_sub003(0x00140050U, 0x002d0005U, 0x04040002U);

        WR1_PROG(REG_94H, 0x0000b400U);
        WR1_PROG(REG_94H, 0xc9b7be57U);

        static const uint32_t Param_func088_func101_002[] =
        {
            0x4f70857fU, 0xf4fc55d8U, 0x2eb242acU, 0x02c09f48U,
        };
        HW_SCE_p_func101(Param_func088_func101_002);
    }

    HW_SCE_p_func_sub006(0x38008800U, 0xc9b7be57U, 0x00A60000U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
