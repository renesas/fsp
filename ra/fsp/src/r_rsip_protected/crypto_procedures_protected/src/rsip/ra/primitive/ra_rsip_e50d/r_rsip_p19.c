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

rsip_ret_t r_rsip_p19 (const uint32_t InData_KeyIndex[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[],
                       uint64_t       MAX_CNT)
{
    uint64_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00190001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000008c8U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000019U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x001b32f4U),
                   bswap_32big(0x9fc51ec7U),
                   bswap_32big(0xd029cc80U),
                   bswap_32big(0x9b6cde81U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000026U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000019U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x55d624e3U),
                   bswap_32big(0x998d1936U),
                   bswap_32big(0x455d5e96U),
                   bswap_32big(0x8ecec968U));
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
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
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
    WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xf2556ae3U),
                   bswap_32big(0x604d314dU),
                   bswap_32big(0xd9e9efecU),
                   bswap_32big(0xf4683450U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x52956e58U), bswap_32big(0x8090efbfU), bswap_32big(0x195701c3U),
                       bswap_32big(0x6eec9c70U));
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

        r_rsip_func100(bswap_32big(0xb9bbea0aU), bswap_32big(0x09e927b6U), bswap_32big(0x32b3f4d2U),
                       bswap_32big(0xd5cccf8fU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xd5bd341bU), bswap_32big(0xec484dc2U), bswap_32big(0xecc5a082U),
                           bswap_32big(0x7b17aa94U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x00000100U);
            WR1_PROG(REG_1A24H, 0x08008107U);
            WR1_PROG(REG_1404H, 0x1c300000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Signature[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Signature[4]);
            WR1_PROG(REG_1400H, 0x00c20021U);

            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x31890f62U), bswap_32big(0x2a971356U), bswap_32big(0x70a996cbU),
                           bswap_32big(0x4c52d809U));
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0c00a420U);
            WR1_PROG(REG_1600H, 0x00000200U);
            WR1_PROG(REG_1600H, 0x00802402U);

            WR1_PROG(REG_1608H, 0x81020000U);
            WR1_PROG(REG_1408H, 0x0000500aU);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_2004H, 0x000000b0U);

            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, S_RAM[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, S_RAM[0 + 1]);

            WR1_PROG(REG_1404H, 0x1c300000U);
            WR1_PROG(REG_1400H, 0x01430021U);
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

            WR1_PROG(REG_1004H, 0x00000000U);
            WR1_PROG(REG_1004H, 0x04040000U);

            r_rsip_func100(bswap_32big(0x6b42fd6bU), bswap_32big(0x3449d7dcU), bswap_32big(0x50dd60e8U),
                           bswap_32big(0xbf8a8cecU));
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
            WR1_PROG(REG_1020H, 0x000009d0U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x14300000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1404H, 0x19100000U);
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

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x02003801U);
            WR1_PROG(REG_1600H, 0x00003440U);
            WR1_PROG(REG_1600H, 0x00076800U);
            WR1_PROG(REG_1600H, 0x000037e0U);

            WR1_PROG(REG_1600H, 0x00008c40U);
            WR1_PROG(REG_1600H, 0x0000007FU);
            WR1_PROG(REG_1600H, 0x02003c41U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1608H, 0x81880000U);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000004d0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000004d0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000004d0U);
            WR1_PROG(REG_1018H, 0x00000ac0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002a0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040006U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000390U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000340U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12800000U);
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
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000003e0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040006U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            r_rsip_func100(bswap_32big(0x1f89d167U), bswap_32big(0x0d317a0cU), bswap_32big(0x7810843aU),
                           bswap_32big(0x3ba8dc3bU));
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000003e0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x0404000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000390U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x00000100U);
            WR1_PROG(REG_1A24H, 0x08008107U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H,
                     bswap_32big(0x0FFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU));
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H,
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFEU));
            WR1_PROG(REG_1400H, 0x00c20021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x7c70b179U), bswap_32big(0x97c68724U), bswap_32big(0x4c3e1871U),
                           bswap_32big(0x9c461616U));
            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_1018H, 0x00000250U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000003e0U);

            WR1_PROG(REG_1004H, 0x0404000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000003e0U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x00000ac0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000340U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x04040006U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x14100000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0001dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x1edc2a2eU), bswap_32big(0x32ac9153U), bswap_32big(0x494bdf4dU),
                           bswap_32big(0xe86b6955U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x000002f0U);
                WR1_PROG(REG_1018H, 0x00000250U);
                WR1_PROG(REG_1020H, 0x00000ac0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000ac0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x58d7f675U),
                               bswap_32big(0x969077d2U),
                               bswap_32big(0xe5de2d28U),
                               bswap_32big(0x986e9ea8U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0xd4cfa273U);

                    r_rsip_func101(bswap_32big(0x6c687933U),
                                   bswap_32big(0x5ee2fa1aU),
                                   bswap_32big(0x56161375U),
                                   bswap_32big(0xdd82d05bU));
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x000003e0U);
                    WR1_PROG(REG_1018H, 0x000001b0U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000250U);
                    WR1_PROG(REG_1010H, 0x00000008U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x12800000U);
                    WR1_PROG(REG_1444H, 0x000007c2U);
                    WR1_PROG(REG_1A2CH, 0x00000100U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_PROG(REG_1420H,
                             bswap_32big(0x2B832480U),
                             bswap_32big(0x4FC1DF0BU),
                             bswap_32big(0x2B4D0099U),
                             bswap_32big(0x3DFBD7A7U));
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_PROG(REG_1420H,
                             bswap_32big(0x2F431806U),
                             bswap_32big(0xAD2FE478U),
                             bswap_32big(0xC4EE1B27U),
                             bswap_32big(0x4A0EA0B0U));
                    WR1_PROG(REG_1400H, 0x00c20021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000003e0U);
                    WR1_PROG(REG_1010H, 0x00000008U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    r_rsip_func101(bswap_32big(0xca9e321cU),
                                   bswap_32big(0x1a0300daU),
                                   bswap_32big(0x296652d1U),
                                   bswap_32big(0x90e95f26U));
                }

                r_rsip_func101(bswap_32big(0x3f231481U),
                               bswap_32big(0xf7e00a43U),
                               bswap_32big(0x95a6f5dfU),
                               bswap_32big(0x050706d1U));
            }
            else
            {
                r_rsip_func101(bswap_32big(0xe69b1d96U),
                               bswap_32big(0xd1b1cb00U),
                               bswap_32big(0x8c45f536U),
                               bswap_32big(0xebd571d9U));
            }

            WR1_PROG(REG_1600H, 0x38008800U);
            WR1_PROG(REG_1600H, 0xd4cfa273U);

            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0x5709d7afU), bswap_32big(0x10de8807U), bswap_32big(0xda6649f8U),
                           bswap_32big(0x52b49393U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x57170f45U),
                               bswap_32big(0x7492f626U),
                               bswap_32big(0x059e71bdU),
                               bswap_32big(0x6430cdbfU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_1404H, 0x1b100000U);
                WR1_PROG(REG_1400H, 0x00c000f1U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x13c00000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x80880001U);
                WR1_PROG(REG_1400H, 0x03430021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1600H, 0x02003841U);

                WR1_PROG(REG_1600H, 0x00008c40U);
                WR1_PROG(REG_1600H, 0x00000001U);

                WR1_PROG(REG_1600H, 0x3800085fU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0x04f96973U),
                               bswap_32big(0x83047dbbU),
                               bswap_32big(0x0be2a2e1U),
                               bswap_32big(0x6bc4218dU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1014H, 0x000003e0U);
                    WR1_PROG(REG_1018H, 0x000001b0U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000480U);
                    WR1_PROG(REG_1010H, 0x00000008U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    r_rsip_func101(bswap_32big(0x59ff83e6U),
                                   bswap_32big(0x17ef5b9dU),
                                   bswap_32big(0x0d474589U),
                                   bswap_32big(0xde9739dcU));
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000070U);
                    WR1_PROG(REG_1018H, 0x000003e0U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x04040006U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x000001b0U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000480U);
                    WR1_PROG(REG_1010H, 0x00000008U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    r_rsip_func101(bswap_32big(0x2a7ee098U),
                                   bswap_32big(0x9ad03f87U),
                                   bswap_32big(0x376ae2bfU),
                                   bswap_32big(0x9c6e6722U));
                }

                WR1_PROG(REG_1010H, 0x00000008U);

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
                WR1_PROG(REG_1420H, bswap_32big(0x00000019U));
                WR1_PROG(REG_1458H, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0x3bb4f2c7U),
                                   bswap_32big(0x23226412U),
                                   bswap_32big(0x6e28ca8fU),
                                   bswap_32big(0xc137cf42U));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    r_rsip_func101(bswap_32big(0xfddab528U),
                                   bswap_32big(0x6c368f90U),
                                   bswap_32big(0x4e21ada5U),
                                   bswap_32big(0x20d84629U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x08000909U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1014H, 0x00000660U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000ca0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000006b0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000cf0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000700U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000d40U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000007c7U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x80880001U);
                for (iLoop = 8; iLoop < 16U; iLoop++)
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_Signature[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

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

                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1400H, 0x00c00021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000250U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000002f0U);
                WR1_PROG(REG_1010H, 0x00000010U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000980U);
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
                WR1_PROG(REG_1018H, 0x000002f0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000980U);

                WR1_PROG(REG_1004H, 0x04040005U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000008U);

                r_rsip_func100(bswap_32big(0x13529bdaU),
                               bswap_32big(0x3c2e69deU),
                               bswap_32big(0x3b0eb06fU),
                               bswap_32big(0x2b7717cbU));
                r_rsip_func401(InData_DomainParam);

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

                WR1_PROG(REG_1404H, 0x19600000U);
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
                WR1_PROG(REG_1420H, bswap_32big(0x00000119U));
                WR1_PROG(REG_1458H, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0x9cef4dc9U),
                                   bswap_32big(0x7f44facbU),
                                   bswap_32big(0xd2f07f98U),
                                   bswap_32big(0xad11a491U));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    r_rsip_func101(bswap_32big(0x60e155d5U),
                                   bswap_32big(0x5eb44f02U),
                                   bswap_32big(0x7ffe0b1cU),
                                   bswap_32big(0xa94f3bfcU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x08000909U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1014H, 0x00000660U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000750U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000006b0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x000007a0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000700U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x000007f0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1400H, 0x00c00021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000ca0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x04040006U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000ca0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000ca0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000570U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000cf0U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x000005c0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000d40U);
                WR1_PROG(REG_1018H, 0x00000b10U);
                WR1_PROG(REG_1020H, 0x00000610U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                r_rsip_func404();

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

                WR1_PROG(REG_1004H, 0x04040006U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                r_rsip_func100(bswap_32big(0x56edf6ccU),
                               bswap_32big(0xab944d61U),
                               bswap_32big(0xa448d41dU),
                               bswap_32big(0x99e63537U));
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

                WR1_PROG(REG_1404H, 0x12300000U);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1404H, 0x14100000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0001dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000c50U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000c50U);
                WR1_PROG(REG_1018H, 0x00000250U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x02bf6fcfU),
                               bswap_32big(0x99992eccU),
                               bswap_32big(0x99e8e91bU),
                               bswap_32big(0x56fa2ce1U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x97247c18U),
                                   bswap_32big(0xdead177fU),
                                   bswap_32big(0x1aa0050bU),
                                   bswap_32big(0x95597667U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func102(bswap_32big(0xac87ba00U),
                                   bswap_32big(0x30ca0b6eU),
                                   bswap_32big(0xa225e1bcU),
                                   bswap_32big(0x37fd9dcfU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
