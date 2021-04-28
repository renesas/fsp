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

void R_SCE_func308(void)
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
    R_SCE_func100(0xb057384eU, 0x03004eb8U, 0x03f35059U, 0xb36635fcU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b5aU;
    SCE->REG_ECH = 0x0000d77cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x3800db7aU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37cU;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00002b5dU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x00003b5eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833U);
    R_SCE_func080();
    R_SCE_func100(0xa18ca9eeU, 0xb5e621a1U, 0x3eb74dfeU, 0xc710978eU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(1020);
    R_SCE_func100(0x1dd54be3U, 0xe6f59cf4U, 0x04914cdbU, 0x22b50074U);
    R_SCE_func314(1020+64);
    R_SCE_func100(0x5fb01cc1U, 0x2256e3f5U, 0x17791ea3U, 0x0d2da591U);
    SCE->REG_ECH = 0x00000b39U;
    SCE->REG_ECH = 0x0000d77dU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x3800db7bU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37dU;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00002b3dU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x00003b3eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    R_SCE_func080();
    R_SCE_func100(0xe5b3569eU, 0xae1103ebU, 0xed441d47U, 0xc892c069U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(1088);
    R_SCE_func100(0x374c7bfbU, 0x694d725fU, 0xeecbbb46U, 0xa6649637U);
    R_SCE_func314(1088+64);
    R_SCE_func100(0xe876f669U, 0x33c26364U, 0x775159efU, 0x6a2365eeU);
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x81010320U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x81010340U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010300U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000dbc0U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000058d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1088);
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037daU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000097U;
    R_SCE_func101(0x24476abdU, 0xed2cc61fU, 0xc70dbde0U, 0x52944ee5U);
    R_SCE_func310();
    R_SCE_func100(0x4a3c9820U, 0x80165372U, 0xabc7c2f8U, 0xec6de5f4U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1020);
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037d9U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000098U;
    R_SCE_func101(0xddec318fU, 0x3f251416U, 0x36ab4a6cU, 0x281950aaU);
    R_SCE_func310();
    SCE->REG_ECH = 0x3800db7eU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xaab3ec60U, 0xd1b13aeeU, 0x77a5d71cU, 0x795a21e6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x81010300U;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x80001191U;
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
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x92cee587U, 0x111485cfU, 0x8ef45a4cU, 0x8cb01b1dU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x81010300U;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x80001181U;
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
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xf4fd8549U, 0xd195a747U, 0xe15df35dU, 0x8702e714U);
    }
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d372U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d772U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d768U;
    SCE->REG_24H = 0x000088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func308.prc
***********************************************************************************************************************/
