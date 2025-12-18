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

rsip_ret_t r_rsip_pe6 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataLength[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e60001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub014(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    r_rsip_func_sub018(0x00000000U, 0x3000a880U, 0x00000002U);
    r_rsip_func_sub022(0x00010020U, 0x0000b480U, 0x00000001U);
    r_rsip_func_sub022(0x00000080U, 0x30003080U, 0x00070020U);
    r_rsip_func_sub022(0x0000b4c0U, 0x00000002U, 0x0000b4e0U);
    r_rsip_func_sub022(0x00000020U, 0x0000b460U, 0x0000000dU);

    r_rsip_func_sub022(0x00030040U, 0x0000b4c0U, 0x00000002U);

    r_rsip_func_sub022(0x0000b4e0U, 0x00000030U, 0x0000b460U);
    WR1_PROG(REG_0094H, 0x00000011U);

    WR1_PROG(REG_0094H, 0x00000080U);

    r_rsip_func_sub014(0x000000c7U, 0x800100a0U);
    WR1_PROG(REG_002CH, InData_KDFInfo_Count[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub016(0x38000ca5U, 0x00000080U, 0x00270000U);

    r_rsip_func_sub016(0x342028c5U, 0x00000080U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xe5ec0dcaU),
                   bswap_32big(0x2780ff22U),
                   bswap_32big(0xd00635dfU),
                   bswap_32big(0x362ef099U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x6bb5f127U), bswap_32big(0xa296ae1aU), bswap_32big(0x15a6bac7U),
                       bswap_32big(0x3a707823U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_002CH, InData_OutDataLength[0]);
        r_rsip_func_sub018(0x00000000U, 0x300030a0U, 0x00030020U);
        r_rsip_func_sub022(0x00003407U, 0x00000060U, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000040U);

        r_rsip_func_sub010(0x00000080U, 0x342028c7U, 0x00270000U);

        r_rsip_func_sub016(0x34202806U, 0x00000080U, 0x00270000U);

        r_rsip_func100(bswap_32big(0xc012fbedU), bswap_32big(0x9b018959U), bswap_32big(0x81d2566aU),
                       bswap_32big(0xef1d34c5U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xb32945d7U), bswap_32big(0xfd166179U), bswap_32big(0x14b7ec57U),
                           bswap_32big(0x626b774cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xd4363110U), bswap_32big(0x4e77a98fU), bswap_32big(0xf430223cU),
                           bswap_32big(0x94876894U));
            r_rsip_func_sub017(0x810100a0U, 0x00005006U);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func100(bswap_32big(0xdacf15eeU), bswap_32big(0x6ff4f7ccU), bswap_32big(0x9788dbacU),
                           bswap_32big(0x1927b51fU));
            r_rsip_func_sub017(0x81010060U, 0x00005006U);
            RD1_ADDR(REG_002CH, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);
            OFS_ADR      = S_RAM[0 + 1];

            r_rsip_func_sub022(0x0000b420U, 0x00000010U, 0x00003cc1U);

            WR1_PROG(REG_0094H, 0x00000800U);

            WR1_PROG(REG_0094H, 0x00000821U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
                WR1_PROG(REG_002CH, InData_KDFInfo[iLoop * OFS_ADR]);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e601U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x6b7cfc01U),
                               bswap_32big(0x3750d0b5U),
                               bswap_32big(0x6282f63fU),
                               bswap_32big(0x318b8e33U));
                r_rsip_func143();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x01799093U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e601U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x7b253539U),
                               bswap_32big(0x8dc7f369U),
                               bswap_32big(0xa8766b9dU),
                               bswap_32big(0x095069aeU));
                r_rsip_func044();

                r_rsip_func_sub016(0x38000c00U, 0x00000080U, 0x00270000U);

                r_rsip_func100(bswap_32big(0xe91b3608U),
                               bswap_32big(0xb4ceba4aU),
                               bswap_32big(0x6dcab603U),
                               bswap_32big(0x32206278U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func_sub016(0x38000c84U, 0x00000080U, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x920b9ae2U),
                                   bswap_32big(0x000c4c1aU),
                                   bswap_32big(0x5b8a7dbeU),
                                   bswap_32big(0xda5cf7fbU));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B0H, 0x00001404U);

                        r_rsip_func101(bswap_32big(0x65f94618U),
                                       bswap_32big(0xbdf3f95cU),
                                       bswap_32big(0x5ffb0201U),
                                       bswap_32big(0x1a9975a0U));
                    }
                    else
                    {
                        WR1_PROG(REG_00B0H, 0x00009406U);

                        r_rsip_func101(bswap_32big(0x7000c6f0U),
                                       bswap_32big(0x2e2c4109U),
                                       bswap_32big(0x03705da5U),
                                       bswap_32big(0x1acd3808U));
                    }

                    r_rsip_func101(bswap_32big(0x0cf54ac8U),
                                   bswap_32big(0x1fc434daU),
                                   bswap_32big(0x29c0226eU),
                                   bswap_32big(0xbeb06bf6U));
                }
                else
                {
                    r_rsip_func_sub016(0x38000c84U, 0x00000080U, 0x00270000U);

                    r_rsip_func100(bswap_32big(0x6960ac90U),
                                   bswap_32big(0xc044445dU),
                                   bswap_32big(0xde1f8d8cU),
                                   bswap_32big(0xbd6d2a43U));
                    WR1_PROG(REG_0040H, 0x00400000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_00B0H, 0x00001408U);

                        r_rsip_func101(bswap_32big(0xc9f3a486U),
                                       bswap_32big(0x1dccf58bU),
                                       bswap_32big(0xcfc00ebbU),
                                       bswap_32big(0x10b17844U));
                    }
                    else
                    {
                        WR1_PROG(REG_00B0H, 0x0000940cU);

                        r_rsip_func101(bswap_32big(0xf9ceb581U),
                                       bswap_32big(0xda5c064aU),
                                       bswap_32big(0x47d5a108U),
                                       bswap_32big(0xc9428710U));
                    }

                    r_rsip_func101(bswap_32big(0x0e5b3fa4U),
                                   bswap_32big(0xac73c438U),
                                   bswap_32big(0xcb1d143eU),
                                   bswap_32big(0xd449e5e1U));
                }

                r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

                r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00000842U);

                for (jLoop = 0U; jLoop < OFS_ADR - 5; )
                {
                    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7008d05U);
                    WR4_ADDR(REG_002CH, &InData_KDFInfo[1 + jLoop + iLoop * OFS_ADR]);

                    r_rsip_func_sub015(0x00c10011U, 0x00001800U);

                    WR1_PROG(REG_0094H, 0x0000a440U);
                    WR1_PROG(REG_0094H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0x04f02334U),
                                   bswap_32big(0xf3eeb659U),
                                   bswap_32big(0x7f6a5a94U),
                                   bswap_32big(0x0ddd5d22U));
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_0094H, 0x000034e3U);
                WR1_PROG(REG_0094H, 0x0000a8e0U);
                r_rsip_func_sub010(0x00000005U, 0x380008e2U, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
                WR4_ADDR(REG_002CH, &InData_KDFInfo[1 + jLoop + iLoop * OFS_ADR]);

                r_rsip_func_sub013(0x9c100005U, 0x00410011U);

                WR1_PROG(REG_0094H, 0x00002c00U);

                r_rsip_func100(bswap_32big(0xbd74762fU),
                               bswap_32big(0x3bbc01dcU),
                               bswap_32big(0xa312c77eU),
                               bswap_32big(0x54200f04U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x0000d020U);
                    r_rsip_func101(bswap_32big(0x421a232bU),
                                   bswap_32big(0x2fd6f40aU),
                                   bswap_32big(0x6c3e30ecU),
                                   bswap_32big(0x37476abdU));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0xf0b33e76U),
                                   bswap_32big(0x40555238U),
                                   bswap_32big(0x35a32b5bU),
                                   bswap_32big(0xfa6f4184U));
                }
            }

            r_rsip_func_sub016(0x38000805U, 0x00000080U, 0x00270000U);
            WR1_PROG(REG_0040H, 0x00402000U);

            r_rsip_func_sub016(0x38000c21U, 0x00000080U, 0x00A70000U);
            r_rsip_func100(bswap_32big(0xa3e563c0U), bswap_32big(0xea6f48d4U), bswap_32big(0xc519a9eaU),
                           bswap_32big(0xd791c018U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x10318d2fU),
                               bswap_32big(0xdd92a44bU),
                               bswap_32big(0x6d0fd1e5U),
                               bswap_32big(0xc2726e9aU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func_sub022(0x0000b420U, 0x00000010U, 0x000038a1U);

                r_rsip_func100(bswap_32big(0x92ffc950U),
                               bswap_32big(0x37be238dU),
                               bswap_32big(0x18542c72U),
                               bswap_32big(0x9bc75d04U));
                r_rsip_func_sub017(0x810100a0U, 0x00005006U);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                r_rsip_func100(bswap_32big(0xbb8c5a6eU),
                               bswap_32big(0x1167fa79U),
                               bswap_32big(0xccbf1a5eU),
                               bswap_32big(0x909b8ad7U));
                r_rsip_func103();

                r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

                r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

                WR1_PROG(REG_0094H, 0x000034c0U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e602U, 0x00000000U);

                r_rsip_func101(bswap_32big(0xc329dd9eU),
                               bswap_32big(0xc13788a8U),
                               bswap_32big(0x37443eecU),
                               bswap_32big(0xf7bf8cdcU));
                r_rsip_func143();

                r_rsip_func_sub022(0x30003080U, 0x00070020U, 0x0000b4c0U);
                r_rsip_func_sub022(0x01b41ce9U, 0x00000060U, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x0199f119U);
                WR1_PROG(REG_0094H, 0x00000080U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e602U, 0x00000000U);

                r_rsip_func101(bswap_32big(0xe64842b8U),
                               bswap_32big(0x7e530998U),
                               bswap_32big(0x10c8f23cU),
                               bswap_32big(0xffded45aU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x5639f7d4U),
                               bswap_32big(0x810bbe8fU),
                               bswap_32big(0x4583cf06U),
                               bswap_32big(0x47d5f355U));
                WR1_PROG(REG_00B0H, 0x00001804U);
                r_rsip_func_sub004(0x40000100U, 0xe7009d07U, 0x00430021U, 0x00001022U);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

                WR1_PROG(REG_0094H, 0x000008e7U);

                r_rsip_func_sub010(0x3420a8a0U, 0x00000021U, 0x00A70000U);

                r_rsip_func100(bswap_32big(0xf8a2a8a8U),
                               bswap_32big(0xc6448393U),
                               bswap_32big(0xa924f5abU),
                               bswap_32big(0xfd8c5095U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_00B0H, 0x00001808U);
                    r_rsip_func_sub012(0x80880007U, 0x03430021U);

                    r_rsip_func101(bswap_32big(0x2f66ecc2U),
                                   bswap_32big(0x639efe51U),
                                   bswap_32big(0x77ea4eaeU),
                                   bswap_32big(0x44aef080U));
                }

                r_rsip_func_sub022(0x00000842U, 0x0000b460U, 0x00000040U);
                r_rsip_func_sub022(0x00002865U, 0x00000884U, 0x00003425U);
                WR1_PROG(REG_0094H, 0x0000a820U);
                WR1_PROG(REG_0094H, 0x00000020U);

                for (iLoop = S_RAM[0]; iLoop < 64U; iLoop++)
                {
                    r_rsip_func_sub022(0x02003c41U, 0x00002c80U, 0x00002c20U);
                    r_rsip_func101(bswap_32big(0x04f984eeU),
                                   bswap_32big(0x831a97beU),
                                   bswap_32big(0x5fe82ca6U),
                                   bswap_32big(0x4b468e65U));
                }

                r_rsip_func_sub016(0x38000883U, 0x00000080U, 0x00270000U);
                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func100(bswap_32big(0x9bcfecd4U),
                               bswap_32big(0xd7823c5eU),
                               bswap_32big(0x47c32057U),
                               bswap_32big(0x595756d0U));
                WR1_PROG(REG_0094H, 0x000008e7U);
                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xe7008d07U);

                r_rsip_func_sub012(0x81880007U, 0x00490021U);
                WR1_PROG(REG_0008H, 0x00001022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

                r_rsip_func100(bswap_32big(0x2d80dfe5U),
                               bswap_32big(0x4bc52bd5U),
                               bswap_32big(0x35f98944U),
                               bswap_32big(0x475644a0U));
                r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

                r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
                RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

                r_rsip_func100(bswap_32big(0x58635cf9U),
                               bswap_32big(0xdee4c7e3U),
                               bswap_32big(0x85d79befU),
                               bswap_32big(0x51ac3f10U));
                r_rsip_func_sub017(0x81010000U, 0x00005006U);
                RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                r_rsip_func102(bswap_32big(0xfbbf594bU),
                               bswap_32big(0xf6796c01U),
                               bswap_32big(0x543777e0U),
                               bswap_32big(0x39355c57U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
