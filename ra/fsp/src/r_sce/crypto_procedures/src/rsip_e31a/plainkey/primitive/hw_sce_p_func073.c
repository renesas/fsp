/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func073_r3 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

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

    HW_SCE_p_func100(0xd44326cfU,0xcc4c8da1U,0x09650840U,0x168841b4U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        HW_SCE_p_func101(0x15223210U,0x048974d4U,0xbf795623U,0x0cc6c2e5U);
    }
    else
    {
        HW_SCE_p_func100(0xf015a2d2U,0x4d6c5ea7U,0x8f4247b4U,0x34e1a825U);

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

        WR1_PROG(REG_B4H, 0x00230069U);
        WR1_PROG(REG_B8H, 0x000a0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00370076U);
        WR1_PROG(REG_B8H, 0x004b0005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0037007aU);
        WR1_PROG(REG_B8H, 0x00500005U);

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
        WR1_PROG(REG_B8H, 0x00550005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0023005fU);
        WR1_PROG(REG_B8H, 0x00280000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00230005U);
        WR1_PROG(REG_B8H, 0x002d0000U);

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

        WR1_PROG(REG_B4H, 0x00230019U);
        WR1_PROG(REG_B8H, 0x005a0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0023001eU);
        WR1_PROG(REG_B8H, 0x005f0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00230055U);
        WR1_PROG(REG_B8H, 0x00640000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x0000046fU);
        WR1_PROG(REG_00H, 0x00c00009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x004b005aU);
        WR1_PROG(REG_B8H, 0x00140000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        WR1_PROG(REG_B4H, 0x005a004bU);
        WR1_PROG(REG_B8H, 0x00140000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        WR1_PROG(REG_B4H, 0x0050005fU);
        WR1_PROG(REG_B8H, 0x00140000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        WR1_PROG(REG_B4H, 0x005f0050U);
        WR1_PROG(REG_B8H, 0x00140000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0xddf243d7U,0xa423d005U,0x3bd6f7c8U,0xd187ee6cU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_B4H, 0x00550064U);
            WR1_PROG(REG_B8H, 0x00730005U);

            WR1_PROG(REG_A4H, 0x04040013U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func101(0xe3fc1b40U,0x44b75688U,0x09354e09U,0xd126dd98U);
        }
        else
        {
            WR1_PROG(REG_B4H, 0x00000064U);
            WR1_PROG(REG_B8H, 0x0073002dU);

            WR1_PROG(REG_A4H, 0x04040014U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func101(0xf224d8abU,0x8167811fU,0x5c12584fU,0x833a6c01U);
        }

        WR1_PROG(REG_B4H, 0x0023000fU);
        WR1_PROG(REG_B8H, 0x00370000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00190019U);
        WR1_PROG(REG_B8H, 0x00190000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x001e001eU);
        WR1_PROG(REG_B8H, 0x001e0000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00230023U);
        WR1_PROG(REG_B8H, 0x00230000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_94H, 0x00000800U);
        for(iLoop = 0U; iLoop < 2U; iLoop++)
        {
            WR1_PROG(REG_94H, 0x000008a5U);

            WR1_PROG(REG_94H, 0x38000c00U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            HW_SCE_p_func100(0x94010accU,0xb6acc956U,0xd6224e72U,0x58986c24U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_B0H, 0x00000834U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000835U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x0000082fU);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000830U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                HW_SCE_p_func101(0xf8c1d30bU,0x200eb628U,0x5d6416ecU,0xdf6ee117U);
            }
            else
            {
                WR1_PROG(REG_B0H, 0x00000836U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000837U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000831U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000832U);
                WR1_PROG(REG_9CH, 0x80820005U);
                WR1_PROG(REG_00H, 0x03430009U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                HW_SCE_p_func101(0x8a72d1cfU,0x999805d9U,0x474ff2caU,0x17504d70U);
            }

            WR1_PROG(REG_94H, 0x00000821U);

            for(jLoop = 0U; jLoop < 4U; jLoop++)
            {
                WR1_PROG(REG_94H, 0x000034a1U);

                WR1_PROG(REG_94H, 0x00026ca5U);

                WR1_PROG(REG_94H, 0x00003865U);

                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000010U);

                WR1_PROG(REG_94H, 0x00003885U);

                WR1_PROG(REG_94H, 0x00000842U);

                for(kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    WR1_PROG(REG_94H, 0x000008a5U);

                    WR1_PROG(REG_94H, 0x01816ca3U);
                    WR1_PROG(REG_94H, 0x01816ca4U);
                    WR1_PROG(REG_94H, 0x00016c63U);
                    WR1_PROG(REG_94H, 0x00016c84U);

                    WR1_PROG(REG_B0H, 0x00001414U);
                    WR1_PROG(REG_00H, 0x00c0001dU);
                    WAIT_STS(REG_04H, 30, 0);
                    WR1_PROG(REG_40H, 0x00001800U);
                    WR1_PROG(REG_14H, 0x000000a5U);
                    WAIT_STS(REG_14H, 31, 1);
                    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                    WR1_PROG(REG_B4H, 0x00140019U);
                    WR1_PROG(REG_B8H, 0x000f0000U);

                    WR1_PROG(REG_A4H, 0x0404000aU);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    WR1_PROG(REG_B4H, 0x00140023U);
                    WR1_PROG(REG_B8H, 0x000f0000U);

                    WR1_PROG(REG_A4H, 0x0404000aU);
                    WR1_PROG(REG_A0H, 0x20010001U);
                    WAIT_STS(REG_A8H, 0, 1);
                    WR1_PROG(REG_ACH, 0x00000001U);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    HW_SCE_p_func100(0x0472c7a8U,0x5363d49dU,0x6e422d40U,0x17637d0cU);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        WR1_PROG(REG_B4H, 0x00000023U);
                        WR1_PROG(REG_B8H, 0x0023002dU);

                        WR1_PROG(REG_A4H, 0x04040014U);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);
                        WR1_PROG(REG_40H, 0x00000d00U);

                        HW_SCE_p_func101(0x656affc3U,0xf594d350U,0x234a2ddfU,0xabebf293U);
                    }
                    else
                    {
                        HW_SCE_p_func101(0xdf8c09abU,0xee6b1638U,0xd68d436fU,0x7620be60U);
                    }

                    WR1_PROG(REG_94H, 0x38000ca5U);
                    WR1_PROG(REG_9CH, 0x00000080U);
                    WR1_PROG(REG_40H, 0x00A70000U);

                    HW_SCE_p_func100(0x1033ada8U,0xaa087ee5U,0xc7ce5a60U,0x0fa2e522U);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        HW_SCE_p_func100(0xdc377967U,0x7018f313U,0x1591c55dU,0x6200f4adU);

                        WR1_PROG(REG_B0H, 0x00001414U);
                        WR1_PROG(REG_00H, 0x00c00021U);
                        WAIT_STS(REG_04H, 30, 0);
                        WR1_PROG(REG_40H, 0x00001800U);

                        WR1_PROG(REG_94H, 0x00007c05U);
                        WR1_PROG(REG_40H, 0x00600000U);

                        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
                        {
                            WR1_PROG(REG_B4H, 0x0014004bU);
                            WR1_PROG(REG_B8H, 0x003c0000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140050U);
                            WR1_PROG(REG_B8H, 0x00410000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140055U);
                            WR1_PROG(REG_B8H, 0x00460000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            HW_SCE_p_func101(0xd9f2a1afU,0x36443713U,0x31c5ca55U,0xed51c392U);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
                        {
                            WR1_PROG(REG_B4H, 0x0014005aU);
                            WR1_PROG(REG_B8H, 0x003c0000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x0014005fU);
                            WR1_PROG(REG_B8H, 0x00410000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140064U);
                            WR1_PROG(REG_B8H, 0x00460000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            HW_SCE_p_func101(0x2996b285U,0x82aec079U,0x89bb240eU,0x31027650U);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
                        {
                            WR1_PROG(REG_B4H, 0x00140069U);
                            WR1_PROG(REG_B8H, 0x003c0000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x0014006eU);
                            WR1_PROG(REG_B8H, 0x00410000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140073U);
                            WR1_PROG(REG_B8H, 0x00460000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            HW_SCE_p_func101(0x86a0c4b5U,0x1d4b7a02U,0x905353f1U,0x599837e7U);
                        }

                        WR1_PROG(REG_B0H, 0x00001414U);
                        WR1_PROG(REG_00H, 0x00c0001dU);
                        WAIT_STS(REG_04H, 30, 0);
                        WR1_PROG(REG_40H, 0x00001800U);
                        WR1_PROG(REG_14H, 0x000000a5U);
                        WAIT_STS(REG_14H, 31, 1);
                        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                        WR1_PROG(REG_B4H, 0x00140019U);
                        WR1_PROG(REG_B8H, 0x000f0000U);

                        WR1_PROG(REG_A4H, 0x0404000aU);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        WR1_PROG(REG_B4H, 0x00140023U);
                        WR1_PROG(REG_B8H, 0x000f0000U);

                        WR1_PROG(REG_A4H, 0x0404000aU);
                        WR1_PROG(REG_A0H, 0x20010001U);
                        WAIT_STS(REG_A8H, 0, 1);
                        WR1_PROG(REG_ACH, 0x00000001U);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        HW_SCE_p_func100(0x9ec30cecU,0xaf1fe16eU,0x2e4fcba6U,0x879d21ccU);
                        WR1_PROG(REG_40H, 0x00400000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            WR1_PROG(REG_B4H, 0x0014003cU);
                            WR1_PROG(REG_B8H, 0x000f0000U);

                            WR1_PROG(REG_A4H, 0x0404000aU);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            WR1_PROG(REG_B4H, 0x00140046U);
                            WR1_PROG(REG_B8H, 0x000f0000U);

                            WR1_PROG(REG_A4H, 0x0404000aU);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            HW_SCE_p_func100(0x173624dcU,0xa3ea5c81U,0x9ac97b2dU,0xef93ed00U);
                            WR1_PROG(REG_40H, 0x00400000U);

                            if (CHCK_STS(REG_40H, 22, 1))
                            {
                                WR1_PROG(REG_B4H, 0x003c0019U);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                WR1_PROG(REG_B4H, 0x0019003cU);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                WR1_PROG(REG_B4H, 0x0041001eU);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                WR1_PROG(REG_B4H, 0x001e0041U);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                WR1_PROG(REG_B4H, 0x00460023U);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                WR1_PROG(REG_B4H, 0x00230046U);
                                WR1_PROG(REG_B8H, 0x000f0000U);

                                WR1_PROG(REG_A4H, 0x0404000aU);
                                WR1_PROG(REG_A0H, 0x20010001U);
                                WAIT_STS(REG_A8H, 0, 1);
                                WR1_PROG(REG_ACH, 0x00000001U);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func100(0x8aea722fU,0xcd737685U,0x65fd1f3dU,0x1b1ca693U);
                                WR1_PROG(REG_40H, 0x00400000U);

                                if (CHCK_STS(REG_40H, 22, 1))
                                {
                                    WR1_PROG(REG_B4H, 0x00460023U);
                                    WR1_PROG(REG_B8H, 0x00230005U);

                                    WR1_PROG(REG_A4H, 0x04040013U);
                                    WR1_PROG(REG_A0H, 0x20010001U);
                                    WAIT_STS(REG_A8H, 0, 1);
                                    WR1_PROG(REG_ACH, 0x00000001U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    HW_SCE_p_func101(0xb6ed1778U,0x3cde6dc6U,0x38eef0b6U,0x3325dea6U);
                                }
                                else
                                {
                                    WR1_PROG(REG_B4H, 0x00000023U);
                                    WR1_PROG(REG_B8H, 0x0023002dU);

                                    WR1_PROG(REG_A4H, 0x04040014U);
                                    WR1_PROG(REG_A0H, 0x20010001U);
                                    WAIT_STS(REG_A8H, 0, 1);
                                    WR1_PROG(REG_ACH, 0x00000001U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    HW_SCE_p_func101(0x4b07d3c2U,0x1cbb75b8U,0xe772770eU,0x5304c00bU);
                                }
                            }
                            else
                            {
                                HW_SCE_p_func101(0x6c53ae6bU,0x8bd65050U,0x2d986b2aU,0x0e88c60aU);
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_B0H, 0x00001414U);
                            WR1_PROG(REG_00H, 0x00c00021U);
                            WAIT_STS(REG_04H, 30, 0);
                            WR1_PROG(REG_40H, 0x00001800U);

                            WR1_PROG(REG_B4H, 0x0014003cU);
                            WR1_PROG(REG_B8H, 0x00190000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140041U);
                            WR1_PROG(REG_B8H, 0x001e0000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            WR1_PROG(REG_B4H, 0x00140046U);
                            WR1_PROG(REG_B8H, 0x00230000U);

                            WR1_PROG(REG_A4H, 0x04040009U);
                            WR1_PROG(REG_A0H, 0x20010001U);
                            WAIT_STS(REG_A8H, 0, 1);
                            WR1_PROG(REG_ACH, 0x00000001U);

                            HW_SCE_p_func101(0x684aa554U,0x72a82464U,0x8adb7d99U,0xed6acda3U);
                        }
                    }
                    else
                    {
                        HW_SCE_p_func101(0x4005b519U,0x6657c68fU,0x0db70743U,0x30407c0cU);
                    }

                    WR1_PROG(REG_94H, 0x00002c40U);
                    HW_SCE_p_func101(0x81ae2678U,0x5b63367bU,0x7edb0e92U,0x92b60bfbU);
                }

                WR1_PROG(REG_94H, 0x38008840U);
                WR1_PROG(REG_94H, 0x00000020U);
                WR1_PROG(REG_9CH, 0x00000080U);
                WR1_PROG(REG_40H, 0x00270000U);

                WR1_PROG(REG_40H, 0x00402000U);

                WR1_PROG(REG_94H, 0x00002c20U);

                HW_SCE_p_func101(0xc3a10a91U,0x77b8f7d9U,0x35127eaeU,0xd28bd99cU);
            }

            WR1_PROG(REG_94H, 0x38008820U);
            WR1_PROG(REG_94H, 0x00000004U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_94H, 0x00002c00U);

            HW_SCE_p_func101(0x4730b82eU,0x93731f89U,0x72ad1513U,0x29c42420U);
        }

        WR1_PROG(REG_94H, 0x38008800U);
        WR1_PROG(REG_94H, 0x00000002U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        WR1_PROG(REG_40H, 0x00402000U);

        WR1_PROG(REG_B0H, 0x00001414U);
        WR1_PROG(REG_00H, 0x00c00021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x0014000aU);
        WR1_PROG(REG_B8H, 0x00690000U);

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
        WR1_PROG(REG_B8H, 0x002d0000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0x446ff254U,0x3dca4f31U,0x7a4fb084U,0x466eadc5U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            HW_SCE_p_func101(0xd4c0a804U,0x3f0d7b92U,0x8f0e1601U,0x3a1cc264U);
        }
        else
        {
            HW_SCE_p_func100(0x7445c5a7U,0x7aae8e0aU,0xcd2fd552U,0x8a923af2U);

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

            HW_SCE_p_func100(0x983fe418U,0xa81ba2cdU,0x185a3d20U,0x67425464U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                HW_SCE_p_func101(0x011b36e9U,0xbba2b20eU,0x7588ab4fU,0x64fa8feaU);
            }
            else
            {
                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0x603ce63aU);

                HW_SCE_p_func101(0xee2f86e6U,0x5e9c9e4bU,0x7a9d9cdeU,0xcb2c5cfaU);
            }
        }
    }

    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x603ce63aU);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A70000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
