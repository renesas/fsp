/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00340001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000034U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p34i_func101_001[] =
    {
        0x4da27befU, 0x84005247U, 0x0a5db6e8U, 0x288f53ebU,
    };
    HW_SCE_p_func101(Param_p34i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p34i_func100_001[] =
    {
        0xc9000bafU, 0xb151a524U, 0xebb11368U, 0xd37f56b6U,
    };
    HW_SCE_p_func100(Param_p34i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p34i_func102_001[] =
        {
            0xa03a6524U, 0x51c583ccU, 0x710918bcU, 0xacf0cbbfU,
        };
        HW_SCE_p_func102(Param_p34i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p34i_func100_002[] =
        {
            0xe32ca8ddU, 0x4b88f8c7U, 0x7b5dbf8fU, 0xf43c63b3U,
        };
        HW_SCE_p_func100(Param_p34i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub002(0x00430011U);

        static const uint32_t Param_p34i_func100_003[] =
        {
            0x172a9770U, 0xadcad966U, 0xacae1b11U, 0x64084129U,
        };
        HW_SCE_p_func100(Param_p34i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub002(0x00430011U);

        static const uint32_t Param_p34i_func100_004[] =
        {
            0xd9e6e0e3U, 0xc30a94d2U, 0xf2adafb9U, 0xa4c12695U,
        };
        HW_SCE_p_func100(Param_p34i_func100_004);
        WR1_PROG(REG_14H, 0x000003c7U);
        HW_SCE_p_func_sub013(0x80840001U);
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

        static const uint32_t Param_p34i_func101_002[] =
        {
            0x6ef1a296U, 0xbae69092U, 0xbf7ab7ccU, 0x991d6c95U,
        };
        HW_SCE_p_func101(Param_p34i_func101_002);

        return FSP_SUCCESS;
    }
}
