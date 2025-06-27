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

rsip_ret_t r_rsip_pefu (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000002c7U);
    WR1_PROG(REG_009CH, 0x80030060U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg1Length[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg2Length[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38008c60U);
    WR1_PROG(REG_0094H, 0xfffffffeU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_0094H, 0x00002423U);
    WR1_PROG(REG_0094H, 0x00002424U);
    WR1_PROG(REG_0094H, 0x00002425U);

    r_rsip_func100(bswap_32big(0xff64a057U),
                   bswap_32big(0x86cee4b4U),
                   bswap_32big(0xc91b36fdU),
                   bswap_32big(0x0a6f1e13U));
    WR1_PROG(REG_0094H, 0x00007c00U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0094H, 0x38008c80U);
        WR1_PROG(REG_0094H, 0xfffffff7U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        WR1_PROG(REG_0094H, 0x38008c20U);
        WR1_PROG(REG_0094H, 0x0000000fU);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func101(bswap_32big(0xe6bfbc10U), bswap_32big(0xaaceb13eU), bswap_32big(0x807481a9U),
                       bswap_32big(0xbd688306U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0094H, 0x38008c80U);
        WR1_PROG(REG_0094H, 0xfffffff3U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        WR1_PROG(REG_0094H, 0x38008c20U);
        WR1_PROG(REG_0094H, 0x0000001fU);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func101(bswap_32big(0xdac1d33dU), bswap_32big(0x286928afU), bswap_32big(0x544cd454U),
                       bswap_32big(0xe5d49026U));
    }

    r_rsip_func100(bswap_32big(0xa8f4fd74U),
                   bswap_32big(0xc4156e06U),
                   bswap_32big(0xd26d034bU),
                   bswap_32big(0x497b9f2dU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x1c728a35U), bswap_32big(0x0ed0200dU), bswap_32big(0xb2840e39U),
                       bswap_32big(0x1218f1b4U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00000821U);

        WR1_PROG(REG_0094H, 0x00003405U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x0fc045faU), bswap_32big(0x7a6dc5afU), bswap_32big(0xc2fee67cU),
                       bswap_32big(0x8555fb20U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x7fdbd792U), bswap_32big(0x7995ae49U), bswap_32big(0xcb0754b2U),
                           bswap_32big(0x5f422355U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x898ed2e3U), bswap_32big(0xd8ca91a9U), bswap_32big(0xde8de765U),
                           bswap_32big(0x2ca1bda2U));
            r_rsip_func044();

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000010U);
            WR1_PROG(REG_0094H, 0x000038a7U);

            r_rsip_func100(bswap_32big(0x5ba315c3U), bswap_32big(0x75c9cb7eU), bswap_32big(0xc285b798U),
                           bswap_32big(0xb17097c5U));

            WR1_PROG(REG_0094H, 0x00007c05U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_0014H, 0x000007c1U);
                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xf7009d07U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1]);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[5]);

                WR1_PROG(REG_00B0H, 0x00001404U);
                WR1_PROG(REG_0000H, 0x00c10021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0x07008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[9]);

                r_rsip_func101(bswap_32big(0x5879596dU),
                               bswap_32big(0x7a14b289U),
                               bswap_32big(0x63ee6ccaU),
                               bswap_32big(0x2b4597d3U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_0014H, 0x00000bc1U);
                WR1_PROG(REG_00D4H, 0x40000200U);
                WR1_PROG(REG_00D0H, 0xf7009d07U);

                for (iLoop = 0U; iLoop < 12U; )
                {
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_00B0H, 0x00009406U);
                WR1_PROG(REG_0000H, 0x00c10031U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0x07008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[13]);

                r_rsip_func101(bswap_32big(0x6462a0ffU),
                               bswap_32big(0x990c96e0U),
                               bswap_32big(0x1f9b5fb6U),
                               bswap_32big(0x5693cc1eU));
            }

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0xbe051680U), bswap_32big(0xde1852e3U), bswap_32big(0x687cba5cU),
                           bswap_32big(0x2d76f1d1U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0xfe8ad779U),
                               bswap_32big(0x775a13e6U),
                               bswap_32big(0x69d5eb3dU),
                               bswap_32big(0x37ad73d8U));
            }

            r_rsip_func101(bswap_32big(0xa0e14f3fU), bswap_32big(0x3fc6cadeU), bswap_32big(0x916cb08aU),
                           bswap_32big(0x1d60ea61U));
        }

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x1c3894f0U), bswap_32big(0x60ebf507U), bswap_32big(0x53d67cc8U),
                       bswap_32big(0x98ff88aeU));
        WR1_PROG(REG_0040H, 0x00400000U);
        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x87d2ca05U), bswap_32big(0xaaadac9bU), bswap_32big(0xd75e727fU),
                           bswap_32big(0xd40fddd3U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WAIT_STS(REG_0118H, 0, 1);

            WR1_PROG(REG_0094H, 0x38000c63U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0x5ffd79f3U), bswap_32big(0xcf727188U), bswap_32big(0x1994d4f1U),
                           bswap_32big(0x3eef3219U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000000c4U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Msg1[0]);

                r_rsip_func101(bswap_32big(0xa6899babU),
                               bswap_32big(0x1986fce4U),
                               bswap_32big(0xb4b4fd5fU),
                               bswap_32big(0x5bbf668aU));
            }

            WR1_PROG(REG_0094H, 0x38000c84U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xc184b10aU), bswap_32big(0x74ce1f80U), bswap_32big(0xe2133660U),
                           bswap_32big(0x9460ba26U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0xfd852830U),
                               bswap_32big(0xa9f2698eU),
                               bswap_32big(0xe8bb0e7fU),
                               bswap_32big(0xaa8b52eaU));

                WR1_PROG(REG_0094H, 0x00007c05U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_00B0H, 0x00001804U);
                    WR1_PROG(REG_0000H, 0x01430021U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x90543b41U),
                                   bswap_32big(0xe3c84065U),
                                   bswap_32big(0xd9191897U),
                                   bswap_32big(0xeca5f567U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_00B0H, 0x00009806U);
                    WR1_PROG(REG_0000H, 0x01430031U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xd8d6628bU),
                                   bswap_32big(0x33fde46dU),
                                   bswap_32big(0x9207c2aeU),
                                   bswap_32big(0x45435ba8U));
                }

                r_rsip_func101(bswap_32big(0xe064237aU),
                               bswap_32big(0x04beadc2U),
                               bswap_32big(0xc8581fddU),
                               bswap_32big(0xdfba7314U));
            }

            r_rsip_func100(bswap_32big(0xd3da2dc2U), bswap_32big(0x99d7c0d2U), bswap_32big(0x95523b18U),
                           bswap_32big(0x72fd7f13U));

            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0014H, 0x00020064U);

            WAIT_STS(REG_0014H, 31, 1);
            for (iLoop = 0; iLoop < (S_RAM[0] & 0x0000000fU); iLoop++)
            {
                WR1_PROG(REG_002CH, InData_Msg2[iLoop]);
            }

            WAIT_STS(REG_0014H, 31, 1);
            for (iLoop = (S_RAM[0] & 0x0000000fU); iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_0014H, 31, 1);
                WR16_ADDR(REG_002CH, &InData_Msg2[iLoop]);
                iLoop = iLoop + 16U;
            }

            WR1_PROG(REG_0014H, 0x00000000U);
            WAIT_STS(REG_0118H, 8, 0);
            WR1_PROG(REG_0040H, 0x00001600U);

            WR1_PROG(REG_0094H, 0x0000b420U);
            WR1_PROG(REG_0094H, 0x00000010U);
            WR1_PROG(REG_0094H, 0x00003801U);

            r_rsip_func101(bswap_32big(0x59dbba41U), bswap_32big(0xacd4abfcU), bswap_32big(0xd91f655eU),
                           bswap_32big(0x78a81ad5U));

            return RSIP_RET_PASS;
        }
    }
}
