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

rsip_ret_t r_rsip_p36i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00360001U, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x00000036U);

    r_rsip_func101(bswap_32big(0x94e9a5d5U),
                   bswap_32big(0xcf528c36U),
                   bswap_32big(0xdd0290efU),
                   bswap_32big(0xcefeb202U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x11ca82e7U),
                   bswap_32big(0xf7405284U),
                   bswap_32big(0x8bc063ccU),
                   bswap_32big(0xc179b62cU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x557d18d8U), bswap_32big(0x9a53d37cU), bswap_32big(0x234442e1U),
                       bswap_32big(0x8637db53U));
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

        r_rsip_func100(bswap_32big(0xe30860aaU), bswap_32big(0x7601f622U), bswap_32big(0xf567869cU),
                       bswap_32big(0xf64c2111U));
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

            r_rsip_func101(bswap_32big(0x03ed8335U), bswap_32big(0x4314586dU), bswap_32big(0xc1f136cbU),
                           bswap_32big(0x894dd32dU));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x00000036U);

            r_rsip_func101(bswap_32big(0x6dcf92dbU), bswap_32big(0x454a310aU), bswap_32big(0xc4006dddU),
                           bswap_32big(0xb5d1b0c3U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x95fe8609U), bswap_32big(0xe1b03c05U), bswap_32big(0x00c5e53eU),
                           bswap_32big(0xfa1a036aU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd0057f70U),
                               bswap_32big(0xe8b7abfaU),
                               bswap_32big(0xee162f11U),
                               bswap_32big(0x3f2bffa6U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x994a5235U),
                               bswap_32big(0x2f23a5ceU),
                               bswap_32big(0xbe69fcb8U),
                               bswap_32big(0x2cd8d070U));
            }
        }

        r_rsip_func100(bswap_32big(0x3b625f44U), bswap_32big(0xc4ae7005U), bswap_32big(0x232e28e2U),
                       bswap_32big(0x96197208U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub004(0x0000181eU, 0x00430011U);

        r_rsip_func100(bswap_32big(0x4a8e6fcbU), bswap_32big(0xcce3eaa3U), bswap_32big(0xc08aa121U),
                       bswap_32big(0x8ec0c77fU));
        r_rsip_func_sub006(0x08000095U, 0x00430011U);

        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        r_rsip_func100(bswap_32big(0x3abf5204U), bswap_32big(0x8c6599acU), bswap_32big(0x4c3aedd0U),
                       bswap_32big(0x0360b47eU));
        r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub008(0x000000a1U, 0x40000000U, 0x0a0080a4U);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0xc18b8156U), bswap_32big(0x976f9c3eU), bswap_32big(0x9b3daa7cU),
                       bswap_32big(0x8b25de42U));

        return RSIP_RET_PASS;
    }
}
