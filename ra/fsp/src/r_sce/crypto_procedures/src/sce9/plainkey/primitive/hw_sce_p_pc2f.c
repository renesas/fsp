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

fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010000u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextBitLen[0];
    SCE->REG_ECH = 0x000037c0u;
    SCE->REG_ECH = 0x00076bdeu;
    SCE->REG_ECH = 0x00026fdeu;
    SCE->REG_ECH = 0x00000bffu;
    SCE->REG_ECH = 0x38008c00u;
    SCE->REG_ECH = 0x0000007fu;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x3420a800u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x1000d3e0u;
    SCE->REG_ECH = 0x2000abc0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x38000fffu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xfae4674du, 0xd71a8d44u, 0xfda7fc43u, 0xe2f0a49bu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xadffe2f2u, 0x15ef16c2u, 0x7cccbab5u, 0x4476dc7cu);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x18ed9061u, 0x9f68c4f2u, 0x0ca876ceu, 0xbab18046u);
        SCE->REG_E0H = 0x810103c0u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_p_func100(0x15720916u, 0x4928aec9u, 0x9aec1c5cu, 0x2a99bea9u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000020u;
        SCE->REG_A4H = 0x0000cda6u;
        SCE->REG_04H = 0x0000c100u;
        iLoop = 0;
        if(S_RAM[0] >= 4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            for (iLoop = 4; iLoop < S_RAM[0]; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop + 0];
                SCE->REG_100H = InData_Text[iLoop + 1];
                SCE->REG_100H = InData_Text[iLoop + 2];
                SCE->REG_100H = InData_Text[iLoop + 3];
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
            }
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
        }
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func100(0xdfe9ad83u, 0x17fc5993u, 0x5e9d63e7u, 0x6c1c43fbu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x7c1fd1a2u, 0x724ba216u, 0x1618d36cu, 0xb919c74bu);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x38008c00u;
            SCE->REG_ECH = 0x0000007fu;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00A60000u;
            HW_SCE_p_func100(0xf699d6ecu, 0xc3789eafu, 0xc2619429u, 0x11f98a28u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func100(0x7e1f6a4cu, 0x5944e041u, 0x8718c3e6u, 0x5a5db474u);
                SCE->REG_104H = 0x00000051u;
                SCE->REG_A4H = 0x00000c84u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_E0H = 0x80040140u;
                SCE->REG_00H = 0x00008113u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_104H = 0x00000051u;
                SCE->REG_B0H = 0x40000020u;
                SCE->REG_A4H = 0x0000cd24u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_104H = 0x00000361u;
                SCE->REG_B0H = 0x40000020u;
                SCE->REG_A4H = 0x0000cda5u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop + 0];
                SCE->REG_100H = InData_Text[iLoop + 1];
                SCE->REG_100H = InData_Text[iLoop + 2];
                SCE->REG_100H = InData_Text[iLoop + 3];
                SCE->REG_ECH = 0x000008c6u;
                SCE->REG_E0H = 0x80840006u;
                SCE->REG_00H = 0x00008113u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b4e0u;
                SCE->REG_ECH = 0x00000010u;
                SCE->REG_104H = 0x00000368u;
                SCE->REG_E0H = 0x80840007u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+4 + 0];
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+5 + 0];
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+6 + 0];
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+7 + 0];
                SCE->REG_ECH = 0x0000b4a0u;
                SCE->REG_ECH = 0x00000004u;
                SCE->REG_ECH = 0x00003500u;
                SCE->REG_ECH = 0x00036908u;
                SCE->REG_ECH = 0x00008d00u;
                SCE->REG_ECH = 0x0000000cu;
                SCE->REG_ECH = 0x000024c8u;
                SCE->REG_ECH = 0x000024e8u;
                SCE->REG_ECH = 0x00003826u;
                SCE->REG_ECH = 0x00003847u;
                SCE->REG_ECH = 0x00003460u;
                SCE->REG_ECH = 0x00008c60u;
                SCE->REG_ECH = 0x0000001fu;
                SCE->REG_ECH = 0x0000b480u;
                SCE->REG_ECH = 0xffffffffu;
                SCE->REG_ECH = 0x00004403u;
                SCE->REG_ECH = 0x00007484u;
                SCE->REG_ECH = 0x00000c24u;
                SCE->REG_ECH = 0x00001484u;
                SCE->REG_ECH = 0x00000c44u;
                SCE->REG_ECH = 0x00001041u;
                SCE->REG_ECH = 0x00003c47u;
                SCE->REG_ECH = 0x000037e0u;
                SCE->REG_ECH = 0x00008fe0u;
                SCE->REG_ECH = 0x0000007fu;
                SCE->REG_ECH = 0x38008fe0u;
                SCE->REG_ECH = 0x0000001fu;
                SCE->REG_ECH = 0x1000a7e0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000080u;
                SCE->REG_ECH = 0x00002bdfu;
                SCE->REG_ECH = 0x00056bdeu;
                SCE->REG_ECH = 0x0000353eu;
                SCE->REG_E0H = 0x810103c0u;
                SCE->REG_04H = 0x00000607u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = change_endian_long(SCE->REG_100H);
                for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x000024c5u;
                    SCE->REG_ECH = 0x000024e5u;
                    SCE->REG_ECH = 0x00003ba6u;
                    SCE->REG_ECH = 0x00003fa7u;
                    SCE->REG_ECH = 0x000033c0u;
                    HW_SCE_p_func101(0x779c56b5u, 0x4650dd64u, 0xe8ad07e3u, 0xae4a4ddcu);
                }
                HW_SCE_p_func100(0x80546670u, 0x081ae0e5u, 0x9a758775u, 0x3da1afa6u);
                SCE->REG_ECH = 0x38000fdeu;
                SCE->REG_E0H = 0x00000080u;
                SCE->REG_1CH = 0x00260000u;
                SCE->REG_1CH = 0x00402000u;
                SCE->REG_A4H = 0x00040805u;
                SCE->REG_E0H = 0x81040140u;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b4e0u;
                SCE->REG_ECH = 0x00000010u;
                SCE->REG_B0H = 0x40000020u;
                SCE->REG_A4H = 0x0000cda5u;
                SCE->REG_E0H = 0x81840007u;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_04H = 0x00000113u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop + 0] = SCE->REG_100H;
                OutData_Text[iLoop + 1] = SCE->REG_100H;
                OutData_Text[iLoop + 2] = SCE->REG_100H;
                OutData_Text[iLoop + 3] = SCE->REG_100H;
                SCE->REG_ECH = 0x000008c6u;
                SCE->REG_ECH = 0x000024c8u;
                SCE->REG_ECH = 0x00003826u;
                SCE->REG_ECH = 0x00000c24u;
                SCE->REG_ECH = 0x00003c26u;
                SCE->REG_ECH = 0x00000bffu;
                for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x000024c5u;
                    SCE->REG_ECH = 0x00003fe6u;
                    SCE->REG_ECH = 0x00003120u;
                    HW_SCE_p_func101(0x29a06074u, 0xbdcbb2c4u, 0x5219eb7eu, 0x6e6e6eefu);
                }
                HW_SCE_p_func100(0x23f0dc1eu, 0x8497a1d5u, 0x8b5eaf23u, 0x8e25429eu);
                SCE->REG_ECH = 0x38000d29u;
                SCE->REG_E0H = 0x00000080u;
                SCE->REG_1CH = 0x00260000u;
                SCE->REG_1CH = 0x00402000u;
                SCE->REG_ECH = 0x000008c6u;
                SCE->REG_E0H = 0x81840006u;
                SCE->REG_04H = 0x00000613u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+4 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+5 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+6 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+7 + 0] = SCE->REG_100H;
                HW_SCE_p_func101(0xffd6f98au, 0xeb205568u, 0xb0b90841u, 0x1a612f24u);
            }
            HW_SCE_p_func102(0xce7b9474u, 0x78b1de12u, 0xb22a31c4u, 0xc86ac379u);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pc2f.prc
***********************************************************************************************************************/
