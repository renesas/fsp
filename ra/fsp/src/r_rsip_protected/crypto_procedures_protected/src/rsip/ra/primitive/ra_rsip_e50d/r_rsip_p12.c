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

rsip_ret_t r_rsip_p12 (const uint32_t InData_KeyIndex[],
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

    WR1_PROG(REG_1B00H, 0x00120001U);
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
    WR1_PROG(REG_1420H, bswap_32big(0x00000012U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xe4e6f231U),
                   bswap_32big(0x94c64e63U),
                   bswap_32big(0x7c2c5fcfU),
                   bswap_32big(0x7d4f0af8U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000024U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000012U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd0b6038fU),
                   bswap_32big(0xb27eeb53U),
                   bswap_32big(0x2077b27eU),
                   bswap_32big(0x361d9115U));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000027c2U);
    WR1_PROG(REG_1A2CH, 0x40000900U);
    WR1_PROG(REG_1A24H, 0xe8009107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1608H, 0x80a80001U);
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
    r_rsip_func_sub002(0x03420021U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[21]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[25]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[29]);
    r_rsip_func_sub002(0x03420031U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[33]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[37]);
    r_rsip_func_sub002(0x03420021U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[41]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    r_rsip_func_sub002(0x00820011U);

    r_rsip_func100(bswap_32big(0x1abeb8e6U),
                   bswap_32big(0xfd779813U),
                   bswap_32big(0x97c75e33U),
                   bswap_32big(0x4a4f39c8U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5171e3e2U), bswap_32big(0xa5776a6bU), bswap_32big(0x72687beeU),
                       bswap_32big(0xbb81f80bU));
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
        WR1_PROG(REG_1420H, bswap_32big(0x00000012U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        r_rsip_func100(bswap_32big(0x7d7553e9U), bswap_32big(0x3bfdbf71U), bswap_32big(0x4b17eeb1U),
                       bswap_32big(0x1cf147f6U));
        r_rsip_func086(InData_DomainParam);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x09090010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x09090010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x18e00000U);
        WR1_PROG(REG_1444H, 0x000027c2U);
        WR1_PROG(REG_1A2CH, 0x00000900U);
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
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        r_rsip_func_sub002(0x00c20021U);

        WR1_PROG(REG_1404H, 0x19300000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[24]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[28]);
        r_rsip_func_sub002(0x00c20031U);

        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[32]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[36]);
        r_rsip_func_sub002(0x00c20021U);

        WR1_PROG(REG_1404H, 0x11b80000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_func_sub002(0x00c00045U);
        r_rsip_func_sub002(0x00c20005U);
        r_rsip_func_sub002(0x0002000dU);

        r_rsip_func_sub001(0x000000c0U, 0x00000200U, 0x00000160U, 0x0909000aU);

        r_rsip_func_sub001(0x00000160U, 0x00000930U, 0x000001b0U, 0x0909000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000930U, 0x00000200U, 0x000001b0U, 0x0909000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000160U, 0x00000980U, 0x000001b0U, 0x0909000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func_sub001(0x00000980U, 0x00000200U, 0x000001b0U, 0x0909000aU);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0x59cc1cccU), bswap_32big(0xee735e5bU), bswap_32big(0x5b29c997U),
                       bswap_32big(0x95f91d04U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x84ddcda9U), bswap_32big(0x0cd1d327U), bswap_32big(0x70f044eeU),
                           bswap_32big(0x8f8b0aecU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x4ebcf058U), bswap_32big(0x0cd163e8U), bswap_32big(0x56fe6533U),
                           bswap_32big(0x801c7524U));

            r_rsip_func_sub001(0x00000160U, 0x00000200U, 0x000001b0U, 0x0909000aU);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x0909000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000840U);
            r_rsip_func_sub003(0x000000c0U, 0x00000160U, 0x09090002U);

            WR1_PROG(REG_1404H, 0x10c00000U);
            r_rsip_func_sub002(0x00c00011U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x8190001fU);
            r_rsip_func_sub002(0x00c90041U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000480U, 0x09090002U);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_func_sub003(0x000000c0U, 0x00000340U, 0x09090002U);

            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11180000U);
            r_rsip_func_sub002(0x00c00049U);

            WR1_PROG(REG_1404H, 0x19800000U);
            r_rsip_func_sub002(0x00c002d1U);

            WR1_PROG(REG_1014H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a70U, 0x09090004U);

            r_rsip_func_sub001(0x00000890U, 0x00000160U, 0x000002a0U, 0x09090009U);

            r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x000002f0U, 0x09090009U);

            WR1_PROG(REG_1404H, 0x10c00000U);
            WR1_PROG(REG_1608H, 0x81940001U);
            r_rsip_func_sub002(0x00c90051U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x000009d0U, 0x09090002U);

            WR1_PROG(REG_1404H, 0x10c00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000050U);
            WR1_PROG(REG_1608H, 0x8194001fU);
            r_rsip_func_sub002(0x00c90051U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_func_sub003(0x00000070U, 0x00000a20U, 0x09090002U);

            r_rsip_func100(bswap_32big(0x7b3ee435U), bswap_32big(0x55c880dfU), bswap_32big(0x0f1dc185U),
                           bswap_32big(0x1405fd8aU));
            r_rsip_func087(InData_DomainParam);

            r_rsip_func_sub001(0x000001b0U, 0x00000160U, 0x00000ac0U, 0x09090009U);

            r_rsip_func_sub001(0x00000200U, 0x00000160U, 0x00000b10U, 0x09090009U);

            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000b60U, 0x09090009U);

            r_rsip_func_sub001(0x00000ac0U, 0x000009d0U, 0x00000110U, 0x0909000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x000009d0U, 0x00000ac0U, 0x00000110U, 0x0909000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000b10U, 0x00000a20U, 0x00000110U, 0x0909000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func_sub001(0x00000a20U, 0x00000b10U, 0x00000110U, 0x0909000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x3ceaf008U), bswap_32big(0xa9e8b676U), bswap_32big(0x0ba171c1U),
                           bswap_32big(0x0942acfdU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                WR1_PROG(REG_1018H, 0x00000a70U);
                r_rsip_func_sub003(0x00000070U, 0x00000c50U, 0x09090013U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0xab6fc217U),
                               bswap_32big(0x3b5bbeebU),
                               bswap_32big(0x0f8f2cc4U),
                               bswap_32big(0xc0e8e2acU));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b60U);
                r_rsip_func_sub003(0x000002f0U, 0x00000c50U, 0x09090014U);
                WR1_PROG(REG_143CH, 0x00000d00U);

                r_rsip_func101(bswap_32big(0x322ab825U),
                               bswap_32big(0xa7480ae3U),
                               bswap_32big(0x0e2e0c65U),
                               bswap_32big(0x4e51f04eU));
            }

            WR1_PROG(REG_1600H, 0x00000821U);

            WR1_PROG(REG_1404H, 0x14380000U);
            WR1_PROG(REG_1608H, 0x80920001U);
            r_rsip_func_sub002(0x03430049U);

            WR1_PROG(REG_1600H, 0x0000a420U);
            WR1_PROG(REG_1600H, 0x00000050U);

            WR1_PROG(REG_1404H, 0x12f80000U);
            WR1_PROG(REG_1608H, 0x80920001U);
            r_rsip_func_sub002(0x03430049U);

            WR1_PROG(REG_1404H, 0x11600000U);
            r_rsip_func_sub002(0x00c000f1U);

            WR1_PROG(REG_1600H, 0x00000821U);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
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

                    WR1_PROG(REG_1404H, 0x11180000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    r_rsip_func_sub002(0x00c00045U);
                    r_rsip_func_sub002(0x00c20005U);
                    r_rsip_func_sub002(0x0002000dU);

                    r_rsip_func_sub001(0x000001b0U, 0x00000160U, 0x00000110U, 0x0909000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0909000aU);

                    WR1_PROG(REG_143CH, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x05c86752U),
                                   bswap_32big(0xf3b94837U),
                                   bswap_32big(0x20890582U),
                                   bswap_32big(0x452d3f20U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1014H, 0x00000250U);
                        r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x09090014U);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0xe4e6a977U),
                                       bswap_32big(0x35784319U),
                                       bswap_32big(0xbd76059fU),
                                       bswap_32big(0x0320b22fU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xb620a53aU),
                                       bswap_32big(0xb2b89a42U),
                                       bswap_32big(0xf93cc3c5U),
                                       bswap_32big(0x29489552U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xc1678e6dU),
                                   bswap_32big(0x260e24e3U),
                                   bswap_32big(0xd8aef2dfU),
                                   bswap_32big(0xdf404a02U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x08ff7922U),
                                       bswap_32big(0x39b9d7e2U),
                                       bswap_32big(0x8d291d06U),
                                       bswap_32big(0x8bb98510U));

                        WR1_PROG(REG_1404H, 0x11180000U);
                        r_rsip_func_sub002(0x00c00049U);

                        WR1_PROG(REG_1600H, 0x00007c05U);
                        WR1_PROG(REG_143CH, 0x00600000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                        {
                            r_rsip_func_sub001(0x000009d0U, 0x00000160U, 0x000003e0U, 0x09090009U);

                            r_rsip_func_sub001(0x00000a20U, 0x00000160U, 0x00000430U, 0x09090009U);

                            r_rsip_func_sub001(0x00000a70U, 0x00000160U, 0x00000480U, 0x09090009U);

                            r_rsip_func101(bswap_32big(0x220bbd69U),
                                           bswap_32big(0xe1061fbbU),
                                           bswap_32big(0x78272fa5U),
                                           bswap_32big(0x8acafd4aU));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
                        {
                            r_rsip_func_sub001(0x00000ac0U, 0x00000160U, 0x000003e0U, 0x09090009U);

                            r_rsip_func_sub001(0x00000b10U, 0x00000160U, 0x00000430U, 0x09090009U);

                            r_rsip_func_sub001(0x00000b60U, 0x00000160U, 0x00000480U, 0x09090009U);

                            r_rsip_func101(bswap_32big(0x94e021a6U),
                                           bswap_32big(0x3f69a9eaU),
                                           bswap_32big(0x98458254U),
                                           bswap_32big(0x9d5500e9U));
                        }
                        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
                        {
                            r_rsip_func_sub001(0x00000bb0U, 0x00000160U, 0x000003e0U, 0x09090009U);

                            r_rsip_func_sub001(0x00000c00U, 0x00000160U, 0x00000430U, 0x09090009U);

                            r_rsip_func_sub001(0x00000c50U, 0x00000160U, 0x00000480U, 0x09090009U);

                            r_rsip_func101(bswap_32big(0x5388c928U),
                                           bswap_32big(0x470d4f32U),
                                           bswap_32big(0x455a67c5U),
                                           bswap_32big(0xd873818fU));
                        }

                        WR1_PROG(REG_1404H, 0x11180000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                        r_rsip_func_sub002(0x00c00045U);
                        r_rsip_func_sub002(0x00c20005U);
                        r_rsip_func_sub002(0x0002000dU);

                        r_rsip_func_sub001(0x000001b0U, 0x00000160U, 0x00000110U, 0x0909000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func_sub001(0x00000250U, 0x00000160U, 0x00000110U, 0x0909000aU);

                        WR1_PROG(REG_143CH, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0xe6e64432U),
                                       bswap_32big(0xaeb5b8b6U),
                                       bswap_32big(0x0ce3b61eU),
                                       bswap_32big(0x3f6b7f24U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            r_rsip_func_sub001(0x000003e0U, 0x00000160U, 0x00000110U, 0x0909000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000110U, 0x0909000aU);

                            WR1_PROG(REG_143CH, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0x9e90facdU),
                                           bswap_32big(0xe7c503d6U),
                                           bswap_32big(0x9dd18390U),
                                           bswap_32big(0x70d19cadU));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                r_rsip_func_sub001(0x000001b0U, 0x000003e0U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x000003e0U, 0x000001b0U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000200U, 0x00000430U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000430U, 0x00000200U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000250U, 0x00000480U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func_sub001(0x00000480U, 0x00000250U, 0x00000110U, 0x0909000aU);

                                WR1_PROG(REG_143CH, 0x00210000U);

                                r_rsip_func100(bswap_32big(0xf0289b69U), bswap_32big(0x57318414U),
                                               bswap_32big(0xb170ae0bU), bswap_32big(0xdf2ef331U));
                                WR1_PROG(REG_143CH, 0x00400000U);

                                if (CHCK_STS(REG_143CH, 22, 1))
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    WR1_PROG(REG_1018H, 0x00000480U);
                                    r_rsip_func_sub003(0x00000070U, 0x00000250U, 0x09090013U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0x3411a5e4U), bswap_32big(0x4a6d4f01U),
                                                   bswap_32big(0x0b14a29cU), bswap_32big(0x080456e1U));
                                }
                                else
                                {
                                    WR1_PROG(REG_1014H, 0x00000250U);
                                    r_rsip_func_sub003(0x000002f0U, 0x00000250U, 0x09090014U);
                                    WR1_PROG(REG_143CH, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xdde60c76U), bswap_32big(0xf2017836U),
                                                   bswap_32big(0x011a6ed8U), bswap_32big(0x7447746eU));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0x1c003eb7U), bswap_32big(0x21ff4999U),
                                               bswap_32big(0xbbe3f19aU), bswap_32big(0x56a52d85U));
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x11180000U);
                            r_rsip_func_sub002(0x00c00049U);

                            r_rsip_func_sub001(0x000003e0U, 0x00000160U, 0x000001b0U, 0x09090009U);

                            r_rsip_func_sub001(0x00000430U, 0x00000160U, 0x00000200U, 0x09090009U);

                            r_rsip_func_sub001(0x00000480U, 0x00000160U, 0x00000250U, 0x09090009U);

                            r_rsip_func101(bswap_32big(0x5974953dU),
                                           bswap_32big(0x0451234dU),
                                           bswap_32big(0x8c13ab0fU),
                                           bswap_32big(0x2e39e063U));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x4f712ed6U),
                                       bswap_32big(0x2e299e13U),
                                       bswap_32big(0xfecaf5b9U),
                                       bswap_32big(0x831785c2U));
                    }

                    WR1_PROG(REG_1600H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0xb7673bffU),
                                   bswap_32big(0xf57300acU),
                                   bswap_32big(0xcd18562aU),
                                   bswap_32big(0x9d6455d2U));
                }

                WR1_PROG(REG_1600H, 0x38008840U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x14b0be08U),
                               bswap_32big(0xe1a8a3feU),
                               bswap_32big(0xbcfb5bf2U),
                               bswap_32big(0x94a19ef2U));
            }

            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0x00000012U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x12580000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            r_rsip_func_sub002(0x00c00045U);
            r_rsip_func_sub002(0x00c20005U);
            r_rsip_func_sub002(0x0002000dU);

            r_rsip_func_sub001(0x00000250U, 0x000002a0U, 0x000002f0U, 0x0909000aU);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x433743e9U), bswap_32big(0x86be0732U), bswap_32big(0x02ccdc65U),
                           bswap_32big(0x0a3986a4U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x75ad8378U),
                               bswap_32big(0x788f0be7U),
                               bswap_32big(0x596a5c5fU),
                               bswap_32big(0xd6ef8398U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x1e956984U),
                               bswap_32big(0x0f59ae25U),
                               bswap_32big(0xabe5ea18U),
                               bswap_32big(0xb823b68dU));

                WR1_PROG(REG_1014H, 0x00000250U);
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x09090004U);

                WR1_PROG(REG_1404H, 0x11180000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                r_rsip_func_sub002(0x00c00045U);
                r_rsip_func_sub002(0x00c20005U);
                r_rsip_func_sub002(0x0002000dU);

                r_rsip_func_sub001(0x00000070U, 0x00000160U, 0x00000110U, 0x0909000aU);

                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000160U);

                WR1_PROG(REG_1004H, 0x0909000fU);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1014H, 0x000001b0U);
                WR1_PROG(REG_1018H, 0x00000160U);
                r_rsip_func_sub003(0x00000070U, 0x000002a0U, 0x09090002U);

                r_rsip_func_sub001(0x000002a0U, 0x00000930U, 0x000001b0U, 0x0909000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func_sub001(0x00000930U, 0x000002a0U, 0x000001b0U, 0x0909000aU);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x2ae41089U),
                               bswap_32big(0x97da58c1U),
                               bswap_32big(0x457b097aU),
                               bswap_32big(0xef2b8cb5U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0xdc972363U),
                                   bswap_32big(0xc30a36d0U),
                                   bswap_32big(0xa11998b0U),
                                   bswap_32big(0x3656289aU));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000b400U);
                    WR1_PROG(REG_1600H, 0x797935bbU);

                    r_rsip_func101(bswap_32big(0xfd99d8f4U),
                                   bswap_32big(0x82ec05c6U),
                                   bswap_32big(0xf5c27e69U),
                                   bswap_32big(0x797c3cfdU));
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

        r_rsip_func100(bswap_32big(0xf1ebfcbdU), bswap_32big(0x6290c228U), bswap_32big(0xe1c40b54U),
                       bswap_32big(0x2085c6cdU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x5c5ef3b1U), bswap_32big(0x6d324abeU), bswap_32big(0xbf1df9f2U),
                           bswap_32big(0x8ac0b838U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0x9dd89bb0U), bswap_32big(0x49925296U), bswap_32big(0x9f276718U),
                           bswap_32big(0x35eabe42U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
