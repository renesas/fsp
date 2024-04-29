/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_RSA4096_KeyPairGenerateSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_1B00H, 0x003b0001U);
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

        HW_SCE_p_func100(0xaf560efdU, 0x332f0a04U, 0x17a0fa87U, 0xb6c55385U);
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
        WR1_PROG(REG_1404H, 0x11200000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000038U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        for (iLoop = 0U; iLoop < 56U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0xb586b1ceU, 0x4bca0058U, 0xc6f0e679U, 0x056abaf5U);
            HW_SCE_p_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x9b45d791U, 0xd12d65aeU, 0xa3f8f58fU, 0xc38159d3U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x6c78b524U, 0x631a010eU, 0x35355acbU, 0x333b4050U);
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

        WR1_PROG(REG_1444H, 0x00003fb0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_940H, 0xB51EB851U);
        WR1_PROG(REG_944H, 0xEB851EB8U);
        WR1_PROG(REG_948H, 0x51EB851EU);
        WR1_PROG(REG_94CH, 0xB851EB85U);
        WR1_PROG(REG_950H, 0x1EB851EBU);
        WR1_PROG(REG_954H, 0x851EB851U);
        WR1_PROG(REG_958H, 0xEB851EB8U);
        WR1_PROG(REG_95CH, 0x51EB851EU);
        WR1_PROG(REG_960H, 0xB851EB85U);
        WR1_PROG(REG_964H, 0x1EB851EBU);
        WR1_PROG(REG_968H, 0x851EB851U);
        WR1_PROG(REG_96CH, 0xEB851EB8U);
        WR1_PROG(REG_970H, 0x51EB851EU);
        WR1_PROG(REG_974H, 0xB851EB85U);
        WR1_PROG(REG_978H, 0x1EB851EBU);
        WR1_PROG(REG_97CH, 0x851EB851U);
        WR1_PROG(REG_980H, 0xEB851EB8U);
        WR1_PROG(REG_984H, 0x51EB851EU);
        WR1_PROG(REG_988H, 0xB851EB85U);
        WR1_PROG(REG_98CH, 0x1EB851EBU);
        WR1_PROG(REG_990H, 0x851EB851U);
        WR1_PROG(REG_994H, 0xEB851EB8U);
        WR1_PROG(REG_998H, 0x51EB851EU);
        WR1_PROG(REG_99CH, 0xB851EB85U);
        WR1_PROG(REG_9A0H, 0x1EB851EBU);
        WR1_PROG(REG_9A4H, 0x851EB851U);
        WR1_PROG(REG_9A8H, 0xEB851EB8U);
        WR1_PROG(REG_9ACH, 0x51EB851EU);
        WR1_PROG(REG_9B0H, 0xB851EB85U);
        WR1_PROG(REG_9B4H, 0x1EB851EBU);
        WR1_PROG(REG_9B8H, 0x851EB851U);
        WR1_PROG(REG_9BCH, 0xEB851EB8U);
        WR1_PROG(REG_9C0H, 0x51EB851EU);
        WR1_PROG(REG_9C4H, 0xB851EB85U);
        WR1_PROG(REG_9C8H, 0x1EB851EBU);
        WR1_PROG(REG_9CCH, 0x851EB851U);
        WR1_PROG(REG_9D0H, 0xEB851EB8U);
        WR1_PROG(REG_9D4H, 0x51EB851EU);
        WR1_PROG(REG_9D8H, 0xB851EB85U);
        WR1_PROG(REG_9DCH, 0x1EB851EBU);
        WR1_PROG(REG_9E0H, 0x851EB851U);
        WR1_PROG(REG_9E4H, 0xEB851EB8U);
        WR1_PROG(REG_9E8H, 0x51EB851EU);
        WR1_PROG(REG_9ECH, 0xB851EB85U);
        WR1_PROG(REG_9F0H, 0x1EB851EBU);
        WR1_PROG(REG_9F4H, 0x851EB851U);
        WR1_PROG(REG_9F8H, 0xEB851EB8U);
        WR1_PROG(REG_9FCH, 0x51EB851EU);
        WR1_PROG(REG_A00H, 0xB851EB85U);
        WR1_PROG(REG_A04H, 0x1EB851EBU);
        WR1_PROG(REG_A08H, 0x851EB851U);
        WR1_PROG(REG_A0CH, 0xEB851EB8U);
        WR1_PROG(REG_A10H, 0x51EB851EU);
        WR1_PROG(REG_A14H, 0xB851EB85U);
        WR1_PROG(REG_A18H, 0x1EB851EBU);
        WR1_PROG(REG_A1CH, 0x851EB851U);
        WR1_PROG(REG_A20H, 0xEB851EB8U);
        WR1_PROG(REG_A24H, 0x51EB851EU);
        WR1_PROG(REG_A28H, 0xB851EB85U);
        WR1_PROG(REG_A2CH, 0x1EB851EBU);
        WR1_PROG(REG_A30H, 0x851EB851U);
        WR1_PROG(REG_A34H, 0xEB851EB8U);
        WR1_PROG(REG_A38H, 0x51EB851EU);
        WR1_PROG(REG_A3CH, 0xB851EB85U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x105b3270U, 0x449719f8U, 0x0c9ca298U, 0x93b875c3U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x63148219U, 0x40d4619dU, 0x9a750e4bU, 0x0493b566U);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0x681ccd72U, 0x3f932a31U, 0xaab5ecaaU, 0x4173dd3dU);
        }

        WR1_PROG(REG_1600H, 0x38008a20U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x76c16ee5U, 0x8c571896U, 0x476c0139U, 0xe3f2dd63U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000320U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x7a07d1cfU, 0xf3a735cbU, 0xf5985636U, 0x791e7523U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000320U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0x913e8cceU, 0xc2a7f474U, 0xfb956771U, 0xdfd6482bU);
            }
            else
            {
                HW_SCE_p_func101(0xa0823df3U, 0x826adae3U, 0x10685514U, 0xef241914U);
            }

            WR1_PROG(REG_1404H, 0x19400000U);
            WR1_PROG(REG_1444H, 0x000003a2U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x10000000U));
            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x6193d67cU, 0xdec83209U, 0x12b2a8ddU, 0x78fdb255U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0x50982015U, 0x956557e6U, 0x7d1d3bd3U, 0x923ce03aU);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0x450111d2U, 0xf519606aU, 0x7c58757bU, 0xe0bce762U);
            }
        }
        else
        {
            HW_SCE_p_func101(0xcfa9f03aU, 0x711272edU, 0x8dc3b71aU, 0xc0d7f5fbU);
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

            WR1_PROG(REG_1404H, 0x15300000U);
            WR1_PROG(REG_1400H, 0x00c000fdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c90005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000630U);

            WR1_PROG(REG_1004H, 0x20200010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x20200004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19400000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c000fdU);
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

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0xe6e69d1eU, 0x847d537eU, 0x0e689d36U, 0xe6e9f74dU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x0000d140U);

                HW_SCE_p_func101(0x6b19cbd1U, 0xe2a3ed1aU, 0x4e5198adU, 0x5a427544U);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x43d5271eU, 0x5285be01U, 0x44f46c4aU, 0xb3511ff9U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x38008940U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x28a6deb8U, 0x9dd17232U, 0x26703995U, 0xf493b83fU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0xf5cba0efU, 0x5415b64eU, 0x95afb99dU, 0xe5239adcU);
            continue;
        }

        WR1_PROG(REG_1404H, 0x18380000U);
        WR1_PROG(REG_1400H, 0x00c00101U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000938U);
        WR1_PROG(REG_1020H, 0x00000428U);

        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000428U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000220U);

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x15300000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00010001U));
        WR1_PROG(REG_1400H, 0x00c000fdU);
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

        WR1_PROG(REG_1004H, 0x20200010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_101CH, 0x00000630U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x20200004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x19400000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c000fdU);
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

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0xbead3acfU, 0xc4202389U, 0xe68426b3U, 0x94b1c604U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x754f24eeU, 0x55b593adU, 0x6696d5b5U, 0x255bfd0aU);
        }
        else
        {
            HW_SCE_p_func100(0x4f718bf8U, 0xe6122e2dU, 0xebe48e99U, 0x8f53c02aU);
            WR1_PROG(REG_1404H, 0x17380000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c000fdU);
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

            WR1_PROG(REG_1004H, 0x20200010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000428U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x20200000U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x78d46690U, 0x4b758e60U, 0x45b33050U, 0x41d88e23U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0x50e24006U, 0x54ec3483U, 0x95d2a04dU, 0x01372a39U);
                continue;
            }

            HW_SCE_p_func100(0x06c3d9aeU, 0x2774d2c4U, 0xf4753614U, 0x78875e0dU);

            WR1_PROG(REG_1600H, 0x0000b560U);
            WR1_PROG(REG_1600H, 0x00000001U);

            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x80c0000aU);
            WR1_PROG(REG_1404H, 0x11200000U);
            WR1_PROG(REG_1400H, 0x03430101U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000929U);
            WR1_PROG(REG_1600H, 0x00000908U);
            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x000000fcU);

            for (iLoop = 0U; iLoop < 64U; iLoop++)
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

            WR1_PROG(REG_1404H, 0x15300000U);
            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x81c0000aU);
            WR1_PROG(REG_1400H, 0x00c90101U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1014H, 0x00000630U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x2020000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000938U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x20200009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x000033e0U);

                HW_SCE_p_func101(0xae91909eU, 0x9085c030U, 0x20383220U, 0x03336ed9U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00007c1fU);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x830a554eU, 0x1182283eU, 0xa11ad9b6U, 0xef645421U);
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
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1600H, 0x000008e7U);

                WR1_PROG(REG_1404H, 0x11200000U);
                for (jLoop = 0U; jLoop < 64U; )
                {
                    WR1_PROG(REG_1600H, 0x34202886U);
                    WR1_PROG(REG_1600H, 0x2000d0e0U);
                    WR1_PROG(REG_1600H, 0x00007c07U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func100(0x1d9c8743U, 0x3bb506b6U, 0x4f9b9be6U, 0xfe67a37cU);
                    HW_SCE_p_func103();
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                    WR1_PROG(REG_1400H, 0x00c20011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002485U);

                    HW_SCE_p_func101(0x39d481d3U, 0xd90b98baU, 0x4c7cc4f1U, 0x337c3b58U);
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000886U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func100(0x13f1cc87U, 0x0a953e8eU, 0x8e56d4e3U, 0x4738bd86U);
                WR1_PROG(REG_1404H, 0x19400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000004U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
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

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000838U);

                WR1_PROG(REG_1004H, 0x20200010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_101CH, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x20200004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x17380000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
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

                WR1_PROG(REG_1004H, 0x20200009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000428U);

                WR1_PROG(REG_1004H, 0x20200010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000630U);
                WR1_PROG(REG_101CH, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x20200000U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x19400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
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

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0xeb6d84a0U, 0xebcce3b5U, 0x11d7fe50U, 0x67dde3dbU);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 0))
                {
                    WR1_PROG(REG_1600H, 0x00002e40U);

                    HW_SCE_p_func101(0xd55cebf7U, 0xcd719d25U, 0xaf442e1cU, 0xe28d9934U);
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000094aU);

                    HW_SCE_p_func100(0xbbedf54fU, 0xe18deb3bU, 0x1c6dc573U, 0xf831d8a6U);
                    WR1_PROG(REG_1608H, 0x81010120U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                    S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);
                    WR1_PROG(REG_1600H, 0x000037e9U);

                    for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
                    {
                        WR1_PROG(REG_1404H, 0x19400000U);
                        WR1_PROG(REG_1608H, 0x81c0000aU);
                        WR1_PROG(REG_1400H, 0x00c90101U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000838U);
                        WR1_PROG(REG_1018H, 0x00000a40U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x2020000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000a40U);
                        WR1_PROG(REG_1018H, 0x00000838U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x2020000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        HW_SCE_p_func100(0xb2570021U, 0x2ffc5990U, 0x33878243U, 0x58429549U);
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 0))
                        {
                            WR1_PROG(REG_1600H, 0x00002e40U);

                            HW_SCE_p_func101(0x95b67955U, 0x97dce60aU, 0xcc92e0abU, 0xacd05160U);
                            break;
                        }
                        else
                        {
                            HW_SCE_p_func100(0x383f726fU, 0x1518c6a4U, 0x102c8882U, 0xb0114fa7U);
                            WR1_PROG(REG_1404H, 0x19400000U);
                            WR1_PROG(REG_1444H, 0x000000a2U);
                            WR1_PROG(REG_1A24H, 0x08000104U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                            WR1_PROG(REG_1400H, 0x00c000fdU);
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

                            WR1_PROG(REG_1004H, 0x20200000U);
                            WR1_PROG(REG_1408H, 0x00020000U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);
                            WR1_PROG(REG_143CH, 0x00000d00U);

                            WR1_PROG(REG_1014H, 0x00000220U);
                            WR1_PROG(REG_1018H, 0x00000938U);
                            WR1_PROG(REG_1020H, 0x00000838U);

                            WR1_PROG(REG_1004H, 0x20200009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            HW_SCE_p_func101(0xa64fe30aU, 0xd8cd50aaU, 0x9fbe2bc9U, 0x195f6289U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008a40U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    HW_SCE_p_func100(0x1e713dfbU, 0x2c20f086U, 0x99dc4479U, 0x48fed1c7U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func101(0xf3678531U, 0x3822f9faU, 0x8e939a80U, 0xf75f0fc2U);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0x700e5650U, 0xe8c3be2dU, 0x29aa3424U, 0x6f3f7a0dU);
                    }
                }
            }

            WR1_PROG(REG_1600H, 0x38000a4bU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xcd4c9909U, 0x8287e7a2U, 0x39958fb4U, 0x3b4adfdfU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002e20U);

                WR1_PROG(REG_1600H, 0x38008a20U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0xd561eb1fU, 0x1da0a293U, 0x92f10031U, 0xced40170U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func101(0xca692f96U, 0xf82f044dU, 0x7d0ec85cU, 0xdf33fa15U);
                    break;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000428U);
                    WR1_PROG(REG_1018H, 0x00000938U);
                    WR1_PROG(REG_1020H, 0x00000320U);

                    WR1_PROG(REG_1004H, 0x20200009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    HW_SCE_p_func101(0xdff1080aU, 0xa6169864U, 0x4b053396U, 0x17d42d2dU);
                }
            }
            else
            {
                HW_SCE_p_func101(0xfd5bbfbcU, 0xf7eb8efbU, 0x6664ad22U, 0x6224941bU);
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008a20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0xe027f15eU, 0x78c9f88eU, 0x5d47071dU, 0x98b859b6U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xacda221fU, 0xac8c0a8eU, 0x9492a275U, 0xd1af4b2bU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1400H, 0x00c00101U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000838U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000738U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    HW_SCE_p_func100(0xcc5babceU, 0x3791b80aU, 0x743c1d95U, 0xb167cdbeU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x2167e419U, 0xc839c153U, 0x270bdb87U, 0xb560b053U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c2000c4U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x16380000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xd38f985dU, 0x4c8248dcU, 0x6306b50dU, 0xb07bf37fU);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000fdU);
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

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000003bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xa60d0a2eU, 0x0aae3872U, 0xf7b835edU, 0x069e4d9bU);
    HW_SCE_p_func054();

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1400H, 0x00c00101U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000660U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x00000dc0U);

    WR1_PROG(REG_1404H, 0x14500000U);
    WR1_PROG(REG_1400H, 0x00c00111U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x16780000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x78a41cd0U, 0x3e3cae69U, 0x61c3a975U, 0x02c95866U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000778U);
    WR1_PROG(REG_1018H, 0x00000878U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x191d1c79U, 0x3987522bU, 0xecf2a21fU, 0x421e69fcU);
    HW_SCE_p_func321();

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000660U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a90U);
    WR1_PROG(REG_1018H, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x2ca71c1dU, 0x6c2efcf1U, 0xa69af818U, 0x1cddf3cfU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x9a8c6fc6U, 0x899d66dcU, 0xf1dd0e0fU, 0x5cb01d8fU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x12480000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xe49ead2eU, 0xb5a6373bU, 0x4d3ad982U, 0xbe931c7dU);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000348U);
    WR1_PROG(REG_1018H, 0x00000448U);
    WR1_PROG(REG_1020H, 0x00000660U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x14600000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x38f04c50U, 0x7c795daeU, 0xda6c2b16U, 0xac480662U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000348U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000130U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000130U);
    WR1_PROG(REG_1018H, 0x00000230U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000660U);

    WR1_PROG(REG_1004H, 0x40400010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000878U);
    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x40400002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x40400003U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000230U);
    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x40400002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x14600000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00010001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
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
    WR1_PROG(REG_1420H, change_endian_long(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xfed4521fU, 0xe377398eU, 0x1675556bU, 0x761c1fb8U);
    HW_SCE_p_func321();

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000660U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a90U);
    WR1_PROG(REG_1018H, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x6fa8c338U, 0x785e919bU, 0x8b9223b4U, 0x1545c1c2U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x46fad1f8U, 0x4ed6c95eU, 0x67db0ae5U, 0x63d34db7U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1400H, 0x00c00201U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000878U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x40400009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x14600000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003b03U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x2e19102bU, 0x7ea27c48U, 0x0bc645dfU, 0xbff6b26bU);
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

    HW_SCE_p_func100(0xc7fb364aU, 0xeca6946eU, 0xb4991bd1U, 0xcee9d651U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func100(0x88c81144U, 0x4331cb49U, 0xb94e0912U, 0x0e469f22U);
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
        WR1_PROG(REG_1420H, change_endian_long(0x00003b01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x21144eb8U, 0x105a30c2U, 0xc3759ff3U, 0xe65710bdU);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000011U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00003b01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xb797fbcfU, 0xc9bdb806U, 0xb9fe08d3U, 0x37a113eeU);
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
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x14600000U);
        for (iLoop = 0U; iLoop < 128U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x4bc70999U, 0x898c66e3U, 0x5e961005U, 0xeee53d08U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[1 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0xdffe7e58U, 0x5cc70942U, 0xd455e570U, 0xf5958b28U);
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
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x12480000U);
        for (iLoop = 0U; iLoop < 128U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x858d85c0U, 0x1fb2d150U, 0xd6fe4066U, 0xb79069f8U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[129 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x38af3df9U, 0xec6a589eU, 0x0c32d5faU, 0x726394a3U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x461822f9U, 0x25a7aaa9U, 0xd06a6665U, 0x4a1de0c7U);
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
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[257]);

        HW_SCE_p_func100(0x1cd40ebaU, 0x1393dc87U, 0xc3531c26U, 0x8a6d5621U);
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

        HW_SCE_p_func101(0x830304eaU, 0x9b022b9eU, 0x98f9eb8aU, 0x5c906bacU);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x14600000U);
        for (iLoop = 0U; iLoop < 128U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x5ac38975U, 0x5a16dd36U, 0xe4371adfU, 0x30c813ecU);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKey[iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x8e58f209U, 0xe45c37feU, 0xea7ad0f6U, 0x9d0e77dcU);
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
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1404H, 0x12480000U);
        for (iLoop = 0U; iLoop < 128U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x5724a255U, 0xaf49fe40U, 0x7030a5dbU, 0xc4c09e99U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WR1_PROG(REG_1400H, 0x00830011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKey[128 + iLoop]);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x5d8f2b0bU, 0x3f5baf86U, 0x1e778476U, 0xd49fc844U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xde531df6U, 0xe8ca5396U, 0x89cea217U, 0x52bf1cb0U);
    }

    WR1_PROG(REG_1600H, 0x00000884U);
    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x14600000U);
    for (iLoop = 0U; iLoop < 128U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x456ad3e4U, 0xb621d9bdU, 0x9a66b2b4U, 0xd121db66U);
        WR1_PROG(REG_1A24H, 0x08000105U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKey[iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        HW_SCE_p_func101(0xcc077bfeU, 0x33946a4bU, 0x02fa653cU, 0xa008e499U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0xe50d724eU, 0xb8cb297cU, 0xb96c144fU, 0xdd188294U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WR1_PROG(REG_1608H, 0x81010280U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKey[128]);

    HW_SCE_p_func102(0x4983c209U, 0xc7dc5621U, 0x36aefbbcU, 0x8b5e8267U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
