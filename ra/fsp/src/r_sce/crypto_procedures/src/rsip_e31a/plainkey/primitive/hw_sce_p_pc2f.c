/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub (const uint32_t InData_TextBitLen[],
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

    HW_SCE_p_func100(0x9ea2fc44U, 0x036e91c6U, 0xcfb0ccf9U, 0x29adbf8eU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x65141a16U, 0xbe813d65U, 0x0bc8f9f4U, 0x05ca1212U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x413c2f88U, 0x5c3c396dU, 0xb4c612bcU, 0xe88c8597U);
        WR1_PROG(REG_9CH, 0x81010040U);
        WR1_PROG(REG_08H, 0x00005006U);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        HW_SCE_p_func100(0x87d7217eU, 0x3e53cba8U, 0x07c6b5d6U, 0x75be6e23U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000020U);
        WR1_PROG(REG_D0H, 0x0d00890eU);
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

        HW_SCE_p_func100(0xa77f9192U, 0xf8a0bb5eU, 0x1262755eU, 0x45a1ad21U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0xdb3f2032U, 0x3081082bU, 0x7b577db1U, 0x08c9a2f1U);

            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D0H, 0x0c000104U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_B0H, 0x00000401U);
            WR1_PROG(REG_00H, 0x00c10009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_B0H, 0x00000402U);
            WR1_PROG(REG_00H, 0x00c10009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000000a1U);
            WR1_PROG(REG_D4H, 0x40000020U);
            WR1_PROG(REG_D0H, 0x0d00880cU);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000020U);
            WR1_PROG(REG_D0H, 0x0d00890dU);
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
                HW_SCE_p_func101(0xe350b7f3U, 0x6e838c22U, 0x9f3d7f43U, 0x8842d368U);
            }

            HW_SCE_p_func100(0x59b711f1U, 0xee3a2a0cU, 0x5ef7109dU, 0x292aecedU);

            WR1_PROG(REG_94H, 0x38000c42U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_B0H, 0x00000801U);
            WR1_PROG(REG_00H, 0x00430009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_B0H, 0x00000802U);
            WR1_PROG(REG_00H, 0x00430009U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x0000b4e0U);
            WR1_PROG(REG_94H, 0x00000010U);
            WR1_PROG(REG_D4H, 0x40000020U);
            WR1_PROG(REG_D0H, 0x0d00890dU);
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
                HW_SCE_p_func101(0xc16ec62dU, 0xf4c146d1U, 0x1ba65951U, 0x545d3a3dU);
            }

            HW_SCE_p_func100(0x56038928U, 0x588c2fa7U, 0xa82a48f5U, 0xed229f1aU);

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

            HW_SCE_p_func101(0x2e07d167U, 0x320a6455U, 0x7426f1d4U, 0xf4a82c97U);
        }

        HW_SCE_p_func102(0xc9bf204bU, 0xcae1ccbfU, 0xb36c267eU, 0x812c36c0U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
