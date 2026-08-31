/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CmacInitSub (uint32_t InData_KeyIndex[])
{
    uint32_t InData_KeyType[1] = {0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00004402U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_p44i_func100_001[] =
    {
        0x96adce0dU, 0x89b7140dU, 0x62c92bfeU, 0xe488284bU,
    };
    HW_SCE_p_func100(Param_p44i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p44i_func102_001[] =
        {
            0x7e586ddaU, 0x6fc0bc63U, 0x4a0264eaU, 0xa3577adcU,
        };
        HW_SCE_p_func102(Param_p44i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p44i_func100_002[] =
        {
            0x5e0c2317U, 0x3b8a7ae8U, 0xcf5be3aeU, 0x860aa704U,
        };
        HW_SCE_p_func100(Param_p44i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000044U);

            static const uint32_t Param_p44i_func101_001[] =
            {
                0xe33551f8U, 0xd1ae31e4U, 0xd63c0e9fU, 0x81e115f5U,
            };
            HW_SCE_p_func101(Param_p44i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000007U);

            static const uint32_t Param_p44i_func101_002[] =
            {
                0xd84da9e7U, 0x428715c9U, 0xbb6bbe1dU, 0x50083aadU,
            };
            HW_SCE_p_func101(Param_p44i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000044U);

            static const uint32_t Param_p44i_func101_003[] =
            {
                0x5df5719dU, 0xc1f5bd7cU, 0xee155dd4U, 0x747a0f10U,
            };
            HW_SCE_p_func101(Param_p44i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x01d04999U);

            static const uint32_t Param_p44i_func101_004[] =
            {
                0xb2e2545eU, 0x3e655119U, 0x60937ee5U, 0x9ed4694bU,
            };
            HW_SCE_p_func101(Param_p44i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x00000044U);

        static const uint32_t Param_p44i_func101_005[] =
        {
            0x45bd36e9U, 0x553f840eU, 0x46e62109U, 0x44d10f75U,
        };
        HW_SCE_p_func101(Param_p44i_func101_005);
        HW_SCE_p_func044();

        static const uint32_t Param_p44i_func100_003[] =
        {
            0x8a54b357U, 0x98550891U, 0x69fe01e2U, 0x4af1d4c9U,
        };
        HW_SCE_p_func100(Param_p44i_func100_003);
        HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

        static const uint32_t Param_p44i_func100_004[] =
        {
            0xf88a2aeeU, 0xf10d2f2cU, 0xf9a5b838U, 0xa6e9c999U,
        };
        HW_SCE_p_func100(Param_p44i_func100_004);
        WR1_PROG(REG_A4H, 0x00090805U);
        WR1_PROG(REG_00H, 0x00001213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_p44i_func100_005[] =
        {
            0xa211f1d0U, 0xb5eeecbdU, 0xc44ad209U, 0x84285284U,
        };
        HW_SCE_p_func100(Param_p44i_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p44i_func102_002[] =
            {
                0x0f02d0e8U, 0x5e2fa0dbU, 0xd2e9123cU, 0x2aaa80ebU,
            };
            HW_SCE_p_func102(Param_p44i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub021(0x00040804U);

            return FSP_SUCCESS;
        }
    }
}
