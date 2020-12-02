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

fsp_err_t HW_SCE_SelfCheck1Sub(void)
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
    HW_SCE_SelfCheck1SubSub();

    SCE->REG_138H = 0xf597806Au;
    SCE->REG_F0H = 0x00000000u;
    SCE->REG_04H = 0x00000001u;
    SCE->REG_10CH = 0x00000701u;
    if (0x0u != (SCE->REG_1BCH & 0x1fu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_80H = 0x00000001u;
    SCE->REG_28H = 0x00000001u;
    SCE->REG_7CH = 0x00000001u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008u;
    SCE->REG_84H = 0x00010101u;
    SCE->REG_13CH = 0x00000F00u;
    SCE->REG_88H = 0x00008002u;
    SCE->REG_104H = 0x00000352u;
    HW_SCE_p_func101(change_endian_long(0xe1a2a5d8u), change_endian_long(0x821a5428u), change_endian_long(0x7c777ac3u), change_endian_long(0xfd151290u));
    SCE->REG_88H = 0x00000000u;
    SCE->REG_104H = 0x00000352u;
    SCE->REG_C4H = 0x000f3a0du;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0x9ed66559u;
    SCE->REG_100H = 0x8e5bcbb9u;
    SCE->REG_100H = 0xd2f5d1d3u;
    SCE->REG_100H = 0xae209b90u;
    HW_SCE_p_func101(change_endian_long(0xf4e6ce80u), change_endian_long(0x39773b0fu), change_endian_long(0x86227f8fu), change_endian_long(0x2b810040u));
    HW_SCE_p_func100(change_endian_long(0x3e5590a5u), change_endian_long(0x96fa7453u), change_endian_long(0x0e213a19u), change_endian_long(0x12498aecu));
    SCE->REG_04H = 0x00001001u;
    SCE->REG_1D0H = 0x00000000u;
    if (0u == (SCE->REG_18H_b.B13))
    {
        SCE->REG_1BCH = 0x00000020u;
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_08H = 0x0000FFFFu;
        SCE->REG_13CH = 0x00000220u;
        HW_SCE_p_func102(change_endian_long(0x62cb9591u), change_endian_long(0x72556c92u), change_endian_long(0x45cac937u), change_endian_long(0x8431be8fu));
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p01.prc
***********************************************************************************************************************/
