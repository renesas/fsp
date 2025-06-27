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

rsip_ret_t r_rsip_p95i (const uint32_t InData_KeyType[],
                        const uint32_t InData_DataType[],
                        const uint32_t InData_Cmd[],
                        const uint32_t InData_TextLen[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        const uint32_t InData_SeqNum[],
                        uint32_t       Header_Len)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00950001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00003640U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010120U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_TextLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x28fe8c10U),
                   bswap_32big(0x351c0eadU),
                   bswap_32big(0x802ce382U),
                   bswap_32big(0xbf51357eU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x3420a920U);
        WR1_PROG(REG_1600H, 0x00004101U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0x42640d0bU), bswap_32big(0xee27a885U), bswap_32big(0x330402edU),
                       bswap_32big(0x54459ca6U));
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x6c3c524fU),
                   bswap_32big(0x31422a56U),
                   bswap_32big(0x61f0cf00U),
                   bswap_32big(0x53c27a42U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe8526d3aU), bswap_32big(0x2922e025U), bswap_32big(0xe8c8ffd0U),
                       bswap_32big(0x09be2a1bU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x3420a800U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x6db572deU), bswap_32big(0x87930f61U), bswap_32big(0x5d49264cU),
                       bswap_32big(0xb83417eeU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xe4dc1b19U), bswap_32big(0x00bc5646U), bswap_32big(0xbe08c9f4U),
                           bswap_32big(0x55c74592U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000095U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xe43624e0U),
                               bswap_32big(0xe4b1a9c2U),
                               bswap_32big(0xb8468791U),
                               bswap_32big(0x1f1e7a18U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                r_rsip_func101(bswap_32big(0xfa9d7930U),
                               bswap_32big(0xaa0bf54bU),
                               bswap_32big(0x681d26f1U),
                               bswap_32big(0x8f9da5eeU));
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010140U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000095U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xbda29cb3U),
                               bswap_32big(0x3eb81b4fU),
                               bswap_32big(0x3851b8bcU),
                               bswap_32big(0x2730facdU));
                r_rsip_func068();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x2a46c04bU);

                r_rsip_func101(bswap_32big(0xa3fbc8bcU),
                               bswap_32big(0x9e3acd2fU),
                               bswap_32big(0xba61703aU),
                               bswap_32big(0xbdeaebb7U));
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000095U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x2da82aaaU), bswap_32big(0xba91ffe4U), bswap_32big(0xb15309d1U),
                           bswap_32big(0x82b077b6U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0xd89a5596U), bswap_32big(0x79932fb5U), bswap_32big(0xce04f76bU),
                           bswap_32big(0x52970cf7U));
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

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func101(bswap_32big(0x4272e8daU), bswap_32big(0xf35091c0U), bswap_32big(0x8eecf4cdU),
                           bswap_32big(0xb3c1a270U));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010140U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010020U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_DataType[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0x04b09d73U), bswap_32big(0xf03a84ccU), bswap_32big(0x99c99ec4U),
                           bswap_32big(0x2cd0aab4U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Cmd[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000036a0U);

                WR1_PROG(REG_1600H, 0x0000b6c0U);
                WR1_PROG(REG_1600H, 0x4cc18a1aU);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000095U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x4bb3c619U),
                               bswap_32big(0x3cf25d1bU),
                               bswap_32big(0x53cf2426U),
                               bswap_32big(0x323544fdU));
                r_rsip_func092();

                r_rsip_func101(bswap_32big(0xad03e763U),
                               bswap_32big(0xf463fa26U),
                               bswap_32big(0x4023d4e6U),
                               bswap_32big(0x6dd2bee7U));
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x000000dfU));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xb16f26f4U),
                               bswap_32big(0x38f5e084U),
                               bswap_32big(0x529da794U),
                               bswap_32big(0xd4b85e49U));
                r_rsip_func068();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x6ad6575eU);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x000000ebU));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x91435511U),
                               bswap_32big(0x21b8a36fU),
                               bswap_32big(0x3e71e1d9U),
                               bswap_32big(0x6cc7ecf8U));
                r_rsip_func044();

                r_rsip_func101(bswap_32big(0x21b0e26aU),
                               bswap_32big(0x7f26f817U),
                               bswap_32big(0x433805deU),
                               bswap_32big(0x61c4c017U));
            }

            r_rsip_func100(bswap_32big(0xffb15aefU), bswap_32big(0xb1a0c5cdU), bswap_32big(0x3a281150U),
                           bswap_32big(0x3b326628U));
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
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_1608H, 0x80040080U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func101(bswap_32big(0x5c27ea77U), bswap_32big(0x451a92afU), bswap_32big(0x0e946632U),
                           bswap_32big(0x71657b58U));
        }

        r_rsip_func100(bswap_32big(0x18e89b1bU), bswap_32big(0x24ad6f3bU), bswap_32big(0x9714058aU),
                       bswap_32big(0xa6e54852U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x863a2e91U), bswap_32big(0x291c0f32U), bswap_32big(0x94f4fb73U),
                           bswap_32big(0xadd64ef2U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003412U);

            WR1_PROG(REG_1600H, 0x3420a800U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0x295088a0U), bswap_32big(0x2144fe6eU), bswap_32big(0x9457b560U),
                           bswap_32big(0x204b5d40U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000145U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                WR1_PROG(REG_1824H, 0x08000065U);
                WR1_PROG(REG_1400H, 0x00410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x07000c04U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x00020061U);
                WR1_PROG(REG_1824H, 0xf8000006U);

                for (iLoop = 0U; iLoop < Header_Len; )
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_Header[iLoop]);
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func216();

                r_rsip_func101(bswap_32big(0x6a10897eU),
                               bswap_32big(0xc1e73e37U),
                               bswap_32big(0x1cd4acceU),
                               bswap_32big(0x5c2c8f55U));
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000001c7U);
                WR1_PROG(REG_1608H, 0x800201c0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[0]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[1]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000008aeU);
                WR1_PROG(REG_1600H, 0x000008cfU);

                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x00000002U);

                WR1_PROG(REG_1600H, 0x01986c64U);
                WR1_PROG(REG_1600H, 0x01986c85U);
                WR1_PROG(REG_1600H, 0x01986ca6U);
                WR1_PROG(REG_1600H, 0x00186cc6U);

                WR1_PROG(REG_1824H, 0x08000145U);
                WR1_PROG(REG_1608H, 0x81040060U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1824H, 0x08000065U);
                WR1_PROG(REG_1400H, 0x00410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x07000c04U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1600H, 0x0000b540U);
                WR1_PROG(REG_1600H, 0x00000010U);
                r_rsip_func031(InData_Header);

                r_rsip_func101(bswap_32big(0x0934175bU),
                               bswap_32big(0x6529f37bU),
                               bswap_32big(0x7d0c1e5cU),
                               bswap_32big(0xb987c71fU));
            }

            return RSIP_RET_PASS;
        }
    }
}
