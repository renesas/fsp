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

rsip_ret_t r_rsip_p97s (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    if (S_RAM[0] == 1)
    {
        r_rsip_func101(bswap_32big(0x709ca98aU), bswap_32big(0x3857904fU), bswap_32big(0x4029cf76U),
                       bswap_32big(0x7d81fdfdU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0x429bac95U), bswap_32big(0x359d8724U), bswap_32big(0x09e2bd40U),
                       bswap_32big(0x6b2fe609U));
    }

    WAIT_STS(REG_1C30H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001c00U);

    RD1_ADDR(REG_1C08H, &OutData_State[0]);
    RD1_ADDR(REG_1C10H, &OutData_State[1]);
    RD1_ADDR(REG_1C14H, &OutData_State[2]);

    for (iLoop = 3; iLoop < 10U; iLoop++)
    {
        RD1_ADDR(REG_1C2CH, &OutData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x000034e3U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00009704U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xb94bc733U),
                   bswap_32big(0x1af28709U),
                   bswap_32big(0x8250881fU),
                   bswap_32big(0x18af0e05U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0121608eU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00009704U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x2b6148bbU),
                   bswap_32big(0x400812dcU),
                   bswap_32big(0xadb5141aU),
                   bswap_32big(0xc1ccc1c5U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xccd3e966U),
                   bswap_32big(0xae3e4138U),
                   bswap_32big(0x7ecf29b7U),
                   bswap_32big(0xedef180fU));
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xe8009104U);
    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_State[11]);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x1844c0bdU),
                   bswap_32big(0x590636aeU),
                   bswap_32big(0x7663bd1fU),
                   bswap_32big(0x27236122U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_State[12]);

    r_rsip_func100(bswap_32big(0x61dfe978U),
                   bswap_32big(0xeaba36dcU),
                   bswap_32big(0x4ba03829U),
                   bswap_32big(0x266b9a13U));
    WR1_PROG(REG_1608H, 0x81010060U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_State[10]);

    r_rsip_func102(bswap_32big(0xa242dde8U),
                   bswap_32big(0x7a91647dU),
                   bswap_32big(0x2ad4f900U),
                   bswap_32big(0x4c728e65U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
