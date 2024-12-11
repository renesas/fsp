/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pf4 (const uint32_t InData_CurveType[], const uint32_t InData_DomainParam[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f40001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xb6ae2293U), bswap_32big(0x86e4f2d6U), bswap_32big(0xa851efe6U), bswap_32big(0x645a7b99U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xae31ca39U), bswap_32big(0xc63c76b5U), bswap_32big(0xc61af3b8U), bswap_32big(0x1def49adU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x3420a800U);
        WR1_PROG(REG_0094H, 0x00000003U);
        WR1_PROG(REG_0094H, 0x2000b400U);
        WR1_PROG(REG_0094H, 0x00000002U);

        r_rsip_func070(InData_DomainParam);

        WR1_PROG(REG_0094H, 0x000034c0U);

        WR1_PROG(REG_00A0H, 0x20010000U);
        WR1_PROG(REG_00B0H, 0x00002428U);

        r_rsip_func100(bswap_32big(0x29fd5bf8U), bswap_32big(0x4a65fadeU), bswap_32big(0xdeff8051U), bswap_32big(0x5e49ed1cU));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0xd4900c71U), bswap_32big(0x7caaa9a3U), bswap_32big(0x559c973dU), bswap_32big(0xfc196739U));
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
        r_rsip_func100(bswap_32big(0xe2ed9ccaU), bswap_32big(0xdf40935bU), bswap_32big(0xffdaf060U), bswap_32big(0xf38517f4U));
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

        WR1_PROG(REG_00B0H, 0x0000140fU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x000f000aU);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000143cU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

        WR1_PROG(REG_00B0H, 0x00001419U);
        WR1_PROG(REG_0000H, 0x00c00021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_0094H, 0x00000863U);
        WR1_PROG(REG_0094H, 0x000008a5U);

        for (iLoop = 0U; iLoop < 64U; iLoop++)
        {
            WR1_PROG(REG_00B4H, 0x00140027U);
            WR1_PROG(REG_00B8H, 0x001e0000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B0H, 0x0000081aU);
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
            WR1_PROG(REG_0040H, 0x00260000U);

            r_rsip_func100(bswap_32big(0xeebe9696U), bswap_32big(0x4b6e0589U), bswap_32big(0x59e8307cU), bswap_32big(0x6e4d118fU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_00B4H, 0x0019001eU);
                WR1_PROG(REG_00B8H, 0x004b0000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                r_rsip_func101(bswap_32big(0xa6ea46daU), bswap_32big(0x61e83ea4U), bswap_32big(0xea741037U), bswap_32big(0x45a70389U));
            }
            else
            {
                WR1_PROG(REG_00B4H, 0x0019001eU);
                WR1_PROG(REG_00B8H, 0x00270000U);

                WR1_PROG(REG_00A4H, 0x04040009U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                r_rsip_func101(bswap_32big(0x7b6bc746U), bswap_32big(0x7e87a082U), bswap_32big(0xd2f5c9d8U), bswap_32big(0x6f850510U));
            }

            WR1_PROG(REG_00B4H, 0x003c002bU);
            WR1_PROG(REG_00B8H, 0x001e0000U);

            WR1_PROG(REG_00A4H, 0x04040007U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x003c0027U);
            WR1_PROG(REG_00B8H, 0x00230000U);

            WR1_PROG(REG_00A4H, 0x04040007U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B0H, 0x0000081fU);
            WR1_PROG(REG_009CH, 0x80020040U);
            WR1_PROG(REG_0000H, 0x03430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B4H, 0x0019001eU);
            WR1_PROG(REG_00B8H, 0x002b0000U);

            WR1_PROG(REG_00A4H, 0x04040009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x001a0023U);
            WR1_PROG(REG_00B8H, 0x00270000U);

            WR1_PROG(REG_00A4H, 0x04040009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0094H, 0x00002ca0U);

            r_rsip_func101(bswap_32big(0xb086e8aaU), bswap_32big(0x43a602f9U), bswap_32big(0xdee976d9U), bswap_32big(0x10496dc3U));
        }

        WR1_PROG(REG_0094H, 0x380088a0U);
        WR1_PROG(REG_0094H, 0x00000040U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0040H, 0x00402000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_00B4H, 0x00140027U);
        WR1_PROG(REG_00B8H, 0x001e0000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B0H, 0x0000081aU);
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
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0x568d9e6fU), bswap_32big(0xa70f5dfbU), bswap_32big(0xa5bd140eU), bswap_32big(0x60135ba1U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_00B4H, 0x0019001eU);
            WR1_PROG(REG_00B8H, 0x004b0000U);

            WR1_PROG(REG_00A4H, 0x04040009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            r_rsip_func101(bswap_32big(0xb4cd05b2U), bswap_32big(0xb783f294U), bswap_32big(0xcf63caceU), bswap_32big(0x814296e1U));
        }
        else
        {
            WR1_PROG(REG_00B4H, 0x0019001eU);
            WR1_PROG(REG_00B8H, 0x00270000U);

            WR1_PROG(REG_00A4H, 0x04040009U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            r_rsip_func101(bswap_32big(0xcfa4faf6U), bswap_32big(0x17a2d429U), bswap_32big(0x1870b2baU), bswap_32big(0xbbf579b8U));
        }

        WR1_PROG(REG_00B4H, 0x000f0027U);
        WR1_PROG(REG_00B8H, 0x00320000U);

        WR1_PROG(REG_00A4H, 0x04040009U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00003406U);

        r_rsip_func071(InData_DomainParam);

        WR1_PROG(REG_0094H, 0x00003420U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000f4U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x3ecfea73U), bswap_32big(0x10b3f4abU), bswap_32big(0x9617635cU), bswap_32big(0x5a496b0aU));
        r_rsip_func088();

        r_rsip_func100(bswap_32big(0x9390374bU), bswap_32big(0x221c6c46U), bswap_32big(0x56b63edfU), bswap_32big(0xeeb30162U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xe19e9e51U), bswap_32big(0x1fc1bf72U), bswap_32big(0x2e4cf792U), bswap_32big(0xbe35a5c4U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xb3e1a734U), bswap_32big(0xb4709052U), bswap_32big(0x40d13717U), bswap_32big(0x86683270U));
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
            WR1_PROG(REG_002CH, bswap_32big(0x0000f401U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x55e70de0U), bswap_32big(0x4f68b9f4U), bswap_32big(0xf4fbaf85U), bswap_32big(0x7a3c9d07U));
            r_rsip_func043();

            r_rsip_func074();

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000f401U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xb7ed0041U), bswap_32big(0xef40ac29U), bswap_32big(0x05dd7d18U), bswap_32big(0xc6f791a0U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x366eec1aU), bswap_32big(0xc4401494U), bswap_32big(0x383425f0U), bswap_32big(0xe577b13bU));
            WR1_PROG(REG_00B0H, 0x00001832U);

            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe7009d07U);
            WR1_PROG(REG_0000H, 0x00430021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[5]);

            r_rsip_func100(bswap_32big(0xd2dcd677U), bswap_32big(0x7c09e1e1U), bswap_32big(0xdeab4a5dU), bswap_32big(0xee062981U));
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
            RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[9]);

            r_rsip_func100(bswap_32big(0xb6958c79U), bswap_32big(0x8166bee4U), bswap_32big(0x1c29ada2U), bswap_32big(0xc5e2eeb8U));
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_PrivKeyIndex[0]);

            r_rsip_func100(bswap_32big(0x658990c0U), bswap_32big(0x960a4694U), bswap_32big(0xbd4b07f1U), bswap_32big(0xd2c591f2U));
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
            WR1_PROG(REG_002CH, bswap_32big(0x0000f402U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x6b857fe7U), bswap_32big(0xeb18d7a9U), bswap_32big(0xddbd52d0U), bswap_32big(0x00ffd55aU));
            r_rsip_func043();

            r_rsip_func075();

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000f402U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x643e352eU), bswap_32big(0x0dd0790aU), bswap_32big(0xe805a151U), bswap_32big(0x1d7c3fe9U));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            r_rsip_func100(bswap_32big(0xb9ba30f2U), bswap_32big(0xd3999c4eU), bswap_32big(0xb9e6b152U), bswap_32big(0x0e80bef4U));
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe8008107U);
            WR1_PROG(REG_00B0H, 0x00001828U);
            WR1_PROG(REG_0000H, 0x00430021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[5]);

            r_rsip_func100(bswap_32big(0xf09f7f27U), bswap_32big(0x77eb6bedU), bswap_32big(0x6ee4a585U), bswap_32big(0x4e04a8ccU));
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe8008107U);
            WR1_PROG(REG_00B0H, 0x0000182dU);
            WR1_PROG(REG_0000H, 0x00430021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[9]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[13]);

            r_rsip_func100(bswap_32big(0x0c51302eU), bswap_32big(0x28fa170bU), bswap_32big(0x0b760704U), bswap_32big(0x28748307U));
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
            RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[17]);

            r_rsip_func100(bswap_32big(0x207e0522U), bswap_32big(0x4741c96fU), bswap_32big(0x839b6797U), bswap_32big(0x417ac9a8U));
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_PubKeyIndex[0]);

            r_rsip_func102(bswap_32big(0xb24e3550U), bswap_32big(0x8ce59a45U), bswap_32big(0x9e461e39U), bswap_32big(0x2ffc1ac4U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
