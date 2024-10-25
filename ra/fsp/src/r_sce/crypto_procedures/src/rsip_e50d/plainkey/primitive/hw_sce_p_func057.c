/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func057_r1 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    HW_SCE_p_func100(0x014fc442U, 0x7fb45e76U, 0x2e7fbef3U, 0x70d8c890U);
    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x08000045U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &ARG1[0]);

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    HW_SCE_p_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

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
    WR1_PROG(REG_1420H, change_endian_long(0x000000ffU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x97c16b1aU, 0xcab4e1e0U, 0xe83dc919U, 0x63d1c089U);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x000034e4U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000feU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xdd9d2f93U, 0x1fd86435U, 0x8920e52aU, 0x6d7c6345U);
    HW_SCE_p_func044_r1();

    HW_SCE_p_func100(0x84231fe2U, 0xc78ac71aU, 0xf5e7c979U, 0x0073272eU);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1000H, 0x00010000U);

    HW_SCE_p_func081_r1();

    WR1_PROG(REG_1600H, 0x00007c01U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    oLoop = 0x00000000U;
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4U); )
        {
            HW_SCE_p_func100(0x72cc0c7dU, 0x89f95449U, 0x0b1cc1acU, 0xdf7d3e8cU);
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

            HW_SCE_p_func101(0x5932c257U, 0x18e9c71bU, 0x730b7181U, 0x37341b89U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        HW_SCE_p_func101(0x614bb121U, 0x704ff38bU, 0x46eb0915U, 0x131c944eU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        HW_SCE_p_func100(0xf88d1321U, 0xe4630131U, 0x2b4d6534U, 0xd7f616ebU);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func061(0U, ARG2);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG3);
        HW_SCE_p_func100(0x5b99cf05U, 0x5d1c45b5U, 0xf961f565U, 0xf0f798d6U);
        HW_SCE_p_func065(8U, ARG3);
        HW_SCE_p_func100(0xc7ef037cU, 0x74826bc3U, 0x6a430c24U, 0x68d40ce4U);
        HW_SCE_p_func065(16U, ARG3);
        HW_SCE_p_func100(0x1bf75dabU, 0xbc824dc0U, 0xfd937910U, 0x85c52eabU);
        HW_SCE_p_func065(24U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0xe1395ad4U, 0x9237099dU, 0xb2de6ca7U, 0x8b6c1224U);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);
        oLoop = oLoop + 4U;

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func101(0x7169fd87U, 0x38b5434eU, 0x4d55c288U, 0x7b0d36a5U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        HW_SCE_p_func100(0xb9d1dfeaU, 0x9e4ddd19U, 0xb2224345U, 0xf69ef6a8U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func061(0U, ARG2);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG3);
        HW_SCE_p_func100(0xc3c0c681U, 0x02c44987U, 0xe512725fU, 0x9a53137fU);
        HW_SCE_p_func062(8U, ARG3);
        HW_SCE_p_func100(0x5cb73e1cU, 0xaf50e6c1U, 0x49258203U, 0x828dd241U);
        HW_SCE_p_func062(16U, ARG3);
        HW_SCE_p_func100(0xd23f35d2U, 0x012c2d9cU, 0x7ef1c90fU, 0x104bd816U);
        HW_SCE_p_func062(24U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0xa171cf1eU, 0x2ad70d00U, 0xfcc81f5eU, 0x49ea4029U);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func061(32U, ARG2);
        iLoop = 32U + 32U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(32U, ARG3);
        HW_SCE_p_func100(0xcf4bd772U, 0x52e2bd96U, 0xdcccff88U, 0x9123a851U);
        HW_SCE_p_func062(40U, ARG3);
        HW_SCE_p_func100(0xf7abe70eU, 0xcdb70258U, 0xc77adbc4U, 0x9c9a153cU);
        HW_SCE_p_func062(48U, ARG3);
        HW_SCE_p_func100(0xed45bb54U, 0x10f91c59U, 0xaaf8679bU, 0xff5d18e3U);
        HW_SCE_p_func062(56U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func101(0x4a51196dU, 0x571b929aU, 0xdceca5f1U, 0x6297ada0U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        HW_SCE_p_func100(0x584c0a00U, 0x0eb56d8eU, 0xf74dfec0U, 0x7c26f2fdU);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func063(0U, ARG2);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG3);
        HW_SCE_p_func100(0xbc39d012U, 0x6ba76cddU, 0xab21fe57U, 0x62c8bd67U);
        HW_SCE_p_func065(8U, ARG3);
        HW_SCE_p_func100(0x5f2d0a0fU, 0x6008f5afU, 0x0fd513dfU, 0x19e8b596U);
        HW_SCE_p_func065(16U, ARG3);
        HW_SCE_p_func100(0x16c3bd73U, 0xa8b90416U, 0x8ad98014U, 0x38610d0cU);
        HW_SCE_p_func065(24U, ARG3);
        HW_SCE_p_func100(0xa4e22ab1U, 0x12665454U, 0x62903721U, 0xa83f0f02U);
        HW_SCE_p_func065(32U, ARG3);
        HW_SCE_p_func100(0xbf711907U, 0x7d9e03b5U, 0x6b5ea360U, 0xc7d5ff12U);
        HW_SCE_p_func065(40U, ARG3);
        HW_SCE_p_func100(0xc54f9756U, 0x49342d56U, 0xea2a3986U, 0xd19806b8U);
        HW_SCE_p_func065(48U, ARG3);
        HW_SCE_p_func100(0x2dcd8013U, 0xde0cb6ebU, 0x529879d7U, 0xfc7081d3U);
        HW_SCE_p_func065(56U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xc20f2e25U, 0xab9e1fd7U, 0xca7e9acbU, 0x1cb7304eU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);
        oLoop = oLoop + 4U;

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func101(0xe67227a1U, 0x1cbaa6c6U, 0xdcb995cfU, 0x2245defcU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        HW_SCE_p_func100(0xd7433c48U, 0x7297f4d2U, 0xe78928eeU, 0x8c5f2293U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func063(0U, ARG2);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG3);
        HW_SCE_p_func100(0xf24bc9b3U, 0x98d8b1a3U, 0xe247e2e0U, 0xd6e20cd9U);
        HW_SCE_p_func062(8U, ARG3);
        HW_SCE_p_func100(0x4b18322aU, 0xe5cb458fU, 0x060afa33U, 0x954bccedU);
        HW_SCE_p_func062(16U, ARG3);
        HW_SCE_p_func100(0xebc3b37eU, 0xc91d80d9U, 0x6c5f767cU, 0x08fcb83dU);
        HW_SCE_p_func062(24U, ARG3);
        HW_SCE_p_func100(0x2f98b9dbU, 0x266b8c1cU, 0xedc12e72U, 0xe31c251eU);
        HW_SCE_p_func062(32U, ARG3);
        HW_SCE_p_func100(0xc2f2e55cU, 0x830c21f5U, 0x683e8b9aU, 0xa115a006U);
        HW_SCE_p_func062(40U, ARG3);
        HW_SCE_p_func100(0x1b9a4081U, 0xa1774fb1U, 0x93d607e7U, 0xfd21a695U);
        HW_SCE_p_func062(48U, ARG3);
        HW_SCE_p_func100(0x83b92a5cU, 0xdff7a94aU, 0x4d37f0f7U, 0xe04657d7U);
        HW_SCE_p_func062(56U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xdf5e347cU, 0x6a81e0d4U, 0x1dac104dU, 0xdfd507e3U);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func063(64U, ARG2);
        iLoop = 64U + 64U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(64U, ARG3);
        HW_SCE_p_func100(0xb442a337U, 0xa18cfcffU, 0xce14fb50U, 0xd3a1f903U);
        HW_SCE_p_func062(72U, ARG3);
        HW_SCE_p_func100(0x9ecb9b7aU, 0x8f7311aeU, 0xa6d140d1U, 0x81042849U);
        HW_SCE_p_func062(80U, ARG3);
        HW_SCE_p_func100(0x0eeebee1U, 0xa23ff315U, 0x7ae87737U, 0xe65d6dceU);
        HW_SCE_p_func062(88U, ARG3);
        HW_SCE_p_func100(0x0e20bd44U, 0x1e4434d7U, 0x834ead2aU, 0xf2d1b575U);
        HW_SCE_p_func062(96U, ARG3);
        HW_SCE_p_func100(0xf511d282U, 0x41bfd85eU, 0xeffb4821U, 0x3783e633U);
        HW_SCE_p_func062(104U, ARG3);
        HW_SCE_p_func100(0x4086e315U, 0x9798360cU, 0xa5cddf04U, 0xd70ae0eeU);
        HW_SCE_p_func062(112U, ARG3);
        HW_SCE_p_func100(0xc5750b35U, 0xd5fc1a84U, 0xaa1426deU, 0xb5c49619U);
        HW_SCE_p_func062(120U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func101(0x1a9821fcU, 0x8a771b55U, 0x5781d988U, 0xd83e7d7cU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4U); )
        {
            HW_SCE_p_func100(0x193fea21U, 0x9dcc2336U, 0x5969d8b6U, 0x495f5a25U);
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

            HW_SCE_p_func101(0x01dbc06fU, 0xbe053546U, 0xca126789U, 0x65db6947U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        HW_SCE_p_func101(0xa8370a04U, 0x9408d256U, 0xee197461U, 0xe6d5b77fU);
    }

    HW_SCE_p_func100(0xb9028d29U, 0x37d0a3b6U, 0x99afb95bU, 0x5e729e90U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

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
