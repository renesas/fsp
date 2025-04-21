/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub (const uint32_t InData_Text[],
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

    HW_SCE_p_func100(0x646761e8U, 0xf11e0355U, 0x9a04805fU, 0xed940e12U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x79aa34dcU, 0x8e6a768bU, 0x728f489eU, 0x0cb80d2eU);
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

        HW_SCE_p_func100(0x7eff3920U, 0x1a91c332U, 0x49a37886U, 0xb6a7b820U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0x5d1c1075U, 0x70e564d6U, 0xa2b38be9U, 0x62000e7dU);
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000020U);
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

            HW_SCE_p_func101(0x320dc3a8U, 0x2ea63a90U, 0x42a15967U, 0x969fa954U);
        }

        HW_SCE_p_func100(0xb58a477dU, 0x6250cdb4U, 0x3dd938f5U, 0x900eeb06U);
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

        WR1_PROG(REG_D4H, 0x40000020U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0x23ab8a2dU, 0x409ee5ceU, 0x7b71074eU, 0x9337e696U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
