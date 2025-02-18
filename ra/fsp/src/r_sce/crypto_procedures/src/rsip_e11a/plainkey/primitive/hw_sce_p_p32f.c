/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           const uint32_t InData_DataT[],
                                           const uint32_t InData_DataTLen[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x000001c7U);
    WR1_PROG(REG_9CH, 0x80020040U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextLen[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextLen[1]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x0000b400U);
    WR1_PROG(REG_94H, 0x0000007FU);
    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0xFFFFFF00U);
    WR1_PROG(REG_94H, 0x0c002823U);
    WR1_PROG(REG_94H, 0x04a02802U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x800100a0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_DataTLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x380088a0U);
    WR1_PROG(REG_94H, 0x00000000U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0x00000010U);
    WR1_PROG(REG_94H, 0x34202825U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x27de1cffU, 0xe5e8df64U, 0xedcd99a0U, 0x034a46f3U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x094b802eU, 0x846e3f9cU, 0xe7445d0eU, 0x1f89b48fU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003403U);
        WR1_PROG(REG_94H, 0x00036800U);

        WR1_PROG(REG_94H, 0x08008c00U);
        WR1_PROG(REG_94H, 0x0000000fU);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A60000U);

        HW_SCE_p_func100(0xcc50a9e5U, 0xe9cea62eU, 0xb52f25f5U, 0xbb2cfc33U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0x0e276017U, 0xfe30a68aU, 0x11096f8cU, 0x366678c4U);
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x00008020U);
            WR1_PROG(REG_D0H, 0x20008d05U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            WR1_PROG(REG_00H, 0x03410011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_94H, 0x3c002820U);
                WR1_PROG(REG_94H, 0x12003c81U);
                WR1_PROG(REG_94H, 0x00002c20U);
            }

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81840001U);

            WR1_PROG(REG_08H, 0x00005012U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            HW_SCE_p_func101(0x4b2001d1U, 0xeb1423c4U, 0xc3fc5ff5U, 0x0909c9ecU);
        }

        WR1_PROG(REG_14H, 0x000001c1U);
        WR1_PROG(REG_D4H, 0x00008000U);
        WR1_PROG(REG_D0H, 0x0e128455U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &InData_DataALen[0]);

        WR1_PROG(REG_9CH, 0x81020040U);
        WR1_PROG(REG_00H, 0x00490009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_D0H, 0x08000045U);
        WR1_PROG(REG_94H, 0x0000b420U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x81840001U);
        WR1_PROG(REG_00H, 0x00490011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x0c100104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D4H, 0x00000020U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        WR1_PROG(REG_00H, 0x03410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000884U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_94H, 0x3c002825U);
            WR1_PROG(REG_94H, 0x12003c81U);
            WR1_PROG(REG_94H, 0x00002c20U);
        }

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0x08000055U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_DataT[0]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x81840001U);
        WR1_PROG(REG_00H, 0x00490011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xc0ff796aU, 0xc4051af6U, 0x2eb84008U, 0x8fd50da4U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x8c6ea52fU, 0x8ad24963U, 0x626bddb3U, 0xb92fe7b0U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            HW_SCE_p_func102(0xcd6451f1U, 0x0c2a34b4U, 0x6bf17242U, 0xe73b701eU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
