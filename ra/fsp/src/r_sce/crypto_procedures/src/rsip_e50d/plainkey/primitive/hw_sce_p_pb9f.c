/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

    HW_SCE_p_func100(0x16be1cd6U, 0x95ac49a5U, 0x80e4c7faU, 0x4db8e170U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x4e176d74U, 0xbe8091ffU, 0x6ec758f8U, 0x7ec5a7daU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xdb84ad07U, 0x4d66219dU, 0xca1e5722U, 0x2ccaddd1U);
        WR1_PROG(REG_1608H, 0x810103c0U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        HW_SCE_p_func100(0x11ac4822U, 0x0540dd22U, 0xc7e5cf63U, 0x4d6acc07U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000020U);
        WR1_PROG(REG_1824H, 0x0d008906U);
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

        HW_SCE_p_func100(0x24df8fe6U, 0x4c2700fbU, 0x6c2117b4U, 0xd2779583U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000020U);
            WR1_PROG(REG_1824H, 0x0d008905U);
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

            HW_SCE_p_func100(0x359d2fadU, 0x9e54bb42U, 0x3ec95bd2U, 0x40eba624U);
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
                HW_SCE_p_func101(0x3d306084U, 0x20838516U, 0x4a7ad98aU, 0x05c73797U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000fdeU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            HW_SCE_p_func100(0x0d909302U, 0x310ce66dU, 0x6d84f867U, 0x0d11b75cU);
            WR1_PROG(REG_182CH, 0x40000020U);
            WR1_PROG(REG_1824H, 0x0d008905U);
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
                HW_SCE_p_func101(0x94f59ce7U, 0x4496a731U, 0x2a261ccfU, 0x31fb6d09U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000d29U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func100(0x3c967e9aU, 0xf5331552U, 0xea879037U, 0x336a855eU);
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

            HW_SCE_p_func101(0x95a512baU, 0x0ef48ef9U, 0xd0051e5aU, 0xc954d2e7U);
        }

        HW_SCE_p_func102(0xb0a4a23dU, 0x2821a6e7U, 0x9e8bd060U, 0x98856b16U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}
