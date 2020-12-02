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

void HW_SCE_p_func308(void)
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
    HW_SCE_p_func100(0x8c2d8cf6u, 0x8d56e617u, 0x4e381155u, 0x0522ae21u);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000024u;
    SCE->REG_ECH = 0x00003c1eu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x00000b5au;
    SCE->REG_ECH = 0x0000d77cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x3800db7au;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d37cu;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00002b5du;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x00003b5eu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe9363776u, 0x8ffc645cu, 0x22b826ccu, 0x70a25e76u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(1020);
    HW_SCE_p_func100(0x073d446bu, 0xeccd11c7u, 0x5b0e9e5fu, 0x98abb4ccu);
    HW_SCE_p_func314(1020+64);
    HW_SCE_p_func100(0xfbf01920u, 0xb35ecab2u, 0x10236fdfu, 0xa5cebfeau);
    SCE->REG_ECH = 0x00000b39u;
    SCE->REG_ECH = 0x0000d77du;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x3800db7bu;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d37du;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00002b3du;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x00003b3eu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x659d1915u, 0x355d44e1u, 0x0a383dc2u, 0xfc52da53u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(1088);
    HW_SCE_p_func100(0xff1123e5u, 0x5c8c6531u, 0x4477a46du, 0x1d416236u);
    HW_SCE_p_func314(1088+64);
    HW_SCE_p_func100(0xd336b7c0u, 0xc1d5ac1cu, 0x38833731u, 0x970f8d08u);
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000c0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x81010320u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_E0H = 0x81010340u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010300u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000d77eu;
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x3000db7cu;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x00002fc0u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3000db7du;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x00002fc0u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3000dbc0u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d77eu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d37eu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000058d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1088);
    SCE->REG_ECH = 0x3000db7cu;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d76bu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d36bu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x000037dau;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000097u;
    HW_SCE_p_func101(0x2d831169u, 0xf3e9c45fu, 0x86a9a7dbu, 0x48bfc00cu);
    HW_SCE_p_func310();
    HW_SCE_p_func100(0x5ba57e89u, 0x2ad0cf5cu, 0xc546cbb0u, 0xdfd6101du);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1020);
    SCE->REG_ECH = 0x3000db7du;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d76bu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d36bu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x000037d9u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000098u;
    HW_SCE_p_func101(0xfb0daf22u, 0xfc7f120eu, 0x6e4b02adu, 0x7c564c8au);
    HW_SCE_p_func310();
    SCE->REG_ECH = 0x3800db7eu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x6ce6e688u, 0x1ca60eafu, 0x25c7e486u, 0x73068e9au);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x81010300u;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x80001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x2a06ba12u, 0xe8bfbe05u, 0xfc7ae4e6u, 0x2454e45au);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x81010300u;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x80001181u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xa71d69d5u, 0x3fd3bbc8u, 0xcfd2107au, 0xc1462c2cu);
    }
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d372u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d772u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_E0H = 0x8081001eu;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_E0H = 0x8081001eu;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000d768u;
    SCE->REG_24H = 0x000088d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000024u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func308.prc
***********************************************************************************************************************/
