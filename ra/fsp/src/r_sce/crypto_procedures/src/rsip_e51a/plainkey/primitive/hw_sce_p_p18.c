/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EddsaSignatureGenerateSub (const uint32_t InData_KeyMode[],
                                            const uint32_t InData_PrivKeyIndex[],
                                            const uint32_t InData_PrivKey[],
                                            const uint32_t InData_PubKey[],
                                            const uint32_t InData_Msg[],
                                            const uint32_t InData_MsgLen[],
                                            const uint32_t InData_DomainParam[],
                                            uint32_t       OutData_Signature[],
                                            const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00180001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000008c8U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyMode[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xd891b870U, 0xa8ae1672U, 0x4733c055U, 0xa7c97552U);
    WR1_PROG(REG_143CH, 0x00400000U);
    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_PrivKeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000018U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x82cfa82dU, 0x96e763ceU, 0x9d9b6b8eU, 0xf8192d9eU);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000027U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000018U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xa30971b4U, 0xaaca075eU, 0xe2e18948U, 0xadbbb783U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_PrivKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1608H, 0x80880000U);
        WR1_PROG(REG_1400H, 0x03420021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PrivKeyIndex[iLoop + 1]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        HW_SCE_p_func101(0xba3e7426U, 0xa7b472fbU, 0xf7e3519aU, 0xdb2f9294U);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1444H, 0x000007c7U);
        WR1_PROG(REG_1608H, 0x80880000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PrivKey[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PrivKey[4]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x7bf70752U, 0xf9d54309U, 0x606ead9fU, 0xa6486f91U);
    }

    HW_SCE_p_func100(0x0d8643f4U, 0x0656109cU, 0x9351315aU, 0xbfb88cc4U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xa7b53627U, 0x109b22a3U, 0xdac48395U, 0x5cfb9251U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0x08008107U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_PubKey[iLoop]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x19100000U);
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000001c7U);
        WR1_PROG(REG_1608H, 0x80020000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR2_ADDR(REG_1420H, &InData_MsgLen[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00000bffU);

        WR1_PROG(REG_1600H, 0x30008800U);
        WR1_PROG(REG_1600H, 0xffffffffU);
        WR1_PROG(REG_1600H, 0x00030020U);
        WR1_PROG(REG_1600H, 0x3000a820U);
        WR1_PROG(REG_1600H, 0xfffffdffU);
        WR1_PROG(REG_1600H, 0x00050020U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x38008be0U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xfe14ce07U, 0x0315830aU, 0xa7396fdcU, 0xcd46a0d9U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xa0383350U, 0x93b40720U, 0x783fbb06U, 0xb2b6a061U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x69d66fc4U, 0x47e7a70dU, 0xee50af59U, 0xe628d4f2U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0c00a420U);
            WR1_PROG(REG_1600H, 0x00000100U);
            WR1_PROG(REG_1600H, 0x00802402U);

            WR1_PROG(REG_1608H, 0x81020000U);
            WR1_PROG(REG_1408H, 0x0000500aU);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);

            HW_SCE_p_func100(0x34a67d74U, 0xb8cb62f6U, 0x7a123a21U, 0xebc8d35cU);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0c00a420U);
            WR1_PROG(REG_1600H, 0x00000100U);
            WR1_PROG(REG_1600H, 0x00802402U);

            WR1_PROG(REG_1608H, 0x81020000U);
            WR1_PROG(REG_1408H, 0x0000500aU);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 2]);
            S_RAM[0 + 2] = change_endian_long(S_RAM[0 + 2]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 3]);
            S_RAM[0 + 3] = change_endian_long(S_RAM[0 + 3]);

            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_2004H, 0x000000b0U);

            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2010H, 0x00000100U);

            WR1_PROG(REG_1608H, 0x8188001eU);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WAIT_STS(REG_2030H, 4, 1);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03450041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00003841U);
            WR1_PROG(REG_1600H, 0x00008c40U);
            WR1_PROG(REG_1600H, 0xf8ffffffU);
            WR1_PROG(REG_1600H, 0x00003c41U);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x0000001cU);
            WR1_PROG(REG_1600H, 0x00003841U);

            WR1_PROG(REG_1600H, 0x00008c40U);
            WR1_PROG(REG_1600H, 0xffffff3fU);

            WR1_PROG(REG_1600H, 0x00009040U);
            WR1_PROG(REG_1600H, 0x00000040U);
            WR1_PROG(REG_1600H, 0x00003c41U);

            WR1_PROG(REG_1404H, 0x19600000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_2004H, 0x000000b0U);

            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, S_RAM[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, S_RAM[0 + 1]);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x00020064U);

            for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR8_ADDR(REG_1420H, &InData_Msg[iLoop]);

                iLoop = iLoop + 8U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WAIT_STS(REG_1444H, 31, 1);
            for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
            {
                WR1_PROG(REG_1420H, InData_Msg[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x00000000U);

            WAIT_STS(REG_2030H, 4, 1);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03450041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000003fU);

            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x02003801U);
                WR1_PROG(REG_1600H, 0x02003843U);
                WR1_PROG(REG_1600H, 0x02003c41U);
                WR1_PROG(REG_1600H, 0x02003c03U);

                WR1_PROG(REG_1600H, 0x00002c20U);
                WR1_PROG(REG_1600H, 0x00003060U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1004H, 0x00000000U);
            WR1_PROG(REG_1004H, 0x04040000U);

            HW_SCE_p_func100(0x8c442a3dU, 0xbe969ba1U, 0xa2bf39faU, 0xd57af1caU);
            HW_SCE_p_func401_r1(InData_DomainParam);

            HW_SCE_p_func100(0x72dc431aU, 0x8c4bf25bU, 0xffd74e71U, 0x508c07c7U);
            HW_SCE_p_func406_r1(InData_DomainParam);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x00000100U);
            WR1_PROG(REG_1A24H, 0x08008107U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U), change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U), change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));
            WR1_PROG(REG_1400H, 0x00c20021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x12800000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000010U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000009d0U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x15000000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
            WR1_PROG(REG_1400H, 0x00c00015U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c2000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00020005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x16400000U);
            WR1_PROG(REG_1400H, 0x00c00021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x16900000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
            WR1_PROG(REG_1400H, 0x00c00015U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c2000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00020005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x16e00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
            WR1_PROG(REG_1400H, 0x00c00015U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c2000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00020005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x1b400000U);
            WR1_PROG(REG_1400H, 0x00c00021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x1b900000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
            WR1_PROG(REG_1400H, 0x00c00015U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c2000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00020005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x1be00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
            WR1_PROG(REG_1400H, 0x00c00015U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c2000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00020005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19b00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x8088001fU);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000908U);
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x0000b660U);
            WR1_PROG(REG_1600H, 0x00000001U);

            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000100U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000018U));
            WR1_PROG(REG_1458H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                HW_SCE_p_func101(0x0b4568e2U, 0x37346249U, 0x3a2eb8adU, 0x32c4f455U);
                HW_SCE_p_func402_r1();

                HW_SCE_p_func404();

                WR1_PROG(REG_1600H, 0x00002d00U);

                HW_SCE_p_func101(0xd337f435U, 0x0df9dc91U, 0x2f0d6085U, 0x646cf2d7U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x08000909U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000570U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000006b0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x000005c0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000700U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000610U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000610U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);
            WR1_PROG(REG_1010H, 0x00000008U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12d00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c0001dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x1b034184U, 0x42e0a90dU, 0x11a93dc7U, 0x3f864eebU);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x0404000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000570U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000005c0U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12800000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80880001U);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00003801U);
            WR1_PROG(REG_1600H, 0x00008c00U);
            WR1_PROG(REG_1600H, 0x7fffffffU);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1608H, 0x80880001U);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x0000003cU);
            WR1_PROG(REG_1600H, 0x00003841U);

            WR1_PROG(REG_1600H, 0x001f6c42U);
            WR1_PROG(REG_1600H, 0x00001002U);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00003c01U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x02003801U);
                WR1_PROG(REG_1600H, 0x02003843U);
                WR1_PROG(REG_1600H, 0x02003c41U);
                WR1_PROG(REG_1600H, 0x02003c03U);

                WR1_PROG(REG_1600H, 0x00002c20U);
                WR1_PROG(REG_1600H, 0x00003060U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x1c300000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_2004H, 0x000000b0U);

            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, S_RAM[0 + 2]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, S_RAM[0 + 3]);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19100000U);
            WR1_PROG(REG_1400H, 0x01430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x00020064U);

            for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);

                iLoop = iLoop + 16U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WAIT_STS(REG_1444H, 31, 1);
            for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
            {
                WR1_PROG(REG_1420H, InData_Msg[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x00000000U);

            WAIT_STS(REG_2030H, 4, 1);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03450041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000003fU);

            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x02003801U);
                WR1_PROG(REG_1600H, 0x02003843U);
                WR1_PROG(REG_1600H, 0x02003c41U);
                WR1_PROG(REG_1600H, 0x02003c03U);

                WR1_PROG(REG_1600H, 0x00002c20U);
                WR1_PROG(REG_1600H, 0x00003060U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81900001U);

            WR1_PROG(REG_1404H, 0x1a000000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x1a500000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19600000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80880001U);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x02003801U);
                WR1_PROG(REG_1600H, 0x02003843U);
                WR1_PROG(REG_1600H, 0x02003c41U);
                WR1_PROG(REG_1600H, 0x02003c03U);

                WR1_PROG(REG_1600H, 0x00002c20U);
                WR1_PROG(REG_1600H, 0x00003060U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x19600000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x00000100U);
            WR1_PROG(REG_1A24H, 0x08008107U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U), change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U), change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));
            WR1_PROG(REG_1400H, 0x00c20021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000a20U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002a0U);
            WR1_PROG(REG_1010H, 0x00000010U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000a70U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000003e0U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000003e0U);
            WR1_PROG(REG_1018H, 0x000002a0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x00000b40U);
            WR1_PROG(REG_1020H, 0x00000430U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000200U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000390U);
            WR1_PROG(REG_1010H, 0x00000010U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_1018H, 0x00000430U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000003e0U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000009d0U);
            WR1_PROG(REG_1018H, 0x00000b40U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x000003e0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1600H, 0x00000842U);
            WR1_PROG(REG_1600H, 0x0000b460U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1404H, 0x12800000U);
            WR1_PROG(REG_1608H, 0x80880001U);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x02003801U);
                WR1_PROG(REG_1600H, 0x02003843U);
                WR1_PROG(REG_1600H, 0x02003c41U);
                WR1_PROG(REG_1600H, 0x02003c03U);

                WR1_PROG(REG_1600H, 0x00002c20U);
                WR1_PROG(REG_1600H, 0x00003060U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            HW_SCE_p_func100(0xc16c890eU, 0x4f2beb79U, 0xe4375a1bU, 0x86185ad0U);
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0x08008107U);

            WR1_PROG(REG_1404H, 0x1c300000U);
            WR1_PROG(REG_1400H, 0x00830021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Signature[0]);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Signature[4]);

            HW_SCE_p_func100(0x893121baU, 0xca6836c3U, 0x0101e24cU, 0xe83c57beU);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1408H, 0x00005022U);
            for (iLoop = 8U; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_Signature[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0x3271df0cU, 0x70f72a10U, 0x65206a4eU, 0x31c5cb92U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
