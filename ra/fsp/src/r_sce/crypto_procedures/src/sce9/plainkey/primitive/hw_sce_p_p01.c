/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
    HW_SCE_SelfCheck1SubSub();

    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_04H = 0x00000001U;
    SCE->REG_10CH = 0x00000701U;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_80H = 0x00000001U;
    SCE->REG_28H = 0x00000001U;
    SCE->REG_7CH = 0x00000001U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_84H = 0x00010101U;
    SCE->REG_13CH = 0x00000F00U;
    SCE->REG_88H = 0x00008002U;
    SCE->REG_104H = 0x00000352U;
    HW_SCE_p_func101(change_endian_long(0xe1a2a5d8U), change_endian_long(0x821a5428U), change_endian_long(0x7c777ac3U), change_endian_long(0xfd151290U));
    SCE->REG_88H = 0x00000000U;
    SCE->REG_104H = 0x00000352U;
    SCE->REG_C4H = 0x000f3a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0x9ed66559U;
    SCE->REG_100H = 0x8e5bcbb9U;
    SCE->REG_100H = 0xd2f5d1d3U;
    SCE->REG_100H = 0xae209b90U;
    HW_SCE_p_func101(change_endian_long(0xf4e6ce80U), change_endian_long(0x39773b0fU), change_endian_long(0x86227f8fU), change_endian_long(0x2b810040U));
    HW_SCE_p_func100(change_endian_long(0x3e5590a5U), change_endian_long(0x96fa7453U), change_endian_long(0x0e213a19U), change_endian_long(0x12498aecU));
    SCE->REG_04H = 0x00001001U;
    SCE->REG_1D0H = 0x00000000U;
    if (0U == (SCE->REG_18H_b.B13))
    {
        SCE->REG_1BCH = 0x00000020U;
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_08H = 0x0000FFFFU;
        SCE->REG_13CH = 0x00000220U;
        HW_SCE_p_func102(change_endian_long(0x62cb9591U), change_endian_long(0x72556c92U), change_endian_long(0x45cac937U), change_endian_long(0x8431be8fU));
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p01.prc
***********************************************************************************************************************/
