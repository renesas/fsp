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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_pf1 (const uint32_t InData_CurveType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00f10001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010340U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_CurveType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010380U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000bdeU);

    WR1_PROG(REG_1444H, 0x000017c7U);
    WR1_PROG(REG_1608H, 0x8098001eU);
    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Signature[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0U; iLoop < 8U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x00000bffU);

        WR1_PROG(REG_1600H, 0x30003380U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1600H, 0x0000d3e0U);
        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1600H, 0x0000381eU);
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1600H, 0x0000381eU);
        WR1_PROG(REG_1600H, 0x000037beU);
        WR1_PROG(REG_1600H, 0x0000a7a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000383dU);
        WR1_PROG(REG_1600H, 0x38001001U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x38000fffU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x0000a7c0U);
        WR1_PROG(REG_1600H, 0x00000020U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x30000f5aU);
    WR1_PROG(REG_1600H, 0x00030020U);
    WR1_PROG(REG_1600H, 0x0000d3e1U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1600H, 0x38000f9cU);
    WR1_PROG(REG_1600H, 0x1000d3e1U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x38008be0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x32c0ec7eU),
                   bswap_32big(0xc5cfc4c2U),
                   bswap_32big(0x983ebc39U),
                   bswap_32big(0xbe19ea41U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x6ed9e479U), bswap_32big(0x71ac82ceU), bswap_32big(0xef3a81deU),
                       bswap_32big(0x07c68c49U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        WR1_PROG(REG_1600H, 0x00000bdeU);
        WR1_PROG(REG_1608H, 0x8190001eU);

        WR1_PROG(REG_1404H, 0x19100000U);
        r_rsip_func_sub002(0x00c90021U);

        WR1_PROG(REG_1404H, 0x19600000U);
        r_rsip_func_sub002(0x00c90021U);

        WR1_PROG(REG_1A2CH, 0x00000100U);
        WR1_PROG(REG_1A24H, 0x08008107U);

        WR1_PROG(REG_1600H, 0x0000b7c0U);
        WR1_PROG(REG_1600H, 0x00000040U);
        WR1_PROG(REG_1608H, 0x8188001eU);
        r_rsip_func_sub002(0x00890021U);

        WR1_PROG(REG_1600H, 0x00000bdeU);
        WR1_PROG(REG_1608H, 0x8088001eU);
        r_rsip_func_sub002(0x03420021U);

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000f1U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x43bb13fcU), bswap_32big(0x182dfc39U), bswap_32big(0x14837629U),
                       bswap_32big(0x70afd34dU));
        r_rsip_func043();

        r_rsip_func075();

        WR1_PROG(REG_1600H, 0x000034feU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000f1U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x05370189U), bswap_32big(0x02cb3a6cU), bswap_32big(0x560dc9a8U),
                       bswap_32big(0x0ae6382bU));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x00000fc2U);
        WR1_PROG(REG_1A2CH, 0x40000300U);
        WR1_PROG(REG_1A24H, 0xe8009107U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1608H, 0x80900001U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);
        r_rsip_func_sub002(0x03420021U);

        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[13]);
        r_rsip_func_sub002(0x03420021U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[17]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        r_rsip_func_sub002(0x00820011U);

        r_rsip_func100(bswap_32big(0xb7566c0dU), bswap_32big(0x44124820U), bswap_32big(0xfb5c99e2U),
                       bswap_32big(0xd613fbcbU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x5833a262U), bswap_32big(0xeac3db6eU), bswap_32big(0x867651c0U),
                           bswap_32big(0x1fd00e06U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x000000f1U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x170e9b9bU), bswap_32big(0xe26ae30aU), bswap_32big(0x0fd80b76U),
                           bswap_32big(0xd870027bU));
            r_rsip_func073(InData_DomainParam);

            r_rsip_func100(bswap_32big(0x9c73f404U), bswap_32big(0x46eabcedU), bswap_32big(0xe064ec0aU),
                           bswap_32big(0xcd0b8b17U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x7cf25279U),
                               bswap_32big(0x39473330U),
                               bswap_32big(0x9dc1eed4U),
                               bswap_32big(0x708b9f32U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x639bee41U),
                               bswap_32big(0x035ece36U),
                               bswap_32big(0x77984a33U),
                               bswap_32big(0xc28f2853U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
