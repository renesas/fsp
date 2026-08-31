/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub (uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len)
{
    uint32_t iLoop             = 0U;
    uint32_t InData_KeyType[1] = {0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000a102U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_pa1i_func100_001[] =
    {
        0xdb03a5dfU, 0xa52570b2U, 0x6601bbb3U, 0x3ea61da6U,
    };
    HW_SCE_p_func100(Param_pa1i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa1i_func102_001[] =
        {
            0x917e3e22U, 0xf04198b0U, 0xb4f8df53U, 0xe25d0b05U,
        };
        HW_SCE_p_func102(Param_pa1i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_pa1i_func100_002[] =
        {
            0x37c069d3U, 0x926145aaU, 0x1c615a04U, 0xb1975c8dU,
        };
        HW_SCE_p_func100(Param_pa1i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000a1U);

            static const uint32_t Param_pa1i_func101_001[] =
            {
                0x52cb1369U, 0x342bfdbfU, 0x7ede6f6bU, 0xb7ee7226U,
            };
            HW_SCE_p_func101(Param_pa1i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000007U);

            static const uint32_t Param_pa1i_func101_002[] =
            {
                0xde111be7U, 0xddd15cc3U, 0x1e0947b7U, 0x20c1a651U,
            };
            HW_SCE_p_func101(Param_pa1i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000a1U);

            static const uint32_t Param_pa1i_func101_003[] =
            {
                0xd206830aU, 0xb87a4d75U, 0x6583f40eU, 0x6464e8b7U,
            };
            HW_SCE_p_func101(Param_pa1i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x01d04999U);

            static const uint32_t Param_pa1i_func101_004[] =
            {
                0x27595344U, 0x35dc3700U, 0x9f30fa1fU, 0xc3288152U,
            };
            HW_SCE_p_func101(Param_pa1i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x000000a1U);

        static const uint32_t Param_pa1i_func101_005[] =
        {
            0x62e27dadU, 0x313b0d1aU, 0x961892e6U, 0x97c437c3U,
        };
        HW_SCE_p_func101(Param_pa1i_func101_005);
        HW_SCE_p_func044();

        static const uint32_t Param_pa1i_func100_003[] =
        {
            0x05255eafU, 0xbb8ee12cU, 0x0b5c438aU, 0x03694643U,
        };
        HW_SCE_p_func100(Param_pa1i_func100_003);
        HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

        static const uint32_t Param_pa1i_func100_004[] =
        {
            0x0e42e528U, 0x697d2e85U, 0xb3709985U, 0xe75d31c8U,
        };
        HW_SCE_p_func100(Param_pa1i_func100_004);
        WR1_PROG(REG_A4H, 0x00090805U);
        WR1_PROG(REG_00H, 0x00001213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_pa1i_func100_005[] =
        {
            0x6752277aU, 0xc69f620fU, 0x46219ec6U, 0xb6e408b1U,
        };
        HW_SCE_p_func100(Param_pa1i_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pa1i_func102_002[] =
            {
                0x0257d3afU, 0x13038f5aU, 0x02a7c01bU, 0xd61eac1aU,
            };
            HW_SCE_p_func102(Param_pa1i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00040885U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_IV[0]);

            HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

            HW_SCE_p_func_sub021(0x00000734U);

            HW_SCE_p_func_sub021(0x00050804U);

            WR1_PROG(REG_104H, 0x000000b1U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00058e56U);

            for (iLoop = 0U; iLoop < Header_Len; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Header[iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func205();

            static const uint32_t Param_pa1i_func100_006[] =
            {
                0xb9e8fcf6U, 0xb4ea8932U, 0x1b72f566U, 0xff824869U,
            };
            HW_SCE_p_func100(Param_pa1i_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pa1i_func102_003[] =
                {
                    0xb45659f9U, 0xbb4e896dU, 0x566c184dU, 0xb6d59c0eU,
                };
                HW_SCE_p_func102(Param_pa1i_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                return FSP_SUCCESS;
            }
        }
    }
}
