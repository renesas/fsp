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

rsip_ret_t r_rsip_p29i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00290001U, 0x00000005U);

    r_rsip_func_sub002(0x800100e0U, 0x00002901U);

    r_rsip_func101(bswap_32big(0xca2b19f0U),
                   bswap_32big(0x563ee931U),
                   bswap_32big(0x6c7caf8cU),
                   bswap_32big(0xa130c5c3U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x03f9b0b1U),
                   bswap_32big(0xf5ec847eU),
                   bswap_32big(0xf0421549U),
                   bswap_32big(0x2f9aee1cU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x913ffd61U), bswap_32big(0x5b0300e5U), bswap_32big(0x6972c608U),
                       bswap_32big(0xb5bcffc1U));
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

        r_rsip_func100(bswap_32big(0x13f60012U), bswap_32big(0xacfc621cU), bswap_32big(0x98438383U),
                       bswap_32big(0x5d3dc0c1U));
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

            r_rsip_func101(bswap_32big(0xc61b1b36U), bswap_32big(0xd6fef7aeU), bswap_32big(0x6e4eadfbU),
                           bswap_32big(0x9baa8fccU));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x00002902U);

            r_rsip_func101(bswap_32big(0x0c813e73U), bswap_32big(0x3ec41a48U), bswap_32big(0x089819b4U),
                           bswap_32big(0xd7ba9824U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xec14d89cU), bswap_32big(0x64a09d13U), bswap_32big(0xa8cf8a0aU),
                           bswap_32big(0x84584bf3U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x4a656e7fU),
                               bswap_32big(0x02dc1030U),
                               bswap_32big(0x5f00e8ebU),
                               bswap_32big(0x32509e26U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x920ddc0dU),
                               bswap_32big(0x875e25caU),
                               bswap_32big(0x577007ceU),
                               bswap_32big(0xf511bfa7U));
            }
        }

        r_rsip_func100(bswap_32big(0xb4ee2d01U), bswap_32big(0x615638a9U), bswap_32big(0xec88dc8dU),
                       bswap_32big(0x468fa4b1U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub003(0x81840000U, 0x00490011U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        r_rsip_func100(bswap_32big(0xa6a9a201U), bswap_32big(0xc83178a0U), bswap_32big(0x4de3177dU),
                       bswap_32big(0xc6795af5U));
        r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub005(0x000000a1U, 0x0a0000a4U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe36fec64U), bswap_32big(0xfe50175dU), bswap_32big(0x4fa5a73bU),
                       bswap_32big(0x3b0bae0aU));

        return RSIP_RET_PASS;
    }
}
