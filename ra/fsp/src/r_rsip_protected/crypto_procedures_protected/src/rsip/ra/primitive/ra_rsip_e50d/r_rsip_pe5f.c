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

rsip_ret_t r_rsip_pe5f (const uint32_t InData_Msg[],
                        const uint32_t InData_EncMsg[],
                        uint32_t       OutData_KDFInfo[],
                        uint32_t       MAX_CNT,
                        uint32_t       MAX_CNT2)
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
        WR1_PROG(REG_1420H, bswap_32big(0x0000e504U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xec72c040U), bswap_32big(0x6c2c86d4U), bswap_32big(0xbbb97d59U),
                       bswap_32big(0x1023c135U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x01799093U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e504U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xded0afd4U), bswap_32big(0xa2c280a4U), bswap_32big(0x87f4dbe4U),
                       bswap_32big(0x9e31e8a9U));
        r_rsip_func044();

        WAIT_STS(REG_2030H, 0, 1);

        r_rsip_func100(bswap_32big(0x7bf28682U), bswap_32big(0xe7ae7329U), bswap_32big(0x50df69c9U),
                       bswap_32big(0xcd440b78U));
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

        WR1_PROG(REG_1600H, 0x3800a900U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x12a3c29aU), bswap_32big(0x810222eeU), bswap_32big(0xe789a2f0U),
                       bswap_32big(0x21232183U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000929U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 9; )
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

                r_rsip_func101(bswap_32big(0xd2773096U),
                               bswap_32big(0xbaf68399U),
                               bswap_32big(0xe5a2c4cbU),
                               bswap_32big(0x17010487U));
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

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_EncMsg[1 + iLoop]);

            WR1_PROG(REG_1400H, 0x01420005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            iLoop = iLoop + 4;

            r_rsip_func101(bswap_32big(0xf85ba35aU), bswap_32big(0x06a0faf9U), bswap_32big(0x6802de4fU),
                           bswap_32big(0x89462668U));
        }
        else
        {
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

                r_rsip_func101(bswap_32big(0xe150ba60U),
                               bswap_32big(0xb1270c63U),
                               bswap_32big(0x43b6791cU),
                               bswap_32big(0x622f74e7U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000909U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe25c20e9U), bswap_32big(0x58f11451U), bswap_32big(0xabc26729U),
                           bswap_32big(0xfcc3e350U));
        }

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncMsg[OFS_ADR - 4]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xeaa14ebfU), bswap_32big(0x24acec4cU), bswap_32big(0xa3eb01c5U),
                       bswap_32big(0x8333f327U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x83a8b714U), bswap_32big(0xddd80255U), bswap_32big(0x25219c4dU),
                           bswap_32big(0x4457c6e4U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0x3e8a4746U), bswap_32big(0x8e173806U), bswap_32big(0xe176550eU),
                           bswap_32big(0x962dd445U));
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0xbd4c386cU), bswap_32big(0xb9e0fd63U), bswap_32big(0xe405a54aU),
                       bswap_32big(0x3dd9a9dfU));
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

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000e502U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x3d3c1ad9U),
                   bswap_32big(0xcbc4c635U),
                   bswap_32big(0xd3808280U),
                   bswap_32big(0x93334145U));
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

    r_rsip_func101(bswap_32big(0x7f05e88fU),
                   bswap_32big(0xa83b2a5aU),
                   bswap_32big(0x270d4df1U),
                   bswap_32big(0xbbe68252U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x01799093U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000e505U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x735cc6e3U),
                   bswap_32big(0xf70c4002U),
                   bswap_32big(0x36840f1aU),
                   bswap_32big(0xc61fe8e5U));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x000008e7U);

    r_rsip_func100(bswap_32big(0x984a8143U),
                   bswap_32big(0x2e1c593eU),
                   bswap_32big(0x4e2be20eU),
                   bswap_32big(0x852e3962U));
    WR1_PROG(REG_1608H, 0x810101e0U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (iLoop = 0U; iLoop < S_RAM[0]; )
    {
        r_rsip_func100(bswap_32big(0x6c0dcf65U), bswap_32big(0x7b61b86cU), bswap_32big(0x20df57daU),
                       bswap_32big(0xa3591191U));
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe7008d05U);
        WR1_PROG(REG_1400H, 0x00850011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KDFInfo[iLoop + 1]);

        WR1_PROG(REG_1600H, 0x0000a4e0U);
        WR1_PROG(REG_1600H, 0x00000004U);

        r_rsip_func101(bswap_32big(0xc3f481c8U), bswap_32big(0xa5e9d05bU), bswap_32big(0x60d06abcU),
                       bswap_32big(0x8d829611U));
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x380008efU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0x549ed717U),
                   bswap_32big(0x869ed820U),
                   bswap_32big(0xbe78d0ecU),
                   bswap_32big(0xd92fb865U));
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
    RD4_ADDR(REG_1420H, &OutData_KDFInfo[iLoop + 1]);

    r_rsip_func100(bswap_32big(0x4e724bf8U),
                   bswap_32big(0xee974c4cU),
                   bswap_32big(0x98d4dc10U),
                   bswap_32big(0x0be67138U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_KDFInfo[0]);

    r_rsip_func102(bswap_32big(0xcd88c46fU),
                   bswap_32big(0x72fb7e60U),
                   bswap_32big(0x97072eafU),
                   bswap_32big(0x84477f7cU));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
