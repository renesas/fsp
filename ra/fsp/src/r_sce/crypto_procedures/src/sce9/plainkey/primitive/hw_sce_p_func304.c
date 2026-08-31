/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func304_r1 (void)
{
    uint32_t oLoop1 = 0U;
    uint32_t oLoop2 = 0U;

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x00000024U);
    WR1_PROG(REG_ECH, 0x00003c1eU);

    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_ECH, 0x0000d779U);

    WR1_PROG(REG_28H, 0x00870001U);
    HW_SCE_p_func_sub002(0x00000b18U, 0x80010300U, 0x00008307U, 0x000000adU);
    WR1_PROG(REG_00H, 0x0000031fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_ECH, 0x3800db1fU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func304_func100_001[] =
    {
        0xe5986152U, 0x77a0ec4cU, 0x96bf2690U, 0x6a2cacffU,
    };
    HW_SCE_p_func100(Param_func304_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_func304_func101_001[] =
        {
            0x10ff3fe3U, 0x4b460b48U, 0x277e1172U, 0x463feb78U,
        };
        HW_SCE_p_func101(Param_func304_func101_001);
    }
    else
    {
        WR1_PROG(REG_28H, 0x00800001U);
        HW_SCE_p_func_sub001(0x000001c0U, 0x00000400U, 0x800080c1U, 0x00000581U);
        WR1_PROG(REG_24H, 0x000080c1U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub020(0x00bf0001U, 0x000001c0U, 0x04001991U);
        HW_SCE_p_func_sub015(0x0000c0c1U, 0x00800001U);
        HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_ECH, 0x0000d379U);

        static const uint32_t Param_func304_func101_002[] =
        {
            0x969611fbU, 0x4648fd51U, 0x43577ed6U, 0xff05cec7U,
        };
        HW_SCE_p_func101(Param_func304_func101_002);
    }

    static const uint32_t Param_func304_func100_002[] =
    {
        0xab8c8692U, 0xebf4f03eU, 0xcca553b8U, 0x62b91c3aU,
    };
    HW_SCE_p_func100(Param_func304_func100_002);
    HW_SCE_p_func_sub009(0x80010020U, 0x017da167U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_003[] =
    {
        0xf2ca2938U, 0xa80f39e9U, 0xc43330daU, 0xf5fde800U,
    };
    HW_SCE_p_func100(Param_func304_func100_003);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000024U);
    HW_SCE_p_func313(1156);

    static const uint32_t Param_func304_func100_004[] =
    {
        0xb49d7ef6U, 0x65fe3fafU, 0xcdf2ff51U, 0x40cac15bU,
    };
    HW_SCE_p_func100(Param_func304_func100_004);
    HW_SCE_p_func314(1156 + 64);

    WR1_PROG(REG_ECH, 0x00000b5aU);
    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_ECH, 0x0000d77cU);
    HW_SCE_p_func_sub007(0x0000b7c0U, 0x00000000U, 0x3800db7aU, 0x00A60000U);
    static const uint32_t Param_func304_func100_005[] =
    {
        0x01dd3aa3U, 0xe9b30484U, 0xe9ee2277U, 0xf9d02553U,
    };
    HW_SCE_p_func100(Param_func304_func100_005);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00800001U);
        HW_SCE_p_func_sub006(0x000001c0U, 0x00000400U, 0x800080c1U);

        WR1_PROG(REG_104H, 0x00000157U);
        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000001U));

        WR1_PROG(REG_E0H, 0x8181001eU);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000110U);

        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_24H, 0x000011c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00bf0001U);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_1CH, 0x00210000U);
            static const uint32_t Param_func304_func100_006[] =
            {
                0xd26d42ffU, 0xc3695e06U, 0x9cf5af99U, 0x9bfeede5U,
            };
            HW_SCE_p_func100(Param_func304_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001981U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                WR1_PROG(REG_ECH, 0x00003340U);

                static const uint32_t Param_func304_func101_003[] =
                {
                    0xefd40792U, 0x390bb84aU, 0x4c63e1c2U, 0x269e897bU,
                };
                HW_SCE_p_func101(Param_func304_func101_003);
            }
            else
            {
                static const uint32_t Param_func304_func101_004[] =
                {
                    0x7ea798c1U, 0x39d52927U, 0xb2a79290U, 0xfca05510U,
                };
                HW_SCE_p_func101(Param_func304_func101_004);
                oLoop1 = 0;
            }
        }

        HW_SCE_p_func_sub022(0x0000d37cU, 0x00000b9cU, 0x00002b9aU, 0x0000375cU);

        static const uint32_t Param_func304_func101_005[] =
        {
            0xb4818009U, 0x9240b2ceU, 0x392a2156U, 0xedf546aeU,
        };
        HW_SCE_p_func101(Param_func304_func101_005);
    }
    else
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_E0H, 0x8181001eU);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000010U);
        HW_SCE_p_func_sub006(0x000001c0U, 0x00000400U, 0x800080c1U);
        HW_SCE_p_func_sub020(0x00bf0001U, 0x000009c0U, 0x04001991U);
        HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
        HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_func304_func100_007[] =
            {
                0xcf9e1796U, 0xe867c7f2U, 0x0c8b147aU, 0x5844a87eU,
            };
            HW_SCE_p_func100(Param_func304_func100_007);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001981U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                static const uint32_t Param_func304_func101_006[] =
                {
                    0x64029b2fU, 0x0f0e1921U, 0x574ab5cbU, 0x278bca4bU,
                };
                HW_SCE_p_func101(Param_func304_func101_006);
                oLoop1 = 0;
            }
            else
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001991U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                WR1_PROG(REG_ECH, 0x00002f40U);

                static const uint32_t Param_func304_func101_007[] =
                {
                    0xe2b49ae6U, 0x659727f9U, 0x3a18be25U, 0x6e781766U,
                };
                HW_SCE_p_func101(Param_func304_func101_007);
            }
        }

        static const uint32_t Param_func304_func101_008[] =
        {
            0xa170ddb7U, 0x02cde70cU, 0x20f0afa1U, 0x6e9e2b7aU,
        };
        HW_SCE_p_func101(Param_func304_func101_008);
    }

    WR1_PROG(REG_24H, 0x000088d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x81c0001eU, 0x00013803U, 0x00000012U);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x80c0001eU, 0x00018303U, 0x00000020U);

    WR1_PROG(REG_ECH, 0x00000b39U);
    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_ECH, 0x0000d77dU);
    HW_SCE_p_func_sub007(0x0000b7c0U, 0x00000004U, 0x3800db7bU, 0x00A60000U);
    static const uint32_t Param_func304_func100_008[] =
    {
        0x3d1e1391U, 0xc39a7bdbU, 0x02df7a57U, 0xa1095da7U,
    };
    HW_SCE_p_func100(Param_func304_func100_008);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00800001U);
        HW_SCE_p_func_sub006(0x000001c0U, 0x00000400U, 0x800080c1U);

        WR1_PROG(REG_104H, 0x00000157U);
        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000001U));

        WR1_PROG(REG_E0H, 0x8181001eU);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000110U);

        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_24H, 0x000011c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00bf0001U);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_1CH, 0x00210000U);
            static const uint32_t Param_func304_func100_009[] =
            {
                0x9ffb65aaU, 0x2cf47374U, 0x960cbf4bU, 0xe0d92891U,
            };
            HW_SCE_p_func100(Param_func304_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001981U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                WR1_PROG(REG_ECH, 0x00003320U);

                static const uint32_t Param_func304_func101_009[] =
                {
                    0x9f6d4d47U, 0x5a540a97U, 0x90e36ff3U, 0xb3e0c0e5U,
                };
                HW_SCE_p_func101(Param_func304_func101_009);
            }
            else
            {
                static const uint32_t Param_func304_func101_010[] =
                {
                    0x428b2571U, 0xa7416f10U, 0x0de2c174U, 0x45a203f0U,
                };
                HW_SCE_p_func101(Param_func304_func101_010);
                oLoop1 = 0;
            }
        }

        HW_SCE_p_func_sub022(0x0000d37dU, 0x00000b9cU, 0x00002b99U, 0x0000373cU);

        static const uint32_t Param_func304_func101_011[] =
        {
            0x6acd5fb2U, 0xdf585e2eU, 0x1c716be9U, 0xff0414eaU,
        };
        HW_SCE_p_func101(Param_func304_func101_011);
    }
    else
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_E0H, 0x8181001eU);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000010U);

        HW_SCE_p_func_sub006(0x000001c0U, 0x00000400U, 0x800080c1U);
        HW_SCE_p_func_sub020(0x00bf0001U, 0x000009c0U, 0x04001991U);
        HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
        HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_func304_func100_010[] =
            {
                0xcdb35358U, 0x9476764cU, 0xa8981e90U, 0xdd46be8bU,
            };
            HW_SCE_p_func100(Param_func304_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001981U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                static const uint32_t Param_func304_func101_012[] =
                {
                    0xbd0b86adU, 0x8c871c31U, 0xdfd5d06cU, 0xf4194799U,
                };
                HW_SCE_p_func101(Param_func304_func101_012);
                oLoop1 = 0;
            }
            else
            {
                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x04001991U);
                HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
                HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
                WR1_PROG(REG_28H, 0x00bf0001U);

                WR1_PROG(REG_ECH, 0x00002f20U);

                static const uint32_t Param_func304_func101_013[] =
                {
                    0x568a7b8bU, 0x164d8cdeU, 0xdb712a97U, 0xf572288dU,
                };
                HW_SCE_p_func101(Param_func304_func101_013);
            }
        }

        static const uint32_t Param_func304_func101_014[] =
        {
            0xc33dc603U, 0x8a8373acU, 0x372774ccU, 0x978192f9U,
        };
        HW_SCE_p_func101(Param_func304_func101_014);
    }

    static const uint32_t Param_func304_func100_011[] =
    {
        0x3461b0c9U, 0xd8ad5898U, 0xe4570345U, 0x8d731553U,
    };
    HW_SCE_p_func100(Param_func304_func100_011);
    HW_SCE_p_func_sub009(0x80010020U, 0x013fd1d7U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_012[] =
    {
        0xcdb27765U, 0x54ad18a7U, 0x2a027349U, 0xaa40ee12U,
    };
    HW_SCE_p_func100(Param_func304_func100_012);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(1088);

    static const uint32_t Param_func304_func100_013[] =
    {
        0x6ca37557U, 0xd24a3739U, 0x7c970af6U, 0x200ecc3eU,
    };
    HW_SCE_p_func100(Param_func304_func100_013);
    HW_SCE_p_func314(1088 + 64);

    static const uint32_t Param_func304_func100_014[] =
    {
        0x65e7019aU, 0xc524e055U, 0x269764ceU, 0x48b54eefU,
    };
    HW_SCE_p_func100(Param_func304_func100_014);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_24H, 0x000088d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x81c0001eU, 0x00013803U, 0x00000012U);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000050U, 0x8088001eU, 0x00008323U, 0x00000022U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000070U, 0x8088001eU, 0x00008323U, 0x00000020U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func_sub004(0x0000480cU, 0x01a2b89bU);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_015[] =
    {
        0xdbfd0b8cU, 0x55072b70U, 0x2b8d035aU, 0xe0f5939aU,
    };
    HW_SCE_p_func100(Param_func304_func100_015);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(1224);

    static const uint32_t Param_func304_func100_016[] =
    {
        0xdc20f138U, 0xd0d20635U, 0x62fe940fU, 0x16494aeeU,
    };
    HW_SCE_p_func100(Param_func304_func100_016);
    HW_SCE_p_func314(1224 + 64);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x81c0001eU, 0x00013803U, 0x00000012U);

    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_E0H, 0x80010380U);
    HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_E0H, 0x800103a0U);
    HW_SCE_p_func_sub011(0x00008307U, 0x000000adU);
    WR1_PROG(REG_00H, 0x0000031fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_2CH, 0x00000012U);
    WR1_PROG(REG_104H, 0x00000767U);
    WAIT_STS(REG_104H, 31, 1);
    WR8_PROG(REG_100H,
             change_endian_long(0x40000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U));
    WR1_PROG(REG_34H, 0x00000030U);
    WR1_PROG(REG_24H, 0x80001dc0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x3800dbbeU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func304_func100_017[] =
    {
        0x71b9f77bU, 0x15ebca7bU, 0xf7ac0f68U, 0x4f17baf2U,
    };
    HW_SCE_p_func100(Param_func304_func100_017);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x00000991U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_ECH, 0x0000d375U);
        static const uint32_t Param_func304_func101_015[] =
        {
            0x3adaeacaU, 0x6e43d4abU, 0x8db7589fU, 0xc4323a0eU,
        };
        HW_SCE_p_func101(Param_func304_func101_015);
    }
    else
    {
        WR1_PROG(REG_24H, 0x00000981U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_ECH, 0x0000d775U);
        static const uint32_t Param_func304_func101_016[] =
        {
            0x7efebc70U, 0xe8bbac54U, 0x76d54f63U, 0xc908420bU,
        };
        HW_SCE_p_func101(Param_func304_func101_016);
    }

    static const uint32_t Param_func304_func100_018[] =
    {
        0xc22d191fU, 0x4585204aU, 0xe46132b0U, 0x3b5fcb5aU,
    };
    HW_SCE_p_func100(Param_func304_func100_018);
    WR1_PROG(REG_34H, 0x00000c00U);
    WR1_PROG(REG_24H, 0x8000e0c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub008(0x00bf0001U, 0x013d2cc1U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_019[] =
    {
        0x6d3ccc34U, 0xfd034277U, 0xe9f917a1U, 0x4b7fe353U,
    };
    HW_SCE_p_func100(Param_func304_func100_019);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000024U);
    HW_SCE_p_func313(1428);

    static const uint32_t Param_func304_func100_020[] =
    {
        0xae117735U, 0x1a2569e6U, 0x41130d87U, 0x42e20119U,
    };
    HW_SCE_p_func100(Param_func304_func100_020);
    HW_SCE_p_func314(1428 + 64);

    static const uint32_t Param_func304_func100_021[] =
    {
        0x0f09dc1bU, 0x0d25ed9bU, 0xc647791bU, 0x2b003f89U,
    };
    HW_SCE_p_func100(Param_func304_func100_021);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000050U, 0x8188001eU, 0x00003823U, 0x00000012U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000070U, 0x8188001eU, 0x00003823U, 0x00000010U);
    HW_SCE_p_func_sub020(0x00bf0001U, 0x000009c0U, 0x000019a1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub023(0x000040c1U, 0x000011c0U);
    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

    HW_SCE_p_func_sub004(0x0000c80cU, 0x01a2b89bU);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    HW_SCE_p_func312(1224);

    HW_SCE_p_func_sub014(0x0000d776U, 0x3800db75U, 0x00A60000U);
    static const uint32_t Param_func304_func100_022[] =
    {
        0x5cc64a69U, 0xf2a44982U, 0xc740beb0U, 0x6a2516bdU,
    };
    HW_SCE_p_func100(Param_func304_func100_022);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_24H, 0x000019c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000991U);
        HW_SCE_p_func_sub017(0x000040c1U, 0x00210000U);
        static const uint32_t Param_func304_func100_023[] =
        {
            0x33b90ce4U, 0x5db0e894U, 0x00e112ddU, 0xf58dcd06U,
        };
        HW_SCE_p_func100(Param_func304_func100_023);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);
        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x0000d376U);

            WR1_PROG(REG_28H, 0x00800001U);
            WR1_PROG(REG_104H, 0x00000257U);
            WR1_PROG(REG_2CH, 0x00000050U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000001U));

            WR1_PROG(REG_2CH, 0x00000110U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0xFFFFFFFFU));

            WR1_PROG(REG_2CH, 0x00000050U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));
            WR1_PROG(REG_28H, 0x00bf0001U);

            static const uint32_t Param_func304_func101_017[] =
            {
                0xae9e04cfU, 0xd330fbdeU, 0x30d4edf8U, 0xc9a2ff40U,
            };
            HW_SCE_p_func101(Param_func304_func101_017);
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000d776U);

            WR1_PROG(REG_28H, 0x00800001U);
            WR1_PROG(REG_2CH, 0x00000010U);
            WR1_PROG(REG_104H, 0x00000067U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));
            WR1_PROG(REG_28H, 0x00bf0001U);

            static const uint32_t Param_func304_func101_018[] =
            {
                0xcd1f90deU, 0x9ac953a4U, 0xfeda1414U, 0xec875363U,
            };
            HW_SCE_p_func101(Param_func304_func101_018);
        }
    }
    else
    {
        WR1_PROG(REG_24H, 0x000009c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001991U);
        HW_SCE_p_func_sub017(0x000040c1U, 0x00210000U);
        static const uint32_t Param_func304_func100_024[] =
        {
            0x5f5687adU, 0xae101c00U, 0x054dc8e3U, 0x12360356U,
        };
        HW_SCE_p_func100(Param_func304_func100_024);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);
        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x0000d376U);

            WR1_PROG(REG_28H, 0x00800001U);
            WR1_PROG(REG_104H, 0x00000257U);
            WR1_PROG(REG_2CH, 0x00000050U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000001U));

            WR1_PROG(REG_2CH, 0x00000110U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0xFFFFFFFFU));

            WR1_PROG(REG_2CH, 0x00000050U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));
            WR1_PROG(REG_28H, 0x00bf0001U);

            static const uint32_t Param_func304_func101_019[] =
            {
                0xffbb0cbcU, 0x0e646d5cU, 0xce376485U, 0x470e965bU,
            };
            HW_SCE_p_func101(Param_func304_func101_019);
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000d776U);

            WR1_PROG(REG_28H, 0x00800001U);
            WR1_PROG(REG_2CH, 0x00000010U);
            WR1_PROG(REG_104H, 0x00000067U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));
            WR1_PROG(REG_28H, 0x00bf0001U);

            static const uint32_t Param_func304_func101_020[] =
            {
                0xd2c19e49U, 0xe40ff80dU, 0x83aeb8a3U, 0xbd0e4c85U,
            };
            HW_SCE_p_func101(Param_func304_func101_020);
        }
    }

    static const uint32_t Param_func304_func100_025[] =
    {
        0x18b5fb6cU, 0x7d7790ffU, 0x9c25c4f6U, 0x8c05cb7fU,
    };
    HW_SCE_p_func100(Param_func304_func100_025);

    WR1_PROG(REG_24H, 0x000009c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x04000189U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
    WR1_PROG(REG_24H, 0x000011c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x02000189U);
    HW_SCE_p_func_sub015(0x000080c1U, 0x00bf0001U);

    WR1_PROG(REG_24H, 0x000009c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x04000189U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
    HW_SCE_p_func_sub023(0x000011c0U, 0x02000189U);
    WR1_PROG(REG_24H, 0x000080c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub008(0x00bf0001U, 0x016be062U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_026[] =
    {
        0xda802bb3U, 0x2d8929d6U, 0x76e9e8cfU, 0xdbc5b788U,
    };
    HW_SCE_p_func100(Param_func304_func100_026);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(1360);

    static const uint32_t Param_func304_func100_027[] =
    {
        0xe6339cf1U, 0xb532bf6aU, 0xa3482974U, 0xd9807aecU,
    };
    HW_SCE_p_func100(Param_func304_func100_027);
    HW_SCE_p_func314(1360 + 64);

    static const uint32_t Param_func304_func100_028[] =
    {
        0x6bc0e5eaU, 0x4aedebcaU, 0xa9fcf8f6U, 0x785dfbb8U,
    };
    HW_SCE_p_func100(Param_func304_func100_028);
    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000008U, 0x8081001eU, 0x00008307U, 0x00000020U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_28H, 0x00800001U);

    WR1_PROG(REG_ECH, 0x000037dcU);

    HW_SCE_p_func_sub008(0x00bf0001U, 0x016be062U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_029[] =
    {
        0xcb65077aU, 0x4d3fa4b8U, 0x1cfe2b93U, 0x8d794d55U,
    };
    HW_SCE_p_func100(Param_func304_func100_029);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    HW_SCE_p_func312(1360);

    HW_SCE_p_func_sub009(0x80010020U, 0x017da167U);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_030[] =
    {
        0x402e7dbfU, 0xfadf9e7eU, 0x4687ad22U, 0x8fe85d29U,
    };
    HW_SCE_p_func100(Param_func304_func100_030);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func312(1156);

    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_E0H, 0x80010380U);
    HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_E0H, 0x810103c0U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000012U);

    HW_SCE_p_func_sub023(0x000009c0U, 0x00001191U);
    WR1_PROG(REG_24H, 0x000080c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_E0H, 0x81010380U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000012U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_E0H, 0x800103c0U);
    HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);
    HW_SCE_p_func_sub022(0x00008fc0U, 0x0000000fU, 0x0000d777U, 0x0000b7a0U);
    HW_SCE_p_func_sub022(0x00000010U, 0x3000dbc3U, 0x00020020U, 0x00002bddU);
    HW_SCE_p_func_sub022(0x00070020U, 0x0000d377U, 0x00000b9cU, 0x00002b9eU);
    WR1_PROG(REG_ECH, 0x000037dcU);
    WR1_PROG(REG_ECH, 0x00000080U);
    WR1_PROG(REG_ECH, 0x00000080U);

    HW_SCE_p_func_sub020(0x00bf0001U, 0x000001c0U, 0x000040c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000080c1U, 0x013d2cc1U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1428);

    HW_SCE_p_func_sub014(0x00000bffU, 0x3800db77U, 0x00A60000U);
    static const uint32_t Param_func304_func100_031[] =
    {
        0xc0dff601U, 0xdd161907U, 0x3683b9ecU, 0xfbd124aeU,
    };
    HW_SCE_p_func100(Param_func304_func100_031);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_func304_func100_032[] =
        {
            0x143b4871U, 0xb551f34eU, 0xd21077e6U, 0x930f4960U,
        };
        HW_SCE_p_func100(Param_func304_func100_032);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x000009c0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x04001991U);
            HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
            HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func304_func101_021[] =
            {
                0xe0c3f7d3U, 0x43549f5eU, 0x91d5a220U, 0xc0ccba56U,
            };
            HW_SCE_p_func101(Param_func304_func101_021);
        }

        static const uint32_t Param_func304_func101_022[] =
        {
            0x5615313fU, 0x56817861U, 0xebc2c1acU, 0x5531da32U,
        };
        HW_SCE_p_func101(Param_func304_func101_022);
    }
    else
    {
        static const uint32_t Param_func304_func100_033[] =
        {
            0x32226c01U, 0x47382077U, 0x5543d625U, 0x0538b162U,
        };
        HW_SCE_p_func100(Param_func304_func100_033);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x000009c0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x04001981U);
            HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
            HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func304_func101_023[] =
            {
                0xda5dda6eU, 0x33afdb96U, 0x36b203a6U, 0x4450e14aU,
            };
            HW_SCE_p_func101(Param_func304_func101_023);
        }

        static const uint32_t Param_func304_func101_024[] =
        {
            0x3afc982bU, 0x640862e2U, 0xdee123a1U, 0xca8502c7U,
        };
        HW_SCE_p_func101(Param_func304_func101_024);
    }

    WR1_PROG(REG_ECH, 0x38000bdfU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    static const uint32_t Param_func304_func100_034[] =
    {
        0x06131c0aU, 0x4c7c54f5U, 0x3ab8cdceU, 0xb791ca1cU,
    };
    HW_SCE_p_func100(Param_func304_func100_034);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub005(0x00000008U, 0x00000058U, 0x80010020U, 0x016be062U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1360);

    WR1_PROG(REG_ECH, 0x3800db76U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func304_func100_035[] =
    {
        0x8abe5331U, 0x481743e0U, 0x5b657230U, 0xbf6f27d2U,
    };
    HW_SCE_p_func100(Param_func304_func100_035);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        HW_SCE_p_func315(0x00000190U);

        static const uint32_t Param_func304_func101_025[] =
        {
            0x8f559563U, 0x97af0837U, 0xd313a066U, 0xa2705e73U,
        };
        HW_SCE_p_func101(Param_func304_func101_025);
    }
    else
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_E0H, 0x8181001eU);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000090U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        static const uint32_t Param_func304_func101_026[] =
        {
            0xb42e3262U, 0x9859ebaeU, 0x954f236bU, 0x77816924U,
        };
        HW_SCE_p_func101(Param_func304_func101_026);
    }

    WR1_PROG(REG_24H, 0x000009c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x04001981U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
    HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func_sub022(0x00000bdeU, 0x02816fdeU, 0x30008bc0U, 0x00000000U);
    HW_SCE_p_func_sub022(0x00020020U, 0x0000d378U, 0x00000060U, 0x0000d778U);
    WR1_PROG(REG_ECH, 0x00000080U);

    static const uint32_t Param_func304_func100_036[] =
    {
        0xc9ed9bb6U, 0x433b0541U, 0xcc23870aU, 0x214a676bU,
    };
    HW_SCE_p_func100(Param_func304_func100_036);
    HW_SCE_p_func_sub009(0x80010020U, 0x016efbeaU);

    HW_SCE_p_func080();

    static const uint32_t Param_func304_func100_037[] =
    {
        0x713e9a08U, 0x75913315U, 0x841cf33dU, 0xb3a1c40dU,
    };
    HW_SCE_p_func100(Param_func304_func100_037);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(1292);

    static const uint32_t Param_func304_func100_038[] =
    {
        0x76276a5dU, 0xf64ab6d3U, 0x8e0a61c5U, 0x3355b0fdU,
    };
    HW_SCE_p_func100(Param_func304_func100_038);
    HW_SCE_p_func314(1292 + 64);

    static const uint32_t Param_func304_func100_039[] =
    {
        0xb5d07c20U, 0x8e60825aU, 0x1ca4c842U, 0x53189972U,
    };
    HW_SCE_p_func100(Param_func304_func100_039);
    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_E0H, 0x81010320U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000010U);
    WR1_PROG(REG_E0H, 0x81010340U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000012U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_E0H, 0x80010300U);
    HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);

    HW_SCE_p_func_sub022(0x0000d77eU, 0x00000bdeU, 0x3000db7cU, 0x00020020U);
    HW_SCE_p_func_sub022(0x00002fc0U, 0x00000080U, 0x3000db7dU, 0x00020020U);
    HW_SCE_p_func_sub022(0x00002fc0U, 0x00000080U, 0x3000dbc0U, 0x00030020U);
    HW_SCE_p_func_sub022(0x0000d77eU, 0x00000060U, 0x0000d37eU, 0x00000080U);

    HW_SCE_p_func_sub020(0x00bf0001U, 0x000001c0U, 0x000040c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000080c1U, 0x013fd1d7U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1088);

    HW_SCE_p_func_sub022(0x3000db7cU, 0x00030020U, 0x0000d76bU, 0x00000060U);
    HW_SCE_p_func_sub022(0x0000d36bU, 0x00000080U, 0x000037daU, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000094U);
    static const uint32_t Param_func304_func101_027[] =
    {
        0xbffe9b14U, 0xa3660d87U, 0x6afbfd85U, 0x60ee86c1U,
    };
    HW_SCE_p_func101(Param_func304_func101_027);
    HW_SCE_p_func310();

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x81c0001eU, 0x00013803U, 0x00000014U);

    HW_SCE_p_func_sub022(0x3000db7dU, 0x00030020U, 0x0000d76bU, 0x00000060U);
    HW_SCE_p_func_sub022(0x0000d36bU, 0x00000080U, 0x000037d9U, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000095U);
    static const uint32_t Param_func304_func101_028[] =
    {
        0xd1f5d657U, 0xe314d678U, 0x376c88dcU, 0x75df4615U,
    };
    HW_SCE_p_func101(Param_func304_func101_028);
    HW_SCE_p_func310();

    static const uint32_t Param_func304_func100_040[] =
    {
        0x4aa63900U, 0xc38d6a07U, 0xb3fe94bcU, 0x286da68cU,
    };
    HW_SCE_p_func100(Param_func304_func100_040);
    HW_SCE_p_func_sub009(0x80010020U, 0x017da167U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1156);

    HW_SCE_p_func_sub022(0x3000db7eU, 0x00030020U, 0x0000d76bU, 0x00000060U);
    HW_SCE_p_func_sub022(0x0000d36bU, 0x00000080U, 0x000037d8U, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000096U);
    static const uint32_t Param_func304_func101_029[] =
    {
        0x5a216a36U, 0x6416411bU, 0xc2a7f063U, 0x4bca700bU,
    };
    HW_SCE_p_func101(Param_func304_func101_029);
    HW_SCE_p_func310();

    static const uint32_t Param_func304_func100_041[] =
    {
        0xd59a05dbU, 0x8ad34186U, 0x98e6f9a9U, 0x07ded72dU,
    };
    HW_SCE_p_func100(Param_func304_func100_041);
    HW_SCE_p_func_sub009(0x80010020U, 0x016efbeaU);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1292);

    WR1_PROG(REG_ECH, 0x3800db78U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func304_func100_042[] =
    {
        0xf2afe4e5U, 0x068a0897U, 0x1c1fdb88U, 0x10ebfab5U,
    };
    HW_SCE_p_func100(Param_func304_func100_042);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_104H, 0x00000257U);
        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000001U));

        WR1_PROG(REG_2CH, 0x00000190U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0xFFFFFFFFU));

        WR1_PROG(REG_2CH, 0x00000050U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));
        WR1_PROG(REG_28H, 0x00bf0001U);

        static const uint32_t Param_func304_func101_030[] =
        {
            0x91c25c8fU, 0xeb55526cU, 0xbd5b2addU, 0x3054a131U,
        };
        HW_SCE_p_func101(Param_func304_func101_030);
    }
    else
    {
        static const uint32_t Param_func304_func101_031[] =
        {
            0x7286ef8fU, 0x826423faU, 0x7d02c7d2U, 0xa490a0b7U,
        };
        HW_SCE_p_func101(Param_func304_func101_031);
    }

    WR1_PROG(REG_24H, 0x000009c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x04001981U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
    HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_ECH, 0x3800db79U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func304_func100_043[] =
    {
        0x6dfc72e1U, 0x4aa97e03U, 0x9fefa641U, 0xb7d6a06aU,
    };
    HW_SCE_p_func100(Param_func304_func100_043);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_func304_func100_044[] =
        {
            0xa6fcc1c7U, 0x509bfa42U, 0xd75055a0U, 0x559ad70fU,
        };
        HW_SCE_p_func100(Param_func304_func100_044);
        WR1_PROG(REG_28H, 0x00800001U);
        HW_SCE_p_func_sub006(0x000001c0U, 0x00000400U, 0x800080c1U);
        HW_SCE_p_func_sub020(0x00bf0001U, 0x000001c0U, 0x04000991U);
        HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
        WR1_PROG(REG_34H, 0x00000004U);
        WR1_PROG(REG_24H, 0x800011c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x02001191U);
        HW_SCE_p_func_sub015(0x000080c1U, 0x00bf0001U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x02816fdeU, 0x30008bc0U, 0x00000000U);
        HW_SCE_p_func_sub022(0x00020020U, 0x0000d368U, 0x00000060U, 0x0000d768U);
        WR1_PROG(REG_ECH, 0x00000080U);

        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_ECH, 0x0000b7c0U);
        HW_SCE_p_func_sub002(0x0000001cU, 0x8081001eU, 0x00008307U, 0x00000020U);
        HW_SCE_p_func_sub008(0x00bf0001U, 0x01a2b89bU);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func312(1224);

        WR1_PROG(REG_24H, 0x000019c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x04000991U);
        HW_SCE_p_func_sub015(0x0000c0c1U, 0x00800001U);
        WR1_PROG(REG_34H, 0x00000004U);
        WR1_PROG(REG_24H, 0x800011c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x02001191U);
        HW_SCE_p_func_sub015(0x000080c1U, 0x00bf0001U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x02816fdeU, 0x30008bc0U, 0x00000000U);
        HW_SCE_p_func_sub022(0x00020020U, 0x0000d372U, 0x00000060U, 0x0000d772U);
        WR1_PROG(REG_ECH, 0x00000080U);

        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_ECH, 0x0000b7c0U);
        HW_SCE_p_func_sub002(0x00000018U, 0x8081001eU, 0x00008307U, 0x00000020U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_24H, 0x000098d0U);
        WAIT_STS(REG_24H, 21, 0);

        static const uint32_t Param_func304_func101_032[] =
        {
            0xc3143860U, 0xcb79a6fdU, 0x9bf4bad1U, 0x20e4b647U,
        };
        HW_SCE_p_func101(Param_func304_func101_032);
    }
    else
    {
        static const uint32_t Param_func304_func100_045[] =
        {
            0x8d0528ddU, 0x4e505ffbU, 0xe5a9e4e6U, 0x71567e2eU,
        };
        HW_SCE_p_func100(Param_func304_func100_045);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x02816fdeU, 0x30008bc0U, 0x00000000U);
        HW_SCE_p_func_sub022(0x00020020U, 0x0000d368U, 0x00000060U, 0x0000d768U);
        WR1_PROG(REG_ECH, 0x00000080U);

        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_ECH, 0x0000b7c0U);
        HW_SCE_p_func_sub002(0x0000001cU, 0x8081001eU, 0x00008307U, 0x00000020U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_ECH, 0x0000b7c0U);
        WR1_PROG(REG_ECH, 0x00000018U);
        HW_SCE_p_func_sub023(0x000001c0U, 0x000080c1U);
        WR1_PROG(REG_E0H, 0x8081001eU);
        HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        HW_SCE_p_func_sub005(0x0000d772U, 0x00000058U, 0x80010020U, 0x01a2b89bU);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func312(1224);

        static const uint32_t Param_func304_func101_033[] =
        {
            0x5fc4a8f8U, 0x188438f1U, 0x443f6818U, 0xdc8f97a7U,
        };
        HW_SCE_p_func101(Param_func304_func101_033);
    }

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000024U, 0x0000381eU, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);
}
