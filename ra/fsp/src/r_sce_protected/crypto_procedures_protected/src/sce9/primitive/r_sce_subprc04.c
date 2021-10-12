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
#include "r_sce.h"
#include "r_sce_private.h"

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

void R_SCE_TlsGenerateSubSub(void)
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
    SCE->REG_7CH = 0x00000011U;
    SCE->REG_104H = 0x00000754U;
    SCE->REG_74H = 0x00000004U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x6a09e667U);
    SCE->REG_100H = change_endian_long(0xbb67ae85U);
    SCE->REG_100H = change_endian_long(0x3c6ef372U);
    SCE->REG_100H = change_endian_long(0xa54ff53aU);
    SCE->REG_100H = change_endian_long(0x510e527fU);
    SCE->REG_100H = change_endian_long(0x9b05688cU);
    SCE->REG_100H = change_endian_long(0x1f83d9abU);
    SCE->REG_100H = change_endian_long(0x5be0cd19U);
    SCE->REG_ECH = 0x0000b5a0U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_ECH = 0x0000b5e0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_74H = 0x00000002U;
    for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000394dU;
        SCE->REG_ECH = 0x00008940U;
        SCE->REG_ECH = 0x36363636U;
        SCE->REG_E0H = 0x81010140U;
        SCE->REG_00H = 0x00005807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000025afU;
    }
    SCE->REG_ECH = 0x00007c0dU;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_104H = 0x00000354U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x36363636U);
    SCE->REG_100H = change_endian_long(0x36363636U);
    SCE->REG_100H = change_endian_long(0x36363636U);
    SCE->REG_100H = change_endian_long(0x36363636U);
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x000035aeU;
    SCE->REG_ECH = 0x000269adU;
    R_SCE_func100(0xde30fd3bU, 0xa1a421cdU, 0xdb782423U, 0x3d06a9daU);
    SCE->REG_E0H = 0x810101a0U;
    SCE->REG_04H = 0x00000607U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
    {
        SCE->REG_E0H = 0x8181000bU;
        SCE->REG_00H = 0x00005807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000a560U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x000031a0U;
        R_SCE_func101(0x0fa9b055U, 0xdd060480U, 0x835c7670U, 0x2851f1a5U);
    }
    SCE->REG_ECH = 0x00007c0dU;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_ECH = 0x0000354eU;
    SCE->REG_ECH = 0x00008d40U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000b5e0U;
    SCE->REG_ECH = 0x80000000U;
    SCE->REG_ECH = 0x00003decU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x000039ebU;
    SCE->REG_ECH = 0x0000b560U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000296aU;
    SCE->REG_ECH = 0x0000354bU;
    SCE->REG_ECH = 0x00036d4aU;
    SCE->REG_ECH = 0x0000440aU;
    SCE->REG_ECH = 0x000075efU;
    SCE->REG_ECH = 0x0000b560U;
    SCE->REG_ECH = 0x80000000U;
    SCE->REG_ECH = 0x01886debU;
    SCE->REG_ECH = 0x0000a940U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_ECH = 0x0000440aU;
    SCE->REG_ECH = 0x000079efU;
    SCE->REG_ECH = 0x00003decU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x8181000cU;
    SCE->REG_00H = 0x00005807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000a5c0U;
    SCE->REG_ECH = 0x00000040U;
    SCE->REG_ECH = 0x00036dceU;
    SCE->REG_F8H = 0x00000040U;
    SCE->REG_ECH = 0x000009adU;
    SCE->REG_E0H = 0x810201a0U;
    SCE->REG_00H = 0x0000580bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_74H = 0x00000000U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_00H = 0x00003523U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000754U;
    SCE->REG_74H = 0x00000004U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x6a09e667U);
    SCE->REG_100H = change_endian_long(0xbb67ae85U);
    SCE->REG_100H = change_endian_long(0x3c6ef372U);
    SCE->REG_100H = change_endian_long(0xa54ff53aU);
    SCE->REG_100H = change_endian_long(0x510e527fU);
    SCE->REG_100H = change_endian_long(0x9b05688cU);
    SCE->REG_100H = change_endian_long(0x1f83d9abU);
    SCE->REG_100H = change_endian_long(0x5be0cd19U);
    SCE->REG_ECH = 0x0000b5a0U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_ECH = 0x0000b5e0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_74H = 0x00000002U;
    for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000394dU;
        SCE->REG_ECH = 0x00008940U;
        SCE->REG_ECH = 0x5c5c5c5cU;
        SCE->REG_E0H = 0x81010140U;
        SCE->REG_00H = 0x00005807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000025afU;
    }
    SCE->REG_ECH = 0x00007c0dU;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_104H = 0x00000354U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x5c5c5c5cU);
    SCE->REG_100H = change_endian_long(0x5c5c5c5cU);
    SCE->REG_100H = change_endian_long(0x5c5c5c5cU);
    SCE->REG_100H = change_endian_long(0x5c5c5c5cU);
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00005323U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000754U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x80000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000300U);
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_74H = 0x00000000U;
    SCE->REG_E0H = 0x8088000cU;
    SCE->REG_00H = 0x00008523U;
    SCE->REG_74H = 0x00000008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0xf4c92da6U, 0x935fd722U, 0x0b3821fdU, 0x8dc68b00U);
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00600000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_subprc04_r1.prc
***********************************************************************************************************************/
