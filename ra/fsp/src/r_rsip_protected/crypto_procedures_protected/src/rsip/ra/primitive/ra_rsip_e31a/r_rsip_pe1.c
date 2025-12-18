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

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_Sel_KeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub010(0x3420a800U, 0x00000003U, 0x00270000U);

    r_rsip_func_sub010(0x38008800U, 0x00000005U, 0x00270000U);

    r_rsip_func100(bswap_32big(0x592b494aU),
                   bswap_32big(0x0d57b2a1U),
                   bswap_32big(0x419ee291U),
                   bswap_32big(0xf8a977daU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x4817d770U), bswap_32big(0x397cbb90U), bswap_32big(0x8f1cb092U),
                       bswap_32big(0x91b03a98U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub022(0x3000a800U, 0x00000007U, 0x00010020U);
        r_rsip_func_sub022(0x0000b400U, 0x00000007U, 0x00000080U);

        r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_002CH, InData_EncCertificateInfo[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e101U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x65541358U), bswap_32big(0x11b03b73U), bswap_32big(0xeafaf801U),
                       bswap_32big(0x61e1fcd3U));
        r_rsip_func043();

        r_rsip_func_sub010(0x38008800U, 0x00000003U, 0x00270000U);

        r_rsip_func_sub010(0x38008800U, 0x00000006U, 0x00270000U);

        r_rsip_func100(bswap_32big(0xdc50a048U), bswap_32big(0x94a0655aU), bswap_32big(0xdf4589fbU),
                       bswap_32big(0x439b7e22U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub022(0x0000b4c0U, 0x010f6caaU, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000008U);

            WR1_PROG(REG_00B0H, 0x00001404U);

            r_rsip_func101(bswap_32big(0xdebeefc7U), bswap_32big(0xd486ae39U), bswap_32big(0xca882353U),
                           bswap_32big(0x29f2f471U));
        }
        else
        {
            r_rsip_func_sub022(0x0000b4c0U, 0x01f6c222U, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x0000000cU);

            WR1_PROG(REG_00B0H, 0x00009406U);

            r_rsip_func101(bswap_32big(0x1c888601U), bswap_32big(0x30520526U), bswap_32big(0xaed3295bU),
                           bswap_32big(0xa0fb4b8cU));
        }

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e101U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x54cb54a6U), bswap_32big(0x45bd4bd0U), bswap_32big(0x27656083U),
                       bswap_32big(0x1bce04d4U));
        r_rsip_func044();

        r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

        r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub022(0x00000884U, 0x0000b440U, 0x00000010U);
        WR1_PROG(REG_0094H, 0x00003c62U);

        r_rsip_func100(bswap_32big(0xdbfd611eU), bswap_32big(0x83d38239U), bswap_32big(0x03490f53U),
                       bswap_32big(0x53cd1bbaU));
        r_rsip_func_sub017(0x81010060U, 0x00005006U);
        RD1_ADDR(REG_002CH, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7008d05U);
            WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[1 + iLoop]);

            r_rsip_func_sub015(0x00c10011U, 0x00001800U);

            WR1_PROG(REG_0094H, 0x0000a480U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x6d1405a3U), bswap_32big(0xa7bf791fU), bswap_32big(0xd38cd899U),
                           bswap_32big(0xd8fc0b34U));
            iLoop = iLoop + 4U;
        }

        r_rsip_func_sub016(0x38000864U, 0x00000080U, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_002CH, &InData_EncCertificateInfo[1 + iLoop]);

        r_rsip_func_sub013(0x9c100005U, 0x00410011U);

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
            r_rsip_func_sub014(0x000000c7U, 0x80010040U);
            WR1_PROG(REG_002CH, InData_CertificateLength[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub014(0x000003c7U, 0x80040060U);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[0]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[2]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_CertificatePubKey[3]);
            r_rsip_func_sub018(0x00000000U, 0x0000b420U, 0x00000014U);
            WR1_PROG(REG_0094H, 0x00003c01U);

            WR1_PROG(REG_00F0H, 0x00000001U);

            WR1_PROG(REG_0094H, 0x000008e7U);

            r_rsip_func_sub010(0x38008800U, 0x00000003U, 0x00270000U);

            r_rsip_func_sub010(0x38008800U, 0x00000006U, 0x00270000U);

            r_rsip_func100(bswap_32big(0xaff0e09aU), bswap_32big(0xa0247f53U), bswap_32big(0xb87d921cU),
                           bswap_32big(0xf2ec9da4U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_00F4H, 0x00000050U);

                r_rsip_func_sub022(0x0000b400U, 0x0000001fU, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                r_rsip_func101(bswap_32big(0x216beda3U),
                               bswap_32big(0xe490d4e8U),
                               bswap_32big(0x9e8e7e28U),
                               bswap_32big(0x06fcbc36U));
            }
            else
            {
                WR1_PROG(REG_00F4H, 0x000000a0U);

                r_rsip_func_sub022(0x0000b400U, 0x0000002fU, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000002fU);

                r_rsip_func101(bswap_32big(0xe37d8a90U),
                               bswap_32big(0xa8e476ceU),
                               bswap_32big(0x854aab46U),
                               bswap_32big(0x1ab98ac0U));
            }

            r_rsip_func_sub022(0x3c0028a6U, 0x1000d0e0U, 0x00002425U);
            r_rsip_func_sub022(0x08002826U, 0x2000d0e0U, 0x3c002864U);
            r_rsip_func_sub022(0x1000d0e0U, 0x3c002885U, 0x1000d0e0U);

            r_rsip_func_sub022(0x00002403U, 0x08002804U, 0x2000d0e0U);

            WR1_PROG(REG_0094H, 0x3c0028c2U);
            r_rsip_func_sub010(0x1000d0e0U, 0x38000ce7U, 0x00A70000U);

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
                r_rsip_func_sub022(0x00000800U, 0x00003422U, 0x01836c01U);
                WR1_PROG(REG_0094H, 0x00036c21U);

                r_rsip_func_sub017(0x81020000U, 0x0000500aU);
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

                r_rsip_func_sub022(0x00003403U, 0x00046800U, 0x00026c00U);

                r_rsip_func_sub017(0x81010000U, 0x00005006U);
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

                r_rsip_func_sub016(0x38000801U, 0x00000080U, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub022(0x00003402U, 0x0000a400U, 0x00000003U);
                WR1_PROG(REG_0094H, 0x00026800U);

                r_rsip_func_sub017(0x81010000U, 0x00005006U);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                r_rsip_func_sub022(0x000034e1U, 0x00026ce7U, 0x00003040U);

                r_rsip_func_sub022(0x00000884U, 0x00003c04U, 0x0000b480U);
                WR1_PROG(REG_0094H, 0x00000014U);
                WR1_PROG(REG_0094H, 0x00003804U);

                r_rsip_func_sub010(0x38008800U, 0x00000003U, 0x00270000U);

                r_rsip_func_sub010(0x38008800U, 0x00000006U, 0x00270000U);

                r_rsip_func100(bswap_32big(0xc7f5aeaaU),
                               bswap_32big(0x04b49ec5U),
                               bswap_32big(0x97e786e0U),
                               bswap_32big(0x33d6998aU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_00B0H, 0x0000340eU);

                    iTemp = iLoop;
                    for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
                    {
                        r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
                        WR1_PROG(REG_002CH, InData_Certificate[iLoop]);
                        r_rsip_func_sub018(0x00000000U, 0x0000b480U, 0x00000004U);
                        WR1_PROG(REG_0094H, 0x00003c24U);

                        WR1_PROG(REG_0094H, 0x00000821U);

                        for (jLoop = 0U; jLoop < 4; jLoop++)
                        {
                            r_rsip_func_sub022(0x00002c20U, 0x01886c06U, 0x00086cc6U);

                            WR1_PROG(REG_0094H, 0x00003485U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            r_rsip_func_sub010(0x0000001fU, 0x3c0028e5U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x2c6c42a8U),
                                           bswap_32big(0x973a5491U),
                                           bswap_32big(0xdbab73a7U),
                                           bswap_32big(0x7282a763U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub016(0x3c002887U, 0x00000080U, 0x00270000U);

                                r_rsip_func100(bswap_32big(0xf05ad2a6U), bswap_32big(0x4fa4a9a4U),
                                               bswap_32big(0x1208e45eU), bswap_32big(0x624ac98aU));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x10c90005U);

                                    r_rsip_func101(bswap_32big(0x83e612a8U), bswap_32big(0x735c141fU),
                                                   bswap_32big(0xddd2066fU), bswap_32big(0x085023dbU));
                                }

                                r_rsip_func101(bswap_32big(0xcfb8357bU), bswap_32big(0x5b029d39U),
                                               bswap_32big(0x36eacbb3U), bswap_32big(0x566dcb8dU));
                            }

                            WR1_PROG(REG_0094H, 0x00003483U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            r_rsip_func_sub010(0x0000001fU, 0x3c0028e3U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0xd5b380adU),
                                           bswap_32big(0x7e910973U),
                                           bswap_32big(0x2dbfe3fdU),
                                           bswap_32big(0xc9fddc1dU));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub016(0x3c002887U, 0x00000080U, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x103746a6U), bswap_32big(0x0e7ea98dU),
                                               bswap_32big(0x6c7ac374U), bswap_32big(0x57739a33U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x10c90005U);

                                    r_rsip_func101(bswap_32big(0x1df858adU), bswap_32big(0x7787ad0cU),
                                                   bswap_32big(0xddf3a0afU), bswap_32big(0x5cb69bceU));
                                }

                                r_rsip_func101(bswap_32big(0x6bc1308bU), bswap_32big(0xf78eb84eU),
                                               bswap_32big(0x5f381b1fU), bswap_32big(0x24906095U));
                            }

                            r_rsip_func_sub016(0x3c002847U, 0x00000080U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x0dd43b75U),
                                           bswap_32big(0x29bcedeeU),
                                           bswap_32big(0x68641598U),
                                           bswap_32big(0x7759b498U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x11490005U);

                                r_rsip_func101(bswap_32big(0x1c8392b5U), bswap_32big(0x7ec909bdU),
                                               bswap_32big(0x96e4c82cU), bswap_32big(0xf8f126b8U));
                            }

                            WR1_PROG(REG_0094H, 0x00002ce0U);

                            r_rsip_func101(bswap_32big(0x8a50b8abU),
                                           bswap_32big(0xf5218864U),
                                           bswap_32big(0x531a5c81U),
                                           bswap_32big(0x6b1640b6U));
                        }

                        r_rsip_func_sub010(0x38008820U, 0x00000004U, 0x00270000U);
                        WR1_PROG(REG_0040H, 0x00402000U);

                        r_rsip_func_sub022(0x0000b480U, 0x00000004U, 0x00003824U);

                        WR1_PROG(REG_0094H, 0x00002c20U);

                        r_rsip_func101(bswap_32big(0x8685e0fbU),
                                       bswap_32big(0xddcdf3afU),
                                       bswap_32big(0x138e9c11U),
                                       bswap_32big(0xe2df3354U));
                    }

                    r_rsip_func101(bswap_32big(0x43dfa63dU),
                                   bswap_32big(0x5e23536dU),
                                   bswap_32big(0xc22b18d3U),
                                   bswap_32big(0x94103c8bU));
                }
                else
                {
                    WR1_PROG(REG_00B0H, 0x0000b412U);

                    iTemp = iLoop;
                    for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
                    {
                        r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
                        WR1_PROG(REG_002CH, InData_Certificate[iLoop]);
                        r_rsip_func_sub018(0x00000000U, 0x0000b480U, 0x00000004U);
                        WR1_PROG(REG_0094H, 0x00003c24U);

                        WR1_PROG(REG_0094H, 0x00000821U);

                        for (jLoop = 0U; jLoop < 4; jLoop++)
                        {
                            r_rsip_func_sub022(0x00002c20U, 0x01886c06U, 0x00086cc6U);

                            WR1_PROG(REG_0094H, 0x00003485U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            r_rsip_func_sub010(0x0000002fU, 0x3c0028e5U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x0d3d71a5U),
                                           bswap_32big(0xac4f972aU),
                                           bswap_32big(0xaa89f2e5U),
                                           bswap_32big(0x8e7bfcf9U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub016(0x3c002887U, 0x00000080U, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x4c3292bcU), bswap_32big(0xa5c4b018U),
                                               bswap_32big(0x3460f8adU), bswap_32big(0xda19ce77U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x10c90005U);

                                    r_rsip_func101(bswap_32big(0xec57dbb8U), bswap_32big(0x6cecb80cU),
                                                   bswap_32big(0x4de7f34aU), bswap_32big(0xe50bd1caU));
                                }

                                r_rsip_func101(bswap_32big(0x7cc124d7U), bswap_32big(0xad6fe4b6U),
                                               bswap_32big(0xb68db92bU), bswap_32big(0x3c4c5a99U));
                            }

                            WR1_PROG(REG_0094H, 0x00003483U);
                            WR1_PROG(REG_0094H, 0x0000a480U);
                            r_rsip_func_sub010(0x0000002fU, 0x3c0028e3U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0x92d99914U),
                                           bswap_32big(0xcfa00c23U),
                                           bswap_32big(0x75d1e01aU),
                                           bswap_32big(0xa6e35cb8U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub016(0x3c002887U, 0x00000080U, 0x00270000U);

                                r_rsip_func100(bswap_32big(0x893cd8ddU), bswap_32big(0x4bd0b087U),
                                               bswap_32big(0x3d04917eU), bswap_32big(0xaeee68e4U));
                                WR1_PROG(REG_0040H, 0x00400000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x10c90005U);

                                    r_rsip_func101(bswap_32big(0xa50484eaU), bswap_32big(0xef5eeae8U),
                                                   bswap_32big(0xfb12e840U), bswap_32big(0xba2fd16bU));
                                }

                                r_rsip_func101(bswap_32big(0x57751df3U), bswap_32big(0xe32dc4a8U),
                                               bswap_32big(0xd58ed526U), bswap_32big(0xa0fca902U));
                            }

                            r_rsip_func_sub016(0x3c002847U, 0x00000080U, 0x00270000U);

                            r_rsip_func100(bswap_32big(0xe5459920U),
                                           bswap_32big(0xe8e3c21aU),
                                           bswap_32big(0x21c07a9bU),
                                           bswap_32big(0x99668b66U));
                            WR1_PROG(REG_0040H, 0x00400000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func_sub005(0x81010000U, 0x1009000dU, 0x11490005U);

                                r_rsip_func101(bswap_32big(0xc6391ec9U), bswap_32big(0xe11f9b0dU),
                                               bswap_32big(0xb7baec9eU), bswap_32big(0xc6e69d88U));
                            }

                            WR1_PROG(REG_0094H, 0x00002ce0U);

                            r_rsip_func101(bswap_32big(0x3249f6e0U),
                                           bswap_32big(0x90f32da5U),
                                           bswap_32big(0x0f60d329U),
                                           bswap_32big(0xc65a44c4U));
                        }

                        r_rsip_func_sub010(0x38008820U, 0x00000004U, 0x00270000U);
                        WR1_PROG(REG_0040H, 0x00402000U);

                        r_rsip_func_sub022(0x0000b480U, 0x00000004U, 0x00003824U);

                        WR1_PROG(REG_0094H, 0x00002c20U);

                        r_rsip_func101(bswap_32big(0x6147ebc8U),
                                       bswap_32big(0x1b41b7a7U),
                                       bswap_32big(0x6d524e48U),
                                       bswap_32big(0x2de0fc9aU));
                    }

                    r_rsip_func101(bswap_32big(0x9f0a5a34U),
                                   bswap_32big(0x8f9ce52cU),
                                   bswap_32big(0x363f1443U),
                                   bswap_32big(0xc97a98ecU));
                }

                WR1_PROG(REG_0094H, 0x00000884U);
                r_rsip_func_sub010(0x00003804U, 0x38000801U, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                WR1_PROG(REG_0094H, 0x00002c40U);

                r_rsip_func100(bswap_32big(0x4341096cU),
                               bswap_32big(0x4a9f6947U),
                               bswap_32big(0xd8e368b3U),
                               bswap_32big(0x4200d728U));
                r_rsip_func_sub022(0x00003402U, 0x00008c00U, 0x00000003U);

                r_rsip_func_sub022(0x0000b440U, 0x00000004U, 0x00002840U);
                WR1_PROG(REG_0094H, 0x00008c40U);
                WR1_PROG(REG_0094H, 0x00000003U);

                r_rsip_func_sub017(0x81010040U, 0x00005006U);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x00000863U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    r_rsip_func_sub005(0x81010060U, 0x11490005U, 0x1009000dU);

                    WR1_PROG(REG_0094H, 0x00086c63U);

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xbed25e06U),
                                   bswap_32big(0x47e60b16U),
                                   bswap_32big(0x912900a2U),
                                   bswap_32big(0x71b3db40U));
                }

                r_rsip_func_sub016(0x38000845U, 0x00000080U, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub022(0x000008a5U, 0x00000800U, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000014U);
                WR1_PROG(REG_0094H, 0x00003881U);

                r_rsip_func_sub010(0x38008880U, 0x00000003U, 0x00270000U);

                r_rsip_func_sub010(0x38008880U, 0x00000006U, 0x00270000U);

                r_rsip_func100(bswap_32big(0xe84c22dfU),
                               bswap_32big(0x73acf52dU),
                               bswap_32big(0x73155f5fU),
                               bswap_32big(0xbecb750cU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_00B0H, 0x00001804U);

                    r_rsip_func101(bswap_32big(0x33147617U),
                                   bswap_32big(0x0eb3ae73U),
                                   bswap_32big(0x82ec591cU),
                                   bswap_32big(0xcc46c6d2U));
                }
                else
                {
                    WR1_PROG(REG_00B0H, 0x00009806U);

                    r_rsip_func101(bswap_32big(0x6c295c06U),
                                   bswap_32big(0x7839a15bU),
                                   bswap_32big(0x2dcc98e3U),
                                   bswap_32big(0x6e3aa7a0U));
                }

                r_rsip_func100(bswap_32big(0xa2d2b2fbU),
                               bswap_32big(0xa3b1e0b4U),
                               bswap_32big(0xe2b988fcU),
                               bswap_32big(0xe13a23abU));
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                r_rsip_func_sub017(0x81810001U, 0x00005006U);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    r_rsip_func_sub012(0x80010020U, 0x03450005U);

                    r_rsip_func_sub006(0x80010040U, 0x03430005U, 0x08002822U, 0x2000d000U);

                    WR1_PROG(REG_0094H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0x02ce80a1U),
                                   bswap_32big(0x88b2f6d5U),
                                   bswap_32big(0x1033c381U),
                                   bswap_32big(0x344ed354U));
                }

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                r_rsip_func_sub010(0x00003841U, 0x380008a2U, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub016(0x38000c00U, 0x00000080U, 0x00A70000U);

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

                    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

                    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

                    WR1_PROG(REG_0094H, 0x000034c0U);

                    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e102U, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x9b4a8adbU),
                                   bswap_32big(0x3ceae954U),
                                   bswap_32big(0x5a394240U),
                                   bswap_32big(0x2967cb53U));
                    r_rsip_func043();

                    r_rsip_func_sub010(0x38008880U, 0x00000003U, 0x00270000U);

                    r_rsip_func_sub010(0x38008880U, 0x00000006U, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x1fcf220bU),
                                   bswap_32big(0xca106d10U),
                                   bswap_32big(0xf632b84fU),
                                   bswap_32big(0x6b403828U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B0H, 0x0000380eU);

                        r_rsip_func_sub022(0x0000b460U, 0x00000010U, 0x38008880U);
                        r_rsip_func_sub022(0x00000003U, 0x00030020U, 0x0000b4c0U);
                        r_rsip_func_sub022(0x00000016U, 0x00000060U, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x0000001cU);
                        WR1_PROG(REG_0094H, 0x00000080U);

                        r_rsip_func101(bswap_32big(0x13a937a1U),
                                       bswap_32big(0x431fd20bU),
                                       bswap_32big(0xffc768b4U),
                                       bswap_32big(0xde37f80dU));
                    }
                    else
                    {
                        WR1_PROG(REG_00B0H, 0x0000b812U);

                        r_rsip_func_sub022(0x0000b460U, 0x00000018U, 0x38008880U);
                        r_rsip_func_sub022(0x00000004U, 0x00030020U, 0x0000b4c0U);
                        r_rsip_func_sub022(0x00000018U, 0x00000060U, 0x0000b4c0U);
                        WR1_PROG(REG_0094H, 0x0000001eU);
                        WR1_PROG(REG_0094H, 0x00000080U);

                        r_rsip_func101(bswap_32big(0xd9f57028U),
                                       bswap_32big(0x3f0e383aU),
                                       bswap_32big(0x01f0e1cbU),
                                       bswap_32big(0x7f1125b3U));
                    }

                    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e102U, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x4f671989U),
                                   bswap_32big(0x390d4985U),
                                   bswap_32big(0x6aa6f889U),
                                   bswap_32big(0x6841e466U));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0x401721d0U),
                                   bswap_32big(0xefb763c1U),
                                   bswap_32big(0x7389be75U),
                                   bswap_32big(0x9f73d05dU));
                    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

                    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

                    r_rsip_func_sub017(0x81010060U, 0x00005006U);
                    RD1_ADDR(REG_002CH, &S_RAM[0]);
                    S_RAM[0] = bswap_32big(S_RAM[0]);

                    WR1_PROG(REG_0094H, 0x00000884U);
                    WR1_PROG(REG_0094H, 0x000008a5U);

                    for (iLoop = 0U; iLoop < S_RAM[0]; )
                    {
                        r_rsip_func_sub022(0x342028a3U, 0x2000d080U, 0x00007c04U);
                        WR1_PROG(REG_0040H, 0x00602000U);

                        r_rsip_func100(bswap_32big(0xd5cb69e3U),
                                       bswap_32big(0xe4b78dc2U),
                                       bswap_32big(0x22ed3c2cU),
                                       bswap_32big(0xfe5e3710U));
                        r_rsip_func_sub004(0x40000000U, 0xe8008105U, 0x00430011U, 0x00001012U);
                        RD4_ADDR(REG_002CH, &OutData_KeyIndex[1 + iLoop]);

                        WR1_PROG(REG_0094H, 0x0000a4a0U);
                        WR1_PROG(REG_0094H, 0x00000004U);

                        r_rsip_func101(bswap_32big(0x533e6d1dU),
                                       bswap_32big(0xd55089e3U),
                                       bswap_32big(0xec52602aU),
                                       bswap_32big(0xadd17df8U));
                        iLoop = iLoop + 4U;
                    }

                    r_rsip_func_sub016(0x380008a3U, 0x00000080U, 0x00270000U);
                    WR1_PROG(REG_0040H, 0x00402000U);

                    r_rsip_func100(bswap_32big(0xcca0bc89U),
                                   bswap_32big(0xcdfff988U),
                                   bswap_32big(0xaa18b49fU),
                                   bswap_32big(0x28d8d258U));
                    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

                    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
                    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1 + iLoop]);

                    r_rsip_func100(bswap_32big(0x58db36e9U),
                                   bswap_32big(0xd502521dU),
                                   bswap_32big(0xe5150727U),
                                   bswap_32big(0x788099deU));
                    r_rsip_func_sub017(0x81010000U, 0x00005006U);
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
