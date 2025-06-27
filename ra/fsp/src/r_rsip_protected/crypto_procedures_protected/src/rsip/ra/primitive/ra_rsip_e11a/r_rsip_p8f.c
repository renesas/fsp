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

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x008f0001U);
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

    r_rsip_func100(bswap_32big(0xdda14420U),
                   bswap_32big(0x2227fc6aU),
                   bswap_32big(0x9a655522U),
                   bswap_32big(0x47736c8bU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x4ddbe11fU), bswap_32big(0xc16afa06U), bswap_32big(0xa4cd14d7U),
                       bswap_32big(0xdb528deaU));
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
        WR1_PROG(REG_002CH, bswap_32big(0x00008f01U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x0b683b97U), bswap_32big(0xa3897413U), bswap_32big(0x818d6522U),
                       bswap_32big(0x95f8a573U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_0094H, 0x1000b4c0U);
        WR1_PROG(REG_0094H, 0x00000005U);
        WR1_PROG(REG_0094H, 0x2000b4c0U);
        WR1_PROG(REG_0094H, 0x00000007U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00008f01U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x69b65843U), bswap_32big(0x270e115eU), bswap_32big(0xae7c1865U),
                       bswap_32big(0x5f582768U));
        r_rsip_func044();

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0xf43e7db4U), bswap_32big(0xb70002abU), bswap_32big(0x0c442e6fU),
                       bswap_32big(0x555461d1U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
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

            r_rsip_func101(bswap_32big(0x5733e390U), bswap_32big(0x032109d1U), bswap_32big(0x5df816afU),
                           bswap_32big(0xab0b9844U));
        }
        else
        {
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

            r_rsip_func101(bswap_32big(0x5069aed8U), bswap_32big(0x324cb321U), bswap_32big(0x06711f65U),
                           bswap_32big(0x99a39c0dU));
        }

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xb31a2fe6U), bswap_32big(0x80763c00U), bswap_32big(0xc443943dU),
                       bswap_32big(0x45ac78a5U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xdef218caU), bswap_32big(0x960ed46eU), bswap_32big(0xc98ec48dU),
                           bswap_32big(0xca9229edU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            r_rsip_func030();

            WR1_PROG(REG_0094H, 0x00003427U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            WR1_PROG(REG_0094H, 0x00003ca3U);

            WR1_PROG(REG_0094H, 0x00003466U);

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_WrappedKeyIndex[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00008f02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x866cfee0U), bswap_32big(0xe4ebe4aeU), bswap_32big(0x62aac685U),
                           bswap_32big(0x8426d8e5U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x000034c3U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00008f02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xc4fdbfa7U), bswap_32big(0x00f52d0dU), bswap_32big(0x4566dd52U),
                           bswap_32big(0xa109e46cU));
            r_rsip_func044();

            WR1_PROG(REG_0094H, 0x000034e1U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            WR1_PROG(REG_0094H, 0x000038a3U);

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0094H, 0x00000863U);

            WR1_PROG(REG_0094H, 0x0000b420U);
            WR1_PROG(REG_0094H, 0x00000010U);

            WR1_PROG(REG_0094H, 0x00000842U);

            WR1_PROG(REG_0094H, 0x0000b400U);
            WR1_PROG(REG_0094H, 0x00000004U);

            WR1_PROG(REG_0094H, 0x0000a8e0U);
            WR1_PROG(REG_0094H, 0x00000005U);

            for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
            {
                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0xf7008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_WrappedKeyIndex[iLoop + 1]);

                WR1_PROG(REG_009CH, 0x80840003U);
                WR1_PROG(REG_0000H, 0x03410011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00002461U);

                WR1_PROG(REG_0094H, 0x00002440U);

                r_rsip_func101(bswap_32big(0xc9c36255U),
                               bswap_32big(0xc5f5a546U),
                               bswap_32big(0xcd6b9beaU),
                               bswap_32big(0x040e8c24U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_0094H, 0x38000847U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_WrappedKeyIndex[iLoop + 1]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x0337cd39U), bswap_32big(0x46467eecU), bswap_32big(0xa7b22702U),
                           bswap_32big(0x58843250U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xfbd0c0f4U),
                               bswap_32big(0xdc85963eU),
                               bswap_32big(0x5e0d4f02U),
                               bswap_32big(0x7f933162U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_0094H, 0x38000c84U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                r_rsip_func100(bswap_32big(0x5691da3bU),
                               bswap_32big(0x4b26f8a8U),
                               bswap_32big(0x0e8b188cU),
                               bswap_32big(0x421ba5fbU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func100(bswap_32big(0xcc0184ceU),
                                   bswap_32big(0x6387b99fU),
                                   bswap_32big(0x837ece70U),
                                   bswap_32big(0x08463acbU));

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

                    r_rsip_func101(bswap_32big(0x0247d50aU),
                                   bswap_32big(0x3bdb2f35U),
                                   bswap_32big(0xc4c33b99U),
                                   bswap_32big(0x1220c3cfU));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xb9c142a3U),
                                   bswap_32big(0x6fef8ae3U),
                                   bswap_32big(0xa7c82148U),
                                   bswap_32big(0x224c69f4U));

                    WR1_PROG(REG_00D0H, 0x08000085U);
                    WR1_PROG(REG_00B0H, 0x00001804U);
                    WR1_PROG(REG_0000H, 0x00430011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func100(bswap_32big(0x1dd09e8cU),
                                   bswap_32big(0xf092f043U),
                                   bswap_32big(0x0633f925U),
                                   bswap_32big(0x0e9912efU));
                    WR1_PROG(REG_00D0H, 0x08000095U);
                    WR1_PROG(REG_0000H, 0x00430011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_00D4H, 0x40000000U);

                    r_rsip_func101(bswap_32big(0x4a9f8376U),
                                   bswap_32big(0xeb159faeU),
                                   bswap_32big(0x75c72639U),
                                   bswap_32big(0x73701c51U));
                }

                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0xa6a6a6a6U);
                WR1_PROG(REG_0094H, 0x00003420U);

                WR1_PROG(REG_0094H, 0x0000b480U);
                WR1_PROG(REG_0094H, 0x00000001U);

                WR1_PROG(REG_0094H, 0x000008c6U);

                WR1_PROG(REG_0094H, 0x00036ca5U);

                for (jLoop = 0U; jLoop <= 5; jLoop++)
                {
                    WR1_PROG(REG_0094H, 0x000008e7U);

                    for (iLoop = 1; iLoop <= (WRAPPED_KEY_SIZE - 2) / 2; iLoop++)
                    {
                        WR1_PROG(REG_00D0H, 0x0a008105U);
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

                        WR1_PROG(REG_0094H, 0x00000824U);

                        WR1_PROG(REG_0094H, 0x00003c47U);
                        WR1_PROG(REG_0094H, 0x0000a4e0U);
                        WR1_PROG(REG_0094H, 0x00000004U);
                        WR1_PROG(REG_0094H, 0x00003c67U);
                        WR1_PROG(REG_0094H, 0x0000a4e0U);
                        WR1_PROG(REG_0094H, 0x00000004U);

                        WR1_PROG(REG_0094H, 0x00002c80U);

                        r_rsip_func101(bswap_32big(0xd6875739U),
                                       bswap_32big(0x8451d02eU),
                                       bswap_32big(0xaeb042d8U),
                                       bswap_32big(0x9e26a9f5U));
                    }

                    WR1_PROG(REG_0094H, 0x380008e5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);

                    WR1_PROG(REG_0040H, 0x00402000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0xfa3d3181U),
                                   bswap_32big(0x9eade361U),
                                   bswap_32big(0xecf69bfeU),
                                   bswap_32big(0x056df28fU));
                }

                WR1_PROG(REG_0094H, 0x380088c0U);
                WR1_PROG(REG_0094H, 0x00000006U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func100(bswap_32big(0x37dd4ab5U),
                               bswap_32big(0x1785c39eU),
                               bswap_32big(0xc4a7b7acU),
                               bswap_32big(0x2a383cabU));
                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0008H, 0x0000500aU);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_Text[0]);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_Text[1]);

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x00000863U);

                WR1_PROG(REG_0094H, 0x000368a5U);

                for (iLoop = 2; iLoop < WRAPPED_KEY_SIZE; )
                {
                    WR1_PROG(REG_0094H, 0x000008c6U);
                    WR1_PROG(REG_0094H, 0x34202865U);
                    WR1_PROG(REG_0094H, 0x2000d0c0U);

                    WR1_PROG(REG_0094H, 0x00007c06U);
                    WR1_PROG(REG_0040H, 0x00602000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0xa887bc1bU),
                                   bswap_32big(0x47ad9e65U),
                                   bswap_32big(0xde99ba43U),
                                   bswap_32big(0x98ba2ddbU));
                    WR1_PROG(REG_009CH, 0x81820007U);
                    WR1_PROG(REG_0008H, 0x0000500aU);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_Text[iLoop]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_Text[iLoop + 1]);

                    WR1_PROG(REG_0094H, 0x0000a4e0U);
                    WR1_PROG(REG_0094H, 0x00000008U);

                    WR1_PROG(REG_0094H, 0x00002c60U);

                    r_rsip_func101(bswap_32big(0xdef46c17U),
                                   bswap_32big(0x1553b742U),
                                   bswap_32big(0x303f9199U),
                                   bswap_32big(0xb233c79cU));
                    iLoop = iLoop + 2;
                }

                WR1_PROG(REG_0094H, 0x38000865U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func102(bswap_32big(0x6f2f4dbaU),
                               bswap_32big(0x68da6a1eU),
                               bswap_32big(0xc5b12857U),
                               bswap_32big(0x0d709620U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
