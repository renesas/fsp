/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func321 (void)
{
    uint32_t OFS_ADR = 0U;

    WR1_PROG(REG_1600H, 0x0000373dU);

    WR1_PROG(REG_1600H, 0x00000bdeU);

    while (1)
    {
        WR1_PROG(REG_1404H, 0x12280000U);
        WR1_PROG(REG_1608H, 0x80010340U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x16580000U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000135bU);
        WR1_PROG(REG_1600H, 0x3800db40U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xcc8bfe72U, 0x0dccb398U, 0x5f1b3137U, 0xb3bd638bU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000230U);

            WR1_PROG(REG_1004H, 0x4040000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000660U);

            WR1_PROG(REG_1004H, 0x4040000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1600H, 0x00002fc0U);

            HW_SCE_p_func101(0x7f913936U, 0xa07b01a0U, 0x628a32ffU, 0x493830b6U);
        }
        else
        {
            HW_SCE_p_func101(0x67e5630cU, 0x873e4bdfU, 0xd6e46158U, 0x6ba3c01bU);

            break;
        }
    }

    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1400H, 0x00c00211U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

    OFS_ADR = 136;

    WR1_PROG(REG_1404H, 0x18800000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003211U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x12de24b6U, 0x82035efdU, 0xea88e21dU, 0x72e436e9U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

    OFS_ADR = 272;

    WR1_PROG(REG_1404H, 0x18800000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003212U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x9fad161bU, 0x6a4aadf9U, 0xe00c9f46U, 0x33bf53f8U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

    OFS_ADR = 0;

    WR1_PROG(REG_1404H, 0x18800000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003213U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xba659f69U, 0x8d9b5f6bU, 0xfe72c104U, 0x590efe34U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

    OFS_ADR = 408;

    WR1_PROG(REG_1404H, 0x18800000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003214U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x1a6c3fa6U, 0xf326cc1cU, 0xa5246a0dU, 0x904eabb6U);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x7edfb1abU));

    OFS_ADR = 544;

    WR1_PROG(REG_1404H, 0x10300000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003215U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xaa63a4aeU, 0xe0ba0fe9U, 0xff3c6a5bU, 0x2939abafU);
    HW_SCE_p_func016(OFS_ADR);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x8162b38bU));

    OFS_ADR = 676;

    WR1_PROG(REG_1404H, 0x14600000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00003216U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x598e95b8U, 0x7fb4fae7U, 0x864fa0d8U, 0xd80dc222U);
    HW_SCE_p_func016(OFS_ADR);

    while (1)
    {
        WR1_PROG(REG_1404H, 0x18900000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c001fdU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000a90U);
        WR1_PROG(REG_1020H, 0x00000878U);

        WR1_PROG(REG_1004H, 0x4040000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x4335320eU, 0x3f2caa87U, 0x226943bbU, 0x244675beU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func101(0x2c711d3dU, 0x5656cac4U, 0x0908b7c7U, 0x65ec8f94U);

            break;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

            OFS_ADR = 0;

            WR1_PROG(REG_1404H, 0x12380000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003211U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x2f927d7cU, 0x3e3c2eebU, 0x644e3447U, 0xd87384eaU);
            HW_SCE_p_func017(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

            OFS_ADR = 136;

            WR1_PROG(REG_1404H, 0x18800000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003212U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xfc76a194U, 0x0e69a91aU, 0xd98378ddU, 0xe6382734U);
            HW_SCE_p_func017(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003211U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x7e47e869U, 0xf808629bU, 0x7070ae54U, 0x129c1115U);
            HW_SCE_p_func322();

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

            OFS_ADR = 0;

            WR1_PROG(REG_1404H, 0x12380000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003217U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x387bc6c6U, 0x657bf656U, 0xd969a0beU, 0xf12eb46fU);
            HW_SCE_p_func016(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

            OFS_ADR = 136;

            WR1_PROG(REG_1404H, 0x18800000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003218U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x6d185646U, 0xb0cc2a65U, 0x00ca42f1U, 0x7b90eac8U);
            HW_SCE_p_func016(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

            OFS_ADR = 272;

            WR1_PROG(REG_1404H, 0x12380000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003213U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x75db1471U, 0xd1f83e8fU, 0xe8215c6fU, 0xf658d701U);
            HW_SCE_p_func017(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

            OFS_ADR = 408;

            WR1_PROG(REG_1404H, 0x18800000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003214U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xdb1fc958U, 0xa19b93e4U, 0x9f36a76dU, 0x353beaddU);
            HW_SCE_p_func017(OFS_ADR);

            WR1_PROG(REG_1404H, 0x1dd80000U);
            WR1_PROG(REG_1400H, 0x00c00201U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000878U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000230U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000660U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003212U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x437ea527U, 0x3b983801U, 0xf4400fa0U, 0x71f1a652U);
            HW_SCE_p_func322();

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

            OFS_ADR = 272;

            WR1_PROG(REG_1404H, 0x12380000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00003219U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x1642b926U, 0x78941c70U, 0x643bb998U, 0xb432bc56U);
            HW_SCE_p_func016(OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

            OFS_ADR = 408;

            WR1_PROG(REG_1404H, 0x18800000U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000321aU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x30624641U, 0x1e460b6cU, 0x184de129U, 0xf14ef4b9U);
            HW_SCE_p_func016(OFS_ADR);

            WR1_PROG(REG_1404H, 0x1dd80000U);
            WR1_PROG(REG_1400H, 0x00c00201U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000878U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000230U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000660U);

            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000878U);

            WR1_PROG(REG_1004H, 0x4040000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00a10000U);

            HW_SCE_p_func100(0x0654e53cU, 0x857c480fU, 0x693e7f4eU, 0x5cfe81b0U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000878U);
                WR1_PROG(REG_1018H, 0x00000fd8U);
                WR1_PROG(REG_1020H, 0x00000230U);

                WR1_PROG(REG_1004H, 0x40400009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

                OFS_ADR = 0;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003215U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xf329afc0U, 0x4b424068U, 0x2a290582U, 0x915924b2U);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

                OFS_ADR = 272;

                WR1_PROG(REG_1404H, 0x1dc80000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003216U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x722a4b92U, 0xd3ea2790U, 0xcc88f410U, 0x320f4d1dU);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003211U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x0b0dd63dU, 0xff1c954eU, 0xae071509U, 0xb2166453U);
                HW_SCE_p_func324();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

                OFS_ADR = 0;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321bU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x6132d291U, 0xd2c77c90U, 0x10203aa4U, 0xa59118f4U);
                HW_SCE_p_func016(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

                OFS_ADR = 136;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003217U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x14685bb6U, 0xea215460U, 0xe122da1aU, 0x073c1759U);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

                OFS_ADR = 408;

                WR1_PROG(REG_1404H, 0x1dc80000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003218U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xd2f10a69U, 0xd7d0a00dU, 0xc376fb8fU, 0x6d8ff4bbU);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003212U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xb7e6de6dU, 0xec315ff1U, 0x6e89db51U, 0x8ce79a73U);
                HW_SCE_p_func324();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

                OFS_ADR = 136;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321cU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xf1f7e5d3U, 0x4366e887U, 0x1fa83c21U, 0x84d82316U);
                HW_SCE_p_func016(OFS_ADR);

                HW_SCE_p_func101(0x26efb837U, 0x7270a517U, 0xd4d52360U, 0xd5b12456U);
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000660U);
                WR1_PROG(REG_1018H, 0x00000230U);
                WR1_PROG(REG_1020H, 0x00000660U);

                WR1_PROG(REG_1004H, 0x4040000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

                OFS_ADR = 272;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321aU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x3048e0f9U, 0x8b618fc3U, 0x39850f36U, 0x8378e7c4U);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x9fd531f0U));

                OFS_ADR = 0;

                WR1_PROG(REG_1404H, 0x1dc80000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321bU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xf9938870U, 0x06a3671cU, 0x681a1792U, 0x00569213U);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003213U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x75487577U, 0x5e075155U, 0xdba5834eU, 0xd1d6a03aU);
                HW_SCE_p_func324();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x5bfa91b0U));

                OFS_ADR = 272;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321dU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xda65bd46U, 0xdfe45222U, 0x2b6a28f0U, 0x6af9d95cU);
                HW_SCE_p_func016(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

                OFS_ADR = 408;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321cU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xb265311cU, 0xce7b5e0bU, 0xd607aa9cU, 0x9605a01fU);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0xf9bf3112U));

                OFS_ADR = 136;

                WR1_PROG(REG_1404H, 0x1dc80000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321dU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x5ae8092eU, 0x1c49ac78U, 0x070d66ceU, 0x41e1303bU);
                HW_SCE_p_func017(OFS_ADR);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00003214U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x4d74ece6U, 0xa07c0e82U, 0xfe3eff57U, 0x1be4eb76U);
                HW_SCE_p_func324();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

                OFS_ADR = 408;

                WR1_PROG(REG_1404H, 0x16680000U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000321eU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x445ed281U, 0x91855344U, 0xd19e9e75U, 0xf694c1f4U);
                HW_SCE_p_func016(OFS_ADR);

                HW_SCE_p_func101(0x488172d2U, 0x5f242084U, 0x824300afU, 0xc47ab35fU);
            }
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x7edfb1abU));

    OFS_ADR = 544;

    WR1_PROG(REG_1404H, 0x10300000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000321eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x8ac61c41U, 0x753d494fU, 0x6b4c55b9U, 0x7f1a7f81U);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    while (1)
    {
        WR1_PROG(REG_1600H, 0x38000fdeU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func100(0xf97f3ab1U, 0x2a8eee40U, 0xe1606157U, 0xd9ca976cU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000a90U);
            WR1_PROG(REG_1018H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000660U);

            WR1_PROG(REG_1004H, 0x40400008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000a90U);
            WR1_PROG(REG_1018H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000230U);

            WR1_PROG(REG_1004H, 0x40400008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1600H, 0x000033c0U);

            HW_SCE_p_func101(0xe295f351U, 0x5cc62a70U, 0x826ea844U, 0x7acafe23U);
        }
        else
        {
            HW_SCE_p_func101(0x01deac11U, 0xd1031008U, 0xb982dc3fU, 0xe64d3f00U);

            break;
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0c0ab7c4U));

    OFS_ADR = 408;

    WR1_PROG(REG_1404H, 0x16680000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000321fU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xf891bdfaU, 0x3923a90fU, 0x6612ba3eU, 0xb36bee4bU);
    HW_SCE_p_func017(OFS_ADR);

    WR1_PROG(REG_1404H, 0x16680000U);
    WR1_PROG(REG_1608H, 0x80010360U);
    WR1_PROG(REG_1400H, 0x00030005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x03430005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    while (1)
    {
        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000878U);
        WR1_PROG(REG_1020H, 0x00000a90U);

        WR1_PROG(REG_1004H, 0x4141000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x7367c1f6U, 0xec0000d6U, 0x2d73a38aU, 0xa77a5aeaU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000878U);

            WR1_PROG(REG_1004H, 0x4141000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func101(0xf86ede5bU, 0xc784835dU, 0x46bbb8e8U, 0x14df31edU);
        }
        else
        {
            HW_SCE_p_func101(0xbc9d35c0U, 0xb9114e02U, 0x84a918f1U, 0xcfb5a3f1U);

            break;
        }
    }

    WR1_PROG(REG_1600H, 0x3800db60U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0xed6b1696U, 0x5ac6d545U, 0xcc412a36U, 0x5b0dd97eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000878U);
        WR1_PROG(REG_1020H, 0x00000878U);

        WR1_PROG(REG_1004H, 0x4141000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        HW_SCE_p_func101(0xe7c62d83U, 0xb1dab124U, 0x77bd11a9U, 0xd30e4829U);
    }
    else
    {
        HW_SCE_p_func101(0xa2815b2cU, 0xda4540ffU, 0x46b80683U, 0x23bfa061U);
    }

    WR1_PROG(REG_1600H, 0x000037b9U);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
