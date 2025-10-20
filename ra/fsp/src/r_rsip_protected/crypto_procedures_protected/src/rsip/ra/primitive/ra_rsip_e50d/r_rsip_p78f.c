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

rsip_ret_t r_rsip_p78f (const uint32_t InData_Msg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_2440H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020065U);

    for (iLoop = 0U; iLoop < (MAX_CNT - MAX_CNT % S_RAM[0]); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        for (jLoop = 0U; jLoop < S_RAM[0]; )
        {
            WR2_ADDR(REG_1420H, &InData_Msg[iLoop + jLoop]);
            jLoop = jLoop + 2;
        }

        iLoop = iLoop + S_RAM[0];
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT - MAX_CNT % S_RAM[0]); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2440H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001400U);

    WAIT_STS(REG_2440H, 4, 1);

    r_rsip_func100(bswap_32big(0x821d6b06U),
                   bswap_32big(0x5848947aU),
                   bswap_32big(0x5e41f7a2U),
                   bswap_32big(0x10e0f686U));
    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func100(bswap_32big(0x81883187U), bswap_32big(0x51d34f14U), bswap_32big(0xe98fd1a7U),
                       bswap_32big(0x727b8cf7U));
        WR1_PROG(REG_1408H, 0x0000601eU);
        WAIT_STS(REG_1408H, 30, 1);
        RD7_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0xe032ece8U), bswap_32big(0xd7fab98cU), bswap_32big(0xeb863875U),
                       bswap_32big(0xeebb3619U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func100(bswap_32big(0xf599829aU), bswap_32big(0x7697c8a5U), bswap_32big(0x5a729547U),
                       bswap_32big(0x7947ab83U));
        WR1_PROG(REG_1408H, 0x00006022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD8_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0x86ed2579U), bswap_32big(0xda8378a5U), bswap_32big(0x81b51eb8U),
                       bswap_32big(0xc72bcfc8U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func100(bswap_32big(0xcbfdffe6U), bswap_32big(0x0b0b5955U), bswap_32big(0xa1d63f89U),
                       bswap_32big(0x4a6233fdU));
        WR1_PROG(REG_1408H, 0x00006032U);
        WAIT_STS(REG_1408H, 30, 1);
        RD12_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0x4b1f9169U), bswap_32big(0x40ba17e2U), bswap_32big(0x8b807cc9U),
                       bswap_32big(0x81191506U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func100(bswap_32big(0x2bc0e784U), bswap_32big(0xef533ca5U), bswap_32big(0x1800bbcfU),
                       bswap_32big(0x4615151cU));
        WR1_PROG(REG_1408H, 0x00006042U);
        WAIT_STS(REG_1408H, 30, 1);
        RD16_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0xf2e9ffb3U), bswap_32big(0x4ac6cf8dU), bswap_32big(0x3854cdb7U),
                       bswap_32big(0x70b53668U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }

    return RSIP_RET_PASS;
}
