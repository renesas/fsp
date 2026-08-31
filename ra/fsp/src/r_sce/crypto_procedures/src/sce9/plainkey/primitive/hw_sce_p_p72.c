/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha224256GenerateMessageDigestSub (const uint32_t InData_InitVal[],
                                                    const uint32_t InData_PaddedMsg[],
                                                    uint32_t       MAX_CNT,
                                                    uint32_t       OutData_MsgDigest[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00007201U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p72_func100_001[] =
    {
        0x89b55281U, 0x097f6146U, 0xd6a77de8U, 0xec3b48deU,
    };
    HW_SCE_p_func100(Param_p72_func100_001);

    WR1_PROG(REG_7CH, 0x00000011U);

    WR1_PROG(REG_104H, 0x00000764U);
    WR1_PROG(REG_74H, 0x00000004U);
    WAIT_STS(REG_104H, 31, 1);
    WR8_ADDR(REG_100H, &InData_InitVal[0]);

    WR1_PROG(REG_104H, 0x000000b4U);
    WR1_PROG(REG_74H, 0x08000002U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR16_ADDR(REG_100H, &InData_PaddedMsg[0 + iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_74H, 18, 0);
    WR1_PROG(REG_74H, 0x00000000U);
    WR1_PROG(REG_104H, 0x00000000U);

    WR1_PROG(REG_1CH, 0x00001600U);

    WR1_PROG(REG_74H, 0x00000008U);
    WR1_PROG(REG_04H, 0x00000523U);
    WAIT_STS(REG_04H, 30, 1);
    RD8_ADDR(REG_100H, &OutData_MsgDigest[0]);

    static const uint32_t Param_p72_func102_001[] =
    {
        0x482a4372U, 0x21f251ebU, 0x29dc06a6U, 0x84167a56U,
    };
    HW_SCE_p_func102(Param_p72_func102_001);

    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
