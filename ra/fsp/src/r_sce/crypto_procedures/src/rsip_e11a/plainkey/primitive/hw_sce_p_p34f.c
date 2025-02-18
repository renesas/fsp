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
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x14bbdd67U, 0x7839bf3bU, 0x53eb419fU, 0x2e398e35U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xe3fc264bU, 0xfdea1122U, 0x02402b59U, 0x6fd16b08U);
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

        HW_SCE_p_func100(0x9cb6ff8eU, 0x622d029eU, 0x9d8413b4U, 0x1a6bb5efU);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0xb8bffe43U, 0x2ae86e82U, 0x9f854f58U, 0x81c72fa6U);
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

            HW_SCE_p_func101(0x2baa7ddeU, 0xb760ef47U, 0xe5376311U, 0x32ea06c6U);
        }

        HW_SCE_p_func100(0xf78fa061U, 0x612507b3U, 0x0fb55e68U, 0xdc0602f5U);
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

        HW_SCE_p_func102(0xa636f20dU, 0xf821e6bcU, 0xa5693fd9U, 0xdafcce12U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
