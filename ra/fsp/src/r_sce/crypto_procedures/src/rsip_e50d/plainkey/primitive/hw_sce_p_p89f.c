/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0x3fc2a091U, 0xa58443b0U, 0x3453d34aU, 0x7c364da4U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0xf629e0d0U, 0x4f88a95aU, 0x464333d5U, 0x9587ea79U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0xd44edda9U, 0x77a3dd8cU, 0x4d7bfe12U, 0x04cd1a24U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x156c06cdU, 0x9dce9f3eU, 0xdeac5c7eU, 0x39e25debU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0x1c3627d0U, 0x9e52f952U, 0xd84eaeeaU, 0x9239b06dU);
    }
    else
    {
        ;
    }

    HW_SCE_p_func102(0x19bdc039U, 0xfb31d0d7U, 0xed8525d6U, 0x6d927bd2U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}

