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

fsp_err_t HW_SCE_Aes256CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT, uint32_t *InData_DataTLen, uint32_t *OutData_DataT)
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
    HW_SCE_func001(0xa6f98bbaU, 0xa970edabU, 0x1f533fbdU, 0xb8a09834U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x01b67f98U, 0xa3fb7fe3U, 0xf628f47bU, 0xd2657899U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_00H = 0x00000113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0xcdcad000U, 0xabc39a21U, 0xd55a0d65U, 0x32ddcdccU);
        }
        else
        {
            HW_SCE_func002(0x16f971e4U, 0xb309e92dU, 0x2ebd6e4bU, 0xbd8d8005U);
        }
        HW_SCE_func003(0x57fae2dfU, 0x68afc29dU, 0xb2b54c36U, 0x466b977bU);
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
        SCE->REG_104H = 0x00000051U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000888cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00408885U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0x4ca5a4cfU, 0x0212ce29U, 0xdbe9a869U, 0xa9674776U);
        }
        else
        {
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00508885U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0xa491fea2U, 0x83857da3U, 0x6754c2b5U, 0xdfc9f322U);
        }
        SCE->REG_A4H = 0x00040605U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            HW_SCE_func001(0x3159f8d9U, 0x47045150U, 0xb59ffaa8U, 0xcc13badeU);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00048c9dU;
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
            HW_SCE_func003(0xf17e6870U, 0x1275c6edU, 0xd6710bbaU, 0xec0d58abU);
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
            SCE->REG_1D0H = 0x00000000U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataTLen[0];
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x3420a840U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x0000b460U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x34202862U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_func001(0x2855c8a0U, 0xd0dd89ebU, 0x50f42494U, 0x8f1a59e4U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func003(0x58ed489eU, 0x0b5080aaU, 0xeed388c1U, 0x65e9d116U);
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
                SCE->REG_B0H = 0x40000000U;
                SCE->REG_A4H = 0x00008c9dU;
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
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x80840001U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000034e2U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000568e7U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003827U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000b4c0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003402U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00008c00U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000028c0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00008cc0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00004406U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00007421U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00007821U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003c27U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000034c2U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000a4c0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000568c6U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000034e6U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000821U;
                SCE->REG_1D0H = 0x00000000U;
                for (iLoop = 0; iLoop < 4; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3420a8e0U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x0000000dU;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x10003c27U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x1000a4e0U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_1D0H = 0x00000000U;
                }
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_E0H = 0x81840001U;
                SCE->REG_1D0H = 0x00000000U;
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
                HW_SCE_func001(0x3cceb3f7U, 0xb8705e83U, 0xb76e8f69U, 0x1d4e9fdcU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_func003(0xcbf2af21U, 0x1f4f967fU, 0xa0337d6bU, 0x034fa02cU);
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
                    HW_SCE_func003(0xf6456957U, 0xafc77358U, 0xc6839628U, 0xb22ae4d0U);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p55.prc
***********************************************************************************************************************/
