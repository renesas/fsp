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
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func321 (void)
{
    uint32_t iLoop;
    uint32_t jLoop;
    uint32_t kLoop;
    uint32_t oLoop;
    uint32_t oLoop1;
    uint32_t OFS_ADR;
    (void) iLoop;
    (void) jLoop;
    (void) kLoop;
    (void) oLoop;
    (void) oLoop1;
    (void) OFS_ADR;
    WR1_PROG(REG_1600H, 0x0000373dU);
    WR1_PROG(REG_1600H, 0x00000bdeU);
    while (1)
    {
        WR1_PROG(REG_1404H, 0x12280000U);
        WR1_PROG(REG_1608H, 0x80010340U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x16580000U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x0000135bU);
        WR1_PROG(REG_1600H, 0x3800db40U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0x9fbf56b4U), bswap_32big(0x8223cb62U), bswap_32big(0x962e59e4U),
                       bswap_32big(0xfb25eb44U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000230U);
            WR1_PROG(REG_1004H, 0x4040000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000660U);
            WR1_PROG(REG_1004H, 0x4040000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1600H, 0x00002fc0U);
            r_rsip_func101(bswap_32big(0x44f55146U), bswap_32big(0x39157059U), bswap_32big(0x47eedb79U),
                           bswap_32big(0x9717cabdU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xac380e98U), bswap_32big(0xcc7999acU), bswap_32big(0xac1ad7a5U),
                           bswap_32big(0x1afbca7aU));
            break;
        }
    }

    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1400H, 0x00c00211U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
    OFS_ADR = 136;
    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003211U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x7b3532fcU),
                   bswap_32big(0xeb1bf883U),
                   bswap_32big(0x00fed6bcU),
                   bswap_32big(0x26e8635fU));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
    OFS_ADR = 272;
    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003212U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xcf2862b1U),
                   bswap_32big(0x50f66644U),
                   bswap_32big(0xdd1e69e6U),
                   bswap_32big(0x3bd0702eU));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
    OFS_ADR = 0;
    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003213U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x6d1e6169U),
                   bswap_32big(0x2d1ef853U),
                   bswap_32big(0x2db10e1dU),
                   bswap_32big(0xb6a93b58U));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
    OFS_ADR = 408;
    WR1_PROG(REG_1404H, 0x18800000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003214U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x8080e075U),
                   bswap_32big(0x0c4533caU),
                   bswap_32big(0xebc35eddU),
                   bswap_32big(0xf08cf298U));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x7edfb1abU));
    OFS_ADR = 544;
    WR1_PROG(REG_1404H, 0x10300000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003215U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x53d2dd71U),
                   bswap_32big(0x3d8ee4fbU),
                   bswap_32big(0x79175aa7U),
                   bswap_32big(0xd2b4ab6dU));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x8162b38bU));
    OFS_ADR = 676;
    WR1_PROG(REG_1404H, 0x14600000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003216U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x9568d133U),
                   bswap_32big(0x58f5dcefU),
                   bswap_32big(0x236add2fU),
                   bswap_32big(0xf5ef8219U));
    r_rsip_func016(OFS_ADR);
    while (1)
    {
        WR1_PROG(REG_1404H, 0x18900000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c001fdU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000a90U);
        WR1_PROG(REG_1020H, 0x00000878U);
        WR1_PROG(REG_1004H, 0x4040000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0x1d8ba92cU), bswap_32big(0x17411a79U), bswap_32big(0x47417322U),
                       bswap_32big(0x9e584798U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func101(bswap_32big(0x89796701U), bswap_32big(0x8341c97cU), bswap_32big(0xa6b336d9U),
                           bswap_32big(0x6c55c63bU));
            break;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
            OFS_ADR = 0;
            WR1_PROG(REG_1404H, 0x12380000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003211U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x1dd9dd9cU), bswap_32big(0x9de4554bU), bswap_32big(0x77f1fb6dU),
                           bswap_32big(0xabe6bbfdU));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
            OFS_ADR = 136;
            WR1_PROG(REG_1404H, 0x18800000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003212U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x3d46da21U), bswap_32big(0xff05b75aU), bswap_32big(0x4d87c0dbU),
                           bswap_32big(0x03fcd064U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003211U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x6acb1c01U), bswap_32big(0xa1c06746U), bswap_32big(0x7ac8e8abU),
                           bswap_32big(0xd1b9c376U));
            r_rsip_func322();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
            OFS_ADR = 0;
            WR1_PROG(REG_1404H, 0x12380000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003217U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xb4e80901U), bswap_32big(0xfc24583eU), bswap_32big(0x49b69976U),
                           bswap_32big(0x46b50d3aU));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
            OFS_ADR = 136;
            WR1_PROG(REG_1404H, 0x18800000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003218U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xa1bd20ffU), bswap_32big(0x92bf4ff4U), bswap_32big(0x8e6a924cU),
                           bswap_32big(0x0dc79eb9U));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
            OFS_ADR = 272;
            WR1_PROG(REG_1404H, 0x12380000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003213U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x3632c743U), bswap_32big(0x65913f6eU), bswap_32big(0xf2168e91U),
                           bswap_32big(0x9ea6d521U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
            OFS_ADR = 408;
            WR1_PROG(REG_1404H, 0x18800000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003214U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x63d18077U), bswap_32big(0x4b97bc8aU), bswap_32big(0x5deb77e4U),
                           bswap_32big(0xe02632e3U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1404H, 0x1dd80000U);
            WR1_PROG(REG_1400H, 0x00c00201U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000878U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000230U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000660U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003212U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xa156624aU), bswap_32big(0x2c2cba01U), bswap_32big(0x93144528U),
                           bswap_32big(0xab329f07U));
            r_rsip_func322();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
            OFS_ADR = 272;
            WR1_PROG(REG_1404H, 0x12380000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003219U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x5f356242U), bswap_32big(0x72a86cefU), bswap_32big(0xff3dffbaU),
                           bswap_32big(0x918a69beU));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
            OFS_ADR = 408;
            WR1_PROG(REG_1404H, 0x18800000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000084U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000321aU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x596679b2U), bswap_32big(0xcacd9491U), bswap_32big(0xdbb55f84U),
                           bswap_32big(0x7d68411fU));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1404H, 0x1dd80000U);
            WR1_PROG(REG_1400H, 0x00c00201U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000878U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000230U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000660U);
            WR1_PROG(REG_1004H, 0x40400009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000230U);
            WR1_PROG(REG_1018H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000878U);
            WR1_PROG(REG_1004H, 0x4040000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00a10000U);
            r_rsip_func100(bswap_32big(0x00231b00U), bswap_32big(0xdc997757U), bswap_32big(0xa4740cafU),
                           bswap_32big(0xed0f13c3U));
            WR1_PROG(REG_143CH, 0x00400000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1014H, 0x00000878U);
                WR1_PROG(REG_1018H, 0x00000fd8U);
                WR1_PROG(REG_1020H, 0x00000230U);
                WR1_PROG(REG_1004H, 0x40400009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003215U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xd84ca561U),
                               bswap_32big(0xad70c105U),
                               bswap_32big(0x28e4027aU),
                               bswap_32big(0xb0d884ecU));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
                OFS_ADR = 272;
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003216U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x16c60115U),
                               bswap_32big(0x93561bb6U),
                               bswap_32big(0x7d2e750dU),
                               bswap_32big(0xbb9ed60aU));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003211U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xef0708cbU),
                               bswap_32big(0x8628fe83U),
                               bswap_32big(0x9a49d347U),
                               bswap_32big(0x036db239U));
                r_rsip_func324();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321bU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x6be35146U),
                               bswap_32big(0x567ad338U),
                               bswap_32big(0x5ae17855U),
                               bswap_32big(0x3a670e7aU));
                r_rsip_func016(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
                OFS_ADR = 136;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003217U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x2f0648d1U),
                               bswap_32big(0xc68a8d27U),
                               bswap_32big(0x022c552cU),
                               bswap_32big(0xc58aa259U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
                OFS_ADR = 408;
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003218U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x2672f28cU),
                               bswap_32big(0x1c4ac3e7U),
                               bswap_32big(0x6052c13fU),
                               bswap_32big(0x46adbb60U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003212U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x183e9ef2U),
                               bswap_32big(0x42bf1d42U),
                               bswap_32big(0x47e15dbfU),
                               bswap_32big(0x7fbfbccbU));
                r_rsip_func324();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
                OFS_ADR = 136;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321cU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x3479179fU),
                               bswap_32big(0x448b4373U),
                               bswap_32big(0xfd09bf8fU),
                               bswap_32big(0xcf754ed6U));
                r_rsip_func016(OFS_ADR);
                r_rsip_func101(bswap_32big(0x03b2d372U),
                               bswap_32big(0x93e05cd4U),
                               bswap_32big(0xb1b6b0e0U),
                               bswap_32big(0x9ee92f95U));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000660U);
                WR1_PROG(REG_1018H, 0x00000230U);
                WR1_PROG(REG_1020H, 0x00000660U);
                WR1_PROG(REG_1004H, 0x4040000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
                OFS_ADR = 272;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321aU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x10325768U),
                               bswap_32big(0xd6697732U),
                               bswap_32big(0x18b0f0fdU),
                               bswap_32big(0x25c358f1U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x9fd531f0U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321bU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x0baf3cf6U),
                               bswap_32big(0x48984e2cU),
                               bswap_32big(0x6ee7cc5aU),
                               bswap_32big(0x32d455d9U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003213U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xc4f1c16bU),
                               bswap_32big(0x8fbeb87aU),
                               bswap_32big(0xe76928e2U),
                               bswap_32big(0xfce7e9d3U));
                r_rsip_func324();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x5bfa91b0U));
                OFS_ADR = 272;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321dU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x9e0262e1U),
                               bswap_32big(0x1fdca22bU),
                               bswap_32big(0x52b05ef2U),
                               bswap_32big(0xf38b5633U));
                r_rsip_func016(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
                OFS_ADR = 408;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321cU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xe3088868U),
                               bswap_32big(0x45bb0fe8U),
                               bswap_32big(0x01ffcd20U),
                               bswap_32big(0x14ed4107U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xf9bf3112U));
                OFS_ADR = 136;
                WR1_PROG(REG_1404H, 0x1dc80000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321dU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xff98eea3U),
                               bswap_32big(0xdc4178efU),
                               bswap_32big(0xa49dcb8bU),
                               bswap_32big(0x1c05f1c9U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003214U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xd6bb27deU),
                               bswap_32big(0xc8df4617U),
                               bswap_32big(0x877446b0U),
                               bswap_32big(0xdb743a5cU));
                r_rsip_func324();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
                OFS_ADR = 408;
                WR1_PROG(REG_1404H, 0x16680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000084U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000321eU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x19273b21U),
                               bswap_32big(0xe89208a1U),
                               bswap_32big(0x19abbf79U),
                               bswap_32big(0x3682d180U));
                r_rsip_func016(OFS_ADR);
                r_rsip_func101(bswap_32big(0xd9eab1c7U),
                               bswap_32big(0xe8cf11d7U),
                               bswap_32big(0xad23639aU),
                               bswap_32big(0xb3f7e648U));
            }
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x7edfb1abU));
    OFS_ADR = 544;
    WR1_PROG(REG_1404H, 0x10300000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000321eU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x39d7cce0U),
                   bswap_32big(0x85759887U),
                   bswap_32big(0x7e2ec732U),
                   bswap_32big(0xf985c637U));
    r_rsip_func017(OFS_ADR);
    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    while (1)
    {
        WR1_PROG(REG_1600H, 0x38000fdeU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);
        r_rsip_func100(bswap_32big(0x4e7eea18U), bswap_32big(0xccbf3c25U), bswap_32big(0x9e149799U),
                       bswap_32big(0x3321db56U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000a90U);
            WR1_PROG(REG_1018H, 0x00000660U);
            WR1_PROG(REG_1020H, 0x00000660U);
            WR1_PROG(REG_1004H, 0x40400008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000a90U);
            WR1_PROG(REG_1018H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000230U);
            WR1_PROG(REG_1004H, 0x40400008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1600H, 0x000033c0U);
            r_rsip_func101(bswap_32big(0x70e12068U), bswap_32big(0x17e56877U), bswap_32big(0xcf9b1f9dU),
                           bswap_32big(0xd91eb19eU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xd30c0b7dU), bswap_32big(0x047d3c99U), bswap_32big(0xa4408661U),
                           bswap_32big(0x3b91b033U));
            break;
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0c0ab7c4U));
    OFS_ADR = 408;
    WR1_PROG(REG_1404H, 0x16680000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000084U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000321fU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x27c3d09dU),
                   bswap_32big(0x2b99a4acU),
                   bswap_32big(0x12d082ceU),
                   bswap_32big(0x2972f09eU));
    r_rsip_func017(OFS_ADR);
    WR1_PROG(REG_1404H, 0x16680000U);
    WR1_PROG(REG_1608H, 0x80010360U);
    WR1_PROG(REG_1400H, 0x00030005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x03430005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    while (1)
    {
        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000878U);
        WR1_PROG(REG_1020H, 0x00000a90U);
        WR1_PROG(REG_1004H, 0x4141000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0xd8bf9319U), bswap_32big(0xcdbf5f8aU), bswap_32big(0x6f4bbb0cU),
                       bswap_32big(0x60062f0eU));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000878U);
            WR1_PROG(REG_1018H, 0x00000230U);
            WR1_PROG(REG_1020H, 0x00000878U);
            WR1_PROG(REG_1004H, 0x4141000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x61ff77fdU), bswap_32big(0x7f775e7fU), bswap_32big(0x795224a5U),
                           bswap_32big(0x380c81faU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0x1fa2bf08U), bswap_32big(0xc0a9a249U), bswap_32big(0xac2d290dU),
                           bswap_32big(0x60d67742U));
            break;
        }
    }

    WR1_PROG(REG_1600H, 0x3800db60U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xf3d04496U),
                   bswap_32big(0x656599b8U),
                   bswap_32big(0x0c44dc80U),
                   bswap_32big(0x37ef4bccU));
    WR1_PROG(REG_143CH, 0x00400000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1014H, 0x00000230U);
        WR1_PROG(REG_1018H, 0x00000878U);
        WR1_PROG(REG_1020H, 0x00000878U);
        WR1_PROG(REG_1004H, 0x4141000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        r_rsip_func101(bswap_32big(0x254702a9U), bswap_32big(0xe88e33ceU), bswap_32big(0x9fb2e846U),
                       bswap_32big(0x37706fffU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0x3aa5f4c0U), bswap_32big(0x1b50bf80U), bswap_32big(0x055b0e62U),
                       bswap_32big(0xb1e1b0efU));
    }

    WR1_PROG(REG_1600H, 0x000037b9U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
