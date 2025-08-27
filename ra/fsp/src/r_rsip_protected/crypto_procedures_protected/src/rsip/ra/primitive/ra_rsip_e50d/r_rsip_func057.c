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

    r_rsip_func101(bswap_32big(0x05928519U),
                   bswap_32big(0x20094bedU),
                   bswap_32big(0x9dd3a61dU),
                   bswap_32big(0x5a94f15eU));
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
    WR1_PROG(REG_1420H, bswap_32big(0x0000f057U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x047b8036U),
                   bswap_32big(0x7c5e5c6bU),
                   bswap_32big(0x832415beU),
                   bswap_32big(0xed194874U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x000034e4U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000f057U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xa01f135eU),
                   bswap_32big(0x12c1c002U),
                   bswap_32big(0x0b85c594U),
                   bswap_32big(0xb65d0f93U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xd2608f9eU),
                   bswap_32big(0x4886fa97U),
                   bswap_32big(0x55af3a4fU),
                   bswap_32big(0xd9491aa7U));

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
            r_rsip_func100(bswap_32big(0xbf80b81dU), bswap_32big(0xb49dc26bU), bswap_32big(0x1c9ffc1dU),
                           bswap_32big(0x75b6f2c3U));
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

            r_rsip_func101(bswap_32big(0xda21911eU), bswap_32big(0xf50d2c16U), bswap_32big(0xb00b6635U),
                           bswap_32big(0x79d708b3U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0x9cfede43U), bswap_32big(0x8ac80985U), bswap_32big(0xeef73c0fU),
                       bswap_32big(0x3901dda8U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        r_rsip_func100(bswap_32big(0x150572b9U), bswap_32big(0x48f45375U), bswap_32big(0xc194bd6bU),
                       bswap_32big(0xe6db849dU));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func065(0, ARG3);
        r_rsip_func100(bswap_32big(0x398ab511U), bswap_32big(0x602d4166U), bswap_32big(0x68ead4bbU),
                       bswap_32big(0x0fc4a985U));
        r_rsip_func065(8, ARG3);
        r_rsip_func100(bswap_32big(0x6e591599U), bswap_32big(0x0d2dd6b9U), bswap_32big(0x9276a780U),
                       bswap_32big(0xbcaf7878U));
        r_rsip_func065(16, ARG3);
        r_rsip_func100(bswap_32big(0x46346c99U), bswap_32big(0xc60cb693U), bswap_32big(0x1ff45009U),
                       bswap_32big(0xae407f66U));
        r_rsip_func065(24, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func100(bswap_32big(0xed57b357U), bswap_32big(0xd33820b2U), bswap_32big(0x5bf191e9U),
                       bswap_32big(0x315b7b7cU));
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

        r_rsip_func101(bswap_32big(0xa1fe1c1fU), bswap_32big(0x2100b6adU), bswap_32big(0xc87ff293U),
                       bswap_32big(0x061b72c1U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        r_rsip_func100(bswap_32big(0x8c70ed9eU), bswap_32big(0xf42dddfbU), bswap_32big(0xe495fbe3U),
                       bswap_32big(0xc971da9fU));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func061(0, ARG2);
        iLoop = 0 + 32;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func062(0, ARG3);
        r_rsip_func100(bswap_32big(0xc9641802U), bswap_32big(0x00ac89a1U), bswap_32big(0xb9a8ec70U),
                       bswap_32big(0xda145a34U));
        r_rsip_func062(8, ARG3);
        r_rsip_func100(bswap_32big(0x9aba046dU), bswap_32big(0x9d2a8436U), bswap_32big(0x0bf507eaU),
                       bswap_32big(0xb3e81cbaU));
        r_rsip_func062(16, ARG3);
        r_rsip_func100(bswap_32big(0x61fdb98fU), bswap_32big(0x506eef14U), bswap_32big(0x184c21e9U),
                       bswap_32big(0xb75e2015U));
        r_rsip_func062(24, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func100(bswap_32big(0xc801a945U), bswap_32big(0x3cc840f6U), bswap_32big(0xd48af6baU),
                       bswap_32big(0x33a62bd9U));
        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func061(32, ARG2);
        iLoop = 32 + 32;

        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func062(32, ARG3);
        r_rsip_func100(bswap_32big(0xe05c8e3aU), bswap_32big(0x6a68d6d8U), bswap_32big(0x64ca9c9eU),
                       bswap_32big(0x70a6e4b4U));
        r_rsip_func062(40, ARG3);
        r_rsip_func100(bswap_32big(0x9bdc7900U), bswap_32big(0xb9deedf1U), bswap_32big(0xcc0b3be2U),
                       bswap_32big(0xeffe3cedU));
        r_rsip_func062(48, ARG3);
        r_rsip_func100(bswap_32big(0xf6b7af28U), bswap_32big(0x70655a28U), bswap_32big(0x9128575eU),
                       bswap_32big(0x0922e1d1U));
        r_rsip_func062(56, ARG3);
        oLoop = oLoop + 32;

        r_rsip_func101(bswap_32big(0xd7efec02U), bswap_32big(0x841e87dbU), bswap_32big(0x06202a19U),
                       bswap_32big(0x37b43f49U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        r_rsip_func100(bswap_32big(0x47de726cU), bswap_32big(0xa6dee9b2U), bswap_32big(0x72b063a1U),
                       bswap_32big(0x95a259eeU));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func065(0, ARG3);
        r_rsip_func100(bswap_32big(0xba068bdbU), bswap_32big(0x66a84f79U), bswap_32big(0xf8b0e95eU),
                       bswap_32big(0xcedfd98aU));
        r_rsip_func065(8, ARG3);
        r_rsip_func100(bswap_32big(0x15e48f0eU), bswap_32big(0x42c76939U), bswap_32big(0x10c79334U),
                       bswap_32big(0x3b815ba2U));
        r_rsip_func065(16, ARG3);
        r_rsip_func100(bswap_32big(0xda54e7e5U), bswap_32big(0x2849139fU), bswap_32big(0x78b77f18U),
                       bswap_32big(0xc00cc35dU));
        r_rsip_func065(24, ARG3);
        r_rsip_func100(bswap_32big(0xfe669854U), bswap_32big(0x71a50a49U), bswap_32big(0x98344956U),
                       bswap_32big(0xd67ad222U));
        r_rsip_func065(32, ARG3);
        r_rsip_func100(bswap_32big(0x4935e3c9U), bswap_32big(0xb0f822eaU), bswap_32big(0x74035f4bU),
                       bswap_32big(0xb3d43a33U));
        r_rsip_func065(40, ARG3);
        r_rsip_func100(bswap_32big(0x6455554aU), bswap_32big(0x47190422U), bswap_32big(0x26321c11U),
                       bswap_32big(0x79fcabdfU));
        r_rsip_func065(48, ARG3);
        r_rsip_func100(bswap_32big(0xa7a96803U), bswap_32big(0x4aefbbabU), bswap_32big(0xbd210542U),
                       bswap_32big(0x471f1e80U));
        r_rsip_func065(56, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func100(bswap_32big(0x1e4c69cbU), bswap_32big(0xc3e7a4afU), bswap_32big(0x929cbd10U),
                       bswap_32big(0xb26d656eU));
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

        r_rsip_func101(bswap_32big(0x671e2dceU), bswap_32big(0xac551ddbU), bswap_32big(0xd9896b23U),
                       bswap_32big(0x818b22a6U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        r_rsip_func100(bswap_32big(0xed7f8e1eU), bswap_32big(0x24435c5fU), bswap_32big(0x59b7f50aU),
                       bswap_32big(0x39af12e5U));
        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func063(0, ARG2);
        iLoop = 0 + 64;

        WR1_PROG(REG_1404H, 0x10000000U);
        r_rsip_func062(0, ARG3);
        r_rsip_func100(bswap_32big(0x6dd8b3bcU), bswap_32big(0x3372df63U), bswap_32big(0xc8973630U),
                       bswap_32big(0x0b17f7a0U));
        r_rsip_func062(8, ARG3);
        r_rsip_func100(bswap_32big(0x81a93426U), bswap_32big(0xd39e0dacU), bswap_32big(0x5bd00fa6U),
                       bswap_32big(0x3123e53fU));
        r_rsip_func062(16, ARG3);
        r_rsip_func100(bswap_32big(0xb8559b20U), bswap_32big(0x20f50a96U), bswap_32big(0x7992234aU),
                       bswap_32big(0x79a04fa6U));
        r_rsip_func062(24, ARG3);
        r_rsip_func100(bswap_32big(0x14e7cd11U), bswap_32big(0x2e9ac7d2U), bswap_32big(0x323a8b34U),
                       bswap_32big(0x74e36f3fU));
        r_rsip_func062(32, ARG3);
        r_rsip_func100(bswap_32big(0x7d025c31U), bswap_32big(0x2cc01853U), bswap_32big(0x86654d27U),
                       bswap_32big(0x84cd49e2U));
        r_rsip_func062(40, ARG3);
        r_rsip_func100(bswap_32big(0xcd040c39U), bswap_32big(0x8d5def42U), bswap_32big(0x3c48b5deU),
                       bswap_32big(0x9ad1f2c7U));
        r_rsip_func062(48, ARG3);
        r_rsip_func100(bswap_32big(0x6e293d03U), bswap_32big(0xc9e5f72dU), bswap_32big(0x9d5c526eU),
                       bswap_32big(0x9ce44f62U));
        r_rsip_func062(56, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func100(bswap_32big(0x2befc839U), bswap_32big(0x1a798025U), bswap_32big(0x13f9e14bU),
                       bswap_32big(0x6527a540U));
        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func063(64, ARG2);
        iLoop = 64 + 64;

        WR1_PROG(REG_1404H, 0x11100000U);
        r_rsip_func062(64, ARG3);
        r_rsip_func100(bswap_32big(0x50cd8871U), bswap_32big(0x3e593c23U), bswap_32big(0x8757cb46U),
                       bswap_32big(0x10f26ffcU));
        r_rsip_func062(72, ARG3);
        r_rsip_func100(bswap_32big(0x6db0f5c7U), bswap_32big(0x4a247f08U), bswap_32big(0x0a8ebedfU),
                       bswap_32big(0x6ce6f427U));
        r_rsip_func062(80, ARG3);
        r_rsip_func100(bswap_32big(0xb06632edU), bswap_32big(0x4a2cf9d7U), bswap_32big(0x143a529aU),
                       bswap_32big(0x883f3c9aU));
        r_rsip_func062(88, ARG3);
        r_rsip_func100(bswap_32big(0x34bca1f3U), bswap_32big(0x77f3d10eU), bswap_32big(0x06274830U),
                       bswap_32big(0x727c36f2U));
        r_rsip_func062(96, ARG3);
        r_rsip_func100(bswap_32big(0xde18381dU), bswap_32big(0xf43f501aU), bswap_32big(0x96fa69aaU),
                       bswap_32big(0xa30bf1d2U));
        r_rsip_func062(104, ARG3);
        r_rsip_func100(bswap_32big(0x67f08f76U), bswap_32big(0xb0287bc7U), bswap_32big(0x7eb6f3d5U),
                       bswap_32big(0x6fb4767eU));
        r_rsip_func062(112, ARG3);
        r_rsip_func100(bswap_32big(0x5ff06c0dU), bswap_32big(0x563e6f81U), bswap_32big(0x24d5b9eeU),
                       bswap_32big(0x5a074decU));
        r_rsip_func062(120, ARG3);
        oLoop = oLoop + 64;

        r_rsip_func101(bswap_32big(0x46ab8325U), bswap_32big(0x9c01dad2U), bswap_32big(0x2532aa6bU),
                       bswap_32big(0x103d03c1U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0xc06a8edcU), bswap_32big(0x81a935f4U), bswap_32big(0x884cf091U),
                           bswap_32big(0xd567a945U));
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

            r_rsip_func101(bswap_32big(0x1b5d88f7U), bswap_32big(0x5828431fU), bswap_32big(0xfbebfa48U),
                           bswap_32big(0xfb980a41U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0x1120c04fU), bswap_32big(0xd488e3feU), bswap_32big(0x07be0ab5U),
                       bswap_32big(0xd3f7d314U));
    }

    r_rsip_func100(bswap_32big(0xf0352fcbU),
                   bswap_32big(0xe5efed4fU),
                   bswap_32big(0x35a3d684U),
                   bswap_32big(0x51b209baU));
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
