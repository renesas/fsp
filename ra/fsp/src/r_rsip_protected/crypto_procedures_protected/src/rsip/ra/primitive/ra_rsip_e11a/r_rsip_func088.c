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
    r_rsip_func100(bswap_32big(0x5c666421U),
                   bswap_32big(0x2963c3ffU),
                   bswap_32big(0x2022d203U),
                   bswap_32big(0x56e80e70U));

    WR1_PROG(REG_00A0H, 0x20010000U);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xd42563ccU),
                   bswap_32big(0xb931ecaeU),
                   bswap_32big(0x63bd533dU),
                   bswap_32big(0x1c8137aeU));
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

    r_rsip_func100(bswap_32big(0xa2ade092U),
                   bswap_32big(0x6b6ebe7cU),
                   bswap_32big(0xfafa73aeU),
                   bswap_32big(0x85140ce0U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x79195a13U), bswap_32big(0xd82dbf23U), bswap_32big(0x63699928U),
                       bswap_32big(0x382528d5U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x74b52af8U), bswap_32big(0x88865dc0U), bswap_32big(0xbbd3fc5aU),
                       bswap_32big(0x31db8acdU));
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

        r_rsip_func100(bswap_32big(0x6253caa4U), bswap_32big(0xd7cd291dU), bswap_32big(0x090bb075U),
                       bswap_32big(0x67ed2452U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xe6154ab4U), bswap_32big(0xd8e4fd8fU), bswap_32big(0x683b6099U),
                           bswap_32big(0xa7198ef5U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xdc0f9f3eU), bswap_32big(0x3583eda5U), bswap_32big(0x34d570f4U),
                           bswap_32big(0x2b4b2747U));
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

            r_rsip_func100(bswap_32big(0x1abd8e32U), bswap_32big(0x71453684U), bswap_32big(0xd2aabc4eU),
                           bswap_32big(0x40211226U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x7276f790U),
                               bswap_32big(0x31fdfe0bU),
                               bswap_32big(0xd4a62998U),
                               bswap_32big(0xd1219e49U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x201a9f11U),
                               bswap_32big(0x20b86454U),
                               bswap_32big(0x14e3bf2aU),
                               bswap_32big(0x9db5b48fU));
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

                r_rsip_func100(bswap_32big(0xe519cee2U),
                               bswap_32big(0xe3f09149U),
                               bswap_32big(0x3f7bc365U),
                               bswap_32big(0x18b4e69bU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0xf5374e2cU),
                                   bswap_32big(0x15b06941U),
                                   bswap_32big(0xf8a7907aU),
                                   bswap_32big(0x5fc4650dU));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xeddf7cedU),
                                   bswap_32big(0x64c33242U),
                                   bswap_32big(0x7e928b60U),
                                   bswap_32big(0xda393332U));
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
                    WR1_PROG(REG_0094H, 0xd71b216bU);

                    r_rsip_func101(bswap_32big(0x1e0e1d4fU),
                                   bswap_32big(0x205fbbffU),
                                   bswap_32big(0xa790208aU),
                                   bswap_32big(0x9be31b75U));
                }
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0xd71b216bU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
