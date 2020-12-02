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

fsp_err_t HW_SCE_Sha256HmacInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t LEN)
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
    SCE->REG_84H = 0x00007602u;
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
    SCE->REG_7CH = 0x00000011u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010000u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000c00u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0xa5d155a0u, 0x90320ae4u, 0x73fb4254u, 0xd884af26u);
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
        SCE->REG_100H = change_endian_long(0x00000076u);
        HW_SCE_p_func101(0x4d5ff0d1u, 0x1216c70eu, 0xa3f4925cu, 0xb6a59070u);
        HW_SCE_p_func043();
        SCE->REG_ECH = 0x0000b4e0u;
        SCE->REG_ECH = 0x0000001bu;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000076u);
        HW_SCE_p_func101(0x15227eb5u, 0x2c6484bau, 0xec96f901u, 0x9e5bf753u);
        HW_SCE_p_func044();
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
        SCE->REG_E0H = 0x80080000u;
        SCE->REG_00H = 0x00008223u;
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
        SCE->REG_ECH = 0x0000b760u;
        SCE->REG_ECH = 0x00003000u;
        HW_SCE_p_func101(0x2deea867u, 0xb7d5bae0u, 0x3157a392u, 0x9b767470u);
    }
    else
    {
        SCE->REG_104H = 0x00000368u;
        SCE->REG_E0H = 0x80040000u;
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
        SCE->REG_ECH = 0x000037e0u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x00ff0000u;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00020000u;
        SCE->REG_ECH = 0x1000d3c0u;
        SCE->REG_ECH = 0x000037e0u;
        SCE->REG_ECH = 0x38008fe0u;
        SCE->REG_ECH = 0x00003000u;
        SCE->REG_ECH = 0x2000d3c1u;
        SCE->REG_ECH = 0x00003760u;
        SCE->REG_ECH = 0x00008f60u;
        SCE->REG_ECH = 0x00003000u;
        SCE->REG_ECH = 0x000037e0u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x000000feu;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x1000d3c2u;
        SCE->REG_ECH = 0x38008bc0u;
        SCE->REG_ECH = 0x00000007u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        SCE->REG_ECH = 0x00003540u;
        SCE->REG_ECH = 0x00003561u;
        SCE->REG_ECH = 0x00003582u;
        SCE->REG_ECH = 0x000035a3u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000076u);
        HW_SCE_p_func101(0x3a2e97efu, 0x1f14d6e0u, 0x37d57d03u, 0xee2e9e0fu);
        HW_SCE_p_func059();
        SCE->REG_104H = 0x00000762u;
        SCE->REG_D0H = 0x40000100u;
        SCE->REG_C4H = 0x02f087b7u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_E0H = 0x80080000u;
        SCE->REG_00H = 0x00008223u;
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
        SCE->REG_100H = InData_KeyIndex[12];
        SCE->REG_100H = InData_KeyIndex[13];
        SCE->REG_100H = InData_KeyIndex[14];
        SCE->REG_100H = InData_KeyIndex[15];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func101(0x45ae9272u, 0x79061a99u, 0xea79821du, 0xe5f9bcc5u);
    }
    HW_SCE_p_func100(0x063a8108u, 0x8c07b7a6u, 0x7e2e826fu, 0xe2a527e9u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x618eda6cu, 0xd48d8015u, 0xaa3ad2fbu, 0xb0d44b36u);
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
        SCE->REG_7CH = 0x00000011u;
        SCE->REG_104H = 0x00000754u;
        SCE->REG_74H = 0x00000004u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x6a09e667u);
        SCE->REG_100H = change_endian_long(0xbb67ae85u);
        SCE->REG_100H = change_endian_long(0x3c6ef372u);
        SCE->REG_100H = change_endian_long(0xa54ff53au);
        SCE->REG_100H = change_endian_long(0x510e527fu);
        SCE->REG_100H = change_endian_long(0x9b05688cu);
        SCE->REG_100H = change_endian_long(0x1f83d9abu);
        SCE->REG_100H = change_endian_long(0x5be0cd19u);
        SCE->REG_74H = 0x00000002u;
        HW_SCE_p_func001();
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p76i_r1.prc
***********************************************************************************************************************/
