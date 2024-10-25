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

rsip_ret_t r_rsip_pe7 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       const uint32_t InData_SeqNum[],
                       uint32_t       OutData_HMACKeyIndex[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e70001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_OutDataType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x38000ca5U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x3420a8c0U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x380088c0U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x6dab8003U), bswap_32big(0x1a7da0d2U), bswap_32big(0x210fece5U), bswap_32big(0xd6fa5586U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xb5e28db5U), bswap_32big(0x448064c9U), bswap_32big(0xee1e95dcU), bswap_32big(0x8807de5dU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xce492b14U), bswap_32big(0xeb0b1b00U), bswap_32big(0xf83a7447U), bswap_32big(0xc9a14a2eU));
        WR1_PROG(REG_1600H, 0x00007c06U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000005U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x8fc9a906U), bswap_32big(0x3c3cb043U), bswap_32big(0xb4ef839eU), bswap_32big(0x83d42424U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000007U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xd8ec559eU), bswap_32big(0x5492a655U), bswap_32big(0x6da6197dU), bswap_32big(0x0ca11fcbU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x81bcbb0fU), bswap_32big(0x19957ebaU), bswap_32big(0xd0b5266bU), bswap_32big(0xb6039b0dU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000003U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x56fa239bU), bswap_32big(0x279414cfU), bswap_32big(0xbf29d59fU), bswap_32big(0x4204b418U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000bU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa3563140U), bswap_32big(0x3419e277U), bswap_32big(0x446de291U), bswap_32big(0x86ba8a21U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0000001bU);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa7d6819bU), bswap_32big(0x72502497U), bswap_32big(0x05c22f1fU), bswap_32big(0xc7e961b3U));
        }

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010100U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_OutDataLocation[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00003608U);
        WR1_PROG(REG_1600H, 0x00056a10U);

        WR1_PROG(REG_1600H, 0x00003628U);
        WR1_PROG(REG_1600H, 0x0000262eU);

        WR1_PROG(REG_1600H, 0x00056a31U);

        WR1_PROG(REG_1600H, 0x00002e20U);

        WR1_PROG(REG_1600H, 0x342028b1U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x34202a11U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0xe803ac3fU), bswap_32big(0xc36aaeb7U), bswap_32big(0xae2f80f9U), bswap_32big(0x1c8187d2U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x448a68e7U), bswap_32big(0xcc9a001cU), bswap_32big(0xc257f9efU), bswap_32big(0xb20eec1bU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x101afb19U), bswap_32big(0x4d1e634dU), bswap_32big(0xd96dba7cU), bswap_32big(0x2432b756U));

            WR1_PROG(REG_1600H, 0x00003651U);
            WR1_PROG(REG_1600H, 0x00002a50U);

            WR1_PROG(REG_1600H, 0x00000a73U);

            WR1_PROG(REG_1600H, 0x000009efU);

            WR1_PROG(REG_1600H, 0x00000a94U);

            WR1_PROG(REG_1600H, 0x00000ad6U);

            WR1_PROG(REG_1608H, 0x81010200U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func100(bswap_32big(0xc3d9ddafU), bswap_32big(0x644ebebaU), bswap_32big(0x83c462f8U), bswap_32big(0xf26dcdcaU));
            WR1_PROG(REG_1608H, 0x81010220U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

            for (iLoop = S_RAM[0]; iLoop < S_RAM[0 + 1]; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x34202a72U);
                WR1_PROG(REG_1600H, 0x2000d2c0U);
                WR1_PROG(REG_1600H, 0x00007c16U);
                WR1_PROG(REG_143CH, 0x00602000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KDFInfo[iLoop * 13]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x3f0878d2U), bswap_32big(0xd779b738U), bswap_32big(0x68cb0221U), bswap_32big(0xcd9e3895U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x01799093U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x9c61fffbU), bswap_32big(0x09e3315bU), bswap_32big(0xcfd3ddfdU), bswap_32big(0x24fcc7abU));
                r_rsip_func044();

                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 1]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 5]);

                WR1_PROG(REG_1608H, 0x8088000fU);
                WR1_PROG(REG_1400H, 0x03420021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 9]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000a5e0U);
                WR1_PROG(REG_1600H, 0x00000020U);

                WR1_PROG(REG_1600H, 0x00002e60U);

                r_rsip_func100(bswap_32big(0xa15169e2U), bswap_32big(0x87812d0dU), bswap_32big(0xfc5176d3U), bswap_32big(0x73047bf6U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x0000d280U);
                    r_rsip_func101(bswap_32big(0x3414df25U), bswap_32big(0xc02e1f2aU), bswap_32big(0x13ffccfdU), bswap_32big(0x59fe9ecdU));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0x834c1409U), bswap_32big(0x2535e21bU), bswap_32big(0x4fb9d23aU), bswap_32big(0x745181a8U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);
            }

            WR1_PROG(REG_1600H, 0x38000a72U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000e94U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0xea047996U), bswap_32big(0x1afa555cU), bswap_32big(0x1934bfecU), bswap_32big(0xdcb5e371U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x67cd0d04U), bswap_32big(0x9a39c118U), bswap_32big(0xcdd8743fU), bswap_32big(0x347472cfU));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x68fba712U), bswap_32big(0x60d8205cU), bswap_32big(0xff5c6648U), bswap_32big(0xc37fc443U));
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
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x3071cbadU), bswap_32big(0x7bd9b3c0U), bswap_32big(0xc12200b9U), bswap_32big(0xa621d257U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x000034e9U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2135551dU), bswap_32big(0x1ea02da0U), bswap_32big(0xd7ef2847U), bswap_32big(0x5394ae29U));
                r_rsip_func044();

                WR1_PROG(REG_1600H, 0x00008d00U);
                WR1_PROG(REG_1600H, 0x0000001fU);

                WR1_PROG(REG_1600H, 0x0000b5e0U);
                WR1_PROG(REG_1600H, 0x00000080U);

                WR1_PROG(REG_1600H, 0x3420a8c0U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0x100a78f3U), bswap_32big(0x673d7874U), bswap_32big(0x35f8e873U), bswap_32big(0xeacbf67bU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    for (iLoop = 0U; iLoop < 32U; iLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x00000ab5U);

                        WR1_PROG(REG_1600H, 0x02003aa8U);
                        WR1_PROG(REG_1600H, 0x02003eafU);

                        WR1_PROG(REG_1600H, 0x00002d00U);
                        WR1_PROG(REG_1600H, 0x00002de0U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x0000b5e0U);
                    WR1_PROG(REG_1600H, 0x00000080U);

                    WR1_PROG(REG_1600H, 0x38000cc6U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    r_rsip_func100(bswap_32big(0xe47c431cU), bswap_32big(0xfd3003a1U), bswap_32big(0x754c8cc1U), bswap_32big(0x864d8b79U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x6070f3e6U), bswap_32big(0x0830d79cU), bswap_32big(0x2a99abadU), bswap_32big(0xa022cb15U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);

                        WR1_PROG(REG_1608H, 0x8184000fU);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0x40f94ebeU), bswap_32big(0xa6a11ddcU), bswap_32big(0x43084112U), bswap_32big(0x7074d4beU));
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
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                        r_rsip_func101(bswap_32big(0xc439205bU), bswap_32big(0xed3efb98U), bswap_32big(0x8fb5de06U), bswap_32big(0x5aa4fdb9U));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x1097cc63U), bswap_32big(0x72a968c2U), bswap_32big(0xe52fdbedU), bswap_32big(0x3d255ec5U));
                        WR1_PROG(REG_1A2CH, 0x40000100U);
                        WR1_PROG(REG_1A24H, 0xe7009d07U);

                        WR1_PROG(REG_1608H, 0x8188000fU);
                        WR1_PROG(REG_1400H, 0x00890021U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                        r_rsip_func100(bswap_32big(0xef93d0e5U), bswap_32big(0x4c5a273fU), bswap_32big(0xdc6dfd2cU), bswap_32big(0xa5bdf014U));
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
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);

                        r_rsip_func101(bswap_32big(0xd3f67117U), bswap_32big(0x80a871caU), bswap_32big(0xfd4f48f9U), bswap_32big(0x51b7bfa2U));
                    }

                    r_rsip_func100(bswap_32big(0xbfac564aU), bswap_32big(0x479f3edaU), bswap_32big(0xf4bf26c8U), bswap_32big(0xbf659d4fU));
                    WR1_PROG(REG_1608H, 0x81010000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x104da134U), bswap_32big(0x22eaaa9fU), bswap_32big(0x7e331779U), bswap_32big(0xd6b28d59U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x3420a8c0U);
                    WR1_PROG(REG_1600H, 0x00000005U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xf1f3b54bU), bswap_32big(0x8bb10d26U), bswap_32big(0xc75a0b3bU), bswap_32big(0x74a779adU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        for (iLoop = 0U; iLoop < 32U; iLoop++)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);

                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1600H, 0x02003eafU);

                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1600H, 0x00000080U);

                        r_rsip_func100(bswap_32big(0xd555c538U), bswap_32big(0x227ab199U), bswap_32big(0xb12bedc1U), bswap_32big(0x79c5ac73U));
                        WR1_PROG(REG_1A2CH, 0x40000100U);
                        WR1_PROG(REG_1A24H, 0xe7009d07U);

                        WR1_PROG(REG_1608H, 0x8188000fU);
                        WR1_PROG(REG_1400H, 0x00890021U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_HMACKeyIndex[1]);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_HMACKeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x2deaedfeU), bswap_32big(0xf3ca0d1eU), bswap_32big(0xb08477caU), bswap_32big(0x2e734277U));
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
                        RD4_ADDR(REG_1420H, &OutData_HMACKeyIndex[9]);

                        r_rsip_func100(bswap_32big(0xddac6033U), bswap_32big(0xab0f9c1bU), bswap_32big(0x624da57dU), bswap_32big(0x5e31f91fU));
                        WR1_PROG(REG_1608H, 0x81010000U);
                        WR1_PROG(REG_1408H, 0x00005006U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[0]);

                        r_rsip_func102(bswap_32big(0x8e3f483eU), bswap_32big(0xe191cae3U), bswap_32big(0x6e77ed23U), bswap_32big(0x7653c785U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return RSIP_RET_PASS;
                    }
                    else
                    {
                        for (iLoop = 0U; iLoop < 16U; iLoop++)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);

                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1600H, 0x02003eafU);

                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1600H, 0x00000080U);

                        WR1_PROG(REG_1600H, 0x380088c0U);
                        WR1_PROG(REG_1600H, 0x00000002U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x172bd3b7U), bswap_32big(0x3d64672bU), bswap_32big(0x15bb7786U), bswap_32big(0xbfb68275U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1A24H, 0x08000105U);
                            WR1_PROG(REG_1608H, 0x8184000fU);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1608H, 0x80040140U);
                            WR1_PROG(REG_1400H, 0x03420011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0xc204f317U), bswap_32big(0xf28599f3U), bswap_32big(0x2f0adafaU), bswap_32big(0xa9f0abf2U));
                        }
                        else
                        {
                            WR1_PROG(REG_1444H, 0x000001c7U);
                            WR1_PROG(REG_1608H, 0x80020080U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, InData_SeqNum[0]);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, InData_SeqNum[1]);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1600H, 0x380088c0U);
                            WR1_PROG(REG_1600H, 0x00000003U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);

                            r_rsip_func100(bswap_32big(0x9e873046U), bswap_32big(0x55d64435U), bswap_32big(0x63f7501eU), bswap_32big(0x6bac916cU));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                WR1_PROG(REG_1600H, 0x0000394fU);

                                WR1_PROG(REG_1600H, 0x00003564U);
                                WR1_PROG(REG_1600H, 0x00003585U);

                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1600H, 0x00000001U);

                                r_rsip_func101(bswap_32big(0x6ad13cb5U), bswap_32big(0x9ff3f5a0U), bswap_32big(0x3269e3f9U), bswap_32big(0xe223e33aU));
                            }
                            else
                            {
                                WR1_PROG(REG_1A24H, 0x08000105U);
                                WR1_PROG(REG_1608H, 0x8183000fU);
                                WR1_PROG(REG_1400H, 0x0089000dU);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1400H, 0x00800005U);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1608H, 0x80040140U);
                                WR1_PROG(REG_1400H, 0x03420011U);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);

                                WR1_PROG(REG_1600H, 0x00000964U);
                                WR1_PROG(REG_1600H, 0x00000985U);

                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1600H, 0x00000001U);

                                r_rsip_func101(bswap_32big(0x07f967b5U), bswap_32big(0xc65f33afU), bswap_32big(0xf9d94c83U), bswap_32big(0xf9b06052U));
                            }
                        }

                        r_rsip_func100(bswap_32big(0x2fe01943U), bswap_32big(0x678b398fU), bswap_32big(0x55180509U), bswap_32big(0xb177a085U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);

                        WR1_PROG(REG_1608H, 0x81040140U);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_EncIV[1]);

                        r_rsip_func100(bswap_32big(0x515aac5fU), bswap_32big(0x5176d607U), bswap_32big(0xd5aee535U), bswap_32big(0x97d45531U));
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
                        RD4_ADDR(REG_1420H, &OutData_EncIV[5]);

                        r_rsip_func100(bswap_32big(0x541431d4U), bswap_32big(0xf3518144U), bswap_32big(0x15642c73U), bswap_32big(0xf072531dU));
                        WR1_PROG(REG_1608H, 0x81010000U);
                        WR1_PROG(REG_1408H, 0x00005006U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[0]);

                        r_rsip_func102(bswap_32big(0xdc55094cU), bswap_32big(0x1ea32b4eU), bswap_32big(0x2e3c8351U), bswap_32big(0x9ce89533U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
