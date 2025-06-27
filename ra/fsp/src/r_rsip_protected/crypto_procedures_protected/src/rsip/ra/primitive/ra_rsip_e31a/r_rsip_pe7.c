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

rsip_ret_t r_rsip_pe7 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e70001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010040U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x800200a0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_OutDataType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a840U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b440U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0094H, 0x3000a8c0U);
    WR1_PROG(REG_0094H, 0x00000008U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);
    WR1_PROG(REG_0094H, 0x00000080U);

    r_rsip_func100(bswap_32big(0x0474295aU),
                   bswap_32big(0xec4d427aU),
                   bswap_32big(0x5950db3cU),
                   bswap_32big(0x5f3a191cU));
    WR1_PROG(REG_0094H, 0x00007c02U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x08000000U);
        WR1_PROG(REG_0094H, 0x34202805U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func101(bswap_32big(0xaac385eaU), bswap_32big(0x2b7c8dedU), bswap_32big(0xdd6350d3U),
                       bswap_32big(0x81045fe8U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x05555555U);
        WR1_PROG(REG_0094H, 0x34202805U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func101(bswap_32big(0xdf2f823cU), bswap_32big(0x332f7eb8U), bswap_32big(0x66a14b64U),
                       bswap_32big(0x420ed312U));
    }

    WR1_PROG(REG_0094H, 0x38000ca5U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x34202806U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xdeeba2b5U),
                   bswap_32big(0x42c6bfebU),
                   bswap_32big(0x944d99c1U),
                   bswap_32big(0xc8dfcac0U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5628c841U), bswap_32big(0xadb14031U), bswap_32big(0x3213f623U),
                       bswap_32big(0x349d5c4aU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x8aa45613U), bswap_32big(0x013c97fdU), bswap_32big(0x4ea5c57eU),
                       bswap_32big(0x25ce3a44U));
        WR1_PROG(REG_0094H, 0x00007c06U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x7408bd90U), bswap_32big(0x21675856U), bswap_32big(0xd348243cU),
                           bswap_32big(0x2fde3808U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000001fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xd74b8144U), bswap_32big(0xab04ef68U), bswap_32big(0x20533d15U),
                           bswap_32big(0xf5f18498U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x3ecaa5d0U), bswap_32big(0x9d5ff684U), bswap_32big(0x75638051U),
                           bswap_32big(0x4fafe499U));
        }

        WR1_PROG(REG_0094H, 0x0000b4e0U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_0094H, 0x00003cc7U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_OutDataLocation[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x30003040U);
        WR1_PROG(REG_0094H, 0x00070020U);

        WR1_PROG(REG_0094H, 0x00003405U);
        WR1_PROG(REG_0094H, 0x00056c00U);
        WR1_PROG(REG_0094H, 0x00003000U);

        WR1_PROG(REG_0094H, 0x00000060U);

        WR1_PROG(REG_0094H, 0x00003405U);
        WR1_PROG(REG_0094H, 0x00046c00U);
        WR1_PROG(REG_0094H, 0x00003465U);
        WR1_PROG(REG_0094H, 0x00056c63U);
        WR1_PROG(REG_0094H, 0x00002403U);
        WR1_PROG(REG_0094H, 0x00003000U);

        WR1_PROG(REG_0094H, 0x00000080U);

        WR1_PROG(REG_0094H, 0x00002481U);

        WR1_PROG(REG_0094H, 0x34202804U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0094H, 0x34202824U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x0edf7dcaU), bswap_32big(0xc2d6ff49U), bswap_32big(0x201ff6e0U),
                       bswap_32big(0xca76f0adU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x000addc1U), bswap_32big(0x6d07e28dU), bswap_32big(0x0f767f12U),
                           bswap_32big(0x10fd5f45U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x000008c6U);

            WR1_PROG(REG_0094H, 0x00000800U);

            WR1_PROG(REG_0094H, 0x00000863U);

            r_rsip_func100(bswap_32big(0xda30d11bU), bswap_32big(0xde0741deU), bswap_32big(0x7532ead9U),
                           bswap_32big(0xade36a9fU));
            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003ca7U);

            r_rsip_func100(bswap_32big(0x42cab37aU), bswap_32big(0xf9ddcc22U), bswap_32big(0xa1967acbU),
                           bswap_32big(0xd9249c8eU));
            WR1_PROG(REG_0094H, 0x00007c02U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_0094H, 0x00000842U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0094H, 0x34202880U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    WR1_PROG(REG_0094H, 0x0000a400U);
                    WR1_PROG(REG_0094H, 0x0000001fU);

                    WR1_PROG(REG_0094H, 0x34202801U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x7901613bU),
                                   bswap_32big(0x46f6671fU),
                                   bswap_32big(0x2c20e358U),
                                   bswap_32big(0xdeb516eeU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func101(bswap_32big(0xdc033de3U),
                                       bswap_32big(0x77720302U),
                                       bswap_32big(0xb6ffa942U),
                                       bswap_32big(0x6bff7da8U));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x00000018U);
                        WR1_PROG(REG_0094H, 0x00003c47U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);
                        WR1_PROG(REG_0094H, 0x00003cc7U);

                        WR1_PROG(REG_0014H, 0x000000c7U);
                        WR1_PROG(REG_009CH, 0x800100c0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, InData_KDFInfo[iLoop * 13]);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        WR1_PROG(REG_0014H, 0x000000a7U);
                        WR1_PROG(REG_009CH, 0x800100e0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0xa65bbc5dU),
                                       bswap_32big(0x51a25989U),
                                       bswap_32big(0x4bc01867U),
                                       bswap_32big(0xd88ceb03U));
                        r_rsip_func043();

                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x01799093U);

                        WR1_PROG(REG_0014H, 0x000000a7U);
                        WR1_PROG(REG_009CH, 0x800100e0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0xffd6fee4U),
                                       bswap_32big(0xce0892acU),
                                       bswap_32big(0x8340727eU),
                                       bswap_32big(0x7e19d744U));
                        r_rsip_func044();

                        WR1_PROG(REG_0094H, 0x38000c63U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);

                        r_rsip_func100(bswap_32big(0x05c0dabfU),
                                       bswap_32big(0x9765ab43U),
                                       bswap_32big(0xe0b88d3fU),
                                       bswap_32big(0xa5feef7eU));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_00B0H, 0x00001404U);

                            r_rsip_func101(bswap_32big(0x512736e4U),
                                           bswap_32big(0x0791524eU),
                                           bswap_32big(0x65b319c8U),
                                           bswap_32big(0xf1452f5eU));
                        }
                        else
                        {
                            WR1_PROG(REG_00B0H, 0x00001408U);

                            r_rsip_func101(bswap_32big(0x79198f48U),
                                           bswap_32big(0x69a6d313U),
                                           bswap_32big(0x9e34e90dU),
                                           bswap_32big(0x428f672dU));
                        }

                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x08000044U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x08000054U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_0014H, 0x000007c1U);
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xf7008d07U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 1]);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 5]);

                        WR1_PROG(REG_0000H, 0x00c10021U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x00002c60U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x00000018U);
                        WR1_PROG(REG_0094H, 0x00003847U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);
                        WR1_PROG(REG_0094H, 0x000038c7U);

                        WR1_PROG(REG_0014H, 0x000003c1U);
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0x07008d05U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 13 + 9]);

                        WR1_PROG(REG_00D0H, 0x9c100005U);
                        WR1_PROG(REG_0000H, 0x00410011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        r_rsip_func100(bswap_32big(0x302b6072U),
                                       bswap_32big(0x59b126d2U),
                                       bswap_32big(0x5f4eec0cU),
                                       bswap_32big(0x6485adb0U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x0000d040U);
                            r_rsip_func101(bswap_32big(0xa0e0df44U),
                                           bswap_32big(0xd46006f6U),
                                           bswap_32big(0x7220482fU),
                                           bswap_32big(0xbb250b3fU));
                        }
                        else
                        {
                            r_rsip_func101(bswap_32big(0x4bd2ae50U),
                                           bswap_32big(0x0e32c0ccU),
                                           bswap_32big(0x9425544cU),
                                           bswap_32big(0xda0a9d40U));
                        }
                    }

                    WR1_PROG(REG_0094H, 0x00002c00U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0xf0fca2fbU),
                                   bswap_32big(0xb1ffbbddU),
                                   bswap_32big(0x72e36b6bU),
                                   bswap_32big(0xefbca5d3U));
                }

                WR1_PROG(REG_0094H, 0x00000884U);

                r_rsip_func101(bswap_32big(0x14fe01e9U),
                               bswap_32big(0x87739025U),
                               bswap_32big(0xfd59349aU),
                               bswap_32big(0x36a959b9U));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_0094H, 0x00000842U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0094H, 0x34202880U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    WR1_PROG(REG_0094H, 0x0000a400U);
                    WR1_PROG(REG_0094H, 0x0000002fU);

                    WR1_PROG(REG_0094H, 0x34202801U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x85b10afeU),
                                   bswap_32big(0x5b785d28U),
                                   bswap_32big(0x8d84ad77U),
                                   bswap_32big(0x1b1224beU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func101(bswap_32big(0xb1075054U),
                                       bswap_32big(0xb97152a1U),
                                       bswap_32big(0xd86735acU),
                                       bswap_32big(0xb949d90aU));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x00000018U);
                        WR1_PROG(REG_0094H, 0x00003c47U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);
                        WR1_PROG(REG_0094H, 0x00003cc7U);

                        WR1_PROG(REG_0014H, 0x000000c7U);
                        WR1_PROG(REG_009CH, 0x800100c0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, InData_KDFInfo[iLoop * 17]);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        WR1_PROG(REG_0014H, 0x000000a7U);
                        WR1_PROG(REG_009CH, 0x800100e0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0x495e5645U),
                                       bswap_32big(0xdd134c47U),
                                       bswap_32big(0x3e18c511U),
                                       bswap_32big(0xab3d09a6U));
                        r_rsip_func043();

                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x01799093U);

                        WR1_PROG(REG_0014H, 0x000000a7U);
                        WR1_PROG(REG_009CH, 0x800100e0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e701U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0xffd6fee4U),
                                       bswap_32big(0xce0892acU),
                                       bswap_32big(0x8340727eU),
                                       bswap_32big(0x7e19d744U));
                        r_rsip_func044();

                        WR1_PROG(REG_0094H, 0x38000c63U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);

                        r_rsip_func100(bswap_32big(0x05c0dabfU),
                                       bswap_32big(0x9765ab43U),
                                       bswap_32big(0xe0b88d3fU),
                                       bswap_32big(0xa5feef7eU));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_00B0H, 0x00009406U);

                            r_rsip_func101(bswap_32big(0x082ba310U),
                                           bswap_32big(0x0d7dd27fU),
                                           bswap_32big(0x5e6285e3U),
                                           bswap_32big(0x76dd00afU));
                        }
                        else
                        {
                            WR1_PROG(REG_00B0H, 0x0000940cU);

                            r_rsip_func101(bswap_32big(0x10a9ec96U),
                                           bswap_32big(0xaf8c9778U),
                                           bswap_32big(0xbcfa6affU),
                                           bswap_32big(0x643e6fd6U));
                        }

                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x08000044U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_0014H, 0x000000a1U);
                        WR1_PROG(REG_00D0H, 0x08000054U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                        WR1_PROG(REG_0014H, 0x00000bc1U);
                        WR1_PROG(REG_00D4H, 0x40000200U);
                        WR1_PROG(REG_00D0H, 0xf7008d07U);

                        for (jLoop = 0U; jLoop < 12U; )
                        {
                            WAIT_STS(REG_0014H, 31, 1);
                            WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 17 + jLoop + 1]);
                            jLoop = jLoop + 4U;
                        }

                        WR1_PROG(REG_0000H, 0x00c10031U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x00002c60U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x00000018U);
                        WR1_PROG(REG_0094H, 0x00003847U);

                        WR1_PROG(REG_0094H, 0x0000b4e0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);
                        WR1_PROG(REG_0094H, 0x000038c7U);

                        WR1_PROG(REG_0014H, 0x000003c1U);
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0x07008d05U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR4_ADDR(REG_002CH, &InData_KDFInfo[iLoop * 17 + jLoop + 1]);

                        WR1_PROG(REG_00D0H, 0x9c100005U);
                        WR1_PROG(REG_0000H, 0x00410011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        r_rsip_func100(bswap_32big(0x7cb97cd2U),
                                       bswap_32big(0x06ee27fbU),
                                       bswap_32big(0x5da744ebU),
                                       bswap_32big(0x963d44a9U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x0000d040U);
                            r_rsip_func101(bswap_32big(0xa1936fe5U),
                                           bswap_32big(0x41e0d8a4U),
                                           bswap_32big(0x4964b82fU),
                                           bswap_32big(0x5d5f12fcU));
                        }
                        else
                        {
                            r_rsip_func101(bswap_32big(0x9279573aU),
                                           bswap_32big(0x8a11b32aU),
                                           bswap_32big(0x8b2fea91U),
                                           bswap_32big(0x4c15ec2bU));
                        }
                    }

                    WR1_PROG(REG_0094H, 0x00002c00U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0x1f8f892aU),
                                   bswap_32big(0x1dbe34fdU),
                                   bswap_32big(0x73b741aaU),
                                   bswap_32big(0x4ac9503dU));
                }

                WR1_PROG(REG_0094H, 0x0000b480U);
                WR1_PROG(REG_0094H, 0x00000001U);

                r_rsip_func101(bswap_32big(0x901a631eU),
                               bswap_32big(0x24be041aU),
                               bswap_32big(0x9559b0d6U),
                               bswap_32big(0x15ed2d29U));
            }

            WR1_PROG(REG_0094H, 0x0000b4e0U);
            WR1_PROG(REG_0094H, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003807U);

            WR1_PROG(REG_0094H, 0x380008c0U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);
            WR1_PROG(REG_0040H, 0x00402000U);

            WR1_PROG(REG_0094H, 0x38000c42U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);
            r_rsip_func100(bswap_32big(0x23b50f0cU), bswap_32big(0x7c6dc4fbU), bswap_32big(0xfe79682aU),
                           bswap_32big(0x49751e65U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x621e433dU),
                               bswap_32big(0x1b7cc490U),
                               bswap_32big(0x65108f8dU),
                               bswap_32big(0xb03da3d6U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xda839fa2U),
                               bswap_32big(0x167bd543U),
                               bswap_32big(0xa4255670U),
                               bswap_32big(0xf0e5ba8eU));
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
                WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x890babbfU),
                               bswap_32big(0x93952f57U),
                               bswap_32big(0x2ca3ec46U),
                               bswap_32big(0xaf831bccU));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_0094H, 0x00003847U);

                r_rsip_func100(bswap_32big(0x0978d7b4U),
                               bswap_32big(0x7b2c8efdU),
                               bswap_32big(0xa353828dU),
                               bswap_32big(0x7f46f21fU));
                WR1_PROG(REG_0094H, 0x00007c02U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000005U);

                    r_rsip_func101(bswap_32big(0x9df155bfU),
                                   bswap_32big(0xd310531fU),
                                   bswap_32big(0xbdf5c6eaU),
                                   bswap_32big(0xfc78ce2fU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000007U);

                    r_rsip_func101(bswap_32big(0xb1755c7eU),
                                   bswap_32big(0x670ed307U),
                                   bswap_32big(0x57e5c14bU),
                                   bswap_32big(0x2a323150U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0199e556U);

                    r_rsip_func101(bswap_32big(0x7c59611dU),
                                   bswap_32big(0x25d153ebU),
                                   bswap_32big(0x09403c7bU),
                                   bswap_32big(0xc30cdf5fU));
                }

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xa71914ffU),
                               bswap_32big(0x7ae6dbcfU),
                               bswap_32big(0x6aaeccafU),
                               bswap_32big(0xb3814eecU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x1d9a4df3U),
                               bswap_32big(0xfb79d835U),
                               bswap_32big(0x337862ceU),
                               bswap_32big(0x28e38d7aU));
                WR1_PROG(REG_0094H, 0x00007c04U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_0094H, 0x00008c20U);
                    WR1_PROG(REG_0094H, 0x0000001fU);

                    WR1_PROG(REG_0094H, 0x38008860U);
                    WR1_PROG(REG_0094H, 0x00000001U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0xd8818d66U),
                                   bswap_32big(0x120c0e27U),
                                   bswap_32big(0xb7549193U),
                                   bswap_32big(0x8c77a046U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000020U);
                        WR1_PROG(REG_00B0H, 0x00001804U);

                        r_rsip_func101(bswap_32big(0x02aba32dU),
                                       bswap_32big(0x167f5297U),
                                       bswap_32big(0x95277f3eU),
                                       bswap_32big(0x2311f212U));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000040U);
                        WR1_PROG(REG_00B0H, 0x00003808U);

                        r_rsip_func101(bswap_32big(0x3a1e5f69U),
                                       bswap_32big(0x73aa0bafU),
                                       bswap_32big(0x40cd2512U),
                                       bswap_32big(0xcf4b500dU));
                    }

                    r_rsip_func101(bswap_32big(0x55c06984U),
                                   bswap_32big(0x6a256bedU),
                                   bswap_32big(0x8ab9fc87U),
                                   bswap_32big(0x2962e0fbU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x00008c20U);
                    WR1_PROG(REG_0094H, 0x0000002fU);

                    WR1_PROG(REG_0094H, 0x38008860U);
                    WR1_PROG(REG_0094H, 0x00000001U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x196f0311U),
                                   bswap_32big(0xd10b18ddU),
                                   bswap_32big(0x0c3e5763U),
                                   bswap_32big(0x9aed8367U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000030U);
                        WR1_PROG(REG_00B0H, 0x00009806U);

                        r_rsip_func101(bswap_32big(0x22e51f10U),
                                       bswap_32big(0x52a34ee7U),
                                       bswap_32big(0x1b82ca1cU),
                                       bswap_32big(0xe3dfff2bU));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000060U);
                        WR1_PROG(REG_00B0H, 0x0000b80cU);

                        r_rsip_func101(bswap_32big(0x204a287fU),
                                       bswap_32big(0x66b63ed8U),
                                       bswap_32big(0x98350987U),
                                       bswap_32big(0x809e973aU));
                    }

                    r_rsip_func101(bswap_32big(0x629dbffcU),
                                   bswap_32big(0xc2d1c66bU),
                                   bswap_32big(0x34354ba8U),
                                   bswap_32big(0x5a7b9934U));
                }

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x000008a5U);

                r_rsip_func100(bswap_32big(0xde192aa2U),
                               bswap_32big(0x1a578cedU),
                               bswap_32big(0xf6f31a43U),
                               bswap_32big(0xebf90661U));
                WR1_PROG(REG_009CH, 0x81010080U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0094H, 0x342028a1U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    WR1_PROG(REG_0094H, 0x3420a8e0U);
                    WR1_PROG(REG_0094H, 0x00000020U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A70000U);

                    r_rsip_func100(bswap_32big(0x18c92e26U),
                                   bswap_32big(0x4ff23a1dU),
                                   bswap_32big(0x2ff3534cU),
                                   bswap_32big(0xf5df1208U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0000H, 0x1000000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x10030005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        r_rsip_func101(bswap_32big(0xd7200742U),
                                       bswap_32big(0x05a9940bU),
                                       bswap_32big(0x46623190U),
                                       bswap_32big(0x057d8ba1U));
                    }
                    else
                    {
                        WR1_PROG(REG_009CH, 0x800100c0U);
                        WR1_PROG(REG_0000H, 0x1340000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x13430005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x02003cc7U);

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0xe1a51d55U),
                                       bswap_32big(0xc6a8e8faU),
                                       bswap_32big(0xc1fa1a68U),
                                       bswap_32big(0xc7cf74e9U));
                    }

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x4d2fdcf8U),
                                   bswap_32big(0xd69d46acU),
                                   bswap_32big(0x29fa0fd8U),
                                   bswap_32big(0x393d1502U));
                }

                WR1_PROG(REG_0094H, 0x380008a4U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x3420a840U);
                WR1_PROG(REG_0094H, 0x00000002U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                r_rsip_func100(bswap_32big(0x7e0872feU),
                               bswap_32big(0xa5dbc57cU),
                               bswap_32big(0xef247529U),
                               bswap_32big(0x62d1432dU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x38000c42U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x2d8d11e9U),
                                   bswap_32big(0x702ab42bU),
                                   bswap_32big(0xb43442e9U),
                                   bswap_32big(0x70669cfcU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0xf29c126fU),
                                       bswap_32big(0x5d04f886U),
                                       bswap_32big(0x91ff6c39U),
                                       bswap_32big(0xbdada3a3U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        WR1_PROG(REG_009CH, 0x81840007U);
                        WR1_PROG(REG_0000H, 0x00490011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0x4e940cefU),
                                       bswap_32big(0x96f0feaeU),
                                       bswap_32big(0x1c46cecfU),
                                       bswap_32big(0x847c9dc6U));
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
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func101(bswap_32big(0x0d172b63U),
                                       bswap_32big(0x475beccdU),
                                       bswap_32big(0x46234f64U),
                                       bswap_32big(0x563d5ccbU));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x34b297adU),
                                       bswap_32big(0xb1372cedU),
                                       bswap_32big(0x80ccd06dU),
                                       bswap_32big(0xc46acb58U));
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xe7009d07U);

                        WR1_PROG(REG_009CH, 0x81880007U);
                        WR1_PROG(REG_0000H, 0x00490021U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001022U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x9b861d44U),
                                       bswap_32big(0x1457a0deU),
                                       bswap_32big(0x4407d684U),
                                       bswap_32big(0xe0e71061U));
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
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

                        r_rsip_func101(bswap_32big(0x1570f702U),
                                       bswap_32big(0xca618025U),
                                       bswap_32big(0x9e4171f3U),
                                       bswap_32big(0x3724d523U));
                    }

                    r_rsip_func100(bswap_32big(0x65a86bd8U),
                                   bswap_32big(0xb6201e6cU),
                                   bswap_32big(0x4710403cU),
                                   bswap_32big(0x78fe3362U));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x9ed7c3ddU),
                                   bswap_32big(0xdac883ddU),
                                   bswap_32big(0xbca9a5a5U),
                                   bswap_32big(0xac52adeeU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x2337e6c9U),
                                   bswap_32big(0xdb7d2151U),
                                   bswap_32big(0x1d368f8eU),
                                   bswap_32big(0x390aaf0dU));
                    WR1_PROG(REG_00D4H, 0x40000000U);
                    WR1_PROG(REG_00D0H, 0xe7009d05U);

                    WR1_PROG(REG_009CH, 0x81840007U);
                    WR1_PROG(REG_0000H, 0x00490011U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0008H, 0x00001012U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_EncIV[1]);

                    r_rsip_func100(bswap_32big(0x9b75b4e5U),
                                   bswap_32big(0x7c06a881U),
                                   bswap_32big(0x79cd0cc1U),
                                   bswap_32big(0x16ce6276U));
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
                    RD4_ADDR(REG_002CH, &OutData_EncIV[5]);

                    r_rsip_func100(bswap_32big(0x679ff7a2U),
                                   bswap_32big(0x4e5e20ffU),
                                   bswap_32big(0x1d90ea20U),
                                   bswap_32big(0x0280a6ebU));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_EncIV[0]);

                    r_rsip_func102(bswap_32big(0x4de69ef6U),
                                   bswap_32big(0x570802b9U),
                                   bswap_32big(0x835d237dU),
                                   bswap_32big(0xac4ef033U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
