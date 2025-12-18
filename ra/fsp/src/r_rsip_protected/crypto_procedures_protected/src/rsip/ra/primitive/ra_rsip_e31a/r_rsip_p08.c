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

rsip_ret_t r_rsip_p08 (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00080001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xd16938ceU),
                   bswap_32big(0x5dfcd16eU),
                   bswap_32big(0x509e2aedU),
                   bswap_32big(0x803c540eU));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000008U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x281b3967U),
                   bswap_32big(0x94521e99U),
                   bswap_32big(0xe72a67ceU),
                   bswap_32big(0xb4bb74e5U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000008U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x3aea01fdU),
                   bswap_32big(0x1fd51c63U),
                   bswap_32big(0x5cad371dU),
                   bswap_32big(0x90f40caaU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x952eb2d9U),
                   bswap_32big(0x0a1519c4U),
                   bswap_32big(0xe2f91525U),
                   bswap_32big(0xf5e9246bU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x17733831U),
                   bswap_32big(0x41a114b5U),
                   bswap_32big(0xb7ae27e0U),
                   bswap_32big(0x1fa9abaeU));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub007(0x00000010U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0x21142020U),
                   bswap_32big(0x75bab68fU),
                   bswap_32big(0x393cf859U),
                   bswap_32big(0xfad691f5U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0x140ae4edU),
                   bswap_32big(0x5d59d18cU),
                   bswap_32big(0x2fc73021U),
                   bswap_32big(0x29cfe08aU));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

    r_rsip_func100(bswap_32big(0xa52f3d1eU),
                   bswap_32big(0xd0dbe76bU),
                   bswap_32big(0x4f51f28fU),
                   bswap_32big(0x88504f0aU));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0xc2f4bc7eU),
                   bswap_32big(0x9112a131U),
                   bswap_32big(0x15828bafU),
                   bswap_32big(0xfece625cU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
