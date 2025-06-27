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

rsip_ret_t r_rsip_p13 (const uint32_t InData_DomainParam[],
                       uint32_t       OutData_PubKeyIndex[],
                       uint32_t       OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00130001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    r_rsip_func100(bswap_32big(0xb6ac2fc2U),
                   bswap_32big(0x821a6020U),
                   bswap_32big(0x62c94bcaU),
                   bswap_32big(0x94794e29U));
    r_rsip_func086(InData_DomainParam);

    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000000c0U);

    WR1_PROG(REG_1004H, 0x09090010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000070U);

    WR1_PROG(REG_1004H, 0x09090010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x12a00000U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001301U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x1ca981e4U),
                   bswap_32big(0x0e9e03b7U),
                   bswap_32big(0xb620b074U),
                   bswap_32big(0x13706408U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1608H, 0x80020000U);
    WR1_PROG(REG_1400H, 0x03420009U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1600H, 0x00008c20U);
    WR1_PROG(REG_1600H, 0x000001ffU);
    WR1_PROG(REG_1608H, 0x81020000U);
    WR1_PROG(REG_1400H, 0x00c90009U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20009U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001302U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc7f62777U),
                   bswap_32big(0x4b1f4d19U),
                   bswap_32big(0x361a8c01U),
                   bswap_32big(0xdf862c35U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001303U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x361265d6U),
                   bswap_32big(0x3c35b722U),
                   bswap_32big(0xf43c59e8U),
                   bswap_32big(0x285ae06cU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001304U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xdbd1b53eU),
                   bswap_32big(0xe729097dU),
                   bswap_32big(0x8d7cf3f6U),
                   bswap_32big(0x42860c0cU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00001305U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0e952e4bU),
                   bswap_32big(0x1113d3e8U),
                   bswap_32big(0x6b6d180bU),
                   bswap_32big(0x144cf513U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x10c80000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c00045U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x000000c0U);
    WR1_PROG(REG_1018H, 0x00000110U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0909000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x11180000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0003dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c00009U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x000001b0U);
    WR1_PROG(REG_1018H, 0x00000160U);
    WR1_PROG(REG_1020H, 0x00000250U);

    WR1_PROG(REG_1004H, 0x09090007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    r_rsip_func100(bswap_32big(0xfc5c6535U),
                   bswap_32big(0xd323e8e0U),
                   bswap_32big(0xcd942317U),
                   bswap_32big(0xa759c678U));
    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00000863U);

    WR1_PROG(REG_1404H, 0x12000000U);
    WR1_PROG(REG_1608H, 0x80940001U);
    WR1_PROG(REG_1400H, 0x03430051U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    for (iLoop = 0U; iLoop < 20; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x38000c63U);
        WR1_PROG(REG_1600H, 0x20000842U);
        WR1_PROG(REG_1600H, 0x10003841U);

        WR1_PROG(REG_1600H, 0x0000b7c0U);
        WR1_PROG(REG_1600H, 0x0000001fU);

        for (jLoop = 0U; jLoop < 32U; jLoop++)
        {
            WR1_PROG(REG_1600H, 0x3800585eU);
            WR1_PROG(REG_1600H, 0x20003460U);
            WR1_PROG(REG_1600H, 0x20002c60U);
            WR1_PROG(REG_1600H, 0x10002c00U);
            WR1_PROG(REG_1600H, 0x100033c0U);
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a420U);
        WR1_PROG(REG_1600H, 0x00000004U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1404H, 0x14300000U);
    WR1_PROG(REG_1400H, 0x00c00051U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000250U);
    WR1_PROG(REG_1018H, 0x00000480U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0a0a0009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x10c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c0004dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00003403U);

    WR1_PROG(REG_1600H, 0x00003060U);

    WR1_PROG(REG_1608H, 0x81010060U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
    {
        WR1_PROG(REG_1014H, 0x000001b0U);
        WR1_PROG(REG_1018H, 0x00000110U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x0a0a0007U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x00000480U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0a0a0009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1600H, 0x00003060U);

        r_rsip_func101(bswap_32big(0x83812a96U), bswap_32big(0x0baa33a4U), bswap_32big(0xf27f8e5cU),
                       bswap_32big(0x75cb1251U));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00007c03U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1404H, 0x10c00000U);
    WR1_PROG(REG_1400H, 0x00c00051U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xddf18b3eU),
                   bswap_32big(0x70c3a98dU),
                   bswap_32big(0x7359a983U),
                   bswap_32big(0x4232d192U));
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
    {
        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x0a0a000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00a10000U);

        r_rsip_func100(bswap_32big(0x1df0055cU), bswap_32big(0x6681a1bdU), bswap_32big(0xfb539466U),
                       bswap_32big(0x21a8980aU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x0a0a0009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            r_rsip_func101(bswap_32big(0xaa5b620fU), bswap_32big(0x65d7d5d4U), bswap_32big(0xe404733eU),
                           bswap_32big(0xf2370d75U));
        }

        WR1_PROG(REG_1014H, 0x000001b0U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x0a0a000cU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x00000110U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0a0a0009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1600H, 0x00003000U);

        r_rsip_func101(bswap_32big(0x8e418104U), bswap_32big(0xa3929c62U), bswap_32big(0x0e73338bU),
                       bswap_32big(0x8ff9ce61U));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1404H, 0x10c80000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c00045U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x000002f0U);
    WR1_PROG(REG_1018H, 0x00000110U);
    WR1_PROG(REG_1020H, 0x00000340U);

    WR1_PROG(REG_1004H, 0x09090009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    r_rsip_func100(bswap_32big(0xf5c7fa1bU),
                   bswap_32big(0x021ffaedU),
                   bswap_32big(0xabe9f49cU),
                   bswap_32big(0xabe94d96U));

    r_rsip_func087(InData_DomainParam);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000013U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xad832b20U),
                   bswap_32big(0xecee8f67U),
                   bswap_32big(0x14ceea65U),
                   bswap_32big(0xff694c07U));
    r_rsip_func091();

    r_rsip_func100(bswap_32big(0x3efec19eU),
                   bswap_32big(0x738bd53cU),
                   bswap_32big(0xb6a78e5eU),
                   bswap_32big(0xeadd4494U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x8d8dfec1U), bswap_32big(0x1a915238U), bswap_32big(0x5d452ea3U),
                       bswap_32big(0xfbcacb5cU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00001306U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xffe604c9U), bswap_32big(0x9d144d24U), bswap_32big(0x16ed3b7aU),
                       bswap_32big(0xfb6a0aadU));
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
        WR1_PROG(REG_1420H, bswap_32big(0x00000013U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xd46fb35bU), bswap_32big(0xa1fb7631U), bswap_32big(0x3f2dd51cU),
                       bswap_32big(0xc9e33226U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000025U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000013U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x9873b624U), bswap_32big(0x24e56d0aU), bswap_32big(0x1b00b720U),
                       bswap_32big(0x87ad72adU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0x1820a720U), bswap_32big(0x7d084caeU), bswap_32big(0x4d2bf6b9U),
                       bswap_32big(0x4e126983U));
        WR1_PROG(REG_1A2CH, 0x40000200U);
        WR1_PROG(REG_1A24H, 0xe7009d07U);
        WR1_PROG(REG_1404H, 0x12f80000U);
        WR1_PROG(REG_1400H, 0x00800009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00830029U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002032U);
        for (iLoop = 0U; iLoop < 12U; )
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x6152a981U), bswap_32big(0x95a8146bU), bswap_32big(0xecfa4a95U),
                       bswap_32big(0x4d14cbcfU));
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xe7008d07U);
        WR1_PROG(REG_1400H, 0x00830021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[iLoop + 1]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[iLoop + 5]);

        r_rsip_func100(bswap_32big(0x52a7bd0aU), bswap_32big(0x2be5b62bU), bswap_32big(0x7f821862U),
                       bswap_32big(0x4e23fd78U));
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
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[iLoop + 9]);

        r_rsip_func100(bswap_32big(0x03e61202U), bswap_32big(0x0e47778fU), bswap_32big(0xc76af654U),
                       bswap_32big(0xf4e0d488U));
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00001307U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x2f5d7f80U), bswap_32big(0x5c38fa25U), bswap_32big(0x91432a3cU),
                       bswap_32big(0x3d9d361bU));
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
        WR1_PROG(REG_1420H, bswap_32big(0x00000113U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x46d53b0fU), bswap_32big(0xbc13e593U), bswap_32big(0x725d4241U),
                       bswap_32big(0x22524616U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000024U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000113U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xcb172c2fU), bswap_32big(0x21e50dddU), bswap_32big(0xc9948a94U),
                       bswap_32big(0xc3dfba9aU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0xc68a5edfU), bswap_32big(0x759be082U), bswap_32big(0x26cd6a97U),
                       bswap_32big(0x047cf198U));
        WR1_PROG(REG_1A2CH, 0x40000200U);
        WR1_PROG(REG_1A24H, 0xe8009107U);
        WR1_PROG(REG_1404H, 0x12580000U);
        WR1_PROG(REG_1400H, 0x00800009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00830029U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002032U);
        for (iLoop = 0U; iLoop < 12U; )
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x0a82ed80U), bswap_32big(0x88455583U), bswap_32big(0x2d3d92a0U),
                       bswap_32big(0x3642aa28U));
        WR1_PROG(REG_1A2CH, 0x40000200U);
        WR1_PROG(REG_1A24H, 0xe8008107U);
        WR1_PROG(REG_1400H, 0x00830021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x12a80000U);
        WR1_PROG(REG_1400H, 0x00800009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00830009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002032U);
        for (iLoop = 12; iLoop < 24U; )
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x9aaf09beU), bswap_32big(0x6238ebbeU), bswap_32big(0x0d008d72U),
                       bswap_32big(0x34bed910U));
        WR1_PROG(REG_1A2CH, 0x40000200U);
        WR1_PROG(REG_1A24H, 0xe8008107U);
        WR1_PROG(REG_1400H, 0x00830031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002032U);
        for (iLoop = 24; iLoop < 36; )
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x39ee005fU), bswap_32big(0x627a4c10U), bswap_32big(0x51524826U),
                       bswap_32big(0xffdedcc6U));
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[iLoop + 1]);

        r_rsip_func100(bswap_32big(0xc9564f47U), bswap_32big(0xdc24f36fU), bswap_32big(0x90007a7fU),
                       bswap_32big(0xff0e895fU));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x09108104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[iLoop + 5]);

        r_rsip_func100(bswap_32big(0x824d504aU), bswap_32big(0x092c0620U), bswap_32big(0xbd3afb05U),
                       bswap_32big(0x9645ca6dU));
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_PubKeyIndex[0]);

        r_rsip_func102(bswap_32big(0x8f74ea7dU), bswap_32big(0xbf758be2U), bswap_32big(0x3829a63cU),
                       bswap_32big(0x3eea288dU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
