/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptSub (uint32_t       InData_KeyIndex[],
                                                   const uint32_t InData_Text[],
                                                   uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00005702U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000057U);

    static const uint32_t Param_p57_func101_001[] =
    {
        0x0bf55ad3U, 0x2adb1b69U, 0x1d9b9787U, 0x023888abU,
    };
    HW_SCE_p_func101(Param_p57_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x0000000dU, 0x00000058U, 0x800103a0U, 0x00000057U);

    static const uint32_t Param_p57_func101_002[] =
    {
        0xea15afbeU, 0x0eadbcbbU, 0x001b01dbU, 0x7a5e95e1U,
    };
    HW_SCE_p_func101(Param_p57_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    WR1_PROG(REG_28H, 0x00000001U);

    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    WR1_PROG(REG_104H, 0x0000bf62U);
    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x02f087b7U);

    for (iLoop = 0U; iLoop < 64U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_ECH, 0x00000821U);
    WR1_PROG(REG_E0H, 0x80c00001U);

    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x00f087b7U);
    WR1_PROG(REG_00H, 0x00018203U);

    for (iLoop = 65; iLoop < 129; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x00f087b7U);

    for (iLoop = 128; iLoop < 192; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[193]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p57_func100_001[] =
    {
        0xb1001691U, 0xf4028eb7U, 0x295866f2U, 0x7f84fd00U,
    };
    HW_SCE_p_func100(Param_p57_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p57_func102_001[] =
        {
            0x06324a76U, 0x607c42abU, 0x43889fe9U, 0xc012d247U,
        };
        HW_SCE_p_func102(Param_p57_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p57_func100_002[] =
        {
            0x2779abe0U, 0x47d803e3U, 0x6a378f2dU, 0x69477a0eU,
        };
        HW_SCE_p_func100(Param_p57_func100_002);
        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00003f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR64_ADDR(REG_100H, &InData_Text[0]);

        WR1_PROG(REG_E0H, 0x00000100U);
        WR1_PROG(REG_ECH, 0x0000b7e0U);
        WR1_PROG(REG_ECH, 0x000000fcU);
        WR1_PROG(REG_18H, 0x00000004U);
        WR1_PROG(REG_38H, 0x00000248U);
        WR1_PROG(REG_E0H, 0x81c0001fU);
        WR1_PROG(REG_00H, 0x00013803U);
        WAIT_STS(REG_18H, 10, 0);
        WR1_PROG(REG_18H, 0x00000000U);
        WR1_PROG(REG_E0H, 0x00000000U);

        static const uint32_t Param_p57_func100_003[] =
        {
            0x3df61758U, 0x0c41d91eU, 0xe9275f9fU, 0x2a583f2bU,
        };
        HW_SCE_p_func100(Param_p57_func100_003);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000303U);
        WAIT_STS(REG_04H, 30, 1);
        RD64_ADDR(REG_100H, &OutData_Text[0]);

        static const uint32_t Param_p57_func102_002[] =
        {
            0x2486d860U, 0x24678ef0U, 0x84ba5d03U, 0x0b42a66dU,
        };
        HW_SCE_p_func102(Param_p57_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
