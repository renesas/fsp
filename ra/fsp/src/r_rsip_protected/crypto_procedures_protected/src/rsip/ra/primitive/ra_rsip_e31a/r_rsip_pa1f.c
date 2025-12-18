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

rsip_ret_t r_rsip_pa1f (const uint32_t InData_Text[],
                        const uint32_t InData_TextLen[],
                        uint32_t       OutData_Text[],
                        uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    r_rsip_func_sub018(0x00000000U, 0x00008c00U, 0x0000000fU);

    r_rsip_func_sub010(0x38008800U, 0x00000000U, 0x00A70000U);

    r_rsip_func100(bswap_32big(0xd5398d84U),
                   bswap_32big(0xde6518eaU),
                   bswap_32big(0x6a59ebf4U),
                   bswap_32big(0x5753fe3dU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xe7008d05U);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0094H, 0x00000821U);
        r_rsip_func_sub006(0x80840001U, 0x03410011U, 0x00000821U, 0x000008a5U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            r_rsip_func_sub022(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
        }

        r_rsip_func100(bswap_32big(0x03cbaf0cU), bswap_32big(0xf782ec0aU), bswap_32big(0x5eb21a61U),
                       bswap_32big(0xe38fd213U));
        WR1_PROG(REG_0094H, 0x00000821U);
        r_rsip_func_sub017(0x81840001U, 0x00005012U);
        RD1_ADDR(REG_002CH, &OutData_Text[0]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[2]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[3]);

        r_rsip_func101(bswap_32big(0x7a42f57aU), bswap_32big(0x5f19726fU), bswap_32big(0x5fa537e1U),
                       bswap_32big(0x83caf6faU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0xfbc5b175U), bswap_32big(0x712cfc1aU), bswap_32big(0xc511415cU),
                       bswap_32big(0x21ddb983U));
    }

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func100(bswap_32big(0xa7568753U),
                   bswap_32big(0x2f36734fU),
                   bswap_32big(0xe57775e9U),
                   bswap_32big(0x975d8741U));
    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_MAC[0]);

    r_rsip_func102(bswap_32big(0x031a30b6U),
                   bswap_32big(0xae2e2895U),
                   bswap_32big(0x077823c8U),
                   bswap_32big(0xe995d025U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
