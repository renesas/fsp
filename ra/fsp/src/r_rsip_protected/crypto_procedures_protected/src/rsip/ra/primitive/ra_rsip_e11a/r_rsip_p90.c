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

rsip_ret_t r_rsip_p90 (const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_WrappedKeyType[],
                       const uint32_t InData_Text[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       WRAPPED_KEY_SIZE,
                       uint32_t       KEY_INDEX_SIZE)
{
    uint32_t iLoop = 0U;
    int32_t  jLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00900001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x800200c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_WrappedKeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00003407U);

    WR1_PROG(REG_0094H, 0x3420a8c0U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0x00014046U),
                   bswap_32big(0x9f4d276dU),
                   bswap_32big(0x4025a588U),
                   bswap_32big(0x7e7147a3U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x2f74a54dU), bswap_32big(0x29126b48U), bswap_32big(0x63187731U),
                       bswap_32big(0x73bb1014U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003486U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00009001U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xb4503a91U), bswap_32big(0xbb351276U), bswap_32big(0x4e41639fU),
                       bswap_32big(0x185a64bfU));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_0094H, 0x1000b4c0U);
        WR1_PROG(REG_0094H, 0x00000005U);
        WR1_PROG(REG_0094H, 0x2000b4c0U);
        WR1_PROG(REG_0094H, 0x00000007U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00009001U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x72cf367fU), bswap_32big(0x6ce48394U), bswap_32big(0x65109ed7U),
                       bswap_32big(0x3e25e84dU));
        r_rsip_func044();

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0xfc43242bU), bswap_32big(0x898f9d41U), bswap_32big(0xbb187193U),
                       bswap_32big(0xbbfd2a1bU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func100(bswap_32big(0xe1e9dbf2U), bswap_32big(0xf6336579U), bswap_32big(0xae7315dbU),
                           bswap_32big(0xe214cc3aU));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xf7009d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);

            WR1_PROG(REG_00B0H, 0x00000401U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_00B0H, 0x00000402U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00000801U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000802U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D4H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x2f755422U), bswap_32big(0x1143393aU), bswap_32big(0x480041a4U),
                           bswap_32big(0x0a2611bdU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x27fadf3fU), bswap_32big(0x01a8c474U), bswap_32big(0x96df87e9U),
                           bswap_32big(0xc5eedb1dU));
            WR1_PROG(REG_0014H, 0x000007c1U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xf7009d07U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

            WR1_PROG(REG_00B0H, 0x00001404U);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0xc63d5ddfU), bswap_32big(0x579f86b7U), bswap_32big(0xa0e8e3a6U),
                           bswap_32big(0xb68c1035U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D4H, 0x40000000U);

            r_rsip_func101(bswap_32big(0xcae485d3U), bswap_32big(0x6c9c7b24U), bswap_32big(0x33f0253aU),
                           bswap_32big(0x7c956eafU));
        }

        r_rsip_func100(bswap_32big(0xdf6c721bU), bswap_32big(0x459ecad6U), bswap_32big(0x09647fe1U),
                       bswap_32big(0xfada669cU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xa61ca121U), bswap_32big(0xd0f8d815U), bswap_32big(0x9996d866U),
                           bswap_32big(0x2284e80aU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            r_rsip_func030();

            WR1_PROG(REG_0094H, 0x00002ca0U);

            WR1_PROG(REG_00D0H, 0x08000044U);
            WR1_PROG(REG_009CH, 0x810100c0U);
            WR1_PROG(REG_0000H, 0x00490005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000054U);
            WR1_PROG(REG_009CH, 0x810100e0U);
            WR1_PROG(REG_0000H, 0x00490005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000001c7U);
            WR1_PROG(REG_009CH, 0x80020000U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_Text[0]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_Text[1]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x00000884U);

            WR1_PROG(REG_0094H, 0x00000863U);
            WR1_PROG(REG_0094H, 0x00002c60U);

            for (iLoop = 2; iLoop < WRAPPED_KEY_SIZE; )
            {
                WR1_PROG(REG_0014H, 0x000001c7U);
                WR1_PROG(REG_009CH, 0x80820004U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Text[iLoop]);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Text[iLoop + 1]);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x0000a480U);
                WR1_PROG(REG_0094H, 0x00000008U);

                WR1_PROG(REG_0094H, 0x00002c60U);

                r_rsip_func101(bswap_32big(0x143b45ecU),
                               bswap_32big(0xd0e1b81fU),
                               bswap_32big(0x6beb14b3U),
                               bswap_32big(0xe9ec3c67U));
                iLoop = iLoop + 2;
            }

            WR1_PROG(REG_0094H, 0x38000865U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x0000a880U);
            WR1_PROG(REG_0094H, 0x00000008U);

            WR1_PROG(REG_00D0H, 0x08000065U);
            WR1_PROG(REG_009CH, 0x81020080U);
            WR1_PROG(REG_0000H, 0x00490009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0000H, 0x00400009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x000034c5U);
            WR1_PROG(REG_0094H, 0x000030c0U);

            WR1_PROG(REG_0094H, 0x00003486U);
            WR1_PROG(REG_0094H, 0x00026c84U);
            WR1_PROG(REG_0094H, 0x00016cc6U);
            WR1_PROG(REG_0094H, 0x00002486U);

            WR1_PROG(REG_0094H, 0x000008a5U);

            for (jLoop = 5; jLoop >= 0; jLoop = jLoop - 1)
            {
                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c200104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_009CH, 0x800100e0U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_009CH, 0x800100c0U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x00010009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x000030c0U);

                for (iLoop = (WRAPPED_KEY_SIZE / 2) - 1; iLoop >= 1; iLoop = iLoop - 1)
                {
                    WR1_PROG(REG_0094H, 0x00000824U);

                    WR1_PROG(REG_00D0H, 0x0a00810dU);
                    WR1_PROG(REG_009CH, 0x81020000U);
                    WR1_PROG(REG_0000H, 0x00490009U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_009CH, 0x81820007U);
                    WR1_PROG(REG_0000H, 0x00490009U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_009CH, 0x80040000U);
                    WR1_PROG(REG_0000H, 0x03410011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x00003c47U);
                    WR1_PROG(REG_0094H, 0x0000a4e0U);
                    WR1_PROG(REG_0094H, 0x00000004U);
                    WR1_PROG(REG_0094H, 0x00003c67U);
                    WR1_PROG(REG_0094H, 0x0000a8e0U);
                    WR1_PROG(REG_0094H, 0x0000000cU);

                    WR1_PROG(REG_0094H, 0x00003080U);

                    WR1_PROG(REG_0094H, 0x000030c0U);

                    r_rsip_func101(bswap_32big(0xc232f32dU),
                                   bswap_32big(0x84747eabU),
                                   bswap_32big(0xcbb2b5b4U),
                                   bswap_32big(0xfa96e8a8U));
                }

                WR1_PROG(REG_0094H, 0x38000cc6U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002ca0U);

                r_rsip_func101(bswap_32big(0x8a239735U),
                               bswap_32big(0xccc0343bU),
                               bswap_32big(0xb35704f0U),
                               bswap_32big(0x9c9c21f3U));
            }

            WR1_PROG(REG_0094H, 0x380088a0U);
            WR1_PROG(REG_0094H, 0x00000006U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x38008800U);
            WR1_PROG(REG_0094H, 0xa6a6a6a6U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0xa6a6a6a6U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x843a96b4U), bswap_32big(0xd4bdef13U), bswap_32big(0xbe59b4d7U),
                           bswap_32big(0xa5f221f7U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x852cd333U),
                               bswap_32big(0x5cf1eea8U),
                               bswap_32big(0x7a724b27U),
                               bswap_32big(0xce8b6148U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xd6579601U),
                               bswap_32big(0x68ff4a7dU),
                               bswap_32big(0x2d789293U),
                               bswap_32big(0x8f5c7227U));

                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x81880002U);
                WR1_PROG(REG_00B0H, 0x00001404U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c100104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_009CH, 0x80010020U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x0001000dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0094H, 0x0000a820U);
                WR1_PROG(REG_0094H, 0x00000005U);

                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c000104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_009CH, 0x80010080U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x0001000dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func103();
                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c200104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_009CH, 0x80010000U);
                WR1_PROG(REG_0000H, 0x03410005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x0001000dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x000034c0U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00009002U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x246188b2U),
                               bswap_32big(0x9f67715bU),
                               bswap_32big(0x03e5b027U),
                               bswap_32big(0x985e5ddaU));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x000034c4U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00009002U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2d33ce77U),
                               bswap_32big(0x623d7cdbU),
                               bswap_32big(0xa1f4ba36U),
                               bswap_32big(0x66f1b667U));
                r_rsip_func044();

                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_009CH, 0x80880002U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x08000044U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x08000054U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_0094H, 0x00000884U);

                for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
                {
                    WR1_PROG(REG_0094H, 0x000008c6U);
                    WR1_PROG(REG_0094H, 0x34202881U);
                    WR1_PROG(REG_0094H, 0x2000d0c0U);

                    WR1_PROG(REG_0094H, 0x00007c06U);
                    WR1_PROG(REG_0040H, 0x00602000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0xe2fb211eU),
                                   bswap_32big(0x004c04f1U),
                                   bswap_32big(0x04d03c84U),
                                   bswap_32big(0x48c51eb2U));
                    WR1_PROG(REG_00D4H, 0x40000000U);
                    WR1_PROG(REG_00D0H, 0xe7008d05U);
                    WR1_PROG(REG_009CH, 0x81840007U);
                    WR1_PROG(REG_0000H, 0x00490011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0008H, 0x00001012U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[iLoop + 1]);

                    WR1_PROG(REG_0094H, 0x0000a4e0U);
                    WR1_PROG(REG_0094H, 0x00000010U);

                    WR1_PROG(REG_0094H, 0x0000a480U);
                    WR1_PROG(REG_0094H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0x4745ee6aU),
                                   bswap_32big(0x9c6aecaaU),
                                   bswap_32big(0x47a820afU),
                                   bswap_32big(0x93ac1fa3U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_0094H, 0x38000881U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func100(bswap_32big(0xd010b531U),
                               bswap_32big(0x86456ec0U),
                               bswap_32big(0x2e21dea2U),
                               bswap_32big(0xa9c2b85bU));
                WR1_PROG(REG_0014H, 0x000000a1U);
                WR1_PROG(REG_00D0H, 0x0c000104U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0x09108105U);
                WR1_PROG(REG_0000H, 0x00410011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0008H, 0x00001012U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[iLoop + 1]);

                r_rsip_func100(bswap_32big(0x76e65c2aU),
                               bswap_32big(0x7690067eU),
                               bswap_32big(0x0c706a81U),
                               bswap_32big(0x961acbb1U));
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                r_rsip_func102(bswap_32big(0x38025114U),
                               bswap_32big(0xe8dbaa13U),
                               bswap_32big(0x502d3f4eU),
                               bswap_32big(0x958849fdU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
