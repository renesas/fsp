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

    WR1_PROG(REG_ECH, 0x000035c8U);

    WR1_PROG(REG_104H, 0x00000168U);
    WR1_PROG(REG_E0H, 0x80020100U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[0]);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[1]);

    HW_SCE_p_func_sub014(0x3420a9c0U, 0x00000004U, 0x00260000U);

    static const uint32_t Param_p32f_func100_001[] =
    {
        0xb41d1f9eU, 0xe710bdb5U, 0xacaee47dU, 0xefa843beU,
    };
    HW_SCE_p_func100(Param_p32f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_ECH, 0x0000b580U);
        WR1_PROG(REG_ECH, 0x0000007FU);
        WR1_PROG(REG_ECH, 0x0000b5a0U);
        HW_SCE_p_func_sub007(0xFFFFFF00U, 0x0c0029a9U, 0x04a02988U, 0x00260000U);

        static const uint32_t Param_p32f_func101_001[] =
        {
            0xea31b4e7U, 0xdda25e33U, 0xc9fca5d6U, 0xd502596bU,
        };
        HW_SCE_p_func101(Param_p32f_func101_001);
    }
    else
    {
        WR1_PROG(REG_ECH, 0x0000b580U);
        WR1_PROG(REG_ECH, 0x00000000U);
        WR1_PROG(REG_ECH, 0x0000b5a0U);
        HW_SCE_p_func_sub007(0x00020800U, 0x0c0029a9U, 0x04a02988U, 0x00260000U);

        static const uint32_t Param_p32f_func101_002[] =
        {
            0x60e816a5U, 0xc35c8141U, 0xd34d1aebU, 0x1529b668U,
        };
        HW_SCE_p_func101(Param_p32f_func101_002);
    }

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010140U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_DataTLen[0]);

    HW_SCE_p_func_sub014(0x38008940U, 0x00000000U, 0x00260000U);

    HW_SCE_p_func_sub007(0x0000b7e0U, 0x00000010U, 0x34202beaU, 0x00260000U);

    static const uint32_t Param_p32f_func100_002[] =
    {
        0x69b6f2edU, 0xcc90f830U, 0xe9ba1093U, 0x7e674d71U,
    };
    HW_SCE_p_func100(Param_p32f_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p32f_func102_001[] =
        {
            0x5f413bf4U, 0x582ef8e3U, 0x45724ad0U, 0xd56e3a4dU,
        };
        HW_SCE_p_func102(Param_p32f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);
        HW_SCE_p_func_sub007(0x00036800U, 0x08008c00U, 0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p32f_func100_003[] =
        {
            0x7b94995cU, 0xc775d50fU, 0x888e5dbfU, 0x76c1768fU,
        };
        HW_SCE_p_func100(Param_p32f_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00000885U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);

            WR1_PROG(REG_D0H, 0x00000020U);
            HW_SCE_p_func_sub013(0x000087b5U, 0x00007113U);

            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x80840001U, 0x00008213U);

            WR1_PROG(REG_ECH, 0x00000bffU);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x3c002be0U);
                WR1_PROG(REG_ECH, 0x12003c3fU);
                WR1_PROG(REG_ECH, 0x00002fe0U);
            }

            static const uint32_t Param_p32f_func100_004[] =
            {
                0x76d42054U, 0x09f07003U, 0x4d85d74aU, 0xb09e3f91U,
            };
            HW_SCE_p_func100(Param_p32f_func100_004);
            WR1_PROG(REG_C4H, 0x00000885U);
            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00002813U);
            WR1_PROG(REG_04H, 0x00000213U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[0]);

            static const uint32_t Param_p32f_func101_003[] =
            {
                0x24faa837U, 0x86969c93U, 0x23100a1eU, 0x5881af9dU,
            };
            HW_SCE_p_func101(Param_p32f_func101_003);
        }

        WR1_PROG(REG_104H, 0x00000164U);
        WAIT_STS(REG_104H, 31, 1);
        WR2_ADDR(REG_100H, &InData_DataALen[0]);

        HW_SCE_p_func_sub010(0x81020100U, 0x0000580bU);

        WAIT_STS(REG_74H, 18, 0);
        WR1_PROG(REG_1CH, 0x00001600U);
        WR1_PROG(REG_74H, 0x00000000U);

        WR1_PROG(REG_C4H, 0x00040805U);
        HW_SCE_p_func_sub010(0x81040080U, 0x00002813U);

        WR1_PROG(REG_D0H, 0x00000020U);
        WR1_PROG(REG_C4H, 0x000087b5U);
        WR1_PROG(REG_00H, 0x00002513U);
        WR1_PROG(REG_74H, 0x00000008U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_ECH, 0x00000821U);
        HW_SCE_p_func_sub010(0x80840001U, 0x00008213U);

        WR1_PROG(REG_ECH, 0x00000bffU);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_ECH, 0x3c002beaU);
            WR1_PROG(REG_ECH, 0x12003c3fU);
            WR1_PROG(REG_ECH, 0x00002fe0U);
        }

        WR1_PROG(REG_104H, 0x00000362U);
        WR1_PROG(REG_C4H, 0x00050805U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_DataT[0]);

        WR1_PROG(REG_C4H, 0x00900c45U);
        WR1_PROG(REG_ECH, 0x00000821U);
        HW_SCE_p_func_sub010(0x81840001U, 0x00002813U);
        WR1_PROG(REG_C4H, 0x00000000U);

        static const uint32_t Param_p32f_func100_005[] =
        {
            0x6592194cU, 0xfc26b76bU, 0x7a3e8c6dU, 0x747aab38U,
        };
        HW_SCE_p_func100(Param_p32f_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p32f_func102_002[] =
            {
                0x62f497e1U, 0xa35385d7U, 0xee460e14U, 0x9a5ffc83U,
            };
            HW_SCE_p_func102(Param_p32f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_p32f_func102_003[] =
            {
                0xb938f129U, 0x3612350eU, 0xfe790d4eU, 0x43169997U,
            };
            HW_SCE_p_func102(Param_p32f_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
