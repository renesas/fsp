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

rsip_ret_t r_rsip_p89i (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00890001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000089U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf8b3ad50U),
                   bswap_32big(0xaae92652U),
                   bswap_32big(0x92a4d7bfU),
                   bswap_32big(0x4738924cU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000089U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x7797b6acU),
                   bswap_32big(0xeb7d5ae5U),
                   bswap_32big(0x877c27f5U),
                   bswap_32big(0x6a4ddb2eU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x33d0ca40U),
                   bswap_32big(0xf22a1ef8U),
                   bswap_32big(0xe2bd9e9bU),
                   bswap_32big(0xb2b7f41dU));
    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

    WR1_PROG(REG_1824H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x65791523U),
                   bswap_32big(0x68594a89U),
                   bswap_32big(0x25b88bbeU),
                   bswap_32big(0xdc9e028cU));
    WR1_PROG(REG_1824H, 0x08000095U);
    WR1_PROG(REG_1400H, 0x00420011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x407cc6fdU),
                   bswap_32big(0xf424a300U),
                   bswap_32big(0x2604c437U),
                   bswap_32big(0xc6e20074U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x851d8212U), bswap_32big(0xb502ddb3U), bswap_32big(0x8e1696f6U),
                       bswap_32big(0x9a2bccddU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1608H, 0x80010000U);
        WR1_PROG(REG_1444H, 0x000000c7U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Cmd[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3000a800U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00000080U);

        r_rsip_func100(bswap_32big(0xad284ee0U), bswap_32big(0x72780197U), bswap_32big(0x90692935U),
                       bswap_32big(0xdc6473ceU));
        WR1_PROG(REG_1600H, 0x00007c00U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func101(bswap_32big(0x82815d8eU), bswap_32big(0x61338f74U), bswap_32big(0x5d1b531aU),
                           bswap_32big(0x94408b0fU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func101(bswap_32big(0xb1c69c16U), bswap_32big(0x9517a426U), bswap_32big(0x2211c437U),
                           bswap_32big(0x187a2584U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0xb1127db0U), bswap_32big(0xb0c739f0U), bswap_32big(0x6939a0d4U),
                           bswap_32big(0x8ee7d7edU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x972cfb65U), bswap_32big(0x40f1dff4U), bswap_32big(0x1ce6c7dfU),
                           bswap_32big(0xee17ecddU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0x5e044856U), bswap_32big(0x7c62990fU), bswap_32big(0x2425c353U),
                           bswap_32big(0x0121188dU));
        }
        else
        {
            ;
        }

        return RSIP_RET_PASS;
    }
}
