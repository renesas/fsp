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

fsp_err_t HW_SCE_GenerateAes128XtsKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00008701U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100e0U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x38000ce7U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func001(0xd7f83c6aU, 0x40157d24U, 0x75b98bfcU, 0xd4e29e1dU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x38008c00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0xfffffff0U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func001(0x8f4899b2U, 0x42ce94beU, 0x1c929b57U, 0x65a9f00aU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func003(0x136515a8U, 0xcbfe3c1eU, 0xb5c04a26U, 0xed3d0d06U);
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
            HW_SCE_func001(0xd31bc27eU, 0xfa51eb81U, 0x3afc1603U, 0x9dba13b3U);
            OFS_ADR = InData_SharedKeyIndex[0]*8;
            SCE->REG_A4H = 0x400c3a0cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x129e32e8U);
            SCE->REG_A4H = 0x400c0a0cU;
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00001807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x42fa063dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_FLASH[OFS_ADR + 0];
            SCE->REG_100H = S_FLASH[OFS_ADR + 1];
            SCE->REG_100H = S_FLASH[OFS_ADR + 2];
            SCE->REG_100H = S_FLASH[OFS_ADR + 3];
            HW_SCE_func001(0xbb07333bU, 0x1ced036fU, 0x738c8fdbU, 0xd93c2a27U);
            SCE->REG_A4H = 0x400006bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 0];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 1];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 2];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 3];
            SCE->REG_A4H = 0x00800c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x0008680dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SessionKey[0];
            SCE->REG_100H = InData_SessionKey[1];
            SCE->REG_100H = InData_SessionKey[2];
            SCE->REG_100H = InData_SessionKey[3];
            HW_SCE_func001(0x6ca1d45dU, 0x8d854a62U, 0x4eab7c9bU, 0xea1f2c86U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x0009680dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SessionKey[4];
            SCE->REG_100H = InData_SessionKey[5];
            SCE->REG_100H = InData_SessionKey[6];
            SCE->REG_100H = InData_SessionKey[7];
            HW_SCE_func001(0xa357dd65U, 0x247297dfU, 0x314188b7U, 0x27b9b7ebU);
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
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00050804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000251U;
            SCE->REG_A4H = 0x0020363cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x002036bcU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x002036bcU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x00060805U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000151U;
            SCE->REG_A4H = 0x0021340cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x000b0805U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func001(0xb8ae23cfU, 0xb652a9c5U, 0xfa69a92bU, 0xbfb7c58eU);
            SCE->REG_E0H = 0x80040000U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x600c3a0dU;
            SCE->REG_E0H = 0x81040000U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00001813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x400c0a0cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x2d8daf39U);
            SCE->REG_104H = 0x00000761U;
            SCE->REG_B0H = 0x00000100U;
            SCE->REG_A4H = 0x00d0c9afU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[0];
            SCE->REG_100H = InData_InstData[1];
            SCE->REG_100H = InData_InstData[2];
            SCE->REG_100H = InData_InstData[3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[4];
            SCE->REG_100H = InData_InstData[5];
            SCE->REG_100H = InData_InstData[6];
            SCE->REG_100H = InData_InstData[7];
            SCE->REG_B0H = 0x00000100U;
            SCE->REG_A4H = 0x43e086bfU;
            SCE->REG_00H = 0x00001123U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000122U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[4] = SCE->REG_100H;
            OutData_KeyIndex[5] = SCE->REG_100H;
            OutData_KeyIndex[6] = SCE->REG_100H;
            OutData_KeyIndex[7] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[8] = SCE->REG_100H;
            OutData_KeyIndex[9] = SCE->REG_100H;
            OutData_KeyIndex[10] = SCE->REG_100H;
            OutData_KeyIndex[11] = SCE->REG_100H;
            HW_SCE_func001(0xdef8d302U, 0x0d5ca74bU, 0x5e4af557U, 0x89cf4091U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x410009cdU;
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
            OutData_KeyIndex[12] = SCE->REG_100H;
            OutData_KeyIndex[13] = SCE->REG_100H;
            OutData_KeyIndex[14] = SCE->REG_100H;
            OutData_KeyIndex[15] = SCE->REG_100H;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[8];
            SCE->REG_100H = InData_InstData[9];
            SCE->REG_100H = InData_InstData[10];
            SCE->REG_100H = InData_InstData[11];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func001(0x1731adbfU, 0x54677ba1U, 0xc451786fU, 0xed119a73U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func003(0xc2e82a26U, 0x85101fbdU, 0x82b146b7U, 0x9a652619U);
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
                HW_SCE_func001(0x3e70dfccU, 0x1d388ed8U, 0xc76f09b8U, 0x6740985fU);
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[3] = SCE->REG_100H;
                HW_SCE_func003(0x818b9bafU, 0x29f54d40U, 0x843998f7U, 0x382339d2U);
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
    else
    {
        HW_SCE_func001(0x74745802U, 0x94b5da2eU, 0xd156499bU, 0x7687a57fU);
        SCE->REG_104H = 0x00000251U;
        SCE->REG_A4H = 0x0020363cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x002036bcU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x002036bcU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x00060805U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000151U;
        SCE->REG_A4H = 0x0021340cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x000b0805U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x01000684U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_func001(0xc23cde81U, 0x790a2f24U, 0xcc15c1eeU, 0xc9d475c2U);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00008113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x600c3a0dU;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00001813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x400c0a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x2d8daf39U);
        SCE->REG_104H = 0x00000761U;
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x00008887U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[0];
        SCE->REG_100H = InData_InstData[1];
        SCE->REG_100H = InData_InstData[2];
        SCE->REG_100H = InData_InstData[3];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[4];
        SCE->REG_100H = InData_InstData[5];
        SCE->REG_100H = InData_InstData[6];
        SCE->REG_100H = InData_InstData[7];
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x43e086bfU;
        SCE->REG_00H = 0x00001123U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000122U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[4] = SCE->REG_100H;
        OutData_KeyIndex[5] = SCE->REG_100H;
        OutData_KeyIndex[6] = SCE->REG_100H;
        OutData_KeyIndex[7] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[8] = SCE->REG_100H;
        OutData_KeyIndex[9] = SCE->REG_100H;
        OutData_KeyIndex[10] = SCE->REG_100H;
        OutData_KeyIndex[11] = SCE->REG_100H;
        HW_SCE_func001(0x492cbe9eU, 0x43bd6eeaU, 0xc223afe4U, 0x4404e219U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000684U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x410009cdU;
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
        OutData_KeyIndex[12] = SCE->REG_100H;
        OutData_KeyIndex[13] = SCE->REG_100H;
        OutData_KeyIndex[14] = SCE->REG_100H;
        OutData_KeyIndex[15] = SCE->REG_100H;
        HW_SCE_func001(0xb8808aa8U, 0x5ff991a3U, 0xab71689cU, 0x5af1efd0U);
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_04H = 0x00000612U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[0] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[1] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[2] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[3] = SCE->REG_100H;
        HW_SCE_func003(0x4a88f02eU, 0x3ba00792U, 0x7b0a0c43U, 0xebbadd2fU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic_PlainKey/HW_SCEp_p87.prc
***********************************************************************************************************************/
