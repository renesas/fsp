/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyType[],
                                              const uint32_t InData_Cmd[],
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

    WR1_PROG(REG_1B00H, 0x00500001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1608H, 0x80020000U);
    WR1_PROG(REG_1444H, 0x000001c7U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x8b63ad9fU, 0x9395fb8bU, 0xdd79ca8fU, 0x4bbc6c76U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x93b26ee1U, 0xa635ee4aU, 0xb46f3e38U, 0xfdd14ca0U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x3000a800U);
        WR1_PROG(REG_1600H, 0x00000006U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1600H, 0x00000006U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x3420a800U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x02adc113U, 0xa3134233U, 0x9e1145beU, 0x7418db57U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x0d63cbc9U, 0x76c7d218U, 0x18ca1561U, 0xb1ac3294U);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000050U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x071df796U, 0x2dbadc5cU, 0xdd61c5d2U, 0x0d8fff63U);
                HW_SCE_p_func043_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000007U);

                HW_SCE_p_func101(0x15a79681U, 0xc96f8831U, 0xd0ab9d67U, 0xb57139afU);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000050U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x2dc2883aU, 0x63bede3aU, 0x5c0c5949U, 0xa95f5dbfU);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x85d04999U);

                HW_SCE_p_func101(0x22e1dc8aU, 0xb2694425U, 0xa81fb838U, 0x691e9f80U);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000050U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x9bd3f0b2U, 0xceee41edU, 0xe2a34b4cU, 0x949de8a1U);
            HW_SCE_p_func044_r1();

            HW_SCE_p_func100(0x9d45d457U, 0xcbd99881U, 0x4c5b30b0U, 0x88775023U);
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

            HW_SCE_p_func100(0xa1ff275dU, 0xfbc46e35U, 0x688f1374U, 0x4c513325U);
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

            HW_SCE_p_func101(0x40d395b6U, 0x6f8bfa6cU, 0x30748727U, 0x4f353849U);
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80040040U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[1]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[2]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[3]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00000bdeU);

            WR1_PROG(REG_1600H, 0x000037e2U);

            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x00ff0000U);
            WR1_PROG(REG_1600H, 0x38008be0U);
            WR1_PROG(REG_1600H, 0x00010000U);
            WR1_PROG(REG_1600H, 0x1000d3c0U);

            WR1_PROG(REG_1600H, 0x38008800U);
            WR1_PROG(REG_1600H, 0x00000005U);
            WR1_PROG(REG_1600H, 0x1000b540U);
            WR1_PROG(REG_1600H, 0x0000000fU);
            WR1_PROG(REG_1600H, 0x2000b540U);
            WR1_PROG(REG_1600H, 0x0000000eU);

            WR1_PROG(REG_1600H, 0x3800584aU);
            WR1_PROG(REG_1600H, 0x2000d3c1U);

            WR1_PROG(REG_1600H, 0x000037e2U);

            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x000000feU);

            WR1_PROG(REG_1600H, 0x38008be0U);
            WR1_PROG(REG_1600H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x1000d3c2U);

            WR1_PROG(REG_1600H, 0x38008bc0U);
            WR1_PROG(REG_1600H, 0x00000007U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            WR1_PROG(REG_1600H, 0x0000a800U);
            WR1_PROG(REG_1600H, 0x00000003U);

            WR1_PROG(REG_1600H, 0x00003542U);
            WR1_PROG(REG_1600H, 0x00003563U);
            WR1_PROG(REG_1600H, 0x00003584U);
            WR1_PROG(REG_1600H, 0x000035a5U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000050U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xb617e2dbU, 0x75c33146U, 0xfe54318eU, 0xca37daccU);
            HW_SCE_p_func059_r1();

            HW_SCE_p_func100(0x189bb226U, 0x6271308aU, 0x58ef370bU, 0x05e2d4f6U);
            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xf7009d07U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[4]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[8]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func100(0x18f78776U, 0xd7484567U, 0x12ccce43U, 0x162323ecU);
            WR1_PROG(REG_1824H, 0x08000095U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[12]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func101(0x3a6c0578U, 0xe5fbe622U, 0x2b22f817U, 0x4d14f67cU);
        }

        HW_SCE_p_func100(0x574fc4a0U, 0xaac286b8U, 0x7aeb2ef4U, 0x91abfd16U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x7865289dU, 0xdcf654c9U, 0x62e31c96U, 0xbe628241U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x78ac61b3U, 0x2dd80de7U, 0xfd93df39U, 0x51e86098U);
            WR1_PROG(REG_1600H, 0x00007c00U);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
            {
                HW_SCE_p_func101(0x7ff132d6U, 0xc5015014U, 0xb7b0da80U, 0x4c7f5deeU);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
            {
                HW_SCE_p_func101(0x3292bcf6U, 0x8b4c7ce8U, 0x3ab1c258U, 0x752e3672U);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0x7548ae11U, 0x0e24fba6U, 0xb36deb1cU, 0x3522c3e2U);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0x7f7eff23U, 0x03b59cecU, 0x6ad0653eU, 0xa118eeceU);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0xdc727fabU, 0xc0c57f88U, 0x61f5c69eU, 0xcbab7047U);
            }
            else
            {
                ;
            }

            return FSP_SUCCESS;
        }
    }
}
