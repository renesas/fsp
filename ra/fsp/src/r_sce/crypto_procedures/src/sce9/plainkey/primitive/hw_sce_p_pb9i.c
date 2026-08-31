/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256XtsEncryptInitSub (uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000b901U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000b9U);

    static const uint32_t Param_pb9i_func101_001[] =
    {
        0xe8aebccaU, 0x08905231U, 0xd1629beaU, 0xd2afa2c7U,
    };
    HW_SCE_p_func101(Param_pb9i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000009U, 0x00000058U, 0x800103a0U, 0x000000b9U);

    static const uint32_t Param_pb9i_func101_002[] =
    {
        0xd3078522U, 0x8c545c34U, 0x21c26adfU, 0xc34e8d5bU,
    };
    HW_SCE_p_func101(Param_pb9i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pb9i_func100_001[] =
    {
        0x6db1b7a5U, 0x42f16527U, 0x6822dfd3U, 0x9fb93cfaU,
    };
    HW_SCE_p_func100(Param_pb9i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pb9i_func100_002[] =
    {
        0x88f6f429U, 0x2b207c89U, 0xabb5649aU, 0xbdb82cbaU,
    };
    HW_SCE_p_func100(Param_pb9i_func100_002);
    HW_SCE_p_func_sub019(0x00090805U, 0x00001213U);

    static const uint32_t Param_pb9i_func100_003[] =
    {
        0x1d1fce8fU, 0xb058c6bfU, 0xe14da850U, 0xc9294f88U,
    };
    HW_SCE_p_func100(Param_pb9i_func100_003);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x00f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[13]);

    HW_SCE_p_func_sub019(0x000a0805U, 0x00001213U);

    static const uint32_t Param_pb9i_func100_004[] =
    {
        0x440234afU, 0x93d1de5fU, 0x1a0d0914U, 0xa38cc8c1U,
    };
    HW_SCE_p_func100(Param_pb9i_func100_004);
    WR1_PROG(REG_A4H, 0x000b0805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[17]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pb9i_func100_005[] =
    {
        0xa7478611U, 0x403128d9U, 0x156b540eU, 0x45be9252U,
    };
    HW_SCE_p_func100(Param_pb9i_func100_005);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb9i_func102_001[] =
        {
            0xbcd15933U, 0x9fd141b7U, 0xe83eed90U, 0xd38ae4eeU,
        };
        HW_SCE_p_func102(Param_pb9i_func102_001);
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
