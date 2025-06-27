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

rsip_ret_t r_rsip_p90 (const uint32_t InData_KeyType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_WrappedKeyType[],
                       const uint32_t InData_Text[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       WRAPPED_KEY_SIZE,
                       uint32_t       KEY_INDEX_SIZE)
{
    uint32_t iLoop = 0U;
    int32_t  jLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00900001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_WrappedKeyType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000bffU);

    WR1_PROG(REG_1600H, 0x00003409U);

    WR1_PROG(REG_1600H, 0x3420a900U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);

    WR1_PROG(REG_1600H, 0x38008940U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00030020U);
    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x1000d3e1U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x38008be0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xad66c77fU),
                   bswap_32big(0x3d58a044U),
                   bswap_32big(0x7177f584U),
                   bswap_32big(0xaaaca63aU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x53dd04acU), bswap_32big(0x2687190cU), bswap_32big(0x19117b61U),
                       bswap_32big(0x2450fea0U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00009001U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x6df902f9U), bswap_32big(0x8fdd71f6U), bswap_32big(0xc334a2a2U),
                       bswap_32big(0x98fd07f4U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x38000d08U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0xc67dcc4fU), bswap_32big(0xbf0b42d2U), bswap_32big(0x1ba21cb8U),
                       bswap_32big(0xd0848d2bU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000005U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00009001U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x71a4d79dU), bswap_32big(0x19fd9f09U), bswap_32big(0x8a323c35U),
                           bswap_32big(0x16e814dfU));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x97a9554eU), bswap_32big(0xb7ed34d5U), bswap_32big(0x63433838U),
                           bswap_32big(0xded20c05U));
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_182CH, 0x00000000U);

            r_rsip_func101(bswap_32big(0x88a11ba8U), bswap_32big(0x25d2dd49U), bswap_32big(0xc54547e5U),
                           bswap_32big(0xb5e51761U));
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000007U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00009002U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x976d8b53U), bswap_32big(0x4cdebaeeU), bswap_32big(0x2117aa2eU),
                           bswap_32big(0x6bfeccceU));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x2c4b16b2U), bswap_32big(0xc212d40aU), bswap_32big(0xde528630U),
                           bswap_32big(0xe71e6ac1U));
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

            r_rsip_func100(bswap_32big(0xcd4d0f80U), bswap_32big(0x1ee104bcU), bswap_32big(0x8c7c1df8U),
                           bswap_32big(0xdcce2de5U));
            WR1_PROG(REG_1824H, 0x08000095U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

            WR1_PROG(REG_182CH, 0x40000000U);

            r_rsip_func101(bswap_32big(0x6954764aU), bswap_32big(0x1e9645f4U), bswap_32big(0x2fa7f32cU),
                           bswap_32big(0x4a62ae8cU));
        }

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xd662c849U), bswap_32big(0xe7917962U), bswap_32big(0xe9c510afU),
                       bswap_32big(0xdb7207c6U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x7e8b4a58U), bswap_32big(0x3b9b4932U), bswap_32big(0xa71d5890U),
                           bswap_32big(0x220057e4U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            r_rsip_func030();

            WR1_PROG(REG_1600H, 0x00002ca0U);

            WR1_PROG(REG_1600H, 0x000035c7U);

            WR1_PROG(REG_1444H, 0x000001c7U);
            WR1_PROG(REG_1608H, 0x80020000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[1]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b7e0U);
            WR1_PROG(REG_1600H, 0x00000008U);

            WR1_PROG(REG_1600H, 0x00000bdeU);
            WR1_PROG(REG_1600H, 0x00002fc0U);

            WR1_PROG(REG_1600H, 0x0000b780U);
            WR1_PROG(REG_1600H, 0x00000008U);

            for (iLoop = 2; iLoop < WRAPPED_KEY_SIZE; )
            {
                WR1_PROG(REG_1444H, 0x000001c7U);
                WR1_PROG(REG_1608H, 0x8082001fU);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Text[iLoop]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Text[iLoop + 1]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000027fcU);

                WR1_PROG(REG_1600H, 0x00002fc0U);

                r_rsip_func101(bswap_32big(0xe32ea363U),
                               bswap_32big(0x7ef18789U),
                               bswap_32big(0xfeeb6aaaU),
                               bswap_32big(0x415870dfU));
                iLoop = iLoop + 2;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000bc5U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000377fU);
            WR1_PROG(REG_1600H, 0x0000ab60U);
            WR1_PROG(REG_1600H, 0x00000008U);

            WR1_PROG(REG_1600H, 0x00003785U);
            WR1_PROG(REG_1600H, 0x00003380U);

            WR1_PROG(REG_1600H, 0x0000349cU);
            WR1_PROG(REG_1600H, 0x00026c84U);
            WR1_PROG(REG_1600H, 0x00016f9cU);
            WR1_PROG(REG_1600H, 0x0000249cU);

            WR1_PROG(REG_1600H, 0x00000bdeU);

            WR1_PROG(REG_1600H, 0x0000b720U);
            WR1_PROG(REG_1600H, 0x00000004U);

            WR1_PROG(REG_1600H, 0x0000b740U);
            WR1_PROG(REG_1600H, 0x0000000cU);

            WR1_PROG(REG_1600H, 0x00003785U);
            WR1_PROG(REG_1600H, 0x00003380U);

            for (jLoop = 5; jLoop >= 0; jLoop = jLoop - 1)
            {
                WR1_PROG(REG_1600H, 0x000037fbU);

                WR1_PROG(REG_1600H, 0x00000bbdU);

                for (iLoop = (WRAPPED_KEY_SIZE / 2) - 1; iLoop >= 1; iLoop = iLoop - 1)
                {
                    WR1_PROG(REG_1600H, 0x00000824U);

                    WR1_PROG(REG_1824H, 0x0a00810dU);
                    WR1_PROG(REG_1608H, 0x81020000U);
                    WR1_PROG(REG_1400H, 0x00490009U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1608H, 0x8182001fU);
                    WR1_PROG(REG_1400H, 0x00490009U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1608H, 0x80040000U);
                    WR1_PROG(REG_1400H, 0x03410011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00003c5fU);
                    WR1_PROG(REG_1600H, 0x000027f9U);
                    WR1_PROG(REG_1600H, 0x00003c7fU);
                    WR1_PROG(REG_1600H, 0x00002bfaU);

                    WR1_PROG(REG_1600H, 0x00003080U);

                    WR1_PROG(REG_1600H, 0x00002fa0U);

                    r_rsip_func101(bswap_32big(0xcb6a02e1U),
                                   bswap_32big(0xf88fab4fU),
                                   bswap_32big(0x1fe350eeU),
                                   bswap_32big(0x32a572beU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000bbcU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00002fc0U);

                r_rsip_func101(bswap_32big(0xa540fd47U),
                               bswap_32big(0x45625612U),
                               bswap_32big(0x80525ae6U),
                               bswap_32big(0xc9c79756U));
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38008bc0U);
            WR1_PROG(REG_1600H, 0x00000006U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38008800U);
            WR1_PROG(REG_1600H, 0xa6a6a6a6U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0xa6a6a6a6U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            r_rsip_func100(bswap_32big(0xeedf8f42U), bswap_32big(0x3e20cbb6U), bswap_32big(0x83827a1dU),
                           bswap_32big(0x013c7fbcU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x0a3b2562U),
                               bswap_32big(0x888edb8cU),
                               bswap_32big(0x08a8aae0U),
                               bswap_32big(0x84120fb9U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000090U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xfeb36c48U),
                               bswap_32big(0xac56c762U),
                               bswap_32big(0xb8f9255dU),
                               bswap_32big(0xe9b4b8e6U));
                r_rsip_func103();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0c200104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1608H, 0x80010000U);
                WR1_PROG(REG_1400H, 0x03420005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x000034e0U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00009002U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xf32a56abU),
                               bswap_32big(0x1995610bU),
                               bswap_32big(0xb14ed73aU),
                               bswap_32big(0x405ebba5U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x000034e6U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00009003U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xd231b630U),
                               bswap_32big(0xaab41079U),
                               bswap_32big(0xd7808171U),
                               bswap_32big(0xca2e20a9U));
                r_rsip_func044();

                WR1_PROG(REG_1600H, 0x000034eeU);

                WR1_PROG(REG_1600H, 0x0000b7e0U);
                WR1_PROG(REG_1600H, 0x00000008U);

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000044U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1600H, 0x00000bdeU);

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00000004U);

                WR1_PROG(REG_1600H, 0x0000b780U);
                WR1_PROG(REG_1600H, 0x00000010U);

                WR1_PROG(REG_1600H, 0x0000a8e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
                {
                    WR1_PROG(REG_1600H, 0x000008c6U);
                    WR1_PROG(REG_1600H, 0x34202bc7U);
                    WR1_PROG(REG_1600H, 0x2000d0c0U);

                    WR1_PROG(REG_1600H, 0x00007c06U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0xb16f7bf8U),
                                   bswap_32big(0xa92cda17U),
                                   bswap_32big(0xebb4c7e2U),
                                   bswap_32big(0x6918513aU));
                    WR1_PROG(REG_1444H, 0x000003c2U);
                    WR1_PROG(REG_1A2CH, 0x40000000U);
                    WR1_PROG(REG_1A24H, 0xe7008d05U);

                    WR1_PROG(REG_1608H, 0x8184001fU);
                    WR1_PROG(REG_1400H, 0x00890011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002012U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 1]);

                    WR1_PROG(REG_1600H, 0x000027fcU);

                    WR1_PROG(REG_1600H, 0x000027dbU);

                    r_rsip_func101(bswap_32big(0x5e610fafU),
                                   bswap_32big(0x48fe9b73U),
                                   bswap_32big(0xf4a55d6cU),
                                   bswap_32big(0xd8840f81U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000bc7U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0xf2af22c3U),
                               bswap_32big(0x971f99baU),
                               bswap_32big(0x6e689b1aU),
                               bswap_32big(0x2b1cbfbbU));
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0c000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x09108105U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1408H, 0x00002012U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 1]);

                r_rsip_func100(bswap_32big(0x905de4baU),
                               bswap_32big(0xd744a462U),
                               bswap_32big(0xf7df0b72U),
                               bswap_32big(0x09349832U));
                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                r_rsip_func102(bswap_32big(0xa33f3031U),
                               bswap_32big(0xc68a2934U),
                               bswap_32big(0x3bfc0b83U),
                               bswap_32big(0x78b48cbfU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
