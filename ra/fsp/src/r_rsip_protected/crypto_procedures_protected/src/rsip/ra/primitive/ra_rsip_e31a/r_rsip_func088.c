/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func088 (void)
{
    r_rsip_func100(bswap_32big(0xfcd8c748U),
                   bswap_32big(0xc2307edfU),
                   bswap_32big(0xad33248bU),
                   bswap_32big(0x39126f9eU));

    WR1_PROG(REG_00A0H, 0x20010000U);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x83c53387U),
                   bswap_32big(0x8db9301eU),
                   bswap_32big(0x60c83150U),
                   bswap_32big(0xe8133015U));
    WR1_PROG(REG_00B0H, 0x0000140fU);
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001428U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B0H, 0x0000142dU);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B4H, 0x002d000aU);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B8H, 0x00000014U);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028000fU);
    WR1_PROG(REG_00B8H, 0x00230014U);

    WR1_PROG(REG_00A4H, 0x04040002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00280023U);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x04040009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00140032U);
    WR1_PROG(REG_00B8H, 0x000f000aU);

    WR1_PROG(REG_00A4H, 0x04040005U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028000fU);
    WR1_PROG(REG_00B8H, 0x002d0000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func100(bswap_32big(0x9f6d0e67U),
                   bswap_32big(0x53513639U),
                   bswap_32big(0x4cf66898U),
                   bswap_32big(0x96d841f3U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x31fe6608U), bswap_32big(0x786fe276U), bswap_32big(0xad730323U),
                       bswap_32big(0xf7ce5b8aU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x18cde02aU), bswap_32big(0xa1af898fU), bswap_32big(0x82889b22U),
                       bswap_32big(0xdb7023a1U));
        WR1_PROG(REG_00B8H, 0x00000005U);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00280037U);
        WR1_PROG(REG_00B8H, 0x00230005U);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000143cU);
        WR1_PROG(REG_0000H, 0x00c00021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x003c005fU);
        WR1_PROG(REG_00B8H, 0x00280000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x003c0005U);
        WR1_PROG(REG_00B8H, 0x002d0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x000f0023U);
        WR1_PROG(REG_00B8H, 0x0046002dU);

        WR1_PROG(REG_00A4H, 0x04040015U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        WR1_PROG(REG_00B0H, 0x0000140fU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x000f0046U);
        WR1_PROG(REG_00B8H, 0x004b0000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0xd595629cU), bswap_32big(0xb13a03d7U), bswap_32big(0x6f519fe0U),
                       bswap_32big(0x8540a863U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x879d4cf6U), bswap_32big(0x2e3471b7U), bswap_32big(0x9aad8b23U),
                           bswap_32big(0x837889f3U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xbd8f7b56U), bswap_32big(0x6fa86a8eU), bswap_32big(0x26cee92eU),
                           bswap_32big(0x9b27f4b4U));
            WR1_PROG(REG_00B4H, 0x00140023U);
            WR1_PROG(REG_00B8H, 0x0055002dU);

            WR1_PROG(REG_00A4H, 0x04040015U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B0H, 0x0000140fU);
            WR1_PROG(REG_0000H, 0x00c0001dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

            WR1_PROG(REG_00B4H, 0x000f0055U);
            WR1_PROG(REG_00B8H, 0x00190000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0x95a604b7U), bswap_32big(0x2fd4316bU), bswap_32big(0xa1b732cbU),
                           bswap_32big(0x9cec0513U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x40ca68bcU),
                               bswap_32big(0x122a08eeU),
                               bswap_32big(0xbefa74f8U),
                               bswap_32big(0x9a3805efU));
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe132d8a5U),
                               bswap_32big(0x45928744U),
                               bswap_32big(0x16901808U),
                               bswap_32big(0xa54c441aU));
                WR1_PROG(REG_00B4H, 0x000f0055U);
                WR1_PROG(REG_00B8H, 0x00230005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001414U);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

                WR1_PROG(REG_00B4H, 0x00140005U);
                WR1_PROG(REG_00B8H, 0x000f0000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x000f0023U);
                WR1_PROG(REG_00B8H, 0x00140005U);

                WR1_PROG(REG_00A4H, 0x04040000U);
                WR1_PROG(REG_0008H, 0x00020000U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B4H, 0x0014004bU);
                WR1_PROG(REG_00B8H, 0x00190005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00140050U);
                WR1_PROG(REG_00B8H, 0x001e0005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e0005U);
                WR1_PROG(REG_00B8H, 0x000f0000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0037000fU);
                WR1_PROG(REG_00B8H, 0x00500005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00370019U);
                WR1_PROG(REG_00B8H, 0x000f0005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001414U);
                WR1_PROG(REG_0000H, 0x00c00021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B4H, 0x0014000fU);
                WR1_PROG(REG_00B8H, 0x004b0000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000142dU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x002d0037U);
                WR1_PROG(REG_00B8H, 0x00550005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00550046U);
                WR1_PROG(REG_00B8H, 0x00230005U);

                WR1_PROG(REG_00A4H, 0x04040013U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B4H, 0x002d0023U);
                WR1_PROG(REG_00B8H, 0x00280000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x9d8640edU),
                               bswap_32big(0x9a0e9231U),
                               bswap_32big(0x8def4afeU),
                               bswap_32big(0xc0b9c480U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0x7fbe47abU),
                                   bswap_32big(0xa644294dU),
                                   bswap_32big(0xc6105a93U),
                                   bswap_32big(0x29526c41U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x773dc358U),
                                   bswap_32big(0xbaf636b5U),
                                   bswap_32big(0x239b3d38U),
                                   bswap_32big(0xb4fce1c2U));
                    WR1_PROG(REG_00B4H, 0x002d0023U);
                    WR1_PROG(REG_00B8H, 0x00280005U);

                    WR1_PROG(REG_00A4H, 0x04040002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B0H, 0x00001414U);
                    WR1_PROG(REG_0000H, 0x00c0001dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

                    WR1_PROG(REG_00B4H, 0x00140005U);
                    WR1_PROG(REG_00B8H, 0x000f0000U);

                    WR1_PROG(REG_00A4H, 0x0404000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B4H, 0x000f0028U);
                    WR1_PROG(REG_00B8H, 0x00140005U);

                    WR1_PROG(REG_00A4H, 0x04040000U);
                    WR1_PROG(REG_0008H, 0x00020000U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);
                    WR1_PROG(REG_0040H, 0x00000d00U);

                    WR1_PROG(REG_00B4H, 0x00140019U);
                    WR1_PROG(REG_00B8H, 0x00280005U);

                    WR1_PROG(REG_00A4H, 0x04040002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B4H, 0x0014001eU);
                    WR1_PROG(REG_00B8H, 0x002d0005U);

                    WR1_PROG(REG_00A4H, 0x04040002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0094H, 0x0000b400U);
                    WR1_PROG(REG_0094H, 0x19253b14U);

                    r_rsip_func101(bswap_32big(0xc95d1f17U),
                                   bswap_32big(0x26936725U),
                                   bswap_32big(0x3db46a16U),
                                   bswap_32big(0xabc09f4eU));
                }
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x19253b14U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
