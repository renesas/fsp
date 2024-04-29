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

void HW_SCE_p_func031(uint32_t* ARG1)
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
    SCE->REG_ECH = 0x0000356aU;
    SCE->REG_ECH = 0x0420a960U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x0001696bU;
    SCE->REG_ECH = 0x00036d6bU;
    SCE->REG_ECH = 0x00009160U;
    SCE->REG_ECH = 0x00000042U;
    SCE->REG_ECH = 0x00186d6bU;
    SCE->REG_ECH = 0x00008c60U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x0000106bU;
    SCE->REG_ECH = 0x000010c9U;
    SCE->REG_A4H = 0x00000885U;
    SCE->REG_E0H = 0x81040060U;
    SCE->REG_00H = 0x00001813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_E0H = 0x80840001U;
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00000885U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(ARG1[0]);
    SCE->REG_E0H = 0x80040180U;
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b560U;
    SCE->REG_ECH = 0x00000005U;
    SCE->REG_ECH = 0x01906d6cU;
    SCE->REG_ECH = 0x01906d8dU;
    SCE->REG_ECH = 0x000009adU;
    SCE->REG_ECH = 0x000009ceU;
    SCE->REG_A4H = 0x00000885U;
    SCE->REG_E0H = 0x81040160U;
    SCE->REG_00H = 0x00001813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000a420U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_E0H = 0x80840001U;
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_B0H = 0x00000100U;
    SCE->REG_A4H = 0x00f08807U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_E0H = 0x81880001U;
    SCE->REG_00H = 0x00001823U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func031.prc
***********************************************************************************************************************/
