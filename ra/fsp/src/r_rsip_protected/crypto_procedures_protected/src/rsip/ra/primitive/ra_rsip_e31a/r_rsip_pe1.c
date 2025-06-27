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
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x5f4b210aU),
                   bswap_32big(0xbca45285U),
                   bswap_32big(0x196eb818U),
                   bswap_32big(0xbccfbceeU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x73ec41aeU), bswap_32big(0x7e54aee7U), bswap_32big(0x3766b851U),
                       bswap_32big(0x93e0cf37U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x3000a800U);
        WR1_PROG(REG_0094H, 0x00000004U);
        WR1_PROG(REG_0094H, 0x00010020U);
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000004U);
        WR1_PROG(REG_0094H, 0x00000080U);

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

        r_rsip_func101(bswap_32big(0x4bef45beU), bswap_32big(0x4ea42f77U), bswap_32big(0x13e56f85U),
                       bswap_32big(0x660ef164U));
        r_rsip_func043();

        r_rsip_func100(bswap_32big(0x3d6f58dbU), bswap_32big(0xe0984811U), bswap_32big(0xe76b87d0U),
                       bswap_32big(0x5ca99cf6U));

        WR1_PROG(REG_0094H, 0x00007c00U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x010f6caaU);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000008U);

            WR1_PROG(REG_00B0H, 0x00001404U);

            r_rsip_func101(bswap_32big(0xe153eacfU), bswap_32big(0xa34cf565U), bswap_32big(0xa2dc1c44U),
                           bswap_32big(0x24a2a397U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01f6c222U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x0000000cU);

            WR1_PROG(REG_00B0H, 0x00009406U);

            r_rsip_func101(bswap_32big(0xd13d28b3U), bswap_32big(0xab090fc4U), bswap_32big(0x781f7894U),
                           bswap_32big(0x3d791cddU));
        }

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000e101U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x54cb54a6U), bswap_32big(0x45bd4bd0U), bswap_32big(0x27656083U),
                       bswap_32big(0x1bce04d4U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0094H, 0x00000884U);

        WR1_PROG(REG_0094H, 0x0000b440U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_0094H, 0x00003c62U);

        r_rsip_func100(bswap_32big(0xdbfd611eU), bswap_32big(0x83d38239U), bswap_32big(0x03490f53U),
                       bswap_32big(0x53cd1bbaU));
        WR1_PROG(REG_009CH, 0x81010060U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xf7008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[1 + iLoop]);

            WR1_PROG(REG_0000H, 0x00c10011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x0000a480U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x6d1405a3U), bswap_32big(0xa7bf791fU), bswap_32big(0xd38cd899U),
                           bswap_32big(0xd8fc0b34U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_0094H, 0x38000864U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[1 + iLoop]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xbd0eef79U), bswap_32big(0xe37bb300U), bswap_32big(0xf9a88b2fU),
                       bswap_32big(0x7d284e2cU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xc87bc54dU), bswap_32big(0x84cd39f4U), bswap_32big(0x684b313dU),
                           bswap_32big(0x537647a1U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xa0116b12U), bswap_32big(0x78baac55U), bswap_32big(0xb8c0bb46U),
                           bswap_32big(0x2b5751dbU));

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

            WR1_PROG(REG_0094H, 0x0000b420U);
            WR1_PROG(REG_0094H, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003c01U);

            WR1_PROG(REG_00F0H, 0x00000001U);

            WR1_PROG(REG_0094H, 0x000008e7U);

            WR1_PROG(REG_0094H, 0x00007c00U);
            WR1_PROG(REG_0040H, 0x00600000U);

            if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
            {
                WR1_PROG(REG_00F4H, 0x00000050U);

                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                r_rsip_func101(bswap_32big(0xfb842034U),
                               bswap_32big(0x1ddaf7ebU),
                               bswap_32big(0x54c6e139U),
                               bswap_32big(0x6e51f08dU));
            }
            else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
            {
                WR1_PROG(REG_00F4H, 0x000000a0U);

                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0x0000002fU);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000002fU);

                r_rsip_func101(bswap_32big(0x75bc5439U),
                               bswap_32big(0xa015bf12U),
                               bswap_32big(0xa1e601f3U),
                               bswap_32big(0x74463d12U));
            }

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
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xbd0bf7e5U), bswap_32big(0x69429de8U), bswap_32big(0x8a66fdb1U),
                           bswap_32big(0x40c826bfU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd1a7cde6U),
                               bswap_32big(0x4b255cf4U),
                               bswap_32big(0x3e8f2fc1U),
                               bswap_32big(0x2566d934U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xd567b677U),
                               bswap_32big(0xec7a82a7U),
                               bswap_32big(0x66424550U),
                               bswap_32big(0x2e5e0a4cU));
                WR1_PROG(REG_0094H, 0x00000800U);
                WR1_PROG(REG_0094H, 0x00003422U);

                WR1_PROG(REG_0094H, 0x01836c01U);
                WR1_PROG(REG_0094H, 0x00036c21U);

                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0008H, 0x0000500aU);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0 + 1]);
                S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                r_rsip_func100(bswap_32big(0x269f07e5U),
                               bswap_32big(0xe5a8dc64U),
                               bswap_32big(0xad6298a7U),
                               bswap_32big(0x9e578302U));
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0104H, S_RAM[0]);
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0100H, S_RAM[0 + 1]);

                WR1_PROG(REG_0094H, 0x00003403U);
                WR1_PROG(REG_0094H, 0x00046800U);
                WR1_PROG(REG_0094H, 0x00026c00U);

                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x00000821U);

                WAIT_STS(REG_0118H, 0, 1);

                for (iLoop = 0U; iLoop < S_RAM[0]; )
                {
                    WR1_PROG(REG_0014H, 0x000003c4U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_Certificate[iLoop]);

                    WR1_PROG(REG_0094H, 0x0000a420U);
                    WR1_PROG(REG_0094H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0xdccf2eb3U),
                                   bswap_32big(0x8db6c900U),
                                   bswap_32big(0x44fc33d1U),
                                   bswap_32big(0x88707a74U));
                    iLoop = iLoop + 4U;
                }

                r_rsip_func100(bswap_32big(0x8ba39084U),
                               bswap_32big(0x175e5f49U),
                               bswap_32big(0x2f70a9f3U),
                               bswap_32big(0xfc0ea338U));

                WR1_PROG(REG_0094H, 0x38000801U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00003402U);
                WR1_PROG(REG_0094H, 0x0000a400U);
                WR1_PROG(REG_0094H, 0x00000003U);
                WR1_PROG(REG_0094H, 0x00026800U);

                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                r_rsip_func100(bswap_32big(0x263c322aU),
                               bswap_32big(0xd33423f9U),
                               bswap_32big(0x754ef677U),
                               bswap_32big(0x63efd588U));

                WR1_PROG(REG_0094H, 0x000034e1U);
                WR1_PROG(REG_0094H, 0x00026ce7U);

                WR1_PROG(REG_0094H, 0x00003040U);

                WR1_PROG(REG_0094H, 0x00000884U);
                WR1_PROG(REG_0094H, 0x00003c04U);

                WR1_PROG(REG_0094H, 0x0000b480U);
                WR1_PROG(REG_0094H, 0x00000014U);
                WR1_PROG(REG_0094H, 0x00003804U);

                WR1_PROG(REG_0094H, 0x00007c00U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                {
                    WR1_PROG(REG_00B0H, 0x0000340eU);

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
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0xfea02bf5U),
                                           bswap_32big(0xbecc8743U),
                                           bswap_32big(0x5b260daeU),
                                           bswap_32big(0x15ac60fbU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_0094H, 0x3c002887U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x27dde1c9U), bswap_32big(0x772b9785U),
                                               bswap_32big(0x07d1b3e5U), bswap_32big(0x5328ca71U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_009CH, 0x81010000U);
                                    WR1_PROG(REG_0000H, 0x1009000dU);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);
                                    WR1_PROG(REG_0000H, 0x10c90005U);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);

                                    r_rsip_func101(bswap_32big(0x9de1c07bU), bswap_32big(0xe57a9071U),
                                                   bswap_32big(0x06c1e689U), bswap_32big(0xb49d708eU));
                                }

                                r_rsip_func101(bswap_32big(0xb188a3f4U), bswap_32big(0x6ef69cb8U),
                                               bswap_32big(0x5fc82f24U), bswap_32big(0x3a5a1bc3U));
                            }

                            WR1_PROG(REG_0094H, 0x00003483U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            WR1_PROG(REG_0094H, 0x0000001fU);

                            WR1_PROG(REG_0094H, 0x3c0028e3U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x5620de1aU),
                                           bswap_32big(0xdcc40146U),
                                           bswap_32big(0xb38f12c1U),
                                           bswap_32big(0xa65dbc8eU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_0094H, 0x3c002887U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x38472369U), bswap_32big(0xed60c542U),
                                               bswap_32big(0xe35a3956U), bswap_32big(0x6de66541U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_009CH, 0x81010000U);
                                    WR1_PROG(REG_0000H, 0x1009000dU);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);
                                    WR1_PROG(REG_0000H, 0x10c90005U);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);

                                    r_rsip_func101(bswap_32big(0xbc32ecccU), bswap_32big(0x2a35aaf4U),
                                                   bswap_32big(0xad169ec8U), bswap_32big(0xfe152b4eU));
                                }

                                r_rsip_func101(bswap_32big(0x485b654dU), bswap_32big(0xa3f9d84cU),
                                               bswap_32big(0xeda48896U), bswap_32big(0x25927c37U));
                            }

                            WR1_PROG(REG_0094H, 0x3c002847U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0xc1042b0dU),
                                           bswap_32big(0x11100214U),
                                           bswap_32big(0x52b0081eU),
                                           bswap_32big(0x147a88eaU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_009CH, 0x81010000U);
                                WR1_PROG(REG_0000H, 0x1009000dU);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);
                                WR1_PROG(REG_0000H, 0x11490005U);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);

                                r_rsip_func101(bswap_32big(0x140adec1U), bswap_32big(0xdefd679fU),
                                               bswap_32big(0x7ecc7817U), bswap_32big(0xab462862U));
                            }

                            WR1_PROG(REG_0094H, 0x00002ce0U);

                            r_rsip_func101(bswap_32big(0x1f1a66eaU),
                                           bswap_32big(0xbcf605d1U),
                                           bswap_32big(0x1c4ebe75U),
                                           bswap_32big(0xee9d81a8U));
                        }

                        WR1_PROG(REG_0094H, 0x38008820U);
                        WR1_PROG(REG_0094H, 0x00000004U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);
                        WR1_PROG(REG_0040H, 0x00402000U);

                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000004U);
                        WR1_PROG(REG_0094H, 0x00003824U);

                        WR1_PROG(REG_0094H, 0x00002c20U);

                        r_rsip_func101(bswap_32big(0x135cc842U),
                                       bswap_32big(0x1e670870U),
                                       bswap_32big(0x40d7acf7U),
                                       bswap_32big(0xdbb30cd7U));
                    }

                    r_rsip_func101(bswap_32big(0x7e833879U),
                                   bswap_32big(0xb8552f99U),
                                   bswap_32big(0xd8520ec6U),
                                   bswap_32big(0x8764c234U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
                {
                    WR1_PROG(REG_00B0H, 0x0000b412U);

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
                            WR1_PROG(REG_0094H, 0x0000002fU);

                            WR1_PROG(REG_0094H, 0x3c0028e5U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x34a6f1baU),
                                           bswap_32big(0x079d278eU),
                                           bswap_32big(0xf6be6cf1U),
                                           bswap_32big(0x1c4f9545U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_0094H, 0x3c002887U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0xadae4607U), bswap_32big(0xb7d93634U),
                                               bswap_32big(0xc72d22acU), bswap_32big(0x63efd056U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_009CH, 0x81010000U);
                                    WR1_PROG(REG_0000H, 0x1009000dU);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);
                                    WR1_PROG(REG_0000H, 0x10c90005U);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);

                                    r_rsip_func101(bswap_32big(0x1ca971f8U), bswap_32big(0x69d7a655U),
                                                   bswap_32big(0xb36975ccU), bswap_32big(0x4d2e5af3U));
                                }

                                r_rsip_func101(bswap_32big(0x81769047U), bswap_32big(0x0879509cU),
                                               bswap_32big(0x118830b0U), bswap_32big(0xdc15bbe4U));
                            }

                            WR1_PROG(REG_0094H, 0x00003483U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            WR1_PROG(REG_0094H, 0x0000002fU);

                            WR1_PROG(REG_0094H, 0x3c0028e3U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0xfe4ca5b0U),
                                           bswap_32big(0xe804491cU),
                                           bswap_32big(0xd54f10faU),
                                           bswap_32big(0x7c31588bU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_0094H, 0x3c002887U);
                                WR1_PROG(REG_009CH, 0x00000080U);
                                WR1_PROG(REG_0040H, 0x00270000U);

                                r_rsip_func100(bswap_32big(0xf665eab5U), bswap_32big(0x360ee9d3U),
                                               bswap_32big(0xe2e1de84U), bswap_32big(0xcfda9e71U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    WR1_PROG(REG_009CH, 0x81010000U);
                                    WR1_PROG(REG_0000H, 0x1009000dU);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);
                                    WR1_PROG(REG_0000H, 0x10c90005U);
                                    WAIT_STS(REG_0004H, 30, 0);
                                    WR1_PROG(REG_0040H, 0x00001800U);

                                    r_rsip_func101(bswap_32big(0xf21338c3U), bswap_32big(0xd9455334U),
                                                   bswap_32big(0x151c8af7U), bswap_32big(0x65411ab6U));
                                }

                                r_rsip_func101(bswap_32big(0x2f6e3452U), bswap_32big(0xc9056f6aU),
                                               bswap_32big(0x679a43bdU), bswap_32big(0x74a9bb31U));
                            }

                            WR1_PROG(REG_0094H, 0x3c002847U);
                            WR1_PROG(REG_009CH, 0x00000080U);
                            WR1_PROG(REG_0040H, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x3f33f812U),
                                           bswap_32big(0x8679730aU),
                                           bswap_32big(0x0c7e4593U),
                                           bswap_32big(0x804e2ddaU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                WR1_PROG(REG_009CH, 0x81010000U);
                                WR1_PROG(REG_0000H, 0x1009000dU);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);
                                WR1_PROG(REG_0000H, 0x11490005U);
                                WAIT_STS(REG_0004H, 30, 0);
                                WR1_PROG(REG_0040H, 0x00001800U);

                                r_rsip_func101(bswap_32big(0xeb3d3be8U), bswap_32big(0xa133d8c7U),
                                               bswap_32big(0xca251653U), bswap_32big(0x3f927f84U));
                            }

                            WR1_PROG(REG_0094H, 0x00002ce0U);

                            r_rsip_func101(bswap_32big(0xe361304fU),
                                           bswap_32big(0xfaf06b52U),
                                           bswap_32big(0xe908ed75U),
                                           bswap_32big(0x411dc9dbU));
                        }

                        WR1_PROG(REG_0094H, 0x38008820U);
                        WR1_PROG(REG_0094H, 0x00000004U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00270000U);
                        WR1_PROG(REG_0040H, 0x00402000U);

                        WR1_PROG(REG_0094H, 0x0000b480U);
                        WR1_PROG(REG_0094H, 0x00000004U);
                        WR1_PROG(REG_0094H, 0x00003824U);

                        WR1_PROG(REG_0094H, 0x00002c20U);

                        r_rsip_func101(bswap_32big(0x3916345aU),
                                       bswap_32big(0x0d9d47aaU),
                                       bswap_32big(0x543366a7U),
                                       bswap_32big(0x67eab3bbU));
                    }

                    r_rsip_func101(bswap_32big(0x2cbf1fb9U),
                                   bswap_32big(0x08708b31U),
                                   bswap_32big(0x5dfbc1b9U),
                                   bswap_32big(0x604cae98U));
                }

                WR1_PROG(REG_0094H, 0x00000884U);
                WR1_PROG(REG_0094H, 0x00003804U);

                WR1_PROG(REG_0094H, 0x38000801U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00002c40U);

                r_rsip_func100(bswap_32big(0x4341096cU),
                               bswap_32big(0x4a9f6947U),
                               bswap_32big(0xd8e368b3U),
                               bswap_32big(0x4200d728U));
                WR1_PROG(REG_0094H, 0x00003402U);
                WR1_PROG(REG_0094H, 0x00008c00U);
                WR1_PROG(REG_0094H, 0x00000003U);

                WR1_PROG(REG_0094H, 0x0000b440U);
                WR1_PROG(REG_0094H, 0x00000004U);
                WR1_PROG(REG_0094H, 0x00002840U);
                WR1_PROG(REG_0094H, 0x00008c40U);
                WR1_PROG(REG_0094H, 0x00000003U);

                WR1_PROG(REG_009CH, 0x81010040U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x00000863U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_009CH, 0x81010060U);
                    WR1_PROG(REG_0000H, 0x11490005U);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);
                    WR1_PROG(REG_0000H, 0x1009000dU);
                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x00086c63U);

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xbed25e06U),
                                   bswap_32big(0x47e60b16U),
                                   bswap_32big(0x912900a2U),
                                   bswap_32big(0x71b3db40U));
                }

                WR1_PROG(REG_0094H, 0x38000845U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func100(bswap_32big(0x0ad21918U),
                               bswap_32big(0xd18d90deU),
                               bswap_32big(0x441484dbU),
                               bswap_32big(0xa3acd1e5U));
                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x00000800U);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000014U);
                WR1_PROG(REG_0094H, 0x00003881U);

                WR1_PROG(REG_0094H, 0x00007c04U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                {
                    WR1_PROG(REG_00B0H, 0x00001804U);

                    r_rsip_func101(bswap_32big(0xb4101099U),
                                   bswap_32big(0xdc2ce4cbU),
                                   bswap_32big(0x34e723f8U),
                                   bswap_32big(0x4d69ea27U));
                }
                else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
                {
                    WR1_PROG(REG_00B0H, 0x00009806U);

                    r_rsip_func101(bswap_32big(0x4cbd2498U),
                                   bswap_32big(0x7748cafbU),
                                   bswap_32big(0xcea3ea1dU),
                                   bswap_32big(0x01911354U));
                }

                r_rsip_func100(bswap_32big(0xa2d2b2fbU),
                               bswap_32big(0xa3b1e0b4U),
                               bswap_32big(0xe2b988fcU),
                               bswap_32big(0xe13a23abU));
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_009CH, 0x81810001U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
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

                    r_rsip_func101(bswap_32big(0x02ce80a1U),
                                   bswap_32big(0x88b2f6d5U),
                                   bswap_32big(0x1033c381U),
                                   bswap_32big(0x344ed354U));
                }

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_0094H, 0x00003841U);

                WR1_PROG(REG_0094H, 0x380008a2U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x38000c00U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00A70000U);

                r_rsip_func100(bswap_32big(0xe137d784U),
                               bswap_32big(0x0f13add4U),
                               bswap_32big(0x5a399015U),
                               bswap_32big(0xc8c38c26U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xba5a056dU),
                                   bswap_32big(0x9914c60fU),
                                   bswap_32big(0x5f63ff9fU),
                                   bswap_32big(0x1bb446b3U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x5d104e7fU),
                                   bswap_32big(0x80745c10U),
                                   bswap_32big(0xa5799c02U),
                                   bswap_32big(0x5eab9e4cU));
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

                    r_rsip_func101(bswap_32big(0x9b4a8adbU),
                                   bswap_32big(0x3ceae954U),
                                   bswap_32big(0x5a394240U),
                                   bswap_32big(0x2967cb53U));
                    r_rsip_func043();

                    r_rsip_func100(bswap_32big(0xfb6a04b8U),
                                   bswap_32big(0x3717a7cbU),
                                   bswap_32big(0x1ce78027U),
                                   bswap_32big(0x4cc9259fU));
                    WR1_PROG(REG_0094H, 0x00007c04U);
                    WR1_PROG(REG_0040H, 0x00600000U);

                    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                    {
                        WR1_PROG(REG_00B0H, 0x0000380eU);

                        WR1_PROG(REG_0094H, 0x0000b460U);
                        WR1_PROG(REG_0094H, 0x00000010U);

                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x00000016U);

                        r_rsip_func101(bswap_32big(0x0df4b056U),
                                       bswap_32big(0x49bbffddU),
                                       bswap_32big(0xfb3cb309U),
                                       bswap_32big(0xb652041aU));
                    }
                    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
                    {
                        WR1_PROG(REG_00B0H, 0x0000b812U);

                        WR1_PROG(REG_0094H, 0x0000b460U);
                        WR1_PROG(REG_0094H, 0x00000018U);

                        WR1_PROG(REG_0094H, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x00000018U);

                        r_rsip_func101(bswap_32big(0x783d3ed1U),
                                       bswap_32big(0x09b1a839U),
                                       bswap_32big(0x917eb102U),
                                       bswap_32big(0x2c6f5b90U));
                    }

                    WR1_PROG(REG_0014H, 0x000000a7U);
                    WR1_PROG(REG_009CH, 0x800100e0U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_0024H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x4f671989U),
                                   bswap_32big(0x390d4985U),
                                   bswap_32big(0x6aa6f889U),
                                   bswap_32big(0x6841e466U));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0x401721d0U),
                                   bswap_32big(0xefb763c1U),
                                   bswap_32big(0x7389be75U),
                                   bswap_32big(0x9f73d05dU));
                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000044U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WR1_PROG(REG_00D0H, 0x08000054U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    WR1_PROG(REG_009CH, 0x81010060U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &S_RAM[0]);
                    S_RAM[0] = bswap_32big(S_RAM[0]);

                    WR1_PROG(REG_0094H, 0x00000884U);
                    WR1_PROG(REG_0094H, 0x000008a5U);

                    for (iLoop = 0U; iLoop < S_RAM[0]; )
                    {
                        WR1_PROG(REG_0094H, 0x342028a3U);
                        WR1_PROG(REG_0094H, 0x2000d080U);
                        WR1_PROG(REG_0094H, 0x00007c04U);
                        WR1_PROG(REG_0040H, 0x00602000U);

                        r_rsip_func100(bswap_32big(0xd5cb69e3U),
                                       bswap_32big(0xe4b78dc2U),
                                       bswap_32big(0x22ed3c2cU),
                                       bswap_32big(0xfe5e3710U));
                        WR1_PROG(REG_00D4H, 0x40000000U);
                        WR1_PROG(REG_00D0H, 0xe8008105U);
                        WR1_PROG(REG_0000H, 0x00430011U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0008H, 0x00001012U);
                        WAIT_STS(REG_0008H, 30, 1);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1 + iLoop]);

                        WR1_PROG(REG_0094H, 0x0000a4a0U);
                        WR1_PROG(REG_0094H, 0x00000004U);

                        r_rsip_func101(bswap_32big(0x533e6d1dU),
                                       bswap_32big(0xd55089e3U),
                                       bswap_32big(0xec52602aU),
                                       bswap_32big(0xadd17df8U));
                        iLoop = iLoop + 4U;
                    }

                    WR1_PROG(REG_0094H, 0x380008a3U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00270000U);
                    WR1_PROG(REG_0040H, 0x00402000U);

                    r_rsip_func100(bswap_32big(0xcca0bc89U),
                                   bswap_32big(0xcdfff988U),
                                   bswap_32big(0xaa18b49fU),
                                   bswap_32big(0x28d8d258U));
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
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1 + iLoop]);

                    r_rsip_func100(bswap_32big(0x58db36e9U),
                                   bswap_32big(0xd502521dU),
                                   bswap_32big(0xe5150727U),
                                   bswap_32big(0x788099deU));
                    WR1_PROG(REG_009CH, 0x81010000U);
                    WR1_PROG(REG_0008H, 0x00005006U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x767415f0U),
                                   bswap_32big(0x22222f1eU),
                                   bswap_32big(0x0f96ccb5U),
                                   bswap_32big(0xeeaa91cfU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
