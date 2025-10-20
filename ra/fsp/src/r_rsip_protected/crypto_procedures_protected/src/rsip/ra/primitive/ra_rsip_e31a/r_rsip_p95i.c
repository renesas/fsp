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

rsip_ret_t r_rsip_p95i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[], const uint32_t InData_Header[], uint32_t Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00950001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00009501U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5745250bU), bswap_32big(0x5eb9f25eU), bswap_32big(0x4d950297U), bswap_32big(0x0dee4558U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x7e8222f6U), bswap_32big(0xa27e2b48U), bswap_32big(0xb923b689U), bswap_32big(0x52e5652cU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xf559769cU), bswap_32big(0xa349051eU), bswap_32big(0x8969e08cU), bswap_32big(0x6af4cc44U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010080U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0xd710f4e5U), bswap_32big(0xf3c05638U), bswap_32big(0x75353d42U), bswap_32big(0x2b1c802fU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x039e86a2U), bswap_32big(0x2e1e724aU), bswap_32big(0x38ba6f83U), bswap_32big(0x876ffdceU));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00009502U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa3f9549cU), bswap_32big(0x2a7853e8U), bswap_32big(0x9bd71b59U), bswap_32big(0xd6765b3cU));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xbd41c2deU), bswap_32big(0xc17957ddU), bswap_32big(0xe43df482U), bswap_32big(0xa07882aaU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x62a0e588U), bswap_32big(0x6dee039dU), bswap_32big(0xadf00230U), bswap_32big(0xc8f49fa3U));
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

                r_rsip_func101(bswap_32big(0xdacae135U), bswap_32big(0x545e6da1U), bswap_32big(0xe5b59e4fU), bswap_32big(0x76c03154U));
            }
        }

        r_rsip_func100(bswap_32big(0x94b2d747U), bswap_32big(0x03624578U), bswap_32big(0x6e9f3dc5U), bswap_32big(0x74ea0487U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_009CH, 0x81840000U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x00000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0x881c6116U), bswap_32big(0xf45ca629U), bswap_32big(0x4b819b47U), bswap_32big(0xd2da7d6eU));

        return RSIP_RET_PASS;
    }
}
