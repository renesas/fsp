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

rsip_ret_t r_rsip_p20 (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00200002U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xb5872699U),
                   bswap_32big(0x04c4b7a3U),
                   bswap_32big(0x9aa94383U),
                   bswap_32big(0x4948df89U));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xd77aa3ffU),
                   bswap_32big(0x0a28af6bU),
                   bswap_32big(0xc9340a15U),
                   bswap_32big(0xdb080f5bU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[0]);

    r_rsip_func102(bswap_32big(0x2e84a8e2U),
                   bswap_32big(0x6c78b6b7U),
                   bswap_32big(0x08b8b98fU),
                   bswap_32big(0xd5d8ba69U));

    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
