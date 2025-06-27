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

void r_rsip_func089 (void)
{
    r_rsip_func100(bswap_32big(0xa081619aU),
                   bswap_32big(0x669f173bU),
                   bswap_32big(0xcc7cae79U),
                   bswap_32big(0x09688aa3U));

    WR1_PROG(REG_00A0H, 0x20010000U);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xf468b22aU),
                   bswap_32big(0x2e9e36b6U),
                   bswap_32big(0x85b97e0dU),
                   bswap_32big(0xf4d4db03U));
    WR1_PROG(REG_00B0H, 0x00009415U);
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xdda97fa1U),
                   bswap_32big(0x65d8f083U),
                   bswap_32big(0x4e0544fbU),
                   bswap_32big(0x283f8a4eU));
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

    WR1_PROG(REG_00B0H, 0x00009438U);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B0H, 0x0000943fU);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B4H, 0x003f000eU);
    WR1_PROG(REG_00B8H, 0x001c0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B8H, 0x0000001cU);

    WR1_PROG(REG_00A4H, 0x06060010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00380015U);
    WR1_PROG(REG_00B8H, 0x0031001cU);

    WR1_PROG(REG_00A4H, 0x06060002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00380031U);
    WR1_PROG(REG_00B8H, 0x001c0000U);

    WR1_PROG(REG_00A4H, 0x06060009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x001c0046U);
    WR1_PROG(REG_00B8H, 0x0015000eU);

    WR1_PROG(REG_00A4H, 0x06060005U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00380015U);
    WR1_PROG(REG_00B8H, 0x003f0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func100(bswap_32big(0xde782a88U),
                   bswap_32big(0xc7bb9f39U),
                   bswap_32big(0x474433d8U),
                   bswap_32big(0x04e0c1e2U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x811db785U), bswap_32big(0xc41ee48dU), bswap_32big(0xe70d779dU),
                       bswap_32big(0x64f2ca5aU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x1dc28ce3U), bswap_32big(0x5e5ba176U), bswap_32big(0x4f1fceadU),
                       bswap_32big(0xf91eace0U));
        WR1_PROG(REG_00B8H, 0x00000007U);

        WR1_PROG(REG_00A4H, 0x06060010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0038004dU);
        WR1_PROG(REG_00B8H, 0x00310007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x00009454U);
        WR1_PROG(REG_0000H, 0x00c00031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x00540085U);
        WR1_PROG(REG_00B8H, 0x00380000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00540007U);
        WR1_PROG(REG_00B8H, 0x003f0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00150031U);
        WR1_PROG(REG_00B8H, 0x0062003fU);

        WR1_PROG(REG_00A4H, 0x06060015U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        WR1_PROG(REG_00B0H, 0x00009415U);
        WR1_PROG(REG_0000H, 0x00c0002dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x00150062U);
        WR1_PROG(REG_00B8H, 0x00690000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x553cd13cU), bswap_32big(0x1404e71aU), bswap_32big(0x44a272e0U),
                       bswap_32big(0x5b166ff8U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x14e4b3a8U), bswap_32big(0x7e7f27daU), bswap_32big(0x2d40fb28U),
                           bswap_32big(0xd03669d8U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x2237ea98U), bswap_32big(0xac1f5bcdU), bswap_32big(0xe2b4a0baU),
                           bswap_32big(0x7ba1018eU));
            WR1_PROG(REG_00B4H, 0x001c0031U);
            WR1_PROG(REG_00B8H, 0x0077003fU);

            WR1_PROG(REG_00A4H, 0x06060015U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B0H, 0x00009415U);
            WR1_PROG(REG_0000H, 0x00c0002dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

            WR1_PROG(REG_00B4H, 0x00150077U);
            WR1_PROG(REG_00B8H, 0x00230000U);

            WR1_PROG(REG_00A4H, 0x0606000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0x5d2c0b68U), bswap_32big(0xcd7d8497U), bswap_32big(0x69f433bcU),
                           bswap_32big(0xeac95009U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x0f99e57eU),
                               bswap_32big(0xc33fe2a4U),
                               bswap_32big(0x6bd96190U),
                               bswap_32big(0x5010b874U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x0061e522U),
                               bswap_32big(0x8e4aa423U),
                               bswap_32big(0xe2102d6cU),
                               bswap_32big(0xdc6d8e0fU));
                WR1_PROG(REG_00B4H, 0x00150077U);
                WR1_PROG(REG_00B8H, 0x00310007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000941cU);
                WR1_PROG(REG_0000H, 0x00c0002dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

                WR1_PROG(REG_00B4H, 0x001c0007U);
                WR1_PROG(REG_00B8H, 0x00150000U);

                WR1_PROG(REG_00A4H, 0x0606000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00150031U);
                WR1_PROG(REG_00B8H, 0x001c0007U);

                WR1_PROG(REG_00A4H, 0x06060000U);
                WR1_PROG(REG_0008H, 0x00020000U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B4H, 0x001c0069U);
                WR1_PROG(REG_00B8H, 0x00230007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001c0070U);
                WR1_PROG(REG_00B8H, 0x002a0007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x002a0007U);
                WR1_PROG(REG_00B8H, 0x00150000U);

                WR1_PROG(REG_00A4H, 0x0606000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x004d0015U);
                WR1_PROG(REG_00B8H, 0x00700007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x004d0023U);
                WR1_PROG(REG_00B8H, 0x00150007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000941cU);
                WR1_PROG(REG_0000H, 0x00c00031U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B4H, 0x001c0015U);
                WR1_PROG(REG_00B8H, 0x00690000U);

                WR1_PROG(REG_00A4H, 0x06060009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000943fU);
                WR1_PROG(REG_0000H, 0x00c0002dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x003f004dU);
                WR1_PROG(REG_00B8H, 0x00770007U);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00770062U);
                WR1_PROG(REG_00B8H, 0x00310007U);

                WR1_PROG(REG_00A4H, 0x06060013U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B4H, 0x003f0031U);
                WR1_PROG(REG_00B8H, 0x00380000U);

                WR1_PROG(REG_00A4H, 0x0606000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x842b8b98U),
                               bswap_32big(0x51f03565U),
                               bswap_32big(0xee186ad5U),
                               bswap_32big(0x7f58c3c6U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0xbae88fddU),
                                   bswap_32big(0x3049eb7eU),
                                   bswap_32big(0x887bef8fU),
                                   bswap_32big(0x620acad0U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xa25f3780U),
                                   bswap_32big(0xe55a5a12U),
                                   bswap_32big(0x0020ca57U),
                                   bswap_32big(0xe89bc7baU));
                    WR1_PROG(REG_00B4H, 0x003f0031U);
                    WR1_PROG(REG_00B8H, 0x00380007U);

                    WR1_PROG(REG_00A4H, 0x06060002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B0H, 0x0000941cU);
                    WR1_PROG(REG_0000H, 0x00c0002dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

                    WR1_PROG(REG_00B4H, 0x001c0007U);
                    WR1_PROG(REG_00B8H, 0x00150000U);

                    WR1_PROG(REG_00A4H, 0x0606000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B4H, 0x00150038U);
                    WR1_PROG(REG_00B8H, 0x001c0007U);

                    WR1_PROG(REG_00A4H, 0x06060000U);
                    WR1_PROG(REG_0008H, 0x00020000U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);
                    WR1_PROG(REG_0040H, 0x00000d00U);

                    WR1_PROG(REG_00B4H, 0x001c0023U);
                    WR1_PROG(REG_00B8H, 0x00380007U);

                    WR1_PROG(REG_00A4H, 0x06060002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_00B4H, 0x001c002aU);
                    WR1_PROG(REG_00B8H, 0x003f0007U);

                    WR1_PROG(REG_00A4H, 0x06060002U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0094H, 0x0000b400U);
                    WR1_PROG(REG_0094H, 0x4390e124U);

                    r_rsip_func101(bswap_32big(0x5d4eb789U),
                                   bswap_32big(0x2bc43ebbU),
                                   bswap_32big(0xdfe12b4dU),
                                   bswap_32big(0x0a6634fdU));
                }
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x4390e124U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
