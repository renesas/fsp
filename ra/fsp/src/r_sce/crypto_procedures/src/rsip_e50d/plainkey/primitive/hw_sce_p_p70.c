/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[])
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

    WR1_PROG(REG_1B00H, 0x00700001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func049_r1(InData_Cmd);

    WR1_PROG(REG_1600H, 0x0000094aU);

    WR1_PROG(REG_1600H, 0x000037e4U);

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x0000002bU);
    WR1_PROG(REG_1600H, 0x00040020U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x38008880U);
    WR1_PROG(REG_1600H, 0x000000ffU);
    WR1_PROG(REG_1600H, 0x1000b480U);
    WR1_PROG(REG_1600H, 0x00000005U);

    WR1_PROG(REG_1600H, 0x38008880U);
    WR1_PROG(REG_1600H, 0x000000feU);
    WR1_PROG(REG_1600H, 0x1000b480U);
    WR1_PROG(REG_1600H, 0x00000005U);

    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1600H, 0x0000002cU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0xfd9fe1ddU, 0x4245941eU, 0x104227ccU, 0x69be7712U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x0d673b43U, 0xc2fe7febU, 0x6fa99eabU, 0xb0a1384cU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x0000349fU);

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000070U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xfb783a8dU, 0x81f94318U, 0xeab67be2U, 0x31922395U);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x000034e4U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000070U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xbfd726f2U, 0x5398bd75U, 0x701cf153U, 0x01e73d80U);
        HW_SCE_p_func044_r1();

        HW_SCE_p_func100(0x7686ce70U, 0xf92ec09eU, 0xd6c3afbaU, 0xe9b669bbU);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func081_r1();

        WR1_PROG(REG_1600H, 0x00007c01U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_1444H, 0x00020062U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009c06U);

            for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func209();

            HW_SCE_p_func101(0x90146eeeU, 0xae9d2d26U, 0x68232710U, 0xc8bdc12aU);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
        {
            WR1_PROG(REG_1444H, 0x000023c2U);
            WR1_PROG(REG_1A2CH, 0x40000800U);
            WR1_PROG(REG_1A24H, 0xe8009007U);

            for (iLoop = 0U; iLoop < 36U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x71be3000U, 0xa2fecf8dU, 0xa8cb8337U, 0xac419607U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
        {
            WR1_PROG(REG_1444H, 0x00003fc2U);
            WR1_PROG(REG_1A2CH, 0x40000f00U);
            WR1_PROG(REG_1A24H, 0xf7009c07U);

            for (iLoop = 0U; iLoop < 64U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x971f2b53U, 0xdb13a644U, 0x11990ea1U, 0x4c5ee279U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
        {
            WR1_PROG(REG_1444H, 0x000043c2U);
            WR1_PROG(REG_1A2CH, 0x40001000U);
            WR1_PROG(REG_1A24H, 0xe8009007U);

            for (iLoop = 0U; iLoop < 68U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x8015f9cbU, 0x727e7d33U, 0xf434dce7U, 0xc8473e32U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
        {
            WR1_PROG(REG_1444H, 0x00007fc2U);
            WR1_PROG(REG_1A2CH, 0x40001f00U);
            WR1_PROG(REG_1A24H, 0xf7009c07U);

            for (iLoop = 0U; iLoop < 128U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x16781e42U, 0xd6148deeU, 0x5ccf876eU, 0xea6b563dU);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
        {
            WR1_PROG(REG_1444H, 0x00020062U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8009006U);

            for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func209();

            HW_SCE_p_func101(0x7f05e1baU, 0xeaae3e55U, 0x17d5c524U, 0xeb6f998cU);
        }

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x7adcd9bcU, 0x5487c2a5U, 0x97e3cd7fU, 0x5b141035U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xe5864acdU, 0x64829e6dU, 0x0365855eU, 0xa095d679U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0xf6ffd952U, 0x5cd8b580U, 0xf8dc2619U, 0xd4e88ddeU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
