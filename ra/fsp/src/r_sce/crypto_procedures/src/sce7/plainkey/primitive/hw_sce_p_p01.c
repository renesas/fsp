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
    SCE->REG_88H = 0x00008004U;
    SCE->REG_104H = 0x00000352U;
    HW_SCE_p_func101(change_endian_long(0x719bc5a0U), change_endian_long(0x07efa893U), change_endian_long(0x9d5a9acaU), change_endian_long(0xd80f933bU));
    SCE->REG_88H = 0x00000000U;
    SCE->REG_104H = 0x00000352U;
    SCE->REG_C4H = 0x000f3a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0xf5801763U;
    SCE->REG_100H = 0xe50f4ad1U;
    SCE->REG_100H = 0x3e9431ecU;
    SCE->REG_100H = 0xcfb55de3U;
    HW_SCE_p_func101(change_endian_long(0xd88e7d16U), change_endian_long(0xab9df63bU), change_endian_long(0xcddb859cU), change_endian_long(0xb02b9b93U));
    HW_SCE_p_func100(change_endian_long(0x7905911bU), change_endian_long(0x51c938afU), change_endian_long(0x13c01eefU), change_endian_long(0x08875fe3U));
    SCE->REG_04H = 0x00001001U;
    SCE->REG_1D0H = 0x00000000U;
    if (0U == (SCE->REG_18H_b.B13))
    {
        SCE->REG_1BCH = 0x00000020U;
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_13CH = 0x00000201U;
        HW_SCE_p_func102(change_endian_long(0x805bb52cU), change_endian_long(0x333b3e3aU), change_endian_long(0x6100feadU), change_endian_long(0xae5da87aU));
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p01.prc
***********************************************************************************************************************/
