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

fsp_err_t HW_SCE_Aes128XtsEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    SCE->REG_84H = 0x0000b301U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func001(0x7a76264dU, 0x29f884a3U, 0x2bdcd3a2U, 0xf9e03db0U);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x600c3a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_100H = InData_KeyIndex[1];
    SCE->REG_100H = InData_KeyIndex[2];
    SCE->REG_100H = InData_KeyIndex[3];
    SCE->REG_A4H = 0x400c0a0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x2d8daf39U);
    SCE->REG_A4H = 0x42f8063dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[4];
    SCE->REG_100H = InData_KeyIndex[5];
    SCE->REG_100H = InData_KeyIndex[6];
    SCE->REG_100H = InData_KeyIndex[7];
    HW_SCE_func001(0x77640d25U, 0x14318a53U, 0x0668c7ebU, 0x022e5cbdU);
    SCE->REG_A4H = 0x40f9063dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[8];
    SCE->REG_100H = InData_KeyIndex[9];
    SCE->REG_100H = InData_KeyIndex[10];
    SCE->REG_100H = InData_KeyIndex[11];
    SCE->REG_A4H = 0x400006bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[12];
    SCE->REG_100H = InData_KeyIndex[13];
    SCE->REG_100H = InData_KeyIndex[14];
    SCE->REG_100H = InData_KeyIndex[15];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_func001(0x1e0b1d16U, 0xd9250389U, 0x73afb6aeU, 0xaf08cd95U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func003(0x9bbda832U, 0x404b9385U, 0x2c45350fU, 0xb3ec64b1U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x0004180dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        SCE->REG_100H = InData_IV[1];
        SCE->REG_100H = InData_IV[2];
        SCE->REG_100H = InData_IV[3];
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_pb3i.prc
***********************************************************************************************************************/
