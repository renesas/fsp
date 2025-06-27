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

rsip_ret_t r_rsip_p31 (const uint32_t InData_HashType[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       uint32_t       OutData_MsgDigest[],
                       uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00310001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x62385557U),
                   bswap_32big(0x7a5628aeU),
                   bswap_32big(0x9a99514fU),
                   bswap_32big(0xdda38601U));
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x22109c28U), bswap_32big(0xba4ec560U), bswap_32big(0x3e908923U),
                       bswap_32big(0xba558af6U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00000040U);

        r_rsip_func101(bswap_32big(0x503d0fa1U), bswap_32big(0x25eec85eU), bswap_32big(0x24ca0eb6U),
                       bswap_32big(0xff93da2bU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        r_rsip_func101(bswap_32big(0xed233fc0U), bswap_32big(0x04ac4f07U), bswap_32big(0xaf05aa05U),
                       bswap_32big(0x11f1cd93U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00000080U);

        r_rsip_func101(bswap_32big(0x4e55f287U), bswap_32big(0x7706d006U), bswap_32big(0x9fe1d6d2U),
                       bswap_32big(0x52d55e94U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00000090U);

        r_rsip_func101(bswap_32big(0xdd6fcefbU), bswap_32big(0x37de5497U), bswap_32big(0xcb784168U),
                       bswap_32big(0xc229c60eU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        r_rsip_func101(bswap_32big(0xa38edc66U), bswap_32big(0x349759a9U), bswap_32big(0x0c42227eU),
                       bswap_32big(0x1308c0dfU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        r_rsip_func101(bswap_32big(0xfa515800U), bswap_32big(0x88647384U), bswap_32big(0xedd52300U),
                       bswap_32big(0xa8324a51U));
    }

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_200CH, 0x00000100U);

        r_rsip_func101(bswap_32big(0x3ec2055bU), bswap_32big(0x723c11deU), bswap_32big(0xfe0ad62fU),
                       bswap_32big(0x8aa8325eU));
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_MsgLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_MsgLen[1]);

        r_rsip_func101(bswap_32big(0x619997b2U), bswap_32big(0x57979dc8U), bswap_32big(0xfeec98aeU),
                       bswap_32big(0x7d85637cU));
    }

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);

        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);

    WAIT_STS(REG_2030H, 4, 1);

    r_rsip_func100(bswap_32big(0x11df1a6fU),
                   bswap_32big(0x4c46acd1U),
                   bswap_32big(0xafc5fc80U),
                   bswap_32big(0x180ad28dU));
    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000001U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func100(bswap_32big(0x6904b628U), bswap_32big(0x35695477U), bswap_32big(0xf951a736U),
                       bswap_32big(0x8337e951U));
        WR1_PROG(REG_1408H, 0x00004016U);
        for (iLoop = 0U; iLoop < 5U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func102(bswap_32big(0x31ffd17cU), bswap_32big(0xa28ec340U), bswap_32big(0x1d00b5bbU),
                       bswap_32big(0x82c82642U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func100(bswap_32big(0xc5895cf7U), bswap_32big(0x8acc4e2bU), bswap_32big(0x3d0a0b09U),
                       bswap_32big(0x1a62561bU));
        WR1_PROG(REG_1408H, 0x0000401eU);
        for (iLoop = 0U; iLoop < 7U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func102(bswap_32big(0xd82a2cc0U), bswap_32big(0xed085186U), bswap_32big(0xd7832099U),
                       bswap_32big(0x6db679cdU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func100(bswap_32big(0x5a0e307dU), bswap_32big(0xbf037881U), bswap_32big(0xe53a0ed6U),
                       bswap_32big(0x981ed136U));
        WR1_PROG(REG_1408H, 0x00004022U);
        for (iLoop = 0U; iLoop < 8U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func102(bswap_32big(0xa836b017U), bswap_32big(0x4bd4cd31U), bswap_32big(0xfe9e745dU),
                       bswap_32big(0xd3f256f2U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        r_rsip_func100(bswap_32big(0x8e5b2e04U), bswap_32big(0x8ee752c5U), bswap_32big(0x57ca9f51U),
                       bswap_32big(0x44a7024dU));
        WR1_PROG(REG_1408H, 0x00004032U);
        for (iLoop = 0U; iLoop < 12U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func102(bswap_32big(0x00266d6eU), bswap_32big(0x072e737aU), bswap_32big(0xacfb1600U),
                       bswap_32big(0x052ca8e4U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        r_rsip_func100(bswap_32big(0xa012e3ecU), bswap_32big(0x015b0f14U), bswap_32big(0xe15eb65fU),
                       bswap_32big(0xe65ff9f0U));
        WR1_PROG(REG_1408H, 0x00004042U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func102(bswap_32big(0x0d4bc92fU), bswap_32big(0x8be7f79cU), bswap_32big(0x9a678cfbU),
                       bswap_32big(0x9ac5dd79U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }

    return RSIP_RET_PASS;
}
