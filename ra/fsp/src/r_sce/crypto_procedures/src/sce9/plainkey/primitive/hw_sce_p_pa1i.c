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

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header, uint32_t Header_Len)
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
    uint32_t InData_KeyType[1] = {0};
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000a102U;
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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xdb03a5dfU, 0xa52570b2U, 0x6601bbb3U, 0x3ea61da6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x917e3e22U, 0xf04198b0U, 0xb4f8df53U, 0xe25d0b05U);
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
        HW_SCE_p_func100(0x37c069d3U, 0x926145aaU, 0x1c615a04U, 0xb1975c8dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000a1U);
            HW_SCE_p_func101(0x52cb1369U, 0x342bfdbfU, 0x7ede6f6bU, 0xb7ee7226U);
            HW_SCE_p_func043();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x00000007U;
            HW_SCE_p_func101(0xde111be7U, 0xddd15cc3U, 0x1e0947b7U, 0x20c1a651U);
        }
        else
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010140U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000a1U);
            HW_SCE_p_func101(0xd206830aU, 0xb87a4d75U, 0x6583f40eU, 0x6464e8b7U);
            HW_SCE_p_func068();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x01d04999U;
            HW_SCE_p_func101(0x27595344U, 0x35dc3700U, 0x9f30fa1fU, 0xc3288152U);
        }
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000a1U);
        HW_SCE_p_func101(0x62e27dadU, 0x313b0d1aU, 0x961892e6U, 0x97c437c3U);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x05255eafU, 0xbb8ee12cU, 0x0b5c438aU, 0x03694643U);
        SCE->REG_104H = 0x00000762U;
        SCE->REG_D0H = 0x40000100U;
        SCE->REG_C4H = 0x02f087b7U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_100H = InData_KeyIndex[4];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_A4H = 0x00080805U;
        SCE->REG_00H = 0x00001213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x0e42e528U, 0x697d2e85U, 0xb3709985U, 0xe75d31c8U);
        SCE->REG_A4H = 0x00090805U;
        SCE->REG_00H = 0x00001213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000362U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000087b5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_100H = InData_KeyIndex[12];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x6752277aU, 0xc69f620fU, 0x46219ec6U, 0xb6e408b1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x0257d3afU, 0x13038f5aU, 0x02a7c01bU, 0xd61eac1aU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00040885U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            SCE->REG_A4H = 0x00060805U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00000734U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00050804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x000000b1U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00058e56U;
            for (iLoop = 0; iLoop < Header_Len; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Header[iLoop + 0];
                SCE->REG_100H = InData_Header[iLoop + 1];
                SCE->REG_100H = InData_Header[iLoop + 2];
                SCE->REG_100H = InData_Header[iLoop + 3];
            }
            HW_SCE_p_func205();//DisableINTEGRATE_WRRDYBinthisfunction.
            HW_SCE_p_func100(0xb9e8fcf6U, 0xb4ea8932U, 0x1b72f566U, 0xff824869U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xb45659f9U, 0xbb4e896dU, 0x566c184dU, 0xb6d59c0eU);
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
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCEp_pa1i_r2.prc
***********************************************************************************************************************/
