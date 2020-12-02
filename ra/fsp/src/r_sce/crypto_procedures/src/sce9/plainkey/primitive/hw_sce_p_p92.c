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

fsp_err_t HW_SCE_SelfCheck3Sub(void)
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
    SCE->REG_84H = 0x00009203u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000001f0u;
    SCE->REG_ECH = 0x00003bfeu;
    SCE->REG_ECH = 0x38008be0u;
    SCE->REG_ECH = 0x2e24c972u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x7252ffb3u, 0xa4f2970fu, 0xccf82b60u, 0xfaf63abcu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
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
        for(jLoop = 0; jLoop < 1; jLoop = jLoop + 1)
        {
            HW_SCE_p_func100(0x79c46a3cu, 0x0ae625b1u, 0x2ec940fdu, 0xfd6753fbu);
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
                HW_SCE_p_func101(0x584ce62cu, 0x7c8ea760u, 0x07dd1294u, 0x228e5267u);
            }
            else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
            {
                /* WAIT_LOOP */
                while (0u != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901eu;
                HW_SCE_p_func101(0x7c885349u, 0x7333bee5u, 0x63655723u, 0x31e16865u);
            }
            else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
            {
                /* WAIT_LOOP */
                while (0u != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901du;
                HW_SCE_p_func101(0x796ca859u, 0x963097eau, 0x416c1f4du, 0x6acf9612u);
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
            HW_SCE_p_func101(0xa8ec0974u, 0x20eb43a5u, 0x794d25d7u, 0x4bdd0550u);
        }
        SCE->REG_ECH = 0x0000b4e0u;
        SCE->REG_ECH = 0x0000005Au;
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
        SCE->REG_ECH = 0x00000100u;
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
        HW_SCE_p_func100(0x61e61c3du, 0x30283a89u, 0x5909828eu, 0xa7699c6eu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x4e350eeeu, 0xd9878500u, 0xcc805ef3u, 0x77d220feu);
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
            HW_SCE_p_func100(0x99af7425u, 0x2113d46au, 0xff58fb18u, 0x24edfe4bu);
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
            HW_SCE_p_func100(0x094f8766u, 0x911c9512u, 0xfb3f4bbdu, 0x460e53e2u);
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
            HW_SCE_p_func100(0x0b1343bfu, 0xfa20139bu, 0xb28498c2u, 0x9a061f91u);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0x27268344u, 0xed4d73cbu, 0x2e42dad1u, 0x2e6e640bu);
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x010d0c04u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            HW_SCE_p_func100(0xb3878676u, 0x7e57894eu, 0xd6748786u, 0x77254975u);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0xa50fc7c5u, 0x110c56e9u, 0xad65e984u, 0x00e91a6cu);
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
            S_RAM[24] = change_endian_long(SCE->REG_100H);
            S_RAM[25] = change_endian_long(SCE->REG_100H);
            S_RAM[26] = change_endian_long(SCE->REG_100H);
            S_RAM[27] = change_endian_long(SCE->REG_100H);
            SCE->REG_13CH = 0x00000202u;
            HW_SCE_p_func102(0x079c4c8cu, 0x962acb2eu, 0x9a5c0aebu, 0x6ec75008u);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
    else
    {
        HW_SCE_p_func100(0x6b276b23u, 0x11089165u, 0x87325daau, 0x63f67f53u);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x9eb0ec5fu, 0xd6b216c4u, 0xe5b5cb54u, 0x17139ef3u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x010d0c04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        HW_SCE_p_func100(0x19d71d04u, 0xf4910acdu, 0x09b90550u, 0x57b49033u);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x0f03b51cu, 0x5b024757u, 0x31ea3b4du, 0xf4eb1056u);
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
        S_RAM[24] = change_endian_long(SCE->REG_100H);
        S_RAM[25] = change_endian_long(SCE->REG_100H);
        S_RAM[26] = change_endian_long(SCE->REG_100H);
        S_RAM[27] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000202u;
        HW_SCE_p_func102(0x974ace4au, 0xbf7d7d22u, 0xfbcbcfc6u, 0xdd8d0fe8u);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p92_r1.prc
***********************************************************************************************************************/
