/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        static const uint32_t Param_p89f_func101_001[] =
        {
            0x529eb8a4U, 0xbbfb9486U, 0x90411712U, 0x130be43aU,
        };
        HW_SCE_p_func101(Param_p89f_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        static const uint32_t Param_p89f_func101_002[] =
        {
            0x726aa5e0U, 0x8652e5c5U, 0x4ffc2ee5U, 0x58c35758U,
        };
        HW_SCE_p_func101(Param_p89f_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        static const uint32_t Param_p89f_func101_003[] =
        {
            0x87a0e5f5U, 0x753db70aU, 0xefe63a11U, 0x8fa5a3caU,
        };
        HW_SCE_p_func101(Param_p89f_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        static const uint32_t Param_p89f_func101_004[] =
        {
            0xda5abb50U, 0x88397877U, 0x6adbab94U, 0xe5827a23U,
        };
        HW_SCE_p_func101(Param_p89f_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        static const uint32_t Param_p89f_func101_005[] =
        {
            0x594c14e1U, 0x7a8d4bb0U, 0x87a899a8U, 0x66ac7516U,
        };
        HW_SCE_p_func101(Param_p89f_func101_005);
    }

    static const uint32_t Param_p89f_func100_001[] =
    {
        0x0a6d6c60U, 0xb3b40ae8U, 0x7498d060U, 0xdc8f87a2U,
    };
    HW_SCE_p_func100(Param_p89f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p89f_func102_001[] =
        {
            0x8621b7b4U, 0xdf4bde26U, 0x51a0438bU, 0xba4e4693U,
        };
        HW_SCE_p_func102(Param_p89f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p89f_func102_002[] =
        {
            0xf9c42484U, 0x22f278bcU, 0x3e90cfbaU, 0xdfc2f6c5U,
        };
        HW_SCE_p_func102(Param_p89f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
