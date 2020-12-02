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

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    SCE->REG_84H = 0x00002902u;
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
    SCE->REG_ECH = 0x38008800u;
    SCE->REG_ECH = 0x00000001u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xaf5f3545u, 0x1ae9eac6u, 0x97916425u, 0xda489c67u);
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
        HW_SCE_p_func100(0x47510073u, 0x644e4901u, 0x2941a0fbu, 0x133e01c2u);
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
            SCE->REG_100H = change_endian_long(0x00000029u);
            HW_SCE_p_func101(0x3e47319cu, 0xd7bff6aau, 0xf4e0b9ebu, 0x1dea1c02u);
            HW_SCE_p_func043();
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x00000005u;
            HW_SCE_p_func101(0xe901524bu, 0x3472aa7bu, 0xaba040b0u, 0xa105b27bu);
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
            SCE->REG_100H = change_endian_long(0x00000029u);
            HW_SCE_p_func101(0x9aa21d07u, 0x688a82edu, 0x1189b8d7u, 0xe29f2684u);
            HW_SCE_p_func068();
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x0146c04bu;
            HW_SCE_p_func101(0xe420a06fu, 0x2d5c4d73u, 0x07a4a937u, 0x9a0afc88u);
        }
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000029u);
        HW_SCE_p_func101(0x41acb932u, 0x1a93d263u, 0x1040891fu, 0x85c5664eu);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0xd177a4d2u, 0x55fd89a4u, 0x4101c1d1u, 0xdbacd9feu);
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
        HW_SCE_p_func101(0x7c240052u, 0x386c9704u, 0xb361b7ffu, 0x1e4f00bfu);
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
        SCE->REG_ECH = 0x00120000u;
        SCE->REG_ECH = 0x1000d3c0u;
        SCE->REG_ECH = 0x3800d80fu;
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
        SCE->REG_100H = change_endian_long(0x00000029u);
        HW_SCE_p_func101(0x2adc7d02u, 0x788211e1u, 0x24bdf442u, 0xdf007432u);
        HW_SCE_p_func059();
        HW_SCE_p_func100(0x85c33db3u, 0xfaf76717u, 0x874d3287u, 0x50161587u);
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
        HW_SCE_p_func101(0x7dac9b7fu, 0x2a43d5c2u, 0x2af22cbeu, 0x0b247357u);
    }
    HW_SCE_p_func100(0x8bff74d4u, 0x226b6052u, 0x135a49e1u, 0xaf348c2bu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x66eabf73u, 0xf41d1e94u, 0xf9a72548u, 0x06165eacu);
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
        SCE->REG_7CH = 0x00000001u;
        SCE->REG_7CH = 0x00000041u;
        SCE->REG_104H = 0x00000051u;
        SCE->REG_A4H = 0x00000a84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_00H = 0x00005113u;
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p29i_r2.prc
***********************************************************************************************************************/
