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

void r_rsip_func311 (void)
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
    WR1_PROG(REG_1404H, 0x1b680000U);
    WR1_PROG(REG_1400H, 0x00c00331U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1014H, 0x00000530U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000d88U);
    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000e98U);
    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    while (1)
    {
        WR1_PROG(REG_1404H, 0x1ae00000U);
        WR1_PROG(REG_1608H, 0x80010080U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x38000c84U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);
        r_rsip_func100(bswap_32big(0x6c3f5059U), bswap_32big(0xc0742058U), bswap_32big(0x72caad39U),
                       bswap_32big(0xcf4dc557U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000b68U);
            WR1_PROG(REG_1018H, 0x00000d88U);
            WR1_PROG(REG_1020H, 0x00000b68U);
            WR1_PROG(REG_1004H, 0x11110009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000948U);
            WR1_PROG(REG_1018H, 0x00000e98U);
            WR1_PROG(REG_1020H, 0x00000948U);
            WR1_PROG(REG_1004H, 0x21210009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0xf065cebbU), bswap_32big(0xb4a2e3ceU), bswap_32big(0x22713327U),
                           bswap_32big(0x0a5a29a7U));
        }
        else
        {
            WR1_PROG(REG_1014H, 0x00000b68U);
            WR1_PROG(REG_1018H, 0x00000d88U);
            WR1_PROG(REG_1020H, 0x00000a58U);
            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x19d00000U);
            WR1_PROG(REG_1608H, 0x800100a0U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000d88U);
            WR1_PROG(REG_1018H, 0x00000b68U);
            WR1_PROG(REG_1020H, 0x00000a58U);
            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x19d00000U);
            WR1_PROG(REG_1608H, 0x800100c0U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1600H, 0x38000cc6U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            r_rsip_func100(bswap_32big(0x9233eb27U), bswap_32big(0xb080aa8aU), bswap_32big(0x4f2e9fbeU),
                           bswap_32big(0x62b0be4fU));
            WR1_PROG(REG_143CH, 0x00400000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1404H, 0x18400000U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1600H, 0x38000ce7U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);
                r_rsip_func100(bswap_32big(0x41cb113bU),
                               bswap_32big(0xc311954fU),
                               bswap_32big(0x2411cb1aU),
                               bswap_32big(0xcce1c8a9U));
                WR1_PROG(REG_143CH, 0x00400000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1014H, 0x00000c78U);
                    WR1_PROG(REG_1018H, 0x00000948U);
                    WR1_PROG(REG_1020H, 0x00000a58U);
                    WR1_PROG(REG_1004H, 0x2121000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1404H, 0x19500000U);
                    WR1_PROG(REG_1608H, 0x80010100U);
                    WR1_PROG(REG_1400H, 0x00030005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x03430005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1600H, 0x00002d00U);
                    WR1_PROG(REG_1404H, 0x19d00000U);
                    WR1_PROG(REG_1608H, 0x81010100U);
                    WR1_PROG(REG_1400H, 0x00c00085U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c90005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1014H, 0x00000b68U);
                    WR1_PROG(REG_1018H, 0x00000a58U);
                    WR1_PROG(REG_1020H, 0x00000b68U);
                    WR1_PROG(REG_1004H, 0x1111000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1404H, 0x19500000U);
                    WR1_PROG(REG_1608H, 0x81010100U);
                    WR1_PROG(REG_1400H, 0x00c00005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c90005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c00101U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1014H, 0x00000948U);
                    WR1_PROG(REG_1018H, 0x00000a58U);
                    WR1_PROG(REG_1020H, 0x00000948U);
                    WR1_PROG(REG_1004H, 0x21210009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    r_rsip_func101(bswap_32big(0xd97d7079U),
                                   bswap_32big(0xece70de5U),
                                   bswap_32big(0x88c3762eU),
                                   bswap_32big(0xe1ed94fdU));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    r_rsip_func100(bswap_32big(0x28f035e2U),
                                   bswap_32big(0x2acfbfc5U),
                                   bswap_32big(0x82581072U),
                                   bswap_32big(0xc4691dd6U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1014H, 0x00000948U);
                        WR1_PROG(REG_1018H, 0x00000e98U);
                        WR1_PROG(REG_1020H, 0x00000a58U);
                        WR1_PROG(REG_1004H, 0x2121000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_1404H, 0x19500000U);
                        WR1_PROG(REG_1608H, 0x80010100U);
                        WR1_PROG(REG_1400H, 0x03430005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x00030005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1600H, 0x38000d08U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00A60000U);
                        r_rsip_func100(bswap_32big(0x61607ae2U),
                                       bswap_32big(0xcac66caeU),
                                       bswap_32big(0x15336fe6U),
                                       bswap_32big(0x125a931bU));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            r_rsip_func101(bswap_32big(0x612561b1U),
                                           bswap_32big(0x69a6b19aU),
                                           bswap_32big(0xb89806e3U),
                                           bswap_32big(0xecaba86aU));
                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x18400000U);
                            WR1_PROG(REG_1400H, 0x00c00109U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1014H, 0x00000b68U);
                            WR1_PROG(REG_1018H, 0x00000d88U);
                            WR1_PROG(REG_1020H, 0x00000b68U);
                            WR1_PROG(REG_1004H, 0x1111000aU);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0U, 0U);
                            WR1_PROG(REG_1014H, 0x00000a58U);
                            WR1_PROG(REG_1018H, 0x00000948U);
                            WR1_PROG(REG_1020H, 0x00000948U);
                            WR1_PROG(REG_1004H, 0x21210009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0U, 0U);
                            r_rsip_func101(bswap_32big(0xcdeaef1eU),
                                           bswap_32big(0xc960fb74U),
                                           bswap_32big(0x69ae4e67U),
                                           bswap_32big(0xfd8d1626U));
                        }
                    }
                    else
                    {
                        WR1_PROG(REG_1404H, 0x18400000U);
                        WR1_PROG(REG_1608H, 0x80010120U);
                        WR1_PROG(REG_1400H, 0x00030005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x03430005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1600H, 0x38000d29U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x2b1a9745U),
                                       bswap_32big(0xd5150c15U),
                                       bswap_32big(0xcd8ab433U),
                                       bswap_32big(0x432e8cd7U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            r_rsip_func101(bswap_32big(0x0684953fU),
                                           bswap_32big(0x4ff4772aU),
                                           bswap_32big(0xdb4046e8U),
                                           bswap_32big(0xeed45ea7U));
                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x18400000U);
                            WR1_PROG(REG_1400H, 0x00c00009U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1404H, 0x19d00000U);
                            WR1_PROG(REG_1608H, 0x81010120U);
                            WR1_PROG(REG_1400H, 0x00c00085U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x00c90005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1014H, 0x00000b68U);
                            WR1_PROG(REG_1018H, 0x00000a58U);
                            WR1_PROG(REG_1020H, 0x00000b68U);
                            WR1_PROG(REG_1004H, 0x21210009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0U, 0U);
                            r_rsip_func101(bswap_32big(0xd03bebfaU),
                                           bswap_32big(0x248a6525U),
                                           bswap_32big(0x5de0f709U),
                                           bswap_32big(0x6183dfe7U));
                        }
                    }
                }
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b68U);
                WR1_PROG(REG_1018H, 0x00000d88U);
                WR1_PROG(REG_1020H, 0x00000b68U);
                WR1_PROG(REG_1004H, 0x1111000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000948U);
                WR1_PROG(REG_1018H, 0x00000e98U);
                WR1_PROG(REG_1020H, 0x00000948U);
                WR1_PROG(REG_1004H, 0x2121000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                r_rsip_func101(bswap_32big(0x2d4d6fecU),
                               bswap_32big(0x5332f872U),
                               bswap_32big(0xeb3db6dcU),
                               bswap_32big(0x2099468eU));
            }
        }
    }

    WR1_PROG(REG_1014H, 0x00000948U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000838U);
    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1014H, 0x00000b68U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000738U);
    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
