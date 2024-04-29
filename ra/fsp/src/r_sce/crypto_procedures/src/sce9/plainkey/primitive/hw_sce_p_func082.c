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

void HW_SCE_p_func082(void)
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
    HW_SCE_p_func100(0x288a0959U, 0xc79a1887U, 0x853954b9U, 0x7e94afbcU);
    SCE->REG_ECH = 0x00008d40U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x00009140U;
    SCE->REG_ECH = 0x01000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00442a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x00082e0cU;
    SCE->REG_E0H = 0x81010140U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x33e4bad9U, 0x38eb1f47U, 0x79a7e4a2U, 0x67359c24U);
    SCE->REG_ECH = 0x00008d40U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x00009140U;
    SCE->REG_ECH = 0x02000000U;
    SCE->REG_C4H = 0x00092e0cU;
    SCE->REG_E0H = 0x81010140U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x300032a0U;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000b6e0U;
    SCE->REG_ECH = 0x0104c99cU;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b6e0U;
    SCE->REG_ECH = 0x01ed4879U;
    SCE->REG_ECH = 0x00050040U;
    SCE->REG_ECH = 0x0000b6e0U;
    SCE->REG_ECH = 0x01182e99U;
    SCE->REG_ECH = 0x00000080U;
    HW_SCE_p_func100(0x1d0cd8d2U, 0xccffd8fdU, 0x9f6d5601U, 0xd112a4c4U);
    SCE->REG_ECH = 0x00008ee0U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x000092e0U;
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
    SCE->REG_C4H = 0x00008e94U;
    SCE->REG_E0H = 0x810102e0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00008ee0U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x000092e0U;
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
    SCE->REG_C4H = 0x00098e14U;
    SCE->REG_E0H = 0x810102e0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xb57e7e65U, 0x45bce9a1U, 0x3aa1960dU, 0x4dca1bd0U);
    SCE->REG_C4H = 0x00080805U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xef42db90U, 0xae85650bU, 0xcae14576U, 0xd599e10cU);
    SCE->REG_ECH = 0x00008ec0U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x000092c0U;
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
    SCE->REG_C4H = 0x00008e94U;
    SCE->REG_E0H = 0x810102c0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00008ec0U;
    SCE->REG_ECH = 0x00ffffffU;
    SCE->REG_ECH = 0x000092c0U;
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
    SCE->REG_C4H = 0x00098e14U;
    SCE->REG_E0H = 0x810102c0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x3ce7165fU, 0xd96d579fU, 0x92420e7bU, 0x33a485a2U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func082.prc
***********************************************************************************************************************/
