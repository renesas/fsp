/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha2HmacInitSub (const uint32_t InData_KeyMode[],
                                  const uint32_t InData_KeyIndex[],
                                  const uint32_t InData_Key[],
                                  const uint32_t InData_HashType[],
                                  const uint32_t InData_MsgLen[])
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

            WR1_PROG(REG_F4H, 0x00000050U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000008U);

            HW_SCE_p_func101(0xc3bca0ddU, 0xc6679423U, 0xc6098cfbU, 0x128d4a00U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000028U);

            WR1_PROG(REG_F4H, 0x000000a0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x0000000cU);

            HW_SCE_p_func101(0xc29b9ad2U, 0xfba760feU, 0x13df341eU, 0x5ed01294U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000029U);

            WR1_PROG(REG_F4H, 0x000000b0U);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000010U);

            HW_SCE_p_func101(0xb8864c8fU, 0xd40eee65U, 0x440c1142U, 0x9515d070U);
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

        HW_SCE_p_func100(0x51f40dddU, 0x46d5b45aU, 0x39120056U, 0x749363f9U);
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
            WR1_PROG(REG_2CH, change_endian_long(0x00007501U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x07c52d40U, 0x94fe6644U, 0xc57e8c17U, 0x8ac3ca36U);
            HW_SCE_p_func043();

            WR1_PROG(REG_94H, 0x000034c5U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00007501U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x4dc74ae7U, 0xa01be54cU, 0xf4164545U, 0xc17b8121U);
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

                HW_SCE_p_func101(0xb6088aacU, 0x099cecb9U, 0x0223b81dU, 0xe76aa254U);
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

            HW_SCE_p_func101(0xb924463fU, 0x0d955707U, 0x79bc4843U, 0x391411a5U);
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

                HW_SCE_p_func101(0xb75bf19cU, 0x8d920999U, 0x52236fe4U, 0x9cffbf45U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_94H, 0x380008e3U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func101(0x84992c60U, 0xf66ff33cU, 0x40d1c39aU, 0x01a0f245U);
        }

        HW_SCE_p_func100(0x972674c1U, 0x8b8a80a6U, 0x355e4abeU, 0x069dd297U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x477de5e0U, 0x715de8acU, 0x4c382e9eU, 0x47bdc664U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_104H, 0x00000000U);
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_100H, 0x00000080U);

                WR1_PROG(REG_FCH, 0x00000001U);

                WAIT_STS(REG_118H, 8, 0);

                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_104H, 0x00000000U);
                WR1_PROG(REG_14H, 0x00000020U);
                WR1_PROG(REG_100H, 0x00000000U);

                WR1_PROG(REG_FCH, 0x00000100U);

                HW_SCE_p_func101(0x8c71a730U, 0x9c9f4021U, 0xc7bc06ccU, 0x2c6fac42U);
            }
            else
            {
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_104H, InData_MsgLen[0]);
                WR1_PROG(REG_14H, 0x00000040U);
                WR1_PROG(REG_100H, InData_MsgLen[1]);

                WR1_PROG(REG_FCH, 0x00000001U);

                HW_SCE_p_func101(0xfa2f82daU, 0x18b32409U, 0x8e915cddU, 0x320094c0U);
            }

            return FSP_SUCCESS;
        }
    }
}
