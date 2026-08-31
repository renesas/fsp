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

void r_rsip_func415 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub025(0x0000379dU, 0x0000b420U, 0x203e6d8dU);

    r_rsip_func_sub010(0x000000c7U, 0x800100e0U);
    WR1_PROG(REG_1420H, ARG1[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func_sub003(0x000000a7U, 0x800103a0U, 0x0000f415U);

    static const uint32_t Param_func415_func101_001[] =
    {
        BSWAP_32BIG_C(0x6ea44668U), BSWAP_32BIG_C(0x3ee863f3U), BSWAP_32BIG_C(0x3206a9eeU), BSWAP_32BIG_C(0xe24cf78dU), 
    };
    r_rsip_func101(Param_func415_func101_001);
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x01799093U);

    r_rsip_func_sub003(0x000000a7U, 0x800103a0U, 0x0000f415U);

    static const uint32_t Param_func415_func101_002[] =
    {
        BSWAP_32BIG_C(0xf454693bU), BSWAP_32BIG_C(0xe1d49ac8U), BSWAP_32BIG_C(0x6c962f3bU), BSWAP_32BIG_C(0x7c4191e7U), 
    };
    r_rsip_func101(Param_func415_func101_002);
    r_rsip_func044();

    r_rsip_func_sub025(0x0000b4e0U, 0x00000010U, 0x000038a7U);

    static const uint32_t Param_func415_func100_001[] =
    {
        BSWAP_32BIG_C(0x2bdbdbfbU), BSWAP_32BIG_C(0xd9b200c2U), BSWAP_32BIG_C(0x9c8c01d2U), BSWAP_32BIG_C(0x10d01fc2U), 
    };
    r_rsip_func100(Param_func415_func100_001);

    r_rsip_func_sub014(0x00007c05U, 0x00600000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func_sub008(0x000007c2U, 0x40000100U, 0xf7009d07U);
        WR4_ADDR(REG_1420H, &ARG1[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG1[5]);

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func_sub001(0x00c20021U);

        r_rsip_func_sub008(0x000003c2U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_1420H, &ARG1[9]);

        static const uint32_t Param_func415_func101_003[] =
        {
            BSWAP_32BIG_C(0x7cbf47deU), BSWAP_32BIG_C(0x8d3f301cU), BSWAP_32BIG_C(0xabe11aabU), BSWAP_32BIG_C(0xc4862812U), 
        };
        r_rsip_func101(Param_func415_func101_003);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func_sub023(0x00000bc2U, 0x40000200U, 0xf7009d07U);

        for (iLoop = 0U; iLoop < 12U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG1[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func_sub001(0x00c20031U);

        r_rsip_func_sub008(0x000003c2U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_1420H, &ARG1[13]);

        static const uint32_t Param_func415_func101_004[] =
        {
            BSWAP_32BIG_C(0x86d7196bU), BSWAP_32BIG_C(0xb9b47df9U), BSWAP_32BIG_C(0x31c7c98eU), BSWAP_32BIG_C(0x231d9905U), 
        };
        r_rsip_func101(Param_func415_func101_004);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func_sub006(0x38008880U, 0x00000040U, 0x00260000U);

        static const uint32_t Param_func415_func100_002[] =
        {
            BSWAP_32BIG_C(0x51d041aaU), BSWAP_32BIG_C(0x55b81d0aU), BSWAP_32BIG_C(0x8f83c1a1U), BSWAP_32BIG_C(0xea093eefU), 
        };
        r_rsip_func100(Param_func415_func100_002);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func_sub023(0x00000fc2U, 0x40000300U, 0xf7009d07U);

            WR1_PROG(REG_1404H, 0x10000000U);
            for (iLoop = 0U; iLoop < 16U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &ARG1[1 + iLoop]);
                r_rsip_func_sub001(0x00c20011U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func_sub008(0x000003c2U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_1420H, &ARG1[17]);

            static const uint32_t Param_func415_func101_005[] =
            {
                BSWAP_32BIG_C(0xc26fb3d5U), BSWAP_32BIG_C(0xe1b85f69U), BSWAP_32BIG_C(0x8c4134c3U), BSWAP_32BIG_C(0x7e8b368bU), 
            };
            r_rsip_func101(Param_func415_func101_005);
        }
        else
        {
            r_rsip_func_sub023(0x000013c2U, 0x40000400U, 0xf7009d07U);

            WR1_PROG(REG_1404H, 0x10000000U);
            for (iLoop = 0U; iLoop < 20; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &ARG1[1 + iLoop]);
                r_rsip_func_sub001(0x00c20011U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func_sub008(0x000003c2U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_1420H, &ARG1[21]);

            static const uint32_t Param_func415_func101_006[] =
            {
                BSWAP_32BIG_C(0x8e7f268dU), BSWAP_32BIG_C(0x606d200eU), BSWAP_32BIG_C(0xd91828bfU), BSWAP_32BIG_C(0x936d67b4U), 
            };
            r_rsip_func101(Param_func415_func101_006);
        }
    }

    WR1_PROG(REG_1A24H, 0x9c100005U);
    r_rsip_func_sub001(0x00820011U);

    static const uint32_t Param_func415_func100_003[] =
    {
        BSWAP_32BIG_C(0x58e9ecb9U), BSWAP_32BIG_C(0x66d2c01bU), BSWAP_32BIG_C(0x881cee8dU), BSWAP_32BIG_C(0x046d015aU), 
    };
    r_rsip_func100(Param_func415_func100_003);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x00000821U);
        static const uint32_t Param_func415_func101_007[] =
        {
            BSWAP_32BIG_C(0x07360a23U), BSWAP_32BIG_C(0x2f639f26U), BSWAP_32BIG_C(0x7ef42ab3U), BSWAP_32BIG_C(0x775e771aU), 
        };
        r_rsip_func101(Param_func415_func101_007);
    }

    r_rsip_func_sub006(0x38008820U, 0x203e6d8dU, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x000037bcU);

    r_rsip_func_sub014(0x00007c1dU, 0x00602000U);
}
