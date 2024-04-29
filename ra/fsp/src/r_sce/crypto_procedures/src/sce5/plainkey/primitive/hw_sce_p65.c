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
        HW_SCE_func002(0x877ac003U, 0x1f55a80eU, 0x56f67726U, 0xb2fb1b27U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func002(0x020800e5U, 0x3739cd04U, 0x46c9610cU, 0xafb0bc84U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func002(0xba294c51U, 0x14afd546U, 0x1c1f8d84U, 0xb8b3e317U);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func002(0x93006859U, 0x575f3d59U, 0xc776b5e7U, 0xd92e9ecbU);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func002(0xc74f2e16U, 0x4e88787cU, 0x52b4731cU, 0x6d9858d0U);
    }
    HW_SCE_func001(0x0fd7d09bU, 0xa7b8d27cU, 0x46c75262U, 0x8075b7beU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x4037084eU, 0xff71ad85U, 0x1b8b2e00U, 0x99824528U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_00H = 0x00000113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0x050a08feU, 0x4fc6390eU, 0xa111da36U, 0x975d32a8U);
        }
        else
        {
            HW_SCE_func002(0x0d3b9483U, 0x0aa68236U, 0x866fe1a6U, 0xee77a58dU);
        }
        HW_SCE_func003(0xcd084c94U, 0xd2324d31U, 0x5dd83952U, 0xcebaf319U);
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
        HW_SCE_func003(0x35ca3d10U, 0xbe886693U, 0xae5873e3U, 0x2477eafbU);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p65.prc
***********************************************************************************************************************/
