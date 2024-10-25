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

rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[],
                       const uint32_t InData_Certificate[],
                       const uint32_t InData_CertificateLength[],
                       const uint32_t InData_CertificatePubKey[],
                       const uint32_t InData_EncCertificateInfo[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e10001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800101e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Sel_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x380089e0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xcfbf3951U), bswap_32big(0x977ea710U), bswap_32big(0xd055fd84U), bswap_32big(0x3af66297U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xfebd8b63U), bswap_32big(0xa9f1b2e7U), bswap_32big(0x04cf48c8U), bswap_32big(0x2d56be86U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_EncCertificateInfo[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e101U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x52d8382cU), bswap_32big(0x7f83961bU), bswap_32big(0x49a9d75bU), bswap_32big(0xd67ac18eU));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x010f6caaU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e101U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x0226458aU), bswap_32big(0x9f783949U), bswap_32big(0x9fee3018U), bswap_32big(0xbf581733U));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncCertificateInfo[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncCertificateInfo[5]);

        WR1_PROG(REG_1824H, 0x08000045U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1824H, 0x08000055U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncCertificateInfo[9]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x2871f5b1U), bswap_32big(0xb9c40ba9U), bswap_32big(0xfb776662U), bswap_32big(0xb79bf0f7U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xc4c24b88U), bswap_32big(0x7b9bd4f1U), bswap_32big(0xce95c57cU), bswap_32big(0xc2aa0a42U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800102c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_CertificateLength[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x800402e0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_CertificatePubKey[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_CertificatePubKey[1]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_CertificatePubKey[2]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_CertificatePubKey[3]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_1600H, 0x00000bffU);

            WR1_PROG(REG_2004H, 0x00000050U);

            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x3c002b3aU);
            WR1_PROG(REG_1600H, 0x1000d3e0U);

            WR1_PROG(REG_1600H, 0x00002439U);
            WR1_PROG(REG_1600H, 0x0800283aU);
            WR1_PROG(REG_1600H, 0x2000d3e0U);

            WR1_PROG(REG_1600H, 0x0000b760U);
            WR1_PROG(REG_1600H, 0x00000010U);

            WR1_PROG(REG_1600H, 0x0000b5c0U);
            WR1_PROG(REG_1600H, 0x00000016U);

            WR1_PROG(REG_1600H, 0x3c002af8U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);

            WR1_PROG(REG_1600H, 0x3c002b19U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);

            WR1_PROG(REG_1600H, 0x00002417U);
            WR1_PROG(REG_1600H, 0x08002818U);
            WR1_PROG(REG_1600H, 0x2000d3e0U);

            WR1_PROG(REG_1600H, 0x3c002b56U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);

            WR1_PROG(REG_1600H, 0x38000fffU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x48066e54U), bswap_32big(0x5f0065eeU), bswap_32big(0xeb588ea0U), bswap_32big(0x2d5aeb0eU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xc99f2535U), bswap_32big(0xd66d36abU), bswap_32big(0x5cb5be0dU), bswap_32big(0x951a78d7U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe069815dU), bswap_32big(0x0b7ea1ddU), bswap_32big(0x44b81d5eU), bswap_32big(0x294c83caU));
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x00003436U);

                WR1_PROG(REG_1600H, 0x01836c01U);
                WR1_PROG(REG_1600H, 0x00036c21U);

                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                r_rsip_func100(bswap_32big(0x2c7831b2U), bswap_32big(0x98e13e25U), bswap_32big(0xbf467edbU), bswap_32big(0xcb699729U));
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, S_RAM[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, S_RAM[0 + 1]);

                WR1_PROG(REG_1600H, 0x00003417U);
                WR1_PROG(REG_1600H, 0x00046800U);
                WR1_PROG(REG_1600H, 0x00026c00U);

                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x000008a5U);

                for (iLoop = 0U; iLoop < S_RAM[0]; )
                {
                    WR1_PROG(REG_1444H, 0x000003c4U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_Certificate[iLoop]);

                    WR1_PROG(REG_1600H, 0x0000a4a0U);
                    WR1_PROG(REG_1600H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0x8f6baa02U), bswap_32big(0x41cb8ce6U), bswap_32big(0x8a2cdcf1U), bswap_32big(0x462d4a90U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0x9cc18001U), bswap_32big(0x3ad78182U), bswap_32big(0x91d1451cU), bswap_32big(0xa8e9e917U));

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1000H, 0x00010000U);
                WR1_PROG(REG_1404H, 0x10000000U);

                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1600H, 0x0000a400U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1600H, 0x00026800U);

                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x00003445U);
                WR1_PROG(REG_1600H, 0x00026c42U);

                WR1_PROG(REG_1600H, 0x000034d6U);
                WR1_PROG(REG_1600H, 0x000030c0U);

                for (; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x80010120U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_Certificate[iLoop]);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x00000821U);

                    for (jLoop = 0U; jLoop < 4; jLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x00002c20U);

                        WR1_PROG(REG_1600H, 0x01886d09U);
                        WR1_PROG(REG_1600H, 0x00086d29U);

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c002859U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x3c002b42U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x56431be3U), bswap_32big(0x51caffc1U), bswap_32big(0x4018caafU), bswap_32big(0x44fcc6e4U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0x5314fbebU), bswap_32big(0x565f1e2fU), bswap_32big(0xab7015ecU), bswap_32big(0xf38cab46U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c002857U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x3c002b02U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x4eb22e73U), bswap_32big(0xb954894aU), bswap_32big(0xbc088914U), bswap_32big(0xc9c1ebffU));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0x85cf35fbU), bswap_32big(0x8ef82df8U), bswap_32big(0xbc83e45eU), bswap_32big(0xa2cf7556U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c0028c2U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x45d614c5U), bswap_32big(0x43e1c85bU), bswap_32big(0x9a1ce580U), bswap_32big(0xd022554cU));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x11490005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0x04e0d38fU), bswap_32big(0xfb2e13e2U), bswap_32big(0xc0680497U), bswap_32big(0x54e6aec2U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);

                        r_rsip_func101(bswap_32big(0x6b3c0ee7U), bswap_32big(0x5ed6f322U), bswap_32big(0x7397cfbeU), bswap_32big(0x9f73020fU));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008820U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x4db45d9cU), bswap_32big(0x490a92c5U), bswap_32big(0x4dce2a6bU), bswap_32big(0xf87bc623U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0x221c8fc6U), bswap_32big(0xdeec510bU), bswap_32big(0xe2a1a66cU), bswap_32big(0xbe51fcd1U));
                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1600H, 0x00008c00U);
                WR1_PROG(REG_1600H, 0x00000003U);

                WR1_PROG(REG_1600H, 0x0000b440U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1600H, 0x00002840U);
                WR1_PROG(REG_1600H, 0x00008c40U);
                WR1_PROG(REG_1600H, 0x00000003U);

                WR1_PROG(REG_1608H, 0x81010040U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x000008a5U);

                WR1_PROG(REG_1600H, 0x00000863U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_1608H, 0x81010060U);
                    WR1_PROG(REG_1400H, 0x11490005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00086c63U);

                    WR1_PROG(REG_1600H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xb54e5c06U), bswap_32big(0x54e70687U), bswap_32big(0x47390f6fU), bswap_32big(0x9e11ffc3U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000845U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x00000800U);

                WR1_PROG(REG_1608H, 0x80880000U);
                WR1_PROG(REG_1400H, 0x03450021U);

                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1608H, 0x81880000U);
                WR1_PROG(REG_1824H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1824H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                r_rsip_func100(bswap_32big(0xb677a0c3U), bswap_32big(0x75f296ceU), bswap_32big(0xfe794ce5U), bswap_32big(0x58a66a0fU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x7a9168d2U), bswap_32big(0x44eb8a4dU), bswap_32big(0xa281c411U), bswap_32big(0x9c6af122U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x60210bceU), bswap_32big(0xce670b8aU), bswap_32big(0x1b80433bU), bswap_32big(0xee0dc507U));
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
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x3f0dc454U), bswap_32big(0x1dbf1e92U), bswap_32big(0x24030626U), bswap_32big(0x4e89f6b0U));
                    r_rsip_func043();

                    WR1_PROG(REG_1600H, 0x000034eeU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0xa77ef16fU), bswap_32big(0xea9e995fU), bswap_32big(0x91934b4aU), bswap_32big(0x84159788U));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0xabe3b7a4U), bswap_32big(0x9c77a9a4U), bswap_32big(0xc8e6bf51U), bswap_32big(0xbd315ed7U));
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000044U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000054U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                    WR1_PROG(REG_1608H, 0x81010360U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0]);
                    S_RAM[0] = bswap_32big(S_RAM[0]);

                    WR1_PROG(REG_1600H, 0x00000884U);
                    WR1_PROG(REG_1600H, 0x000008a5U);

                    WR1_PROG(REG_1404H, 0x10000000U);
                    for (iLoop = 0U; iLoop < S_RAM[0]; )
                    {
                        WR1_PROG(REG_1600H, 0x342028bbU);
                        WR1_PROG(REG_1600H, 0x2000d080U);
                        WR1_PROG(REG_1600H, 0x00007c04U);
                        WR1_PROG(REG_143CH, 0x00602000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        r_rsip_func100(bswap_32big(0x016b8e8cU), bswap_32big(0x05e9e3e6U), bswap_32big(0x7009f85dU), bswap_32big(0x4f281387U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008105U);
                        WR1_PROG(REG_1400H, 0x00830011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1 + iLoop]);

                        WR1_PROG(REG_1600H, 0x0000a4a0U);
                        WR1_PROG(REG_1600H, 0x00000004U);

                        r_rsip_func101(bswap_32big(0xff204b58U), bswap_32big(0x42605f17U), bswap_32big(0x5c4fc156U), bswap_32big(0xf2a74e8fU));
                        iLoop = iLoop + 4U;
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x380008bbU);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0x2f52cb5dU), bswap_32big(0xd4c47d2dU), bswap_32big(0xff999268U), bswap_32big(0xac060899U));
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
                    RD4_ADDR(REG_1420H, &OutData_KeyIndex[1 + iLoop]);

                    r_rsip_func100(bswap_32big(0x0503370eU), bswap_32big(0x610cd23bU), bswap_32big(0x30c1277dU), bswap_32big(0xe9173370U));
                    WR1_PROG(REG_1608H, 0x81010000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x3a337037U), bswap_32big(0x63115e8dU), bswap_32big(0x3854e7acU), bswap_32big(0xe5c72bf7U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
