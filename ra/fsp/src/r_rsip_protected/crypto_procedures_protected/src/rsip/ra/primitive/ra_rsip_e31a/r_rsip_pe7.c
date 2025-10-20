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
                       uint32_t       OutData_HMACKeyIndex[],
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

    WR1_PROG(REG_0094H, 0x380088c0U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x380088c0U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x380088c0U);
    WR1_PROG(REG_0094H, 0x00000005U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xa8059c1bU),
                   bswap_32big(0x22cc9149U),
                   bswap_32big(0x40f7c5fbU),
                   bswap_32big(0x5f4741ffU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x48aceb5dU), bswap_32big(0x5949d84dU), bswap_32big(0x0bc1256aU),
                       bswap_32big(0xc81595f7U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x9bae2425U), bswap_32big(0x66688472U), bswap_32big(0xd5ddff05U),
                       bswap_32big(0x1ebd9cf7U));
        WR1_PROG(REG_0094H, 0x00007c06U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe60467cbU), bswap_32big(0x019f6760U), bswap_32big(0x733e3920U),
                           bswap_32big(0x5c08c02eU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000001fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x3e3197b4U), bswap_32big(0xc55b9efeU), bswap_32big(0xe040870dU),
                           bswap_32big(0x8d4fabd9U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000000fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x23296402U), bswap_32big(0xe7f679beU), bswap_32big(0xdc1d3ff9U),
                           bswap_32big(0x4754960dU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000001fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x622f80aeU), bswap_32big(0xc61e8c81U), bswap_32big(0x9f3a5683U),
                           bswap_32big(0xae676121U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000007U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x80010080U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000002fU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xafcc7751U), bswap_32big(0x89960253U), bswap_32big(0x1d9ad6feU),
                           bswap_32big(0x624568dbU));
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
                            WR1_PROG(REG_0094H, 0x38008860U);
                            WR1_PROG(REG_0094H, 0x00000001U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x5b1f387aU),
                                           bswap_32big(0xa71f4192U),
                                           bswap_32big(0xb0acbc18U),
                                           bswap_32big(0x094035a8U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_00B0H, 0x00001408U);

                                r_rsip_func101(bswap_32big(0xb6f56a9aU), bswap_32big(0x25ecc003U),
                                               bswap_32big(0xd21f8118U), bswap_32big(0x8aa87da7U));
                            }
                            else
                            {
                                WR1_PROG(REG_00B0H, 0x0000140cU);

                                r_rsip_func101(bswap_32big(0xba6d0b90U), bswap_32big(0x872baf77U),
                                               bswap_32big(0xdf8c90b6U), bswap_32big(0xcf9abff7U));
                            }

                            r_rsip_func101(bswap_32big(0x944859d7U),
                                           bswap_32big(0x75d8848eU),
                                           bswap_32big(0xc410d1b1U),
                                           bswap_32big(0x957a7b61U));
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
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0x8d6678d4U),
                                       bswap_32big(0xb8bc0d6dU),
                                       bswap_32big(0x588beb10U),
                                       bswap_32big(0xca8ef939U));
                        r_rsip_func143();

                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x01799093U);

                        WR1_PROG(REG_0014H, 0x000000a7U);
                        WR1_PROG(REG_009CH, 0x800100e0U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x0000e702U));
                        WR1_PROG(REG_0024H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0xcdaad173U),
                                       bswap_32big(0x759ee735U),
                                       bswap_32big(0xc0a90cdfU),
                                       bswap_32big(0x790cb926U));
                        r_rsip_func044();

                        WR1_PROG(REG_0094H, 0x38000c63U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);

                        r_rsip_func100(bswap_32big(0xbc640838U),
                                       bswap_32big(0x6003df74U),
                                       bswap_32big(0x1ae109d5U),
                                       bswap_32big(0xf3807d59U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_00B0H, 0x00009406U);

                            WR1_PROG(REG_0094H, 0x0000b4e0U);
                            WR1_PROG(REG_0094H, 0x0000001cU);

                            WR1_PROG(REG_0094H, 0x000038a7U);

                            r_rsip_func101(bswap_32big(0x21bab97bU),
                                           bswap_32big(0xaf7e7237U),
                                           bswap_32big(0xc61352c6U),
                                           bswap_32big(0x8ab68484U));
                        }
                        else
                        {
                            WR1_PROG(REG_00B0H, 0x0000940cU);

                            r_rsip_func101(bswap_32big(0x944f1f5aU),
                                           bswap_32big(0x598af3d0U),
                                           bswap_32big(0xd0669889U),
                                           bswap_32big(0xec48763fU));
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
                WR1_PROG(REG_002CH, bswap_32big(0x0000e703U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x651802c3U),
                               bswap_32big(0xc4bccd6fU),
                               bswap_32big(0xe0aac8faU),
                               bswap_32big(0xe28da32aU));
                r_rsip_func143();

                WR1_PROG(REG_0094H, 0x0000b4e0U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_0094H, 0x00003847U);

                r_rsip_func100(bswap_32big(0x40269ffbU),
                               bswap_32big(0xf75e4a92U),
                               bswap_32big(0x0021b47aU),
                               bswap_32big(0x668c740cU));
                WR1_PROG(REG_0094H, 0x00007c02U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000005U);

                    r_rsip_func101(bswap_32big(0x8d475e89U),
                                   bswap_32big(0xb6c2344eU),
                                   bswap_32big(0x6177a8aeU),
                                   bswap_32big(0x8117368aU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000007U);

                    r_rsip_func101(bswap_32big(0x79f3162eU),
                                   bswap_32big(0xd97d6857U),
                                   bswap_32big(0xa3819e72U),
                                   bswap_32big(0xdbf985e3U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0199e556U);

                    r_rsip_func101(bswap_32big(0xbde86ce6U),
                                   bswap_32big(0x60dfcd3cU),
                                   bswap_32big(0x7de476f3U),
                                   bswap_32big(0x150aafabU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x0000001bU);

                    r_rsip_func101(bswap_32big(0x474d1a94U),
                                   bswap_32big(0x2f42092aU),
                                   bswap_32big(0xe1e8d4c0U),
                                   bswap_32big(0x063e20fdU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000007U)
                {
                    WR1_PROG(REG_0094H, 0x0000b4c0U);
                    WR1_PROG(REG_0094H, 0x00000028U);

                    r_rsip_func101(bswap_32big(0x3c25b32aU),
                                   bswap_32big(0x034cf0faU),
                                   bswap_32big(0x4d0f9541U),
                                   bswap_32big(0x01454607U));
                }

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x0000e703U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x69fe8c7dU),
                               bswap_32big(0x71d991edU),
                               bswap_32big(0x06a6fd9eU),
                               bswap_32big(0x203c754dU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0xdfd76ffcU),
                               bswap_32big(0xecfa3251U),
                               bswap_32big(0x533f7c5cU),
                               bswap_32big(0xe8b686d7U));
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

                    r_rsip_func100(bswap_32big(0xdf52b556U),
                                   bswap_32big(0xa1f1537eU),
                                   bswap_32big(0xdd3855dcU),
                                   bswap_32big(0xadce6f47U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000b460U);
                        WR1_PROG(REG_0094H, 0x00000020U);
                        WR1_PROG(REG_00B0H, 0x00001804U);

                        r_rsip_func101(bswap_32big(0xd25974b8U),
                                       bswap_32big(0x4ebdbf5dU),
                                       bswap_32big(0x3ab94f92U),
                                       bswap_32big(0x8d8caa43U));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x38008860U);
                        WR1_PROG(REG_0094H, 0x00000002U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);

                        r_rsip_func100(bswap_32big(0x9d151ddeU),
                                       bswap_32big(0x664ced06U),
                                       bswap_32big(0xe949ef5aU),
                                       bswap_32big(0xb64f70b2U));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x0000b460U);
                            WR1_PROG(REG_0094H, 0x00000040U);
                            WR1_PROG(REG_00B0H, 0x00003808U);

                            r_rsip_func101(bswap_32big(0xa00800bbU),
                                           bswap_32big(0x99de371dU),
                                           bswap_32big(0x80bdb603U),
                                           bswap_32big(0xfdcec22aU));
                        }
                        else
                        {
                            WR1_PROG(REG_0094H, 0x0000b460U);
                            WR1_PROG(REG_0094H, 0x00000060U);
                            WR1_PROG(REG_00B0H, 0x0000b80cU);

                            r_rsip_func101(bswap_32big(0xdac6fbfeU),
                                           bswap_32big(0x68cf71afU),
                                           bswap_32big(0x6b3a359dU),
                                           bswap_32big(0xc522e366U));
                        }

                        r_rsip_func101(bswap_32big(0x5d76770dU),
                                       bswap_32big(0x839298afU),
                                       bswap_32big(0x10563c79U),
                                       bswap_32big(0xa92d3efaU));
                    }

                    r_rsip_func101(bswap_32big(0x55c06984U),
                                   bswap_32big(0x6a256bedU),
                                   bswap_32big(0x8ab9fc87U),
                                   bswap_32big(0x2962e0fbU));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_0094H, 0x000034e5U);
                    WR1_PROG(REG_0094H, 0x00046ce7U);
                    WR1_PROG(REG_0094H, 0x00056ca5U);
                    WR1_PROG(REG_0094H, 0x000024a7U);
                    WR1_PROG(REG_0094H, 0x00002825U);

                    WR1_PROG(REG_0094H, 0x38008860U);
                    WR1_PROG(REG_0094H, 0x00000001U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x0015edd2U),
                                   bswap_32big(0xf1c50f53U),
                                   bswap_32big(0xe1f950daU),
                                   bswap_32big(0x0eef29b8U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0094H, 0x0000b460U);
                        WR1_PROG(REG_0094H, 0x00000030U);
                        WR1_PROG(REG_00B0H, 0x00009806U);

                        r_rsip_func101(bswap_32big(0xbed38b05U),
                                       bswap_32big(0x772e5023U),
                                       bswap_32big(0xa0f98ad1U),
                                       bswap_32big(0xb6439250U));
                    }
                    else
                    {
                        WR1_PROG(REG_0094H, 0x0000b460U);
                        WR1_PROG(REG_0094H, 0x00000060U);
                        WR1_PROG(REG_00B0H, 0x0000b80cU);

                        r_rsip_func101(bswap_32big(0xf10f29adU),
                                       bswap_32big(0xbedd15e2U),
                                       bswap_32big(0x496e07cfU),
                                       bswap_32big(0x4bc57070U));
                    }

                    r_rsip_func101(bswap_32big(0x629dbffcU),
                                   bswap_32big(0xc2d1c66bU),
                                   bswap_32big(0x34354ba8U),
                                   bswap_32big(0x5a7b9934U));
                }

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x000008a5U);

                r_rsip_func100(bswap_32big(0x96985e1dU),
                               bswap_32big(0xb6c1d963U),
                               bswap_32big(0xee4fd143U),
                               bswap_32big(0x6fd83130U));
                WR1_PROG(REG_009CH, 0x81010060U);
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

                    r_rsip_func100(bswap_32big(0x4eece013U),
                                   bswap_32big(0x221c0d95U),
                                   bswap_32big(0xd4b5ac17U),
                                   bswap_32big(0x71d9ed6eU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_0000H, 0x1000000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x10030005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        r_rsip_func101(bswap_32big(0x5c28ea65U),
                                       bswap_32big(0x6803d506U),
                                       bswap_32big(0x7d69c5ecU),
                                       bswap_32big(0x24d5fd49U));
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

                        WR1_PROG(REG_0094H, 0x380088e0U);
                        WR1_PROG(REG_0094H, 0x00000020U);
                        WR1_PROG(REG_0094H, 0x00030020U);
                        WR1_PROG(REG_0094H, 0x000034c5U);
                        WR1_PROG(REG_0094H, 0x00002cc0U);
                        WR1_PROG(REG_0094H, 0x00000080U);

                        r_rsip_func101(bswap_32big(0x602073d1U),
                                       bswap_32big(0x4c7a4cf1U),
                                       bswap_32big(0xfe91955cU),
                                       bswap_32big(0x75054e8eU));
                    }

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x932229d8U),
                                   bswap_32big(0x0546a79dU),
                                   bswap_32big(0xf0b3b09dU),
                                   bswap_32big(0xb1232575U));
                }

                WR1_PROG(REG_0094H, 0x380008a3U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x3420a840U);
                WR1_PROG(REG_0094H, 0x00000002U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                r_rsip_func100(bswap_32big(0x7029a978U),
                               bswap_32big(0xc5cc4e3fU),
                               bswap_32big(0xd069b1a6U),
                               bswap_32big(0x8463eabdU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x38000c42U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);

                    r_rsip_func100(bswap_32big(0xc00b2098U),
                                   bswap_32big(0xdab5fc4aU),
                                   bswap_32big(0xed23ed18U),
                                   bswap_32big(0x02667a4bU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x88940bcaU),
                                       bswap_32big(0x29ba7f32U),
                                       bswap_32big(0xcf4b0fdeU),
                                       bswap_32big(0x70897136U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        WR1_PROG(REG_009CH, 0x81840007U);
                        WR1_PROG(REG_0000H, 0x00490011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0x7f3d54a8U),
                                       bswap_32big(0xbb9102dcU),
                                       bswap_32big(0x8afdb787U),
                                       bswap_32big(0xee8c689bU));
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

                        r_rsip_func101(bswap_32big(0xe7e379aaU),
                                       bswap_32big(0xf8371c27U),
                                       bswap_32big(0x3d10e0c4U),
                                       bswap_32big(0x3c7bba0fU));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x7eecefc1U),
                                       bswap_32big(0xf39c06fcU),
                                       bswap_32big(0x20c0ab88U),
                                       bswap_32big(0x68fa179fU));
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

                        r_rsip_func100(bswap_32big(0x9194d8d5U),
                                       bswap_32big(0x064d23d7U),
                                       bswap_32big(0x53a89920U),
                                       bswap_32big(0x83244cd9U));
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

                        r_rsip_func101(bswap_32big(0xea8afebcU),
                                       bswap_32big(0xc18b70ebU),
                                       bswap_32big(0x95fc4bfeU),
                                       bswap_32big(0x0ab32077U));
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
                    WR1_PROG(REG_0094H, 0x3420a840U);
                    WR1_PROG(REG_0094H, 0x00000006U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A70000U);

                    r_rsip_func100(bswap_32big(0x2043b9f2U),
                                   bswap_32big(0xf5460363U),
                                   bswap_32big(0xf5f84729U),
                                   bswap_32big(0xc4b65b59U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x5bb79af0U),
                                       bswap_32big(0xfba92fa6U),
                                       bswap_32big(0xf3dfa057U),
                                       bswap_32big(0x9580b098U));
                        WR1_PROG(REG_00D4H, 0x40000100U);
                        WR1_PROG(REG_00D0H, 0xe7009d07U);

                        WR1_PROG(REG_009CH, 0x81880007U);
                        WR1_PROG(REG_0000H, 0x00490021U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001022U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[1]);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[5]);

                        WR1_PROG(REG_0094H, 0x38008840U);
                        WR1_PROG(REG_0094H, 0x00000006U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);

                        r_rsip_func100(bswap_32big(0x942cbbb8U),
                                       bswap_32big(0x07079968U),
                                       bswap_32big(0xcf6a3628U),
                                       bswap_32big(0xddeda1deU));
                        WR1_PROG(REG_0040H, 0x00400000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            r_rsip_func100(bswap_32big(0x658f2046U),
                                           bswap_32big(0x07fa69a8U),
                                           bswap_32big(0x124e0f84U),
                                           bswap_32big(0x51a1522bU));
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
                            RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[9]);

                            r_rsip_func101(bswap_32big(0xce2eb1baU),
                                           bswap_32big(0x4a3d151aU),
                                           bswap_32big(0xffea5083U),
                                           bswap_32big(0x9367eb7cU));
                        }
                        else
                        {
                            r_rsip_func100(bswap_32big(0x8e911f12U),
                                           bswap_32big(0x5f73c9d6U),
                                           bswap_32big(0x29d4200cU),
                                           bswap_32big(0x59b053b9U));
                            WR1_PROG(REG_0094H, 0x00007c04U);
                            WR1_PROG(REG_0040H, 0x00600000U);

                            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                            {
                                WR1_PROG(REG_0094H, 0x00003426U);

                                WR1_PROG(REG_0094H, 0x38008860U);
                                WR1_PROG(REG_0094H, 0x00000020U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x93597a1dU), bswap_32big(0x1dd3c05bU),
                                               bswap_32big(0x46c513c1U), bswap_32big(0xe4086a65U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_00B0H, 0x00001804U);

                                    r_rsip_func101(bswap_32big(0x9612281fU), bswap_32big(0x270736d2U),
                                                   bswap_32big(0x0be7ab39U), bswap_32big(0x6270294cU));
                                }
                                else
                                {
                                    WR1_PROG(REG_0094H, 0x38008860U);
                                    WR1_PROG(REG_0094H, 0x00000040U);
                                    WR1_PROG(REG_009CH, 0x00000080U);
                                    WR1_PROG(REG_0040H, 0x00270000U);

                                    r_rsip_func100(bswap_32big(0x8a481fcfU), bswap_32big(0x3bb40884U),
                                                   bswap_32big(0x92d24ff4U), bswap_32big(0xadc0726eU));
                                    WR1_PROG(REG_0040H, 0x00400000U);

                                    if (CHCK_STS(REG_0040H, 22, 1))
                                    {
                                        WR1_PROG(REG_00B0H, 0x00003808U);

                                        r_rsip_func101(bswap_32big(0xcdf40887U), bswap_32big(0x50b3789eU),
                                                       bswap_32big(0x2364c4b7U), bswap_32big(0x3b9e17f3U));
                                    }
                                    else
                                    {
                                        WR1_PROG(REG_00B0H, 0x0000b80cU);

                                        r_rsip_func101(bswap_32big(0x641dacf0U), bswap_32big(0x6bf1fef3U),
                                                       bswap_32big(0x6fa947caU), bswap_32big(0x0d46d5ddU));
                                    }

                                    r_rsip_func101(bswap_32big(0x93d6407fU), bswap_32big(0xf7495c30U),
                                                   bswap_32big(0x3c0cc76dU), bswap_32big(0xa53577d1U));
                                }

                                r_rsip_func101(bswap_32big(0x3f932ad8U), bswap_32big(0x395a9e71U),
                                               bswap_32big(0x9535e686U), bswap_32big(0x2994d2afU));
                            }
                            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                            {
                                WR1_PROG(REG_0094H, 0x00003426U);

                                WR1_PROG(REG_0094H, 0x38008860U);
                                WR1_PROG(REG_0094H, 0x00000030U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0xb007c3a2U), bswap_32big(0x2ae949c2U),
                                               bswap_32big(0x0e4783f5U), bswap_32big(0x8b577cd5U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_00B0H, 0x00009806U);

                                    r_rsip_func101(bswap_32big(0xc46f1a06U), bswap_32big(0x81b9d431U),
                                                   bswap_32big(0x97387ebfU), bswap_32big(0x890ec869U));
                                }
                                else
                                {
                                    WR1_PROG(REG_00B0H, 0x0000b80cU);

                                    r_rsip_func101(bswap_32big(0xe7679254U), bswap_32big(0x438bd26fU),
                                                   bswap_32big(0xe7e3e92bU), bswap_32big(0xacc755c2U));
                                }

                                r_rsip_func101(bswap_32big(0x362f5818U), bswap_32big(0x537087deU),
                                               bswap_32big(0xda3a555aU), bswap_32big(0x49f17071U));
                            }

                            WR1_PROG(REG_0094H, 0x000008a5U);

                            r_rsip_func100(bswap_32big(0xb3b715fcU),
                                           bswap_32big(0x77aaf802U),
                                           bswap_32big(0x10315dc0U),
                                           bswap_32big(0xe3829811U));
                            WR1_PROG(REG_009CH, 0x81010060U);
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
                                WR1_PROG(REG_0094H, 0x00000010U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00A70000U);

                                r_rsip_func100(bswap_32big(0x14b4c4bbU), bswap_32big(0x28ac32e3U),
                                               bswap_32big(0x82106fb9U), bswap_32big(0x4d856ceaU));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_0000H, 0x1000000dU);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);
                                    WR1_PROG(REG_0000H, 0x10030005U);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);

                                    r_rsip_func101(bswap_32big(0xdc2f657bU), bswap_32big(0x969e41e5U),
                                                   bswap_32big(0x9d21d2cdU), bswap_32big(0x60c0dca6U));
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

                                    r_rsip_func101(bswap_32big(0x009ccbb6U), bswap_32big(0xe33ae4d6U),
                                                   bswap_32big(0x47504141U), bswap_32big(0xefc71cb8U));
                                }

                                WR1_PROG(REG_0094H, 0x00002ca0U);

                                r_rsip_func101(bswap_32big(0x96123615U), bswap_32big(0x89bf3aa3U),
                                               bswap_32big(0x1c07ecc6U), bswap_32big(0x8bd19b3aU));
                            }

                            WR1_PROG(REG_0094H, 0x380008a3U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);
                            WR1_PROG(REG_0040H, 0x00402000U);

                            WR1_PROG(REG_0094H, 0x000008e7U);

                            r_rsip_func100(bswap_32big(0xe7136344U),
                                           bswap_32big(0x416972ebU),
                                           bswap_32big(0x6ab1ac80U),
                                           bswap_32big(0x292fe3b0U));
                            WR1_PROG(REG_00D4H, 0x40000000U);
                            WR1_PROG(REG_00D0H, 0xe7008d05U);

                            WR1_PROG(REG_009CH, 0x81840007U);
                            WR1_PROG(REG_0000H, 0x00490011U);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);
                            WR1_PROG(REG_0008H, 0x00001012U);
                            WAIT_STS(REG_0008H, 30, 1);
                            RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[9]);

                            r_rsip_func100(bswap_32big(0x04df8c75U),
                                           bswap_32big(0x94641ddfU),
                                           bswap_32big(0x989f2569U),
                                           bswap_32big(0x475c6e29U));
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
                            RD4_ADDR(REG_002CH, &OutData_HMACKeyIndex[13]);

                            r_rsip_func101(bswap_32big(0x333c14cbU),
                                           bswap_32big(0xb9501fd2U),
                                           bswap_32big(0x8777c968U),
                                           bswap_32big(0xb9640223U));
                        }

                        r_rsip_func100(bswap_32big(0x95b1eb14U),
                                       bswap_32big(0x4234e1baU),
                                       bswap_32big(0x150c58cdU),
                                       bswap_32big(0xaac7bd00U));
                        WR1_PROG(REG_009CH, 0x81010000U);
                        WR1_PROG(REG_0008H, 0x00005006U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD1_ADDR(REG_002CH, &OutData_HMACKeyIndex[0]);

                        r_rsip_func102(bswap_32big(0x7d6b79c7U),
                                       bswap_32big(0x5fa01c3eU),
                                       bswap_32big(0xadb77805U),
                                       bswap_32big(0xf22ea65eU));
                        WR1_PROG(REG_006CH, 0x00000040U);
                        WAIT_STS(REG_0020H, 12, 0);

                        return RSIP_RET_PASS;
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x7fcbdd01U),
                                       bswap_32big(0x59e5016cU),
                                       bswap_32big(0x43ad7445U),
                                       bswap_32big(0x77dfdb04U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe7009d05U);

                        WR1_PROG(REG_009CH, 0x81840007U);
                        WR1_PROG(REG_0000H, 0x00490011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_EncIV[1]);

                        r_rsip_func100(bswap_32big(0x5a6c7a79U),
                                       bswap_32big(0x8376be5aU),
                                       bswap_32big(0xd2512f7aU),
                                       bswap_32big(0xa76c01c8U));
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

                        r_rsip_func100(bswap_32big(0x14f5adf1U),
                                       bswap_32big(0xb07fd031U),
                                       bswap_32big(0x94dd42aeU),
                                       bswap_32big(0xb4ffc86aU));
                        WR1_PROG(REG_009CH, 0x81010000U);
                        WR1_PROG(REG_0008H, 0x00005006U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD1_ADDR(REG_002CH, &OutData_EncIV[0]);

                        r_rsip_func102(bswap_32big(0x0212979fU),
                                       bswap_32big(0x3a7c8125U),
                                       bswap_32big(0xed9fa888U),
                                       bswap_32big(0xffb29142U));
                        WR1_PROG(REG_006CH, 0x00000040U);
                        WAIT_STS(REG_0020H, 12, 0);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
