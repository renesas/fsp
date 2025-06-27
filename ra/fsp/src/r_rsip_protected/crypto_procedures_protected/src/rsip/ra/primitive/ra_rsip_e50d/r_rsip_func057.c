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

void r_rsip_func057 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x08000045U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &ARG1[0]);

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000f057U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x1d9c643fU),
                   bswap_32big(0x51f05ae0U),
                   bswap_32big(0x1a2fbd89U),
                   bswap_32big(0x4a9f277eU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000ffU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x91115787U),
                   bswap_32big(0x3dc4b55cU),
                   bswap_32big(0xcce4258fU),
                   bswap_32big(0x98a1bd5aU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x000034e4U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000feU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x7a34a588U),
                   bswap_32big(0x9f19faddU),
                   bswap_32big(0x105d4e65U),
                   bswap_32big(0x2c6b9c61U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xb45d6191U),
                   bswap_32big(0x69f02425U),
                   bswap_32big(0xcdcf3ff3U),
                   bswap_32big(0xfcd2661cU));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1000H, 0x00010000U);

    r_rsip_func081();

    WR1_PROG(REG_1600H, 0x00007c01U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    oLoop = 0U;
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0xf78b7c3bU), bswap_32big(0x5bf2abb1U), bswap_32big(0x2dd45823U),
                           bswap_32big(0x8b9bebacU));
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0xd900090dU);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG2[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG3[1 + iLoop]);

            r_rsip_func101(bswap_32big(0x8c67d4baU), bswap_32big(0x5dbb6346U), bswap_32big(0x36314530U),
                           bswap_32big(0xe22570ceU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0x3c8e1e9eU), bswap_32big(0x8b587a19U), bswap_32big(0x22480e81U),
                       bswap_32big(0x604ecefeU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        r_rsip_func100(bswap_32big(0xd9e45ba4U), bswap_32big(0x3ee3425fU), bswap_32big(0xda42dcd5U),
                       bswap_32big(0xaa35d3a6U));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func065(0, ARG3);
        r_rsip_func100(bswap_32big(0xb747c814U), bswap_32big(0x21e78d2aU), bswap_32big(0x570dc412U),
                       bswap_32big(0x5b2ccc31U));
        r_rsip_func065(8, ARG3);
        r_rsip_func100(bswap_32big(0xfff15fe9U), bswap_32big(0x4730eb1cU), bswap_32big(0xac182b22U),
                       bswap_32big(0xf6f9539bU));
        r_rsip_func065(16, ARG3);
        r_rsip_func100(bswap_32big(0x63681694U), bswap_32big(0x2cd6435cU), bswap_32big(0x26d97b23U),
                       bswap_32big(0x73d8a97aU));
        r_rsip_func065(24, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func100(bswap_32big(0x405e106eU), bswap_32big(0x287e9cefU), bswap_32big(0x1189f507U),
                       bswap_32big(0x9e9ff40aU));
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);
        oLoop = oLoop + 4;

        WAIT_STS(REG_1A28H, 6, 0);

        r_rsip_func101(bswap_32big(0x36b59a3bU), bswap_32big(0x55dcbb6eU), bswap_32big(0x39143f0dU),
                       bswap_32big(0x171df73cU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        r_rsip_func100(bswap_32big(0x9690cf2cU), bswap_32big(0x7bce5c8fU), bswap_32big(0xccb52088U),
                       bswap_32big(0x835c8d5eU));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func062(0, ARG3);
        r_rsip_func100(bswap_32big(0xf83aee04U), bswap_32big(0x2b223e4dU), bswap_32big(0x5848680cU),
                       bswap_32big(0x1b78422cU));
        r_rsip_func062(8, ARG3);
        r_rsip_func100(bswap_32big(0x124534cfU), bswap_32big(0xe443f2aeU), bswap_32big(0xc81ffa4cU),
                       bswap_32big(0xfcf24872U));
        r_rsip_func062(16, ARG3);
        r_rsip_func100(bswap_32big(0xa2ef1772U), bswap_32big(0xe524a4eaU), bswap_32big(0x7d43abf8U),
                       bswap_32big(0x92f2280fU));
        r_rsip_func062(24, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func100(bswap_32big(0xc44d7458U), bswap_32big(0xc3c8b89eU), bswap_32big(0xf6edcc85U),
                       bswap_32big(0x87a1a2ffU));
        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func061(32, ARG2);
        iLoop = 32 + 32;

        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func062(32, ARG3);
        r_rsip_func100(bswap_32big(0xb03f6da5U), bswap_32big(0x2f58fba3U), bswap_32big(0x9422647eU),
                       bswap_32big(0x1efb85c2U));
        r_rsip_func062(40, ARG3);
        r_rsip_func100(bswap_32big(0x2acb4987U), bswap_32big(0xf5fbd999U), bswap_32big(0x54b43cdeU),
                       bswap_32big(0x495aef0aU));
        r_rsip_func062(48, ARG3);
        r_rsip_func100(bswap_32big(0xcd3086c4U), bswap_32big(0x82afd5cdU), bswap_32big(0xd99519e1U),
                       bswap_32big(0x4afbc043U));
        r_rsip_func062(56, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func101(bswap_32big(0xf0420fadU), bswap_32big(0xd2e744eaU), bswap_32big(0xf7e14ea2U),
                       bswap_32big(0xd5f37807U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        r_rsip_func100(bswap_32big(0x28e8224fU), bswap_32big(0x63d20dfdU), bswap_32big(0x5bdef589U),
                       bswap_32big(0xf86b2b83U));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func065(0, ARG3);
        r_rsip_func100(bswap_32big(0x97c2b947U), bswap_32big(0x484f0b12U), bswap_32big(0x97a74178U),
                       bswap_32big(0x22faac60U));
        r_rsip_func065(8, ARG3);
        r_rsip_func100(bswap_32big(0x5a8bcdd1U), bswap_32big(0x8a0e585dU), bswap_32big(0xaf0c9d37U),
                       bswap_32big(0x6365655cU));
        r_rsip_func065(16, ARG3);
        r_rsip_func100(bswap_32big(0x186833fbU), bswap_32big(0xa8bf2705U), bswap_32big(0x813b7c1aU),
                       bswap_32big(0x60a1ee73U));
        r_rsip_func065(24, ARG3);
        r_rsip_func100(bswap_32big(0xf315072aU), bswap_32big(0x8300d795U), bswap_32big(0xe9258088U),
                       bswap_32big(0x05c8fb87U));
        r_rsip_func065(32, ARG3);
        r_rsip_func100(bswap_32big(0x6c359d20U), bswap_32big(0x92180d08U), bswap_32big(0x560dc733U),
                       bswap_32big(0x793a44f6U));
        r_rsip_func065(40, ARG3);
        r_rsip_func100(bswap_32big(0xd5fcd702U), bswap_32big(0x79e33f9aU), bswap_32big(0xbc282de2U),
                       bswap_32big(0x90183566U));
        r_rsip_func065(48, ARG3);
        r_rsip_func100(bswap_32big(0x7a92f74aU), bswap_32big(0x52470de2U), bswap_32big(0x50d493bbU),
                       bswap_32big(0x03e04151U));
        r_rsip_func065(56, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func100(bswap_32big(0xd11d182bU), bswap_32big(0xb071b621U), bswap_32big(0xa8f29e62U),
                       bswap_32big(0x7ab7d5e2U));
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);
        oLoop = oLoop + 4;

        WAIT_STS(REG_1A28H, 6, 0);

        r_rsip_func101(bswap_32big(0xac19009bU), bswap_32big(0xf87b8294U), bswap_32big(0x50d45fe1U),
                       bswap_32big(0xec9f2329U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        r_rsip_func100(bswap_32big(0xad6e80b8U), bswap_32big(0x0fa2d1bfU), bswap_32big(0xe445bb5aU),
                       bswap_32big(0xb1c7d229U));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func062(0, ARG3);
        r_rsip_func100(bswap_32big(0xdab49857U), bswap_32big(0x7718798fU), bswap_32big(0xe14af5e9U),
                       bswap_32big(0x8a3d02e9U));
        r_rsip_func062(8, ARG3);
        r_rsip_func100(bswap_32big(0x027d9eb3U), bswap_32big(0xb4bfad26U), bswap_32big(0xa58cff45U),
                       bswap_32big(0x939ac84cU));
        r_rsip_func062(16, ARG3);
        r_rsip_func100(bswap_32big(0xbbfaf311U), bswap_32big(0x92ee6a2fU), bswap_32big(0xe3d82256U),
                       bswap_32big(0x8ecfbaa9U));
        r_rsip_func062(24, ARG3);
        r_rsip_func100(bswap_32big(0x2021b03cU), bswap_32big(0x195766e1U), bswap_32big(0x88c6535dU),
                       bswap_32big(0x5ec43fd9U));
        r_rsip_func062(32, ARG3);
        r_rsip_func100(bswap_32big(0x4788bc1aU), bswap_32big(0x580f048dU), bswap_32big(0x7f3d5b5fU),
                       bswap_32big(0xaebe64c4U));
        r_rsip_func062(40, ARG3);
        r_rsip_func100(bswap_32big(0x97959b92U), bswap_32big(0x2f308f5aU), bswap_32big(0x4b48d814U),
                       bswap_32big(0xda49080aU));
        r_rsip_func062(48, ARG3);
        r_rsip_func100(bswap_32big(0x790137f4U), bswap_32big(0xdf8fdb4aU), bswap_32big(0x72d57a72U),
                       bswap_32big(0x6f3a69c8U));
        r_rsip_func062(56, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func100(bswap_32big(0x01dc96e0U), bswap_32big(0x063094d5U), bswap_32big(0x28d2a8a9U),
                       bswap_32big(0xf82bf24aU));
        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func063(64, ARG2);
        iLoop = 64 + 64;

        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func062(64, ARG3);
        r_rsip_func100(bswap_32big(0x8ea0e088U), bswap_32big(0x90b980c7U), bswap_32big(0x1a00697fU),
                       bswap_32big(0x04d70a97U));
        r_rsip_func062(72, ARG3);
        r_rsip_func100(bswap_32big(0x0b7474afU), bswap_32big(0x6bd14713U), bswap_32big(0x1bc8ba7eU),
                       bswap_32big(0xb140ac37U));
        r_rsip_func062(80, ARG3);
        r_rsip_func100(bswap_32big(0xb5482b2cU), bswap_32big(0x684ae3bdU), bswap_32big(0xb09e4fdcU),
                       bswap_32big(0xb24eb9ebU));
        r_rsip_func062(88, ARG3);
        r_rsip_func100(bswap_32big(0x78d066eaU), bswap_32big(0xe71d7d67U), bswap_32big(0xd8af340eU),
                       bswap_32big(0xf32bb617U));
        r_rsip_func062(96, ARG3);
        r_rsip_func100(bswap_32big(0xa8de069cU), bswap_32big(0x4e9fc512U), bswap_32big(0x541b99fbU),
                       bswap_32big(0x38eb7b59U));
        r_rsip_func062(104, ARG3);
        r_rsip_func100(bswap_32big(0x27dc1b25U), bswap_32big(0xb4705dd3U), bswap_32big(0x29f7e483U),
                       bswap_32big(0x144a2fb5U));
        r_rsip_func062(112, ARG3);
        r_rsip_func100(bswap_32big(0x2496bcafU), bswap_32big(0xab036e21U), bswap_32big(0xd3b37848U),
                       bswap_32big(0x05d61913U));
        r_rsip_func062(120, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func101(bswap_32big(0x8ecd93f9U), bswap_32big(0x41535173U), bswap_32big(0xc416675cU),
                       bswap_32big(0xa0b1103fU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0x23f19a7dU), bswap_32big(0x9609f129U), bswap_32big(0x6313ecacU),
                           bswap_32big(0xc36ca68eU));
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0xd900090dU);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG2[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8008105U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG3[1 + iLoop]);

            r_rsip_func101(bswap_32big(0x2fbfac41U), bswap_32big(0xb085fcd4U), bswap_32big(0xdac79525U),
                           bswap_32big(0x3ef0d443U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0xf9029aadU), bswap_32big(0xdb469de3U), bswap_32big(0x5ade0f46U),
                       bswap_32big(0x6ba8e912U));
    }

    r_rsip_func100(bswap_32big(0x1f9e302aU),
                   bswap_32big(0x1d48214dU),
                   bswap_32big(0xb463381dU),
                   bswap_32big(0x32afbb34U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x0900090dU);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &ARG2[iLoop]);

    WR1_PROG(REG_1824H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00007c1cU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
