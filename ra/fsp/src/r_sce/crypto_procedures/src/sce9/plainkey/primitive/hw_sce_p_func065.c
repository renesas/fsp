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

void HW_SCE_p_func065_r1(uint32_t* ARG1, uint32_t* ARG2)
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
    HW_SCE_p_func100(0x23a20f43u, 0xb31e013bu, 0x7d30fa57u, 0xddf885eeu);
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
    SCE->REG_100H = change_endian_long(0x00000011u);
    HW_SCE_p_func101(0xabc8f62eu, 0xa0b4b4cdu, 0xabed9fedu, 0x55efaa74u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x000034e4u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000011u);
    HW_SCE_p_func101(0x79da836fu, 0x01a8f4b7u, 0x4410b933u, 0x7d62b94du);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0xfef7fdd1u, 0x5e78f5c3u, 0xd66fdca4u, 0x5b2ab651u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00050804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    HW_SCE_p_func081();
    SCE->REG_ECH = 0x00007c01u;
    SCE->REG_1CH = 0x00600000u;
    SCE->REG_1D0H = 0x00000000u;
    if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x3b31b2c7u, 0xfdedce3fu, 0xf2657d0au, 0x9d2cac16u);
        SCE->REG_00H = 0x80002100u;
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00000886u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02e087b6u;
        SCE->REG_04H = 0x0000c200u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[0];
        SCE->REG_100H = ARG1[1];
        SCE->REG_100H = ARG1[2];
        SCE->REG_100H = ARG1[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG1[4+iLoop + 0];
            SCE->REG_100H = ARG1[4+iLoop + 1];
            SCE->REG_100H = ARG1[4+iLoop + 2];
            SCE->REG_100H = ARG1[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+iLoop + 0] = SCE->REG_100H;
            ARG2[1+iLoop + 1] = SCE->REG_100H;
            ARG2[1+iLoop + 2] = SCE->REG_100H;
            ARG2[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG2[1+iLoop + 0] = SCE->REG_100H;
        ARG2[1+iLoop + 1] = SCE->REG_100H;
        ARG2[1+iLoop + 2] = SCE->REG_100H;
        ARG2[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x26483003u, 0x4db2d050u, 0x1fb2570au, 0x627d3e3bu);
    }
    else if (0x0a000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x2be8ca08u, 0xf05b8eaau, 0xeb20462au, 0xc40e8c69u);
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func066(0,ARG1);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        SCE->REG_D0H = 0x40000700u;
        SCE->REG_C4H = 0x02e08887u;
        SCE->REG_04H = 0x00000282u;
        for(oLoop=0; oLoop<32; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+oLoop + 0] = SCE->REG_100H;
            ARG2[1+oLoop + 1] = SCE->REG_100H;
            ARG2[1+oLoop + 2] = SCE->REG_100H;
            ARG2[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xc47ff753u, 0x04506ad6u, 0x013e3dd5u, 0xbe1ead25u);
        SCE->REG_104H = 0x00000361u;
        SCE->REG_A4H = 0x00000885u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[iLoop + 0];
        SCE->REG_100H = ARG1[iLoop + 1];
        SCE->REG_100H = ARG1[iLoop + 2];
        SCE->REG_100H = ARG1[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x00e08885u;
        SCE->REG_00H = 0x00002113u;
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
        ARG2[1+oLoop + 0] = SCE->REG_100H;
        ARG2[1+oLoop + 1] = SCE->REG_100H;
        ARG2[1+oLoop + 2] = SCE->REG_100H;
        ARG2[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0u != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x3b861e61u, 0xb600ea62u, 0x4bf70f4eu, 0xff3c1866u);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func062(36,ARG2);
        oLoop = 36 + 32;
        HW_SCE_p_func101(0x23e8fb2eu, 0x74657e4du, 0x076514e5u, 0xb519809cu);
    }
    else if (0x0b000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x65278693u, 0x04fabe2eu, 0xfc2fa6d5u, 0x9de2decbu);
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func066(0,ARG1);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func062(0,ARG2);
        oLoop = 0 + 32;
        HW_SCE_p_func100(0x7fa0d5a1u, 0x3517f529u, 0x36e90eafu, 0x91f1dc4bu);
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000011u;
        HW_SCE_p_func066(32,ARG1);
        iLoop = 32 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000021u;
        HW_SCE_p_func062(32,ARG2);
        oLoop = 32 + 32;
        HW_SCE_p_func100(0xcaa3bb50u, 0xd6691c2bu, 0xc5ff2240u, 0x7f7071bdu);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func062(64,ARG2);
        oLoop = 64 + 32;
        HW_SCE_p_func101(0x8427d069u, 0x71e1837eu, 0x1d040576u, 0x0c34e400u);
    }
    else if (0x0c000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0xa26076b9u, 0x10e94805u, 0x196f6ef1u, 0xf38da63du);
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func067(0,ARG1);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000024u;
        SCE->REG_D0H = 0x40000f00u;
        SCE->REG_C4H = 0x02e08887u;
        SCE->REG_04H = 0x00000202u;
        for(oLoop=0; oLoop<64; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+oLoop + 0] = SCE->REG_100H;
            ARG2[1+oLoop + 1] = SCE->REG_100H;
            ARG2[1+oLoop + 2] = SCE->REG_100H;
            ARG2[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xa56b7d5du, 0xf4486507u, 0x64d0b38fu, 0x04fb55a5u);
        SCE->REG_104H = 0x00000361u;
        SCE->REG_A4H = 0x00000885u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[iLoop + 0];
        SCE->REG_100H = ARG1[iLoop + 1];
        SCE->REG_100H = ARG1[iLoop + 2];
        SCE->REG_100H = ARG1[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x00e08885u;
        SCE->REG_00H = 0x00002113u;
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
        ARG2[1+oLoop + 0] = SCE->REG_100H;
        ARG2[1+oLoop + 1] = SCE->REG_100H;
        ARG2[1+oLoop + 2] = SCE->REG_100H;
        ARG2[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0u != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x4aed1905u, 0xe5d8ff2eu, 0xcee610e7u, 0x2b56f36cu);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func064(68,ARG2);
        oLoop = 68 + 64;
        HW_SCE_p_func101(0x953dbb7cu, 0x684783a0u, 0xec9db7b7u, 0xeadfcaa6u);
    }
    else if (0x0d000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x0da69955u, 0x4c58a953u, 0x660176a5u, 0xb9ae0c4eu);
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func067(0,ARG1);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func064(0,ARG2);
        oLoop = 0 + 64;
        HW_SCE_p_func100(0x58754c97u, 0xd4752e10u, 0x9fa38d8fu, 0xbe29908fu);
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func067(64,ARG1);
        iLoop = 64 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func064(64,ARG2);
        oLoop = 64 + 64;
        HW_SCE_p_func100(0x3ab34648u, 0x51ed9b48u, 0x476e0a97u, 0x9dd57620u);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func064(128,ARG2);
        oLoop = 128 + 64;
        HW_SCE_p_func101(0x25db8d2cu, 0xd2c88a95u, 0x654191cbu, 0x45fcaca9u);
    }
    else if (0x12000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x546d42e4u, 0x4fab67fau, 0x54171dfeu, 0x01b96779u);
        SCE->REG_00H = 0x80002100u;
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00000886u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02e08886u;
        SCE->REG_04H = 0x0000c200u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[0];
        SCE->REG_100H = ARG1[1];
        SCE->REG_100H = ARG1[2];
        SCE->REG_100H = ARG1[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG1[4+iLoop + 0];
            SCE->REG_100H = ARG1[4+iLoop + 1];
            SCE->REG_100H = ARG1[4+iLoop + 2];
            SCE->REG_100H = ARG1[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+iLoop + 0] = SCE->REG_100H;
            ARG2[1+iLoop + 1] = SCE->REG_100H;
            ARG2[1+iLoop + 2] = SCE->REG_100H;
            ARG2[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG2[1+iLoop + 0] = SCE->REG_100H;
        ARG2[1+iLoop + 1] = SCE->REG_100H;
        ARG2[1+iLoop + 2] = SCE->REG_100H;
        ARG2[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x0afcbf2fu, 0xc4a4aabau, 0x39c6470fu, 0x02417d40u);
    }
    HW_SCE_p_func100(0xd3371c6du, 0xd24af252u, 0x239fe0dcu, 0x815b0e6cu);
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
    ARG2[1+oLoop + 0] = SCE->REG_100H;
    ARG2[1+oLoop + 1] = SCE->REG_100H;
    ARG2[1+oLoop + 2] = SCE->REG_100H;
    ARG2[1+oLoop + 3] = SCE->REG_100H;
    SCE->REG_ECH = 0x00007c1cu;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func065_r1.prc
***********************************************************************************************************************/
