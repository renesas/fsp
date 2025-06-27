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
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x9c80c788U),
                   bswap_32big(0x2a95778fU),
                   bswap_32big(0x8998d340U),
                   bswap_32big(0x021df710U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x4f273077U), bswap_32big(0x289fef1bU), bswap_32big(0x9fbb8fe5U),
                       bswap_32big(0x9370bf29U));
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

        r_rsip_func100(bswap_32big(0xdaac6d26U), bswap_32big(0x93584a11U), bswap_32big(0xbfc6f33fU),
                       bswap_32big(0x2e523f79U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000005U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000090U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xedba8c40U), bswap_32big(0xb389c5caU), bswap_32big(0x838c761cU),
                           bswap_32big(0x0a54468fU));
            r_rsip_func440(InData_KeyIndex);

            r_rsip_func100(bswap_32big(0x099d380cU), bswap_32big(0x9d147c05U), bswap_32big(0x10fd1f50U),
                           bswap_32big(0xd066e7beU));
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

            r_rsip_func101(bswap_32big(0xf8894e3bU), bswap_32big(0x9fce4b5dU), bswap_32big(0xedc510dcU),
                           bswap_32big(0xa9ac08f5U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000007U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000090U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x69990113U), bswap_32big(0x19ffe889U), bswap_32big(0xf3e38e5fU),
                           bswap_32big(0xff59d66cU));
            r_rsip_func441(InData_KeyIndex);

            r_rsip_func100(bswap_32big(0xd6206f64U), bswap_32big(0x25dec164U), bswap_32big(0x3849470aU),
                           bswap_32big(0xffa6fadbU));
            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x0000181eU);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x39e3ba83U), bswap_32big(0x6b70413aU), bswap_32big(0x2ac310bbU),
                           bswap_32big(0xdf71d321U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D4H, 0x40000000U);

            r_rsip_func101(bswap_32big(0xe544a19aU), bswap_32big(0xc90c215fU), bswap_32big(0xf7a3f475U),
                           bswap_32big(0xe0486889U));
        }

        r_rsip_func100(bswap_32big(0x15666930U), bswap_32big(0xa2d82daeU), bswap_32big(0xa69bc796U),
                       bswap_32big(0x2e80ace0U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x7f295659U), bswap_32big(0xa5c7790fU), bswap_32big(0x4cb0b56fU),
                           bswap_32big(0x54996f9bU));
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

            for (iLoop = 2; iLoop < WRAPPED_KEY_SIZE; iLoop = iLoop + 2)
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

                r_rsip_func101(bswap_32big(0x4f61659eU),
                               bswap_32big(0x6fdc4263U),
                               bswap_32big(0xc8fe1c9eU),
                               bswap_32big(0xfae3e9daU));
            }

            WR1_PROG(REG_0094H, 0x38000865U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            WR1_PROG(REG_0040H, 0x00402000U);

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

                    r_rsip_func101(bswap_32big(0xb426fe27U),
                                   bswap_32big(0x610d6daaU),
                                   bswap_32big(0x104dd64dU),
                                   bswap_32big(0xecb1c94eU));
                }

                WR1_PROG(REG_0094H, 0x38000cc6U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00002ca0U);

                r_rsip_func101(bswap_32big(0x027857d4U),
                               bswap_32big(0x70773527U),
                               bswap_32big(0x3d72540dU),
                               bswap_32big(0xdbb1b2b2U));
            }

            WR1_PROG(REG_0094H, 0x380088a0U);
            WR1_PROG(REG_0094H, 0x00000006U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0094H, 0x38008800U);
            WR1_PROG(REG_0094H, 0xa6a6a6a6U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0xa6a6a6a6U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0x92005d33U), bswap_32big(0x6619a033U), bswap_32big(0xcb6e9ee2U),
                           bswap_32big(0xa9b1866cU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x1f040664U),
                               bswap_32big(0x00de8b7aU),
                               bswap_32big(0x3250f3b3U),
                               bswap_32big(0xb69b4f69U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x205fa2a6U),
                               bswap_32big(0xb45d6feeU),
                               bswap_32big(0x25b8ca41U),
                               bswap_32big(0xdbec6aeeU));

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
                WR1_PROG(REG_002CH, bswap_32big(0x00000090U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x035eb0fdU),
                               bswap_32big(0x2a121fc6U),
                               bswap_32big(0xcf994f75U),
                               bswap_32big(0x189eb2e3U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x000034c4U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000090U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xf9294de5U),
                               bswap_32big(0xaa6de478U),
                               bswap_32big(0x2116e5fbU),
                               bswap_32big(0x28c7f63aU));
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

                for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; iLoop = iLoop + 4U)
                {
                    WR1_PROG(REG_0094H, 0x000008c6U);
                    WR1_PROG(REG_0094H, 0x34202881U);
                    WR1_PROG(REG_0094H, 0x2000d0c0U);

                    WR1_PROG(REG_0094H, 0x00007c06U);
                    WR1_PROG(REG_0040H, 0x00602000U);

                    r_rsip_func100(bswap_32big(0x39c0a0e2U),
                                   bswap_32big(0x0119de6fU),
                                   bswap_32big(0xf33f7afeU),
                                   bswap_32big(0x4f6b8387U));
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

                    r_rsip_func101(bswap_32big(0x9adf5b90U),
                                   bswap_32big(0xbe2fe00eU),
                                   bswap_32big(0x2e9ad64cU),
                                   bswap_32big(0xb3c46649U));
                }

                WR1_PROG(REG_0094H, 0x38000881U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func100(bswap_32big(0x1b99e6cfU),
                               bswap_32big(0x5ea5970dU),
                               bswap_32big(0x0faf07b5U),
                               bswap_32big(0x73ca92baU));
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

                r_rsip_func100(bswap_32big(0xcdc6b124U),
                               bswap_32big(0x7e4f0bc8U),
                               bswap_32big(0x9b4a0922U),
                               bswap_32big(0xc3f1136bU));
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                r_rsip_func102(bswap_32big(0xf101e0ddU),
                               bswap_32big(0xe0faf36cU),
                               bswap_32big(0x08028894U),
                               bswap_32big(0x8eb5d771U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
