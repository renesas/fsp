/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

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

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x0000b4a0U);
    WR1_PROG(REG_94H, 0x00000008U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000b6U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x65275d23U, 0xb119e624U, 0x3983e074U, 0x68c37c5aU);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    HW_SCE_p_func100(0x2aadf72bU, 0x818ca241U, 0xdd6e8183U, 0x9a04aa41U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf657f715U, 0xc9141cf6U, 0x62fd02c0U, 0x91bd8127U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x0c8ad901U, 0xfbd83e43U, 0x8c36832eU, 0x99b38a61U);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xe7e6448dU, 0x38458b3bU, 0xbcf004feU, 0x1c3f68a1U);
        WR1_PROG(REG_D0H, 0x08000095U);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0x0a010045U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_IV[0]);

        HW_SCE_p_func101(0x3efe26f4U, 0xff31ea5cU, 0xf9abd3a1U, 0xa9ac38e1U);

        return FSP_SUCCESS;
    }
}
