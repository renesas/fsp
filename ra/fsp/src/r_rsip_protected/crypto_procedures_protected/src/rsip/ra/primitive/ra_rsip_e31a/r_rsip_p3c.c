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

rsip_ret_t r_rsip_p3c (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x003c0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x4ef69559U),
                   bswap_32big(0x85ca2e62U),
                   bswap_32big(0xf27b67a3U),
                   bswap_32big(0xe9d5f95bU));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000003cU, 0x00000000U);

    r_rsip_func101(bswap_32big(0x89ef96d7U),
                   bswap_32big(0x07be9d73U),
                   bswap_32big(0x746f34cfU),
                   bswap_32big(0x7af97dcaU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000028U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000003cU, 0x00000000U);

    r_rsip_func101(bswap_32big(0xff1b9d14U),
                   bswap_32big(0xf4760e95U),
                   bswap_32big(0x8d3341a4U),
                   bswap_32big(0xaa3cb6f8U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x8df31b85U),
                   bswap_32big(0xf8e1e54aU),
                   bswap_32big(0xa51f8a94U),
                   bswap_32big(0x2caa8b41U));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x4641d3c6U),
                   bswap_32big(0xe314f910U),
                   bswap_32big(0x48f5efa7U),
                   bswap_32big(0xd8085d56U));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub007(0x00000010U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0xed4e0009U),
                   bswap_32big(0x4b676424U),
                   bswap_32big(0x15e51b7eU),
                   bswap_32big(0x39ae2223U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0x22cd6638U),
                   bswap_32big(0x88b3bbfaU),
                   bswap_32big(0x561818c9U),
                   bswap_32big(0x9a1405e7U));
    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0x767d6265U),
                   bswap_32big(0x001cc2d7U),
                   bswap_32big(0xc7ce0be1U),
                   bswap_32big(0x57381a02U));
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0xe7008d05U);
    r_rsip_func_sub007(0x00000821U, 0x81840001U, 0x00490011U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

    r_rsip_func100(bswap_32big(0x345c4d63U),
                   bswap_32big(0x9fdbf594U),
                   bswap_32big(0xd208bb54U),
                   bswap_32big(0x39218ce3U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

    r_rsip_func100(bswap_32big(0x58ee4957U),
                   bswap_32big(0x00538937U),
                   bswap_32big(0x2cee9bf6U),
                   bswap_32big(0x585f82adU));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0x7737fd95U),
                   bswap_32big(0x0b4cb205U),
                   bswap_32big(0x11f6ae4aU),
                   bswap_32big(0x6a8fd673U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
