/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192CcmEncryptInitSub (uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000a701U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000a7U);

    static const uint32_t Param_pa7i_func101_001[] =
    {
        0x98b7c339U, 0xccbb44a8U, 0xd55098f5U, 0x0d6b75e8U,
    };
    HW_SCE_p_func101(Param_pa7i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000006U, 0x00000058U, 0x800103a0U, 0x000000a7U);

    static const uint32_t Param_pa7i_func101_002[] =
    {
        0x69ae2359U, 0xc1253b04U, 0xf91fff11U, 0xe3f154b7U,
    };
    HW_SCE_p_func101(Param_pa7i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pa7i_func100_001[] =
    {
        0xa36f9c4dU, 0x37e9c677U, 0x8ec01528U, 0xea48bd9fU,
    };
    HW_SCE_p_func100(Param_pa7i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pa7i_func100_002[] =
    {
        0xde214992U, 0xf942e85fU, 0xafa19138U, 0x2cd51c14U,
    };
    HW_SCE_p_func100(Param_pa7i_func100_002);
    WR1_PROG(REG_A4H, 0x00090805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pa7i_func100_003[] =
    {
        0xaf3cf47fU, 0xcaa9f87fU, 0xbc272f9dU, 0xc956bf1aU,
    };
    HW_SCE_p_func100(Param_pa7i_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa7i_func102_001[] =
        {
            0xfcd0cc8eU, 0x1ac446d7U, 0x062aa28eU, 0xac7f72a3U,
        };
        HW_SCE_p_func102(Param_pa7i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000361U);
        WR1_PROG(REG_A4H, 0x00040885U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_IV[0]);

        HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

        HW_SCE_p_func_sub021(0x00000734U);

        HW_SCE_p_func_sub021(0x00050804U);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x00058e56U);

        for (iLoop = 0U; iLoop < Header_Len; )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Header[iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205();

        static const uint32_t Param_pa7i_func100_004[] =
        {
            0xbb3e71a7U, 0x5b7e113fU, 0x566bd588U, 0x28c333d9U,
        };
        HW_SCE_p_func100(Param_pa7i_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pa7i_func102_002[] =
            {
                0x4a7126bbU, 0x08691572U, 0x01bf8522U, 0xe3d418e5U,
            };
            HW_SCE_p_func102(Param_pa7i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            return FSP_SUCCESS;
        }
    }
}
