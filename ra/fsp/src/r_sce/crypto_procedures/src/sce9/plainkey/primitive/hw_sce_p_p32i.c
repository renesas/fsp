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

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    SCE->REG_84H = 0x00003202u;
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
    SCE->REG_ECH = 0x38008800u;
    SCE->REG_ECH = 0x00000002u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x3e15d278u, 0x29418229u, 0x20cbf19fu, 0xd78e8134u);
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
        SCE->REG_ECH = 0x38000c00u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x87a0b2ddu, 0x026adc03u, 0x93a8dfeau, 0xf5ae5b87u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000032u);
            HW_SCE_p_func101(0x08eafffau, 0x3c3455aeu, 0x69a6c0f4u, 0xb54f8ea7u);
            HW_SCE_p_func043();
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x00000005u;
            HW_SCE_p_func101(0xfc2e4213u, 0xa406243cu, 0x89b4493cu, 0xd459c7bau);
        }
        else
        {
            SCE->REG_ECH = 0x00003547u;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000032u);
            HW_SCE_p_func101(0x7259cb1bu, 0x9f84c893u, 0xa6879bddu, 0x63d60a09u);
            HW_SCE_p_func068();
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x0146c04bu;
            HW_SCE_p_func101(0x5d699af5u, 0x8e5d7ed4u, 0x709a8d2bu, 0x2ee32018u);
        }
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000032u);
        HW_SCE_p_func101(0x7a5351fdu, 0x60372278u, 0x4f1ff6c5u, 0xa75f4137u);
        HW_SCE_p_func044();
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
        SCE->REG_E0H = 0x80040000u;
        SCE->REG_00H = 0x00008213u;
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
        SCE->REG_104H = 0x00000368u;
        SCE->REG_E0H = 0x80040080u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[1];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[2];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[3];
        HW_SCE_p_func101(0xd6326ea8u, 0x43f9f29fu, 0xcd13f106u, 0x80e8934bu);
    }
    else
    {
        SCE->REG_ECH = 0x38008800u;
        SCE->REG_ECH = 0x00000001u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x3f3e1153u, 0xcf793552u, 0xe4d7efe6u, 0x14c50f80u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
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
            SCE->REG_ECH = 0x00120000u;
            SCE->REG_ECH = 0x1000d3c0u;
            SCE->REG_ECH = 0x3800d80eu;
            SCE->REG_ECH = 0x2000d3c1u;
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
            SCE->REG_100H = change_endian_long(0x00000032u);
            HW_SCE_p_func101(0x047ee2ccu, 0x6bd55018u, 0x422b9459u, 0x9faaf0aeu);
            HW_SCE_p_func059();
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
            SCE->REG_E0H = 0x80040000u;
            SCE->REG_00H = 0x00008213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00000362u;
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x00f087b5u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_E0H = 0x80040080u;
            SCE->REG_00H = 0x00008213u;
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
            HW_SCE_p_func101(0xa077dacau, 0x4e0be9edu, 0x33810a24u, 0x5b0571bbu);
        }
        else
        {
            SCE->REG_104H = 0x00000068u;
            SCE->REG_E0H = 0x80010140u;
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
            SCE->REG_100H = change_endian_long(0x00000005u);
            HW_SCE_p_func101(0xb5c6f42fu, 0x7a27fa8cu, 0xa5ddd6adu, 0x57736414u);
            HW_SCE_p_func068();
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x0195f71du;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000005u);
            HW_SCE_p_func101(0xae0bda23u, 0x6d486cb9u, 0x4cd9b7bbu, 0xc741ba11u);
            HW_SCE_p_func044();
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
            SCE->REG_E0H = 0x80040000u;
            SCE->REG_00H = 0x00008213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00000362u;
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x00f087b5u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_E0H = 0x80040080u;
            SCE->REG_00H = 0x00008213u;
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
            HW_SCE_p_func101(0xa7c07c76u, 0xc417f413u, 0x41723116u, 0x10163c9fu);
        }
    }
    HW_SCE_p_func100(0xf6afb1f0u, 0x49b85b75u, 0x1de05501u, 0x9a451cf9u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xb07a6c46u, 0x392fbf2cu, 0x101414cfu, 0x13d1fd8au);
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
        HW_SCE_p_func100(0x4bc6b123u, 0x27352405u, 0xd72a388eu, 0x427382d1u);
        SCE->REG_E0H = 0x81040000u;
        SCE->REG_C4H = 0x00080805u;
        SCE->REG_00H = 0x00002813u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_7CH = 0x00000001u;
        SCE->REG_7CH = 0x00000041u;
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x00000a84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_00H = 0x00005213u;
        SCE->REG_74H = 0x00001000u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_74H = 0x00000004u;
        SCE->REG_104H = 0x00000354u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_74H = 0x00000002u;
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p32i_r3.prc
***********************************************************************************************************************/
