/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub (const uint32_t InData_KeyType[],
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

    WR1_PROG(REG_1B00H, 0x00290001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008900U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xdb07871bU, 0x9a4faa69U, 0xd8969119U, 0xba8e3514U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x8d6b8caeU, 0x5df339d4U, 0x79fb1247U, 0x16170e68U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000d08U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x38008900U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x5b8d99b3U, 0x2ff4e86aU, 0x51193283U, 0x3e686045U);
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

            HW_SCE_p_func100(0x3c3446a1U, 0x7e6da0d0U, 0x8ad5f057U, 0xa5675bd0U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000029U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x070dbfdbU, 0xf6dedb1aU, 0x7a641ddbU, 0x682b2442U);
                HW_SCE_p_func043_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                HW_SCE_p_func101(0xe68de85bU, 0x714abe2aU, 0x98d184a2U, 0x1e553dabU);
            }
            else
            {
                WR1_PROG(REG_1600H, 0x00003547U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000029U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x200101feU, 0xa9b256d2U, 0xfdd48523U, 0x92cd8c7bU);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x2a46c04bU);

                HW_SCE_p_func101(0xe0764891U, 0xe54d722bU, 0xfb88e91aU, 0x9366254cU);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000029U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x41de7c4bU, 0xf2f82ba5U, 0x38aa8e35U, 0x0d47a12cU);
            HW_SCE_p_func044_r1();

            HW_SCE_p_func100(0x55d71f8cU, 0x7baba611U, 0x01b55c41U, 0xf3f69df6U);
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

            HW_SCE_p_func101(0x4b5ee5c3U, 0x60531982U, 0x0bae78f4U, 0x76a42722U);
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38008900U);
            WR1_PROG(REG_1600H, 0x00000001U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xd79a543bU, 0x86e1785bU, 0xa7a00857U, 0x49efb466U);
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

                WR1_PROG(REG_1600H, 0x3800d80fU);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000029U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x2bc0c543U, 0xb7bd1bfaU, 0x1db4831cU, 0x88d15eb0U);
                HW_SCE_p_func059_r1();

                HW_SCE_p_func100(0x8871df3aU, 0x5954f2ecU, 0xc48b2cadU, 0xf9d22a20U);
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
                HW_SCE_p_func101(0x6416762eU, 0x5336ee43U, 0x1760f87cU, 0xbd80b2d3U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010140U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010020U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_DataType[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000c21U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0xeb8b3710U, 0xc92f949eU, 0x6395b0e0U, 0x224a300fU);
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
                    WR1_PROG(REG_1600H, 0x4cc18a1aU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000029U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x8dabdd81U, 0xe7ce720bU, 0x8fdfe377U, 0x781c3d9bU);
                    HW_SCE_p_func092_r1();

                    HW_SCE_p_func101(0xd50d6fbeU, 0x1b676e1fU, 0x31f85b02U, 0x9d421a5dU);
                }
                else
                {
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x000000edU));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x53e426e9U, 0x1d2223e2U, 0xb16472afU, 0x7ceb14acU);
                    HW_SCE_p_func068_r1();

                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1600H, 0x6ad6575eU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x000000edU));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x18b4070eU, 0xb8d45aefU, 0x8827a44aU, 0xafb7d939U);
                    HW_SCE_p_func044_r1();

                    HW_SCE_p_func101(0xa0db73b8U, 0x2f60b53fU, 0xbf48c568U, 0x75b6ccebU);
                }

                WR1_PROG(REG_1444H, 0x000001c7U);
                WR1_PROG(REG_1608H, 0x80020360U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[0]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[1]);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func100(0x993e70b0U, 0xbeabd698U, 0xfec3691eU, 0x9656faebU);
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

                HW_SCE_p_func101(0x77ab0c42U, 0xbb1e2195U, 0x12627fe3U, 0xfa15aeb4U);
            }

            HW_SCE_p_func101(0xd53250cfU, 0xcb67142cU, 0x3e92ebb4U, 0x65067810U);
        }

        HW_SCE_p_func100(0xb6574844U, 0x6a7967b7U, 0x7542a6e1U, 0xf57c1473U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xaf3f6031U, 0x94383906U, 0xea11e5e3U, 0x55f3a4acU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x3000a900U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1600H, 0x00010020U);
            WR1_PROG(REG_1600H, 0x000008bbU);
            WR1_PROG(REG_1600H, 0x000008dcU);
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000001U);
            WR1_PROG(REG_1600H, 0x00000080U);

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
}
