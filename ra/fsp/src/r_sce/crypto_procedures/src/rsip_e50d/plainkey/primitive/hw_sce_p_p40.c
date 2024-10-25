/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_LoadHukSub (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00400001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func048_r1(InData_LC);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x0000000aU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1600H, 0x10003401U);

    WR1_PROG(REG_1600H, 0x34202801U);
    WR1_PROG(REG_1600H, 0x20003401U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_143CH, 0x00b80000U);

        HW_SCE_p_func101(0xd79669fbU, 0x9d346923U, 0x3a14355fU, 0x358484d1U);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_143CH, 0x00b00000U);

        HW_SCE_p_func101(0xf20d07e1U, 0xec188734U, 0x209ee85dU, 0xbb5e2fc1U);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_143CH, 0x00b30000U);

        HW_SCE_p_func101(0x97eebde0U, 0x8d60c103U, 0x9347fdb4U, 0xe03c0d68U);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_143CH, 0x00b50000U);

        HW_SCE_p_func101(0xd4cebd6bU, 0x8f82c577U, 0x5086ee81U, 0x87898155U);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_143CH, 0x00b60000U);

        HW_SCE_p_func101(0x3ecf5357U, 0x09080fb2U, 0x13b715a0U, 0x18249bdcU);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_143CH, 0x00b70000U);

        HW_SCE_p_func101(0xa9faa165U, 0xcb8f5381U, 0xd75fb2a1U, 0x13b1e47cU);
    }
    else if (InData_LC[0] == 0x00000009U)
    {
        WR1_PROG(REG_143CH, 0x00b90000U);

        HW_SCE_p_func101(0x05540a4eU, 0x1d8683ebU, 0xdc87d36dU, 0x6320823aU);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func101(0xe886da82U, 0xa450ca98U, 0xd30e97e4U, 0xfe7111bdU);
    }

    HW_SCE_p_func100(0x641e93fcU, 0x3ed85bd2U, 0x9363798aU, 0x421abaecU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xf3dcebe3U, 0xc3489b64U, 0x7ba32bc8U, 0xb4539034U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x0a0700f5U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x05818b2aU), change_endian_long(0x0adf0d83U), change_endian_long(0x0c37adbdU), change_endian_long(0xaaae696bU));

        WR1_PROG(REG_1A24H, 0x30471084U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x01ea725dU));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000004U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1A24H, 0x30471094U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x02ea725dU));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000004U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x0a0700f5U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, change_endian_long(0x1d571b38U), change_endian_long(0x1dee8c72U), change_endian_long(0xced283ddU), change_endian_long(0x6ec23923U));

        HW_SCE_p_func100(0x0057d336U, 0xf628239cU, 0xe566a56aU, 0x37fecac3U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d05U);
        WR1_PROG(REG_1438H, 0x20000000U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xf7008d05U);
        WR1_PROG(REG_1438H, 0x20000010U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1824H, 0x08000085U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x2738ee3eU, 0xe0c6a22cU, 0xf02a5aa4U, 0xcd9ff36dU);
        WR1_PROG(REG_1824H, 0x08000095U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001b0U);
        WR1_PROG(REG_1600H, 0x00003c01U);

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WR1_PROG(REG_1438H, 0x20000020U);
        WR1_PROG(REG_1400H, 0x00880011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1A24H, 0x8c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000002a1U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x4a008044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x018beba7U));

        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x028beba7U));

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001d0U);
        WR1_PROG(REG_1608H, 0x80880001U);
        WR1_PROG(REG_1400H, 0x03410021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xbe586421U, 0x0bb26051U, 0xa5c545f9U, 0xe68755e4U);
        WR1_PROG(REG_1A24H, 0x4a470044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1A24H, 0x0e4704c4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0152db38U));

        WR1_PROG(REG_1A24H, 0x4a040044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1A24H, 0x0e040504U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x01f7370eU));

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x000001c0U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1B08H, 0x00000202U);

        HW_SCE_p_func102(0xd07768feU, 0xa9bad713U, 0xe23a8a11U, 0x5ac29ca4U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}
