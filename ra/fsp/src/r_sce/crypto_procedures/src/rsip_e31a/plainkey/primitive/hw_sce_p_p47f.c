/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0xda1adf84U, 0xc29d2b7fU, 0x4db61339U, 0x930e3311U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0x2a76b8ceU, 0x29d6331dU, 0x044c251dU, 0xabe7f3d3U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x69c37bfbU, 0x559e98d9U, 0x4f91f7f2U, 0x94ab7b29U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0xbe886957U, 0xba679820U, 0x06f991f0U, 0xcca8ae22U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0x7b59b54bU, 0xfcaac2c0U, 0x43230e84U, 0x3a260a2dU);
    }

    HW_SCE_p_func102(0xe499f904U, 0xb0f38bd3U, 0x83f4cac9U, 0x096259ccU);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
