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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p50i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00500001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x1e50768aU),
                   bswap_32big(0x5930933bU),
                   bswap_32big(0x311f1280U),
                   bswap_32big(0xece84cb3U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x6327f387U),
                   bswap_32big(0x2baf972dU),
                   bswap_32big(0x89127376U),
                   bswap_32big(0x72e99f32U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc5e00c86U), bswap_32big(0x69d970a5U), bswap_32big(0x8961cdc1U),
                       bswap_32big(0x32aa4fa1U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x3c00a880U);
        WR1_PROG(REG_0094H, 0x00000002U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0xe7b5ccf0U), bswap_32big(0x34c50a1aU), bswap_32big(0x22e5823aU),
                       bswap_32big(0xc1795e76U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x3c00a880U);
            WR1_PROG(REG_0094H, 0x00000004U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0x69c8e350U), bswap_32big(0xf1556ea8U), bswap_32big(0x8471565bU),
                           bswap_32big(0x36da8bf9U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000000c7U);
                WR1_PROG(REG_009CH, 0x800100a0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_IVType[0]);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x1d5a7194U),
                               bswap_32big(0x2c64bdadU),
                               bswap_32big(0x48d01062U),
                               bswap_32big(0x8f9350d7U));
            }

            WR1_PROG(REG_0094H, 0x38000ca5U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            r_rsip_func100(bswap_32big(0xff3bb46dU), bswap_32big(0x0ca2b8ceU), bswap_32big(0xea68c347U),
                           bswap_32big(0x9fbcd8bbU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D0H, 0x08000045U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_IV[0]);

                r_rsip_func101(bswap_32big(0x0d309780U),
                               bswap_32big(0x2270e931U),
                               bswap_32big(0x15b26d30U),
                               bswap_32big(0x9a9b2d28U));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b4a0U);
                WR1_PROG(REG_0094H, 0x0199e556U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x6efc8c9bU),
                               bswap_32big(0x6e1459c7U),
                               bswap_32big(0x05243ec9U),
                               bswap_32big(0x0b3c7c48U));
                r_rsip_func440(InData_IV);

                r_rsip_func100(bswap_32big(0x70c0955aU),
                               bswap_32big(0xf547cdacU),
                               bswap_32big(0x022675c6U),
                               bswap_32big(0x4984584eU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x3f30bc75U),
                                   bswap_32big(0x58ac2203U),
                                   bswap_32big(0x3667f034U),
                                   bswap_32big(0x480ccf6cU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_00D0H, 0x08000045U);
                    WR1_PROG(REG_00B0H, 0x00000801U);
                    WR1_PROG(REG_0000H, 0x00430009U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_00B0H, 0x00000802U);
                    WR1_PROG(REG_0000H, 0x00430009U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xab38d16aU),
                                   bswap_32big(0xc0a3dee7U),
                                   bswap_32big(0xf0fe7fe7U),
                                   bswap_32big(0x0b740c3fU));
                }
            }
        }

        r_rsip_func100(bswap_32big(0x3e9191e3U), bswap_32big(0x83289b6bU), bswap_32big(0x8260e39fU),
                       bswap_32big(0x58cabaebU));
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x0000181eU);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xf142c420U), bswap_32big(0x6f0f79a3U), bswap_32big(0xbc3eeddbU),
                       bswap_32big(0xd9cbc04bU));
        WR1_PROG(REG_00D0H, 0x08000095U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x0c003080U);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x0a000100U);

        WR1_PROG(REG_0094H, 0x0c003080U);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x0a000108U);

        WR1_PROG(REG_0094H, 0x0c003080U);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x0e000500U);

        WR1_PROG(REG_0094H, 0x0c003080U);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x09000908U);

        WR1_PROG(REG_0094H, 0x0c00a880U);
        WR1_PROG(REG_0094H, 0xfffffffcU);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x07000d00U);

        r_rsip_func101(bswap_32big(0xfda76a5cU), bswap_32big(0x2c028b81U), bswap_32big(0xb22309f1U),
                       bswap_32big(0x86f50e37U));

        return RSIP_RET_PASS;
    }
}
