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
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func322 (void)
{
    uint32_t iLoop;
    uint32_t jLoop;
    uint32_t kLoop;
    uint32_t oLoop;
    uint32_t oLoop1;
    uint32_t OFS_ADR;
    (void) iLoop;
    (void) jLoop;
    (void) kLoop;
    (void) oLoop;
    (void) oLoop1;
    (void) OFS_ADR;
    WR1_PROG(REG_1600H, 0x0000379dU);
    while (1)
    {
        WR1_PROG(REG_1404H, 0x12280000U);
        WR1_PROG(REG_1608H, 0x80010340U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x3800db40U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0xb1dd5988U), bswap_32big(0x6724050aU), bswap_32big(0x1fb6da00U),
                       bswap_32big(0xcb12386dU));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000230U);
            WR1_PROG(REG_1004H, 0x4040000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x14400000U);
            WR1_PROG(REG_1608H, 0x80010340U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1404H, 0x1a880000U);
            WR1_PROG(REG_1608H, 0x80010360U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1600H, 0x0000135bU);
            WR1_PROG(REG_1600H, 0x3800db40U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            r_rsip_func100(bswap_32big(0x70785f8eU), bswap_32big(0xf531bb18U), bswap_32big(0xd3f02cd6U),
                           bswap_32big(0xabcc7de7U));
            WR1_PROG(REG_143CH, 0x00400000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1404H, 0x12380000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x18800000U);
                WR1_PROG(REG_1608H, 0x80010300U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x12380000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x18800000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000448U);
                WR1_PROG(REG_1020H, 0x00000448U);
                WR1_PROG(REG_1004H, 0x4141000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000a90U);
                WR1_PROG(REG_1020H, 0x00000a90U);
                WR1_PROG(REG_1004H, 0x4141000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1404H, 0x12380000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x18800000U);
                WR1_PROG(REG_1608H, 0x81010300U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                r_rsip_func101(bswap_32big(0xb4b65d12U),
                               bswap_32big(0x0b0077e7U),
                               bswap_32big(0xb41fa2b3U),
                               bswap_32big(0x65c2a4c8U));
            }
            else
            {
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1400H, 0x00c00211U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x8162b38bU));
                OFS_ADR = 676;
                WR1_PROG(REG_1404H, 0x1dd80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000080U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003221U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xacf207f3U),
                               bswap_32big(0x152726d7U),
                               bswap_32big(0x7e0bcc84U),
                               bswap_32big(0x4f5dc8e5U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1400H, 0x00c00211U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000448U);
                WR1_PROG(REG_1018H, 0x00000878U);
                WR1_PROG(REG_1020H, 0x00000878U);
                WR1_PROG(REG_1004H, 0x42420009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000f322U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xa2fa752eU),
                               bswap_32big(0x67b01aafU),
                               bswap_32big(0x7fa73a51U),
                               bswap_32big(0x78169ab1U));
                r_rsip_func323();
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000878U);
                WR1_PROG(REG_1020H, 0x00000448U);
                WR1_PROG(REG_1004H, 0x4141000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1404H, 0x12380000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1400H, 0x00c00211U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x7edfb1abU));
                OFS_ADR = 544;
                WR1_PROG(REG_1404H, 0x1dd80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000080U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003222U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xf66ac87eU),
                               bswap_32big(0xa61626cdU),
                               bswap_32big(0xc7b198c4U),
                               bswap_32big(0x17f1dfe4U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1400H, 0x00c00211U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000a90U);
                WR1_PROG(REG_1018H, 0x00000878U);
                WR1_PROG(REG_1020H, 0x00000878U);
                WR1_PROG(REG_1004H, 0x42420009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000f322U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x600e5cf9U),
                               bswap_32big(0xa890991eU),
                               bswap_32big(0xb69ce047U),
                               bswap_32big(0x336790b2U));
                r_rsip_func324();
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1608H, 0x800102e0U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1400H, 0x00c00009U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000878U);
                WR1_PROG(REG_1020H, 0x00000a90U);
                WR1_PROG(REG_1004H, 0x4141000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1404H, 0x18800000U);
                WR1_PROG(REG_1608H, 0x810102e0U);
                WR1_PROG(REG_1400H, 0x00c00005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c90005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                r_rsip_func101(bswap_32big(0x0e7039f5U),
                               bswap_32big(0x30767f49U),
                               bswap_32big(0x0ef2e8fbU),
                               bswap_32big(0x29d1f692U));
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x7e9a673eU), bswap_32big(0x90a84e5fU), bswap_32big(0xfdf8ac6dU),
                           bswap_32big(0xa0987c1fU));
            break;
        }
    }

    WR1_PROG(REG_1600H, 0x000037bcU);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
