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

rsip_ret_t r_rsip_p97f (const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        uint32_t       OutData_Text[],
                        uint32_t       OutData_DataT[],
                        uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    r_rsip_func100(bswap_32big(0x4f97827cU),
                   bswap_32big(0x3197bb3bU),
                   bswap_32big(0xbf3cb88dU),
                   bswap_32big(0xfefa1498U));

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010020U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, MAX_CNT);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1608H, 0x81010020U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    r_rsip_func100(bswap_32big(0x39004fa3U),
                   bswap_32big(0xce9d2ef8U),
                   bswap_32big(0x6fa63133U),
                   bswap_32big(0x59d92bd9U));

    WR1_PROG(REG_1444H, 0x00020066U);
    WR1_PROG(REG_1408H, 0x000c7000U);

    for (iLoop = 0U; iLoop < (S_RAM[0] & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Text[iLoop]);
        WAIT_STS(REG_1408H, 30, 1);
        RD16_ADDR(REG_1420H, &OutData_Text[iLoop]);
        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = (S_RAM[0] & 0xfffffff0U); iLoop < S_RAM[0]; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Text[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = (S_RAM[0] & 0xfffffff0U); iLoop < S_RAM[0]; iLoop++)
    {
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1408H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_1C30H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001c00U);

    r_rsip_func100(bswap_32big(0x98bc0b8dU),
                   bswap_32big(0x7e4ef363U),
                   bswap_32big(0x33c4b477U),
                   bswap_32big(0x4a376644U));
    WR1_PROG(REG_1600H, 0x00008c20U);
    WR1_PROG(REG_1600H, 0x0000000fU);

    WR1_PROG(REG_1600H, 0x38000c21U);
    WR1_PROG(REG_1600H, 0x1000b420U);
    WR1_PROG(REG_1600H, 0x00000010U);

    WR1_PROG(REG_1608H, 0x81010020U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (iLoop = S_RAM[0]; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_1400H, 0x00070005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00002c20U);

        r_rsip_func101(bswap_32big(0x256b027eU), bswap_32big(0x4b4d1e0dU), bswap_32big(0x562ec933U),
                       bswap_32big(0x8a688078U));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000010U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xe26ae406U),
                   bswap_32big(0xba7cdf8bU),
                   bswap_32big(0x893931eeU),
                   bswap_32big(0x3a0b0cfaU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func100(bswap_32big(0x4a95c84eU), bswap_32big(0x374f1582U), bswap_32big(0x15a50a87U),
                       bswap_32big(0x4dc391a0U));
        WR1_PROG(REG_1408H, 0x00007012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0x71451674U), bswap_32big(0xcbb808b9U), bswap_32big(0x5f43c4d7U),
                       bswap_32big(0x2eb0afd4U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A24H, 0x08000055U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_DataT[0]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00870011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x4e1c6d4cU), bswap_32big(0xc717b102U), bswap_32big(0x048163adU),
                       bswap_32big(0x87fed261U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x353c4e40U), bswap_32big(0x67102343U), bswap_32big(0x9510403eU),
                           bswap_32big(0x09cf7499U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_AUTH_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0x9080c024U), bswap_32big(0x817ac5c7U), bswap_32big(0x9083bb66U),
                           bswap_32big(0x20f1b82aU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
