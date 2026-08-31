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
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000a4U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pa4i_func101_001[] =
    {
        0xa823ba86U, 0xaf09f282U, 0x731cf163U, 0x857ead3bU,
    };
    HW_SCE_p_func101(Param_pa4i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_pa4i_func100_001[] =
    {
        0x8e98b141U, 0x41b529a4U, 0xe66ee1b8U, 0xfa414103U,
    };
    HW_SCE_p_func100(Param_pa4i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pa4i_func102_001[] =
        {
            0xb5ba710cU, 0x75c74e63U, 0xcf8ed41aU, 0xf80d1be5U,
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
            0xa78ea6c8U, 0x7b1df8aaU, 0x4c3050ccU, 0xbf86080fU,
        };
        HW_SCE_p_func100(Param_pa4i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub002(0x00430011U);

        static const uint32_t Param_pa4i_func100_003[] =
        {
            0x1a7c4a49U, 0xd88c4096U, 0xd24f9590U, 0xe11be059U,
        };
        HW_SCE_p_func100(Param_pa4i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub002(0x00430011U);

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_pa4i_func101_002[] =
        {
            0x3af0b612U, 0xa5282b6aU, 0xd29f7148U, 0x665472f1U,
        };
        HW_SCE_p_func101(Param_pa4i_func101_002);

        return FSP_SUCCESS;
    }
}
