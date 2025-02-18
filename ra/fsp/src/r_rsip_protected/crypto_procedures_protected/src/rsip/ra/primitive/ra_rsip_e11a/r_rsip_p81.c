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
    WR1_PROG(REG_008CH, 0x00000001U);

    WAIT_STS(REG_008CH, 1, 0);

    if (RD1_MASK(REG_0090H, 0xFFFFFFFFU) != 0x00047C00U)
    {
        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_000CH, 0x38c60eedU);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0048H, 0x00000000U);

        WR1_PROG(REG_0008H, 0x00000001U);
        WR1_PROG(REG_0010H, 0x00001401U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
        {
            return RSIP_RET_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_00C0H, 0x00000001U);
        WR1_PROG(REG_00E0H, 0x00000001U);
        WR1_PROG(REG_00F0H, 0x00000001U);

        WR1_PROG(REG_0070H, 0x00818001U);
        WR1_PROG(REG_0078H, 0x00000d00U);

        WR1_PROG(REG_00C4H, 0x00008001U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        r_rsip_func101(0xc2be509fU, 0xced517cdU, 0xe0f616a8U, 0x0edb670fU);
        WR1_PROG(REG_00C4H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x0a0700f5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, 0xf2c2f7bbU, 0x2459a06dU, 0x47b0dadeU, 0x4cbf533bU);

        r_rsip_func101(0xe3d3c322U, 0xae15fea9U, 0x9c1e7c17U, 0x43fe16a3U);

        r_rsip_func100(0xf4497efaU, 0x1854b776U, 0xd4dbc516U, 0x66431440U);

        WR1_PROG(REG_0008H, 0x00020000U);

        if (CHCK_STS(REG_0020H, 13, 0))
        {
            WR1_PROG(REG_006CH, 0x00000020U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0038H, 0x000000F1U);

            WR1_PROG(REG_0078H, 0x00000220U);

            r_rsip_func102(0x2c9cbb4bU, 0xfb4b02c4U, 0x7c92fe57U, 0xea9c1756U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
