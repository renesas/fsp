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

rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[],
                       const uint32_t InData_Certificate[],
                       const uint32_t InData_CertificateLength[],
                       const uint32_t InData_CertificatePubKey[],
                       const uint32_t InData_EncCertificateInfo[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t iTemp = 0U;

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

    WR1_PROG(REG_1600H, 0x3420a9e0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xe5f859edU),
                   bswap_32big(0x53931fd1U),
                   bswap_32big(0x637e9996U),
                   bswap_32big(0xd1d925beU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x16dedb43U), bswap_32big(0x20dd646eU), bswap_32big(0x00a1a904U),
                       bswap_32big(0x958fcf49U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x3000a9e0U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x0000b5e0U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x3000a9e0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1600H, 0x0000b5c0U);
        WR1_PROG(REG_1600H, 0x010f6caaU);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x00000008U);
        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1600H, 0x0000b5c0U);
        WR1_PROG(REG_1600H, 0x01f6c222U);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x0000000cU);
        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1600H, 0x0000b5c0U);
        WR1_PROG(REG_1600H, 0x013a8e02U);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x00000010U);
        WR1_PROG(REG_1600H, 0x00000080U);

        r_rsip_func100(bswap_32big(0x83d70f4aU), bswap_32big(0x3915f1c7U), bswap_32big(0x37aa821dU),
                       bswap_32big(0xc7bd81c4U));
        WR1_PROG(REG_1608H, 0x81010200U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

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

        r_rsip_func101(bswap_32big(0x5e4bcd2aU), bswap_32big(0x63e05642U), bswap_32big(0x9d5a0a47U),
                       bswap_32big(0x042ab940U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x000034eeU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e101U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xc9540137U), bswap_32big(0xd995ff31U), bswap_32big(0xb0a7cf4eU),
                       bswap_32big(0xc2e287a6U));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1600H, 0x000008a5U);

        WR1_PROG(REG_1600H, 0x00000800U);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_EncCertificateInfo[1 + iLoop]);

            WR1_PROG(REG_1608H, 0x80840000U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000a400U);
            WR1_PROG(REG_1600H, 0x00000010U);

            WR1_PROG(REG_1600H, 0x0000a4a0U);
            WR1_PROG(REG_1600H, 0x00000004U);

            r_rsip_func101(bswap_32big(0xe6724a0dU), bswap_32big(0x45c62eb2U), bswap_32big(0x2c607da4U),
                           bswap_32big(0x92de6debU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000a05U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncCertificateInfo[1 + iLoop]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xbf71ef6cU), bswap_32big(0xff5c0fdbU), bswap_32big(0xc76f6c8bU),
                       bswap_32big(0x4a4ebcfcU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xab87a1a5U), bswap_32big(0xf5e9b4b2U), bswap_32big(0x4265aa06U),
                           bswap_32big(0x0db6f774U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x436c46d0U), bswap_32big(0x2232724dU), bswap_32big(0xc21ccbedU),
                           bswap_32big(0x98124919U));

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

            WR1_PROG(REG_1600H, 0x00007c0fU);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
            {
                WR1_PROG(REG_2004H, 0x00000050U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00000010U);

                WR1_PROG(REG_1600H, 0x0000b5c0U);
                WR1_PROG(REG_1600H, 0x00000016U);

                r_rsip_func101(bswap_32big(0xda4b6533U),
                               bswap_32big(0x1c025110U),
                               bswap_32big(0x71e2cbd4U),
                               bswap_32big(0x2c58a25cU));
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
            {
                WR1_PROG(REG_2004H, 0x000000a0U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x0000002fU);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x0000002fU);

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00000018U);

                WR1_PROG(REG_1600H, 0x0000b5c0U);
                WR1_PROG(REG_1600H, 0x00000018U);

                r_rsip_func101(bswap_32big(0xda5e9b43U),
                               bswap_32big(0x4e68d3b0U),
                               bswap_32big(0x057fdaf4U),
                               bswap_32big(0xcc9075e4U));
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
            {
                WR1_PROG(REG_2004H, 0x000000b0U);

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0x00000041U);

                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1600H, 0x00000041U);

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00000028U);

                WR1_PROG(REG_1600H, 0x0000b5c0U);
                WR1_PROG(REG_1600H, 0x00000024U);

                r_rsip_func101(bswap_32big(0x4ed62bbbU),
                               bswap_32big(0x688da3d5U),
                               bswap_32big(0x69411f6eU),
                               bswap_32big(0x8fcb96adU));
            }

            WR1_PROG(REG_1600H, 0x3c002b3aU);
            WR1_PROG(REG_1600H, 0x1000d3e0U);

            WR1_PROG(REG_1600H, 0x00002439U);
            WR1_PROG(REG_1600H, 0x0800283aU);
            WR1_PROG(REG_1600H, 0x2000d3e0U);

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

            r_rsip_func100(bswap_32big(0x210dd939U), bswap_32big(0xa6fa5d65U), bswap_32big(0xf8e493c7U),
                           bswap_32big(0x7ce6069dU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd6b295b5U),
                               bswap_32big(0x3ad60ee7U),
                               bswap_32big(0xdbcd1aa8U),
                               bswap_32big(0xd614eb62U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x73486254U),
                               bswap_32big(0xbbf45fa9U),
                               bswap_32big(0xc0f6e844U),
                               bswap_32big(0xb505eb78U));
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

                r_rsip_func100(bswap_32big(0xf6fb9f58U),
                               bswap_32big(0x27c206bdU),
                               bswap_32big(0x80d37382U),
                               bswap_32big(0x2a4bb405U));
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

                    r_rsip_func101(bswap_32big(0x4ca9e6c5U),
                                   bswap_32big(0xe7815412U),
                                   bswap_32big(0xfaa581e6U),
                                   bswap_32big(0x7bdc5bb4U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0xa3a2237bU),
                               bswap_32big(0x0255990cU),
                               bswap_32big(0x5c95da1cU),
                               bswap_32big(0x89730260U));

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

                iTemp = iLoop;
                for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
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

                        r_rsip_func100(bswap_32big(0xd7cd7b1bU),
                                       bswap_32big(0xc193483eU),
                                       bswap_32big(0xf9aa9cf8U),
                                       bswap_32big(0xb860ae74U));
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

                            r_rsip_func101(bswap_32big(0x2de13bf2U),
                                           bswap_32big(0x2301380bU),
                                           bswap_32big(0xdeef4966U),
                                           bswap_32big(0x6ea2cf50U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c002857U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x3c002b02U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0xd35ad9b2U),
                                       bswap_32big(0xb83f554dU),
                                       bswap_32big(0xcd8096b0U),
                                       bswap_32big(0x680eb5afU));
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

                            r_rsip_func101(bswap_32big(0x89cf42a5U),
                                           bswap_32big(0x1db03debU),
                                           bswap_32big(0x70d34219U),
                                           bswap_32big(0x7f6514d1U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c0028c2U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x23a8a71dU),
                                       bswap_32big(0xa33043d8U),
                                       bswap_32big(0x942d1c09U),
                                       bswap_32big(0x38fc3a44U));
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

                            r_rsip_func101(bswap_32big(0x106a1855U),
                                           bswap_32big(0x2c84008fU),
                                           bswap_32big(0x2f7114bcU),
                                           bswap_32big(0xa3aa0502U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);

                        r_rsip_func101(bswap_32big(0xdd5098a9U),
                                       bswap_32big(0xcdf89368U),
                                       bswap_32big(0x5c8beeb2U),
                                       bswap_32big(0x5ec4ecc9U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008820U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xe304a236U),
                                   bswap_32big(0xcfc87fbdU),
                                   bswap_32big(0x1c697c4cU),
                                   bswap_32big(0x7f2d6214U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0x4b3a5963U),
                               bswap_32big(0xade90730U),
                               bswap_32big(0xf3f2200cU),
                               bswap_32big(0xf0f4cd82U));
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

                    r_rsip_func101(bswap_32big(0xd9c8773eU),
                                   bswap_32big(0x715d13dcU),
                                   bswap_32big(0xa3718a88U),
                                   bswap_32big(0x72d67ac0U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000845U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x00000800U);

                r_rsip_func100(bswap_32big(0x877f9088U),
                               bswap_32big(0x72e44acbU),
                               bswap_32big(0xfe563c0dU),
                               bswap_32big(0xddc1d601U));
                WR1_PROG(REG_1608H, 0x81010200U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x000008a5U);

                WR1_PROG(REG_1600H, 0x00000bffU);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_1608H, 0x80010020U);
                    WR1_PROG(REG_1400H, 0x03450005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00003840U);

                    WR1_PROG(REG_1600H, 0x08002822U);
                    WR1_PROG(REG_1600H, 0x2000d3e0U);

                    WR1_PROG(REG_1600H, 0x0000a400U);
                    WR1_PROG(REG_1600H, 0x00000004U);

                    WR1_PROG(REG_1600H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xaab0dd0bU),
                                   bswap_32big(0x47b20ff5U),
                                   bswap_32big(0x426b7c2eU),
                                   bswap_32big(0xba5ed4cbU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000a05U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000fffU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                r_rsip_func100(bswap_32big(0x67e4d98eU),
                               bswap_32big(0x61f29891U),
                               bswap_32big(0x212764d3U),
                               bswap_32big(0x5c7d3fcbU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xac65695fU),
                                   bswap_32big(0x4744d87dU),
                                   bswap_32big(0x312610d1U),
                                   bswap_32big(0x0bf34fefU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x380089e0U);
                    WR1_PROG(REG_1600H, 0x00000005U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    r_rsip_func100(bswap_32big(0x9c9ae4eeU),
                                   bswap_32big(0xe9a63f5bU),
                                   bswap_32big(0x1635412aU),
                                   bswap_32big(0x1f00e4f2U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);

                        WR1_PROG(REG_1608H, 0x80a80000U);

                        WR1_PROG(REG_1400H, 0x13400039U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1404H, 0x10000000U);
                        WR1_PROG(REG_1400H, 0x13430109U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1400H, 0x13400039U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1400H, 0x13430109U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1404H, 0x10000000U);
                        WR1_PROG(REG_1608H, 0x81a80000U);
                        WR1_PROG(REG_1400H, 0x00c900a1U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        r_rsip_func101(bswap_32big(0xd76b2013U),
                                       bswap_32big(0x3ff4463cU),
                                       bswap_32big(0x336f2d0aU),
                                       bswap_32big(0x89661fc2U));
                    }

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x000000e1U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0xdd63be91U),
                                   bswap_32big(0xcfc27455U),
                                   bswap_32big(0xdb0855b9U),
                                   bswap_32big(0xf226fedcU));
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

                    r_rsip_func101(bswap_32big(0xeb6f5947U),
                                   bswap_32big(0x151c1644U),
                                   bswap_32big(0x81c8cb11U),
                                   bswap_32big(0x86206473U));
                    r_rsip_func043();

                    WR1_PROG(REG_1600H, 0x000034eeU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0xa77ef16fU),
                                   bswap_32big(0xea9e995fU),
                                   bswap_32big(0x91934b4aU),
                                   bswap_32big(0x84159788U));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0xabe3b7a4U),
                                   bswap_32big(0x9c77a9a4U),
                                   bswap_32big(0xc8e6bf51U),
                                   bswap_32big(0xbd315ed7U));
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

                        r_rsip_func100(bswap_32big(0x016b8e8cU),
                                       bswap_32big(0x05e9e3e6U),
                                       bswap_32big(0x7009f85dU),
                                       bswap_32big(0x4f281387U));
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

                        r_rsip_func101(bswap_32big(0xff204b58U),
                                       bswap_32big(0x42605f17U),
                                       bswap_32big(0x5c4fc156U),
                                       bswap_32big(0xf2a74e8fU));
                        iLoop = iLoop + 4U;
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x380008bbU);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0x2f52cb5dU),
                                   bswap_32big(0xd4c47d2dU),
                                   bswap_32big(0xff999268U),
                                   bswap_32big(0xac060899U));
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

                    r_rsip_func100(bswap_32big(0x0503370eU),
                                   bswap_32big(0x610cd23bU),
                                   bswap_32big(0x30c1277dU),
                                   bswap_32big(0xe9173370U));
                    WR1_PROG(REG_1608H, 0x81010000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x3a337037U),
                                   bswap_32big(0x63115e8dU),
                                   bswap_32big(0x3854e7acU),
                                   bswap_32big(0xe5c72bf7U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
