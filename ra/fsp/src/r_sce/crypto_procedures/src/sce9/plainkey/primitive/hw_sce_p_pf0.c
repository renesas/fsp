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

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_MsgDgst, uint32_t *OutData_Signature)
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
    if (0x0u != (SCE->REG_1B8H & 0x1eu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000f002u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010340u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010380u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000c0u;
    SCE->REG_104H = 0x00000768u;
    SCE->REG_E0H = 0x8088001eu;
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MsgDgst[iLoop + 0];
    }
    SCE->REG_ECH = 0x00000bffu;
    SCE->REG_ECH = 0x30003380u;
    SCE->REG_ECH = 0x00070020u;
    SCE->REG_ECH = 0x0000d3e0u;
    SCE->REG_ECH = 0x00030040u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x38000c00u;
    SCE->REG_ECH = 0x1000d3e0u;
    SCE->REG_ECH = 0x00050040u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x000037beu;
    SCE->REG_ECH = 0x0000a7a0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x0000383du;
    SCE->REG_ECH = 0x38001001u;
    SCE->REG_ECH = 0x1000d3e0u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x30000f5au;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d3e1u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x38000f9cu;
    SCE->REG_ECH = 0x1000d3e1u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x38008be0u;
    SCE->REG_ECH = 0x00000003u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x80b99bc2u, 0x9ee4a418u, 0x49ce3627u, 0x4351adfau);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x563d1fa8u, 0x5a5d6fb3u, 0x1459421cu, 0xe53d7473u);
        SCE->REG_1B8H = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x451200efu, 0xc8d401b7u, 0x2fa241a7u, 0xb8a7f10cu);
        SCE->REG_28H = 0x00870001u;
        SCE->REG_ECH = 0x30003340u;
        SCE->REG_ECH = 0x00050020u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x000004C8u;
        SCE->REG_ECH = 0x00030040u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x0000031Cu;
        SCE->REG_ECH = 0x00070040u;
        SCE->REG_ECH = 0x30003380u;
        SCE->REG_ECH = 0x00070020u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_ECH = 0x00030040u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x0000013Cu;
        SCE->REG_ECH = 0x00050040u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x000001F8u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_E0H = 0x81010000u;
        SCE->REG_04H = 0x00000606u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        OFS_ADR = S_RAM[0];
        HW_SCE_p_func100(0xf071916eu, 0xbb83fee2u, 0xd34567d9u, 0x5f50077eu);
        HW_SCE_p_func070_r2(OFS_ADR);
        HW_SCE_p_func100(0x470710d8u, 0x2d41069cu, 0xa5095108u, 0xfec111dbu);
        SCE->REG_34H = 0x00000003u;
        SCE->REG_24H = 0x800068d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000084d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00021028u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
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
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x704a81dfu, 0xd750501au, 0xfdc7daaau, 0x30ad6bdfu);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_00H = 0x00003213u;
        SCE->REG_2CH = 0x00000011u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
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
        SCE->REG_24H = 0x00001228u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
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
        SCE->REG_24H = 0x0000a0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xef5f6f61u, 0x8b7b541du, 0x60a83d4cu, 0xe6fcc2f3u);
        HW_SCE_p_func071_r2(OFS_ADR);
        SCE->REG_34H = 0x00000802u;
        SCE->REG_24H = 0x800088d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000802u;
        SCE->REG_24H = 0x8000acd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000040u;
        SCE->REG_E0H = 0x8088001fu;
        SCE->REG_00H = 0x00008323u;
        SCE->REG_2CH = 0x00000024u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x00001dc0u;
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
        SCE->REG_24H = 0x000084d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00021028u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
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
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000c0c1u;
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
        SCE->REG_24H = 0x00001028u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
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
        SCE->REG_24H = 0x0000e0c1u;
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
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_E0H = 0x8088001fu;
        SCE->REG_00H = 0x00008323u;
        SCE->REG_2CH = 0x00000020u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x00005cd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00000bffu;
        SCE->REG_E0H = 0x8088001fu;
        SCE->REG_00H = 0x00008323u;
        SCE->REG_2CH = 0x00000021u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x00000842u;
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x00000004u;
        SCE->REG_ECH = 0x0000b480u;
        SCE->REG_ECH = 0x00000100u;
        SCE->REG_ECH = 0x0000b7a0u;
        SCE->REG_ECH = 0x000000f0u;
        SCE->REG_ECH = 0x0000373cu;
        SCE->REG_ECH = 0x00000b9cu;
        HW_SCE_p_func100(0x1d4ac2e4u, 0x51589b8eu, 0x542a868au, 0x975cf1b6u);
        SCE->REG_E0H = 0x81010380u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<256;iLoop=iLoop+1)
        {
            HW_SCE_p_func101(0x78e307d7u, 0x63d014e3u, 0x594119d3u, 0xc6df9701u);
            HW_SCE_p_func300();
            if (S_RAM[0] == 0x00000001)
            {
                break;
            }
            HW_SCE_p_func101(0x6db06aceu, 0xebbad615u, 0x7726e7c9u, 0x4983ea35u);
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
        SCE->REG_1CH = 0x00001f00u;
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0xa9085fbeu, 0x25a8489cu, 0xe5f22119u, 0x0e253310u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x85ca9aa5u, 0x59e5f5b6u, 0x4e2034b2u, 0x9a0a1c47u);
            SCE->REG_1B8H = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_24H = 0x00001dc0u;
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
            SCE->REG_24H = 0x000015c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x800040c1u;
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
            SCE->REG_24H = 0x00005004u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00008404u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b420u;
            SCE->REG_ECH = 0x00000004u;
            SCE->REG_ECH = 0x00000bffu;
            SCE->REG_E0H = 0x8088001fu;
            SCE->REG_00H = 0x00008323u;
            SCE->REG_2CH = 0x00000021u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            for(iLoop=0; iLoop<8; iLoop=iLoop+1)
            {
                SCE->REG_ECH = 0x0000381fu;
                for(jLoop=0; jLoop<32; jLoop=jLoop+1)
                {
                    SCE->REG_24H = 0x0000102cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
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
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_ECH = 0x3800d81fu;
                    SCE->REG_E0H = 0x00000080u;
                    SCE->REG_1CH = 0x00A60000u;
                    SCE->REG_ECH = 0x00016c00u;
                    HW_SCE_p_func100(0x32739d60u, 0x0e2671edu, 0x23998dfeu, 0x4f6c4200u);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        SCE->REG_24H = 0x0000082cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
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
                        SCE->REG_24H = 0x000080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        HW_SCE_p_func101(0x8258f1e6u, 0x553b5587u, 0x4f1e0975u, 0xd75763f4u);
                    }
                    else
                    {
                        HW_SCE_p_func101(0x539fd0d3u, 0xea3031bau, 0x97e22ba0u, 0x5000a199u);
                    }
                }
                SCE->REG_ECH = 0x000027e1u;
                HW_SCE_p_func101(0x5919a370u, 0x0f6d04c5u, 0xce11e96au, 0x4d2ef3fau);
            }
            SCE->REG_ECH = 0x00008be0u;
            SCE->REG_ECH = 0x00000020u;
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            SCE->REG_24H = 0x00001028u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_E0H = 0x8188001fu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000012u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x0000082cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008u;
            SCE->REG_24H = 0x800012c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c2u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000a2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x0000082cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x0000082cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x800060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008u;
            SCE->REG_24H = 0x800016c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c2u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000e2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000e2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000040u;
            SCE->REG_E0H = 0x8188001fu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000014u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_24H = 0x000084d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00021028u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x8000c0c1u;
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
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x8000ecd0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a8d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000020u;
            SCE->REG_24H = 0x80001dc0u;
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
            SCE->REG_24H = 0x00000a2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000828u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
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
            SCE->REG_1CH = 0x00001f00u;
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0xc94388e0u, 0x9a7e6cb9u, 0xce5c4ac7u, 0xb132c2d9u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x117e7a37u, 0xe9611638u, 0xe3b97e76u, 0xadd63588u);
                SCE->REG_1B8H = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                SCE->REG_24H = 0x00000ac0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800060c2u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x800009c0u;
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
                SCE->REG_24H = 0x0000a0c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00005004u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00008404u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b420u;
                SCE->REG_ECH = 0x00000004u;
                SCE->REG_ECH = 0x00000bffu;
                SCE->REG_E0H = 0x8088001fu;
                SCE->REG_00H = 0x00008323u;
                SCE->REG_2CH = 0x00000021u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                for(iLoop=0; iLoop<8; iLoop=iLoop+1)
                {
                    SCE->REG_ECH = 0x0000381fu;
                    for(jLoop=0; jLoop<32; jLoop=jLoop+1)
                    {
                        SCE->REG_24H = 0x0000102cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
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
                        SCE->REG_24H = 0x000080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_ECH = 0x3800d81fu;
                        SCE->REG_E0H = 0x00000080u;
                        SCE->REG_1CH = 0x00A60000u;
                        SCE->REG_ECH = 0x00016c00u;
                        HW_SCE_p_func100(0xf488209bu, 0x8754f3d9u, 0x9dcac910u, 0x6a315209u);
                        SCE->REG_1CH = 0x00400000u;
                        SCE->REG_1D0H = 0x00000000u;
                        if (1u == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_24H = 0x0000082cu;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x100019b1u;
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
                            SCE->REG_24H = 0x000080c1u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            HW_SCE_p_func101(0x564da9c0u, 0x175afa15u, 0xdb42594eu, 0x2a5f439fu);
                        }
                        else
                        {
                            HW_SCE_p_func101(0x707f79d8u, 0xf36e9205u, 0xc8bbbdfcu, 0xa87d56c3u);
                        }
                    }
                    SCE->REG_ECH = 0x000027e1u;
                    HW_SCE_p_func101(0x4e12ae86u, 0x9ec13781u, 0x54edd46au, 0x1512b2b6u);
                }
                SCE->REG_ECH = 0x00008be0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_ECH = 0x00007c1fu;
                SCE->REG_1CH = 0x00602000u;
                SCE->REG_24H = 0x00001028u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1u;
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
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7e0u;
                SCE->REG_ECH = 0x000000c0u;
                SCE->REG_E0H = 0x8188001fu;
                SCE->REG_00H = 0x00003823u;
                SCE->REG_2CH = 0x00000011u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_34H = 0x00000020u;
                SCE->REG_24H = 0x80001dc0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x80000a2cu;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1u;
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
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x800009c0u;
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
                SCE->REG_34H = 0x00000020u;
                SCE->REG_24H = 0x80001dc0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_104H = 0x00000068u;
                SCE->REG_E0H = 0x800100e0u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                SCE->REG_104H = 0x00000058u;
                SCE->REG_E0H = 0x800103a0u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f0u);
                HW_SCE_p_func101(0xf1d0563cu, 0xbbd53440u, 0x9277dcaau, 0xf580df08u);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x00003799u;
                HW_SCE_p_func074_r1();
                SCE->REG_ECH = 0x000034feu;
                SCE->REG_104H = 0x00000058u;
                SCE->REG_E0H = 0x800103a0u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f0u);
                HW_SCE_p_func101(0xeb59fefbu, 0xc02a6ecbu, 0xdaec63f0u, 0x7971ef3du);
                HW_SCE_p_func044();
                SCE->REG_104H = 0x00000762u;
                SCE->REG_D0H = 0x40000100u;
                SCE->REG_C4H = 0x02f087b7u;
                SCE->REG_00H = 0x00003223u;
                SCE->REG_2CH = 0x00000018u;
                for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
                {
                    /* WAIT_LOOP */
                    while (1u != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
                    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
                    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
                    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
                }
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
                SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
                SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
                SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
                SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
                SCE->REG_C4H = 0x00900c45u;
                SCE->REG_00H = 0x00002213u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func100(0x8a7f35bcu, 0x18556ebdu, 0xb1818f43u, 0x312f0c9fu);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x508e103bu, 0x5176429fu, 0x3455628au, 0x1a3d6475u);
                    SCE->REG_1B8H = 0x00000040u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                }
                else
                {
                    SCE->REG_24H = 0x000015c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x80000c2du;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
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
                    SCE->REG_24H = 0x000060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000c2cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
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
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x8000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
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
                    SCE->REG_34H = 0x00000800u;
                    SCE->REG_24H = 0x800040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x800009c0u;
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
                    SCE->REG_1CH = 0x00001f00u;
                    SCE->REG_1CH = 0x00210000u;
                    HW_SCE_p_func100(0x54820b6au, 0x3952524au, 0xa5020e8bu, 0x902155ffu);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func102(0xca61be04u, 0xf4a62121u, 0x1d40756bu, 0x97a09354u);
                        SCE->REG_1B8H = 0x00000040u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_18H_b.B12)
                        {
                            /* waiting */
                        }
                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        HW_SCE_p_func100(0x64195d93u, 0xee1713e1u, 0x2b8c720bu, 0xb8b83929u);
                        SCE->REG_2CH = 0x0000002bu;
                        SCE->REG_04H = 0x00000322u;
                        /* WAIT_LOOP */
                        while (1u != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_Signature[0] = SCE->REG_100H;
                        OutData_Signature[1] = SCE->REG_100H;
                        OutData_Signature[2] = SCE->REG_100H;
                        OutData_Signature[3] = SCE->REG_100H;
                        OutData_Signature[4] = SCE->REG_100H;
                        OutData_Signature[5] = SCE->REG_100H;
                        OutData_Signature[6] = SCE->REG_100H;
                        OutData_Signature[7] = SCE->REG_100H;
                        HW_SCE_p_func100(0x7f837de5u, 0x2783bdc9u, 0x09f9efa6u, 0xdc30d0abu);
                        SCE->REG_2CH = 0x0000002au;
                        SCE->REG_04H = 0x00000322u;
                        /* WAIT_LOOP */
                        while (1u != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_Signature[8] = SCE->REG_100H;
                        OutData_Signature[9] = SCE->REG_100H;
                        OutData_Signature[10] = SCE->REG_100H;
                        OutData_Signature[11] = SCE->REG_100H;
                        OutData_Signature[12] = SCE->REG_100H;
                        OutData_Signature[13] = SCE->REG_100H;
                        OutData_Signature[14] = SCE->REG_100H;
                        OutData_Signature[15] = SCE->REG_100H;
                        HW_SCE_p_func102(0x582e0cefu, 0x9b53cdceu, 0x3672fe6du, 0x4599d89du);
                        SCE->REG_1B8H = 0x00000040u;
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
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf0_r5.prc
***********************************************************************************************************************/
