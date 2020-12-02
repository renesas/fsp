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

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV)
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
    SCE->REG_84H = 0x00008901u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x800100e0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000089u);
    HW_SCE_p_func101(0xd2d17f17u, 0x9ed64bfbu, 0xebed71f8u, 0xd0f1de28u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000006u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000089u);
    HW_SCE_p_func101(0x3a350608u, 0xf1283fdeu, 0xb7c2416eu, 0x378561d5u);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x112550f9u, 0x2ef76aeau, 0x48f9d518u, 0xe2095dc6u);
    SCE->REG_104H = 0x00000762u;
    SCE->REG_D0H = 0x40000100u;
    SCE->REG_C4H = 0x02f087b7u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[1];
    SCE->REG_100H = InData_KeyIndex[2];
    SCE->REG_100H = InData_KeyIndex[3];
    SCE->REG_100H = InData_KeyIndex[4];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[5];
    SCE->REG_100H = InData_KeyIndex[6];
    SCE->REG_100H = InData_KeyIndex[7];
    SCE->REG_100H = InData_KeyIndex[8];
    SCE->REG_A4H = 0x00080805u;
    SCE->REG_00H = 0x00001213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x7106f61eu, 0x705629cfu, 0x82ae645fu, 0xc89bfb94u);
    SCE->REG_A4H = 0x00090805u;
    SCE->REG_00H = 0x00001213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000362u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x000087b5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[9];
    SCE->REG_100H = InData_KeyIndex[10];
    SCE->REG_100H = InData_KeyIndex[11];
    SCE->REG_100H = InData_KeyIndex[12];
    SCE->REG_C4H = 0x00900c45u;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xca5b4afcu, 0xbae7dfd1u, 0x9e7fd8b3u, 0x09358784u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xc78ea399u, 0xa678759fu, 0x300215feu, 0xf2ce9a45u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        SCE->REG_E0H = 0x80010000u;
        SCE->REG_104H = 0x00000068u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Cmd[0];
        SCE->REG_ECH = 0x3000a800u;
        SCE->REG_ECH = 0x00000004u;
        SCE->REG_ECH = 0x00010020u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x00000004u;
        SCE->REG_ECH = 0x00000080u;
        HW_SCE_p_func100(0xe11f3cd4u, 0x4287c0d2u, 0xe2b6bf61u, 0x6afc0ad0u);
        SCE->REG_ECH = 0x00007c00u;
        SCE->REG_1CH = 0x00600000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0x2c0be082u, 0x51950bd2u, 0x5501e81du, 0x37634e53u);
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0xf7c9cd50u, 0xc14979ebu, 0xe09af696u, 0x823702e1u);
        }
        else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0xb5faa29fu, 0xb8d5f49fu, 0xbc20a648u, 0x49f17503u);
        }
        else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x3a1757deu, 0x5d8bf593u, 0xa8dd7442u, 0x5d4eae78u);
        }
        else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x85c9c52eu, 0x99021743u, 0xeb05d66fu, 0x9be91a40u);
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p89i.prc
***********************************************************************************************************************/
