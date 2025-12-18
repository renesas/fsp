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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func410 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0094H, 0x00003407U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f410U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfb2a778aU),
                   bswap_32big(0x44ba8bf7U),
                   bswap_32big(0x9180ca08U),
                   bswap_32big(0x0ecae93eU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0165e3d8U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f410U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5f2466b6U),
                   bswap_32big(0xcdb1c67bU),
                   bswap_32big(0x02df3cd2U),
                   bswap_32big(0x88e350a4U));
    r_rsip_func044();

    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);
    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    WR1_PROG(REG_0014H, 0x00000bc1U);
    WR1_PROG(REG_00D4H, 0x40000200U);
    WR1_PROG(REG_00D0H, 0xf7009d07U);

    for (iLoop = 0U; iLoop < 12U; )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG1[1 + iLoop]);
        iLoop = iLoop + 4U;
    }

    r_rsip_func_sub009(0x00009406U, 0x00c10031U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &ARG1[13]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    WR1_PROG(REG_0094H, 0x000034e0U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
