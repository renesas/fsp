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

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R)
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
    SCE->REG_84H = 0x00009b02u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_28H = 0x008b0001u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010340u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
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
    SCE->REG_100H = change_endian_long(0x0000009bu);
    HW_SCE_p_func101(0x729ab639u, 0xfe0a0d1du, 0x1e7fbae5u, 0x6d0e18e6u);
    HW_SCE_p_func043();
    HW_SCE_p_func076();
    SCE->REG_ECH = 0x000034feu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000009bu);
    HW_SCE_p_func101(0xba343e79u, 0xfe31a1f3u, 0x7dbd0515u, 0xb71fd7bau);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000b62u;
    SCE->REG_D0H = 0x40000200u;
    SCE->REG_C4H = 0x02f087b7u;
    SCE->REG_00H = 0x00003233u;
    SCE->REG_2CH = 0x00000011u;
    for (iLoop = 0; iLoop < 12; iLoop = iLoop + 4)
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
    HW_SCE_p_func100(0xa67b83a2u, 0xc869f5b9u, 0x79ac9b3au, 0x05db1be5u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xf1c61cd6u, 0x638a9ff7u, 0x30d2fddfu, 0x66063230u);
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
        HW_SCE_p_func100(0x4d994ba1u, 0x0e83dd5fu, 0x1ad395aeu, 0xf05795a2u);
        SCE->REG_ECH = 0x38000f5au;
        SCE->REG_ECH = 0x00030020u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x000002B4u;
        SCE->REG_ECH = 0x00000060u;
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x000003D8u;
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
        HW_SCE_p_func100(0x7c3c2b42u, 0x77da4ba5u, 0xdd828a5fu, 0xf0ae4b81u);
        HW_SCE_p_func027_r2(OFS_ADR);
        HW_SCE_p_func100(0xada38979u, 0x5574dcfbu, 0xcbcebb86u, 0x44cc9663u);
        SCE->REG_24H = 0x0000dcd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000820u;
        SCE->REG_24H = 0x80009cd0u;
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
        SCE->REG_24H = 0x00004404u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e8d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000808u;
        SCE->REG_24H = 0x8000f0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_2CH = 0x00000010u;
        SCE->REG_104H = 0x00000b67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[0];
        SCE->REG_100H = InData_PubKey[1];
        SCE->REG_100H = InData_PubKey[2];
        SCE->REG_100H = InData_PubKey[3];
        SCE->REG_100H = InData_PubKey[4];
        SCE->REG_100H = InData_PubKey[5];
        SCE->REG_100H = InData_PubKey[6];
        SCE->REG_100H = InData_PubKey[7];
        SCE->REG_100H = InData_PubKey[8];
        SCE->REG_100H = InData_PubKey[9];
        SCE->REG_100H = InData_PubKey[10];
        SCE->REG_100H = InData_PubKey[11];
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
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x800040c1u;
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
        SCE->REG_2CH = 0x00000010u;
        SCE->REG_104H = 0x00000b67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[12];
        SCE->REG_100H = InData_PubKey[13];
        SCE->REG_100H = InData_PubKey[14];
        SCE->REG_100H = InData_PubKey[15];
        SCE->REG_100H = InData_PubKey[16];
        SCE->REG_100H = InData_PubKey[17];
        SCE->REG_100H = InData_PubKey[18];
        SCE->REG_100H = InData_PubKey[19];
        SCE->REG_100H = InData_PubKey[20];
        SCE->REG_100H = InData_PubKey[21];
        SCE->REG_100H = InData_PubKey[22];
        SCE->REG_100H = InData_PubKey[23];
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
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x800060c1u;
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
        SCE->REG_ECH = 0x00000bffu;
        SCE->REG_E0H = 0x808c001fu;
        SCE->REG_00H = 0x00008333u;
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
        SCE->REG_ECH = 0x00000180u;
        SCE->REG_ECH = 0x0000b7a0u;
        SCE->REG_ECH = 0x0000009bu;
        SCE->REG_ECH = 0x00000b9cu;
        SCE->REG_E0H = 0x81010380u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<384;iLoop=iLoop+1)
        {
            HW_SCE_p_func101(0xd1a20304u, 0x7ec5a832u, 0xfe786d80u, 0x8db0ff21u);
            HW_SCE_p_func300();
            if (S_RAM[0] == 0x00000001)
            {
                break;
            }
            HW_SCE_p_func101(0xd89c8381u, 0xd1f4a61cu, 0x434fe417u, 0x7150d01du);
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
        HW_SCE_p_func100(0x62b875dcu, 0x77b1bd44u, 0x9da356ddu, 0x268018dbu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x142493c0u, 0x7f78d4e0u, 0xc34d38b2u, 0x5166c60eu);
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
            SCE->REG_E0H = 0x808c001fu;
            SCE->REG_00H = 0x00008333u;
            SCE->REG_2CH = 0x00000021u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            for(iLoop=0; iLoop<12; iLoop=iLoop+1)
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
                    HW_SCE_p_func100(0x6dfda009u, 0xdb9d8c6fu, 0x5f3558dfu, 0x4eeb90f1u);
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
                        HW_SCE_p_func101(0x97eb165fu, 0x003b8d10u, 0xd9f32031u, 0xa635451cu);
                    }
                    else
                    {
                        HW_SCE_p_func101(0x3775974eu, 0xfd8b4302u, 0x33a3cd37u, 0x5bcc8a49u);
                    }
                }
                SCE->REG_ECH = 0x000027e1u;
                HW_SCE_p_func101(0xa93bfadeu, 0x9ae6845au, 0x6ec11109u, 0x707f0125u);
            }
            SCE->REG_ECH = 0x00008be0u;
            SCE->REG_ECH = 0x00000030u;
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            HW_SCE_p_func301();
            HW_SCE_p_func100(0x036d9c54u, 0xe4a2ebc2u, 0x357cde20u, 0xd1165e27u);
            SCE->REG_2CH = 0x00000022u;
            SCE->REG_04H = 0x00000332u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_R[0] = SCE->REG_100H;
            OutData_R[1] = SCE->REG_100H;
            OutData_R[2] = SCE->REG_100H;
            OutData_R[3] = SCE->REG_100H;
            OutData_R[4] = SCE->REG_100H;
            OutData_R[5] = SCE->REG_100H;
            OutData_R[6] = SCE->REG_100H;
            OutData_R[7] = SCE->REG_100H;
            OutData_R[8] = SCE->REG_100H;
            OutData_R[9] = SCE->REG_100H;
            OutData_R[10] = SCE->REG_100H;
            OutData_R[11] = SCE->REG_100H;
            HW_SCE_p_func100(0x05a57fffu, 0x0c4047f5u, 0xb8df91a5u, 0x33f572e9u);
            SCE->REG_2CH = 0x00000023u;
            SCE->REG_04H = 0x00000332u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_R[12] = SCE->REG_100H;
            OutData_R[13] = SCE->REG_100H;
            OutData_R[14] = SCE->REG_100H;
            OutData_R[15] = SCE->REG_100H;
            OutData_R[16] = SCE->REG_100H;
            OutData_R[17] = SCE->REG_100H;
            OutData_R[18] = SCE->REG_100H;
            OutData_R[19] = SCE->REG_100H;
            OutData_R[20] = SCE->REG_100H;
            OutData_R[21] = SCE->REG_100H;
            OutData_R[22] = SCE->REG_100H;
            OutData_R[23] = SCE->REG_100H;
            HW_SCE_p_func102(0xd6535d3fu, 0x32ed02a4u, 0xf2ad998eu, 0x83ac46d5u);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p9b_r3.prc
***********************************************************************************************************************/
