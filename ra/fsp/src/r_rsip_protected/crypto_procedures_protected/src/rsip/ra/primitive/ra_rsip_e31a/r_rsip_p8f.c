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
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x6bdf5203U),
                   bswap_32big(0x100cee15U),
                   bswap_32big(0x6f825f89U),
                   bswap_32big(0x8a64f422U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x8547f411U), bswap_32big(0x6f8292f1U), bswap_32big(0xc35f6d75U),
                       bswap_32big(0x24c7ff17U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003486U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x9b208424U), bswap_32big(0xf8f96fe3U), bswap_32big(0xee039ac7U),
                       bswap_32big(0x9a9142e7U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000005U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000008fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa1008e0dU), bswap_32big(0x3c1664fbU), bswap_32big(0x5091f263U),
                           bswap_32big(0xc6960c83U));
            r_rsip_func440(InData_KeyIndex);

            r_rsip_func101(bswap_32big(0xe4e2028eU), bswap_32big(0x0621621aU), bswap_32big(0x699e2c29U),
                           bswap_32big(0xf76a65feU));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000007U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000008fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x3ed1eb53U), bswap_32big(0x09904c91U), bswap_32big(0xdb6bf867U),
                           bswap_32big(0x1dd8a24aU));
            r_rsip_func441(InData_KeyIndex);

            r_rsip_func101(bswap_32big(0x6cebc5ebU), bswap_32big(0x34d98932U), bswap_32big(0x61876f03U),
                           bswap_32big(0xa14f939eU));
        }

        r_rsip_func100(bswap_32big(0xb3af5de1U), bswap_32big(0x5e447bb6U), bswap_32big(0x8a4840b4U),
                       bswap_32big(0x33702ee4U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xa6722325U), bswap_32big(0xfea8bcc2U), bswap_32big(0xbd0f1e2fU),
                           bswap_32big(0xf7e9b445U));
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
            WR1_PROG(REG_002CH, bswap_32big(0x0000008fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe0c340e5U), bswap_32big(0xf33b113aU), bswap_32big(0xc7558c52U),
                           bswap_32big(0x469e3208U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x000034c3U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000008fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xdc8a8976U), bswap_32big(0x9c487474U), bswap_32big(0x71d6d6a2U),
                           bswap_32big(0xa0c86e8bU));
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

            for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; iLoop = iLoop + 4U)
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

                r_rsip_func101(bswap_32big(0x17d38572U),
                               bswap_32big(0xc85cf38aU),
                               bswap_32big(0xc82dd22aU),
                               bswap_32big(0xcaa78cbbU));
            }

            WR1_PROG(REG_0094H, 0x38000847U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_WrappedKeyIndex[iLoop + 1]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x75bbd83cU), bswap_32big(0x23a579a9U), bswap_32big(0x4045e828U),
                           bswap_32big(0xbc74141aU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x3b0460f9U),
                               bswap_32big(0xe369c89eU),
                               bswap_32big(0x65423aaaU),
                               bswap_32big(0x76791c44U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_0094H, 0x38000c84U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                r_rsip_func100(bswap_32big(0x1df3bd3aU),
                               bswap_32big(0xb36560b3U),
                               bswap_32big(0x7bbb6b20U),
                               bswap_32big(0x1dafb02bU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func100(bswap_32big(0x882e7c90U),
                                   bswap_32big(0xef6d64dfU),
                                   bswap_32big(0x722a0431U),
                                   bswap_32big(0xd44f3774U));

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

                    r_rsip_func101(bswap_32big(0x14dd885bU),
                                   bswap_32big(0x2783dd9cU),
                                   bswap_32big(0x7cf03258U),
                                   bswap_32big(0x799f97a5U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xca6ac8fcU),
                                   bswap_32big(0x7b1be157U),
                                   bswap_32big(0xfdab8e4fU),
                                   bswap_32big(0x64d6fcf0U));

                    WR1_PROG(REG_00D0H, 0x08000085U);
                    WR1_PROG(REG_00B0H, 0x0000181eU);
                    WR1_PROG(REG_0000H, 0x00430011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func100(bswap_32big(0x3a567b5dU),
                                   bswap_32big(0x8171a245U),
                                   bswap_32big(0x3674b621U),
                                   bswap_32big(0x15bc4d6bU));
                    WR1_PROG(REG_00D0H, 0x08000095U);
                    WR1_PROG(REG_0000H, 0x00430011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_00D4H, 0x40000000U);

                    r_rsip_func101(bswap_32big(0x509fcf21U),
                                   bswap_32big(0x4a2606d4U),
                                   bswap_32big(0x078af485U),
                                   bswap_32big(0xb6a5bde6U));
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

                        r_rsip_func101(bswap_32big(0x86591fc1U),
                                       bswap_32big(0x7ac576b6U),
                                       bswap_32big(0xe4e61d93U),
                                       bswap_32big(0x6a631b88U));
                    }

                    WR1_PROG(REG_0094H, 0x380008e5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    WR1_PROG(REG_0040H, 0x00402000U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0x31a73bdeU),
                                   bswap_32big(0xd5700f7cU),
                                   bswap_32big(0x9c886a7eU),
                                   bswap_32big(0xafc98011U));
                }

                WR1_PROG(REG_0094H, 0x380088c0U);
                WR1_PROG(REG_0094H, 0x00000006U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func100(bswap_32big(0xe7925d08U),
                               bswap_32big(0xf1ab9484U),
                               bswap_32big(0x0962a014U),
                               bswap_32big(0xb83dbbc1U));
                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0008H, 0x0000500aU);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_Text[0]);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_Text[1]);

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x00000863U);

                WR1_PROG(REG_0094H, 0x000368a5U);

                for (iLoop = 2; iLoop < WRAPPED_KEY_SIZE; iLoop = iLoop + 2)
                {
                    WR1_PROG(REG_0094H, 0x000008c6U);
                    WR1_PROG(REG_0094H, 0x34202865U);
                    WR1_PROG(REG_0094H, 0x2000d0c0U);

                    WR1_PROG(REG_0094H, 0x00007c06U);
                    WR1_PROG(REG_0040H, 0x00602000U);

                    r_rsip_func100(bswap_32big(0xbd92fde4U),
                                   bswap_32big(0x5cbaf69bU),
                                   bswap_32big(0x86662d92U),
                                   bswap_32big(0x73f91c6eU));
                    WR1_PROG(REG_009CH, 0x81820007U);
                    WR1_PROG(REG_0008H, 0x0000500aU);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_Text[iLoop]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_Text[iLoop + 1]);

                    WR1_PROG(REG_0094H, 0x0000a4e0U);
                    WR1_PROG(REG_0094H, 0x00000008U);

                    WR1_PROG(REG_0094H, 0x00002c60U);

                    r_rsip_func101(bswap_32big(0xda605fdfU),
                                   bswap_32big(0x30c29b99U),
                                   bswap_32big(0xca6fb82fU),
                                   bswap_32big(0x612ddfc2U));
                }

                WR1_PROG(REG_0094H, 0x38000865U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func102(bswap_32big(0xace8f447U),
                               bswap_32big(0x586e40b4U),
                               bswap_32big(0x97d84f7dU),
                               bswap_32big(0xe080e1e4U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
