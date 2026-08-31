/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsEncryptInitSub (uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000b301U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000b3U);

    static const uint32_t Param_pb3i_func101_001[] =
    {
        0xa3847694U, 0xba217b7dU, 0x761fc8f0U, 0x1fe1218cU,
    };
    HW_SCE_p_func101(Param_pb3i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000008U, 0x00000058U, 0x800103a0U, 0x000000b3U);

    static const uint32_t Param_pb3i_func101_002[] =
    {
        0x1814288bU, 0x6b57786cU, 0x6f589fcbU, 0xc4affa6bU,
    };
    HW_SCE_p_func101(Param_pb3i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pb3i_func100_001[] =
    {
        0x5c7e3adaU, 0x2e7118f6U, 0x80e1963bU, 0xd32bc1a7U,
    };
    HW_SCE_p_func100(Param_pb3i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pb3i_func100_002[] =
    {
        0xa2848470U, 0xe9fa7aebU, 0x5e4cac5eU, 0x78b70946U,
    };
    HW_SCE_p_func100(Param_pb3i_func100_002);
    WR1_PROG(REG_A4H, 0x00090805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pb3i_func100_003[] =
    {
        0x84e62500U, 0x9a34e5e7U, 0x7bee933cU, 0xe449a4a0U,
    };
    HW_SCE_p_func100(Param_pb3i_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb3i_func102_001[] =
        {
            0x94484a86U, 0x6ac09497U, 0xacca3456U, 0x2007aa2cU,
        };
        HW_SCE_p_func102(Param_pb3i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00041a05U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_IV[0]);

        return FSP_SUCCESS;
    }
}
