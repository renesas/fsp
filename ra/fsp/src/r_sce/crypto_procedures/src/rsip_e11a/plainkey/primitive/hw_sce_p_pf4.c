/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub (const uint32_t InData_KeyMode[],
                                               const uint32_t InData_CurveType[],
                                               const uint32_t InData_DomainParam[],
                                               uint32_t       OutData_PubKey[],
                                               uint32_t       OutData_PrivKeyIndex[],
                                               uint32_t       OutData_PrivKey[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f40001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    HW_SCE_p_func070_r1(InData_DomainParam);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00002428U);

    HW_SCE_p_func100(0x095b5341U, 0x00d38bdfU, 0x159a754fU, 0xf75398c2U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x1aca66c0U, 0x6e7e5f9cU, 0x89697765U, 0x047eb159U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x00010009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func100(0xeb3e3707U, 0x9acec535U, 0x434bd9edU, 0x3a9b8d91U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    WR1_PROG(REG_00H, 0x00c0001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

    WR1_PROG(REG_B4H, 0x000f000aU);
    WR1_PROG(REG_B8H, 0x00140000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B0H, 0x0000143cU);
    WR1_PROG(REG_00H, 0x00c0001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

    WR1_PROG(REG_B0H, 0x00001419U);
    WR1_PROG(REG_00H, 0x00c00021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_94H, 0x00000863U);
    WR1_PROG(REG_94H, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        WR1_PROG(REG_B4H, 0x00140027U);
        WR1_PROG(REG_B8H, 0x001e0000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x0000081aU);
        WR1_PROG(REG_9CH, 0x80020000U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000884U);

        WR1_PROG(REG_94H, 0x38000c21U);
        WR1_PROG(REG_94H, 0x2000d080U);

        WR1_PROG(REG_94H, 0x38000c63U);
        WR1_PROG(REG_94H, 0x1000d081U);

        WR1_PROG(REG_94H, 0x38008880U);
        WR1_PROG(REG_94H, 0x00000003U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        HW_SCE_p_func100(0xf162ada1U, 0x32395b22U, 0x6b24049bU, 0x566dd424U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_B4H, 0x0019001eU);
            WR1_PROG(REG_B8H, 0x004b0000U);

            WR1_PROG(REG_A4H, 0x04040009U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func101(0xf6795a8cU, 0x06bb4188U, 0x987ee520U, 0x94d06473U);
        }
        else
        {
            WR1_PROG(REG_B4H, 0x0019001eU);
            WR1_PROG(REG_B8H, 0x00270000U);

            WR1_PROG(REG_A4H, 0x04040009U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func101(0xea5dcde1U, 0x67607120U, 0xe0686590U, 0x6f5bb77fU);
        }

        WR1_PROG(REG_B4H, 0x003c002bU);
        WR1_PROG(REG_B8H, 0x001e0000U);

        WR1_PROG(REG_A4H, 0x04040007U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x003c0027U);
        WR1_PROG(REG_B8H, 0x00230000U);

        WR1_PROG(REG_A4H, 0x04040007U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x0000081fU);
        WR1_PROG(REG_9CH, 0x80020040U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x002b0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x001a0023U);
        WR1_PROG(REG_B8H, 0x00270000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_94H, 0x00002ca0U);

        HW_SCE_p_func101(0x8f1f10a1U, 0x08e13779U, 0x2a52e3cdU, 0x6497f3f1U);
    }

    WR1_PROG(REG_94H, 0x380088a0U);
    WR1_PROG(REG_94H, 0x00000040U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    WR1_PROG(REG_40H, 0x00402000U);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_B4H, 0x00140027U);
    WR1_PROG(REG_B8H, 0x001e0000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B0H, 0x0000081aU);
    WR1_PROG(REG_9CH, 0x80020000U);
    WR1_PROG(REG_00H, 0x03430009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x00000884U);

    WR1_PROG(REG_94H, 0x38000c21U);
    WR1_PROG(REG_94H, 0x2000d080U);

    WR1_PROG(REG_94H, 0x38000c63U);
    WR1_PROG(REG_94H, 0x1000d081U);

    WR1_PROG(REG_94H, 0x38008880U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x54f77d72U, 0x03baed44U, 0x7c8a967fU, 0x94e59fddU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x004b0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func101(0x74e79011U, 0x5845bf78U, 0x6ef80091U, 0x2d4db133U);
    }
    else
    {
        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x00270000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func101(0xf159175dU, 0xab9a327cU, 0x8c3b1f34U, 0xbb476ff8U);
    }

    WR1_PROG(REG_B4H, 0x000f0027U);
    WR1_PROG(REG_B8H, 0x00320000U);

    WR1_PROG(REG_A4H, 0x04040009U);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_94H, 0x00003406U);

    HW_SCE_p_func071_r1(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xaee7665dU, 0xdaf92cd8U, 0xb36f75ebU, 0xa7b10b10U);
    HW_SCE_p_func088();

    HW_SCE_p_func100(0xcb83c991U, 0xd0e8b383U, 0xa9aa384cU, 0xfce6e1a7U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf8b93f4bU, 0xf90039dcU, 0x82807fd8U, 0xae8f365cU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010000U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x38000c00U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        HW_SCE_p_func100(0x17e3b02bU, 0xc25d4013U, 0x2b23b657U, 0x1f764db1U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);
        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0xc3e968a1U, 0xa0e12941U, 0x30a4b25eU, 0x674fcc09U);
            HW_SCE_p_func103();
            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D0H, 0x0c200104U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_9CH, 0x80010000U);
            WR1_PROG(REG_00H, 0x03410005U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_00H, 0x0001000dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x000034c0U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x291a0ca3U, 0x28a82454U, 0x476b77b1U, 0xf6c53132U);
            HW_SCE_p_func043();

            HW_SCE_p_func074();

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x59a1a407U, 0x60874020U, 0x4ecc1000U, 0x54ba8c6fU);
            HW_SCE_p_func044();

            HW_SCE_p_func100(0x2b316d31U, 0xd922edaaU, 0x79ce9339U, 0x46be6298U);
            WR1_PROG(REG_B0H, 0x00001832U);

            WR1_PROG(REG_D4H, 0x40000100U);
            WR1_PROG(REG_D0H, 0xe7009d07U);
            WR1_PROG(REG_00H, 0x00430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_08H, 0x00001022U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);

            HW_SCE_p_func100(0xce5dbb96U, 0xae78b31cU, 0x1cf6e125U, 0x835302f5U);
            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D0H, 0x0c000104U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x09108105U);
            WR1_PROG(REG_00H, 0x00410011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

            HW_SCE_p_func100(0x4b4722e5U, 0x76edacf2U, 0xbba4e3d1U, 0xa5d9f0c8U);
            WR1_PROG(REG_9CH, 0x81010000U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

            HW_SCE_p_func101(0x77ad81deU, 0x3c1b16b5U, 0xe263e21fU, 0x4ba1346fU);
        }
        else
        {
            HW_SCE_p_func100(0x2c009193U, 0x29108391U, 0x139489cdU, 0x1e5f9a02U);
            WR1_PROG(REG_B0H, 0x00001832U);
            WR1_PROG(REG_08H, 0x00006022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

            HW_SCE_p_func101(0xf81dc7f5U, 0x50629fbfU, 0xbcab0ea1U, 0x01fe5642U);
        }

        HW_SCE_p_func100(0xc7644ce3U, 0x97c3c8cbU, 0x587698bbU, 0xe12f901dU);
        WR1_PROG(REG_B0H, 0x00001828U);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

        HW_SCE_p_func100(0xcfb6d08aU, 0xd71b381eU, 0x2a5ccc11U, 0x0575dc32U);
        WR1_PROG(REG_B0H, 0x0000182dU);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[8]);

        HW_SCE_p_func102(0x12ecc7b7U, 0xf2a39a12U, 0xfb4787c5U, 0x096427afU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
