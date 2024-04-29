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

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void)
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
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0x05fe0e6eU, 0x5c0dfd00U, 0x61fc3255U, 0x7f3699e0U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0xb8862e41U, 0x46801955U, 0xa5ae887fU, 0x2f2d49c8U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0xdab2d58fU, 0xfa2b5c0dU, 0x1c15eea2U, 0xdc2d96f6U);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0x3ccc6daeU, 0xd1b145c9U, 0xda3cd3fdU, 0xe36dd2a8U);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0xd6b21e6bU, 0x8971798dU, 0x0072aefcU, 0xcb42ca56U);
    }
    HW_SCE_p_func100(0x9e4b0444U, 0x3a40354fU, 0x3d33796cU, 0x04af656eU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x53018695U, 0xba49ec33U, 0x27e2a150U, 0x9fb48525U);
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
        HW_SCE_p_func102(0x21f93335U, 0xcf9f109dU, 0xd2983a12U, 0x64b0d8caU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p89f.prc
***********************************************************************************************************************/
