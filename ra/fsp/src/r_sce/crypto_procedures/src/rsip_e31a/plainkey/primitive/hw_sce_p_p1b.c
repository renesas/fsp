/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Ed25519ScalarMultiplicationSub (const uint32_t InData_KeyMode[],
                                                 const uint32_t InData_KeyIndex[],
                                                 const uint32_t InData_Key[],
                                                 const uint32_t InData_XYZ[],
                                                 const uint32_t InData_DomainParam[],
                                                 uint32_t       OutData_XYZ[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x001b0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xbc257e39U, 0x2a7b6d57U, 0x6073db63U, 0x19be25d0U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000001bU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xfb1dca3bU, 0x40fe2e22U, 0x6ddef056U, 0xb2b9ecdeU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000027U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000001bU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xed9c8d86U, 0x89b7dedaU, 0x879be45fU, 0xaadb8676U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x000014a0U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0x53bc6604U, 0x9eea181cU, 0x7b5cca45U, 0x93d07f10U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x000014a0U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_Key[0]);

        HW_SCE_p_func101(0xd42e63faU, 0x523c3df3U, 0x90cd9a3fU, 0xc7395f61U);
    }

    HW_SCE_p_func100(0xa99d6acaU, 0xba109224U, 0xa8997a38U, 0x4503f9f7U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xd9aaa934U, 0xc099c26dU, 0xcf954263U, 0x01f8fd3fU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func406(InData_DomainParam);

        WR1_PROG(REG_B0H, 0x00001487U);
        WR1_PROG(REG_00H, 0x00c00021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001446U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_XYZ[0]);

        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x0000144bU);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_XYZ[8]);

        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001450U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_XYZ[16]);

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
        WR1_PROG(REG_2CH, change_endian_long(0x0000001bU));
        WR1_PROG(REG_24H, 0x00000000U);

        for (iLoop = 0U; iLoop < 256U; iLoop++)
        {
            HW_SCE_p_func405();

            HW_SCE_p_func403();

            HW_SCE_p_func101(0x6aae7d51U, 0x449f9b4cU, 0xfdc594f4U, 0xa8a51559U);
            HW_SCE_p_func402();

            HW_SCE_p_func404();

            WR1_PROG(REG_94H, 0x00002cc0U);

            HW_SCE_p_func101(0x6d14d760U, 0xf4e5c674U, 0x17db44d4U, 0x9e494d16U);
        }

        WR1_PROG(REG_94H, 0x380088c0U);
        WR1_PROG(REG_94H, 0x00000100U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        WR1_PROG(REG_40H, 0x00402000U);

        HW_SCE_p_func100(0x5e275997U, 0xbe42fa7eU, 0xf0241e7eU, 0x1ac5645fU);
        WR1_PROG(REG_B0H, 0x00001864U);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_XYZ[0]);

        HW_SCE_p_func100(0x6c233f5cU, 0xe46693ccU, 0x58a1acb6U, 0x680d15b4U);
        WR1_PROG(REG_B0H, 0x00001869U);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_XYZ[8]);

        HW_SCE_p_func100(0xf4616bfaU, 0xd576ea54U, 0x82591216U, 0xd480a68aU);
        WR1_PROG(REG_B0H, 0x0000186eU);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_XYZ[16]);

        HW_SCE_p_func102(0x4490da4bU, 0x199970cbU, 0x838ce0afU, 0xb2f4dddeU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
