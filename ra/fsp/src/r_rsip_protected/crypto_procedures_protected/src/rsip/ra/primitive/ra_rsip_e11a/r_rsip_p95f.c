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

rsip_ret_t r_rsip_p95f (const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
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

    r_rsip_func100(bswap_32big(0xb9a27ff0U), bswap_32big(0x853bb8e7U), bswap_32big(0xfc884222U), bswap_32big(0x2032a4b2U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0xe7000d05U);
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

        r_rsip_func100(bswap_32big(0x809e1a95U), bswap_32big(0xec144a92U), bswap_32big(0x0daf90dcU), bswap_32big(0x46d7e386U));
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

        r_rsip_func101(bswap_32big(0x68a372b7U), bswap_32big(0x828cfedfU), bswap_32big(0xae0a728bU), bswap_32big(0x186c51b5U));
    }
    else
    {
        r_rsip_func101(bswap_32big(0xee0a14d0U), bswap_32big(0x59a5e822U), bswap_32big(0xeecece5cU), bswap_32big(0xf6b69b2cU));
    }

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0x8363bbbfU), bswap_32big(0x96f760c2U), bswap_32big(0x272d57b4U), bswap_32big(0x5b4f8cfeU));
    WR1_PROG(REG_00D0H, 0x09100105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_MAC[0]);

    r_rsip_func102(bswap_32big(0x90a81bb2U), bswap_32big(0xe27d2368U), bswap_32big(0x0de73bfdU), bswap_32big(0xfaaf820bU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
