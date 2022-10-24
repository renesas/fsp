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

fsp_err_t R_SCE_UpdateOemKeyIndexSub(uint32_t *InData_LC, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00006f01U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func048(InData_LC);
    HW_SCE_func049(InData_Cmd);
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    SCE->REG_ECH = 0x3420a880U;
    SCE->REG_ECH = 0x00000005U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x3420a880U;
    SCE->REG_ECH = 0x0000000aU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    SCE->REG_ECH = 0x38208880U;
    SCE->REG_ECH = 0x00000006U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func100(0x0460e680U, 0xe8f7232bU, 0xb3f3d398U, 0x29d20aa0U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func102(0x4f9f4c0aU, 0xa3d2bed6U, 0x429429afU, 0x80696c37U);
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
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x800100a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_INST2[0];
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800100c0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000006fU);
        HW_SCE_func101(0x16c877faU, 0xbce92e25U, 0x5a648fb7U, 0xb043be64U);
        HW_SCE_func043();
        HW_SCE_func100(0xcdee38d0U, 0x71d045d5U, 0xcd5224d2U, 0xa3fee8a4U);
        SCE->REG_ECH = 0x0000b4a0U;
        SCE->REG_ECH = 0x00000100U;
        HW_SCE_func044();
        HW_SCE_func100(0xdfb335c4U, 0x73150f15U, 0x267a0a25U, 0x42466b15U);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x02f8263dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_INST2[0+1 + 0];
        SCE->REG_100H = S_INST2[0+1 + 1];
        SCE->REG_100H = S_INST2[0+1 + 2];
        SCE->REG_100H = S_INST2[0+1 + 3];
        HW_SCE_func100(0x0a1cd05bU, 0xc5fae2f1U, 0x6af0a97eU, 0x476e6724U);
        SCE->REG_104H = 0x00000761U;
        SCE->REG_A4H = 0x00f9263dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_INST2[0+5 + 0];
        SCE->REG_100H = S_INST2[0+5 + 1];
        SCE->REG_100H = S_INST2[0+5 + 2];
        SCE->REG_100H = S_INST2[0+5 + 3];
        SCE->REG_A4H = 0x000026bdU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_INST2[0+9 + 0];
        SCE->REG_100H = S_INST2[0+9 + 1];
        SCE->REG_100H = S_INST2[0+9 + 2];
        SCE->REG_100H = S_INST2[0+9 + 3];
        SCE->REG_A4H = 0x00800c45U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_func100(0x051975c3U, 0xeafa34acU, 0x87caf25cU, 0x17b4beb4U);
        HW_SCE_func103();
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_00H = 0x00008107U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000010fU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034a0U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800100c0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        HW_SCE_func101(0x13cc0e6cU, 0x0da897a3U, 0xce0d0c69U, 0x65038d18U);
        HW_SCE_func043();
        SCE->REG_ECH = 0x00003405U;
        HW_SCE_func100(0x4a96a010U, 0x590d2b55U, 0x3825b186U, 0x7e954c3dU);
        SCE->REG_ECH = 0x000034a4U;
        HW_SCE_func044();
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00040805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        SCE->REG_100H = InData_IV[1];
        SCE->REG_100H = InData_IV[2];
        SCE->REG_100H = InData_IV[3];
        SCE->REG_104H = 0x00000251U;
        SCE->REG_A4H = 0x00050804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x00060804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x00070804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
        {
            HW_SCE_func100(0x44abd2f8U, 0x6a576998U, 0xbc0e21a5U, 0x9a7db8f6U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[iLoop + 0];
            SCE->REG_100H = InData_InstData[iLoop + 1];
            SCE->REG_100H = InData_InstData[iLoop + 2];
            SCE->REG_100H = InData_InstData[iLoop + 3];
            SCE->REG_A4H = 0x01e026bdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
            HW_SCE_func101(0xa3288270U, 0x0018e657U, 0x4b776fcbU, 0xa2799616U);
        }
        HW_SCE_func100(0xfbfe3dc5U, 0xdecbb149U, 0xad0953aaU, 0x951d12f2U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000684U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x010029cdU;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000112U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x000049adU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[iLoop + 0];
        SCE->REG_100H = InData_InstData[iLoop + 1];
        SCE->REG_100H = InData_InstData[iLoop + 2];
        SCE->REG_100H = InData_InstData[iLoop + 3];
        SCE->REG_A4H = 0x00900c45U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_func100(0x5f4b871bU, 0x806163fbU, 0xcb2fa1bfU, 0x64a824a9U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func102(0xe50db69eU, 0xb80ec990U, 0x4ed72811U, 0x991d47a3U);
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
            HW_SCE_func100(0x768a2c4bU, 0x54984cdbU, 0xe343573fU, 0x0b766b17U);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[0] = SCE->REG_100H;
            HW_SCE_func102(0x7b3b1eb5U, 0x1f822264U, 0x78d7d42dU, 0xf130b544U);
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

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p6f_r1.prc
***********************************************************************************************************************/
