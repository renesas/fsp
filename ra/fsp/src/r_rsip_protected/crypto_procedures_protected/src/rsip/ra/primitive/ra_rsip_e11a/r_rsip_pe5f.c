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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

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

    r_rsip_func_sub016(0x000008e7U, 0x300088a0U, 0x00000000U);
    r_rsip_func_sub016(0x00030020U, 0x00002ce0U, 0x00000080U);

    r_rsip_func_sub016(0x300088a0U, 0x0000000dU, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    r_rsip_func_sub007(0x00000080U, 0x38000ce7U, 0x00260000U);

    r_rsip_func100(bswap_32big(0x44f4025eU),
                   bswap_32big(0x9b213911U),
                   bswap_32big(0x9da2ee54U),
                   bswap_32big(0xf1841a6cU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe2090228U), bswap_32big(0x202d8015U), bswap_32big(0x62bc6475U),
                       bswap_32big(0x1e84a15aU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x38000ca5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0xc99f732cU), bswap_32big(0xe455318bU), bswap_32big(0xb3942fa6U),
                       bswap_32big(0xefbcf5c9U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x800100e0U, 0x0000e504U);

            r_rsip_func101(bswap_32big(0x52569860U), bswap_32big(0x66c317a8U), bswap_32big(0xeb35316aU),
                           bswap_32big(0xe47cd3c5U));
            r_rsip_func143();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            r_rsip_func_sub002(0x800100e0U, 0x0000e504U);

            r_rsip_func101(bswap_32big(0x4d2301aeU), bswap_32big(0x6f21a515U), bswap_32big(0xf71aa2dbU),
                           bswap_32big(0xf1f9e924U));
            r_rsip_func044();

            WAIT_STS(REG_00F8H, 0, 1);

            r_rsip_func100(bswap_32big(0x291eda37U), bswap_32big(0x54661415U), bswap_32big(0x24f96d86U),
                           bswap_32big(0x9810e22eU));
            r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

            r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func_sub016(0x0000a8a0U, 0x00000002U, 0x000268a5U);

            WR1_PROG(REG_0094H, 0x00000884U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
            {
                r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0xf7008d05U);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

                r_rsip_func_sub009(0x01410011U, 0x00002c80U);

                r_rsip_func101(bswap_32big(0xae784995U),
                               bswap_32big(0xc5402b9aU),
                               bswap_32big(0xf4104232U),
                               bswap_32big(0xe3c7d703U));
                iLoop = iLoop + 4U;
            }

            r_rsip_func_sub010(0x38000885U);

            r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

            r_rsip_func_sub006(0x9c100005U, 0x00410011U);

            r_rsip_func100(bswap_32big(0xb778a933U), bswap_32big(0x03c45ec8U), bswap_32big(0x11fe896fU),
                           bswap_32big(0xeb476a27U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x939d1d40U),
                               bswap_32big(0x175a4a0dU),
                               bswap_32big(0xad7486ccU),
                               bswap_32big(0x925c76eaU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x1784d33bU),
                               bswap_32big(0x91ca4667U),
                               bswap_32big(0x0ce242ffU),
                               bswap_32big(0xe64c7d9fU));
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x2916cc0aU), bswap_32big(0x31c74cb1U), bswap_32big(0xf019e318U),
                           bswap_32big(0x6f75c56cU));
        }

        WAIT_STS(REG_00F8H, 0, 1);

        WR1_PROG(REG_0014H, 0x00020064U);

        for (iLoop = 0U; iLoop < MAX_CNT; iLoop++)
        {
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_Msg[iLoop]);
        }

        WAIT_STS(REG_00F8H, 2, 0);

        WR1_PROG(REG_0014H, 0x00000000U);

        WR1_PROG(REG_0040H, 0x00001600U);

        WR1_PROG(REG_00F4H, 0x00000100U);

        WR1_PROG(REG_00F4H, 0x00000020U);

        r_rsip_func_sub004(0x0000140cU, 0x00c50021U);

        WR1_PROG(REG_00F4H, 0x00000010U);

        WR1_PROG(REG_0014H, 0x000007a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_PROG(REG_002CH,
                 bswap_32big(0x6a09e667U),
                 bswap_32big(0xbb67ae85U),
                 bswap_32big(0x3c6ef372U),
                 bswap_32big(0xa54ff53aU),
                 bswap_32big(0x510e527fU),
                 bswap_32big(0x9b05688cU),
                 bswap_32big(0x1f83d9abU),
                 bswap_32big(0x5be0cd19U));

        WR1_PROG(REG_00F4H, 0x00000011U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        r_rsip_func_sub004(0x00001804U, 0x00430011U);

        r_rsip_func_sub006(0x08000055U, 0x00430011U);

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0xfc55180aU), bswap_32big(0xf703bfd1U), bswap_32big(0x0db9e328U),
                       bswap_32big(0x58a83a1bU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func002();

            r_rsip_func101(bswap_32big(0x4f39addaU), bswap_32big(0x38199c51U), bswap_32big(0x806273c5U),
                           bswap_32big(0x22677792U));
        }
        else
        {
            WR1_PROG(REG_0000H, 0x01410021U);
            WR1_PROG(REG_0014H, 0x000007a1U);

            WR1_PROG(REG_00D0H, 0x0c000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU));

            WR1_PROG(REG_00D0H, 0x0c100105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU));

            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000045U);
            r_rsip_func_sub004(0x00001808U, 0x00430011U);

            r_rsip_func_sub006(0x08000055U, 0x00430011U);

            WR1_PROG(REG_0000H, 0x01410021U);
            WR1_PROG(REG_0014H, 0x000007a1U);

            WR1_PROG(REG_00D0H, 0x0c000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU));

            WR1_PROG(REG_00D0H, 0x0c100105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU),
                     bswap_32big(0x5c5c5c5cU));

            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0xc200c3b5U), bswap_32big(0xd577b378U), bswap_32big(0x0bf80a71U),
                           bswap_32big(0x5c130897U));
        }

        r_rsip_func_sub004(0x0000180cU, 0x01430021U);

        WR1_PROG(REG_0014H, 0x000000a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x80000000U));

        WR1_PROG(REG_0000H, 0x01400015U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000001a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_PROG(REG_002CH, bswap_32big(0x00000000U), bswap_32big(0x00000300U));

        WAIT_STS(REG_00F8H, 2, 0);

        WR1_PROG(REG_00F4H, 0x00000100U);

        WR1_PROG(REG_0040H, 0x00001600U);

        r_rsip_func100(bswap_32big(0xa7751a8bU), bswap_32big(0x7a6858dcU), bswap_32big(0xa462822fU),
                       bswap_32big(0x1fa3a720U));
        r_rsip_func103();

        r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);

        r_rsip_func_sub003(0x80010000U, 0x03410005U);
        r_rsip_func_sub009(0x0001000dU, 0x000034c0U);

        r_rsip_func_sub002(0x800100e0U, 0x0000e505U);

        r_rsip_func101(bswap_32big(0x4882d44fU), bswap_32big(0x3d1a8e30U), bswap_32big(0xcd21bed3U),
                       bswap_32big(0xf24ba31aU));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x01799093U);

        r_rsip_func_sub002(0x800100e0U, 0x0000e505U);

        r_rsip_func101(bswap_32big(0x7a87c052U), bswap_32big(0x511b3e14U), bswap_32big(0xac886483U),
                       bswap_32big(0x3179c944U));
        r_rsip_func044();

        WR1_PROG(REG_00F4H, 0x00000020U);

        r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

        r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func100(bswap_32big(0xa861e49bU), bswap_32big(0x752e79cfU), bswap_32big(0x7ea59d25U),
                       bswap_32big(0x532f0bc4U));
        WR1_PROG(REG_00D4H, 0x40000100U);
        r_rsip_func_sub006(0xe7008d07U, 0x00450021U);

        WR1_PROG(REG_0008H, 0x00001022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KDFInfo[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KDFInfo[5]);

        r_rsip_func100(bswap_32big(0x2169e4acU), bswap_32big(0xfdc8a492U), bswap_32big(0x4fb9b467U),
                       bswap_32big(0x471c978dU));
        r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func_sub006(0x09108105U, 0x00410011U);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_KDFInfo[9]);

        r_rsip_func100(bswap_32big(0xf67c5beeU), bswap_32big(0x5054c4bdU), bswap_32big(0x4febccd9U),
                       bswap_32big(0x634fe56fU));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_KDFInfo[0]);

        r_rsip_func102(bswap_32big(0x69192b72U), bswap_32big(0x31e41757U), bswap_32big(0xeca3af7eU),
                       bswap_32big(0xfce4d307U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
