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

rsip_ret_t r_rsip_p29f (const uint32_t InData_Text[],
                        const uint32_t InData_DataALen[],
                        const uint32_t InData_TextLen[],
                        uint32_t       OutData_Text[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x80020040U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[1]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x0000007FU);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0xFFFFFF00U);
    WR1_PROG(REG_0094H, 0x0c002823U);
    WR1_PROG(REG_0094H, 0x04a02802U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x1f482e19U),
                   bswap_32big(0xa67b78deU),
                   bswap_32big(0xf09d1683U),
                   bswap_32big(0xaa23c0b1U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xaf975377U), bswap_32big(0x2a30e2cbU), bswap_32big(0x6d34bd59U),
                       bswap_32big(0x680c1ccaU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003403U);
        WR1_PROG(REG_0094H, 0x00036800U);

        WR1_PROG(REG_0094H, 0x08008c00U);
        WR1_PROG(REG_0094H, 0x0000000fU);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x4b0d3b70U), bswap_32big(0xb50a0a0dU), bswap_32big(0xc90bfbb4U),
                       bswap_32big(0xdf0b2c23U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func100(bswap_32big(0xe801181eU), bswap_32big(0xc93e4253U), bswap_32big(0xd4db8e62U),
                           bswap_32big(0xe87746f7U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x00000020U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x80840001U);
            WR1_PROG(REG_0000H, 0x03410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x3c002820U);
                WR1_PROG(REG_0094H, 0x12003c81U);
                WR1_PROG(REG_0094H, 0x00002c20U);
            }

            WR1_PROG(REG_00D4H, 0x00008000U);
            WR1_PROG(REG_00D0H, 0x0e128455U);
            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WAIT_STS(REG_00C8H, 6, 0);
            WR1_PROG(REG_0040H, 0x00000400U);
            WR1_PROG(REG_0040H, 0x00000500U);

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

            r_rsip_func101(bswap_32big(0xa6d2ebdeU), bswap_32big(0xf51d65a6U), bswap_32big(0xb45f5afdU),
                           bswap_32big(0xe157cdc8U));
        }

        r_rsip_func100(bswap_32big(0xc290b953U), bswap_32big(0xb36621dfU), bswap_32big(0xdd888662U),
                       bswap_32big(0xc4de39b7U));
        WR1_PROG(REG_0014H, 0x000001c1U);
        WR1_PROG(REG_00D4H, 0x00008000U);
        WR1_PROG(REG_00D0H, 0x0e128455U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_DataALen[0]);

        WR1_PROG(REG_009CH, 0x81020040U);
        WR1_PROG(REG_0000H, 0x00490009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        WR1_PROG(REG_0094H, 0x0000b420U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c100104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D4H, 0x00000020U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0x3e00f0e4U), bswap_32big(0x2755602aU), bswap_32big(0xd5f91fbfU),
                       bswap_32big(0x9f92be49U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
