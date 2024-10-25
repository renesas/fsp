/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func093_r1 (const uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    HW_SCE_p_func100(0x700d45a4U, 0xc88e4b39U, 0xfb9a3a88U, 0xcb7bd92eU);
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

    HW_SCE_p_func101(0x5a6fa76cU, 0xc3f5a279U, 0x76947271U, 0xac64b2fcU);
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

    oLoop = 0;
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
        {
            HW_SCE_p_func100(0xe9a56638U, 0x6522dcabU, 0xc8a742d8U, 0x98e73e4cU);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG1[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG2[1 + iLoop]);

            HW_SCE_p_func101(0xa412e637U, 0x57a7976cU, 0xc5446639U, 0xbee3e677U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        HW_SCE_p_func101(0xd8961dbaU, 0x6cf022e6U, 0xb6157651U, 0xdcd35cf8U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        HW_SCE_p_func100(0x6c2ff35fU, 0x349e5234U, 0x6d0ec82dU, 0x1fbd14e5U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func094(0U, ARG1);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG2);
        HW_SCE_p_func100(0xf93cc2edU, 0xd59c9727U, 0x51cb1ba6U, 0x211d5f21U);
        HW_SCE_p_func065(8U, ARG2);
        HW_SCE_p_func100(0x6e0e7509U, 0xd7d4ce7eU, 0x75399976U, 0x7920f2cbU);
        HW_SCE_p_func065(16U, ARG2);
        HW_SCE_p_func100(0xdc19ba12U, 0xb2dcd600U, 0x671d6f34U, 0x87560acfU);
        HW_SCE_p_func065(24U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0x0f8af3b1U, 0x9c84f3a3U, 0x4e966b36U, 0x5bc5fe95U);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000105U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG1[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);
        oLoop = oLoop + 4U;

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func101(0xd19cf6e8U, 0x882da882U, 0x85ca14a9U, 0x9b8ec661U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        HW_SCE_p_func100(0x11773ce2U, 0x40f5136fU, 0x10570524U, 0x58b3b90bU);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func094(0U, ARG1);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG2);
        HW_SCE_p_func100(0x121f4eacU, 0x2a6d8fe8U, 0x6dc0b312U, 0x72125139U);
        HW_SCE_p_func062(8U, ARG2);
        HW_SCE_p_func100(0xc9ad5753U, 0xb68dfa75U, 0x5f0965dbU, 0xa1df3fbeU);
        HW_SCE_p_func062(16U, ARG2);
        HW_SCE_p_func100(0x14031643U, 0x300ac1f1U, 0xf3edcb69U, 0x3f6aaae5U);
        HW_SCE_p_func062(24U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0x239062d0U, 0xa3869d27U, 0xcc0ccdeaU, 0xf682ac8cU);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func094(32U, ARG1);
        iLoop = 32U + 32U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(32U, ARG2);
        HW_SCE_p_func100(0xd4608773U, 0x895feb49U, 0x589b6c7fU, 0x7fc2d46fU);
        HW_SCE_p_func062(40U, ARG2);
        HW_SCE_p_func100(0xa3be59f0U, 0x1e7b31c0U, 0x34080981U, 0x14c4abbcU);
        HW_SCE_p_func062(48U, ARG2);
        HW_SCE_p_func100(0x6f14a10cU, 0x720ce1a4U, 0xe298b228U, 0x4075bfc2U);
        HW_SCE_p_func062(56U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func101(0x3f211600U, 0x63506e0dU, 0x28df6168U, 0x1a87d6cdU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        HW_SCE_p_func100(0x887ee928U, 0x10ed34caU, 0x78e0b1fbU, 0xd5ce66b0U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func095(0U, ARG1);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG2);
        HW_SCE_p_func100(0xe96d42d7U, 0xcd5fff27U, 0x7bf8e98eU, 0xe424df7bU);
        HW_SCE_p_func065(8U, ARG2);
        HW_SCE_p_func100(0x92fb461fU, 0x75789d47U, 0xf86a5155U, 0x783849b4U);
        HW_SCE_p_func065(16U, ARG2);
        HW_SCE_p_func100(0x779cd9b1U, 0xad329da1U, 0x4c73344fU, 0x636d05bbU);
        HW_SCE_p_func065(24U, ARG2);
        HW_SCE_p_func100(0x266c849eU, 0xbabdf5aeU, 0x86952065U, 0xd1ed0840U);
        HW_SCE_p_func065(32U, ARG2);
        HW_SCE_p_func100(0x2d69f29aU, 0x971cfc77U, 0xc46c4f70U, 0x48be4444U);
        HW_SCE_p_func065(40U, ARG2);
        HW_SCE_p_func100(0x6a06c768U, 0x64240a75U, 0x7aadf1d8U, 0xe2d00bc6U);
        HW_SCE_p_func065(48U, ARG2);
        HW_SCE_p_func100(0xe203b97bU, 0x919ca6edU, 0x45cfde06U, 0xd73f4108U);
        HW_SCE_p_func065(56U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xd8f913f5U, 0x04ff8208U, 0xc3c5d614U, 0xc0eace46U);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000105U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG1[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);
        oLoop = oLoop + 4U;

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func101(0xec9d8a2dU, 0x138b3f57U, 0x7f356064U, 0x230e4674U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        HW_SCE_p_func100(0x89b14b3dU, 0xd94a1787U, 0x3a44d94eU, 0x0f050001U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func095(0U, ARG1);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG2);
        HW_SCE_p_func100(0x3364c4ffU, 0xc23236c2U, 0x9c018512U, 0xdbfa56bcU);
        HW_SCE_p_func062(8U, ARG2);
        HW_SCE_p_func100(0xa33a026dU, 0x94d77fd4U, 0x1a779111U, 0xe7491f7cU);
        HW_SCE_p_func062(16U, ARG2);
        HW_SCE_p_func100(0xf48f7504U, 0xeb5f40d5U, 0x29a09d4aU, 0x2af7d1bfU);
        HW_SCE_p_func062(24U, ARG2);
        HW_SCE_p_func100(0xea0f3d11U, 0xfea2319cU, 0x0ab8e103U, 0xc183ec12U);
        HW_SCE_p_func062(32U, ARG2);
        HW_SCE_p_func100(0xe75bdf82U, 0xf84ca427U, 0xc14d4035U, 0x4287d43aU);
        HW_SCE_p_func062(40U, ARG2);
        HW_SCE_p_func100(0xb54aab44U, 0x963a5e1fU, 0xdcfbe0b2U, 0x5106f5daU);
        HW_SCE_p_func062(48U, ARG2);
        HW_SCE_p_func100(0x9f3d2c75U, 0x9519b394U, 0x0f446c4eU, 0xb0bad03fU);
        HW_SCE_p_func062(56U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xadadc817U, 0x4b678cd8U, 0x48ff5293U, 0xcc849c72U);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func095(64U, ARG1);
        iLoop = 64U + 64U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(64U, ARG2);
        HW_SCE_p_func100(0x42ca095cU, 0xf3a701eaU, 0x656829e9U, 0x6d952bb7U);
        HW_SCE_p_func062(72U, ARG2);
        HW_SCE_p_func100(0xceaf4a3cU, 0xae137683U, 0xb46f5cf2U, 0x64728568U);
        HW_SCE_p_func062(80U, ARG2);
        HW_SCE_p_func100(0x69e99598U, 0xcf5b6642U, 0x1d055073U, 0xe3074f77U);
        HW_SCE_p_func062(88U, ARG2);
        HW_SCE_p_func100(0xf75334c0U, 0x27f5a7ffU, 0x268f2dd2U, 0x319fabdaU);
        HW_SCE_p_func062(96U, ARG2);
        HW_SCE_p_func100(0x83aa4eb0U, 0x87ba9af9U, 0xee309c32U, 0x482d7f23U);
        HW_SCE_p_func062(104U, ARG2);
        HW_SCE_p_func100(0xf4147342U, 0x8c7accf5U, 0xa78f7a62U, 0x4f48f687U);
        HW_SCE_p_func062(112U, ARG2);
        HW_SCE_p_func100(0xd945f2dbU, 0xf568a0c3U, 0xc0378622U, 0xcce3b57aU);
        HW_SCE_p_func062(120U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func101(0xa3af0ea0U, 0xd90607f4U, 0x13bad035U, 0xac052446U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
        {
            HW_SCE_p_func100(0xf1fc7f18U, 0x14751a03U, 0x3cef6661U, 0xc8c9937fU);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG1[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8008105U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG2[1 + iLoop]);

            HW_SCE_p_func101(0xe8cbba12U, 0x0dc8f936U, 0xa8819e4fU, 0x08832f59U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        oLoop = iLoop;

        HW_SCE_p_func101(0x5e40088fU, 0x4e8ceed4U, 0x615f435cU, 0x2fd884e0U);
    }

    HW_SCE_p_func100(0x5f7f7e31U, 0x738c66fdU, 0x3c478859U, 0xab9d49b1U);
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
    RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);

    WR1_PROG(REG_1600H, 0x00007c1cU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
