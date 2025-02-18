/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0xf5ed4b89U, 0xc35d7813U, 0x6077b61fU, 0x2454cdacU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0xc356f587U, 0xb892e933U, 0xfdd4816eU, 0x9c286438U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x87e6e6aeU, 0x6de43fe6U, 0x040fe532U, 0xa2c67e23U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x9ee1cb73U, 0x263a4efeU, 0xf338601aU, 0xd8ac1517U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0xda0befdcU, 0xeada4bb9U, 0x07ab6353U, 0xe6653c81U);
    }

    HW_SCE_p_func102(0x191bbdcdU, 0xe6b5fd44U, 0x0a44793dU, 0xec04dd68U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
