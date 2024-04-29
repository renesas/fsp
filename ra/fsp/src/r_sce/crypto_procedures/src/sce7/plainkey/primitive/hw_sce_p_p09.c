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

fsp_err_t HW_SCE_UpdateAes192KeyIndexSub(const uint32_t * const InData_IV, const uint32_t * const InData_InstData, uint32_t * const OutData_KeyIndex)
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
    if (0x0U != (SCE->REG_1B4H & 0x1dU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00000901U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0xaf3791d1U, 0x3d7354dcU, 0x4376924eU, 0xff6b173bU);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x200c3b0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_INST2[0];
    SCE->REG_100H = S_INST2[1];
    SCE->REG_100H = S_INST2[2];
    SCE->REG_100H = S_INST2[3];
    SCE->REG_C4H = 0x000c0b0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0xda0168d1U);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x02f8073dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_INST2[4];
    SCE->REG_100H = S_INST2[5];
    SCE->REG_100H = S_INST2[6];
    SCE->REG_100H = S_INST2[7];
    HW_SCE_p_func100(0x0a2966eaU, 0x687a74e3U, 0x36428479U, 0x27780546U);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00f9073dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_INST2[4+4 + 0];
    SCE->REG_100H = S_INST2[4+4 + 1];
    SCE->REG_100H = S_INST2[4+4 + 2];
    SCE->REG_100H = S_INST2[4+4 + 3];
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x000007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_INST2[4+8 + 0];
    SCE->REG_100H = S_INST2[4+8 + 1];
    SCE->REG_100H = S_INST2[4+8 + 2];
    SCE->REG_100H = S_INST2[4+8 + 3];
    SCE->REG_A4H = 0x00800c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xa9e7acc7U, 0xe8074faaU, 0xb7f05e13U, 0x3f92c330U);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00040805U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_IV[0];
    SCE->REG_100H = InData_IV[1];
    SCE->REG_100H = InData_IV[2];
    SCE->REG_100H = InData_IV[3];
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00050804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x701c1d1fU, 0x22592387U, 0x8d6f55f7U, 0x1fcdced4U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80040000U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x200c3b0dU;
    SCE->REG_E0H = 0x81040000U;
    SCE->REG_00H = 0x00001813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x000c0b0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0xc79c2843U);
    SCE->REG_00H = 0x00002123U;
    SCE->REG_104H = 0x00000761U;
    SCE->REG_B0H = 0x00000100U;
    SCE->REG_A4H = 0x00d0c9a7U;
    SCE->REG_D0H = 0x00000100U;
    SCE->REG_C4H = 0x02e087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[0];
    SCE->REG_100H = InData_InstData[1];
    SCE->REG_100H = InData_InstData[2];
    SCE->REG_100H = InData_InstData[3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[4];
    SCE->REG_100H = InData_InstData[5];
    SCE->REG_100H = InData_InstData[6];
    SCE->REG_100H = InData_InstData[7];
    SCE->REG_04H = 0x00000222U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[4] = SCE->REG_100H;
    OutData_KeyIndex[5] = SCE->REG_100H;
    OutData_KeyIndex[6] = SCE->REG_100H;
    OutData_KeyIndex[7] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[8] = SCE->REG_100H;
    OutData_KeyIndex[9] = SCE->REG_100H;
    OutData_KeyIndex[10] = SCE->REG_100H;
    OutData_KeyIndex[11] = SCE->REG_100H;
    HW_SCE_p_func100(0xcdcb485cU, 0x0627d4f7U, 0x347b5891U, 0x85147413U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x000009cdU;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[12] = SCE->REG_100H;
    OutData_KeyIndex[13] = SCE->REG_100H;
    OutData_KeyIndex[14] = SCE->REG_100H;
    OutData_KeyIndex[15] = SCE->REG_100H;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x000049a5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[8];
    SCE->REG_100H = InData_InstData[9];
    SCE->REG_100H = InData_InstData[10];
    SCE->REG_100H = InData_InstData[11];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xce35e0ccU, 0xce384569U, 0xcc4a80b5U, 0x9e2f87e7U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x83ee3e36U, 0xe430b2ddU, 0x106036c8U, 0x0bc240e0U);
        SCE->REG_1B4H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x7b58b8a8U, 0x042cac83U, 0xd07cb197U, 0x23fd4233U);
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_04H = 0x00000612U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[0] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[1] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[2] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[3] = SCE->REG_100H;
        HW_SCE_p_func102(0xc634303dU, 0x59ea7bd7U, 0x7bcb069bU, 0xae32796bU);
        SCE->REG_1B4H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p09.prc
***********************************************************************************************************************/
