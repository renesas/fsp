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

    r_rsip_func100(bswap_32big(0x90fe6d96U),
                   bswap_32big(0xf9d7b763U),
                   bswap_32big(0x0d0350acU),
                   bswap_32big(0x2f8f440fU));
    r_rsip_func103();
    r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub003(0x80010000U, 0x03410005U);
    r_rsip_func_sub009(0x0001000dU, 0x000034c0U);

    r_rsip_func_sub002(0x800100e0U, 0x00000008U);

    r_rsip_func101(bswap_32big(0x2a4cc2c0U),
                   bswap_32big(0xd8932e92U),
                   bswap_32big(0xccc153a6U),
                   bswap_32big(0x3c444233U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x00000008U);

    r_rsip_func101(bswap_32big(0xa78dc70fU),
                   bswap_32big(0x40ec3ab7U),
                   bswap_32big(0x88c1c35fU),
                   bswap_32big(0x72cec54bU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x691fc30aU),
                   bswap_32big(0x3b19358bU),
                   bswap_32big(0x980ce1d9U),
                   bswap_32big(0x48b5e99cU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0xfa5ad980U),
                   bswap_32big(0x7c9e0040U),
                   bswap_32big(0x877f78edU),
                   bswap_32big(0x73466a09U));
    r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x00000821U);
    r_rsip_func_sub003(0x80840001U, 0x03410011U);

    r_rsip_func103();

    r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    r_rsip_func_sub003(0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0x99d2e125U),
                   bswap_32big(0x12c4e0a8U),
                   bswap_32big(0xaf1aa698U),
                   bswap_32big(0x85f20fd7U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    WR1_PROG(REG_0094H, 0x00000821U);
    r_rsip_func_sub003(0x81880001U, 0x00490021U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0x2173c542U),
                   bswap_32big(0x29c6911bU),
                   bswap_32big(0x1edebb61U),
                   bswap_32big(0x37706b8aU));
    r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    r_rsip_func_sub006(0x09108105U, 0x00410011U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

    r_rsip_func100(bswap_32big(0x95dd844dU),
                   bswap_32big(0x8d352f33U),
                   bswap_32big(0xa9006d22U),
                   bswap_32big(0xff96334fU));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0x55765ef5U),
                   bswap_32big(0xbca56218U),
                   bswap_32big(0x68fbf24fU),
                   bswap_32big(0x7c70916fU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
