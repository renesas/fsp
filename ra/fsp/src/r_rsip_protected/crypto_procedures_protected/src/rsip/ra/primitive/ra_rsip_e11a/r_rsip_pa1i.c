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

rsip_ret_t r_rsip_pa1i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00a10001U, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x000000a1U);

    r_rsip_func101(bswap_32big(0xaa11abf2U),
                   bswap_32big(0xbb3caf1cU),
                   bswap_32big(0x8d729836U),
                   bswap_32big(0xf73e2b4aU));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x38757c92U),
                   bswap_32big(0x96318703U),
                   bswap_32big(0xa5edf4a0U),
                   bswap_32big(0x7ba3ce71U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x05060c29U), bswap_32big(0xa6042d38U), bswap_32big(0x544f762aU),
                       bswap_32big(0xe8a31f3fU));
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

        r_rsip_func100(bswap_32big(0x0f795149U), bswap_32big(0xec917a2bU), bswap_32big(0x69636c10U),
                       bswap_32big(0x1e3c108aU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x4d4a47b9U), bswap_32big(0xe27060b7U), bswap_32big(0x934605f3U),
                           bswap_32big(0x3b88a196U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x000000a1U);

            r_rsip_func101(bswap_32big(0xa7017194U), bswap_32big(0x9c95e9b9U), bswap_32big(0x78859c43U),
                           bswap_32big(0x1129ff2eU));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xfe3e4a9aU), bswap_32big(0x2427bb82U), bswap_32big(0xce02c8b3U),
                           bswap_32big(0x4d398315U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xe988275dU),
                               bswap_32big(0xdbf6e2faU),
                               bswap_32big(0x8bdf6ce7U),
                               bswap_32big(0x694ed6c4U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                r_rsip_func_sub004(0x00000801U, 0x00430009U);

                r_rsip_func_sub004(0x00000802U, 0x00430009U);

                r_rsip_func101(bswap_32big(0xae352b37U),
                               bswap_32big(0xdf9c189cU),
                               bswap_32big(0x086c5d17U),
                               bswap_32big(0xc269b119U));
            }
        }

        r_rsip_func100(bswap_32big(0x04fa419cU), bswap_32big(0xaad3d715U), bswap_32big(0x574e3f10U),
                       bswap_32big(0x115ba07cU));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub004(0x0000181eU, 0x00430011U);

        r_rsip_func100(bswap_32big(0xc8398579U), bswap_32big(0x3d4e740bU), bswap_32big(0xfe153857U),
                       bswap_32big(0xdae4119fU));
        r_rsip_func_sub006(0x08000095U, 0x00430011U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0x249d8118U), bswap_32big(0x1d680b40U), bswap_32big(0x337d2619U),
                       bswap_32big(0x291d88afU));

        return RSIP_RET_PASS;
    }
}
