/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Rsa1024ModularExponentDecryptSub (uint32_t       InData_KeyIndex[],
                                                   const uint32_t InData_Text[],
                                                   uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00005402U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000054U);

    static const uint32_t Param_p54_func101_001[] =
    {
        0xeb32b181U, 0x1272c66fU, 0x5cb2b3e4U, 0xe9c76996U,
    };
    HW_SCE_p_func101(Param_p54_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x0000000bU, 0x00000058U, 0x800103a0U, 0x00000054U);

    static const uint32_t Param_p54_func101_002[] =
    {
        0x3dffd046U, 0x37b2efeeU, 0x789dd210U, 0xe375c626U,
    };
    HW_SCE_p_func101(Param_p54_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    WR1_PROG(REG_28H, 0x00000001U);

    WR1_PROG(REG_28H, 0x009f0001U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000014U);
    WR1_PROG(REG_104H, 0x00005f62U);
    WR1_PROG(REG_D0H, 0x40000700U);
    WR1_PROG(REG_C4H, 0x02f087b7U);

    for (iLoop = 0U; iLoop < 32U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000011U);
    WR1_PROG(REG_D0H, 0x40000700U);
    WR1_PROG(REG_C4H, 0x00f087b7U);

    for (iLoop = 32; iLoop < 64U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000012U);
    WR1_PROG(REG_D0H, 0x40000700U);
    WR1_PROG(REG_C4H, 0x00f087b7U);

    for (iLoop = 64; iLoop < 96U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[97]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p54_func100_001[] =
    {
        0x1c8570a1U, 0x6af29485U, 0x89c3645cU, 0x9fcf3700U,
    };
    HW_SCE_p_func100(Param_p54_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p54_func102_001[] =
        {
            0x7afa114dU, 0x5c5e02abU, 0xc2f2e651U, 0x9d0608e0U,
        };
        HW_SCE_p_func102(Param_p54_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p54_func100_002[] =
        {
            0xb35cda70U, 0x69c8bb80U, 0x39b710a1U, 0xd273f549U,
        };
        HW_SCE_p_func100(Param_p54_func100_002);
        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00001f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR32_ADDR(REG_100H, &InData_Text[0]);

        WR1_PROG(REG_24H, 0x000068d0U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_18H, 0x00000004U);
        WR1_PROG(REG_38H, 0x00000440U);
        WAIT_STS(REG_18H, 10, 0);
        WR1_PROG(REG_18H, 0x00000000U);

        static const uint32_t Param_p54_func100_003[] =
        {
            0x2b18e3d9U, 0x0bba4b2fU, 0x583ca510U, 0x75eaf5fbU,
        };
        HW_SCE_p_func100(Param_p54_func100_003);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000383U);
        WAIT_STS(REG_04H, 30, 1);
        RD32_ADDR(REG_100H, &OutData_Text[0]);

        static const uint32_t Param_p54_func102_002[] =
        {
            0xb86a92cbU, 0xba8e00c1U, 0x863e4a60U, 0x615ae72dU,
        };
        HW_SCE_p_func102(Param_p54_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
