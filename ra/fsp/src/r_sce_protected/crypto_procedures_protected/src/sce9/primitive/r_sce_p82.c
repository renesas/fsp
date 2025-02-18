/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

fsp_err_t R_SCE_SelfCheck2Sub(void)
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
    SCE->REG_84H = 0x00008202U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00093b8cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01c7ba56U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00070804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x3000a820U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00010020U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x00000080U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00002008U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_ECH = 0x00000842U;
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x00000040U;
    SCE->REG_ECH = 0x0000b4c0U;
    SCE->REG_ECH = 0x00000013U;
    SCE->REG_ECH = 0x0000b620U;
    SCE->REG_ECH = 0x00000355U;
    for(jLoop = 0; jLoop < 2; jLoop = jLoop + 1)
    {
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0020905cU;
        SCE->REG_C4H = 0x41001e5eU;
        SCE->REG_00H = 0x80002401U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001200U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B30)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x00000001U;
        SCE->REG_C4H = 0x00000000U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0010B008U;
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_E0H = 0x80900000U;
        SCE->REG_00H = 0x00008443U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000038a0U;
        SCE->REG_ECH = 0x34202a25U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x0000b500U;
        SCE->REG_ECH = 0x00000400U;
        SCE->REG_ECH = 0x04202905U;
        SCE->REG_ECH = 0x34202a28U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0000005AU;
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x0000b4a0U;
        SCE->REG_ECH = 0x00000002U;
        for(iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003804U;
            SCE->REG_ECH = 0x342028e0U;
            SCE->REG_ECH = 0x10005066U;
            SCE->REG_ECH = 0x00002440U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_ECH = 0x00002485U;
        }
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x00000037U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x0000003cU;
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x00002cc0U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x0000003eU;
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000cc4U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x8084000aU;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000a540U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_ECH = 0x0000a4c0U;
        SCE->REG_ECH = 0x00000002U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00002008U;
        R_SCE_func101(0x2f9974edU, 0x5b81fb15U, 0x12b2aaacU, 0xa489d594U);
    }
    SCE->REG_ECH = 0x00002c20U;
    SCE->REG_ECH = 0x38008840U;
    SCE->REG_ECH = 0x00000200U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x38008860U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x8752b825U, 0x94164081U, 0x0f3acfb3U, 0x0aac3e7aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x6334ebb3U, 0x3709c96eU, 0x91cd611cU, 0x7a3c897eU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000001f0U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x8a681df7U;
        SCE->REG_ECH = 0x00003ffeU;
        R_SCE_func100(0xf61cad5fU, 0xbf13df5cU, 0x354511c2U, 0x7f6841b7U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x000b0804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x00070805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000001U);
        R_SCE_func100(0xcac08e72U, 0xb14b6522U, 0xd325a3aeU, 0x4dda977fU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x0100b7f7U;
        SCE->REG_ECH = 0x0000b540U;
        SCE->REG_ECH = 0x00000040U;
        SCE->REG_E0H = 0x8188000aU;
        SCE->REG_00H = 0x00002823U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x000b0805U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x00070805U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x2b6949adU, 0xcaad5bf9U, 0xf3e6089aU, 0x88cf1187U);
        R_SCE_func103();
        R_SCE_func100(0x9f426479U, 0x73398377U, 0x91e1526aU, 0x8925be3eU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x0a5890c4U, 0x96324e42U, 0x76850e62U, 0x2e8870a3U);
        R_SCE_func103();
        R_SCE_func100(0x3fa01441U, 0xbb928ba2U, 0xd264e2e4U, 0x83034508U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[20] = SCE->REG_100H;
        S_RAM[21] = SCE->REG_100H;
        S_RAM[22] = SCE->REG_100H;
        S_RAM[23] = SCE->REG_100H;
        SCE->REG_13CH = 0x00000202U;
        R_SCE_func102(0x55dd773aU, 0xaf263f67U, 0xa18300fdU, 0xb7af8e2aU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p82_r4.prc
***********************************************************************************************************************/
