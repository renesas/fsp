/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00b30001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000008U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000b3U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pb3i_func101_001[] =
    {
        0xdaf5165fU, 0x98b78a5bU, 0x77054fc9U, 0xd4c1a986U,
    };
    HW_SCE_p_func101(Param_pb3i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_pb3i_func100_001[] =
    {
        0xe2bf50c0U, 0x98ec48f0U, 0xd41eb6b6U, 0x2f7d823eU,
    };
    HW_SCE_p_func100(Param_pb3i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pb3i_func102_001[] =
        {
            0x199ab418U, 0x0b47e815U, 0xfd40e0eaU, 0x9078293fU,
        };
        HW_SCE_p_func102(Param_pb3i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_pb3i_func100_002[] =
        {
            0x6927212dU, 0xf053392fU, 0x54794ebbU, 0x8ddefeaeU,
        };
        HW_SCE_p_func100(Param_pb3i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pb3i_func100_003[] =
        {
            0x72742dbfU, 0x12ae64ecU, 0x93e86f38U, 0xd03504b0U,
        };
        HW_SCE_p_func100(Param_pb3i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);
        HW_SCE_p_func_sub011(0x000003c1U, 0x0a010045U);
        WR4_ADDR(REG_2CH, &InData_IV[0]);

        static const uint32_t Param_pb3i_func101_002[] =
        {
            0x5f6fba1fU, 0x1104a60fU, 0xb3691419U, 0xe46e27afU,
        };
        HW_SCE_p_func101(Param_pb3i_func101_002);

        return FSP_SUCCESS;
    }
}
