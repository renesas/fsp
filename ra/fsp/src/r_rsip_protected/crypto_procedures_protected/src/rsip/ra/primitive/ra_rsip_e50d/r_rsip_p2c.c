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

rsip_ret_t r_rsip_p2c (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x002c0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000002cU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xe4550b41U),
                   bswap_32big(0x816b27d7U),
                   bswap_32big(0xa6f03cf4U),
                   bswap_32big(0x1b2b8f33U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000005U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000002cU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x739f6269U),
                   bswap_32big(0xed55ff32U),
                   bswap_32big(0xe94789c6U),
                   bswap_32big(0x0b4d7a23U));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xf7009d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1608H, 0x80840001U);
    WR1_PROG(REG_1400H, 0x03420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xf3c4df08U),
                   bswap_32big(0xde01e9caU),
                   bswap_32big(0x5029ab3eU),
                   bswap_32big(0xeb6fb089U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd050af91U), bswap_32big(0x30204a38U), bswap_32big(0xfc8aff57U),
                       bswap_32big(0x74abc66fU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Cmd[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0xe03a2d32U), bswap_32big(0x4adbe643U), bswap_32big(0xed83b415U),
                       bswap_32big(0x1e3150d3U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func100(bswap_32big(0x174b3bd9U), bswap_32big(0xa2e47267U), bswap_32big(0x916bd729U),
                           bswap_32big(0xc3ad8ce1U));
            WR1_PROG(REG_1438H, 0x40000100U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1400H, 0x02090005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xe4c00074U), bswap_32big(0x4ab4eeafU), bswap_32big(0x8559c79dU),
                           bswap_32big(0x5ef97923U));
            WR1_PROG(REG_1438H, 0x40000110U);

            WR1_PROG(REG_1400H, 0x02000011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xf8616aa7U), bswap_32big(0x11740f54U), bswap_32big(0x39f759edU),
                           bswap_32big(0xcd4da9d5U));
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1400H, 0x02090011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000001c7U);
            WR1_PROG(REG_1608H, 0x80020000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DOTFSEED[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DOTFSEED[1]);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func100(bswap_32big(0x27c0282fU), bswap_32big(0x32f39a5aU), bswap_32big(0x56c075a5U),
                           bswap_32big(0xf8dcf7ceU));
            WR1_PROG(REG_1438H, 0x40000140U);

            WR1_PROG(REG_1608H, 0x81020000U);
            WR1_PROG(REG_1400H, 0x02090009U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func102(bswap_32big(0xba34c0a9U), bswap_32big(0x430780daU), bswap_32big(0x045b7abdU),
                           bswap_32big(0x1be1add3U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x8274ca82U), bswap_32big(0x50cb6da3U), bswap_32big(0x5eb6eba0U),
                           bswap_32big(0xa00f4d02U));
            WR1_PROG(REG_1438H, 0x40000180U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1400H, 0x02090005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xb6e426c5U), bswap_32big(0x33b03187U), bswap_32big(0xaeea656aU),
                           bswap_32big(0xb444159cU));
            WR1_PROG(REG_1438H, 0x40000190U);

            WR1_PROG(REG_1400H, 0x02000011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xa6359915U), bswap_32big(0xf89cce2aU), bswap_32big(0xe36bf9e4U),
                           bswap_32big(0xa318b87aU));
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1400H, 0x02090011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000001c7U);
            WR1_PROG(REG_1608H, 0x80020000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DOTFSEED[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DOTFSEED[1]);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func100(bswap_32big(0x27461ddbU), bswap_32big(0xb596838cU), bswap_32big(0x3d10e96dU),
                           bswap_32big(0x21df5c70U));
            WR1_PROG(REG_1438H, 0x400001C0U);

            WR1_PROG(REG_1608H, 0x81020000U);
            WR1_PROG(REG_1400H, 0x02090009U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func102(bswap_32big(0x71a30a73U), bswap_32big(0x6d12ae73U), bswap_32big(0x75b581f1U),
                           bswap_32big(0x1b42f29dU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
