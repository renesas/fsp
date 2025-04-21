/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub (const uint32_t InData_TextBitLen[],
                                           const uint32_t InData_Text[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextBitLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x00003440U);
    WR1_PROG(REG_94H, 0x00076842U);
    WR1_PROG(REG_94H, 0x00026c42U);

    WR1_PROG(REG_94H, 0x00000821U);

    WR1_PROG(REG_94H, 0x38008c00U);
    WR1_PROG(REG_94H, 0x0000007fU);
    WR1_PROG(REG_94H, 0x00020020U);
    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000080U);
    WR1_PROG(REG_94H, 0x1000d020U);
    WR1_PROG(REG_94H, 0x2000a840U);
    WR1_PROG(REG_94H, 0x00000004U);
    WR1_PROG(REG_94H, 0x00000080U);
    WR1_PROG(REG_94H, 0x38000c21U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A70000U);

    HW_SCE_p_func100(0x9c2f64d5U, 0x7832a189U, 0x0fb5f831U, 0xbb7f2bb1U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x46f39f88U, 0xe7072f86U, 0x1c02d5e5U, 0xafc52d1fU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x6a354ddcU, 0x10a8054eU, 0x7d955b00U, 0x79eb430bU);
        WR1_PROG(REG_9CH, 0x81010040U);
        WR1_PROG(REG_08H, 0x00005006U);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        HW_SCE_p_func100(0x59a03fa9U, 0x253c69a4U, 0x442f29aaU, 0x1cbac808U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000020U);
        WR1_PROG(REG_D0H, 0x0d008906U);
        WR1_PROG(REG_08H, 0x000c1000U);

        iLoop = 0U;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_Text[0]);
            for (iLoop = 4; iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
                WAIT_STS(REG_08H, 30, 1);
                RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
        }

        HW_SCE_p_func206();

        WR1_PROG(REG_94H, 0x38008c00U);
        WR1_PROG(REG_94H, 0x0000007fU);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        HW_SCE_p_func100(0x9a389393U, 0x2517e6c9U, 0x664a2109U, 0xa146b58cU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000020U);
            WR1_PROG(REG_D0H, 0x0d008905U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_Text[iLoop]);

            WR1_PROG(REG_94H, 0x000008c6U);
            WR1_PROG(REG_9CH, 0x80840006U);
            WR1_PROG(REG_00H, 0x03410011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x0000b4e0U);
            WR1_PROG(REG_94H, 0x00000010U);
            WR1_PROG(REG_14H, 0x000003c7U);
            WR1_PROG(REG_9CH, 0x80840007U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 4]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 5]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 6]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 7]);
            WR1_PROG(REG_24H, 0x00000000U);

            WR1_PROG(REG_94H, 0x000034a0U);
            WR1_PROG(REG_94H, 0x000368a5U);
            WR1_PROG(REG_94H, 0x00008ca0U);
            WR1_PROG(REG_94H, 0x0000000cU);

            WR1_PROG(REG_94H, 0x000024c5U);

            WR1_PROG(REG_94H, 0x000024e5U);

            WR1_PROG(REG_94H, 0x00003826U);

            WR1_PROG(REG_94H, 0x00003847U);

            WR1_PROG(REG_94H, 0x00003460U);
            WR1_PROG(REG_94H, 0x00008c60U);
            WR1_PROG(REG_94H, 0x0000001fU);

            WR1_PROG(REG_94H, 0x0000b480U);
            WR1_PROG(REG_94H, 0xffffffffU);
            WR1_PROG(REG_94H, 0x00004403U);
            WR1_PROG(REG_94H, 0x00007484U);

            WR1_PROG(REG_94H, 0x00000c24U);

            WR1_PROG(REG_94H, 0x00001484U);

            WR1_PROG(REG_94H, 0x00000c44U);

            WR1_PROG(REG_94H, 0x00001041U);

            WR1_PROG(REG_94H, 0x00003c47U);

            WR1_PROG(REG_94H, 0x00003420U);
            WR1_PROG(REG_94H, 0x00008c20U);
            WR1_PROG(REG_94H, 0x0000007fU);

            WR1_PROG(REG_94H, 0x38008c20U);
            WR1_PROG(REG_94H, 0x0000001fU);
            WR1_PROG(REG_94H, 0x1000a420U);
            WR1_PROG(REG_94H, 0x00000020U);

            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000080U);
            WR1_PROG(REG_94H, 0x00002841U);
            WR1_PROG(REG_94H, 0x00056842U);
            WR1_PROG(REG_94H, 0x00003402U);

            HW_SCE_p_func100(0x2d480fc7U, 0x67919955U, 0x16a0bb3aU, 0xe43ab1a0U);
            WR1_PROG(REG_9CH, 0x81010040U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000004U);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_94H, 0x000024c3U);
                WR1_PROG(REG_94H, 0x000024e3U);

                WR1_PROG(REG_94H, 0x00003826U);
                WR1_PROG(REG_94H, 0x00003c27U);

                WR1_PROG(REG_94H, 0x00003040U);
                HW_SCE_p_func101(0x81d901baU, 0xbdacedbdU, 0x93399d78U, 0x48bf8131U);
            }

            WR1_PROG(REG_94H, 0x38000c42U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            HW_SCE_p_func100(0xf37d345cU, 0x8df94728U, 0x45fbb8c3U, 0x7f7cbd0aU);
            WR1_PROG(REG_94H, 0x0000b4e0U);
            WR1_PROG(REG_94H, 0x00000010U);
            WR1_PROG(REG_D4H, 0x40000020U);
            WR1_PROG(REG_D0H, 0x0d008905U);
            WR1_PROG(REG_9CH, 0x81840007U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_Text[iLoop]);

            WR1_PROG(REG_94H, 0x000008c6U);

            WR1_PROG(REG_94H, 0x000024c5U);

            WR1_PROG(REG_94H, 0x00003826U);

            WR1_PROG(REG_94H, 0x00000c24U);

            WR1_PROG(REG_94H, 0x00003c26U);

            WR1_PROG(REG_94H, 0x00000821U);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_94H, 0x000024c3U);

                WR1_PROG(REG_94H, 0x00003c26U);

                WR1_PROG(REG_94H, 0x00003000U);
                HW_SCE_p_func101(0x910ed915U, 0xc6e84522U, 0xb1395bdaU, 0xb3e29e12U);
            }

            HW_SCE_p_func100(0x6485fc1fU, 0x8ece303fU, 0x93db37f7U, 0xaa956d85U);
            WR1_PROG(REG_94H, 0x38000c00U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_94H, 0x000008c6U);
            WR1_PROG(REG_9CH, 0x81840006U);
            WR1_PROG(REG_08H, 0x00005012U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 4]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 5]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 6]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 7]);

            HW_SCE_p_func101(0x36baf791U, 0xddcbfbdbU, 0xa2f90051U, 0x58bb561cU);
        }

        HW_SCE_p_func102(0xd8f5a4a1U, 0x776c0a03U, 0xc7e05f70U, 0x88c38fdfU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
