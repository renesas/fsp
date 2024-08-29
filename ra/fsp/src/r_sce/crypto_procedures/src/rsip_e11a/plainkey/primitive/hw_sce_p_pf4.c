/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A60000U);

    HW_SCE_p_func100(0xe1655fa9U, 0x10cb5f07U, 0x5e631d58U, 0xe8449f6cU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xb83e9ab0U, 0x987328edU, 0xceca149bU, 0x1ef0a176U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func070(InData_DomainParam);

        WR1_PROG(REG_A0H, 0x20010000U);
        WR1_PROG(REG_B0H, 0x00002428U);

        HW_SCE_p_func100(0xa09dae7cU, 0xdc3771b6U, 0x67cedc83U, 0x75e3b6ceU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x370c5e16U, 0x6dbab032U, 0xf97621dbU, 0xec47788bU);
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
        HW_SCE_p_func100(0x3eb27e2dU, 0x4ca3bc36U, 0x287a15e6U, 0x871cc18dU);
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

            HW_SCE_p_func100(0x136e4fd0U, 0x2a3d4709U, 0xe229ac61U, 0x3df6b00eU);
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

                HW_SCE_p_func101(0xbe35432dU, 0x19b4ccb6U, 0xdd428c97U, 0x4020f0e9U);
            }
            else
            {
                WR1_PROG(REG_B4H, 0x0019001eU);
                WR1_PROG(REG_B8H, 0x00270000U);

                WR1_PROG(REG_A4H, 0x04040009U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                HW_SCE_p_func101(0xe8d967ceU, 0xd5fb32d9U, 0xd2d066f7U, 0x08f7babaU);
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

            HW_SCE_p_func101(0xe2c56e03U, 0xa85e461bU, 0x367e12e0U, 0x31c60900U);
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

        HW_SCE_p_func100(0x83026fa5U, 0x88c9d714U, 0x6e07060dU, 0x8066febbU);
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

            HW_SCE_p_func101(0x83faaa75U, 0x8b66b906U, 0x057f0ce1U, 0xcf1ea8abU);
        }
        else
        {
            WR1_PROG(REG_B4H, 0x0019001eU);
            WR1_PROG(REG_B8H, 0x00270000U);

            WR1_PROG(REG_A4H, 0x04040009U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func101(0x3f065c13U, 0x1630f2d1U, 0x850fd28eU, 0x983ec30aU);
        }

        WR1_PROG(REG_B4H, 0x000f0027U);
        WR1_PROG(REG_B8H, 0x00320000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func071(InData_DomainParam);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xdd1eee67U, 0xd8f080dfU, 0x192fa9f0U, 0xcd5f776cU);
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

                WR1_PROG(REG_94H, 0x0000b4c0U);
                WR1_PROG(REG_94H, 0x00000017U);

                WR1_PROG(REG_14H, 0x000000a7U);
                WR1_PROG(REG_9CH, 0x800100e0U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0x7897f6a1U, 0x43fbffa6U, 0xeb4ac5e4U, 0x16faea81U);
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

                HW_SCE_p_func101(0x8844ca5aU, 0x1aa078c2U, 0xf1c8b4dcU, 0x476d2b6cU);
            }
            else
            {
                HW_SCE_p_func100(0x2c009193U, 0x29108391U, 0x139489cdU, 0x1e5f9a02U);
                WR1_PROG(REG_B0H, 0x00001832U);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

                HW_SCE_p_func101(0x451b2d83U, 0xd6e99100U, 0xc636adf1U, 0x71b67122U);
            }

            HW_SCE_p_func100(0xe5a0067bU, 0xccd9c8efU, 0x3d6bc5e4U, 0x24eacce3U);
            WR1_PROG(REG_B0H, 0x00001828U);
            WR1_PROG(REG_08H, 0x00006022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

            HW_SCE_p_func100(0x1b40fbfeU, 0x83c7061eU, 0x6aca4c74U, 0x6e5e3705U);
            WR1_PROG(REG_B0H, 0x0000182dU);
            WR1_PROG(REG_08H, 0x00006022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_PubKey[8]);

            HW_SCE_p_func102(0x35653737U, 0x731875a7U, 0xf3dd8235U, 0x5c852523U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
