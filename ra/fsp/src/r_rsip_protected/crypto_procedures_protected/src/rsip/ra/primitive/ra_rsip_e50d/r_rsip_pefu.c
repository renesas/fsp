/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pefu (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[])
{
    r_rsip_func_sub010(0x000002c7U, 0x80030060U);
    WR1_PROG(REG_1420H, InData_Msg1Length[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_EncMsgLength[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Msg2Length[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func_sub006(0x38008c60U, 0xfffffffeU, 0x00A60000U);

    r_rsip_func_sub021(0x00003423U, 0x00026c21U, 0x00002424U, 0x00002425U);

    static const uint32_t Param_pefu_func100_001[] =
    {
        BSWAP_32BIG_C(0xc2e738d1U), BSWAP_32BIG_C(0x2362296eU), BSWAP_32BIG_C(0x6e7cdf0eU), BSWAP_32BIG_C(0xc66bf535U), 
    };
    r_rsip_func100(Param_pefu_func100_001);
    r_rsip_func_sub014(0x00007c00U, 0x00600000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func_sub006(0x38008c80U, 0xffffffdfU, 0x00A60000U);

        r_rsip_func_sub006(0x38008c20U, 0x0000003fU, 0x00A60000U);

        static const uint32_t Param_pefu_func101_001[] =
        {
            BSWAP_32BIG_C(0xbee42905U), BSWAP_32BIG_C(0x78806118U), BSWAP_32BIG_C(0xe730fa01U), BSWAP_32BIG_C(0xa18b7250U), 
        };
        r_rsip_func101(Param_pefu_func101_001);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func_sub022(0x38000c84U, 0x00020020U, 0x38008880U);
        r_rsip_func_sub006(0x00000030U, 0x00000080U, 0x00A60000U);

        r_rsip_func_sub006(0x38008c20U, 0x0000007fU, 0x00A60000U);

        static const uint32_t Param_pefu_func101_002[] =
        {
            BSWAP_32BIG_C(0x19574cb3U), BSWAP_32BIG_C(0xf0c67333U), BSWAP_32BIG_C(0x881da685U), BSWAP_32BIG_C(0xb4c6c302U), 
        };
        r_rsip_func101(Param_pefu_func101_002);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func_sub021(0x38008c80U, 0xffffffbfU, 0x00020020U, 0x38008880U);
        r_rsip_func_sub006(0x00000042U, 0x00000080U, 0x00A60000U);

        r_rsip_func_sub006(0x38008c20U, 0x0000007fU, 0x00A60000U);

        static const uint32_t Param_pefu_func101_003[] =
        {
            BSWAP_32BIG_C(0xd4402460U), BSWAP_32BIG_C(0x354b4cd6U), BSWAP_32BIG_C(0x22b1ea74U), BSWAP_32BIG_C(0x5c72b17dU), 
        };
        r_rsip_func101(Param_pefu_func101_003);
    }

    static const uint32_t Param_pefu_func100_002[] =
    {
        BSWAP_32BIG_C(0xdf3b3537U), BSWAP_32BIG_C(0xff9e4402U), BSWAP_32BIG_C(0x76d5381bU), BSWAP_32BIG_C(0x45e54921U), 
    };
    r_rsip_func100(Param_pefu_func100_002);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        static const uint32_t Param_pefu_func102_001[] =
        {
            BSWAP_32BIG_C(0x94f24b7bU), BSWAP_32BIG_C(0x5adde9deU), BSWAP_32BIG_C(0x629a27a7U), BSWAP_32BIG_C(0xf4c22bf6U), 
        };
        r_rsip_func102(Param_pefu_func102_001);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub006(0x00003505U, 0x38000c84U, 0x00A60000U);

        static const uint32_t Param_pefu_func100_003[] =
        {
            BSWAP_32BIG_C(0x09c3c4fbU), BSWAP_32BIG_C(0x54a71103U), BSWAP_32BIG_C(0x9ab50665U), BSWAP_32BIG_C(0xc76f6e55U), 
        };
        r_rsip_func100(Param_pefu_func100_003);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func_sub003(0x800103a0U, 0x0000ef01U);

            static const uint32_t Param_pefu_func101_004[] =
            {
                BSWAP_32BIG_C(0x4c5fd260U), BSWAP_32BIG_C(0xa363fe1aU), BSWAP_32BIG_C(0x1ae95246U), BSWAP_32BIG_C(0x66ca2810U), 
            };
            r_rsip_func101(Param_pefu_func101_004);
            r_rsip_func415(InData_EncMsg);

            static const uint32_t Param_pefu_func101_005[] =
            {
                BSWAP_32BIG_C(0xddff47eeU), BSWAP_32BIG_C(0x104e853dU), BSWAP_32BIG_C(0x4b1bde6aU), BSWAP_32BIG_C(0x120ea8a0U), 
            };
            r_rsip_func101(Param_pefu_func101_005);
        }

        static const uint32_t Param_pefu_func100_004[] =
        {
            BSWAP_32BIG_C(0xe90c35f0U), BSWAP_32BIG_C(0x5663aac4U), BSWAP_32BIG_C(0x8456fa42U), BSWAP_32BIG_C(0xd6a464c6U), 
        };
        r_rsip_func100(Param_pefu_func100_004);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            static const uint32_t Param_pefu_func102_002[] =
            {
                BSWAP_32BIG_C(0x1249e7aeU), BSWAP_32BIG_C(0x9f1ec7cbU), BSWAP_32BIG_C(0x562ed345U), BSWAP_32BIG_C(0x8071e667U), 
            };
            r_rsip_func102(Param_pefu_func102_002);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub003(0x800103a0U, 0x0000ef01U);

            static const uint32_t Param_pefu_func101_006[] =
            {
                BSWAP_32BIG_C(0x2122a97eU), BSWAP_32BIG_C(0x80907ea8U), BSWAP_32BIG_C(0x38aab6cbU), BSWAP_32BIG_C(0x679d9b38U), 
            };
            r_rsip_func101(Param_pefu_func101_006);
            r_rsip_func416(InData_Msg1, InData_Msg2);

            r_rsip_func_sub022(0x0000b420U, 0x00000010U, 0x00003801U);

            static const uint32_t Param_pefu_func101_007[] =
            {
                BSWAP_32BIG_C(0x193e1823U), BSWAP_32BIG_C(0x787a667dU), BSWAP_32BIG_C(0xb09d685dU), BSWAP_32BIG_C(0x0cd49c77U), 
            };
            r_rsip_func101(Param_pefu_func101_007);

            return RSIP_RET_PASS;
        }
    }
}
