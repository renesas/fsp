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

fsp_err_t HW_SCE_Aes256XtsEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    SCE->REG_84H = 0x0000b901U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000b9U);
    HW_SCE_p_func101(0xe8aebccaU, 0x08905231U, 0xd1629beaU, 0xd2afa2c7U);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000b9U);
    HW_SCE_p_func101(0xd3078522U, 0x8c545c34U, 0x21c26adfU, 0xc34e8d5bU);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x6db1b7a5U, 0x42f16527U, 0x6822dfd3U, 0x9fb93cfaU);
    SCE->REG_104H = 0x00000762U;
    SCE->REG_D0H = 0x40000100U;
    SCE->REG_C4H = 0x02f087b7U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[1];
    SCE->REG_100H = InData_KeyIndex[2];
    SCE->REG_100H = InData_KeyIndex[3];
    SCE->REG_100H = InData_KeyIndex[4];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[5];
    SCE->REG_100H = InData_KeyIndex[6];
    SCE->REG_100H = InData_KeyIndex[7];
    SCE->REG_100H = InData_KeyIndex[8];
    SCE->REG_A4H = 0x00080805U;
    SCE->REG_00H = 0x00001213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x88f6f429U, 0x2b207c89U, 0xabb5649aU, 0xbdb82cbaU);
    SCE->REG_A4H = 0x00090805U;
    SCE->REG_00H = 0x00001213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x1d1fce8fU, 0xb058c6bfU, 0xe14da850U, 0xc9294f88U);
    SCE->REG_104H = 0x00000762U;
    SCE->REG_D0H = 0x40000100U;
    SCE->REG_C4H = 0x00f087b7U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[9];
    SCE->REG_100H = InData_KeyIndex[10];
    SCE->REG_100H = InData_KeyIndex[11];
    SCE->REG_100H = InData_KeyIndex[12];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[13];
    SCE->REG_100H = InData_KeyIndex[14];
    SCE->REG_100H = InData_KeyIndex[15];
    SCE->REG_100H = InData_KeyIndex[16];
    SCE->REG_A4H = 0x000a0805U;
    SCE->REG_00H = 0x00001213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x440234afU, 0x93d1de5fU, 0x1a0d0914U, 0xa38cc8c1U);
    SCE->REG_A4H = 0x000b0805U;
    SCE->REG_00H = 0x00001213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000362U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000087b5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[17];
    SCE->REG_100H = InData_KeyIndex[18];
    SCE->REG_100H = InData_KeyIndex[19];
    SCE->REG_100H = InData_KeyIndex[20];
    SCE->REG_C4H = 0x00900c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xa7478611U, 0x403128d9U, 0x156b540eU, 0x45be9252U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xbcd15933U, 0x9fd141b7U, 0xe83eed90U, 0xd38ae4eeU);
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
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0004aa05U;
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pb9i.prc
***********************************************************************************************************************/
