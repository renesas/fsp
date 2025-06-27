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

rsip_ret_t r_rsip_p8f (const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_WrappedKeyType[],
                       const uint32_t InData_WrappedKeyIndex[],
                       uint32_t       OutData_Text[],
                       uint32_t       KEY_INDEX_SIZE,
                       uint32_t       WRAPPED_KEY_SIZE)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14B4H, 0x0000001dU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x008f0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x80020100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_WrappedKeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00003409U);

    WR1_PROG(REG_1600H, 0x3420a900U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x028a0cbbU),
                   bswap_32big(0x40697bf1U),
                   bswap_32big(0x1816f508U),
                   bswap_32big(0x6c044d0eU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x48e2ca3cU), bswap_32big(0xba015e40U), bswap_32big(0xeece954bU),
                       bswap_32big(0x09e53f29U));
        WR1_PROG(REG_14B4H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00008f01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe2c5515dU), bswap_32big(0x629ac68bU), bswap_32big(0x9b8282ccU),
                       bswap_32big(0x3fd2c138U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x38000d08U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x0e2189e0U), bswap_32big(0x1e75781cU), bswap_32big(0x6def5d24U),
                       bswap_32big(0x87f14c42U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000005U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00008f01U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x053bef49U), bswap_32big(0x8641d4b2U), bswap_32big(0xb6e32ec2U),
                           bswap_32big(0x58ef0673U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x761b584cU), bswap_32big(0x0539381bU), bswap_32big(0x7adc43e3U),
                           bswap_32big(0x0b25fb8eU));
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_182CH, 0x00000000U);

            r_rsip_func101(bswap_32big(0x195a4dc1U), bswap_32big(0x7b015d19U), bswap_32big(0xa7b9599fU),
                           bswap_32big(0x683928c1U));
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000007U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00008f02U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x47736210U), bswap_32big(0x3e1ae5bcU), bswap_32big(0xdc81757aU),
                           bswap_32big(0xfdd99ba4U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0xc2c71bf6U), bswap_32big(0x795d20c4U), bswap_32big(0x18121a7cU),
                           bswap_32big(0xec06ff95U));
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xf7009d07U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x58e3d241U), bswap_32big(0x312e4e4eU), bswap_32big(0x40f10a05U),
                           bswap_32big(0xf21f15feU));
            WR1_PROG(REG_1824H, 0x08000095U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

            WR1_PROG(REG_182CH, 0x40000000U);

            r_rsip_func101(bswap_32big(0x49aedde1U), bswap_32big(0x8b816fdaU), bswap_32big(0xcae25c76U),
                           bswap_32big(0x70a88ae5U));
        }

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xfdb7088dU), bswap_32big(0x93fc06b3U), bswap_32big(0x07fc0f7eU),
                       bswap_32big(0x5eb38b57U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x8d4ff5f1U), bswap_32big(0xd2545684U), bswap_32big(0x6b56ebe0U),
                           bswap_32big(0x221d6b1aU));
            WR1_PROG(REG_14B4H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            r_rsip_func030();

            WR1_PROG(REG_1600H, 0x000035c7U);

            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800100e0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_WrappedKeyIndex[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00008f02U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xb62b748dU), bswap_32big(0x8fbd6610U), bswap_32big(0xa9c91c45U),
                           bswap_32big(0xc9240f9eU));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x000034e6U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00008f03U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x395b3e5bU), bswap_32big(0x1d52f6f8U), bswap_32big(0x5f34bef1U),
                           bswap_32big(0x40236ddfU));
            r_rsip_func044();

            WR1_PROG(REG_1600H, 0x000034eeU);

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000044U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000054U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1600H, 0x0000b7e0U);
            WR1_PROG(REG_1600H, 0x00000008U);

            WR1_PROG(REG_1600H, 0x0000b780U);
            WR1_PROG(REG_1600H, 0x00000010U);

            WR1_PROG(REG_1600H, 0x00000bdeU);

            WR1_PROG(REG_1600H, 0x0000b760U);
            WR1_PROG(REG_1600H, 0x00000004U);

            WR1_PROG(REG_1600H, 0x0000a8e0U);
            WR1_PROG(REG_1600H, 0x00000005U);

            for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
            {
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0xf7008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_WrappedKeyIndex[iLoop + 1]);

                WR1_PROG(REG_1608H, 0x8084001fU);
                WR1_PROG(REG_1400H, 0x03420011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x000027fcU);

                WR1_PROG(REG_1600H, 0x000027dbU);

                r_rsip_func101(bswap_32big(0x7f5cec79U),
                               bswap_32big(0x2be2151fU),
                               bswap_32big(0xabf0c984U),
                               bswap_32big(0x7f58aef6U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38000bc7U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_WrappedKeyIndex[iLoop + 1]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0xc7a1ed92U), bswap_32big(0xcfddade1U), bswap_32big(0x3a9c19e4U),
                           bswap_32big(0x42d6de77U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x329b5189U),
                               bswap_32big(0x9431dac3U),
                               bswap_32big(0x6235cc44U),
                               bswap_32big(0x234f64deU));
                WR1_PROG(REG_14B4H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0xa6a6a6a6U);
                WR1_PROG(REG_1600H, 0x00003420U);

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00000008U);

                WR1_PROG(REG_1600H, 0x0000b780U);
                WR1_PROG(REG_1600H, 0x00000004U);

                WR1_PROG(REG_1600H, 0x0000b480U);
                WR1_PROG(REG_1600H, 0x00000001U);

                WR1_PROG(REG_1600H, 0x00000bdeU);

                for (jLoop = 0U; jLoop <= 5; jLoop++)
                {
                    WR1_PROG(REG_1600H, 0x000037fbU);

                    WR1_PROG(REG_1600H, 0x00000bbdU);

                    for (iLoop = 1; iLoop <= (WRAPPED_KEY_SIZE - 2) / 2; iLoop++)
                    {
                        WR1_PROG(REG_1824H, 0x0a008105U);
                        WR1_PROG(REG_1608H, 0x81020000U);
                        WR1_PROG(REG_1400H, 0x00490009U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1608H, 0x8182001fU);
                        WR1_PROG(REG_1400H, 0x00490009U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1608H, 0x80040000U);
                        WR1_PROG(REG_1400H, 0x03410011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1600H, 0x00000824U);

                        WR1_PROG(REG_1600H, 0x00003c5fU);
                        WR1_PROG(REG_1600H, 0x000027fcU);
                        WR1_PROG(REG_1600H, 0x00003c7fU);
                        WR1_PROG(REG_1600H, 0x000027fcU);

                        WR1_PROG(REG_1600H, 0x00002c80U);

                        WR1_PROG(REG_1600H, 0x00002fa0U);

                        r_rsip_func101(bswap_32big(0xfd5a860dU),
                                       bswap_32big(0x8c14061eU),
                                       bswap_32big(0xcfc1d543U),
                                       bswap_32big(0x2ab0b6a3U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38000ba5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x00002fc0U);

                    r_rsip_func101(bswap_32big(0x23d9c946U),
                                   bswap_32big(0x854c9920U),
                                   bswap_32big(0xfb74a4cfU),
                                   bswap_32big(0x49bd84c7U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38008bc0U);
                WR1_PROG(REG_1600H, 0x00000006U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000bffU);
                WR1_PROG(REG_1600H, 0x00003c1fU);
                WR1_PROG(REG_1600H, 0x000027fcU);
                WR1_PROG(REG_1600H, 0x00003c3fU);

                WR1_PROG(REG_1600H, 0x00000bffU);

                WR1_PROG(REG_1600H, 0x00000bdeU);

                WR1_PROG(REG_1600H, 0x000037a5U);
                WR1_PROG(REG_1600H, 0x00002fa0U);

                WR1_PROG(REG_1600H, 0x0000b780U);
                WR1_PROG(REG_1600H, 0x00000008U);

                for (iLoop = 0U; iLoop < WRAPPED_KEY_SIZE; )
                {
                    WR1_PROG(REG_1600H, 0x000008c6U);
                    WR1_PROG(REG_1600H, 0x34202bddU);
                    WR1_PROG(REG_1600H, 0x2000d0c0U);

                    WR1_PROG(REG_1600H, 0x00007c06U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0xfb11b1c0U),
                                   bswap_32big(0xcc3434caU),
                                   bswap_32big(0xea166ad2U),
                                   bswap_32big(0x88637393U));
                    WR1_PROG(REG_1608H, 0x8182001fU);
                    WR1_PROG(REG_1408H, 0x0000500aU);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_Text[iLoop]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 1]);

                    WR1_PROG(REG_1600H, 0x000027fcU);

                    WR1_PROG(REG_1600H, 0x00002fc0U);

                    r_rsip_func101(bswap_32big(0xf345f53dU),
                                   bswap_32big(0xf58ec480U),
                                   bswap_32big(0xea093b02U),
                                   bswap_32big(0xf5387c5fU));
                    iLoop = iLoop + 2;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000bddU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func102(bswap_32big(0xb7614d87U),
                               bswap_32big(0x36498aadU),
                               bswap_32big(0x66753f20U),
                               bswap_32big(0xf279371dU));
                WR1_PROG(REG_14B4H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
