/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmDecryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00360001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000036U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p36i_func101_001[] =
    {
        0xf4efbd8eU, 0x39e33fc3U, 0x412cc364U, 0x8067102eU,
    };
    HW_SCE_p_func101(Param_p36i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p36i_func100_001[] =
    {
        0x77ce70cbU, 0x258decd9U, 0x13029cd9U, 0xaee2e373U,
    };
    HW_SCE_p_func100(Param_p36i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p36i_func102_001[] =
        {
            0xf3bb0ef8U, 0x22a08810U, 0x4fa96145U, 0xb9c81dfeU,
        };
        HW_SCE_p_func102(Param_p36i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p36i_func100_002[] =
        {
            0x0e00f987U, 0xee1e66b5U, 0x8bb693edU, 0x2f460a5aU,
        };
        HW_SCE_p_func100(Param_p36i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_p36i_func100_003[] =
        {
            0xb651a968U, 0x08a1fe5dU, 0x8f09fbcdU, 0x64cbfd34U,
        };
        HW_SCE_p_func100(Param_p36i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_p36i_func100_004[] =
        {
            0x45a4b524U, 0x6803691dU, 0x4cff3284U, 0x96f5349cU,
        };
        HW_SCE_p_func100(Param_p36i_func100_004);
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

        HW_SCE_p_func_sub007(0x000000a1U, 0x40000000U, 0x0a0080a4U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        static const uint32_t Param_p36i_func101_002[] =
        {
            0x1e48a709U, 0xa74b4166U, 0xb6c16490U, 0x6cd3dadaU,
        };
        HW_SCE_p_func101(Param_p36i_func101_002);

        return FSP_SUCCESS;
    }
}
