/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MACLength[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
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

    WR1_PROG(REG_1B00H, 0x00980001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00003640U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010120U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_TextLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00003689U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x308a9d60U, 0x35efe51eU, 0x375863deU, 0xaaa058aeU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010140U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_MACLength[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xa0693193U, 0x27cbf525U, 0x8578d549U, 0xf98a5165U);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x0000b540U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x3420a920U);
        WR1_PROG(REG_1600H, 0x00004101U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func101(0xc6664537U, 0x6a88f19fU, 0xbcb7b62bU, 0x51a65f8fU);
    }

    WR1_PROG(REG_1600H, 0x0000366aU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xf5a5f0c2U, 0xfb80f1e7U, 0x1eb3b84aU, 0xf7f23ec7U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xa7d3d8e9U, 0xbdbb5ca9U, 0xf554388cU, 0x6cbdcaa4U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x3420a800U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xd7a396b0U, 0x4ba265c9U, 0xb2410861U, 0xb69ec622U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xd15ae930U, 0x9cab87a5U, 0x07acd3e8U, 0x02a4a296U);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x78137d2fU, 0x3cff59deU, 0x21b038f2U, 0x66464ea6U);
                HW_SCE_p_func043_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                HW_SCE_p_func101(0xdd4cc28fU, 0x7e668064U, 0x667b125bU, 0xdbddda17U);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x798697c6U, 0x18441b11U, 0xdb88ed2dU, 0x5e65e035U);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x2a46c04bU);

                HW_SCE_p_func101(0x352d828cU, 0xcdd74883U, 0x4bc05a3dU, 0x4e3dd827U);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000098U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xf02bfb28U, 0x08c5790dU, 0x22ddf482U, 0xbaa94f09U);
            HW_SCE_p_func044_r1();

            HW_SCE_p_func100(0x64b6b644U, 0x10b9f68eU, 0x59865245U, 0xf1060d22U);
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

            HW_SCE_p_func101(0x26658122U, 0x89a3c24aU, 0x1eeeafc6U, 0xdce185caU);
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

            HW_SCE_p_func100(0x1df82688U, 0x94e7ccbeU, 0x61742becU, 0x7cb96874U);
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
                WR1_PROG(REG_1420H, change_endian_long(0x00000098U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x6478206cU, 0x3f0ccb62U, 0x1b4e1a4bU, 0xd96480efU);
                HW_SCE_p_func092_r1();

                HW_SCE_p_func101(0xa10379b4U, 0xa25e622bU, 0x7e685e17U, 0x26e76b60U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000003U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x2a7ce433U, 0x9aa4cfd0U, 0xf719afcbU, 0x2ccc6180U);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x98bae316U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x000000ccU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x1c6c94a9U, 0xfdb30059U, 0x942359c1U, 0x9fc771b6U);
                HW_SCE_p_func044_r1();

                HW_SCE_p_func101(0x299fe51cU, 0x28278dc2U, 0x3e11a9c5U, 0x7fde349eU);
            }

            HW_SCE_p_func100(0xb599fe6eU, 0xdb680de0U, 0x2d9b6f5dU, 0x22089984U);
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

            HW_SCE_p_func101(0xdff9a5e7U, 0x4ec735b6U, 0xcb48b076U, 0xa7e3b04aU);
        }

        HW_SCE_p_func100(0x86f965c6U, 0xa3ce271fU, 0xb7fd1ff5U, 0x43dae454U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x5b7203a3U, 0xb4a47420U, 0x3fbc29e1U, 0x026d3895U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003534U);

            WR1_PROG(REG_1600H, 0x00003553U);

            WR1_PROG(REG_1600H, 0x00003412U);

            WR1_PROG(REG_1600H, 0x3420a800U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xf2eeab2eU, 0x4b61ae25U, 0xd964018bU, 0x81979456U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000145U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_IV[0]);

                WR1_PROG(REG_1824H, 0x08000065U);
                WR1_PROG(REG_1400H, 0x00410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x07000c04U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                WR1_PROG(REG_1444H, 0x00020061U);
                WR1_PROG(REG_1824H, 0xf8000006U);

                for (iLoop = 0U; iLoop < Header_Len; )
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_Header[iLoop]);
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func216();

                HW_SCE_p_func101(0xe18d6f6dU, 0xb3246c6fU, 0x728bd90aU, 0x3e08a01fU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000001c7U);
                WR1_PROG(REG_1608H, 0x800201c0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[0]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_SeqNum[1]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000008aeU);
                WR1_PROG(REG_1600H, 0x000008cfU);

                WR1_PROG(REG_1600H, 0x0000b460U);
                WR1_PROG(REG_1600H, 0x00000002U);

                WR1_PROG(REG_1600H, 0x01986c64U);
                WR1_PROG(REG_1600H, 0x01986c85U);
                WR1_PROG(REG_1600H, 0x01986ca6U);
                WR1_PROG(REG_1600H, 0x00186cc6U);

                WR1_PROG(REG_1824H, 0x08000145U);
                WR1_PROG(REG_1608H, 0x81040060U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1824H, 0x08000065U);
                WR1_PROG(REG_1400H, 0x00410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x07000c04U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                HW_SCE_p_func031_r1(InData_Header);

                HW_SCE_p_func101(0xcbb26a03U, 0x9ea71d6aU, 0x8a910aefU, 0x3e8ad20cU);
            }

            return FSP_SUCCESS;
        }
    }
}
