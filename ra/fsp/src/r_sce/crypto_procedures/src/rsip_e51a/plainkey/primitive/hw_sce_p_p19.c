/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EddsaSignatureVerificationSub (const uint32_t InData_Key[],
                                                const uint32_t InData_Msg[],
                                                const uint32_t InData_MsgLen[],
                                                const uint32_t InData_Signature[],
                                                const uint32_t InData_DomainParam[],
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

    WR1_PROG(REG_1B00H, 0x00190001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000008c8U);

    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0x08008107U);

    for (iLoop = 0U; iLoop < 8U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Key[iLoop]);
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

    HW_SCE_p_func100(0x06b675d0U, 0x435d8929U, 0xd829e3f1U, 0xea6dc389U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x5e83ae17U, 0xf3b161c2U, 0xccf44271U, 0x7ee2574dU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x00000100U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WR1_PROG(REG_1404H, 0x1c300000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[4]);
        WR1_PROG(REG_1400H, 0x00c20021U);

        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x7edc87c6U, 0x93f3bfe2U, 0x3c2f2947U, 0x897be24aU);
        WR1_PROG(REG_1600H, 0x00000842U);
        WR1_PROG(REG_1600H, 0x0c00a420U);
        WR1_PROG(REG_1600H, 0x00000200U);
        WR1_PROG(REG_1600H, 0x00802402U);

        WR1_PROG(REG_1608H, 0x81020000U);
        WR1_PROG(REG_1408H, 0x0000500aU);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
        S_RAM[0 + 1] = change_endian_long(S_RAM[0 + 1]);

        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_2004H, 0x000000b0U);

        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, S_RAM[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, S_RAM[0 + 1]);

        WR1_PROG(REG_1404H, 0x1c300000U);
        WR1_PROG(REG_1400H, 0x01430021U);
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

        WR1_PROG(REG_1004H, 0x00000000U);
        WR1_PROG(REG_1004H, 0x04040000U);

        HW_SCE_p_func100(0xe347f06dU, 0x2226b3d6U, 0xc3c18529U, 0xc3d7e00fU);
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
        WR1_PROG(REG_1020H, 0x000009d0U);

        WR1_PROG(REG_1004H, 0x04040005U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x14300000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1600H, 0x00000842U);
        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x0000001fU);

        WR1_PROG(REG_1404H, 0x19100000U);
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

        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1600H, 0x02003801U);
        WR1_PROG(REG_1600H, 0x00003440U);
        WR1_PROG(REG_1600H, 0x00076800U);
        WR1_PROG(REG_1600H, 0x000037e0U);

        WR1_PROG(REG_1600H, 0x00008c40U);
        WR1_PROG(REG_1600H, 0x0000007FU);
        WR1_PROG(REG_1600H, 0x02003c41U);

        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1608H, 0x81880000U);

        WR1_PROG(REG_1404H, 0x12300000U);
        WR1_PROG(REG_1400H, 0x00c90021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000004d0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000004d0U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x00000ac0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000004d0U);
        WR1_PROG(REG_1018H, 0x00000ac0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002a0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x000002a0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002f0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040006U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000390U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_1018H, 0x000002a0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000340U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040005U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000340U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x12800000U);
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
        WR1_PROG(REG_1018H, 0x000002a0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000003e0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040006U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        HW_SCE_p_func100(0xec82f887U, 0x94eae90aU, 0x943007edU, 0x92fe6777U);
        WR1_PROG(REG_1014H, 0x00000250U);
        WR1_PROG(REG_1018H, 0x000003e0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002a0U);

        WR1_PROG(REG_1004H, 0x0404000fU);
        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_1018H, 0x000002a0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000390U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x12300000U);
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x00000100U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x0FFFFFFFU), change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU));
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFEU));
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x02799e33U, 0x1d9ee0fdU, 0xbf0b2f91U, 0x5e874afbU);
        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_1018H, 0x00000250U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000003e0U);

        WR1_PROG(REG_1004H, 0x0404000fU);
        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000003e0U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002f0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x00000ac0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_1018H, 0x00000ac0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000340U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000340U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002f0U);
        WR1_PROG(REG_1010H, 0x00000008U);

        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000070U);
        WR1_PROG(REG_1018H, 0x00000390U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x04040006U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x14100000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0001dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x000002f0U);
        WR1_PROG(REG_1018H, 0x00000390U);
        WR1_PROG(REG_1020H, 0x00000ac0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_1018H, 0x000002f0U);
        WR1_PROG(REG_1020H, 0x00000ac0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x281e10e3U, 0x73cd51f8U, 0x86ad16dcU, 0x50ab9400U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_1018H, 0x00000250U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000ac0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0xbfe9d3daU, 0x60e47800U, 0x427d5898U, 0x3a8bcf48U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1600H, 0xd4cfa273U);

                HW_SCE_p_func101(0xa82ed5bfU, 0xef57393cU, 0xd94e7d44U, 0x241a2a78U);
            }
            else
            {
                WR1_PROG(REG_1014H, 0x000003e0U);
                WR1_PROG(REG_1018H, 0x000001b0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000250U);
                WR1_PROG(REG_1010H, 0x00000008U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x00000100U);
                WR1_PROG(REG_1A24H, 0x08008107U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H, change_endian_long(0x2B832480U), change_endian_long(0x4FC1DF0BU), change_endian_long(0x2B4D0099U), change_endian_long(0x3DFBD7A7U));
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H, change_endian_long(0x2F431806U), change_endian_long(0xAD2FE478U), change_endian_long(0xC4EE1B27U), change_endian_long(0x4A0EA0B0U));
                WR1_PROG(REG_1400H, 0x00c20021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000003e0U);
                WR1_PROG(REG_1010H, 0x00000008U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0x16633196U, 0x29acdf3cU, 0x1e2650f7U, 0xda674705U);
            }

            HW_SCE_p_func101(0x62101dffU, 0x9cab5070U, 0xa881c7acU, 0xd0671ab9U);
        }
        else
        {
            HW_SCE_p_func101(0x63d7d197U, 0x12b5aa31U, 0x52dd5d5fU, 0x2e649765U);
        }

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1600H, 0xd4cfa273U);

        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xeced85feU, 0x8e42bf44U, 0x2a329fc8U, 0x78d52b60U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x9cfcac49U, 0x168dbd10U, 0x6d623542U, 0xa2f29568U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1404H, 0x1b100000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x13c00000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80880001U);
            WR1_PROG(REG_1400H, 0x03430021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x02003841U);

            WR1_PROG(REG_1600H, 0x00008c40U);
            WR1_PROG(REG_1600H, 0x00000001U);

            WR1_PROG(REG_1600H, 0x3800085fU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x524b3775U, 0xfecc7135U, 0xc9a1f79fU, 0x1807c7b0U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x000003e0U);
                WR1_PROG(REG_1018H, 0x000001b0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000480U);
                WR1_PROG(REG_1010H, 0x00000008U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0xc913f684U, 0x89a15f2cU, 0x0ab4784aU, 0x88431a1fU);
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000070U);
                WR1_PROG(REG_1018H, 0x000003e0U);
                WR1_PROG(REG_1020H, 0x00000250U);

                WR1_PROG(REG_1004H, 0x04040006U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000001b0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000480U);
                WR1_PROG(REG_1010H, 0x00000008U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0x0e842f90U, 0x4cd32a99U, 0xd12eafc3U, 0x1e47649cU);
            }

            WR1_PROG(REG_1010H, 0x00000008U);

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
            WR1_PROG(REG_1420H, change_endian_long(0x00000019U));
            WR1_PROG(REG_1458H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                HW_SCE_p_func101(0x750de3a8U, 0x46157684U, 0xbb47bdfaU, 0xab504981U);
                HW_SCE_p_func402_r1();

                HW_SCE_p_func404();

                WR1_PROG(REG_1600H, 0x00002d00U);

                HW_SCE_p_func101(0x311b7465U, 0x9f4a0949U, 0xef1fe782U, 0xc6c52212U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x08000909U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000ca0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000006b0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000cf0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000700U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000d40U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1444H, 0x000007c7U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80880001U);
            for (iLoop = 8U; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Signature[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

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

            WR1_PROG(REG_1404H, 0x12800000U);
            WR1_PROG(REG_1400H, 0x00c00021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000250U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000010U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
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
            WR1_PROG(REG_1018H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000980U);

            WR1_PROG(REG_1004H, 0x04040005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1010H, 0x00000008U);

            HW_SCE_p_func100(0xe5a858e3U, 0xffbf2c7cU, 0x6ac3ec00U, 0x2d98ebe7U);
            HW_SCE_p_func401_r1(InData_DomainParam);

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

            WR1_PROG(REG_1404H, 0x19600000U);
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
            WR1_PROG(REG_1420H, change_endian_long(0x00000119U));
            WR1_PROG(REG_1458H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                HW_SCE_p_func101(0xfd589218U, 0xab975a25U, 0xaa527c42U, 0x6d21e2ceU);
                HW_SCE_p_func402_r1();

                HW_SCE_p_func404();

                WR1_PROG(REG_1600H, 0x00002d00U);

                HW_SCE_p_func101(0xc8c6f90aU, 0xa7b3ee20U, 0x11e367d3U, 0x358f02faU);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x08000909U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1014H, 0x00000660U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000750U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000006b0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x000007a0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000700U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x000007f0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1400H, 0x00c00021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000ca0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x04040006U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000ca0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000ca0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000570U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000cf0U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x000005c0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000d40U);
            WR1_PROG(REG_1018H, 0x00000b10U);
            WR1_PROG(REG_1020H, 0x00000610U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func404();

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

            WR1_PROG(REG_1004H, 0x04040006U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x7410c50fU, 0xba19661bU, 0xd7a3e4b5U, 0xaeac1fe4U);
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

            WR1_PROG(REG_1404H, 0x12300000U);
            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x14100000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0001dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000c50U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000c50U);
            WR1_PROG(REG_1018H, 0x00000250U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0xf1b7799aU, 0x66bc1b04U, 0xb7d25a05U, 0x89397042U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x35847fa3U, 0xaf6ca66eU, 0x2fef84c6U, 0xacf79a6cU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0x28c520a7U, 0x01ddc6caU, 0x60be3908U, 0x96ff583bU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
