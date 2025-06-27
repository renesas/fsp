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

rsip_ret_t r_rsip_p73r (const uint32_t InData_HashType[], const uint32_t InData_State[])
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

    WR1_PROG(REG_1B00H, 0x00730001U);
    WR1_PROG(REG_144CH, 0x00000000U);
    r_rsip_func100(bswap_32big(0x10536e75U),
                   bswap_32big(0x331466a8U),
                   bswap_32big(0x7eefde91U),
                   bswap_32big(0xe28e803fU));
    WR1_PROG(REG_2000H, 0x00000001U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);
    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00001000U);
        r_rsip_func101(bswap_32big(0x2e718b88U), bswap_32big(0xdb4b75c2U), bswap_32big(0xb3a8b0acU),
                       bswap_32big(0xf3e09da0U));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00001040U);
        r_rsip_func101(bswap_32big(0xe379ab73U), bswap_32big(0x404c8b84U), bswap_32big(0xe6897dedU),
                       bswap_32big(0xf7ab42c5U));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00001050U);
        r_rsip_func101(bswap_32big(0x2316ff0eU), bswap_32big(0xc5fde60dU), bswap_32big(0x863172d9U),
                       bswap_32big(0xf9cc187eU));
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00001080U);
        r_rsip_func101(bswap_32big(0x11f65666U), bswap_32big(0x499bd4a0U), bswap_32big(0xd344b1f9U),
                       bswap_32big(0xf2a866a5U));
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00001090U);
        r_rsip_func101(bswap_32big(0xac484580U), bswap_32big(0xdefd0225U), bswap_32big(0x8430b2c6U),
                       bswap_32big(0xfbf4d22fU));
    }
    else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x000010a0U);
        r_rsip_func101(bswap_32big(0xf2ac21deU), bswap_32big(0xa6584e00U), bswap_32big(0xd0dcec5cU),
                       bswap_32big(0xac5f5b57U));
    }
    else if (0x00000006U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x000010b0U);
        r_rsip_func101(bswap_32big(0x20311c6cU), bswap_32big(0xfaa52075U), bswap_32big(0x4cabf318U),
                       bswap_32big(0xecbb34e5U));
    }

    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_ADDR(REG_2014H, &InData_State[18]);
    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_ADDR(REG_2010H, &InData_State[19]);
    for (iLoop = 0; iLoop < 18; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_ADDR(REG_2028H, &InData_State[iLoop + 0]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xafa17b39U),
                   bswap_32big(0x8c4f9b53U),
                   bswap_32big(0x049691c3U),
                   bswap_32big(0x4a78e698U));

    return RSIP_RET_PASS;
}
