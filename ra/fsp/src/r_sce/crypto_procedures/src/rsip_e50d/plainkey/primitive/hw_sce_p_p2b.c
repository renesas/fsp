/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_RSA2048_KeyPairGenerateSub (const uint32_t MAX_CNT,
                                             uint32_t       OutData_PubKeyIndex[],
                                             uint32_t       OutData_PrivKeyIndex[])
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

    WR1_PROG(REG_1B00H, 0x002b0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x00000e50U);

    WR1_PROG(REG_1600H, 0x00000a31U);
    for (kLoop = 0U; kLoop < MAX_CNT; kLoop++)
    {
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1444H, 0x00002fa2U);
        WR1_PROG(REG_1A2CH, 0x00000b00U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x00030005U), change_endian_long(0x0007000bU), change_endian_long(0x000d0011U), change_endian_long(0x00130017U));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x001d001fU), change_endian_long(0x00250029U), change_endian_long(0x002b002fU), change_endian_long(0x003b003dU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x00430047U), change_endian_long(0x0049004fU), change_endian_long(0x00530059U), change_endian_long(0x00610065U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x0067006bU), change_endian_long(0x006d0071U), change_endian_long(0x007f0083U), change_endian_long(0x0089008bU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x00950097U), change_endian_long(0x009d00a3U), change_endian_long(0x00a700adU), change_endian_long(0x00b300b5U));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x00bf00c1U), change_endian_long(0x00c500c7U), change_endian_long(0x00d300dfU), change_endian_long(0x00e300e5U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x00e900efU), change_endian_long(0x00f100fbU), change_endian_long(0x01010107U), change_endian_long(0x010d010fU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x01150119U), change_endian_long(0x011b0125U), change_endian_long(0x01330137U), change_endian_long(0x0139013dU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x014b0151U), change_endian_long(0x015b015dU), change_endian_long(0x01610167U), change_endian_long(0x016f0175U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x017b017fU), change_endian_long(0x0185018dU), change_endian_long(0x01910199U), change_endian_long(0x01a301a5U));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x01af01b1U), change_endian_long(0x01b701bbU), change_endian_long(0x01c101c9U), change_endian_long(0x01cd01cfU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x01d301dfU), change_endian_long(0x01e701ebU), change_endian_long(0x01f301f7U), change_endian_long(0x01fd0000U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x80b00006U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x034300c1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x10180000U);
        WR1_PROG(REG_1400H, 0x00c00209U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x1ae60b97U, 0xa6c8ed21U, 0x728f647fU, 0xc43baca2U);
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
        WR1_PROG(REG_1404H, 0x11a00000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000018U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        for (iLoop = 0U; iLoop < 24U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x752bd061U, 0xca677056U, 0xca3154b0U, 0xfd048b4dU);
            HW_SCE_p_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00002485U);

            HW_SCE_p_func101(0x574d5788U, 0x1193b66aU, 0x933836eaU, 0x902ec7acU);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x7ee3201dU, 0xaf6f99e2U, 0x64c366e1U, 0x4fa43583U);
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

        WR1_PROG(REG_1404H, 0x19c00000U);
        WR1_PROG(REG_1444H, 0x00001fa2U);
        WR1_PROG(REG_1A2CH, 0x00000700U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0xB51EB851U), change_endian_long(0xEB851EB8U), change_endian_long(0x51EB851EU), change_endian_long(0xB851EB85U));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x1EB851EBU), change_endian_long(0x851EB851U), change_endian_long(0xEB851EB8U), change_endian_long(0x51EB851EU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0xB851EB85U), change_endian_long(0x1EB851EBU), change_endian_long(0x851EB851U), change_endian_long(0xEB851EB8U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x51EB851EU), change_endian_long(0xB851EB85U), change_endian_long(0x1EB851EBU), change_endian_long(0x851EB851U));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0xEB851EB8U), change_endian_long(0x51EB851EU), change_endian_long(0xB851EB85U), change_endian_long(0x1EB851EBU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x851EB851U), change_endian_long(0xEB851EB8U), change_endian_long(0x51EB851EU), change_endian_long(0xB851EB85U));
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x1EB851EBU), change_endian_long(0x851EB851U), change_endian_long(0xEB851EB8U), change_endian_long(0x51EB851EU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0xB851EB85U), change_endian_long(0x1EB851EBU), change_endian_long(0x851EB851U), change_endian_long(0xEB851B5CU));
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x1010000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x5079c5a0U, 0xdf6a565cU, 0x8bd32464U, 0x730ad2b7U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0xdb1b3f10U, 0xe98e32fdU, 0x98ea3ae8U, 0x1ba904e6U);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0xc4656062U, 0x33b9851fU, 0xfe32983dU, 0x1ca650b7U);
        }

        WR1_PROG(REG_1600H, 0x38008a20U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x6b997cb5U, 0x906457b9U, 0x4dcca82eU, 0x062e7fcfU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000320U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x1010000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0xe36453e9U, 0x8d2468e2U, 0x00e4190dU, 0x1129aa5eU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000320U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x1010000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0x15f16407U, 0x0bf669f2U, 0xbc408c5eU, 0x5fb7b887U);
            }
            else
            {
                HW_SCE_p_func101(0x55cddbeaU, 0x85d4ff08U, 0xd34df758U, 0x6cecbe73U);
            }

            WR1_PROG(REG_1404H, 0x19c00000U);
            WR1_PROG(REG_1444H, 0x000003a2U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x00000000U), change_endian_long(0x10000000U));
            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c00071U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1010000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x9b13e5f1U, 0x8370afe3U, 0xece8d2acU, 0x54b6db2dU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0x32e4b193U, 0x34912044U, 0xdc6cde01U, 0x9c8b95c4U);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0x6f9498e9U, 0xf29b6940U, 0xc2599a47U, 0x64b803f2U);
            }
        }
        else
        {
            HW_SCE_p_func101(0x63d4643bU, 0x38761a1eU, 0x0a3cd5cdU, 0x28d27a69U);
        }

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x0000094aU);

        for (iLoop = 0U; iLoop < 95U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x01003906U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1608H, 0x81010100U);

            WR1_PROG(REG_1404H, 0x14280000U);
            WR1_PROG(REG_1400H, 0x00c00209U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x15b00000U);
            WR1_PROG(REG_1400H, 0x00c0007dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c90005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000630U);

            WR1_PROG(REG_1004H, 0x10100010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x10100004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19c00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0007dU);
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

            WR1_PROG(REG_1004H, 0x1010000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0xe81789f5U, 0xfb37d489U, 0xee58a599U, 0x3c6763b0U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x0000d140U);

                HW_SCE_p_func101(0xd2e74abdU, 0xab4c0982U, 0xba2ea5efU, 0x0c8309aeU);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x6fd84691U, 0xd310d75dU, 0x82dbad3dU, 0x211059deU);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x38008940U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x4bd03332U, 0x4327e41cU, 0xbea0d3b0U, 0x01f4541dU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x222f87a9U, 0xdfe4906dU, 0xcf35af79U, 0x9085a398U);
            continue;
        }

        WR1_PROG(REG_1404H, 0x18b80000U);
        WR1_PROG(REG_1400H, 0x00c00081U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000938U);
        WR1_PROG(REG_1020H, 0x00000428U);

        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000428U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000220U);

        WR1_PROG(REG_1004H, 0x1010000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x14280000U);
        WR1_PROG(REG_1400H, 0x00c00209U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x15b00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00010001U));
        WR1_PROG(REG_1400H, 0x00c0007dU);
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

        WR1_PROG(REG_1004H, 0x10100010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_101CH, 0x00000630U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x10100004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x19c00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0007dU);
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

        WR1_PROG(REG_1004H, 0x1010000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0xf0977896U, 0x186571f8U, 0x0b6ebb2fU, 0x9d28a562U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x73b303c5U, 0x2b8496c6U, 0x53f264d5U, 0xe27c4552U);
        }
        else
        {
            WR1_PROG(REG_1404H, 0x16300000U);
            WR1_PROG(REG_1400H, 0x00c00209U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func100(0xa0844331U, 0x1d8f3f6fU, 0x833510e5U, 0x51116384U);
            WR1_PROG(REG_1404H, 0x17b80000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c0007dU);
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

            WR1_PROG(REG_1004H, 0x10100010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000428U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x10100000U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1010000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x1010000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x645abd3eU, 0x4cac3949U, 0x10327c08U, 0xc483ac93U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func101(0x6a114a1eU, 0xe434e283U, 0x08a19cafU, 0x0d40a354U);
                continue;
            }

            HW_SCE_p_func100(0x7c564cf8U, 0xa6a8c178U, 0x63bc81f7U, 0x56e820c2U);

            WR1_PROG(REG_1600H, 0x0000b560U);
            WR1_PROG(REG_1600H, 0x00000003U);

            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x80a0000aU);
            WR1_PROG(REG_1404H, 0x11a00000U);
            WR1_PROG(REG_1400H, 0x03430081U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000929U);
            WR1_PROG(REG_1600H, 0x00000908U);
            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x0000007cU);

            for (iLoop = 0U; iLoop < 32U; iLoop++)
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

            WR1_PROG(REG_1404H, 0x15b00000U);
            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x81a0000aU);
            WR1_PROG(REG_1400H, 0x00c90081U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1014H, 0x00000630U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x1010000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000938U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x10100009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x000033e0U);

                HW_SCE_p_func101(0xb555a649U, 0x25ff3c81U, 0x5700b3a2U, 0x83e1bc37U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00007c1fU);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x6df12feaU, 0x23092d8aU, 0xd55b45f8U, 0x3d6a940bU);
            WR1_PROG(REG_1600H, 0x00000a52U);

            WR1_PROG(REG_1608H, 0x81010160U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1404H, 0x10180000U);
                WR1_PROG(REG_1400H, 0x00c00209U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000884U);
                WR1_PROG(REG_1600H, 0x0000b4a0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1600H, 0x0000b4c0U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1600H, 0x000008e7U);

                WR1_PROG(REG_1404H, 0x11a00000U);
                for (jLoop = 0U; jLoop < 32U; )
                {
                    WR1_PROG(REG_1600H, 0x34202886U);
                    WR1_PROG(REG_1600H, 0x2000d0e0U);
                    WR1_PROG(REG_1600H, 0x00007c07U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func100(0x6951e92cU, 0xad293fb5U, 0x2591152bU, 0xe703bb39U);
                    HW_SCE_p_func103();
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                    WR1_PROG(REG_1400H, 0x00c20011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002485U);

                    HW_SCE_p_func101(0x6cc32e3dU, 0x4af6751dU, 0x157c8d08U, 0x6c21bf6eU);
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000886U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func100(0x79c9d5ecU, 0xd711b79aU, 0xb9045de8U, 0xc7429848U);
                WR1_PROG(REG_1404H, 0x19c00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000004U));
                WR1_PROG(REG_1400H, 0x00c0007dU);
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

                WR1_PROG(REG_1004H, 0x1010000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000838U);

                WR1_PROG(REG_1004H, 0x10100010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_101CH, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x10100004U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x17b80000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c0007dU);
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

                WR1_PROG(REG_1004H, 0x10100009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000428U);

                WR1_PROG(REG_1004H, 0x10100010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000630U);
                WR1_PROG(REG_101CH, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x10100000U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x19c00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0007dU);
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

                WR1_PROG(REG_1004H, 0x1010000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x1010000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0xa7183ef6U, 0x509a3127U, 0x8f9791b4U, 0xb2063b43U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 0))
                {
                    WR1_PROG(REG_1600H, 0x00002e40U);

                    HW_SCE_p_func101(0x604257f5U, 0xa596d4e7U, 0x86463a2aU, 0x704acc7eU);
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000094aU);

                    HW_SCE_p_func100(0x1aa0e02eU, 0x93bcc257U, 0xbf618fb3U, 0x959e5a40U);
                    WR1_PROG(REG_1608H, 0x81010120U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                    S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);
                    WR1_PROG(REG_1600H, 0x000037e9U);

                    for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
                    {
                        WR1_PROG(REG_1404H, 0x19c00000U);
                        WR1_PROG(REG_1608H, 0x81a0000aU);
                        WR1_PROG(REG_1400H, 0x00c90081U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000838U);
                        WR1_PROG(REG_1018H, 0x00000a40U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x1010000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000a40U);
                        WR1_PROG(REG_1018H, 0x00000838U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x1010000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        HW_SCE_p_func100(0xcdca73deU, 0xd874a893U, 0x079f897dU, 0x66f74438U);
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 0))
                        {
                            WR1_PROG(REG_1600H, 0x00002e40U);

                            HW_SCE_p_func101(0xae6f91efU, 0xc8f67f47U, 0x8697c3baU, 0x76a9e5f9U);
                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x18380000U);
                            WR1_PROG(REG_1400H, 0x00c00209U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            HW_SCE_p_func100(0x9e3cd50fU, 0x71f64e29U, 0x4a00f5f5U, 0xcdd76cf0U);
                            WR1_PROG(REG_1404H, 0x19c00000U);
                            WR1_PROG(REG_1444H, 0x000000a2U);
                            WR1_PROG(REG_1A24H, 0x08000104U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                            WR1_PROG(REG_1400H, 0x00c0007dU);
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

                            WR1_PROG(REG_1004H, 0x10100000U);
                            WR1_PROG(REG_1408H, 0x00020000U);
                            WR1_PROG(REG_1000H, 0x00010201U);
                            WAIT_STS(REG_1000H, 0, 0);
                            WR1_PROG(REG_143CH, 0x00000d00U);

                            WR1_PROG(REG_1014H, 0x00000220U);
                            WR1_PROG(REG_1018H, 0x00000938U);
                            WR1_PROG(REG_1020H, 0x00000838U);

                            WR1_PROG(REG_1004H, 0x10100009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            HW_SCE_p_func101(0x36b45adeU, 0x305fb6caU, 0x59765e1fU, 0x63d15531U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008a40U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    HW_SCE_p_func100(0xd5330796U, 0x12be73c6U, 0x93144bddU, 0xc8336326U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func101(0x044d327dU, 0x644b51c2U, 0xb31d6c42U, 0x2ad06794U);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0x648590dcU, 0x0a73eae3U, 0x79199bddU, 0x43b1e9b8U);
                    }
                }
            }

            WR1_PROG(REG_1600H, 0x38000a4bU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xa8f83e3eU, 0xf1b1ad09U, 0xd421a09cU, 0xb7ad8381U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002e20U);

                WR1_PROG(REG_1600H, 0x38008a20U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0xdf1b71cdU, 0xc52be53dU, 0x9f6c7101U, 0xb46a8c38U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func101(0xd2e2b9ebU, 0x414778c6U, 0x6b8f816fU, 0x07a4dc7dU);
                    break;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000428U);
                    WR1_PROG(REG_1018H, 0x00000938U);
                    WR1_PROG(REG_1020H, 0x00000320U);

                    WR1_PROG(REG_1004H, 0x10100009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    HW_SCE_p_func101(0xe652f2caU, 0x5be6dd75U, 0x4fb54809U, 0x92757281U);
                }
            }
            else
            {
                HW_SCE_p_func101(0x0878e254U, 0xe5eb2237U, 0x24f55dc9U, 0x9f6509ffU);
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008a20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0x16e530e0U, 0xcf4ded35U, 0xdb98121aU, 0x1116babbU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x0b54c2efU, 0x815a7fd2U, 0xcd703c4aU, 0x6db5138eU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x19c00000U);
    WR1_PROG(REG_1400H, 0x00c00081U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000838U);

    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x000007b8U);

    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    HW_SCE_p_func100(0x73616696U, 0x8630997aU, 0xfedfd07eU, 0xcbb352edU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xd0431654U, 0x03336f1eU, 0xa7f8b68aU, 0xeb7b53fbU);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c2000c4U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x820edca6U));

    OFS_ADR = 356;

    WR1_PROG(REG_1404H, 0x17380000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xa734b1abU, 0x2ebcf7b9U, 0x2d8fc41bU, 0x9a2017a3U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0007dU);
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

    WR1_PROG(REG_1004H, 0x1010000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x1010000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000002bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x032631faU, 0x2a96f76eU, 0x64823ae9U, 0x98d30f94U);
    HW_SCE_p_func052();

    WR1_PROG(REG_1404H, 0x15200000U);
    WR1_PROG(REG_1400H, 0x00c00091U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x820edca6U));

    OFS_ADR = 356;

    WR1_PROG(REG_1404H, 0x17380000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xd9b0e5f6U, 0xa7167730U, 0x669d0191U, 0x1c2a7857U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x000007b8U);
    WR1_PROG(REG_1018H, 0x00000838U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x10100007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x80b53e6fU, 0x17e8f062U, 0x6dcd482aU, 0x869863b1U);
    HW_SCE_p_func054();

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

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a40U);
    WR1_PROG(REG_1018H, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x28bb44fdU, 0x917b4c85U, 0x540b0040U, 0x0d4771cdU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xf52afbecU, 0x8f571c03U, 0x36415c1cU, 0xdd1d50b3U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x820edca6U));

    OFS_ADR = 356;

    WR1_PROG(REG_1404H, 0x13280000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x67a060e0U, 0xa203d5a8U, 0x2ac5d15aU, 0xb6905231U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x000003a8U);
    WR1_PROG(REG_1018H, 0x00000428U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x10100007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x820edca6U));

    OFS_ADR = 356;

    WR1_PROG(REG_1404H, 0x15300000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x1cda4bc3U, 0x3df9ac79U, 0x6bb95029U, 0x5c0bddeaU);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x17280000U);
    WR1_PROG(REG_1400H, 0x00c00011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x19c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0007dU);
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

    WR1_PROG(REG_1004H, 0x1010000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x000003a8U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x000001a0U);

    WR1_PROG(REG_1004H, 0x1010000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x000001a0U);
    WR1_PROG(REG_1018H, 0x00000220U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x10100007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000630U);

    WR1_PROG(REG_1004H, 0x20200010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000838U);
    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x20200002U);
    WR1_PROG(REG_1000H, 0x00010201U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x20200003U);
    WR1_PROG(REG_1000H, 0x00010201U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000220U);
    WR1_PROG(REG_101CH, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x20200002U);
    WR1_PROG(REG_1000H, 0x00010201U);
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

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xe0f381ddU, 0x8818a165U, 0x5b56bbf1U, 0xde72fe10U);
    HW_SCE_p_func054();

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

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a40U);
    WR1_PROG(REG_1018H, 0x00000630U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x112fe9ccU, 0x7eb5cdc1U, 0x15d6e346U, 0x7b761c98U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xda0cb818U, 0xa32e2080U, 0x4566635dU, 0x4d969c8aU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1400H, 0x00c00101U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000838U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000428U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x820edca6U));

    OFS_ADR = 356;

    WR1_PROG(REG_1404H, 0x15300000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00002b03U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x28ad7851U, 0xa7e096e0U, 0xffeb6c3fU, 0x06364136U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x00010001U);

    HW_SCE_p_func100(0x5ac4d446U, 0xe57bc99eU, 0x5023862aU, 0x26da91c6U);
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
    WR1_PROG(REG_1420H, change_endian_long(0x0000012bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x1a28bcf1U, 0x652c3ddcU, 0xd8eed235U, 0xef84ed64U);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000000dU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000012bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x3be047e2U, 0xe54e2a4dU, 0x246df305U, 0x68324e21U);
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
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x15300000U);
    for (iLoop = 0U; iLoop < 64U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x117556caU, 0x20b8b405U, 0x71770969U, 0xc44a71a2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe7008d05U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[1 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        HW_SCE_p_func101(0x99de8815U, 0xe3b60313U, 0x75843724U, 0xbd64d4f3U);
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
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x13280000U);
    for (iLoop = 0U; iLoop < 64U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0xb36852b5U, 0x19e484f7U, 0xd07604d7U, 0x733f088bU);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe7008d05U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[65 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        HW_SCE_p_func101(0x4083ae66U, 0x7e8f5ae5U, 0x175e45e8U, 0x7b3b9837U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0xf3da5d23U, 0x105a19f1U, 0x5805632dU, 0x4a7d18dfU);
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
    RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[129]);

    HW_SCE_p_func100(0x070d5e21U, 0x50af8f89U, 0x144ea57aU, 0x874626cfU);
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

    HW_SCE_p_func100(0x2fdac2bbU, 0x06b8556cU, 0x383d3c28U, 0xbf56c497U);
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
    WR1_PROG(REG_1420H, change_endian_long(0x0000022bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x9302326cU, 0x9c0d1864U, 0xd65ea9b1U, 0x279b3b7cU);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000000cU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000022bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x07a217c4U, 0x4dd38bd3U, 0xdfed9db4U, 0xed753cccU);
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
    WR1_PROG(REG_1600H, 0x00000040U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x15300000U);
    for (iLoop = 0U; iLoop < 64U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0xa1e896a6U, 0xc2173b77U, 0x2250dc70U, 0xc79e0f47U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[1 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        HW_SCE_p_func101(0xcd01b92fU, 0x7681047eU, 0xf1878982U, 0xfb4d6cfbU);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0x2ad4c1acU, 0x0d158bf5U, 0xcea9af76U, 0xc17310cdU);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xe8008104U);
    WR1_PROG(REG_1608H, 0x81010280U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[65]);

    HW_SCE_p_func100(0x97c92455U, 0xc1876e4eU, 0x3f1c0696U, 0x634a04f7U);
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
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[69]);

    HW_SCE_p_func100(0x37d06136U, 0xec2c651aU, 0x95e794bdU, 0x54992396U);
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PubKeyIndex[0]);

    HW_SCE_p_func102(0x1daa0de1U, 0x22623086U, 0x108f4d95U, 0xb121e306U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
