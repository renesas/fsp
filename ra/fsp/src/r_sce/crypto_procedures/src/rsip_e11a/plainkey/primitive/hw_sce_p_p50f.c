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
        0x7231c174U, 0x1901f47eU, 0xa4af64f1U, 0xc10a24d1U,
    };
    HW_SCE_p_func102(Param_p50f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
