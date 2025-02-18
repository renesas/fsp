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

rsip_ret_t r_rsip_pa4f (const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010060U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_MACLength[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38008860U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_0094H, 0x342028a3U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0x65adc143U), bswap_32big(0x0fbfeab9U), bswap_32big(0x281826d2U), bswap_32big(0x0bd7f13aU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x1e9a06ddU), bswap_32big(0xf3947fb6U), bswap_32big(0x8e5aac58U), bswap_32big(0x3bb6c9d0U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
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

        r_rsip_func100(bswap_32big(0x181b769cU), bswap_32big(0x1eb41883U), bswap_32big(0x94718677U), bswap_32big(0xe2a5a6a7U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
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

            r_rsip_func100(bswap_32big(0x5c1c76dcU), bswap_32big(0x73dbbb94U), bswap_32big(0x2f7fa56cU), bswap_32big(0xaa2d6d07U));
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

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x0e108405U);
            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x64068ab7U), bswap_32big(0x52031ee7U), bswap_32big(0x8a7eac51U), bswap_32big(0x186d422eU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0x0d9516c1U), bswap_32big(0x3677ea26U), bswap_32big(0xdb23a010U), bswap_32big(0x5766879aU));
        }

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c100104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07208d05U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x80840001U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x000008a5U);

        WR1_PROG(REG_0094H, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x3c0028a3U);
            WR1_PROG(REG_0094H, 0x12003c25U);
            WR1_PROG(REG_0094H, 0x00002ca0U);
        }

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x08000055U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_MAC[0]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00D0H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x7db0d3aaU), bswap_32big(0x3838e6e8U), bswap_32big(0xf0e0f08eU), bswap_32big(0x455b5e70U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x334a361eU), bswap_32big(0x5d071300U), bswap_32big(0x415d9f57U), bswap_32big(0x58ba50b0U));

            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_AUTH_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0x7777d002U), bswap_32big(0x5fae10c8U), bswap_32big(0x1050edd7U), bswap_32big(0x578921e4U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
