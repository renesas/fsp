/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t Header_Len)
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00950001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000095U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p95i_func101_001[] =
    {
        0xfac8ee87U, 0x23df5652U, 0x4f031cafU, 0xbb676e0cU,
    };
    HW_SCE_p_func101(Param_p95i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p95i_func100_001[] =
    {
        0x39b8481eU, 0x512ba289U, 0xf323b9bfU, 0xe8246b8aU,
    };
    HW_SCE_p_func100(Param_p95i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p95i_func102_001[] =
        {
            0xb497cda3U, 0x72f9eb0eU, 0x0a1c7efcU, 0x8d6b0ee8U,
        };
        HW_SCE_p_func102(Param_p95i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p95i_func100_002[] =
        {
            0xebb05ae4U, 0xbbe5a41dU, 0x196dd7deU, 0x12e73f19U,
        };
        HW_SCE_p_func100(Param_p95i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_D4H, 0x00000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_p95i_func101_002[] =
        {
            0x39be7fadU, 0x8f95e38eU, 0xf42dd388U, 0x94205525U,
        };
        HW_SCE_p_func101(Param_p95i_func101_002);

        return FSP_SUCCESS;
    }
}
