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

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header, uint32_t Header_Len)
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
    SCE->REG_84H = 0x00007901U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func001(0xb20a7c92U, 0x1dd2b54fU, 0x6aed6a93U, 0xcccee09dU);
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
    SCE->REG_100H = change_endian_long(0x213f32e4U);
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
    HW_SCE_func001(0x974ff911U, 0xf030adaaU, 0xd37d1bcbU, 0xf5d204d2U);
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
    HW_SCE_func001(0xfe5cb552U, 0xf493318bU, 0x659f1a66U, 0x6b76895bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func003(0x9247c15aU, 0xd573b5a3U, 0x561d0112U, 0x7a4b1e64U);
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
        SCE->REG_A4H = 0x00040885U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        SCE->REG_100H = InData_IV[1];
        SCE->REG_100H = InData_IV[2];
        SCE->REG_100H = InData_IV[3];
        SCE->REG_A4H = 0x00060805U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x0000063cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x00050804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00058c5eU;
        for (iLoop = 0; iLoop < Header_Len; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Header[iLoop + 0];
            SCE->REG_100H = InData_Header[iLoop + 1];
            SCE->REG_100H = InData_Header[iLoop + 2];
            SCE->REG_100H = InData_Header[iLoop + 3];
        }
        HW_SCE_func205();
        HW_SCE_func001(0x327611a5U, 0xfa0ea4a5U, 0x5a23ab4dU, 0x62f55590U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0x4c83bcb3U, 0xf5ed605aU, 0x49f449a1U, 0x25cf72c5U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_00H = 0x00000113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_func002(0xb44b63e2U, 0x29c4463fU, 0x74b891c2U, 0xb0e9a2b5U);
            }
            else
            {
                HW_SCE_func002(0x04228297U, 0xdc09d514U, 0xbfde7f4eU, 0x36f7606bU);
            }
            HW_SCE_func003(0x8685c57bU, 0x697d3074U, 0xef5986aeU, 0x2a8e8ee6U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p79.prc
***********************************************************************************************************************/
