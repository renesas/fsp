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

rsip_ret_t r_rsip_p98i (const uint32_t InData_KeyType[],
                        const uint32_t InData_DataType[],
                        const uint32_t InData_Cmd[],
                        const uint32_t InData_TextLen[],
                        const uint32_t InData_MACLength[],
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

    WR1_PROG(REG_1B00H, 0x00980001U);
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

    WR1_PROG(REG_1600H, 0x00003689U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x07f7d3adU),
                   bswap_32big(0xe7e18e46U),
                   bswap_32big(0x0c7c9777U),
                   bswap_32big(0x08fcd417U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010140U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_MACLength[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xd2d21e10U), bswap_32big(0x38dc7f8cU), bswap_32big(0x571b1409U),
                       bswap_32big(0x03814f66U));
    }
    else
    {
        WR1_PROG(REG_1600H, 0x0000b540U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x3420a920U);
        WR1_PROG(REG_1600H, 0x00004101U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0xb80412b3U), bswap_32big(0x6a869691U), bswap_32big(0xc5f6796aU),
                       bswap_32big(0x08883696U));
    }

    WR1_PROG(REG_1600H, 0x0000366aU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x780f33baU),
                   bswap_32big(0xe21013f8U),
                   bswap_32big(0xbd489679U),
                   bswap_32big(0x21a911e8U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc08b2bd8U), bswap_32big(0x2650909dU), bswap_32big(0x0be12f4eU),
                       bswap_32big(0x33e8bbb0U));
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

        r_rsip_func100(bswap_32big(0x1377180bU), bswap_32big(0xd0efb08bU), bswap_32big(0xa4dd7d8eU),
                       bswap_32big(0xf599f9b8U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xeb3e68bdU), bswap_32big(0x1624ece4U), bswap_32big(0xaef68fe4U),
                           bswap_32big(0x8295253aU));
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
                WR1_PROG(REG_1420H, bswap_32big(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2a6743e3U),
                               bswap_32big(0xc5f99062U),
                               bswap_32big(0xc0036048U),
                               bswap_32big(0xcd77e7beU));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                r_rsip_func101(bswap_32big(0xfb66bbdeU),
                               bswap_32big(0x0dc61ec7U),
                               bswap_32big(0x01c0c80bU),
                               bswap_32big(0xfe5079ffU));
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
                WR1_PROG(REG_1420H, bswap_32big(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xf326e5f9U),
                               bswap_32big(0x3b4f3a4dU),
                               bswap_32big(0x85f9f081U),
                               bswap_32big(0xeeb7a449U));
                r_rsip_func068();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x2a46c04bU);

                r_rsip_func101(bswap_32big(0xad61608bU),
                               bswap_32big(0xb4f1990aU),
                               bswap_32big(0xbccbb331U),
                               bswap_32big(0xb2ec6be9U));
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000098U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xd7b6888bU), bswap_32big(0x53b1ffbbU), bswap_32big(0xf528690eU),
                           bswap_32big(0xf634547dU));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0xdfb9e6fdU), bswap_32big(0x038dc6bcU), bswap_32big(0x3baba902U),
                           bswap_32big(0xdc91ad82U));
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

            r_rsip_func101(bswap_32big(0x0dd4724eU), bswap_32big(0x002c51f3U), bswap_32big(0xa7562e3fU),
                           bswap_32big(0xb0530559U));
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

            r_rsip_func100(bswap_32big(0xb1483cf3U), bswap_32big(0x9395000fU), bswap_32big(0xbf42cfbdU),
                           bswap_32big(0x47e0d856U));
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
                WR1_PROG(REG_1600H, 0x8026ee7fU);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x7c0fea46U),
                               bswap_32big(0x86f3c34aU),
                               bswap_32big(0x85bc3dffU),
                               bswap_32big(0xee522f80U));
                r_rsip_func092();

                r_rsip_func101(bswap_32big(0xee21bc6fU),
                               bswap_32big(0x78c6b471U),
                               bswap_32big(0x2f5d5cb8U),
                               bswap_32big(0x0baa76d7U));
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000003U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xbd535448U),
                               bswap_32big(0x23995423U),
                               bswap_32big(0x703ed7f2U),
                               bswap_32big(0x28c7c4daU));
                r_rsip_func068();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x98bae316U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x000000ccU));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x311549fdU),
                               bswap_32big(0x4178cdfdU),
                               bswap_32big(0x85f2e598U),
                               bswap_32big(0xdefc168fU));
                r_rsip_func044();

                r_rsip_func101(bswap_32big(0x03fc24f6U),
                               bswap_32big(0xb2214770U),
                               bswap_32big(0x5f764c4dU),
                               bswap_32big(0xe34f086eU));
            }

            r_rsip_func100(bswap_32big(0x2800bbc9U), bswap_32big(0x8f5414aeU), bswap_32big(0x937101efU),
                           bswap_32big(0x349a0e0aU));
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

            r_rsip_func101(bswap_32big(0x48f2ab55U), bswap_32big(0xec4d6b94U), bswap_32big(0x821c67e2U),
                           bswap_32big(0xf5e5b8c6U));
        }

        r_rsip_func100(bswap_32big(0x1e044adeU), bswap_32big(0x56e26d1cU), bswap_32big(0xfa4cf9b6U),
                       bswap_32big(0x24ff0d46U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x58130d85U), bswap_32big(0x1f1691b3U), bswap_32big(0x8234a9b0U),
                           bswap_32big(0xd8aba884U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003534U);

            WR1_PROG(REG_1600H, 0x00003553U);

            WR1_PROG(REG_1600H, 0x00003412U);

            WR1_PROG(REG_1600H, 0x3420a800U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xfee8981dU), bswap_32big(0xd8fd762aU), bswap_32big(0x780dde0aU),
                           bswap_32big(0x7c586fe9U));
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

                r_rsip_func101(bswap_32big(0xedd9569fU),
                               bswap_32big(0x05dccab3U),
                               bswap_32big(0x413b5813U),
                               bswap_32big(0xb1f5ea28U));
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

                r_rsip_func031(InData_Header);

                r_rsip_func101(bswap_32big(0x3e8ee2feU),
                               bswap_32big(0xbcf98c4eU),
                               bswap_32big(0x5adc5e56U),
                               bswap_32big(0xc1ae4c8bU));
            }

            return RSIP_RET_PASS;
        }
    }
}
