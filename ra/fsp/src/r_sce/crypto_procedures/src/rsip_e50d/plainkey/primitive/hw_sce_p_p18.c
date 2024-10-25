/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EddsaSignatureGenerateSub (const uint32_t InData_PrivKeyIndex[],
                                            const uint32_t InData_PubKeyIndex[],
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
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_PrivKeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000018U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x11e62c0fU, 0xf5247faeU, 0xc018ad15U, 0x65cb749eU);
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

    HW_SCE_p_func100(0x64d65371U, 0xd9e8226cU, 0x125472efU, 0x2ccf71f0U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x12fe8eafU, 0x87c116e9U, 0x826131aaU, 0x439bde44U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_PubKeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000118U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xecdd018eU, 0x968d1990U, 0x31c8e40aU, 0xbf6393d4U);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000026U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000118U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xc1669fb2U, 0x97c52030U, 0x4ba4da5cU, 0xe092f700U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xe8009107U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_PubKeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x19100000U);
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_PubKeyIndex[iLoop + 1]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x8c533990U, 0xa75f3d1aU, 0x43a83475U, 0x70e7bf64U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x6dbe6988U, 0x3ad492e7U, 0x43d1eb3fU, 0xeb6b121aU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
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

            HW_SCE_p_func100(0x72b52af4U, 0x0dda046bU, 0x429efaa6U, 0x8feaf2deU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0xb1111f87U, 0x50a5b542U, 0x0ca5b21bU, 0x76c932ddU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xb9081a49U, 0x6ec2636cU, 0x2d43bd80U, 0x5b03ec7eU);
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
                S_RAM[1] = change_endian_long(S_RAM[1]);

                HW_SCE_p_func100(0x42134d9aU, 0xb6146474U, 0xbe7f9200U, 0x729375a0U);
                WR1_PROG(REG_1600H, 0x00000842U);
                WR1_PROG(REG_1600H, 0x0c00a420U);
                WR1_PROG(REG_1600H, 0x00000100U);
                WR1_PROG(REG_1600H, 0x00802402U);

                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 2]);
                S_RAM[2] = change_endian_long(S_RAM[2]);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 3]);
                S_RAM[3] = change_endian_long(S_RAM[3]);

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

                HW_SCE_p_func100(0xaa2c719eU, 0x27a0685dU, 0xf6ec0affU, 0x3391f477U);
                HW_SCE_p_func401_r1(InData_DomainParam);

                HW_SCE_p_func100(0xf1181aeeU, 0xfbdb03baU, 0x752db2cbU, 0xa3da3035U);
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

                    HW_SCE_p_func101(0xcfdd4a6eU, 0x3b6e6e7dU, 0x868f7a30U, 0x6819701eU);
                    HW_SCE_p_func402_r1();

                    HW_SCE_p_func404();

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    HW_SCE_p_func101(0xb871b128U, 0x9cc9baa4U, 0xdb265b27U, 0xbfa65e97U);
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

                HW_SCE_p_func100(0x71809130U, 0x44b1c47eU, 0xbeddd158U, 0x77c914deU);
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
                HW_SCE_p_func100(0x028d0a3fU, 0xdba8c3d3U, 0x09d259e1U, 0x608a9559U);
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

                HW_SCE_p_func100(0x30e5362aU, 0x794d9a71U, 0x408a5f6cU, 0xb7b3a94cU);
                WR1_PROG(REG_1600H, 0x00000821U);
                WR1_PROG(REG_1608H, 0x81880001U);
                WR1_PROG(REG_1408H, 0x00005022U);
                for (iLoop = 8U; iLoop < 16U; iLoop++)
                {
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_Signature[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func102(0xea8f8c67U, 0xa5746442U, 0x0a7564eaU, 0x667474e9U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
