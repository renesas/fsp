/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha224HmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_MAC[],
                                     const uint32_t InData_length[],
                                     uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_F4H, 0x00000020U);

    WR1_PROG(REG_B0H, 0x00001404U);
    WR1_PROG(REG_00H, 0x00c50021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

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

    HW_SCE_p_func002();

    WR1_PROG(REG_B0H, 0x00001804U);
    WR1_PROG(REG_00H, 0x0143001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x00030005U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000000a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x80000000U));

    WR1_PROG(REG_00H, 0x01400019U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000001a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR2_PROG(REG_2CH,
             change_endian_long(0x00000000U),
             change_endian_long(0x000002E0U));

    WAIT_STS(REG_F8H, 2, 0);

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_40H, 0x00001600U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0xf6be2fcfU, 0x8e45eaaeU, 0x24075e47U, 0x361e30f0U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func100(0x4d0f8b67U, 0x6f3584f8U, 0x5a7d5c23U, 0x425c3a42U);
        WR1_PROG(REG_F4H, 0x00000020U);

        WR1_PROG(REG_08H, 0x0000401eU);
        WAIT_STS(REG_08H, 30, 1);
        RD7_ADDR(REG_2CH, &OutData_MAC[0]);
        WR1_PROG(REG_00H, 0x00050005U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func102(0x4fa05bb0U, 0xd7c2cc51U, 0xc2bc6028U, 0xa7cfed35U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010020U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_length[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000004U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x0000001dU);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A60000U);

        HW_SCE_p_func100(0xf69cc09bU, 0x84210ef0U, 0xf6697e29U, 0x812a3509U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xc1c7b7adU, 0x7d9ceb89U, 0xb608eb1cU, 0x7d3ce4cdU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80870002U);

            WR1_PROG(REG_F4H, 0x00000020U);

            WR1_PROG(REG_00H, 0x0345001dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_00H, 0x00050005U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x00000800U);
            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_94H, 0x3c002841U);
                WR1_PROG(REG_94H, 0x12003c02U);
                WR1_PROG(REG_94H, 0x00002c40U);
            }

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x81880002U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_D0H, 0x08000055U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000006c1U);
            WR1_PROG(REG_D0H, 0x9c000005U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MAC[0]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            WAIT_STS(REG_14H, 31, 1);
            WR3_ADDR(REG_2CH, &InData_MAC[4]);
            WR1_PROG(REG_14H, 0x000000a1U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            HW_SCE_p_func100(0xe799f8c9U, 0x685d99b1U, 0x345f09beU, 0x837f9ee6U);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xec480ddaU, 0x881798aeU, 0x76836f3dU, 0x5585144fU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0x2ced3052U, 0x3cc76baeU, 0xde7b29d7U, 0x4bd22981U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
