/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha224HmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00dc0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0xfd585916U, 0xee88e73bU, 0x12383efbU, 0x7ae24532U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);
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
        WR1_PROG(REG_2CH, change_endian_long(0x000000dcU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xb035ed80U, 0x4e7dab2bU, 0xcd68b2d0U, 0x6138d60fU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x0000001aU);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x000000dcU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x7283a2b9U, 0xfc16a0b7U, 0x07e123f1U, 0x7ea399adU);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x00001404U);
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

        HW_SCE_p_func101(0xd665616aU, 0xa60210a1U, 0xa862c24dU, 0x29df8d0cU);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001404U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[4]);

        HW_SCE_p_func101(0x3821200dU, 0x77eaeec9U, 0xd0acc990U, 0x9dee3ecaU);
    }

    HW_SCE_p_func100(0x5fddb2a3U, 0x73ad4219U, 0x656befb9U, 0x0bfd6fedU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xa2ad601fU, 0xdb8ef99aU, 0x25cb3060U, 0x585ce026U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_F4H, 0x00000010U);

        WR1_PROG(REG_14H, 0x000007a4U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_PROG(REG_2CH,
                 change_endian_long(0xc1059ed8U),
                 change_endian_long(0x367cd507U),
                 change_endian_long(0x3070dd17U),
                 change_endian_long(0xf70e5939U),
                 change_endian_long(0xffc00b31U),
                 change_endian_long(0x68581511U),
                 change_endian_long(0x64f98fa7U),
                 change_endian_long(0xbefa4fa4U));

        WR1_PROG(REG_F4H, 0x00000011U);

        HW_SCE_p_func001();

        HW_SCE_p_func101(0x53fa0b86U, 0x8f688219U, 0x7b76f7a2U, 0x09e60a83U);

        return FSP_SUCCESS;
    }
}
