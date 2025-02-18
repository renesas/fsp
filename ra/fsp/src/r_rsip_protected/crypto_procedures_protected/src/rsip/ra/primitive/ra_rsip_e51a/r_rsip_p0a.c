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

rsip_ret_t r_rsip_p0a(uint32_t OutData_KeyIndex[])
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
    if (0x0U != RD1_MASK(REG_14BCH, 0x1fU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    WR1_PROG(REG_1B00H, 0x000a0001U);
    WR1_PROG(REG_144CH, 0x00000000U);
    r_rsip_func100(bswap_32big(0xa607d8b9U), bswap_32big(0xa337cbd5U), bswap_32big(0xe3eb541fU), bswap_32big(0xc6ead19aU));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1600H, 0x000034e0U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000000aU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x8d3a94bdU), bswap_32big(0xdc0f9284U), bswap_32big(0xf4d3813fU), bswap_32big(0x86262844U));
    r_rsip_func043();
    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000001aU);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000000aU));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x1efeae3cU), bswap_32big(0x01f0f7dcU), bswap_32big(0x215f8d58U), bswap_32big(0x807b3d17U));
    r_rsip_func044();
    r_rsip_func100(bswap_32big(0x57ee6a4bU), bswap_32big(0xf23b2c01U), bswap_32big(0xb6225974U), bswap_32big(0x78482520U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30U, 1U);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);
    r_rsip_func100(bswap_32big(0x58b6ccc3U), bswap_32big(0x2a1601d3U), bswap_32big(0xab17850cU), bswap_32big(0xdd442b76U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1608H, 0x80080000U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    r_rsip_func100(bswap_32big(0xbd66f90aU), bswap_32big(0x035e44bcU), bswap_32big(0x7d8d4418U), bswap_32big(0x0d5bd498U));
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    r_rsip_func100(bswap_32big(0x874d926aU), bswap_32big(0xab755bcbU), bswap_32big(0x20cfe03eU), bswap_32big(0x4922a282U));
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xe7009d47U);
    WR1_PROG(REG_1608H, 0x81070000U);
    WR1_PROG(REG_1400H, 0x0089001dU);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00800005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1444H, 0x000003a2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    WR1_PROG(REG_1408H, 0x00002032U);
    WAIT_STS(REG_1408H, 30U, 1U);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[1]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[2]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[3]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[4]);
    WAIT_STS(REG_1408H, 30U, 1U);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[5]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[6]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[7]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[8]);
    WAIT_STS(REG_1408H, 30U, 1U);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[9]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[10]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[11]);
    RD1_ADDR(REG_1420H, &OutData_KeyIndex[12]);
    r_rsip_func102(bswap_32big(0xfb875bc3U), bswap_32big(0xdddd4e04U), bswap_32big(0xc5daa5beU), bswap_32big(0x8ee61d28U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12U, 0U);
    return RSIP_RET_PASS;
}
