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

fsp_err_t HW_SCE_EcdsaSignatureVerificationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_MsgDgst, const uint32_t *InData_Signature)
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
    SCE->REG_84H = 0x0000f101u;
    SCE->REG_108H = 0x00000000u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_104H = 0x00001768u;
    SCE->REG_E0H = 0x8098001eu;
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Signature[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MsgDgst[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
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
        SCE->REG_ECH = 0x38000fffu;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        SCE->REG_ECH = 0x0000a7c0u;
        SCE->REG_ECH = 0x00000020u;
    }
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
    HW_SCE_p_func100(0xb3a4bb56u, 0x412a388cu, 0x4f9be231u, 0xe3706b28u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x0ea78a51u, 0xe36bea34u, 0xc54dd04cu, 0xa2ffc22au);
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
        SCE->REG_28H = 0x00870001u;
        HW_SCE_p_func100(0x55305e12u, 0x530c0fb5u, 0x1c13599eu, 0x4532a352u);
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
        HW_SCE_p_func100(0x8f8943c0u, 0x598761b3u, 0xe9847b6eu, 0x8453ab3eu);
        HW_SCE_p_func070_r2(OFS_ADR);
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000bcd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00000bffu;
        SCE->REG_E0H = 0x8190001fu;
        SCE->REG_00H = 0x00003823u;
        SCE->REG_2CH = 0x00000015u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_00H = 0x00003823u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000140u;
        SCE->REG_E0H = 0x8088001fu;
        SCE->REG_00H = 0x00008323u;
        SCE->REG_2CH = 0x00000024u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000070d0u;
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
        SCE->REG_24H = 0x00008cd0u;
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
        SCE->REG_24H = 0x000060c1u;
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
        SCE->REG_24H = 0x00000d91u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00u;
        SCE->REG_1CH = 0x00210000u;
        SCE->REG_24H = 0x00000dc0u;
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
        SCE->REG_24H = 0x00001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00u;
        SCE->REG_1CH = 0x00210000u;
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
        SCE->REG_1CH = 0x00001f00u;
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0x590b209bu, 0xc82029c5u, 0x60cf2f49u, 0x6b7025c3u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xf6aee8c1u, 0x440d430du, 0x36ee5c4eu, 0x8625dc70u);
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
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000100u;
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
                    HW_SCE_p_func100(0x2201181cu, 0x9eb62239u, 0x8daf8909u, 0x42c0e057u);
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
                        HW_SCE_p_func101(0xce3c73fbu, 0x286447d7u, 0x58f537c8u, 0xfb51f8bfu);
                    }
                    else
                    {
                        HW_SCE_p_func101(0xfcf15e4du, 0xa058aa75u, 0x613ad247u, 0x512b85e6u);
                    }
                }
                SCE->REG_ECH = 0x000027e1u;
                HW_SCE_p_func101(0x3c499c8au, 0x6ea4ec8fu, 0x030ea18cu, 0x70d4f24fu);
            }
            SCE->REG_ECH = 0x00008be0u;
            SCE->REG_ECH = 0x00000120u;
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            HW_SCE_p_func100(0x7d936becu, 0xe1c658d1u, 0xd42327a8u, 0x9d36429eu);
            SCE->REG_24H = 0x00001dc0u;
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
            SCE->REG_2CH = 0x00000011u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000094au;
            SCE->REG_E0H = 0x8088000au;
            SCE->REG_00H = 0x00008323u;
            SCE->REG_2CH = 0x00000023u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
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
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000094d0u;
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
            SCE->REG_24H = 0x0000e0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008u;
            SCE->REG_24H = 0x8000d4d0u;
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
            SCE->REG_34H = 0x00000003u;
            SCE->REG_24H = 0x800048d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
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
            SCE->REG_ECH = 0x0000b540u;
            SCE->REG_ECH = 0x00000040u;
            SCE->REG_E0H = 0x8088000au;
            SCE->REG_00H = 0x00008323u;
            SCE->REG_2CH = 0x00000025u;
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
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000100u;
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
            SCE->REG_ECH = 0x000000f1u;
            SCE->REG_ECH = 0x0000377cu;
            SCE->REG_ECH = 0x00000b9cu;
            HW_SCE_p_func100(0x60e62d54u, 0x797b21c9u, 0x1e8cd1c3u, 0xd81aced7u);
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
                HW_SCE_p_func101(0xf6ba2066u, 0x71c4054cu, 0x82369773u, 0x52f78ec2u);
                HW_SCE_p_func302();
                if (S_RAM[0] == 0x00000001)
                {
                    break;
                }
                HW_SCE_p_func101(0x3bbc5587u, 0x0ec4b9dfu, 0xfc6d0c6au, 0x4b97b23cu);
            }
            SCE->REG_ECH = 0x00000a73u;
            SCE->REG_ECH = 0x0000b660u;
            SCE->REG_ECH = 0x00000040u;
            SCE->REG_E0H = 0x81880013u;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x0000001au;
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
            SCE->REG_24H = 0x00000591u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001f00u;
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0x55b2bd60u, 0x788ffd90u, 0x69408616u, 0x9bf25968u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xbc5993a1u, 0x4614565bu, 0x1e1848c2u, 0xbf3b91dfu);
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
                SCE->REG_34H = 0x00000003u;
                SCE->REG_24H = 0x800048d0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800068d0u;
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
                SCE->REG_ECH = 0x0000b7e0u;
                SCE->REG_ECH = 0x00000100u;
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
                        HW_SCE_p_func100(0x9392224cu, 0x4611f3adu, 0x503f7b17u, 0x7545889cu);
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
                            HW_SCE_p_func101(0xa70971feu, 0x5d3a322cu, 0xdd3f98e8u, 0x8d873476u);
                        }
                        else
                        {
                            HW_SCE_p_func101(0xdd8687b0u, 0xce2201d7u, 0xba53b658u, 0xeab59d81u);
                        }
                    }
                    SCE->REG_ECH = 0x000027e1u;
                    HW_SCE_p_func101(0x2957d6f7u, 0x2f37a3cdu, 0x94d16a5fu, 0x7d4f21fcu);
                }
                SCE->REG_ECH = 0x00008be0u;
                SCE->REG_ECH = 0x00000120u;
                SCE->REG_ECH = 0x00007c1fu;
                SCE->REG_1CH = 0x00602000u;
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x80000dc0u;
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
                SCE->REG_24H = 0x0000a0c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000008u;
                SCE->REG_24H = 0x800011c0u;
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
                SCE->REG_34H = 0x00000008u;
                SCE->REG_24H = 0x800015c0u;
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
                SCE->REG_24H = 0x000015c0u;
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
                SCE->REG_24H = 0x000009c0u;
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
                SCE->REG_24H = 0x000011c0u;
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
                SCE->REG_ECH = 0x0000379bu;
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
                SCE->REG_100H = change_endian_long(0x000000f1u);
                HW_SCE_p_func101(0xa2143480u, 0xab721c7du, 0x400794fbu, 0x90b7f286u);
                HW_SCE_p_func043();
                HW_SCE_p_func075_r1();
                SCE->REG_ECH = 0x000034feu;
                SCE->REG_104H = 0x00000058u;
                SCE->REG_E0H = 0x800103a0u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f1u);
                HW_SCE_p_func101(0xdfb7aecbu, 0x249b9e49u, 0xbd4f48f9u, 0x09ce82beu);
                HW_SCE_p_func044();
                SCE->REG_104H = 0x00000052u;
                SCE->REG_C4H = 0x00040804u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_104H = 0x00000f62u;
                SCE->REG_D0H = 0x40000300u;
                SCE->REG_C4H = 0x02e08887u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[1];
                SCE->REG_100H = InData_KeyIndex[2];
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_100H = InData_KeyIndex[4];
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[5];
                SCE->REG_100H = InData_KeyIndex[6];
                SCE->REG_100H = InData_KeyIndex[7];
                SCE->REG_100H = InData_KeyIndex[8];
                SCE->REG_00H = 0x00003223u;
                SCE->REG_2CH = 0x00000010u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[9];
                SCE->REG_100H = InData_KeyIndex[10];
                SCE->REG_100H = InData_KeyIndex[11];
                SCE->REG_100H = InData_KeyIndex[12];
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[13];
                SCE->REG_100H = InData_KeyIndex[14];
                SCE->REG_100H = InData_KeyIndex[15];
                SCE->REG_100H = InData_KeyIndex[16];
                SCE->REG_00H = 0x00003223u;
                SCE->REG_2CH = 0x0000001bu;
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
                SCE->REG_100H = InData_KeyIndex[17];
                SCE->REG_100H = InData_KeyIndex[18];
                SCE->REG_100H = InData_KeyIndex[19];
                SCE->REG_100H = InData_KeyIndex[20];
                SCE->REG_C4H = 0x00900c45u;
                SCE->REG_00H = 0x00002213u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func100(0xcde594d5u, 0x132b8725u, 0xbc346b76u, 0xb366788au);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x1f11c475u, 0x7cc92153u, 0x52eadf9eu, 0xee64c69bu);
                    SCE->REG_1BCH = 0x00000040u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                }
                else
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
                    SCE->REG_24H = 0x000011c0u;
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
                    SCE->REG_24H = 0x80008cd0u;
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
                    SCE->REG_24H = 0x000080c1u;
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
                    SCE->REG_34H = 0x00000800u;
                    SCE->REG_24H = 0x800060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x800011c0u;
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
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x800009c0u;
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
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x80000dc0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000800u;
                    SCE->REG_24H = 0x8000a0c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_ECH = 0x0000b540u;
                    SCE->REG_ECH = 0x00000080u;
                    SCE->REG_E0H = 0x8088000au;
                    SCE->REG_00H = 0x00008323u;
                    SCE->REG_2CH = 0x00000022u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800u;
                    SCE->REG_ECH = 0x0000b540u;
                    SCE->REG_ECH = 0x000000C0u;
                    SCE->REG_E0H = 0x8088000au;
                    SCE->REG_00H = 0x00008323u;
                    SCE->REG_2CH = 0x00000023u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800u;
                    SCE->REG_ECH = 0x0000b7e0u;
                    SCE->REG_ECH = 0x00000100u;
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
                    SCE->REG_ECH = 0x00000001u;
                    SCE->REG_ECH = 0x00000b9cu;
                    HW_SCE_p_func100(0x26f45b8bu, 0x622dcf12u, 0x37ebeb9au, 0x07bc3f54u);
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
                        HW_SCE_p_func101(0xfa6fa228u, 0xead297ceu, 0x1fc0b519u, 0x12a298ecu);
                        HW_SCE_p_func302();
                        if (S_RAM[0] == 0x00000001)
                        {
                            break;
                        }
                        HW_SCE_p_func101(0xf284d5a3u, 0x6e54b6ddu, 0x2b8ba9d2u, 0x19948033u);
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
                    HW_SCE_p_func100(0xfff9e72au, 0x6a9b2259u, 0x9b87326cu, 0x07f21f83u);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func102(0x7bf8560fu, 0x90b8357bu, 0x986d0b9eu, 0x78964becu);
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
                        SCE->REG_ECH = 0x0000b660u;
                        SCE->REG_ECH = 0x00000080u;
                        SCE->REG_E0H = 0x81880013u;
                        SCE->REG_00H = 0x00003823u;
                        SCE->REG_2CH = 0x0000001au;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        SCE->REG_ECH = 0x0000b660u;
                        SCE->REG_ECH = 0x000000C0u;
                        SCE->REG_E0H = 0x81880013u;
                        SCE->REG_00H = 0x00003823u;
                        SCE->REG_2CH = 0x0000001bu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        SCE->REG_24H = 0x00009cd0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
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
                        SCE->REG_24H = 0x000070d0u;
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
                        SCE->REG_24H = 0x800048d0u;
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
                        SCE->REG_34H = 0x00000008u;
                        SCE->REG_24H = 0x800011c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000200u;
                        SCE->REG_24H = 0x80000a41u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000008u;
                        SCE->REG_24H = 0x800011c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000200u;
                        SCE->REG_24H = 0x80000951u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000002u;
                        SCE->REG_24H = 0x80004cd0u;
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
                        SCE->REG_34H = 0x00000280u;
                        SCE->REG_24H = 0x800019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000080u;
                        SCE->REG_24H = 0x800080c1u;
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
                        SCE->REG_24H = 0x0000e0c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
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
                        SCE->REG_34H = 0x00000200u;
                        SCE->REG_24H = 0x900019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000280u;
                        SCE->REG_24H = 0x800019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000008u;
                        SCE->REG_24H = 0x800015c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000941u;
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
                        SCE->REG_34H = 0x00000008u;
                        SCE->REG_24H = 0x800015c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000951u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000080u;
                        SCE->REG_24H = 0x800040c2u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000200u;
                        SCE->REG_24H = 0x800012c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00008cd0u;
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
                        SCE->REG_24H = 0x00008cd0u;
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
                        SCE->REG_24H = 0x00000951u;
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
                        SCE->REG_24H = 0x800080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000149u;
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
                        SCE->REG_24H = 0x000009c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000d51u;
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
                        SCE->REG_34H = 0x00000080u;
                        SCE->REG_24H = 0x800080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000080u;
                        SCE->REG_24H = 0x800060c2u;
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
                        SCE->REG_24H = 0x000009c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000d51u;
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
                        SCE->REG_24H = 0x00000145u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000800u;
                        SCE->REG_24H = 0x8000a0c1u;
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
                        SCE->REG_1CH = 0x00001f00u;
                        SCE->REG_1CH = 0x00210000u;
                        HW_SCE_p_func100(0xf8dae94fu, 0x10eb8740u, 0xd99a2a7fu, 0x5994642eu);
                        SCE->REG_1CH = 0x00400000u;
                        SCE->REG_1D0H = 0x00000000u;
                        if (1u == (SCE->REG_1CH_b.B22))
                        {
                            HW_SCE_p_func102(0x3ebc5aabu, 0xb88b7fd2u, 0x30e22266u, 0xd261e34du);
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
                            SCE->REG_34H = 0x00000003u;
                            SCE->REG_24H = 0x800048d0u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_34H = 0x00000800u;
                            SCE->REG_24H = 0x800068d0u;
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
                            SCE->REG_ECH = 0x0000b7e0u;
                            SCE->REG_ECH = 0x00000100u;
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
                                    HW_SCE_p_func100(0xa674de4bu, 0x7cfddb14u, 0x04a7a5f9u, 0xe48f30a2u);
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
                                        HW_SCE_p_func101(0x7073dd36u, 0x2dd6f3acu, 0xc91b5027u, 0xd78a65c5u);
                                    }
                                    else
                                    {
                                        HW_SCE_p_func101(0x92571603u, 0xfcfec157u, 0x36856296u, 0x6a9eb6b0u);
                                    }
                                }
                                SCE->REG_ECH = 0x000027e1u;
                                HW_SCE_p_func101(0x953447d6u, 0x130e6df0u, 0x513a9531u, 0xcf569436u);
                            }
                            SCE->REG_ECH = 0x00008be0u;
                            SCE->REG_ECH = 0x00000120u;
                            SCE->REG_ECH = 0x00007c1fu;
                            SCE->REG_1CH = 0x00602000u;
                            SCE->REG_34H = 0x00000002u;
                            SCE->REG_24H = 0x80000dc0u;
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
                            SCE->REG_24H = 0x0000a0c1u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_34H = 0x00000008u;
                            SCE->REG_24H = 0x800011c0u;
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
                            SCE->REG_ECH = 0x0000b7e0u;
                            SCE->REG_ECH = 0x00000140u;
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
                            SCE->REG_24H = 0x000088d0u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x00009004u;
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
                            SCE->REG_24H = 0x000040c1u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_ECH = 0x0000b660u;
                            SCE->REG_ECH = 0x00000000u;
                            SCE->REG_E0H = 0x81880013u;
                            SCE->REG_00H = 0x00003823u;
                            SCE->REG_2CH = 0x00000014u;
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
                            SCE->REG_24H = 0x00001991u;
                            /* WAIT_LOOP */
                            while (0u != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_1CH = 0x00001f00u;
                            SCE->REG_1CH = 0x00210000u;
                            SCE->REG_24H = 0x000019c0u;
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
                            SCE->REG_1CH = 0x00001f00u;
                            SCE->REG_1CH = 0x00210000u;
                            HW_SCE_p_func100(0x0407c0bdu, 0x083c771au, 0xf0b7db95u, 0xc265fa8cu);
                            SCE->REG_1CH = 0x00400000u;
                            SCE->REG_1D0H = 0x00000000u;
                            if (1u == (SCE->REG_1CH_b.B22))
                            {
                                HW_SCE_p_func102(0x85746d5fu, 0x25b93196u, 0x52b9dc3eu, 0x9cbb1883u);
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
                                HW_SCE_p_func102(0x06dfc759u, 0xb0c6aaa4u, 0x39be31bcu, 0x42fe0748u);
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
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf1_r3.prc
***********************************************************************************************************************/
