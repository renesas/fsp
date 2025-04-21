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

rsip_ret_t r_rsip_p50i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00500001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a880U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x37a7ae57U),
                   bswap_32big(0x950c063cU),
                   bswap_32big(0x4f5f7f91U),
                   bswap_32big(0x480fb1abU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x01084dc2U),
                   bswap_32big(0x2f642a43U),
                   bswap_32big(0x655439daU),
                   bswap_32big(0x422012ebU));
    r_rsip_func044();

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

    r_rsip_func100(bswap_32big(0x5898a5a7U),
                   bswap_32big(0xc10ec368U),
                   bswap_32big(0xd30f6420U),
                   bswap_32big(0xa09c3e59U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc200eb92U), bswap_32big(0x9c300ebcU), bswap_32big(0xf19c75d8U),
                       bswap_32big(0x50179ae6U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xdf384a7dU), bswap_32big(0x8332d745U), bswap_32big(0x43996ca6U),
                       bswap_32big(0x94119020U));
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func100(bswap_32big(0xc08fae7fU), bswap_32big(0xfe3f9e65U), bswap_32big(0x1b548b2cU),
                           bswap_32big(0x7a68e074U));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x063bd2b1U), bswap_32big(0x3bf19d47U), bswap_32big(0x7e6dba42U),
                           bswap_32big(0xf18c2e47U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x540e8f45U), bswap_32big(0x8dffb326U), bswap_32big(0x267495a9U),
                           bswap_32big(0xe06bf2a5U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0x822c6ffaU), bswap_32big(0xa672fa12U), bswap_32big(0x179049caU),
                           bswap_32big(0xe5be87e0U));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0xdc701691U), bswap_32big(0x16cfec28U), bswap_32big(0xb89641feU),
                           bswap_32big(0x7fc4daddU));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x40fd78a4U), bswap_32big(0x8ef1af82U), bswap_32big(0x029308e6U),
                           bswap_32big(0x335e3e54U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00005001U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x6c851545U), bswap_32big(0x4ebcb0ecU), bswap_32big(0xa29419c5U),
                           bswap_32big(0x123e9e17U));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x8de4ffd0U), bswap_32big(0xb906cc83U), bswap_32big(0x59bceb45U),
                           bswap_32big(0xa0ec8583U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x3a676115U),
                               bswap_32big(0x6d0d55e4U),
                               bswap_32big(0x3289a63aU),
                               bswap_32big(0xfd1f5ff6U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_009CH, 0x81840001U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x049742f8U),
                               bswap_32big(0xada515baU),
                               bswap_32big(0xf108cffeU),
                               bswap_32big(0xb21f4826U));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x85b732dfU),
                               bswap_32big(0xf8bfaa2aU),
                               bswap_32big(0x54591be0U),
                               bswap_32big(0xd1833c33U));
                WR1_PROG(REG_00D0H, 0x08000095U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xe25ed2e2U),
                               bswap_32big(0x27cbb552U),
                               bswap_32big(0x61bcfb8cU),
                               bswap_32big(0x27746677U));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00005002U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x7835ec33U), bswap_32big(0x65451ba6U), bswap_32big(0x49b62412U),
                           bswap_32big(0x84e71cbfU));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x82e9ab3eU), bswap_32big(0x663d19d2U), bswap_32big(0xb9e6b499U),
                           bswap_32big(0x9e541a26U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xc0f599d3U),
                               bswap_32big(0x847734bcU),
                               bswap_32big(0x71005931U),
                               bswap_32big(0x62f7966cU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_009CH, 0x81840001U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x7faaf202U),
                               bswap_32big(0x0bf66c41U),
                               bswap_32big(0x2cc13b9fU),
                               bswap_32big(0x7a5d0233U));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x01660738U),
                               bswap_32big(0x8e864df0U),
                               bswap_32big(0x2d5d2d0aU),
                               bswap_32big(0x0e0da958U));
                WR1_PROG(REG_00D0H, 0x08000095U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x958b0015U),
                               bswap_32big(0xc3d175a2U),
                               bswap_32big(0x939ea944U),
                               bswap_32big(0xfde2a0e4U));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            r_rsip_func100(bswap_32big(0xe10ab048U), bswap_32big(0xb1082085U), bswap_32big(0xf1d7737dU),
                           bswap_32big(0x8bc69b36U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x98e57375U), bswap_32big(0x79659dd5U), bswap_32big(0x55ccf10dU),
                           bswap_32big(0xc3c798fdU));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0xd0e3d22fU), bswap_32big(0x1a6d61a8U), bswap_32big(0x5b3bcfa8U),
                           bswap_32big(0xafa1dc08U));
        }
        else
        {
        }

        return RSIP_RET_PASS;
    }
}
