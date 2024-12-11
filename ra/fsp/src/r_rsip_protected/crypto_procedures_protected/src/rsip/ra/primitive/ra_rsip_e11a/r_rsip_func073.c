/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

void r_rsip_func073 (const uint32_t ARG1[])
{
    r_rsip_func070(ARG1);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_00B8H, 0x0000000aU);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B0H, 0x0000141eU);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B4H, 0x001e000aU);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00690014U);
    WR1_PROG(REG_00B8H, 0x00190000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x001e0069U);
    WR1_PROG(REG_00B8H, 0x00190000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);
    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x006e0014U);
    WR1_PROG(REG_00B8H, 0x00190000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x001e006eU);
    WR1_PROG(REG_00B8H, 0x00190000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func100(bswap_32big(0xe51f8c65U), bswap_32big(0xafa0f132U), bswap_32big(0x457067c3U), bswap_32big(0x63aa4fc3U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0xcdba6a97U), bswap_32big(0x89a1ed04U), bswap_32big(0xde937922U), bswap_32big(0xad3b4582U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x7095fd7cU), bswap_32big(0x9d8da667U), bswap_32big(0xb72431feU), bswap_32big(0xa3cc89b9U));

        WR1_PROG(REG_00B4H, 0x001e0014U);
        WR1_PROG(REG_00B8H, 0x00190000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0019006eU);
        WR1_PROG(REG_00B8H, 0x000f000aU);

        WR1_PROG(REG_00A4H, 0x04040000U);
        WR1_PROG(REG_0008H, 0x00020000U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        WR1_PROG(REG_00B4H, 0x005a000fU);
        WR1_PROG(REG_00B8H, 0x0014000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x00001423U);
        WR1_PROG(REG_0000H, 0x00c00021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x00230072U);
        WR1_PROG(REG_00B8H, 0x000f0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0014000fU);
        WR1_PROG(REG_00B8H, 0x000f000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00140069U);
        WR1_PROG(REG_00B8H, 0x0032000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B8H, 0x00000005U);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00370076U);
        WR1_PROG(REG_00B8H, 0x00190005U);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0037007aU);
        WR1_PROG(REG_00B8H, 0x001e0005U);

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
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x00140037U);
        WR1_PROG(REG_00B8H, 0x00230005U);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x00001414U);
        WR1_PROG(REG_0000H, 0x00c00021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x0014005fU);
        WR1_PROG(REG_00B8H, 0x00280000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        r_rsip_func100(bswap_32big(0x225ffe5eU), bswap_32big(0x3c6b43c4U), bswap_32big(0x217d24dcU), bswap_32big(0x51d01a1aU));
        WR1_PROG(REG_00B4H, 0x00140005U);
        WR1_PROG(REG_00B8H, 0x002d0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00320023U);
        WR1_PROG(REG_00B8H, 0x0055002dU);

        WR1_PROG(REG_00A4H, 0x04040015U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        WR1_PROG(REG_00B0H, 0x0000141eU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x001e0055U);
        WR1_PROG(REG_00B8H, 0x00190000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x82cfd909U), bswap_32big(0xbee3ad8bU), bswap_32big(0xfe2270a2U), bswap_32big(0x2ae2a2e7U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xb3c66a59U), bswap_32big(0xe52c8fe5U), bswap_32big(0x219e3fd8U), bswap_32big(0x4ea0aee5U));
        }
        else
        {
            WR1_PROG(REG_00B4H, 0x001e000fU);
            WR1_PROG(REG_00B8H, 0x00190000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0xe01f89dfU), bswap_32big(0x06ca454cU), bswap_32big(0xf518fa67U), bswap_32big(0xa843a1daU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0x55a9773bU), bswap_32big(0x92751d13U), bswap_32big(0xcb494804U), bswap_32big(0x69c4439dU));
                WR1_PROG(REG_00B4H, 0x0014004bU);
                WR1_PROG(REG_00B8H, 0x00190000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00140050U);
                WR1_PROG(REG_00B8H, 0x001e0000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00140055U);
                WR1_PROG(REG_00B8H, 0x00230000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001414U);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x00140023U);
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

                WR1_PROG(REG_00B4H, 0x00690028U);
                WR1_PROG(REG_00B8H, 0x00190000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                WR1_PROG(REG_00B4H, 0x00280069U);
                WR1_PROG(REG_00B8H, 0x00190000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x2d73f732U), bswap_32big(0x5779bd65U), bswap_32big(0x6f792fd2U), bswap_32big(0x0145d020U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0x491ba8b6U), bswap_32big(0xc757603fU), bswap_32big(0xa0acca1cU), bswap_32big(0x714300ffU));
                }
                else
                {
                    WR1_PROG(REG_0094H, 0x0000b400U);
                    WR1_PROG(REG_0094H, 0x665331ecU);

                    r_rsip_func101(bswap_32big(0x317005c5U), bswap_32big(0x344f3c89U), bswap_32big(0xbe26f439U), bswap_32big(0x9f714878U));
                }
            }
            else
            {
                r_rsip_func100(bswap_32big(0x53e1b0d1U), bswap_32big(0xc4b0695fU), bswap_32big(0xea26a6feU), bswap_32big(0x43be98e4U));
                WR1_PROG(REG_00B4H, 0x0014000fU);
                WR1_PROG(REG_00B8H, 0x00320000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00000415U);
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x0000041aU);
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                r_rsip_func071(ARG1);

                WR1_PROG(REG_00B4H, 0x00320023U);
                WR1_PROG(REG_00B8H, 0x0046002dU);

                WR1_PROG(REG_00A4H, 0x04040015U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B0H, 0x0000141eU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x001e0046U);
                WR1_PROG(REG_00B8H, 0x00190000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x9f1c1196U), bswap_32big(0x80a8ac9bU), bswap_32big(0x7cd42ffcU), bswap_32big(0x27674c5aU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0x62a730efU), bswap_32big(0xb6295761U), bswap_32big(0xd1db0538U), bswap_32big(0xf6455f2eU));
                }
                else
                {
                    WR1_PROG(REG_00B4H, 0x00550046U);
                    WR1_PROG(REG_00B8H, 0x00230005U);

                    WR1_PROG(REG_00A4H, 0x04040013U);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);
                    WR1_PROG(REG_0040H, 0x00000d00U);

                    WR1_PROG(REG_00B0H, 0x00001414U);
                    WR1_PROG(REG_0000H, 0x00c0001dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                    WR1_PROG(REG_00B4H, 0x00140023U);
                    WR1_PROG(REG_00B8H, 0x002d0000U);

                    WR1_PROG(REG_00A4H, 0x0404000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0040H, 0x00210000U);

                    r_rsip_func100(bswap_32big(0xbc5aedbcU), bswap_32big(0xb008e818U), bswap_32big(0xa7138284U), bswap_32big(0x0839271eU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x00000800U);

                        r_rsip_func101(bswap_32big(0xc9c2fd8eU), bswap_32big(0xb1c0c885U), bswap_32big(0x85afa958U), bswap_32big(0x4cc63ed6U));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x6270e391U), bswap_32big(0x43dc7313U), bswap_32big(0x1e7c4321U), bswap_32big(0x028cb15dU));

                        WR1_PROG(REG_00B4H, 0x00140023U);
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

                        WR1_PROG(REG_00B4H, 0x00690028U);
                        WR1_PROG(REG_00B8H, 0x00190000U);

                        WR1_PROG(REG_00A4H, 0x0404000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00210000U);

                        WR1_PROG(REG_00B4H, 0x00280069U);
                        WR1_PROG(REG_00B8H, 0x00190000U);

                        WR1_PROG(REG_00A4H, 0x0404000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00210000U);

                        r_rsip_func100(bswap_32big(0xce46e7e2U), bswap_32big(0x2d4fafbdU), bswap_32big(0x24f61b39U), bswap_32big(0x1c19ceecU));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x00000800U);

                            r_rsip_func101(bswap_32big(0xbd1c27f3U), bswap_32big(0x4cd8af27U), bswap_32big(0x6f3b4d38U), bswap_32big(0x8bac6cc3U));
                        }
                        else
                        {
                            WR1_PROG(REG_0094H, 0x0000b400U);
                            WR1_PROG(REG_0094H, 0x665331ecU);

                            r_rsip_func101(bswap_32big(0x7829b3cdU), bswap_32big(0xfe43204dU), bswap_32big(0xebf44289U), bswap_32big(0x4c97782cU));
                        }
                    }
                }
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x665331ecU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
