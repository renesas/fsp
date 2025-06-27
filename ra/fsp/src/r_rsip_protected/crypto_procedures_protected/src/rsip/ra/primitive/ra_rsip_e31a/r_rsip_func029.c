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

void r_rsip_func029 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    r_rsip_func027(ARG1);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_00B8H, 0x0000000eU);

    WR1_PROG(REG_00A4H, 0x06060010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B0H, 0x0000942aU);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B4H, 0x002a000eU);
    WR1_PROG(REG_00B8H, 0x001c0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0093001cU);
    WR1_PROG(REG_00B8H, 0x00230000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x002a0093U);
    WR1_PROG(REG_00B8H, 0x00230000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);
    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x009a001cU);
    WR1_PROG(REG_00B8H, 0x00230000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    WR1_PROG(REG_00B4H, 0x002a009aU);
    WR1_PROG(REG_00B8H, 0x00230000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func100(bswap_32big(0x1c9cd66aU),
                   bswap_32big(0x6c0686dcU),
                   bswap_32big(0x227f68afU),
                   bswap_32big(0x9a49da99U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x8e7f2421U), bswap_32big(0x6ad18893U), bswap_32big(0x1d9f9f25U),
                       bswap_32big(0xc38d01d1U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x5fba907bU), bswap_32big(0x8e56b274U), bswap_32big(0xd1bd2dbfU),
                       bswap_32big(0xe7af088cU));

        WR1_PROG(REG_00B4H, 0x002a001cU);
        WR1_PROG(REG_00B8H, 0x00230000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0023009aU);
        WR1_PROG(REG_00B8H, 0x0015000eU);

        WR1_PROG(REG_00A4H, 0x06060000U);
        WR1_PROG(REG_0008H, 0x00020000U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        WR1_PROG(REG_00B4H, 0x007e0015U);
        WR1_PROG(REG_00B8H, 0x001c000eU);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x00009431U);
        WR1_PROG(REG_0000H, 0x00c00031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x003100a1U);
        WR1_PROG(REG_00B8H, 0x00150000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x001c0015U);
        WR1_PROG(REG_00B8H, 0x0015000eU);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x001c0093U);
        WR1_PROG(REG_00B8H, 0x0046000eU);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B8H, 0x00000007U);

        WR1_PROG(REG_00A4H, 0x06060010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00310093U);
        WR1_PROG(REG_00B8H, 0x000e0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x004d00a7U);
        WR1_PROG(REG_00B8H, 0x00690007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x004d00adU);
        WR1_PROG(REG_00B8H, 0x00700007U);

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
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x001c004dU);
        WR1_PROG(REG_00B8H, 0x00770007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00310085U);
        WR1_PROG(REG_00B8H, 0x00380000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00310007U);
        WR1_PROG(REG_00B8H, 0x003f0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000041dU);
        WR1_PROG(REG_0000H, 0x00c00009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000424U);
        WR1_PROG(REG_0000H, 0x00c00009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        r_rsip_func028(ARG1);

        WR1_PROG(REG_00B4H, 0x00310023U);
        WR1_PROG(REG_00B8H, 0x007e0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0031002aU);
        WR1_PROG(REG_00B8H, 0x00850000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00310077U);
        WR1_PROG(REG_00B8H, 0x008c0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0069007eU);
        WR1_PROG(REG_00B8H, 0x001c0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x007e0069U);
        WR1_PROG(REG_00B8H, 0x001c0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x00700085U);
        WR1_PROG(REG_00B8H, 0x001c0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x00850070U);
        WR1_PROG(REG_00B8H, 0x001c0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x48479999U), bswap_32big(0x10fe0d30U), bswap_32big(0xb3f6f38eU),
                       bswap_32big(0xf9ba9f81U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_00B4H, 0x0077008cU);
            WR1_PROG(REG_00B8H, 0x00a10007U);

            WR1_PROG(REG_00A4H, 0x06060013U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0x059b1185U), bswap_32big(0xba56f272U), bswap_32big(0x33af6f5dU),
                           bswap_32big(0xcbe66441U));
        }
        else
        {
            WR1_PROG(REG_00B4H, 0x0000008cU);
            WR1_PROG(REG_00B8H, 0x00a1003fU);

            WR1_PROG(REG_00A4H, 0x06060014U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0x859c8251U), bswap_32big(0xfe7fdb56U), bswap_32big(0x64897002U),
                           bswap_32big(0xa48c8e30U));
        }

        WR1_PROG(REG_00B4H, 0x00310015U);
        WR1_PROG(REG_00B8H, 0x004d0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00230023U);
        WR1_PROG(REG_00B8H, 0x00230000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x002a002aU);
        WR1_PROG(REG_00B8H, 0x002a0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00310031U);
        WR1_PROG(REG_00B8H, 0x00310000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00000800U);
        for (iLoop = 0U; iLoop < 3U; iLoop++)
        {
            r_rsip_func100(bswap_32big(0xa7a8cb90U), bswap_32big(0x895fa2c6U), bswap_32big(0xb7c2d34dU),
                           bswap_32big(0x4b5f143aU));
            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x00007c00U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_00B0H, 0x00000848U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000849U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000841U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x357bdc1bU),
                               bswap_32big(0x02a7d11aU),
                               bswap_32big(0xd882cc36U),
                               bswap_32big(0x8fc37427U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_00B0H, 0x0000084aU);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x0000084bU);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000843U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000844U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xfc5cc89bU),
                               bswap_32big(0x20bee20eU),
                               bswap_32big(0x8e6bc75eU),
                               bswap_32big(0xe2821838U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
            {
                WR1_PROG(REG_00B0H, 0x0000084cU);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x0000084dU);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000845U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_00B0H, 0x00000846U);
                WR1_PROG(REG_009CH, 0x80820005U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xae28d97dU),
                               bswap_32big(0xb59bddd6U),
                               bswap_32big(0x09386c63U),
                               bswap_32big(0xeba677c4U));
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

                    WR1_PROG(REG_00B0H, 0x0000941cU);
                    WR1_PROG(REG_0000H, 0x00c0002dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                    WR1_PROG(REG_00B4H, 0x001c0023U);
                    WR1_PROG(REG_00B8H, 0x00150000U);

                    WR1_PROG(REG_00A4H, 0x0606000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    WR1_PROG(REG_00B4H, 0x001c0031U);
                    WR1_PROG(REG_00B8H, 0x00150000U);

                    WR1_PROG(REG_00A4H, 0x0606000aU);
                    WR1_PROG(REG_00A0H, 0x20010001U);
                    WAIT_STS(REG_00A8H, 0, 1);
                    WR1_PROG(REG_00ACH, 0x00000001U);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0xb1340d49U),
                                   bswap_32big(0xc14f9913U),
                                   bswap_32big(0x38eae8bfU),
                                   bswap_32big(0x7d5d1ba8U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B4H, 0x00000031U);
                        WR1_PROG(REG_00B8H, 0x0031003fU);

                        WR1_PROG(REG_00A4H, 0x06060014U);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);
                        WR1_PROG(REG_0040H, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0xdba42418U),
                                       bswap_32big(0x5fdc197cU),
                                       bswap_32big(0x4aea159aU),
                                       bswap_32big(0xf4f70e6bU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x00c468d8U),
                                       bswap_32big(0x194187caU),
                                       bswap_32big(0xfb4d1db0U),
                                       bswap_32big(0x6ab259d1U));
                    }

                    WR1_PROG(REG_0094H, 0x38000ca5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A70000U);

                    r_rsip_func100(bswap_32big(0x6053e84cU),
                                   bswap_32big(0x804f5a96U),
                                   bswap_32big(0xeda2756eU),
                                   bswap_32big(0x309f2cd1U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x830b05edU),
                                       bswap_32big(0xfb2539cfU),
                                       bswap_32big(0xb76091bfU),
                                       bswap_32big(0x61325be1U));

                        WR1_PROG(REG_00B0H, 0x0000941cU);
                        WR1_PROG(REG_0000H, 0x00c00031U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x00007c05U);
                        WR1_PROG(REG_0040H, 0x00600000U);

                        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                        {
                            WR1_PROG(REG_00B4H, 0x001c0069U);
                            WR1_PROG(REG_00B8H, 0x00540000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c0070U);
                            WR1_PROG(REG_00B8H, 0x005b0000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c0077U);
                            WR1_PROG(REG_00B8H, 0x00620000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0x40f6d1c7U),
                                           bswap_32big(0x5248f83aU),
                                           bswap_32big(0x0aca5d41U),
                                           bswap_32big(0xaa5bf654U));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                        {
                            WR1_PROG(REG_00B4H, 0x001c007eU);
                            WR1_PROG(REG_00B8H, 0x00540000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c0085U);
                            WR1_PROG(REG_00B8H, 0x005b0000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c008cU);
                            WR1_PROG(REG_00B8H, 0x00620000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0xc83a25e9U),
                                           bswap_32big(0xfc99de22U),
                                           bswap_32big(0x3e05b138U),
                                           bswap_32big(0x9f48c140U));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                        {
                            WR1_PROG(REG_00B4H, 0x001c0093U);
                            WR1_PROG(REG_00B8H, 0x00540000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c009aU);
                            WR1_PROG(REG_00B8H, 0x005b0000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c00a1U);
                            WR1_PROG(REG_00B8H, 0x00620000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0xae850568U),
                                           bswap_32big(0xae6ecedaU),
                                           bswap_32big(0xe17c35e5U),
                                           bswap_32big(0xf5deb148U));
                        }

                        WR1_PROG(REG_00B0H, 0x0000941cU);
                        WR1_PROG(REG_0000H, 0x00c0002dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0014H, 0x000000a5U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                        WR1_PROG(REG_00B4H, 0x001c0023U);
                        WR1_PROG(REG_00B8H, 0x00150000U);

                        WR1_PROG(REG_00A4H, 0x0606000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        WR1_PROG(REG_00B4H, 0x001c0031U);
                        WR1_PROG(REG_00B8H, 0x00150000U);

                        WR1_PROG(REG_00A4H, 0x0606000aU);
                        WR1_PROG(REG_00A0H, 0x20010001U);
                        WAIT_STS(REG_00A8H, 0, 1);
                        WR1_PROG(REG_00ACH, 0x00000001U);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0xfec61ac8U),
                                       bswap_32big(0x791d1f57U),
                                       bswap_32big(0xd424b15cU),
                                       bswap_32big(0x9d4ef2d9U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_00B4H, 0x001c0054U);
                            WR1_PROG(REG_00B8H, 0x00150000U);

                            WR1_PROG(REG_00A4H, 0x0606000aU);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            WR1_PROG(REG_00B4H, 0x001c0062U);
                            WR1_PROG(REG_00B8H, 0x00150000U);

                            WR1_PROG(REG_00A4H, 0x0606000aU);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0xba3a1b1dU),
                                           bswap_32big(0xaf721cb7U),
                                           bswap_32big(0x07f77197U),
                                           bswap_32big(0x7b8c89c5U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_00B4H, 0x00540023U);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x00230054U);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x005b002aU);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x002a005bU);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x00620031U);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                WR1_PROG(REG_00B4H, 0x00310062U);
                                WR1_PROG(REG_00B8H, 0x00150000U);

                                WR1_PROG(REG_00A4H, 0x0606000aU);
                                WR1_PROG(REG_00A0H, 0x20010001U);
                                WAIT_STS(REG_00A8H, 0, 1);
                                WR1_PROG(REG_00ACH, 0x00000001U);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func100(bswap_32big(0x2021f60aU), bswap_32big(0x1ebeb1a2U),
                                               bswap_32big(0x1a07aa53U), bswap_32big(0xc6f79d47U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_00B4H, 0x00620031U);
                                    WR1_PROG(REG_00B8H, 0x00310007U);

                                    WR1_PROG(REG_00A4H, 0x06060013U);
                                    WR1_PROG(REG_00A0H, 0x20010001U);
                                    WAIT_STS(REG_00A8H, 0, 1);
                                    WR1_PROG(REG_00ACH, 0x00000001U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x62b326a7U), bswap_32big(0x25ed0afcU),
                                                   bswap_32big(0x82e367e5U), bswap_32big(0xc8fd333cU));
                                }
                                else
                                {
                                    WR1_PROG(REG_00B4H, 0x00000031U);
                                    WR1_PROG(REG_00B8H, 0x0031003fU);

                                    WR1_PROG(REG_00A4H, 0x06060014U);
                                    WR1_PROG(REG_00A0H, 0x20010001U);
                                    WAIT_STS(REG_00A8H, 0, 1);
                                    WR1_PROG(REG_00ACH, 0x00000001U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xd24a2374U), bswap_32big(0x06cee0d3U),
                                                   bswap_32big(0x47eff067U), bswap_32big(0xabb08c1eU));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0xbc5b0905U), bswap_32big(0xd8f18706U),
                                               bswap_32big(0x1f48e8c5U), bswap_32big(0x652bd716U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_00B0H, 0x0000941cU);
                            WR1_PROG(REG_0000H, 0x00c00031U);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);

                            WR1_PROG(REG_00B4H, 0x001c0054U);
                            WR1_PROG(REG_00B8H, 0x00230000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c005bU);
                            WR1_PROG(REG_00B8H, 0x002a0000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            WR1_PROG(REG_00B4H, 0x001c0062U);
                            WR1_PROG(REG_00B8H, 0x00310000U);

                            WR1_PROG(REG_00A4H, 0x06060009U);
                            WR1_PROG(REG_00A0H, 0x20010001U);
                            WAIT_STS(REG_00A8H, 0, 1);
                            WR1_PROG(REG_00ACH, 0x00000001U);

                            r_rsip_func101(bswap_32big(0x6bea40b5U),
                                           bswap_32big(0x5d32cc36U),
                                           bswap_32big(0xd064339fU),
                                           bswap_32big(0x20f18b97U));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xff2792c3U),
                                       bswap_32big(0x812a6ef7U),
                                       bswap_32big(0xd033b03bU),
                                       bswap_32big(0x2ef27adaU));
                    }

                    WR1_PROG(REG_0094H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0x4f9fc63eU),
                                   bswap_32big(0x2f82ec8cU),
                                   bswap_32big(0xfe3015acU),
                                   bswap_32big(0x68129f4eU));
                }

                WR1_PROG(REG_0094H, 0x38008840U);
                WR1_PROG(REG_0094H, 0x00000020U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x18d83ee5U),
                               bswap_32big(0x12d8dae2U),
                               bswap_32big(0x7580ebb2U),
                               bswap_32big(0xc8f88c8bU));
            }

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0x00000004U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0094H, 0x00002c00U);

            r_rsip_func101(bswap_32big(0x3d8e7e91U), bswap_32big(0xe3c03935U), bswap_32big(0xfeebbf11U),
                           bswap_32big(0x2ed92729U));
        }

        WR1_PROG(REG_0094H, 0x38008800U);
        WR1_PROG(REG_0094H, 0x00000003U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        WR1_PROG(REG_00B0H, 0x0000941cU);
        WR1_PROG(REG_0000H, 0x00c00031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x001c000eU);
        WR1_PROG(REG_00B8H, 0x00930000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000941cU);
        WR1_PROG(REG_0000H, 0x00c0002dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x001c0031U);
        WR1_PROG(REG_00B8H, 0x003f0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0xfcce7918U), bswap_32big(0x723f11ccU), bswap_32big(0x0c065489U),
                       bswap_32big(0xe4708d2eU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x87f139a6U), bswap_32big(0xd584f906U), bswap_32big(0x89f8b7a4U),
                           bswap_32big(0x0b6bd1efU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xcbf8c725U), bswap_32big(0x35c02352U), bswap_32big(0x811cbd1fU),
                           bswap_32big(0x7c500d8bU));

            WR1_PROG(REG_00B4H, 0x001c0031U);
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

            WR1_PROG(REG_00B4H, 0x00930038U);
            WR1_PROG(REG_00B8H, 0x00230000U);

            WR1_PROG(REG_00A4H, 0x0606000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0040H, 0x00210000U);

            WR1_PROG(REG_00B4H, 0x00380093U);
            WR1_PROG(REG_00B8H, 0x00230000U);

            WR1_PROG(REG_00A4H, 0x0606000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0x90fe9cc9U), bswap_32big(0x2835c704U), bswap_32big(0xef5881aaU),
                           bswap_32big(0x33f71106U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0xd8778b32U),
                               bswap_32big(0x65ecb25cU),
                               bswap_32big(0xc01b8c84U),
                               bswap_32big(0x772ea7a6U));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0xbf434bdeU);

                r_rsip_func101(bswap_32big(0xe1ec7e83U),
                               bswap_32big(0x86bdd3efU),
                               bswap_32big(0x344509abU),
                               bswap_32big(0xd820076bU));
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0xbf434bdeU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
