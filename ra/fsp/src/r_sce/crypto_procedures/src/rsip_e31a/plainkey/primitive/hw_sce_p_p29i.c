/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

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

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x0000b4a0U);
    WR1_PROG(REG_94H, 0x00000005U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000029U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x3beaa225U, 0x2935e993U, 0x0162f857U, 0x9b6321abU);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    HW_SCE_p_func100(0xfff6e82fU, 0x8c451418U, 0xffd1edaeU, 0x52d64cf5U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf5532d22U, 0x9309a015U, 0x84bddbf2U, 0x6e784668U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xb5c63cfeU, 0xec08d6bdU, 0xf0509c46U, 0xb914a7e3U);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000802U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x42a2240fU, 0x31187d31U, 0x3a19154bU, 0x80156272U);
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

        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x08000054U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x0a0000a4U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xf707afa9U, 0x0e64c7c4U, 0x800c7550U, 0x0da8fcbfU);

        return FSP_SUCCESS;
    }
}
