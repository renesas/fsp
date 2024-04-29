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

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00000601U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func001(0xd5d93ab8U, 0x5a88a67eU, 0x514d1e4bU, 0xcde045a3U);
    SCE->REG_104H = 0x00000251U;
    SCE->REG_A4H = 0x0020363cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x002036bcU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x002036bcU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x00060805U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000151U;
    SCE->REG_A4H = 0x0021340cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x000b0805U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x01000684U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    HW_SCE_func001(0x8ad6ce23U, 0x3b09b780U, 0x36b9f537U, 0x816cdb27U);
    SCE->REG_E0H = 0x80040000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x81040000U;
    SCE->REG_1D0H = 0x00000000U;
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
    SCE->REG_A4H = 0x600c3a0dU;
    SCE->REG_E0H = 0x81040000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_00H = 0x00001813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x400c0a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0xef138998U);
    HW_SCE_func001(0xcdb2986eU, 0x03cf3311U, 0x1ab8e0e1U, 0x00890f96U);
    SCE->REG_104H = 0x00000251U;
    SCE->REG_A4H = 0x0020363cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x002036bcU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x002036bcU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x00060805U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000151U;
    SCE->REG_A4H = 0x0021340cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x000b0805U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x01000684U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    HW_SCE_func001(0x8ff2f5ceU, 0xc3bc59e4U, 0x80415a70U, 0x55935064U);
    SCE->REG_A4H = 0x42e406bdU;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000351U;
    SCE->REG_A4H = 0x400009cdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000001U);
    SCE->REG_04H = 0x00000122U;
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
    HW_SCE_func003(0x7213a768U, 0x20388bc9U, 0xcd2486d5U, 0x98481c7aU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p06.prc
***********************************************************************************************************************/
