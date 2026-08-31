/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           const uint32_t InData_DataT[],
                                           const uint32_t InData_DataTLen[],
                                           uint32_t       OutData_Text[])
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

    HW_SCE_p_func_sub005(0x000000c7U, 0x800100a0U);
    WR1_PROG(REG_2CH, InData_DataTLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub006(0x380088a0U, 0x00000000U, 0x00260000U);

    HW_SCE_p_func_sub001(0x0000b420U, 0x00000010U, 0x34202825U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    static const uint32_t Param_p32f_func100_001[] =
    {
        0x27de1cffU, 0xe5e8df64U, 0xedcd99a0U, 0x034a46f3U,
    };
    HW_SCE_p_func100(Param_p32f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p32f_func102_001[] =
        {
            0x094b802eU, 0x846e3f9cU, 0xe7445d0eU, 0x1f89b48fU,
        };
        HW_SCE_p_func102(Param_p32f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub001(0x00003403U, 0x00036800U, 0x08008c00U);
        HW_SCE_p_func_sub009(0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p32f_func100_002[] =
        {
            0xcc50a9e5U, 0xe9cea62eU, 0xb52f25f5U, 0xbb2cfc33U,
        };
        HW_SCE_p_func100(Param_p32f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p32f_func100_003[] =
            {
                0x0e276017U, 0xfe30a68aU, 0x11096f8cU, 0x366678c4U,
            };
            HW_SCE_p_func100(Param_p32f_func100_003);
            HW_SCE_p_func_sub007(0x000003c1U, 0x00008020U, 0x20008d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub002(0x03410011U);

            WR1_PROG(REG_94H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3c002820U, 0x12003c81U, 0x00002c20U);
            }

            WR1_PROG(REG_94H, 0x00000821U);
            HW_SCE_p_func_sub012(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            static const uint32_t Param_p32f_func101_001[] =
            {
                0x4b2001d1U, 0xeb1423c4U, 0xc3fc5ff5U, 0x0909c9ecU,
            };
            HW_SCE_p_func101(Param_p32f_func101_001);
        }

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

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        HW_SCE_p_func_sub002(0x03410011U);

        WR1_PROG(REG_94H, 0x00000884U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            HW_SCE_p_func_sub001(0x3c002825U, 0x12003c81U, 0x00002c20U);
        }

        HW_SCE_p_func_sub008(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_2CH, &InData_DataT[0]);

        HW_SCE_p_func_sub016(0x9c100005U, 0x00000821U, 0x81840001U);
        HW_SCE_p_func_sub002(0x00490011U);

        static const uint32_t Param_p32f_func100_004[] =
        {
            0xc0ff796aU, 0xc4051af6U, 0x2eb84008U, 0x8fd50da4U,
        };
        HW_SCE_p_func100(Param_p32f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p32f_func102_002[] =
            {
                0x8c6ea52fU, 0x8ad24963U, 0x626bddb3U, 0xb92fe7b0U,
            };
            HW_SCE_p_func102(Param_p32f_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_p32f_func102_003[] =
            {
                0xcd6451f1U, 0x0c2a34b4U, 0x6bf17242U, 0xe73b701eU,
            };
            HW_SCE_p_func102(Param_p32f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
