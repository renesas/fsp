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

void HW_SCE_p_func043(void)
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
    HW_SCE_p_func100(0x763017c1U, 0xa6e06e5cU, 0x413ee7c5U, 0x8be19d82U);
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x000001d0U;
    SCE->REG_E0H = 0x8188000aU;
    SCE->REG_C4H = 0x00080805U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x661813d3U, 0x1f0216ddU, 0xdb1c9067U, 0xe4e2daeeU);
    SCE->REG_C4H = 0x00090805U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x41d550f1U, 0x3237f543U, 0x559f9bcaU, 0x9aceaba9U);
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x000001c0U;
    SCE->REG_E0H = 0x8184000aU;
    SCE->REG_C4H = 0x000c0805U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x3778e67fU, 0x59eb9657U, 0x649d9837U, 0x6e6ab952U);
    SCE->REG_C4H = 0x00000b8cU;
    SCE->REG_E0H = 0x810100e0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x80040140U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00008d40U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x00009140U;
    SCE->REG_ECH = 0x01000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00448a04U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00008e95U;
    SCE->REG_E0H = 0x81040140U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00008d40U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x00009140U;
    SCE->REG_ECH = 0x02000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00448a04U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00098e15U;
    SCE->REG_E0H = 0x81040140U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x1bbad22dU, 0xbc25efb7U, 0x0737ee54U, 0x5dcc4009U);
    SCE->REG_C4H = 0x00080805U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func043.prc
***********************************************************************************************************************/
