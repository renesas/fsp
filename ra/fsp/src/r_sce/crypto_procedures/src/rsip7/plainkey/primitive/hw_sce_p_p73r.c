/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestResumeSub (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00730001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x7f797d3fU, 0x084303d5U, 0xd4bb5ca2U, 0x798174fdU);
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00001000U);

        HW_SCE_p_func101(0xa52081c3U, 0x704a846cU, 0x6d1c4051U, 0x39f652c7U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00001040U);

        HW_SCE_p_func101(0xeacc224fU, 0x5c6dc8bdU, 0x78256838U, 0xd19c02c1U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00001050U);

        HW_SCE_p_func101(0xdb8d6e66U, 0x2b18612dU, 0x40a3e6f9U, 0x119f4b11U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00001080U);

        HW_SCE_p_func101(0xa0531910U, 0xe623c802U, 0xf57fae6dU, 0x404a893eU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00001090U);

        HW_SCE_p_func101(0xc83d204cU, 0xaaa9bb18U, 0x774f3d9dU, 0x479bd9cfU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000010a0U);

        HW_SCE_p_func101(0x8361cba1U, 0x651b5a0dU, 0xb7d1227cU, 0x9328ec50U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000010b0U);

        HW_SCE_p_func101(0xfb746668U, 0xfd9d6868U, 0xb4881592U, 0x8bfad6f8U);
    }

    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2014H, InData_State[18]);
    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2010H, InData_State[19]);

    for (iLoop = 0U; iLoop < 18U; iLoop++)
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2028H, InData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x8118c984U, 0xb9ebccbaU, 0x168cc13aU, 0xc1818490U);

    return FSP_SUCCESS;
}
