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

fsp_err_t HW_SCE_SelfCheck2Sub(void)
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
    SCE->REG_84H = 0x00000202u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00093b8cu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01c7ba56u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00070804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_ECH = 0x3000a820u;
    SCE->REG_ECH = 0x00000003u;
    SCE->REG_ECH = 0x00010020u;
    SCE->REG_ECH = 0x00000821u;
    SCE->REG_ECH = 0x00000080u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00002008u;
    SCE->REG_ECH = 0x00000863u;
    SCE->REG_ECH = 0x00000884u;
    SCE->REG_ECH = 0x000008a5u;
    SCE->REG_ECH = 0x0000b4c0u;
    SCE->REG_ECH = 0x00000013u;
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000348u;
    SCE->REG_ECH = 0x0000b500u;
    SCE->REG_ECH = 0x000000b7u;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        HW_SCE_p_func100(0x6c71e264u, 0x905d3c7cu, 0x2a4c435eu, 0xbdb4777bu);
        SCE->REG_ECH = 0x00007c01u;
        SCE->REG_1CH = 0x00600000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
        {
            /* WAIT_LOOP */
            while (0u != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901cu;
            HW_SCE_p_func101(0x4ed68504u, 0x34692cfcu, 0xa224db89u, 0x08268dfbu);
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            /* WAIT_LOOP */
            while (0u != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901eu;
            HW_SCE_p_func101(0x7de6d907u, 0x8a506eeau, 0x951e9155u, 0x15bb7447u);
        }
        else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
        {
            /* WAIT_LOOP */
            while (0u != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901du;
            HW_SCE_p_func101(0x6f12da0du, 0xb83a404au, 0x1332d5efu, 0x94827cceu);
        }
        SCE->REG_C4H = 0x41001e5eu;
        SCE->REG_00H = 0x80002401u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001200u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B30)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x00000001u;
        SCE->REG_C4H = 0x00000000u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0010B008u;
        SCE->REG_ECH = 0x00000800u;
        SCE->REG_E0H = 0x80900000u;
        SCE->REG_00H = 0x00008443u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x000038a0u;
        SCE->REG_ECH = 0x00003405u;
        SCE->REG_ECH = 0x00002804u;
        SCE->REG_ECH = 0x342028e0u;
        SCE->REG_ECH = 0x10005066u;
        SCE->REG_ECH = 0x34202808u;
        SCE->REG_ECH = 0x10005066u;
        SCE->REG_ECH = 0x00003485u;
        HW_SCE_p_func101(0xca3b3ea4u, 0x71236437u, 0x3e0d1f89u, 0x58d2df4bu);
    }
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000B50u;
    SCE->REG_ECH = 0x00000842u;
    SCE->REG_ECH = 0x000008c6u;
    SCE->REG_ECH = 0x0000b480u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x0000b4a0u;
    SCE->REG_ECH = 0x00000002u;
    for(iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x01003804u;
        SCE->REG_ECH = 0x342028e0u;
        SCE->REG_ECH = 0x10005066u;
        SCE->REG_ECH = 0x00002440u;
        SCE->REG_ECH = 0x00002cc0u;
        SCE->REG_ECH = 0x00002485u;
    }
    SCE->REG_ECH = 0x00002c20u;
    SCE->REG_ECH = 0x38008840u;
    SCE->REG_ECH = 0x00002000u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000033u;
    SCE->REG_ECH = 0x0000b480u;
    SCE->REG_ECH = 0x0000003cu;
    SCE->REG_ECH = 0x01003804u;
    SCE->REG_ECH = 0x342028e0u;
    SCE->REG_ECH = 0x10005066u;
    SCE->REG_ECH = 0x00002cc0u;
    SCE->REG_ECH = 0x0000b480u;
    SCE->REG_ECH = 0x0000003eu;
    SCE->REG_ECH = 0x01003804u;
    SCE->REG_ECH = 0x342028e0u;
    SCE->REG_ECH = 0x10005066u;
    SCE->REG_ECH = 0x38008860u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x25d4d69bu, 0x231245f9u, 0x52a77bdau, 0xba7e5bc8u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7d948770u, 0x3e084379u, 0xc51558cau, 0x81647cd1u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x000001f0u;
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x2e24c972u;
        SCE->REG_ECH = 0x00003ffeu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0000001cu;
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000cc4u;
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
        SCE->REG_C4H = 0x41001eddu;
        SCE->REG_00H = 0x00002413u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000000u;
        SCE->REG_E0H = 0x80040080u;
        SCE->REG_00H = 0x00008213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0x8d0bfb78u, 0xe6d5ba61u, 0xf547a492u, 0x401bf606u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x000b0804u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_104H = 0x00000352u;
        SCE->REG_C4H = 0x00070805u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_100H = change_endian_long(0x00000001u);
        HW_SCE_p_func100(0xbffc56f3u, 0x242ee8afu, 0xd6f5a7f5u, 0xdc95f65eu);
        SCE->REG_D0H = 0x00000100u;
        SCE->REG_C4H = 0x0100b7f7u;
        SCE->REG_E0H = 0x81080000u;
        SCE->REG_00H = 0x00002823u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_C4H = 0x000b0805u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_C4H = 0x00070805u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0x48de5befu, 0x8b1403c2u, 0x1e08e8feu, 0xa1a7a87cu);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x3cb5779eu, 0xbab174adu, 0xf71b0f88u, 0xbe7d89cdu);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x010d0c04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        HW_SCE_p_func100(0x95ad7aabu, 0x2279e4ddu, 0x55fb6a92u, 0x431d725eu);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x70782e85u, 0x7706b601u, 0x736af867u, 0x38a12bdfu);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_04H = 0x00000212u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[20] = change_endian_long(SCE->REG_100H);
        S_RAM[21] = change_endian_long(SCE->REG_100H);
        S_RAM[22] = change_endian_long(SCE->REG_100H);
        S_RAM[23] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000202u;
        HW_SCE_p_func102(0x75fe6fe1u, 0x9ab95ef0u, 0xec59c801u, 0x84cb693au);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p02_r2.prc
***********************************************************************************************************************/
