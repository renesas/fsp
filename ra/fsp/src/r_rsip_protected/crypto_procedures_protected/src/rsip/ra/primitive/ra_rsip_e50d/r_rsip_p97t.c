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

void r_rsip_p97t (void)
{
    r_rsip_func100(bswap_32big(0x85ab01ceU),
                   bswap_32big(0xf5845f81U),
                   bswap_32big(0x0574070bU),
                   bswap_32big(0x07d1c4f3U));
    WR1_PROG(REG_1600H, 0x0000b440U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    r_rsip_func101(bswap_32big(0x2c26ad81U),
                   bswap_32big(0x82c64639U),
                   bswap_32big(0xf6ecc569U),
                   bswap_32big(0x26e94211U));
}
