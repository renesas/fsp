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

void r_rsip_pb6u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    r_rsip_func100(bswap_32big(0x8b28d618U),
                   bswap_32big(0xca3e7296U),
                   bswap_32big(0x8b02a1cfU),
                   bswap_32big(0x48458921U));

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00000020U);
    WR1_PROG(REG_1824H, 0x0d00890eU);
    WR1_PROG(REG_1408H, 0x000c1000U);

    r_rsip_func220(InData_Text, MAX_CNT, OutData_Text);

    r_rsip_func101(bswap_32big(0x58211f97U),
                   bswap_32big(0x044b49b0U),
                   bswap_32big(0x4c29ece3U),
                   bswap_32big(0x2ecf9546U));
}
