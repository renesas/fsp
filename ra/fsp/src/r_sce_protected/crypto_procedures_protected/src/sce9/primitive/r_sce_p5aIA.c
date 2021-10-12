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
#include "r_sce.h"
#include "r_sce_private.h"

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

fsp_err_t R_SCE_EcdhP256QeuOutputSub(uint32_t *InData_Cmd, uint32_t *InData_data, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00005a02U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_C4H = 0x200e1a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000c0U;
    SCE->REG_104H = 0x00001068U;
    SCE->REG_E0H = 0x8091001eU;
    for (iLoop = 0; iLoop < 17; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_data[iLoop + 0];
    }
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000c0U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x38000f5aU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    R_SCE_func100(0x63ef3c96U, 0x8bd4214cU, 0xecd20b25U, 0x9ea5f2f5U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_E0H = 0x8190001eU;
        SCE->REG_00H = 0x00003843U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func101(0x7f6df52dU, 0x8f3e0234U, 0xc9cd1bf9U, 0xc4727d98U);
    }
    else
    {
        SCE->REG_E0H = 0x8191001eU;
        SCE->REG_00H = 0x08000807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x08013803U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0800080fU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func101(0x2573acd4U, 0x299be00dU, 0x10b37e28U, 0x87a8d24dU);
    }
    R_SCE_func100(0xa5d912eaU, 0x44c782a2U, 0xf513e6d0U, 0xa0882fe4U);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008207U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00003540U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000048U);
    R_SCE_func101(0x34956140U, 0x1fe2187aU, 0x29db1464U, 0x3b891a7bU);
    R_SCE_func068();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x01771788U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000048U);
    R_SCE_func101(0x56a9f7cfU, 0xb7993096U, 0xa91cda35U, 0x4bd9fe11U);
    R_SCE_func044();
    R_SCE_func100(0xfcbf927fU, 0xbe320726U, 0x926ce5b1U, 0xb5548303U);
    SCE->REG_00H = 0x00002343U;
    SCE->REG_2CH = 0x00000020U;
    SCE->REG_D0H = 0x40000300U;
    SCE->REG_C4H = 0x02e087b7U;
    SCE->REG_04H = 0x00000242U;
    for (iLoop = 1; iLoop < 17; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    }
    R_SCE_func100(0x21acc534U, 0x4d6a5977U, 0xa402e93cU, 0x34bdbe6dU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000089c5U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    R_SCE_func100(0x642e5b3eU, 0x38c3cf91U, 0xc9eb5311U, 0xd5782200U);
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = SCE->REG_100H;
    R_SCE_func102(0x6b1e07a9U, 0x05f193f9U, 0x5c98f1b7U, 0xd9b346d5U);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p5a_IAR.prc
***********************************************************************************************************************/
