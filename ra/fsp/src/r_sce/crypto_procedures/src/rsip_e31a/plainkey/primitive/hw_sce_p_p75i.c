/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha2HmacInitSub (const uint32_t InData_KeyMode[],
                                  const uint32_t InData_KeyIndex[],
                                  const uint32_t InData_Key[],
                                  const uint32_t InData_HashType[],
                                  const uint32_t InData_MsgLen[])
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

    static const uint32_t Param_p75i_func100_001[] =
    {
        0x9ad88fb3U, 0xd9b78db5U, 0xf3102673U, 0xaaedb9d8U,
    };
    HW_SCE_p_func100(Param_p75i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p75i_func102_001[] =
        {
            0x61659ac1U, 0x26c5ab40U, 0xe9459945U, 0xcfc16d5eU,
        };
        HW_SCE_p_func102(Param_p75i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p75i_func100_002[] =
        {
            0x90bc409cU, 0x808bc39bU, 0x6d8c5976U, 0xd0db7054U,
        };
        HW_SCE_p_func100(Param_p75i_func100_002);
        HW_SCE_p_func_sub001(0x3420a880U, 0x00000007U, 0x2000b480U, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000001bU);

            WR1_PROG(REG_F4H, 0x00000050U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000008U);

            static const uint32_t Param_p75i_func101_001[] =
            {
                0xb5860b0eU, 0x37c982a9U, 0x4a2925f4U, 0x6120866dU,
            };
            HW_SCE_p_func101(Param_p75i_func101_001);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000002aU);

            WR1_PROG(REG_F4H, 0x00000080U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75i_func101_002[] =
            {
                0x58acbbfcU, 0xcc6595a9U, 0x3ce3f81aU, 0xdd85b5adU,
            };
            HW_SCE_p_func101(Param_p75i_func101_002);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000002bU);

            WR1_PROG(REG_F4H, 0x00000090U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75i_func101_003[] =
            {
                0xb1007c90U, 0x95e07c0bU, 0x94d1eeeeU, 0xad75fc9cU,
            };
            HW_SCE_p_func101(Param_p75i_func101_003);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000028U);

            WR1_PROG(REG_F4H, 0x000000a0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x0000000cU);

            static const uint32_t Param_p75i_func101_004[] =
            {
                0x8b9a72b5U, 0x584d675fU, 0x0901691aU, 0x74edc4dcU,
            };
            HW_SCE_p_func101(Param_p75i_func101_004);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000029U);

            WR1_PROG(REG_F4H, 0x000000b0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            static const uint32_t Param_p75i_func101_005[] =
            {
                0xa47acea5U, 0xd6259382U, 0x9bf3b9b3U, 0xd50a26ceU,
            };
            HW_SCE_p_func101(Param_p75i_func101_005);
        }

        WR1_PROG(REG_F8H, 0x00000003U);

        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

        static const uint32_t Param_p75i_func100_003[] =
        {
            0x51f40dddU, 0x46d5b45aU, 0x39120056U, 0x749363f9U,
        };
        HW_SCE_p_func100(Param_p75i_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
            WR1_PROG(REG_2CH, InData_KeyIndex[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00007501U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_p75i_func101_006[] =
            {
                0x07c52d40U, 0x94fe6644U, 0xc57e8c17U, 0x8ac3ca36U,
            };
            HW_SCE_p_func101(Param_p75i_func101_006);
            HW_SCE_p_func043();

            WR1_PROG(REG_94H, 0x000034c5U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00007501U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_p75i_func101_007[] =
            {
                0x4dc74ae7U, 0xa01be54cU, 0xf4164545U, 0xc17b8121U,
            };
            HW_SCE_p_func101(Param_p75i_func101_007);
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

                static const uint32_t Param_p75i_func101_008[] =
                {
                    0xb6088aacU, 0x099cecb9U, 0x0223b81dU, 0xe76aa254U,
                };
                HW_SCE_p_func101(Param_p75i_func101_008);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func_sub010(0x380008e3U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            HW_SCE_p_func_sub003(0x00410011U);

            static const uint32_t Param_p75i_func101_009[] =
            {
                0xb924463fU, 0x0d955707U, 0x79bc4843U, 0x391411a5U,
            };
            HW_SCE_p_func101(Param_p75i_func101_009);
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

                static const uint32_t Param_p75i_func101_010[] =
                {
                    0xb75bf19cU, 0x8d920999U, 0x52236fe4U, 0x9cffbf45U,
                };
                HW_SCE_p_func101(Param_p75i_func101_010);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func_sub010(0x380008e3U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            static const uint32_t Param_p75i_func101_011[] =
            {
                0x84992c60U, 0xf66ff33cU, 0x40d1c39aU, 0x01a0f245U,
            };
            HW_SCE_p_func101(Param_p75i_func101_011);
        }

        static const uint32_t Param_p75i_func100_004[] =
        {
            0x972674c1U, 0x8b8a80a6U, 0x355e4abeU, 0x069dd297U,
        };
        HW_SCE_p_func100(Param_p75i_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p75i_func102_002[] =
            {
                0x477de5e0U, 0x715de8acU, 0x4c382e9eU, 0x47bdc664U,
            };
            HW_SCE_p_func102(Param_p75i_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_104H, 0x00000000U);
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_100H, 0x00000080U);

                WR1_PROG(REG_FCH, 0x00000001U);

                WAIT_STS(REG_118H, 8, 0);

                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_104H, 0x00000000U);
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_100H, 0x00000000U);

                WR1_PROG(REG_FCH, 0x00000100U);

                static const uint32_t Param_p75i_func101_012[] =
                {
                    0x8c71a730U, 0x9c9f4021U, 0xc7bc06ccU, 0x2c6fac42U,
                };
                HW_SCE_p_func101(Param_p75i_func101_012);
            }
            else
            {
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_104H, InData_MsgLen[0]);
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_100H, InData_MsgLen[1]);

                WR1_PROG(REG_FCH, 0x00000001U);

                static const uint32_t Param_p75i_func101_013[] =
                {
                    0xfa2f82daU, 0x18b32409U, 0x8e915cddU, 0x320094c0U,
                };
                HW_SCE_p_func101(Param_p75i_func101_013);
            }

            return FSP_SUCCESS;
        }
    }
}
