/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Chacha20InitSub (const uint32_t InData_KeyMode[],
                                  const uint32_t InData_KeyIndex[],
                                  const uint32_t InData_Key[],
                                  const uint32_t InData_Ctr[],
                                  const uint32_t InData_Nonce[],
                                  const uint32_t InData_TextLen[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00960001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x95795a6dU, 0xc01b5607U, 0xe1f548bdU, 0x899ca0aaU);
    WR1_PROG(REG_1C00H, 0x00000001U);

    WR1_PROG(REG_1C04H, 0x00001000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyMode[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x18911ef1U, 0xf7070703U, 0xbcd6136dU, 0x0a4b48dbU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000096U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x320e03b3U, 0xacc7c806U, 0xc01669b3U, 0x98db251cU);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000030U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000096U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x4b649643U, 0xe20d1560U, 0x7bc794d9U, 0xb789b3bdU);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

        WR1_PROG(REG_1400H, 0x01c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func101(0xd14c64a4U, 0xd1db89c5U, 0xa2268eb0U, 0x73657e89U);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000007c6U);
        WAIT_STS(REG_1444H, 31, 1);
        WR8_ADDR(REG_1420H, &InData_Key[0]);

        HW_SCE_p_func101(0xf7701728U, 0xc7d33cdbU, 0x8a08821dU, 0x85f8a699U);
    }

    HW_SCE_p_func100(0x69f27b15U, 0x2db8fff3U, 0x06e9de25U, 0xd044931fU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x4a00a291U, 0xeea9c52bU, 0x5c3f8e42U, 0xc08e253eU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_1C08H, InData_Ctr[0]);

        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_1C0CH, InData_Nonce[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_1C0CH, InData_Nonce[1]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_1C0CH, InData_Nonce[2]);

        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_1C10H, InData_TextLen[0]);

        return FSP_SUCCESS;
    }
}
