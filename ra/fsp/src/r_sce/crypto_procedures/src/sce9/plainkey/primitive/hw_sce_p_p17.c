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

fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00001702U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0x737bb4a5U, 0xbff6a348U, 0xaeb16686U, 0xe2d29c1aU);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008207U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x000034e0U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000017U);
    HW_SCE_p_func101(0x4815a41cU, 0x00916820U, 0xbe01c103U, 0x1dec006aU);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000017U);
    HW_SCE_p_func101(0xd842bfd1U, 0xd2970d65U, 0xbc2702f7U, 0x02db49feU);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0xf7d92364U, 0x5552bf8aU, 0x97e251cdU, 0xecbc6a8cU);
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = SCE->REG_100H;
    HW_SCE_p_func100(0x9393aedfU, 0x0a40b1f7U, 0x05756c3aU, 0x1b56ba0cU);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80100000U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xac85b8abU, 0xee4cd758U, 0xa30bc79dU, 0x400754d0U);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x72864ca0U, 0xa02a9463U, 0x51458194U, 0x25480ca7U);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xca854ddfU, 0x013d0d2bU, 0xbae6953fU, 0x203b2168U);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x98a0b10bU, 0xbc9e675fU, 0xc7c22bccU, 0xc608476eU);
    SCE->REG_D0H = 0x40000300U;
    SCE->REG_C4H = 0x02e487b7U;
    SCE->REG_E0H = 0x81100000U;
    SCE->REG_00H = 0x00002843U;
    SCE->REG_04H = 0x00000242U;
    for(iLoop=1; iLoop<17; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    }
    HW_SCE_p_func100(0x6d2f16f6U, 0xa21672b3U, 0x54a9986cU, 0xb2894ec7U);
    SCE->REG_104H = 0x00000352U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000089c5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000004U);
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    HW_SCE_p_func102(0xe907d5eeU, 0x06fc1a87U, 0x4695e21dU, 0x9b334c1dU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p17_r1.prc
***********************************************************************************************************************/
