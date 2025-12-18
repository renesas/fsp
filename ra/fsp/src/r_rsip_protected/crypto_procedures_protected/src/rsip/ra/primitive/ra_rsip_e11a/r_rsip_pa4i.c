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

rsip_ret_t r_rsip_pa4i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00a40001U, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x000000a4U);

    r_rsip_func101(bswap_32big(0xae234251U),
                   bswap_32big(0x577bb95cU),
                   bswap_32big(0xc48c311fU),
                   bswap_32big(0x453d1f11U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x7543619dU),
                   bswap_32big(0x6e07611fU),
                   bswap_32big(0x32a8d831U),
                   bswap_32big(0xd9b8b4e0U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xa4814e21U), bswap_32big(0xfaed354eU), bswap_32big(0x6255699aU),
                       bswap_32big(0xe88ef58fU));
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

        r_rsip_func100(bswap_32big(0x77ea2d05U), bswap_32big(0xb7f9e8faU), bswap_32big(0xb8c17713U),
                       bswap_32big(0xac19d9b5U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x0a8b37ceU), bswap_32big(0x22cff5ffU), bswap_32big(0xa756a04dU),
                           bswap_32big(0x9df88536U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x800100e0U, 0x000000a4U);

            r_rsip_func101(bswap_32big(0x14dd1faaU), bswap_32big(0x9a24f2cfU), bswap_32big(0x7f481dbcU),
                           bswap_32big(0xb8021569U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x67e525e2U), bswap_32big(0x20ba7973U), bswap_32big(0xfdc7924eU),
                           bswap_32big(0x30c76aa6U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x809c0f9dU),
                               bswap_32big(0x1f2e46f3U),
                               bswap_32big(0x8718296bU),
                               bswap_32big(0xcea74c7dU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                r_rsip_func_sub004(0x00000801U, 0x00430009U);

                r_rsip_func_sub004(0x00000802U, 0x00430009U);

                r_rsip_func101(bswap_32big(0x3f1b8e43U),
                               bswap_32big(0x10ae81ecU),
                               bswap_32big(0xe78c8dfeU),
                               bswap_32big(0x5aa342d2U));
            }
        }

        r_rsip_func100(bswap_32big(0x756f20c2U), bswap_32big(0xebed14b4U), bswap_32big(0x364da16bU),
                       bswap_32big(0x7e5a5735U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub004(0x0000181eU, 0x00430011U);

        r_rsip_func100(bswap_32big(0x8eb3c75cU), bswap_32big(0x8a74af99U), bswap_32big(0xbe1cf2e8U),
                       bswap_32big(0x94d74eb0U));
        r_rsip_func_sub006(0x08000095U, 0x00430011U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0xef328880U), bswap_32big(0x5fa88accU), bswap_32big(0xb3196322U),
                       bswap_32big(0xe07c4a37U));

        return RSIP_RET_PASS;
    }
}
