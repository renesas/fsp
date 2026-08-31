/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    static const uint32_t Param_p47f_func102_001[] =
    {
        0xddb4b6b4U, 0xce4cb5f2U, 0xcd9e1213U, 0x8c342fefU,
    };
    HW_SCE_p_func102(Param_p47f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
