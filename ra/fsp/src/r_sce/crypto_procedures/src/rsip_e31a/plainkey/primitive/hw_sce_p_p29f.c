/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_DataT[])
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
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xc0fd7594U, 0x475bd122U, 0x64adf2dcU, 0x93dd73efU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf5871566U, 0xd3a5a14fU, 0x6cc6ef60U, 0x1d36c559U);
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
        WR1_PROG(REG_40H, 0x00A70000U);

        HW_SCE_p_func100(0xbec7df7cU, 0x6b82b62aU, 0x0b9684b5U, 0xf0ee50aaU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0x428f9823U, 0xa6aee347U, 0x45fc41e2U, 0xe7cc1eebU);
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x00000020U);
            WR1_PROG(REG_D0H, 0x07008d05U);
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

            WR1_PROG(REG_D4H, 0x00008000U);
            WR1_PROG(REG_D0H, 0x0e128455U);
            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x81840001U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WAIT_STS(REG_C8H, 6, 0);
            WR1_PROG(REG_40H, 0x00000400U);
            WR1_PROG(REG_40H, 0x00000500U);

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

            HW_SCE_p_func101(0x225a1956U, 0x8548cddbU, 0xc73e7a9eU, 0xe7cb49c2U);
        }

        HW_SCE_p_func100(0x2623b4ccU, 0x60c26a42U, 0x933b5c2aU, 0xfac76d8eU);
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

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0xba175fe9U, 0xc2bdff30U, 0x5abf6002U, 0x0b30ff58U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
