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

void r_rsip_pb3u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    r_rsip_func100(bswap_32big(0x02fa6705U),
                   bswap_32big(0x5ab474d0U),
                   bswap_32big(0xe09d1923U),
                   bswap_32big(0x618d45f9U));

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00000020U);
    WR1_PROG(REG_1824H, 0x0d008906U);
    WR1_PROG(REG_1408H, 0x000c1000U);

    r_rsip_func220(InData_Text, MAX_CNT, OutData_Text);

    r_rsip_func101(bswap_32big(0x22ae9ffcU),
                   bswap_32big(0x3b8baaedU),
                   bswap_32big(0x46803757U),
                   bswap_32big(0x837ed581U));
}
