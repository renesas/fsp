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

rsip_ret_t r_rsip_pe7 (const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e70001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x800200a0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_OutDataType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000ca5U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x08000000U);
    WR1_PROG(REG_0094H, 0x34202805U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x34202806U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0xd5de0837U), bswap_32big(0x9408ecfaU), bswap_32big(0xe9e1f84aU), bswap_32big(0xaf3cd0f5U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe59c25e2U), bswap_32big(0xb54fc63bU), bswap_32big(0xf80c0a9eU), bswap_32big(0x89edb2beU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xc575694fU), bswap_32big(0xa40fbd02U), bswap_32big(0x61eea7a1U), bswap_32big(0x5ca4e1f3U));
        WR1_PROG(REG_0094H, 0x00007c06U);
        WR1_PROG(REG_0040H, 0x00600000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x1b0ab255U), bswap_32big(0x1c533cd3U), bswap_32big(0x2b39ab28U), bswap_32big(0x6233f2efU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000001fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xd602d25dU), bswap_32big(0x78331065U), bswap_32big(0x58f1d0ddU), bswap_32big(0x7df85d6eU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x24a6999bU), bswap_32big(0x083d15daU), bswap_32big(0x1fc6deffU), bswap_32big(0x8ad56f2bU));
        }

        WR1_PROG(REG_0094H, 0x0000b4e0U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_0094H, 0x00003cc7U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_OutDataLocation[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x00003405U);
        WR1_PROG(REG_0094H, 0x00056c00U);
        WR1_PROG(REG_0094H, 0x00003000U);

        WR1_PROG(REG_0094H, 0x00002481U);

        WR1_PROG(REG_0094H, 0x34202804U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0094H, 0x34202824U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x818762c0U), bswap_32big(0x2899c407U), bswap_32big(0x8cbdb209U), bswap_32big(0x4923b5b3U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x99cebf8bU), bswap_32big(0xc73e0e3bU), bswap_32big(0x11f2effaU), bswap_32big(0xba191fc4U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x000008c6U);

            WR1_PROG(REG_0094H, 0x00000800U);

            WR1_PROG(REG_0094H, 0x00000842U);

            WR1_PROG(REG_0094H, 0x00000863U);

            r_rsip_func100(bswap_32big(0xf0290472U), bswap_32big(0x9ff95744U), bswap_32big(0x12bf3972U), bswap_32big(0xaeda341fU));
            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003ca7U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x34202880U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0094H, 0x0000a400U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                WR1_PROG(REG_0094H, 0x34202801U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                r_rsip_func100(bswap_32big(0x53394a86U), bswap_32big(0x64f23fc7U), bswap_32big(0xd426ae85U), bswap_32big(0xa96a3de1U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func101(bswap_32big(0x7103159aU), bswap_32big(0x569f6e78U), bswap_32big(0x1715601dU), bswap_32big(0x59512b03U));
                }
                else
                {
                    WR1_PROG(REG_0094H, 0x0000b4e0U);
                    WR1_PROG(REG_0094H, 0x00000018U);
                    WR1_PROG(REG_0094H, 0x00003c47U);

                    WR1_PROG(REG_0094H, 0x0000b4e0U);
                    WR1_PROG(REG_0094H, 0x0000001cU);
                    WR1_PROG(REG_0094H, 0x00003cc7U);

                    WR1_PROG(REG_0014H, 0x000000c7U);
                    WR1_PROG(REG_009CH, 0x800100c0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, InData_KDFInfo[iLoop * 13]);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0014H, 0x000000a7U);
                    WR1_PROG(REG_009CH, 0x800100e0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x4d60e0ccU), bswap_32big(0x0cd67874U), bswap_32big(0xe254189eU), bswap_32big(0x8ff6cb17U));
                    r_rsip_func043();

                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x01799093U);

                    WR1_PROG(REG_0014H, 0x000000a7U);
                    WR1_PROG(REG_009CH, 0x800100e0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0xf4c08e43U), bswap_32big(0x318d95b2U), bswap_32big(0xd1e6f2d7U), bswap_32big(0x4135e1e3U));
                    r_rsip_func044();

                    WR1_PROG(REG_0094H, 0x38000c63U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    r_rsip_func100(bswap_32big(0x760f25b8U), bswap_32big(0x2d1e4780U), bswap_32big(0xc2f55ca6U), bswap_32big(0x44ae6a4eU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B0H, 0x00001404U);

                        r_rsip_func101(bswap_32big(0xc2c1d9b9U), bswap_32big(0x387a7e59U), bswap_32big(0x2bf55b95U), bswap_32big(0x19d56ec8U));
                    }
                    else
                    {
                        WR1_PROG(REG_00B0H, 0x00001408U);

                        r_rsip_func101(bswap_32big(0x68ce6d75U), bswap_32big(0x3bbdd06fU), bswap_32big(0x9a333aa0U), bswap_32big(0x97bda50dU));
                    }

                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000044U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000054U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_0014H, 0x000007c1U);
                    WR1_PROG(REG_00D4H, 0x40000100U);
                    WR1_PROG(REG_00D0H, 0xf7008d07U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 1]);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 5]);

                    WR1_PROG(REG_0000H, 0x00c10021U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x00002c60U);

                    WR1_PROG(REG_0094H, 0x0000b4e0U);
                    WR1_PROG(REG_0094H, 0x00000018U);
                    WR1_PROG(REG_0094H, 0x00003847U);

                    WR1_PROG(REG_0094H, 0x0000b4e0U);
                    WR1_PROG(REG_0094H, 0x0000001cU);
                    WR1_PROG(REG_0094H, 0x000038c7U);

                    WR1_PROG(REG_0014H, 0x000003c1U);
                    WR1_PROG(REG_00D4H, 0x40000000U);
                    WR1_PROG(REG_00D0H, 0x07008d05U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 9]);

                    WR1_PROG(REG_00D0H, 0x9c100005U);
                    WR1_PROG(REG_0000H, 0x00410011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func100(bswap_32big(0x0df102a4U), bswap_32big(0xe26020ceU), bswap_32big(0x4c02d3a9U), bswap_32big(0xdcce7c9aU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000d040U);
                        r_rsip_func101(bswap_32big(0x5f124310U), bswap_32big(0x15de0e46U), bswap_32big(0xf828f69cU), bswap_32big(0x98e30fd9U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x8f26ae97U), bswap_32big(0xd952a7abU), bswap_32big(0x60d8465eU), bswap_32big(0x828732f6U));
                    }
                }

                WR1_PROG(REG_0094H, 0x00002c00U);

                WR1_PROG(REG_0094H, 0x00002cc0U);

                r_rsip_func101(bswap_32big(0x1e3eb30dU), bswap_32big(0xe33f2eaeU), bswap_32big(0xc51827a1U), bswap_32big(0xaef949cdU));
            }

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003807U);

            WR1_PROG(REG_0094H, 0x380008c0U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);
            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x38000c42U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);
            r_rsip_func100(bswap_32big(0x05d9184dU), bswap_32big(0x5a5d455eU), bswap_32big(0xf473ef91U), bswap_32big(0x6a60a711U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa7623a25U), bswap_32big(0x8b353fd5U), bswap_32big(0x3626c7f8U), bswap_32big(0xebe92818U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x6e3390c6U), bswap_32big(0x16b03663U), bswap_32big(0x8a964c98U), bswap_32big(0xc9c03e28U));
                r_rsip_func103();

                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c200104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_009CH, 0x80010000U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x0001000dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x000034c0U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x7e5d1b30U), bswap_32big(0xaae92fccU), bswap_32big(0x939a14e0U), bswap_32big(0xcebe2ed0U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_0094H, 0x00003847U);

                r_rsip_func100(bswap_32big(0x073cc0d7U), bswap_32big(0x7e727945U), bswap_32big(0xd4687191U), bswap_32big(0x93034af1U));
                WR1_PROG(REG_0094H, 0x00007c02U);
                WR1_PROG(REG_0040H, 0x00600000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000005U);

                    r_rsip_func101(bswap_32big(0x99c5e711U), bswap_32big(0xca9bdb0eU), bswap_32big(0x4243703cU), bswap_32big(0xd37d10e8U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000007U);

                    r_rsip_func101(bswap_32big(0xe9cf1961U), bswap_32big(0x4637165dU), bswap_32big(0x15ac5397U), bswap_32big(0xab219046U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0199e556U);

                    r_rsip_func101(bswap_32big(0x6708712dU), bswap_32big(0x094472a7U), bswap_32big(0x581a3827U), bswap_32big(0x167e9108U));
                }

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xb2838e5fU), bswap_32big(0x7ddef38eU), bswap_32big(0x32f21c1aU), bswap_32big(0xc0d33dcdU));
                r_rsip_func044();

                WR1_PROG(REG_0094H, 0x00008c20U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x38008860U);
                WR1_PROG(REG_0094H, 0x00000001U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                r_rsip_func100(bswap_32big(0x51b794c7U), bswap_32big(0x9c85fe03U), bswap_32big(0x66eb37a1U), bswap_32big(0xd60a4d3bU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000020U);
                    WR1_PROG(REG_00B0H, 0x00001804U);

                    r_rsip_func101(bswap_32big(0x8a0741e6U), bswap_32big(0x83843246U), bswap_32big(0x36041072U), bswap_32big(0x17bcd42cU));
                }
                else
                {
                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000040U);
                    WR1_PROG(REG_00B0H, 0x00003808U);

                    r_rsip_func101(bswap_32big(0x86fc0914U), bswap_32big(0x8c19584bU), bswap_32big(0xa76de44bU), bswap_32big(0xaa52932aU));
                }

                r_rsip_func100(bswap_32big(0xd2e3eddcU), bswap_32big(0xd1491349U), bswap_32big(0xb8834944U), bswap_32big(0xd146fcc7U));
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

                    WR1_PROG(REG_0094H, 0x3420a8e0U);
                    WR1_PROG(REG_0094H, 0x00000020U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xd616a99cU), bswap_32big(0xee776c24U), bswap_32big(0x19791fe6U), bswap_32big(0xeaf143eeU));
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

                        r_rsip_func101(bswap_32big(0xee4eb7abU), bswap_32big(0xa029b9d6U), bswap_32big(0x51d34a7bU), bswap_32big(0xb235c07fU));
                    }
                    else
                    {
                        WR1_PROG(REG_009CH, 0x800100c0U);
                        WR1_PROG(REG_0000H, 0x1340000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x13430005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x02003cc7U);

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0x8b083f32U), bswap_32big(0xbe550ebaU), bswap_32big(0x21f31c86U), bswap_32big(0x98fffd3cU));
                    }

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xbb203d3fU), bswap_32big(0x168b8066U), bswap_32big(0x0fd3877eU), bswap_32big(0x4750a2d2U));
                }

                WR1_PROG(REG_0094H, 0x380008a4U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x3420a840U);
                WR1_PROG(REG_0094H, 0x00000002U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                r_rsip_func100(bswap_32big(0x09ea0d90U), bswap_32big(0xc2759f7cU), bswap_32big(0x1e737daeU), bswap_32big(0xc66675f8U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x38000c42U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    r_rsip_func100(bswap_32big(0xd7d82226U), bswap_32big(0x35716785U), bswap_32big(0xe16e59b9U), bswap_32big(0xfdbe682aU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x8069ac5aU), bswap_32big(0x5af201e6U), bswap_32big(0xbf393810U), bswap_32big(0x67a8b293U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        WR1_PROG(REG_009CH, 0x81840007U);
                        WR1_PROG(REG_0000H, 0x00490011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0x83be8878U), bswap_32big(0xe91559c6U), bswap_32big(0x280dafe4U), bswap_32big(0x278d93c0U));
                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x0c000104U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0x09108105U);
                        WR1_PROG(REG_0000H, 0x00410011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func101(bswap_32big(0x13a25e80U), bswap_32big(0x16caa0e6U), bswap_32big(0x4a9a81aaU), bswap_32big(0xbfc37d6eU));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x0be92dc2U), bswap_32big(0x6184d31fU), bswap_32big(0x4afecabfU), bswap_32big(0xdca9fd83U));
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xe7009d07U);

                        WR1_PROG(REG_009CH, 0x81880007U);
                        WR1_PROG(REG_0000H, 0x00490021U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001022U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x44ccc008U), bswap_32big(0x682fb7abU), bswap_32big(0xd6862dd9U), bswap_32big(0x2cb7c7a1U));
                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x0c000104U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0x09108105U);
                        WR1_PROG(REG_0000H, 0x00410011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

                        r_rsip_func101(bswap_32big(0x76c83d11U), bswap_32big(0x65beced1U), bswap_32big(0x26eac509U), bswap_32big(0xe214e2c1U));
                    }

                    r_rsip_func100(bswap_32big(0x20f39bcbU), bswap_32big(0xbbf1ffe7U), bswap_32big(0x636ac79eU), bswap_32big(0xe0b48692U));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x3efb1c6bU), bswap_32big(0x90307becU), bswap_32big(0x424f984fU), bswap_32big(0xe1e2d288U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xf08ef7d1U), bswap_32big(0xe20dccddU), bswap_32big(0x9e085a66U), bswap_32big(0x6641cde2U));
                    WR1_PROG(REG_00D4H, 0x40000000U);
                    WR1_PROG(REG_00D0H, 0xe7009d05U);

                    WR1_PROG(REG_009CH, 0x81840007U);
                    WR1_PROG(REG_0000H, 0x00490011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0008H, 0x00001012U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_EncIV[1]);

                    r_rsip_func100(bswap_32big(0xa6305c5cU), bswap_32big(0x46d9f79eU), bswap_32big(0x6b41ebb8U), bswap_32big(0xf42c6536U));
                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x0c000104U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_00D4H, 0x40000000U);
                    WR1_PROG(REG_00D0H, 0x09108105U);
                    WR1_PROG(REG_0000H, 0x00410011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0008H, 0x00001012U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_EncIV[5]);

                    r_rsip_func100(bswap_32big(0x04e8576fU), bswap_32big(0xd1c0f088U), bswap_32big(0x6c2381a6U), bswap_32big(0xf7c2aa66U));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_EncIV[0]);

                    r_rsip_func102(bswap_32big(0x01277eb5U), bswap_32big(0x87fcd470U), bswap_32big(0x440ada29U), bswap_32big(0xd668ec9cU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
