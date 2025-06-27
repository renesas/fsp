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

void r_rsip_func312 (void)
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
    WR1_PROG(REG_1600H, 0x0000379dU);
    WR1_PROG(REG_1600H, 0x00000842U);
    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1404H, 0x18380000U);
    WR1_PROG(REG_1400H, 0x00c00661U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1608H, 0x80a00004U);
    WR1_PROG(REG_1400H, 0x03400081U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    for (oLoop = 0; oLoop < 3; oLoop++)
    {
        WR1_PROG(REG_1404H, 0x18380000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0x1a696e5fU), bswap_32big(0xc828001cU), bswap_32big(0xec6dd6caU),
                       bswap_32big(0xe8f80945U));
        WR1_PROG(REG_1600H, 0x00007c02U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_1018H, 0x000008c0U);
            WR1_PROG(REG_1020H, 0x00000e98U);
            WR1_PROG(REG_1004H, 0x10100009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x540e146cU), bswap_32big(0xfad7dd2dU), bswap_32big(0xa0cae7b4U),
                           bswap_32big(0x4898d8d3U));
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1014H, 0x000001a0U);
            WR1_PROG(REG_1018H, 0x000008c0U);
            WR1_PROG(REG_1020H, 0x00000e98U);
            WR1_PROG(REG_1004H, 0x10100009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x078b9536U), bswap_32big(0xea684953U), bswap_32big(0x794ecce8U),
                           bswap_32big(0xa6855652U));
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1014H, 0x00000120U);
            WR1_PROG(REG_1018H, 0x000008c0U);
            WR1_PROG(REG_1020H, 0x00000e98U);
            WR1_PROG(REG_1004H, 0x10100009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0xbc588686U), bswap_32big(0xf6ac8a2aU), bswap_32big(0xc88d5d35U),
                           bswap_32big(0x56e4a25aU));
        }

        WR1_PROG(REG_1014H, 0x00000838U);
        WR1_PROG(REG_1018H, 0x000008c0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e98U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000948U);
        WR1_PROG(REG_1020H, 0x00000948U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1d080000U);
        WR1_PROG(REG_1400H, 0x00c00081U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x000008c8U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000ae8U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x18380000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x1d080000U);
        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1608H, 0x81a00004U);
        WR1_PROG(REG_1400H, 0x00c90081U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000948U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100007U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000d88U);
        WR1_PROG(REG_1018H, 0x000008c0U);
        WR1_PROG(REG_1020H, 0x00000e10U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000630U);
        WR1_PROG(REG_1018H, 0x000008c0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e10U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000948U);
        WR1_PROG(REG_1020H, 0x00000948U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x19480000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x000007b8U);
        WR1_PROG(REG_1018H, 0x000009d0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e98U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000a58U);
        WR1_PROG(REG_1020H, 0x00000a58U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1c780000U);
        WR1_PROG(REG_1400H, 0x00c00111U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000ae8U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000a58U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000a58U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x000009d8U);
        WR1_PROG(REG_1018H, 0x00000d00U);
        WR1_PROG(REG_1020H, 0x00000bf8U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x19480000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x000005b0U);
        WR1_PROG(REG_1018H, 0x000009d0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e10U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000a58U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x000008c8U);
        WR1_PROG(REG_1018H, 0x000009d0U);
        WR1_PROG(REG_1020H, 0x00000948U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x18380000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000d88U);
        WR1_PROG(REG_1018H, 0x00000948U);
        WR1_PROG(REG_1020H, 0x00000948U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x000008c8U);
        WR1_PROG(REG_1018H, 0x000009d0U);
        WR1_PROG(REG_1020H, 0x000009d8U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1a580000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000738U);
        WR1_PROG(REG_1018H, 0x00000ae0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e98U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000b68U);
        WR1_PROG(REG_1020H, 0x00000b68U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1c780000U);
        WR1_PROG(REG_1400H, 0x00c00111U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000bf8U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000b68U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_1020H, 0x00000b68U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000ae8U);
        WR1_PROG(REG_1018H, 0x00000d00U);
        WR1_PROG(REG_1020H, 0x000008c8U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1a580000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000530U);
        WR1_PROG(REG_1018H, 0x00000ae0U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000e10U);
        WR1_PROG(REG_1018H, 0x00000d88U);
        WR1_PROG(REG_101CH, 0x00000b68U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x1010000dU);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x000009d8U);
        WR1_PROG(REG_1018H, 0x00000ae0U);
        WR1_PROG(REG_1020H, 0x00000a58U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x19480000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000d88U);
        WR1_PROG(REG_1018H, 0x00000a58U);
        WR1_PROG(REG_1020H, 0x00000a58U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x000009d8U);
        WR1_PROG(REG_1018H, 0x00000ae0U);
        WR1_PROG(REG_1020H, 0x00000ae8U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1c780000U);
        WR1_PROG(REG_1400H, 0x00c00111U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x000008c8U);
        WR1_PROG(REG_1018H, 0x00000d00U);
        WR1_PROG(REG_1020H, 0x00000d88U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000ae8U);
        WR1_PROG(REG_1018H, 0x00000d00U);
        WR1_PROG(REG_1020H, 0x00000c78U);
        WR1_PROG(REG_1004H, 0x10100009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1b680000U);
        WR1_PROG(REG_1400H, 0x00c00091U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000d88U);
        WR1_PROG(REG_1018H, 0x00000c78U);
        WR1_PROG(REG_1020H, 0x00000e98U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x1d080000U);
        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x81a00004U);
        WR1_PROG(REG_1400H, 0x00c90081U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000d88U);
        WR1_PROG(REG_1018H, 0x00000e98U);
        WR1_PROG(REG_1020H, 0x00000b68U);
        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x80a00004U);
        WR1_PROG(REG_1404H, 0x1a680000U);
        WR1_PROG(REG_1400H, 0x03430081U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x00002c40U);
        r_rsip_func101(bswap_32big(0xa3821c57U), bswap_32big(0x1f2d8810U), bswap_32big(0x2b32ccfbU),
                       bswap_32big(0xe9c5b595U));
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000843U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1014H, 0x00000a58U);
    WR1_PROG(REG_1018H, 0x00000d00U);
    WR1_PROG(REG_1020H, 0x000008c8U);
    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000f312U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xa02039fdU),
                   bswap_32big(0x7a3bd2e7U),
                   bswap_32big(0xa4e1b28bU),
                   bswap_32big(0x4cc8e0dbU));
    r_rsip_func311();
    WR1_PROG(REG_1600H, 0x000037bcU);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
