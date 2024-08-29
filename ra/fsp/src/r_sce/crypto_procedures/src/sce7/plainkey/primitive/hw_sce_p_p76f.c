/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce_if.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

fsp_err_t HW_SCE_Sha256HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length, uint32_t *OutData_MAC)
{
    uint32_t iLoop    = 0U;
    uint32_t iLoop1   = 0U;
    uint32_t iLoop2   = 0U;
    int32_t  jLoop    = 0U;
    uint32_t kLoop    = 0U;
    uint32_t oLoop    = 0U;
    uint32_t oLoop1   = 0U;
    uint32_t oLoop2   = 0U;
    uint32_t dummy    = 0U;
    uint32_t KEY_ADR  = 0U;
    uint32_t OFS_ADR  = 0U;
    uint32_t MAX_CNT2 = 0U;
    (void)iLoop;
    (void)iLoop1;
    (void)iLoop2;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)oLoop1;
    (void)oLoop2;
    (void)dummy;
    (void)KEY_ADR;
    (void)OFS_ADR;
    (void)MAX_CNT2;
    SCE->REG_74H = 0x00000000U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_00H = 0x00003523U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_7CH = 0x00000011U;
    SCE->REG_104H = 0x00000754U;
    SCE->REG_74H = 0x00000004U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x6a09e667U);
    SCE->REG_100H = change_endian_long(0xbb67ae85U);
    SCE->REG_100H = change_endian_long(0x3c6ef372U);
    SCE->REG_100H = change_endian_long(0xa54ff53aU);
    SCE->REG_100H = change_endian_long(0x510e527fU);
    SCE->REG_100H = change_endian_long(0x9b05688cU);
    SCE->REG_100H = change_endian_long(0x1f83d9abU);
    SCE->REG_100H = change_endian_long(0x5be0cd19U);
    SCE->REG_74H = 0x00000002U;
    HW_SCE_p_func002();
    SCE->REG_00H = 0x00005323U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000054U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x80000000U);
    SCE->REG_F8H = 0x00000040U;
    SCE->REG_104H = 0x00000154U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000300U);
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_74H = 0x00000000U;
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_104H = 0x00000068U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x38000c00U;
    SCE->REG_ECH = 0x1000b780U;
    SCE->REG_ECH = 0x00200000U;
    SCE->REG_ECH = 0x2000b780U;
    SCE->REG_ECH = 0x00100000U;
    SCE->REG_ECH = 0x38000f9dU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x488aa8c9U, 0xf9556af4U, 0x36466f82U, 0xf38045adU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xd6190916U, 0x1c43ab40U, 0x1f3fe3a8U, 0x3c6ebae6U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x45b9be38U, 0xec63f892U, 0x6696e593U, 0xbd21f6ceU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func100(0x5dd6d6fdU, 0xa7e67acaU, 0x13a59fe9U, 0x944098deU);
            SCE->REG_74H = 0x00000008U;
            SCE->REG_04H = 0x00000522U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MAC[0] = SCE->REG_100H;
            OutData_MAC[1] = SCE->REG_100H;
            OutData_MAC[2] = SCE->REG_100H;
            OutData_MAC[3] = SCE->REG_100H;
            OutData_MAC[4] = SCE->REG_100H;
            OutData_MAC[5] = SCE->REG_100H;
            OutData_MAC[6] = SCE->REG_100H;
            OutData_MAC[7] = SCE->REG_100H;
            HW_SCE_p_func102(0xbb040658U, 0x91426810U, 0x387cb391U, 0xd996200eU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
        else
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_length[0];
            SCE->REG_ECH = 0x3420a820U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3420a820U;
            SCE->REG_ECH = 0x00000021U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_p_func100(0xc8246913U, 0xfce55d24U, 0x88b728d6U, 0xcd562ca3U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x34a18025U, 0x9cb17c85U, 0xe4073cc8U, 0x7c52435cU);
                SCE->REG_1BCH = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_E0H = 0x8088001fU;
                SCE->REG_00H = 0x00008523U;
                SCE->REG_74H = 0x00000008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x00000800U;
                for (iLoop = 0; iLoop < 32; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3c002be1U;
                    SCE->REG_ECH = 0x12003c1fU;
                    SCE->REG_ECH = 0x00002fe0U;
                }
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x00050805U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000761U;
                SCE->REG_A4H = 0x00900c05U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[0];
                SCE->REG_100H = InData_MAC[1];
                SCE->REG_100H = InData_MAC[2];
                SCE->REG_100H = InData_MAC[3];
                SCE->REG_A4H = 0x00900c45U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[4];
                SCE->REG_100H = InData_MAC[5];
                SCE->REG_100H = InData_MAC[6];
                SCE->REG_100H = InData_MAC[7];
                HW_SCE_p_func100(0x4c658300U, 0xe6e2e11cU, 0x14b0e629U, 0xdcfb3d75U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x37a847dfU, 0x06bec80cU, 0x867620f7U, 0x8f0a3c5cU);
                    SCE->REG_1BCH = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func102(0x61036932U, 0x8cf665d4U, 0x60bda192U, 0x99161c7eU);
                    SCE->REG_1BCH = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_SUCCESS;
                }
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p76f.prc
***********************************************************************************************************************/
