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

rsip_ret_t r_rsip_pe5e (const uint32_t InData_EncMsg[], uint32_t MAX_CNT2)
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(MAX_CNT2));
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000d08U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xb1896bd9U),
                   bswap_32big(0xa91c0f26U),
                   bswap_32big(0xaeb0a8bfU),
                   bswap_32big(0x94a1395aU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_EncMsg[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xc12bffadU), bswap_32big(0xefa1a2b5U), bswap_32big(0x993f55fcU),
                       bswap_32big(0x4613e8deU));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x01799093U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xfbda1c8aU), bswap_32big(0x5b3a2b82U), bswap_32big(0x0231fbb2U),
                       bswap_32big(0x1df93cb9U));
        r_rsip_func044();

        WAIT_STS(REG_2030H, 0, 1);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e501U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa258d38fU), bswap_32big(0x94adbc0dU), bswap_32big(0x74a32a5fU),
                       bswap_32big(0x143659e2U));
        r_rsip_func103();

        r_rsip_func100(bswap_32big(0xab76a25eU), bswap_32big(0xc89af2bfU), bswap_32big(0xc2c770ecU),
                       bswap_32big(0x6a6ca66aU));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c2000c4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x3027a54bU), bswap_32big(0xb93d2d09U), bswap_32big(0x4a9c61ccU),
                       bswap_32big(0xd3a79ac9U));
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);
        OFS_ADR  = S_RAM[0];

        WR1_PROG(REG_1600H, 0x0000a900U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1600H, 0x00026908U);

        WR1_PROG(REG_1600H, 0x00000929U);

        for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_EncMsg[1 + iLoop]);

            r_rsip_func100(bswap_32big(0x0804c50cU), bswap_32big(0x1336dbb5U), bswap_32big(0xa981bc60U),
                           bswap_32big(0xbe7903a7U));
            WR1_PROG(REG_1824H, 0xe7040d05U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &S_HEAP[iLoop]);

            WR1_PROG(REG_1600H, 0x00002d20U);

            r_rsip_func101(bswap_32big(0x3ac3c074U), bswap_32big(0x51e374b3U), bswap_32big(0xb929cf87U),
                           bswap_32big(0x26464566U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x11f013b6U), bswap_32big(0xd6573539U), bswap_32big(0xbe2315baU),
                       bswap_32big(0x2ceaac82U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x0c000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1824H, 0x09140105U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &S_HEAP[iLoop]);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncMsg[OFS_ADR - 4]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x0c8ea856U), bswap_32big(0x41a67e36U), bswap_32big(0xb14d5042U),
                       bswap_32big(0xcadf5d71U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func101(bswap_32big(0xd025a147U), bswap_32big(0xc746a03dU), bswap_32big(0xbefde3feU),
                           bswap_32big(0x758aaa01U));

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000044U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000054U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1600H, 0x3800a900U);
            WR1_PROG(REG_1600H, 0x00000005U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xd72edd61U), bswap_32big(0x0a711c0fU), bswap_32big(0x19cb9fd1U),
                           bswap_32big(0xb25bddbcU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000929U);

                for (iLoop = 0U; iLoop < S_RAM[0] - 9; )
                {
                    WR1_PROG(REG_1444H, 0x000003c1U);
                    WR1_PROG(REG_1824H, 0xf7040d05U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);
                    WR1_PROG(REG_1400H, 0x01410011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002d20U);

                    r_rsip_func101(bswap_32big(0x0dab4927U),
                                   bswap_32big(0xd02d1833U),
                                   bswap_32big(0x518a5a85U),
                                   bswap_32big(0x4cdc3d6aU));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000037e8U);
                WR1_PROG(REG_1600H, 0x000033e0U);
                WR1_PROG(REG_1600H, 0x38000be9U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0xf7040d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);
                WR1_PROG(REG_1400H, 0x01410005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0001000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                iLoop = iLoop + 4;

                r_rsip_func101(bswap_32big(0x57043d22U),
                               bswap_32big(0xa0d5491aU),
                               bswap_32big(0x66f0e4bfU),
                               bswap_32big(0x168a271eU));
            }
            else
            {
                WR1_PROG(REG_1600H, 0x00000929U);

                for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
                {
                    WR1_PROG(REG_1444H, 0x000003c1U);
                    WR1_PROG(REG_1824H, 0xf7040d05U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);
                    WR1_PROG(REG_1400H, 0x01410011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002d20U);

                    r_rsip_func101(bswap_32big(0x942bfd40U),
                                   bswap_32big(0x6607090aU),
                                   bswap_32big(0x9dd1a346U),
                                   bswap_32big(0x128d6cb2U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000909U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x5df4da92U),
                               bswap_32big(0x093b4a45U),
                               bswap_32big(0x6148ead7U),
                               bswap_32big(0x6a6ad0c5U));
            }

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x07040d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);

            WR1_PROG(REG_1824H, 0x8c100005U);
            WR1_PROG(REG_1400H, 0x00410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xfd9d845cU), bswap_32big(0xc4400d41U), bswap_32big(0x0b42e199U),
                           bswap_32big(0x77133469U));

            WR1_PROG(REG_1408H, 0x00020000U);

            r_rsip_func101(bswap_32big(0x5510ea78U), bswap_32big(0x12d5fdceU), bswap_32big(0x30e3f9a1U),
                           bswap_32big(0xdd405250U));

            return RSIP_RET_PASS;
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0x7be6d59aU), bswap_32big(0x660960d3U), bswap_32big(0x1385e7fdU),
                       bswap_32big(0x1f28b2a5U));

        return RSIP_RET_PASS;
    }
}
