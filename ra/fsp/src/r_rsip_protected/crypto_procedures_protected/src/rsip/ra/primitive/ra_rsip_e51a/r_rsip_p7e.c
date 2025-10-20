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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p7e (const uint32_t InData_KeyIndex[],
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

    WR1_PROG(REG_1B00H, 0x007e0001U);
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
    WR1_PROG(REG_1420H, bswap_32big(0x0000007eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x331e84e0U),
                   bswap_32big(0x1c477d9dU),
                   bswap_32big(0x82b9edf0U),
                   bswap_32big(0xa085474dU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000020U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000007eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc46018cdU),
                   bswap_32big(0x0ee89f0fU),
                   bswap_32big(0x23b0b717U),
                   bswap_32big(0x7265f191U));
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
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
        r_rsip_func_sub002(0x03420011U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 17]);
        r_rsip_func_sub002(0x03420011U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[33]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    r_rsip_func_sub002(0x00820011U);

    r_rsip_func100(bswap_32big(0xbcdf1297U),
                   bswap_32big(0x4567f627U),
                   bswap_32big(0xb9c56121U),
                   bswap_32big(0x664d75a1U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x9929fc88U), bswap_32big(0xc7c941c3U), bswap_32big(0x91ac1fd1U),
                       bswap_32big(0xc969ab27U));
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

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000007eU));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        r_rsip_func100(bswap_32big(0xcd01c7f7U), bswap_32big(0x4c737b82U), bswap_32big(0x44ef9d55U),
                       bswap_32big(0xf41b0bb2U));
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
        r_rsip_func_sub002(0x00c20031U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        r_rsip_func_sub002(0x00c20011U);

        WR1_PROG(REG_1404H, 0x19400000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[24]);
        r_rsip_func_sub002(0x00c20031U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[28]);
        r_rsip_func_sub002(0x00c20011U);

        WR1_PROG(REG_1404H, 0x11c00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_func_sub002(0x00c0003dU);
        r_rsip_func_sub002(0x00c20005U);
        r_rsip_func_sub002(0x0002000dU);

        r_rsip_func_sub001(0x000000c0U, 0x00000200U, 0x00000160U, 0x0808000aU);

        r_rsip_func_sub001(0x00000160U, 0x00000930U, 0x000001b0U, 0x0808000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000930U, 0x00000200U, 0x000001b0U, 0x0808000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000160U, 0x00000980U, 0x000001b0U, 0x0808000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000980U, 0x00000200U, 0x000001b0U, 0x0808000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0x306c7cd5U), bswap_32big(0x4aaa36cdU), bswap_32big(0x3289d560U),
                       bswap_32big(0xb95da083U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x0c1053fcU), bswap_32big(0xf8f0d08aU), bswap_32big(0x12645fc6U),
                           bswap_32big(0xf82ba89aU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xc9efe878U), bswap_32big(0x3dd98d4eU), bswap_32big(0x61cc304aU),
                           bswap_32big(0x61717222U));

            r_rsip_func_sub001(0x00000160U, 0x00000200U, 0x000001b0U, 0x0808000aU);

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
            r_rsip_func_sub003(0x000000c0U, 0x00000160U, 0x08080002U);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x8190001fU);
            r_rsip_func_sub002(0x00c90041U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000480U, 0x08080002U);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000340U, 0x08080002U);

            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11200000U);
            r_rsip_func_sub002(0x00c00041U);

            WR1_PROG(REG_1404H, 0x19800000U);
            r_rsip_func_sub002(0x00c002d1U);

            WR1_PROG(REG_1014H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a70U, 0x08080004U);

            r_rsip_func_sub001(0x00000890U, 0x00000160U, 0x000002a8U, 0x08080009U);

            r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x000002f0U, 0x08080009U);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1608H, 0x81900001U);
            r_rsip_func_sub002(0x00c90041U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x000009e0U, 0x08080002U);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000040U);
            WR1_PROG(REG_1608H, 0x8190001fU);
            r_rsip_func_sub002(0x00c90041U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a28U, 0x08080002U);

            r_rsip_func100(bswap_32big(0x1d8d6d5bU), bswap_32big(0xeca4b656U), bswap_32big(0x8a4c8630U),
                           bswap_32big(0x13afe170U));
            r_rsip_func079(InData_DomainParam);

            r_rsip_func_sub001(0x000001c0U, 0x00000160U, 0x00000ad0U, 0x08080009U);

            r_rsip_func_sub001(0x00000208U, 0x00000160U, 0x00000b18U, 0x08080009U);

            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000b60U, 0x08080009U);

            r_rsip_func_sub001(0x00000ad0U, 0x000009e0U, 0x00000110U, 0x0808000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x000009e0U, 0x00000ad0U, 0x00000110U, 0x0808000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000b18U, 0x00000a28U, 0x00000110U, 0x0808000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000a28U, 0x00000b18U, 0x00000110U, 0x0808000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xbad88468U), bswap_32big(0x73fa70f6U), bswap_32big(0xd82f664aU),
                           bswap_32big(0x031fffcdU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                WR1_PROG(REG_1018H, 0x00000a70U);
                r_rsip_func_sub003(0x00000070U, 0x00000c50U, 0x08080013U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0x954d3910U),
                               bswap_32big(0xda1b4896U),
                               bswap_32big(0xee693040U),
                               bswap_32big(0xe2fe7ae8U));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                r_rsip_func_sub003(0x000002f0U, 0x00000c50U, 0x08080014U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0xfeae9548U),
                               bswap_32big(0xf2a06da1U),
                               bswap_32big(0x4fc0b425U),
                               bswap_32big(0x26a58024U));
            }

            WR1_PROG(REG_1600H, 0x00000821U);

            WR1_PROG(REG_1404H, 0x14400000U);
            WR1_PROG(REG_1608H, 0x80900001U);
            r_rsip_func_sub002(0x03430041U);

            WR1_PROG(REG_1600H, 0x0000a420U);
            WR1_PROG(REG_1600H, 0x00000050U);

            WR1_PROG(REG_1404H, 0x13000000U);
            WR1_PROG(REG_1608H, 0x80900001U);
            r_rsip_func_sub002(0x03430041U);

            WR1_PROG(REG_1404H, 0x11600000U);
            r_rsip_func_sub002(0x00c000f1U);

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
                    r_rsip_func_sub002(0x00c0003dU);
                    r_rsip_func_sub002(0x00c20005U);
                    r_rsip_func_sub002(0x0002000dU);

                    r_rsip_func_sub001(0x000001c0U, 0x00000160U, 0x00000110U, 0x0808000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0808000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x249e5836U),
                                   bswap_32big(0xabc66244U),
                                   bswap_32big(0x606c531bU),
                                   bswap_32big(0x6f42e26bU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1014H, 0x00000250U);
                        r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x08080014U);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0x6d92a778U),
                                       bswap_32big(0x4ecf7844U),
                                       bswap_32big(0xdd9eac9bU),
                                       bswap_32big(0x0b94263dU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xc3729894U),
                                       bswap_32big(0xd7341b7aU),
                                       bswap_32big(0x2f1dad42U),
                                       bswap_32big(0x5747a9f8U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xe0e5fe6aU),
                                   bswap_32big(0x7620493dU),
                                   bswap_32big(0x6c406e36U),
                                   bswap_32big(0x48da7dc0U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x678b676bU),
                                       bswap_32big(0x2cc7db67U),
                                       bswap_32big(0x28119041U),
                                       bswap_32big(0x94720d30U));

                        WR1_PROG(REG_1404H, 0x11200000U);
                        r_rsip_func_sub002(0x00c00041U);

                        WR1_PROG(REG_1600H, 0x00007c05U);
                        WR1_PROG(REG_143CH, 0x00600000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                        {
                            r_rsip_func_sub001(0x000009e0U, 0x00000160U, 0x000003f0U, 0x08080009U);

                            r_rsip_func_sub001(0x00000a28U, 0x00000160U, 0x00000438U, 0x08080009U);

                            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000480U, 0x08080009U);

                            r_rsip_func101(bswap_32big(0xad9b81c4U),
                                           bswap_32big(0xd43a7e36U),
                                           bswap_32big(0xe706826bU),
                                           bswap_32big(0xfe24ed6bU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
                        {
                            r_rsip_func_sub001(0x00000ad0U, 0x00000160U, 0x000003f0U, 0x08080009U);

                            r_rsip_func_sub001(0x00000b18U, 0x00000160U, 0x00000438U, 0x08080009U);

                            r_rsip_func_sub001(0x00000b60U, 0x00000160U, 0x00000480U, 0x08080009U);

                            r_rsip_func101(bswap_32big(0xbf5e7a10U),
                                           bswap_32big(0x0a76436dU),
                                           bswap_32big(0xc9222b4dU),
                                           bswap_32big(0x518ba3d2U));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
                        {
                            r_rsip_func_sub001(0x00000bc0U, 0x00000160U, 0x000003f0U, 0x08080009U);

                            r_rsip_func_sub001(0x00000c08U, 0x00000160U, 0x00000438U, 0x08080009U);

                            r_rsip_func_sub001(0x00000c50U, 0x00000160U, 0x00000480U, 0x08080009U);

                            r_rsip_func101(bswap_32big(0x232ff655U),
                                           bswap_32big(0x0a4322c0U),
                                           bswap_32big(0xa1100469U),
                                           bswap_32big(0xfba69e68U));
                        }

                        WR1_PROG(REG_1404H, 0x11200000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                        r_rsip_func_sub002(0x00c0003dU);
                        r_rsip_func_sub002(0x00c20005U);
                        r_rsip_func_sub002(0x0002000dU);

                        r_rsip_func_sub001(0x000001c0U, 0x00000160U, 0x00000110U, 0x0808000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0808000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0x5a4e7440U),
                                       bswap_32big(0x1927f2daU),
                                       bswap_32big(0x0017b154U),
                                       bswap_32big(0xe4fc2e98U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            r_rsip_func_sub001(0x000003f0U, 0x00000160U, 0x00000110U, 0x0808000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000110U, 0x0808000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0xcac34c3cU),
                                           bswap_32big(0xce416f3cU),
                                           bswap_32big(0xb5c842f7U),
                                           bswap_32big(0x51b7f912U));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                r_rsip_func_sub001(0x000001c0U, 0x000003f0U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x000003f0U, 0x000001c0U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000208U, 0x00000438U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000438U, 0x00000208U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000250U, 0x00000480U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000480U, 0x00000250U, 0x00000110U, 0x0808000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func100(bswap_32big(0x6a098fd1U), bswap_32big(0xd427204eU),
                                               bswap_32big(0x3478b127U), bswap_32big(0xc1b858e2U));
                                WR1_PROG(REG_143CH, 0x00400000U);

                                if (CHCK_STS(REG_143CH, 22, 1))
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    WR1_PROG(REG_1018H, 0x00000480U);
                                    r_rsip_func_sub003(0x00000070U, 0x00000250U, 0x08080013U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xbf3994ddU), bswap_32big(0xc56d6cfdU),
                                                   bswap_32big(0x6f60de55U), bswap_32big(0x6f86e857U));
                                }
                                else
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x08080014U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xb9352a35U), bswap_32big(0xb62d53edU),
                                                   bswap_32big(0xda436f56U), bswap_32big(0xbb8e52bbU));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0x33a8cb47U), bswap_32big(0x7b4b128cU),
                                               bswap_32big(0xe2b6754eU), bswap_32big(0x59b74136U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x11200000U);
                            r_rsip_func_sub002(0x00c00041U);

                            r_rsip_func_sub001(0x000003f0U, 0x00000160U, 0x000001c0U, 0x08080009U);

                            r_rsip_func_sub001(0x00000438U, 0x00000160U, 0x00000208U, 0x08080009U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000250U, 0x08080009U);

                            r_rsip_func101(bswap_32big(0x51c8bd08U),
                                           bswap_32big(0xb72c9019U),
                                           bswap_32big(0x0900f0e4U),
                                           bswap_32big(0x8e8e6167U));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x0812f1b1U),
                                       bswap_32big(0x9bdfdbe5U),
                                       bswap_32big(0x78583637U),
                                       bswap_32big(0x871aad66U));
                    }

                    WR1_PROG(REG_1600H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0x20fc2467U),
                                   bswap_32big(0x30515322U),
                                   bswap_32big(0x7095c208U),
                                   bswap_32big(0x3e19c9c8U));
                }

                WR1_PROG(REG_1600H, 0x38008840U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x5d175a92U),
                               bswap_32big(0x831a1017U),
                               bswap_32big(0x4c26afb9U),
                               bswap_32big(0x7d9b3e5bU));
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
            r_rsip_func_sub002(0x00c0003dU);
            r_rsip_func_sub002(0x00c20005U);
            r_rsip_func_sub002(0x0002000dU);

            r_rsip_func_sub001(0x00000250U, 0x000002a0U, 0x000002f0U, 0x0808000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xe46c269aU), bswap_32big(0x87f26ee9U), bswap_32big(0x1b358840U),
                           bswap_32big(0x408e8353U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0xbf9819a4U),
                               bswap_32big(0x676eda8fU),
                               bswap_32big(0xcaf21897U),
                               bswap_32big(0xd750ef71U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x00be8870U),
                               bswap_32big(0x4202d626U),
                               bswap_32big(0xcabd94ebU),
                               bswap_32big(0xb340c0cfU));

                WR1_PROG(REG_1014H, 0x00000250U);
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x08080004U);

                WR1_PROG(REG_1404H, 0x11200000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                r_rsip_func_sub002(0x00c0003dU);
                r_rsip_func_sub002(0x00c20005U);
                r_rsip_func_sub002(0x0002000dU);

                r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x00000110U, 0x0808000aU);

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
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x08080002U);

                r_rsip_func_sub001(0x000002a0U, 0x00000930U, 0x000001b0U, 0x0808000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func_sub001(0x00000930U, 0x000002a0U, 0x000001b0U, 0x0808000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0xa3b6a580U),
                               bswap_32big(0x991cc0b4U),
                               bswap_32big(0xd5c121dcU),
                               bswap_32big(0xa3324b95U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0xcca0c364U),
                                   bswap_32big(0x2eddf876U),
                                   bswap_32big(0x7d738bd8U),
                                   bswap_32big(0xfbbc069eU));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0x797935bbU);

                    r_rsip_func101(bswap_32big(0x3edf04c6U),
                                   bswap_32big(0x8f9bd110U),
                                   bswap_32big(0x765237d2U),
                                   bswap_32big(0xe27a29e3U));
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

        r_rsip_func100(bswap_32big(0x00f9ba66U), bswap_32big(0xf8179214U), bswap_32big(0x9f758430U),
                       bswap_32big(0x5c5e453fU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x56870795U), bswap_32big(0xbf6a8b0dU), bswap_32big(0xdff875d5U),
                           bswap_32big(0x0a9df613U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0xcd2ca957U), bswap_32big(0x7d0c2da1U), bswap_32big(0x996cbe10U),
                           bswap_32big(0x25014c80U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
