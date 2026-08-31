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
    HW_SCE_p_func_sub020(0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000095U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p95i_func101_001[] =
    {
        0xdd607a23U, 0xa327ff69U, 0xe5cd7bd4U, 0x9fa3a446U,
    };
    HW_SCE_p_func101(Param_p95i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p95i_func100_001[] =
    {
        0xbf1666abU, 0x2aab0197U, 0x3e51d0cbU, 0x2f16c647U,
    };
    HW_SCE_p_func100(Param_p95i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p95i_func102_001[] =
        {
            0xb81d1f72U, 0x6f4b8981U, 0x284d54dcU, 0xea361adeU,
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
            0x216124a2U, 0x94734327U, 0xbe20d7f3U, 0x974a3d17U,
        };
        HW_SCE_p_func100(Param_p95i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_D4H, 0x00000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_p95i_func101_002[] =
        {
            0x2f4bcae9U, 0xeb0113ecU, 0x841f0e57U, 0x56a12616U,
        };
        HW_SCE_p_func101(Param_p95i_func101_002);

        return FSP_SUCCESS;
    }
}
