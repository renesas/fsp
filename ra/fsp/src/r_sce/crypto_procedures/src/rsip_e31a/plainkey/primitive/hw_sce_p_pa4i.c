/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_70H, 0x00a40001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000a4U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pa4i_func101_001[] =
    {
        0x7baf24e4U, 0xdd5a4a4fU, 0x7363cf8bU, 0xcb1ded9bU,
    };
    HW_SCE_p_func101(Param_pa4i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_pa4i_func100_001[] =
    {
        0xded13f03U, 0xe18b0f6cU, 0x4083857bU, 0xb4ecd1ceU,
    };
    HW_SCE_p_func100(Param_pa4i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pa4i_func102_001[] =
        {
            0x3631a2dbU, 0x194536a5U, 0x792ed9e6U, 0xa1ee71baU,
        };
        HW_SCE_p_func102(Param_pa4i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_pa4i_func100_002[] =
        {
            0x1570484eU, 0xd2ad1ae8U, 0x4ff3b17bU, 0xb5ae362eU,
        };
        HW_SCE_p_func100(Param_pa4i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pa4i_func100_003[] =
        {
            0x37eaf4b5U, 0x651742a0U, 0xa2e9ca15U, 0xa6066f96U,
        };
        HW_SCE_p_func100(Param_pa4i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_pa4i_func101_002[] =
        {
            0xe0b8d78dU, 0xe8dd045fU, 0xb6992552U, 0x11ff4c9aU,
        };
        HW_SCE_p_func101(Param_pa4i_func101_002);

        return FSP_SUCCESS;
    }
}
