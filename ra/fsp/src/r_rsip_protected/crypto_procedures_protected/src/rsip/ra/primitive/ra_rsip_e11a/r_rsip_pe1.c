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

rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[],
                       const uint32_t InData_Certificate[],
                       const uint32_t InData_CertificateLength[],
                       const uint32_t InData_CertificatePubKey[],
                       const uint32_t InData_EncCertificateInfo[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t iTemp = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e10001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Sel_KeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000005U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0xe5f121e0U),
                   bswap_32big(0x65e237e3U),
                   bswap_32big(0x0c7bc9c8U),
                   bswap_32big(0x928b56ccU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x25ae2478U), bswap_32big(0x91146df6U), bswap_32big(0x8991984dU),
                       bswap_32big(0xe77d770dU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x3000a800U);
        WR1_PROG(REG_0094H, 0x00000006U);
        WR1_PROG(REG_0094H, 0x00010020U);
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000006U);
        WR1_PROG(REG_0094H, 0x00000080U);

        WR1_PROG(REG_0094H, 0x0000b420U);
        WR1_PROG(REG_0094H, 0x00000014U);
        WR1_PROG(REG_0094H, 0x00003c01U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_EncCertificateInfo[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000e101U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x09417f4cU), bswap_32big(0x26e6eabdU), bswap_32big(0xd26a1368U),
                       bswap_32big(0x5e06f705U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x010f6caaU);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000e101U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x83625c63U), bswap_32big(0xdd36ccccU), bswap_32big(0x435fa1b7U),
                       bswap_32big(0x1990b12eU));
        r_rsip_func044();

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
        WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[5]);

        WR1_PROG(REG_00B0H, 0x00001404U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[9]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xac7d098dU), bswap_32big(0x62514c07U), bswap_32big(0x5a03bd4cU),
                       bswap_32big(0x85802714U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xd0d9d631U), bswap_32big(0xcac792ecU), bswap_32big(0x82b1cd58U),
                           bswap_32big(0x42e6f781U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x80010040U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificateLength[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000003c7U);
            WR1_PROG(REG_009CH, 0x80040060U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[0]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[2]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[3]);
            WR1_PROG(REG_0024H, 0x00000000U);

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

            WR1_PROG(REG_0094H, 0x000008e7U);

            WR1_PROG(REG_0094H, 0x0000b400U);
            WR1_PROG(REG_0094H, 0x0000001fU);

            WR1_PROG(REG_0094H, 0x0000b420U);
            WR1_PROG(REG_0094H, 0x0000001fU);

            WR1_PROG(REG_0094H, 0x3c0028a6U);
            WR1_PROG(REG_0094H, 0x1000d0e0U);

            WR1_PROG(REG_0094H, 0x00002425U);
            WR1_PROG(REG_0094H, 0x08002826U);
            WR1_PROG(REG_0094H, 0x2000d0e0U);

            WR1_PROG(REG_0094H, 0x3c002864U);
            WR1_PROG(REG_0094H, 0x1000d0e0U);

            WR1_PROG(REG_0094H, 0x3c002885U);
            WR1_PROG(REG_0094H, 0x1000d0e0U);

            WR1_PROG(REG_0094H, 0x00002403U);
            WR1_PROG(REG_0094H, 0x08002804U);
            WR1_PROG(REG_0094H, 0x2000d0e0U);

            WR1_PROG(REG_0094H, 0x3c0028c2U);
            WR1_PROG(REG_0094H, 0x1000d0e0U);

            WR1_PROG(REG_0094H, 0x38000ce7U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0xe7658efaU), bswap_32big(0xe6d46e36U), bswap_32big(0x261f9028U),
                           bswap_32big(0xbf38b9daU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x71e92a3dU),
                               bswap_32big(0x4a7fbb4cU),
                               bswap_32big(0xb36f2642U),
                               bswap_32big(0x4898dc3cU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x7cedb3c1U),
                               bswap_32big(0x669a33a2U),
                               bswap_32big(0x63c7d2aaU),
                               bswap_32big(0xd9d2bdd6U));
                WR1_PROG(REG_0094H, 0x00003403U);
                WR1_PROG(REG_0094H, 0x00046800U);
                WR1_PROG(REG_0094H, 0x00026c00U);

                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x00000821U);

                for (iLoop = 0U; iLoop < S_RAM[0]; )
                {
                    WR1_PROG(REG_0014H, 0x000003c4U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_Certificate[iLoop]);

                    WR1_PROG(REG_0094H, 0x0000a420U);
                    WR1_PROG(REG_0094H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0xd4a17bf3U),
                                   bswap_32big(0x561856ccU),
                                   bswap_32big(0xe43c74c7U),
                                   bswap_32big(0xec2bb09eU));
                    iLoop = iLoop + 4U;
                }

                r_rsip_func100(bswap_32big(0x2c950e37U),
                               bswap_32big(0xaf70b267U),
                               bswap_32big(0x5cbb215dU),
                               bswap_32big(0xbfc873c2U));

                WR1_PROG(REG_0094H, 0x38000801U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_00B0H, 0x0000340cU);

                WR1_PROG(REG_0094H, 0x00003402U);
                WR1_PROG(REG_0094H, 0x0000a400U);
                WR1_PROG(REG_0094H, 0x00000003U);
                WR1_PROG(REG_0094H, 0x00026800U);

                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000034e1U);
                WR1_PROG(REG_0094H, 0x00026ce7U);

                WR1_PROG(REG_0094H, 0x00003040U);

                WR1_PROG(REG_0094H, 0x00000884U);
                WR1_PROG(REG_0094H, 0x00003c04U);

                iTemp = iLoop;
                for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0014H, 0x000000c7U);
                    WR1_PROG(REG_009CH, 0x800100c0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, InData_Certificate[iLoop]);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000004U);
                    WR1_PROG(REG_0094H, 0x00003c24U);

                    WR1_PROG(REG_0094H, 0x00000821U);

                    for (jLoop = 0U; jLoop < 4; jLoop++)
                    {
                        WR1_PROG(REG_0094H, 0x00002c20U);

                        WR1_PROG(REG_0094H, 0x01886c06U);
                        WR1_PROG(REG_0094H, 0x00086cc6U);

                        WR1_PROG(REG_0094H, 0x00003485U);
                        WR1_PROG(REG_0094H, 0x0000a480U);
                        WR1_PROG(REG_0094H, 0x0000001fU);

                        WR1_PROG(REG_0094H, 0x3c0028e5U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00260000U);

                        r_rsip_func100(bswap_32big(0xb9215619U),
                                       bswap_32big(0x640092c5U),
                                       bswap_32big(0xcf485692U),
                                       bswap_32big(0x74576b3cU));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x3c002887U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00260000U);

                            r_rsip_func100(bswap_32big(0x51ff950dU),
                                           bswap_32big(0x690d17d6U),
                                           bswap_32big(0xd5299dd8U),
                                           bswap_32big(0xffc16e32U));
                            WR1_PROG(REG_0040H, 0x00400000U);
                            WR1_PROG(REG_0024H, 0x00000000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_009CH, 0x81010000U);
                                WR1_PROG(REG_0000H, 0x1009000dU);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);
                                WR1_PROG(REG_0000H, 0x10c90005U);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);

                                r_rsip_func101(bswap_32big(0x0fdd268dU), bswap_32big(0x61aab0b3U),
                                               bswap_32big(0xede01555U), bswap_32big(0x1b7ad57fU));
                            }

                            r_rsip_func101(bswap_32big(0xd680661aU),
                                           bswap_32big(0x962cc512U),
                                           bswap_32big(0xb8e47fb5U),
                                           bswap_32big(0x4d9f1101U));
                        }

                        WR1_PROG(REG_0094H, 0x00003483U);
                        WR1_PROG(REG_0094H, 0x0000a480U);
                        WR1_PROG(REG_0094H, 0x0000001fU);

                        WR1_PROG(REG_0094H, 0x3c0028e3U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x0a80254eU),
                                       bswap_32big(0x791bc6c5U),
                                       bswap_32big(0x65c70125U),
                                       bswap_32big(0xb0c3fcc1U));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_0094H, 0x3c002887U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00260000U);

                            r_rsip_func100(bswap_32big(0xd083bf18U),
                                           bswap_32big(0x6f33374cU),
                                           bswap_32big(0x34537126U),
                                           bswap_32big(0x9320d91bU));
                            WR1_PROG(REG_0040H, 0x00400000U);
                            WR1_PROG(REG_0024H, 0x00000000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_009CH, 0x81010000U);
                                WR1_PROG(REG_0000H, 0x1009000dU);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);
                                WR1_PROG(REG_0000H, 0x10c90005U);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);

                                r_rsip_func101(bswap_32big(0x8ec53278U), bswap_32big(0x2f330114U),
                                               bswap_32big(0x0e4aacc4U), bswap_32big(0x273899dbU));
                            }

                            r_rsip_func101(bswap_32big(0xf6c9d1eeU),
                                           bswap_32big(0xb2973df2U),
                                           bswap_32big(0xc7a0ff79U),
                                           bswap_32big(0xbe49f954U));
                        }

                        WR1_PROG(REG_0094H, 0x3c002847U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00260000U);

                        r_rsip_func100(bswap_32big(0xce0e04f5U),
                                       bswap_32big(0xa7622873U),
                                       bswap_32big(0xe91df532U),
                                       bswap_32big(0x4e89b0cdU));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_009CH, 0x81010000U);
                            WR1_PROG(REG_0000H, 0x1009000dU);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);
                            WR1_PROG(REG_0000H, 0x11490005U);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);

                            r_rsip_func101(bswap_32big(0xf7a82c6eU),
                                           bswap_32big(0xc513e182U),
                                           bswap_32big(0x359a3d40U),
                                           bswap_32big(0xabe092d4U));
                        }

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0x3fa1d897U),
                                       bswap_32big(0xb0b796f3U),
                                       bswap_32big(0x20d3832fU),
                                       bswap_32big(0x3786c233U));
                    }

                    WR1_PROG(REG_0094H, 0x38008820U);
                    WR1_PROG(REG_0094H, 0x00000004U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);
                    WR1_PROG(REG_0040H, 0x00402000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x0000b480U);
                    WR1_PROG(REG_0094H, 0x00000004U);
                    WR1_PROG(REG_0094H, 0x00003824U);

                    WR1_PROG(REG_0094H, 0x00002c20U);

                    r_rsip_func101(bswap_32big(0xc473977cU),
                                   bswap_32big(0xc5a51b3dU),
                                   bswap_32big(0x8a619c4eU),
                                   bswap_32big(0xf5bbc6e1U));
                }

                WR1_PROG(REG_0094H, 0x00000884U);
                WR1_PROG(REG_0094H, 0x00003804U);

                WR1_PROG(REG_0094H, 0x38000801U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002c40U);

                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0x00000080U);
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0000H, 0x1009000dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0000H, 0x11490005U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00003402U);
                WR1_PROG(REG_0094H, 0x00002c00U);
                WR1_PROG(REG_0094H, 0x00008c00U);
                WR1_PROG(REG_0094H, 0x0000003fU);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000038U);
                WR1_PROG(REG_0094H, 0x3c002820U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                r_rsip_func100(bswap_32big(0x1b268efdU),
                               bswap_32big(0x394c0a4dU),
                               bswap_32big(0x69d46c42U),
                               bswap_32big(0xed786bcaU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00202820U);

                    r_rsip_func101(bswap_32big(0xa59cd21aU),
                                   bswap_32big(0x222ef775U),
                                   bswap_32big(0x84116184U),
                                   bswap_32big(0x570d63b6U));
                }
                else
                {
                    WR1_PROG(REG_0094H, 0x0000a420U);
                    WR1_PROG(REG_0094H, 0x00000040U);
                    WR1_PROG(REG_0094H, 0x00202820U);

                    r_rsip_func101(bswap_32big(0x78e41c0eU),
                                   bswap_32big(0x6e2868d1U),
                                   bswap_32big(0xaf48549dU),
                                   bswap_32big(0xe5f7a8f7U));
                }

                r_rsip_func100(bswap_32big(0x65eb4f3aU),
                               bswap_32big(0x2b297a30U),
                               bswap_32big(0xff99ab44U),
                               bswap_32big(0xb0d8216dU));
                WR1_PROG(REG_009CH, 0x81010020U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x00000800U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0000H, 0x11490005U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0000H, 0x1009000dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x8a87c4b0U),
                                   bswap_32big(0xf8bcf046U),
                                   bswap_32big(0x4444cda6U),
                                   bswap_32big(0x09d050dfU));
                }

                WR1_PROG(REG_0094H, 0x38000825U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x01836c22U);
                WR1_PROG(REG_0094H, 0x00036c42U);

                WR1_PROG(REG_009CH, 0x81020020U);
                WR1_PROG(REG_0000H, 0x01490009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WAIT_STS(REG_00F8H, 2, 0);

                WR1_PROG(REG_00F4H, 0x00000100U);

                WR1_PROG(REG_0040H, 0x00001600U);

                WR1_PROG(REG_00F4H, 0x00000020U);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x00000800U);

                WR1_PROG(REG_00B0H, 0x00001804U);

                for (iLoop = 0U; iLoop < 8U; iLoop++)
                {
                    WR1_PROG(REG_009CH, 0x80010020U);
                    WR1_PROG(REG_0000H, 0x03450005U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_009CH, 0x80010040U);
                    WR1_PROG(REG_0000H, 0x03430005U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x08002822U);
                    WR1_PROG(REG_0094H, 0x2000d000U);

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x6a08b8abU),
                                   bswap_32big(0x6a4daf43U),
                                   bswap_32big(0x39316551U),
                                   bswap_32big(0x48b425d6U));
                }

                WR1_PROG(REG_0094H, 0x380088a0U);
                WR1_PROG(REG_0094H, 0x00000008U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x38000c00U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00A60000U);

                r_rsip_func100(bswap_32big(0xde099eecU),
                               bswap_32big(0x57064854U),
                               bswap_32big(0xf0665017U),
                               bswap_32big(0x31bedd1bU));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x7b1b8e14U),
                                   bswap_32big(0x842f3439U),
                                   bswap_32big(0x85e828c6U),
                                   bswap_32big(0x6e790ec4U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xae6cb94dU),
                                   bswap_32big(0x6acfde91U),
                                   bswap_32big(0x6ffc68c0U),
                                   bswap_32big(0x0e3f2206U));
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
                    WR1_PROG(REG_002CH, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x953eac3cU),
                                   bswap_32big(0xe3caf5e9U),
                                   bswap_32big(0x64d4a1b9U),
                                   bswap_32big(0xee058ee8U));
                    r_rsip_func043();

                    WR1_PROG(REG_0094H, 0x0000b420U);
                    WR1_PROG(REG_0094H, 0x00000014U);
                    WR1_PROG(REG_0094H, 0x00003881U);

                    r_rsip_func100(bswap_32big(0x4cd91c6fU),
                                   bswap_32big(0x6b88467cU),
                                   bswap_32big(0xa228984bU),
                                   bswap_32big(0xc59f77e4U));
                    WR1_PROG(REG_0094H, 0x00007c04U);
                    WR1_PROG(REG_0040H, 0x00600000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                    {
                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x00000016U);

                        r_rsip_func101(bswap_32big(0x0b82053dU),
                                       bswap_32big(0xb8d9c83dU),
                                       bswap_32big(0x750d4e76U),
                                       bswap_32big(0x9b171b83U));
                    }
                    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
                    {
                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);

                        r_rsip_func101(bswap_32big(0xd7980f48U),
                                       bswap_32big(0x9514d7a0U),
                                       bswap_32big(0xdb539f15U),
                                       bswap_32big(0xa309fbd5U));
                    }

                    WR1_PROG(REG_0014H, 0x000000a7U);
                    WR1_PROG(REG_009CH, 0x800100e0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x45cb7810U),
                                   bswap_32big(0x518be860U),
                                   bswap_32big(0x65b7989bU),
                                   bswap_32big(0xce21edeeU));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0x1b074282U),
                                   bswap_32big(0xde072271U),
                                   bswap_32big(0xb67e284dU),
                                   bswap_32big(0x847f1c1fU));
                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000044U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000054U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_00D4H, 0x40000100U);
                    WR1_PROG(REG_00D0H, 0xe8008107U);
                    WR1_PROG(REG_00B0H, 0x00001808U);
                    WR1_PROG(REG_0000H, 0x00430021U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0008H, 0x00001022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                    r_rsip_func100(bswap_32big(0x43435a2fU),
                                   bswap_32big(0xdebdd7deU),
                                   bswap_32big(0x8797a247U),
                                   bswap_32big(0x5169eecdU));
                    WR1_PROG(REG_00D4H, 0x40000100U);
                    WR1_PROG(REG_00D0H, 0xe8008107U);
                    WR1_PROG(REG_00B0H, 0x0000180cU);
                    WR1_PROG(REG_0000H, 0x00430021U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0008H, 0x00001022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

                    r_rsip_func100(bswap_32big(0x390c85e3U),
                                   bswap_32big(0x735c7338U),
                                   bswap_32big(0x9e704ba8U),
                                   bswap_32big(0x08bb6397U));
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
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

                    r_rsip_func100(bswap_32big(0x58603459U),
                                   bswap_32big(0x8a2fd396U),
                                   bswap_32big(0x6dcb2857U),
                                   bswap_32big(0x81ebb71fU));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x7a122badU),
                                   bswap_32big(0xbcf1ec7eU),
                                   bswap_32big(0xcf408e42U),
                                   bswap_32big(0xa53289a5U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
