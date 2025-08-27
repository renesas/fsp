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

    WR1_PROG(REG_14H, 0x000007c5U);
    WR1_PROG(REG_B0H, 0x000014a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_Key[0]);

    WR1_PROG(REG_14H, 0x000001c7U);
    WR1_PROG(REG_9CH, 0x80020000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_MsgLen[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_MsgLen[1]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x00000842U);

    WR1_PROG(REG_94H, 0x30008800U);
    WR1_PROG(REG_94H, 0xffffffffU);
    WR1_PROG(REG_94H, 0x00030020U);
    WR1_PROG(REG_94H, 0x3000a820U);
    WR1_PROG(REG_94H, 0xfffffdffU);
    WR1_PROG(REG_94H, 0x00050020U);
    WR1_PROG(REG_94H, 0x1000d040U);
    WR1_PROG(REG_94H, 0x00000080U);
    WR1_PROG(REG_94H, 0x00000080U);

    WR1_PROG(REG_94H, 0x38008840U);
    WR1_PROG(REG_94H, 0x00000001U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xbd2f8c23U, 0xbc34642dU, 0xd4bf289eU, 0x41938af1U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x35c41ac5U, 0x51579566U, 0x86863d6bU, 0x902b231cU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x0000149bU);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_Signature[0]);

        HW_SCE_p_func100(0x1fa4f9a4U, 0x2af78a3eU, 0x009ebf73U, 0x1ff52340U);
        WR1_PROG(REG_94H, 0x00000842U);
        WR1_PROG(REG_94H, 0x0c00a420U);
        WR1_PROG(REG_94H, 0x00000200U);
        WR1_PROG(REG_94H, 0x00802402U);

        WR1_PROG(REG_9CH, 0x81020000U);
        WR1_PROG(REG_08H, 0x0000500aU);
        WAIT_STS(REG_08H, 30, 1);
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
        WR1_PROG(REG_00H, 0x01430021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x000018a5U);
        WR1_PROG(REG_00H, 0x01430021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

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
        WR1_PROG(REG_00H, 0x03450021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func409();

        WR1_PROG(REG_B0H, 0x000014afU);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x81880001U);
        WR1_PROG(REG_00H, 0x00c90021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_94H, 0x00000842U);
        WR1_PROG(REG_9CH, 0x80880001U);
        WR1_PROG(REG_00H, 0x03450021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func409();

        WR1_PROG(REG_B0H, 0x000014aaU);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x81880001U);
        WR1_PROG(REG_00H, 0x00c90021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func406(InData_DomainParam);

        WR1_PROG(REG_B0H, 0x00001487U);
        WR1_PROG(REG_00H, 0x00c00021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000841U);
        WR1_PROG(REG_9CH, 0x80020000U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_B0H, 0x000004b1U);
        WR1_PROG(REG_9CH, 0x81020000U);
        WR1_PROG(REG_00H, 0x00c90009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00001423U);
        WR1_PROG(REG_14H, 0x000007a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U),
                 change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U),
                 change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));

        WR1_PROG(REG_B4H, 0x00aa0023U);
        WR1_PROG(REG_B8H, 0x0028000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x001e00afU);
        WR1_PROG(REG_B8H, 0x0023000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001482U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x00820023U);
        WR1_PROG(REG_B8H, 0x003c000aU);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0028003cU);
        WR1_PROG(REG_B8H, 0x00a0000aU);

        WR1_PROG(REG_A4H, 0x04040005U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_94H, 0x00000821U);

        WR1_PROG(REG_B0H, 0x000018a5U);
        WR1_PROG(REG_9CH, 0x80880001U);
        WR1_PROG(REG_00H, 0x03430021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func409();

        HW_SCE_p_func100(0x62c5e545U, 0xaff1adb5U, 0xdd87903fU, 0xace484fcU);

        WR1_PROG(REG_94H, 0x00000800U);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_94H, 0x02003801U);
        WR1_PROG(REG_94H, 0x00003440U);
        WR1_PROG(REG_94H, 0x00076800U);
        WR1_PROG(REG_94H, 0x00003460U);

        WR1_PROG(REG_94H, 0x00008c40U);
        WR1_PROG(REG_94H, 0x0000007FU);
        WR1_PROG(REG_94H, 0x02003c41U);

        WR1_PROG(REG_94H, 0x00000800U);
        WR1_PROG(REG_9CH, 0x81880000U);

        WR1_PROG(REG_B0H, 0x00001423U);
        WR1_PROG(REG_00H, 0x00c90021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000840U);
        WR1_PROG(REG_9CH, 0x80020000U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_B0H, 0x000004b1U);
        WR1_PROG(REG_9CH, 0x81020000U);
        WR1_PROG(REG_00H, 0x00c90009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x00190023U);
        WR1_PROG(REG_B8H, 0x004b0005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x004b004bU);
        WR1_PROG(REG_B8H, 0x00230005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001482U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x00820019U);
        WR1_PROG(REG_B8H, 0x00280005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00280023U);
        WR1_PROG(REG_B8H, 0x002d0005U);

        WR1_PROG(REG_A4H, 0x04040006U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00140023U);
        WR1_PROG(REG_B8H, 0x00370005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00280037U);
        WR1_PROG(REG_B8H, 0x00320005U);

        WR1_PROG(REG_A4H, 0x04040005U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00820032U);
        WR1_PROG(REG_B8H, 0x00230005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001428U);
        WR1_PROG(REG_00H, 0x00c0001dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

        WR1_PROG(REG_B4H, 0x00280005U);
        WR1_PROG(REG_B8H, 0x003c0005U);

        WR1_PROG(REG_A4H, 0x04040006U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x003c0023U);
        WR1_PROG(REG_B8H, 0x00280005U);

        WR1_PROG(REG_A4H, 0x04040000U);
        WR1_PROG(REG_08H, 0x00020000U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func100(0x9ec066e1U, 0x1b8099b4U, 0x113ad9bbU, 0x9caacc57U);
        WR1_PROG(REG_B4H, 0x0028002dU);
        WR1_PROG(REG_B8H, 0x00370005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x00001423U);
        WR1_PROG(REG_14H, 0x000007a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0x0FFFFFFFU), change_endian_long(0xFFFFFFFFU),
                 change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU));
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFFU),
                 change_endian_long(0xFFFFFFFFU), change_endian_long(0xFFFFFFFEU));

        WR1_PROG(REG_B4H, 0x00230037U);
        WR1_PROG(REG_B8H, 0x003c0005U);

        WR1_PROG(REG_A4H, 0x04040000U);
        WR1_PROG(REG_08H, 0x00020000U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);
        WR1_PROG(REG_40H, 0x00000d00U);

        WR1_PROG(REG_B4H, 0x0019003cU);
        WR1_PROG(REG_B8H, 0x002d0005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x002d002dU);
        WR1_PROG(REG_B8H, 0x00320005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00820032U);
        WR1_PROG(REG_B8H, 0x002d0005U);

        WR1_PROG(REG_A4H, 0x04040002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00370005U);
        WR1_PROG(REG_B8H, 0x00230005U);

        WR1_PROG(REG_A4H, 0x04040006U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x0037002dU);
        WR1_PROG(REG_B8H, 0x00820000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        WR1_PROG(REG_B4H, 0x002d0037U);
        WR1_PROG(REG_B8H, 0x00820000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0xea964a81U, 0x94149761U, 0xdfc36ae7U, 0x8074db9fU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_B4H, 0x0023002dU);
            WR1_PROG(REG_B8H, 0x00820000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            WR1_PROG(REG_B4H, 0x002d0023U);
            WR1_PROG(REG_B8H, 0x00820000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func100(0x7cf28299U, 0x9cd1ca6dU, 0x7a038a90U, 0xe086b09aU);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                HW_SCE_p_func101(0xa4821d9aU, 0x6588428fU, 0x3b74af10U, 0x35e113cdU);
            }
            else
            {
                WR1_PROG(REG_B4H, 0x0019003cU);
                WR1_PROG(REG_B8H, 0x00230005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B0H, 0x00001428U);
                WR1_PROG(REG_14H, 0x000007a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_PROG(REG_2CH, change_endian_long(0x2B832480U), change_endian_long(0x4FC1DF0BU),
                         change_endian_long(0x2B4D0099U), change_endian_long(0x3DFBD7A7U));
                WAIT_STS(REG_14H, 31, 1);
                WR4_PROG(REG_2CH, change_endian_long(0x2F431806U), change_endian_long(0xAD2FE478U),
                         change_endian_long(0xC4EE1B27U), change_endian_long(0x4A0EA0B0U));

                WR1_PROG(REG_B4H, 0x00280023U);
                WR1_PROG(REG_B8H, 0x003c0005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0xed08d7a1U);

                HW_SCE_p_func101(0x2e47bf58U, 0xfaf4642cU, 0x3429cfefU, 0xf78f621dU);
            }
        }
        else
        {
            WR1_PROG(REG_94H, 0x0000b400U);
            WR1_PROG(REG_94H, 0xed08d7a1U);

            HW_SCE_p_func101(0x09e9a5b6U, 0xa7d7bca3U, 0x660d8db9U, 0x69ba9acbU);
        }

        WR1_PROG(REG_94H, 0x38008800U);
        WR1_PROG(REG_94H, 0xed08d7a1U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        HW_SCE_p_func100(0x725465e3U, 0x04e51c60U, 0x58d875e4U, 0xe86b6772U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x1d2f9683U, 0xcb0f0f68U, 0xd0b5a84fU, 0x14fdfa37U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_B0H, 0x0000183cU);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            WR1_PROG(REG_00H, 0x03430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x0000b420U);
            WR1_PROG(REG_94H, 0x0000001fU);
            WR1_PROG(REG_94H, 0x02003841U);

            WR1_PROG(REG_94H, 0x00008c40U);
            WR1_PROG(REG_94H, 0x00000001U);

            WR1_PROG(REG_94H, 0x38000843U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            HW_SCE_p_func100(0x273c87c8U, 0x41b2cf22U, 0x1d1146e2U, 0x6cd2f740U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_B4H, 0x0019003cU);
                WR1_PROG(REG_B8H, 0x00460005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                HW_SCE_p_func101(0xa9f6ec95U, 0xbe14f983U, 0x0544488dU, 0xf8baaf9dU);
            }
            else
            {
                WR1_PROG(REG_B4H, 0x003c0005U);
                WR1_PROG(REG_B8H, 0x00230005U);

                WR1_PROG(REG_A4H, 0x04040006U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00190023U);
                WR1_PROG(REG_B8H, 0x00460005U);

                WR1_PROG(REG_A4H, 0x04040002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                HW_SCE_p_func101(0x615c9235U, 0x021d69aaU, 0x9fb7ccd4U, 0xd208d563U);
            }

            WR1_PROG(REG_B0H, 0x00001450U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001464U);
            WR1_PROG(REG_00H, 0x00c00021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001469U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x0000146eU);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x0000148cU);
            WR1_PROG(REG_00H, 0x00c00021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001491U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001496U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x000018a0U);
            WR1_PROG(REG_94H, 0x00000800U);
            WR1_PROG(REG_9CH, 0x80880000U);
            WR1_PROG(REG_00H, 0x03430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x000008c6U);
            WR1_PROG(REG_94H, 0x00000800U);

            WR1_PROG(REG_94H, 0x0000b420U);
            WR1_PROG(REG_94H, 0x0000001fU);

            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000001U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000019U));
            WR1_PROG(REG_24H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                HW_SCE_p_func101(0x5714053bU, 0xcf5d6141U, 0x593595afU, 0x5607b425U);
                HW_SCE_p_func402();

                HW_SCE_p_func404();

                WR1_PROG(REG_94H, 0x00002cc0U);

                HW_SCE_p_func101(0x8698711eU, 0xd588a680U, 0xf2220f86U, 0xfbb7a316U);
            }

            WR1_PROG(REG_94H, 0x380088c0U);
            WR1_PROG(REG_94H, 0x00000100U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_B4H, 0x00870064U);
            WR1_PROG(REG_B8H, 0x00a50000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00870069U);
            WR1_PROG(REG_B8H, 0x00aa0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x0087006eU);
            WR1_PROG(REG_B8H, 0x00af0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x0087009bU);
            WR1_PROG(REG_B8H, 0x00a00000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

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
            WR1_PROG(REG_00H, 0x00c90021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00000841U);
            WR1_PROG(REG_9CH, 0x80020000U);
            WR1_PROG(REG_00H, 0x03430009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_B0H, 0x000004b1U);
            WR1_PROG(REG_9CH, 0x81020000U);
            WR1_PROG(REG_00H, 0x00c90009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001423U);
            WR1_PROG(REG_14H, 0x000007a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0EEC73D2U), change_endian_long(0x17F5BE65U),
                     change_endian_long(0xCB5C63AAU), change_endian_long(0x97A331B5U));
            WAIT_STS(REG_14H, 31, 1);
            WR4_PROG(REG_2CH, change_endian_long(0x0665E1DBU), change_endian_long(0x6EABA043U),
                     change_endian_long(0xF98B4BAAU), change_endian_long(0x9C78F954U));

            WR1_PROG(REG_B0H, 0x00001428U);
            WR1_PROG(REG_00H, 0x00c00021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B4H, 0x00230028U);
            WR1_PROG(REG_B8H, 0x002d000aU);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x001e009bU);
            WR1_PROG(REG_B8H, 0x0023000aU);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B0H, 0x00001482U);
            WR1_PROG(REG_00H, 0x00c0001dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

            WR1_PROG(REG_B4H, 0x00820023U);
            WR1_PROG(REG_B8H, 0x003c000aU);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x002d003cU);
            WR1_PROG(REG_B8H, 0x009b000aU);

            WR1_PROG(REG_A4H, 0x04040005U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func401(InData_DomainParam);

            WR1_PROG(REG_B0H, 0x00000840U);
            WR1_PROG(REG_9CH, 0x80020000U);
            WR1_PROG(REG_00H, 0x03430009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_B0H, 0x000004b1U);
            WR1_PROG(REG_9CH, 0x81020000U);
            WR1_PROG(REG_00H, 0x00c90009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001450U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001464U);
            WR1_PROG(REG_00H, 0x00c00021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00001469U);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x0000146eU);
            WR1_PROG(REG_00H, 0x00c00015U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000026U));
            WR1_PROG(REG_00H, 0x00c00009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x0000189bU);
            WR1_PROG(REG_94H, 0x00000800U);
            WR1_PROG(REG_9CH, 0x80880000U);
            WR1_PROG(REG_00H, 0x03430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x000008c6U);
            WR1_PROG(REG_94H, 0x00000800U);

            WR1_PROG(REG_94H, 0x0000b420U);
            WR1_PROG(REG_94H, 0x0000001fU);

            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000001U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000119U));
            WR1_PROG(REG_24H, 0x00000000U);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                HW_SCE_p_func405();

                HW_SCE_p_func403();

                HW_SCE_p_func101(0x54082ad4U, 0x59bddeb6U, 0x4d89865bU, 0xa262b5d7U);
                HW_SCE_p_func402();

                HW_SCE_p_func404();

                WR1_PROG(REG_94H, 0x00002cc0U);

                HW_SCE_p_func101(0x675ea1cfU, 0x150fe454U, 0xec6ee67eU, 0x31fca300U);
            }

            WR1_PROG(REG_94H, 0x380088c0U);
            WR1_PROG(REG_94H, 0x00000100U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_B4H, 0x00870064U);
            WR1_PROG(REG_B8H, 0x00730000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00870069U);
            WR1_PROG(REG_B8H, 0x00780000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x0087006eU);
            WR1_PROG(REG_B8H, 0x007d0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00a50087U);
            WR1_PROG(REG_B8H, 0x00280005U);

            WR1_PROG(REG_A4H, 0x04040006U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00870028U);
            WR1_PROG(REG_B8H, 0x00a50000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x008700a5U);
            WR1_PROG(REG_B8H, 0x00550000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x008700aaU);
            WR1_PROG(REG_B8H, 0x005a0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x008700afU);
            WR1_PROG(REG_B8H, 0x005f0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func404();

            WR1_PROG(REG_B4H, 0x00870064U);
            WR1_PROG(REG_B8H, 0x00550000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00870069U);
            WR1_PROG(REG_B8H, 0x005a0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x0087006eU);
            WR1_PROG(REG_B8H, 0x005f0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func100(0x07ea25cdU, 0xf04cfef3U, 0x8b1d8b8bU, 0xf5e9c98eU);

            WR1_PROG(REG_B0H, 0x00001482U);
            WR1_PROG(REG_00H, 0x00c0001dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

            WR1_PROG(REG_B4H, 0x0082005fU);
            WR1_PROG(REG_B8H, 0x00230005U);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B0H, 0x0000142dU);
            WR1_PROG(REG_00H, 0x00c0001dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

            WR1_PROG(REG_B4H, 0x002d0005U);
            WR1_PROG(REG_B8H, 0x00280000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00280023U);
            WR1_PROG(REG_B8H, 0x002d0005U);

            WR1_PROG(REG_A4H, 0x04040000U);
            WR1_PROG(REG_08H, 0x00020000U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);
            WR1_PROG(REG_40H, 0x00000d00U);

            WR1_PROG(REG_B4H, 0x002d0055U);
            WR1_PROG(REG_B8H, 0x00230005U);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x002d005aU);
            WR1_PROG(REG_B8H, 0x00280005U);

            WR1_PROG(REG_A4H, 0x04040002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B0H, 0x00001823U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            WR1_PROG(REG_00H, 0x03430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x0000b420U);
            WR1_PROG(REG_94H, 0x0000001cU);
            WR1_PROG(REG_94H, 0x00003841U);

            WR1_PROG(REG_94H, 0x001f6c42U);

            WR1_PROG(REG_B0H, 0x00001828U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80880001U);
            WR1_PROG(REG_00H, 0x03430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x00003801U);

            WR1_PROG(REG_94H, 0x00008c00U);
            WR1_PROG(REG_94H, 0x7fffffffU);

            WR1_PROG(REG_94H, 0x00001002U);

            WR1_PROG(REG_94H, 0x00003c01U);

            HW_SCE_p_func409();

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_B0H, 0x00001423U);
            WR1_PROG(REG_9CH, 0x81880001U);
            WR1_PROG(REG_00H, 0x00c90021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B4H, 0x008700a0U);
            WR1_PROG(REG_B8H, 0x009b0000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x009b0023U);
            WR1_PROG(REG_B8H, 0x00280000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            WR1_PROG(REG_B4H, 0x0023009bU);
            WR1_PROG(REG_B8H, 0x00280000U);

            WR1_PROG(REG_A4H, 0x0404000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func100(0x6b1c214aU, 0x1ad52054U, 0x2732f8d7U, 0xfad1ccb7U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xc22bf72aU, 0xc7886ba0U, 0xa0bdc112U, 0xb20f0715U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0x1cf4a18aU, 0x598668bfU, 0x76fab73eU, 0x4ab15bc3U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
