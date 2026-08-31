/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRsa1024RandomKeyIndexSub (uint32_t MAX_CNT,
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

    WR1_PROG(REG_84H, 0x00002a02U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p2a_func100_001[] =
    {
        0x1fb96e46U, 0x081cd081U, 0x2c72f4dfU, 0x551f4d99U,
    };
    HW_SCE_p_func100(Param_p2a_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_p2a_func100_002[] =
    {
        0x14b1e394U, 0xa13506a4U, 0xc5cb4cb4U, 0x2e6ee502U,
    };
    HW_SCE_p_func100(Param_p2a_func100_002);
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

        WR1_PROG(REG_28H, 0x008f0001U);

        static const uint32_t Param_p2a_func100_003[] =
        {
            0x97b4f88fU, 0xb43c6e83U, 0x2e5860f1U, 0x42fe8c0cU,
        };
        HW_SCE_p_func100(Param_p2a_func100_003);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);
        HW_SCE_p_func_sub002(0x0000d01fU, 0x81040000U, 0x00003813U, 0x00000010U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            static const uint32_t Param_p2a_func100_004[] =
            {
                0x308272beU, 0x6a7b49c2U, 0x120117f1U, 0xfe0313a7U,
            };
            HW_SCE_p_func100(Param_p2a_func100_004);
            HW_SCE_p_func103();
            HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

            WR1_PROG(REG_00H, 0x00003213U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            static const uint32_t Param_p2a_func101_001[] =
            {
                0xd899a1dfU, 0xa6e04f54U, 0x5174433eU, 0x40deffdcU,
            };
            HW_SCE_p_func101(Param_p2a_func101_001);
            iLoop = iLoop + 4U;
        }

        static const uint32_t Param_p2a_func100_005[] =
        {
            0x308272beU, 0x6a7b49c2U, 0x120117f1U, 0xfe0313a7U,
        };
        HW_SCE_p_func100(Param_p2a_func100_005);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);
        WR1_PROG(REG_ECH, 0x0000d060U);
        HW_SCE_p_func_sub010(0x81040000U, 0x00003813U);

        WR1_PROG(REG_2CH, 0x00000011U);
        WR1_PROG(REG_104H, 0x00000f57U);
        WAIT_STS(REG_104H, 31, 1);
        WR16_PROG(REG_100H,
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
                  change_endian_long(0x851EB80EU));

        WR1_PROG(REG_24H, 0x000011c0U);
        HW_SCE_p_func_sub017(0x00001591U, 0x00210000U);

        static const uint32_t Param_p2a_func100_006[] =
        {
            0xad29dc62U, 0x0efb107eU, 0xad45984bU, 0xb49321bbU,
        };
        HW_SCE_p_func100(Param_p2a_func100_006);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2a_func101_002[] =
            {
                0xac9f0956U, 0xd2467c51U, 0x139a5b33U, 0xad785449U,
            };
            HW_SCE_p_func101(Param_p2a_func101_002);
            continue;
        }
        else
        {
            static const uint32_t Param_p2a_func101_003[] =
            {
                0x6c659b24U, 0x4e425a0bU, 0x78cf416eU, 0x1366a62eU,
            };
            HW_SCE_p_func101(Param_p2a_func101_003);
        }

        HW_SCE_p_func_sub014(0x38008a20U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p2a_func100_007[] =
        {
            0xa8a7649dU, 0xbfe63421U, 0x3e720722U, 0x6ab5239cU,
        };
        HW_SCE_p_func100(Param_p2a_func100_007);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00001dc0U);
            HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

            static const uint32_t Param_p2a_func100_008[] =
            {
                0x0f3fc6fdU, 0xb94153a9U, 0x267af091U, 0x7db2ba05U,
            };
            HW_SCE_p_func100(Param_p2a_func100_008);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub023(0x000011c0U, 0x00001d91U);

                static const uint32_t Param_p2a_func101_004[] =
                {
                    0xde3bcf5aU, 0x2f1f00e9U, 0x67567a04U, 0x307ad1d8U,
                };
                HW_SCE_p_func101(Param_p2a_func101_004);
            }
            else
            {
                static const uint32_t Param_p2a_func101_005[] =
                {
                    0xfb19a96fU, 0x17e46b20U, 0xe1ed13b4U, 0x48b60152U,
                };
                HW_SCE_p_func101(Param_p2a_func101_005);
            }

            WR1_PROG(REG_2CH, 0x00000011U);
            WR1_PROG(REG_104H, 0x00000357U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                     change_endian_long(0x00000000U), change_endian_long(0x10000000U));
            WR1_PROG(REG_00H, 0x00003033U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_24H, 0x00001591U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_p2a_func100_009[] =
            {
                0xf3ee43c9U, 0xf16a715eU, 0x486b5890U, 0xd5adc75bU,
            };
            HW_SCE_p_func100(Param_p2a_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p2a_func101_006[] =
                {
                    0xf200cb28U, 0x95d383b6U, 0xefa1d7dcU, 0xe342fa1cU,
                };
                HW_SCE_p_func101(Param_p2a_func101_006);
                continue;
            }
            else
            {
                static const uint32_t Param_p2a_func101_007[] =
                {
                    0x5432a6acU, 0x895f0a01U, 0x4c3d350eU, 0x9a286873U,
                };
                HW_SCE_p_func101(Param_p2a_func101_007);
            }
        }
        else
        {
            static const uint32_t Param_p2a_func101_008[] =
            {
                0xdfeb4c53U, 0x0d1d5003U, 0x408103edU, 0xf7b9246fU,
            };
            HW_SCE_p_func101(Param_p2a_func101_008);
        }

        WR1_PROG(REG_ECH, 0x000008c6U);
        WR1_PROG(REG_ECH, 0x0000094aU);

        for (iLoop = 0U; iLoop < 96U; iLoop++)
        {
            WR1_PROG(REG_ECH, 0x01003906U);
            WR1_PROG(REG_ECH, 0x00002cc0U);
            HW_SCE_p_func_sub002(0x00002cc0U, 0x81010100U, 0x0000303fU, 0x00000014U);
            WR1_PROG(REG_00H, 0x00003807U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_24H, 0x00004006U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000009c0U);
            HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);
            static const uint32_t Param_p2a_func100_010[] =
            {
                0x73ebecc7U, 0xe9f73cb5U, 0x23a2c07eU, 0xf7a27c65U,
            };
            HW_SCE_p_func100(Param_p2a_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);
            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x0000d140U);

                static const uint32_t Param_p2a_func101_009[] =
                {
                    0x27a0a5bcU, 0xbd7a7e0cU, 0xa9945f33U, 0xfac352e2U,
                };
                HW_SCE_p_func101(Param_p2a_func101_009);
                break;
            }
            else
            {
                static const uint32_t Param_p2a_func101_010[] =
                {
                    0x1b68ddf4U, 0xece9a003U, 0x07503ca5U, 0x598ef5a0U,
                };
                HW_SCE_p_func101(Param_p2a_func101_010);
            }
        }

        HW_SCE_p_func_sub014(0x38008940U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p2a_func100_011[] =
        {
            0xa317c927U, 0xd88de3a5U, 0x5415605eU, 0x29024848U,
        };
        HW_SCE_p_func100(Param_p2a_func100_011);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2a_func101_011[] =
            {
                0xed43d36fU, 0xc0df89a1U, 0xed4fd39cU, 0x4476573fU,
            };
            HW_SCE_p_func101(Param_p2a_func101_011);
            continue;
        }

        HW_SCE_p_func_sub023(0x000011c0U, 0x000060c1U);
        HW_SCE_p_func_sub023(0x000011c0U, 0x00000591U);
        WR1_PROG(REG_24H, 0x000080c1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub011(0x0000303fU, 0x00000014U);
        WR1_PROG(REG_104H, 0x00000057U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00010001U));

        HW_SCE_p_func_sub023(0x00004006U, 0x00000dc0U);
        WR1_PROG(REG_24H, 0x000080c1U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);
        static const uint32_t Param_p2a_func100_012[] =
        {
            0x81022f02U, 0xc55d4dd3U, 0x69032594U, 0x79d605bdU,
        };
        HW_SCE_p_func100(Param_p2a_func100_012);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2a_func101_012[] =
            {
                0xaaca257cU, 0xe78596ceU, 0x6cb19cd6U, 0xf50757cdU,
            };
            HW_SCE_p_func101(Param_p2a_func101_012);
        }
        else
        {
            HW_SCE_p_func_sub023(0x0000d0d0U, 0x000019c0U);
            HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

            HW_SCE_p_func_sub001(0x000084d0U, 0x00000800U, 0x8002d008U, 0x000005c0U);
            HW_SCE_p_func_sub023(0x00000189U, 0x000080c1U);

            static const uint32_t Param_p2a_func100_013[] =
            {
                0x94f41beeU, 0x2e70fadcU, 0x5251259aU, 0xf8b94a36U,
            };
            HW_SCE_p_func100(Param_p2a_func100_013);
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

            static const uint32_t Param_p2a_func100_014[] =
            {
                0xb2101807U, 0xd8841e13U, 0x363690f8U, 0xdee420d3U,
            };
            HW_SCE_p_func100(Param_p2a_func100_014);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p2a_func101_013[] =
                {
                    0x982bb79bU, 0x9640a6c4U, 0xa57f90b7U, 0xf71592fcU,
                };
                HW_SCE_p_func101(Param_p2a_func101_013);
                continue;
            }

            WR1_PROG(REG_24H, 0x000098d0U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000b540U);
            HW_SCE_p_func_sub002(0x000000c0U, 0x8090000aU, 0x00008343U, 0x00000020U);

            WR1_PROG(REG_ECH, 0x0000b560U);
            WR1_PROG(REG_ECH, 0x00000006U);

            WR1_PROG(REG_B0H, 0x00000300U);
            WR1_PROG(REG_A4H, 0x42e0873fU);
            HW_SCE_p_func_sub011(0x00001343U, 0x00000020U);

            HW_SCE_p_func_sub021(0x00000c84U);

            HW_SCE_p_func_sub019(0x400009cdU, 0x00001113U);

            HW_SCE_p_func_sub014(0x38008a20U, 0x00000000U, 0x00260000U);

            static const uint32_t Param_p2a_func100_015[] =
            {
                0x76cc74d4U, 0x59965208U, 0xe8a7d87fU, 0xe1b57d3fU,
            };
            HW_SCE_p_func100(Param_p2a_func100_015);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_7CH, 0x00000021U);
                WR1_PROG(REG_00H, 0x00005113U);
                WR1_PROG(REG_74H, 0x00000004U);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                static const uint32_t Param_p2a_func101_014[] =
                {
                    0x72781bc6U, 0x9c1a437cU, 0xa9733a1fU, 0x0f79bf92U,
                };
                HW_SCE_p_func101(Param_p2a_func101_014);
            }
            else
            {
                WR1_PROG(REG_7CH, 0x00000041U);
                WR1_PROG(REG_00H, 0x00005113U);
                WR1_PROG(REG_74H, 0x00000004U);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                static const uint32_t Param_p2a_func101_015[] =
                {
                    0xdfbfd057U, 0xac57bef0U, 0x66b482d0U, 0xb4279a72U,
                };
                HW_SCE_p_func101(Param_p2a_func101_015);
            }

            static const uint32_t Param_p2a_func100_016[] =
            {
                0x19ecc5efU, 0x50046f94U, 0xe53fb3f6U, 0x6a4007c6U,
            };
            HW_SCE_p_func100(Param_p2a_func100_016);
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

                static const uint32_t Param_p2a_func101_016[] =
                {
                    0x677321ffU, 0x1a5b95e6U, 0xbe47d278U, 0x83345c77U,
                };
                HW_SCE_p_func101(Param_p2a_func101_016);
            }

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            static const uint32_t Param_p2a_func100_017[] =
            {
                0x67ca3062U, 0xf487c1d4U, 0x252ffbc7U, 0x56f4d158U,
            };
            HW_SCE_p_func100(Param_p2a_func100_017);
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

                static const uint32_t Param_p2a_func101_017[] =
                {
                    0x51f1fe67U, 0x2b55f583U, 0xd0183856U, 0xc41ef963U,
                };
                HW_SCE_p_func101(Param_p2a_func101_017);
            }

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            static const uint32_t Param_p2a_func100_018[] =
            {
                0x1982eb37U, 0x311f8a6eU, 0xafe2e477U, 0xdbb76737U,
            };
            HW_SCE_p_func100(Param_p2a_func100_018);
            WR1_PROG(REG_24H, 0x0000a0c1U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000a52U);

            WR1_PROG(REG_24H, 0x000084d0U);
            WAIT_STS(REG_24H, 21, 0);
            HW_SCE_p_func_sub001(0x00029008U, 0x00000800U, 0x8000c0c1U, 0x00006404U);
            WR1_PROG(REG_24H, 0x00006c04U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_E0H, 0x81010160U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_2CH, 0x00000010U);

                for (jLoop = 0U; jLoop < 16U; )
                {
                    static const uint32_t Param_p2a_func100_019[] =
                    {
                        0x370e2528U, 0x09215692U, 0x397fbe80U, 0xa0361021U,
                    };
                    HW_SCE_p_func100(Param_p2a_func100_019);
                    HW_SCE_p_func103();
                    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

                    WR1_PROG(REG_00H, 0x00003213U);
                    WAIT_STS(REG_00H, 25, 0);
                    WR1_PROG(REG_1CH, 0x00001800U);

                    static const uint32_t Param_p2a_func101_018[] =
                    {
                        0x68612f15U, 0x2b99ae27U, 0xc6a90302U, 0x863b3725U,
                    };
                    HW_SCE_p_func101(Param_p2a_func101_018);
                    jLoop = jLoop + 4U;
                }

                static const uint32_t Param_p2a_func100_020[] =
                {
                    0x4709ca31U, 0x0b2e9badU, 0xc932ddc3U, 0x5be0cd9eU,
                };
                HW_SCE_p_func100(Param_p2a_func100_020);

                HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
                HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
                HW_SCE_p_func_sub023(0x00000591U, 0x0000c0c1U);

                HW_SCE_p_func_sub023(0x000050d0U, 0x000084d0U);
                HW_SCE_p_func_sub001(0x00029008U, 0x00000800U, 0x8000c0c1U, 0x000088d0U);
                HW_SCE_p_func_sub023(0x00009008U, 0x000011c0U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x00000581U, 0x00000581U);
                HW_SCE_p_func_sub023(0x0000c0c1U, 0x000050d0U);

                WR1_PROG(REG_24H, 0x000084d0U);
                WAIT_STS(REG_24H, 21, 0);
                HW_SCE_p_func_sub001(0x00029008U, 0x00000800U, 0x8000c0c1U, 0x000088d0U);

                HW_SCE_p_func_sub023(0x00000dc0U, 0x000040c1U);

                WR1_PROG(REG_18H, 0x00000004U);
                WR1_PROG(REG_38H, 0x00000c40U);
                WAIT_STS(REG_18H, 10, 0);
                WR1_PROG(REG_18H, 0x00000000U);

                WR1_PROG(REG_24H, 0x000005c0U);
                HW_SCE_p_func_sub017(0x00001191U, 0x00210000U);

                HW_SCE_p_func_sub023(0x000005c0U, 0x000040c1U);
                WR1_PROG(REG_24H, 0x000011c0U);
                HW_SCE_p_func_sub017(0x00000991U, 0x00210000U);

                static const uint32_t Param_p2a_func100_021[] =
                {
                    0xc20c2b7fU, 0xdeb9736dU, 0x6a1e227dU, 0x7ac1cb13U,
                };
                HW_SCE_p_func100(Param_p2a_func100_021);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 0))
                {
                    WR1_PROG(REG_ECH, 0x00002e40U);

                    static const uint32_t Param_p2a_func101_019[] =
                    {
                        0xd9901c60U, 0x6bbf8f3bU, 0xe80eadd2U, 0x38cd54f7U,
                    };
                    HW_SCE_p_func101(Param_p2a_func101_019);
                }
                else
                {
                    static const uint32_t Param_p2a_func100_022[] =
                    {
                        0x6ed922bfU, 0x5b4e139aU, 0x12a11497U, 0x9b7b9fcfU,
                    };
                    HW_SCE_p_func100(Param_p2a_func100_022);

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

                        static const uint32_t Param_p2a_func100_023[] =
                        {
                            0xf9c188d9U, 0xc11afd0aU, 0x99af0d6bU, 0x3c2358b0U,
                        };
                        HW_SCE_p_func100(Param_p2a_func100_023);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 0))
                        {
                            WR1_PROG(REG_ECH, 0x00002e40U);

                            static const uint32_t Param_p2a_func101_020[] =
                            {
                                0xbb7d1ae6U, 0x6b1ece1fU, 0xe857ed7eU, 0x96c8652bU,
                            };
                            HW_SCE_p_func101(Param_p2a_func101_020);
                            break;
                        }
                        else
                        {
                            HW_SCE_p_func_sub023(0x00004c0cU, 0x0000880cU);

                            HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
                            WR1_PROG(REG_24H, 0x000040c1U);
                            WAIT_STS(REG_24H, 21, 0);

                            static const uint32_t Param_p2a_func101_021[] =
                            {
                                0xff623b76U, 0x9bbd89b4U, 0xfc27bd0bU, 0x36ae4523U,
                            };
                            HW_SCE_p_func101(Param_p2a_func101_021);
                        }
                    }

                    HW_SCE_p_func_sub014(0x38008a40U, 0x00000000U, 0x00260000U);

                    static const uint32_t Param_p2a_func100_024[] =
                    {
                        0xa47cd66bU, 0x9cba44dcU, 0x319d67e8U, 0x8b1db386U,
                    };
                    HW_SCE_p_func100(Param_p2a_func100_024);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        static const uint32_t Param_p2a_func101_022[] =
                        {
                            0x944c4aa1U, 0x49fa5f7fU, 0xef1e79adU, 0xea096376U,
                        };
                        HW_SCE_p_func101(Param_p2a_func101_022);
                        break;
                    }
                    else
                    {
                        static const uint32_t Param_p2a_func101_023[] =
                        {
                            0x04739207U, 0x06ed1bc5U, 0x4dca20d1U, 0xa82347d7U,
                        };
                        HW_SCE_p_func101(Param_p2a_func101_023);
                    }
                }
            }

            WR1_PROG(REG_ECH, 0x38000a4bU);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p2a_func100_025[] =
            {
                0x0001d18bU, 0xdf6784e1U, 0xace4ad69U, 0xc469425fU,
            };
            HW_SCE_p_func100(Param_p2a_func100_025);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub007(0x00002e20U, 0x38008a20U, 0x00000002U, 0x00260000U);

                static const uint32_t Param_p2a_func100_026[] =
                {
                    0x6e3d15b3U, 0xb4dc0c86U, 0x833b7f90U, 0xa1055b37U,
                };
                HW_SCE_p_func100(Param_p2a_func100_026);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_p2a_func101_024[] =
                    {
                        0xe5a62450U, 0x16727ebbU, 0xcba7d912U, 0x52ca8212U,
                    };
                    HW_SCE_p_func101(Param_p2a_func101_024);
                    break;
                }
                else
                {
                    HW_SCE_p_func_sub023(0x000019c0U, 0x0000e0c1U);

                    static const uint32_t Param_p2a_func101_025[] =
                    {
                        0x49d15384U, 0x78db1911U, 0x4fd8119aU, 0x0db65cc9U,
                    };
                    HW_SCE_p_func101(Param_p2a_func101_025);
                }
            }
            else
            {
                static const uint32_t Param_p2a_func101_026[] =
                {
                    0xc924b0c3U, 0x337001bfU, 0x6902ba7dU, 0x183a6dd3U,
                };
                HW_SCE_p_func101(Param_p2a_func101_026);
            }
        }
    }

    HW_SCE_p_func_sub014(0x38008a20U, 0x00000002U, 0x00A60000U);

    static const uint32_t Param_p2a_func100_027[] =
    {
        0xeb2ab658U, 0x65d21d66U, 0x0da6fa4fU, 0x7c925b48U,
    };
    HW_SCE_p_func100(Param_p2a_func100_027);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p2a_func102_001[] =
        {
            0x88da49e3U, 0x4801ae72U, 0xfaf4d9caU, 0xa218a591U,
        };
        HW_SCE_p_func102(Param_p2a_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    static const uint32_t Param_p2a_func100_028[] =
    {
        0x2ab47987U, 0xd77f2a5aU, 0xaa782e07U, 0xfc61b4c4U,
    };
    HW_SCE_p_func100(Param_p2a_func100_028);

    WR1_PROG(REG_ECH, 0x0000b5c0U);
    WR1_PROG(REG_ECH, 0x00010001U);

    HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
    HW_SCE_p_func_sub023(0x000080c1U, 0x00001dc0U);
    WR1_PROG(REG_34H, 0x00000800U);
    HW_SCE_p_func_sub001(0x8000c0c1U, 0x00000020U, 0x800019c0U, 0x00000591U);
    WR1_PROG(REG_24H, 0x000040c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001U);

    WR1_PROG(REG_D0H, 0x00000700U);
    WR1_PROG(REG_C4H, 0x42e087bfU);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000024U);
    WR1_PROG(REG_04H, 0x00000282U);

    for (iLoop = 0U; iLoop < 32U; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
        iLoop = iLoop + 4U;
    }

    static const uint32_t Param_p2a_func100_029[] =
    {
        0xfc99d2e6U, 0x32ae5f36U, 0x12a184f3U, 0xbc2c702dU,
    };
    HW_SCE_p_func100(Param_p2a_func100_029);
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    HW_SCE_p_func_sub013(0x400009cdU, 0x00002213U);

    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

    HW_SCE_p_func_sub020(0x008f0001U, 0x0000b0d0U, 0x0000c8d0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e8d0U);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_24H, 0x00008006U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000011c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00210000U);

        static const uint32_t Param_p2a_func100_030[] =
        {
            0x27480881U, 0xba71af30U, 0x7d92b8a1U, 0x7019b6b9U,
        };
        HW_SCE_p_func100(Param_p2a_func100_030);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p2a_func101_027[] =
            {
                0xe75dda89U, 0x15caa1deU, 0x7558f29eU, 0x3fd0d6c9U,
            };
            HW_SCE_p_func101(Param_p2a_func101_027);
            break;
        }
        else
        {
            HW_SCE_p_func_sub023(0x000019c0U, 0x0000d0d0U);
            WR1_PROG(REG_24H, 0x000080c1U);
            WAIT_STS(REG_24H, 21, 0);

            static const uint32_t Param_p2a_func101_028[] =
            {
                0x715b495bU, 0x1f5cd765U, 0xf202b576U, 0x98d0b8faU,
            };
            HW_SCE_p_func101(Param_p2a_func101_028);
        }
    }

    WR1_PROG(REG_24H, 0x000094d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000U);
    HW_SCE_p_func_sub023(0x0000c002U, 0x0000dcd0U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_34H, 0x00000800U);
    WR1_PROG(REG_24H, 0x8000980aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001U);

    HW_SCE_p_func_sub011(0x0000307fU, 0x00000014U);
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

    HW_SCE_p_func_sub020(0x009f0001U, 0x000011c0U, 0x00000991U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000011c0U);
    HW_SCE_p_func_sub016(0x0000e0c1U, 0x0000b500U);
    WR1_PROG(REG_ECH, 0x00010001U);

    HW_SCE_p_func_sub023(0x000005c0U, 0x000080c1U);

    while (1)
    {
        static const uint32_t Param_p2a_func100_031[] =
        {
            0x17a24cd5U, 0xc54f82dfU, 0xbe2fe3e4U, 0xf93aca4dU,
        };
        HW_SCE_p_func100(Param_p2a_func100_031);
        HW_SCE_p_func103();
        static const uint32_t Param_p2a_func100_032[] =
        {
            0xb289e5d1U, 0x24522af0U, 0x229710feU, 0xba1709edU,
        };
        HW_SCE_p_func100(Param_p2a_func100_032);
        HW_SCE_p_func_sub012(0x00000052U, 0x01090c84U, 0x00000000U);

        HW_SCE_p_func_sub002(0x0000094aU, 0x80a0000aU, 0x00008383U, 0x00000022U);

        static const uint32_t Param_p2a_func100_033[] =
        {
            0x7daefa82U, 0x521af0cfU, 0x4dba7417U, 0xd27b184bU,
        };
        HW_SCE_p_func100(Param_p2a_func100_033);
        WR1_PROG(REG_D0H, 0x00000700U);
        WR1_PROG(REG_C4H, 0x42e097bfU);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 36; iLoop < 68; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
            iLoop = iLoop + 4U;
        }

        static const uint32_t Param_p2a_func100_034[] =
        {
            0xb3fbcaa6U, 0x69ad23d1U, 0x003c5402U, 0xb99ced8fU,
        };
        HW_SCE_p_func100(Param_p2a_func100_034);
        HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

        HW_SCE_p_func_sub013(0x400019cdU, 0x00002213U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

        WR1_PROG(REG_28H, 0x008f0001U);
        HW_SCE_p_func_sub001(0x00001dc0U, 0x00000800U, 0x800080c1U, 0x000080d0U);

        WR1_PROG(REG_28H, 0x00870001U);
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

        static const uint32_t Param_p2a_func100_035[] =
        {
            0x3077c994U, 0x7d4f1137U, 0x4e3cc110U, 0xcdb09089U,
        };
        HW_SCE_p_func100(Param_p2a_func100_035);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_28H, 0x008f0001U);

            WR1_PROG(REG_104H, 0x00001f61U);
            WR1_PROG(REG_B0H, 0x00000700U);
            WR1_PROG(REG_A4H, 0x42f087bfU);
            WR1_PROG(REG_00H, 0x00003143U);
            WR1_PROG(REG_2CH, 0x00000015U);
            for (iLoop = 0U; iLoop < 16U; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_00H, 0x00003143U);
            WR1_PROG(REG_2CH, 0x00000014U);
            for (iLoop = 16; iLoop < 32U; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            static const uint32_t Param_p2a_func101_029[] =
            {
                0x994c1884U, 0xed7fc7d5U, 0x31e198f6U, 0x9eb6897bU,
            };
            HW_SCE_p_func101(Param_p2a_func101_029);
            break;
        }
        else
        {
            WR1_PROG(REG_28H, 0x008f0001U);
            WR1_PROG(REG_34H, 0x00000008U);
            HW_SCE_p_func_sub023(0x800011c0U, 0x0000e0c1U);

            HW_SCE_p_func_sub011(0x00003043U, 0x00000018U);

            WR1_PROG(REG_28H, 0x009f0001U);

            WR1_PROG(REG_24H, 0x0000890eU);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_104H, 0x00001f62U);
            WR1_PROG(REG_D0H, 0x00000700U);
            WR1_PROG(REG_C4H, 0x42f097bfU);
            WR1_PROG(REG_00H, 0x00003283U);
            WR1_PROG(REG_2CH, 0x00000012U);
            for (iLoop = 36; iLoop < 68; )
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

            HW_SCE_p_func_sub023(0x00001de1U, 0x000040c1U);

            HW_SCE_p_func_sub002(0x0000094aU, 0x81a0000aU, 0x00003883U, 0x00000010U);

            static const uint32_t Param_p2a_func101_030[] =
            {
                0xb2b28a0dU, 0x98773ad8U, 0xd4aee07aU, 0x833efbc7U,
            };
            HW_SCE_p_func101(Param_p2a_func101_030);
        }
    }

    WR1_PROG(REG_ECH, 0x00007c06U);
    WR1_PROG(REG_1CH, 0x00602000U);

    WR1_PROG(REG_A4H, 0x400007bdU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[iLoop]);

    HW_SCE_p_func_sub019(0x00800c45U, 0x00001113U);

    WR1_PROG(REG_34H, 0x00000802U);
    HW_SCE_p_func_sub023(0x800088d0U, 0x000088d0U);

    WR1_PROG(REG_24H, 0x0000b8d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000002U);
    WR1_PROG(REG_24H, 0x00007b0aU);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub006(0x0000c8d0U, 0x00000800U, 0x8000ccd0U);

    WR1_PROG(REG_28H, 0x009f0001U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800103e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x38000fffU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    static const uint32_t Param_p2a_func100_036[] =
    {
        0x199771aaU, 0xba49ce89U, 0x936a86c8U, 0x61b0297fU,
    };
    HW_SCE_p_func100(Param_p2a_func100_036);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p2a_func100_037[] =
        {
            0x2428d673U, 0x343e5be4U, 0x37f8e3f4U, 0x3d94b370U,
        };
        HW_SCE_p_func100(Param_p2a_func100_037);

        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
        WR1_PROG(REG_00H, 0x0000020fU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x0000002aU);

        static const uint32_t Param_p2a_func101_031[] =
        {
            0x71fbd176U, 0xdecc2073U, 0xfbde9f70U, 0x46b5d07cU,
        };
        HW_SCE_p_func101(Param_p2a_func101_031);
        HW_SCE_p_func043();

        WR1_PROG(REG_ECH, 0x0000b4e0U);
        HW_SCE_p_func_sub005(0x0000000aU, 0x00000058U, 0x800103a0U, 0x0000002aU);

        static const uint32_t Param_p2a_func101_032[] =
        {
            0x25eab0a7U, 0xeedf4e4eU, 0x3974534bU, 0x0e853059U,
        };
        HW_SCE_p_func101(Param_p2a_func101_032);
        HW_SCE_p_func044();

        static const uint32_t Param_p2a_func100_038[] =
        {
            0x5fa2ac2fU, 0x6180b08bU, 0xf3ee3300U, 0x50d5a863U,
        };
        HW_SCE_p_func100(Param_p2a_func100_038);
        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PubKeyIndex[0]);

        static const uint32_t Param_p2a_func100_039[] =
        {
            0x43fce02eU, 0xe24f9819U, 0x798bdf21U, 0xa246cc05U,
        };
        HW_SCE_p_func100(Param_p2a_func100_039);
        HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x02e08887U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 0U; iLoop < 32U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2a_func100_040[] =
        {
            0x4c66c6ddU, 0xdd3f0015U, 0x4ca8409fU, 0x5aa5e529U,
        };
        HW_SCE_p_func100(Param_p2a_func100_040);
        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x00e08884U);
        HW_SCE_p_func_sub010(0x810101c0U, 0x00002807U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PubKeyIndex[33]);

        WAIT_STS(REG_C8H, 6, 0);

        static const uint32_t Param_p2a_func100_041[] =
        {
            0x7bc8803aU, 0xa0137578U, 0x1fbde34cU, 0x64e0ae17U,
        };
        HW_SCE_p_func100(Param_p2a_func100_041);
        WR1_PROG(REG_18H, 0x00000004U);
        WR1_PROG(REG_24H, 0x00004404U);
        WAIT_STS(REG_18H, 10, 0);

        WR1_PROG(REG_24H, 0x00004804U);
        WAIT_STS(REG_18H, 10, 0);
        WR1_PROG(REG_18H, 0x00000000U);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 36; iLoop < 68; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2a_func100_042[] =
        {
            0x95d33a9dU, 0x038dc668U, 0x6841f86eU, 0x6bc4d8bfU,
        };
        HW_SCE_p_func100(Param_p2a_func100_042);
        HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000008U));

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PubKeyIndex[69]);

        static const uint32_t Param_p2a_func100_043[] =
        {
            0xa243fb38U, 0xcfdc8352U, 0x176677d7U, 0x85951b62U,
        };
        HW_SCE_p_func100(Param_p2a_func100_043);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
        WR1_PROG(REG_00H, 0x0000020fU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000020U);

        static const uint32_t Param_p2a_func101_033[] =
        {
            0x7a9d80ffU, 0x776a4124U, 0xcfc0d8f1U, 0x9bf14cedU,
        };
        HW_SCE_p_func101(Param_p2a_func101_033);
        HW_SCE_p_func043();

        WR1_PROG(REG_ECH, 0x0000b4e0U);
        HW_SCE_p_func_sub005(0x0000000bU, 0x00000058U, 0x800103a0U, 0x00000020U);

        static const uint32_t Param_p2a_func101_034[] =
        {
            0x929ba5deU, 0x944d881aU, 0xf081b692U, 0x45370d03U,
        };
        HW_SCE_p_func101(Param_p2a_func101_034);
        HW_SCE_p_func044();

        static const uint32_t Param_p2a_func100_044[] =
        {
            0xebd0a0d1U, 0xa766c73eU, 0xcf0b6fc3U, 0xfe03f64cU,
        };
        HW_SCE_p_func100(Param_p2a_func100_044);
        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PrivKeyIndex[0]);

        static const uint32_t Param_p2a_func100_045[] =
        {
            0xc3d5ecb2U, 0x59e1d7d8U, 0xc3576c47U, 0x841cac4cU,
        };
        HW_SCE_p_func100(Param_p2a_func100_045);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x02e087b7U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 0U; iLoop < 32U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2a_func100_046[] =
        {
            0xfd08ea8dU, 0x5cd52b2cU, 0xa51f9128U, 0x9cff4242U,
        };
        HW_SCE_p_func100(Param_p2a_func100_046);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 32; iLoop < 64U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2a_func100_047[] =
        {
            0x58c81937U, 0xea52e29aU, 0x933261f7U, 0x57282707U,
        };
        HW_SCE_p_func100(Param_p2a_func100_047);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);

        WR1_PROG(REG_D0H, 0x40000700U);
        WR1_PROG(REG_C4H, 0x00e087b7U);
        WR1_PROG(REG_04H, 0x00000282U);

        for (iLoop = 64; iLoop < 96U; )
        {
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        static const uint32_t Param_p2a_func100_048[] =
        {
            0x8e9798bbU, 0x1429dce1U, 0x33bad5e8U, 0x2c23ef01U,
        };
        HW_SCE_p_func100(Param_p2a_func100_048);
        HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000018U));

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[97]);

        static const uint32_t Param_p2a_func101_035[] =
        {
            0x19c5d3ccU, 0x8f6947f6U, 0x7fc75e21U, 0x894c7d8fU,
        };
        HW_SCE_p_func101(Param_p2a_func101_035);
    }
    else
    {
        static const uint32_t Param_p2a_func100_049[] =
        {
            0xef40ee55U, 0x7e91fb78U, 0x13ed610fU, 0x36352957U,
        };
        HW_SCE_p_func100(Param_p2a_func100_049);

        WR1_PROG(REG_2CH, 0x00000024U);
        WR1_PROG(REG_04H, 0x00000382U);
        WAIT_STS(REG_04H, 30, 1);
        RD32_ADDR(REG_100H, &OutData_PubKey[0]);

        static const uint32_t Param_p2a_func100_050[] =
        {
            0xd4d4a3e5U, 0xc1caa233U, 0x44a9433dU, 0x7ee31e97U,
        };
        HW_SCE_p_func100(Param_p2a_func100_050);
        WR1_PROG(REG_E0H, 0x810101c0U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &OutData_PubKey[32]);

        static const uint32_t Param_p2a_func100_051[] =
        {
            0xe512b7eeU, 0xda4e182aU, 0x7db535aeU, 0xf498200bU,
        };
        HW_SCE_p_func100(Param_p2a_func100_051);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000382U);
        WAIT_STS(REG_04H, 30, 1);
        RD32_ADDR(REG_100H, &OutData_PrivKey[0]);

        static const uint32_t Param_p2a_func101_036[] =
        {
            0xc0b9810bU, 0xe3f47f17U, 0xda3eedf4U, 0x17e7ac29U,
        };
        HW_SCE_p_func101(Param_p2a_func101_036);
    }

    static const uint32_t Param_p2a_func102_002[] =
    {
        0x24aaab1aU, 0x93acdb7bU, 0x9b21b62cU, 0x89da253fU,
    };
    HW_SCE_p_func102(Param_p2a_func102_002);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
