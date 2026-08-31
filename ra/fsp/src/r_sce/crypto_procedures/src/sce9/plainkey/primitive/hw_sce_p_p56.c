/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub (const uint32_t InData_KeyIndex[],
                                                   const uint32_t InData_Text[],
                                                   uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00005601U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000056U);

    static const uint32_t Param_p56_func101_001[] =
    {
        0xdc0a590bU, 0x6e3392ffU, 0x97adc5b9U, 0x633171bbU,
    };
    HW_SCE_p_func101(Param_p56_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x0000000cU, 0x00000058U, 0x800103a0U, 0x00000056U);

    static const uint32_t Param_p56_func101_002[] =
    {
        0xfc2447faU, 0x9cf0143bU, 0x85110c57U, 0x2b7cbdcfU,
    };
    HW_SCE_p_func101(Param_p56_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    WR1_PROG(REG_28H, 0x00000001U);

    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    WR1_PROG(REG_104H, 0x00008362U);
    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x02e08887U);

    for (iLoop = 0U; iLoop < 64U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00e08885U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[65]);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x00f087b7U);

    for (iLoop = 68; iLoop < 132; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[133]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p56_func100_001[] =
    {
        0x0493bf32U, 0x4fd6ac99U, 0x18fd6dbdU, 0x235e32ddU,
    };
    HW_SCE_p_func100(Param_p56_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p56_func102_001[] =
        {
            0xe07e4daaU, 0x5778972bU, 0xd2cb35fdU, 0x1c09d955U,
        };
        HW_SCE_p_func102(Param_p56_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p56_func100_002[] =
        {
            0x30b546ddU, 0x1c282749U, 0xd166b5dfU, 0x5f659d4bU,
        };
        HW_SCE_p_func100(Param_p56_func100_002);
        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00003f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR64_ADDR(REG_100H, &InData_Text[0]);

        WR1_PROG(REG_18H, 0x00000004U);
        WR1_PROG(REG_38H, 0x00000338U);

        HW_SCE_p_func_sub010(0x81010000U, 0x00003807U);

        WAIT_STS(REG_18H, 10, 0);
        WR1_PROG(REG_18H, 0x00000000U);

        static const uint32_t Param_p56_func100_003[] =
        {
            0x305b97ceU, 0x263481e9U, 0x9ae65b13U, 0xb79bccfeU,
        };
        HW_SCE_p_func100(Param_p56_func100_003);
        WR1_PROG(REG_2CH, 0x00000020U);
        WR1_PROG(REG_04H, 0x00000303U);
        WAIT_STS(REG_04H, 30, 1);
        RD64_ADDR(REG_100H, &OutData_Text[0]);

        static const uint32_t Param_p56_func102_002[] =
        {
            0xa498754bU, 0x729577e0U, 0x423a9c49U, 0xbf249dabU,
        };
        HW_SCE_p_func102(Param_p56_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
