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

rsip_ret_t r_rsip_pa1f (const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00008c00U);
    WR1_PROG(REG_0094H, 0x0000000fU);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x0a6032a4U), bswap_32big(0x33da8786U), bswap_32big(0x73aa16e0U), bswap_32big(0x44436769U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xe7008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x80840001U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000821U);

        WR1_PROG(REG_0094H, 0x000008a5U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x3c0028a0U);
            WR1_PROG(REG_0094H, 0x12003c25U);
            WR1_PROG(REG_0094H, 0x00002ca0U);
        }

        r_rsip_func100(bswap_32big(0xd18b3490U), bswap_32big(0x6f6a6ee2U), bswap_32big(0x0534576cU), bswap_32big(0xe015b7d2U));
        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0008H, 0x00005012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[0]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[2]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[3]);

        r_rsip_func101(bswap_32big(0x8e752d87U), bswap_32big(0x54e4c42dU), bswap_32big(0x8258eae8U), bswap_32big(0xeace9d5cU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0xee8929fdU), bswap_32big(0xbb62601cU), bswap_32big(0xc49290edU), bswap_32big(0x554a0abaU));
    }

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0x23779b99U), bswap_32big(0x23b05fa5U), bswap_32big(0x453c84c9U), bswap_32big(0x924ecce0U));
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x09108105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_MAC[0]);

    r_rsip_func102(bswap_32big(0xfb65f077U), bswap_32big(0x41a090d9U), bswap_32big(0xba456db1U), bswap_32big(0xc6fbb442U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
