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

rsip_ret_t r_rsip_pe5f (const uint32_t InData_Msg[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        uint32_t       OutData_KDFInfo[],
                        uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100a0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x000008e7U);

    WR1_PROG(REG_0094H, 0x300088a0U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_0094H, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0094H, 0x300088a0U);
    WR1_PROG(REG_0094H, 0x0000000dU);
    WR1_PROG(REG_0094H, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0094H, 0x300088a0U);
    WR1_PROG(REG_0094H, 0x00000011U);
    WR1_PROG(REG_0094H, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0094H, 0x38000ce7U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xbb586cafU),
                   bswap_32big(0xedfb77e0U),
                   bswap_32big(0x04de4fdaU),
                   bswap_32big(0x6a15df92U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x12ba7348U), bswap_32big(0x1ca4682fU), bswap_32big(0x1a9b773eU),
                       bswap_32big(0xe5fd36fdU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x38000ca5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0xc032819bU), bswap_32big(0x5f824611U), bswap_32big(0x3f66c088U),
                       bswap_32big(0xaacd8effU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000e504U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x73b4d1a4U), bswap_32big(0x9d8952b7U), bswap_32big(0x3c33282aU),
                           bswap_32big(0x1ff91b6bU));
            r_rsip_func143();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000e504U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x86a2e62eU), bswap_32big(0x987d153dU), bswap_32big(0x9b599951U),
                           bswap_32big(0x96e13fdeU));
            r_rsip_func044();

            WAIT_STS(REG_0118H, 0, 1);

            r_rsip_func100(bswap_32big(0x149c0475U), bswap_32big(0x19e36a4cU), bswap_32big(0x5359f0caU),
                           bswap_32big(0x1f872997U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0094H, 0x0000a8a0U);
            WR1_PROG(REG_0094H, 0x00000002U);
            WR1_PROG(REG_0094H, 0x000268a5U);

            WR1_PROG(REG_0094H, 0x00000821U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
            {
                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0xf7008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

                WR1_PROG(REG_0000H, 0x01410011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x8205e9aaU),
                               bswap_32big(0xecfae505U),
                               bswap_32big(0x063c3e34U),
                               bswap_32big(0x5f1eadefU));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_0094H, 0x38000825U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);
            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x5179dcdeU), bswap_32big(0x87e7900eU), bswap_32big(0x348e5b5dU),
                           bswap_32big(0x703e409dU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x326e92a6U),
                               bswap_32big(0x79de6402U),
                               bswap_32big(0xc5ecca70U),
                               bswap_32big(0x985893eaU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x245b9a59U),
                               bswap_32big(0xd0f4d6ebU),
                               bswap_32big(0x31a63f71U),
                               bswap_32big(0x2769a979U));
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x85e76a12U), bswap_32big(0x9c4bf558U), bswap_32big(0x4c3647c2U),
                           bswap_32big(0xacc156a4U));
        }

        WAIT_STS(REG_0118H, 0, 1);

        WR1_PROG(REG_0014H, 0x00020064U);

        for (iLoop = 0U; iLoop < MAX_CNT; iLoop++)
        {
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_Msg[iLoop]);
        }

        WR1_PROG(REG_0014H, 0x00000000U);
        WAIT_STS(REG_0118H, 8, 0);
        WR1_PROG(REG_0040H, 0x00001600U);

        WAIT_STS(REG_0118H, 4, 1);

        r_rsip_func100(bswap_32big(0x88acafeeU), bswap_32big(0x8174c3c7U), bswap_32big(0xe454bc47U),
                       bswap_32big(0x1908feaeU));
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
        WR1_PROG(REG_002CH, bswap_32big(0x0000e505U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xfb3300b0U), bswap_32big(0x6e830222U), bswap_32big(0x765622d1U),
                       bswap_32big(0xcbef19c5U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x01799093U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000e505U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xd470580fU), bswap_32big(0x833eefcaU), bswap_32big(0xa828b622U),
                       bswap_32big(0x1e4332a9U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0094H, 0x000008e7U);

        WR1_PROG(REG_0094H, 0x30003080U);
        WR1_PROG(REG_0094H, 0x00070020U);
        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x00000008U);
        WR1_PROG(REG_0094H, 0x00030040U);
        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x0000000cU);
        WR1_PROG(REG_0094H, 0x00000080U);

        r_rsip_func100(bswap_32big(0xe1d2adeeU), bswap_32big(0xc37666b7U), bswap_32big(0xb333e257U),
                       bswap_32big(0x36bb84c2U));
        WR1_PROG(REG_009CH, 0x810100a0U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            r_rsip_func100(bswap_32big(0x7cfb2a2eU), bswap_32big(0xd46ede94U), bswap_32big(0xe57abad1U),
                           bswap_32big(0x360215e4U));
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xe7008d05U);
            WR1_PROG(REG_0000H, 0x00450011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KDFInfo[iLoop + 1]);

            WR1_PROG(REG_0094H, 0x0000a4e0U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x032750eeU), bswap_32big(0x17625f29U), bswap_32big(0x13459aeeU),
                           bswap_32big(0x7c8d5c4eU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_0094H, 0x380008e5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);
        WR1_PROG(REG_0040H, 0x00402000U);

        r_rsip_func100(bswap_32big(0x8eaf4c4eU), bswap_32big(0x0c08232cU), bswap_32big(0x370576d4U),
                       bswap_32big(0xdd1f1b63U));
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
        RD4_ADDR(REG_002CH, &OutData_KDFInfo[iLoop + 1]);

        r_rsip_func100(bswap_32big(0xd952bb3aU), bswap_32big(0xde2f723eU), bswap_32big(0x60ee51f9U),
                       bswap_32big(0xc9ba7393U));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_KDFInfo[0]);

        r_rsip_func102(bswap_32big(0x7e0a4f62U), bswap_32big(0xde7e611cU), bswap_32big(0x4a6df031U),
                       bswap_32big(0xcd4cda98U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
