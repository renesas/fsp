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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func073 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    r_rsip_func100(bswap_32big(0x1a17116dU),
                   bswap_32big(0x1534088dU),
                   bswap_32big(0x822d9d3aU),
                   bswap_32big(0x86cf5164U));
    r_rsip_func070(ARG1);

    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000000c0U);

    WR1_PROG(REG_1004H, 0x04040010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000070U);

    WR1_PROG(REG_1004H, 0x04040010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x11e00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    r_rsip_func_sub002(0x00c0001dU);
    r_rsip_func_sub002(0x00c20005U);
    r_rsip_func_sub002(0x0002000dU);

    r_rsip_func_sub001(0x000000c0U, 0x00000200U, 0x00000160U, 0x0404000aU);

    r_rsip_func_sub001(0x00000160U, 0x00000930U, 0x000001b0U, 0x0404000aU);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func_sub001(0x00000930U, 0x00000200U, 0x000001b0U, 0x0404000aU);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func_sub001(0x00000160U, 0x00000980U, 0x000001b0U, 0x0404000aU);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func_sub001(0x00000980U, 0x00000200U, 0x000001b0U, 0x0404000aU);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func100(bswap_32big(0x4bcdf189U),
                   bswap_32big(0xaf66475bU),
                   bswap_32big(0xb52b2d2dU),
                   bswap_32big(0x3e0f065cU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x95486067U), bswap_32big(0xf45456e8U), bswap_32big(0xa5b526f0U),
                       bswap_32big(0x798882b6U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0xdaaf0924U), bswap_32big(0xf21f9d17U), bswap_32big(0x95199256U),
                       bswap_32big(0xb2dd032bU));

        r_rsip_func_sub001(0x00000160U, 0x00000200U, 0x000001b0U, 0x0404000aU);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);
        WR1_PROG(REG_1010H, 0x00000020U);

        WR1_PROG(REG_1004H, 0x0404000fU);
        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_143CH, 0x00000d00U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000840U);
        r_rsip_func_sub003(0x000000c0U, 0x00000160U, 0x04040002U);

        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1608H, 0x8188001fU);
        r_rsip_func_sub002(0x00c90021U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000160U);
        r_rsip_func_sub003(0x000000c0U, 0x00000480U, 0x04040002U);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000160U);
        r_rsip_func_sub003(0x000000c0U, 0x00000340U, 0x04040002U);

        WR1_PROG(REG_1010H, 0x00000018U);

        WR1_PROG(REG_1404H, 0x11400000U);
        r_rsip_func_sub002(0x00c00021U);

        WR1_PROG(REG_1404H, 0x19800000U);
        r_rsip_func_sub002(0x00c002d1U);

        WR1_PROG(REG_1014H, 0x00000390U);
        r_rsip_func_sub003(0x00000070U, 0x00000a70U, 0x04040004U);

        r_rsip_func_sub001(0x00000890U, 0x00000160U, 0x000002c8U, 0x04040009U);

        r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x000002f0U, 0x04040009U);

        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1608H, 0x81880001U);
        r_rsip_func_sub002(0x00c90021U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000390U);
        r_rsip_func_sub003(0x00000070U, 0x00000a20U, 0x04040002U);

        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1600H, 0x000037e1U);
        WR1_PROG(REG_1600H, 0x0000a7e0U);
        WR1_PROG(REG_1600H, 0x00000020U);
        WR1_PROG(REG_1608H, 0x8188001fU);
        r_rsip_func_sub002(0x00c90021U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000390U);
        r_rsip_func_sub003(0x00000070U, 0x00000a48U, 0x04040002U);

        r_rsip_func100(bswap_32big(0x95ce33b6U), bswap_32big(0x0caec020U), bswap_32big(0x3d68910fU),
                       bswap_32big(0x726ba7bdU));
        r_rsip_func071(ARG1);

        r_rsip_func_sub001(0x00000200U, 0x00000160U, 0x00000b10U, 0x04040009U);

        r_rsip_func_sub001(0x00000228U, 0x00000160U, 0x00000b38U, 0x04040009U);

        r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000b60U, 0x04040009U);

        r_rsip_func_sub001(0x00000b10U, 0x00000a20U, 0x00000110U, 0x0404000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000a20U, 0x00000b10U, 0x00000110U, 0x0404000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000b38U, 0x00000a48U, 0x00000110U, 0x0404000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000a48U, 0x00000b38U, 0x00000110U, 0x0404000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xf2c73929U), bswap_32big(0x543811e5U), bswap_32big(0x274e655eU),
                       bswap_32big(0xcb1a2177U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000b60U);
            WR1_PROG(REG_1018H, 0x00000a70U);
            r_rsip_func_sub003(0x00000070U, 0x00000c50U, 0x04040013U);
            WR1_PROG(REG_143CH, 0x00000d00U);

            r_rsip_func101(bswap_32big(0x7bc13891U), bswap_32big(0x2d588ab0U), bswap_32big(0xaba1ee5aU),
                           bswap_32big(0x1f0e61fcU));
        }
        else
        {
            WR1_PROG(REG_1014H, 0x00000b60U);
            r_rsip_func_sub003(0x000002f0U, 0x00000c50U, 0x04040014U);
            WR1_PROG(REG_143CH, 0x00000d00U);

            r_rsip_func101(bswap_32big(0xa796a82aU), bswap_32big(0x0b15b4d8U), bswap_32big(0x144272e1U),
                           bswap_32big(0xc1f8f6ecU));
        }

        WR1_PROG(REG_1600H, 0x00000821U);

        WR1_PROG(REG_1404H, 0x14600000U);
        WR1_PROG(REG_1608H, 0x80880001U);
        r_rsip_func_sub002(0x03430021U);

        WR1_PROG(REG_1600H, 0x0000a420U);
        WR1_PROG(REG_1600H, 0x00000050U);

        WR1_PROG(REG_1404H, 0x13200000U);
        WR1_PROG(REG_1608H, 0x80880001U);
        r_rsip_func_sub002(0x03430021U);

        WR1_PROG(REG_1404H, 0x11600000U);
        r_rsip_func_sub002(0x00c000f1U);

        WR1_PROG(REG_1600H, 0x00000821U);

        for (iLoop = 0U; iLoop < 8U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x000034a1U);

            WR1_PROG(REG_1600H, 0x00026ca5U);

            WR1_PROG(REG_1600H, 0x00003865U);

            WR1_PROG(REG_1600H, 0x0000a4a0U);
            WR1_PROG(REG_1600H, 0x00000050U);

            WR1_PROG(REG_1600H, 0x00003885U);

            WR1_PROG(REG_1600H, 0x00000842U);

            for (jLoop = 0U; jLoop < 32U; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x000008a5U);

                WR1_PROG(REG_1600H, 0x01816ca3U);
                WR1_PROG(REG_1600H, 0x01816ca4U);
                WR1_PROG(REG_1600H, 0x00016c63U);
                WR1_PROG(REG_1600H, 0x00016c84U);

                WR1_PROG(REG_1404H, 0x11400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                r_rsip_func_sub002(0x00c0001dU);
                r_rsip_func_sub002(0x00c20005U);
                r_rsip_func_sub002(0x0002000dU);

                r_rsip_func_sub001(0x00000200U, 0x00000160U, 0x00000110U, 0x0404000aU);

                WR1_PROG(REG_143CH, 0x00a10000U);

                r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0404000aU);

                WR1_PROG(REG_143CH, 0x00a10000U);

                r_rsip_func100(bswap_32big(0x191767f0U),
                               bswap_32big(0xabc6db42U),
                               bswap_32big(0x9992ee17U),
                               bswap_32big(0x44d567baU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1014H, 0x00000250U);
                    r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x04040014U);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    r_rsip_func101(bswap_32big(0x0bf72d59U),
                                   bswap_32big(0x410c46e2U),
                                   bswap_32big(0xf26de175U),
                                   bswap_32big(0x5aa05d25U));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0x8cec993eU),
                                   bswap_32big(0xa3e7c7c2U),
                                   bswap_32big(0x39305501U),
                                   bswap_32big(0xbed293bfU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000ca5U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                r_rsip_func100(bswap_32big(0xbdc2f467U),
                               bswap_32big(0x6e7526a0U),
                               bswap_32big(0x242438bfU),
                               bswap_32big(0x5047ecc5U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func100(bswap_32big(0x3b8dc878U),
                                   bswap_32big(0x344a8884U),
                                   bswap_32big(0x9a078a77U),
                                   bswap_32big(0xefdd58cfU));

                    WR1_PROG(REG_1404H, 0x11400000U);
                    r_rsip_func_sub002(0x00c00021U);

                    WR1_PROG(REG_1600H, 0x00007c05U);
                    WR1_PROG(REG_143CH, 0x00600000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                    {
                        r_rsip_func_sub001(0x00000a20U, 0x00000160U, 0x00000430U, 0x04040009U);

                        r_rsip_func_sub001(0x00000a48U, 0x00000160U, 0x00000458U, 0x04040009U);

                        r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000480U, 0x04040009U);

                        r_rsip_func101(bswap_32big(0x30231137U),
                                       bswap_32big(0xfd6f9e09U),
                                       bswap_32big(0xdfe25bfdU),
                                       bswap_32big(0x6df51643U));
                    }
                    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
                    {
                        r_rsip_func_sub001(0x00000b10U, 0x00000160U, 0x00000430U, 0x04040009U);

                        r_rsip_func_sub001(0x00000b38U, 0x00000160U, 0x00000458U, 0x04040009U);

                        r_rsip_func_sub001(0x00000b60U, 0x00000160U, 0x00000480U, 0x04040009U);

                        r_rsip_func101(bswap_32big(0xa8fe4a11U),
                                       bswap_32big(0x10661ad1U),
                                       bswap_32big(0xc7063800U),
                                       bswap_32big(0xd95f9173U));
                    }
                    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
                    {
                        r_rsip_func_sub001(0x00000c00U, 0x00000160U, 0x00000430U, 0x04040009U);

                        r_rsip_func_sub001(0x00000c28U, 0x00000160U, 0x00000458U, 0x04040009U);

                        r_rsip_func_sub001(0x00000c50U, 0x00000160U, 0x00000480U, 0x04040009U);

                        r_rsip_func101(bswap_32big(0xd4201b8dU),
                                       bswap_32big(0xb71b39cdU),
                                       bswap_32big(0x6aaa4ad1U),
                                       bswap_32big(0x9684b655U));
                    }

                    WR1_PROG(REG_1404H, 0x11400000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    r_rsip_func_sub002(0x00c0001dU);
                    r_rsip_func_sub002(0x00c20005U);
                    r_rsip_func_sub002(0x0002000dU);

                    r_rsip_func_sub001(0x00000200U, 0x00000160U, 0x00000110U, 0x0404000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0404000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x815d4972U),
                                   bswap_32big(0x35424cf3U),
                                   bswap_32big(0x32df663cU),
                                   bswap_32big(0xf3b8ee50U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func_sub001(0x00000430U, 0x00000160U, 0x00000110U, 0x0404000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000110U, 0x0404000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0x4ba41fffU),
                                       bswap_32big(0xf81310a6U),
                                       bswap_32big(0xf8796bdfU),
                                       bswap_32big(0xaab20d7fU));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            r_rsip_func_sub001(0x00000200U, 0x00000430U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func_sub001(0x00000430U, 0x00000200U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func_sub001(0x00000228U, 0x00000458U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func_sub001(0x00000458U, 0x00000228U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func_sub001(0x00000250U, 0x00000480U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func_sub001(0x00000480U, 0x00000250U, 0x00000110U, 0x0404000aU);

                            WR1_PROG(REG_143CH, 0x00210000U);

                            r_rsip_func100(bswap_32big(0x2635d046U),
                                           bswap_32big(0x20b329a4U),
                                           bswap_32big(0xde498607U),
                                           bswap_32big(0x5f44fecaU));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                WR1_PROG(REG_1014H, 0x00000250U);
                                WR1_PROG(REG_1018H, 0x00000480U);
                                r_rsip_func_sub003(0x00000070U, 0x00000250U, 0x04040013U);
                                WR1_PROG(REG_143CH, 0x00000d00U);

                                r_rsip_func101(bswap_32big(0xcbfc8dfbU), bswap_32big(0x5c1f6da9U),
                                               bswap_32big(0x5eb382a7U), bswap_32big(0xcb77f9e4U));
                            }
                            else
                            {
                                WR1_PROG(REG_1014H, 0x00000250U);
                                r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x04040014U);
                                WR1_PROG(REG_143CH, 0x00000d00U);

                                r_rsip_func101(bswap_32big(0x121ad6a0U), bswap_32big(0x4abdaa1dU),
                                               bswap_32big(0x87efc800U), bswap_32big(0xc9b59ee2U));
                            }
                        }
                        else
                        {
                            r_rsip_func101(bswap_32big(0x4437f798U),
                                           bswap_32big(0xc2603db6U),
                                           bswap_32big(0xdb097d26U),
                                           bswap_32big(0x6e736af2U));
                        }
                    }
                    else
                    {
                        WR1_PROG(REG_1404H, 0x11400000U);
                        r_rsip_func_sub002(0x00c00021U);

                        r_rsip_func_sub001(0x00000430U, 0x00000160U, 0x00000200U, 0x04040009U);

                        r_rsip_func_sub001(0x00000458U, 0x00000160U, 0x00000228U, 0x04040009U);

                        r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000250U, 0x04040009U);

                        r_rsip_func101(bswap_32big(0x3de3f17dU),
                                       bswap_32big(0x87271290U),
                                       bswap_32big(0x9c1a9c8fU),
                                       bswap_32big(0x9e585bafU));
                    }
                }
                else
                {
                    r_rsip_func101(bswap_32big(0x8b0ae415U),
                                   bswap_32big(0x7b46fb70U),
                                   bswap_32big(0xeb25ac6eU),
                                   bswap_32big(0xd4382c1dU));
                }

                WR1_PROG(REG_1600H, 0x00002c40U);
                r_rsip_func101(bswap_32big(0xf4655730U),
                               bswap_32big(0xf928fbbeU),
                               bswap_32big(0x4abbd73fU),
                               bswap_32big(0xf874d7deU));
            }

            WR1_PROG(REG_1600H, 0x38008840U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00002c20U);

            r_rsip_func101(bswap_32big(0xa2384d69U), bswap_32big(0xf9a4974cU), bswap_32big(0x779a3b1cU),
                           bswap_32big(0xda9e0812U));
        }

        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000008U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x12800000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_func_sub002(0x00c0001dU);
        r_rsip_func_sub002(0x00c20005U);
        r_rsip_func_sub002(0x0002000dU);

        r_rsip_func_sub001(0x00000250U, 0x000002a0U, 0x000002f0U, 0x0404000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0x96e6a243U), bswap_32big(0xc9efea35U), bswap_32big(0xea881343U),
                       bswap_32big(0x77955462U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xfa7deb28U), bswap_32big(0x7d91d2abU), bswap_32big(0x884549b3U),
                           bswap_32big(0x87d6ca43U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xcc82ccacU), bswap_32big(0xd1cdc457U), bswap_32big(0x32e6b3e2U),
                           bswap_32big(0xa5d19c08U));

            WR1_PROG(REG_1014H, 0x00000250U);
            r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x04040004U);

            WR1_PROG(REG_1404H, 0x11400000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
            r_rsip_func_sub002(0x00c0001dU);
            r_rsip_func_sub002(0x00c20005U);
            r_rsip_func_sub002(0x0002000dU);

            r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x00000110U, 0x0404000aU);

            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x0404000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000200U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x04040002U);

            r_rsip_func_sub001(0x000002a0U, 0x00000930U, 0x000001b0U, 0x0404000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000930U, 0x000002a0U, 0x000001b0U, 0x0404000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x785aa023U), bswap_32big(0x28d92742U), bswap_32big(0x352febc3U),
                           bswap_32big(0xced84b2eU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x14c1a0a2U),
                               bswap_32big(0x99dcd412U),
                               bswap_32big(0x0f5bf522U),
                               bswap_32big(0xb0da0764U));
            }
            else
            {
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x797935bbU);

                r_rsip_func101(bswap_32big(0x925a047dU),
                               bswap_32big(0x795335c8U),
                               bswap_32big(0x389791f7U),
                               bswap_32big(0x58dee35dU));
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x797935bbU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
