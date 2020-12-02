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

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    SCE->REG_84H = 0x0000f402u;
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
    SCE->REG_ECH = 0x3020ab80u;
    SCE->REG_ECH = 0x00000003u;
    SCE->REG_ECH = 0x00060020u;
    SCE->REG_ECH = 0x0000b780u;
    SCE->REG_ECH = 0x00000002u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000bffu;
    SCE->REG_ECH = 0x30000f5au;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d3e1u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x38000f9cu;
    SCE->REG_ECH = 0x1000d3e1u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x38008be0u;
    SCE->REG_ECH = 0x00000002u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x559bf95fu, 0xebb795a1u, 0x6dc7cb91u, 0x6ee821fbu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7fbe7fe1u, 0xa5906d5eu, 0x43e09b67u, 0x4d4cf4ffu);
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
        HW_SCE_p_func100(0xb7d91f1du, 0x1603c2b5u, 0x01b8091du, 0x6410772cu);
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
        HW_SCE_p_func100(0x93efae5eu, 0xdfb854afu, 0xeaead505u, 0xf922d3fbu);
        HW_SCE_p_func070_r2(OFS_ADR);
        HW_SCE_p_func100(0xac5929b8u, 0x9009251bu, 0x3d6d1fdfu, 0x1da02173u);
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x8000c0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00890001u;
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x88a8f9acu, 0x709537c5u, 0xef19b46au, 0xd7f9fa8fu);
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
        HW_SCE_p_func100(0xb4ea2121u, 0x3fec0e34u, 0xde041e9du, 0xb8f5bb73u);
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
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x780a5964u, 0x6e5c9e99u, 0x8c0a5040u, 0x002f258au);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_00H = 0x0000320bu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_00H = 0x0000020bu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x00007c1cu;
        SCE->REG_1CH = 0x00600000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_28H = 0x00890001u;
            HW_SCE_p_func101(0x9f1db89du, 0x0f5aa67bu, 0x2b151cd8u, 0x3dc562ecu);
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_28H = 0x00880001u;
            HW_SCE_p_func101(0xca3f7eeeu, 0x09a4472au, 0x2e218f86u, 0x908b33dau);
        }
        else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_28H = 0x00870001u;
            HW_SCE_p_func101(0x9c093ae5u, 0x1ed6255au, 0x8f67f24au, 0xeb53eefbu);
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
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000004u;
        SCE->REG_24H = 0x0000a206u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000u;
        SCE->REG_24H = 0x000016c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000682u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c2u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
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
        HW_SCE_p_func100(0xb0cc8c1au, 0xdabf4f6eu, 0x50ddfd40u, 0x55d7e34fu);
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
        HW_SCE_p_func071_r2(OFS_ADR);
        HW_SCE_p_func100(0x40c0ae57u, 0x29ba04aeu, 0xc761c11eu, 0x1bd201abu);
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
        SCE->REG_ECH = 0x000000f4u;
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
            HW_SCE_p_func101(0xc75067e4u, 0x65f5d835u, 0x270dd151u, 0x1ff8007fu);
            HW_SCE_p_func300();
            if (S_RAM[0] == 0x00000001)
            {
                break;
            }
            HW_SCE_p_func101(0x8e822641u, 0xa560dfdbu, 0xcd8aa6f6u, 0x7ac6e030u);
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
        HW_SCE_p_func100(0xe2066680u, 0xf0184b25u, 0xf343846fu, 0xa63764f2u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x4356149eu, 0x5afb71ceu, 0xe511df28u, 0xdd8745e2u);
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
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x8000f4d0u;
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
                    HW_SCE_p_func100(0x837faa79u, 0xae805b51u, 0xa4f2c9bfu, 0x7ffc4df8u);
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
                        HW_SCE_p_func101(0xaeabc302u, 0x1b959fdcu, 0xd1c51b83u, 0x95ab024fu);
                    }
                    else
                    {
                        HW_SCE_p_func101(0xbf206840u, 0x607bab5du, 0x9367a3bfu, 0x193a6d4au);
                    }
                }
                SCE->REG_ECH = 0x000027e1u;
                HW_SCE_p_func101(0x4a374666u, 0x52864535u, 0xc339c67cu, 0x34409fbau);
            }
            SCE->REG_ECH = 0x00008be0u;
            SCE->REG_ECH = 0x00000020u;
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            HW_SCE_p_func301();
            HW_SCE_p_func100(0xab9d9720u, 0xdce394c1u, 0xf00a566cu, 0x266678d5u);
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
            SCE->REG_100H = change_endian_long(0x000000f4u);
            HW_SCE_p_func101(0xd8882ff8u, 0xb938c560u, 0x5d570822u, 0x3cd2ca54u);
            HW_SCE_p_func043();
            SCE->REG_ECH = 0x0000379bu;
            HW_SCE_p_func074_r1();
            SCE->REG_ECH = 0x000034feu;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000f4u);
            HW_SCE_p_func101(0xb255d103u, 0xd13ef5d2u, 0x45974775u, 0xadde338bu);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x0e9623e0u, 0xf58c286au, 0xf778486au, 0x4df18dd9u);
            SCE->REG_D0H = 0x40000100u;
            SCE->REG_C4H = 0x02e087b7u;
            SCE->REG_00H = 0x00002323u;
            SCE->REG_2CH = 0x0000002du;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_04H = 0x00000222u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[1] = SCE->REG_100H;
            OutData_PrivKeyIndex[2] = SCE->REG_100H;
            OutData_PrivKeyIndex[3] = SCE->REG_100H;
            OutData_PrivKeyIndex[4] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[5] = SCE->REG_100H;
            OutData_PrivKeyIndex[6] = SCE->REG_100H;
            OutData_PrivKeyIndex[7] = SCE->REG_100H;
            OutData_PrivKeyIndex[8] = SCE->REG_100H;
            HW_SCE_p_func100(0x3019d35cu, 0x645ddc1du, 0x35918009u, 0x199ce470u);
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x00000c84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x000089c5u;
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
            OutData_PrivKeyIndex[9] = SCE->REG_100H;
            OutData_PrivKeyIndex[10] = SCE->REG_100H;
            OutData_PrivKeyIndex[11] = SCE->REG_100H;
            OutData_PrivKeyIndex[12] = SCE->REG_100H;
            HW_SCE_p_func100(0x425dd56du, 0xaab5a89cu, 0x75d7c47fu, 0xdacdb289u);
            SCE->REG_E0H = 0x81010000u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[0] = SCE->REG_100H;
            HW_SCE_p_func100(0xec71435au, 0x62d6e866u, 0xaca8918du, 0x3c88529au);
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
            SCE->REG_100H = change_endian_long(0x00000001u);
            HW_SCE_p_func101(0x878f63fdu, 0x1d540d16u, 0x7ec1ac78u, 0xb20bf112u);
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
            SCE->REG_100H = change_endian_long(0x00000002u);
            HW_SCE_p_func101(0xb177a360u, 0xa939f773u, 0x7d142f97u, 0x6344bcedu);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0xbb1bd422u, 0xef8c3c92u, 0x4cd047dau, 0x8a62dbe3u);
            SCE->REG_D0H = 0x40000200u;
            SCE->REG_C4H = 0x02e08887u;
            SCE->REG_00H = 0x00002323u;
            SCE->REG_2CH = 0x00000022u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00002313u;
            SCE->REG_2CH = 0x00000023u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_04H = 0x00000232u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[1] = SCE->REG_100H;
            OutData_PubKeyIndex[2] = SCE->REG_100H;
            OutData_PubKeyIndex[3] = SCE->REG_100H;
            OutData_PubKeyIndex[4] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[5] = SCE->REG_100H;
            OutData_PubKeyIndex[6] = SCE->REG_100H;
            OutData_PubKeyIndex[7] = SCE->REG_100H;
            OutData_PubKeyIndex[8] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[9] = SCE->REG_100H;
            OutData_PubKeyIndex[10] = SCE->REG_100H;
            OutData_PubKeyIndex[11] = SCE->REG_100H;
            OutData_PubKeyIndex[12] = SCE->REG_100H;
            HW_SCE_p_func100(0x5ca913fau, 0x6604aba7u, 0x5e907a49u, 0xe6ac5f43u);
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x00e08885u;
            SCE->REG_00H = 0x00002313u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00000052u;
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x000089c4u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_04H = 0x00000222u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[13] = SCE->REG_100H;
            OutData_PubKeyIndex[14] = SCE->REG_100H;
            OutData_PubKeyIndex[15] = SCE->REG_100H;
            OutData_PubKeyIndex[16] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[17] = SCE->REG_100H;
            OutData_PubKeyIndex[18] = SCE->REG_100H;
            OutData_PubKeyIndex[19] = SCE->REG_100H;
            OutData_PubKeyIndex[20] = SCE->REG_100H;
            HW_SCE_p_func100(0xa27751c1u, 0x16ee123cu, 0x8536a299u, 0x3fe25d73u);
            SCE->REG_E0H = 0x81010000u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[0] = SCE->REG_100H;
            HW_SCE_p_func102(0xd6c43818u, 0xa89dde83u, 0x15a5cc4au, 0x12255586u);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf4_r4.prc
***********************************************************************************************************************/
