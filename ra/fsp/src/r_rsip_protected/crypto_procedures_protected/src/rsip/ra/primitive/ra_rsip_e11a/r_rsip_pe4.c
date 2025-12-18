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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e40001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub002(0x800100e0U, 0x000000e4U);

    r_rsip_func101(bswap_32big(0x8d07f53dU),
                   bswap_32big(0x0440de5eU),
                   bswap_32big(0x0e73661aU),
                   bswap_32big(0x8f20f1a0U));
    r_rsip_func407(InData_EncSecret);

    r_rsip_func100(bswap_32big(0x89e3059dU),
                   bswap_32big(0x566ab4d5U),
                   bswap_32big(0x3a382b82U),
                   bswap_32big(0xc4c94cc4U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc835b5cfU), bswap_32big(0x76de5ff7U), bswap_32big(0x3f0442beU),
                       bswap_32big(0x7a6afcf5U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xb891ad3eU), bswap_32big(0x51a5c561U), bswap_32big(0xb9b865f7U),
                       bswap_32big(0xba82933cU));
        r_rsip_func103();

        r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);

        r_rsip_func_sub003(0x80010000U, 0x03410005U);
        r_rsip_func_sub009(0x0001000dU, 0x000034c0U);

        r_rsip_func_sub002(0x800100e0U, 0x000000e4U);

        r_rsip_func101(bswap_32big(0x7a09292fU), bswap_32big(0x176ab02fU), bswap_32big(0x424a87c2U),
                       bswap_32big(0x8a918ffeU));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x01b41ce9U);

        r_rsip_func_sub002(0x800100e0U, 0x000000e4U);

        r_rsip_func101(bswap_32big(0x927b287cU), bswap_32big(0xf7b02168U), bswap_32big(0x234124ccU),
                       bswap_32big(0x66584a5fU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0xb772de1cU), bswap_32big(0x53bbd847U), bswap_32big(0x82028872U),
                       bswap_32big(0x2601725eU));

        WR1_PROG(REG_00B0H, 0x00001804U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        r_rsip_func_sub006(0xe7009d07U, 0x00430021U);

        WR1_PROG(REG_0008H, 0x00001022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

        r_rsip_func100(bswap_32big(0xc950767bU), bswap_32big(0x49c9bbaeU), bswap_32big(0xf67cf923U),
                       bswap_32big(0x38fe2f1aU));
        WR1_PROG(REG_00D4H, 0x40000100U);
        r_rsip_func_sub006(0xe7008d07U, 0x00400021U);

        WR1_PROG(REG_0008H, 0x00001022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

        r_rsip_func100(bswap_32big(0x814cf397U), bswap_32big(0x4ddefea6U), bswap_32big(0x9f2431f0U),
                       bswap_32big(0x951bddb7U));
        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func_sub006(0x09108105U, 0x00410011U);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

        r_rsip_func100(bswap_32big(0xbd489ce6U), bswap_32big(0xe6d079dfU), bswap_32big(0x673907b3U),
                       bswap_32big(0xdbd216acU));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

        r_rsip_func102(bswap_32big(0x40dfd160U), bswap_32big(0x2f3be525U), bswap_32big(0x745d9985U),
                       bswap_32big(0xf001f9ecU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
