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

fsp_err_t HW_SCE_UpdateEccPublicKeyIndexSub(const uint32_t * const InData_CurveType, const uint32_t * const InData_Cmd, const uint32_t * const InData_IV, const uint32_t * const InData_InstData, uint32_t * const OutData_KeyIndex)
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
    SCE->REG_84H = 0x00002c01U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0xeb08211dU, 0x1de7ecb6U, 0xdf61583cU, 0xea9b8593U);
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
    HW_SCE_p_func100(0xdc3f5d61U, 0xea67d58cU, 0xd0060027U, 0x2e344008U);
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
    HW_SCE_p_func100(0x652fec16U, 0x7a517723U, 0xb81becf8U, 0x768178a2U);
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
    HW_SCE_p_func100(0x225e30f7U, 0x0021380fU, 0xda58e7adU, 0x193d5c1dU);
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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010380U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    HW_SCE_p_func023_r1();
    SCE->REG_00H = 0x00002133U;
    SCE->REG_104H = 0x00000b61U;
    SCE->REG_B0H = 0x00000200U;
    SCE->REG_A4H = 0x00d0c9a7U;
    SCE->REG_D0H = 0x00000200U;
    SCE->REG_C4H = 0x02e0888fU;
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
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[8];
    SCE->REG_100H = InData_InstData[9];
    SCE->REG_100H = InData_InstData[10];
    SCE->REG_100H = InData_InstData[11];
    SCE->REG_04H = 0x00000232U;
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
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[12] = SCE->REG_100H;
    OutData_KeyIndex[13] = SCE->REG_100H;
    OutData_KeyIndex[14] = SCE->REG_100H;
    OutData_KeyIndex[15] = SCE->REG_100H;
    HW_SCE_p_func100(0x00bb9116U, 0xafd37834U, 0x4dfbfa40U, 0x230ff536U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x0045094cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00002113U;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00d049a5U;
    SCE->REG_C4H = 0x00e0088dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[12];
    SCE->REG_100H = InData_InstData[13];
    SCE->REG_100H = InData_InstData[14];
    SCE->REG_100H = InData_InstData[15];
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[16] = SCE->REG_100H;
    OutData_KeyIndex[17] = SCE->REG_100H;
    OutData_KeyIndex[18] = SCE->REG_100H;
    OutData_KeyIndex[19] = SCE->REG_100H;
    HW_SCE_p_func100(0x9d488d3dU, 0x0cc52d83U, 0x76e336f9U, 0x7fa1467dU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000cc4U;
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
    OutData_KeyIndex[20] = SCE->REG_100H;
    OutData_KeyIndex[21] = SCE->REG_100H;
    OutData_KeyIndex[22] = SCE->REG_100H;
    OutData_KeyIndex[23] = SCE->REG_100H;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x000049a5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_InstData[16];
    SCE->REG_100H = InData_InstData[17];
    SCE->REG_100H = InData_InstData[18];
    SCE->REG_100H = InData_InstData[19];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x5da02d01U, 0xef0033afU, 0xbf1d3cfeU, 0x65894f74U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x661eb0d3U, 0xdf0afa4cU, 0x9ac4bab5U, 0x65543d37U);
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
        HW_SCE_p_func100(0x562e2ee1U, 0xc02a8306U, 0xa4a7644dU, 0x38fd5e6dU);
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
        HW_SCE_p_func102(0x3f87c120U, 0x2cb941dbU, 0xef914017U, 0xcaff2aedU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p2c_r1.prc
***********************************************************************************************************************/
