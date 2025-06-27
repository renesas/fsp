/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func053 (void)
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

        r_rsip_func100(bswap_32big(0xe6bfc659U), bswap_32big(0xaf9aa26cU), bswap_32big(0xc8e73f5cU),
                       bswap_32big(0x199a1c3dU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000220U);

            WR1_PROG(REG_1004H, 0x1010000cU);
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

            r_rsip_func100(bswap_32big(0x12dd95b0U), bswap_32big(0xbe6c58beU), bswap_32big(0x9bdf49fcU),
                           bswap_32big(0x221d17fcU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1404H, 0x13980000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19b00000U);
                WR1_PROG(REG_1608H, 0x80010300U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x13980000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x19b00000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000428U);

                WR1_PROG(REG_1004H, 0x1111000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x1111000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x13980000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19b00000U);
                WR1_PROG(REG_1608H, 0x81010300U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                r_rsip_func101(bswap_32big(0xc13881d8U),
                               bswap_32big(0x8f55227dU),
                               bswap_32big(0xb9d32959U),
                               bswap_32big(0xce03406eU));
            }
            else
            {
                WR1_PROG(REG_1404H, 0x1f480000U);
                WR1_PROG(REG_1600H, 0x00000b7bU);
                WR1_PROG(REG_1608H, 0x81a0001bU);
                WR1_PROG(REG_1400H, 0x00c00011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90081U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1400H, 0x00c00091U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x12120009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000f053U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xccf9c189U),
                               bswap_32big(0x98d77cf7U),
                               bswap_32big(0xad66dba6U),
                               bswap_32big(0x1f2c9932U));
                r_rsip_func302();

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000428U);

                WR1_PROG(REG_1004H, 0x1111000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x13980000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1f480000U);
                WR1_PROG(REG_1400H, 0x00c00091U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x093b7d04U));

                OFS_ADR = 160;

                WR1_PROG(REG_1404H, 0x1f580000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000020U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000f053U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x508b97d6U),
                               bswap_32big(0x0506d2e3U),
                               bswap_32big(0x539b32c2U),
                               bswap_32big(0x86244960U));
                r_rsip_func017(OFS_ADR);

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1400H, 0x00c00091U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x12120009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000f053U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x9662b54eU),
                               bswap_32big(0x60ac207aU),
                               bswap_32big(0x8ef02d9dU),
                               bswap_32big(0x9a705dceU));
                r_rsip_func303();

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x17a80000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x1111000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x19b00000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                r_rsip_func101(bswap_32big(0xffc80b1aU),
                               bswap_32big(0x97eae19fU),
                               bswap_32big(0xf22d352bU),
                               bswap_32big(0xd442eedbU));
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x15aec9a0U), bswap_32big(0xa660fc1aU), bswap_32big(0x3b76b919U),
                           bswap_32big(0x2f5393d5U));

            break;
        }
    }

    WR1_PROG(REG_1600H, 0x000037bcU);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
