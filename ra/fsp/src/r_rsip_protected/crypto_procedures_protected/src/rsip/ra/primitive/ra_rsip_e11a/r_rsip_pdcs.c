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

rsip_ret_t r_rsip_pdcs (uint32_t OutData_State[])
{
    WR1_PROG(REG_00F4H, 0x00000100U);

    r_rsip_func100(bswap_32big(0x7425e7c6U), bswap_32big(0x3ee9926fU), bswap_32big(0xbe8eb266U), bswap_32big(0x559eacc5U));
    WR1_PROG(REG_00F4H, 0x00000020U);

    WR1_PROG(REG_0008H, 0x00004022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD8_ADDR(REG_002CH, &OutData_State[0]);

    r_rsip_func102(bswap_32big(0x9fcdcbb2U), bswap_32big(0xe4dff52cU), bswap_32big(0x8e11ee54U), bswap_32big(0xb98abea4U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
