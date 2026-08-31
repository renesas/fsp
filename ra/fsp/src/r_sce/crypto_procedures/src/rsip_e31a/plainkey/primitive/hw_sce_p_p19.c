/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EddsaSignatureVerificationSub (const uint32_t InData_Key[],
                                                const uint32_t InData_Msg[],
                                                const uint32_t InData_MsgLen[],
                                                const uint32_t InData_Signature[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00190001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    HW_SCE_p_func_sub017(0x000007c5U, 0x000014a5U);
    WR8_ADDR(REG_2CH, &InData_Key[0]);

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

    static const uint32_t Param_p19_func100_001[] =
    {
        0xbd2f8c23U, 0xbc34642dU, 0xd4bf289eU, 0x41938af1U,
    };
    HW_SCE_p_func100(Param_p19_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p19_func102_001[] =
        {
            0x35c41ac5U, 0x51579566U, 0x86863d6bU, 0x902b231cU,
        };
        HW_SCE_p_func102(Param_p19_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub017(0x000007c5U, 0x0000149bU);
        WR8_ADDR(REG_2CH, &InData_Signature[0]);

        static const uint32_t Param_p19_func100_002[] =
        {
            0x1fa4f9a4U, 0x2af78a3eU, 0x009ebf73U, 0x1ff52340U,
        };
        HW_SCE_p_func100(Param_p19_func100_002);
        HW_SCE_p_func_sub001(0x00000842U, 0x0c00a420U, 0x00000200U, 0x00802402U);

        HW_SCE_p_func_sub009(0x81020000U, 0x0000500aU);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &S_RAM[0 + 1]);
        S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);

        WR1_PROG(REG_F0H, 0x00000001U);

        WR1_PROG(REG_F4H, 0x000000b0U);

        WR1_PROG(REG_14H, 0x00000040U);
        WR1_PROG(REG_104H, S_RAM[0]);
        WR1_PROG(REG_14H, 0x00000040U);
        WR1_PROG(REG_100H, S_RAM[0 + 1]);

        WR1_PROG(REG_B0H, 0x0000189bU);
        HW_SCE_p_func_sub003(0x01430021U);

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

        HW_SCE_p_func_sub002(0x00aa0023U, 0x0028000aU, 0x04040002U);

        HW_SCE_p_func_sub002(0x001e00afU, 0x0023000aU, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001482U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x00820023U, 0x003c000aU, 0x04040002U);

        HW_SCE_p_func_sub002(0x0028003cU, 0x00a0000aU, 0x04040005U);

        WR1_PROG(REG_94H, 0x00000821U);

        WR1_PROG(REG_B0H, 0x000018a5U);
        WR1_PROG(REG_9CH, 0x80880001U);
        HW_SCE_p_func_sub003(0x03430021U);

        HW_SCE_p_func409();

        static const uint32_t Param_p19_func100_003[] =
        {
            0x62c5e545U, 0xaff1adb5U, 0xdd87903fU, 0xace484fcU,
        };
        HW_SCE_p_func100(Param_p19_func100_003);

        HW_SCE_p_func_sub001(0x00000800U, 0x00000821U, 0x02003801U, 0x00003440U);
        HW_SCE_p_func_sub001(0x00076800U, 0x00003460U, 0x00008c40U, 0x0000007FU);
        WR1_PROG(REG_94H, 0x02003c41U);

        WR1_PROG(REG_94H, 0x00000800U);
        WR1_PROG(REG_9CH, 0x81880000U);

        WR1_PROG(REG_B0H, 0x00001423U);
        HW_SCE_p_func_sub003(0x00c90021U);

        WR1_PROG(REG_B0H, 0x00000840U);
        WR1_PROG(REG_9CH, 0x80020000U);
        HW_SCE_p_func_sub003(0x03430009U);
        WR1_PROG(REG_B0H, 0x000004b1U);
        WR1_PROG(REG_9CH, 0x81020000U);
        HW_SCE_p_func_sub003(0x00c90009U);

        HW_SCE_p_func_sub002(0x00190023U, 0x004b0005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x004b004bU, 0x00230005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001482U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x00820019U, 0x00280005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x00280023U, 0x002d0005U, 0x04040006U);

        HW_SCE_p_func_sub002(0x00140023U, 0x00370005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x00280037U, 0x00320005U, 0x04040005U);

        HW_SCE_p_func_sub002(0x00820032U, 0x00230005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001428U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

        HW_SCE_p_func_sub002(0x00280005U, 0x003c0005U, 0x04040006U);

        HW_SCE_p_func_sub019(0x003c0023U, 0x00280005U, 0x04040000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        static const uint32_t Param_p19_func100_004[] =
        {
            0x9ec066e1U, 0x1b8099b4U, 0x113ad9bbU, 0x9caacc57U,
        };
        HW_SCE_p_func100(Param_p19_func100_004);
        HW_SCE_p_func_sub002(0x0028002dU, 0x00370005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001423U);
        WR1_PROG(REG_14H, 0x000007a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0x0FFFFFFFU), change_endian_long(0xFFFFFFFFU),
                 change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU));
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU),
                 change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFEU));

        HW_SCE_p_func_sub019(0x00230037U, 0x003c0005U, 0x04040000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub002(0x0019003cU, 0x002d0005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x002d002dU, 0x00320005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x00820032U, 0x002d0005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x00370005U, 0x00230005U, 0x04040006U);

        HW_SCE_p_func_sub002(0x0037002dU, 0x00820000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x002d0037U, 0x00820000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_p19_func100_005[] =
        {
            0xea964a81U, 0x94149761U, 0xdfc36ae7U, 0x8074db9fU,
        };
        HW_SCE_p_func100(Param_p19_func100_005);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub002(0x0023002dU, 0x00820000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub002(0x002d0023U, 0x00820000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_p19_func100_006[] =
            {
                0x7cf28299U, 0x9cd1ca6dU, 0x7a038a90U, 0xe086b09aU,
            };
            HW_SCE_p_func100(Param_p19_func100_006);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                static const uint32_t Param_p19_func101_001[] =
                {
                    0xa4821d9aU, 0x6588428fU, 0x3b74af10U, 0x35e113cdU,
                };
                HW_SCE_p_func101(Param_p19_func101_001);
            }
            else
            {
                HW_SCE_p_func_sub002(0x0019003cU, 0x00230005U, 0x04040002U);

                WR1_PROG(REG_B0H, 0x00001428U);
                WR1_PROG(REG_14H, 0x000007a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_PROG(REG_2CH, change_endian_long(0x2B832480U), change_endian_long(0x4FC1DF0BU),
                         change_endian_long(0x2B4D0099U), change_endian_long(0x3DFBD7A7U));
                WAIT_STS(REG_14H, 31, 1);
                WR4_PROG(REG_2CH, change_endian_long(0x2F431806U), change_endian_long(0xAD2FE478U),
                         change_endian_long(0xC4EE1B27U), change_endian_long(0x4A0EA0B0U));

                HW_SCE_p_func_sub002(0x00280023U, 0x003c0005U, 0x04040002U);

                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0xed08d7a1U);

                static const uint32_t Param_p19_func101_002[] =
                {
                    0x2e47bf58U, 0xfaf4642cU, 0x3429cfefU, 0xf78f621dU,
                };
                HW_SCE_p_func101(Param_p19_func101_002);
            }
        }
        else
        {
            WR1_PROG(REG_94H, 0x0000b400U);
            WR1_PROG(REG_94H, 0xed08d7a1U);

            static const uint32_t Param_p19_func101_003[] =
            {
                0x09e9a5b6U, 0xa7d7bca3U, 0x660d8db9U, 0x69ba9acbU,
            };
            HW_SCE_p_func101(Param_p19_func101_003);
        }

        HW_SCE_p_func_sub006(0x38008800U, 0xed08d7a1U, 0x00A70000U);

        static const uint32_t Param_p19_func100_007[] =
        {
            0x725465e3U, 0x04e51c60U, 0x58d875e4U, 0xe86b6772U,
        };
        HW_SCE_p_func100(Param_p19_func100_007);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p19_func102_002[] =
            {
                0x1d2f9683U, 0xcb0f0f68U, 0xd0b5a84fU, 0x14fdfa37U,
            };
            HW_SCE_p_func102(Param_p19_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_B0H, 0x0000183cU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func_sub001(0x0000b420U, 0x0000001fU, 0x02003841U, 0x00008c40U);
            HW_SCE_p_func_sub006(0x00000001U, 0x38000843U, 0x00270000U);

            static const uint32_t Param_p19_func100_008[] =
            {
                0x273c87c8U, 0x41b2cf22U, 0x1d1146e2U, 0x6cd2f740U,
            };
            HW_SCE_p_func100(Param_p19_func100_008);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func_sub002(0x0019003cU, 0x00460005U, 0x04040002U);

                static const uint32_t Param_p19_func101_004[] =
                {
                    0xa9f6ec95U, 0xbe14f983U, 0x0544488dU, 0xf8baaf9dU,
                };
                HW_SCE_p_func101(Param_p19_func101_004);
            }
            else
            {
                HW_SCE_p_func_sub002(0x003c0005U, 0x00230005U, 0x04040006U);

                HW_SCE_p_func_sub002(0x00190023U, 0x00460005U, 0x04040002U);

                static const uint32_t Param_p19_func101_005[] =
                {
                    0x615c9235U, 0x021d69aaU, 0x9fb7ccd4U, 0xd208d563U,
                };
                HW_SCE_p_func101(Param_p19_func101_005);
            }

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
            WR1_PROG(REG_2CH, change_endian_long(0x00000019U));
            WR1_PROG(REG_24H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                static const uint32_t Param_p19_func101_006[] =
                {
                    0x5714053bU, 0xcf5d6141U, 0x593595afU, 0x5607b425U,
                };
                HW_SCE_p_func101(Param_p19_func101_006);
                HW_SCE_p_func402();

                HW_SCE_p_func404();

                WR1_PROG(REG_94H, 0x00002cc0U);

                static const uint32_t Param_p19_func101_007[] =
                {
                    0x8698711eU, 0xd588a680U, 0xf2220f86U, 0xfbb7a316U,
                };
                HW_SCE_p_func101(Param_p19_func101_007);
            }

            HW_SCE_p_func_sub006(0x380088c0U, 0x00000100U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func_sub002(0x00870064U, 0x00a50000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x00870069U, 0x00aa0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x0087006eU, 0x00af0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x0087009bU, 0x00a00000U, 0x0404000aU);

            WR1_PROG(REG_14H, 0x000007c7U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);

            for (iLoop = 8; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, InData_Signature[iLoop]);
            }

            WR1_PROG(REG_24H, 0x00000000U);

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

            WR1_PROG(REG_B0H, 0x00001428U);
            HW_SCE_p_func_sub003(0x00c00021U);

            HW_SCE_p_func_sub002(0x00230028U, 0x002d000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x001e009bU, 0x0023000aU, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001482U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

            HW_SCE_p_func_sub002(0x00820023U, 0x003c000aU, 0x04040002U);

            HW_SCE_p_func_sub002(0x002d003cU, 0x009b000aU, 0x04040005U);

            HW_SCE_p_func401(InData_DomainParam);

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

            WR1_PROG(REG_B0H, 0x0000189bU);
            WR1_PROG(REG_94H, 0x00000800U);
            WR1_PROG(REG_9CH, 0x80880000U);
            HW_SCE_p_func_sub003(0x03430021U);

            HW_SCE_p_func_sub001(0x000008c6U, 0x00000800U, 0x0000b420U, 0x0000001fU);

            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000001U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x00000119U));
            WR1_PROG(REG_24H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                static const uint32_t Param_p19_func101_008[] =
                {
                    0x54082ad4U, 0x59bddeb6U, 0x4d89865bU, 0xa262b5d7U,
                };
                HW_SCE_p_func101(Param_p19_func101_008);
                HW_SCE_p_func402();

                HW_SCE_p_func404();

                WR1_PROG(REG_94H, 0x00002cc0U);

                static const uint32_t Param_p19_func101_009[] =
                {
                    0x675ea1cfU, 0x150fe454U, 0xec6ee67eU, 0x31fca300U,
                };
                HW_SCE_p_func101(Param_p19_func101_009);
            }

            HW_SCE_p_func_sub006(0x380088c0U, 0x00000100U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func_sub002(0x00870064U, 0x00730000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x00870069U, 0x00780000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x0087006eU, 0x007d0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x00a50087U, 0x00280005U, 0x04040006U);

            HW_SCE_p_func_sub002(0x00870028U, 0x00a50000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x008700a5U, 0x00550000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x008700aaU, 0x005a0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x008700afU, 0x005f0000U, 0x0404000aU);

            HW_SCE_p_func404();

            HW_SCE_p_func_sub002(0x00870064U, 0x00550000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x00870069U, 0x005a0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x0087006eU, 0x005f0000U, 0x0404000aU);

            static const uint32_t Param_p19_func100_009[] =
            {
                0x07ea25cdU, 0xf04cfef3U, 0x8b1d8b8bU, 0xf5e9c98eU,
            };
            HW_SCE_p_func100(Param_p19_func100_009);

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

            WR1_PROG(REG_B0H, 0x00001423U);
            WR1_PROG(REG_9CH, 0x81880001U);
            HW_SCE_p_func_sub003(0x00c90021U);

            HW_SCE_p_func_sub002(0x008700a0U, 0x009b0000U, 0x0404000aU);

            HW_SCE_p_func_sub002(0x009b0023U, 0x00280000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub002(0x0023009bU, 0x00280000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_p19_func100_010[] =
            {
                0x6b1c214aU, 0x1ad52054U, 0x2732f8d7U, 0xfad1ccb7U,
            };
            HW_SCE_p_func100(Param_p19_func100_010);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p19_func102_003[] =
                {
                    0xc22bf72aU, 0xc7886ba0U, 0xa0bdc112U, 0xb20f0715U,
                };
                HW_SCE_p_func102(Param_p19_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p19_func102_004[] =
                {
                    0x1cf4a18aU, 0x598668bfU, 0x76fab73eU, 0x4ab15bc3U,
                };
                HW_SCE_p_func102(Param_p19_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
