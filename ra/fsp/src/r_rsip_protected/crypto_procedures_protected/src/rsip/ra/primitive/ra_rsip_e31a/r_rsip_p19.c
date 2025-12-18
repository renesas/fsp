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

rsip_ret_t r_rsip_p19 (const uint32_t InData_KeyIndex[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[],
                       uint64_t       MAX_CNT)
{
    uint64_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00190001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x20010000U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000019U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0f0d3397U),
                   bswap_32big(0x458a50b8U),
                   bswap_32big(0x84aa032fU),
                   bswap_32big(0x5d20cc8cU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000026U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000019U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x9fd74482U),
                   bswap_32big(0xc5c9ccfaU),
                   bswap_32big(0xa89ec4f6U),
                   bswap_32big(0x76eb2134U));
    r_rsip_func044();

    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func_sub011(0x000007c1U, 0x40000100U, 0xe8008107U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    r_rsip_func_sub009(0x000014a5U, 0x00c10021U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x73ce6d10U),
                   bswap_32big(0xbc0635b0U),
                   bswap_32big(0xa670a9a0U),
                   bswap_32big(0x51b718bfU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x2671071dU), bswap_32big(0x2a307c53U), bswap_32big(0xcddd21c6U),
                       bswap_32big(0x36fa000eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000001c7U, 0x80020000U);
        WR1_PROG(REG_002CH, InData_MsgLen[0]);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_MsgLen[1]);
        r_rsip_func_sub018(0x00000000U, 0x00000842U, 0x30008800U);
        r_rsip_func_sub022(0xffffffffU, 0x00030020U, 0x3000a820U);
        r_rsip_func_sub022(0xfffffdffU, 0x00050020U, 0x1000d040U);
        WR1_PROG(REG_0094H, 0x00000080U);
        WR1_PROG(REG_0094H, 0x00000080U);

        r_rsip_func_sub010(0x38008840U, 0x00000001U, 0x00270000U);

        r_rsip_func100(bswap_32big(0x7e714825U), bswap_32big(0x3ae71774U), bswap_32big(0x3ad489a6U),
                       bswap_32big(0x6c1cbef4U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xdb3c3ba0U), bswap_32big(0xf2fef98dU), bswap_32big(0x62096c92U),
                           bswap_32big(0xcecd49fcU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000007c5U);
            WR1_PROG(REG_00B0H, 0x0000149bU);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_Signature[0]);

            r_rsip_func100(bswap_32big(0x3308c6e1U), bswap_32big(0x9846b4e6U), bswap_32big(0x69281908U),
                           bswap_32big(0x1a0b3131U));
            r_rsip_func_sub022(0x00000842U, 0x0c00a420U, 0x00000200U);
            WR1_PROG(REG_0094H, 0x00802402U);

            r_rsip_func_sub017(0x81020000U, 0x0000500aU);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

            WR1_PROG(REG_00F0H, 0x00000001U);

            WR1_PROG(REG_00F4H, 0x000000b0U);

            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0104H, S_RAM[0]);
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0100H, S_RAM[0 + 1]);

            r_rsip_func_sub009(0x0000189bU, 0x01430021U, 0x00001800U);

            r_rsip_func_sub009(0x000018a5U, 0x01430021U, 0x00001800U);

            WR1_PROG(REG_0014H, 0x00020064U);

            for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffffffffffff0U); )
            {
                WAIT_STS(REG_0014H, 31, 1);
                WR16_ADDR(REG_002CH, &InData_Msg[iLoop]);
                iLoop = iLoop + 16U;
            }

            WAIT_STS(REG_0014H, 31, 1);
            for (iLoop = (MAX_CNT & 0xfffffffffffffff0U); iLoop < MAX_CNT; iLoop++)
            {
                WR1_PROG(REG_002CH, InData_Msg[iLoop]);
            }

            WR1_PROG(REG_0014H, 0x00000000U);

            WAIT_STS(REG_0118H, 4, 1);

            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub007(0x00000842U, 0x80880001U, 0x03450021U);

            r_rsip_func409();

            WR1_PROG(REG_00B0H, 0x000014afU);
            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub006(0x81880001U, 0x00c90021U, 0x00000821U, 0x00000842U);
            r_rsip_func_sub012(0x80880001U, 0x03450021U);

            r_rsip_func409();

            WR1_PROG(REG_00B0H, 0x000014aaU);
            r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00c90021U);

            r_rsip_func406(InData_DomainParam);

            r_rsip_func_sub009(0x00001487U, 0x00c00021U, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000841U);
            r_rsip_func_sub012(0x80020000U, 0x03430009U);
            WR1_PROG(REG_00B0H, 0x000004b1U);
            r_rsip_func_sub012(0x81020000U, 0x00c90009U);

            WR1_PROG(REG_00B0H, 0x00001423U);
            WR1_PROG(REG_0014H, 0x000007a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x0EEC73D2U),
                     bswap_32big(0x17F5BE65U),
                     bswap_32big(0xCB5C63AAU),
                     bswap_32big(0x97A331B5U));
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x0665E1DBU),
                     bswap_32big(0x6EABA043U),
                     bswap_32big(0xF98B4BAAU),
                     bswap_32big(0x9C78F954U));

            r_rsip_func_sub001(0x00aa0023U, 0x0028000aU, 0x04040002U);

            r_rsip_func_sub001(0x001e00afU, 0x0023000aU, 0x04040002U);

            r_rsip_func_sub003(0x00001482U, 0x00c0001dU, 0x00000001U);

            r_rsip_func_sub001(0x00820023U, 0x003c000aU, 0x04040002U);

            r_rsip_func_sub001(0x0028003cU, 0x00a0000aU, 0x04040005U);

            WR1_PROG(REG_0094H, 0x00000821U);

            WR1_PROG(REG_00B0H, 0x000018a5U);
            r_rsip_func_sub012(0x80880001U, 0x03430021U);

            r_rsip_func409();

            r_rsip_func100(bswap_32big(0xe39784e4U), bswap_32big(0xe65df4bfU), bswap_32big(0xdbbbbae0U),
                           bswap_32big(0x3048af6fU));

            r_rsip_func_sub022(0x00000800U, 0x00000821U, 0x02003801U);
            r_rsip_func_sub022(0x00003440U, 0x00076800U, 0x00003460U);

            r_rsip_func_sub022(0x00008c40U, 0x0000007FU, 0x02003c41U);

            WR1_PROG(REG_0094H, 0x00000800U);
            WR1_PROG(REG_009CH, 0x81880000U);

            r_rsip_func_sub009(0x00001423U, 0x00c90021U, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000840U);
            r_rsip_func_sub012(0x80020000U, 0x03430009U);
            WR1_PROG(REG_00B0H, 0x000004b1U);
            r_rsip_func_sub012(0x81020000U, 0x00c90009U);

            r_rsip_func_sub001(0x00190023U, 0x004b0005U, 0x04040002U);

            r_rsip_func_sub001(0x004b004bU, 0x00230005U, 0x04040002U);

            r_rsip_func_sub003(0x00001482U, 0x00c0001dU, 0x00000001U);

            r_rsip_func_sub001(0x00820019U, 0x00280005U, 0x04040002U);

            r_rsip_func_sub001(0x00280023U, 0x002d0005U, 0x04040006U);

            r_rsip_func_sub001(0x00140023U, 0x00370005U, 0x04040002U);

            r_rsip_func_sub001(0x00280037U, 0x00320005U, 0x04040005U);

            r_rsip_func_sub001(0x00820032U, 0x00230005U, 0x04040002U);

            r_rsip_func_sub003(0x00001428U, 0x00c0001dU, 0x00000002U);

            r_rsip_func_sub001(0x00280005U, 0x003c0005U, 0x04040006U);

            r_rsip_func_sub021(0x003c0023U, 0x00280005U, 0x04040000U);
            r_rsip_func_sub020(0x20010001U, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func100(bswap_32big(0x55cdd456U), bswap_32big(0x28b5898bU), bswap_32big(0xcf29fb95U),
                           bswap_32big(0x1d040b0dU));
            r_rsip_func_sub001(0x0028002dU, 0x00370005U, 0x04040002U);

            WR1_PROG(REG_00B0H, 0x00001423U);
            WR1_PROG(REG_0014H, 0x000007a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0x0FFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU));
            WAIT_STS(REG_0014H, 31, 1);
            WR4_PROG(REG_002CH,
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFFU),
                     bswap_32big(0xFFFFFFFEU));

            r_rsip_func_sub021(0x00230037U, 0x003c0005U, 0x04040000U);
            r_rsip_func_sub020(0x20010001U, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func_sub001(0x0019003cU, 0x002d0005U, 0x04040002U);

            r_rsip_func_sub001(0x002d002dU, 0x00320005U, 0x04040002U);

            r_rsip_func_sub001(0x00820032U, 0x002d0005U, 0x04040002U);

            r_rsip_func_sub001(0x00370005U, 0x00230005U, 0x04040006U);

            r_rsip_func_sub001(0x0037002dU, 0x00820000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func_sub001(0x002d0037U, 0x00820000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0x2cc4c86eU), bswap_32big(0x8ff9a6a5U), bswap_32big(0xd96bad3cU),
                           bswap_32big(0xe5bc6fd8U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func_sub001(0x0023002dU, 0x00820000U, 0x0404000aU);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func_sub001(0x002d0023U, 0x00820000U, 0x0404000aU);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0xb52f2076U),
                               bswap_32big(0xbce5bfaeU),
                               bswap_32big(0x9d3797f9U),
                               bswap_32big(0x891b2ec0U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    WR1_PROG(REG_0094H, 0x00000800U);

                    r_rsip_func101(bswap_32big(0xb40f8d17U),
                                   bswap_32big(0x5b88d5c6U),
                                   bswap_32big(0xa5b6d5c7U),
                                   bswap_32big(0x3c92de46U));
                }
                else
                {
                    r_rsip_func_sub001(0x0019003cU, 0x00230005U, 0x04040002U);

                    WR1_PROG(REG_00B0H, 0x00001428U);
                    WR1_PROG(REG_0014H, 0x000007a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_PROG(REG_002CH,
                             bswap_32big(0x2B832480U),
                             bswap_32big(0x4FC1DF0BU),
                             bswap_32big(0x2B4D0099U),
                             bswap_32big(0x3DFBD7A7U));
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_PROG(REG_002CH,
                             bswap_32big(0x2F431806U),
                             bswap_32big(0xAD2FE478U),
                             bswap_32big(0xC4EE1B27U),
                             bswap_32big(0x4A0EA0B0U));

                    r_rsip_func_sub001(0x00280023U, 0x003c0005U, 0x04040002U);

                    WR1_PROG(REG_0094H, 0x0000b400U);
                    WR1_PROG(REG_0094H, 0xed08d7a1U);

                    r_rsip_func101(bswap_32big(0xea6935a5U),
                                   bswap_32big(0x33caa60bU),
                                   bswap_32big(0xeecf48fbU),
                                   bswap_32big(0x1119a6e1U));
                }
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0xed08d7a1U);

                r_rsip_func101(bswap_32big(0xe9d49363U),
                               bswap_32big(0xf2937847U),
                               bswap_32big(0x9af30eb1U),
                               bswap_32big(0x54dbb3dfU));
            }

            r_rsip_func_sub010(0x38008800U, 0xed08d7a1U, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xb9561ebbU), bswap_32big(0xf4c9ba3dU), bswap_32big(0x9974816fU),
                           bswap_32big(0xefe69c1fU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd234f7e9U),
                               bswap_32big(0xe6ee7a8fU),
                               bswap_32big(0xa723b340U),
                               bswap_32big(0x1173ce90U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00B0H, 0x0000183cU);
                WR1_PROG(REG_0094H, 0x00000821U);
                r_rsip_func_sub006(0x80880001U, 0x03430021U, 0x0000b420U, 0x0000001fU);
                WR1_PROG(REG_0094H, 0x02003841U);

                WR1_PROG(REG_0094H, 0x00008c40U);
                r_rsip_func_sub010(0x00000001U, 0x38000843U, 0x00270000U);

                r_rsip_func100(bswap_32big(0xd53bc865U),
                               bswap_32big(0x6c17e7afU),
                               bswap_32big(0xfc2c512aU),
                               bswap_32big(0xe9ba149dU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func_sub001(0x0019003cU, 0x00460005U, 0x04040002U);

                    r_rsip_func101(bswap_32big(0xf5737ee4U),
                                   bswap_32big(0x09c75e19U),
                                   bswap_32big(0x373db964U),
                                   bswap_32big(0x18a11cb7U));
                }
                else
                {
                    r_rsip_func_sub001(0x003c0005U, 0x00230005U, 0x04040006U);

                    r_rsip_func_sub001(0x00190023U, 0x00460005U, 0x04040002U);

                    r_rsip_func101(bswap_32big(0x8114101fU),
                                   bswap_32big(0x7e7cb416U),
                                   bswap_32big(0xda90af3bU),
                                   bswap_32big(0xa285a185U));
                }

                r_rsip_func_sub003(0x00001450U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub009(0x00001464U, 0x00c00021U, 0x00001800U);

                r_rsip_func_sub003(0x00001469U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub003(0x0000146eU, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub009(0x0000148cU, 0x00c00021U, 0x00001800U);

                r_rsip_func_sub003(0x00001491U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub003(0x00001496U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x000018a0U);
                WR1_PROG(REG_0094H, 0x00000800U);
                r_rsip_func_sub006(0x80880000U, 0x03430021U, 0x000008c6U, 0x00000800U);

                r_rsip_func_sub022(0x0000b420U, 0x0000001fU, 0x0000b440U);
                WR1_PROG(REG_0094H, 0x00000001U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000019U, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0xe8d2a7deU),
                                   bswap_32big(0xfa813de7U),
                                   bswap_32big(0x1df99434U),
                                   bswap_32big(0x163ef8d7U));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0x79bf5b60U),
                                   bswap_32big(0xb5018478U),
                                   bswap_32big(0xa419452bU),
                                   bswap_32big(0x14835ec9U));
                }

                r_rsip_func_sub010(0x380088c0U, 0x00000100U, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub001(0x00870064U, 0x00a50000U, 0x0404000aU);

                r_rsip_func_sub001(0x00870069U, 0x00aa0000U, 0x0404000aU);

                r_rsip_func_sub001(0x0087006eU, 0x00af0000U, 0x0404000aU);

                r_rsip_func_sub001(0x0087009bU, 0x00a00000U, 0x0404000aU);

                WR1_PROG(REG_0014H, 0x000007c7U);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x80880001U);

                for (iLoop = 8; iLoop < 16U; iLoop++)
                {
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, InData_Signature[iLoop]);
                }

                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x0000149bU);
                r_rsip_func_sub007(0x00000821U, 0x81880001U, 0x00c90021U);

                WR1_PROG(REG_00B0H, 0x00000841U);
                r_rsip_func_sub012(0x80020000U, 0x03430009U);
                WR1_PROG(REG_00B0H, 0x000004b1U);
                r_rsip_func_sub012(0x81020000U, 0x00c90009U);

                WR1_PROG(REG_00B0H, 0x00001423U);
                WR1_PROG(REG_0014H, 0x000007a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0EEC73D2U),
                         bswap_32big(0x17F5BE65U),
                         bswap_32big(0xCB5C63AAU),
                         bswap_32big(0x97A331B5U));
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0665E1DBU),
                         bswap_32big(0x6EABA043U),
                         bswap_32big(0xF98B4BAAU),
                         bswap_32big(0x9C78F954U));

                r_rsip_func_sub009(0x00001428U, 0x00c00021U, 0x00001800U);

                r_rsip_func_sub001(0x00230028U, 0x002d000aU, 0x04040002U);

                r_rsip_func_sub001(0x001e009bU, 0x0023000aU, 0x04040002U);

                r_rsip_func_sub003(0x00001482U, 0x00c0001dU, 0x00000001U);

                r_rsip_func_sub001(0x00820023U, 0x003c000aU, 0x04040002U);

                r_rsip_func_sub001(0x002d003cU, 0x009b000aU, 0x04040005U);

                r_rsip_func401(InData_DomainParam);

                WR1_PROG(REG_00B0H, 0x00000840U);
                r_rsip_func_sub012(0x80020000U, 0x03430009U);
                WR1_PROG(REG_00B0H, 0x000004b1U);
                r_rsip_func_sub012(0x81020000U, 0x00c90009U);

                r_rsip_func_sub003(0x00001450U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub009(0x00001464U, 0x00c00021U, 0x00001800U);

                r_rsip_func_sub003(0x00001469U, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                r_rsip_func_sub003(0x0000146eU, 0x00c00015U, 0x00000026U);
                r_rsip_func_sub015(0x00c00009U, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x0000189bU);
                WR1_PROG(REG_0094H, 0x00000800U);
                r_rsip_func_sub006(0x80880000U, 0x03430021U, 0x000008c6U, 0x00000800U);

                r_rsip_func_sub022(0x0000b420U, 0x0000001fU, 0x0000b440U);
                WR1_PROG(REG_0094H, 0x00000001U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000119U, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0x31135f5fU),
                                   bswap_32big(0xc0ed8dedU),
                                   bswap_32big(0xf4512512U),
                                   bswap_32big(0xd8a4d244U));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0x70bf3618U),
                                   bswap_32big(0x89b10f17U),
                                   bswap_32big(0xcf521ef0U),
                                   bswap_32big(0x51f6a8dcU));
                }

                r_rsip_func_sub010(0x380088c0U, 0x00000100U, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func_sub001(0x00870064U, 0x00730000U, 0x0404000aU);

                r_rsip_func_sub001(0x00870069U, 0x00780000U, 0x0404000aU);

                r_rsip_func_sub001(0x0087006eU, 0x007d0000U, 0x0404000aU);

                r_rsip_func_sub001(0x00a50087U, 0x00280005U, 0x04040006U);

                r_rsip_func_sub001(0x00870028U, 0x00a50000U, 0x0404000aU);

                r_rsip_func_sub001(0x008700a5U, 0x00550000U, 0x0404000aU);

                r_rsip_func_sub001(0x008700aaU, 0x005a0000U, 0x0404000aU);

                r_rsip_func_sub001(0x008700afU, 0x005f0000U, 0x0404000aU);

                r_rsip_func404();

                r_rsip_func_sub001(0x00870064U, 0x00550000U, 0x0404000aU);

                r_rsip_func_sub001(0x00870069U, 0x005a0000U, 0x0404000aU);

                r_rsip_func_sub001(0x0087006eU, 0x005f0000U, 0x0404000aU);

                r_rsip_func100(bswap_32big(0xac95c2e2U),
                               bswap_32big(0xf303408cU),
                               bswap_32big(0x23091acfU),
                               bswap_32big(0x7897cf58U));

                r_rsip_func_sub003(0x00001482U, 0x00c0001dU, 0x00000001U);

                r_rsip_func_sub001(0x0082005fU, 0x00230005U, 0x04040002U);

                r_rsip_func_sub003(0x0000142dU, 0x00c0001dU, 0x00000002U);

                r_rsip_func_sub001(0x002d0005U, 0x00280000U, 0x0404000aU);

                r_rsip_func_sub021(0x00280023U, 0x002d0005U, 0x04040000U);
                r_rsip_func_sub020(0x20010001U, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                r_rsip_func_sub001(0x002d0055U, 0x00230005U, 0x04040002U);

                r_rsip_func_sub001(0x002d005aU, 0x00280005U, 0x04040002U);

                WR1_PROG(REG_00B0H, 0x00001823U);
                WR1_PROG(REG_0094H, 0x00000821U);
                r_rsip_func_sub006(0x80880001U, 0x03430021U, 0x0000b420U, 0x0000001cU);
                WR1_PROG(REG_0094H, 0x00003841U);

                WR1_PROG(REG_0094H, 0x001f6c42U);

                WR1_PROG(REG_00B0H, 0x00001828U);
                WR1_PROG(REG_0094H, 0x00000821U);
                r_rsip_func_sub006(0x80880001U, 0x03430021U, 0x00003801U, 0x00008c00U);
                r_rsip_func_sub022(0x7fffffffU, 0x00001002U, 0x00003c01U);

                r_rsip_func409();

                WR1_PROG(REG_0094H, 0x00000821U);

                WR1_PROG(REG_00B0H, 0x00001423U);
                r_rsip_func_sub012(0x81880001U, 0x00c90021U);

                r_rsip_func_sub001(0x008700a0U, 0x009b0000U, 0x0404000aU);

                r_rsip_func_sub001(0x009b0023U, 0x00280000U, 0x0404000aU);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func_sub001(0x0023009bU, 0x00280000U, 0x0404000aU);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0xd036b62dU),
                               bswap_32big(0x572c8f40U),
                               bswap_32big(0xd64057d9U),
                               bswap_32big(0x7c7e522bU));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x59de217cU),
                                   bswap_32big(0x92bf5df2U),
                                   bswap_32big(0xf5f0ed23U),
                                   bswap_32big(0x9b3d13d0U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func102(bswap_32big(0x519fa1dbU),
                                   bswap_32big(0xe6314422U),
                                   bswap_32big(0x39b97fb3U),
                                   bswap_32big(0x881bd693U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
