/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192CcmDecryptInitSub (uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000b001U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x000000b0U);

    static const uint32_t Param_pb0i_func101_001[] =
    {
        0xbdd17f39U, 0x08088efeU, 0x35974f03U, 0x7e5b170cU,
    };
    HW_SCE_p_func101(Param_pb0i_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000006U, 0x00000058U, 0x800103a0U, 0x000000b0U);

    static const uint32_t Param_pb0i_func101_002[] =
    {
        0x42001f4cU, 0xd3136d01U, 0x69ac7c8bU, 0xc56dd6b8U,
    };
    HW_SCE_p_func101(Param_pb0i_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_pb0i_func100_001[] =
    {
        0xb415d07fU, 0x65b938e5U, 0xbcbe29a7U, 0xb22a1080U,
    };
    HW_SCE_p_func100(Param_pb0i_func100_001);
    HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

    HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

    static const uint32_t Param_pb0i_func100_002[] =
    {
        0xc53a1e0fU, 0x2de3033dU, 0xf96b4fd1U, 0x9b9529f2U,
    };
    HW_SCE_p_func100(Param_pb0i_func100_002);
    WR1_PROG(REG_A4H, 0x00090805U);
    WR1_PROG(REG_00H, 0x00001213U);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_pb0i_func100_003[] =
    {
        0x6d67554cU, 0xaf4b35f3U, 0x9e34693bU, 0x6a7e461bU,
    };
    HW_SCE_p_func100(Param_pb0i_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb0i_func102_001[] =
        {
            0x8be5abacU, 0x4d261e29U, 0x2edada3eU, 0x7140c6e9U,
        };
        HW_SCE_p_func102(Param_pb0i_func102_001);
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
        WR1_PROG(REG_A4H, 0x00008e56U);

        for (iLoop = 0U; iLoop < Header_Len; )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Header[iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205();

        static const uint32_t Param_pb0i_func100_004[] =
        {
            0xd160a2aeU, 0x155a728eU, 0x8e7b2421U, 0xfd62a0e3U,
        };
        HW_SCE_p_func100(Param_pb0i_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pb0i_func102_002[] =
            {
                0xfca9b293U, 0xe2bd4011U, 0x35a81beaU, 0x56d06150U,
            };
            HW_SCE_p_func102(Param_pb0i_func102_002);
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
