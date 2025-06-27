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

rsip_ret_t r_rsip_p34i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00340001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000034U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xe2453bbbU),
                   bswap_32big(0x15cb22b5U),
                   bswap_32big(0xfd3450deU),
                   bswap_32big(0x546c82d2U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000034U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5a3a0127U),
                   bswap_32big(0xe2ffdea0U),
                   bswap_32big(0x1f9a413fU),
                   bswap_32big(0xc8589a5aU));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000007c1U);
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xf7009d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    WR1_PROG(REG_00B0H, 0x00001404U);
    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x6d5ccfbaU),
                   bswap_32big(0x371a557cU),
                   bswap_32big(0xe1c15157U),
                   bswap_32big(0x64716b5fU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xbfc43f7bU), bswap_32big(0xd746fe45U), bswap_32big(0x68f113d2U),
                       bswap_32big(0xaec9c1c2U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000034U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xac58d073U), bswap_32big(0x780096bfU), bswap_32big(0xd69b0c26U),
                       bswap_32big(0x71e04f11U));
        r_rsip_func510(InData_IVType, InData_IV);

        WR1_PROG(REG_0094H, 0x38000c00U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x10917d72U), bswap_32big(0x13cc8fe3U), bswap_32big(0xe758f4e7U),
                       bswap_32big(0xec8456c4U));
        WR1_PROG(REG_0040H, 0x00400000U);
        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xdf445ec3U), bswap_32big(0x53d5fe25U), bswap_32big(0x8e491902U),
                           bswap_32big(0x20d81892U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x9e254c43U), bswap_32big(0x2bf6c36bU), bswap_32big(0x3126f606U),
                           bswap_32big(0x835d56d6U));
            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x5f20ff70U), bswap_32big(0xe3b2ae47U), bswap_32big(0xaaa808b6U),
                           bswap_32big(0x22674264U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x96ff68eeU), bswap_32big(0x703995cdU), bswap_32big(0x073fbec1U),
                           bswap_32big(0xd77a3d21U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x0a0080a4U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            r_rsip_func101(bswap_32big(0x33e656f6U), bswap_32big(0x5c0a9bffU), bswap_32big(0x855b8f96U),
                           bswap_32big(0x36e97c57U));

            return RSIP_RET_PASS;
        }
    }
}
