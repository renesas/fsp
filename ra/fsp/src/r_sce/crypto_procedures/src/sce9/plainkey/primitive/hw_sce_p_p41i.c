/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CmacInitSub (uint32_t InData_KeyIndex[])
{
    uint32_t InData_KeyType[1] = {0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00004102U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_p41i_func100_001[] =
    {
        0xabd38050U, 0x5ba81f06U, 0x71f86840U, 0xab20a600U,
    };
    HW_SCE_p_func100(Param_p41i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p41i_func102_001[] =
        {
            0x40c3155fU, 0xfade58a2U, 0x81b2308cU, 0xbec9a415U,
        };
        HW_SCE_p_func102(Param_p41i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p41i_func100_002[] =
        {
            0xfa043140U, 0x2c6b0e94U, 0x20a68d42U, 0x37f054e3U,
        };
        HW_SCE_p_func100(Param_p41i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000041U);

            static const uint32_t Param_p41i_func101_001[] =
            {
                0x98a04074U, 0x66bafebeU, 0xd412c527U, 0xf52309f8U,
            };
            HW_SCE_p_func101(Param_p41i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000005U);

            static const uint32_t Param_p41i_func101_002[] =
            {
                0x26d01534U, 0x98e8e4ebU, 0xdc58bfdaU, 0xc07e7d51U,
            };
            HW_SCE_p_func101(Param_p41i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000041U);

            static const uint32_t Param_p41i_func101_003[] =
            {
                0x4e3ea3a0U, 0xfdb662dcU, 0x180a7f7cU, 0x63cbe076U,
            };
            HW_SCE_p_func101(Param_p41i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x0146c04bU);

            static const uint32_t Param_p41i_func101_004[] =
            {
                0xdf744ad9U, 0x6c17598fU, 0x12d94ec0U, 0xd9ea16a9U,
            };
            HW_SCE_p_func101(Param_p41i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x00000041U);

        static const uint32_t Param_p41i_func101_005[] =
        {
            0xac6c999cU, 0xf27778f2U, 0x330f1addU, 0x0d60716eU,
        };
        HW_SCE_p_func101(Param_p41i_func101_005);
        HW_SCE_p_func044();

        static const uint32_t Param_p41i_func100_003[] =
        {
            0x4942a239U, 0x977f047cU, 0xb0220abfU, 0xc4aa2689U,
        };
        HW_SCE_p_func100(Param_p41i_func100_003);
        HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

        WR1_PROG(REG_A4H, 0x00080805U);
        WR1_PROG(REG_00H, 0x00001213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_p41i_func100_004[] =
        {
            0x99397a13U, 0x7c7f0177U, 0xc3d94e5cU, 0x78b7f2f6U,
        };
        HW_SCE_p_func100(Param_p41i_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p41i_func102_002[] =
            {
                0x93d24779U, 0xc0c06183U, 0x80c823c6U, 0x99b0bf1bU,
            };
            HW_SCE_p_func102(Param_p41i_func102_002);
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
