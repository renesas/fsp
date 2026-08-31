/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func082 (void)
{
    static const uint32_t Param_func082_func100_001[] =
    {
        0x288a0959U, 0xc79a1887U, 0x853954b9U, 0x7e94afbcU,
    };
    HW_SCE_p_func100(Param_func082_func100_001);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x01000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00442a0cU, 0x00000000U);

    WR1_PROG(REG_C4H, 0x00082e0cU);
    HW_SCE_p_func_sub010(0x81010140U, 0x00002807U);

    static const uint32_t Param_func082_func100_002[] =
    {
        0x33e4bad9U, 0x38eb1f47U, 0x79a7e4a2U, 0x67359c24U,
    };
    HW_SCE_p_func100(Param_func082_func100_002);
    HW_SCE_p_func_sub022(0x00008d40U, 0x00ffffffU, 0x00009140U, 0x02000000U);

    WR1_PROG(REG_C4H, 0x00092e0cU);
    HW_SCE_p_func_sub010(0x81010140U, 0x00002807U);

    HW_SCE_p_func_sub022(0x300032a0U, 0x00070020U, 0x0000b6e0U, 0x0104c99cU);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000b6e0U, 0x01ed4879U, 0x00050040U);
    WR1_PROG(REG_ECH, 0x0000b6e0U);
    WR1_PROG(REG_ECH, 0x01182e99U);
    WR1_PROG(REG_ECH, 0x00000080U);

    static const uint32_t Param_func082_func100_003[] =
    {
        0x1d0cd8d2U, 0xccffd8fdU, 0x9f6d5601U, 0xd112a4c4U,
    };
    HW_SCE_p_func100(Param_func082_func100_003);
    HW_SCE_p_func_sub022(0x00008ee0U, 0x00ffffffU, 0x000092e0U, 0x01000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00008e94U);
    HW_SCE_p_func_sub010(0x810102e0U, 0x00002807U);

    HW_SCE_p_func_sub022(0x00008ee0U, 0x00ffffffU, 0x000092e0U, 0x02000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00098e14U);
    HW_SCE_p_func_sub010(0x810102e0U, 0x00002807U);

    static const uint32_t Param_func082_func100_004[] =
    {
        0xb57e7e65U, 0x45bce9a1U, 0x3aa1960dU, 0x4dca1bd0U,
    };
    HW_SCE_p_func100(Param_func082_func100_004);
    HW_SCE_p_func_sub013(0x00080805U, 0x00002213U);

    static const uint32_t Param_func082_func100_005[] =
    {
        0xef42db90U, 0xae85650bU, 0xcae14576U, 0xd599e10cU,
    };
    HW_SCE_p_func100(Param_func082_func100_005);
    HW_SCE_p_func_sub022(0x00008ec0U, 0x00ffffffU, 0x000092c0U, 0x01000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00008e94U);
    HW_SCE_p_func_sub010(0x810102c0U, 0x00002807U);

    HW_SCE_p_func_sub022(0x00008ec0U, 0x00ffffffU, 0x000092c0U, 0x02000000U);

    HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00448a04U);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x00098e14U);
    HW_SCE_p_func_sub010(0x810102c0U, 0x00002807U);

    static const uint32_t Param_func082_func100_006[] =
    {
        0x3ce7165fU, 0xd96d579fU, 0x92420e7bU, 0x33a485a2U,
    };
    HW_SCE_p_func100(Param_func082_func100_006);
    HW_SCE_p_func_sub013(0x00080805U, 0x00002213U);

    WR1_PROG(REG_ECH, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
