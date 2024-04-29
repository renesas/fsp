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

fsp_err_t HW_SCE_Aes128CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT, uint32_t *InData_DataTLen, uint32_t *OutData_DataT)
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
    HW_SCE_p_func100(0xc5088878U, 0xd1dec1b4U, 0x55d5ce23U, 0x4e2fd2c8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x604c1827U, 0x7d1c29c0U, 0x087e5414U, 0xb61b49daU);
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
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00400a84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func101(0x1f5670b0U, 0x5a29b28bU, 0x9e079501U, 0xcf4fd055U);
        }
        else
        {
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00500a84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func101(0x9d3e98d0U, 0x303cb037U, 0x8cfbaeb2U, 0x1e5a5fc3U);
        }
        SCE->REG_A4H = 0x00040c05U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            HW_SCE_p_func100(0x522fdcccU, 0xd5217facU, 0x768fef5cU, 0x5d257f66U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00000e95U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_DataT[0] = SCE->REG_100H;
            OutData_DataT[1] = SCE->REG_100H;
            OutData_DataT[2] = SCE->REG_100H;
            OutData_DataT[3] = SCE->REG_100H;
            HW_SCE_p_func102(0x8d120335U, 0xa8b323f8U, 0x23f1a63aU, 0x82b60252U);
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
            SCE->REG_E0H = 0x80010040U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataTLen[0];
            SCE->REG_ECH = 0x3420a840U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x0000b460U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_ECH = 0x34202862U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xa34170f3U, 0x2ffafb72U, 0x6bd00efeU, 0x312ba181U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x594cfb93U, 0x8784511cU, 0xd6dc51f6U, 0x4d7b6d9cU);
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
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00000e95U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[0];
                SCE->REG_100H = InData_Text[1];
                SCE->REG_100H = InData_Text[2];
                SCE->REG_100H = InData_Text[3];
                SCE->REG_ECH = 0x00000821U;
                SCE->REG_E0H = 0x80840001U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000034e2U;
                SCE->REG_ECH = 0x000568e7U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_ECH = 0x00003827U;
                SCE->REG_ECH = 0x0000b4c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_ECH = 0x00003402U;
                SCE->REG_ECH = 0x00008c00U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x000028c0U;
                SCE->REG_ECH = 0x00008cc0U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x00004406U;
                SCE->REG_ECH = 0x00007421U;
                SCE->REG_ECH = 0x00007821U;
                SCE->REG_ECH = 0x00003c27U;
                SCE->REG_ECH = 0x000034c2U;
                SCE->REG_ECH = 0x0000a4c0U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x000568c6U;
                SCE->REG_ECH = 0x000034e6U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_ECH = 0x00000821U;
                for (iLoop = 0; iLoop < 4; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3420a8e0U;
                    SCE->REG_ECH = 0x0000000dU;
                    SCE->REG_ECH = 0x10003c27U;
                    SCE->REG_ECH = 0x1000a4e0U;
                    SCE->REG_ECH = 0x00000004U;
                }
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_E0H = 0x81840001U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00900c05U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_DataT[0];
                SCE->REG_100H = InData_DataT[1];
                SCE->REG_100H = InData_DataT[2];
                SCE->REG_100H = InData_DataT[3];
                HW_SCE_p_func100(0x4da42f56U, 0x353cb5ffU, 0xf9d3580bU, 0xbb884079U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x7ac07674U, 0xa2f236faU, 0xecf4dd04U, 0xe11bf76cU);
                    SCE->REG_1BCH = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
                }
                else
                {
                    HW_SCE_p_func102(0x3f36b8c5U, 0x7738b9a0U, 0x1ac6ed97U, 0xb9631f3aU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p41f.prc
***********************************************************************************************************************/
