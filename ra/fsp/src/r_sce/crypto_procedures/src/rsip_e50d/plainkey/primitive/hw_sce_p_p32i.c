/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_SeqNum[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00320001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000d08U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008900U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x32f88d6eU, 0xb836a9b4U, 0xcfe8380eU, 0xa938b48dU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000d08U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xc54eb590U, 0xf4a88aacU, 0xd603e9f8U, 0x12175bdaU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000032U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xc0eaef35U, 0xf13e8dd9U, 0x05dfb9e1U, 0xe3996c76U);
            HW_SCE_p_func043_r1();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000005U);

            HW_SCE_p_func101(0xd6624eadU, 0xd2588b0dU, 0x5cb7fe46U, 0x5191deb9U);
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003547U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000032U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x6a87b60fU, 0xdf498608U, 0xf14aa686U, 0xf6c599edU);
            HW_SCE_p_func068_r1();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x2a46c04bU);

            HW_SCE_p_func101(0xeb91cdc8U, 0xa5979a89U, 0xb94700e7U, 0xf8571fb1U);
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000032U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xbbafaa86U, 0x4c11a922U, 0xc4662789U, 0xffd88408U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xf7009d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c7U);
        WR1_PROG(REG_1608H, 0x80040080U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_IV[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_IV[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_IV[2]);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_IV[3]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x50eb8120U, 0xf38d8d34U, 0xa125632fU, 0x074a2540U);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38008900U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x81fc5727U, 0x17bd9145U, 0x10196a2eU, 0x3748a39bU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80040000U);
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

            WR1_PROG(REG_1600H, 0x000037e0U);

            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x00ff0000U);
            WR1_PROG(REG_1600H, 0x38008be0U);
            WR1_PROG(REG_1600H, 0x00120000U);
            WR1_PROG(REG_1600H, 0x1000d3c0U);

            WR1_PROG(REG_1600H, 0x3800d80eU);
            WR1_PROG(REG_1600H, 0x2000d3c1U);

            WR1_PROG(REG_1600H, 0x000037e0U);

            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x000000feU);

            WR1_PROG(REG_1600H, 0x38008be0U);
            WR1_PROG(REG_1600H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x1000d3c2U);

            WR1_PROG(REG_1600H, 0x38008bc0U);
            WR1_PROG(REG_1600H, 0x00000007U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            WR1_PROG(REG_1600H, 0x00003540U);
            WR1_PROG(REG_1600H, 0x00003561U);
            WR1_PROG(REG_1600H, 0x00003582U);
            WR1_PROG(REG_1600H, 0x000035a3U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000032U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x9f3ea6d0U, 0x9e150982U, 0xc79c7d4fU, 0x23ea3749U);
            HW_SCE_p_func059_r1();

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[4]);

            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[8]);
            WR1_PROG(REG_1608H, 0x80040080U);
            WR1_PROG(REG_1400H, 0x03420011U);
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

            HW_SCE_p_func101(0x358c44b7U, 0x7eedb999U, 0xe7cd5692U, 0x14c3d26eU);
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010140U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyIndex[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x3800a900U);
            WR1_PROG(REG_1600H, 0x00000003U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xe4f70dfdU, 0x036ca37fU, 0x6ac6227aU, 0x68bab7d3U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000005U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x4d4fcee1U, 0x7ec2b1e1U, 0x218c1feaU, 0x5443e2b2U);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x01ad8717U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000005U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x306d9c10U, 0x2f8ec0deU, 0xc585fda1U, 0x08fdc8e9U);
                HW_SCE_p_func044_r1();

                HW_SCE_p_func101(0x34c53331U, 0x345d7c74U, 0x54414d67U, 0x027f2d78U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010020U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_DataType[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000c21U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0x125e6f28U, 0x604b9522U, 0xc9d8362cU, 0x4d259892U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x80010000U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_Cmd[0]);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x000036a0U);

                    WR1_PROG(REG_1600H, 0x0000b6c0U);
                    WR1_PROG(REG_1600H, 0x8026ee7fU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000032U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x12c33be5U, 0x9e7ec77eU, 0x9f08f7b2U, 0x3c979ef1U);
                    HW_SCE_p_func092_r1();

                    HW_SCE_p_func101(0xe13bbf92U, 0x7d55b3a9U, 0x7dbb57d9U, 0x08268a92U);
                }
                else
                {
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x000000ecU));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x87e72d5cU, 0x79b1eb62U, 0xf4cbc95bU, 0xe6b43d24U);
                    HW_SCE_p_func068_r1();

                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1600H, 0x98bae316U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x000000ecU));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x84cfcaacU, 0x0141415eU, 0x4c534a21U, 0xb8eda236U);
                    HW_SCE_p_func044_r1();

                    HW_SCE_p_func101(0x9c69b4c6U, 0x1e57455fU, 0x2269acb3U, 0xd245c9b2U);
                }

                WR1_PROG(REG_1444H, 0x000001c7U);
                WR1_PROG(REG_1608H, 0x80020360U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[0]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[1]);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xbf92fd39U, 0xf3cdabd7U, 0xcf4acd48U, 0xf5ec2a14U);
            }

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);
            WR1_PROG(REG_1608H, 0x80040080U);
            WR1_PROG(REG_1400H, 0x03420011U);
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

            HW_SCE_p_func101(0x2c3aa771U, 0x4535a9c7U, 0x593e8a83U, 0x637c5afbU);
        }

        HW_SCE_p_func101(0x08ce720dU, 0xdaa6cb16U, 0x097d89dbU, 0x714922efU);
    }

    HW_SCE_p_func100(0x5c9e1f22U, 0x6815b48eU, 0xb3327a3dU, 0x3274ea6eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xc81a7d36U, 0x4dd6c85aU, 0x949435c2U, 0x3f174c4fU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x246535fbU, 0x0d2016c9U, 0xcffad8d6U, 0x671db5fdU);
        WR1_PROG(REG_1600H, 0x3000a900U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x000008bbU);
        WR1_PROG(REG_1600H, 0x000008dcU);
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1824H, 0x08000085U);
        WR1_PROG(REG_1400H, 0x00490011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000024U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_182CH, 0x00070000U);
        WR1_PROG(REG_1824H, 0x0a008004U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        return FSP_SUCCESS;
    }
}
