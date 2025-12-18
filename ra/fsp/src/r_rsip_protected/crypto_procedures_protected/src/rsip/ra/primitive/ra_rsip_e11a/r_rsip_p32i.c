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

rsip_ret_t r_rsip_p32i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00320001U, 0x00000005U);

    r_rsip_func_sub002(0x800100e0U, 0x00003201U);

    r_rsip_func101(bswap_32big(0x83aaaf23U),
                   bswap_32big(0x6e9484d6U),
                   bswap_32big(0xbe1676dbU),
                   bswap_32big(0x607c518dU));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x92eef925U),
                   bswap_32big(0xb919c118U),
                   bswap_32big(0x3bef1984U),
                   bswap_32big(0xbbc99a4fU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xf35a7eedU), bswap_32big(0xe098e4c2U), bswap_32big(0x0619f873U),
                       bswap_32big(0x33656158U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100a0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        r_rsip_func_sub012(0x38000ca5U, 0x00260000U);

        r_rsip_func100(bswap_32big(0x84717cbcU), bswap_32big(0xd384d2feU), bswap_32big(0x7b49f9f9U),
                       bswap_32big(0xe0253631U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func_sub004(0x00000401U, 0x00c10009U);

            r_rsip_func_sub004(0x00000402U, 0x00c10009U);

            r_rsip_func101(bswap_32big(0x7389cb51U), bswap_32big(0xa233108aU), bswap_32big(0x9a1eb648U),
                           bswap_32big(0x7673e1caU));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x00003202U);

            r_rsip_func101(bswap_32big(0xbb94fbc0U), bswap_32big(0xc014f93eU), bswap_32big(0x48aa9ff2U),
                           bswap_32big(0xc5cd5823U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xf2c082bbU), bswap_32big(0x44a1e58aU), bswap_32big(0x4798e338U),
                           bswap_32big(0x327e9d3dU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xe0bd3fafU),
                               bswap_32big(0x55e8c3d4U),
                               bswap_32big(0xd931ce60U),
                               bswap_32big(0xacedc61aU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x160f5f17U),
                               bswap_32big(0x2d1c0280U),
                               bswap_32big(0xcce0eeadU),
                               bswap_32big(0x609e438aU));
            }
        }

        r_rsip_func100(bswap_32big(0xfcfa8006U), bswap_32big(0x60f2ebfdU), bswap_32big(0x3c4cb3eeU),
                       bswap_32big(0x5e05787aU));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub003(0x81840000U, 0x00490011U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        r_rsip_func100(bswap_32big(0x196f05b2U), bswap_32big(0x1d91792eU), bswap_32big(0x83251f87U),
                       bswap_32big(0xab54cca5U));
        r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub005(0x000000a1U, 0x0a0000a4U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xdc8faf92U), bswap_32big(0xe72405edU), bswap_32big(0x65d3e74fU),
                       bswap_32big(0x18c8b6bfU));

        return RSIP_RET_PASS;
    }
}
