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

rsip_ret_t r_rsip_peff (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[],
                        uint32_t       OutData_KDFInfo[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000002c7U);
    WR1_PROG(REG_009CH, 0x80030060U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg1Length[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg2Length[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38008c60U);
    WR1_PROG(REG_0094H, 0xfffffffeU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A70000U);

    r_rsip_func100(bswap_32big(0x77c79546U),
                   bswap_32big(0x5b883fa9U),
                   bswap_32big(0x68eec830U),
                   bswap_32big(0x37f823b6U));
    WR1_PROG(REG_0094H, 0x00007c00U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0094H, 0x38008c80U);
        WR1_PROG(REG_0094H, 0xfffffff7U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func101(bswap_32big(0x5a83a99dU), bswap_32big(0x9a3e5d68U), bswap_32big(0x84ecd58fU),
                       bswap_32big(0x5450d810U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0094H, 0x38008c80U);
        WR1_PROG(REG_0094H, 0xfffffff3U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func101(bswap_32big(0x22846764U), bswap_32big(0x34e6ffe5U), bswap_32big(0x60532fedU),
                       bswap_32big(0x8d7b27d1U));
    }

    r_rsip_func100(bswap_32big(0xa87977abU),
                   bswap_32big(0xd113bd2bU),
                   bswap_32big(0x143acc5aU),
                   bswap_32big(0xb1cf0984U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x10c20255U), bswap_32big(0x6c2416b0U), bswap_32big(0x5ac23861U),
                       bswap_32big(0x6b3af435U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00000821U);

        WR1_PROG(REG_0094H, 0x00003405U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x2f59c109U), bswap_32big(0x6ce5c1a7U), bswap_32big(0x6ee8ac2fU),
                       bswap_32big(0xf366437dU));
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
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x3f81902fU), bswap_32big(0xb31ee327U), bswap_32big(0xc4fd9a53U),
                           bswap_32big(0xd04e1439U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x6b38a144U), bswap_32big(0x2e901d7dU), bswap_32big(0xf21fb199U),
                           bswap_32big(0x1e68b467U));
            r_rsip_func044();

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000010U);
            WR1_PROG(REG_0094H, 0x000038a7U);

            r_rsip_func100(bswap_32big(0x596f4dd1U), bswap_32big(0xec1b1601U), bswap_32big(0xc95ec90fU),
                           bswap_32big(0x39c977d6U));

            WR1_PROG(REG_0094H, 0x00007c05U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_0014H, 0x000007c1U);
                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xf7009d07U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1]);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[5]);

                WR1_PROG(REG_00B0H, 0x00001404U);
                WR1_PROG(REG_0000H, 0x00c10021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0x07008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[9]);

                r_rsip_func101(bswap_32big(0x044f1ba4U),
                               bswap_32big(0x200b8722U),
                               bswap_32big(0xbcfcfa9eU),
                               bswap_32big(0x2ce55e06U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_0014H, 0x00000bc1U);
                WR1_PROG(REG_00D4H, 0x40000200U);
                WR1_PROG(REG_00D0H, 0xf7009d07U);

                for (iLoop = 0U; iLoop < 12U; )
                {
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_00B0H, 0x00009406U);
                WR1_PROG(REG_0000H, 0x00c10031U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D4H, 0x40000000U);
                WR1_PROG(REG_00D0H, 0x07008d05U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_EncMsg[13]);

                r_rsip_func101(bswap_32big(0xf101a855U),
                               bswap_32big(0x22c13b4aU),
                               bswap_32big(0x3c294bb8U),
                               bswap_32big(0xde22d0a2U));
            }

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x3da41bfaU), bswap_32big(0xb1850ae8U), bswap_32big(0x8f51ef46U),
                           bswap_32big(0x028aca79U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0xfe9a5476U),
                               bswap_32big(0xec51c853U),
                               bswap_32big(0xe94af13fU),
                               bswap_32big(0xbe09f81eU));
            }

            r_rsip_func101(bswap_32big(0x13434e96U), bswap_32big(0x4c332e14U), bswap_32big(0x4a0edf69U),
                           bswap_32big(0xf6b48948U));
        }

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0xb5c50105U), bswap_32big(0x7538e135U), bswap_32big(0xf914df10U),
                       bswap_32big(0x06fa2843U));
        WR1_PROG(REG_0040H, 0x00400000U);
        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xa9b92298U), bswap_32big(0xe13a7b4fU), bswap_32big(0xb94aba3fU),
                           bswap_32big(0xfc318108U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WAIT_STS(REG_0118H, 0, 1);

            WR1_PROG(REG_0094H, 0x38000c63U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xed6212c0U), bswap_32big(0xc81b637eU), bswap_32big(0x31302d3cU),
                           bswap_32big(0x85300b2fU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000000c4U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Msg1[0]);

                r_rsip_func101(bswap_32big(0x08b3e0c2U),
                               bswap_32big(0xc2c5d9dfU),
                               bswap_32big(0x5c4e1e9cU),
                               bswap_32big(0x09be19bbU));
            }

            WR1_PROG(REG_0094H, 0x38000c84U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xdb22ef74U), bswap_32big(0x2770f7e1U), bswap_32big(0xad9507baU),
                           bswap_32big(0xa664085cU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0x8948645aU),
                               bswap_32big(0xc6c98229U),
                               bswap_32big(0xddc51630U),
                               bswap_32big(0x451ed6eaU));

                WR1_PROG(REG_0094H, 0x00007c05U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_00B0H, 0x00001804U);
                    WR1_PROG(REG_0000H, 0x01430021U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x669aae5bU),
                                   bswap_32big(0x6a9e9044U),
                                   bswap_32big(0xefd533daU),
                                   bswap_32big(0x4012432aU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_00B0H, 0x00009806U);
                    WR1_PROG(REG_0000H, 0x01430031U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xc125a71eU),
                                   bswap_32big(0x3273ab48U),
                                   bswap_32big(0xfe9ecfc4U),
                                   bswap_32big(0xb2c9462dU));
                }

                r_rsip_func101(bswap_32big(0xea2757aaU),
                               bswap_32big(0xf41a5ff1U),
                               bswap_32big(0x80f5990bU),
                               bswap_32big(0x72c0048aU));
            }

            r_rsip_func100(bswap_32big(0x5e2ee778U), bswap_32big(0xd23bfafaU), bswap_32big(0x4bf0da27U),
                           bswap_32big(0xbcc4e510U));

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100a0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_Msg2Length[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0014H, 0x00020064U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Msg2[iLoop]);
            }

            WR1_PROG(REG_0014H, 0x00000000U);
            WAIT_STS(REG_0118H, 8, 0);
            WR1_PROG(REG_0040H, 0x00001600U);

            WAIT_STS(REG_0118H, 4, 1);

            WR1_PROG(REG_0094H, 0x0000b420U);
            WR1_PROG(REG_0094H, 0x00000010U);
            WR1_PROG(REG_0094H, 0x00003801U);

            r_rsip_func100(bswap_32big(0x9056b78cU), bswap_32big(0x5b894999U), bswap_32big(0x167ea27dU),
                           bswap_32big(0x6a8f1260U));
            r_rsip_func103();

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c200104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_009CH, 0x80010020U);
            WR1_PROG(REG_0000H, 0x03410005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0000H, 0x0001000dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x000034c1U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef03U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xc614872fU), bswap_32big(0xec586c67U), bswap_32big(0xf2feea27U),
                           bswap_32big(0x663b8766U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef03U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x767df497U), bswap_32big(0x5e19a3fbU), bswap_32big(0xb5902602U),
                           bswap_32big(0xc40af809U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0xc7abe6bfU), bswap_32big(0x213145a4U), bswap_32big(0x7fd77d29U),
                           bswap_32big(0xf7d64048U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0094H, 0x00007c00U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
            {
                r_rsip_func100(bswap_32big(0xfe8e6b56U),
                               bswap_32big(0x8b402258U),
                               bswap_32big(0x6559d931U),
                               bswap_32big(0x42447b20U));
                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xe7009d07U);
                WR1_PROG(REG_0000H, 0x00450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0008H, 0x00001022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[5]);

                r_rsip_func100(bswap_32big(0x679e442aU),
                               bswap_32big(0x020a935eU),
                               bswap_32big(0x1dde0c71U),
                               bswap_32big(0xa68a4ce4U));
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
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[9]);

                r_rsip_func101(bswap_32big(0x76186d88U),
                               bswap_32big(0x5e566f71U),
                               bswap_32big(0x71b15075U),
                               bswap_32big(0x49efc593U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
            {
                r_rsip_func100(bswap_32big(0x3a1c26edU),
                               bswap_32big(0x57f3ea69U),
                               bswap_32big(0x512d83a9U),
                               bswap_32big(0xbf8d9fd2U));
                WR1_PROG(REG_00D4H, 0x40000200U);
                WR1_PROG(REG_00D0H, 0xe7009d07U);
                WR1_PROG(REG_0000H, 0x00450031U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0008H, 0x00001032U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[5]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[9]);

                r_rsip_func100(bswap_32big(0xba03fefcU),
                               bswap_32big(0xe6cb627fU),
                               bswap_32big(0x03354c45U),
                               bswap_32big(0xd042aca9U));
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
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[13]);

                r_rsip_func101(bswap_32big(0x4e478e72U),
                               bswap_32big(0xc6eab20aU),
                               bswap_32big(0x260bdd18U),
                               bswap_32big(0xae97ae27U));
            }

            r_rsip_func100(bswap_32big(0xc1d9a534U), bswap_32big(0x1e70ed82U), bswap_32big(0x390a25c8U),
                           bswap_32big(0x64e83dcaU));
            WR1_PROG(REG_009CH, 0x81010020U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_KDFInfo[0]);

            r_rsip_func102(bswap_32big(0x0c115460U), bswap_32big(0x7101a3e6U), bswap_32big(0x84657003U),
                           bswap_32big(0xba37eb5fU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
