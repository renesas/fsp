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

rsip_ret_t r_rsip_pf9 (const uint32_t InData_CurveType[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_PubKeyIndex[],
                       uint32_t       OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f90001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func027(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x000034c0U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x0000a438U);

    r_rsip_func100(bswap_32big(0x5502da09U),
                   bswap_32big(0x2bc831ebU),
                   bswap_32big(0x7ca03579U),
                   bswap_32big(0xadeaf2f6U));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xbc0e9a91U),
                   bswap_32big(0xc663f43fU),
                   bswap_32big(0xf1772460U),
                   bswap_32big(0x736b8c98U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x00010009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x874b3659U),
                   bswap_32big(0x037a6323U),
                   bswap_32big(0x81e8b5c1U),
                   bswap_32big(0xcd2ff8ceU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x6d606379U),
                   bswap_32big(0x0286ab85U),
                   bswap_32big(0x85d2aa87U),
                   bswap_32big(0x893299e4U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00009415U);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B4H, 0x0015000eU);
    WR1_PROG(REG_00B8H, 0x001c0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B0H, 0x00009454U);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B0H, 0x00009423U);
    WR1_PROG(REG_0000H, 0x00c00031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_0094H, 0x00000863U);
    WR1_PROG(REG_0094H, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        WR1_PROG(REG_00B4H, 0x001c0037U);
        WR1_PROG(REG_00B8H, 0x002a0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x00000824U);
        WR1_PROG(REG_009CH, 0x80020000U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000884U);

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_0094H, 0x2000d080U);

        WR1_PROG(REG_0094H, 0x38000c63U);
        WR1_PROG(REG_0094H, 0x1000d081U);

        WR1_PROG(REG_0094H, 0x38008880U);
        WR1_PROG(REG_0094H, 0x00000003U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x6a199833U), bswap_32big(0x21225edfU), bswap_32big(0x7fa7b803U),
                       bswap_32big(0x2af8926aU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_00B4H, 0x0023002aU);
            WR1_PROG(REG_00B8H, 0x00690000U);

            WR1_PROG(REG_00A4H, 0x06060009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            r_rsip_func101(bswap_32big(0x4c78fb83U), bswap_32big(0xaec4e66aU), bswap_32big(0xd06a8b40U),
                           bswap_32big(0x9f73cf6bU));
        }
        else
        {
            WR1_PROG(REG_00B4H, 0x0023002aU);
            WR1_PROG(REG_00B8H, 0x00370000U);

            WR1_PROG(REG_00A4H, 0x06060009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            r_rsip_func101(bswap_32big(0x6d63ad29U), bswap_32big(0x7af200efU), bswap_32big(0x5484f84aU),
                           bswap_32big(0x6b19c7adU));
        }

        WR1_PROG(REG_00B4H, 0x0054003dU);
        WR1_PROG(REG_00B8H, 0x002a0000U);

        WR1_PROG(REG_00A4H, 0x06060007U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00540037U);
        WR1_PROG(REG_00B8H, 0x00310000U);

        WR1_PROG(REG_00A4H, 0x06060007U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000082bU);
        WR1_PROG(REG_009CH, 0x80020040U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B4H, 0x0023002aU);
        WR1_PROG(REG_00B8H, 0x003d0000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00240031U);
        WR1_PROG(REG_00B8H, 0x00370000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00002ca0U);

        r_rsip_func101(bswap_32big(0x24205b4fU), bswap_32big(0x8b7497b6U), bswap_32big(0xd46d8732U),
                       bswap_32big(0xc92c1cd0U));
    }

    WR1_PROG(REG_0094H, 0x380088a0U);
    WR1_PROG(REG_0094H, 0x00000040U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0040H, 0x00402000U);

    WR1_PROG(REG_00B4H, 0x001c0037U);
    WR1_PROG(REG_00B8H, 0x002a0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B0H, 0x00000824U);
    WR1_PROG(REG_009CH, 0x80020000U);
    WR1_PROG(REG_0000H, 0x03430009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00000884U);

    WR1_PROG(REG_0094H, 0x38000c21U);
    WR1_PROG(REG_0094H, 0x2000d080U);

    WR1_PROG(REG_0094H, 0x38000c63U);
    WR1_PROG(REG_0094H, 0x1000d081U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xb80f0fc3U),
                   bswap_32big(0x8130edf7U),
                   bswap_32big(0xbac1b820U),
                   bswap_32big(0x470f5066U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_00B4H, 0x0023002aU);
        WR1_PROG(REG_00B8H, 0x00690000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        r_rsip_func101(bswap_32big(0xb73e7f1eU), bswap_32big(0x2792ddb1U), bswap_32big(0x556968beU),
                       bswap_32big(0xd75c42b9U));
    }
    else
    {
        WR1_PROG(REG_00B4H, 0x0023002aU);
        WR1_PROG(REG_00B8H, 0x00370000U);

        WR1_PROG(REG_00A4H, 0x06060009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        r_rsip_func101(bswap_32big(0xfed810bfU), bswap_32big(0x050ae387U), bswap_32big(0xed8e191dU),
                       bswap_32big(0x9abe5e6dU));
    }

    WR1_PROG(REG_00B4H, 0x00150037U);
    WR1_PROG(REG_00B8H, 0x00460000U);

    WR1_PROG(REG_00A4H, 0x06060009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0094H, 0x00003406U);

    r_rsip_func028(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000f9U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x16f649c3U),
                   bswap_32big(0x66e15067U),
                   bswap_32big(0xfdc8d975U),
                   bswap_32big(0xec719d5dU));
    r_rsip_func089();

    r_rsip_func100(bswap_32big(0xf389ff0dU),
                   bswap_32big(0xa44de422U),
                   bswap_32big(0xb6507f03U),
                   bswap_32big(0xe0229350U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xadb68688U), bswap_32big(0x02d8a149U), bswap_32big(0xcaf5985bU),
                       bswap_32big(0xfc40cb5eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x765411acU), bswap_32big(0xa004d3caU), bswap_32big(0xd94248d8U),
                       bswap_32big(0xc6a78f17U));
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
        WR1_PROG(REG_002CH, bswap_32big(0x0000f901U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xdf939ad0U), bswap_32big(0x5011ef59U), bswap_32big(0x214f3f62U),
                       bswap_32big(0xe89ea958U));
        r_rsip_func043();

        r_rsip_func076();

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f901U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x749274f9U), bswap_32big(0x6554628fU), bswap_32big(0xb1f7eaffU),
                       bswap_32big(0xb141e6daU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0x60d506a7U), bswap_32big(0xb89c23cbU), bswap_32big(0x645dec86U),
                       bswap_32big(0x62d14b28U));
        WR1_PROG(REG_00B0H, 0x00009846U);

        WR1_PROG(REG_00D4H, 0x40000200U);
        WR1_PROG(REG_00D0H, 0xe7009d07U);
        WR1_PROG(REG_0000H, 0x00430031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001032U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[5]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[9]);

        r_rsip_func100(bswap_32big(0xa8e86076U), bswap_32big(0xc3bdc4c4U), bswap_32big(0x90c3f5f4U),
                       bswap_32big(0x00d07867U));
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
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[13]);

        r_rsip_func100(bswap_32big(0x40cbf55fU), bswap_32big(0x9a2e5dcbU), bswap_32big(0xbefaa4acU),
                       bswap_32big(0xc6509d36U));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_PrivKeyIndex[0]);

        r_rsip_func100(bswap_32big(0x0737beb8U), bswap_32big(0x140fc657U), bswap_32big(0x9fc2d4ceU),
                       bswap_32big(0xf13581e2U));
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
        WR1_PROG(REG_002CH, bswap_32big(0x0000f902U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe32d7190U), bswap_32big(0x359d793bU), bswap_32big(0xb2654f99U),
                       bswap_32big(0xec3d5bf4U));
        r_rsip_func043();

        r_rsip_func077();

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f902U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x9e8468d0U), bswap_32big(0x4f83651fU), bswap_32big(0x76a5d420U),
                       bswap_32big(0x15bf2c19U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0xbf9235dfU), bswap_32big(0x1e3de2e9U), bswap_32big(0x82323264U),
                       bswap_32big(0x59737254U));
        WR1_PROG(REG_00D4H, 0x40000200U);
        WR1_PROG(REG_00D0H, 0xe8008107U);
        WR1_PROG(REG_00B0H, 0x00009838U);
        WR1_PROG(REG_0000H, 0x00430031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001032U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[5]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[9]);

        r_rsip_func100(bswap_32big(0xb9faede6U), bswap_32big(0xec5bb281U), bswap_32big(0xed6e025dU),
                       bswap_32big(0x4548fcb5U));
        WR1_PROG(REG_00D4H, 0x40000200U);
        WR1_PROG(REG_00D0H, 0xe8008107U);
        WR1_PROG(REG_00B0H, 0x0000983fU);
        WR1_PROG(REG_0000H, 0x00430031U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001032U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[13]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[17]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[21]);

        r_rsip_func100(bswap_32big(0x82b4e3d2U), bswap_32big(0x431fed20U), bswap_32big(0xca97a048U),
                       bswap_32big(0xceb1aca5U));
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
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[25]);

        r_rsip_func100(bswap_32big(0x6be56124U), bswap_32big(0x3df9e981U), bswap_32big(0xf15277e2U),
                       bswap_32big(0x8078cf72U));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_PubKeyIndex[0]);

        r_rsip_func102(bswap_32big(0x7aa29a30U), bswap_32big(0x221882f7U), bswap_32big(0x261af4eeU),
                       bswap_32big(0x8c74ddfcU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
