/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00890001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000089U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xf14e00a3U, 0x203b8b78U, 0x148c5f9aU, 0xd44d4816U);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000089U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x8894bb64U, 0x1939c2a7U, 0x08d3ef72U, 0xa04174d0U);
    HW_SCE_p_func044_r1();

    HW_SCE_p_func100(0xa7190113U, 0x4538cebeU, 0x1797d4eeU, 0x4c21f2feU);
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

    HW_SCE_p_func100(0x2546a552U, 0xe79d693bU, 0x987535ecU, 0xd709247eU);
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

    HW_SCE_p_func100(0xb4ca8274U, 0x99eea609U, 0x66d70578U, 0x5edb8ab1U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x6436b828U, 0x506ad5b6U, 0x02a55b88U, 0x78591182U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1608H, 0x80010000U);
        WR1_PROG(REG_1444H, 0x000000c7U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Cmd[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3000a800U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00000080U);

        HW_SCE_p_func100(0x75ff3d73U, 0x2dc5b5f6U, 0xf79ded62U, 0x80a3b457U);
        WR1_PROG(REG_1600H, 0x00007c00U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x6de31559U, 0x730899daU, 0xaaa8d778U, 0xfce560a3U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0xe2816c8eU, 0x8dbc0883U, 0x9e8ba170U, 0xec1a8425U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            HW_SCE_p_func101(0x1bf18b84U, 0xf6f9720fU, 0x1bed2eaeU, 0xbe5243d7U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            HW_SCE_p_func101(0x9a068ef5U, 0xa0cdfab0U, 0xcf6bfdd1U, 0x01c237e3U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_IV[0]);

            HW_SCE_p_func101(0xcb32926aU, 0x1c3cbac0U, 0x037be187U, 0x8b24b5adU);
        }
        else
        {
            ;
        }

        return FSP_SUCCESS;
    }
}
