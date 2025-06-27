/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func073_r1 (const uint32_t ARG1[])
{
    HW_SCE_p_func070_r1(ARG1);

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

    HW_SCE_p_func100(0xfbd5542eU, 0x952a2feaU, 0x3c2aed29U, 0xebd14e69U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        HW_SCE_p_func101(0x546d8feaU, 0xd05dc217U, 0x6c079791U, 0x6074a853U);
    }
    else
    {
        HW_SCE_p_func100(0x3b9fd33bU, 0x48c66d72U, 0xf7a02abfU, 0xbecc9087U);

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

        HW_SCE_p_func100(0x1ea7ea70U, 0x0e653e4bU, 0xeb782dcdU, 0x5bf0cf3bU);
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

        HW_SCE_p_func100(0x67291dacU, 0xcb3d1bd7U, 0x345458c0U, 0xd4323526U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            HW_SCE_p_func101(0xc723c6aaU, 0xa77955f0U, 0xdc281335U, 0x2349fb23U);
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

            HW_SCE_p_func100(0xcf58941fU, 0xf8e1b4a2U, 0x8e516437U, 0xa30045fbU);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func100(0xa41a6036U, 0x054e4956U, 0xf285584dU, 0x36a3b44bU);
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

                HW_SCE_p_func100(0x492eafaaU, 0x095416caU, 0xa324dd8eU, 0xc68d5468U);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    WR1_PROG(REG_94H, 0x00000800U);

                    HW_SCE_p_func101(0x8fdef240U, 0x4dda6e10U, 0x1562f7cdU, 0x7e6f8f2dU);
                }
                else
                {
                    WR1_PROG(REG_94H, 0x0000b400U);
                    WR1_PROG(REG_94H, 0x740d7282U);

                    HW_SCE_p_func101(0x7e779a60U, 0x4b10d6adU, 0x48879febU, 0x6adc9fb6U);
                }
            }
            else
            {
                HW_SCE_p_func100(0x706622bbU, 0xa689e94cU, 0xd9fef720U, 0x7e5b98e3U);
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
                HW_SCE_p_func071_r1(ARG1);

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

                HW_SCE_p_func100(0x9af253c0U, 0x7349f6a7U, 0x223a05e0U, 0xb65ad923U);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    WR1_PROG(REG_94H, 0x00000800U);

                    HW_SCE_p_func101(0xe6f3e348U, 0xf67cba3cU, 0xaf627d38U, 0xf8a21bcbU);
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

                    HW_SCE_p_func100(0x7f77ff35U, 0x1d4d6722U, 0xa2072bedU, 0x4387e18dU);
                    WR1_PROG(REG_40H, 0x00400000U);
                    WR1_PROG(REG_24H, 0x00000000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        WR1_PROG(REG_94H, 0x00000800U);

                        HW_SCE_p_func101(0xa641f952U, 0x8f25f978U, 0x12e2a8dfU, 0x33b4c266U);
                    }
                    else
                    {
                        HW_SCE_p_func100(0x008afbcfU, 0xc69f2d28U, 0xf5acb66aU, 0x141c211eU);

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

                        HW_SCE_p_func100(0x3b384b87U, 0x42f1d164U, 0xdbe8c5f0U, 0x635cdd5fU);
                        WR1_PROG(REG_40H, 0x00400000U);
                        WR1_PROG(REG_24H, 0x00000000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            WR1_PROG(REG_94H, 0x00000800U);

                            HW_SCE_p_func101(0x4cbd97b5U, 0x2286f4b3U, 0x04a69879U, 0xd20897b2U);
                        }
                        else
                        {
                            WR1_PROG(REG_94H, 0x0000b400U);
                            WR1_PROG(REG_94H, 0x740d7282U);

                            HW_SCE_p_func101(0x6ec326a2U, 0x2fefa556U, 0x21e024e2U, 0x1118a105U);
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
