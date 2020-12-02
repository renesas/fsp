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

fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    SCE->REG_84H = 0x00002b02u;
    SCE->REG_108H = 0x00000000u;
    HW_SCE_p_func100(0x29802336u, 0xd159a0b7u, 0xe311d54cu, 0x36dce5c5u);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xb8dc77d4u, 0x3247864du, 0xc9a3aaf3u, 0x419c0ae7u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01080c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_ECH = 0x00000a31u;
    for(kLoop = 0; kLoop < MAX_CNT; kLoop = kLoop + 1)
    {
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_00H = 0x00003043u;
        SCE->REG_2CH = 0x00000012u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_104H = 0x00002f57u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00030005u);
        SCE->REG_100H = change_endian_long(0x0007000bu);
        SCE->REG_100H = change_endian_long(0x000d0011u);
        SCE->REG_100H = change_endian_long(0x00130017u);
        SCE->REG_100H = change_endian_long(0x001d001fu);
        SCE->REG_100H = change_endian_long(0x00250029u);
        SCE->REG_100H = change_endian_long(0x002b002fu);
        SCE->REG_100H = change_endian_long(0x003b003du);
        SCE->REG_100H = change_endian_long(0x00430047u);
        SCE->REG_100H = change_endian_long(0x0049004fu);
        SCE->REG_100H = change_endian_long(0x00530059u);
        SCE->REG_100H = change_endian_long(0x00610065u);
        SCE->REG_100H = change_endian_long(0x0067006bu);
        SCE->REG_100H = change_endian_long(0x006d0071u);
        SCE->REG_100H = change_endian_long(0x007f0083u);
        SCE->REG_100H = change_endian_long(0x0089008bu);
        SCE->REG_100H = change_endian_long(0x00950097u);
        SCE->REG_100H = change_endian_long(0x009d00a3u);
        SCE->REG_100H = change_endian_long(0x00a700adu);
        SCE->REG_100H = change_endian_long(0x00b300b5u);
        SCE->REG_100H = change_endian_long(0x00bf00c1u);
        SCE->REG_100H = change_endian_long(0x00c500c7u);
        SCE->REG_100H = change_endian_long(0x00d300dfu);
        SCE->REG_100H = change_endian_long(0x00e300e5u);
        SCE->REG_100H = change_endian_long(0x00e900efu);
        SCE->REG_100H = change_endian_long(0x00f100fbu);
        SCE->REG_100H = change_endian_long(0x01010107u);
        SCE->REG_100H = change_endian_long(0x010d010fu);
        SCE->REG_100H = change_endian_long(0x01150119u);
        SCE->REG_100H = change_endian_long(0x011b0125u);
        SCE->REG_100H = change_endian_long(0x01330137u);
        SCE->REG_100H = change_endian_long(0x0139013du);
        SCE->REG_100H = change_endian_long(0x014b0151u);
        SCE->REG_100H = change_endian_long(0x015b015du);
        SCE->REG_100H = change_endian_long(0x01610167u);
        SCE->REG_100H = change_endian_long(0x016f0175u);
        SCE->REG_100H = change_endian_long(0x017b017fu);
        SCE->REG_100H = change_endian_long(0x0185018du);
        SCE->REG_100H = change_endian_long(0x01910199u);
        SCE->REG_100H = change_endian_long(0x01a301a5u);
        SCE->REG_100H = change_endian_long(0x01af01b1u);
        SCE->REG_100H = change_endian_long(0x01b701bbu);
        SCE->REG_100H = change_endian_long(0x01c101c9u);
        SCE->REG_100H = change_endian_long(0x01cd01cfu);
        SCE->REG_100H = change_endian_long(0x01d301dfu);
        SCE->REG_100H = change_endian_long(0x01e701ebu);
        SCE->REG_100H = change_endian_long(0x01f301f7u);
        SCE->REG_100H = change_endian_long(0x01fd0000u);
        SCE->REG_ECH = 0x000008c6u;
        SCE->REG_00H = 0x00000343u;
        SCE->REG_2CH = 0x00000022u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_E0H = 0x80b00006u;
        SCE->REG_00H = 0x000083c3u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x009f0001u;
        HW_SCE_p_func100(0x7c3be8a4u, 0x10077703u, 0x98320738u, 0x5903bfb6u);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_E0H = 0x80040000u;
        SCE->REG_00H = 0x00008213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x0000d01fu;
        SCE->REG_E0H = 0x81040000u;
        SCE->REG_00H = 0x00003813u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        for(iLoop = 0; iLoop < 24; iLoop = iLoop + 4)
        {
            HW_SCE_p_func100(0x10e16e07u, 0x8fb49ab6u, 0xf23e1fdfu, 0x970de29au);
            HW_SCE_p_func103();
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x01000c84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_00H = 0x00003213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func101(0xfc43caa7u, 0xb55af2a9u, 0x6c16fba1u, 0x313b167cu);
        }
        HW_SCE_p_func100(0x10e16e07u, 0x8fb49ab6u, 0xf23e1fdfu, 0x970de29au);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_E0H = 0x80040000u;
        SCE->REG_00H = 0x00008213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x0000d060u;
        SCE->REG_E0H = 0x81040000u;
        SCE->REG_00H = 0x00003813u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_2CH = 0x00000011u;
        SCE->REG_104H = 0x00001f57u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xB51EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851EB8u);
        SCE->REG_100H = change_endian_long(0x51EB851Eu);
        SCE->REG_100H = change_endian_long(0xB851EB85u);
        SCE->REG_100H = change_endian_long(0x1EB851EBu);
        SCE->REG_100H = change_endian_long(0x851EB851u);
        SCE->REG_100H = change_endian_long(0xEB851B5Cu);
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0x90ae1e92u, 0x8bca1ce6u, 0x377f1b58u, 0x7427eca8u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x5cba8941u, 0x18800bcfu, 0x699933a2u, 0xc0a9c83du);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0x755f15bcu, 0xfaa7c752u, 0x8cdee2ccu, 0x7c5d5e22u);
        }
        SCE->REG_ECH = 0x38008a20u;
        SCE->REG_ECH = 0x00000001u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x1ff30c58u, 0x2c43ede7u, 0x51891153u, 0xc6f0919au);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_24H = 0x00001dc0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0x491d7813u, 0x9669f2a6u, 0x8ab8a647u, 0xebc5b55fu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001d91u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                HW_SCE_p_func101(0x512c888cu, 0xac3c9b30u, 0x350fde63u, 0xaae062a7u);
            }
            else
            {
                HW_SCE_p_func101(0xc1f2ef4fu, 0x557853acu, 0x59b8831bu, 0x4b149043u);
            }
            SCE->REG_2CH = 0x00000011u;
            SCE->REG_104H = 0x00000357u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_100H = change_endian_long(0x10000000u);
            SCE->REG_00H = 0x00003073u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x00001591u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0x87807a30u, 0x9f5ca829u, 0xe1175f96u, 0x1a9e6e75u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xe281d2f1u, 0x0c9fbf53u, 0xf7faeb43u, 0xc9102828u);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0xc6d10669u, 0x9f4ff89du, 0x8038e04au, 0x9a3e17b0u);
            }
        }
        else
        {
            HW_SCE_p_func101(0x07901e4cu, 0x0cebe917u, 0x0f834a0eu, 0x9f2d080eu);
        }
        SCE->REG_ECH = 0x000008c6u;
        SCE->REG_ECH = 0x0000094au;
        for(iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003906u;
            SCE->REG_ECH = 0x00002cc0u;
            SCE->REG_ECH = 0x00002cc0u;
            SCE->REG_E0H = 0x81010100u;
            SCE->REG_00H = 0x0000307fu;
            SCE->REG_2CH = 0x00000014u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00003807u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x00004006u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000009c0u;
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
            HW_SCE_p_func100(0x85dde662u, 0xd8fc3123u, 0x89de60c8u, 0x07d5ef2eu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000d140u;
                HW_SCE_p_func101(0x28a65192u, 0xe2a959dbu, 0xd43404eau, 0x7339fd84u);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x11a06545u, 0x32ad1e6fu, 0xdeb595cdu, 0xe97bc932u);
            }
        }
        SCE->REG_ECH = 0x38008940u;
        SCE->REG_ECH = 0x00000001u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x11867603u, 0x6f83bc5au, 0xaa875c8du, 0x12f9e1ecu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xebf0bae4u, 0x21cca239u, 0xd872659au, 0xfcdcf0fcu);
            continue;
        }
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000060c1u;
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
        SCE->REG_24H = 0x00000591u;
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
        SCE->REG_00H = 0x0000307fu;
        SCE->REG_2CH = 0x00000014u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_104H = 0x00000057u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00010001u);
        SCE->REG_24H = 0x00004006u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000dc0u;
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
        SCE->REG_24H = 0x000009c0u;
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
        HW_SCE_p_func100(0x7c533ae2u, 0x000734a8u, 0x356810bau, 0x487c1ecfu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x5436329au, 0x9632d27fu, 0x10281c9eu, 0xc0df0d5fu);
        }
        else
        {
            SCE->REG_24H = 0x0000d0d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019c0u;
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
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000005c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000189u;
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
            HW_SCE_p_func100(0x79f5b90au, 0xd7922a5au, 0xac0169c2u, 0x03577a52u);
            SCE->REG_18H = 0x00000004u;
            SCE->REG_38H = 0x00004080u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000u;
            SCE->REG_24H = 0x000005c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000u;
            SCE->REG_24H = 0x000044d0u;
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
            SCE->REG_24H = 0x00000991u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0x8a4e89beu, 0xad785403u, 0x03489702u, 0x2497f830u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xbe8e9962u, 0x0bda5eb5u, 0x5c30c9c9u, 0x33a96ae3u);
                continue;
            }
            SCE->REG_24H = 0x000098d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b540u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_E0H = 0x80a0000au;
            SCE->REG_00H = 0x00008383u;
            SCE->REG_2CH = 0x00000020u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b560u;
            SCE->REG_ECH = 0x00000003u;
            SCE->REG_B0H = 0x00000700u;
            SCE->REG_A4H = 0x42e0873fu;
            SCE->REG_00H = 0x00001383u;
            SCE->REG_2CH = 0x00000020u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00000051u;
            SCE->REG_A4H = 0x00000c84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_A4H = 0x400009cdu;
            SCE->REG_00H = 0x00001113u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x38008a20u;
            SCE->REG_ECH = 0x00000000u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            HW_SCE_p_func100(0xf96cb05eu, 0x7a810f51u, 0x46e8fa5eu, 0x812236d7u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_7CH = 0x00000021u;
                SCE->REG_00H = 0x00005113u;
                SCE->REG_74H = 0x00000004u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func101(0x87016245u, 0x5e83f673u, 0x602e7aebu, 0xeb5683b0u);
            }
            else
            {
                SCE->REG_7CH = 0x00000041u;
                SCE->REG_00H = 0x00005113u;
                SCE->REG_74H = 0x00000004u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func101(0x239b33b8u, 0xd6eb409fu, 0x93df7b47u, 0xb35986dcu);
            }
            HW_SCE_p_func100(0xeaa4de27u, 0x5c6570b3u, 0x23239a44u, 0xb259bd4du);
            SCE->REG_24H = 0x000011c0u;
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
            SCE->REG_ECH = 0x00000929u;
            SCE->REG_ECH = 0x0000b4c0u;
            SCE->REG_ECH = 0x000000fcu;
            SCE->REG_ECH = 0x00003906u;
            SCE->REG_ECH = 0x00008d00u;
            SCE->REG_ECH = 0xfffffffeu;
            SCE->REG_ECH = 0x00003d06u;
            SCE->REG_ECH = 0x00000908u;
            for(iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                SCE->REG_ECH = 0x000038e6u;
                SCE->REG_ECH = 0x0000a8c0u;
                SCE->REG_ECH = 0x00000004u;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x38008900u;
                    SCE->REG_ECH = 0x00000000u;
                    SCE->REG_ECH = 0x11816907u;
                    SCE->REG_ECH = 0x38008900u;
                    SCE->REG_ECH = 0x00000000u;
                    SCE->REG_ECH = 0x10002d20u;
                    SCE->REG_ECH = 0x000168e7u;
                }
            }
            SCE->REG_ECH = 0x00003549u;
            SCE->REG_ECH = 0x0000a540u;
            SCE->REG_ECH = 0x00000003u;
            SCE->REG_ECH = 0x0002694au;
            SCE->REG_E0H = 0x81010140u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eau;
            SCE->REG_24H = 0x000011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x00000185u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0u;
                HW_SCE_p_func101(0x25f7c21cu, 0xa58e2d37u, 0xc7d2c302u, 0x94a4950cu);
            }
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            HW_SCE_p_func100(0x3ffbde47u, 0xdf842701u, 0x3ed2ea1fu, 0x92f4b6cdu);
            SCE->REG_ECH = 0x00026d4au;
            SCE->REG_ECH = 0x00002949u;
            SCE->REG_E0H = 0x81010140u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eau;
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x2000018du;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0u;
                HW_SCE_p_func101(0xf2494d23u, 0x208dc9cfu, 0x9eaacfe5u, 0xe3122179u);
            }
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            HW_SCE_p_func100(0xb09a35c9u, 0x5d8bb3e6u, 0xfc920928u, 0x6f246efau);
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000a52u;
            SCE->REG_24H = 0x00006404u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00006c04u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_E0H = 0x81010160u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_2CH = 0x00000010u;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 4)
                {
                    HW_SCE_p_func100(0x80f0c0afu, 0xb016844bu, 0xab5eb905u, 0x9689d197u);
                    HW_SCE_p_func103();
                    SCE->REG_104H = 0x00000052u;
                    SCE->REG_C4H = 0x01000c84u;
                    /* WAIT_LOOP */
                    while (1u != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000000u);
                    SCE->REG_00H = 0x00003213u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800u;
                    HW_SCE_p_func101(0x615822e9u, 0xfce99d10u, 0xc52ef231u, 0xd71f309au);
                }
                HW_SCE_p_func100(0xad8720efu, 0x8c70ba5eu, 0xc306a7e5u, 0x8d3defeeu);
                SCE->REG_24H = 0x000019c0u;
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
                SCE->REG_24H = 0x00000591u;
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
                SCE->REG_24H = 0x00000591u;
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
                SCE->REG_24H = 0x00009008u;
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
                SCE->REG_24H = 0x00000581u;
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
                SCE->REG_24H = 0x000019c0u;
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
                SCE->REG_24H = 0x00000581u;
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
                SCE->REG_24H = 0x00000581u;
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
                SCE->REG_24H = 0x00000dc0u;
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
                SCE->REG_18H = 0x00000004u;
                SCE->REG_38H = 0x00000c40u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B10)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000000u;
                SCE->REG_24H = 0x000005c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001191u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000u;
                SCE->REG_24H = 0x000005c0u;
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
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000991u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000u;
                HW_SCE_p_func100(0x5025e1b2u, 0xe9c90814u, 0x20f9ebb3u, 0x8d9af69eu);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (0u == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00002e40u;
                    HW_SCE_p_func101(0x400c3652u, 0x19b00af6u, 0x415d810du, 0x6580bbf1u);
                }
                else
                {
                    HW_SCE_p_func100(0x87f0e1cbu, 0x06afd9adu, 0xc94c17ecu, 0xc9d9cfc0u);
                    SCE->REG_24H = 0x000019c0u;
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
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006404u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006c04u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_E0H = 0x81010120u;
                    SCE->REG_04H = 0x00000606u;
                    /* WAIT_LOOP */
                    while (1u != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    S_RAM[0+1 + 0] = change_endian_long(SCE->REG_100H);
                    SCE->REG_ECH = 0x000037e9u;
                    for(jLoop = 0; jLoop < S_RAM[0+1]; jLoop = jLoop + 1)
                    {
                        SCE->REG_24H = 0x000009c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001191u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000u;
                        SCE->REG_24H = 0x000011c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000991u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000u;
                        HW_SCE_p_func100(0x8ec7a622u, 0xc2ecfd33u, 0x4596d1b1u, 0xdd384955u);
                        SCE->REG_1CH = 0x00400000u;
                        SCE->REG_1D0H = 0x00000000u;
                        if (0u == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_ECH = 0x00002e40u;
                            HW_SCE_p_func101(0xd4b47306u, 0x947e48e2u, 0xe08a050cu, 0x6baf7466u);
                            break;
                        }
                        else
                        {
                            SCE->REG_24H = 0x00004c0cu;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x0000880cu;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x000019c0u;
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
                            SCE->REG_24H = 0x000040c1u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            HW_SCE_p_func101(0xe518ad9du, 0x5640af24u, 0x34eac94eu, 0x014d63edu);
                        }
                    }
                    SCE->REG_ECH = 0x38008a40u;
                    SCE->REG_ECH = 0x00000000u;
                    SCE->REG_E0H = 0x00000080u;
                    SCE->REG_1CH = 0x00260000u;
                    HW_SCE_p_func100(0x98765488u, 0x67b2035eu, 0x3880187bu, 0x02273ca1u);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func101(0xdbe391c8u, 0xe36886d3u, 0x44ecc41bu, 0x542e2e2du);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0x624f8893u, 0xe40b8b49u, 0x8082da1au, 0xc20670a6u);
                    }
                }
            }
            SCE->REG_ECH = 0x38000a4bu;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            HW_SCE_p_func100(0xd67e7880u, 0xe9c8649eu, 0x28a2b1cau, 0xa1387d95u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00002e20u;
                SCE->REG_ECH = 0x38008a20u;
                SCE->REG_ECH = 0x00000002u;
                SCE->REG_E0H = 0x00000080u;
                SCE->REG_1CH = 0x00260000u;
                HW_SCE_p_func100(0xc0f8142au, 0x43ece9e1u, 0xe5a42c4cu, 0x95e232e0u);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func101(0x72ead49bu, 0x3189737du, 0x9848fc7du, 0x2304bad9u);
                    break;
                }
                else
                {
                    SCE->REG_24H = 0x000019c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000e0c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    HW_SCE_p_func101(0x4165eaaau, 0xde546422u, 0x77a875aau, 0x47feb412u);
                }
            }
            else
            {
                HW_SCE_p_func101(0x424beb5fu, 0x7e7bd614u, 0xc3225a20u, 0xaa7eb3c8u);
            }
        }
    }
    SCE->REG_ECH = 0x38008a20u;
    SCE->REG_ECH = 0x00000002u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x797c9f8cu, 0xf9c42989u, 0xc34235dcu, 0xabd7d990u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x9557ba67u, 0x07316373u, 0x90ae53f1u, 0x62dc9458u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    HW_SCE_p_func100(0xac0314bdu, 0x515c4e7eu, 0xb9f37c2bu, 0xa620448du);
    SCE->REG_ECH = 0x0000b5c0u;
    SCE->REG_ECH = 0x00010001u;
    SCE->REG_24H = 0x000019c0u;
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
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001dc0u;
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
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_D0H = 0x00000f00u;
    SCE->REG_C4H = 0x42e087bfu;
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    SCE->REG_04H = 0x00000202u;
    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
    }
    HW_SCE_p_func100(0xd43ec52du, 0x5fb382ecu, 0xa9cc436cu, 0x4d6b8853u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_C4H = 0x400009cdu;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_HEAP[iLoop + 0] = SCE->REG_100H;
    S_HEAP[iLoop + 1] = SCE->REG_100H;
    S_HEAP[iLoop + 2] = SCE->REG_100H;
    S_HEAP[iLoop + 3] = SCE->REG_100H;
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000009c0u;
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
    SCE->REG_24H = 0x0000e0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    while(1)
    {
        SCE->REG_24H = 0x00008006u;
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
        SCE->REG_24H = 0x00000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0xa7c960d8u, 0xb1109e97u, 0x6b23ed89u, 0x19ad0c6du);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x1f9661cdu, 0x28746ae5u, 0x8cd2741du, 0x6ddec20bu);
            break;
        }
        else
        {
            SCE->REG_24H = 0x000019c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000d0d0u;
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
            HW_SCE_p_func101(0x3f844510u, 0xe045fee9u, 0x9ccc4a88u, 0x014d4648u);
        }
    }
    SCE->REG_24H = 0x000094d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000c002u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000dcd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000b80au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_00H = 0x000030ffu;
    SCE->REG_2CH = 0x00000014u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000057u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00010001u);
    SCE->REG_2CH = 0x00000002u;
    SCE->REG_24H = 0x0000c002u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_E0H = 0x800100c0u;
    SCE->REG_00H = 0x0000031fu;
    SCE->REG_2CH = 0x00000024u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x00008307u;
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
    SCE->REG_24H = 0x00000991u;
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
    SCE->REG_24H = 0x000011c0u;
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
    SCE->REG_ECH = 0x0000b500u;
    SCE->REG_ECH = 0x00010001u;
    SCE->REG_24H = 0x000005c0u;
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
    while(1)
    {
        HW_SCE_p_func100(0x2601c365u, 0x86269c2cu, 0x8bd2d673u, 0x7fd6e24eu);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x628d9e05u, 0xdbb7daa3u, 0xa04bf479u, 0x0ed0c908u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01090c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_ECH = 0x0000094au;
        SCE->REG_E0H = 0x80c0000au;
        SCE->REG_00H = 0x00018303u;
        SCE->REG_2CH = 0x00000022u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0x91cef570u, 0x5ddcb017u, 0x1a28922fu, 0xde55c6f6u);
        SCE->REG_D0H = 0x00000f00u;
        SCE->REG_C4H = 0x42e097bfu;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        SCE->REG_04H = 0x00000202u;
        for (iLoop=68; iLoop<132; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_HEAP[iLoop + 0] = SCE->REG_100H;
            S_HEAP[iLoop + 1] = SCE->REG_100H;
            S_HEAP[iLoop + 2] = SCE->REG_100H;
            S_HEAP[iLoop + 3] = SCE->REG_100H;
        }
        HW_SCE_p_func100(0x85c5fb6eu, 0xd3462e3cu, 0xefde4039u, 0x337f35b6u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x00000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_C4H = 0x400019cdu;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_04H = 0x00000212u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_24H = 0x000019c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_00H = 0x0000301fu;
        SCE->REG_2CH = 0x00000014u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_E0H = 0x810100c0u;
        SCE->REG_00H = 0x00003807u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_00H = 0x0000301fu;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_E0H = 0x81010100u;
        SCE->REG_00H = 0x00003807u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_2CH = 0x00000000u;
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000c002u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00003506u;
        SCE->REG_E0H = 0x800100c0u;
        SCE->REG_00H = 0x0000031fu;
        SCE->REG_2CH = 0x0000002cu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_00H = 0x00008307u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x380088c0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x84072e81u, 0xb4707fe1u, 0x210e80f2u, 0x478f4a77u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_104H = 0x00003f61u;
            SCE->REG_B0H = 0x00000f00u;
            SCE->REG_A4H = 0x42f087bfu;
            SCE->REG_00H = 0x00013103u;
            SCE->REG_2CH = 0x00000014u;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_HEAP[iLoop + 0];
                SCE->REG_100H = S_HEAP[iLoop + 1];
                SCE->REG_100H = S_HEAP[iLoop + 2];
                SCE->REG_100H = S_HEAP[iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func101(0x4d7de79eu, 0x7aee29b9u, 0xfdb1ad36u, 0xe56bb109u);
            break;
        }
        else
        {
            SCE->REG_28H = 0x009f0001u;
            SCE->REG_24H = 0x000015c0u;
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
            SCE->REG_00H = 0x00003083u;
            SCE->REG_2CH = 0x00000011u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_24H = 0x0000880eu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_104H = 0x00003f62u;
            SCE->REG_D0H = 0x00000f00u;
            SCE->REG_C4H = 0x42f097bfu;
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000012u;
            for (iLoop=68; iLoop<132; iLoop=iLoop+4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_HEAP[iLoop + 0];
                SCE->REG_100H = S_HEAP[iLoop + 1];
                SCE->REG_100H = S_HEAP[iLoop + 2];
                SCE->REG_100H = S_HEAP[iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_C4H = 0x400017bdu;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_HEAP[iLoop + 0];
            SCE->REG_100H = S_HEAP[iLoop + 1];
            SCE->REG_100H = S_HEAP[iLoop + 2];
            SCE->REG_100H = S_HEAP[iLoop + 3];
            SCE->REG_C4H = 0x00800c45u;
            SCE->REG_00H = 0x00002213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
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
            SCE->REG_ECH = 0x0000094au;
            SCE->REG_E0H = 0x81c0000au;
            SCE->REG_00H = 0x00013803u;
            SCE->REG_2CH = 0x00000010u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func101(0xd78e57d3u, 0x88d3ecf5u, 0x786fbc37u, 0x62fe7edfu);
        }
    }
    SCE->REG_ECH = 0x00007c06u;
    SCE->REG_1CH = 0x00602000u;
    SCE->REG_A4H = 0x400007bdu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[iLoop + 0];
    SCE->REG_100H = S_HEAP[iLoop + 1];
    SCE->REG_100H = S_HEAP[iLoop + 2];
    SCE->REG_100H = S_HEAP[iLoop + 3];
    SCE->REG_A4H = 0x00800c45u;
    SCE->REG_00H = 0x00001113u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xe8af30a3u, 0x68c2064eu, 0x712f8903u, 0xf66d4c14u);
    SCE->REG_28H = 0x00bf0001u;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xd6fee8b4u, 0xfeb8e1cfu, 0xec897771u, 0x8805760eu);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01090c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    HW_SCE_p_func100(0x7a264cd4u, 0x63f846bdu, 0x4e808fcau, 0xacfd971fu);
    SCE->REG_D0H = 0x00000f00u;
    SCE->REG_C4H = 0x42e097bfu;
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    SCE->REG_04H = 0x00000202u;
    for (iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
    }
    HW_SCE_p_func100(0x771da7e3u, 0x9729dd62u, 0xae475f17u, 0x8047367cu);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_C4H = 0x400019cdu;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_HEAP[iLoop + 0] = SCE->REG_100H;
    S_HEAP[iLoop + 1] = SCE->REG_100H;
    S_HEAP[iLoop + 2] = SCE->REG_100H;
    S_HEAP[iLoop + 3] = SCE->REG_100H;
    HW_SCE_p_func100(0x34fa079fu, 0x31773c42u, 0xb11338adu, 0x91df1e11u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x0000b8d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000002u;
    SCE->REG_24H = 0x00007b0au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0xfcbf0001u;
    SCE->REG_24H = 0x0000c8d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_00H = 0x00008207u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000020fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x000034e0u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000002bu);
    HW_SCE_p_func101(0x04fca964u, 0x90725814u, 0x17b38229u, 0xc9c8f0b5u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000002bu);
    HW_SCE_p_func101(0xea8d2962u, 0x23b0c731u, 0x02063f7bu, 0x360e6545u);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0xfb3eaadcu, 0x1b4c926bu, 0x41d898b5u, 0x5d237607u);
    SCE->REG_E0H = 0x81010000u;
    SCE->REG_04H = 0x00000606u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[0] = SCE->REG_100H;
    HW_SCE_p_func100(0x15b39e7du, 0xbc172d9fu, 0x0dbd45d3u, 0x9d30cd21u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x02e08887u;
    SCE->REG_04H = 0x00000202u;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xea7a2df8u, 0x6d487225u, 0x96637959u, 0xd7948d95u);
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x00e08884u;
    SCE->REG_E0H = 0x810101c0u;
    SCE->REG_00H = 0x00002807u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[65] = SCE->REG_100H;
    OutData_PubKeyIndex[66] = SCE->REG_100H;
    OutData_PubKeyIndex[67] = SCE->REG_100H;
    OutData_PubKeyIndex[68] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (0u != SCE->REG_C8H_b.B6)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0xf17df3bdu, 0xa237d4c4u, 0x31891948u, 0x398bde44u);
    SCE->REG_18H = 0x00000004u;
    SCE->REG_24H = 0x00004404u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00004804u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000u;
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x00e087b7u;
    SCE->REG_04H = 0x00000202u;
    for(iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x77aecc1au, 0xc4e61c3cu, 0x32de60c5u, 0xc40e7285u);
    SCE->REG_104H = 0x00000352u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x000089c5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000010u);
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[133] = SCE->REG_100H;
    OutData_PubKeyIndex[134] = SCE->REG_100H;
    OutData_PubKeyIndex[135] = SCE->REG_100H;
    OutData_PubKeyIndex[136] = SCE->REG_100H;
    HW_SCE_p_func100(0xb77e9d11u, 0x739cdbb4u, 0xb03798c4u, 0x99c1079bu);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_00H = 0x00008207u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000020fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x000034e0u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000fdu);
    HW_SCE_p_func101(0x394f8441u, 0xfba13dc3u, 0x22815382u, 0xff49cec6u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x0000000du;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000fdu);
    HW_SCE_p_func101(0x66692d56u, 0x5e6c77cau, 0xed7b634fu, 0x905615c9u);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x35fa4854u, 0xcef1ec09u, 0xab49a001u, 0x599a6c24u);
    SCE->REG_E0H = 0x81010000u;
    SCE->REG_04H = 0x00000606u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[0] = SCE->REG_100H;
    HW_SCE_p_func100(0x06f73d5fu, 0x532f17d5u, 0x54dc5af0u, 0x6eee362du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x02e087b7u;
    SCE->REG_04H = 0x00000202u;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xbecdb75cu, 0xbca8b94eu, 0x0b91504cu, 0xc1f7fc25u);
    SCE->REG_00H = 0x00012103u;
    SCE->REG_104H = 0x00000031u;
    SCE->REG_B0H = 0x00000f00u;
    SCE->REG_A4H = 0x42f097bfu;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x00e087b7u;
    SCE->REG_04H = 0x00000202u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[68];
    SCE->REG_100H = S_HEAP[69];
    SCE->REG_100H = S_HEAP[70];
    SCE->REG_100H = S_HEAP[71];
    for (iLoop = 64; iLoop < 124 ; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_HEAP[iLoop+8 + 0];
        SCE->REG_100H = S_HEAP[iLoop+8 + 1];
        SCE->REG_100H = S_HEAP[iLoop+8 + 2];
        SCE->REG_100H = S_HEAP[iLoop+8 + 3];
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    SCE->REG_104H = 0x00000000u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_C8H_b.B6)
    {
        /* waiting */
    }
    SCE->REG_A4H = 0x400017bdu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[132];
    SCE->REG_100H = S_HEAP[133];
    SCE->REG_100H = S_HEAP[134];
    SCE->REG_100H = S_HEAP[135];
    SCE->REG_A4H = 0x00800c45u;
    SCE->REG_00H = 0x00001113u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x9ac4e83au, 0xf48e1713u, 0xe59c8f74u, 0xb22f3529u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x00e087b7u;
    SCE->REG_04H = 0x00000202u;
    for(iLoop=128; iLoop<192; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x36d14ec8u, 0xb8c807a7u, 0x74d82cfdu, 0x7a62a60bu);
    SCE->REG_104H = 0x00000352u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x000089c5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000030u);
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[193] = SCE->REG_100H;
    OutData_PrivKeyIndex[194] = SCE->REG_100H;
    OutData_PrivKeyIndex[195] = SCE->REG_100H;
    OutData_PrivKeyIndex[196] = SCE->REG_100H;
    HW_SCE_p_func102(0x772f0564u, 0x25d380e3u, 0x92a87dc9u, 0x37b7f321u);
    SCE->REG_1BCH = 0x00000040u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p2b_r2.prc
***********************************************************************************************************************/
