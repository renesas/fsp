/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func314 (void)
{
    uint32_t OFS_ADR = 0U;

    WR1_PROG(REG_1600H, 0x0000379dU);

    while (1)
    {
        WR1_PROG(REG_1404H, 0x12180000U);
        WR1_PROG(REG_1608H, 0x80010340U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x3800db40U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x367fd627U, 0xeacd50d5U, 0x44483ed5U, 0x5b4c428cU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000220U);

            WR1_PROG(REG_1004H, 0x1818000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x14200000U);
            WR1_PROG(REG_1608H, 0x80010340U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x1a380000U);
            WR1_PROG(REG_1608H, 0x80010360U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000135bU);
            WR1_PROG(REG_1600H, 0x3800db40U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x41d721fdU, 0x45da851bU, 0x437f0ec6U, 0xf2a800d3U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1404H, 0x13580000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19700000U);
                WR1_PROG(REG_1608H, 0x80010300U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x13580000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x19700000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000428U);

                WR1_PROG(REG_1004H, 0x1919000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x1919000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x13580000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19700000U);
                WR1_PROG(REG_1608H, 0x81010300U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0x13451407U, 0xf6b702ecU, 0x28a7c2ffU, 0x51f4feecU);
            }
            else
            {
                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1600H, 0x00000b7bU);
                WR1_PROG(REG_1608H, 0x81b0001bU);
                WR1_PROG(REG_1400H, 0x00c00011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c900c1U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1400H, 0x00c000d1U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x1a1a0009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000f314U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x464151e4U, 0xb056ed9fU, 0xef7fc366U, 0xd17e4bcfU);
                HW_SCE_p_func317();

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000428U);

                WR1_PROG(REG_1004H, 0x1919000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x13580000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1400H, 0x00c000d1U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0xf6428095U));

                OFS_ADR = 224;

                WR1_PROG(REG_1404H, 0x1f180000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000030U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000f314U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xab5ad8a7U, 0xe970f650U, 0x30b38769U, 0x6a4d4201U);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1400H, 0x00c000d1U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x1a1a0009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000f314U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x5afd62c1U, 0x70bab88eU, 0x0a5d77b6U, 0xa4081e91U);
                HW_SCE_p_func318();

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x1919000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x19700000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0xdb8a18a7U, 0x0f1a9fabU, 0xd4525dd7U, 0x70d05543U);
            }
        }
        else
        {
            HW_SCE_p_func101(0xa24df6d5U, 0xb10f9340U, 0xdb36ebf4U, 0x0fcf72ffU);

            break;
        }
    }

    WR1_PROG(REG_1600H, 0x000037bcU);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
