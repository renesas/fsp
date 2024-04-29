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

fsp_err_t HW_SCE_Sha224256GenerateMessageDigestSub(const uint32_t *InData_SHAInitVal, const uint32_t *InData_PaddedMsg, const uint32_t MAX_CNT, uint32_t *OutData_MsgDigest)
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
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00007201U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0x889eb33fU, 0xbc8a6fe3U, 0x3b466098U, 0xd3313024U);
    SCE->REG_7CH = 0x00000011U;
    SCE->REG_104H = 0x00000764U;
    SCE->REG_74H = 0x00000004U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_SHAInitVal[0];
    SCE->REG_100H = InData_SHAInitVal[1];
    SCE->REG_100H = InData_SHAInitVal[2];
    SCE->REG_100H = InData_SHAInitVal[3];
    SCE->REG_100H = InData_SHAInitVal[4];
    SCE->REG_100H = InData_SHAInitVal[5];
    SCE->REG_100H = InData_SHAInitVal[6];
    SCE->REG_100H = InData_SHAInitVal[7];
    SCE->REG_104H = 0x000000b4U;
    SCE->REG_74H = 0x08000002U;
    for (iLoop = 0; iLoop < MAX_CNT ; iLoop = iLoop + 16)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
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
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_74H = 0x00000000U;
    SCE->REG_104H = 0x00000000U;
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_04H = 0x00000522U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
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
    HW_SCE_p_func102(0xcf182aceU, 0xfb59fc68U, 0xb40a7052U, 0x8744ab57U);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p72.prc
***********************************************************************************************************************/
