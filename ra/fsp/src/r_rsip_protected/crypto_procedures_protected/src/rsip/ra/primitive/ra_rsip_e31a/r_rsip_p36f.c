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

rsip_ret_t r_rsip_p36f (const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        const uint32_t InData_DataALen[],
                        const uint32_t InData_TextLen[],
                        const uint32_t InData_DataTLen[],
                        uint32_t       OutData_Text[])
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

    r_rsip_func_sub014(0x000000c7U, 0x800100a0U);
    WR1_PROG(REG_002CH, InData_DataTLen[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub010(0x380088a0U, 0x00000000U, 0x00270000U);

    WR1_PROG(REG_0094H, 0x0000b420U);
    r_rsip_func_sub010(0x00000010U, 0x34202825U, 0x00270000U);

    r_rsip_func100(bswap_32big(0x65b1038eU),
                   bswap_32big(0xca33f6e0U),
                   bswap_32big(0x4366d2f2U),
                   bswap_32big(0x2aeb8e97U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x85eeba00U), bswap_32big(0x79d76661U), bswap_32big(0x7dd6e807U),
                       bswap_32big(0xe668a6c0U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003403U);
        WR1_PROG(REG_0094H, 0x00036800U);

        r_rsip_func_sub010(0x08008c00U, 0x0000000fU, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x945a97f1U), bswap_32big(0x23c16bbcU), bswap_32big(0xc9173309U),
                       bswap_32big(0xa651e5b5U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func100(bswap_32big(0x9a869b62U), bswap_32big(0xfe66832fU), bswap_32big(0x4b430f28U),
                           bswap_32big(0x25220e3bU));
            r_rsip_func_sub011(0x000003c1U, 0x40008020U, 0x20008d05U);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

            WR1_PROG(REG_0094H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                r_rsip_func_sub022(0x3c002820U, 0x12003c81U, 0x00002c20U);
            }

            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub017(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_002CH, &OutData_Text[0]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[2]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[3]);

            r_rsip_func101(bswap_32big(0x15a01df2U), bswap_32big(0xf75dc337U), bswap_32big(0x83797c51U),
                           bswap_32big(0xd8d79126U));
        }

        r_rsip_func_sub011(0x000001c1U, 0x00008000U, 0x0e128455U);
        WR2_ADDR(REG_002CH, &InData_DataALen[0]);

        r_rsip_func_sub012(0x81020040U, 0x00490009U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        WR1_PROG(REG_0094H, 0x0000b420U);
        r_rsip_func_sub007(0x00000010U, 0x81840001U, 0x00490011U);

        r_rsip_func_sub008(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_00D4H, 0x40000020U);
        r_rsip_func_sub013(0x07008d05U, 0x00410011U);

        r_rsip_func_sub007(0x00000821U, 0x80840001U, 0x03410011U);

        WR1_PROG(REG_0094H, 0x00000884U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            r_rsip_func_sub022(0x3c002825U, 0x12003c81U, 0x00002c20U);
        }

        r_rsip_func_sub019(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_002CH, &InData_DataT[0]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        r_rsip_func_sub007(0x00000821U, 0x81840001U, 0x00490011U);

        r_rsip_func100(bswap_32big(0xeb90bf07U), bswap_32big(0x73bcf80dU), bswap_32big(0x76b4dc4fU),
                       bswap_32big(0x499f1876U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x93b11b33U), bswap_32big(0x36526ec6U), bswap_32big(0x85ef3364U),
                           bswap_32big(0xeedaccc3U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_AUTH_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0xb0f7d203U), bswap_32big(0xa7329d2fU), bswap_32big(0x02baa06eU),
                           bswap_32big(0xe6e95bfcU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
