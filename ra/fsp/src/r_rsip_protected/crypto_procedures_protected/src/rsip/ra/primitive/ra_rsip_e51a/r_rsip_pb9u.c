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

void r_rsip_pb9u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    r_rsip_func100(bswap_32big(0xa8510faeU),
                   bswap_32big(0x1729f824U),
                   bswap_32big(0xa921e87dU),
                   bswap_32big(0x8dcf578aU));

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x40000020U);
    WR1_PROG(REG_1824H, 0x0d008906U);
    WR1_PROG(REG_1408H, 0x000c1000U);

    r_rsip_func220(InData_Text, MAX_CNT, OutData_Text);

    r_rsip_func101(bswap_32big(0x5d82b68fU),
                   bswap_32big(0x50c018a8U),
                   bswap_32big(0xc8af3e4bU),
                   bswap_32big(0x7397fee7U));
}
