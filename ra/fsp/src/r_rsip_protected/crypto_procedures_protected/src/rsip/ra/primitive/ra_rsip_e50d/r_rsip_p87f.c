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

rsip_ret_t r_rsip_p87f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    r_rsip_func100(bswap_32big(0x87eb6ebaU),
                   bswap_32big(0x3509b223U),
                   bswap_32big(0xc0a4899fU),
                   bswap_32big(0x59153b58U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x8f708f63U), bswap_32big(0x47c93bb7U), bswap_32big(0x7515dcbbU),
                       bswap_32big(0xaf6e04ecU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x4a008104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            r_rsip_func101(bswap_32big(0x3817102aU), bswap_32big(0xddc1c982U), bswap_32big(0xa6063cdcU),
                           bswap_32big(0x3de637faU));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x5a008104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            r_rsip_func101(bswap_32big(0x72dfc1e7U), bswap_32big(0x06620d71U), bswap_32big(0xe1b44debU),
                           bswap_32big(0x01a9f1c1U));
        }

        WR1_PROG(REG_1824H, 0x0c000045U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            r_rsip_func100(bswap_32big(0x49c21239U), bswap_32big(0x56a4ce69U), bswap_32big(0x1cf0f8b5U),
                           bswap_32big(0xcca99c3bU));
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x0e008505U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);

            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_DataT[0]);

            r_rsip_func102(bswap_32big(0x0cf911a1U), bswap_32big(0x72d726a6U), bswap_32big(0x72dd7dd0U),
                           bswap_32big(0x6848c90dU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010040U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DataTLen[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x3420a840U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x00000080U);
            WR1_PROG(REG_1600H, 0x34202862U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0x4c70d0d0U), bswap_32big(0x717f8565U), bswap_32big(0x709e9899U),
                           bswap_32big(0xe00dd203U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x46cf0a01U),
                               bswap_32big(0xa1cc7b23U),
                               bswap_32big(0x14f1edd1U),
                               bswap_32big(0x76787cd4U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_182CH, 0x40000010U);
                WR1_PROG(REG_1824H, 0x0e008505U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_Text[0]);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x80840001U);
                WR1_PROG(REG_1400H, 0x03410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x000034e2U);
                WR1_PROG(REG_1600H, 0x000568e7U);
                WR1_PROG(REG_1600H, 0x00026ce7U);

                WR1_PROG(REG_1600H, 0x00003827U);

                WR1_PROG(REG_1600H, 0x0000b4c0U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1600H, 0x00003402U);
                WR1_PROG(REG_1600H, 0x00008c00U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1600H, 0x000028c0U);
                WR1_PROG(REG_1600H, 0x00008cc0U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1600H, 0x00004406U);

                WR1_PROG(REG_1600H, 0x00007421U);
                WR1_PROG(REG_1600H, 0x00007821U);

                WR1_PROG(REG_1600H, 0x00003c27U);

                WR1_PROG(REG_1600H, 0x000034c2U);
                WR1_PROG(REG_1600H, 0x0000a4c0U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1600H, 0x000568c6U);

                WR1_PROG(REG_1600H, 0x000034e6U);
                WR1_PROG(REG_1600H, 0x00026ce7U);

                WR1_PROG(REG_1600H, 0x00000821U);

                for (iLoop = 0U; iLoop < 4U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x3420a8e0U);
                    WR1_PROG(REG_1600H, 0x0000000dU);
                    WR1_PROG(REG_1600H, 0x10003c27U);

                    WR1_PROG(REG_1600H, 0x1000a4e0U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1824H, 0x08000045U);
                WR1_PROG(REG_1608H, 0x81840001U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x9c000005U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_DataT[0]);

                r_rsip_func100(bswap_32big(0x03990d4fU),
                               bswap_32big(0x4fe64d63U),
                               bswap_32big(0x6f990fe0U),
                               bswap_32big(0x0aaf01a5U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xd291cd60U),
                                   bswap_32big(0xb5cb891cU),
                                   bswap_32big(0xd7819e89U),
                                   bswap_32big(0x94a13e4aU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_AUTH_FAIL;
                }
                else
                {
                    r_rsip_func102(bswap_32big(0x5ba60e6eU),
                                   bswap_32big(0xcb91a9c0U),
                                   bswap_32big(0x5ae38b39U),
                                   bswap_32big(0x2dd9e11cU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
