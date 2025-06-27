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

void r_rsip_p34u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    r_rsip_func100(bswap_32big(0x96d9bcbdU),
                   bswap_32big(0x8aadca48U),
                   bswap_32big(0x82cea6adU),
                   bswap_32big(0xb7b62c80U));

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_182CH, 0x40020020U);
    WR1_PROG(REG_1824H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Text[0]);
    WR1_PROG(REG_1408H, 0x00001012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[0]);

    r_rsip_func100(bswap_32big(0x98e71896U),
                   bswap_32big(0x50db210fU),
                   bswap_32big(0xf4825ac2U),
                   bswap_32big(0x48da729fU));

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x40028020U);
    WR1_PROG(REG_1824H, 0x07008d06U);
    WR1_PROG(REG_1408H, 0x000c1000U);

    if (MAX_CNT >= 8)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[4]);
        for (iLoop = 8; iLoop < MAX_CNT; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
            iLoop = iLoop + 4U;
        }

        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
    }

    r_rsip_func215();

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_182CH, 0x00028000U);
    WR1_PROG(REG_1824H, 0x08008004U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    r_rsip_func101(bswap_32big(0x3909db02U),
                   bswap_32big(0x2fdfa9f5U),
                   bswap_32big(0x004b6dedU),
                   bswap_32big(0xbf673aa5U));
}
