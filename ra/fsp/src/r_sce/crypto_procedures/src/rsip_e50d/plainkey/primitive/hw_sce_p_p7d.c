/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaP512SignatureGenerateSub (const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_Signature[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x007d0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    HW_SCE_p_func100(0xc28e5f5cU, 0xaa587464U, 0xd69cce04U, 0x65f4deafU);
    HW_SCE_p_func078_r2(InData_DomainParam);
    HW_SCE_p_func100(0xae72fe3eU, 0x95f6fa6bU, 0x9b6a04e2U, 0xa3b86142U);

    WR1_PROG(REG_1404H, 0x11200000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
    WR1_PROG(REG_1400H, 0x00c0003dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x000000c0U);
    WR1_PROG(REG_1018H, 0x00000160U);
    WR1_PROG(REG_1020H, 0x000003f0U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000003f0U);

    WR1_PROG(REG_1004H, 0x08080010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000070U);

    WR1_PROG(REG_1004H, 0x08080010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x10d00000U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xfe35c45cU, 0x0ce618d7U, 0x394b95a1U, 0x74a43856U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func100(0x0e957d55U, 0xa15ff1adU, 0x5ae3f859U, 0x83d091f8U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func100(0xc4790e58U, 0xcec3a12bU, 0x0d8aef0dU, 0x2d0b7300U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000110U);
    WR1_PROG(REG_101CH, 0x000003f0U);
    WR1_PROG(REG_1020H, 0x00000160U);
    WR1_PROG(REG_1010H, 0x00000020U);

    WR1_PROG(REG_1004H, 0x08080004U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x13f80000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0003dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000438U);
    WR1_PROG(REG_1020H, 0x00000340U);

    WR1_PROG(REG_1004H, 0x08080009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000000c0U);

    WR1_PROG(REG_1004H, 0x08080010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    HW_SCE_p_func100(0x72243ca7U, 0x62f3ba45U, 0xf70ee7c4U, 0x4694b666U);
    HW_SCE_p_func079_r2(InData_DomainParam);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000007dU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xda41e66dU, 0x3aca0734U, 0x3301ac76U, 0x7115431fU);
    HW_SCE_p_func090_r1();

    HW_SCE_p_func100(0x99aace2fU, 0xffc8148cU, 0xc113485bU, 0xa8adbb2fU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x658b0e9fU, 0x9355a40aU, 0xb785b85fU, 0xf8722862U);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1014H, 0x000002a0U);
        WR1_PROG(REG_1018H, 0x00000840U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x000002f0U);
        WR1_PROG(REG_1010H, 0x00000020U);

        WR1_PROG(REG_1004H, 0x08080002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x000002a0U);

        WR1_PROG(REG_1004H, 0x08080004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x10d00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0003dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x000002a0U);
        WR1_PROG(REG_1018H, 0x00000110U);
        WR1_PROG(REG_1020H, 0x00000150U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x8b99c51aU, 0x63534a0eU, 0x0cddbde2U, 0x739eaba0U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xda2ec3ceU, 0xf6ff2d6dU, 0x3cd082a1U, 0x88dac9a6U);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x354665c1U, 0xc6f616b4U, 0x1700644eU, 0x27d9eed5U);
            WR1_PROG(REG_1404H, 0x11200000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c0003dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x000000c0U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000340U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x0808000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1444H, 0x00000fc2U);
            WR1_PROG(REG_1A2CH, 0x00000300U);
            WR1_PROG(REG_1A24H, 0x08008107U);

            WR1_PROG(REG_1404H, 0x11200000U);
            for (iLoop = 0U; iLoop < 16U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_MsgDgst[iLoop]);
                WR1_PROG(REG_1400H, 0x00c20011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800100e0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000007dU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x7d4dbd5dU, 0x5a0b9ef6U, 0x4a26f749U, 0xa5ec739bU);
            HW_SCE_p_func043_r1();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000021U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000007dU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xeef7941aU, 0x3756f3aeU, 0x7e610515U, 0xe032a5d2U);
            HW_SCE_p_func044_r1();

            WR1_PROG(REG_1444H, 0x00000fc2U);
            WR1_PROG(REG_1A2CH, 0x40000300U);
            WR1_PROG(REG_1A24H, 0xf7009d07U);

            WR1_PROG(REG_1404H, 0x11c00000U);

            for (iLoop = 0U; iLoop < 16U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
                WR1_PROG(REG_1400H, 0x00c20011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func100(0x87f78f03U, 0xd3664b26U, 0x930eb998U, 0xb200e158U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0xd59f90ceU, 0x6285670bU, 0xb6d77a53U, 0x59d60414U);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000200U);
                WR1_PROG(REG_1018H, 0x00000840U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000001b0U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000200U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x08080005U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x000001b0U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000200U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x10d00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0003dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000200U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_1020H, 0x00000150U);

                WR1_PROG(REG_1004H, 0x0808000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0xf36cf79aU, 0xab3145a9U, 0xdbf7521aU, 0x99135820U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0x628a129eU, 0x3d7efadaU, 0x7a7dd18cU, 0x7238618eU);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0x6c8cfd61U, 0x20305620U, 0x50c3f690U, 0x61acac69U);
                    WR1_PROG(REG_1404H, 0x12600000U);
                    WR1_PROG(REG_1A2CH, 0x00000200U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002032U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[0]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[4]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[8]);

                    HW_SCE_p_func100(0x90140fcdU, 0xcd06c2baU, 0xb536e9f0U, 0x8d908c90U);
                    WR1_PROG(REG_1A24H, 0x08000105U);
                    WR1_PROG(REG_1400H, 0x00830011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002012U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[12]);

                    HW_SCE_p_func100(0x2d378205U, 0x1f23f6dcU, 0x6923132aU, 0x6ff823d4U);
                    WR1_PROG(REG_1404H, 0x11c00000U);
                    WR1_PROG(REG_1A2CH, 0x00000200U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002032U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[16]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[20]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[24]);

                    HW_SCE_p_func100(0x34e11dd8U, 0x805163aaU, 0x78ee151dU, 0x5296aa90U);
                    WR1_PROG(REG_1A24H, 0x08000105U);
                    WR1_PROG(REG_1400H, 0x00830011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002012U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_Signature[28]);

                    HW_SCE_p_func102(0x32425f38U, 0x1c3d0776U, 0x2f47db0fU, 0xd17d676fU);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
