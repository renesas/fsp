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

fsp_err_t HW_SCE_Sha256HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length, uint32_t *OutData_MAC)
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
    SCE->REG_74H = 0x00000000u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_00H = 0x00003523u;
    SCE->REG_74H = 0x00000008u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
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
    HW_SCE_p_func002();
    SCE->REG_00H = 0x00005323u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000054u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x80000000u);
    SCE->REG_F8H = 0x00000040u;
    SCE->REG_104H = 0x00000154u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000300u);
    /* WAIT_LOOP */
    while (0u != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_74H = 0x00000000u;
    SCE->REG_1CH = 0x00001600u;
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_104H = 0x00000068u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x38000c00u;
    SCE->REG_ECH = 0x1000b780u;
    SCE->REG_ECH = 0x00002000u;
    SCE->REG_ECH = 0x2000b780u;
    SCE->REG_ECH = 0x00001000u;
    SCE->REG_ECH = 0x38000f9bu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x5645d712u, 0xf440c1a2u, 0x355c8516u, 0x48ad4f74u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x9f0753abu, 0x672d8e04u, 0x33faac82u, 0xa4233a9eu);
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
        SCE->REG_ECH = 0x38000c00u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x63745b29u, 0xaebe8cc7u, 0x7085ee73u, 0x8e5d85a1u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func100(0x5b5be3a7u, 0x336987a4u, 0x9aa80c8cu, 0x48f5e12au);
            SCE->REG_74H = 0x00000008u;
            SCE->REG_04H = 0x00000523u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MAC[0] = SCE->REG_100H;
            OutData_MAC[1] = SCE->REG_100H;
            OutData_MAC[2] = SCE->REG_100H;
            OutData_MAC[3] = SCE->REG_100H;
            OutData_MAC[4] = SCE->REG_100H;
            OutData_MAC[5] = SCE->REG_100H;
            OutData_MAC[6] = SCE->REG_100H;
            OutData_MAC[7] = SCE->REG_100H;
            HW_SCE_p_func102(0xf3b0da21u, 0xaa2c1883u, 0x81dcbe92u, 0x1211e78fu);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
        else
        {
            SCE->REG_104H = 0x00000068u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_length[0];
            SCE->REG_ECH = 0x3420a820u;
            SCE->REG_ECH = 0x00000004u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            SCE->REG_ECH = 0x3420a820u;
            SCE->REG_ECH = 0x00000021u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00A60000u;
            HW_SCE_p_func100(0x787f2c3cu, 0x51494157u, 0x8d21dbdau, 0xae4b1106u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x48ebd1e7u, 0x8950bad9u, 0xacd6fb88u, 0x66f4b1edu);
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
                SCE->REG_ECH = 0x00000bffu;
                SCE->REG_E0H = 0x8088001fu;
                SCE->REG_00H = 0x00008523u;
                SCE->REG_74H = 0x00000008u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x00000800u;
                for (iLoop = 0; iLoop < 32; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3c002be1u;
                    SCE->REG_ECH = 0x12003c1fu;
                    SCE->REG_ECH = 0x00002fe0u;
                }
                SCE->REG_A4H = 0x00040805u;
                SCE->REG_ECH = 0x00000bffu;
                SCE->REG_E0H = 0x8188001fu;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_A4H = 0x00050805u;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_104H = 0x00000761u;
                SCE->REG_A4H = 0x00900c05u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[0];
                SCE->REG_100H = InData_MAC[1];
                SCE->REG_100H = InData_MAC[2];
                SCE->REG_100H = InData_MAC[3];
                SCE->REG_A4H = 0x00900c45u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[4];
                SCE->REG_100H = InData_MAC[5];
                SCE->REG_100H = InData_MAC[6];
                SCE->REG_100H = InData_MAC[7];
                HW_SCE_p_func100(0xfcc31f34u, 0x1b5c3390u, 0x9e47672du, 0x93c96d76u);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x7db6d140u, 0xac1e40a8u, 0x55d31ba6u, 0xdf750b0bu);
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
                    HW_SCE_p_func102(0x8e622b72u, 0x844d725fu, 0xd2e4a8e7u, 0x6bff87e6u);
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
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p76f_r1.prc
***********************************************************************************************************************/
