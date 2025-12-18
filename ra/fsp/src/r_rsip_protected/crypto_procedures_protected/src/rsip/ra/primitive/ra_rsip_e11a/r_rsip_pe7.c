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

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_pe7 (const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       uint32_t       OutData_HMACKeyIndex[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00e70001U, 0x000001c7U, 0x800200a0U);
    WR1_PROG(REG_002CH, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_OutDataType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub016(0x3000a8c0U, 0x00000007U, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000006U);
    r_rsip_func_sub007(0x00000080U, 0x38000ca5U, 0x00260000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    r_rsip_func_sub007(0x08000000U, 0x34202805U, 0x00260000U);

    r_rsip_func_sub007(0x380088c0U, 0x00000003U, 0x00260000U);

    r_rsip_func_sub007(0x380088c0U, 0x00000004U, 0x00260000U);

    r_rsip_func_sub007(0x380088c0U, 0x00000005U, 0x00260000U);

    r_rsip_func100(bswap_32big(0x23444ccdU),
                   bswap_32big(0x1cd09463U),
                   bswap_32big(0xb77bdad9U),
                   bswap_32big(0x983cc684U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xddfd5b8dU), bswap_32big(0x35e0dbdaU), bswap_32big(0x27d6bc7eU),
                       bswap_32big(0x5f0b986bU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x86f86687U), bswap_32big(0xff12997fU), bswap_32big(0xa1367908U),
                       bswap_32big(0x559d2aa0U));
        WR1_PROG(REG_0094H, 0x00007c06U);
        WR1_PROG(REG_0040H, 0x00600000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func_sub002(0x80010080U, 0x0000000fU);

            r_rsip_func101(bswap_32big(0xb538c615U), bswap_32big(0x3ee41483U), bswap_32big(0x03237020U),
                           bswap_32big(0xe20726d7U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func_sub002(0x80010080U, 0x0000001fU);

            r_rsip_func101(bswap_32big(0xf7ca43bfU), bswap_32big(0xe1b1880cU), bswap_32big(0x4f28d81cU),
                           bswap_32big(0x66d165a6U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func_sub002(0x80010080U, 0x0000000fU);

            r_rsip_func101(bswap_32big(0x5ec3d184U), bswap_32big(0xac868236U), bswap_32big(0xb245df37U),
                           bswap_32big(0x2093fd3bU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            r_rsip_func_sub002(0x80010080U, 0x0000001fU);

            r_rsip_func101(bswap_32big(0xe4a0dbffU), bswap_32big(0x2cb9ce63U), bswap_32big(0x3b067e2eU),
                           bswap_32big(0xcb488f39U));
        }

        WR1_PROG(REG_0094H, 0x0000b4e0U);
        WR1_PROG(REG_0094H, 0x00000010U);
        r_rsip_func_sub013(0x00003cc7U, 0x80010020U);
        WR1_PROG(REG_002CH, InData_OutDataLocation[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub016(0x00003405U, 0x00056c00U, 0x00003000U);

        r_rsip_func_sub007(0x00002481U, 0x34202804U, 0x00260000U);

        WR1_PROG(REG_0094H, 0x34202824U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x818762c0U), bswap_32big(0x2899c407U), bswap_32big(0x8cbdb209U),
                       bswap_32big(0x4923b5b3U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x99cebf8bU), bswap_32big(0xc73e0e3bU), bswap_32big(0x11f2effaU),
                           bswap_32big(0xba191fc4U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub016(0x000008c6U, 0x00000800U, 0x00000842U);

            WR1_PROG(REG_0094H, 0x00000863U);

            r_rsip_func100(bswap_32big(0xf0290472U), bswap_32big(0x9ff95744U), bswap_32big(0x12bf3972U),
                           bswap_32big(0xaeda341fU));
            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func_sub016(0x0000b4e0U, 0x00000014U, 0x00003ca7U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x34202880U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0094H, 0x0000a400U);
                r_rsip_func_sub007(0x0000001fU, 0x34202801U, 0x00260000U);

                r_rsip_func100(bswap_32big(0x53394a86U),
                               bswap_32big(0x64f23fc7U),
                               bswap_32big(0xd426ae85U),
                               bswap_32big(0xa96a3de1U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func101(bswap_32big(0x7103159aU),
                                   bswap_32big(0x569f6e78U),
                                   bswap_32big(0x1715601dU),
                                   bswap_32big(0x59512b03U));
                }
                else
                {
                    r_rsip_func_sub016(0x0000b4e0U, 0x00000018U, 0x00003c47U);

                    WR1_PROG(REG_0094H, 0x0000b4e0U);
                    WR1_PROG(REG_0094H, 0x0000001cU);
                    r_rsip_func_sub013(0x00003cc7U, 0x800100c0U);
                    WR1_PROG(REG_002CH, InData_KDFInfo[iLoop * 13]);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func_sub002(0x800100e0U, 0x0000e701U);

                    r_rsip_func101(bswap_32big(0x4d60e0ccU),
                                   bswap_32big(0x0cd67874U),
                                   bswap_32big(0xe254189eU),
                                   bswap_32big(0x8ff6cb17U));
                    r_rsip_func043();

                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x01799093U);

                    r_rsip_func_sub002(0x800100e0U, 0x0000e701U);

                    r_rsip_func101(bswap_32big(0xf4c08e43U),
                                   bswap_32big(0x318d95b2U),
                                   bswap_32big(0xd1e6f2d7U),
                                   bswap_32big(0x4135e1e3U));
                    r_rsip_func044();

                    WR1_PROG(REG_0094H, 0x38000c63U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    r_rsip_func100(bswap_32big(0x760f25b8U),
                                   bswap_32big(0x2d1e4780U),
                                   bswap_32big(0xc2f55ca6U),
                                   bswap_32big(0x44ae6a4eU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B0H, 0x00001404U);

                        r_rsip_func101(bswap_32big(0xc2c1d9b9U),
                                       bswap_32big(0x387a7e59U),
                                       bswap_32big(0x2bf55b95U),
                                       bswap_32big(0x19d56ec8U));
                    }
                    else
                    {
                        WR1_PROG(REG_00B0H, 0x00001408U);

                        r_rsip_func101(bswap_32big(0x68ce6d75U),
                                       bswap_32big(0x3bbdd06fU),
                                       bswap_32big(0x9a333aa0U),
                                       bswap_32big(0x97bda50dU));
                    }

                    r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

                    r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

                    r_rsip_func_sub008(0x000007c1U, 0x40000100U, 0xf7008d07U);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 1]);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 5]);

                    r_rsip_func_sub009(0x00c10021U, 0x00002c60U);

                    r_rsip_func_sub016(0x0000b4e0U, 0x00000018U, 0x00003847U);

                    r_rsip_func_sub016(0x0000b4e0U, 0x0000001cU, 0x000038c7U);

                    r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 9]);

                    r_rsip_func_sub006(0x9c100005U, 0x00410011U);

                    r_rsip_func100(bswap_32big(0x0df102a4U),
                                   bswap_32big(0xe26020ceU),
                                   bswap_32big(0x4c02d3a9U),
                                   bswap_32big(0xdcce7c9aU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000d040U);
                        r_rsip_func101(bswap_32big(0x5f124310U),
                                       bswap_32big(0x15de0e46U),
                                       bswap_32big(0xf828f69cU),
                                       bswap_32big(0x98e30fd9U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x8f26ae97U),
                                       bswap_32big(0xd952a7abU),
                                       bswap_32big(0x60d8465eU),
                                       bswap_32big(0x828732f6U));
                    }
                }

                WR1_PROG(REG_0094H, 0x00002c00U);

                WR1_PROG(REG_0094H, 0x00002cc0U);

                r_rsip_func101(bswap_32big(0x1e3eb30dU),
                               bswap_32big(0xe33f2eaeU),
                               bswap_32big(0xc51827a1U),
                               bswap_32big(0xaef949cdU));
            }

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000014U);
            r_rsip_func_sub007(0x00003807U, 0x380008c0U, 0x00260000U);
            WR1_PROG(REG_0040H, 0x00402000U);
            r_rsip_func_sub012(0x38000c42U, 0x00A60000U);
            r_rsip_func100(bswap_32big(0x05d9184dU), bswap_32big(0x5a5d455eU), bswap_32big(0xf473ef91U),
                           bswap_32big(0x6a60a711U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa7623a25U),
                               bswap_32big(0x8b353fd5U),
                               bswap_32big(0x3626c7f8U),
                               bswap_32big(0xebe92818U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x6e3390c6U),
                               bswap_32big(0x16b03663U),
                               bswap_32big(0x8a964c98U),
                               bswap_32big(0xc9c03e28U));
                r_rsip_func103();

                r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);

                r_rsip_func_sub003(0x80010000U, 0x03410005U);
                r_rsip_func_sub009(0x0001000dU, 0x000034c0U);

                r_rsip_func_sub002(0x800100e0U, 0x0000e702U);

                r_rsip_func101(bswap_32big(0x7e5d1b30U),
                               bswap_32big(0xaae92fccU),
                               bswap_32big(0x939a14e0U),
                               bswap_32big(0xcebe2ed0U));
                r_rsip_func043();

                r_rsip_func_sub016(0x0000b4e0U, 0x00000010U, 0x00003847U);

                r_rsip_func100(bswap_32big(0x073cc0d7U),
                               bswap_32big(0x7e727945U),
                               bswap_32big(0xd4687191U),
                               bswap_32big(0x93034af1U));
                WR1_PROG(REG_0094H, 0x00007c02U);
                WR1_PROG(REG_0040H, 0x00600000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000005U);

                    r_rsip_func101(bswap_32big(0x99c5e711U),
                                   bswap_32big(0xca9bdb0eU),
                                   bswap_32big(0x4243703cU),
                                   bswap_32big(0xd37d10e8U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000007U);

                    r_rsip_func101(bswap_32big(0xe9cf1961U),
                                   bswap_32big(0x4637165dU),
                                   bswap_32big(0x15ac5397U),
                                   bswap_32big(0xab219046U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0199e556U);

                    r_rsip_func101(bswap_32big(0x6708712dU),
                                   bswap_32big(0x094472a7U),
                                   bswap_32big(0x581a3827U),
                                   bswap_32big(0x167e9108U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0000001bU);

                    r_rsip_func101(bswap_32big(0xfb0616c1U),
                                   bswap_32big(0x386df986U),
                                   bswap_32big(0xc49524e1U),
                                   bswap_32big(0x56d86728U));
                }

                r_rsip_func_sub002(0x800100e0U, 0x0000e702U);

                r_rsip_func101(bswap_32big(0xb2838e5fU),
                               bswap_32big(0x7ddef38eU),
                               bswap_32big(0x32f21c1aU),
                               bswap_32big(0xc0d33dcdU));
                r_rsip_func044();

                r_rsip_func_sub016(0x00008c20U, 0x0000001fU, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x000008a5U);

                r_rsip_func_sub007(0x38008860U, 0x00000001U, 0x00260000U);

                r_rsip_func100(bswap_32big(0x51b794c7U),
                               bswap_32big(0x9c85fe03U),
                               bswap_32big(0x66eb37a1U),
                               bswap_32big(0xd60a4d3bU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000020U);
                    WR1_PROG(REG_00B0H, 0x00001804U);

                    r_rsip_func101(bswap_32big(0x8a0741e6U),
                                   bswap_32big(0x83843246U),
                                   bswap_32big(0x36041072U),
                                   bswap_32big(0x17bcd42cU));
                }
                else
                {
                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000040U);
                    WR1_PROG(REG_00B0H, 0x00003808U);

                    r_rsip_func101(bswap_32big(0x86fc0914U),
                                   bswap_32big(0x8c19584bU),
                                   bswap_32big(0xa76de44bU),
                                   bswap_32big(0xaa52932aU));
                }

                r_rsip_func100(bswap_32big(0xd2e3eddcU),
                               bswap_32big(0xd1491349U),
                               bswap_32big(0xb8834944U),
                               bswap_32big(0xd146fcc7U));
                WR1_PROG(REG_009CH, 0x81010080U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0094H, 0x342028a1U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    r_rsip_func_sub007(0x3420a8e0U, 0x00000020U, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xd616a99cU),
                                   bswap_32big(0xee776c24U),
                                   bswap_32big(0x19791fe6U),
                                   bswap_32big(0xeaf143eeU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0000H, 0x1000000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x10030005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        r_rsip_func101(bswap_32big(0xee4eb7abU),
                                       bswap_32big(0xa029b9d6U),
                                       bswap_32big(0x51d34a7bU),
                                       bswap_32big(0xb235c07fU));
                    }
                    else
                    {
                        r_rsip_func_sub003(0x800100c0U, 0x1340000dU);
                        r_rsip_func_sub009(0x13430005U, 0x02003cc7U);

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0x8b083f32U),
                                       bswap_32big(0xbe550ebaU),
                                       bswap_32big(0x21f31c86U),
                                       bswap_32big(0x98fffd3cU));
                    }

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xbb203d3fU),
                                   bswap_32big(0x168b8066U),
                                   bswap_32big(0x0fd3877eU),
                                   bswap_32big(0x4750a2d2U));
                }

                r_rsip_func_sub010(0x380008a4U);

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000000U);

                r_rsip_func_sub007(0x3420a840U, 0x00000002U, 0x00260000U);

                r_rsip_func100(bswap_32big(0x09ea0d90U),
                               bswap_32big(0xc2759f7cU),
                               bswap_32big(0x1e737daeU),
                               bswap_32big(0xc66675f8U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x38000c42U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    r_rsip_func100(bswap_32big(0xd7d82226U),
                                   bswap_32big(0x35716785U),
                                   bswap_32big(0xe16e59b9U),
                                   bswap_32big(0xfdbe682aU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x8069ac5aU),
                                       bswap_32big(0x5af201e6U),
                                       bswap_32big(0xbf393810U),
                                       bswap_32big(0x67a8b293U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        r_rsip_func_sub003(0x81840007U, 0x00490011U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0x83be8878U),
                                       bswap_32big(0xe91559c6U),
                                       bswap_32big(0x280dafe4U),
                                       bswap_32big(0x278d93c0U));
                        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        r_rsip_func_sub006(0x09108105U, 0x00410011U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func101(bswap_32big(0x13a25e80U),
                                       bswap_32big(0x16caa0e6U),
                                       bswap_32big(0x4a9a81aaU),
                                       bswap_32big(0xbfc37d6eU));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x0be92dc2U),
                                       bswap_32big(0x6184d31fU),
                                       bswap_32big(0x4afecabfU),
                                       bswap_32big(0xdca9fd83U));
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xe7009d07U);

                        r_rsip_func_sub003(0x81880007U, 0x00490021U);
                        WR1_PROG(REG_0008H, 0x00001022U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x44ccc008U),
                                       bswap_32big(0x682fb7abU),
                                       bswap_32big(0xd6862dd9U),
                                       bswap_32big(0x2cb7c7a1U));
                        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        r_rsip_func_sub006(0x09108105U, 0x00410011U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

                        r_rsip_func101(bswap_32big(0x76c83d11U),
                                       bswap_32big(0x65beced1U),
                                       bswap_32big(0x26eac509U),
                                       bswap_32big(0xe214e2c1U));
                    }

                    r_rsip_func100(bswap_32big(0x20f39bcbU),
                                   bswap_32big(0xbbf1ffe7U),
                                   bswap_32big(0x636ac79eU),
                                   bswap_32big(0xe0b48692U));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x3efb1c6bU),
                                   bswap_32big(0x90307becU),
                                   bswap_32big(0x424f984fU),
                                   bswap_32big(0xe1e2d288U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
                else
                {
                    r_rsip_func_sub007(0x3420a840U, 0x00000006U, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0x54dc6648U),
                                   bswap_32big(0xf6674d58U),
                                   bswap_32big(0xec193d6eU),
                                   bswap_32big(0x7afa0270U));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x4bb49e14U),
                                       bswap_32big(0x897e9aa3U),
                                       bswap_32big(0x87997f5fU),
                                       bswap_32big(0x85cc3c46U));
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xe7009d07U);

                        r_rsip_func_sub003(0x81880007U, 0x00490021U);
                        WR1_PROG(REG_0008H, 0x00001022U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[1]);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x24135ccfU),
                                       bswap_32big(0xf5dbaa30U),
                                       bswap_32big(0xfaa6067aU),
                                       bswap_32big(0x53dad97bU));
                        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        r_rsip_func_sub006(0x09108105U, 0x00410011U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[9]);

                        r_rsip_func100(bswap_32big(0xbc184f28U),
                                       bswap_32big(0xc2030cbaU),
                                       bswap_32big(0x261c2225U),
                                       bswap_32big(0x0ccc61eeU));
                        WR1_PROG(REG_009CH, 0x81010000U);
                        WR1_PROG(REG_0008H, 0x00005006U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD1_ADDR(REG_002CH, &OutData_HMACKeyIndex[0]);

                        r_rsip_func102(bswap_32big(0x9746947bU),
                                       bswap_32big(0x1505a3e7U),
                                       bswap_32big(0xc487f28fU),
                                       bswap_32big(0x09835b77U));
                        WR1_PROG(REG_006CH, 0x00000040U);
                        WAIT_STS(REG_0020H, 12, 0);

                        return RSIP_RET_PASS;
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0xee3d3854U),
                                       bswap_32big(0xe7aa18eeU),
                                       bswap_32big(0x2a27f125U),
                                       bswap_32big(0xe8fa696fU));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        r_rsip_func_sub003(0x81840007U, 0x00490011U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_EncIV[1]);

                        r_rsip_func100(bswap_32big(0x15471752U),
                                       bswap_32big(0xd761a449U),
                                       bswap_32big(0x32733ee0U),
                                       bswap_32big(0x2e3a128fU));
                        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        r_rsip_func_sub006(0x09108105U, 0x00410011U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_EncIV[5]);

                        r_rsip_func100(bswap_32big(0x64711f3cU),
                                       bswap_32big(0x0747c734U),
                                       bswap_32big(0x473fc529U),
                                       bswap_32big(0x4ee0b68dU));
                        WR1_PROG(REG_009CH, 0x81010000U);
                        WR1_PROG(REG_0008H, 0x00005006U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD1_ADDR(REG_002CH, &OutData_EncIV[0]);

                        r_rsip_func102(bswap_32big(0x69f2a2f0U),
                                       bswap_32big(0x6b9b7794U),
                                       bswap_32big(0xc8ad6f57U),
                                       bswap_32big(0xa4b5ed3eU));
                        WR1_PROG(REG_006CH, 0x00000040U);
                        WAIT_STS(REG_0020H, 12, 0);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
