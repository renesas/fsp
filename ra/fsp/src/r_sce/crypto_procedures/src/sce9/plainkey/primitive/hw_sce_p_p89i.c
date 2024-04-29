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

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV)
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
    SCE->REG_84H = 0x00008901U;
    SCE->REG_108H = 0x00000000U;
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
    SCE->REG_100H = change_endian_long(0x00000089U);
    HW_SCE_p_func101(0xd2d17f17U, 0x9ed64bfbU, 0xebed71f8U, 0xd0f1de28U);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000006U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000089U);
    HW_SCE_p_func101(0x3a350608U, 0xf1283fdeU, 0xb7c2416eU, 0x378561d5U);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x112550f9U, 0x2ef76aeaU, 0x48f9d518U, 0xe2095dc6U);
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
    HW_SCE_p_func100(0x7106f61eU, 0x705629cfU, 0x82ae645fU, 0xc89bfb94U);
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
    HW_SCE_p_func100(0xca5b4afcU, 0xbae7dfd1U, 0x9e7fd8b3U, 0x09358784U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xc78ea399U, 0xa678759fU, 0x300215feU, 0xf2ce9a45U);
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
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_104H = 0x00000068U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Cmd[0];
        SCE->REG_ECH = 0x3000a800U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x00010020U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x00000080U;
        HW_SCE_p_func100(0xe11f3cd4U, 0x4287c0d2U, 0xe2b6bf61U, 0x6afc0ad0U);
        SCE->REG_ECH = 0x00007c00U;
        SCE->REG_1CH = 0x00600000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
        {
            HW_SCE_p_func101(0x2c0be082U, 0x51950bd2U, 0x5501e81dU, 0x37634e53U);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            HW_SCE_p_func101(0xf7c9cd50U, 0xc14979ebU, 0xe09af696U, 0x823702e1U);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
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
            HW_SCE_p_func101(0xb5faa29fU, 0xb8d5f49fU, 0xbc20a648U, 0x49f17503U);
        }
        else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
        {
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
            HW_SCE_p_func101(0x3a1757deU, 0x5d8bf593U, 0xa8dd7442U, 0x5d4eae78U);
        }
        else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
        {
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
            HW_SCE_p_func101(0x85c9c52eU, 0x99021743U, 0xeb05d66fU, 0x9be91a40U);
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p89i.prc
***********************************************************************************************************************/
