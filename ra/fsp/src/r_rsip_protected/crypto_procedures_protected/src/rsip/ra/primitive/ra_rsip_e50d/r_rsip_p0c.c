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

rsip_ret_t r_rsip_p0c (const uint32_t InData_CurrentVer[], const uint32_t InData_NextVer[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x000c0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func048(InData_CurrentVer);

    r_rsip_func049(InData_NextVer);

    WR1_PROG(REG_1600H, 0x34202880U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xa006fff8U),
                   bswap_32big(0xd93cd0bbU),
                   bswap_32big(0xcdb66f1eU),
                   bswap_32big(0x184dd992U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_14BCH, 0x00000020U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_VERIFICATION_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38002880U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x3983300cU), bswap_32big(0xf424286cU), bswap_32big(0x74c57a20U),
                       bswap_32big(0x880d5960U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1B08H, 0x00000215U);

            r_rsip_func102(bswap_32big(0x937ec401U), bswap_32big(0x67c174b4U), bswap_32big(0xc32d39c1U),
                           bswap_32big(0x80bc13f3U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_VERSION_MATCH;
        }
        else
        {
            WR1_PROG(REG_1B08H, 0x00000215U);

            r_rsip_func102(bswap_32big(0x3adff011U), bswap_32big(0xf98f1382U), bswap_32big(0xcc6f21a7U),
                           bswap_32big(0x9774e299U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
