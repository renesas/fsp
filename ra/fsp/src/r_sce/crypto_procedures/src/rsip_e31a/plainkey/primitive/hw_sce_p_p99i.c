/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_70H, 0x00990001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000099U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p99i_func101_001[] =
    {
        0x68a67604U, 0x6104f7beU, 0x3e57c467U, 0x7f7e0921U,
    };
    HW_SCE_p_func101(Param_p99i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p99i_func100_001[] =
    {
        0x48a34deaU, 0x1e3e31d5U, 0x0b424aceU, 0xb7bd8f4fU,
    };
    HW_SCE_p_func100(Param_p99i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p99i_func102_001[] =
        {
            0x79cf8340U, 0x9b55a890U, 0x2638e4e0U, 0xf8182802U,
        };
        HW_SCE_p_func102(Param_p99i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p99i_func100_002[] =
        {
            0xf7cadb9dU, 0x734c695aU, 0xa6cbc6dbU, 0xd28e8273U,
        };
        HW_SCE_p_func100(Param_p99i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_D4H, 0x00000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_p99i_func101_002[] =
        {
            0x605c3739U, 0xc2d239a7U, 0x1f52a793U, 0xc2a7cc55U,
        };
        HW_SCE_p_func101(Param_p99i_func101_002);

        return FSP_SUCCESS;
    }
}
