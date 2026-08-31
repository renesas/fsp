/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        static const uint32_t Param_p50f_func101_001[] =
        {
            0xa53a714eU, 0xce2b3fd6U, 0x3801fd1bU, 0xa2b83ef5U,
        };
        HW_SCE_p_func101(Param_p50f_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        static const uint32_t Param_p50f_func101_002[] =
        {
            0x82fe7aceU, 0xacd65af6U, 0x959bdef5U, 0x8e151cecU,
        };
        HW_SCE_p_func101(Param_p50f_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        static const uint32_t Param_p50f_func101_003[] =
        {
            0x0863ac10U, 0x4a52da44U, 0xd5687f54U, 0x4962b267U,
        };
        HW_SCE_p_func101(Param_p50f_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        static const uint32_t Param_p50f_func101_004[] =
        {
            0xcd1f7364U, 0xc1420ba6U, 0x87d65bffU, 0xb3858d7fU,
        };
        HW_SCE_p_func101(Param_p50f_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        static const uint32_t Param_p50f_func101_005[] =
        {
            0x39f66ff5U, 0x749d4554U, 0x3bed7a06U, 0xf39940faU,
        };
        HW_SCE_p_func101(Param_p50f_func101_005);
    }

    static const uint32_t Param_p50f_func100_001[] =
    {
        0x2b31b234U, 0x798ccde6U, 0x81ae9de2U, 0x634149d6U,
    };
    HW_SCE_p_func100(Param_p50f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p50f_func102_001[] =
        {
            0x7d67ba6dU, 0x40f2ca12U, 0x3fc845eaU, 0xccc18a2eU,
        };
        HW_SCE_p_func102(Param_p50f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p50f_func102_002[] =
        {
            0xda587a2aU, 0x27b36189U, 0x2078e407U, 0xeeeb0a36U,
        };
        HW_SCE_p_func102(Param_p50f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
