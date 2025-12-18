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

rsip_ret_t r_rsip_p34i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00340001U, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x00000034U);

    r_rsip_func101(bswap_32big(0x66cae883U),
                   bswap_32big(0x7c0dd2b7U),
                   bswap_32big(0xdcc2f6e7U),
                   bswap_32big(0xc84965f8U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x6c663574U),
                   bswap_32big(0x63d4107cU),
                   bswap_32big(0x0dfdff0cU),
                   bswap_32big(0x6edb9b78U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x3b7a64a5U), bswap_32big(0xd652faa7U), bswap_32big(0x87b10039U),
                       bswap_32big(0xe178325dU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010080U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        r_rsip_func_sub012(0x38000c84U, 0x00260000U);

        r_rsip_func100(bswap_32big(0x1304ba7dU), bswap_32big(0x306874fcU), bswap_32big(0x30ada4d3U),
                       bswap_32big(0xa243d97fU));
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

            r_rsip_func101(bswap_32big(0xc0cdccc4U), bswap_32big(0xcfc2c533U), bswap_32big(0xa6735d03U),
                           bswap_32big(0xd87648b8U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x00000034U);

            r_rsip_func101(bswap_32big(0x6df54f51U), bswap_32big(0x7751be03U), bswap_32big(0x23af02ddU),
                           bswap_32big(0xb5d555e2U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x771a7cf4U), bswap_32big(0x1eeedc23U), bswap_32big(0x9c673505U),
                           bswap_32big(0xf79387a9U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa42a61b1U),
                               bswap_32big(0x06781a5aU),
                               bswap_32big(0x35dc54c1U),
                               bswap_32big(0xb802f9bcU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x372171f3U),
                               bswap_32big(0x95aa7e1bU),
                               bswap_32big(0x32bed9a4U),
                               bswap_32big(0x7a57b6adU));
            }
        }

        r_rsip_func100(bswap_32big(0x3d936d3cU), bswap_32big(0x1b1a6725U), bswap_32big(0x2e8965f8U),
                       bswap_32big(0x2ae514a5U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub004(0x0000181eU, 0x00430011U);

        r_rsip_func100(bswap_32big(0xcf70d2feU), bswap_32big(0x3fd706e7U), bswap_32big(0x50d1bcb6U),
                       bswap_32big(0xee2468c1U));
        r_rsip_func_sub006(0x08000095U, 0x00430011U);

        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        r_rsip_func100(bswap_32big(0x19ecf0c4U), bswap_32big(0xcacce755U), bswap_32big(0x05a77ea8U),
                       bswap_32big(0x0d99f11fU));
        r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub008(0x000000a1U, 0x40000000U, 0x0a0080a4U);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x474be05dU), bswap_32big(0x8ced7c0eU), bswap_32big(0x7eb16ce5U),
                       bswap_32big(0x974d9489U));

        return RSIP_RET_PASS;
    }
}
