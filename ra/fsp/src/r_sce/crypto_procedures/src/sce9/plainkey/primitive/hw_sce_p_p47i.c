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

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t * InData_Cmd,
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
    SCE->REG_84H = 0x00004702u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_C4H = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_104H = 0x00000068u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x3000a800u;
    SCE->REG_ECH = 0x00000006u;
    SCE->REG_ECH = 0x00010020u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000006u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3420a800u;
    SCE->REG_ECH = 0x00000005u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x858a1019u, 0xc34f62cdu, 0xea57d0acu, 0x0aee4802u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
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
        SCE->REG_100H = change_endian_long(0x00000047u);
        HW_SCE_p_func101(0x0d35081bu, 0xbfc89a44u, 0x4b817b82u, 0x1e3a9efau);
        HW_SCE_p_func043();
        SCE->REG_ECH = 0x0000b4e0u;
        SCE->REG_ECH = 0x00000005u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000047u);
        HW_SCE_p_func101(0x187b7158u, 0x36068296u, 0xc75b90d8u, 0x3c2e975fu);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x5250cc11u, 0xb301ced7u, 0x9817c7a8u, 0x9bd7e48bu);
        SCE->REG_104H = 0x00000362u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02f087b5u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_A4H = 0x00080805u;
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
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func101(0x50aac0e4u, 0x44f73738u, 0x16915f2fu, 0xb58af45eu);
    }
    else
    {
        SCE->REG_104H = 0x00000368u;
        SCE->REG_E0H = 0x80040040u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[0];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[2];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x000037e2u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x00ff0000u;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x1000d3c0u;
        SCE->REG_ECH = 0x38008800u;
        SCE->REG_ECH = 0x00000005u;
        SCE->REG_ECH = 0x1000b540u;
        SCE->REG_ECH = 0x0000000fu;
        SCE->REG_ECH = 0x2000b540u;
        SCE->REG_ECH = 0x0000000eu;
        SCE->REG_ECH = 0x3800584au;
        SCE->REG_ECH = 0x2000d3c1u;
        SCE->REG_ECH = 0x000037e2u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x000000feu;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x1000d3c2u;
        SCE->REG_ECH = 0x38008bc0u;
        SCE->REG_ECH = 0x00000007u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        SCE->REG_ECH = 0x0000a800u;
        SCE->REG_ECH = 0x00000003u;
        SCE->REG_ECH = 0x00003542u;
        SCE->REG_ECH = 0x00003563u;
        SCE->REG_ECH = 0x00003584u;
        SCE->REG_ECH = 0x000035a5u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000047u);
        HW_SCE_p_func101(0x771f6fe9u, 0x155336bcu, 0xa502adc2u, 0x151b8494u);
        HW_SCE_p_func059();
        HW_SCE_p_func100(0x1d35c958u, 0x8ab99b81u, 0x1fab250au, 0xeeb14dabu);
        SCE->REG_104H = 0x00000362u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02f087b5u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_A4H = 0x00080805u;
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
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func101(0xe1960594u, 0x2cad8339u, 0xefabb8bbu, 0x59e74638u);
    }
    HW_SCE_p_func100(0xfc1f2510u, 0xf5be6b44u, 0x98aa6735u, 0xcb95d279u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x5e7915ecu, 0xb154b7a3u, 0x2b870eaeu, 0x15ea0d85u);
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
        HW_SCE_p_func100(0xfcc75883u, 0x8b53d34bu, 0x64cd4158u, 0x2f466f82u);
        SCE->REG_ECH = 0x00007c00u;
        SCE->REG_1CH = 0x00600000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0x3b9bc948u, 0xecccd80bu, 0x3d091b4fu, 0xc60b0873u);
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0xf1a717d0u, 0x39aef144u, 0xaeaf235cu, 0x114d5fb4u);
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
            HW_SCE_p_func101(0xc3ba43adu, 0xc15afa63u, 0x48f007e8u, 0xda48eeb4u);
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
            HW_SCE_p_func101(0x7a684752u, 0x024be5efu, 0x579221adu, 0x47a0a264u);
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
            HW_SCE_p_func101(0x0d80a60bu, 0x4b29a5abu, 0x2db3f5b8u, 0xbbdf960eu);
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p47i_r1.prc
***********************************************************************************************************************/
