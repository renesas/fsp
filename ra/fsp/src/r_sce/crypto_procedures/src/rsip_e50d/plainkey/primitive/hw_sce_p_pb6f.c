/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub (const uint32_t InData_TextBitLen[],
                                           const uint32_t InData_Text[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_TextBitLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x000037c0U);
    WR1_PROG(REG_1600H, 0x00076bdeU);
    WR1_PROG(REG_1600H, 0x00026fdeU);

    WR1_PROG(REG_1600H, 0x00000bffU);

    WR1_PROG(REG_1600H, 0x38008c00U);
    WR1_PROG(REG_1600H, 0x0000007fU);
    WR1_PROG(REG_1600H, 0x00020020U);
    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1600H, 0x2000abc0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0xc5fac114U, 0xc7d577a7U, 0x6695e641U, 0x80af3b68U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x0cd76d61U, 0x50205986U, 0xbfdf31f0U, 0x46e4da88U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xb1417816U, 0x64cd51b6U, 0xb2a9ee0cU, 0x610a4e81U);
        WR1_PROG(REG_1608H, 0x810103c0U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        HW_SCE_p_func100(0x85074003U, 0xd76d412eU, 0x89698da7U, 0xd70a9649U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x00000020U);
        WR1_PROG(REG_1824H, 0x0d00890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);

        iLoop = 0;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);
            for (iLoop = 4U; iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
        }

        HW_SCE_p_func214();

        WR1_PROG(REG_1600H, 0x38008c00U);
        WR1_PROG(REG_1600H, 0x0000007fU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func100(0xf980dd59U, 0xd581c75dU, 0x0cf0867dU, 0x7a0356f5U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func100(0x42906485U, 0xf65e1b69U, 0xdd306bfaU, 0x0f76b75dU);

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x0c000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
            WR1_PROG(REG_1608H, 0x80040140U);
            WR1_PROG(REG_1400H, 0x03410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_182CH, 0x00000020U);
            WR1_PROG(REG_1824H, 0x0d00880cU);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x00000020U);
            WR1_PROG(REG_1824H, 0x0d00890dU);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[iLoop]);

            WR1_PROG(REG_1600H, 0x000008c6U);
            WR1_PROG(REG_1608H, 0x80840006U);
            WR1_PROG(REG_1400H, 0x03410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80840007U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 4]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 5]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 6]);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Text[iLoop + 7]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b4a0U);
            WR1_PROG(REG_1600H, 0x00000004U);

            WR1_PROG(REG_1600H, 0x00003500U);
            WR1_PROG(REG_1600H, 0x00036908U);
            WR1_PROG(REG_1600H, 0x00008d00U);
            WR1_PROG(REG_1600H, 0x0000000cU);

            WR1_PROG(REG_1600H, 0x000024c8U);

            WR1_PROG(REG_1600H, 0x000024e8U);

            WR1_PROG(REG_1600H, 0x00003826U);

            WR1_PROG(REG_1600H, 0x00003847U);

            WR1_PROG(REG_1600H, 0x00003460U);
            WR1_PROG(REG_1600H, 0x00008c60U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x0000b480U);
            WR1_PROG(REG_1600H, 0xffffffffU);
            WR1_PROG(REG_1600H, 0x00004403U);
            WR1_PROG(REG_1600H, 0x00007484U);

            WR1_PROG(REG_1600H, 0x00000c24U);

            WR1_PROG(REG_1600H, 0x00001484U);

            WR1_PROG(REG_1600H, 0x00000c44U);

            WR1_PROG(REG_1600H, 0x00001041U);

            WR1_PROG(REG_1600H, 0x00003c47U);

            WR1_PROG(REG_1600H, 0x000037e0U);
            WR1_PROG(REG_1600H, 0x00008fe0U);
            WR1_PROG(REG_1600H, 0x0000007fU);

            WR1_PROG(REG_1600H, 0x38008fe0U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x1000a7e0U);
            WR1_PROG(REG_1600H, 0x00000020U);

            WR1_PROG(REG_1600H, 0x0000b7c0U);
            WR1_PROG(REG_1600H, 0x00000080U);
            WR1_PROG(REG_1600H, 0x00002bdfU);
            WR1_PROG(REG_1600H, 0x00056bdeU);
            WR1_PROG(REG_1600H, 0x0000353eU);

            WR1_PROG(REG_1608H, 0x810103c0U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x000024c5U);
                WR1_PROG(REG_1600H, 0x000024e5U);

                WR1_PROG(REG_1600H, 0x00003ba6U);
                WR1_PROG(REG_1600H, 0x00003fa7U);

                WR1_PROG(REG_1600H, 0x000033c0U);
                HW_SCE_p_func101(0x99075d9aU, 0x8c43411aU, 0x23dc9040U, 0xdd5b5efeU);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            HW_SCE_p_func100(0x8d8ac482U, 0xd9e5d7bdU, 0x56ed8bf5U, 0xac0e6073U);

            WR1_PROG(REG_1600H, 0x38000fdeU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1824H, 0x08000045U);
            WR1_PROG(REG_1608H, 0x81040140U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_182CH, 0x00000020U);
            WR1_PROG(REG_1824H, 0x0d00890dU);
            WR1_PROG(REG_1608H, 0x81840007U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_Text[iLoop]);

            WR1_PROG(REG_1600H, 0x000008c6U);

            WR1_PROG(REG_1600H, 0x000024c8U);

            WR1_PROG(REG_1600H, 0x00003826U);

            WR1_PROG(REG_1600H, 0x00000c24U);

            WR1_PROG(REG_1600H, 0x00003c26U);

            WR1_PROG(REG_1600H, 0x00000bffU);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x000024c5U);

                WR1_PROG(REG_1600H, 0x00003fe6U);

                WR1_PROG(REG_1600H, 0x00003120U);
                HW_SCE_p_func101(0x0f6ea9b4U, 0x35d56368U, 0x9edeab9bU, 0x4d53d4a2U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            HW_SCE_p_func100(0x348785baU, 0x25bc91d9U, 0x06c9ccbeU, 0xe8f10b36U);

            WR1_PROG(REG_1600H, 0x38000d29U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x000008c6U);
            WR1_PROG(REG_1608H, 0x81840006U);
            WR1_PROG(REG_1408H, 0x00005012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 4]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 5]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 6]);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 7]);

            HW_SCE_p_func101(0x78293427U, 0x29b3e19cU, 0xba7a23cbU, 0xd38de0cdU);
        }

        HW_SCE_p_func102(0xfe87e389U, 0x65abe748U, 0x88c6319fU, 0x2575a13dU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}
