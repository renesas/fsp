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

void HW_SCE_p_func309(void)
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
    HW_SCE_p_func100(0x507efdf0u, 0x2d03401au, 0xf5398ec0u, 0x286217ffu);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000028u;
    SCE->REG_ECH = 0x00003c1eu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x00000b7bu;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x230f406fu, 0xda7f5edcu, 0x27c3bebbu, 0x1ca2d98fu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(476);
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(612);
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000090u;
    HW_SCE_p_func101(0x6cc0e7d9u, 0x458cdd1fu, 0x11511bb6u, 0x77d8e29au);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0xb8612113u, 0xf762b28au, 0x1e228883u, 0x606b460fu);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_ECH = 0x00003fbeu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x07650df4u, 0x218ae494u, 0x62a374a7u, 0x69f77c6du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(884);
    HW_SCE_p_func100(0x3b9e2e17u, 0x00dc30b0u, 0xd4f87fbdu, 0x78cc9f77u);
    HW_SCE_p_func314(884+64);
    HW_SCE_p_func100(0x34f500c3u, 0x1e7d953du, 0x5a457d14u, 0x1456c4e7u);
    SCE->REG_ECH = 0x3000db72u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d770u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_24H = 0x0000d0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000090u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d366u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x045fd001u, 0x1c068ffcu, 0xf9ad4dc2u, 0x0dc15f12u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x23ee48a2u, 0x420f6666u, 0x7f916148u, 0xbcaeb32fu);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0xedc72e02u, 0x9067ecb0u, 0xbd01da64u, 0x475ec240u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_E0H = 0x8081001eu;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x000000a0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02001191u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d371u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d771u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa0d2af88u, 0x564963feu, 0xfda15b9fu, 0x0a9b6eb2u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x8efeada1u, 0x86c947d3u, 0x97c19f1du, 0xc42b5457u);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0x9b785ba7u, 0xca31ebe8u, 0xf0c98a00u, 0x3de02bd5u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3du);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbc1763d6u, 0xbaf51d99u, 0x286abac4u, 0x4afbbf25u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(544);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x20f12a95u, 0x2310397au, 0x9acc6944u, 0x9593ac91u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(612);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000004u;
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
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xffceae7au, 0x6ced0145u, 0xa2b22416u, 0x66e29adcu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(408);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(476);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_34H = 0x00000008u;
    SCE->REG_24H = 0x800011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000000cu;
    SCE->REG_24H = 0x82001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_E0H = 0x8081001eu;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000028u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000091u;
    HW_SCE_p_func101(0x38ac0cdfu, 0x425c549bu, 0x4671434cu, 0xe7db001cu);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0xdcd705d9u, 0xc956e1bau, 0x824590e2u, 0xe2a4d2bau);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000d0d0u;
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
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x3800db66u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xc5cbb3acu, 0x5a613e5fu, 0xe6719980u, 0xf4de0324u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0x5618de29u, 0x7dbf376bu, 0xdc848924u, 0xc3253b00u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xb8196e42u, 0x78ff726au, 0xcffc4955u, 0x6a8728b9u);
    }
    HW_SCE_p_func100(0x2f82a82du, 0xbf4bcf6au, 0x553f6038u, 0x8cac813cu);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000090u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x89e121cdu, 0x93dc5382u, 0x515ddcadu, 0x04b38724u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0xae198934u, 0x9f1bc69cu, 0x05bffac6u, 0x9ba4919fu);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x8459fdfbu, 0x6264fd2cu, 0x58015355u, 0x6a1a691fu);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000014u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
    SCE->REG_ECH = 0x3800db71u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x13094415u, 0x7c03e279u, 0x87253dceu, 0x8671997bu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0xf526deaau, 0x635f2504u, 0x0c669acau, 0x08b6f407u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xc43db222u, 0xe635f693u, 0xeba2377du, 0xd87d0b4cu);
    }
    HW_SCE_p_func100(0xabd3f950u, 0x60198146u, 0xadd1361cu, 0xd933adc9u);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000090u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d371u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d771u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0737b74fu, 0x953016b6u, 0xb66797cbu, 0x75808618u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x78ef5134u, 0x844af139u, 0xd4823d75u, 0xf6f97fd9u);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0xe5f9bbbeu, 0x96509cc3u, 0x8318b854u, 0x9bd50be0u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
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
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaa1376c8u, 0x78c0ff2au, 0xbe1af5b8u, 0xda3a88cfu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(408);
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3du);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9bedacc0u, 0x8f425520u, 0x027f1c14u, 0xc15dde50u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(544);
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
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(680);
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000092u;
    HW_SCE_p_func101(0xb3093a43u, 0xac9c9129u, 0x503622eeu, 0x14cdab75u);
    HW_SCE_p_func304();
    HW_SCE_p_func100(0xe32e76f5u, 0x11a6942du, 0xdf08bb94u, 0x69570b0du);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000d0d0u;
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
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_ECH = 0x3800db72u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x62b11180u, 0x0ee880b8u, 0xc1c11bd2u, 0x15f65922u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190u);
        HW_SCE_p_func101(0x0d868a6au, 0x65052db0u, 0xe774b17au, 0xab134626u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x4507bc11u, 0xdf51099eu, 0x7400ad3bu, 0xadedb23du);
    }
    HW_SCE_p_func100(0x1db9f65du, 0x7a78d897u, 0xb589b7bau, 0x0d86c3a2u);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d366u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x90e33230u, 0xd7da6c0cu, 0xabd9d876u, 0x2d38ff3bu);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x9fd81c3du, 0x58ca1673u, 0xa58d4cbbu, 0x1a9d9068u);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x0d1d631du, 0x1c5ababau, 0xd136b9c0u, 0x6a317f80u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
    SCE->REG_ECH = 0x3800db71u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x0e836fc7u, 0x884c03cfu, 0x77ffdf45u, 0x4db53950u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0xe5becc29u, 0x9802628eu, 0xae42ccabu, 0xd07c1c64u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x29b7a504u, 0xc94a398du, 0x66872d1bu, 0x8601d289u);
    }
    HW_SCE_p_func100(0x0b00de3du, 0x621ec070u, 0xab514fd4u, 0x37132da0u);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d371u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d771u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcc64659cu, 0x8f163d4au, 0x02a5e2a5u, 0x5b33e3c2u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x5ca187ebu, 0x6d8317b9u, 0x3a029136u, 0x64db1852u);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0xe3b6589cu, 0xab1e9255u, 0x276afe4cu, 0x0aabeb6fu);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_ECH = 0x00003b9eu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003f9eu;
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
    SCE->REG_ECH = 0x3000db68u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d37au;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000093u;
    HW_SCE_p_func101(0x297b5087u, 0xb154b2a1u, 0x00f202ecu, 0x33047f78u);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0x86e1c646u, 0x99aeac35u, 0x85f6aae8u, 0x98139038u);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000d0d0u;
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
    SCE->REG_100H = change_endian_long(0x01f0b809u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(884);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_ECH = 0x3800db72u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xd506cd07u, 0xc57d0308u, 0x73a273d2u, 0x115959dfu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190u);
        HW_SCE_p_func101(0xe51785d3u, 0x16e71b98u, 0x2b674987u, 0xecd2eb45u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xec1d90edu, 0xafea5063u, 0x4014965au, 0xc4644ea5u);
    }
    HW_SCE_p_func100(0x8212523fu, 0x83dc322du, 0x9e84585du, 0xf22dd763u);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d370u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d770u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcfb1c7c9u, 0xb6df7dcdu, 0x49ba0092u, 0x5d22b17du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(884);
    HW_SCE_p_func100(0x1de4b4b9u, 0xab0b62a0u, 0x23a8f5e1u, 0x3cf5363eu);
    HW_SCE_p_func314(884+64);
    HW_SCE_p_func100(0xd2cfce67u, 0xfb8ed3a2u, 0x08f387fau, 0xda42e922u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000010u;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x3800db66u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x6d365454u, 0x4239bc0bu, 0x853c3d8du, 0x207b1244u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0x3945b5a2u, 0x4da29a16u, 0x105b508eu, 0xac563ff4u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x964d6119u, 0x7782c2d7u, 0x7e79dd33u, 0xce9d6cd1u);
    }
    HW_SCE_p_func100(0xeb4eea4au, 0xadad34cfu, 0x6f717270u, 0xc9e241eeu);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000014u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000090u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d366u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xdf42a902u, 0x8d143a96u, 0x81d9c449u, 0x99d9b6a3u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x5f571992u, 0x76ecf695u, 0xf56636dfu, 0x4d8743e8u);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x58beab10u, 0x244d3763u, 0x6eea2fb4u, 0x309d7802u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
    SCE->REG_ECH = 0x3800db71u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x933c9b61u, 0x0b68a76bu, 0xf68bd356u, 0x641ef71fu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0xf6014c4cu, 0x8056f7b7u, 0x72b2ba3au, 0xa19a3635u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x1764ff9fu, 0x1a8492b3u, 0xc49a1d32u, 0x2dc11287u);
    }
    HW_SCE_p_func100(0xad074cdcu, 0xea7ae448u, 0x7324e020u, 0xd3129bcbu);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d371u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d771u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000014u;
    SCE->REG_ECH = 0x00003b9eu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_ECH = 0x3000db71u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d37au;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000581u;
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
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(680);
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000094u;
    HW_SCE_p_func101(0x51e65f45u, 0x2cdb1de0u, 0xf57eea4au, 0x2c370be4u);
    HW_SCE_p_func304();
    HW_SCE_p_func100(0x725794c2u, 0x871ac300u, 0xac83aff0u, 0xf400d18du);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000d0d0u;
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
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x3800db66u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xc31cbbd1u, 0x268d2b25u, 0xe7a62786u, 0x27e369bcu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0x4ca8e691u, 0xd83998fau, 0x26c5f9f2u, 0xe71b8a45u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xf54c3628u, 0x49f01760u, 0xcd33d93du, 0xfeedfa57u);
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_ECH = 0x3800db72u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x239e8ef4u, 0x45342004u, 0x4cd0d273u, 0x246ec09du);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190u);
        HW_SCE_p_func101(0x73401201u, 0xa84dc3b4u, 0x54435447u, 0x3f45b6bdu);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x69bf6174u, 0xbd2a73a4u, 0x831c564bu, 0xc86a28cfu);
    }
    HW_SCE_p_func100(0xcece2e3du, 0x451a005bu, 0x84c56b5eu, 0x0934d294u);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d366u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x14512db2u, 0x44a5245au, 0x46a63ddau, 0xe66d64d7u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x8e38417cu, 0x84dd6705u, 0x34259ec4u, 0xad64a68du);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x2f4e25f7u, 0x508e0b9au, 0x9d404c48u, 0x813169cdu);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_ECH = 0x00003b9eu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003f9eu;
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
    SCE->REG_ECH = 0x3000db68u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d77au;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d37au;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003f9eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x0000d77bu;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000095u;
    HW_SCE_p_func101(0x882fccf7u, 0xa9db782bu, 0x0cb6d375u, 0x49f70d6du);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0x023d5574u, 0xd6d309ffu, 0x25ba5b5eu, 0x580371f1u);
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
    SCE->REG_24H = 0x0000c8d0u;
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
    SCE->REG_100H = change_endian_long(0x010b238bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x3800db66u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x7455c717u, 0x6006723au, 0x42eb0f2du, 0x9b272b9du);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0xa1bc46c7u, 0x07125db3u, 0xa32ee9a0u, 0x47f7555cu);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xc879e5dcu, 0x17888d82u, 0x5f5c4d9bu, 0xc82298aeu);
    }
    HW_SCE_p_func100(0x0d5b76d6u, 0xb70cd2cfu, 0x3b074b32u, 0xb6516a0fu);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x8181001eu;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000090u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d366u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d766u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000014u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(884);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_ECH = 0x3800db70u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x5dfa8bb0u, 0xf9addc81u, 0x8a267091u, 0x100b0e96u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110u);
        HW_SCE_p_func101(0x97d49d5cu, 0xb0f0efeau, 0xeee5ba07u, 0x48ea7fe7u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x77cef942u, 0x2ac856acu, 0x6ee1e859u, 0x95e98234u);
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000018u;
    SCE->REG_ECH = 0x3800db72u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x0b686405u, 0x878db4bbu, 0xd8c40795u, 0xfe6a6eb6u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190u);
        HW_SCE_p_func101(0xdb27deefu, 0xd2f2fcedu, 0x462b8a78u, 0x7eabc0c4u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x99186c2fu, 0xd463674bu, 0xa9b83865u, 0xedc5f09du);
    }
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001191u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x3800db66u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x7c788bcau, 0xa3bb3c75u, 0xb469bc2fu, 0x85b3a642u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x04000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_34H = 0x00000008u;
        SCE->REG_24H = 0x800011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x00000030u;
        SCE->REG_E0H = 0x8088001eu;
        SCE->REG_00H = 0x00008323u;
        SCE->REG_2CH = 0x00000024u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x0000000cu;
        SCE->REG_ECH = 0x00003b9eu;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x0000004cu;
        SCE->REG_ECH = 0x00003f9eu;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x00000030u;
        SCE->REG_E0H = 0x8188001eu;
        SCE->REG_00H = 0x00003823u;
        SCE->REG_2CH = 0x00000014u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_28H = 0x00800001u;
        SCE->REG_104H = 0x00000257u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001u);
        SCE->REG_2CH = 0x00000190u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xFFFFFFFFu);
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x775d82a9u, 0x6e093bcdu, 0xaee304d3u, 0xd1452d0bu);
    }
    else
    {
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000014u;
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
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x68e145aeu, 0xf73293aau, 0x898193e4u, 0x8bab27edu);
    }
    HW_SCE_p_func100(0x5ec7873du, 0x6d0dd9e3u, 0xeef645ecu, 0xc612a596u);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d37eu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d77eu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000020u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000010u;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb9165f89u, 0xf87676cau, 0x3bc818f5u, 0x726d1a94u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(680);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x3800db7eu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x084f91efu, 0xd3cb359bu, 0x5514cb43u, 0xeb853283u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x000000a0u;
        SCE->REG_E0H = 0x80c0001eu;
        SCE->REG_00H = 0x00018303u;
        SCE->REG_2CH = 0x00000022u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        SCE->REG_24H = 0x000049c1u;
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
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            HW_SCE_p_func100(0x053fe767u, 0x7e88b106u, 0x364f0755u, 0x687c7376u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x06001181u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1u;
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
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000050u;
                SCE->REG_E0H = 0x8088001eu;
                SCE->REG_00H = 0x00008323u;
                SCE->REG_2CH = 0x00000020u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000070u;
                SCE->REG_E0H = 0x8088001eu;
                SCE->REG_00H = 0x00008323u;
                SCE->REG_2CH = 0x000000a0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_28H = 0x00800001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_104H = 0x00000157u;
                SCE->REG_2CH = 0x00000050u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001u);
                SCE->REG_E0H = 0x8181001eu;
                SCE->REG_00H = 0x00003807u;
                SCE->REG_2CH = 0x00000110u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_2CH = 0x00000050u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_24H = 0x000001c0u;
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
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001181u;
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
                SCE->REG_1CH = 0x00210000u;
                SCE->REG_28H = 0x00870001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000050u;
                SCE->REG_E0H = 0x8188001eu;
                SCE->REG_00H = 0x00003823u;
                SCE->REG_2CH = 0x00000010u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000070u;
                SCE->REG_E0H = 0x8188001eu;
                SCE->REG_00H = 0x00003823u;
                SCE->REG_2CH = 0x00000090u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x000000a0u;
                SCE->REG_E0H = 0x81c0001eu;
                SCE->REG_00H = 0x00013803u;
                SCE->REG_2CH = 0x00000010u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func101(0xfe9804e6u, 0x12645ab9u, 0xdae649f1u, 0x0ec657c8u);
            }
            else
            {
                HW_SCE_p_func101(0x9e0b8c35u, 0xdd07524au, 0x03cc62fau, 0x826984e6u);
                oLoop1 = 0;
            }
        }
        HW_SCE_p_func101(0x1f5625b7u, 0xda5863eeu, 0x88bfd0b1u, 0x9cba4d84u);
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x000000a0u;
            SCE->REG_E0H = 0x80c0001eu;
            SCE->REG_00H = 0x00018303u;
            SCE->REG_2CH = 0x00000022u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001991u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1u;
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
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x000000a0u;
            SCE->REG_E0H = 0x80c0001eu;
            SCE->REG_00H = 0x00018303u;
            SCE->REG_2CH = 0x00000022u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x06001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1u;
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
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001u;
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x00000050u;
            SCE->REG_E0H = 0x8088001eu;
            SCE->REG_00H = 0x00008323u;
            SCE->REG_2CH = 0x00000020u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x00000070u;
            SCE->REG_E0H = 0x8088001eu;
            SCE->REG_00H = 0x00008323u;
            SCE->REG_2CH = 0x000000a0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_28H = 0x00800001u;
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x00000020u;
            SCE->REG_E0H = 0x8181001eu;
            SCE->REG_00H = 0x00003807u;
            SCE->REG_2CH = 0x00000090u;
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
            SCE->REG_34H = 0x00000004u;
            SCE->REG_24H = 0x800011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_1CH = 0x00210000u;
            SCE->REG_28H = 0x00870001u;
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x00000050u;
            SCE->REG_E0H = 0x8188001eu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000010u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x00000070u;
            SCE->REG_E0H = 0x8188001eu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000090u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_24H = 0x000011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0u;
            SCE->REG_ECH = 0x000000a0u;
            SCE->REG_E0H = 0x81c0001eu;
            SCE->REG_00H = 0x00013803u;
            SCE->REG_2CH = 0x00000010u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func100(0xa5d602dcu, 0x83ac45edu, 0x9d872697u, 0x8b1a9561u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xcad68de3u, 0xaf4e1f11u, 0x82c8a327u, 0x940029c3u);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x04001991u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x06001191u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1u;
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
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000050u;
                SCE->REG_E0H = 0x8088001eu;
                SCE->REG_00H = 0x00008323u;
                SCE->REG_2CH = 0x00000020u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000070u;
                SCE->REG_E0H = 0x8088001eu;
                SCE->REG_00H = 0x00008323u;
                SCE->REG_2CH = 0x000000a0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_28H = 0x00800001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_104H = 0x00000157u;
                SCE->REG_2CH = 0x00000050u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001u);
                SCE->REG_E0H = 0x8181001eu;
                SCE->REG_00H = 0x00003807u;
                SCE->REG_2CH = 0x00000110u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_2CH = 0x00000050u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_24H = 0x000001c0u;
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
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001191u;
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
                SCE->REG_28H = 0x00870001u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000050u;
                SCE->REG_E0H = 0x8188001eu;
                SCE->REG_00H = 0x00003823u;
                SCE->REG_2CH = 0x00000010u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x00000070u;
                SCE->REG_E0H = 0x8188001eu;
                SCE->REG_00H = 0x00003823u;
                SCE->REG_2CH = 0x00000090u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0u;
                SCE->REG_ECH = 0x000000a0u;
                SCE->REG_E0H = 0x81c0001eu;
                SCE->REG_00H = 0x00013803u;
                SCE->REG_2CH = 0x00000010u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func101(0xe24acd49u, 0x60443dd8u, 0x248474a6u, 0x58cab95eu);
            }
        }
        HW_SCE_p_func101(0xdd2a0b5cu, 0x766c6608u, 0xe17bc4d7u, 0xa3f93441u);
    }
    SCE->REG_24H = 0x000088d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000028u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func309.prc
***********************************************************************************************************************/
