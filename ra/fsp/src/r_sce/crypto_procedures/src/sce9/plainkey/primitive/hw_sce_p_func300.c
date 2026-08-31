/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func300 (void)
{
    HW_SCE_p_func_sub022(0x38008fc0U, 0x0000001fU, 0x1000381fU, 0x100027e1U);

    HW_SCE_p_func_sub022(0x00002fc0U, 0x38008c00U, 0x80000000U, 0x20002c40U);

    HW_SCE_p_func_sub023(0x00009cd0U, 0x0000302cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

    WR1_PROG(REG_24H, 0x000070d0U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub001(0x000080c1U, 0x00000002U, 0x800048d0U, 0x0000282cU);

    WR1_PROG(REG_24H, 0x100019b1U);
    HW_SCE_p_func_sub016(0x000019a1U, 0x00000863U);

    HW_SCE_p_func_sub022(0x38008840U, 0x00000001U, 0x1000d060U, 0x38008c00U);
    WR1_PROG(REG_ECH, 0x80000000U);
    HW_SCE_p_func_sub007(0x2000d061U, 0x38008860U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_func300_func100_001[] =
    {
        0x7cb9bdc4U, 0xe2ed2e73U, 0x4a5b41a8U, 0x425eb43eU,
    };
    HW_SCE_p_func100(Param_func300_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x800088d0U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_001[] =
        {
            0xd0c4c720U, 0x1d3105e5U, 0x59d8a4afU, 0x0aca73a5U,
        };
        HW_SCE_p_func101(Param_func300_func101_001);
    }

    HW_SCE_p_func_sub023(0x000040c1U, 0x00002c2cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

    HW_SCE_p_func_sub006(0x000080c1U, 0x00000008U, 0x800011c0U);

    WR1_PROG(REG_34H, 0x00000200U);
    HW_SCE_p_func_sub006(0x80000a41U, 0x00000008U, 0x800011c0U);

    WR1_PROG(REG_34H, 0x00000200U);
    HW_SCE_p_func_sub001(0x80000951U, 0x00000002U, 0x80004cd0U, 0x0000282cU);

    WR1_PROG(REG_24H, 0x100019b1U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub006(0x000019a1U, 0x00000280U, 0x800019a1U);

    HW_SCE_p_func_sub014(0x38008860U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_func300_func100_002[] =
    {
        0x05080e70U, 0x42335a73U, 0xa2816ca7U, 0x60d9a58eU,
    };
    HW_SCE_p_func100(Param_func300_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x8000a8d0U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_002[] =
        {
            0x5439d1d0U, 0xf77edaccU, 0x57b2b29fU, 0xdd61d360U,
        };
        HW_SCE_p_func101(Param_func300_func101_002);
    }

    WR1_PROG(REG_34H, 0x00000080U);
    HW_SCE_p_func_sub023(0x800080c1U, 0x000040c1U);
    HW_SCE_p_func_sub023(0x00002c2cU, 0x100019b1U);

    WR1_PROG(REG_24H, 0x000019a1U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub014(0x38008840U, 0x00000001U, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008c00U, 0x80000000U, 0x00260000U);

    static const uint32_t Param_func300_func100_003[] =
    {
        0x6881e9fbU, 0x06aa6fdfU, 0x762ffc17U, 0x0ae7d84aU,
    };
    HW_SCE_p_func100(Param_func300_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000040c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_003[] =
        {
            0x1e20aafbU, 0x0da3797bU, 0x1af729a3U, 0x9c0738b4U,
        };
        HW_SCE_p_func101(Param_func300_func101_003);
    }
    else
    {
        WR1_PROG(REG_24H, 0x0000e0c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_004[] =
        {
            0x646bf0ddU, 0x564d0572U, 0xea3a4866U, 0x1d52fff8U,
        };
        HW_SCE_p_func101(Param_func300_func101_004);
    }

    HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

    HW_SCE_p_func_sub006(0x00002c2cU, 0x00000200U, 0x900019b1U);

    WR1_PROG(REG_34H, 0x00000280U);
    HW_SCE_p_func_sub001(0x800019a1U, 0x00000008U, 0x800015c0U, 0x00000941U);
    HW_SCE_p_func_sub001(0x000080c1U, 0x00000008U, 0x800015c0U, 0x00000951U);
    WR1_PROG(REG_34H, 0x00000080U);
    HW_SCE_p_func_sub001(0x800040c2U, 0x00000200U, 0x800012c0U, 0x00008cd0U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
    HW_SCE_p_func_sub023(0x0000282cU, 0x100019b1U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x00008cd0U);
    HW_SCE_p_func_sub023(0x000040c1U, 0x0000302cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

    HW_SCE_p_func_sub023(0x00000951U, 0x000019a1U);

    HW_SCE_p_func_sub014(0x38008840U, 0x00000001U, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008c00U, 0x80000000U, 0x00260000U);

    static const uint32_t Param_func300_func100_004[] =
    {
        0x5784ad1eU, 0x63814257U, 0x33a4b910U, 0x1700cf71U,
    };
    HW_SCE_p_func100(Param_func300_func100_004);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000060c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_005[] =
        {
            0x8b0b83e6U, 0x57999af5U, 0x29955b52U, 0xa5f96b63U,
        };
        HW_SCE_p_func101(Param_func300_func101_005);
    }
    else
    {
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x800080c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_006[] =
        {
            0xdd3bb8caU, 0x5d1667a4U, 0x248aebc8U, 0x3a8569d1U,
        };
        HW_SCE_p_func101(Param_func300_func101_006);
    }

    HW_SCE_p_func_sub023(0x00000149U, 0x000060c1U);
    HW_SCE_p_func_sub023(0x000009c0U, 0x00000d51U);
    HW_SCE_p_func_sub023(0x000040c1U, 0x0000282cU);

    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

    WR1_PROG(REG_34H, 0x00000080U);
    HW_SCE_p_func_sub001(0x800080c1U, 0x00000080U, 0x800060c2U, 0x000040c1U);
    HW_SCE_p_func_sub023(0x00002c2cU, 0x100019b1U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
    HW_SCE_p_func_sub023(0x000009c0U, 0x00000d51U);

    HW_SCE_p_func_sub023(0x000019a1U, 0x00000145U);

    HW_SCE_p_func_sub014(0x38008840U, 0x00000001U, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008c00U, 0x80000000U, 0x00260000U);

    static const uint32_t Param_func300_func100_005[] =
    {
        0x3a6b9affU, 0x96c744c5U, 0x2ba5e0d7U, 0x473b64d7U,
    };
    HW_SCE_p_func100(Param_func300_func100_005);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000060c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_007[] =
        {
            0x6d4b179bU, 0xd894c624U, 0x41aec014U, 0x3b6a07ccU,
        };
        HW_SCE_p_func101(Param_func300_func101_007);
    }
    else
    {
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x8000a0c1U);
        WAIT_STS(REG_24H, 21, 0);
        static const uint32_t Param_func300_func101_008[] =
        {
            0x4585ea52U, 0xc7508304U, 0xa730e47dU, 0x56bff85aU,
        };
        HW_SCE_p_func101(Param_func300_func101_008);
    }

    WR1_PROG(REG_ECH, 0x38000bc4U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    static const uint32_t Param_func300_func100_006[] =
    {
        0x19bb82daU, 0x8e4d3bddU, 0x159c1223U, 0x100a1ebfU,
    };
    HW_SCE_p_func100(Param_func300_func100_006);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_ECH, 0x00002f80U);

        static const uint32_t Param_func300_func100_007[] =
        {
            0x9496dc85U, 0x5565ff4fU, 0x0e3ae0fcU, 0x5fccf5f2U,
        };
        HW_SCE_p_func100(Param_func300_func100_007);
        WR1_PROG(REG_E0H, 0x81010380U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        WR1_PROG(REG_ECH, 0x00007c1dU);
        WR1_PROG(REG_1CH, 0x00602000U);
    }
    else
    {
        HW_SCE_p_func_sub001(0x00009cd0U, 0x00000020U, 0x80005cd0U, 0x0000302cU);

        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

        HW_SCE_p_func_sub023(0x000070d0U, 0x000080c1U);
        HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

        WR1_PROG(REG_24H, 0x000019a1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub001(0x000080c1U, 0x00000208U, 0x800011c0U, 0x0000282cU);

        WR1_PROG(REG_24H, 0x100019b1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub001(0x000019a1U, 0x00000080U, 0x800080c1U, 0x000040c1U);
        HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);
        HW_SCE_p_func_sub023(0x00000149U, 0x00001141U);
        HW_SCE_p_func_sub006(0x00000941U, 0x00000080U, 0x800040c1U);
        WR1_PROG(REG_34H, 0x00000008U);
        HW_SCE_p_func_sub001(0x800094d0U, 0x00000200U, 0x800019a1U, 0x00002c2cU);

        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

        HW_SCE_p_func_sub023(0x00000149U, 0x000019a1U);

        HW_SCE_p_func_sub014(0x38008840U, 0x00000000U, 0x00260000U);

        static const uint32_t Param_func300_func100_008[] =
        {
            0xdc69660aU, 0x37cc1f51U, 0x3a646afcU, 0x133dad9dU,
        };
        HW_SCE_p_func100(Param_func300_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x000040c1U);
            WAIT_STS(REG_24H, 21, 0);
            static const uint32_t Param_func300_func101_009[] =
            {
                0xb93c6b4eU, 0xdaa196c9U, 0xf84a2b35U, 0x80f87383U,
            };
            HW_SCE_p_func101(Param_func300_func101_009);
        }
        else
        {
            WR1_PROG(REG_24H, 0x0000e0c1U);
            WAIT_STS(REG_24H, 21, 0);
            static const uint32_t Param_func300_func101_010[] =
            {
                0xc769e365U, 0x6330fdfdU, 0x3604efb4U, 0xb017fb9eU,
            };
            HW_SCE_p_func101(Param_func300_func101_010);
        }

        HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);
        HW_SCE_p_func_sub023(0x0000282cU, 0x100019b1U);

        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);
        HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

        HW_SCE_p_func_sub001(0x000019a1U, 0x00000200U, 0x800002d1U, 0x000009c0U);
        HW_SCE_p_func_sub023(0x00000149U, 0x00000149U);
        WR1_PROG(REG_24H, 0x000040c1U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub001(0x00000149U, 0x00000080U, 0x800080c1U, 0x000060c1U);
        HW_SCE_p_func_sub023(0x0000302cU, 0x100019b1U);

        HW_SCE_p_func_sub023(0x000019a1U, 0x00000d51U);

        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x800080c1U, 0x000060c1U);
        HW_SCE_p_func_sub023(0x000009c0U, 0x00000d51U);
        HW_SCE_p_func_sub001(0x000040c1U, 0x00000080U, 0x8000014aU, 0x00000149U);
        HW_SCE_p_func_sub001(0x00000149U, 0x00000080U, 0x800080c1U, 0x000060c1U);
        HW_SCE_p_func_sub023(0x0000282cU, 0x100019b1U);

        HW_SCE_p_func_sub023(0x000019a1U, 0x00000d51U);

        HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x8000a0c1U);

        WR1_PROG(REG_ECH, 0x00016c00U);

        WR1_PROG(REG_ECH, 0x00007c1dU);
        WR1_PROG(REG_1CH, 0x00602000U);
    }
}
