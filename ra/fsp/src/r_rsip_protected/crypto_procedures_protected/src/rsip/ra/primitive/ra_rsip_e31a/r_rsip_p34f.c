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

rsip_ret_t r_rsip_p34f (const uint32_t InData_Text[],
                        const uint32_t InData_DataALen[],
                        const uint32_t InData_TextLen[],
                        uint32_t       OutData_Text[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub014(0x000001c7U, 0x80020040U);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[1]);
    r_rsip_func_sub018(0x00000000U, 0x0000b400U, 0x0000007FU);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0xFFFFFF00U);
    r_rsip_func_sub010(0x0c002823U, 0x04a02802U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xf03c9fa2U),
                   bswap_32big(0x11dd16aaU),
                   bswap_32big(0xfc834fa6U),
                   bswap_32big(0x20ac329aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xdbc95eb8U), bswap_32big(0x9ef329daU), bswap_32big(0xe70c35ecU),
                       bswap_32big(0x5450548eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003403U);
        WR1_PROG(REG_0094H, 0x00036800U);

        r_rsip_func_sub010(0x08008c00U, 0x0000000fU, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x7b88e3c9U), bswap_32big(0x69193099U), bswap_32big(0x0b469426U),
                       bswap_32big(0xcaf84524U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func100(bswap_32big(0x99956588U), bswap_32big(0x0fbf751dU), bswap_32big(0x3db382fcU),
                           bswap_32big(0x05c19615U));
            r_rsip_func_sub011(0x000003c1U, 0x40000020U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

            WR1_PROG(REG_0094H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                r_rsip_func_sub022(0x3c002820U, 0x12003c81U, 0x00002c20U);
            }

            WR1_PROG(REG_00D4H, 0x00008000U);
            WR1_PROG(REG_00D0H, 0x0e128455U);
            r_rsip_func_sub007(0x00000821U, 0x81840001U, 0x00490011U);

            WAIT_STS(REG_00C8H, 6, 0);
            WR1_PROG(REG_0040H, 0x00000400U);
            WR1_PROG(REG_0040H, 0x00000500U);

            r_rsip_func_sub017(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_002CH, &OutData_Text[0]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[2]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[3]);

            r_rsip_func101(bswap_32big(0x9cb420b0U), bswap_32big(0x8fc3e3bcU), bswap_32big(0x6e3da513U),
                           bswap_32big(0x3af62061U));
        }

        r_rsip_func100(bswap_32big(0xe0af0393U), bswap_32big(0x52ea7dc4U), bswap_32big(0x9640d333U),
                       bswap_32big(0x09a1e188U));
        r_rsip_func_sub011(0x000001c1U, 0x00008000U, 0x0e128455U);
        WR2_ADDR(REG_002CH, &InData_DataALen[0]);

        r_rsip_func_sub012(0x81020040U, 0x00490009U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        WR1_PROG(REG_0094H, 0x0000b420U);
        r_rsip_func_sub007(0x00000010U, 0x81840001U, 0x00490011U);

        r_rsip_func_sub008(0x000000a1U, 0x0c100104U, 0x00000000U);

        r_rsip_func_sub004(0x40000020U, 0x07008d05U, 0x00410011U, 0x00001012U);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0xfba7252fU), bswap_32big(0x30b31604U), bswap_32big(0x873eb9c8U),
                       bswap_32big(0xd5085d78U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
