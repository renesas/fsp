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

void r_rsip_func313 (void)
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
        WR1_PROG(REG_1404H, 0x12180000U);
        WR1_PROG(REG_1608H, 0x80010340U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x16280000U);
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
        r_rsip_func100(bswap_32big(0x601736b6U), bswap_32big(0x19fb0987U), bswap_32big(0x68ead324U),
                       bswap_32big(0x0bafc5cfU));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000220U);
            WR1_PROG(REG_1004H, 0x1818000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000630U);
            WR1_PROG(REG_1004H, 0x1818000cU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1600H, 0x00002fc0U);
            r_rsip_func101(bswap_32big(0x6b757ba9U), bswap_32big(0x333b00b6U), bswap_32big(0x0926d849U),
                           bswap_32big(0xdea75fecU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xc2fd8664U), bswap_32big(0x1607d0a7U), bswap_32big(0xce650d98U),
                           bswap_32big(0x44c5103cU));
            break;
        }
    }

    WR1_PROG(REG_1404H, 0x19700000U);
    WR1_PROG(REG_1400H, 0x00c000d1U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
    OFS_ADR = 56;
    WR1_PROG(REG_1404H, 0x19700000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000034U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003131U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x9f7b69d4U),
                   bswap_32big(0xda3ba583U),
                   bswap_32big(0xfb075510U),
                   bswap_32big(0xaa01f531U));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
    OFS_ADR = 112;
    WR1_PROG(REG_1404H, 0x19700000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000034U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003132U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x6a87e9d0U),
                   bswap_32big(0x17c15a85U),
                   bswap_32big(0x751d056dU),
                   bswap_32big(0x2d96f3fcU));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1404H, 0x19800000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000bdU);
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
    WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
    OFS_ADR = 0;
    WR1_PROG(REG_1404H, 0x19700000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000034U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003133U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xf30204aeU),
                   bswap_32big(0xe707b24cU),
                   bswap_32big(0x60e62817U),
                   bswap_32big(0xfc5cdffaU));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
    OFS_ADR = 168;
    WR1_PROG(REG_1404H, 0x19700000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000034U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003134U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xe847ce29U),
                   bswap_32big(0xc7ff1346U),
                   bswap_32big(0xb3798ac0U),
                   bswap_32big(0x66179da1U));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xf6428095U));
    OFS_ADR = 224;
    WR1_PROG(REG_1404H, 0x11600000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000030U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003135U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x60439d51U),
                   bswap_32big(0x6c02fbeaU),
                   bswap_32big(0xac8cd97dU),
                   bswap_32big(0xe3062ea0U));
    r_rsip_func016(OFS_ADR);
    WR1_PROG(REG_1404H, 0x15700000U);
    WR1_PROG(REG_1600H, 0x00000b7bU);
    WR1_PROG(REG_1608H, 0x80b0001bU);
    WR1_PROG(REG_1400H, 0x034300c1U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    while (1)
    {
        WR1_PROG(REG_1404H, 0x19800000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c000bdU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000838U);
        WR1_PROG(REG_1004H, 0x1818000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0xa4928d99U), bswap_32big(0x8ccb6d81U), bswap_32big(0xb273c1cdU),
                       bswap_32big(0xdb626188U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func101(bswap_32big(0xe052148bU), bswap_32big(0xf0ecd87bU), bswap_32big(0x5f593ca7U),
                           bswap_32big(0xac34cd3bU));
            break;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
            OFS_ADR = 0;
            WR1_PROG(REG_1404H, 0x13580000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003131U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x36c1d3aeU), bswap_32big(0xb1fd7c31U), bswap_32big(0x866d0b43U),
                           bswap_32big(0x8ae28132U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
            OFS_ADR = 56;
            WR1_PROG(REG_1404H, 0x19700000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003132U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x93695a66U), bswap_32big(0x1b406f63U), bswap_32big(0x49196257U),
                           bswap_32big(0x671b5c6bU));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003131U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x9271668aU), bswap_32big(0xef4f78ddU), bswap_32big(0xcada7454U),
                           bswap_32big(0xd8a8648fU));
            r_rsip_func314();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
            OFS_ADR = 0;
            WR1_PROG(REG_1404H, 0x13580000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003136U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x11c23b1fU), bswap_32big(0x462a935fU), bswap_32big(0xf30a0e6fU),
                           bswap_32big(0x7df428dfU));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
            OFS_ADR = 56;
            WR1_PROG(REG_1404H, 0x19700000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003137U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x9cefca6dU), bswap_32big(0x956fd979U), bswap_32big(0xf07c01d0U),
                           bswap_32big(0xa1542807U));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
            OFS_ADR = 112;
            WR1_PROG(REG_1404H, 0x13580000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003133U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x3b4efc9fU), bswap_32big(0x66f98bd7U), bswap_32big(0x2ce42495U),
                           bswap_32big(0xc0d2a9f1U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
            OFS_ADR = 168;
            WR1_PROG(REG_1404H, 0x19700000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003134U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xe7013b3eU), bswap_32big(0xa2c5ad8aU), bswap_32big(0x6d827c74U),
                           bswap_32big(0xf0770fa0U));
            r_rsip_func017(OFS_ADR);
            WR1_PROG(REG_1404H, 0x1f180000U);
            WR1_PROG(REG_1400H, 0x00c000c1U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000220U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000630U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003132U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x186cc5b7U), bswap_32big(0x7420d5a4U), bswap_32big(0xcfc756e2U),
                           bswap_32big(0xf9183b48U));
            r_rsip_func314();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
            OFS_ADR = 112;
            WR1_PROG(REG_1404H, 0x13580000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003138U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x29ce0bd2U), bswap_32big(0x4cdbcf3cU), bswap_32big(0x77ab84c0U),
                           bswap_32big(0x878595a7U));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0b040184U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
            OFS_ADR = 168;
            WR1_PROG(REG_1404H, 0x19700000U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000034U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003139U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xf75fd450U), bswap_32big(0x6079636fU), bswap_32big(0x8abd4af0U),
                           bswap_32big(0x8973d947U));
            r_rsip_func016(OFS_ADR);
            WR1_PROG(REG_1404H, 0x1f180000U);
            WR1_PROG(REG_1400H, 0x00c000c1U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000220U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000630U);
            WR1_PROG(REG_1004H, 0x18180009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x1818000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00a10000U);
            r_rsip_func100(bswap_32big(0xe300f11fU), bswap_32big(0x8b2e4275U), bswap_32big(0x0323bde9U),
                           bswap_32big(0xb705bcd9U));
            WR1_PROG(REG_143CH, 0x00400000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000fd8U);
                WR1_PROG(REG_1020H, 0x00000220U);
                WR1_PROG(REG_1004H, 0x18180009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003135U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x72449468U),
                               bswap_32big(0x97696a0aU),
                               bswap_32big(0x0e1e6703U),
                               bswap_32big(0x5f6d0728U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
                OFS_ADR = 112;
                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003136U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x41182fa3U),
                               bswap_32big(0xc99bbdb0U),
                               bswap_32big(0x334b6958U),
                               bswap_32big(0x644f9a03U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003131U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xbe82515aU),
                               bswap_32big(0x55489f24U),
                               bswap_32big(0x528e969bU),
                               bswap_32big(0x03f8f718U));
                r_rsip_func318();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313aU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x2b135aa0U),
                               bswap_32big(0x2e45d35eU),
                               bswap_32big(0x3c4e2ff2U),
                               bswap_32big(0x559e8e9aU));
                r_rsip_func016(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
                OFS_ADR = 56;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003137U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xfac50d60U),
                               bswap_32big(0x0576dd30U),
                               bswap_32big(0xc16c18a9U),
                               bswap_32big(0xd6a8f7c3U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
                OFS_ADR = 168;
                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003138U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xebaec341U),
                               bswap_32big(0xb6b145e3U),
                               bswap_32big(0x1a6814e4U),
                               bswap_32big(0x8f20f3aaU));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003132U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xac0accfbU),
                               bswap_32big(0xb717f228U),
                               bswap_32big(0xeaee71b3U),
                               bswap_32big(0x0f24f3cfU));
                r_rsip_func318();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
                OFS_ADR = 56;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313bU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xdad3dae3U),
                               bswap_32big(0x0c8e7e1bU),
                               bswap_32big(0x6e1a0d23U),
                               bswap_32big(0xbf77ba47U));
                r_rsip_func016(OFS_ADR);
                r_rsip_func101(bswap_32big(0x7df2e2d1U),
                               bswap_32big(0x72ae1bb1U),
                               bswap_32big(0xd8ca81e6U),
                               bswap_32big(0x189cf641U));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000630U);
                WR1_PROG(REG_1018H, 0x00000220U);
                WR1_PROG(REG_1020H, 0x00000630U);
                WR1_PROG(REG_1004H, 0x1818000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
                OFS_ADR = 112;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313aU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xa0c300c3U),
                               bswap_32big(0x289d5f26U),
                               bswap_32big(0x83278ddcU),
                               bswap_32big(0xde65c683U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xab580788U));
                OFS_ADR = 0;
                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313bU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb1a5c137U),
                               bswap_32big(0x4d82510aU),
                               bswap_32big(0x2afbd7f9U),
                               bswap_32big(0x7b036221U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003133U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xcf433d64U),
                               bswap_32big(0xdd50045cU),
                               bswap_32big(0x5e6b31f3U),
                               bswap_32big(0x44001b9fU));
                r_rsip_func318();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x4db9e5b0U));
                OFS_ADR = 112;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313cU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb9d83081U),
                               bswap_32big(0xcc17117aU),
                               bswap_32big(0x179ce4d6U),
                               bswap_32big(0xb0984394U));
                r_rsip_func016(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
                OFS_ADR = 168;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313cU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xf4a60cb1U),
                               bswap_32big(0x1071ad70U),
                               bswap_32big(0x494fb89cU),
                               bswap_32big(0xd25acd29U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xa277852fU));
                OFS_ADR = 56;
                WR1_PROG(REG_1404H, 0x1f080000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313dU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb6d74ebfU),
                               bswap_32big(0x70ee8bd8U),
                               bswap_32big(0x824af075U),
                               bswap_32big(0xc190dff2U));
                r_rsip_func017(OFS_ADR);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00003134U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb89562cfU),
                               bswap_32big(0x1d4c335aU),
                               bswap_32big(0x4acb6936U),
                               bswap_32big(0x1bd9ee01U));
                r_rsip_func318();
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0b040184U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
                OFS_ADR = 168;
                WR1_PROG(REG_1404H, 0x17680000U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000034U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000313dU));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xea0750fcU),
                               bswap_32big(0xec110227U),
                               bswap_32big(0xce067e1dU),
                               bswap_32big(0x2bfb6617U));
                r_rsip_func016(OFS_ADR);
                r_rsip_func101(bswap_32big(0x1f0d3f81U),
                               bswap_32big(0x126b48aaU),
                               bswap_32big(0x87efc409U),
                               bswap_32big(0x229c44bfU));
            }
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xf6428095U));
    OFS_ADR = 224;
    WR1_PROG(REG_1404H, 0x11600000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000030U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000313eU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xd6b7e1abU),
                   bswap_32big(0x3019af4aU),
                   bswap_32big(0xc68d9fd0U),
                   bswap_32big(0x053798a8U));
    r_rsip_func017(OFS_ADR);
    WR1_PROG(REG_1404H, 0x19800000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c000bdU);
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
        r_rsip_func100(bswap_32big(0x699e3e0dU), bswap_32big(0x3bf794f4U), bswap_32big(0xad74dc44U),
                       bswap_32big(0x04223bf8U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000630U);
            WR1_PROG(REG_1004H, 0x18180008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000220U);
            WR1_PROG(REG_1004H, 0x18180008U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1600H, 0x000033c0U);
            r_rsip_func101(bswap_32big(0x2206fab3U), bswap_32big(0x44f06b9bU), bswap_32big(0xa8e9eb51U),
                           bswap_32big(0x06e705cdU));
        }
        else
        {
            r_rsip_func101(bswap_32big(0x71e9a522U), bswap_32big(0x75f83d15U), bswap_32big(0x805eac24U),
                           bswap_32big(0x73853ef7U));
            break;
        }
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0xc447d111U));
    OFS_ADR = 168;
    WR1_PROG(REG_1404H, 0x17680000U);
    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000034U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000313fU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x2f926c08U),
                   bswap_32big(0xa43d848aU),
                   bswap_32big(0x7b7f81aaU),
                   bswap_32big(0xd98a8350U));
    r_rsip_func017(OFS_ADR);
    WR1_PROG(REG_1404H, 0x17680000U);
    WR1_PROG(REG_1608H, 0x80010360U);
    WR1_PROG(REG_1400H, 0x00030005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x03430005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    while (1)
    {
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000838U);
        WR1_PROG(REG_1020H, 0x00000a40U);
        WR1_PROG(REG_1004H, 0x1919000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0xa621e6aaU), bswap_32big(0x3fc6b52eU), bswap_32big(0x18bfb9a5U),
                       bswap_32big(0x76e5cecaU));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x1919000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x4c0ddd5aU), bswap_32big(0xbba73c23U), bswap_32big(0x72898d56U),
                           bswap_32big(0xc55e31d6U));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xeca9afafU), bswap_32big(0xeda04ec6U), bswap_32big(0xd7d96c40U),
                           bswap_32big(0x4b48a5b3U));
            break;
        }
    }

    WR1_PROG(REG_1600H, 0x3800db60U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xa60bfb3aU),
                   bswap_32big(0x8d4bd31cU),
                   bswap_32big(0xdf36912eU),
                   bswap_32big(0x07c6f6d5U));
    WR1_PROG(REG_143CH, 0x00400000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000838U);
        WR1_PROG(REG_1020H, 0x00000838U);
        WR1_PROG(REG_1004H, 0x1919000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        r_rsip_func101(bswap_32big(0x997b6084U), bswap_32big(0x4a9f74b8U), bswap_32big(0x68ef78b0U),
                       bswap_32big(0x7407aeafU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0x9db08274U), bswap_32big(0x56fcc2dfU), bswap_32big(0xa05cdb0cU),
                       bswap_32big(0x60fd4729U));
    }

    WR1_PROG(REG_1600H, 0x000037b9U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
