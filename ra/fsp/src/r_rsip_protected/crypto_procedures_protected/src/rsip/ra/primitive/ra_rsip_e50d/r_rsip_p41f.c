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

rsip_ret_t r_rsip_p41f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x4a000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0xd6118a6cU), bswap_32big(0xc28daa0eU), bswap_32big(0xe9bbcfa9U),
                       bswap_32big(0x1b84397cU));
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x5a000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x181a0deaU), bswap_32big(0xcfcfb706U), bswap_32big(0xc41434c6U),
                       bswap_32big(0xed9b60baU));
    }

    WR1_PROG(REG_1824H, 0x0c000045U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        r_rsip_func100(bswap_32big(0xbff2d496U), bswap_32big(0x1d097928U), bswap_32big(0x37f77fa6U),
                       bswap_32big(0x698f7f19U));
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x0e000505U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[0]);

        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0x8fd23867U), bswap_32big(0x1868bff9U), bswap_32big(0xcef01686U),
                       bswap_32big(0x972da3d4U));
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

        r_rsip_func100(bswap_32big(0xa63e5f17U), bswap_32big(0xe3de58b0U), bswap_32big(0xf57087d4U),
                       bswap_32big(0x4b2048e7U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x99f25e2fU), bswap_32big(0xdcbb3b70U), bswap_32big(0x0b00381dU),
                           bswap_32big(0x1733a148U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x0e000505U);
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

            r_rsip_func100(bswap_32big(0x8c41fff8U), bswap_32big(0x9c2c6192U), bswap_32big(0xfb507cb9U),
                           bswap_32big(0x9724068bU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x886a58a0U),
                               bswap_32big(0x6210ec96U),
                               bswap_32big(0xae928243U),
                               bswap_32big(0x029ba73eU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_AUTH_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x0a02398cU),
                               bswap_32big(0x2098c3b3U),
                               bswap_32big(0x45511380U),
                               bswap_32big(0xa43cdd13U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
