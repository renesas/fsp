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

rsip_ret_t r_rsip_pf6 (const uint32_t InData_CurveType[],
                       const uint32_t InData_KeyIndex[],
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

    WR1_PROG(REG_1B00H, 0x00f60001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010340U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_CurveType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000f6U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xbbc2583fU),
                   bswap_32big(0x0b77e50aU),
                   bswap_32big(0x47376bcbU),
                   bswap_32big(0xe796333bU));
    r_rsip_func043();

    r_rsip_func077();

    WR1_PROG(REG_1600H, 0x000034feU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000f6U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xe0fcd2bdU),
                   bswap_32big(0x5dff2296U),
                   bswap_32big(0xc7b73718U),
                   bswap_32big(0x9c0d7097U));
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
    r_rsip_func_sub002(0x03420031U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[13]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[17]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[21]);
    r_rsip_func_sub002(0x03420031U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[25]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    r_rsip_func_sub002(0x00820011U);

    r_rsip_func100(bswap_32big(0xdd4d4326U),
                   bswap_32big(0xecc32e1bU),
                   bswap_32big(0x678374c8U),
                   bswap_32big(0xbeb6c400U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x004ac751U), bswap_32big(0x1eb6ba0aU), bswap_32big(0xfd56ee83U),
                       bswap_32big(0x84dcb049U));
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
        WR1_PROG(REG_1420H, bswap_32big(0x000000f6U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        r_rsip_func100(bswap_32big(0x7b32a97eU), bswap_32big(0xe8f46b19U), bswap_32big(0x61547683U),
                       bswap_32big(0x3e1a957bU));
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
        r_rsip_func_sub002(0x00c20031U);

        WR1_PROG(REG_1404H, 0x19500000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        r_rsip_func_sub002(0x00c20031U);

        WR1_PROG(REG_1404H, 0x11d00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_func_sub002(0x00c0002dU);
        r_rsip_func_sub002(0x00c20005U);
        r_rsip_func_sub002(0x0002000dU);

        r_rsip_func_sub001(0x000000c0U, 0x00000200U, 0x00000160U, 0x0606000aU);

        r_rsip_func_sub001(0x00000160U, 0x00000930U, 0x000001b0U, 0x0606000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000930U, 0x00000200U, 0x000001b0U, 0x0606000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000160U, 0x00000980U, 0x000001b0U, 0x0606000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000980U, 0x00000200U, 0x000001b0U, 0x0606000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xd0702932U), bswap_32big(0x67ebeff0U), bswap_32big(0xd9a33228U),
                       bswap_32big(0xf8cfc189U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0xaae76fecU), bswap_32big(0xddbd1d83U), bswap_32big(0x58986dacU),
                           bswap_32big(0x3724e93bU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x302f4ccfU), bswap_32big(0x369a3af5U), bswap_32big(0x959cb153U),
                           bswap_32big(0x4632d664U));

            r_rsip_func_sub001(0x00000160U, 0x00000200U, 0x000001b0U, 0x0606000aU);

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
            r_rsip_func_sub003(0x000000c0U, 0x00000160U, 0x06060002U);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x818c001fU);
            r_rsip_func_sub002(0x00c90031U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000480U, 0x06060002U);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000340U, 0x06060002U);

            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11300000U);
            r_rsip_func_sub002(0x00c00031U);

            WR1_PROG(REG_1404H, 0x19800000U);
            r_rsip_func_sub002(0x00c002d1U);

            WR1_PROG(REG_1014H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a70U, 0x06060004U);

            r_rsip_func_sub001(0x00000890U, 0x00000160U, 0x000002b8U, 0x06060009U);

            r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x000002f0U, 0x06060009U);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1608H, 0x818c0001U);
            r_rsip_func_sub002(0x00c90031U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a00U, 0x06060002U);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000030U);
            WR1_PROG(REG_1608H, 0x818c001fU);
            r_rsip_func_sub002(0x00c90031U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a38U, 0x06060002U);

            r_rsip_func100(bswap_32big(0xc0401041U), bswap_32big(0x8a4ba88bU), bswap_32big(0x6d3c7918U),
                           bswap_32big(0x4fb8407fU));
            r_rsip_func028(InData_DomainParam);

            r_rsip_func_sub001(0x000001e0U, 0x00000160U, 0x00000af0U, 0x06060009U);

            r_rsip_func_sub001(0x00000218U, 0x00000160U, 0x00000b28U, 0x06060009U);

            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000b60U, 0x06060009U);

            r_rsip_func_sub001(0x00000af0U, 0x00000a00U, 0x00000110U, 0x0606000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000a00U, 0x00000af0U, 0x00000110U, 0x0606000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000b28U, 0x00000a38U, 0x00000110U, 0x0606000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000a38U, 0x00000b28U, 0x00000110U, 0x0606000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xdc151ea5U), bswap_32big(0x190d8560U), bswap_32big(0x936bb66fU),
                           bswap_32big(0x3766db0aU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                WR1_PROG(REG_1018H, 0x00000a70U);
                r_rsip_func_sub003(0x00000070U, 0x00000c50U, 0x06060013U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0xf1fe4625U),
                               bswap_32big(0xbc007e74U),
                               bswap_32big(0x19fd1bfdU),
                               bswap_32big(0xdd83e8c3U));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                r_rsip_func_sub003(0x000002f0U, 0x00000c50U, 0x06060014U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0x245a8d17U),
                               bswap_32big(0x8ae1d93fU),
                               bswap_32big(0x55ff9c00U),
                               bswap_32big(0x2dde1392U));
            }

            WR1_PROG(REG_1600H, 0x00000821U);

            WR1_PROG(REG_1404H, 0x14500000U);
            WR1_PROG(REG_1608H, 0x808c0001U);
            r_rsip_func_sub002(0x03430031U);

            WR1_PROG(REG_1600H, 0x0000a420U);
            WR1_PROG(REG_1600H, 0x00000050U);

            WR1_PROG(REG_1404H, 0x13100000U);
            WR1_PROG(REG_1608H, 0x808c0001U);
            r_rsip_func_sub002(0x03430031U);

            WR1_PROG(REG_1404H, 0x11600000U);
            r_rsip_func_sub002(0x00c000f1U);

            WR1_PROG(REG_1600H, 0x00000821U);

            for (iLoop = 0U; iLoop < 12U; iLoop++)
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

                    WR1_PROG(REG_1404H, 0x11300000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    r_rsip_func_sub002(0x00c0002dU);
                    r_rsip_func_sub002(0x00c20005U);
                    r_rsip_func_sub002(0x0002000dU);

                    r_rsip_func_sub001(0x000001e0U, 0x00000160U, 0x00000110U, 0x0606000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0606000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x78488daeU),
                                   bswap_32big(0xa33ce35aU),
                                   bswap_32big(0x9c7e3896U),
                                   bswap_32big(0xcf165b32U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1014H, 0x00000250U);
                        r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x06060014U);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0x5904743eU),
                                       bswap_32big(0xc53b5d4aU),
                                       bswap_32big(0x28eeaf58U),
                                       bswap_32big(0x11663c56U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x1eb9f769U),
                                       bswap_32big(0xb418bd5dU),
                                       bswap_32big(0x5dd5ea57U),
                                       bswap_32big(0x3b5b332cU));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0x2d76c0acU),
                                   bswap_32big(0x7618c9fcU),
                                   bswap_32big(0x2d91762eU),
                                   bswap_32big(0x85d4f3c9U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x458705ccU),
                                       bswap_32big(0xe267b315U),
                                       bswap_32big(0xb4015c58U),
                                       bswap_32big(0x958400bcU));

                        WR1_PROG(REG_1404H, 0x11300000U);
                        r_rsip_func_sub002(0x00c00031U);

                        WR1_PROG(REG_1600H, 0x00007c05U);
                        WR1_PROG(REG_143CH, 0x00600000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                        {
                            r_rsip_func_sub001(0x00000a00U, 0x00000160U, 0x00000410U, 0x06060009U);

                            r_rsip_func_sub001(0x00000a38U, 0x00000160U, 0x00000448U, 0x06060009U);

                            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000480U, 0x06060009U);

                            r_rsip_func101(bswap_32big(0x17b5d499U),
                                           bswap_32big(0xfac09d37U),
                                           bswap_32big(0x19e9bfdeU),
                                           bswap_32big(0x5952342aU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
                        {
                            r_rsip_func_sub001(0x00000af0U, 0x00000160U, 0x00000410U, 0x06060009U);

                            r_rsip_func_sub001(0x00000b28U, 0x00000160U, 0x00000448U, 0x06060009U);

                            r_rsip_func_sub001(0x00000b60U, 0x00000160U, 0x00000480U, 0x06060009U);

                            r_rsip_func101(bswap_32big(0xc0042aa1U),
                                           bswap_32big(0xdd9fb291U),
                                           bswap_32big(0xa275e87dU),
                                           bswap_32big(0xebec268dU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
                        {
                            r_rsip_func_sub001(0x00000be0U, 0x00000160U, 0x00000410U, 0x06060009U);

                            r_rsip_func_sub001(0x00000c18U, 0x00000160U, 0x00000448U, 0x06060009U);

                            r_rsip_func_sub001(0x00000c50U, 0x00000160U, 0x00000480U, 0x06060009U);

                            r_rsip_func101(bswap_32big(0x307ebf99U),
                                           bswap_32big(0xcd78573eU),
                                           bswap_32big(0x698afb3eU),
                                           bswap_32big(0x0ed028cfU));
                        }

                        WR1_PROG(REG_1404H, 0x11300000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                        r_rsip_func_sub002(0x00c0002dU);
                        r_rsip_func_sub002(0x00c20005U);
                        r_rsip_func_sub002(0x0002000dU);

                        r_rsip_func_sub001(0x000001e0U, 0x00000160U, 0x00000110U, 0x0606000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0606000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0x6a073adaU),
                                       bswap_32big(0x43a0cfadU),
                                       bswap_32big(0x32c49c78U),
                                       bswap_32big(0xf38d2e41U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            r_rsip_func_sub001(0x00000410U, 0x00000160U, 0x00000110U, 0x0606000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000110U, 0x0606000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0x17fc605aU),
                                           bswap_32big(0x28a89aabU),
                                           bswap_32big(0x1425ac1fU),
                                           bswap_32big(0x1fd898a5U));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                r_rsip_func_sub001(0x000001e0U, 0x00000410U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000410U, 0x000001e0U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000218U, 0x00000448U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000448U, 0x00000218U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000250U, 0x00000480U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000480U, 0x00000250U, 0x00000110U, 0x0606000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func100(bswap_32big(0xe822ea65U), bswap_32big(0x254610d6U),
                                               bswap_32big(0x93efde2eU), bswap_32big(0xf7f525bfU));
                                WR1_PROG(REG_143CH, 0x00400000U);

                                if (CHCK_STS(REG_143CH, 22, 1))
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    WR1_PROG(REG_1018H, 0x00000480U);
                                    r_rsip_func_sub003(0x00000070U, 0x00000250U, 0x06060013U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x17bbf529U), bswap_32big(0x0c73b7caU),
                                                   bswap_32big(0x68fceefcU), bswap_32big(0xa0e4585dU));
                                }
                                else
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x06060014U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x5c601e67U), bswap_32big(0xab91835bU),
                                                   bswap_32big(0xf7500dd1U), bswap_32big(0x4c0721ccU));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0xaea03807U), bswap_32big(0x49514dadU),
                                               bswap_32big(0xe1045737U), bswap_32big(0xe97504a5U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x11300000U);
                            r_rsip_func_sub002(0x00c00031U);

                            r_rsip_func_sub001(0x00000410U, 0x00000160U, 0x000001e0U, 0x06060009U);

                            r_rsip_func_sub001(0x00000448U, 0x00000160U, 0x00000218U, 0x06060009U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000250U, 0x06060009U);

                            r_rsip_func101(bswap_32big(0xa9feff43U),
                                           bswap_32big(0x77d772dfU),
                                           bswap_32big(0xd5697b9cU),
                                           bswap_32big(0x3dd5bec1U));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x74f4c842U),
                                       bswap_32big(0x6b55e0d5U),
                                       bswap_32big(0x3ab7e5e0U),
                                       bswap_32big(0x2e581b0fU));
                    }

                    WR1_PROG(REG_1600H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0x58661d5cU),
                                   bswap_32big(0x307b56d8U),
                                   bswap_32big(0x3840358bU),
                                   bswap_32big(0x951d0d3aU));
                }

                WR1_PROG(REG_1600H, 0x38008840U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x054d23b7U),
                               bswap_32big(0x1a639893U),
                               bswap_32big(0x52a47e89U),
                               bswap_32big(0x17199521U));
            }

            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0x0000000cU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x12700000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            r_rsip_func_sub002(0x00c0002dU);
            r_rsip_func_sub002(0x00c20005U);
            r_rsip_func_sub002(0x0002000dU);

            r_rsip_func_sub001(0x00000250U, 0x000002a0U, 0x000002f0U, 0x0606000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xd9b9f22cU), bswap_32big(0xb2a5026cU), bswap_32big(0xffba9197U),
                           bswap_32big(0x02c27a15U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0xa26c9c9cU),
                               bswap_32big(0x579ded4aU),
                               bswap_32big(0x13041f6eU),
                               bswap_32big(0xae04a268U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x68d243dbU),
                               bswap_32big(0x81864761U),
                               bswap_32big(0xd34296afU),
                               bswap_32big(0xca5ba0fdU));

                WR1_PROG(REG_1014H, 0x00000250U);
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x06060004U);

                WR1_PROG(REG_1404H, 0x11300000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                r_rsip_func_sub002(0x00c0002dU);
                r_rsip_func_sub002(0x00c20005U);
                r_rsip_func_sub002(0x0002000dU);

                r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x00000110U, 0x0606000aU);

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
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x06060002U);

                r_rsip_func_sub001(0x000002a0U, 0x00000930U, 0x000001b0U, 0x0606000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func_sub001(0x00000930U, 0x000002a0U, 0x000001b0U, 0x0606000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x396ab264U),
                               bswap_32big(0xa4b4bcdaU),
                               bswap_32big(0x33643a68U),
                               bswap_32big(0x549ea493U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0x8b2bb26dU),
                                   bswap_32big(0x5de6c6ceU),
                                   bswap_32big(0x0fbe8043U),
                                   bswap_32big(0x28650794U));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0x797935bbU);

                    r_rsip_func101(bswap_32big(0x8d92baa8U),
                                   bswap_32big(0xfbd58e93U),
                                   bswap_32big(0xa600c8caU),
                                   bswap_32big(0x22c2e085U));
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

        r_rsip_func100(bswap_32big(0x2dcf05ffU), bswap_32big(0x91e573c9U), bswap_32big(0xc4577fc3U),
                       bswap_32big(0x817852c4U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xdbe846a4U), bswap_32big(0xd29e2f19U), bswap_32big(0x2f3393b8U),
                           bswap_32big(0x0fd59554U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0x0c055d02U), bswap_32big(0x353d4708U), bswap_32big(0x17c65129U),
                           bswap_32big(0x873ebf7fU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
