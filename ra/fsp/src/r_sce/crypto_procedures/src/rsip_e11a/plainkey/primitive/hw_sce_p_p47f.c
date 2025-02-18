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
        HW_SCE_p_func101(0xa9559b66U, 0x156b47bcU, 0xc0b4e84cU, 0xbcd053a0U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0xdffb3428U, 0x817d47aaU, 0xc4234844U, 0x1a7eab9cU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x9577d73cU, 0xa18dd8cbU, 0xf769491aU, 0x007a991eU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0xae8d48cfU, 0xa816d95bU, 0x7b55232fU, 0xd32f64b0U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0xeca9b298U, 0x24cee46aU, 0x9e640167U, 0xb0df14f6U);
    }

    HW_SCE_p_func102(0x2ed698bcU, 0x3b2e1938U, 0x41ea3d5aU, 0x86cac3a4U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
