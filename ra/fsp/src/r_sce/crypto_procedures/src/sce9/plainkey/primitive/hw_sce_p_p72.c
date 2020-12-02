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

fsp_err_t HW_SCE_Sha224256GenerateMessageDigestSub(const uint32_t *InData_InitVal, const uint32_t *InData_PaddedMsg, const uint32_t MAX_CNT, uint32_t *OutData_MsgDigest)
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
    if (0x0u != (SCE->REG_1BCH & 0x1fu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00007201u;
    SCE->REG_108H = 0x00000000u;
    HW_SCE_p_func100(0x89b55281u, 0x097f6146u, 0xd6a77de8u, 0xec3b48deu);
    SCE->REG_7CH = 0x00000011u;
    SCE->REG_104H = 0x00000764u;
    SCE->REG_74H = 0x00000004u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InitVal[0];
    SCE->REG_100H = InData_InitVal[1];
    SCE->REG_100H = InData_InitVal[2];
    SCE->REG_100H = InData_InitVal[3];
    SCE->REG_100H = InData_InitVal[4];
    SCE->REG_100H = InData_InitVal[5];
    SCE->REG_100H = InData_InitVal[6];
    SCE->REG_100H = InData_InitVal[7];
    SCE->REG_104H = 0x000000b4u;
    SCE->REG_74H = 0x08000002u;
    for (iLoop = 0; iLoop < MAX_CNT ; iLoop = iLoop + 16)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 0];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 1];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 2];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 3];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 4];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 5];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 6];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 7];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 8];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 9];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 10];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 11];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 12];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 13];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 14];
        SCE->REG_100H = InData_PaddedMsg[0+iLoop + 15];
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_74H = 0x00000000u;
    SCE->REG_104H = 0x00000000u;
    SCE->REG_1CH = 0x00001600u;
    SCE->REG_74H = 0x00000008u;
    SCE->REG_04H = 0x00000523u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_MsgDigest[0] = SCE->REG_100H;
    OutData_MsgDigest[1] = SCE->REG_100H;
    OutData_MsgDigest[2] = SCE->REG_100H;
    OutData_MsgDigest[3] = SCE->REG_100H;
    OutData_MsgDigest[4] = SCE->REG_100H;
    OutData_MsgDigest[5] = SCE->REG_100H;
    OutData_MsgDigest[6] = SCE->REG_100H;
    OutData_MsgDigest[7] = SCE->REG_100H;
    HW_SCE_p_func102(0x482a4372u, 0x21f251ebu, 0x29dc06a6u, 0x84167a56u);
    SCE->REG_1BCH = 0x00000040u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p72.prc
***********************************************************************************************************************/
