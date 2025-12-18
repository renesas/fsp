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

rsip_ret_t r_rsip_p95i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00950001U, 0x00000005U);

    r_rsip_func_sub002(0x800100e0U, 0x00009501U);

    r_rsip_func101(bswap_32big(0x0c0018c3U),
                   bswap_32big(0x20958bdaU),
                   bswap_32big(0x4b28f863U),
                   bswap_32big(0xeef0fabaU));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x98ecec4dU),
                   bswap_32big(0x404021ccU),
                   bswap_32big(0xe6f2f501U),
                   bswap_32big(0xb144740fU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xcf36a407U), bswap_32big(0x518b72dbU), bswap_32big(0x2e0143a8U),
                       bswap_32big(0x4d374773U));
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
        WR1_PROG(REG_009CH, 0x80010080U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        r_rsip_func_sub012(0x38000c84U, 0x00260000U);

        r_rsip_func100(bswap_32big(0xfe78b3e8U), bswap_32big(0x9c3711efU), bswap_32big(0x0311946dU),
                       bswap_32big(0xe3240b94U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x1a15466dU), bswap_32big(0xdcdcc075U), bswap_32big(0x7951c9d5U),
                           bswap_32big(0x67331294U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x00009502U);

            r_rsip_func101(bswap_32big(0xb578499bU), bswap_32big(0x82882949U), bswap_32big(0x87fc7de2U),
                           bswap_32big(0xd0d297f3U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x10cb73caU), bswap_32big(0x80bc1252U), bswap_32big(0xd1500eceU),
                           bswap_32big(0x1ccac826U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x28b48edfU),
                               bswap_32big(0xa584e2d0U),
                               bswap_32big(0x1134273bU),
                               bswap_32big(0xf57fe680U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                r_rsip_func_sub004(0x00000801U, 0x00430009U);

                r_rsip_func_sub004(0x00000802U, 0x00430009U);

                r_rsip_func101(bswap_32big(0x5584cdb3U),
                               bswap_32big(0x390dc7d6U),
                               bswap_32big(0xdb63c81fU),
                               bswap_32big(0xd796655bU));
            }
        }

        r_rsip_func100(bswap_32big(0x78b98525U), bswap_32big(0x88e32fc5U), bswap_32big(0xc922548aU),
                       bswap_32big(0x860b69b8U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub003(0x81840000U, 0x00490011U);

        WR1_PROG(REG_00D4H, 0x00000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0x47457a11U), bswap_32big(0x7e435741U), bswap_32big(0xbda8e140U),
                       bswap_32big(0xcce9ff15U));

        return RSIP_RET_PASS;
    }
}
