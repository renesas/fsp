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

rsip_ret_t r_rsip_p76s (uint32_t OutData_State[])
{
    WR1_PROG(REG_00F4H, 0x00000100U);

    r_rsip_func100(bswap_32big(0x4fd152c1U), bswap_32big(0x94c11b9fU), bswap_32big(0xe1c36a7cU), bswap_32big(0x62432e48U));
    WR1_PROG(REG_00F4H, 0x00000020U);

    WR1_PROG(REG_0008H, 0x00004022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD8_ADDR(REG_002CH, &OutData_State[0]);

    r_rsip_func102(bswap_32big(0xa22f2beaU), bswap_32big(0xe2010f54U), bswap_32big(0x470fadb4U), bswap_32big(0xef673c85U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
