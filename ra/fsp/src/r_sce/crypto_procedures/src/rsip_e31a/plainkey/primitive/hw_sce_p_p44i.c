/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00440001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000044U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p44i_func101_001[] =
    {
        0xa28be97dU, 0x7bb312f8U, 0x67806b8fU, 0xa12bd4afU,
    };
    HW_SCE_p_func101(Param_p44i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p44i_func100_001[] =
    {
        0x4a9213d0U, 0xe466a702U, 0x1aca1f6cU, 0x771a6c69U,
    };
    HW_SCE_p_func100(Param_p44i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p44i_func102_001[] =
        {
            0x1871b79bU, 0xbf5fa38cU, 0x850e2665U, 0xa65bea6fU,
        };
        HW_SCE_p_func102(Param_p44i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p44i_func100_002[] =
        {
            0x5760fc30U, 0xab961c63U, 0x6ceae00eU, 0x9d7bb7aeU,
        };
        HW_SCE_p_func100(Param_p44i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_p44i_func100_003[] =
        {
            0x079aca97U, 0x047afaa9U, 0xb6110f5eU, 0x20a98674U,
        };
        HW_SCE_p_func100(Param_p44i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

        static const uint32_t Param_p44i_func101_002[] =
        {
            0x9376e0fcU, 0x826a944eU, 0x4f94f27bU, 0xce325895U,
        };
        HW_SCE_p_func101(Param_p44i_func101_002);

        return FSP_SUCCESS;
    }
}
