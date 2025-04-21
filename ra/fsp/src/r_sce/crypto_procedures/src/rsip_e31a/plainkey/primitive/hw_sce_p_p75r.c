/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha2HmacResumeSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[],
                                    const uint32_t InData_HashType[],
                                    const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00750001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_F0H, 0x00000001U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010080U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_HashType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c84U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    WR1_PROG(REG_94H, 0x38008880U);
    WR1_PROG(REG_94H, 0x00000001U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    WR1_PROG(REG_94H, 0x38008880U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    WR1_PROG(REG_94H, 0x38008880U);
    WR1_PROG(REG_94H, 0x00000004U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0x930d1923U, 0xe350baffU, 0x838e7adaU, 0x5285019dU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xbf916453U, 0x7192bd89U, 0x73622bcaU, 0xe9900608U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x300c37cfU, 0x8d6d21e9U, 0x4862a509U, 0x304fedccU);
        WR1_PROG(REG_94H, 0x3420a880U);
        WR1_PROG(REG_94H, 0x00000007U);
        WR1_PROG(REG_94H, 0x2000b480U);
        WR1_PROG(REG_94H, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x0000001bU);

            WR1_PROG(REG_F4H, 0x00001050U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000008U);

            HW_SCE_p_func101(0x4aedf5d9U, 0x4138d5ebU, 0x6f16439bU, 0x222b8168U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000028U);

            WR1_PROG(REG_F4H, 0x000010a0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x0000000cU);

            HW_SCE_p_func101(0xe1a3be6fU, 0x0a442696U, 0x238548fcU, 0xfd790de6U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000029U);

            WR1_PROG(REG_F4H, 0x000010b0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            HW_SCE_p_func101(0x98012843U, 0x25b5e6d0U, 0x70af8e5fU, 0xb742bb91U);
        }

        WR1_PROG(REG_F8H, 0x00000003U);

        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010000U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x38000c00U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        HW_SCE_p_func100(0x75aa5ea9U, 0x6d1cf711U, 0x61c381acU, 0x34137158U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_14H, 0x000000c7U);
            WR1_PROG(REG_9CH, 0x800100c0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_KeyIndex[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00007502U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x036f79b8U, 0x4c41a92eU, 0xd57de635U, 0x9115102fU);
            HW_SCE_p_func043();

            WR1_PROG(REG_94H, 0x000034c5U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00007502U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0xddacfd65U, 0xd259ee24U, 0xd057b9daU, 0x28634f6dU);
            HW_SCE_p_func044();

            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D0H, 0x08000044U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D0H, 0x08000054U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_94H, 0x000008e7U);

            for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
            {
                WR1_PROG(REG_14H, 0x000003c1U);
                WR1_PROG(REG_D4H, 0x40000000U);
                WR1_PROG(REG_D0H, 0xf7008d05U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_KeyIndex[iLoop + 1]);

                WR1_PROG(REG_00H, 0x01410011U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_94H, 0x0000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);

                HW_SCE_p_func101(0x307c5affU, 0xc92ba040U, 0x642831cfU, 0x4be1a96aU);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_94H, 0x380008e3U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x07008d05U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            WR1_PROG(REG_00H, 0x00410011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            HW_SCE_p_func101(0x2d417ee4U, 0xacb61c58U, 0x09aeb11bU, 0xfbdfc263U);
        }
        else
        {
            WR1_PROG(REG_94H, 0x000008e7U);

            for (iLoop = 0U; iLoop < InLen; )
            {
                WR1_PROG(REG_14H, 0x000003c4U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_Key[iLoop]);

                WR1_PROG(REG_94H, 0x0000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);

                HW_SCE_p_func101(0xfce9c699U, 0xb22d0bd0U, 0x575f6422U, 0xae4cf047U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_94H, 0x380008e3U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func101(0xe271ba37U, 0x5badac52U, 0x872cb732U, 0xc07e8674U);
        }

        HW_SCE_p_func100(0x4a86df2fU, 0x7b68c7f6U, 0x1ddb9310U, 0xd26710d6U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x1a1b8fc8U, 0x5df4adf0U, 0x94a1ab84U, 0x5b47b87bU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, InData_State[18]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, InData_State[19]);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_110H, InData_State[iLoop]);
            }

            HW_SCE_p_func101(0xfc974f98U, 0xa99bd688U, 0xfd538793U, 0x97049dfeU);

            return FSP_SUCCESS;
        }
    }
}
