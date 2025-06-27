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

rsip_ret_t r_rsip_p73i (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
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
        WR1_PROG(REG_2004H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xd96bfc9eU), bswap_32big(0x487c02b2U), bswap_32big(0xfc75625fU),
                       bswap_32big(0x6053b6c3U));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00000040U);
        r_rsip_func101(bswap_32big(0xd82c8e37U), bswap_32big(0x57edf2f6U), bswap_32big(0x44321c10U),
                       bswap_32big(0x9549981fU));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00000050U);
        r_rsip_func101(bswap_32big(0x3aa12cabU), bswap_32big(0x7b307f76U), bswap_32big(0x8d4e154cU),
                       bswap_32big(0x61e17003U));
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00000080U);
        r_rsip_func101(bswap_32big(0xf197febfU), bswap_32big(0x0acf8d75U), bswap_32big(0x65ffcf05U),
                       bswap_32big(0xca09fd44U));
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x00000090U);
        r_rsip_func101(bswap_32big(0xf34ef58fU), bswap_32big(0x907ea3cfU), bswap_32big(0xa313eeecU),
                       bswap_32big(0x2445166eU));
    }
    else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x000000a0U);
        r_rsip_func101(bswap_32big(0x98d7fc97U), bswap_32big(0xa91c8662U), bswap_32big(0xb76231c5U),
                       bswap_32big(0xff218a00U));
    }
    else if (0x00000006U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_2004H, 0x000000b0U);
        r_rsip_func101(bswap_32big(0xd91630c6U), bswap_32big(0x254dddb8U), bswap_32big(0x87ef4539U),
                       bswap_32big(0x831051b2U));
    }

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_200CH, 0x00000100U);
        r_rsip_func101(bswap_32big(0xd7e4dd58U), bswap_32big(0x6deb38e7U), bswap_32big(0x38547147U),
                       bswap_32big(0xcea045caU));
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_ADDR(REG_2014H, &InData_MsgLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_ADDR(REG_2010H, &InData_MsgLen[1]);
        r_rsip_func101(bswap_32big(0xe64467f0U), bswap_32big(0x1ec38968U), bswap_32big(0xace088cfU),
                       bswap_32big(0xa6ae0529U));
    }

    return RSIP_RET_PASS;
}
