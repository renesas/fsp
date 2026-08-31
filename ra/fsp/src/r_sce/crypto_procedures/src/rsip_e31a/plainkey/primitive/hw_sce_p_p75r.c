/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha2HmacResumeSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[],
                                    const uint32_t InData_HashType[],
                                    const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00750001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_F0H, 0x00000001U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_2CH, InData_HashType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c84U, 0x00270000U);

    HW_SCE_p_func_sub006(0x38008880U, 0x00000001U, 0x00270000U);

    static const uint32_t Param_p75r_func100_001[] =
    {
        0x9ad88fb3U, 0xd9b78db5U, 0xf3102673U, 0xaaedb9d8U,
    };
    HW_SCE_p_func100(Param_p75r_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p75r_func102_001[] =
        {
            0x61659ac1U, 0x26c5ab40U, 0xe9459945U, 0xcfc16d5eU,
        };
        HW_SCE_p_func102(Param_p75r_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p75r_func100_002[] =
        {
            0x90bc409cU, 0x808bc39bU, 0x6d8c5976U, 0xd0db7054U,
        };
        HW_SCE_p_func100(Param_p75r_func100_002);
        HW_SCE_p_func_sub001(0x3420a880U, 0x00000007U, 0x2000b480U, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000001bU);

            WR1_PROG(REG_F4H, 0x00001050U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000008U);

            static const uint32_t Param_p75r_func101_001[] =
            {
                0xefd15d08U, 0xb89427c2U, 0xbb2663ccU, 0xa20f9084U,
            };
            HW_SCE_p_func101(Param_p75r_func101_001);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000002aU);

            WR1_PROG(REG_F4H, 0x00001080U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75r_func101_002[] =
            {
                0x049765ffU, 0xca0873c2U, 0x3727e6bfU, 0x05ac69dcU,
            };
            HW_SCE_p_func101(Param_p75r_func101_002);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000002bU);

            WR1_PROG(REG_F4H, 0x00001090U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75r_func101_003[] =
            {
                0xf8dce5c6U, 0x8438add4U, 0x2d0544f2U, 0xaf66dc13U,
            };
            HW_SCE_p_func101(Param_p75r_func101_003);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000028U);

            WR1_PROG(REG_F4H, 0x000010a0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x0000000cU);

            static const uint32_t Param_p75r_func101_004[] =
            {
                0x7f7e42a4U, 0x23681c01U, 0x44974db1U, 0xe9715d77U,
            };
            HW_SCE_p_func101(Param_p75r_func101_004);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000029U);

            WR1_PROG(REG_F4H, 0x000010b0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75r_func101_005[] =
            {
                0x9b552b99U, 0x08c09165U, 0x86687051U, 0x58827bc5U,
            };
            HW_SCE_p_func101(Param_p75r_func101_005);
        }

        WR1_PROG(REG_F8H, 0x00000003U);

        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

        static const uint32_t Param_p75r_func100_003[] =
        {
            0x75aa5ea9U, 0x6d1cf711U, 0x61c381acU, 0x34137158U,
        };
        HW_SCE_p_func100(Param_p75r_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
            WR1_PROG(REG_2CH, InData_KeyIndex[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00007502U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_p75r_func101_006[] =
            {
                0x036f79b8U, 0x4c41a92eU, 0xd57de635U, 0x9115102fU,
            };
            HW_SCE_p_func101(Param_p75r_func101_006);
            HW_SCE_p_func043();

            WR1_PROG(REG_94H, 0x000034c5U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00007502U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_p75r_func101_007[] =
            {
                0xddacfd65U, 0xd259ee24U, 0xd057b9daU, 0x28634f6dU,
            };
            HW_SCE_p_func101(Param_p75r_func101_007);
            HW_SCE_p_func044();

            HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

            HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

            WR1_PROG(REG_94H, 0x000008e7U);

            for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
            {
                HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0xf7008d05U);
                WR4_ADDR(REG_2CH, &InData_KeyIndex[iLoop + 1]);

                HW_SCE_p_func_sub003(0x01410011U);

                WR1_PROG(REG_94H, 0x0000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);

                static const uint32_t Param_p75r_func101_008[] =
                {
                    0x307c5affU, 0xc92ba040U, 0x642831cfU, 0x4be1a96aU,
                };
                HW_SCE_p_func101(Param_p75r_func101_008);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func_sub010(0x380008e3U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            HW_SCE_p_func_sub003(0x00410011U);

            static const uint32_t Param_p75r_func101_009[] =
            {
                0x2d417ee4U, 0xacb61c58U, 0x09aeb11bU, 0xfbdfc263U,
            };
            HW_SCE_p_func101(Param_p75r_func101_009);
        }
        else
        {
            WR1_PROG(REG_94H, 0x000008e7U);

            for (iLoop = 0U; iLoop < InLen; )
            {
                WR1_PROG(REG_14H, 0x000003c4U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_Key[iLoop]);

                WR1_PROG(REG_94H, 0x0000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);

                static const uint32_t Param_p75r_func101_010[] =
                {
                    0xfce9c699U, 0xb22d0bd0U, 0x575f6422U, 0xae4cf047U,
                };
                HW_SCE_p_func101(Param_p75r_func101_010);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func_sub010(0x380008e3U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            static const uint32_t Param_p75r_func101_011[] =
            {
                0xe271ba37U, 0x5badac52U, 0x872cb732U, 0xc07e8674U,
            };
            HW_SCE_p_func101(Param_p75r_func101_011);
        }

        static const uint32_t Param_p75r_func100_004[] =
        {
            0x4a86df2fU, 0x7b68c7f6U, 0x1ddb9310U, 0xd26710d6U,
        };
        HW_SCE_p_func100(Param_p75r_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p75r_func102_002[] =
            {
                0x1a1b8fc8U, 0x5df4adf0U, 0x94a1ab84U, 0x5b47b87bU,
            };
            HW_SCE_p_func102(Param_p75r_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, InData_State[18]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, InData_State[19]);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_110H, InData_State[iLoop]);
            }

            static const uint32_t Param_p75r_func101_012[] =
            {
                0xfc974f98U, 0xa99bd688U, 0xfd538793U, 0x97049dfeU,
            };
            HW_SCE_p_func101(Param_p75r_func101_012);

            return FSP_SUCCESS;
        }
    }
}
