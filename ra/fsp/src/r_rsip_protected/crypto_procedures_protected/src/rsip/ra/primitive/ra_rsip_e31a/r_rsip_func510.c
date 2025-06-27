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

void r_rsip_func510 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    WR1_PROG(REG_0094H, 0x00003427U);

    WR1_PROG(REG_0094H, 0x00000800U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c84U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x1d9224a5U),
                   bswap_32big(0xdf5be037U),
                   bswap_32big(0x04fa948fU),
                   bswap_32big(0x602576daU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x08000105U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[0]);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x80840003U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func101(bswap_32big(0xe5554ab4U), bswap_32big(0x9a3d325bU), bswap_32big(0x3b7274bfU),
                       bswap_32big(0x28e9beb7U));
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, ARG2[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f510U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xd14be293U), bswap_32big(0x5d9cf8e6U), bswap_32big(0x07161fafU),
                       bswap_32big(0x4eaa675eU));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x0199e556U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f510U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x697eef91U), bswap_32big(0x3d401850U), bswap_32big(0x2b6a852aU),
                       bswap_32big(0x982e472cU));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[1]);
        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x80840003U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[5]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x6790e94cU), bswap_32big(0xc5774a6fU), bswap_32big(0x8c8009cbU),
                       bswap_32big(0x060ffa0fU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00002c00U);
            r_rsip_func101(bswap_32big(0x2e72eacaU), bswap_32big(0xdaf5de12U), bswap_32big(0xd0b1a32bU),
                           bswap_32big(0x72a816ceU));
        }

        r_rsip_func101(bswap_32big(0x646fb4ecU), bswap_32big(0xc07c7238U), bswap_32big(0x8d886524U),
                       bswap_32big(0x4a7eeffcU));
    }

    WR1_PROG(REG_0094H, 0x000034e1U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
