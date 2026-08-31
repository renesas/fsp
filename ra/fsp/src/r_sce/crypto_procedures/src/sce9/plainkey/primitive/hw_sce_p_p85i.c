/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192GcmDecryptInitSub (uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00008501U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000085U);

    static const uint32_t Param_p85i_func101_001[] =
    {
        0xe07e8f74U, 0x2a826c66U, 0x0d03786cU, 0xa14cb824U,
    };
    HW_SCE_p_func101(Param_p85i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000006U, 0x00000058U, 0x800103a0U, 0x00000085U);

    static const uint32_t Param_p85i_func101_002[] =
    {
        0x27b8cd9dU, 0x5b4d5484U, 0x025b0739U, 0xad75a550U,
    };
    HW_SCE_p_func101(Param_p85i_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    WR1_PROG(REG_E0H, 0x80080000U);
    WR1_PROG(REG_00H, 0x00008223U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p85i_func100_001[] =
    {
        0x7f580f58U, 0xd0e49a86U, 0x549e4e93U, 0xbb5def4fU,
    };
    HW_SCE_p_func100(Param_p85i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p85i_func102_001[] =
        {
            0x92430e5fU, 0xeaf95742U, 0xc3ff848eU, 0x2e1c9922U,
        };
        HW_SCE_p_func102(Param_p85i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p85i_func100_002[] =
        {
            0xe82d34e4U, 0xe8e1e9faU, 0x91fa95b0U, 0x87580ed5U,
        };
        HW_SCE_p_func100(Param_p85i_func100_002);
        WR1_PROG(REG_E0H, 0x81080000U);
        HW_SCE_p_func_sub013(0x00080805U, 0x00002813U);

        static const uint32_t Param_p85i_func100_003[] =
        {
            0x82937cb4U, 0x55eb782bU, 0x198879e5U, 0xbd5e3457U,
        };
        HW_SCE_p_func100(Param_p85i_func100_003);
        HW_SCE_p_func_sub013(0x00090805U, 0x00002813U);

        WR1_PROG(REG_104H, 0x00000368U);
        WR1_PROG(REG_E0H, 0x80040080U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[0]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[2]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[3]);

        WR1_PROG(REG_7CH, 0x00000001U);
        WR1_PROG(REG_7CH, 0x00000041U);

        HW_SCE_p_func_sub018(0x00000052U, 0x40000010U, 0x00008a84U);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_00H, 0x00005213U);
        WR1_PROG(REG_74H, 0x00001000U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_74H, 0x00000004U);
        WR1_PROG(REG_104H, 0x00000354U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000000U));

        WR1_PROG(REG_74H, 0x00000002U);

        return FSP_SUCCESS;
    }
}
