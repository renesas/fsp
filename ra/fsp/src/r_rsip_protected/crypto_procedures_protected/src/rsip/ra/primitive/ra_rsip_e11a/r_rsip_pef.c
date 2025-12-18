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

rsip_ret_t r_rsip_pef (const uint32_t InData_InitVal[],
                       const uint32_t InData_Msg1[],
                       const uint32_t InData_Msg1Length[],
                       const uint32_t InData_EncMsg[],
                       const uint32_t InData_EncMsgLength[],
                       const uint32_t InData_Msg2[],
                       const uint32_t InData_Msg2Length[],
                       const uint32_t InData_OutDataType[],
                       uint32_t       OutData_MsgDigest[],
                       uint32_t       OutData_KDFInfo[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00ef0001U, 0x000003c7U, 0x80040040U);
    WR1_PROG(REG_002CH, InData_OutDataType[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg1Length[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg2Length[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub016(0x3420a840U, 0x00000002U, 0x2000b440U);
    WR1_PROG(REG_0094H, 0x00000001U);

    r_rsip_func_sub007(0x38008c80U, 0xffffffdfU, 0x00A60000U);

    r_rsip_func_sub007(0x3420a8a0U, 0x00000009U, 0x00260000U);

    r_rsip_func_sub016(0x00000800U, 0x00002403U, 0x00002404U);
    WR1_PROG(REG_0094H, 0x00002405U);

    r_rsip_func_sub007(0x38008c00U, 0x0000003fU, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x696ca684U),
                   bswap_32big(0x704fd1ceU),
                   bswap_32big(0x8647501eU),
                   bswap_32big(0x48458f0aU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x14db3da2U), bswap_32big(0x0d170b37U), bswap_32big(0x7ac66831U),
                       bswap_32big(0xab5d72f3U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub016(0x0000b420U, 0x00000010U, 0x00003c41U);

        WR1_PROG(REG_0094H, 0x00000821U);

        r_rsip_func_sub007(0x00003405U, 0x38000c84U, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x4481ba76U), bswap_32big(0x393be736U), bswap_32big(0x735aef59U),
                       bswap_32big(0xf41bd278U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x800100e0U, 0x0000ef01U);

            r_rsip_func101(bswap_32big(0x332a6c34U), bswap_32big(0xf0a54f52U), bswap_32big(0xa5229163U),
                           bswap_32big(0x70502948U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            r_rsip_func_sub002(0x800100e0U, 0x0000ef01U);

            r_rsip_func101(bswap_32big(0x7d0efc43U), bswap_32big(0x15efe684U), bswap_32big(0x29c3d9cbU),
                           bswap_32big(0xc31017d6U));
            r_rsip_func044();

            r_rsip_func_sub008(0x000007c1U, 0x40000100U, 0xf7009d07U);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncMsg[5]);

            r_rsip_func_sub004(0x00001404U, 0x00c10021U);

            r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_EncMsg[9]);

            r_rsip_func_sub006(0x9c100005U, 0x00410011U);

            r_rsip_func100(bswap_32big(0x3e268571U), bswap_32big(0x4418e672U), bswap_32big(0x24651cdaU),
                           bswap_32big(0xc631e030U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0x53e9821eU),
                               bswap_32big(0xe29359c2U),
                               bswap_32big(0xefff844eU),
                               bswap_32big(0x3a60df2cU));
            }

            r_rsip_func101(bswap_32big(0xdc6aac19U), bswap_32big(0x3670fbeaU), bswap_32big(0xe257baabU),
                           bswap_32big(0x0a90a920U));
        }

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x7da5a0eaU), bswap_32big(0xa6fd16e0U), bswap_32big(0x1b2f935fU),
                       bswap_32big(0x2fd43e0fU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x60afac5cU), bswap_32big(0xeb8418a2U), bswap_32big(0xd69ec92fU),
                           bswap_32big(0x38f68456U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_00F4H, 0x00000010U);

            WR1_PROG(REG_0014H, 0x000007c4U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_InitVal[0]);

            WR1_PROG(REG_00F4H, 0x00000011U);

            WR1_PROG(REG_0094H, 0x00000821U);

            r_rsip_func_sub007(0x00003c01U, 0x38000c63U, 0x00A60000U);

            r_rsip_func100(bswap_32big(0xb980043fU), bswap_32big(0xd69b0853U), bswap_32big(0xaf720807U),
                           bswap_32big(0x2d8d8e78U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0x1e05cf35U),
                               bswap_32big(0xf62dc2fbU),
                               bswap_32big(0x82aafce6U),
                               bswap_32big(0x8c985fc7U));

                r_rsip_func_sub016(0x00000800U, 0x00003443U, 0x0000a440U);
                WR1_PROG(REG_0094H, 0x00000003U);
                r_rsip_func_sub015(0x00026842U, 0x81010040U, 0x00005006U);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x000008c6U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0014H, 0x000000c7U);
                    WR1_PROG(REG_009CH, 0x80010020U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, InData_Msg1[iLoop]);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x000008e7U);

                    for (jLoop = 0U; jLoop < 4; jLoop++)
                    {
                        WR1_PROG(REG_0094H, 0x01886c01U);
                        r_rsip_func_sub007(0x00086c21U, 0x342028a3U, 0x00260000U);
                        r_rsip_func100(bswap_32big(0xef3f4551U),
                                       bswap_32big(0xbc5b3433U),
                                       bswap_32big(0x90f75e47U),
                                       bswap_32big(0x2072ca2dU));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            r_rsip_func_sub003(0x81010000U, 0x1009000dU);
                            r_rsip_func_sub009(0x11490005U, 0x00002ca0U);
                            r_rsip_func101(bswap_32big(0x3990559eU),
                                           bswap_32big(0x4e4baaf0U),
                                           bswap_32big(0x6b5f1a49U),
                                           bswap_32big(0x3fc5e7bcU));
                        }

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0x15532271U),
                                       bswap_32big(0x88991257U),
                                       bswap_32big(0x551aeab2U),
                                       bswap_32big(0x95c69f47U));
                    }

                    r_rsip_func_sub007(0x380088e0U, 0x00000004U, 0x00260000U);
                    WR1_PROG(REG_0040H, 0x00402000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0xd2f1c8acU),
                                   bswap_32big(0xef8d15c8U),
                                   bswap_32big(0xff7cf5cfU),
                                   bswap_32big(0xfb879120U));
                }

                r_rsip_func_sub010(0x380008c2U);

                r_rsip_func101(bswap_32big(0x3d3520d1U),
                               bswap_32big(0x11ba7f6aU),
                               bswap_32big(0x380a503cU),
                               bswap_32big(0x2ade55eeU));
            }

            WR1_PROG(REG_0094H, 0x38000c84U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x6823b52dU), bswap_32big(0x76b0d997U), bswap_32big(0xed0e9469U),
                           bswap_32big(0xfcfca565U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func_sub004(0x00001804U, 0x11430081U);

                r_rsip_func101(bswap_32big(0xbf0375d5U),
                               bswap_32big(0x21774b1aU),
                               bswap_32big(0x695dfa15U),
                               bswap_32big(0xba75648bU));
            }

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_0094H, 0x00003861U);

            r_rsip_func100(bswap_32big(0xde8d8373U), bswap_32big(0xe1285f51U), bswap_32big(0xedbf96f8U),
                           bswap_32big(0xebc2eb7eU));

            r_rsip_func_sub016(0x00000800U, 0x00003443U, 0x0000a440U);
            WR1_PROG(REG_0094H, 0x00000003U);
            r_rsip_func_sub015(0x00026842U, 0x81010040U, 0x00005006U);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x000008c6U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_0014H, 0x000000c7U);
                WR1_PROG(REG_009CH, 0x80010020U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Msg2[iLoop]);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x000008e7U);

                for (jLoop = 0U; jLoop < 4; jLoop++)
                {
                    WR1_PROG(REG_0094H, 0x01886c01U);
                    r_rsip_func_sub007(0x00086c21U, 0x342028a3U, 0x00260000U);
                    r_rsip_func100(bswap_32big(0x802fd208U),
                                   bswap_32big(0x852a16bbU),
                                   bswap_32big(0x6222a4b9U),
                                   bswap_32big(0xee57f4a1U));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func_sub003(0x81010000U, 0x1009000dU);
                        r_rsip_func_sub009(0x11490005U, 0x00002ca0U);
                        r_rsip_func101(bswap_32big(0x9ab12738U),
                                       bswap_32big(0xd9cf92fbU),
                                       bswap_32big(0xba45b3bcU),
                                       bswap_32big(0x04049f16U));
                    }

                    WR1_PROG(REG_0094H, 0x00002ce0U);

                    r_rsip_func101(bswap_32big(0x083b4bf2U),
                                   bswap_32big(0xa47d2036U),
                                   bswap_32big(0x675b04c9U),
                                   bswap_32big(0xbbd48ccbU));
                }

                r_rsip_func_sub007(0x380088e0U, 0x00000004U, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002cc0U);

                r_rsip_func101(bswap_32big(0xc7318646U),
                               bswap_32big(0x210e9c83U),
                               bswap_32big(0xf2b77dd2U),
                               bswap_32big(0x25f498cfU));
            }

            r_rsip_func_sub010(0x380008c2U);

            WAIT_STS(REG_00F8H, 2, 0);

            WR1_PROG(REG_00F4H, 0x00000100U);

            WR1_PROG(REG_0040H, 0x00001600U);

            WR1_PROG(REG_00F4H, 0x00000020U);

            WR1_PROG(REG_0094H, 0x0000b400U);
            WR1_PROG(REG_0094H, 0x00000010U);
            r_rsip_func_sub007(0x00003820U, 0x38000c21U, 0x00260000U);

            r_rsip_func100(bswap_32big(0xe51c62b4U), bswap_32big(0x45798338U), bswap_32big(0xc0a5abcfU),
                           bswap_32big(0x89534c8bU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0xe0e1d800U),
                               bswap_32big(0x00766ab0U),
                               bswap_32big(0x7ea2ddcdU),
                               bswap_32big(0x5c42921fU));

                WR1_PROG(REG_0008H, 0x00004022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD8_ADDR(REG_002CH, &OutData_MsgDigest[0]);

                r_rsip_func102(bswap_32big(0xcbc2cd77U),
                               bswap_32big(0x11d02e6eU),
                               bswap_32big(0x46567163U),
                               bswap_32big(0x5b3128efU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x4cb6659eU),
                               bswap_32big(0x07626121U),
                               bswap_32big(0x44d7c138U),
                               bswap_32big(0xb702f23aU));
                r_rsip_func103();

                r_rsip_func_sub005(0x000000a1U, 0x0c200104U, 0x00000000U);

                r_rsip_func_sub003(0x80010000U, 0x03410005U);
                r_rsip_func_sub009(0x0001000dU, 0x000034c0U);

                r_rsip_func_sub002(0x800100e0U, 0x0000ef02U);

                r_rsip_func101(bswap_32big(0x51f49093U),
                               bswap_32big(0x41eb4ea6U),
                               bswap_32big(0x1a716e88U),
                               bswap_32big(0x155c6dc8U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x01799093U);

                r_rsip_func_sub002(0x800100e0U, 0x0000ef02U);

                r_rsip_func101(bswap_32big(0x5ed5a8e2U),
                               bswap_32big(0x5dff1c45U),
                               bswap_32big(0xa435e196U),
                               bswap_32big(0xd7acc765U));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0xfc3c89afU),
                               bswap_32big(0xac7169caU),
                               bswap_32big(0x71547106U),
                               bswap_32big(0x5f554f0fU));
                r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

                r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

                WR1_PROG(REG_00D4H, 0x40000100U);
                r_rsip_func_sub006(0xe7009d07U, 0x00450021U);

                WR1_PROG(REG_0008H, 0x00001022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[5]);

                r_rsip_func100(bswap_32big(0x03cb5bc7U),
                               bswap_32big(0x4db758ebU),
                               bswap_32big(0x204f610cU),
                               bswap_32big(0x8d6b6577U));
                r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

                WR1_PROG(REG_00D4H, 0x40000000U);
                r_rsip_func_sub006(0x09108105U, 0x00410011U);

                WR1_PROG(REG_0008H, 0x00001012U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_KDFInfo[9]);

                r_rsip_func100(bswap_32big(0x7a7c257fU),
                               bswap_32big(0x7228db43U),
                               bswap_32big(0xdbd827c7U),
                               bswap_32big(0x3316f326U));
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_KDFInfo[0]);

                r_rsip_func102(bswap_32big(0xe31084a9U),
                               bswap_32big(0xf8f3f4e3U),
                               bswap_32big(0xcf71bfaaU),
                               bswap_32big(0x94b9f8f8U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
