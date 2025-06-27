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

rsip_ret_t r_rsip_p51i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[],
                        const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00510001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1600H, 0x00000b5aU);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005101U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf2c9df0bU),
                   bswap_32big(0x6f47aa8aU),
                   bswap_32big(0x2f6e6749U),
                   bswap_32big(0xfe86575dU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000018U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005101U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x4cb482e7U),
                   bswap_32big(0x3c98ee8eU),
                   bswap_32big(0x6608850bU),
                   bswap_32big(0xc4874613U));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000017c2U);
    WR1_PROG(REG_1A2CH, 0x40000500U);
    WR1_PROG(REG_1A24H, 0xe8009107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1608H, 0x80980001U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);
    WR1_PROG(REG_1400H, 0x03420031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[13]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[17]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[21]);
    WR1_PROG(REG_1400H, 0x03420031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[25]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x81ce3c2fU),
                   bswap_32big(0x00d63520U),
                   bswap_32big(0x4bc21c04U),
                   bswap_32big(0x14e139f0U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc7808741U), bswap_32big(0x231cfb41U), bswap_32big(0x1738c005U),
                       bswap_32big(0x15018108U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000bc7U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1608H, 0x808c001fU);
        for (iLoop = 0U; iLoop < 12U; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000051U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        r_rsip_func100(bswap_32big(0xeca4a15cU), bswap_32big(0x34eaa213U), bswap_32big(0x57595d3cU),
                       bswap_32big(0x37f9b8b2U));
        r_rsip_func027(InData_DomainParam);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x06060010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x06060010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x19000000U);
        WR1_PROG(REG_1444H, 0x000017c2U);
        WR1_PROG(REG_1A2CH, 0x00000500U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[4]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[8]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x19500000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x11d00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0002dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x000000c0U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000930U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xedeef1c0U), bswap_32big(0xea0e0e5eU), bswap_32big(0x272bac7eU),
                       bswap_32big(0xc29918c5U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x919fb5f5U), bswap_32big(0x7e8728a1U), bswap_32big(0xd243e261U),
                           bswap_32big(0xc92e05e7U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x68bd90a3U), bswap_32big(0x4e3c5549U), bswap_32big(0x382f458eU),
                           bswap_32big(0xfa930efbU));

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0606000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x0606000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x818c001fU);
            WR1_PROG(REG_1400H, 0x00c90031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000480U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x06060004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x11300000U);
            WR1_PROG(REG_1400H, 0x00c00031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000890U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002b8U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            r_rsip_func100(bswap_32big(0x9d4e7e58U), bswap_32big(0x82e05b40U), bswap_32big(0x289d478fU),
                           bswap_32big(0xa5fd523bU));

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1608H, 0x818c0001U);
            WR1_PROG(REG_1400H, 0x00c90031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000001e0U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000030U);
            WR1_PROG(REG_1608H, 0x818c001fU);
            WR1_PROG(REG_1400H, 0x00c90031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000218U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000570U);

            WR1_PROG(REG_1004H, 0x06060015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1404H, 0x11d00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0002dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000570U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0606000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x3a24dc52U), bswap_32big(0x9d52150cU), bswap_32big(0x8c465525U),
                           bswap_32big(0xc9442388U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x863b4ce2U),
                               bswap_32big(0xde173115U),
                               bswap_32big(0x1178bb65U),
                               bswap_32big(0x86fd78ceU));
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe4d603f7U),
                               bswap_32big(0xa58da24dU),
                               bswap_32big(0x88d219ceU),
                               bswap_32big(0x59e2a2b1U));
                WR1_PROG(REG_1404H, 0x11b00000U);
                WR1_PROG(REG_1400H, 0x00c00031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000480U);
                WR1_PROG(REG_1018H, 0x000001e0U);
                WR1_PROG(REG_1020H, 0x00000340U);

                WR1_PROG(REG_1004H, 0x06060009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                r_rsip_func028(InData_DomainParam);

                WR1_PROG(REG_1404H, 0x14500000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0002dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000340U);
                WR1_PROG(REG_1018H, 0x00000480U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x0606000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x62f21a78U),
                               bswap_32big(0x21752da4U),
                               bswap_32big(0x2b038841U),
                               bswap_32big(0x79847d41U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1404H, 0x14500000U);
                    WR1_PROG(REG_1400H, 0x00c00031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000500U);
                    WR1_PROG(REG_1018H, 0x00000480U);
                    WR1_PROG(REG_1020H, 0x000001e0U);

                    WR1_PROG(REG_1004H, 0x06060009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000538U);
                    WR1_PROG(REG_1018H, 0x00000480U);
                    WR1_PROG(REG_1020H, 0x00000218U);

                    WR1_PROG(REG_1004H, 0x06060009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000570U);
                    WR1_PROG(REG_1018H, 0x00000480U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x06060009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0x797935bbU);

                    r_rsip_func101(bswap_32big(0xb3860abfU),
                                   bswap_32big(0xcd23cae4U),
                                   bswap_32big(0x4e9be022U),
                                   bswap_32big(0xbd0e7f24U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x5e181c40U),
                                   bswap_32big(0x1b886103U),
                                   bswap_32big(0xbae5f57eU),
                                   bswap_32big(0x34937976U));
                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x00000340U);
                    WR1_PROG(REG_101CH, 0x000002f0U);
                    WR1_PROG(REG_1020H, 0x00000480U);

                    WR1_PROG(REG_1004H, 0x06060015U);
                    WR1_PROG(REG_1408H, 0x00020000U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1404H, 0x11d00000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0002dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000480U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x0606000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    r_rsip_func100(bswap_32big(0x77867303U),
                                   bswap_32big(0x402b9855U),
                                   bswap_32big(0x45f7f266U),
                                   bswap_32big(0x5daeab8bU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);

                        r_rsip_func101(bswap_32big(0x4436a4d7U),
                                       bswap_32big(0xabdc8ad1U),
                                       bswap_32big(0x004b3ef6U),
                                       bswap_32big(0x4525b063U));
                    }
                    else
                    {
                        WR1_PROG(REG_1014H, 0x00000480U);
                        WR1_PROG(REG_1018H, 0x00000570U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000250U);

                        WR1_PROG(REG_1004H, 0x06060013U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        WR1_PROG(REG_1404H, 0x12700000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                        WR1_PROG(REG_1400H, 0x00c0002dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x00c20005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x0002000dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000250U);
                        WR1_PROG(REG_1018H, 0x000002a0U);
                        WR1_PROG(REG_1020H, 0x000002f0U);

                        WR1_PROG(REG_1004H, 0x0606000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        r_rsip_func100(bswap_32big(0x46af9f05U),
                                       bswap_32big(0xcab10301U),
                                       bswap_32big(0xc58274b3U),
                                       bswap_32big(0xea0fe15fU));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1600H, 0x00000800U);

                            r_rsip_func101(bswap_32big(0x20b1a9c7U),
                                           bswap_32big(0x331c1077U),
                                           bswap_32big(0xfe7b8945U),
                                           bswap_32big(0x91788aa8U));
                        }
                        else
                        {
                            WR1_PROG(REG_1600H, 0x0000b400U);
                            WR1_PROG(REG_1600H, 0x797935bbU);

                            r_rsip_func101(bswap_32big(0x8fd43585U),
                                           bswap_32big(0x4dd16090U),
                                           bswap_32big(0x937607bfU),
                                           bswap_32big(0x25e2765eU));
                        }
                    }
                }

                WR1_PROG(REG_1600H, 0x38008800U);
                WR1_PROG(REG_1600H, 0x797935bbU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                r_rsip_func100(bswap_32big(0x943e8159U),
                               bswap_32big(0xf244127eU),
                               bswap_32big(0xfe2863e2U),
                               bswap_32big(0x66ae9220U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func101(bswap_32big(0x08e98d23U),
                                   bswap_32big(0x857219f6U),
                                   bswap_32big(0xe6ef4ed6U),
                                   bswap_32big(0x9fabf5ccU));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xeb327d6bU),
                                   bswap_32big(0x6209b817U),
                                   bswap_32big(0x9c4818d4U),
                                   bswap_32big(0x3b8ddec5U));

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);

                    WR1_PROG(REG_1004H, 0x06060004U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x11300000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                    WR1_PROG(REG_1400H, 0x00c0002dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000070U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000110U);

                    WR1_PROG(REG_1004H, 0x0606000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000110U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000160U);

                    WR1_PROG(REG_1004H, 0x0606000fU);
                    WR1_PROG(REG_1408H, 0x00020000U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1014H, 0x000001e0U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);

                    WR1_PROG(REG_1004H, 0x06060002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000930U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x0606000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    WR1_PROG(REG_1014H, 0x00000930U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x0606000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    r_rsip_func100(bswap_32big(0xdb0354d0U),
                                   bswap_32big(0xa27caebcU),
                                   bswap_32big(0x2c8b2c2aU),
                                   bswap_32big(0x010cf7ddU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);

                        r_rsip_func101(bswap_32big(0x451281c4U),
                                       bswap_32big(0x7c163bb9U),
                                       bswap_32big(0x8e165f1cU),
                                       bswap_32big(0xef6aa1c8U));
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x0000b400U);
                        WR1_PROG(REG_1600H, 0x797935bbU);

                        r_rsip_func101(bswap_32big(0xe23442c6U),
                                       bswap_32big(0xec641f5bU),
                                       bswap_32big(0x672ac7f0U),
                                       bswap_32big(0xdfd192c8U));
                    }
                }
            }
        }

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1600H, 0x797935bbU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        WR1_PROG(REG_1600H, 0x00007c1bU);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0xa2de49e8U), bswap_32big(0x7697f4cdU), bswap_32big(0x931f9158U),
                       bswap_32big(0xd451f7d6U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x34ff8593U), bswap_32big(0x8246840cU), bswap_32big(0xe6861bdaU),
                           bswap_32big(0x07aec466U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0xe8673b6fU), bswap_32big(0x8be3e373U), bswap_32big(0x2db97162U),
                           bswap_32big(0x300345a1U));

            return RSIP_RET_PASS;
        }
    }
}
