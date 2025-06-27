/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_RSA3072_KeyPairGenerateSub (const uint32_t InData_KeyMode[],
                                             const uint32_t MAX_CNT,
                                             uint32_t       OutData_PubKey[],
                                             uint32_t       OutData_PrivKeyIndex[],
                                             uint32_t       OutData_PrivKey[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;
    uint32_t kLoop   = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x003a0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x00000e50U);

    WR1_PROG(REG_1600H, 0x00000a31U);
    for (kLoop = 0U; kLoop < MAX_CNT; kLoop++)
    {
        WR1_PROG(REG_1444H, 0x00002fb0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_160H, 0x00030005U);
        WR1_PROG(REG_164H, 0x0007000bU);
        WR1_PROG(REG_168H, 0x000d0011U);
        WR1_PROG(REG_16CH, 0x00130017U);
        WR1_PROG(REG_170H, 0x001d001fU);
        WR1_PROG(REG_174H, 0x00250029U);
        WR1_PROG(REG_178H, 0x002b002fU);
        WR1_PROG(REG_17CH, 0x003b003dU);
        WR1_PROG(REG_180H, 0x00430047U);
        WR1_PROG(REG_184H, 0x0049004fU);
        WR1_PROG(REG_188H, 0x00530059U);
        WR1_PROG(REG_18CH, 0x00610065U);
        WR1_PROG(REG_190H, 0x0067006bU);
        WR1_PROG(REG_194H, 0x006d0071U);
        WR1_PROG(REG_198H, 0x007f0083U);
        WR1_PROG(REG_19CH, 0x0089008bU);
        WR1_PROG(REG_1A0H, 0x00950097U);
        WR1_PROG(REG_1A4H, 0x009d00a3U);
        WR1_PROG(REG_1A8H, 0x00a700adU);
        WR1_PROG(REG_1ACH, 0x00b300b5U);
        WR1_PROG(REG_1B0H, 0x00bf00c1U);
        WR1_PROG(REG_1B4H, 0x00c500c7U);
        WR1_PROG(REG_1B8H, 0x00d300dfU);
        WR1_PROG(REG_1BCH, 0x00e300e5U);
        WR1_PROG(REG_1C0H, 0x00e900efU);
        WR1_PROG(REG_1C4H, 0x00f100fbU);
        WR1_PROG(REG_1C8H, 0x01010107U);
        WR1_PROG(REG_1CCH, 0x010d010fU);
        WR1_PROG(REG_1D0H, 0x01150119U);
        WR1_PROG(REG_1D4H, 0x011b0125U);
        WR1_PROG(REG_1D8H, 0x01330137U);
        WR1_PROG(REG_1DCH, 0x0139013dU);
        WR1_PROG(REG_1E0H, 0x014b0151U);
        WR1_PROG(REG_1E4H, 0x015b015dU);
        WR1_PROG(REG_1E8H, 0x01610167U);
        WR1_PROG(REG_1ECH, 0x016f0175U);
        WR1_PROG(REG_1F0H, 0x017b017fU);
        WR1_PROG(REG_1F4H, 0x0185018dU);
        WR1_PROG(REG_1F8H, 0x01910199U);
        WR1_PROG(REG_1FCH, 0x01a301a5U);
        WR1_PROG(REG_200H, 0x01af01b1U);
        WR1_PROG(REG_204H, 0x01b701bbU);
        WR1_PROG(REG_208H, 0x01c101c9U);
        WR1_PROG(REG_20CH, 0x01cd01cfU);
        WR1_PROG(REG_210H, 0x01d301dfU);
        WR1_PROG(REG_214H, 0x01e701ebU);
        WR1_PROG(REG_218H, 0x01f301f7U);
        WR1_PROG(REG_21CH, 0x01fd0000U);

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x000000c0U);
        WR1_PROG(REG_1608H, 0x80b00006U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x034300c1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x09e471e4U, 0x6ae25eaaU, 0xa8d7b9f0U, 0x77ad6be3U);
        HW_SCE_p_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x0000d01fU);
        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000028U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        for (iLoop = 0U; iLoop < 40U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x3ded4471U, 0x8afc490cU, 0x82c0194dU, 0x9c4eb5fcU);
            HW_SCE_p_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x4018aaa3U, 0xbff9b286U, 0x457b1a04U, 0x93e04171U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x854de42aU, 0xe0229b06U, 0xccb0e716U, 0xaf6d1d56U);
        HW_SCE_p_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x0000d060U);
        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x00002fb0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_980H, 0xB51EB851U);
        WR1_PROG(REG_984H, 0xEB851EB8U);
        WR1_PROG(REG_988H, 0x51EB851EU);
        WR1_PROG(REG_98CH, 0xB851EB85U);
        WR1_PROG(REG_990H, 0x1EB851EBU);
        WR1_PROG(REG_994H, 0x851EB851U);
        WR1_PROG(REG_998H, 0xEB851EB8U);
        WR1_PROG(REG_99CH, 0x51EB851EU);
        WR1_PROG(REG_9A0H, 0xB851EB85U);
        WR1_PROG(REG_9A4H, 0x1EB851EBU);
        WR1_PROG(REG_9A8H, 0x851EB851U);
        WR1_PROG(REG_9ACH, 0xEB851EB8U);
        WR1_PROG(REG_9B0H, 0x51EB851EU);
        WR1_PROG(REG_9B4H, 0xB851EB85U);
        WR1_PROG(REG_9B8H, 0x1EB851EBU);
        WR1_PROG(REG_9BCH, 0x851EB851U);
        WR1_PROG(REG_9C0H, 0xEB851EB8U);
        WR1_PROG(REG_9C4H, 0x51EB851EU);
        WR1_PROG(REG_9C8H, 0xB851EB85U);
        WR1_PROG(REG_9CCH, 0x1EB851EBU);
        WR1_PROG(REG_9D0H, 0x851EB851U);
        WR1_PROG(REG_9D4H, 0xEB851EB8U);
        WR1_PROG(REG_9D8H, 0x51EB851EU);
        WR1_PROG(REG_9DCH, 0xB851EB85U);
        WR1_PROG(REG_9E0H, 0x1EB851EBU);
        WR1_PROG(REG_9E4H, 0x851EB851U);
        WR1_PROG(REG_9E8H, 0xEB851EB8U);
        WR1_PROG(REG_9ECH, 0x51EB851EU);
        WR1_PROG(REG_9F0H, 0xB851EB85U);
        WR1_PROG(REG_9F4H, 0x1EB851EBU);
        WR1_PROG(REG_9F8H, 0x851EB851U);
        WR1_PROG(REG_9FCH, 0xEB851EB8U);
        WR1_PROG(REG_A00H, 0x51EB851EU);
        WR1_PROG(REG_A04H, 0xB851EB85U);
        WR1_PROG(REG_A08H, 0x1EB851EBU);
        WR1_PROG(REG_A0CH, 0x851EB851U);
        WR1_PROG(REG_A10H, 0xEB851EB8U);
        WR1_PROG(REG_A14H, 0x51EB851EU);
        WR1_PROG(REG_A18H, 0xB851EB85U);
        WR1_PROG(REG_A1CH, 0x1EB851EBU);
        WR1_PROG(REG_A20H, 0x851EB851U);
        WR1_PROG(REG_A24H, 0xEB851EB8U);
        WR1_PROG(REG_A28H, 0x51EB851EU);
        WR1_PROG(REG_A2CH, 0xB851EB85U);
        WR1_PROG(REG_A30H, 0x1EB851EBU);
        WR1_PROG(REG_A34H, 0x851EB851U);
        WR1_PROG(REG_A38H, 0xEB851EB8U);
        WR1_PROG(REG_A3CH, 0x51EB851EU);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x1818000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x7a144583U, 0xddb0efc0U, 0x788db1a4U, 0x133b401bU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0xf96a7839U, 0x054b01efU, 0x249e2326U, 0xe5742124U);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0x6b6f930cU, 0xb69eff0dU, 0x5066efb6U, 0xd51f213fU);
        }

        WR1_PROG(REG_1600H, 0x38008a20U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x7a5a19ebU, 0x1b21a894U, 0x8860c788U, 0x36306d86U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000320U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x581158c4U, 0xc1ef4718U, 0x253d635aU, 0xb13bb7c1U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000320U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x1818000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0x8f47d113U, 0x4e51c7b5U, 0xa435091fU, 0xabcd6fdeU);
            }
            else
            {
                HW_SCE_p_func101(0xf63ad8b6U, 0x8913dfc9U, 0xf3fb0fbfU, 0x321f5255U);
            }

            WR1_PROG(REG_1404H, 0x19800000U);
            WR1_PROG(REG_1444H, 0x000003a2U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x10000000U));
            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c000b1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x0386344aU, 0xe14bb6e9U, 0xc054a583U, 0x2394fab4U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0xf71c73beU, 0x1ffdbf36U, 0x3b6cbb98U, 0x2827e7c2U);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0xb4951b18U, 0x5d5d9d6bU, 0x1d8e5bbaU, 0x3c7a0197U);
            }
        }
        else
        {
            HW_SCE_p_func101(0x5bdd1443U, 0x87804291U, 0x79b67ebfU, 0x95f9f0dfU);
        }

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x000000c0U);
        WR1_PROG(REG_1600H, 0x0000094aU);

        for (iLoop = 0U; iLoop < 95U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x01003906U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1608H, 0x81010100U);

            WR1_PROG(REG_1404H, 0x15700000U);
            WR1_PROG(REG_1400H, 0x00c000bdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c90005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000630U);

            WR1_PROG(REG_1004H, 0x18180010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x18180004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19800000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c000bdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x2ef8f0eeU, 0xebc8a381U, 0x0109e0b0U, 0xa70975d6U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x0000d140U);

                HW_SCE_p_func101(0x1f6a3624U, 0xc5a0b734U, 0x2b7754feU, 0x82fbc6d4U);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x096466e1U, 0x87f4676cU, 0x6f582294U, 0xc3b8ddadU);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x38008940U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x160dbb0aU, 0x67268c1eU, 0x2286ef40U, 0x22a615f9U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x6e807013U, 0x5fc919b9U, 0x87b4de4eU, 0x73e7eea2U);
            continue;
        }

        WR1_PROG(REG_1404H, 0x18780000U);
        WR1_PROG(REG_1400H, 0x00c000c1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000938U);
        WR1_PROG(REG_1020H, 0x00000428U);

        WR1_PROG(REG_1004H, 0x18180009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000428U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000220U);

        WR1_PROG(REG_1004H, 0x1818000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x15700000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00010001U));
        WR1_PROG(REG_1400H, 0x00c000bdU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000630U);

        WR1_PROG(REG_1004H, 0x18180010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_101CH, 0x00000630U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x18180004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x19800000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c000bdU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000838U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000630U);

        WR1_PROG(REG_1004H, 0x1818000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x432e513cU, 0xf9624104U, 0x7494c3b9U, 0xdb09bdc0U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x7a2c9f4bU, 0xd3cd6105U, 0xc12b0814U, 0x4302ac9fU);
        }
        else
        {
            HW_SCE_p_func100(0xe3ca775bU, 0xb7aa7b7bU, 0xd47809eeU, 0x3cc35e6eU);
            WR1_PROG(REG_1404H, 0x17780000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c000bdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000428U);

            WR1_PROG(REG_1004H, 0x18180010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000428U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x18180000U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x701cc725U, 0x23873babU, 0xf986b9c0U, 0x1b6eae4bU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0x14594116U, 0x9d223bcbU, 0xe403e971U, 0xdd74b283U);
                continue;
            }

            HW_SCE_p_func100(0xb54722d5U, 0xd3996cfbU, 0xc77aba9fU, 0x53e57137U);

            WR1_PROG(REG_1600H, 0x0000b560U);
            WR1_PROG(REG_1600H, 0x00000002U);

            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x80b0000aU);
            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x034300c1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000929U);
            WR1_PROG(REG_1600H, 0x00000908U);
            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x000000bcU);

            for (iLoop = 0U; iLoop < 48U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x000038e6U);
                WR1_PROG(REG_1600H, 0x0000a8c0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    WR1_PROG(REG_1600H, 0x38008900U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x11816907U);

                    WR1_PROG(REG_1600H, 0x38008900U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x10002d20U);

                    WR1_PROG(REG_1600H, 0x000168e7U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x81010120U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);
            WR1_PROG(REG_1600H, 0x000037e9U);

            WR1_PROG(REG_1404H, 0x15700000U);
            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x81b0000aU);
            WR1_PROG(REG_1400H, 0x00c900c1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1014H, 0x00000630U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x1818000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000938U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x18180009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x000033e0U);

                HW_SCE_p_func101(0xd6936884U, 0xfe7a8812U, 0x048f23b6U, 0x00635841U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00007c1fU);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0xd457ac08U, 0x17ed3b27U, 0x2b5a36cbU, 0xe103af52U);
            WR1_PROG(REG_1600H, 0x00000a52U);

            WR1_PROG(REG_1608H, 0x81010160U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x00000884U);
                WR1_PROG(REG_1600H, 0x0000b4a0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1600H, 0x0000b4c0U);
                WR1_PROG(REG_1600H, 0x00000030U);
                WR1_PROG(REG_1600H, 0x000008e7U);

                WR1_PROG(REG_1404H, 0x11600000U);
                for (jLoop = 0U; jLoop < 48U; )
                {
                    WR1_PROG(REG_1600H, 0x34202886U);
                    WR1_PROG(REG_1600H, 0x2000d0e0U);
                    WR1_PROG(REG_1600H, 0x00007c07U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func100(0x65c915e0U, 0xd0432503U, 0x0218e5e9U, 0x51c3f94bU);
                    HW_SCE_p_func103();
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                    WR1_PROG(REG_1400H, 0x00c20011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002485U);

                    HW_SCE_p_func101(0x57276a64U, 0xcbc8d2aeU, 0x3a61f966U, 0x95e81048U);
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000886U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func100(0x403afcf3U, 0xc0d3ee47U, 0x0665f697U, 0xceab9f3cU);
                WR1_PROG(REG_1404H, 0x19800000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000004U));
                WR1_PROG(REG_1400H, 0x00c000bdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1018H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x1818000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000838U);

                WR1_PROG(REG_1004H, 0x18180010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_101CH, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x18180004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x17780000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c000bdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x18180009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000428U);

                WR1_PROG(REG_1004H, 0x18180010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000630U);
                WR1_PROG(REG_101CH, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x18180000U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x19800000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c000bdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x1818000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x1818000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0x5f687a47U, 0xdddc03e6U, 0x2df325dcU, 0x9ade80b8U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 0))
                {
                    WR1_PROG(REG_1600H, 0x00002e40U);

                    HW_SCE_p_func101(0x1847951aU, 0x1e3aec84U, 0xc6b15080U, 0xd093c4a6U);
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000094aU);

                    HW_SCE_p_func100(0x361003faU, 0xbf96c297U, 0x24567341U, 0x20a7d5f0U);
                    WR1_PROG(REG_1608H, 0x81010120U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                    S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);
                    WR1_PROG(REG_1600H, 0x000037e9U);

                    for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
                    {
                        WR1_PROG(REG_1404H, 0x19800000U);
                        WR1_PROG(REG_1608H, 0x81b0000aU);
                        WR1_PROG(REG_1400H, 0x00c900c1U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000838U);
                        WR1_PROG(REG_1018H, 0x00000a40U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x1818000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000a40U);
                        WR1_PROG(REG_1018H, 0x00000838U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x1818000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        HW_SCE_p_func100(0xdff22835U, 0x89b38691U, 0x9b848dd0U, 0x950c0177U);
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 0))
                        {
                            WR1_PROG(REG_1600H, 0x00002e40U);

                            HW_SCE_p_func101(0x04a7386dU, 0xd185a349U, 0x766658d3U, 0x7044c12dU);
                            break;
                        }
                        else
                        {
                            HW_SCE_p_func100(0x3eacd295U, 0x7279b4aaU, 0x219336f0U, 0x16bc4182U);
                            WR1_PROG(REG_1404H, 0x19800000U);
                            WR1_PROG(REG_1444H, 0x000000a2U);
                            WR1_PROG(REG_1A24H, 0x08000104U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                            WR1_PROG(REG_1400H, 0x00c000bdU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x00c20005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x0002000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1014H, 0x00000838U);
                            WR1_PROG(REG_1018H, 0x00000a40U);
                            WR1_PROG(REG_101CH, 0x00000428U);
                            WR1_PROG(REG_1020H, 0x00000220U);

                            WR1_PROG(REG_1004H, 0x18180000U);
                            WR1_PROG(REG_1408H, 0x00020000U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);
                            WR1_PROG(REG_143CH, 0x00000d00U);

                            WR1_PROG(REG_1014H, 0x00000220U);
                            WR1_PROG(REG_1018H, 0x00000938U);
                            WR1_PROG(REG_1020H, 0x00000838U);

                            WR1_PROG(REG_1004H, 0x18180009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            HW_SCE_p_func101(0x4abd8a47U, 0xf407e6bdU, 0xe9be08c6U, 0xaf314761U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008a40U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    HW_SCE_p_func100(0xfe17b17bU, 0xf459ca06U, 0x93b16597U, 0x473aa144U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func101(0xb9aa60ceU, 0x8d2ea23aU, 0x3914d333U, 0x8d838c72U);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0xc0521c17U, 0x516352dbU, 0xdcddc1bcU, 0x23a2a263U);
                    }
                }
            }

            WR1_PROG(REG_1600H, 0x38000a4bU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x5be0bce2U, 0xbad2aef9U, 0xf03b7b80U, 0x3758585bU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002e20U);

                WR1_PROG(REG_1600H, 0x38008a20U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0x1750ccb5U, 0x2c5fa409U, 0xbf5bf624U, 0x66c8efd6U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func101(0x064e334eU, 0xaaeb7b5eU, 0x76352aa6U, 0xd26ea92fU);
                    break;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000428U);
                    WR1_PROG(REG_1018H, 0x00000938U);
                    WR1_PROG(REG_1020H, 0x00000320U);

                    WR1_PROG(REG_1004H, 0x18180009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    HW_SCE_p_func101(0x98bbc21aU, 0xc4070a06U, 0xe0daaa9eU, 0xba424312U);
                }
            }
            else
            {
                HW_SCE_p_func101(0x0ea2ff57U, 0x075aa68fU, 0x01159489U, 0x50c26a7dU);
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008a20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0xe6d5ef21U, 0x8c201741U, 0x1ebcf4bcU, 0xb0bd4e6eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x54659092U, 0xe3995ea3U, 0xba310643U, 0x53394a93U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x19800000U);
    WR1_PROG(REG_1400H, 0x00c000c1U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000838U);

    WR1_PROG(REG_1004H, 0x18180009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000778U);

    WR1_PROG(REG_1004H, 0x18180009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    HW_SCE_p_func100(0xdede0dd9U, 0x04718667U, 0x81394218U, 0x6d0d3c43U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xf8e5805cU, 0x8617cebeU, 0xc3c27da8U, 0x95f27e62U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c2000c4U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xc9690989U));

    OFS_ADR = 516;

    WR1_PROG(REG_1404H, 0x16b80000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000060U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xf60bcc85U, 0x410fa467U, 0xc7dfe41dU, 0x431bcf49U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19800000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000bdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x1818000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x1818000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000003aU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x142278e2U, 0x5f5062beU, 0x79d576aeU, 0xd1b4a3a0U);
    HW_SCE_p_func313();

    WR1_PROG(REG_1404H, 0x14a00000U);
    WR1_PROG(REG_1400H, 0x00c000d1U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xc9690989U));

    OFS_ADR = 516;

    WR1_PROG(REG_1404H, 0x16b80000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000060U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xc194afa7U, 0xdf39583fU, 0x86850b1eU, 0x5e346bbeU);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000778U);
    WR1_PROG(REG_1018H, 0x00000838U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x18180007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x2f315bb8U, 0x0bcacf43U, 0x8f524c96U, 0x0e673be8U);
    HW_SCE_p_func315();

    WR1_PROG(REG_1404H, 0x18c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0017dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x3030000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a40U);
    WR1_PROG(REG_1018H, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x3030000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0xb8d7dc46U, 0x95c9542bU, 0xc84bc714U, 0xa69ac2e6U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x8f72c02dU, 0x07ed828bU, 0x6bcf52c0U, 0x4ce11d67U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xc9690989U));

    OFS_ADR = 516;

    WR1_PROG(REG_1404H, 0x12a80000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000060U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x6f3d13f3U, 0xa78c4b88U, 0x0c7c5439U, 0xeea4c661U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000368U);
    WR1_PROG(REG_1018H, 0x00000428U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x18180007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xc9690989U));

    OFS_ADR = 516;

    WR1_PROG(REG_1404H, 0x14b00000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000060U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xb2ead204U, 0x96520249U, 0x2acbdcc8U, 0x9a4646d9U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19800000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000bdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x1818000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000368U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000160U);

    WR1_PROG(REG_1004H, 0x1818000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000220U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x18180007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000630U);

    WR1_PROG(REG_1004H, 0x30300010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000838U);
    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x30300002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x30300003U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000220U);
    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x30300002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x14b00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00010001U));
    WR1_PROG(REG_1400H, 0x00c0017dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x321158f5U, 0x35a4465eU, 0xc7b39a88U, 0xa8683e8dU);
    HW_SCE_p_func315();

    WR1_PROG(REG_1404H, 0x18c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0017dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x3030000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a40U);
    WR1_PROG(REG_1018H, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x3030000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x5e4aaf31U, 0x4f1b2eedU, 0x1c53034dU, 0xe15005e0U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x323cd82bU, 0xc77365f7U, 0xf92100a4U, 0x4db9bc0bU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x18c00000U);
    WR1_PROG(REG_1400H, 0x00c00181U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000838U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x30300009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xc9690989U));

    OFS_ADR = 516;

    WR1_PROG(REG_1404H, 0x14b00000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000060U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003a0fU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x677a4591U, 0x070518e6U, 0xa979e4faU, 0xfd8371a4U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x00010001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800103e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyMode[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x8bd78f28U, 0x36a10d47U, 0x36263639U, 0xd76f094eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func100(0x1fb68656U, 0xbf70e12bU, 0xf884a313U, 0x4865c711U);
        HW_SCE_p_func103();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1608H, 0x80010000U);
        WR1_PROG(REG_1400H, 0x03420005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x000034e0U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00003a01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x81c04ef7U, 0x6262d405U, 0xb251db6bU, 0xd68e6544U);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x0000000fU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00003a01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x53540d18U, 0xecbfd3e6U, 0x633b7725U, 0x60335047U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x14b00000U);
        for (iLoop = 0U; iLoop < 96U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x99dc39e3U, 0xf3179ec7U, 0x28c78168U, 0x1721ceadU);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[1 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0xe672a687U, 0x629c467dU, 0xf9713afcU, 0xa31165a3U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x12a80000U);
        for (iLoop = 0U; iLoop < 96U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x97035500U, 0xbca1da28U, 0x2b066c4cU, 0x243b7fb3U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[97 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x2c6bf540U, 0x68f46814U, 0x4a2f19d7U, 0x476fd51cU);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x9dcef00aU, 0x042a9c29U, 0xfcf2c70dU, 0x548a9a18U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x09108105U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[193]);

        HW_SCE_p_func100(0x11152a31U, 0xb615d209U, 0x101dd0f6U, 0xa79f537bU);
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

        HW_SCE_p_func101(0x4e898ab0U, 0x015c361eU, 0xf7b7a915U, 0xf17e9259U);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x14b00000U);
        for (iLoop = 0U; iLoop < 96U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x51a34704U, 0x87ab6e65U, 0xdced5a46U, 0xafaec493U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKey[iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x160b0497U, 0x353b1f4fU, 0x2485eccaU, 0x69ae8ba7U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x12a80000U);
        for (iLoop = 0U; iLoop < 96U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x4e759b95U, 0x3da70a3bU, 0xc3dfad91U, 0x09974773U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKey[96 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x4a0d7c03U, 0x350f34a7U, 0x35b5a76bU, 0xcc4d6e44U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xe9700a11U, 0x47241dbfU, 0x9d8bdfafU, 0xb28b29e5U);
    }

    WR1_PROG(REG_1600H, 0x00000884U);
    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x14b00000U);
    for (iLoop = 0U; iLoop < 96U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x356232dbU, 0xa57faa33U, 0xe26c3ed0U, 0xd9918cefU);
        WR1_PROG(REG_1A24H, 0x08000105U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKey[iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        HW_SCE_p_func101(0x2153239dU, 0x7d7c2741U, 0x1f20ac85U, 0xf41094dbU);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0x0d0f8b28U, 0x38852cf9U, 0x4cd2dedaU, 0x676ef0bcU);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WR1_PROG(REG_1608H, 0x81010280U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKey[96]);

    HW_SCE_p_func102(0x90c0197cU, 0xba93cb58U, 0x69820030U, 0xce6b8511U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
