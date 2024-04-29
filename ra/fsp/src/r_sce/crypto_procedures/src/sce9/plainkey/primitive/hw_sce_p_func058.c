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

void HW_SCE_p_func058(uint32_t* ARG1, uint32_t ARG2)
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
    HW_SCE_p_func100(0xf09a7897U, 0xa3a7a023U, 0x3b7a61fdU, 0x362e6610U);
    SCE->REG_C4H = 0x00443a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x000c3e1cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0174d08aU);
    HW_SCE_p_func100(0x884433ccU, 0x9a27dd57U, 0x8cdc7aa3U, 0xbb2d9912U);
    SCE->REG_ECH = 0x00009020U;
    SCE->REG_ECH = 0x01000000U;
    SCE->REG_C4H = 0x00440a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x000c0e1cU;
    SCE->REG_E0H = 0x81010020U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xa363e8a4U, 0x95c20c4fU, 0x7c0172d7U, 0xdab18365U);
    SCE->REG_A4H = 0x02fb073dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG2 + 0];
    SCE->REG_100H = S_FLASH2[ARG2 + 1];
    SCE->REG_100H = S_FLASH2[ARG2 + 2];
    SCE->REG_100H = S_FLASH2[ARG2 + 3];
    HW_SCE_p_func100(0xc113d43fU, 0x19520dc7U, 0x0b311f0aU, 0x07b8b3c5U);
    SCE->REG_A4H = 0x000007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG2+4 + 0];
    SCE->REG_100H = S_FLASH2[ARG2+4 + 1];
    SCE->REG_100H = S_FLASH2[ARG2+4 + 2];
    SCE->REG_100H = S_FLASH2[ARG2+4 + 3];
    SCE->REG_A4H = 0x00800c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00087a05U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[0];
    SCE->REG_100H = ARG1[1];
    SCE->REG_100H = ARG1[2];
    SCE->REG_100H = ARG1[3];
    HW_SCE_p_func100(0x81625709U, 0x8fa95ce2U, 0xa44190b7U, 0xe2458f05U);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00097a05U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[4];
    SCE->REG_100H = ARG1[5];
    SCE->REG_100H = ARG1[6];
    SCE->REG_100H = ARG1[7];
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func058.prc
***********************************************************************************************************************/
