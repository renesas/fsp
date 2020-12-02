/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
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

fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub(uint32_t *InData_Text, uint32_t *InData_DataT, uint32_t *InData_DataALen, uint32_t *InData_TextLen, uint32_t *InData_DataTLen, uint32_t *OutData_Text)
{
    uint32_t iLoop = 0u, iLoop1 = 0u, iLoop2 = 0u, jLoop = 0u, kLoop = 0u, oLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, KEY_ADR = 0u, OFS_ADR = 0u, MAX_CNT2 = 0u;
    uint32_t dummy = 0u;
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
    SCE->REG_104H = 0x00000168u;
    SCE->REG_E0H = 0x80020100u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[0];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[1];
    SCE->REG_ECH = 0x0000b580u;
    SCE->REG_ECH = 0x0000007Fu;
    SCE->REG_ECH = 0x0000b5a0u;
    SCE->REG_ECH = 0xFFFFFF00u;
    SCE->REG_ECH = 0x0c0029a9u;
    SCE->REG_ECH = 0x04a02988u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010140u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_DataTLen[0];
    SCE->REG_ECH = 0x38008940u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_ECH = 0x0000b7e0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_ECH = 0x34202beau;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x7e77cbbau, 0x173242d0u, 0x905c6012u, 0x92a08d85u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xa78e5625u, 0x1c356b17u, 0x3622d00au, 0xc1826f48u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_ECH = 0x00003409u;
        SCE->REG_ECH = 0x00036800u;
        SCE->REG_ECH = 0x08008c00u;
        SCE->REG_ECH = 0x0000000fu;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x96608198u, 0xfb81f3afu, 0x9d675d2cu, 0x0d909e69u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00000885u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_D0H = 0x40000030u;
            SCE->REG_C4H = 0x000087b5u;
            SCE->REG_00H = 0x00007113u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x00000821u;
            SCE->REG_E0H = 0x80840001u;
            SCE->REG_00H = 0x00008213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x00000bffu;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002be0u;
                SCE->REG_ECH = 0x12003c3fu;
                SCE->REG_ECH = 0x00002fe0u;
            }
            HW_SCE_p_func100(0x8815b4d1u, 0x270bd3bdu, 0x2e31e5a5u, 0x6453b313u);
            SCE->REG_C4H = 0x00000885u;
            SCE->REG_ECH = 0x00000821u;
            SCE->REG_E0H = 0x81840001u;
            SCE->REG_00H = 0x00002813u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_04H = 0x00000213u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[0] = SCE->REG_100H;
            OutData_Text[1] = SCE->REG_100H;
            OutData_Text[2] = SCE->REG_100H;
            OutData_Text[3] = SCE->REG_100H;
            HW_SCE_p_func101(0xcaa030b7u, 0x85d7cce6u, 0xabf927c9u, 0x00d6ab94u);
        }
        SCE->REG_104H = 0x00000164u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataALen[0];
        SCE->REG_100H = InData_DataALen[1];
        SCE->REG_E0H = 0x81020100u;
        SCE->REG_00H = 0x0000580bu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_74H_b.B18)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001600u;
        SCE->REG_74H = 0x00000000u;
        SCE->REG_C4H = 0x00040805u;
        SCE->REG_E0H = 0x81040080u;
        SCE->REG_00H = 0x00002813u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_D0H = 0x40000030u;
        SCE->REG_C4H = 0x000087b5u;
        SCE->REG_00H = 0x00002513u;
        SCE->REG_74H = 0x00000008u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x00000821u;
        SCE->REG_E0H = 0x80840001u;
        SCE->REG_00H = 0x00008213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x00000bffu;
        for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
        {
            SCE->REG_ECH = 0x3c002beau;
            SCE->REG_ECH = 0x12003c3fu;
            SCE->REG_ECH = 0x00002fe0u;
        }
        SCE->REG_104H = 0x00000362u;
        SCE->REG_C4H = 0x00050805u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataT[0];
        SCE->REG_100H = InData_DataT[1];
        SCE->REG_100H = InData_DataT[2];
        SCE->REG_100H = InData_DataT[3];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_ECH = 0x00000821u;
        SCE->REG_E0H = 0x81840001u;
        SCE->REG_00H = 0x00002813u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_C4H = 0x00000000u;
        HW_SCE_p_func100(0xbcf86870u, 0xbfb89ad4u, 0xba4c0d39u, 0x2d73a273u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xbec06d50u, 0xd0d0f3ecu, 0xd61c911du, 0x14d3fa2cu);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            HW_SCE_p_func102(0xaece36fcu, 0x1401eb3eu, 0xd2b724d6u, 0x943cd55eu);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p85f.prc
***********************************************************************************************************************/
