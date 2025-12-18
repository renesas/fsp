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

rsip_ret_t r_rsip_pe5i (const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00e50001U, 0x000000c7U, 0x80010020U);
    WR1_PROG(REG_002CH, InData_KeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x800100e0U, 0x0000e501U);

    r_rsip_func101(bswap_32big(0xcd3dcd75U),
                   bswap_32big(0x8e794e96U),
                   bswap_32big(0xaf862c11U),
                   bswap_32big(0x1fe751d3U));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x38000c21U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0x58dcc9b5U),
                   bswap_32big(0xbcae4d45U),
                   bswap_32big(0x29e27253U),
                   bswap_32big(0x2a5a3318U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub016(0x0000b4c0U, 0x0000001bU, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000008U);

        WR1_PROG(REG_00B0H, 0x00001404U);

        r_rsip_func101(bswap_32big(0x4bd3495cU), bswap_32big(0xbf00a9ecU), bswap_32big(0x662a2ffdU),
                       bswap_32big(0x50ebd57fU));
    }
    else
    {
        r_rsip_func_sub016(0x0000b4c0U, 0x01b41ce9U, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00B0H, 0x00003408U);

        r_rsip_func101(bswap_32big(0x2886bd94U), bswap_32big(0x2cfa656aU), bswap_32big(0xf62e4011U),
                       bswap_32big(0x0b291fb6U));
    }

    r_rsip_func_sub002(0x800100e0U, 0x0000e501U);

    r_rsip_func101(bswap_32big(0xc63efd11U),
                   bswap_32big(0x8d7c676eU),
                   bswap_32big(0xc2b27cacU),
                   bswap_32big(0xeaa25480U));
    r_rsip_func044();

    r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func100(bswap_32big(0xde0abf76U),
                   bswap_32big(0x24487690U),
                   bswap_32big(0xd423affeU),
                   bswap_32big(0x1db097e1U));
    WR1_PROG(REG_009CH, 0x81010060U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_0094H, 0x000008e7U);

    for (iLoop = 0U; iLoop < S_RAM[0]; )
    {
        r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0xf7008d05U);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        r_rsip_func_sub009(0x00c10011U, 0x0000a4e0U);
        WR1_PROG(REG_0094H, 0x00000004U);

        r_rsip_func101(bswap_32big(0x3c25180aU), bswap_32big(0x0b5ba0c6U), bswap_32big(0x5b13b93eU),
                       bswap_32big(0x2eb14b5aU));
        iLoop = iLoop + 4U;
    }

    r_rsip_func_sub010(0x380008e3U);

    r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

    r_rsip_func_sub006(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0xa1644ea3U),
                   bswap_32big(0x13f9d061U),
                   bswap_32big(0x88b6bc3dU),
                   bswap_32big(0x5cc69f22U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x82603d0cU), bswap_32big(0xee1dafc6U), bswap_32big(0x1c1a7947U),
                       bswap_32big(0x88193035U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
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

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0x98ccef83U), bswap_32big(0x555ed3f6U), bswap_32big(0x3ee93636U),
                       bswap_32big(0xe5f47d93U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func001();

            r_rsip_func101(bswap_32big(0x45874a19U), bswap_32big(0x5065dff9U), bswap_32big(0xe4e1dd6cU),
                           bswap_32big(0x68cf1310U));
        }
        else
        {
            WR1_PROG(REG_00D0H, 0x08000045U);
            r_rsip_func_sub004(0x00001804U, 0x00430011U);

            r_rsip_func_sub006(0x08000055U, 0x00430011U);

            WR1_PROG(REG_0000H, 0x01410021U);
            WR1_PROG(REG_0014H, 0x000007a1U);

            WR1_PROG(REG_00D0H, 0x0c000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U));

            WR1_PROG(REG_00D0H, 0x0c100105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U));

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
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U));

            WR1_PROG(REG_00D0H, 0x0c100105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U),
                     bswap_32big(0x36363636U));

            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x039d8b3fU), bswap_32big(0xc0737f3bU), bswap_32big(0x9c1fa17bU),
                           bswap_32big(0x0e91a88dU));
        }

        r_rsip_func101(bswap_32big(0x0b4eb894U), bswap_32big(0x43ccfa0eU), bswap_32big(0xd8c88f8cU),
                       bswap_32big(0x8658fbf2U));

        return RSIP_RET_PASS;
    }
}
