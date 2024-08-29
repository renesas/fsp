/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func073 (const uint32_t ARG1[])
{
    HW_SCE_p_func070(ARG1);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_B8H, 0x0000000aU);

    WR1_PROG(REG_A4H, 0x04040010U);

    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B0H, 0x0000141eU);
    WR1_PROG(REG_00H, 0x00c0001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

    WR1_PROG(REG_B4H, 0x001e000aU);
    WR1_PROG(REG_B8H, 0x00140000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B4H, 0x00690014U);
    WR1_PROG(REG_B8H, 0x00190000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_40H, 0x00210000U);

    WR1_PROG(REG_B4H, 0x001e0069U);
    WR1_PROG(REG_B8H, 0x00190000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);
    WR1_PROG(REG_40H, 0x00210000U);

    WR1_PROG(REG_B4H, 0x006e0014U);
    WR1_PROG(REG_B8H, 0x00190000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_40H, 0x00210000U);

    WR1_PROG(REG_B4H, 0x001e006eU);
    WR1_PROG(REG_B8H, 0x00190000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func100(0x056e32b7U, 0x2da176dcU, 0x8f1aa02fU, 0x1d084950U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        HW_SCE_p_func101(0xb54cbd3dU, 0xf17d8352U, 0x1166b7ccU, 0xe38eed20U);
    }
    else
    {
        HW_SCE_p_func100(0xfefd37f9U, 0x512acb6bU, 0x0dd874ecU, 0x99e8df0fU);

        WR1_PROG(REG_B4H, 0x001e0014U);
        WR1_PROG(REG_B8H, 0x00190000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0019006eU);
        WR1_PROG(REG_B8H, 0x000f000aU);

        WR1_PROG(REG_A4H, 0x04040000U);
        WR1_PROG(REG_08H, 0x00020000U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);
        WR1_PROG(REG_40H, 0x00000d00U);

        WR1_PROG(REG_B4H, 0x005a000fU);
        WR1_PROG(REG_B8H, 0x0014000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001423U);
        WR1_PROG(REG_00H, 0x00c00021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x00230072U);
        WR1_PROG(REG_B8H, 0x000f0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0014000fU);
        WR1_PROG(REG_B8H, 0x000f000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00140069U);
        WR1_PROG(REG_B8H, 0x0032000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00370076U);
        WR1_PROG(REG_B8H, 0x00190005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0037007aU);
        WR1_PROG(REG_B8H, 0x001e0005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001414U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x00140037U);
        WR1_PROG(REG_B8H, 0x00230005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001414U);
        WR1_PROG(REG_00H, 0x00c00021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x0014005fU);
        WR1_PROG(REG_B8H, 0x00280000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func100(0xbde8b68cU, 0xfab07457U, 0x2493fbcaU, 0xa60008d2U);
        WR1_PROG(REG_B4H, 0x00140005U);
        WR1_PROG(REG_B8H, 0x002d0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00320023U);
        WR1_PROG(REG_B8H, 0x0055002dU);

        WR1_PROG(REG_A4H, 0x04040015U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);
        WR1_PROG(REG_40H, 0x00000d00U);

        WR1_PROG(REG_B0H, 0x0000141eU);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x001e0055U);
        WR1_PROG(REG_B8H, 0x00190000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0x70bd2501U, 0x1701aef4U, 0x928ab38cU, 0xd6acfd36U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            HW_SCE_p_func101(0x5602eec5U, 0x04c2f794U, 0x871ec4f6U, 0xe6522e43U);
        }
        else
        {
            WR1_PROG(REG_B4H, 0x001e000fU);
            WR1_PROG(REG_B8H, 0x00190000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func100(0x52715911U, 0x08e95d86U, 0x4a005f1bU, 0x058b1dd3U);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func100(0xfdf38eb2U, 0x60ee8121U, 0x9fe25c9aU, 0x747a044bU);
                WR1_PROG(REG_B4H, 0x0014004bU);
                WR1_PROG(REG_B8H, 0x00190000U);

                WR1_PROG(REG_A4H, 0x04040009U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00140050U);
                WR1_PROG(REG_B8H, 0x001e0000U);

                WR1_PROG(REG_A4H, 0x04040009U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00140055U);
                WR1_PROG(REG_B8H, 0x00230000U);

                WR1_PROG(REG_A4H, 0x04040009U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B0H, 0x00001414U);
                WR1_PROG(REG_00H, 0x00c0001dU);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_14H, 0x000000a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                WR1_PROG(REG_B4H, 0x00140023U);
                WR1_PROG(REG_B8H, 0x00280005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B0H, 0x00001414U);
                WR1_PROG(REG_00H, 0x00c0001dU);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_14H, 0x000000a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

                WR1_PROG(REG_B4H, 0x00140005U);
                WR1_PROG(REG_B8H, 0x000f0000U);

                WR1_PROG(REG_A4H, 0x0404000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x000f0028U);
                WR1_PROG(REG_B8H, 0x00140005U);

                WR1_PROG(REG_A4H, 0x04040000U);
                WR1_PROG(REG_08H, 0x00020000U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);
                WR1_PROG(REG_40H, 0x00000d00U);

                WR1_PROG(REG_B4H, 0x00140019U);
                WR1_PROG(REG_B8H, 0x00280005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00690028U);
                WR1_PROG(REG_B8H, 0x00190000U);

                WR1_PROG(REG_A4H, 0x0404000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_40H, 0x00210000U);

                WR1_PROG(REG_B4H, 0x00280069U);
                WR1_PROG(REG_B8H, 0x00190000U);

                WR1_PROG(REG_A4H, 0x0404000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_40H, 0x00210000U);

                HW_SCE_p_func100(0x5fa71709U, 0x7eea20e0U, 0xc161149aU, 0x571cf1bbU);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    WR1_PROG(REG_94H, 0x00000800U);

                    HW_SCE_p_func101(0x2d968a02U, 0xd245f367U, 0xc25fc0bfU, 0x1ab60bb6U);
                }
                else
                {
                    WR1_PROG(REG_94H, 0x0000b400U);
                    WR1_PROG(REG_94H, 0x740d7282U);

                    HW_SCE_p_func101(0x81636b7fU, 0x5cf33a57U, 0xfc42aa12U, 0xd599c1a1U);
                }
            }
            else
            {
                HW_SCE_p_func100(0x32f03e83U, 0xa344f7e3U, 0xcccaa091U, 0xeac4a81bU);
                WR1_PROG(REG_B4H, 0x0014000fU);
                WR1_PROG(REG_B8H, 0x00320000U);

                WR1_PROG(REG_A4H, 0x04040009U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B0H, 0x00000415U);
                WR1_PROG(REG_00H, 0x00c00009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_B0H, 0x0000041aU);
                WR1_PROG(REG_00H, 0x00c00009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                HW_SCE_p_func071(ARG1);

                WR1_PROG(REG_B4H, 0x00320023U);
                WR1_PROG(REG_B8H, 0x0046002dU);

                WR1_PROG(REG_A4H, 0x04040015U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);
                WR1_PROG(REG_40H, 0x00000d00U);

                WR1_PROG(REG_B0H, 0x0000141eU);
                WR1_PROG(REG_00H, 0x00c0001dU);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_14H, 0x000000a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                WR1_PROG(REG_B4H, 0x001e0046U);
                WR1_PROG(REG_B8H, 0x00190000U);

                WR1_PROG(REG_A4H, 0x0404000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_40H, 0x00210000U);

                HW_SCE_p_func100(0x597ddfe8U, 0x6306ea48U, 0x5ddb1460U, 0xc8bad192U);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    WR1_PROG(REG_94H, 0x00000800U);

                    HW_SCE_p_func101(0x5990ee72U, 0x4b4e494bU, 0x92ff91afU, 0x82051d17U);
                }
                else
                {
                    WR1_PROG(REG_B4H, 0x00550046U);
                    WR1_PROG(REG_B8H, 0x00230005U);

                    WR1_PROG(REG_A4H, 0x04040013U);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);
                    WR1_PROG(REG_40H, 0x00000d00U);

                    WR1_PROG(REG_B0H, 0x00001414U);
                    WR1_PROG(REG_00H, 0x00c0001dU);
                    WAIT_STS(REG_04H, 30, 0);
                    WR1_PROG(REG_40H, 0x00001800U);
                    WR1_PROG(REG_14H, 0x000000a5U);
                    WAIT_STS(REG_14H, 31, 1);
                    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                    WR1_PROG(REG_B4H, 0x00140023U);
                    WR1_PROG(REG_B8H, 0x002d0000U);

                    WR1_PROG(REG_A4H, 0x0404000aU);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_40H, 0x00210000U);

                    HW_SCE_p_func100(0x45738d33U, 0xab94d1e6U, 0xe6d6a6b1U, 0xe48b985dU);
                    WR1_PROG(REG_40H, 0x00400000U);
                    WR1_PROG(REG_24H, 0x00000000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        WR1_PROG(REG_94H, 0x00000800U);

                        HW_SCE_p_func101(0x7b267b59U, 0x261e8c94U, 0x82f879e3U, 0x08a5737aU);
                    }
                    else
                    {
                        HW_SCE_p_func100(0x70668f9fU, 0x47343c20U, 0x4f6bbdd5U, 0xdbce9747U);

                        WR1_PROG(REG_B4H, 0x00140023U);
                        WR1_PROG(REG_B8H, 0x00280005U);

                        WR1_PROG(REG_A4H, 0x04040002U);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_B0H, 0x00001414U);
                        WR1_PROG(REG_00H, 0x00c0001dU);
                        WAIT_STS(REG_04H, 30, 0);
                        WR1_PROG(REG_40H, 0x00001800U);
                        WR1_PROG(REG_14H, 0x000000a5U);
                        WAIT_STS(REG_14H, 31, 1);
                        WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

                        WR1_PROG(REG_B4H, 0x00140005U);
                        WR1_PROG(REG_B8H, 0x000f0000U);

                        WR1_PROG(REG_A4H, 0x0404000aU);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_B4H, 0x000f0028U);
                        WR1_PROG(REG_B8H, 0x00140005U);

                        WR1_PROG(REG_A4H, 0x04040000U);
                        WR1_PROG(REG_08H, 0x00020000U);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);
                        WR1_PROG(REG_40H, 0x00000d00U);

                        WR1_PROG(REG_B4H, 0x00140019U);
                        WR1_PROG(REG_B8H, 0x00280005U);

                        WR1_PROG(REG_A4H, 0x04040002U);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_B4H, 0x00690028U);
                        WR1_PROG(REG_B8H, 0x00190000U);

                        WR1_PROG(REG_A4H, 0x0404000aU);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_40H, 0x00210000U);

                        WR1_PROG(REG_B4H, 0x00280069U);
                        WR1_PROG(REG_B8H, 0x00190000U);

                        WR1_PROG(REG_A4H, 0x0404000aU);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_40H, 0x00210000U);

                        HW_SCE_p_func100(0x48b7d3aaU, 0x40a756c8U, 0x002446bbU, 0xae8329dcU);
                        WR1_PROG(REG_40H, 0x00400000U);
                        WR1_PROG(REG_24H, 0x00000000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            WR1_PROG(REG_94H, 0x00000800U);

                            HW_SCE_p_func101(0x1b562b57U, 0x23de575aU, 0x3c426f52U, 0x24228fccU);
                        }
                        else
                        {
                            WR1_PROG(REG_94H, 0x0000b400U);
                            WR1_PROG(REG_94H, 0x740d7282U);

                            HW_SCE_p_func101(0x6c687973U, 0x271de84aU, 0xae5cfeceU, 0xb1b41057U);
                        }
                    }
                }
            }
        }
    }

    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x740d7282U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A60000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
    WR1_PROG(REG_24H, 0x00000000U);
}
