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

rsip_ret_t r_rsip_pb9f (const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_TextBitLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x000037c0U);
    WR1_PROG(REG_1600H, 0x00076bdeU);
    WR1_PROG(REG_1600H, 0x00026fdeU);

    WR1_PROG(REG_1600H, 0x00000bffU);

    WR1_PROG(REG_1600H, 0x38008c00U);
    WR1_PROG(REG_1600H, 0x0000007fU);
    WR1_PROG(REG_1600H, 0x00020020U);
    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1600H, 0x2000abc0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xd8da462dU),
                   bswap_32big(0x64e8df52U),
                   bswap_32big(0xf3f303edU),
                   bswap_32big(0xc5b50e63U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x10a0739dU), bswap_32big(0xf44c76c3U), bswap_32big(0x6fd15de3U),
                       bswap_32big(0xcb8731ecU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x862dc7faU), bswap_32big(0x787b6f87U), bswap_32big(0x11f98422U),
                       bswap_32big(0x76e2e398U));
        WR1_PROG(REG_1608H, 0x810103c0U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        r_rsip_func100(bswap_32big(0x5699d13eU), bswap_32big(0xcd62c1a9U), bswap_32big(0xc840f6ecU),
                       bswap_32big(0xc50dee50U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000020U);
        WR1_PROG(REG_1824H, 0x0d008906U);
        WR1_PROG(REG_1408H, 0x000c1000U);

        iLoop = 0;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);
            for (iLoop = 4U; iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
        }

        r_rsip_func214();

        WR1_PROG(REG_1600H, 0x38008c00U);
        WR1_PROG(REG_1600H, 0x0000007fU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0xcc939b6bU), bswap_32big(0x411b5dddU), bswap_32big(0x100593f7U),
                       bswap_32big(0x37eb763dU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000020U);
            WR1_PROG(REG_1824H, 0x0d008905U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[iLoop]);

            WR1_PROG(REG_1600H, 0x000008c6U);
            WR1_PROG(REG_1608H, 0x80840006U);
            WR1_PROG(REG_1400H, 0x03410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80840007U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 4]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 5]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 6]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 7]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b4a0U);
            WR1_PROG(REG_1600H, 0x00000004U);

            WR1_PROG(REG_1600H, 0x00003500U);
            WR1_PROG(REG_1600H, 0x00036908U);
            WR1_PROG(REG_1600H, 0x00008d00U);
            WR1_PROG(REG_1600H, 0x0000000cU);

            WR1_PROG(REG_1600H, 0x000024c8U);

            WR1_PROG(REG_1600H, 0x000024e8U);

            WR1_PROG(REG_1600H, 0x00003826U);

            WR1_PROG(REG_1600H, 0x00003847U);

            WR1_PROG(REG_1600H, 0x00003460U);
            WR1_PROG(REG_1600H, 0x00008c60U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x0000b480U);
            WR1_PROG(REG_1600H, 0xffffffffU);
            WR1_PROG(REG_1600H, 0x00004403U);
            WR1_PROG(REG_1600H, 0x00007484U);

            WR1_PROG(REG_1600H, 0x00000c24U);

            WR1_PROG(REG_1600H, 0x00001484U);

            WR1_PROG(REG_1600H, 0x00000c44U);

            WR1_PROG(REG_1600H, 0x00001041U);

            WR1_PROG(REG_1600H, 0x00003c47U);

            WR1_PROG(REG_1600H, 0x000037e0U);
            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x0000007fU);

            WR1_PROG(REG_1600H, 0x38008fe0U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x1000a7e0U);
            WR1_PROG(REG_1600H, 0x00000020U);

            WR1_PROG(REG_1600H, 0x0000b7c0U);
            WR1_PROG(REG_1600H, 0x00000080U);
            WR1_PROG(REG_1600H, 0x00002bdfU);
            WR1_PROG(REG_1600H, 0x00056bdeU);
            WR1_PROG(REG_1600H, 0x0000353eU);

            r_rsip_func100(bswap_32big(0xff177965U), bswap_32big(0x914bd92eU), bswap_32big(0x9a78c83eU),
                           bswap_32big(0x4b0de11eU));
            WR1_PROG(REG_1608H, 0x810103c0U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x000024c5U);
                WR1_PROG(REG_1600H, 0x000024e5U);

                WR1_PROG(REG_1600H, 0x00003ba6U);
                WR1_PROG(REG_1600H, 0x00003fa7U);

                WR1_PROG(REG_1600H, 0x000033c0U);
                r_rsip_func101(bswap_32big(0xdd4f6190U),
                               bswap_32big(0x14ac8090U),
                               bswap_32big(0xdd40cdcaU),
                               bswap_32big(0x3fd9c077U));
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000fdeU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            r_rsip_func100(bswap_32big(0xf9293b97U), bswap_32big(0x92ca72c6U), bswap_32big(0x8358603cU),
                           bswap_32big(0xfe7e5551U));
            WR1_PROG(REG_182CH, 0x40000020U);
            WR1_PROG(REG_1824H, 0x0d008905U);
            WR1_PROG(REG_1608H, 0x81840007U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Text[iLoop]);

            WR1_PROG(REG_1600H, 0x000008c6U);

            WR1_PROG(REG_1600H, 0x000024c8U);

            WR1_PROG(REG_1600H, 0x00003826U);

            WR1_PROG(REG_1600H, 0x00000c24U);

            WR1_PROG(REG_1600H, 0x00003c26U);

            WR1_PROG(REG_1600H, 0x00000bffU);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x000024c5U);

                WR1_PROG(REG_1600H, 0x00003fe6U);

                WR1_PROG(REG_1600H, 0x00003120U);
                r_rsip_func101(bswap_32big(0x9561c00eU),
                               bswap_32big(0x42e8cfc0U),
                               bswap_32big(0xa4aa5e1dU),
                               bswap_32big(0x3c8d3f9aU));
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000d29U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func100(bswap_32big(0xf5f442acU), bswap_32big(0xf05fc7f6U), bswap_32big(0x93a19d0aU),
                           bswap_32big(0x2e8bf6cfU));
            WR1_PROG(REG_1600H, 0x000008c6U);
            WR1_PROG(REG_1608H, 0x81840006U);
            WR1_PROG(REG_1408H, 0x00005012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 4]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 5]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 6]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 7]);

            r_rsip_func101(bswap_32big(0x8f844894U), bswap_32big(0x2dfc2660U), bswap_32big(0xb49bf75cU),
                           bswap_32big(0x60942927U));
        }

        r_rsip_func102(bswap_32big(0x7d891785U), bswap_32big(0xf92cdc48U), bswap_32big(0x9fa20882U),
                       bswap_32big(0x0598117eU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
