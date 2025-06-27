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

rsip_ret_t r_rsip_p81 (void)
{
    WR1_PROG(REG_1D04H, 0x0008eff4U);
    WR1_PROG(REG_1D08H, 0x000ce801U);

    WR1_PROG(REG_1D00H, 0x00000001U);

    WAIT_STS(REG_1D00H, 1, 0);

    if (RD1_MASK(REG_1D00H, 0x00030000U) != 0x00000000U)
    {
        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_140CH, 0x38c60eedU);
        WR1_PROG(REG_1448H, 0x00000000U);

        WR1_PROG(REG_1408H, 0x00000001U);
        WR1_PROG(REG_1414H, 0x00001401U);

        if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
        {
            return RSIP_RET_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_1800H, 0x00000001U);
        WR1_PROG(REG_1700H, 0x00000001U);

        WR1_PROG(REG_1B00H, 0x00818001U);
        WR1_PROG(REG_1B08H, 0x00000d00U);

        WR1_PROG(REG_1804H, 0x00008003U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        r_rsip_func101(0x7b32b49dU, 0x44008805U, 0xcbcc8015U, 0x30853d95U);
        WR1_PROG(REG_1804H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x0a0700f5U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, 0x19ad4ea4U, 0x5ffc9cf9U, 0xa84d0839U, 0x1c6cb358U);
        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000900U);

        r_rsip_func101(0x23164eefU, 0xdbc9411fU, 0x16e70254U, 0x4d9452eeU);

        r_rsip_func100(0x2f59c033U, 0x2f1fbbc4U, 0xc208c759U, 0xc9b1a43aU);

        WR1_PROG(REG_1408H, 0x00020000U);

        if (CHCK_STS(REG_142CH, 13, 0))
        {
            WR1_PROG(REG_14BCH, 0x00000020U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1430H, 0x0000FFFFU);

            WR1_PROG(REG_1B08H, 0x00000220U);

            r_rsip_func102(0x157dae9eU, 0x6db19678U, 0x334d88c1U, 0xe66cddc8U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
