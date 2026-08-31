/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EddsaSignatureGenerateSub (const uint32_t InData_KeyMode[],
                                            const uint32_t InData_PrivKeyIndex[],
                                            const uint32_t InData_PrivKey[],
                                            const uint32_t InData_PubKey[],
                                            const uint32_t InData_Msg[],
                                            const uint32_t InData_MsgLen[],
                                            const uint32_t InData_DomainParam[],
                                            uint32_t       OutData_Signature[],
                                            uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00180001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_p18_func100_001[] =
    {
        0x84c341e1U, 0x08e623cdU, 0xbd9e3c3cU, 0x39e5a5daU,
    };
    HW_SCE_p_func100(Param_p18_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_2CH, InData_PrivKeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000018U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p18_func101_001[] =
        {
            0x898e92d2U, 0x93eef7d7U, 0xfe8c2f51U, 0x87e132f7U,
        };
        HW_SCE_p_func101(Param_p18_func101_001);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000027U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000018U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p18_func101_002[] =
        {
            0x26d6d396U, 0x92425521U, 0x57470479U, 0xbd9eab3fU,
        };
        HW_SCE_p_func101(Param_p18_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub007(0x000007c1U, 0x40000100U, 0xf7009d07U);
        WR4_ADDR(REG_2CH, &InData_PrivKeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_PrivKeyIndex[5]);

        WR1_PROG(REG_94H, 0x00000800U);
        WR1_PROG(REG_9CH, 0x80880000U);
        HW_SCE_p_func_sub003(0x03410021U);

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &InData_PrivKeyIndex[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub003(0x00410011U);

        static const uint32_t Param_p18_func101_003[] =
        {
            0x9ad4bcb0U, 0xa3a141fbU, 0xe14919fbU, 0x4fe947b8U,
        };
        HW_SCE_p_func101(Param_p18_func101_003);
    }
    else
    {
        WR1_PROG(REG_94H, 0x00000800U);
        WR1_PROG(REG_14H, 0x000007c7U);
        WR1_PROG(REG_9CH, 0x80880000U);

        for (iLoop = 0U; iLoop < 8U; iLoop++)
        {
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_PrivKey[iLoop]);
        }

        static const uint32_t Param_p18_func101_004[] =
        {
            0x03549999U, 0xa6cc89f2U, 0x87827ab3U, 0xed4ec974U,
        };
        HW_SCE_p_func101(Param_p18_func101_004);
    }

    static const uint32_t Param_p18_func100_002[] =
    {
        0xa08c8b3bU, 0xa4853210U, 0xbe8a3107U, 0x51e7d978U,
    };
    HW_SCE_p_func100(Param_p18_func100_002);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p18_func102_001[] =
        {
            0xdd5f8eb2U, 0xdcae6ddfU, 0x306089c0U, 0xc64abce1U,
        };
        HW_SCE_p_func102(Param_p18_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub017(0x000007c5U, 0x000014a5U);
        WR8_ADDR(REG_2CH, &InData_PubKey[0]);

        HW_SCE_p_func_sub005(0x000001c7U, 0x80020000U);
        WR1_PROG(REG_2CH, InData_MsgLen[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_MsgLen[1]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub001(0x00000842U, 0x30008800U, 0xffffffffU, 0x00030020U);
        HW_SCE_p_func_sub001(0x3000a820U, 0xfffffdffU, 0x00050020U, 0x1000d040U);
        HW_SCE_p_func_sub001(0x00000080U, 0x00000080U, 0x38008840U, 0x00000001U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        static const uint32_t Param_p18_func100_003[] =
        {
            0x4c920252U, 0x7aeace0bU, 0x74f42da7U, 0x200d183dU,
        };
        HW_SCE_p_func100(Param_p18_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p18_func102_002[] =
            {
                0x721758b1U, 0x91e5121eU, 0xe43e3234U, 0x4ea75befU,
            };
            HW_SCE_p_func102(Param_p18_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_p18_func100_004[] =
            {
                0x8d8bb567U, 0x77fdc346U, 0xd5470eaaU, 0x3dd0d448U,
            };
            HW_SCE_p_func100(Param_p18_func100_004);
            HW_SCE_p_func_sub001(0x00000842U, 0x0c00a420U, 0x00000100U, 0x00802402U);

            HW_SCE_p_func_sub009(0x81020000U, 0x0000500aU);
            RD1_ADDR(REG_2CH, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);

            static const uint32_t Param_p18_func100_005[] =
            {
                0xb3198d84U, 0xbfc84004U, 0xc682e63bU, 0xc8932840U,
            };
            HW_SCE_p_func100(Param_p18_func100_005);
            HW_SCE_p_func_sub001(0x00000842U, 0x0c00a420U, 0x00000100U, 0x00802402U);

            HW_SCE_p_func_sub009(0x81020000U, 0x0000500aU);
            RD1_ADDR(REG_2CH, &S_RAM[0 + 2]);
            S_RAM[0 + 2] = change_endian_long(S_RAM[0 + 2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &S_RAM[0 + 3]);
            S_RAM[0 + 3] = change_endian_long(S_RAM[0 + 3]);

            WR1_PROG(REG_F0H, 0x00000001U);

            WR1_PROG(REG_F4H, 0x000000b0U);

            WR1_PROG(REG_14H, 0x00000020U);
            WR1_PROG(REG_104H, 0x00000000U);
            WR1_PROG(REG_14H, 0x00000020U);
            WR1_PROG(REG_100H, 0x00000100U);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x01490021U);

            WAIT_STS(REG_118H, 4, 1);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            HW_SCE_p_func_sub001(0x00003841U, 0x00008c40U, 0xf8ffffffU, 0x00003c41U);

            HW_SCE_p_func_sub001(0x0000b420U, 0x0000001cU, 0x00003841U, 0x00008c40U);
            HW_SCE_p_func_sub001(0xffffff3fU, 0x00009040U, 0x00000040U, 0x00003c41U);

            WR1_PROG(REG_B0H, 0x0000149bU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            WR1_PROG(REG_F0H, 0x00000001U);

            WR1_PROG(REG_F4H, 0x000000b0U);

            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, S_RAM[0]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, S_RAM[0 + 1]);

            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x01490021U);

            WR1_PROG(REG_14H, 0x00020064U);

            for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
            {
                WAIT_STS(REG_14H, 31, 1);
                WR8_ADDR(REG_2CH, &InData_Msg[iLoop]);
                iLoop = iLoop + 8U;
            }

            WAIT_STS(REG_14H, 31, 1);
            for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
            {
                WR1_PROG(REG_2CH, InData_Msg[iLoop]);
            }

            WR1_PROG(REG_14H, 0x00000000U);

            WAIT_STS(REG_118H, 4, 1);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            HW_SCE_p_func409();

            WR1_PROG(REG_B0H, 0x00001437U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            HW_SCE_p_func409();

            WR1_PROG(REG_B0H, 0x00001432U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            HW_SCE_p_func401(InData_DomainParam);

            HW_SCE_p_func406(InData_DomainParam);

            WR1_PROG(REG_B0H, 0x00001487U);
            HW_SCE_p_func_sub003(0x00c00021U);

            WR1_PROG(REG_B0H, 0x00000841U);
            WR1_PROG(REG_9CH, 0x80020000U);
            HW_SCE_p_func_sub003(0x03430009U);
            WR1_PROG(REG_B0H, 0x000004b1U);
            WR1_PROG(REG_9CH, 0x81020000U);
            HW_SCE_p_func_sub003(0x00c90009U);

            WR1_PROG(REG_B0H, 0x00001423U);
            WR1_PROG(REG_14H, 0x000007a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U),
                     change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U),
                     change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));

            HW_SCE_p_func_sub002(0x00320023U, 0x002d000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x001e0037U, 0x0028000aU, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001482U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

            HW_SCE_p_func_sub002(0x00820028U, 0x0023000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x002d0023U, 0x00a0000aU, 0x04040005U);

            WR1_PROG(REG_B0H, 0x00000840U);
            WR1_PROG(REG_9CH, 0x80020000U);
            HW_SCE_p_func_sub003(0x03430009U);
            WR1_PROG(REG_B0H, 0x000004b1U);
            WR1_PROG(REG_9CH, 0x81020000U);
            HW_SCE_p_func_sub003(0x00c90009U);

            WR1_PROG(REG_B0H, 0x00001450U);
            HW_SCE_p_func_sub003(0x00c00015U);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
            HW_SCE_p_func_sub003(0x00c00009U);

            WR1_PROG(REG_B0H, 0x00001464U);
            HW_SCE_p_func_sub003(0x00c00021U);

            WR1_PROG(REG_B0H, 0x00001469U);
            HW_SCE_p_func_sub003(0x00c00015U);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
            HW_SCE_p_func_sub003(0x00c00009U);

            WR1_PROG(REG_B0H, 0x0000146eU);
            HW_SCE_p_func_sub003(0x00c00015U);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
            HW_SCE_p_func_sub003(0x00c00009U);

            WR1_PROG(REG_B0H, 0x0000148cU);
            HW_SCE_p_func_sub003(0x00c00021U);

            WR1_PROG(REG_B0H, 0x00001491U);
            HW_SCE_p_func_sub003(0x00c00015U);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
            HW_SCE_p_func_sub003(0x00c00009U);

            WR1_PROG(REG_B0H, 0x00001496U);
            HW_SCE_p_func_sub003(0x00c00015U);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
            HW_SCE_p_func_sub003(0x00c00009U);

            WR1_PROG(REG_B0H, 0x000018a0U);
            WR1_PROG(REG_94H, 0x00000800U);
            WR1_PROG(REG_9CH, 0x80880000U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func_sub001(0x000008c6U, 0x00000800U, 0x0000b420U, 0x0000001fU);

            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000001U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00000018U));
            WR1_PROG(REG_24H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                static const uint32_t Param_p18_func101_005[] =
                {
                    0x455fa391U, 0x783f0a8fU, 0xc9d42b9fU, 0x027bc0a9U,
                };
                HW_SCE_p_func101(Param_p18_func101_005);
                HW_SCE_p_func402();

                HW_SCE_p_func404();

                WR1_PROG(REG_94H, 0x00002cc0U);

                static const uint32_t Param_p18_func101_006[] =
                {
                    0x3c0ca2ccU, 0x22b11201U, 0xd95226e8U, 0xeb937ba7U,
                };
                HW_SCE_p_func101(Param_p18_func101_006);
            }

            HW_SCE_p_func_sub006(0x380088c0U, 0x00000100U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            static const uint32_t Param_p18_func100_006[] =
            {
                0xfff5eddfU, 0x49db1ba9U, 0x3cde4979U, 0x7a62e943U,
            };
            HW_SCE_p_func100(Param_p18_func100_006);

            HW_SCE_p_func_sub002(0x00870064U, 0x00550000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x00870069U, 0x005a0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x0087006eU, 0x005f0000U, 0x0404000aU);

            WR1_PROG(REG_B0H, 0x00001482U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

            HW_SCE_p_func_sub002(0x0082005fU, 0x00230005U, 0x04040002U);

            WR1_PROG(REG_B0H, 0x0000142dU);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub002(0x002d0005U, 0x00280000U, 0x0404000aU);

            HW_SCE_p_func_sub019(0x00280023U, 0x002d0005U, 0x04040000U);
            HW_SCE_p_func_sub012();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub002(0x002d0055U, 0x00230005U, 0x04040002U);

            HW_SCE_p_func_sub002(0x002d005aU, 0x00280005U, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001823U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func_sub001(0x0000b420U, 0x0000001cU, 0x00003841U, 0x001f6c42U);

            WR1_PROG(REG_B0H, 0x00001828U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func_sub001(0x00003801U, 0x00008c00U, 0x7fffffffU, 0x00001002U);

            WR1_PROG(REG_94H, 0x00003c01U);

            HW_SCE_p_func409();

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_B0H, 0x0000142dU);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_F0H, 0x00000001U);

            WR1_PROG(REG_F4H, 0x000000b0U);

            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, S_RAM[0 + 2]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, S_RAM[0 + 3]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x01490021U);

            WR1_PROG(REG_B0H, 0x000018a5U);
            HW_SCE_p_func_sub003(0x01430021U);

            WR1_PROG(REG_14H, 0x00020064U);

            for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
            {
                WAIT_STS(REG_14H, 31, 1);
                WR16_ADDR(REG_2CH, &InData_Msg[iLoop]);
                iLoop = iLoop + 16U;
            }

            WAIT_STS(REG_14H, 31, 1);
            for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
            {
                WR1_PROG(REG_2CH, InData_Msg[iLoop]);
            }

            WR1_PROG(REG_14H, 0x00000000U);

            WAIT_STS(REG_118H, 4, 1);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            HW_SCE_p_func409();

            WR1_PROG(REG_B0H, 0x000014afU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03450021U);

            HW_SCE_p_func409();

            WR1_PROG(REG_B0H, 0x000014aaU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_B0H, 0x0000189bU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func409();

            WR1_PROG(REG_B0H, 0x0000149bU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            WR1_PROG(REG_B0H, 0x00000841U);
            WR1_PROG(REG_9CH, 0x80020000U);
            HW_SCE_p_func_sub003(0x03430009U);
            WR1_PROG(REG_B0H, 0x000004b1U);
            WR1_PROG(REG_9CH, 0x81020000U);
            HW_SCE_p_func_sub003(0x00c90009U);

            WR1_PROG(REG_B0H, 0x00001423U);
            WR1_PROG(REG_14H, 0x000007a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U),
                     change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U),
                     change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));

            HW_SCE_p_func_sub002(0x00aa0023U, 0x0028000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x001e00afU, 0x0023000aU, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001482U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

            HW_SCE_p_func_sub002(0x00820023U, 0x003c000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x0028003cU, 0x0032000aU, 0x04040005U);

            HW_SCE_p_func_sub002(0x0032001eU, 0x0037000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x009b0037U, 0x003c000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x003c00a0U, 0x0028000aU, 0x04040005U);

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_B0H, 0x00001828U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func409();

            static const uint32_t Param_p18_func100_007[] =
            {
                0x1d34c357U, 0x8ea6f839U, 0x388e1ac9U, 0x1cf826a5U,
            };
            HW_SCE_p_func100(Param_p18_func100_007);
            HW_SCE_p_func_sub015(0x0000182dU, 0x00006022U);
            RD8_ADDR(REG_2CH, &OutData_Signature[0]);

            static const uint32_t Param_p18_func100_008[] =
            {
                0x9afe8cdfU, 0x558f55eaU, 0x6663f9ccU, 0x4e37a14dU,
            };
            HW_SCE_p_func100(Param_p18_func100_008);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81880001U);
            WR1_PROG(REG_08H, 0x00005022U);
            for (iLoop = 8; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_08H, 30, 1);
                RD1_ADDR(REG_2CH, &OutData_Signature[iLoop]);
            }

            static const uint32_t Param_p18_func102_003[] =
            {
                0xec260f4fU, 0x18130c0fU, 0xe3d42de1U, 0x0f10bf26U,
            };
            HW_SCE_p_func102(Param_p18_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
