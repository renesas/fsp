/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsDecryptInitSub (uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000b601U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000b6U);

    static const uint32_t Param_pb6i_func101_001[] =
    {
        0x4c614de9U, 0x5e8ab367U, 0x8f0ec989U, 0xabac3714U,
    };
    HW_SCE_p_func101(Param_pb6i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000008U, 0x00000058U, 0x800103a0U, 0x000000b6U);

    static const uint32_t Param_pb6i_func101_002[] =
    {
        0x922537c5U, 0xa9a9461fU, 0xd4343eaaU, 0x3ed82bd8U,
    };
    HW_SCE_p_func101(Param_pb6i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pb6i_func100_001[] =
    {
        0x59700e14U, 0x47fa423cU, 0x7408c9eaU, 0x8ea9b7b6U,
    };
    HW_SCE_p_func100(Param_pb6i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pb6i_func100_002[] =
    {
        0x5d49c1ceU, 0x2dc53336U, 0xb3bd49a8U, 0xc5aab113U,
    };
    HW_SCE_p_func100(Param_pb6i_func100_002);
    WR1_PROG(REG_A4H, 0x00090805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pb6i_func100_003[] =
    {
        0x1467aa39U, 0x6d7b3825U, 0x22152c4bU, 0x021db04eU,
    };
    HW_SCE_p_func100(Param_pb6i_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb6i_func102_001[] =
        {
            0x3ae42f8dU, 0x0275f942U, 0x97e65683U, 0x20dbf82aU,
        };
        HW_SCE_p_func102(Param_pb6i_func102_001);
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
