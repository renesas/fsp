/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0x21dc6aa3U, 0x017e4d31U, 0x46bbcfb7U, 0xe0f6e464U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0xa54452d6U, 0x60a6e71fU, 0xbe6efe10U, 0x7d733132U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x1cd30caeU, 0xf5872021U, 0x2340e41eU, 0xc5f390f0U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x9fdae256U, 0x46508d25U, 0x45091d6bU, 0x117e4230U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0x443d2831U, 0x4c64d2a9U, 0x554c54d4U, 0xe68f937fU);
    }
    else
    {
        ;
    }

    HW_SCE_p_func102(0xb611ddefU, 0xee31bfa6U, 0xee97e815U, 0xd5a7c6a1U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}

