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

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
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
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x9c2bad13U, 0x79b50416U, 0x08b4a371U, 0xa6936ecaU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00000a86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x1f26deedU, 0x56986197U, 0x4d36f8e9U, 0xd2396fe3U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00004a86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x46890128U, 0xa4bea142U, 0x46108c23U, 0x5eb9e253U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00000e96U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xf1e2c1c3U, 0xabc1c083U, 0xb30732a7U, 0x8c59ae8dU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x000049a6U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xb0e543a4U, 0xa63ab851U, 0xb0bb040bU, 0x54ffef58U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x000007b6U;
        SCE->REG_04H = 0x0000c100U;
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Text[0];
    SCE->REG_100H = InData_Text[1];
    SCE->REG_100H = InData_Text[2];
    SCE->REG_100H = InData_Text[3];
    for (iLoop = 4; iLoop < MAX_CNT ; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Text[iLoop + 0];
        SCE->REG_100H = InData_Text[iLoop + 1];
        SCE->REG_100H = InData_Text[iLoop + 2];
        SCE->REG_100H = InData_Text[iLoop + 3];
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_Text[MAX_CNT-4 + 0] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 1] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 2] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 3] = SCE->REG_100H;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x3e045906U, 0x3dab084bU, 0x7f066ce2U, 0xc6491214U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xfb0d3b5cU, 0x665b5756U, 0xf6d445c4U, 0xf1f34104U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xbee7945aU, 0x9846b5c0U, 0x2a31d3d7U, 0xa5080511U);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xe585a470U, 0xf5c70a3aU, 0x81d43f35U, 0xe506b30fU);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x115cf208U, 0xb5af7fdeU, 0x2d878176U, 0xb6d311d0U);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p47u_r1.prc
***********************************************************************************************************************/
