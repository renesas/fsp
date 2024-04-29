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
    HW_SCE_func001(0x85f1f743U, 0x9d0167c7U, 0xf01a6eb3U, 0xa34dd05aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x416db2deU, 0x8d5e184cU, 0xbee699caU, 0x2a7ddeadU);
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
            HW_SCE_func002(0xfaa6589dU, 0xd8ccc330U, 0x25cd199fU, 0x326492e1U);
        }
        else
        {
            HW_SCE_func002(0x898f1535U, 0x537f84c2U, 0xd85382b9U, 0x411ae863U);
        }
        HW_SCE_func003(0x2b77689dU, 0x996540ebU, 0x0bc29f41U, 0xfa8e373dU);
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
        SCE->REG_A4H = 0x0000088cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            SCE->REG_A4H = 0x00400885U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0xd3436cecU, 0x641fac01U, 0x2465213fU, 0x47686bd4U);
        }
        else
        {
            SCE->REG_A4H = 0x00500885U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0x87b567d9U, 0x7812f09bU, 0xf1a07779U, 0x05440fe3U);
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
            HW_SCE_func001(0x5f2d6047U, 0x4a2eb549U, 0xf274c14eU, 0x60ec98caU);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00000c9dU;
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
            HW_SCE_func003(0xdc02c966U, 0x9c8070e5U, 0x63d21f46U, 0x18f82684U);
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
            HW_SCE_func001(0x46290762U, 0xfdd11c85U, 0x1ac1e40bU, 0x860fe3acU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func003(0x66b8ede0U, 0x0ec5e9dcU, 0x9836cab3U, 0xc9d891e3U);
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
                SCE->REG_A4H = 0x00000c9dU;
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
                HW_SCE_func001(0x4ac5bc17U, 0xe24b751cU, 0x2b5ed4fbU, 0xa226455aU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_func003(0x8f229174U, 0x15a111cbU, 0xdbf9222fU, 0xf3c1e792U);
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
                    HW_SCE_func003(0x485ab686U, 0x0e200f29U, 0x22c4e46cU, 0xdf45c32bU);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p52.prc
***********************************************************************************************************************/
