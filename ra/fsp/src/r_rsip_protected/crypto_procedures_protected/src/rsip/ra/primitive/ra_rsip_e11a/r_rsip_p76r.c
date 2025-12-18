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

rsip_ret_t r_rsip_p76r (const uint32_t InData_KeyIndex[], const uint32_t InData_State[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00760001U, 0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x800100e0U, 0x00007602U);

    r_rsip_func101(bswap_32big(0xf41d1960U),
                   bswap_32big(0xe4e676e5U),
                   bswap_32big(0x7d924e82U),
                   bswap_32big(0xae270e0fU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001bU);

    r_rsip_func_sub002(0x800100e0U, 0x00007602U);

    r_rsip_func101(bswap_32big(0xbfd5e979U),
                   bswap_32big(0xa990b2f5U),
                   bswap_32big(0x0b13610bU),
                   bswap_32big(0xf3bedf4fU));
    r_rsip_func044();

    r_rsip_func_sub008(0x000007c1U, 0x40000100U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    r_rsip_func_sub004(0x00001404U, 0x00c10021U);

    r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub006(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x43c51bc2U),
                   bswap_32big(0x205ecb98U),
                   bswap_32big(0x60e17ac2U),
                   bswap_32big(0x1e078cf2U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xcd0dd564U), bswap_32big(0x27eae833U), bswap_32big(0xab6fd1dfU),
                       bswap_32big(0x47ffe4c5U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_00F4H, 0x00000010U);

        WR1_PROG(REG_0014H, 0x000007c4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_State[0]);

        WR1_PROG(REG_00F4H, 0x00000011U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        r_rsip_func_sub004(0x00001804U, 0x00430011U);

        r_rsip_func_sub006(0x08000055U, 0x00430011U);

        r_rsip_func101(bswap_32big(0x0b1fa522U), bswap_32big(0x3c76590bU), bswap_32big(0x78cf6a43U),
                       bswap_32big(0xaf7620f6U));

        return RSIP_RET_PASS;
    }
}
