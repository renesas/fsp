/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyType[],
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

    WR1_PROG(REG_1B00H, 0x00470001U);
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

    HW_SCE_p_func100(0xd8da6abaU, 0x050c6b5fU, 0x2daa1113U, 0x291087f9U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x84fd02ecU, 0x4c4a34bdU, 0x9936e595U, 0xf22289adU);
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

        HW_SCE_p_func100(0xc1a06834U, 0xcedc2eaeU, 0xd9981013U, 0xc12828c3U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x8d77f88bU, 0xd3214095U, 0xcc221d55U, 0x085a8faaU);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000047U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xf1c1d2f7U, 0x26c40b65U, 0xeff4f8ffU, 0xe5c57f8aU);
                HW_SCE_p_func043_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                HW_SCE_p_func101(0x5198c8a7U, 0x3d512e12U, 0x734a98b0U, 0x67ffd239U);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000047U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xbeccfb27U, 0xbd026df7U, 0x27d34e12U, 0x0a96729bU);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x2a46c04bU);

                HW_SCE_p_func101(0x7d0be759U, 0x0b5a42d7U, 0xe0ca4611U, 0xbf9c5bd9U);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000047U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x4058c560U, 0x03149f44U, 0xb2ba741fU, 0x536df022U);
            HW_SCE_p_func044_r1();

            HW_SCE_p_func100(0x4df94c16U, 0xf3444978U, 0x5c08cf8bU, 0xc2aea882U);
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
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

            HW_SCE_p_func101(0xdee3f75dU, 0x45ba79a0U, 0xda17eb9aU, 0xb225fc01U);
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
            WR1_PROG(REG_1600H, 0x00000000U);
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
            WR1_PROG(REG_1420H, change_endian_long(0x00000047U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x3a2b4cc1U, 0x34faf857U, 0x3941a196U, 0xf3518674U);
            HW_SCE_p_func059_r1();

            HW_SCE_p_func100(0xfb58974dU, 0x7c1618eeU, 0x316fd381U, 0x972730bfU);
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[4]);

            WR1_PROG(REG_1824H, 0x08000085U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[8]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func101(0x60bdba69U, 0x1018b900U, 0x626e6771U, 0x96f5e96aU);
        }

        HW_SCE_p_func100(0x6e64546eU, 0x5d16aba8U, 0xec5a66ffU, 0x2f3497a6U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xa6bd4176U, 0x64efd6beU, 0xf5eb9386U, 0x15c6bf7bU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0xbf18d2b4U, 0xf10ed05dU, 0x8130e031U, 0xd62273c1U);
            WR1_PROG(REG_1600H, 0x00007c00U);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
            {
                HW_SCE_p_func101(0xe0a8faabU, 0x1728276bU, 0x87dc748dU, 0x18e9f16aU);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
            {
                HW_SCE_p_func101(0x9d79bc67U, 0x9c71b49aU, 0x73935154U, 0xe8972f5cU);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0x74ac8c62U, 0x6cf70e01U, 0x0e7c2be7U, 0x93c144bcU);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0x56893593U, 0x7acb301eU, 0xf5e295fdU, 0x07ce3eb9U);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                HW_SCE_p_func101(0x841043f2U, 0xf0a2d1e1U, 0x8b39c9beU, 0x5cdb00d5U);
            }
            else
            {
                ;
            }

            return FSP_SUCCESS;
        }
    }
}
