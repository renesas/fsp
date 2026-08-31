/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00008901U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000089U);

    static const uint32_t Param_p89i_func101_001[] =
    {
        0xd2d17f17U, 0x9ed64bfbU, 0xebed71f8U, 0xd0f1de28U,
    };
    HW_SCE_p_func101(Param_p89i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000006U, 0x00000058U, 0x800103a0U, 0x00000089U);

    static const uint32_t Param_p89i_func101_002[] =
    {
        0x3a350608U, 0xf1283fdeU, 0xb7c2416eU, 0x378561d5U,
    };
    HW_SCE_p_func101(Param_p89i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p89i_func100_001[] =
    {
        0x112550f9U, 0x2ef76aeaU, 0x48f9d518U, 0xe2095dc6U,
    };
    HW_SCE_p_func100(Param_p89i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_p89i_func100_002[] =
    {
        0x7106f61eU, 0x705629cfU, 0x82ae645fU, 0xc89bfb94U,
    };
    HW_SCE_p_func100(Param_p89i_func100_002);
    WR1_PROG(REG_A4H, 0x00090805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p89i_func100_003[] =
    {
        0xca5b4afcU, 0xbae7dfd1U, 0x9e7fd8b3U, 0x09358784U,
    };
    HW_SCE_p_func100(Param_p89i_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p89i_func102_001[] =
        {
            0xc78ea399U, 0xa678759fU, 0x300215feU, 0xf2ce9a45U,
        };
        HW_SCE_p_func102(Param_p89i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_E0H, 0x80010000U);
        WR1_PROG(REG_104H, 0x00000068U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_Cmd[0]);

        HW_SCE_p_func_sub022(0x3000a800U, 0x00000004U, 0x00010020U, 0x0000b400U);
        WR1_PROG(REG_ECH, 0x00000004U);
        WR1_PROG(REG_ECH, 0x00000080U);

        static const uint32_t Param_p89i_func100_004[] =
        {
            0xe11f3cd4U, 0x4287c0d2U, 0xe2b6bf61U, 0x6afc0ad0U,
        };
        HW_SCE_p_func100(Param_p89i_func100_004);
        WR1_PROG(REG_ECH, 0x00007c00U);
        WR1_PROG(REG_1CH, 0x00600000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
        {
            static const uint32_t Param_p89i_func101_003[] =
            {
                0x2c0be082U, 0x51950bd2U, 0x5501e81dU, 0x37634e53U,
            };
            HW_SCE_p_func101(Param_p89i_func101_003);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
        {
            static const uint32_t Param_p89i_func101_004[] =
            {
                0xf7c9cd50U, 0xc14979ebU, 0xe09af696U, 0x823702e1U,
            };
            HW_SCE_p_func101(Param_p89i_func101_004);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00040805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_IV[0]);

            static const uint32_t Param_p89i_func101_005[] =
            {
                0xb5faa29fU, 0xb8d5f49fU, 0xbc20a648U, 0x49f17503U,
            };
            HW_SCE_p_func101(Param_p89i_func101_005);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00040805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_IV[0]);

            static const uint32_t Param_p89i_func101_006[] =
            {
                0x3a1757deU, 0x5d8bf593U, 0xa8dd7442U, 0x5d4eae78U,
            };
            HW_SCE_p_func101(Param_p89i_func101_006);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00040805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_IV[0]);

            static const uint32_t Param_p89i_func101_007[] =
            {
                0x85c9c52eU, 0x99021743U, 0xeb05d66fU, 0x9be91a40U,
            };
            HW_SCE_p_func101(Param_p89i_func101_007);
        }

        return FSP_SUCCESS;
    }
}
