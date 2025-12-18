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

rsip_ret_t r_rsip_p76i (const uint32_t InData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00760001U, 0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x800100e0U, 0x00000076U);

    r_rsip_func101(bswap_32big(0x4a4df99fU),
                   bswap_32big(0xe5be2dd4U),
                   bswap_32big(0x506822f0U),
                   bswap_32big(0x9ea1d1b9U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001bU);

    r_rsip_func_sub002(0x800100e0U, 0x00000076U);

    r_rsip_func101(bswap_32big(0xc12326b5U),
                   bswap_32big(0x06b2e098U),
                   bswap_32big(0x76b3ad4eU),
                   bswap_32big(0x3b6b4407U));
    r_rsip_func044();

    r_rsip_func_sub008(0x000007c1U, 0x40000100U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    r_rsip_func_sub004(0x00001404U, 0x00c10021U);

    r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub006(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0xae7681d1U),
                   bswap_32big(0x6ab0e43aU),
                   bswap_32big(0x493183cfU),
                   bswap_32big(0x39378d37U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xbfe89678U), bswap_32big(0xfe583687U), bswap_32big(0xf7a8a8c6U),
                       bswap_32big(0x9ffd0c01U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_00F4H, 0x00000010U);

        WR1_PROG(REG_0014H, 0x000007a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_PROG(REG_002CH,
                 bswap_32big(0x6a09e667U),
                 bswap_32big(0xbb67ae85U),
                 bswap_32big(0x3c6ef372U),
                 bswap_32big(0xa54ff53aU),
                 bswap_32big(0x510e527fU),
                 bswap_32big(0x9b05688cU),
                 bswap_32big(0x1f83d9abU),
                 bswap_32big(0x5be0cd19U));

        WR1_PROG(REG_00F4H, 0x00000011U);

        r_rsip_func001();

        r_rsip_func101(bswap_32big(0x9afb12a6U), bswap_32big(0xc892b828U), bswap_32big(0xed5aca13U),
                       bswap_32big(0x7df5aa47U));

        return RSIP_RET_PASS;
    }
}
