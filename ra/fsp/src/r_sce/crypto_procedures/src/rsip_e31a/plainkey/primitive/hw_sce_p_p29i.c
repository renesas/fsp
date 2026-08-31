/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00290001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000029U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p29i_func101_001[] =
    {
        0x3beaa225U, 0x2935e993U, 0x0162f857U, 0x9b6321abU,
    };
    HW_SCE_p_func101(Param_p29i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p29i_func100_001[] =
    {
        0xfff6e82fU, 0x8c451418U, 0xffd1edaeU, 0x52d64cf5U,
    };
    HW_SCE_p_func100(Param_p29i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p29i_func102_001[] =
        {
            0xf5532d22U, 0x9309a015U, 0x84bddbf2U, 0x6e784668U,
        };
        HW_SCE_p_func102(Param_p29i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p29i_func100_002[] =
        {
            0xb5c63cfeU, 0xec08d6bdU, 0xf0509c46U, 0xb914a7e3U,
        };
        HW_SCE_p_func100(Param_p29i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub003(0x00430009U);

        static const uint32_t Param_p29i_func100_003[] =
        {
            0x42a2240fU, 0x31187d31U, 0x3a19154bU, 0x80156272U,
        };
        HW_SCE_p_func100(Param_p29i_func100_003);
        WR1_PROG(REG_14H, 0x000003c7U);
        WR1_PROG(REG_94H, 0x0000b420U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x80840001U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[2]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[3]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0a0000a4U, 0x00000000U);

        static const uint32_t Param_p29i_func101_002[] =
        {
            0xf707afa9U, 0x0e64c7c4U, 0x800c7550U, 0x0da8fcbfU,
        };
        HW_SCE_p_func101(Param_p29i_func101_002);

        return FSP_SUCCESS;
    }
}
