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

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R)
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
    SCE->REG_84H = 0x00009a02u;
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
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_104H = 0x00000f68u;
    SCE->REG_E0H = 0x8090001eu;
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 2; iLoop = iLoop + 1)
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
    HW_SCE_p_func100(0x3965c2d2u, 0x82748bcdu, 0xc40cd983u, 0x4cfda6a2u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x57ec98c4u, 0x37655b01u, 0xbd5955d6u, 0x4b280573u);
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
        SCE->REG_100H = change_endian_long(0x0000009au);
        HW_SCE_p_func101(0x3aa30067u, 0x566ddb9au, 0x5cee2e76u, 0x4083c512u);
        HW_SCE_p_func043();
        HW_SCE_p_func074_r1();
        SCE->REG_ECH = 0x000034feu;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000009au);
        HW_SCE_p_func101(0x832ab6cbu, 0xf2fc811cu, 0x465c0d18u, 0x085b85d7u);
        HW_SCE_p_func044();
        SCE->REG_104H = 0x00000762u;
        SCE->REG_D0H = 0x40000100u;
        SCE->REG_C4H = 0x02f087b7u;
        SCE->REG_00H = 0x00003223u;
        SCE->REG_2CH = 0x00000011u;
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
        HW_SCE_p_func100(0x3d38fe92u, 0x745739efu, 0x96383b59u, 0x1fcc88e9u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x71c33e0du, 0xb021c479u, 0x6b63089eu, 0x571fde41u);
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
            HW_SCE_p_func100(0x86959a7cu, 0xa4eed527u, 0xeeec7768u, 0xff9ea61bu);
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
            HW_SCE_p_func100(0x1ed97c6fu, 0x109d0bc2u, 0xfa651f26u, 0xf32e898eu);
            HW_SCE_p_func070_r2(OFS_ADR);
            HW_SCE_p_func100(0xd1fe94f1u, 0x147cf197u, 0xf1f0ff33u, 0xab3dc8c1u);
            SCE->REG_34H = 0x00000003u;
            SCE->REG_24H = 0x800068d0u;
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
            SCE->REG_ECH = 0x00000bffu;
            SCE->REG_E0H = 0x8188001fu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000010u;
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
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000020u;
            SCE->REG_E0H = 0x8188001fu;
            SCE->REG_00H = 0x00003823u;
            SCE->REG_2CH = 0x00000010u;
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
            SCE->REG_ECH = 0x0000009au;
            SCE->REG_ECH = 0x0000377cu;
            SCE->REG_ECH = 0x00000b9cu;
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
                HW_SCE_p_func101(0xae6f33b4u, 0x064fc23eu, 0x7a4c092bu, 0xd9ff2a9eu);
                HW_SCE_p_func300();
                if (S_RAM[0] == 0x00000001)
                {
                    break;
                }
                HW_SCE_p_func101(0xf42c3d9eu, 0x179e2b97u, 0xac23a620u, 0xc94db83bu);
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
            HW_SCE_p_func100(0xfa0e2dd1u, 0x0d9f7059u, 0xe5c47b66u, 0x1267bf4fu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xd1535a62u, 0x712ffe15u, 0x35a7c325u, 0xaec12d1fu);
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
                        HW_SCE_p_func100(0xbfa07cbbu, 0x892d135cu, 0x6f39790au, 0x1ebe4fcbu);
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
                            HW_SCE_p_func101(0xcd606843u, 0x98cbb1f5u, 0x4052dda2u, 0x61b8fdd1u);
                        }
                        else
                        {
                            HW_SCE_p_func101(0x0ce52ca3u, 0x9ceedb58u, 0x5f26d152u, 0x98cc1206u);
                        }
                    }
                    SCE->REG_ECH = 0x000027e1u;
                    HW_SCE_p_func101(0x84355fe5u, 0xb797abfcu, 0xc5bc5e73u, 0xf3cdaec0u);
                }
                SCE->REG_ECH = 0x00008be0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_ECH = 0x00007c1fu;
                SCE->REG_1CH = 0x00602000u;
                HW_SCE_p_func301();
                HW_SCE_p_func100(0x0c5448bdu, 0xe38e6a0du, 0xbc1dc8f3u, 0xc7fa8025u);
                SCE->REG_2CH = 0x00000022u;
                SCE->REG_04H = 0x00000322u;
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
                HW_SCE_p_func100(0x11f40d9du, 0xc57e5588u, 0x575e1647u, 0x235ad24bu);
                SCE->REG_2CH = 0x00000023u;
                SCE->REG_04H = 0x00000322u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_R[8] = SCE->REG_100H;
                OutData_R[9] = SCE->REG_100H;
                OutData_R[10] = SCE->REG_100H;
                OutData_R[11] = SCE->REG_100H;
                OutData_R[12] = SCE->REG_100H;
                OutData_R[13] = SCE->REG_100H;
                OutData_R[14] = SCE->REG_100H;
                OutData_R[15] = SCE->REG_100H;
                HW_SCE_p_func102(0x69e7c53au, 0x0f736cf0u, 0xc4577672u, 0x449008dcu);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p9a_r4.prc
***********************************************************************************************************************/
