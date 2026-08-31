/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func065_r1 (uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    static const uint32_t Param_func065_func100_001[] =
    {
        0x23a20f43U, 0xb31e013bU, 0x7d30fa57U, 0xddf885eeU,
    };
    HW_SCE_p_func100(Param_func065_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000011U);

    static const uint32_t Param_func065_func101_001[] =
    {
        0xabc8f62eU, 0xa0b4b4cdU, 0xabed9fedU, 0x55efaa74U,
    };
    HW_SCE_p_func101(Param_func065_func101_001);
    HW_SCE_p_func043();

    HW_SCE_p_func_sub005(0x000034e4U, 0x00000058U, 0x800103a0U, 0x00000011U);

    static const uint32_t Param_func065_func101_002[] =
    {
        0x79da836fU, 0x01a8f4b7U, 0x4410b933U, 0x7d62b94dU,
    };
    HW_SCE_p_func101(Param_func065_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_func065_func100_002[] =
    {
        0xfef7fdd1U, 0x5e78f5c3U, 0xd66fdca4U, 0x5b2ab651U,
    };
    HW_SCE_p_func100(Param_func065_func100_002);

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00050804U, 0x00000000U);

    HW_SCE_p_func081();

    WR1_PROG(REG_ECH, 0x00007c01U);
    WR1_PROG(REG_1CH, 0x00600000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        static const uint32_t Param_func065_func100_003[] =
        {
            0x3b31b2c7U, 0xfdedce3fU, 0xf2657d0aU, 0x9d2cac16U,
        };
        HW_SCE_p_func100(Param_func065_func100_003);
        WR1_PROG(REG_00H, 0x80002100U);
        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00000886U);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x02e087b6U);
        WR1_PROG(REG_04H, 0x0000c200U);

        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG1[0]);
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &ARG1[4 + iLoop]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG2[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG2[1 + iLoop]);
        iLoop = iLoop + 4;
        oLoop = iLoop;

        HW_SCE_p_func202();

        static const uint32_t Param_func065_func101_003[] =
        {
            0x26483003U, 0x4db2d050U, 0x1fb2570aU, 0x627d3e3bU,
        };
        HW_SCE_p_func101(Param_func065_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0a000000U)
    {
        static const uint32_t Param_func065_func100_004[] =
        {
            0x2be8ca08U, 0xf05b8eaaU, 0xeb20462aU, 0xc40e8c69U,
        };
        HW_SCE_p_func100(Param_func065_func100_004);
        WR1_PROG(REG_28H, 0x009f0001U);

        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func066(0, ARG1);
        iLoop = 0 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (oLoop = 0U; oLoop < 32U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);
            oLoop = oLoop + 4;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_func065_func100_005[] =
        {
            0xc47ff753U, 0x04506ad6U, 0x013e3dd5U, 0xbe1ead25U,
        };
        HW_SCE_p_func100(Param_func065_func100_005);
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00000885U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG1[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_D0H, 0x40000000U);
        HW_SCE_p_func_sub013(0x00e08885U, 0x00002113U);
        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_func065_func100_006[] =
        {
            0x3b861e61U, 0xb600ea62U, 0x4bf70f4eU, 0xff3c1866U,
        };
        HW_SCE_p_func100(Param_func065_func100_006);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func062(36, ARG2);
        oLoop = 36 + 32;

        static const uint32_t Param_func065_func101_004[] =
        {
            0x23e8fb2eU, 0x74657e4dU, 0x076514e5U, 0xb519809cU,
        };
        HW_SCE_p_func101(Param_func065_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0b000000U)
    {
        static const uint32_t Param_func065_func100_007[] =
        {
            0x65278693U, 0x04fabe2eU, 0xfc2fa6d5U, 0x9de2decbU,
        };
        HW_SCE_p_func100(Param_func065_func100_007);
        WR1_PROG(REG_28H, 0x009f0001U);

        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func066(0, ARG1);
        iLoop = 0 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func062(0, ARG2);
        oLoop = 0 + 32;

        static const uint32_t Param_func065_func100_008[] =
        {
            0x7fa0d5a1U, 0x3517f529U, 0x36e90eafU, 0x91f1dc4bU,
        };
        HW_SCE_p_func100(Param_func065_func100_008);
        WR1_PROG(REG_00H, 0x00003183U);
        WR1_PROG(REG_2CH, 0x00000011U);
        HW_SCE_p_func066(32, ARG1);
        iLoop = 32 + 32;

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000021U);
        HW_SCE_p_func062(32, ARG2);
        oLoop = 32 + 32;

        static const uint32_t Param_func065_func100_009[] =
        {
            0xcaa3bb50U, 0xd6691c2bU, 0xc5ff2240U, 0x7f7071bdU,
        };
        HW_SCE_p_func100(Param_func065_func100_009);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func062(64, ARG2);
        oLoop = 64 + 32;

        static const uint32_t Param_func065_func101_005[] =
        {
            0x8427d069U, 0x71e1837eU, 0x1d040576U, 0x0c34e400U,
        };
        HW_SCE_p_func101(Param_func065_func101_005);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0c000000U)
    {
        static const uint32_t Param_func065_func100_010[] =
        {
            0xa26076b9U, 0x10e94805U, 0x196f6ef1U, 0xf38da63dU,
        };
        HW_SCE_p_func100(Param_func065_func100_010);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func067(0, ARG1);
        iLoop = 0 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (oLoop = 0U; oLoop < 64U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);
            oLoop = oLoop + 4;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_func065_func100_011[] =
        {
            0xa56b7d5dU, 0xf4486507U, 0x64d0b38fU, 0x04fb55a5U,
        };
        HW_SCE_p_func100(Param_func065_func100_011);
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00000885U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG1[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_D0H, 0x40000000U);
        HW_SCE_p_func_sub013(0x00e08885U, 0x00002113U);
        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_func065_func100_012[] =
        {
            0x4aed1905U, 0xe5d8ff2eU, 0xcee610e7U, 0x2b56f36cU,
        };
        HW_SCE_p_func100(Param_func065_func100_012);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func064(68, ARG2);
        oLoop = 68 + 64;

        static const uint32_t Param_func065_func101_006[] =
        {
            0x953dbb7cU, 0x684783a0U, 0xec9db7b7U, 0xeadfcaa6U,
        };
        HW_SCE_p_func101(Param_func065_func101_006);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x0d000000U)
    {
        static const uint32_t Param_func065_func100_013[] =
        {
            0x0da69955U, 0x4c58a953U, 0x660176a5U, 0xb9ae0c4eU,
        };
        HW_SCE_p_func100(Param_func065_func100_013);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func067(0, ARG1);
        iLoop = 0 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func064(0, ARG2);
        oLoop = 0 + 64;

        static const uint32_t Param_func065_func100_014[] =
        {
            0x58754c97U, 0xd4752e10U, 0x9fa38d8fU, 0xbe29908fU,
        };
        HW_SCE_p_func100(Param_func065_func100_014);

        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func067(64, ARG1);
        iLoop = 64 + 64;

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func064(64, ARG2);
        oLoop = 64 + 64;

        static const uint32_t Param_func065_func100_015[] =
        {
            0x3ab34648U, 0x51ed9b48U, 0x476e0a97U, 0x9dd57620U,
        };
        HW_SCE_p_func100(Param_func065_func100_015);
        HW_SCE_p_func060();

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func064(128, ARG2);
        oLoop = 128 + 64;

        static const uint32_t Param_func065_func101_007[] =
        {
            0x25db8d2cU, 0xd2c88a95U, 0x654191cbU, 0x45fcaca9U,
        };
        HW_SCE_p_func101(Param_func065_func101_007);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x12000000U)
    {
        static const uint32_t Param_func065_func100_016[] =
        {
            0x546d42e4U, 0x4fab67faU, 0x54171dfeU, 0x01b96779U,
        };
        HW_SCE_p_func100(Param_func065_func100_016);
        WR1_PROG(REG_00H, 0x80002100U);
        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00000886U);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x02e08886U);
        WR1_PROG(REG_04H, 0x0000c200U);

        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG1[0]);
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &ARG1[4 + iLoop]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &ARG2[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG2[1 + iLoop]);
        iLoop = iLoop + 4;
        oLoop = iLoop;

        HW_SCE_p_func202();

        static const uint32_t Param_func065_func101_008[] =
        {
            0x0afcbf2fU, 0xc4a4aabaU, 0x39c6470fU, 0x02417d40U,
        };
        HW_SCE_p_func101(Param_func065_func101_008);
    }

    static const uint32_t Param_func065_func100_017[] =
    {
        0xd3371c6dU, 0xd24af252U, 0x239fe0dcU, 0x815b0e6cU,
    };
    HW_SCE_p_func100(Param_func065_func100_017);
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    WR1_PROG(REG_D0H, 0x40000000U);
    HW_SCE_p_func_sub013(0x000089c5U, 0x00002213U);
    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);

    WR1_PROG(REG_ECH, 0x00007c1cU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
