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

rsip_ret_t r_rsip_p5fi (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[],
                        const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x005f0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005f01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x14f5ff4aU),
                   bswap_32big(0xd670bef1U),
                   bswap_32big(0xf2d71c66U),
                   bswap_32big(0xa02338c3U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000020U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005f01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x852a94f6U),
                   bswap_32big(0x0df68518U),
                   bswap_32big(0x3ba54f3dU),
                   bswap_32big(0x2dba871bU));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x00001fc2U);
    WR1_PROG(REG_1A2CH, 0x40000700U);
    WR1_PROG(REG_1A24H, 0xe8009107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1608H, 0x80a00001U);
    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[17 + iLoop]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[33]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0x86cc11c5U),
                   bswap_32big(0x4c37c1cfU),
                   bswap_32big(0x239e84a6U),
                   bswap_32big(0x960edb12U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd42abd63U), bswap_32big(0x281b47d9U), bswap_32big(0xb8e26af4U),
                       bswap_32big(0x8763ce98U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000fc7U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1608H, 0x8090001fU);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00000bdeU);
        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1600H, 0x00000100U);

        WR1_PROG(REG_1A2CH, 0x00000300U);
        WR1_PROG(REG_1A24H, 0x08008107U);

        for (iLoop = 0U; iLoop < 16U; )
        {
            WR1_PROG(REG_1608H, 0x8184001eU);
            WR1_PROG(REG_1400H, 0x00890011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1608H, 0x8084001fU);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000a7c0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000005fU));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        r_rsip_func100(bswap_32big(0xe8131870U), bswap_32big(0xff52cbcdU), bswap_32big(0xcb537efbU),
                       bswap_32big(0xdaf09b0aU));
        r_rsip_func078(InData_DomainParam);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x08080010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x08080010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x18f00000U);
        WR1_PROG(REG_1444H, 0x00001fc2U);
        WR1_PROG(REG_1A2CH, 0x00000700U);
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
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x19400000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[24]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[28]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x11c00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0003dU);
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
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000930U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xd1fbc162U), bswap_32big(0xe20f739fU), bswap_32big(0xc0602066U),
                       bswap_32big(0x215f30eaU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xd5838959U), bswap_32big(0x19bb59c6U), bswap_32big(0x59985b7aU),
                           bswap_32big(0x203e0838U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xb3995d73U), bswap_32big(0x8d9031e9U), bswap_32big(0x9e6491c6U),
                           bswap_32big(0xa5e779b0U));

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x0808000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x8190001fU);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000480U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11200000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19800000U);
            WR1_PROG(REG_1400H, 0x00c002d1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000a70U);

            WR1_PROG(REG_1004H, 0x08080004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000890U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002a8U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1608H, 0x81900001U);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000009e0U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000040U);
            WR1_PROG(REG_1608H, 0x8190001fU);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000a28U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            r_rsip_func100(bswap_32big(0xe09be6d1U), bswap_32big(0x2242d919U), bswap_32big(0xe7b16682U),
                           bswap_32big(0x8fc18a8eU));
            r_rsip_func079(InData_DomainParam);

            WR1_PROG(REG_1014H, 0x000001c0U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000ad0U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000208U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000b18U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000a70U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000b60U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000ad0U);
            WR1_PROG(REG_1018H, 0x000009e0U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x000009e0U);
            WR1_PROG(REG_1018H, 0x00000ad0U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000b18U);
            WR1_PROG(REG_1018H, 0x00000a28U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000a28U);
            WR1_PROG(REG_1018H, 0x00000b18U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x9711a114U), bswap_32big(0x442e5613U), bswap_32big(0xd2104118U),
                           bswap_32big(0x802c1395U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                WR1_PROG(REG_1018H, 0x00000a70U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000c50U);

                WR1_PROG(REG_1004H, 0x08080013U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0x11b79db5U),
                               bswap_32big(0x1aba9207U),
                               bswap_32big(0x0efe17bfU),
                               bswap_32big(0x369da93eU));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                WR1_PROG(REG_101CH, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000c50U);

                WR1_PROG(REG_1004H, 0x08080014U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0x8b485f09U),
                               bswap_32big(0xce2bcdacU),
                               bswap_32big(0xd1480dbeU),
                               bswap_32big(0x69c108a1U));
            }

            WR1_PROG(REG_1600H, 0x00000821U);

            WR1_PROG(REG_1404H, 0x14400000U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03430041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000a420U);
            WR1_PROG(REG_1600H, 0x00000050U);

            WR1_PROG(REG_1404H, 0x13000000U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03430041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000821U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x000034a1U);

                WR1_PROG(REG_1600H, 0x00026ca5U);

                WR1_PROG(REG_1600H, 0x00003865U);

                WR1_PROG(REG_1600H, 0x0000a4a0U);
                WR1_PROG(REG_1600H, 0x00000050U);

                WR1_PROG(REG_1600H, 0x00003885U);

                WR1_PROG(REG_1600H, 0x00000842U);

                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    WR1_PROG(REG_1600H, 0x000008a5U);

                    WR1_PROG(REG_1600H, 0x01816ca3U);
                    WR1_PROG(REG_1600H, 0x01816ca4U);
                    WR1_PROG(REG_1600H, 0x00016c63U);
                    WR1_PROG(REG_1600H, 0x00016c84U);

                    WR1_PROG(REG_1404H, 0x11200000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0003dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x000001c0U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000110U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000110U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x4304b1c3U),
                                   bswap_32big(0x8043e874U),
                                   bswap_32big(0x766162beU),
                                   bswap_32big(0x9579dacbU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1014H, 0x00000250U);
                        WR1_PROG(REG_101CH, 0x000002f0U);
                        WR1_PROG(REG_1020H, 0x00000250U);

                        WR1_PROG(REG_1004H, 0x08080014U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0x79341e0eU),
                                       bswap_32big(0x4fc54342U),
                                       bswap_32big(0x83f41afdU),
                                       bswap_32big(0x9b47de33U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x14a478c2U),
                                       bswap_32big(0xf427bcb2U),
                                       bswap_32big(0x92afb93aU),
                                       bswap_32big(0xb0971002U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0x30885ff3U),
                                   bswap_32big(0x26d5a0adU),
                                   bswap_32big(0xe40b1f32U),
                                   bswap_32big(0x33a46184U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x97c381c6U),
                                       bswap_32big(0x72d6f91eU),
                                       bswap_32big(0xb191e2edU),
                                       bswap_32big(0x9b79b148U));

                        WR1_PROG(REG_1404H, 0x11200000U);
                        WR1_PROG(REG_1400H, 0x00c00041U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1600H, 0x00007c05U);
                        WR1_PROG(REG_143CH, 0x00600000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                        {
                            WR1_PROG(REG_1014H, 0x000009e0U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x000003f0U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000a28U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000438U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000a70U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000480U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            r_rsip_func101(bswap_32big(0x37c03066U),
                                           bswap_32big(0xc58756deU),
                                           bswap_32big(0x6ef8bee4U),
                                           bswap_32big(0xeb9d65aaU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
                        {
                            WR1_PROG(REG_1014H, 0x00000ad0U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x000003f0U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000b18U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000438U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000b60U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000480U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            r_rsip_func101(bswap_32big(0xe60eb951U),
                                           bswap_32big(0xeaa1cddaU),
                                           bswap_32big(0x5abcda3eU),
                                           bswap_32big(0x3a8315adU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
                        {
                            WR1_PROG(REG_1014H, 0x00000bc0U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x000003f0U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000c08U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000438U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000c50U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000480U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            r_rsip_func101(bswap_32big(0xc1f6e268U),
                                           bswap_32big(0x81135f76U),
                                           bswap_32big(0x7e8c2439U),
                                           bswap_32big(0xd53a4128U));
                        }

                        WR1_PROG(REG_1404H, 0x11200000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                        WR1_PROG(REG_1400H, 0x00c0003dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x00c20005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x0002000dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x000001c0U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000110U);

                        WR1_PROG(REG_1004H, 0x0808000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        WR1_PROG(REG_1014H, 0x00000250U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000110U);

                        WR1_PROG(REG_1004H, 0x0808000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0x42e0b694U),
                                       bswap_32big(0xb92dbe55U),
                                       bswap_32big(0x85958a49U),
                                       bswap_32big(0xd84a8177U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1014H, 0x000003f0U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000110U);

                            WR1_PROG(REG_1004H, 0x0808000aU);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            WR1_PROG(REG_1014H, 0x00000480U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000110U);

                            WR1_PROG(REG_1004H, 0x0808000aU);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0x284ed7baU),
                                           bswap_32big(0x84998a8fU),
                                           bswap_32big(0xb41ad3d5U),
                                           bswap_32big(0x9dfcbbf1U));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                WR1_PROG(REG_1014H, 0x000001c0U);
                                WR1_PROG(REG_1018H, 0x000003f0U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                WR1_PROG(REG_1014H, 0x000003f0U);
                                WR1_PROG(REG_1018H, 0x000001c0U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                WR1_PROG(REG_1014H, 0x00000208U);
                                WR1_PROG(REG_1018H, 0x00000438U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                WR1_PROG(REG_1014H, 0x00000438U);
                                WR1_PROG(REG_1018H, 0x00000208U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                WR1_PROG(REG_1014H, 0x00000250U);
                                WR1_PROG(REG_1018H, 0x00000480U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                WR1_PROG(REG_1014H, 0x00000480U);
                                WR1_PROG(REG_1018H, 0x00000250U);
                                WR1_PROG(REG_1020H, 0x00000110U);

                                WR1_PROG(REG_1004H, 0x0808000aU);
                                WR1_PROG(REG_1000H, 0x00010001U);
                                WAIT_STS(REG_1000H, 0, 0);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func100(bswap_32big(0xfd2a4a4dU), bswap_32big(0xdbd7f245U),
                                               bswap_32big(0xb221a381U), bswap_32big(0x3e3239eaU));
                                WR1_PROG(REG_143CH, 0x00400000U);

                                if (CHCK_STS(REG_143CH, 22, 1))
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    WR1_PROG(REG_1018H, 0x00000480U);
                                    WR1_PROG(REG_101CH, 0x00000070U);
                                    WR1_PROG(REG_1020H, 0x00000250U);

                                    WR1_PROG(REG_1004H, 0x08080013U);
                                    WR1_PROG(REG_1000H, 0x00010001U);
                                    WAIT_STS(REG_1000H, 0, 0);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xb302f2c4U), bswap_32big(0x27371218U),
                                                   bswap_32big(0x6aad2245U), bswap_32big(0xd0ab66dfU));
                                }
                                else
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    WR1_PROG(REG_101CH, 0x000002f0U);
                                    WR1_PROG(REG_1020H, 0x00000250U);

                                    WR1_PROG(REG_1004H, 0x08080014U);
                                    WR1_PROG(REG_1000H, 0x00010001U);
                                    WAIT_STS(REG_1000H, 0, 0);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x9bf656f8U), bswap_32big(0x5bb23bd5U),
                                                   bswap_32big(0x45135387U), bswap_32big(0xb6d43e03U));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0xe7ccefeaU), bswap_32big(0xc19ee188U),
                                               bswap_32big(0x98b43ed0U), bswap_32big(0x8fa5ac12U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x11200000U);
                            WR1_PROG(REG_1400H, 0x00c00041U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1014H, 0x000003f0U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x000001c0U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000438U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000208U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000480U);
                            WR1_PROG(REG_1018H, 0x00000160U);
                            WR1_PROG(REG_1020H, 0x00000250U);

                            WR1_PROG(REG_1004H, 0x08080009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            r_rsip_func101(bswap_32big(0x82d351a8U),
                                           bswap_32big(0x71068ad1U),
                                           bswap_32big(0x5d88792fU),
                                           bswap_32big(0xe21262fcU));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xd899b2e0U),
                                       bswap_32big(0x2f4a67ebU),
                                       bswap_32big(0x92de9931U),
                                       bswap_32big(0x9658b8e4U));
                    }

                    WR1_PROG(REG_1600H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0xe3f9fb58U),
                                   bswap_32big(0x992b70fcU),
                                   bswap_32big(0x2ae296b7U),
                                   bswap_32big(0x6704c5e6U));
                }

                WR1_PROG(REG_1600H, 0x38008840U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x2074f063U),
                               bswap_32big(0x1a6ec197U),
                               bswap_32big(0x3d14eedcU),
                               bswap_32big(0x2a71438bU));
            }

            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x12600000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0003dU);
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

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xcc7d3a82U), bswap_32big(0xfa8f1b52U), bswap_32big(0xc4377cfaU),
                           bswap_32big(0x4bbc4600U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x63e9b9feU),
                               bswap_32big(0xfcf0f282U),
                               bswap_32big(0xc7c86e4eU),
                               bswap_32big(0x235cf277U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe24de367U),
                               bswap_32big(0x198b18f1U),
                               bswap_32big(0x394368d8U),
                               bswap_32big(0x96bce89aU));

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x08080004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x11200000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c0003dU);
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

                WR1_PROG(REG_1004H, 0x0808000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000160U);

                WR1_PROG(REG_1004H, 0x0808000fU);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1014H, 0x000001c0U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002a0U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000930U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x0808000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000930U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x0808000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x282a5db5U),
                               bswap_32big(0xaa96282dU),
                               bswap_32big(0xd9c6bb6dU),
                               bswap_32big(0x142f971bU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0x850ee47cU),
                                   bswap_32big(0xc5203495U),
                                   bswap_32big(0xdf3995c0U),
                                   bswap_32big(0xbdaef5c9U));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0x797935bbU);

                    r_rsip_func101(bswap_32big(0xd4c8e979U),
                                   bswap_32big(0x97f1c61aU),
                                   bswap_32big(0x9b73d8cbU),
                                   bswap_32big(0x5143ff61U));
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

        r_rsip_func100(bswap_32big(0x4b66efe5U), bswap_32big(0xb3cffb0bU), bswap_32big(0xd277b0eaU),
                       bswap_32big(0xd1a18e8dU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xfa34f86bU), bswap_32big(0x78d78ecbU), bswap_32big(0x0b94a562U),
                           bswap_32big(0xaae0540eU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000b7c0U);
            WR1_PROG(REG_1600H, 0x00000100U);
            WR1_PROG(REG_1600H, 0x00000bffU);

            WR1_PROG(REG_1A2CH, 0x00000300U);
            WR1_PROG(REG_1A24H, 0x08008107U);

            for (iLoop = 0U; iLoop < 16U; )
            {
                WR1_PROG(REG_1608H, 0x8184001eU);
                WR1_PROG(REG_1400H, 0x00890011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1608H, 0x8084001fU);
                WR1_PROG(REG_1400H, 0x03420011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000a7c0U);
                WR1_PROG(REG_1600H, 0x00000010U);
                WR1_PROG(REG_1600H, 0x0000a7e0U);
                WR1_PROG(REG_1600H, 0x00000010U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            return RSIP_RET_PASS;
        }
    }
}
