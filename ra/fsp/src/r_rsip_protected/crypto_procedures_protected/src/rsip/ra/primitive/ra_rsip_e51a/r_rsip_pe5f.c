/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pe5f (const uint32_t InData_Msg[], const uint32_t InData_EncMsg[], uint32_t OutData_KDFInfo[], uint32_t MAX_CNT, uint32_t MAX_CNT2)
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

    r_rsip_func100(bswap_32big(0xb1896bd9U), bswap_32big(0xa91c0f26U), bswap_32big(0xaeb0a8bfU), bswap_32big(0x94a1395aU));
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
        WR1_PROG(REG_1420H, bswap_32big(0x0000e504U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xec72c040U), bswap_32big(0x6c2c86d4U), bswap_32big(0xbbb97d59U), bswap_32big(0x1023c135U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x01799093U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e504U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xded0afd4U), bswap_32big(0xa2c280a4U), bswap_32big(0x87f4dbe4U), bswap_32big(0x9e31e8a9U));
        r_rsip_func044();

        WAIT_STS(REG_2030H, 0, 1);

        r_rsip_func100(bswap_32big(0x7bf28682U), bswap_32big(0xe7ae7329U), bswap_32big(0x50df69c9U), bswap_32big(0xcd440b78U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

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

            WR1_PROG(REG_1400H, 0x01420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00002d20U);

            r_rsip_func101(bswap_32big(0x1c122981U), bswap_32big(0xa219b3cfU), bswap_32big(0xb8008871U), bswap_32big(0x4ac8eabbU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncMsg[OFS_ADR - 4]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x6ad13853U), bswap_32big(0xb38706b9U), bswap_32big(0xbf5efbd1U), bswap_32big(0xc5d9aeb8U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x6b4469e4U), bswap_32big(0xea5a575eU), bswap_32big(0xd6dabb88U), bswap_32big(0x71719d2bU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0x85f186dbU), bswap_32big(0xa0fa4fcfU), bswap_32big(0xc71f775dU), bswap_32big(0xc277614fU));
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0xbd4c386cU), bswap_32big(0xb9e0fd63U), bswap_32big(0xe405a54aU), bswap_32big(0x3dd9a9dfU));
    }

    WAIT_STS(REG_2030H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2030H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001600U);

    WAIT_STS(REG_2030H, 4, 1);

    r_rsip_func100(bswap_32big(0x1c20c3d9U), bswap_32big(0x05a4d8afU), bswap_32big(0x5451122dU), bswap_32big(0x1953b44bU));
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
    WR1_PROG(REG_1420H, bswap_32big(0x0000e505U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfd62ca63U), bswap_32big(0x68a38376U), bswap_32big(0x50112e94U), bswap_32big(0xed2b015dU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x01799093U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000e505U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x735cc6e3U), bswap_32big(0xf70c4002U), bswap_32big(0x36840f1aU), bswap_32big(0xc61fe8e5U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xd134df84U), bswap_32big(0xdce41663U), bswap_32big(0x0b57cb77U), bswap_32big(0xb42849b3U));
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xe7009d07U);
    WR1_PROG(REG_1400H, 0x00850021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002022U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);

    r_rsip_func100(bswap_32big(0xb24b34e2U), bswap_32big(0x1e193199U), bswap_32big(0x537ea2fcU), bswap_32big(0xd550e898U));
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
    RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

    r_rsip_func100(bswap_32big(0xc13aa26dU), bswap_32big(0x5faa6384U), bswap_32big(0xcf81dab6U), bswap_32big(0xecd325abU));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_KDFInfo[0]);

    r_rsip_func102(bswap_32big(0x045d8f37U), bswap_32big(0x28df2f43U), bswap_32big(0xc06352daU), bswap_32big(0xf673bd63U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
