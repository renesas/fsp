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

void R_SCE_func003_r1(uint32_t* ARG1)
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
    SCE->REG_28H = 0x00870001U;
    OFS_ADR = 128;
    R_SCE_func100(0xea3764daU, 0xebb4b66dU, 0xebd4ecb9U, 0x7dd67d43U);
    R_SCE_func004_r1(OFS_ADR);
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000403U;
    SCE->REG_24H = 0x8000e8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00029008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000010U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x80008cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000880cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x800088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x800094d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000880cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x8000acd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010360U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000f0U);
    R_SCE_func101(0x10831ca1U, 0xc281a506U, 0x17374301U, 0xe4d3212cU);
    R_SCE_func006();
    R_SCE_func100(0x582a5ed6U, 0x0a427c5fU, 0xc5125e60U, 0x64386bb9U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x00000800U;
        R_SCE_func101(0x399f44b1U, 0x8b4e6131U, 0xbfe405a2U, 0x82f3103bU);
    }
    else
    {
        R_SCE_func100(0x0e020092U, 0xf0b2e70eU, 0xaa972bdcU, 0x6e2a711cU);
        SCE->REG_24H = 0x00009cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x000000b0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_34H = 0x00000010U;
        SCE->REG_24H = 0x80005cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000880cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800050d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004a0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004a0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800074d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func100(0xba8cb150U, 0x59aa1fe3U, 0x84900f4fU, 0x3d4a7d23U);
        R_SCE_func103();
        R_SCE_func100(0x76272c57U, 0xd7c1946bU, 0x146dc60cU, 0xb38d6331U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01080c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x530ee80bU, 0x825a9a41U, 0x5dea54ccU, 0xd0141d7bU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x42e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000aaU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[0] = SCE->REG_100H;
        S_HEAP[1] = SCE->REG_100H;
        S_HEAP[2] = SCE->REG_100H;
        S_HEAP[3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[4] = SCE->REG_100H;
        S_HEAP[5] = SCE->REG_100H;
        S_HEAP[6] = SCE->REG_100H;
        S_HEAP[7] = SCE->REG_100H;
        R_SCE_func100(0xf7040eccU, 0xff42e53dU, 0xd783ce09U, 0xcfe0b390U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000abU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[8] = SCE->REG_100H;
        S_HEAP[9] = SCE->REG_100H;
        S_HEAP[10] = SCE->REG_100H;
        S_HEAP[11] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[12] = SCE->REG_100H;
        S_HEAP[13] = SCE->REG_100H;
        S_HEAP[14] = SCE->REG_100H;
        S_HEAP[15] = SCE->REG_100H;
        R_SCE_func100(0x5fa88adaU, 0x24425fb0U, 0xadc8f0deU, 0xc3256a37U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000a8U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[16] = SCE->REG_100H;
        S_HEAP[17] = SCE->REG_100H;
        S_HEAP[18] = SCE->REG_100H;
        S_HEAP[19] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[20] = SCE->REG_100H;
        S_HEAP[21] = SCE->REG_100H;
        S_HEAP[22] = SCE->REG_100H;
        S_HEAP[23] = SCE->REG_100H;
        R_SCE_func100(0x36ab2e42U, 0xaf522ca7U, 0x455a7df8U, 0x89a46c78U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000a9U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[24] = SCE->REG_100H;
        S_HEAP[25] = SCE->REG_100H;
        S_HEAP[26] = SCE->REG_100H;
        S_HEAP[27] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[28] = SCE->REG_100H;
        S_HEAP[29] = SCE->REG_100H;
        S_HEAP[30] = SCE->REG_100H;
        S_HEAP[31] = SCE->REG_100H;
        R_SCE_func100(0xff14ab87U, 0xe9063228U, 0xe10a46ecU, 0xc003e706U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x0000002aU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[32] = SCE->REG_100H;
        S_HEAP[33] = SCE->REG_100H;
        S_HEAP[34] = SCE->REG_100H;
        S_HEAP[35] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[36] = SCE->REG_100H;
        S_HEAP[37] = SCE->REG_100H;
        S_HEAP[38] = SCE->REG_100H;
        S_HEAP[39] = SCE->REG_100H;
        R_SCE_func100(0x960ffa68U, 0xd6e49372U, 0x6040d1b1U, 0x5f85e6cdU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x0000002bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[40] = SCE->REG_100H;
        S_HEAP[41] = SCE->REG_100H;
        S_HEAP[42] = SCE->REG_100H;
        S_HEAP[43] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[44] = SCE->REG_100H;
        S_HEAP[45] = SCE->REG_100H;
        S_HEAP[46] = SCE->REG_100H;
        S_HEAP[47] = SCE->REG_100H;
        R_SCE_func100(0x4a6fc245U, 0xb66f99f9U, 0x1916205fU, 0xcfe4a20dU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[48] = SCE->REG_100H;
        S_HEAP[49] = SCE->REG_100H;
        S_HEAP[50] = SCE->REG_100H;
        S_HEAP[51] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[52] = SCE->REG_100H;
        S_HEAP[53] = SCE->REG_100H;
        S_HEAP[54] = SCE->REG_100H;
        S_HEAP[55] = SCE->REG_100H;
        R_SCE_func100(0xec1a7029U, 0xa1765d2eU, 0xae2bbaecU, 0x95c70385U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000023U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000223U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[56] = SCE->REG_100H;
        S_HEAP[57] = SCE->REG_100H;
        S_HEAP[58] = SCE->REG_100H;
        S_HEAP[59] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[60] = SCE->REG_100H;
        S_HEAP[61] = SCE->REG_100H;
        S_HEAP[62] = SCE->REG_100H;
        S_HEAP[63] = SCE->REG_100H;
        R_SCE_func100(0x699d0600U, 0xaeb1bdf6U, 0x2f612c33U, 0x857d0108U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x400009cdU;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000213U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[64] = SCE->REG_100H;
        S_HEAP[65] = SCE->REG_100H;
        S_HEAP[66] = SCE->REG_100H;
        S_HEAP[67] = SCE->REG_100H;
        R_SCE_func100(0x3d62468cU, 0x9d641ddeU, 0xb04bcb68U, 0x22da51caU);
        R_SCE_func004_r1(OFS_ADR);
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000dcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000403U;
        SCE->REG_24H = 0x8000e8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000002U;
        SCE->REG_24H = 0x800048d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000c00U;
        SCE->REG_24H = 0x800058d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000c20U;
        SCE->REG_24H = 0x8000bcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x00003523U;
        SCE->REG_74H = 0x00000008U;
        SCE->REG_2CH = 0x00000094U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x0000001dU;
        SCE->REG_104H = 0x00000767U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[0];
        SCE->REG_100H = ARG1[1];
        SCE->REG_100H = ARG1[2];
        SCE->REG_100H = ARG1[3];
        SCE->REG_100H = ARG1[4];
        SCE->REG_100H = ARG1[5];
        SCE->REG_100H = ARG1[6];
        SCE->REG_100H = ARG1[7];
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00000767U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[8];
        SCE->REG_100H = ARG1[9];
        SCE->REG_100H = ARG1[10];
        SCE->REG_100H = ARG1[11];
        SCE->REG_100H = ARG1[12];
        SCE->REG_100H = ARG1[13];
        SCE->REG_100H = ARG1[14];
        SCE->REG_100H = ARG1[15];
        SCE->REG_24H = 0x0000dcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a4d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0002b208U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000020U;
        SCE->REG_24H = 0x80007cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000d91U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_34H = 0x00000020U;
        SCE->REG_24H = 0x80001dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0x3ef22588U, 0x6a7d7afeU, 0xa92dad9dU, 0xac7e07cdU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x00000800U;
            R_SCE_func101(0x4d316739U, 0x41c9f42bU, 0x9687f998U, 0x1abab41cU);
        }
        else
        {
            SCE->REG_34H = 0x00000c20U;
            SCE->REG_24H = 0x8000fcd0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800048d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            R_SCE_func100(0x5e194be2U, 0x88ccf668U, 0x25469559U, 0xbbf829b0U);
            R_SCE_func009();
            R_SCE_func100(0x7e527544U, 0xca96159bU, 0xf8863d50U, 0x30fc468cU);
            SCE->REG_34H = 0x00000410U;
            SCE->REG_24H = 0x800098d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            R_SCE_func005_r1(OFS_ADR);
            R_SCE_func100(0x74052956U, 0x1e74f390U, 0x70f9080bU, 0xa3ebd23fU);
            SCE->REG_34H = 0x00000110U;
            SCE->REG_24H = 0x800019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000110U;
            SCE->REG_24H = 0x80001ec0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000330U;
            SCE->REG_24H = 0x800019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000330U;
            SCE->REG_24H = 0x80001ec0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            R_SCE_func007();
            SCE->REG_34H = 0x00000008U;
            SCE->REG_24H = 0x8000f0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008U;
            SCE->REG_24H = 0x800050d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000004U;
            SCE->REG_38H = 0x00231030U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000U;
            SCE->REG_24H = 0x00001dc0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001f00U;
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0x5cd41677U, 0xd60e6b13U, 0x4d025716U, 0x6647711cU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00000800U;
                R_SCE_func101(0x2fa62f65U, 0xf8419f52U, 0x85a35c73U, 0x6b7f5edfU);
            }
            else
            {
                SCE->REG_24H = 0x0000bcd0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000b20cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000054d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x00000908U;
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000060U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x00000908U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000013U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x00008c0cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000880cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000008U;
                SCE->REG_24H = 0x800011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019a1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00009008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000014U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x0000a4d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0002b208U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800U;
                SCE->REG_24H = 0x8000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000040U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000012U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x0000880cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001f00U;
                SCE->REG_1CH = 0x00a10000U;
                R_SCE_func100(0xfa21fea5U, 0x5c4198b3U, 0xca598f46U, 0xaee0bb8aU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00000800U;
                    R_SCE_func101(0xe99d5d5dU, 0xcdff99d6U, 0x1760c984U, 0x01b9a5f5U);
                }
                else
                {
                    SCE->REG_ECH = 0x0000d000U;
                    R_SCE_func101(0xed89af9aU, 0xd96477e8U, 0x61f940bbU, 0x9e982112U);
                }
            }
        }
    }
    SCE->REG_ECH = 0x38000c00U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func003_r1.prc
***********************************************************************************************************************/
