/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestSub (const uint32_t InData_InitVal[],
                                              const uint32_t InData_PaddedMsg[],
                                              uint32_t       OutData_MsgDigest[],
                                              const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_68H, 0x00000016U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00720001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_F4H, 0x00000010U);

    WAIT_STS(REG_F8H, 0, 1);

    WR1_PROG(REG_14H, 0x000007c4U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_InitVal[0]);

    WR1_PROG(REG_F4H, 0x00000011U);

    WAIT_STS(REG_F8H, 0, 1);

    WR1_PROG(REG_14H, 0x00000064U);
    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR16_ADDR(REG_2CH, &InData_PaddedMsg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_F8H, 2, 0);

    WR1_PROG(REG_14H, 0x00000000U);

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_F4H, 0x00000020U);

    WAIT_STS(REG_F8H, 1, 1);

    HW_SCE_p_func100(0x345f6e95U, 0xd7b24623U, 0x9a61bfd4U, 0x8761df09U);
    WR1_PROG(REG_08H, 0x00004022U);
    WAIT_STS(REG_08H, 30, 1);
    RD8_ADDR(REG_2CH, &OutData_MsgDigest[0]);

    HW_SCE_p_func102(0xb6abe216U, 0xcdc58683U, 0x8c62c3dfU, 0x3b148ae0U);
    WR1_PROG(REG_68H, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
