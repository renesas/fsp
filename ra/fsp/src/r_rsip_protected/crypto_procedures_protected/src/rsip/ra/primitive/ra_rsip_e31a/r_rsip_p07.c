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

rsip_ret_t r_rsip_p07 (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00070001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x4ad271afU),
                   bswap_32big(0x1978ac11U),
                   bswap_32big(0xc5934b88U),
                   bswap_32big(0xcf015a13U));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000007U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x9973de79U),
                   bswap_32big(0x65645179U),
                   bswap_32big(0xb20c3cbbU),
                   bswap_32big(0x60aa85f3U));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000007U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0934658bU),
                   bswap_32big(0xfa574998U),
                   bswap_32big(0xf05a5d2cU),
                   bswap_32big(0x8f3cb049U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x321f23a7U),
                   bswap_32big(0xc00a15a0U),
                   bswap_32big(0xf4f5e46aU),
                   bswap_32big(0x3ccbfd3cU));
    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

    r_rsip_func100(bswap_32big(0xe4eab2a9U),
                   bswap_32big(0xf7980b69U),
                   bswap_32big(0x6564b11cU),
                   bswap_32big(0xdd6f7070U));
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0xe7009d05U);
    r_rsip_func_sub007(0x00000821U, 0x81840001U, 0x00490011U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);

    r_rsip_func100(bswap_32big(0x16d51dadU),
                   bswap_32big(0xa6a5f85eU),
                   bswap_32big(0x56109d3aU),
                   bswap_32big(0xb7b4b2cbU));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0x42800ebeU),
                   bswap_32big(0x148dc45cU),
                   bswap_32big(0x14f4552eU),
                   bswap_32big(0xa357be13U));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0xa73adff8U),
                   bswap_32big(0xd1595bc6U),
                   bswap_32big(0xa9b3fd02U),
                   bswap_32big(0x0a4d791fU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
