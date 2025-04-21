/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestFinalSub (const uint32_t InData_Msg[],
                                                   uint32_t       OutData_MsgDigest[],
                                                   const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WAIT_STS(REG_118H, 0, 1);

    WR1_PROG(REG_14H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR16_ADDR(REG_2CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_14H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_2CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_14H, 0x00000000U);
    WAIT_STS(REG_118H, 8, 0);
    WR1_PROG(REG_40H, 0x00001600U);

    WAIT_STS(REG_118H, 4, 1);

    HW_SCE_p_func100(0x0a6815fdU, 0x757d2026U, 0x003fe7a7U, 0x863c6377U);
    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x1000b400U);
    WR1_PROG(REG_94H, 0x00000001U);

    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x00000004U);
    WR1_PROG(REG_94H, 0x1000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_94H, 0x00007c00U);
    WR1_PROG(REG_40H, 0x00600000U);

    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func100(0xede8fbc9U, 0xd07b4987U, 0x2f7dcb5cU, 0x46bfda9eU);
        WR1_PROG(REG_08H, 0x0000401eU);
        WAIT_STS(REG_08H, 30, 1);
        RD7_ADDR(REG_2CH, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xfc023ccfU, 0xd3595441U, 0xcfa3b025U, 0x4a65d1f2U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func100(0x5759f702U, 0x944148e2U, 0x17b012d9U, 0x4f714125U);
        WR1_PROG(REG_08H, 0x00004022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x492edd28U, 0x0f56ed85U, 0x28484885U, 0xb2187087U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
    {
        HW_SCE_p_func100(0xbf478bdfU, 0x53cf1ab5U, 0xd2196661U, 0x650743d1U);
        WR1_PROG(REG_08H, 0x00004032U);
        WAIT_STS(REG_08H, 30, 1);
        RD12_ADDR(REG_2CH, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xa9618cdcU, 0x85b9d121U, 0x4b174196U, 0xc58e26d4U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
    {
        HW_SCE_p_func100(0x280d53deU, 0xcdedb527U, 0x919e798eU, 0x061079a4U);
        WR1_PROG(REG_08H, 0x00004042U);
        WAIT_STS(REG_08H, 30, 1);
        RD16_ADDR(REG_2CH, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x5ed823c8U, 0x9f80dde1U, 0x15041878U, 0xa476e732U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);
    }

    return FSP_SUCCESS;
}
