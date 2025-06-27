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

void r_rsip_func073 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

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

    r_rsip_func100(bswap_32big(0xe4799c35U),
                   bswap_32big(0xd1908904U),
                   bswap_32big(0x9aa829f3U),
                   bswap_32big(0x0854254eU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x6d1308c3U), bswap_32big(0x4aea4cb8U), bswap_32big(0xa09420a1U),
                       bswap_32big(0x1180f75eU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x2e28b8e1U), bswap_32big(0xfd407768U), bswap_32big(0x98e2e591U),
                       bswap_32big(0xae0b992aU));

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

        WR1_PROG(REG_00B4H, 0x0023007eU);
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

        WR1_PROG(REG_00B4H, 0x00230069U);
        WR1_PROG(REG_00B8H, 0x000a0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00370076U);
        WR1_PROG(REG_00B8H, 0x004b0005U);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0037007aU);
        WR1_PROG(REG_00B8H, 0x00500005U);

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
        WR1_PROG(REG_00B8H, 0x00550005U);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0023005fU);
        WR1_PROG(REG_00B8H, 0x00280000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00230005U);
        WR1_PROG(REG_00B8H, 0x002d0000U);

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

        WR1_PROG(REG_00B4H, 0x00230019U);
        WR1_PROG(REG_00B8H, 0x005a0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0023001eU);
        WR1_PROG(REG_00B8H, 0x005f0000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00230055U);
        WR1_PROG(REG_00B8H, 0x00640000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000046fU);
        WR1_PROG(REG_0000H, 0x00c00009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x004b005aU);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x005a004bU);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x0050005fU);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x005f0050U);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x72552dbeU), bswap_32big(0xa0b5d9b1U), bswap_32big(0x9f03ecfeU),
                       bswap_32big(0xde061076U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_00B4H, 0x00550064U);
            WR1_PROG(REG_00B8H, 0x00730005U);

            WR1_PROG(REG_00A4H, 0x04040013U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0xa75674f8U), bswap_32big(0x559f161dU), bswap_32big(0xb5989385U),
                           bswap_32big(0x356621dbU));
        }
        else
        {
            WR1_PROG(REG_00B4H, 0x00000064U);
            WR1_PROG(REG_00B8H, 0x0073002dU);

            WR1_PROG(REG_00A4H, 0x04040014U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0xe757df62U), bswap_32big(0x0ddb49d9U), bswap_32big(0x70e52916U),
                           bswap_32big(0x1852d2dfU));
        }

        WR1_PROG(REG_00B4H, 0x0023000fU);
        WR1_PROG(REG_00B8H, 0x00370000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00190019U);
        WR1_PROG(REG_00B8H, 0x00190000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x001e001eU);
        WR1_PROG(REG_00B8H, 0x001e0000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00230023U);
        WR1_PROG(REG_00B8H, 0x00230000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00000800U);
        for (iLoop = 0U; iLoop < 2U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            r_rsip_func100(bswap_32big(0x3a05bea8U), bswap_32big(0x768d99b3U), bswap_32big(0x720acd1eU),
                           bswap_32big(0x2dd1efe2U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_00B0H, 0x00000834U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000835U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x0000082fU);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000830U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xd7b36b3fU),
                               bswap_32big(0x56a8eb98U),
                               bswap_32big(0xcd9e01bbU),
                               bswap_32big(0xb68e57bdU));
            }
            else
            {
                WR1_PROG(REG_00B0H, 0x00000836U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000837U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000831U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000832U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xe90e8014U),
                               bswap_32big(0xbc68f990U),
                               bswap_32big(0x0d597c9bU),
                               bswap_32big(0x604d1b6dU));
            }

            WR1_PROG(REG_0094H, 0x00000821U);

            for (jLoop = 0U; jLoop < 4; jLoop++)
            {
                WR1_PROG(REG_0094H, 0x000034a1U);

                WR1_PROG(REG_0094H, 0x00026ca5U);

                WR1_PROG(REG_0094H, 0x00003865U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000010U);

                WR1_PROG(REG_0094H, 0x00003885U);

                WR1_PROG(REG_0094H, 0x00000842U);

                for (kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    WR1_PROG(REG_0094H, 0x000008a5U);

                    WR1_PROG(REG_0094H, 0x01816ca3U);
                    WR1_PROG(REG_0094H, 0x01816ca4U);
                    WR1_PROG(REG_0094H, 0x00016c63U);
                    WR1_PROG(REG_0094H, 0x00016c84U);

                    WR1_PROG(REG_00B0H, 0x00001414U);
                    WR1_PROG(REG_0000H, 0x00c0001dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                    WR1_PROG(REG_00B4H, 0x00140019U);
                    WR1_PROG(REG_00B8H, 0x000f0000U);

                    WR1_PROG(REG_00A4H, 0x0404000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    WR1_PROG(REG_00B4H, 0x00140023U);
                    WR1_PROG(REG_00B8H, 0x000f0000U);

                    WR1_PROG(REG_00A4H, 0x0404000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x7b46f476U),
                                   bswap_32big(0xa47f8404U),
                                   bswap_32big(0x20f8574cU),
                                   bswap_32big(0x2060d2bfU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B4H, 0x00000023U);
                        WR1_PROG(REG_00B8H, 0x0023002dU);

                        WR1_PROG(REG_00A4H, 0x04040014U);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);
                        WR1_PROG(REG_0040H, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0x7ddf3913U),
                                       bswap_32big(0xb15f5ca8U),
                                       bswap_32big(0x4c7def48U),
                                       bswap_32big(0x4e8abd62U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x9e766aa6U),
                                       bswap_32big(0x90f35ebeU),
                                       bswap_32big(0xa9205c65U),
                                       bswap_32big(0xb7c88365U));
                    }

                    WR1_PROG(REG_0094H, 0x38000ca5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A70000U);

                    r_rsip_func100(bswap_32big(0x81a1e390U),
                                   bswap_32big(0xe52817dfU),
                                   bswap_32big(0xc018ac9dU),
                                   bswap_32big(0xef19d160U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x7053f177U),
                                       bswap_32big(0xcb75b0b6U),
                                       bswap_32big(0x153201b9U),
                                       bswap_32big(0x975a4f81U));

                        WR1_PROG(REG_00B0H, 0x00001414U);
                        WR1_PROG(REG_0000H, 0x00c00021U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x00007c05U);
                        WR1_PROG(REG_0040H, 0x00600000U);

                        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                        {
                            WR1_PROG(REG_00B4H, 0x0014004bU);
                            WR1_PROG(REG_00B8H, 0x003c0000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140050U);
                            WR1_PROG(REG_00B8H, 0x00410000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140055U);
                            WR1_PROG(REG_00B8H, 0x00460000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0xa3051ea0U),
                                           bswap_32big(0x29317afdU),
                                           bswap_32big(0x7f31aec0U),
                                           bswap_32big(0xd46c175dU));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                        {
                            WR1_PROG(REG_00B4H, 0x0014005aU);
                            WR1_PROG(REG_00B8H, 0x003c0000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x0014005fU);
                            WR1_PROG(REG_00B8H, 0x00410000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140064U);
                            WR1_PROG(REG_00B8H, 0x00460000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0xa03aed2bU),
                                           bswap_32big(0x4b9c8da6U),
                                           bswap_32big(0x8d7037efU),
                                           bswap_32big(0xae729e27U));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                        {
                            WR1_PROG(REG_00B4H, 0x00140069U);
                            WR1_PROG(REG_00B8H, 0x003c0000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x0014006eU);
                            WR1_PROG(REG_00B8H, 0x00410000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140073U);
                            WR1_PROG(REG_00B8H, 0x00460000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0x8ef7d770U),
                                           bswap_32big(0x44fea75aU),
                                           bswap_32big(0x89b332cdU),
                                           bswap_32big(0x8d31afdeU));
                        }

                        WR1_PROG(REG_00B0H, 0x00001414U);
                        WR1_PROG(REG_0000H, 0x00c0001dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0014H, 0x000000a5U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                        WR1_PROG(REG_00B4H, 0x00140019U);
                        WR1_PROG(REG_00B8H, 0x000f0000U);

                        WR1_PROG(REG_00A4H, 0x0404000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        WR1_PROG(REG_00B4H, 0x00140023U);
                        WR1_PROG(REG_00B8H, 0x000f0000U);

                        WR1_PROG(REG_00A4H, 0x0404000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0xdf2b9ee7U),
                                       bswap_32big(0xca103e5dU),
                                       bswap_32big(0x54f52d59U),
                                       bswap_32big(0x22dcad63U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_00B4H, 0x0014003cU);
                            WR1_PROG(REG_00B8H, 0x000f0000U);

                            WR1_PROG(REG_00A4H, 0x0404000aU);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            WR1_PROG(REG_00B4H, 0x00140046U);
                            WR1_PROG(REG_00B8H, 0x000f0000U);

                            WR1_PROG(REG_00A4H, 0x0404000aU);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0x6703b7c3U),
                                           bswap_32big(0x66dff0bbU),
                                           bswap_32big(0x9a95b2bcU),
                                           bswap_32big(0x2b857d7eU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_00B4H, 0x003c0019U);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x0019003cU);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x0041001eU);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x001e0041U);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x00460023U);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x00230046U);
                                WR1_PROG(REG_00B8H, 0x000f0000U);

                                WR1_PROG(REG_00A4H, 0x0404000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func100(bswap_32big(0xdcb84fa8U), bswap_32big(0xc1c6c3a5U),
                                               bswap_32big(0xff8f5cecU), bswap_32big(0x51db98d0U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_00B4H, 0x00460023U);
                                    WR1_PROG(REG_00B8H, 0x00230005U);

                                    WR1_PROG(REG_00A4H, 0x04040013U);
                                    WR1_PROG(REG_00A0H, 0x20010001U);
                                    WAIT_STS(REG_00A8H, 0, 1);
                                    WR1_PROG(REG_00ACH, 0x00000001U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xb3653215U), bswap_32big(0x855b3026U),
                                                   bswap_32big(0x76e9210cU), bswap_32big(0xcb3d4fe4U));
                                }
                                else
                                {
                                    WR1_PROG(REG_00B4H, 0x00000023U);
                                    WR1_PROG(REG_00B8H, 0x0023002dU);

                                    WR1_PROG(REG_00A4H, 0x04040014U);
                                    WR1_PROG(REG_00A0H, 0x20010001U);
                                    WAIT_STS(REG_00A8H, 0, 1);
                                    WR1_PROG(REG_00ACH, 0x00000001U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x8862eea8U), bswap_32big(0x8872966dU),
                                                   bswap_32big(0x54b90d85U), bswap_32big(0xce984103U));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0xf4eed56eU), bswap_32big(0xda9fb427U),
                                               bswap_32big(0x78a8f046U), bswap_32big(0x4da9fa67U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_00B0H, 0x00001414U);
                            WR1_PROG(REG_0000H, 0x00c00021U);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);

                            WR1_PROG(REG_00B4H, 0x0014003cU);
                            WR1_PROG(REG_00B8H, 0x00190000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140041U);
                            WR1_PROG(REG_00B8H, 0x001e0000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x00140046U);
                            WR1_PROG(REG_00B8H, 0x00230000U);

                            WR1_PROG(REG_00A4H, 0x04040009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0x4a6ec644U),
                                           bswap_32big(0x1b38ba4fU),
                                           bswap_32big(0xe85b31f3U),
                                           bswap_32big(0x563786eeU));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x7407e7bbU),
                                       bswap_32big(0x643c049bU),
                                       bswap_32big(0x3a560941U),
                                       bswap_32big(0x2a3a38c5U));
                    }

                    WR1_PROG(REG_0094H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0x5a459c8dU),
                                   bswap_32big(0x95145248U),
                                   bswap_32big(0x82ce5720U),
                                   bswap_32big(0x089ccbacU));
                }

                WR1_PROG(REG_0094H, 0x38008840U);
                WR1_PROG(REG_0094H, 0x00000020U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x597da616U),
                               bswap_32big(0x0ac41546U),
                               bswap_32big(0x6f108361U),
                               bswap_32big(0xad56a7b5U));
            }

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0x00000004U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0094H, 0x00002c00U);

            r_rsip_func101(bswap_32big(0xfdf186ddU), bswap_32big(0x89debddaU), bswap_32big(0xc7ffe95dU),
                           bswap_32big(0x7cb64360U));
        }

        WR1_PROG(REG_0094H, 0x38008800U);
        WR1_PROG(REG_0094H, 0x00000002U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        WR1_PROG(REG_00B0H, 0x00001414U);
        WR1_PROG(REG_0000H, 0x00c00021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x0014000aU);
        WR1_PROG(REG_00B8H, 0x00690000U);

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
        WR1_PROG(REG_00B8H, 0x002d0000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0xfb1950f8U), bswap_32big(0x541678a1U), bswap_32big(0x125a3700U),
                       bswap_32big(0x48e985d9U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xe9610ddeU), bswap_32big(0x7f04cb63U), bswap_32big(0xa0dfac12U),
                           bswap_32big(0x171f4c2eU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x24f45b8eU), bswap_32big(0x72317c29U), bswap_32big(0xf3e0472aU),
                           bswap_32big(0xf2df13c3U));

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

            r_rsip_func100(bswap_32big(0x678af566U), bswap_32big(0xdebeae10U), bswap_32big(0x3078fa48U),
                           bswap_32big(0x75905acbU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0xd0f56c5cU),
                               bswap_32big(0x923a0f8bU),
                               bswap_32big(0x2da6d99fU),
                               bswap_32big(0x75c5053cU));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0xd8f48c0dU);

                r_rsip_func101(bswap_32big(0x2da902bfU),
                               bswap_32big(0x0a201fe9U),
                               bswap_32big(0x218eba73U),
                               bswap_32big(0x74a9525dU));
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0xd8f48c0dU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
