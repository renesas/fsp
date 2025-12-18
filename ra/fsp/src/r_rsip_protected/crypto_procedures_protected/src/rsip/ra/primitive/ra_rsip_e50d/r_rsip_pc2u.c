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

void r_rsip_pc2u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    r_rsip_func100(bswap_32big(0xf47101f4U),
                   bswap_32big(0x0ff7ba4fU),
                   bswap_32big(0xefcd3648U),
                   bswap_32big(0x83117d31U));

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x40000020U);
    WR1_PROG(REG_1824H, 0x0d00890eU);
    WR1_PROG(REG_1408H, 0x000c1000U);

    r_rsip_func220(InData_Text, MAX_CNT, OutData_Text);

    r_rsip_func101(bswap_32big(0x9e894a56U),
                   bswap_32big(0x31fcbe81U),
                   bswap_32big(0xab8a8887U),
                   bswap_32big(0x40634befU));
}
