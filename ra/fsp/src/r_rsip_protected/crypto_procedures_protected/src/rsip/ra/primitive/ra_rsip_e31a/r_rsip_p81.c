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

    if (RD1_MASK(REG_0090H, 0xFFFFFFFFU) != 0x000D8087U)
    {
        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_000CH, 0x38c60eedU);
        WR1_PROG(REG_0048H, 0x00000000U);

        WR1_PROG(REG_0008H, 0x00000001U);
        WR1_PROG(REG_0010H, 0x00001401U);

        if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
        {
            return RSIP_RET_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_00C0H, 0x00000001U);
        WR1_PROG(REG_00E0H, 0x00000001U);

        WR1_PROG(REG_0070H, 0x00818001U);
        WR1_PROG(REG_0078H, 0x00000d00U);

        WR1_PROG(REG_00C4H, 0x00008003U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        r_rsip_func101(0x31abdad9U, 0xe2670818U, 0xa1798641U, 0xdfe2b0baU);
        WR1_PROG(REG_00C4H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x0a0700f5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, 0x8c789bd1U, 0x86be0420U, 0x0861c081U, 0x52317426U);

        r_rsip_func101(0x62898deaU, 0x6230c402U, 0x7f8ae49dU, 0x1fd2fe86U);

        r_rsip_func100(0x5eb18f89U, 0x06980d12U, 0x49433099U, 0xdc4d05f9U);

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

            r_rsip_func102(0xd519a52aU, 0x9b8a8615U, 0xf5ec9053U, 0x62c65350U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
