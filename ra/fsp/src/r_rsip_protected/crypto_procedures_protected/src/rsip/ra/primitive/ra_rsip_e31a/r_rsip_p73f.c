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

rsip_ret_t r_rsip_p73f (const uint32_t InData_Msg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[])
{
    uint32_t iLoop = 0U;

    WAIT_STS(REG_0118H, 0, 1);

    WR1_PROG(REG_0014H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); iLoop = iLoop + 16U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &InData_Msg[iLoop]);
    }

    WAIT_STS(REG_0014H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_002CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_0014H, 0x00000000U);
    WAIT_STS(REG_0118H, 8, 0);
    WR1_PROG(REG_0040H, 0x00001600U);

    WAIT_STS(REG_0118H, 4, 1);

    r_rsip_func100(bswap_32big(0xa2c4a1fdU),
                   bswap_32big(0xac08db0eU),
                   bswap_32big(0x5f410eadU),
                   bswap_32big(0xc3c5be3eU));
    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x1000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x1000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    WR1_PROG(REG_0094H, 0x00007c00U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func100(bswap_32big(0xa58082c6U), bswap_32big(0x3f879f00U), bswap_32big(0x816affa0U),
                       bswap_32big(0x795273e1U));
        WR1_PROG(REG_0008H, 0x0000401eU);
        WAIT_STS(REG_0008H, 30, 1);
        RD7_ADDR(REG_002CH, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0xc019dcbeU), bswap_32big(0xa552809fU), bswap_32big(0x984fc62eU),
                       bswap_32big(0x46b83ae7U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func100(bswap_32big(0x6248df88U), bswap_32big(0x5b075037U), bswap_32big(0x07a3aaddU),
                       bswap_32big(0xb8cd02d1U));
        WR1_PROG(REG_0008H, 0x00004022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD8_ADDR(REG_002CH, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0x30737869U), bswap_32big(0x1c64302eU), bswap_32big(0x2b4acf3eU),
                       bswap_32big(0xdfcaceccU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
    {
        r_rsip_func100(bswap_32big(0xac6a0371U), bswap_32big(0x2ca41847U), bswap_32big(0x6d2aea84U),
                       bswap_32big(0xaf49a2b9U));
        WR1_PROG(REG_0008H, 0x00004032U);
        WAIT_STS(REG_0008H, 30, 1);
        RD12_ADDR(REG_002CH, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0xf80b2d06U), bswap_32big(0xda6a3270U), bswap_32big(0xa4bdc938U),
                       bswap_32big(0x9936eafcU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
    {
        r_rsip_func100(bswap_32big(0x68d423e3U), bswap_32big(0xc7a2da06U), bswap_32big(0x24a01e4eU),
                       bswap_32big(0x86b44fddU));
        WR1_PROG(REG_0008H, 0x00004042U);
        WAIT_STS(REG_0008H, 30, 1);
        RD16_ADDR(REG_002CH, &OutData_MsgDigest[0]);

        r_rsip_func102(bswap_32big(0xe6373b9bU), bswap_32big(0x7f30e07aU), bswap_32big(0x7b4fd7a4U),
                       bswap_32big(0x52ce06a7U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);
    }

    return RSIP_RET_PASS;
}
