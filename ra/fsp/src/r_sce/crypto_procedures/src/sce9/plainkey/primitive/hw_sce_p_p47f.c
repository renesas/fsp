/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        static const uint32_t Param_p47f_func101_001[] =
        {
            0x2567e134U, 0x1c59a254U, 0x33a91a4aU, 0x06f2d769U,
        };
        HW_SCE_p_func101(Param_p47f_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        static const uint32_t Param_p47f_func101_002[] =
        {
            0xaeef1b59U, 0xa2d2eaadU, 0x59797dcdU, 0x3d305810U,
        };
        HW_SCE_p_func101(Param_p47f_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        static const uint32_t Param_p47f_func101_003[] =
        {
            0x39200434U, 0x3a9b8bf3U, 0x9bd38d07U, 0xf8813cd9U,
        };
        HW_SCE_p_func101(Param_p47f_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        static const uint32_t Param_p47f_func101_004[] =
        {
            0xea6f2734U, 0xa16e75a5U, 0xe73f8298U, 0x686c805bU,
        };
        HW_SCE_p_func101(Param_p47f_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        static const uint32_t Param_p47f_func101_005[] =
        {
            0x160ec850U, 0x256044acU, 0x2e147e96U, 0xc4166693U,
        };
        HW_SCE_p_func101(Param_p47f_func101_005);
    }

    static const uint32_t Param_p47f_func100_001[] =
    {
        0x1aee5930U, 0xbae62181U, 0x010b5253U, 0xf8837913U,
    };
    HW_SCE_p_func100(Param_p47f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p47f_func102_001[] =
        {
            0x456c3ac1U, 0x66da1c4fU, 0xb41b43bcU, 0x951bd5f4U,
        };
        HW_SCE_p_func102(Param_p47f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p47f_func102_002[] =
        {
            0x8984c019U, 0x50eb8683U, 0x6fdd4b33U, 0xe6447ca1U,
        };
        HW_SCE_p_func102(Param_p47f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
