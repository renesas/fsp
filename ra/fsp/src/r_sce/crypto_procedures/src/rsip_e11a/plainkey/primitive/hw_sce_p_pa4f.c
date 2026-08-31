/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010060U);
    WR1_PROG(REG_2CH, InData_MACLength[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub006(0x38008860U, 0x00000000U, 0x00260000U);

    HW_SCE_p_func_sub001(0x0000b4a0U, 0x00000010U, 0x342028a3U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    static const uint32_t Param_pa4f_func100_001[] =
    {
        0x45505b8aU, 0x095fa7feU, 0xfb2df64eU, 0x58d77a4fU,
    };
    HW_SCE_p_func100(Param_pa4f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pa4f_func102_001[] =
        {
            0xf76bcac6U, 0xb5267e65U, 0xf558eee4U, 0xa0daa9b4U,
        };
        HW_SCE_p_func102(Param_pa4f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_TextLen[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub001(0x00008c00U, 0x0000000fU, 0x38008800U);
        HW_SCE_p_func_sub009(0x00000000U, 0x00A60000U);

        static const uint32_t Param_pa4f_func100_002[] =
        {
            0x6669f684U, 0xe31f543fU, 0x3d152436U, 0xf7140f01U,
        };
        HW_SCE_p_func100(Param_pa4f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub002(0x03410011U);

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_94H, 0x000008a5U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
            }

            static const uint32_t Param_pa4f_func100_003[] =
            {
                0x640a1651U, 0x489a8108U, 0x25756dd4U, 0xa3bb8413U,
            };
            HW_SCE_p_func100(Param_pa4f_func100_003);
            WR1_PROG(REG_94H, 0x00000821U);
            HW_SCE_p_func_sub012(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x0e108405U);
            WR1_PROG(REG_9CH, 0x81840001U);
            HW_SCE_p_func_sub002(0x00490011U);

            static const uint32_t Param_pa4f_func101_001[] =
            {
                0xfd71c325U, 0xcb0da219U, 0x0ed317fdU, 0x2c133a20U,
            };
            HW_SCE_p_func101(Param_pa4f_func101_001);
        }
        else
        {
            static const uint32_t Param_pa4f_func101_002[] =
            {
                0x17123262U, 0x661ad0dbU, 0x26176a94U, 0xa2c446bdU,
            };
            HW_SCE_p_func101(Param_pa4f_func101_002);
        }

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07208d05U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        HW_SCE_p_func_sub002(0x03410011U);

        WR1_PROG(REG_94H, 0x000008a5U);

        WR1_PROG(REG_94H, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            HW_SCE_p_func_sub001(0x3c0028a3U, 0x12003c25U, 0x00002ca0U);
        }

        HW_SCE_p_func_sub008(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_2CH, &InData_MAC[0]);

        HW_SCE_p_func_sub016(0x9c100005U, 0x00000821U, 0x81840001U);
        HW_SCE_p_func_sub002(0x00490011U);
        WR1_PROG(REG_D0H, 0x00000000U);

        static const uint32_t Param_pa4f_func100_004[] =
        {
            0x0cfb5661U, 0xc09f7c3fU, 0xc387dd63U, 0x0261605fU,
        };
        HW_SCE_p_func100(Param_pa4f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pa4f_func102_002[] =
            {
                0x6aecd973U, 0x00aa3b0eU, 0x8b2f9e4bU, 0x3b6345a9U,
            };
            HW_SCE_p_func102(Param_pa4f_func102_002);

            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_pa4f_func102_003[] =
            {
                0xf85aef4aU, 0x8a27b2cfU, 0xd8b459e9U, 0xd5828ea1U,
            };
            HW_SCE_p_func102(Param_pa4f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
