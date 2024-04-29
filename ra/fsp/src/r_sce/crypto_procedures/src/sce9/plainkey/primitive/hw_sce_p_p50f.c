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

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void)
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
        HW_SCE_p_func101(0xa53a714eU, 0xce2b3fd6U, 0x3801fd1bU, 0xa2b83ef5U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0x82fe7aceU, 0xacd65af6U, 0x959bdef5U, 0x8e151cecU);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0x0863ac10U, 0x4a52da44U, 0xd5687f54U, 0x4962b267U);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0xcd1f7364U, 0xc1420ba6U, 0x87d65bffU, 0xb3858d7fU);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func101(0x39f66ff5U, 0x749d4554U, 0x3bed7a06U, 0xf39940faU);
    }
    HW_SCE_p_func100(0x2b31b234U, 0x798ccde6U, 0x81ae9de2U, 0x634149d6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7d67ba6dU, 0x40f2ca12U, 0x3fc845eaU, 0xccc18a2eU);
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
        HW_SCE_p_func102(0xda587a2aU, 0x27b36189U, 0x2078e407U, 0xeeeb0a36U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p50f_r1.prc
***********************************************************************************************************************/
