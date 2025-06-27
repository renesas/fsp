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

rsip_ret_t r_rsip_p95f (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1600H, 0x00003409U);

    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1600H, 0x0000000fU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xa11068c4U),
                   bswap_32big(0xb7f332a7U),
                   bswap_32big(0x03f43030U),
                   bswap_32big(0xea88e86bU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xe7000d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[0]);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1400H, 0x03410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000821U);

        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1600H, 0x00000080U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x3c002be0U);
            WR1_PROG(REG_1600H, 0x12003c3fU);
            WR1_PROG(REG_1600H, 0x00002fe0U);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x148f2f03U), bswap_32big(0xdc09a971U), bswap_32big(0xc435d56cU),
                       bswap_32big(0x68310accU));
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x81840001U);
        WR1_PROG(REG_1408H, 0x00005012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[0]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[1]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[2]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[3]);

        r_rsip_func101(bswap_32big(0xd7c1f698U), bswap_32big(0x6eaca583U), bswap_32big(0xd7e2bf25U),
                       bswap_32big(0x3406b295U));
    }
    else
    {
        r_rsip_func101(bswap_32big(0x38cd3bbbU), bswap_32big(0xb23c38edU), bswap_32big(0x471a3732U),
                       bswap_32big(0xc71c9a20U));
    }

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0x2f193d6dU),
                   bswap_32big(0x226cd42cU),
                   bswap_32big(0x6d345a31U),
                   bswap_32big(0x8bfec233U));
    WR1_PROG(REG_1824H, 0x09100105U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00001012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_MAC[0]);

    r_rsip_func102(bswap_32big(0x8e0070bbU),
                   bswap_32big(0x5db79a38U),
                   bswap_32big(0x8a809e10U),
                   bswap_32big(0x1b8591a0U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
