/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub (uint32_t MAX_CNT,
                                                   uint32_t InData_KeyType[],
                                                   uint32_t OutData_PubKeyIndex[],
                                                   uint32_t OutData_PubKey[],
                                                   uint32_t OutData_PrivKeyIndex[],
                                                   uint32_t OutData_PrivKey[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002b02U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p2b_func100_001[] =
    {
        0x29802336U, 0xd159a0b7U, 0xe311d54cU, 0x36dce5c5U,
    };
    HW_SCE_p_func100(Param_p2b_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_p2b_func100_002[] =
    {
        0xb8dc77d4U, 0x3247864dU, 0xc9a3aaf3U, 0x419c0ae7U,
    };
    HW_SCE_p_func100(Param_p2b_func100_002);
    HW_SCE_p_func_sub012(0x00000052U, 0x01080c84U, 0x00000000U);

    WR1_PROG(REG_ECH, 0x00000a31U);
    for (kLoop = 0U; kLoop < MAX_CNT; kLoop++)
    {
        WR1_PROG(REG_28H, 0x00bf0001U);
        HW_SCE_p_func_sub011(0x00003043U, 0x00000012U);
        WR1_PROG(REG_104H, 0x00002f57U);
        WAIT_STS(REG_104H, 31, 1);
        WR48_PROG(REG_100H,
                  change_endian_long(0x00030005U),
                  change_endian_long(0x0007000bU),
                  change_endian_long(0x000d0011U),
                  change_endian_long(0x00130017U),
                  change_endian_long(0x001d001fU),
                  change_endian_long(0x00250029U),
                  change_endian_long(0x002b002fU),
                  change_endian_long(0x003b003dU),
                  change_endian_long(0x00430047U),
                  change_endian_long(0x0049004fU),
                  change_endian_long(0x00530059U),
                  change_endian_long(0x00610065U),
                  change_endian_long(0x0067006bU),
                  change_endian_long(0x006d0071U),
                  change_endian_long(0x007f0083U),
                  change_endian_long(0x0089008bU),
                  change_endian_long(0x00950097U),
                  change_endian_long(0x009d00a3U),
                  change_endian_long(0x00a700adU),
                  change_endian_long(0x00b300b5U),
                  change_endian_long(0x00bf00c1U),
                  change_endian_long(0x00c500c7U),
                  change_endian_long(0x00d300dfU),
                  change_endian_long(0x00e300e5U),
                  change_endian_long(0x00e900efU),
                  change_endian_long(0x00f100fbU),
                  change_endian_long(0x01010107U),
                  change_endian_long(0x010d010fU),
                  change_endian_long(0x01150119U),
                  change_endian_long(0x011b0125U),
                  change_endian_long(0x01330137U),
                  change_endian_long(0x0139013dU),
                  change_endian_long(0x014b0151U),
                  change_endian_long(0x015b015dU),
                  change_endian_long(0x01610167U),
                  change_endian_long(0x016f0175U),
                  change_endian_long(0x017b017fU),
                  change_endian_long(0x0185018dU),
                  change_endian_long(0x01910199U),
                  change_endian_long(0x01a301a5U),
                  change_endian_long(0x01af01b1U),
                  change_endian_long(0x01b701bbU),
                  change_endian_long(0x01c101c9U),
                  change_endian_long(0x01cd01cfU),
                  change_endian_long(0x01d301dfU),
                  change_endian_long(0x01e701ebU),
                  change_endian_long(0x01f301f7U),
                  change_endian_long(0x01fd0000U));

        WR1_PROG(REG_ECH, 0x000008c6U);

        HW_SCE_p_func_sub011(0x00000343U, 0x00000022U);
        HW_SCE_p_func_sub010(0x80b00006U, 0x000083c3U);

        WR1_PROG(REG_28H, 0x009f0001U);

        static const uint32_t Param_p2b_func100_003[] =
        {
            0x7c3be8a4U, 0x10077703U, 0x98320738U, 0x5903bfb6U,
        };
        HW_SCE_p_func100(Param_p2b_func100_003);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);
        HW_SCE_p_func_sub002(0x0000d01fU, 0x81040000U, 0x00003813U, 0x00000010U);

        for (iLoop = 0U; iLoop < 24U; )
        {
            static const uint32_t Param_p2b_func100_004[] =
            {
                0x10e16e07U, 0x8fb49ab6U, 0xf23e1fdfU, 0x970de29aU,
            };
            HW_SCE_p_func100(Param_p2b_func100_004);
            HW_SCE_p_func103();
            HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

            WR1_PROG(REG_00H, 0x00003213U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            static const uint32_t Param_p2b_func101_001[] =
            {
                0xfc43caa7U, 0xb55af2a9U, 0x6c16fba1U, 0x313b167cU,
            };
            HW_SCE_p_func101(Param_p2b_func101_001);
            iLoop = iLoop + 4U;
        }

        static const uint32_t Param_p2b_func100_005[] =
        {
            0x10e16e07U, 0x8fb49ab6U, 0xf23e1fdfU, 0x970de29aU,
        };
        HW_SCE_p_func100(Param_p2b_func100_005);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);
        WR1_PROG(REG_ECH, 0x0000d060U);
        HW_SCE_p_func_sub010(0x81040000U, 0x00003813U);

        WR1_PROG(REG_2CH, 0x00000011U);
        WR1_PROG(REG_104H, 0x00001f57U);
        WAIT_STS(REG_104H, 31, 1);
        WR32_PROG(REG_100H,
                  change_endian_long(0xB51EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851EB8U),
                  change_endian_long(0x51EB851EU),
                  change_endian_long(0xB851EB85U),
                  change_endian_long(0x1EB851EBU),
                  change_endian_long(0x851EB851U),
                  change_endian_long(0xEB851B5CU));

        WR1_PROG(REG_24H, 0x000011c0U);
        HW_SCE_p_func_sub017(0x00001591U, 0x00210000U);

        static const uint32_t Param_p2b_func100_006[] =
        {
            0x90ae1e92U, 0x8bca1ce6U, 0x377f1b58U, 0x7427eca8U,
        };
        HW_SCE_p_func100(Param_p2b_func100_006);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2b_func101_002[] =
            {
                0x5cba8941U, 0x18800bcfU, 0x699933a2U, 0xc0a9c83dU,
            };
            HW_SCE_p_func101(Param_p2b_func101_002);
            continue;
        }
        else
        {
            static const uint32_t Param_p2b_func101_003[] =
            {
                0x755f15bcU, 0xfaa7c752U, 0x8cdee2ccU, 0x7c5d5e22U,
            };
            HW_SCE_p_func101(Param_p2b_func101_003);
        }

        HW_SCE_p_func_sub014(0x38008a20U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p2b_func100_007[] =
        {
            0x1ff30c58U, 0x2c43ede7U, 0x51891153U, 0xc6f0919aU,
        };
        HW_SCE_p_func100(Param_p2b_func100_007);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00001dc0U);
            HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

            static const uint32_t Param_p2b_func100_008[] =
            {
                0x491d7813U, 0x9669f2a6U, 0x8ab8a647U, 0xebc5b55fU,
            };
            HW_SCE_p_func100(Param_p2b_func100_008);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub023(0x000011c0U, 0x00001d91U);

                static const uint32_t Param_p2b_func101_004[] =
                {
                    0x512c888cU, 0xac3c9b30U, 0x350fde63U, 0xaae062a7U,
                };
                HW_SCE_p_func101(Param_p2b_func101_004);
            }
            else
            {
                static const uint32_t Param_p2b_func101_005[] =
                {
                    0xc1f2ef4fU, 0x557853acU, 0x59b8831bU, 0x4b149043U,
                };
                HW_SCE_p_func101(Param_p2b_func101_005);
            }

            WR1_PROG(REG_2CH, 0x00000011U);
            WR1_PROG(REG_104H, 0x00000357U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                     change_endian_long(0x00000000U), change_endian_long(0x10000000U));
            WR1_PROG(REG_00H, 0x00003073U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_24H, 0x00001591U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_p2b_func100_009[] =
            {
                0x87807a30U, 0x9f5ca829U, 0xe1175f96U, 0x1a9e6e75U,
            };
            HW_SCE_p_func100(Param_p2b_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p2b_func101_006[] =
                {
                    0xe281d2f1U, 0x0c9fbf53U, 0xf7faeb43U, 0xc9102828U,
                };
                HW_SCE_p_func101(Param_p2b_func101_006);
                continue;
            }
            else
            {
                static const uint32_t Param_p2b_func101_007[] =
                {
                    0xc6d10669U, 0x9f4ff89dU, 0x8038e04aU, 0x9a3e17b0U,
                };
                HW_SCE_p_func101(Param_p2b_func101_007);
            }
        }
        else
        {
            static const uint32_t Param_p2b_func101_008[] =
            {
                0x07901e4cU, 0x0cebe917U, 0x0f834a0eU, 0x9f2d080eU,
            };
            HW_SCE_p_func101(Param_p2b_func101_008);
        }

        WR1_PROG(REG_ECH, 0x000008c6U);
        WR1_PROG(REG_ECH, 0x0000094aU);

        for (iLoop = 0U; iLoop < 96U; iLoop++)
        {
            WR1_PROG(REG_ECH, 0x01003906U);
            WR1_PROG(REG_ECH, 0x00002cc0U);
            HW_SCE_p_func_sub002(0x00002cc0U, 0x81010100U, 0x0000307fU, 0x00000014U);
            WR1_PROG(REG_00H, 0x00003807U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_24H, 0x00004006U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000009c0U);
            HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);
            static const uint32_t Param_p2b_func100_010[] =
            {
                0x85dde662U, 0xd8fc3123U, 0x89de60c8U, 0x07d5ef2eU,
            };
            HW_SCE_p_func100(Param_p2b_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);
            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x0000d140U);

                static const uint32_t Param_p2b_func101_009[] =
                {
                    0x28a65192U, 0xe2a959dbU, 0xd43404eaU, 0x7339fd84U,
                };
                HW_SCE_p_func101(Param_p2b_func101_009);
                break;
            }
            else
            {
                static const uint32_t Param_p2b_func101_010[] =
                {
                    0x11a06545U, 0x32ad1e6fU, 0xdeb595cdU, 0xe97bc932U,
                };
                HW_SCE_p_func101(Param_p2b_func101_010);
            }
        }

        HW_SCE_p_func_sub014(0x38008940U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p2b_func100_011[] =
        {
            0x11867603U, 0x6f83bc5aU, 0xaa875c8dU, 0x12f9e1ecU,
        };
        HW_SCE_p_func100(Param_p2b_func100_011);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2b_func101_011[] =
            {
                0xebf0bae4U, 0x21cca239U, 0xd872659aU, 0xfcdcf0fcU,
            };
            HW_SCE_p_func101(Param_p2b_func101_011);
            continue;
        }

        HW_SCE_p_func_sub023(0x000011c0U, 0x000060c1U);
        HW_SCE_p_func_sub023(0x000011c0U, 0x00000591U);
        WR1_PROG(REG_24H, 0x000080c1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub011(0x0000307fU, 0x00000014U);
        WR1_PROG(REG_104H, 0x00000057U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00010001U));

        HW_SCE_p_func_sub023(0x00004006U, 0x00000dc0U);
        WR1_PROG(REG_24H, 0x000080c1U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);
        static const uint32_t Param_p2b_func100_012[] =
        {
            0x7c533ae2U, 0x000734a8U, 0x356810baU, 0x487c1ecfU,
        };
        HW_SCE_p_func100(Param_p2b_func100_012);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2b_func101_012[] =
            {
                0x5436329aU, 0x9632d27fU, 0x10281c9eU, 0xc0df0d5fU,
            };
            HW_SCE_p_func101(Param_p2b_func101_012);
        }
        else
        {
            HW_SCE_p_func_sub023(0x0000d0d0U, 0x000019c0U);
            HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

            HW_SCE_p_func_sub023(0x000005c0U, 0x00000189U);
            WR1_PROG(REG_24H, 0x000080c1U);
            WAIT_STS(REG_24H, 21, 0);

            static const uint32_t Param_p2b_func100_013[] =
            {
                0x79f5b90aU, 0xd7922a5aU, 0xac0169c2U, 0x03577a52U,
            };
            HW_SCE_p_func100(Param_p2b_func100_013);
            WR1_PROG(REG_18H, 0x00000004U);
            WR1_PROG(REG_38H, 0x00004080U);
            WAIT_STS(REG_18H, 10, 0);

            WR1_PROG(REG_18H, 0x00000000U);

            WR1_PROG(REG_24H, 0x000005c0U);
            HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

            WR1_PROG(REG_24H, 0x000044d0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000011c0U);
            HW_SCE_p_func_sub017(0x00000991U, 0x00210000U);

            static const uint32_t Param_p2b_func100_014[] =
            {
                0x8a4e89beU, 0xad785403U, 0x03489702U, 0x2497f830U,
            };
            HW_SCE_p_func100(Param_p2b_func100_014);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p2b_func101_013[] =
                {
                    0xbe8e9962U, 0x0bda5eb5U, 0x5c30c9c9U, 0x33a96ae3U,
                };
                HW_SCE_p_func101(Param_p2b_func101_013);
                continue;
            }

            WR1_PROG(REG_24H, 0x000098d0U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000b540U);
            HW_SCE_p_func_sub002(0x00000080U, 0x80a0000aU, 0x00008383U, 0x00000020U);

            WR1_PROG(REG_ECH, 0x0000b560U);
            WR1_PROG(REG_ECH, 0x00000003U);

            WR1_PROG(REG_B0H, 0x00000700U);
            WR1_PROG(REG_A4H, 0x42e0873fU);
            HW_SCE_p_func_sub011(0x00001383U, 0x00000020U);

            HW_SCE_p_func_sub021(0x00000c84U);

            HW_SCE_p_func_sub019(0x400009cdU, 0x00001113U);

            HW_SCE_p_func_sub014(0x38008a20U, 0x00000000U, 0x00260000U);

            static const uint32_t Param_p2b_func100_015[] =
            {
                0xf96cb05eU, 0x7a810f51U, 0x46e8fa5eU, 0x812236d7U,
            };
            HW_SCE_p_func100(Param_p2b_func100_015);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_7CH, 0x00000021U);
                WR1_PROG(REG_00H, 0x00005113U);
                WR1_PROG(REG_74H, 0x00000004U);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                static const uint32_t Param_p2b_func101_014[] =
                {
                    0x87016245U, 0x5e83f673U, 0x602e7aebU, 0xeb5683b0U,
                };
                HW_SCE_p_func101(Param_p2b_func101_014);
            }
            else
            {
                WR1_PROG(REG_7CH, 0x00000041U);
                WR1_PROG(REG_00H, 0x00005113U);
                WR1_PROG(REG_74H, 0x00000004U);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                static const uint32_t Param_p2b_func101_015[] =
                {
                    0x239b33b8U, 0xd6eb409fU, 0x93df7b47U, 0xb35986dcU,
                };
                HW_SCE_p_func101(Param_p2b_func101_015);
            }

            static const uint32_t Param_p2b_func100_016[] =
            {
                0xeaa4de27U, 0x5c6570b3U, 0x23239a44U, 0xb259bd4dU,
            };
            HW_SCE_p_func100(Param_p2b_func100_016);
            WR1_PROG(REG_24H, 0x000011c0U);
            HW_SCE_p_func_sub016(0x0000c0c1U, 0x00000929U);

            HW_SCE_p_func_sub022(0x0000b4c0U, 0x000000fcU, 0x00003906U, 0x00008d00U);
            WR1_PROG(REG_ECH, 0xfffffffeU);
            WR1_PROG(REG_ECH, 0x00003d06U);

            WR1_PROG(REG_ECH, 0x00000908U);
            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x000038e6U);
                WR1_PROG(REG_ECH, 0x0000a8c0U);
                WR1_PROG(REG_ECH, 0x00000004U);
                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    HW_SCE_p_func_sub022(0x38008900U, 0x00000000U, 0x11816907U, 0x38008900U);
                    WR1_PROG(REG_ECH, 0x00000000U);
                    WR1_PROG(REG_ECH, 0x10002d20U);

                    WR1_PROG(REG_ECH, 0x000168e7U);
                }
            }

            HW_SCE_p_func_sub022(0x00003549U, 0x0000a540U, 0x00000003U, 0x0002694aU);

            WR1_PROG(REG_E0H, 0x81010140U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037eaU);
            WR1_PROG(REG_24H, 0x000011c0U);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                HW_SCE_p_func_sub023(0x00000185U, 0x00000185U);
                WR1_PROG(REG_24H, 0x00000185U);
                HW_SCE_p_func_sub016(0x00000185U, 0x000033e0U);

                static const uint32_t Param_p2b_func101_016[] =
                {
                    0x25f7c21cU, 0xa58e2d37U, 0xc7d2c302U, 0x94a4950cU,
                };
                HW_SCE_p_func101(Param_p2b_func101_016);
            }

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            static const uint32_t Param_p2b_func100_017[] =
            {
                0x3ffbde47U, 0xdf842701U, 0x3ed2ea1fU, 0x92f4b6cdU,
            };
            HW_SCE_p_func100(Param_p2b_func100_017);
            WR1_PROG(REG_ECH, 0x00026d4aU);
            WR1_PROG(REG_ECH, 0x00002949U);

            WR1_PROG(REG_E0H, 0x81010140U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037eaU);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_24H, 0x2000018dU);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_ECH, 0x000033e0U);

                static const uint32_t Param_p2b_func101_017[] =
                {
                    0xf2494d23U, 0x208dc9cfU, 0x9eaacfe5U, 0xe3122179U,
                };
                HW_SCE_p_func101(Param_p2b_func101_017);
            }

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            static const uint32_t Param_p2b_func100_018[] =
            {
                0xb09a35c9U, 0x5d8bb3e6U, 0xfc920928U, 0x6f246efaU,
            };
            HW_SCE_p_func100(Param_p2b_func100_018);
            WR1_PROG(REG_24H, 0x0000a0c1U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000a52U);

            HW_SCE_p_func_sub023(0x00006404U, 0x00006c04U);

            WR1_PROG(REG_E0H, 0x81010160U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_2CH, 0x00000010U);

                for (jLoop = 0U; jLoop < 32U; )
                {
                    static const uint32_t Param_p2b_func100_019[] =
                    {
                        0x80f0c0afU, 0xb016844bU, 0xab5eb905U, 0x9689d197U,
                    };
                    HW_SCE_p_func100(Param_p2b_func100_019);
                    HW_SCE_p_func103();
                    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

                    WR1_PROG(REG_00H, 0x00003213U);
                    WAIT_STS(REG_00H, 25, 0);
                    WR1_PROG(REG_1CH, 0x00001800U);

                    static const uint32_t Param_p2b_func101_018[] =
                    {
                        0x615822e9U, 0xfce99d10U, 0xc52ef231U, 0xd71f309aU,
                    };
                    HW_SCE_p_func101(Param_p2b_func101_018);
                    jLoop = jLoop + 4U;
                }

                static const uint32_t Param_p2b_func100_020[] =
                {
                    0xad8720efU, 0x8c70ba5eU, 0xc306a7e5U, 0x8d3defeeU,
                };
                HW_SCE_p_func100(Param_p2b_func100_020);

                HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
                HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
                HW_SCE_p_func_sub023(0x00000591U, 0x0000c0c1U);

                HW_SCE_p_func_sub023(0x00009008U, 0x000011c0U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x0000c0c1U, 0x00000dc0U);
                WR1_PROG(REG_24H, 0x000040c1U);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_18H, 0x00000004U);
                WR1_PROG(REG_38H, 0x00000c40U);
                WAIT_STS(REG_18H, 10, 0);
                WR1_PROG(REG_18H, 0x00000000U);

                WR1_PROG(REG_24H, 0x000005c0U);
                HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

                HW_SCE_p_func_sub023(0x000005c0U, 0x000040c1U);
                WR1_PROG(REG_24H, 0x000011c0U);
                HW_SCE_p_func_sub017(0x00000991U, 0x00210000U);

                static const uint32_t Param_p2b_func100_021[] =
                {
                    0x5025e1b2U, 0xe9c90814U, 0x20f9ebb3U, 0x8d9af69eU,
                };
                HW_SCE_p_func100(Param_p2b_func100_021);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 0))
                {
                    WR1_PROG(REG_ECH, 0x00002e40U);

                    static const uint32_t Param_p2b_func101_019[] =
                    {
                        0x400c3652U, 0x19b00af6U, 0x415d810dU, 0x6580bbf1U,
                    };
                    HW_SCE_p_func101(Param_p2b_func101_019);
                }
                else
                {
                    static const uint32_t Param_p2b_func100_022[] =
                    {
                        0x87f0e1cbU, 0x06afd9adU, 0xc94c17ecU, 0xc9d9cfc0U,
                    };
                    HW_SCE_p_func100(Param_p2b_func100_022);

                    HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
                    HW_SCE_p_func_sub023(0x000040c1U, 0x00006404U);
                    WR1_PROG(REG_24H, 0x00006c04U);
                    WAIT_STS(REG_24H, 21, 0);

                    WR1_PROG(REG_E0H, 0x81010120U);
                    WR1_PROG(REG_04H, 0x00000606U);
                    WAIT_STS(REG_04H, 30, 1);
                    RD1_ADDR(REG_100H, &S_RAM[0 + 1]);
                    S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);
                    WR1_PROG(REG_ECH, 0x000037e9U);

                    for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
                    {
                        WR1_PROG(REG_24H, 0x000009c0U);
                        HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

                        WR1_PROG(REG_24H, 0x000011c0U);
                        HW_SCE_p_func_sub017(0x00000991U, 0x00210000U);

                        static const uint32_t Param_p2b_func100_023[] =
                        {
                            0x8ec7a622U, 0xc2ecfd33U, 0x4596d1b1U, 0xdd384955U,
                        };
                        HW_SCE_p_func100(Param_p2b_func100_023);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 0))
                        {
                            WR1_PROG(REG_ECH, 0x00002e40U);

                            static const uint32_t Param_p2b_func101_020[] =
                            {
                                0xd4b47306U, 0x947e48e2U, 0xe08a050cU, 0x6baf7466U,
                            };
                            HW_SCE_p_func101(Param_p2b_func101_020);
                            break;
                        }
                        else
                        {
                            HW_SCE_p_func_sub023(0x00004c0cU, 0x0000880cU);

                            HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
                            WR1_PROG(REG_24H, 0x000040c1U);
                            WAIT_STS(REG_24H, 21, 0);

                            static const uint32_t Param_p2b_func101_021[] =
                            {
                                0xe518ad9dU, 0x5640af24U, 0x34eac94eU, 0x014d63edU,
                            };
                            HW_SCE_p_func101(Param_p2b_func101_021);
                        }
                    }

                    HW_SCE_p_func_sub014(0x38008a40U, 0x00000000U, 0x00260000U);

                    static const uint32_t Param_p2b_func100_024[] =
                    {
                        0x98765488U, 0x67b2035eU, 0x3880187bU, 0x02273ca1U,
                    };
                    HW_SCE_p_func100(Param_p2b_func100_024);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        static const uint32_t Param_p2b_func101_022[] =
                        {
                            0xdbe391c8U, 0xe36886d3U, 0x44ecc41bU, 0x542e2e2dU,
                        };
                        HW_SCE_p_func101(Param_p2b_func101_022);
                        break;
                    }
                    else
                    {
                        static const uint32_t Param_p2b_func101_023[] =
                        {
                            0x624f8893U, 0xe40b8b49U, 0x8082da1aU, 0xc20670a6U,
                        };
                        HW_SCE_p_func101(Param_p2b_func101_023);
                    }
                }
            }

            WR1_PROG(REG_ECH, 0x38000a4bU);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p2b_func100_025[] =
            {
                0xd67e7880U, 0xe9c8649eU, 0x28a2b1caU, 0xa1387d95U,
            };
            HW_SCE_p_func100(Param_p2b_func100_025);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub007(0x00002e20U, 0x38008a20U, 0x00000002U, 0x00260000U);

                static const uint32_t Param_p2b_func100_026[] =
                {
                    0xc0f8142aU, 0x43ece9e1U, 0xe5a42c4cU, 0x95e232e0U,
                };
                HW_SCE_p_func100(Param_p2b_func100_026);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_p2b_func101_024[] =
                    {
                        0x72ead49bU, 0x3189737dU, 0x9848fc7dU, 0x2304bad9U,
                    };
                    HW_SCE_p_func101(Param_p2b_func101_024);
                    break;
                }
                else
                {
                    HW_SCE_p_func_sub023(0x000019c0U, 0x0000e0c1U);

                    static const uint32_t Param_p2b_func101_025[] =
                    {
                        0x4165eaaaU, 0xde546422U, 0x77a875aaU, 0x47feb412U,
                    };
                    HW_SCE_p_func101(Param_p2b_func101_025);
                }
            }
            else
            {
                static const uint32_t Param_p2b_func101_026[] =
                {
                    0x424beb5fU, 0x7e7bd614U, 0xc3225a20U, 0xaa7eb3c8U,
                };
                HW_SCE_p_func101(Param_p2b_func101_026);
            }
        }
    }

    HW_SCE_p_func_sub014(0x38008a20U, 0x00000002U, 0x00A60000U);

    static const uint32_t Param_p2b_func100_027[] =
    {
        0x797c9f8cU, 0xf9c42989U, 0xc34235dcU, 0xabd7d990U,
    };
    HW_SCE_p_func100(Param_p2b_func100_027);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p2b_func102_001[] =
        {
            0x9557ba67U, 0x07316373U, 0x90ae53f1U, 0x62dc9458U,
        };
        HW_SCE_p_func102(Param_p2b_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    static const uint32_t Param_p2b_func100_028[] =
    {
        0xac0314bdU, 0x515c4e7eU, 0xb9f37c2bU, 0xa620448dU,
    };
    HW_SCE_p_func100(Param_p2b_func100_028);

    WR1_PROG(REG_ECH, 0x0000b5c0U);
    WR1_PROG(REG_ECH, 0x00010001U);

    HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
    HW_SCE_p_func_sub023(0x000080c1U, 0x00001dc0U);
    WR1_PROG(REG_24H, 0x00000591U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00bf0001U);

    WR1_PROG(REG_D0H, 0x00000f00U);
    WR1_PROG(REG_C4H, 0x42e087bfU);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000024U);
    WR1_PROG(REG_04H, 0x00000202U);

    for (iLoop = 0U; iLoop < 64U; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
        iLoop = iLoop + 4U;
    }

    static const uint32_t Param_p2b_func100_029[] =
    {
        0xd43ec52dU, 0x5fb382ecU, 0xa9cc436cU, 0x4d6b8853U,
    };
    HW_SCE_p_func100(Param_p2b_func100_029);
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    HW_SCE_p_func_sub013(0x400009cdU, 0x00002213U);

    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

    HW_SCE_p_func_sub020(0x009f0001U, 0x000011c0U, 0x0000a0c1U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub023(0x000009c0U, 0x0000c0c1U);
    WR1_PROG(REG_24H, 0x0000e0c1U);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_24H, 0x00008006U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000011c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);

        static const uint32_t Param_p2b_func100_030[] =
        {
            0xa7c960d8U, 0xb1109e97U, 0x6b23ed89U, 0x19ad0c6dU,
        };
        HW_SCE_p_func100(Param_p2b_func100_030);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2b_func101_027[] =
            {
                0x1f9661cdU, 0x28746ae5U, 0x8cd2741dU, 0x6ddec20bU,
            };
            HW_SCE_p_func101(Param_p2b_func101_027);
            break;
        }
        else
        {
            HW_SCE_p_func_sub023(0x000019c0U, 0x0000d0d0U);
            WR1_PROG(REG_24H, 0x000080c1U);
            WAIT_STS(REG_24H, 21, 0);

            static const uint32_t Param_p2b_func101_028[] =
            {
                0x3f844510U, 0xe045fee9U, 0x9ccc4a88U, 0x014d4648U,
            };
            HW_SCE_p_func101(Param_p2b_func101_028);
        }
    }

    WR1_PROG(REG_24H, 0x000094d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000U);
    HW_SCE_p_func_sub023(0x0000c002U, 0x0000dcd0U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000b80aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func_sub011(0x000030ffU, 0x00000014U);
    WR1_PROG(REG_104H, 0x00000057U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00010001U));

    WR1_PROG(REG_2CH, 0x00000002U);
    WR1_PROG(REG_24H, 0x0000c002U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_E0H, 0x800100c0U);
    HW_SCE_p_func_sub011(0x0000031fU, 0x00000024U);
    WR1_PROG(REG_00H, 0x00008307U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub020(0x00bf0001U, 0x000011c0U, 0x00000991U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000011c0U);
    HW_SCE_p_func_sub016(0x0000c0c1U, 0x0000b500U);
    WR1_PROG(REG_ECH, 0x00010001U);

    HW_SCE_p_func_sub023(0x000005c0U, 0x000080c1U);

    while (1)
    {
        static const uint32_t Param_p2b_func100_031[] =
        {
            0x2601c365U, 0x86269c2cU, 0x8bd2d673U, 0x7fd6e24eU,
        };
        HW_SCE_p_func100(Param_p2b_func100_031);
        HW_SCE_p_func103();
        static const uint32_t Param_p2b_func100_032[] =
        {
            0x628d9e05U, 0xdbb7daa3U, 0xa04bf479U, 0x0ed0c908U,
        };
        HW_SCE_p_func100(Param_p2b_func100_032);
        HW_SCE_p_func_sub012(0x00000052U, 0x01090c84U, 0x00000000U);

        HW_SCE_p_func_sub002(0x0000094aU, 0x80c0000aU, 0x00018303U, 0x00000022U);

        static const uint32_t Param_p2b_func100_033[] =
        {
            0x91cef570U, 0x5ddcb017U, 0x1a28922fU, 0xde55c6f6U,
        };
        HW_SCE_p_func100(Param_p2b_func100_033);
        WR1_PROG(REG_D0H, 0x00000f00U);
        WR1_PROG(REG_C4H, 0x42e097bfU);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (iLoop = 68; iLoop < 132; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
            iLoop = iLoop + 4U;
        }

        static const uint32_t Param_p2b_func100_034[] =
        {
            0x85c5fb6eU, 0xd3462e3cU, 0xefde4039U, 0x337f35b6U,
        };
        HW_SCE_p_func100(Param_p2b_func100_034);
        HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

        HW_SCE_p_func_sub013(0x400019cdU, 0x00002213U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

        HW_SCE_p_func_sub020(0x009f0001U, 0x000019c0U, 0x0000a0c1U);
        HW_SCE_p_func_sub015(0x000080d0U, 0x00870001U);
        HW_SCE_p_func_sub011(0x0000301fU, 0x00000014U);
        HW_SCE_p_func_sub010(0x810100c0U, 0x00003807U);

        HW_SCE_p_func_sub011(0x0000301fU, 0x00000010U);
        HW_SCE_p_func_sub010(0x81010100U, 0x00003807U);

        WR1_PROG(REG_2CH, 0x00000000U);
        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x8000c002U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub002(0x00003506U, 0x800100c0U, 0x0000031fU, 0x0000002cU);
        WR1_PROG(REG_00H, 0x00008307U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub014(0x380088c0U, 0x00000000U, 0x00260000U);

        static const uint32_t Param_p2b_func100_035[] =
        {
            0x84072e81U, 0xb4707fe1U, 0x210e80f2U, 0x478f4a77U,
        };
        HW_SCE_p_func100(Param_p2b_func100_035);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_104H, 0x00003f61U);
            WR1_PROG(REG_B0H, 0x00000f00U);
            WR1_PROG(REG_A4H, 0x42f087bfU);
            WR1_PROG(REG_00H, 0x00013103U);
            WR1_PROG(REG_2CH, 0x00000014U);

            for (iLoop = 0U; iLoop < 64U; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            static const uint32_t Param_p2b_func101_029[] =
            {
                0x4d7de79eU, 0x7aee29b9U, 0xfdb1ad36U, 0xe56bb109U,
            };
            HW_SCE_p_func101(Param_p2b_func101_029);
            break;
        }
        else
        {
            HW_SCE_p_func_sub020(0x009f0001U, 0x000015c0U, 0x0000c0c1U);
            WAIT_STS(REG_24H, 21, 0);

            HW_SCE_p_func_sub011(0x00003083U, 0x00000011U);

            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_24H, 0x0000880eU);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_104H, 0x00003f62U);
            WR1_PROG(REG_D0H, 0x00000f00U);
            WR1_PROG(REG_C4H, 0x42f097bfU);
            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000012U);
            for (iLoop = 68; iLoop < 132; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_C4H, 0x400017bdU);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &S_HEAP[iLoop]);

            HW_SCE_p_func_sub013(0x00800c45U, 0x00002213U);

            HW_SCE_p_func_sub023(0x000009c0U, 0x00001191U);

            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

            HW_SCE_p_func_sub002(0x0000094aU, 0x81c0000aU, 0x00013803U, 0x00000010U);

            static const uint32_t Param_p2b_func101_030[] =
            {
                0xd78e57d3U, 0x88d3ecf5U, 0x786fbc37U, 0x62fe7edfU,
            };
            HW_SCE_p_func101(Param_p2b_func101_030);
        }
    }

    WR1_PROG(REG_ECH, 0x00007c06U);
    WR1_PROG(REG_1CH, 0x00602000U);

    WR1_PROG(REG_A4H, 0x400007bdU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[iLoop]);

    HW_SCE_p_func_sub019(0x00800c45U, 0x00001113U);

    static const uint32_t Param_p2b_func100_036[] =
    {
        0xe8af30a3U, 0x68c2064eU, 0x712f8903U, 0xf66d4c14U,
    };
    HW_SCE_p_func100(Param_p2b_func100_036);
    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func103();
    static const uint32_t Param_p2b_func100_037[] =
    {
        0xd6fee8b4U, 0xfeb8e1cfU, 0xec897771U, 0x8805760eU,
    };
    HW_SCE_p_func100(Param_p2b_func100_037);
    HW_SCE_p_func_sub012(0x00000052U, 0x01090c84U, 0x00000000U);

    static const uint32_t Param_p2b_func100_038[] =
    {
        0x7a264cd4U, 0x63f846bdU, 0x4e808fcaU, 0xacfd971fU,
    };
    HW_SCE_p_func100(Param_p2b_func100_038);
    WR1_PROG(REG_D0H, 0x00000f00U);
    WR1_PROG(REG_C4H, 0x42e097bfU);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    WR1_PROG(REG_04H, 0x00000202U);

    for (iLoop = 68; iLoop < 132; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
        iLoop = iLoop + 4U;
    }

    static const uint32_t Param_p2b_func100_039[] =
    {
        0x771da7e3U, 0x9729dd62U, 0xae475f17U, 0x8047367cU,
    };
    HW_SCE_p_func100(Param_p2b_func100_039);
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    HW_SCE_p_func_sub013(0x400019cdU, 0x00002213U);

    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

    WR1_PROG(REG_28H, 0x009f0001U);
    WR1_PROG(REG_24H, 0x0000b8d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000002U);
    WR1_PROG(REG_24H, 0x00007b0aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0xfcbf0001U);

    WR1_PROG(REG_24H, 0x0000c8d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800103e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x38000fffU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    static const uint32_t Param_p2b_func100_040[] =
    {
        0xf87eee7cU, 0x9e5e9ba6U, 0xd674c5d9U, 0xb96e11d5U,
    };
    HW_SCE_p_func100(Param_p2b_func100_040);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p2b_func100_041[] =
        {
            0xd6c84d13U, 0xcdd54a0aU, 0xf1a3df40U, 0x96ab1f3eU,
        };
        HW_SCE_p_func100(Param_p2b_func100_041);

        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
        WR1_PROG(REG_00H, 0x0000020fU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x0000002bU);

        static const uint32_t Param_p2b_func101_031[] =
        {
            0x18f639afU, 0x6e25c8b7U, 0x6bd5d373U, 0x20c980dfU,
        };
        HW_SCE_p_func101(Param_p2b_func101_031);
        HW_SCE_p_func043();

        WR1_PROG(REG_ECH, 0x0000b4e0U);
        HW_SCE_p_func_sub005(0x0000000cU, 0x00000058U, 0x800103a0U, 0x0000002bU);

        static const uint32_t Param_p2b_func101_032[] =
        {
            0xea8d2962U, 0x23b0c731U, 0x02063f7bU, 0x360e6545U,
        };
        HW_SCE_p_func101(Param_p2b_func101_032);
        HW_SCE_p_func044();

        static const uint32_t Param_p2b_func100_042[] =
        {
            0xfb3eaadcU, 0x1b4c926bU, 0x41d898b5U, 0x5d237607U,
        };
        HW_SCE_p_func100(Param_p2b_func100_042);
        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PubKeyIndex[0]);

        static const uint32_t Param_p2b_func100_043[] =
        {
            0x15b39e7dU, 0xbc172d9fU, 0x0dbd45d3U, 0x9d30cd21U,
        };
        HW_SCE_p_func100(Param_p2b_func100_043);
        HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (iLoop = 0U; iLoop < 64U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2b_func100_044[] =
        {
            0xea7a2df8U, 0x6d487225U, 0x96637959U, 0xd7948d95U,
        };
        HW_SCE_p_func100(Param_p2b_func100_044);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x00e08884U);
        HW_SCE_p_func_sub010(0x810101c0U, 0x00002807U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PubKeyIndex[65]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_p2b_func100_045[] =
        {
            0xf17df3bdU, 0xa237d4c4U, 0x31891948U, 0x398bde44U,
        };
        HW_SCE_p_func100(Param_p2b_func100_045);
        WR1_PROG(REG_18H, 0x00000004U);
        WR1_PROG(REG_24H, 0x00004404U);
        WAIT_STS(REG_18H, 10, 0);

        WR1_PROG(REG_24H, 0x00004804U);
        WAIT_STS(REG_18H, 10, 0);
        WR1_PROG(REG_18H, 0x00000000U);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (iLoop = 68; iLoop < 132; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2b_func100_046[] =
        {
            0x77aecc1aU, 0xc4e61c3cU, 0x32de60c5U, 0xc40e7285U,
        };
        HW_SCE_p_func100(Param_p2b_func100_046);
        HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000010U));

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PubKeyIndex[133]);

        static const uint32_t Param_p2b_func100_047[] =
        {
            0xb77e9d11U, 0x739cdbb4U, 0xb03798c4U, 0x99c1079bU,
        };
        HW_SCE_p_func100(Param_p2b_func100_047);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
        WR1_PROG(REG_00H, 0x0000020fU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x000000fdU);

        static const uint32_t Param_p2b_func101_033[] =
        {
            0x394f8441U, 0xfba13dc3U, 0x22815382U, 0xff49cec6U,
        };
        HW_SCE_p_func101(Param_p2b_func101_033);
        HW_SCE_p_func043();

        WR1_PROG(REG_ECH, 0x0000b4e0U);
        HW_SCE_p_func_sub005(0x0000000dU, 0x00000058U, 0x800103a0U, 0x000000fdU);

        static const uint32_t Param_p2b_func101_034[] =
        {
            0x66692d56U, 0x5e6c77caU, 0xed7b634fU, 0x905615c9U,
        };
        HW_SCE_p_func101(Param_p2b_func101_034);
        HW_SCE_p_func044();

        static const uint32_t Param_p2b_func100_048[] =
        {
            0x35fa4854U, 0xcef1ec09U, 0xab49a001U, 0x599a6c24U,
        };
        HW_SCE_p_func100(Param_p2b_func100_048);
        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PrivKeyIndex[0]);

        static const uint32_t Param_p2b_func100_049[] =
        {
            0x06f73d5fU, 0x532f17d5U, 0x54dc5af0U, 0x6eee362dU,
        };
        HW_SCE_p_func100(Param_p2b_func100_049);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x02e087b7U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (iLoop = 0U; iLoop < 64U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2b_func100_050[] =
        {
            0xbecdb75cU, 0xbca8b94eU, 0x0b91504cU, 0xc1f7fc25U,
        };
        HW_SCE_p_func100(Param_p2b_func100_050);
        WR1_PROG(REG_00H, 0x00012103U);
        WR1_PROG(REG_104H, 0x00000031U);
        WR1_PROG(REG_B0H, 0x00000f00U);
        WR1_PROG(REG_A4H, 0x42f097bfU);
        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000202U);

        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[68]);
        for (iLoop = 64; iLoop < 124; )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &S_HEAP[iLoop + 8]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);

        WR1_PROG(REG_104H, 0x00000000U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);
        WAIT_STS(REG_C8H, 6, 0);

        WR1_PROG(REG_A4H, 0x400017bdU);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[132]);

        HW_SCE_p_func_sub019(0x00800c45U, 0x00001113U);

        static const uint32_t Param_p2b_func100_051[] =
        {
            0x9ac4e83aU, 0xf48e1713U, 0xe59c8f74U, 0xb22f3529U,
        };
        HW_SCE_p_func100(Param_p2b_func100_051);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);

        WR1_PROG(REG_D0H, 0x40000f00U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000202U);

        for (iLoop = 128; iLoop < 192; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2b_func100_052[] =
        {
            0x36d14ec8U, 0xb8c807a7U, 0x74d82cfdU, 0x7a62a60bU,
        };
        HW_SCE_p_func100(Param_p2b_func100_052);
        HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000030U));

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[193]);

        static const uint32_t Param_p2b_func101_035[] =
        {
            0x5e0bdd5bU, 0x98aa40d7U, 0x7420083fU, 0x1fbf92daU,
        };
        HW_SCE_p_func101(Param_p2b_func101_035);
    }
    else
    {
        static const uint32_t Param_p2b_func100_053[] =
        {
            0x44a10193U, 0x9b7f8205U, 0x4ed43b28U, 0xde684559U,
        };
        HW_SCE_p_func100(Param_p2b_func100_053);

        WR1_PROG(REG_2CH, 0x00000024U);
        WR1_PROG(REG_04H, 0x00000302U);
        WAIT_STS(REG_04H, 30, 1);
        RD64_ADDR(REG_100H, &OutData_PubKey[0]);

        static const uint32_t Param_p2b_func100_054[] =
        {
            0xbfc6d200U, 0x18e2c977U, 0xd859db6cU, 0x5abd8659U,
        };
        HW_SCE_p_func100(Param_p2b_func100_054);
        WR1_PROG(REG_E0H, 0x810101c0U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PubKey[64]);

        static const uint32_t Param_p2b_func100_055[] =
        {
            0xea5f5baaU, 0xfd08e672U, 0xe7b9ba08U, 0x2d526356U,
        };
        HW_SCE_p_func100(Param_p2b_func100_055);
        WR1_PROG(REG_104H, 0x00003f61U);
        WR1_PROG(REG_B0H, 0x00000f00U);
        WR1_PROG(REG_A4H, 0x42f097bfU);
        WR1_PROG(REG_00H, 0x00013103U);
        WR1_PROG(REG_2CH, 0x00000010U);

        for (iLoop = 68; iLoop < 132; )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_A4H, 0x400017bdU);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[132]);

        HW_SCE_p_func_sub019(0x00800c45U, 0x00001113U);

        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000302U);
        WAIT_STS(REG_04H, 30, 1);
        RD64_ADDR(REG_100H, &OutData_PrivKey[0]);

        static const uint32_t Param_p2b_func101_036[] =
        {
            0xd097e80dU, 0x8c2ccf6eU, 0x232872d5U, 0xe1cd1cb8U,
        };
        HW_SCE_p_func101(Param_p2b_func101_036);
    }

    static const uint32_t Param_p2b_func102_002[] =
    {
        0x38178303U, 0x237b9524U, 0xe9505df9U, 0x646a3b4aU,
    };
    HW_SCE_p_func102(Param_p2b_func102_002);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
