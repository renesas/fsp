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

fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    HW_SCE_p_func100(0xad40f525u, 0x552fe1a0u, 0x010897f9u, 0xe0e389ddu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x0009f09au, 0x9d3e2b34u, 0x6ae01d0cu, 0x4bf49bf1u);
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
        HW_SCE_p_func100(0xfe5dca73u, 0x08cc0978u, 0x98b6f585u, 0xa843022au);
        SCE->REG_E0H = 0x810103c0u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_p_func100(0xe0102f0cu, 0xf120e54cu, 0x11b41821u, 0xbd53d74du);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x00000020u;
        SCE->REG_A4H = 0x00008da6u;
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
        HW_SCE_p_func100(0xe172eb4au, 0x2d4b73feu, 0x7554ebaau, 0xf0d03c8bu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xdbe6b8d7u, 0x70b75292u, 0x08bff4a7u, 0x0321e806u);
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
            HW_SCE_p_func100(0xf7feb80bu, 0xf012f7edu, 0x61b6bcbcu, 0x544a1c4au);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000361u;
                SCE->REG_B0H = 0x00000020u;
                SCE->REG_A4H = 0x00008da5u;
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
                HW_SCE_p_func100(0x43b55f31u, 0x800162aau, 0xe080c202u, 0xf8240dc2u);
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
                    HW_SCE_p_func101(0xb7a81182u, 0xf79854d8u, 0xe46b3c43u, 0x4ed0ac4fu);
                }
                SCE->REG_ECH = 0x38000fdeu;
                SCE->REG_E0H = 0x00000080u;
                SCE->REG_1CH = 0x00260000u;
                SCE->REG_1CH = 0x00402000u;
                HW_SCE_p_func100(0x94909a24u, 0xce4d9e60u, 0x76135666u, 0xb5af3e2bu);
                SCE->REG_ECH = 0x0000b4e0u;
                SCE->REG_ECH = 0x00000010u;
                SCE->REG_B0H = 0x00000020u;
                SCE->REG_A4H = 0x00008da5u;
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
                    HW_SCE_p_func101(0xd0f5eec8u, 0xacc05fcdu, 0x76ac3301u, 0x03700592u);
                }
                HW_SCE_p_func100(0x1a1a0d1cu, 0xf347e5e8u, 0x5e9966d6u, 0xbc3fca09u);
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
                HW_SCE_p_func101(0x26c1c523u, 0x69d64c70u, 0x201c76dcu, 0x42b3d6bdu);
            }
            HW_SCE_p_func102(0xc6c80c94u, 0x4115ede4u, 0x3cd02c22u, 0x212a144au);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pb3f.prc
***********************************************************************************************************************/
