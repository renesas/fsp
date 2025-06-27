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

rsip_ret_t r_rsip_p18 (const uint32_t InData_PrivKeyIndex[],
                       const uint32_t InData_PubKeyIndex[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_Signature[],
                       uint64_t       MAX_CNT)
{
    uint64_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00180001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000008c8U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_PrivKeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000018U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x94f522baU),
                   bswap_32big(0x0eea8e03U),
                   bswap_32big(0x4595497aU),
                   bswap_32big(0x5cc50199U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000027U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000018U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x33f4fda5U),
                   bswap_32big(0x0368fe5eU),
                   bswap_32big(0x8879fbf7U),
                   bswap_32big(0x10a0d100U));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);

    for (iLoop = 0U; iLoop < 8U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PrivKeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1608H, 0x80880000U);
    WR1_PROG(REG_1400H, 0x03420021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_PrivKeyIndex[iLoop + 1]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x7bb45a99U),
                   bswap_32big(0x4ccccec5U),
                   bswap_32big(0x8ffa3a9aU),
                   bswap_32big(0x4eda35fcU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x36aa8486U), bswap_32big(0x7b06a90eU), bswap_32big(0x1d6624ecU),
                       bswap_32big(0xdd6da797U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_PubKeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000118U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x55ebe36dU), bswap_32big(0x4018b866U), bswap_32big(0x7d3035d5U),
                       bswap_32big(0xd9016dd0U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000026U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000118U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x5ac59946U), bswap_32big(0x12bad022U), bswap_32big(0x377b00deU),
                       bswap_32big(0xfa177bf3U));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xe8009107U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x19100000U);
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PubKeyIndex[iLoop + 1]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x554f1971U), bswap_32big(0x7e628bbdU), bswap_32big(0x2669b605U),
                       bswap_32big(0xb23c74cfU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xf0563577U), bswap_32big(0x04be4d92U), bswap_32big(0xe8b24446U),
                           bswap_32big(0x7f2633ccU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000001c7U);
            WR1_PROG(REG_1608H, 0x80020000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR2_ADDR(REG_1420H, &InData_MsgLen[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00000bffU);

            WR1_PROG(REG_1600H, 0x30008800U);
            WR1_PROG(REG_1600H, 0xffffffffU);
            WR1_PROG(REG_1600H, 0x00030020U);
            WR1_PROG(REG_1600H, 0x3000a820U);
            WR1_PROG(REG_1600H, 0xfffffdffU);
            WR1_PROG(REG_1600H, 0x00050020U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);
            WR1_PROG(REG_1600H, 0x00000080U);
            WR1_PROG(REG_1600H, 0x00000080U);
            WR1_PROG(REG_1600H, 0x38008be0U);
            WR1_PROG(REG_1600H, 0x00000001U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xcfb57323U), bswap_32big(0xb367d1cdU), bswap_32big(0x162ed74fU),
                           bswap_32big(0x10adf402U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x3548e285U),
                               bswap_32big(0x04f27027U),
                               bswap_32big(0x194fe286U),
                               bswap_32big(0x6ae1e54eU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xc19f4c21U),
                               bswap_32big(0xaab90c0eU),
                               bswap_32big(0xdc09dc9eU),
                               bswap_32big(0x08c9bc19U));
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0c00a420U);
                WR1_PROG(REG_1600H, 0x00000100U);
                WR1_PROG(REG_1600H, 0x00802402U);

                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                r_rsip_func100(bswap_32big(0x5e5c29f8U),
                               bswap_32big(0xe938cb33U),
                               bswap_32big(0x84df03d6U),
                               bswap_32big(0xec2d6d15U));
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0c00a420U);
                WR1_PROG(REG_1600H, 0x00000100U);
                WR1_PROG(REG_1600H, 0x00802402U);

                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 2]);
                S_RAM[0 + 2] = bswap_32big(S_RAM[0 + 2]);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 3]);
                S_RAM[0 + 3] = bswap_32big(S_RAM[0 + 3]);

                WR1_PROG(REG_2000H, 0x00000001U);

                WR1_PROG(REG_2004H, 0x000000b0U);

                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2010H, 0x00000100U);

                WR1_PROG(REG_1600H, 0x00000bdeU);
                WR1_PROG(REG_1608H, 0x8188001eU);
                WR1_PROG(REG_1400H, 0x01490021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1608H, 0x80900001U);
                WR1_PROG(REG_1400H, 0x03450041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00003841U);
                WR1_PROG(REG_1600H, 0x00008c40U);
                WR1_PROG(REG_1600H, 0xf8ffffffU);
                WR1_PROG(REG_1600H, 0x00003c41U);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000001cU);
                WR1_PROG(REG_1600H, 0x00003841U);

                WR1_PROG(REG_1600H, 0x00008c40U);
                WR1_PROG(REG_1600H, 0xffffff3fU);

                WR1_PROG(REG_1600H, 0x00009040U);
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1600H, 0x00003c41U);

                WR1_PROG(REG_1404H, 0x19600000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_2000H, 0x00000001U);

                WR1_PROG(REG_2004H, 0x000000b0U);

                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, S_RAM[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, S_RAM[0 + 1]);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x01490021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x00020064U);

                for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffffffffffff0U); )
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR8_ADDR(REG_1420H, &InData_Msg[iLoop]);
                    iLoop = iLoop + 8U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WAIT_STS(REG_1444H, 31, 1);
                for (iLoop = (MAX_CNT & 0xfffffffffffffff0U); iLoop < MAX_CNT; iLoop++)
                {
                    WR1_PROG(REG_1420H, InData_Msg[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x00000000U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1608H, 0x80900001U);
                WR1_PROG(REG_1400H, 0x03450041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x0000003fU);

                for (iLoop = 0U; iLoop < 32U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003801U);
                    WR1_PROG(REG_1600H, 0x02003843U);
                    WR1_PROG(REG_1600H, 0x02003c41U);
                    WR1_PROG(REG_1600H, 0x02003c03U);

                    WR1_PROG(REG_1600H, 0x00002c20U);
                    WR1_PROG(REG_1600H, 0x00003060U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1004H, 0x00000000U);
                WR1_PROG(REG_1004H, 0x04040000U);

                r_rsip_func100(bswap_32big(0xc00166d4U),
                               bswap_32big(0x377facbaU),
                               bswap_32big(0x9d4b46a8U),
                               bswap_32big(0x73897090U));
                r_rsip_func401(InData_DomainParam);

                r_rsip_func100(bswap_32big(0xca31355fU),
                               bswap_32big(0xe31e3c3bU),
                               bswap_32big(0x77c985ccU),
                               bswap_32big(0xedb1fdfeU));
                r_rsip_func406(InData_DomainParam);

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x00000100U);
                WR1_PROG(REG_1A24H, 0x08008107U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H,
                         bswap_32big(0x0EEC73D2U),
                         bswap_32big(0x17F5BE65U),
                         bswap_32big(0xCB5C63AAU),
                         bswap_32big(0x97A331B5U));
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H,
                         bswap_32big(0x0665E1DBU),
                         bswap_32big(0x6EABA043U),
                         bswap_32big(0xF98B4BAAU),
                         bswap_32big(0x9C78F954U));
                WR1_PROG(REG_1400H, 0x00c20021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000002f0U);
                WR1_PROG(REG_1010H, 0x00000010U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000250U);

                WR1_PROG(REG_1004H, 0x04040004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000009d0U);

                WR1_PROG(REG_1004H, 0x04040005U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x15000000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
                WR1_PROG(REG_1400H, 0x00c00015U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c2000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00020005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x16400000U);
                WR1_PROG(REG_1400H, 0x00c00021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x16900000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
                WR1_PROG(REG_1400H, 0x00c00015U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c2000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00020005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x16e00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
                WR1_PROG(REG_1400H, 0x00c00015U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c2000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00020005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1b400000U);
                WR1_PROG(REG_1400H, 0x00c00021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1b900000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
                WR1_PROG(REG_1400H, 0x00c00015U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c2000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00020005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1be00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000026U));
                WR1_PROG(REG_1400H, 0x00c00015U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c2000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00020005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19b00000U);
                WR1_PROG(REG_1600H, 0x00000bffU);
                WR1_PROG(REG_1608H, 0x8088001fU);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000908U);
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1600H, 0x0000b660U);
                WR1_PROG(REG_1600H, 0x00000001U);

                WR1_PROG(REG_1600H, 0x0000b520U);
                WR1_PROG(REG_1600H, 0x00000100U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000018U));
                WR1_PROG(REG_1458H, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0xf277a28bU),
                                   bswap_32big(0x801c2c7fU),
                                   bswap_32big(0x86b03079U),
                                   bswap_32big(0x73c1961aU));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    r_rsip_func101(bswap_32big(0x9ae1bb93U),
                                   bswap_32big(0x02131eedU),
                                   bswap_32big(0x40407ec4U),
                                   bswap_32big(0xcfeda0dcU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x08000909U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1014H, 0x00000660U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000570U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000006b0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x000005c0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000700U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000610U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000610U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000250U);
                WR1_PROG(REG_1010H, 0x00000008U);

                WR1_PROG(REG_1004H, 0x04040004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x12d00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c0001dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000070U);
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                r_rsip_func100(bswap_32big(0x037807b7U),
                               bswap_32big(0x36742391U),
                               bswap_32big(0x3960ff58U),
                               bswap_32big(0x2884a15aU));
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002f0U);

                WR1_PROG(REG_1004H, 0x0404000fU);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000570U);
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000250U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000005c0U);
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x80880001U);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00003801U);
                WR1_PROG(REG_1600H, 0x00008c00U);
                WR1_PROG(REG_1600H, 0x7fffffffU);

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x80880001U);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000003cU);
                WR1_PROG(REG_1600H, 0x00003841U);

                WR1_PROG(REG_1600H, 0x001f6c42U);
                WR1_PROG(REG_1600H, 0x00001002U);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00003c01U);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                for (iLoop = 0U; iLoop < 16U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003801U);
                    WR1_PROG(REG_1600H, 0x02003843U);
                    WR1_PROG(REG_1600H, 0x02003c41U);
                    WR1_PROG(REG_1600H, 0x02003c03U);

                    WR1_PROG(REG_1600H, 0x00002c20U);
                    WR1_PROG(REG_1600H, 0x00003060U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1404H, 0x1c300000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_2000H, 0x00000001U);

                WR1_PROG(REG_2004H, 0x000000b0U);

                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, S_RAM[0 + 2]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, S_RAM[0 + 3]);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x01490021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19100000U);
                WR1_PROG(REG_1400H, 0x01430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x00020064U);

                for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffffffffffff0U); )
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);
                    iLoop = iLoop + 16U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WAIT_STS(REG_1444H, 31, 1);
                for (iLoop = (MAX_CNT & 0xfffffffffffffff0U); iLoop < MAX_CNT; iLoop++)
                {
                    WR1_PROG(REG_1420H, InData_Msg[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x00000000U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1608H, 0x80900001U);
                WR1_PROG(REG_1400H, 0x03450041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x0000003fU);

                for (iLoop = 0U; iLoop < 32U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003801U);
                    WR1_PROG(REG_1600H, 0x02003843U);
                    WR1_PROG(REG_1600H, 0x02003c41U);
                    WR1_PROG(REG_1600H, 0x02003c03U);

                    WR1_PROG(REG_1600H, 0x00002c20U);
                    WR1_PROG(REG_1600H, 0x00003060U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81900001U);

                WR1_PROG(REG_1404H, 0x1a000000U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x1a500000U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x19600000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x80880001U);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                for (iLoop = 0U; iLoop < 16U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003801U);
                    WR1_PROG(REG_1600H, 0x02003843U);
                    WR1_PROG(REG_1600H, 0x02003c41U);
                    WR1_PROG(REG_1600H, 0x02003c03U);

                    WR1_PROG(REG_1600H, 0x00002c20U);
                    WR1_PROG(REG_1600H, 0x00003060U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1404H, 0x19600000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x00000100U);
                WR1_PROG(REG_1A24H, 0x08008107U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H,
                         bswap_32big(0x0EEC73D2U),
                         bswap_32big(0x17F5BE65U),
                         bswap_32big(0xCB5C63AAU),
                         bswap_32big(0x97A331B5U));
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H,
                         bswap_32big(0x0665E1DBU),
                         bswap_32big(0x6EABA043U),
                         bswap_32big(0xF98B4BAAU),
                         bswap_32big(0x9C78F954U));
                WR1_PROG(REG_1400H, 0x00c20021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000a20U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000002a0U);
                WR1_PROG(REG_1010H, 0x00000010U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000a70U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000250U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000003e0U);

                WR1_PROG(REG_1004H, 0x04040004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000003e0U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000340U);

                WR1_PROG(REG_1004H, 0x04040005U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000980U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000430U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000200U);
                WR1_PROG(REG_1018H, 0x00000340U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000390U);
                WR1_PROG(REG_1010H, 0x00000010U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000390U);
                WR1_PROG(REG_1018H, 0x00000430U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000003e0U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000009d0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x000002f0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000002f0U);
                WR1_PROG(REG_1018H, 0x000003e0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x04040005U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1608H, 0x80880001U);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                for (iLoop = 0U; iLoop < 16U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003801U);
                    WR1_PROG(REG_1600H, 0x02003843U);
                    WR1_PROG(REG_1600H, 0x02003c41U);
                    WR1_PROG(REG_1600H, 0x02003c03U);

                    WR1_PROG(REG_1600H, 0x00002c20U);
                    WR1_PROG(REG_1600H, 0x00003060U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0xacb6bdf2U),
                               bswap_32big(0x0c21cf38U),
                               bswap_32big(0x9d4d21b3U),
                               bswap_32big(0x121b1e56U));
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0x08008107U);

                WR1_PROG(REG_1404H, 0x1c300000U);
                WR1_PROG(REG_1400H, 0x00830021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1408H, 0x00002022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_Signature[0]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_Signature[4]);

                r_rsip_func100(bswap_32big(0xd714cbb8U),
                               bswap_32big(0xb4c37a98U),
                               bswap_32big(0xea20def9U),
                               bswap_32big(0x7e46ecefU));
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1408H, 0x00005022U);
                for (iLoop = 8; iLoop < 16U; iLoop++)
                {
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_Signature[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func102(bswap_32big(0x111f4c92U),
                               bswap_32big(0xb9d8b869U),
                               bswap_32big(0x17016699U),
                               bswap_32big(0x1c3a0990U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
