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
    SCE->REG_84H = 0x00000201u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00093b8cu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0x01c7ba56u;
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00070804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0x00000000u;
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
        HW_SCE_p_func100(change_endian_long(0x600eb3f3u), change_endian_long(0x5be54db5u), change_endian_long(0xd957da80u), change_endian_long(0xb7be0bbdu));
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
            HW_SCE_p_func101(change_endian_long(0x1cb8f160u), change_endian_long(0x44a42eb9u), change_endian_long(0xb9d9de91u), change_endian_long(0xf7e69233u));
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            /* WAIT_LOOP */
            while (0u != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901eu;
            HW_SCE_p_func101(change_endian_long(0x59fb7336u), change_endian_long(0x9c8f2482u), change_endian_long(0xc090f97fu), change_endian_long(0x0dba80dfu));
        }
        else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
        {
            /* WAIT_LOOP */
            while (0u != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901du;
            HW_SCE_p_func101(change_endian_long(0xed4e6151u), change_endian_long(0xc771e206u), change_endian_long(0x81266996u), change_endian_long(0x2bbee94du));
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
        HW_SCE_p_func101(change_endian_long(0x48b1bfc2u), change_endian_long(0x2f0d98c0u), change_endian_long(0xff07792fu), change_endian_long(0x166d190cu));
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
    HW_SCE_p_func100(change_endian_long(0xaddf6f7bu), change_endian_long(0xae6de2f8u), change_endian_long(0xf97e7cdau), change_endian_long(0x68b0a447u));
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(change_endian_long(0x2c21e21cu), change_endian_long(0x8f10bb7au), change_endian_long(0x7714e304u), change_endian_long(0x3807136cu));
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
        SCE->REG_100H = 0x00000000u;
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
        HW_SCE_p_func100(change_endian_long(0xcfbe1fc5u), change_endian_long(0xae3c0b75u), change_endian_long(0xfa1b775cu), change_endian_long(0xfccd985au));
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x000b0804u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = 0x00000000u;
        SCE->REG_104H = 0x00000352u;
        SCE->REG_C4H = 0x00070805u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = 0x00000000u;
        SCE->REG_100H = 0x00000000u;
        SCE->REG_100H = 0x00000000u;
        SCE->REG_100H = 0x00000001u;
        HW_SCE_p_func100(change_endian_long(0xd69c553bu), change_endian_long(0x72e04337u), change_endian_long(0xcf6834e5u), change_endian_long(0x29b2da04u));
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
        HW_SCE_p_func100(change_endian_long(0x1c99323fu), change_endian_long(0x6c63dba1u), change_endian_long(0x38229203u), change_endian_long(0x22d91767u));
        HW_SCE_p_func103();
        HW_SCE_p_func100(change_endian_long(0x80b45ab9u), change_endian_long(0x4d97ab5fu), change_endian_long(0x3ef09550u), change_endian_long(0xa94d5b6eu));
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x010d0c04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = 0x00000000u;
        HW_SCE_p_func100(change_endian_long(0xe6c8760fu), change_endian_long(0x099c6fc6u), change_endian_long(0x1406eda2u), change_endian_long(0x580bd39cu));
        HW_SCE_p_func103();
        HW_SCE_p_func100(change_endian_long(0xff2b1e8au), change_endian_long(0x3e6453b3u), change_endian_long(0xe33170b8u), change_endian_long(0xe2d6af49u));
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = 0x00000000u;
        SCE->REG_04H = 0x00000212u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[16] = change_endian_long(SCE->REG_100H);
        S_RAM[17] = change_endian_long(SCE->REG_100H);
        S_RAM[18] = change_endian_long(SCE->REG_100H);
        S_RAM[19] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000221u;
        HW_SCE_p_func102(change_endian_long(0xf3939357u), change_endian_long(0x04e0f3c0u), change_endian_long(0x2c7db127u), change_endian_long(0x9914e276u));
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p02.prc
***********************************************************************************************************************/
