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

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header, uint32_t Header_Len)
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
    SCE->REG_84H = 0x00007301U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func001(0x4e150ef1U, 0x31b1008bU, 0x19b488daU, 0x42810d0aU);
    SCE->REG_A4H = 0x600c3a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_100H = InData_KeyIndex[1];
    SCE->REG_100H = InData_KeyIndex[2];
    SCE->REG_100H = InData_KeyIndex[3];
    SCE->REG_A4H = 0x400c0a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0xef138998U);
    SCE->REG_A4H = 0x42f8063dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[4];
    SCE->REG_100H = InData_KeyIndex[5];
    SCE->REG_100H = InData_KeyIndex[6];
    SCE->REG_100H = InData_KeyIndex[7];
    SCE->REG_A4H = 0x400006bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[8];
    SCE->REG_100H = InData_KeyIndex[9];
    SCE->REG_100H = InData_KeyIndex[10];
    SCE->REG_100H = InData_KeyIndex[11];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_func001(0x60b7262fU, 0xd87e9a85U, 0x186ff7acU, 0xfdc7c8b8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func003(0x98793f82U, 0x9ac6c5c5U, 0x71d4d29cU, 0x19c0807eU);
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
        SCE->REG_A4H = 0x0000063cU;
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
        SCE->REG_A4H = 0x00f00806U;
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
        HW_SCE_func205();
        HW_SCE_func001(0x794cebc2U, 0x27a53180U, 0xd459ce03U, 0xaef0d86bU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0xee6ff299U, 0xd58cdec1U, 0xbadd2f4fU, 0xb7d39176U);
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
                HW_SCE_func002(0xe11df6acU, 0x3a2600d2U, 0x96bab086U, 0xd4ccc931U);
            }
            else
            {
                HW_SCE_func002(0x902118a3U, 0x2d470afaU, 0x8d517b92U, 0xf15d228fU);
            }
            HW_SCE_func003(0xd534ab9dU, 0x60f0a05dU, 0x1a2b787aU, 0xc8fe0ccfU);
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

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p73.prc
***********************************************************************************************************************/
