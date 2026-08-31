/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func302 (void)
{
    HW_SCE_p_func_sub022(0x38008fc0U, 0x0000001fU, 0x1000381fU, 0x100027e1U);

    WR1_PROG(REG_ECH, 0x00002fc0U);

    WR1_PROG(REG_ECH, 0x38008c00U);
    WR1_PROG(REG_ECH, 0x80000000U);
    HW_SCE_p_func_sub007(0x20002c40U, 0x38008840U, 0x00000000U, 0x00A60000U);

    static const uint32_t Param_func302_func100_001[] =
    {
        0x0be803f1U, 0xaf43b4fbU, 0xc4b808e5U, 0x656569c2U,
    };
    HW_SCE_p_func100(Param_func302_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_ECH, 0x3800d81fU);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00A60000U);

        static const uint32_t Param_func302_func100_002[] =
        {
            0x7e98a73bU, 0xd8a9ce59U, 0xdb79f215U, 0xa333be2cU,
        };
        HW_SCE_p_func100(Param_func302_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            HW_SCE_p_func_sub023(0x00009cd0U, 0x0000302cU);

            HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

            WR1_PROG(REG_24H, 0x000070d0U);
            WAIT_STS(REG_24H, 21, 0);
            HW_SCE_p_func_sub001(0x000080c1U, 0x00000002U, 0x800048d0U, 0x0000282cU);

            HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

            HW_SCE_p_func_sub007(0x00000863U, 0x38008840U, 0x00000001U, 0x00260000U);

            static const uint32_t Param_func302_func100_003[] =
            {
                0x97923a72U, 0xf3c1b530U, 0x377b742dU, 0x1cfbe97fU,
            };
            HW_SCE_p_func100(Param_func302_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_34H, 0x00000800U);
                WR1_PROG(REG_24H, 0x800088d0U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_001[] =
                {
                    0x7b388408U, 0x87cdbf3dU, 0x2de37e3eU, 0x6980acafU,
                };
                HW_SCE_p_func101(Param_func302_func101_001);
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

            HW_SCE_p_func_sub014(0x38008840U, 0x00000001U, 0x00260000U);

            static const uint32_t Param_func302_func100_004[] =
            {
                0x8c171365U, 0x2d85eca3U, 0x2870eac6U, 0x0728f6e1U,
            };
            HW_SCE_p_func100(Param_func302_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_34H, 0x00000800U);
                WR1_PROG(REG_24H, 0x8000a8d0U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_002[] =
                {
                    0xf0b2a5cfU, 0x92e837e0U, 0xc8e075efU, 0x5e47de2eU,
                };
                HW_SCE_p_func101(Param_func302_func101_002);
            }

            WR1_PROG(REG_34H, 0x00000080U);
            HW_SCE_p_func_sub023(0x800080c1U, 0x000040c1U);
            HW_SCE_p_func_sub023(0x00002c2cU, 0x100019b1U);

            WR1_PROG(REG_24H, 0x000019a1U);
            WAIT_STS(REG_24H, 21, 0);

            HW_SCE_p_func_sub014(0x38008840U, 0x00000001U, 0x00260000U);

            static const uint32_t Param_func302_func100_005[] =
            {
                0x2c7196a2U, 0x36fb8304U, 0xafce3eb1U, 0xaeaee9a8U,
            };
            HW_SCE_p_func100(Param_func302_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000040c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_003[] =
                {
                    0xb5777ab6U, 0x40e740a5U, 0x49575931U, 0xf19d5425U,
                };
                HW_SCE_p_func101(Param_func302_func101_003);
            }
            else
            {
                WR1_PROG(REG_24H, 0x0000e0c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_004[] =
                {
                    0xb2724ea1U, 0x7c74561fU, 0xa0b5d998U, 0x57550da6U,
                };
                HW_SCE_p_func101(Param_func302_func101_004);
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

            static const uint32_t Param_func302_func100_006[] =
            {
                0x75ba536dU, 0x2e30f36cU, 0xb3324f38U, 0x5968458cU,
            };
            HW_SCE_p_func100(Param_func302_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000060c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_005[] =
                {
                    0x802b0684U, 0x69264948U, 0x4286494bU, 0x3bdd8e36U,
                };
                HW_SCE_p_func101(Param_func302_func101_005);
            }
            else
            {
                WR1_PROG(REG_34H, 0x00000800U);
                WR1_PROG(REG_24H, 0x800080c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_006[] =
                {
                    0x44ebc595U, 0x10b0e3a3U, 0x777d4c82U, 0xd06d541bU,
                };
                HW_SCE_p_func101(Param_func302_func101_006);
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

            static const uint32_t Param_func302_func100_007[] =
            {
                0xb09dccf4U, 0x63be4033U, 0x60160e20U, 0xcbb759d4U,
            };
            HW_SCE_p_func100(Param_func302_func100_007);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000060c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_007[] =
                {
                    0x7eb1a8abU, 0xbac3f161U, 0x463f7896U, 0x8c21338aU,
                };
                HW_SCE_p_func101(Param_func302_func101_007);
            }
            else
            {
                WR1_PROG(REG_34H, 0x00000800U);
                WR1_PROG(REG_24H, 0x8000a0c1U);
                WAIT_STS(REG_24H, 21, 0);
                static const uint32_t Param_func302_func101_008[] =
                {
                    0xfc93967bU, 0xa7d222e5U, 0x1a38ceaeU, 0x64f35868U,
                };
                HW_SCE_p_func101(Param_func302_func101_008);
            }
        }
        else
        {
            static const uint32_t Param_func302_func101_009[] =
            {
                0x42dbdae1U, 0xd6c90dadU, 0xf0da9152U, 0x4af05ac5U,
            };
            HW_SCE_p_func101(Param_func302_func101_009);
        }

        WR1_PROG(REG_ECH, 0x38000bc4U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_func302_func100_008[] =
        {
            0x04c62050U, 0x85471239U, 0x431e9a1eU, 0x94e9736cU,
        };
        HW_SCE_p_func100(Param_func302_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x00002f80U);

            static const uint32_t Param_func302_func100_009[] =
            {
                0x0ca11aceU, 0xf756a0aaU, 0x85202c6bU, 0xeafbb7edU,
            };
            HW_SCE_p_func100(Param_func302_func100_009);
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

            HW_SCE_p_func_sub023(0x0000e0c1U, 0x0000302cU);

            HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

            HW_SCE_p_func_sub023(0x000080c1U, 0x0000282cU);

            HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

            HW_SCE_p_func_sub023(0x000040c1U, 0x0000302cU);

            WR1_PROG(REG_24H, 0x100019b1U);
            WAIT_STS(REG_24H, 21, 0);

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

            static const uint32_t Param_func302_func101_010[] =
            {
                0x52430301U, 0x4929e648U, 0xddef7975U, 0x2d2cf120U,
            };
            HW_SCE_p_func101(Param_func302_func101_010);

            WR1_PROG(REG_ECH, 0x00007c1dU);
            WR1_PROG(REG_1CH, 0x00602000U);
        }
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00016c00U);

        static const uint32_t Param_func302_func101_011[] =
        {
            0x2feff25fU, 0xfcd487ebU, 0x6afa67d6U, 0x32960ea4U,
        };
        HW_SCE_p_func101(Param_func302_func101_011);

        WR1_PROG(REG_ECH, 0x00007c1dU);
        WR1_PROG(REG_1CH, 0x00602000U);
    }
}
