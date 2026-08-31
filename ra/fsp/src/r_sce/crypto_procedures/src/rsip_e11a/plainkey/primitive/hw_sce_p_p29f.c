/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub (const uint32_t InData_Text[],
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

    HW_SCE_p_func_sub001(0x0000b400U, 0x0000007FU, 0x0000b420U);
    HW_SCE_p_func_sub001(0xFFFFFF00U, 0x0c002823U, 0x04a02802U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    static const uint32_t Param_p29f_func100_001[] =
    {
        0x88894300U, 0x1bccb8c3U, 0xec0432dbU, 0x54099e76U,
    };
    HW_SCE_p_func100(Param_p29f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p29f_func102_001[] =
        {
            0x5ed35366U, 0x60a441a3U, 0xc2ca981cU, 0x84ee1ba4U,
        };
        HW_SCE_p_func102(Param_p29f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub001(0x00003403U, 0x00036800U, 0x08008c00U);
        HW_SCE_p_func_sub009(0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p29f_func100_002[] =
        {
            0xf67fa0dbU, 0xa532d818U, 0x6cb68751U, 0x863dce91U,
        };
        HW_SCE_p_func100(Param_p29f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p29f_func100_003[] =
            {
                0xca3feb6eU, 0x5f8c5dc1U, 0x196966d6U, 0xefc37e08U,
            };
            HW_SCE_p_func100(Param_p29f_func100_003);
            HW_SCE_p_func_sub007(0x000003c1U, 0x00000020U, 0x07008d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub002(0x03410011U);

            WR1_PROG(REG_94H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3c002820U, 0x12003c81U, 0x00002c20U);
            }

            WR1_PROG(REG_D4H, 0x00008000U);
            HW_SCE_p_func_sub016(0x0e128455U, 0x00000821U, 0x81840001U);
            HW_SCE_p_func_sub002(0x00490011U);

            WAIT_STS(REG_C8H, 6, 0);
            WR1_PROG(REG_40H, 0x00000400U);
            WR1_PROG(REG_40H, 0x00000500U);

            HW_SCE_p_func_sub012(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            static const uint32_t Param_p29f_func101_001[] =
            {
                0x19464602U, 0xcde619edU, 0x4896fc96U, 0xe7edecd2U,
            };
            HW_SCE_p_func101(Param_p29f_func101_001);
        }

        static const uint32_t Param_p29f_func100_004[] =
        {
            0x81b5f1c2U, 0xc3fffe77U, 0xbf3d7fb9U, 0x06f56007U,
        };
        HW_SCE_p_func100(Param_p29f_func100_004);
        HW_SCE_p_func_sub007(0x000001c1U, 0x00008000U, 0x0e128455U);
        WR2_ADDR(REG_2CH, &InData_DataALen[0]);

        WR1_PROG(REG_9CH, 0x81020040U);
        HW_SCE_p_func_sub002(0x00490009U);

        WR1_PROG(REG_D0H, 0x08000045U);
        HW_SCE_p_func_sub013(0x81840001U);
        HW_SCE_p_func_sub002(0x00490011U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x00000020U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        static const uint32_t Param_p29f_func102_002[] =
        {
            0x1a085af7U, 0x4e8e3030U, 0x1c77694dU, 0x7604c6b6U,
        };
        HW_SCE_p_func102(Param_p29f_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
