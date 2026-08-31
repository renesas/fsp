/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    static const uint32_t Param_p50f_func102_001[] =
    {
        0x4128e7b0U, 0x3100b291U, 0xdf3757e9U, 0xf1a72ba7U,
    };
    HW_SCE_p_func102(Param_p50f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
