/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha2HmacFinalSub (const uint32_t InData_Cmd[],
                                   const uint32_t InData_Msg[],
                                   const uint32_t InData_MAC[],
                                   const uint32_t InData_length[],
                                   uint32_t       OutData_MAC[],
                                   const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_118H, 0, 1);

    WR1_PROG(REG_14H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR16_ADDR(REG_2CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_14H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_2CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_14H, 0x00000000U);
    WAIT_STS(REG_118H, 8, 0);
    WR1_PROG(REG_40H, 0x00001600U);

    WAIT_STS(REG_118H, 4, 1);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0x89383ee0U, 0xd972216cU, 0xb16904f6U, 0xa9abeabaU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func100(0xeb393190U, 0x50a34c17U, 0x85a8d7bdU, 0xb8b8ff16U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            HW_SCE_p_func100(0xd27bebadU, 0x25ac5e55U, 0x91f4ac57U, 0xba4b0e62U);
            WR1_PROG(REG_08H, 0x00004022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_MAC[0]);

            HW_SCE_p_func102(0x1fb4d6b3U, 0x26b6bbe9U, 0xa66b3111U, 0x1bf2c6f0U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            HW_SCE_p_func100(0x39c1a6b7U, 0x4a47a222U, 0xe330e226U, 0xd4054e91U);
            WR1_PROG(REG_08H, 0x00004032U);
            WAIT_STS(REG_08H, 30, 1);
            RD12_ADDR(REG_2CH, &OutData_MAC[0]);

            HW_SCE_p_func102(0x6e091fadU, 0xa4aa6044U, 0xb29e9523U, 0x89298f8aU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            HW_SCE_p_func100(0x7c6b624aU, 0x1794d6a3U, 0x99528880U, 0x73943314U);
            WR1_PROG(REG_08H, 0x00004042U);
            WAIT_STS(REG_08H, 30, 1);
            RD16_ADDR(REG_2CH, &OutData_MAC[0]);

            HW_SCE_p_func102(0xb319281bU, 0x9f86292dU, 0x058da764U, 0x73f1676fU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }

        return FSP_SUCCESS;
    }
    else
    {
        HW_SCE_p_func100(0x56fb8de7U, 0x45376641U, 0x45ce47d5U, 0xa410c2f2U);

        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010020U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_length[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000020U);

            HW_SCE_p_func101(0xdfebb7d4U, 0xfa664c7bU, 0xe7885e06U, 0xbcadc797U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000030U);

            HW_SCE_p_func101(0xfd9a58b7U, 0x7de219c9U, 0x22293563U, 0x2473769fU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000040U);

            HW_SCE_p_func101(0x4403f0d2U, 0xd91975f7U, 0xa0bb31dbU, 0xd198f9b8U);
        }

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000004U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        WR1_PROG(REG_94H, 0x34202841U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        HW_SCE_p_func100(0x00471861U, 0x787b159aU, 0x215321f8U, 0x4e30a891U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x35c6ba41U, 0xf290472eU, 0x8335f4c3U, 0x24a970b5U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x5d7cc8e0U, 0x0349e8d5U, 0x18f0327bU, 0x9e171c12U);

            WR1_PROG(REG_94H, 0x000008c6U);

            WR1_PROG(REG_94H, 0x000008a5U);

            WR1_PROG(REG_94H, 0x00026842U);

            WR1_PROG(REG_9CH, 0x81010040U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; )
            {
                WR1_PROG(REG_94H, 0x000008e7U);

                WR1_PROG(REG_9CH, 0x80840007U);
                WR1_PROG(REG_00H, 0x03450011U);

                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_14H, 0x000003c1U);
                WR1_PROG(REG_D0H, 0x08000045U);
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_MAC[iLoop]);

                WR1_PROG(REG_94H, 0x00000800U);
                for (jLoop = 0U; jLoop < 16U; jLoop++)
                {
                    WR1_PROG(REG_94H, 0x3c0028a1U);
                    WR1_PROG(REG_94H, 0x12003c07U);
                    WR1_PROG(REG_94H, 0x00002ce0U);
                    WR1_PROG(REG_94H, 0x00002ca0U);
                }

                WR1_PROG(REG_D0H, 0x9c000005U);
                WR1_PROG(REG_94H, 0x000008e7U);
                WR1_PROG(REG_9CH, 0x81840007U);
                WR1_PROG(REG_00H, 0x00490011U);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);

                WR1_PROG(REG_94H, 0x0000a4c0U);
                WR1_PROG(REG_94H, 0x00000004U);

                HW_SCE_p_func101(0xd3e09a43U, 0xc57c457cU, 0xb0e80ea5U, 0x8ca1b691U);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_94H, 0x000008c2U);

            WR1_PROG(REG_94H, 0x00007c06U);
            WR1_PROG(REG_40H, 0x00602000U);

            HW_SCE_p_func100(0x98808fa4U, 0x2369c4a2U, 0x0dc6e1e3U, 0x7796a29cU);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x5a476d01U, 0xbec27248U, 0xe6a63bbcU, 0xdeaf7a63U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0x20a1692fU, 0x99fe752eU, 0xcdc0d901U, 0x1c344197U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
