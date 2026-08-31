/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

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

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000027U);

    static const uint32_t Param_p1b_sub100_001[] =
    {
        0x92ab756bU, 0x1f393ea3U, 0xd3e511e1U, 0x11ba5ff9U, 0x0000001bU, 0xbde8407fU, 0xce6bcc8eU, 0xbe1dfff7U,
        0x92a91aabU, 0x0000001bU, 0x5afcd62bU, 0x186c5110U, 0x0e622b98U, 0xcbe51015U, 0x000014a0U, 0x53bc6604U,
        0x9eea181cU, 0x7b5cca45U, 0x93d07f10U, 0x000014a0U, 0x915c2e7dU, 0x37e71fe2U, 0x12f1bbcdU, 0x76da5d40U,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_p1b_sub100_001, RSIP_SEL_BIT_LENGTH_256);

    static const uint32_t Param_p1b_func100_001[] =
    {
        0xa99d6acaU, 0xba109224U, 0xa8997a38U, 0x4503f9f7U,
    };
    HW_SCE_p_func100(Param_p1b_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p1b_func102_001[] =
        {
            0xd9aaa934U, 0xc099c26dU, 0xcf954263U, 0x01f8fd3fU,
        };
        HW_SCE_p_func102(Param_p1b_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func406(InData_DomainParam);

        WR1_PROG(REG_B0H, 0x00001487U);
        HW_SCE_p_func_sub003(0x00c00021U);

        HW_SCE_p_func_sub017(0x000007c5U, 0x00001446U);
        WR8_ADDR(REG_2CH, &InData_XYZ[0]);

        HW_SCE_p_func_sub017(0x000007c5U, 0x0000144bU);
        WR8_ADDR(REG_2CH, &InData_XYZ[8]);

        HW_SCE_p_func_sub017(0x000007c5U, 0x00001450U);
        WR8_ADDR(REG_2CH, &InData_XYZ[16]);

        WR1_PROG(REG_B0H, 0x00000840U);
        WR1_PROG(REG_9CH, 0x80020000U);
        HW_SCE_p_func_sub003(0x03430009U);
        WR1_PROG(REG_B0H, 0x000004b1U);
        WR1_PROG(REG_9CH, 0x81020000U);
        HW_SCE_p_func_sub003(0x00c90009U);

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
        WR1_PROG(REG_2CH, change_endian_long(0x0000001bU));
        WR1_PROG(REG_24H, 0x00000000U);

        for (iLoop = 0U; iLoop < 256U; iLoop++)
        {
            HW_SCE_p_func405();

            HW_SCE_p_func403();

            static const uint32_t Param_p1b_func101_001[] =
            {
                0x6aae7d51U, 0x449f9b4cU, 0xfdc594f4U, 0xa8a51559U,
            };
            HW_SCE_p_func101(Param_p1b_func101_001);
            HW_SCE_p_func402();

            HW_SCE_p_func404();

            WR1_PROG(REG_94H, 0x00002cc0U);

            static const uint32_t Param_p1b_func101_002[] =
            {
                0x6d14d760U, 0xf4e5c674U, 0x17db44d4U, 0x9e494d16U,
            };
            HW_SCE_p_func101(Param_p1b_func101_002);
        }

        HW_SCE_p_func_sub006(0x380088c0U, 0x00000100U, 0x00270000U);

        WR1_PROG(REG_40H, 0x00402000U);

        static const uint32_t Param_p1b_func100_002[] =
        {
            0x5e275997U, 0xbe42fa7eU, 0xf0241e7eU, 0x1ac5645fU,
        };
        HW_SCE_p_func100(Param_p1b_func100_002);
        HW_SCE_p_func_sub015(0x00001864U, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_XYZ[0]);

        static const uint32_t Param_p1b_func100_003[] =
        {
            0x6c233f5cU, 0xe46693ccU, 0x58a1acb6U, 0x680d15b4U,
        };
        HW_SCE_p_func100(Param_p1b_func100_003);
        HW_SCE_p_func_sub015(0x00001869U, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_XYZ[8]);

        static const uint32_t Param_p1b_func100_004[] =
        {
            0xf4616bfaU, 0xd576ea54U, 0x82591216U, 0xd480a68aU,
        };
        HW_SCE_p_func100(Param_p1b_func100_004);
        HW_SCE_p_func_sub015(0x0000186eU, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_XYZ[16]);

        static const uint32_t Param_p1b_func102_002[] =
        {
            0x4490da4bU, 0x199970cbU, 0x838ce0afU, 0xb2f4dddeU,
        };
        HW_SCE_p_func102(Param_p1b_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
