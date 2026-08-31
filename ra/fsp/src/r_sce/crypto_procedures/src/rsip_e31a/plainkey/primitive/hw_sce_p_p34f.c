/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub005(0x000001c7U, 0x80020040U);
    WR1_PROG(REG_2CH, InData_TextLen[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextLen[1]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x0000b400U, 0x0000007FU, 0x0000b420U, 0xFFFFFF00U);
    HW_SCE_p_func_sub006(0x0c002823U, 0x04a02802U, 0x00270000U);

    static const uint32_t Param_p34f_func100_001[] =
    {
        0x646761e8U, 0xf11e0355U, 0x9a04805fU, 0xed940e12U,
    };
    HW_SCE_p_func100(Param_p34f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p34f_func102_001[] =
        {
            0x79aa34dcU, 0x8e6a768bU, 0x728f489eU, 0x0cb80d2eU,
        };
        HW_SCE_p_func102(Param_p34f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub001(0x00003403U, 0x00036800U, 0x08008c00U, 0x0000000fU);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        static const uint32_t Param_p34f_func100_002[] =
        {
            0x7eff3920U, 0x1a91c332U, 0x49a37886U, 0xb6a7b820U,
        };
        HW_SCE_p_func100(Param_p34f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p34f_func100_003[] =
            {
                0x5d1c1075U, 0x70e564d6U, 0xa2b38be9U, 0x62000e7dU,
            };
            HW_SCE_p_func100(Param_p34f_func100_003);
            HW_SCE_p_func_sub007(0x000003c1U, 0x40000020U, 0x07008d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub003(0x03410011U);

            WR1_PROG(REG_94H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub022(0x3c002820U, 0x12003c81U, 0x00002c20U);
            }

            WR1_PROG(REG_D4H, 0x00008000U);
            HW_SCE_p_func_sub013(0x0e128455U, 0x00000821U, 0x81840001U);
            HW_SCE_p_func_sub003(0x00490011U);

            WAIT_STS(REG_C8H, 6, 0);
            WR1_PROG(REG_40H, 0x00000400U);
            WR1_PROG(REG_40H, 0x00000500U);

            HW_SCE_p_func_sub009(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            static const uint32_t Param_p34f_func101_001[] =
            {
                0x320dc3a8U, 0x2ea63a90U, 0x42a15967U, 0x969fa954U,
            };
            HW_SCE_p_func101(Param_p34f_func101_001);
        }

        static const uint32_t Param_p34f_func100_004[] =
        {
            0xb58a477dU, 0x6250cdb4U, 0x3dd938f5U, 0x900eeb06U,
        };
        HW_SCE_p_func100(Param_p34f_func100_004);
        HW_SCE_p_func_sub007(0x000001c1U, 0x00008000U, 0x0e128455U);
        WR2_ADDR(REG_2CH, &InData_DataALen[0]);

        WR1_PROG(REG_9CH, 0x81020040U);
        HW_SCE_p_func_sub003(0x00490009U);

        WR1_PROG(REG_D0H, 0x08000045U);
        WR1_PROG(REG_94H, 0x0000b420U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x81840001U);
        HW_SCE_p_func_sub003(0x00490011U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000020U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        static const uint32_t Param_p34f_func102_002[] =
        {
            0x23ab8a2dU, 0x409ee5ceU, 0x7b71074eU, 0x9337e696U,
        };
        HW_SCE_p_func102(Param_p34f_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
