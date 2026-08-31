/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func308 (void)
{
    static const uint32_t Param_func308_func100_001[] =
    {
        0x8c2d8cf6U, 0x8d56e617U, 0x4e381155U, 0x0522ae21U,
    };
    HW_SCE_p_func100(Param_func308_func100_001);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x00000024U);
    WR1_PROG(REG_ECH, 0x00003c1eU);

    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func_sub022(0x00000b5aU, 0x0000d77cU, 0x0000b7c0U, 0x00000000U);

    HW_SCE_p_func_sub022(0x3800db7aU, 0x00020020U, 0x0000d37cU, 0x00003bbeU);
    WR1_PROG(REG_ECH, 0x00002b5dU);
    WR1_PROG(REG_ECH, 0x00000060U);

    WR1_PROG(REG_ECH, 0x00003b5eU);
    HW_SCE_p_func_sub005(0x00000080U, 0x00000058U, 0x80010020U, 0x0161d833U);

    HW_SCE_p_func080();

    static const uint32_t Param_func308_func100_002[] =
    {
        0xe9363776U, 0x8ffc645cU, 0x22b826ccU, 0x70a25e76U,
    };
    HW_SCE_p_func100(Param_func308_func100_002);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(1020);

    static const uint32_t Param_func308_func100_003[] =
    {
        0x073d446bU, 0xeccd11c7U, 0x5b0e9e5fU, 0x98abb4ccU,
    };
    HW_SCE_p_func100(Param_func308_func100_003);
    HW_SCE_p_func314(1020 + 64);

    static const uint32_t Param_func308_func100_004[] =
    {
        0xfbf01920U, 0xb35ecab2U, 0x10236fdfU, 0xa5cebfeaU,
    };
    HW_SCE_p_func100(Param_func308_func100_004);
    HW_SCE_p_func_sub022(0x00000b39U, 0x0000d77dU, 0x0000b7c0U, 0x00000004U);

    HW_SCE_p_func_sub022(0x3800db7bU, 0x00020020U, 0x0000d37dU, 0x00003bbeU);
    WR1_PROG(REG_ECH, 0x00002b3dU);
    WR1_PROG(REG_ECH, 0x00000060U);

    WR1_PROG(REG_ECH, 0x00003b3eU);
    HW_SCE_p_func_sub005(0x00000080U, 0x00000058U, 0x80010020U, 0x013fd1d7U);

    HW_SCE_p_func080();

    static const uint32_t Param_func308_func100_005[] =
    {
        0x659d1915U, 0x355d44e1U, 0x0a383dc2U, 0xfc52da53U,
    };
    HW_SCE_p_func100(Param_func308_func100_005);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(1088);

    static const uint32_t Param_func308_func100_006[] =
    {
        0xff1123e5U, 0x5c8c6531U, 0x4477a46dU, 0x1d416236U,
    };
    HW_SCE_p_func100(Param_func308_func100_006);
    HW_SCE_p_func314(1088 + 64);

    static const uint32_t Param_func308_func100_007[] =
    {
        0xd336b7c0U, 0xc1d5ac1cU, 0x38833731U, 0x970f8d08U,
    };
    HW_SCE_p_func100(Param_func308_func100_007);
    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x80c0001eU, 0x00018303U, 0x00000020U);

    WR1_PROG(REG_24H, 0x0000c0c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_E0H, 0x81010320U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000010U);
    WR1_PROG(REG_E0H, 0x81010340U);
    HW_SCE_p_func_sub011(0x00003807U, 0x00000012U);

    WR1_PROG(REG_2CH, 0x00000000U);
    WR1_PROG(REG_24H, 0x0000080aU);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_E0H, 0x80010300U);
    HW_SCE_p_func_sub011(0x00008307U, 0x00000020U);

    HW_SCE_p_func_sub022(0x0000d77eU, 0x00000bdeU, 0x3000db7cU, 0x00020020U);
    HW_SCE_p_func_sub022(0x00002fc0U, 0x00000080U, 0x3000db7dU, 0x00020020U);
    HW_SCE_p_func_sub022(0x00002fc0U, 0x00000080U, 0x3000dbc0U, 0x00030020U);
    HW_SCE_p_func_sub022(0x0000d77eU, 0x00000060U, 0x0000d37eU, 0x00000080U);

    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub006(0x000080c1U, 0x00000400U, 0x800080c1U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000058d0U, 0x013fd1d7U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1088);

    HW_SCE_p_func_sub022(0x3000db7cU, 0x00030020U, 0x0000d76bU, 0x00000060U);
    HW_SCE_p_func_sub022(0x0000d36bU, 0x00000080U, 0x000037daU, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000097U);
    static const uint32_t Param_func308_func101_001[] =
    {
        0x2d831169U, 0xf3e9c45fU, 0x86a9a7dbU, 0x48bfc00cU,
    };
    HW_SCE_p_func101(Param_func308_func101_001);
    HW_SCE_p_func310();

    static const uint32_t Param_func308_func100_008[] =
    {
        0x5ba57e89U, 0x2ad0cf5cU, 0xc546cbb0U, 0xdfd6101dU,
    };
    HW_SCE_p_func100(Param_func308_func100_008);

    HW_SCE_p_func_sub009(0x80010020U, 0x0161d833U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(1020);

    HW_SCE_p_func_sub022(0x3000db7dU, 0x00030020U, 0x0000d76bU, 0x00000060U);
    HW_SCE_p_func_sub022(0x0000d36bU, 0x00000080U, 0x000037d9U, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000098U);
    static const uint32_t Param_func308_func101_002[] =
    {
        0xfb0daf22U, 0xfc7f120eU, 0x6e4b02adU, 0x7c564c8aU,
    };
    HW_SCE_p_func101(Param_func308_func101_002);
    HW_SCE_p_func310();

    WR1_PROG(REG_ECH, 0x3800db7eU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);
    static const uint32_t Param_func308_func100_009[] =
    {
        0x6ce6e688U, 0x1ca60eafU, 0x25c7e486U, 0x73068e9aU,
    };
    HW_SCE_p_func100(Param_func308_func100_009);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_E0H, 0x81010300U);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000090U);

        HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x80001191U, 0x000080c1U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        static const uint32_t Param_func308_func101_003[] =
        {
            0x2a06ba12U, 0xe8bfbe05U, 0xfc7ae4e6U, 0x2454e45aU,
        };
        HW_SCE_p_func101(Param_func308_func101_003);
    }
    else
    {
        WR1_PROG(REG_28H, 0x00800001U);
        WR1_PROG(REG_E0H, 0x81010300U);
        HW_SCE_p_func_sub011(0x00003807U, 0x00000090U);

        HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x80001181U, 0x000080c1U);
        WR1_PROG(REG_28H, 0x00bf0001U);

        static const uint32_t Param_func308_func101_004[] =
        {
            0xa71d69d5U, 0x3fd3bbc8U, 0xcfd2107aU, 0xc1462c2cU,
        };
        HW_SCE_p_func101(Param_func308_func101_004);
    }

    HW_SCE_p_func_sub022(0x00000bdeU, 0x02816fdeU, 0x30008bc0U, 0x00000000U);
    HW_SCE_p_func_sub022(0x00020020U, 0x0000d372U, 0x00000060U, 0x0000d772U);
    WR1_PROG(REG_ECH, 0x00000080U);

    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x00000018U, 0x8081001eU, 0x00008307U, 0x00000020U);
    WR1_PROG(REG_24H, 0x000001c0U);
    HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x0000001cU, 0x8081001eU, 0x00008307U, 0x00000020U);
    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_ECH, 0x0000d768U);

    WR1_PROG(REG_24H, 0x000088d0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    HW_SCE_p_func_sub002(0x000000a0U, 0x81c0001eU, 0x00013803U, 0x00000012U);

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000024U, 0x0000381eU, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);
}
