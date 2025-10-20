/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Chacha20Poly1305SuspendSub (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    if (S_RAM[0] == 1)
    {
        HW_SCE_p_func101(0x04e744f2U, 0xaf0f4804U, 0x28f90944U, 0xdd4c9915U);
    }
    else
    {
        HW_SCE_p_func101(0xd16b08d7U, 0x197a5d99U, 0x7cf9402bU, 0x7fc6505eU);
    }

    WAIT_STS(REG_1C30H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001c00U);

    RD1_ADDR(REG_1C08H, &OutData_State[0]);
    RD1_ADDR(REG_1C10H, &OutData_State[1]);
    RD1_ADDR(REG_1C14H, &OutData_State[2]);

    for (iLoop = 3; iLoop < 10U; iLoop++)
    {
        RD1_ADDR(REG_1C2CH, &OutData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c21U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x7c5b05b3U, 0xd39779d0U, 0x0cf11fd5U, 0xc39f4133U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func101(0x9800d41aU, 0x93976132U, 0x6053614aU, 0x872319caU);
    }
    else
    {
        HW_SCE_p_func100(0x3830d835U, 0x04f461e7U, 0x563c19b6U, 0x6d769a26U);
        HW_SCE_p_func103();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1608H, 0x80010060U);
        WR1_PROG(REG_1400H, 0x03420005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func101(0x0bab9b22U, 0x8a9e7dfbU, 0x92848bd3U, 0xece99310U);
    }

    WR1_PROG(REG_1600H, 0x000034e3U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00009704U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xf16225afU, 0xc10ba6a8U, 0xddfa5568U, 0xc9e4d84bU);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0121608eU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00009704U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xa1c51bdaU, 0x6cb8b60fU, 0xd2be0e95U, 0xc46f7aa7U);
    HW_SCE_p_func044_r1();

    HW_SCE_p_func100(0xe1687838U, 0xf90acf01U, 0x2c823ae7U, 0xa34ce5d0U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xe8009104U);
    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_State[11]);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0xd95716b4U, 0xbb4a076aU, 0x0aa4c643U, 0x5d6bdd3dU);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_State[12]);

    HW_SCE_p_func100(0x6253f599U, 0x5dfba3f2U, 0xb0eade5eU, 0x8a4dffb7U);
    WR1_PROG(REG_1608H, 0x81010060U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_State[10]);

    HW_SCE_p_func102(0x56678fb1U, 0x5ccfa540U, 0xfb551e0eU, 0xec8ba451U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
