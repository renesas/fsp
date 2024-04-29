/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t Header_Len)
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

    WR1_PROG(REG_1B00H, 0x00a40001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x2857ddcbU, 0x05ca7b9bU, 0x1c0c42d1U, 0x445c7a60U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x153c65caU, 0x4944b7c8U, 0x12a52cf5U, 0x161ee0c3U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xce55ea47U, 0x97ea0208U, 0x218671faU, 0xb280af34U);
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
            WR1_PROG(REG_1420H, change_endian_long(0x000000a4U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x3ceb2b1eU, 0x43ce4e8fU, 0xab31f055U, 0x4bdbac60U);
            HW_SCE_p_func043_r1();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000007U);

            HW_SCE_p_func101(0x58eaf4ffU, 0x933c1aedU, 0xc898c6feU, 0x80873e1bU);
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010140U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x000000a4U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xb38a335bU, 0x83c0e669U, 0xe92d8c16U, 0x730e8e7cU);
            HW_SCE_p_func068_r1();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x85d04999U);

            HW_SCE_p_func101(0xfa7f40efU, 0xde9386aeU, 0x0f4aa682U, 0xb056c1a8U);
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x000000a4U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xedd1226dU, 0xe89673afU, 0xebd25f11U, 0xdbb45f5dU);
        HW_SCE_p_func044_r1();

        HW_SCE_p_func100(0x2fab63ffU, 0x5a78b868U, 0x6ea21e7cU, 0x342a3337U);
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

        WR1_PROG(REG_1824H, 0x08000085U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x6fa7cfe2U, 0xd52cb8bbU, 0xf49fd9beU, 0x9d5da7c4U);
        WR1_PROG(REG_1824H, 0x08000095U);
        WR1_PROG(REG_1400H, 0x00420011U);
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

        HW_SCE_p_func100(0x96fcb434U, 0xfa49875bU, 0xa7d9c6f0U, 0x3b30c15cU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xc75e1c84U, 0xe215e246U, 0xc4ab8072U, 0x2c1a01ddU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000145U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            WR1_PROG(REG_1824H, 0x08000065U);
            WR1_PROG(REG_1400H, 0x00410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x07000c04U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000054U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1444H, 0x00020061U);
            WR1_PROG(REG_182CH, 0x40000000U);
            WR1_PROG(REG_1824H, 0x0e108406U);

            for (iLoop = 0U; iLoop < Header_Len; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_Header[iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func216();

            return FSP_SUCCESS;
        }
    }
}
