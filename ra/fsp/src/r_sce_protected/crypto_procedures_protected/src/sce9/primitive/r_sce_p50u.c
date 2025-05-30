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

void R_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
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
        R_SCE_func100(0x128e5264U, 0x59e9387eU, 0x5fe79e18U, 0x3d15d141U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008a86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        R_SCE_func100(0x3a3a928dU, 0xccbb107eU, 0x999d6b35U, 0xcdff2fd9U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000ca86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        R_SCE_func100(0x84d19817U, 0x81d9c173U, 0x053e9c1bU, 0x65660ffdU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008e96U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        R_SCE_func100(0x2ce0913eU, 0x8dd1daf5U, 0x434a4259U, 0xbeb15720U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000c9a6U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        R_SCE_func100(0xc3bd00d2U, 0xdfcdffe8U, 0x21bfc115U, 0x5220d5e9U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x000087b6U;
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
        R_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0x604b6104U, 0xacdd30b8U, 0x31071817U, 0xf9f45895U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0x9461b710U, 0xe0f6ea4dU, 0x81f18309U, 0xf773a8eeU);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0x96f513bfU, 0x1dd583ddU, 0x8119c69eU, 0x5c42786fU);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0x133a4c90U, 0x78a68808U, 0x0478a49dU, 0xadf672efU);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0x317b2a2eU, 0x5e04d777U, 0xf918ab42U, 0xad0cbde7U);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p50u_r1.prc
***********************************************************************************************************************/
