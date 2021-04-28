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
#include "r_sce.h"
#include "r_sce_private.h"

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

fsp_err_t R_SCE_LoadHukSub(uint32_t *InData_LC)
{
    uint32_t iLoop    = 0U;
    uint32_t iLoop1   = 0U;
    uint32_t iLoop2   = 0U;
    int32_t  jLoop    = 0U;
    uint32_t kLoop    = 0U;
    uint32_t oLoop    = 0U;
    uint32_t oLoop1   = 0U;
    uint32_t oLoop2   = 0U;
    uint32_t dummy    = 0U;
    uint32_t KEY_ADR  = 0U;
    uint32_t OFS_ADR  = 0U;
    uint32_t MAX_CNT2 = 0U;
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
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00004001U;
    SCE->REG_108H = 0x00000000U;
    R_SCE_func048(InData_LC);
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_ECH = 0x34202801U;
    SCE->REG_ECH = 0x20003401U;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
    if (InData_LC[0] == 0x00000000)
    {
        SCE->REG_1CH = 0x00b80000U;
        R_SCE_func101(0x910462eeU, 0xc019489bU, 0x423f71caU, 0xd2f2c484U);
    }
    else if (InData_LC[0] == 0x00000001)
    {
        SCE->REG_1CH = 0x00b00000U;
        R_SCE_func101(0x0757ac60U, 0xd2bf9036U, 0x6f9557efU, 0x97b40d75U);
    }
    else if (InData_LC[0] == 0x00000002)
    {
        SCE->REG_1CH = 0x00b10000U;
        R_SCE_func101(0x248eecceU, 0x6a647475U, 0x4b2d3e05U, 0xcd67a1c0U);
    }
    else if (InData_LC[0] == 0x00000003)
    {
        SCE->REG_1CH = 0x00b20000U;
        R_SCE_func101(0x69da3cd7U, 0xa5d27e49U, 0xedaaaca6U, 0x3b74f8e8U);
    }
    else if (InData_LC[0] == 0x00000004)
    {
        SCE->REG_1CH = 0x00b30000U;
        R_SCE_func101(0xd3577449U, 0xa802a60dU, 0xacd705b0U, 0xde5d62cdU);
    }
    else if (InData_LC[0] == 0x00000005)
    {
        SCE->REG_1CH = 0x00b40000U;
        R_SCE_func101(0x30538696U, 0xa8e7a5c8U, 0x6548cd7eU, 0xe4849bafU);
    }
    else if (InData_LC[0] == 0x00000006)
    {
        SCE->REG_1CH = 0x00b50000U;
        R_SCE_func101(0x30239a5eU, 0xf543ab1dU, 0x9d7944e6U, 0xef8e76dbU);
    }
    else if (InData_LC[0] == 0x00000007)
    {
        SCE->REG_1CH = 0x00b60000U;
        R_SCE_func101(0x13fc13ebU, 0x62a27527U, 0xcbaa64faU, 0x3f75ba45U);
    }
    else if (InData_LC[0] == 0x00000008)
    {
        SCE->REG_1CH = 0x00b70000U;
        R_SCE_func101(0x3cc5aa3fU, 0xf5189eafU, 0x1dd14f5cU, 0xbce9f462U);
    }
    else
    {
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func101(0x125e03f6U, 0x852ac185U, 0xf4527cb6U, 0x7995d726U);
    }
    R_SCE_func100(0xfa382636U, 0x2cc695f9U, 0x8103ad09U, 0x8874586cU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0xbd3f4ffbU, 0x6cf73347U, 0x34307717U, 0xcbda6163U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000040U);
        R_SCE_func101(0x137090ecU, 0x06be17caU, 0xc7ba1504U, 0xe9018f7dU);
        R_SCE_func040();
        SCE->REG_D0H = 0x40000100U;
        SCE->REG_C4H = 0x02f087b5U;
        SCE->REG_E8H = 0x80000000U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00f087b5U;
        SCE->REG_E8H = 0x80000004U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001d0U;
        SCE->REG_E0H = 0x80880001U;
        SCE->REG_00H = 0x00008223U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001b0U;
        SCE->REG_ECH = 0x00003c01U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000087b5U;
        SCE->REG_E8H = 0x80000008U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x00800c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xf05b4952U, 0x6e695becU, 0x81e946b3U, 0x941f422eU);
        SCE->REG_C4H = 0x20443a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x200c3e1cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0152db38U);
        SCE->REG_C4H = 0x00440a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x00000e9cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f7370eU);
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001c0U;
        SCE->REG_E0H = 0x80840001U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_13CH = 0x00000211U;
        R_SCE_func102(0xcc23e22eU, 0x1dccf1a2U, 0x0dd974e8U, 0xa1d0098dU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p40_r1.prc
***********************************************************************************************************************/
