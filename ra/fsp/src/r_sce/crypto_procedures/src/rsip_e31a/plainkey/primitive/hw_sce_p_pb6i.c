/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsDecryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00b60001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000008U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000b6U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pb6i_func101_001[] =
    {
        0x65275d23U, 0xb119e624U, 0x3983e074U, 0x68c37c5aU,
    };
    HW_SCE_p_func101(Param_pb6i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_pb6i_func100_001[] =
    {
        0x2aadf72bU, 0x818ca241U, 0xdd6e8183U, 0x9a04aa41U,
    };
    HW_SCE_p_func100(Param_pb6i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pb6i_func102_001[] =
        {
            0xf657f715U, 0xc9141cf6U, 0x62fd02c0U, 0x91bd8127U,
        };
        HW_SCE_p_func102(Param_pb6i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_pb6i_func100_002[] =
        {
            0x0c8ad901U, 0xfbd83e43U, 0x8c36832eU, 0x99b38a61U,
        };
        HW_SCE_p_func100(Param_pb6i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pb6i_func100_003[] =
        {
            0xe7e6448dU, 0x38458b3bU, 0xbcf004feU, 0x1c3f68a1U,
        };
        HW_SCE_p_func100(Param_pb6i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);
        HW_SCE_p_func_sub011(0x000003c1U, 0x0a010045U);
        WR4_ADDR(REG_2CH, &InData_IV[0]);

        static const uint32_t Param_pb6i_func101_002[] =
        {
            0x3efe26f4U, 0xff31ea5cU, 0xf9abd3a1U, 0xa9ac38e1U,
        };
        HW_SCE_p_func101(Param_pb6i_func101_002);

        return FSP_SUCCESS;
    }
}
