/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_70H, 0x00a10001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000a1U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pa1i_func101_001[] =
    {
        0x4182c432U, 0xe8a44201U, 0x6aee001dU, 0xa926046eU,
    };
    HW_SCE_p_func101(Param_pa1i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_pa1i_func100_001[] =
    {
        0x5a9bb3c2U, 0x7ffeecc6U, 0x26c59478U, 0x9e38148bU,
    };
    HW_SCE_p_func100(Param_pa1i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pa1i_func102_001[] =
        {
            0xd9a3cbafU, 0xfbfcc175U, 0xbc8c2a96U, 0x9ed3ca56U,
        };
        HW_SCE_p_func102(Param_pa1i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_pa1i_func100_002[] =
        {
            0x6a41887aU, 0xfa59f60dU, 0x76b5b50cU, 0x42e21235U,
        };
        HW_SCE_p_func100(Param_pa1i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub002(0x00430011U);

        static const uint32_t Param_pa1i_func100_003[] =
        {
            0xc847e8c6U, 0x52fcfe95U, 0x0bd84585U, 0x2a5114d9U,
        };
        HW_SCE_p_func100(Param_pa1i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub002(0x00430011U);

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_pa1i_func101_002[] =
        {
            0x14785b70U, 0x1ffcac4dU, 0xeb1459ddU, 0xb755ed72U,
        };
        HW_SCE_p_func101(Param_pa1i_func101_002);

        return FSP_SUCCESS;
    }
}
