/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256XtsDecryptInitSub (uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000c201U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000c2U);

    static const uint32_t Param_pc2i_func101_001[] =
    {
        0x64f3220dU, 0x22e30a77U, 0x226d2950U, 0x99636fa0U,
    };
    HW_SCE_p_func101(Param_pc2i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000009U, 0x00000058U, 0x800103a0U, 0x000000c2U);

    static const uint32_t Param_pc2i_func101_002[] =
    {
        0x92b4071bU, 0x488ba86cU, 0xb12db5c7U, 0x22f81140U,
    };
    HW_SCE_p_func101(Param_pc2i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pc2i_func100_001[] =
    {
        0x83e016f1U, 0xc8145747U, 0xdf402c37U, 0x475507c9U,
    };
    HW_SCE_p_func100(Param_pc2i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pc2i_func100_002[] =
    {
        0x650e1e8fU, 0x0eeeefc1U, 0xc66d9626U, 0xc92ddf65U,
    };
    HW_SCE_p_func100(Param_pc2i_func100_002);
    HW_SCE_p_func_sub019(0x00090805U, 0x00001213U);

    static const uint32_t Param_pc2i_func100_003[] =
    {
        0xc7d82035U, 0x5c97b869U, 0x164f07dcU, 0xe289816fU,
    };
    HW_SCE_p_func100(Param_pc2i_func100_003);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x00f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[13]);

    HW_SCE_p_func_sub019(0x000a0805U, 0x00001213U);

    static const uint32_t Param_pc2i_func100_004[] =
    {
        0x78ea820eU, 0xa4d34913U, 0xa9b13f98U, 0x8c104d27U,
    };
    HW_SCE_p_func100(Param_pc2i_func100_004);
    WR1_PROG(REG_A4H, 0x000b0805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[17]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pc2i_func100_005[] =
    {
        0xe00ff40eU, 0x4ce66660U, 0x29f91899U, 0x2e7d40bcU,
    };
    HW_SCE_p_func100(Param_pc2i_func100_005);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pc2i_func102_001[] =
        {
            0x5c87614cU, 0x072c8029U, 0xe1f5444fU, 0x6022c195U,
        };
        HW_SCE_p_func102(Param_pc2i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x0004aa05U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_IV[0]);

        return FSP_SUCCESS;
    }
}
