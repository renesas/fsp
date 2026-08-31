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

void r_rsip_func416 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_2030H, 0, 1);

    r_rsip_func_sub017(0x38000c63U, 0x00A60000U);

    static const uint32_t Param_func416_func100_001[] =
    {
        BSWAP_32BIG_C(0xb3312033U), BSWAP_32BIG_C(0x63052dc7U), BSWAP_32BIG_C(0xb6b6989dU), BSWAP_32BIG_C(0x45c7d7b9U), 
    };
    r_rsip_func100(Param_func416_func100_001);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func_sub010(0x000000c7U, 0x800103e0U);
        WR1_PROG(REG_1420H, ARG1[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x810103e0U);
        r_rsip_func_sub001(0x11490011U);

        static const uint32_t Param_func416_func101_001[] =
        {
            BSWAP_32BIG_C(0xa1e476e2U), BSWAP_32BIG_C(0xc411e54bU), BSWAP_32BIG_C(0xa5ac3493U), BSWAP_32BIG_C(0x5bf214f8U), 
        };
        r_rsip_func101(Param_func416_func101_001);
    }

    r_rsip_func_sub017(0x38000c84U, 0x00A60000U);

    static const uint32_t Param_func416_func100_002[] =
    {
        BSWAP_32BIG_C(0x79bb5c3bU), BSWAP_32BIG_C(0x11199447U), BSWAP_32BIG_C(0x9a6b9594U), BSWAP_32BIG_C(0x499c8ddbU), 
    };
    r_rsip_func100(Param_func416_func100_002);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        static const uint32_t Param_func416_func100_003[] =
        {
            BSWAP_32BIG_C(0xffb9ebcaU), BSWAP_32BIG_C(0x93253c48U), BSWAP_32BIG_C(0xd090f24bU), BSWAP_32BIG_C(0x29f4b997U), 
        };
        r_rsip_func100(Param_func416_func100_003);

        r_rsip_func_sub014(0x00007c05U, 0x00600000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_1404H, 0x10000000U);
            r_rsip_func_sub001(0x11430081U);

            static const uint32_t Param_func416_func101_002[] =
            {
                BSWAP_32BIG_C(0xe3a56c56U), BSWAP_32BIG_C(0x75a596d9U), BSWAP_32BIG_C(0x525444deU), BSWAP_32BIG_C(0xd16e8a5eU), 
            };
            r_rsip_func101(Param_func416_func101_002);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_1404H, 0x10000000U);
            r_rsip_func_sub001(0x114300c1U);

            static const uint32_t Param_func416_func101_003[] =
            {
                BSWAP_32BIG_C(0x6646c9caU), BSWAP_32BIG_C(0x2e08bc54U), BSWAP_32BIG_C(0x331563c9U), BSWAP_32BIG_C(0x045b0b9bU), 
            };
            r_rsip_func101(Param_func416_func101_003);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func_sub006(0x38008880U, 0x00000040U, 0x00260000U);

            static const uint32_t Param_func416_func100_004[] =
            {
                BSWAP_32BIG_C(0x400d4a8aU), BSWAP_32BIG_C(0xcf8a6928U), BSWAP_32BIG_C(0x91661461U), BSWAP_32BIG_C(0xc21deccaU), 
            };
            r_rsip_func100(Param_func416_func100_004);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1404H, 0x10000000U);
                r_rsip_func_sub001(0x11430101U);

                static const uint32_t Param_func416_func101_004[] =
                {
                    BSWAP_32BIG_C(0xb718c62fU), BSWAP_32BIG_C(0xec22d2c3U), BSWAP_32BIG_C(0x434f9394U), BSWAP_32BIG_C(0x6084555bU), 
                };
                r_rsip_func101(Param_func416_func101_004);
            }
            else
            {
                WR1_PROG(REG_1404H, 0x10000000U);
                r_rsip_func_sub001(0x11430109U);
                r_rsip_func_sub001(0x10030039U);

                static const uint32_t Param_func416_func101_005[] =
                {
                    BSWAP_32BIG_C(0x410b1ba6U), BSWAP_32BIG_C(0x41e14a89U), BSWAP_32BIG_C(0x562119a3U), BSWAP_32BIG_C(0xbe9686f1U), 
                };
                r_rsip_func101(Param_func416_func101_005);
            }
        }
    }

    static const uint32_t Param_func416_func100_005[] =
    {
        BSWAP_32BIG_C(0x8ca83da1U), BSWAP_32BIG_C(0xf97145a1U), BSWAP_32BIG_C(0x549132bcU), BSWAP_32BIG_C(0x8b7fa549U), 
    };
    r_rsip_func100(Param_func416_func100_005);

    WR1_PROG(REG_1600H, 0x00003408U);
    WR1_PROG(REG_1600H, 0x00026808U);

    r_rsip_func_sub016(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
    {
        r_rsip_func_sub010(0x000000c7U, 0x800103e0U);
        WR1_PROG(REG_1420H, ARG2[iLoop]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x810103e0U);
        r_rsip_func_sub001(0x11490011U);

        static const uint32_t Param_func416_func101_006[] =
        {
            BSWAP_32BIG_C(0x73a0403eU), BSWAP_32BIG_C(0x10716486U), BSWAP_32BIG_C(0xeef060ffU), BSWAP_32BIG_C(0xe47b7709U), 
        };
        r_rsip_func101(Param_func416_func101_006);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func_sub006(0x08008d00U, 0x00000003U, 0x00A60000U);

    static const uint32_t Param_func416_func100_006[] =
    {
        BSWAP_32BIG_C(0x8c31e16fU), BSWAP_32BIG_C(0x85434857U), BSWAP_32BIG_C(0x94ee94beU), BSWAP_32BIG_C(0xb2bfd999U), 
    };
    r_rsip_func100(Param_func416_func100_006);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        static const uint32_t Param_func416_func100_007[] =
        {
            BSWAP_32BIG_C(0x04720e7eU), BSWAP_32BIG_C(0xdea7a519U), BSWAP_32BIG_C(0x023e8682U), BSWAP_32BIG_C(0xb9531306U), 
        };
        r_rsip_func100(Param_func416_func100_007);
        r_rsip_func_sub010(0x000000c7U, 0x800103e0U);
        WR1_PROG(REG_1420H, ARG2[iLoop]);
        WR1_PROG(REG_1458H, 0x00000000U);
        iLoop = iLoop + 1;

        r_rsip_func_sub016(0x81010100U, 0x00005006U);
        RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
        S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

        for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
        {
            WR1_PROG(REG_1608H, 0x810103e0U);
            r_rsip_func_sub001(0x11490005U);
            r_rsip_func_sub001(0x1009000dU);
            WR1_PROG(REG_1600H, 0x00086fffU);
            WR1_PROG(REG_1600H, 0x00003100U);

            static const uint32_t Param_func416_func101_007[] =
            {
                BSWAP_32BIG_C(0x89d26c10U), BSWAP_32BIG_C(0xb2eae8edU), BSWAP_32BIG_C(0xcb2245e3U), BSWAP_32BIG_C(0x59f15929U), 
            };
            r_rsip_func101(Param_func416_func101_007);
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func_sub014(0x00007c08U, 0x00602000U);

        static const uint32_t Param_func416_func101_008[] =
        {
            BSWAP_32BIG_C(0x0ec9b2fbU), BSWAP_32BIG_C(0x462f7765U), BSWAP_32BIG_C(0x2053994eU), BSWAP_32BIG_C(0x1851fafaU), 
        };
        r_rsip_func101(Param_func416_func101_008);
    }

    WAIT_STS(REG_2030H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001600U);

    r_rsip_func_sub014(0x00007c1dU, 0x00602000U);
}
