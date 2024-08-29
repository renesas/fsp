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

fsp_err_t HW_SCE_EcdsaSignatureVerificationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_MsgDgst, const uint32_t *InData_Signature)
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
    SCE->REG_84H = 0x0000f101U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010380U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_104H = 0x00001768U;
    SCE->REG_E0H = 0x8098001eU;
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Signature[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MsgDgst[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_ECH = 0x30003380U;
        SCE->REG_ECH = 0x00070020U;
        SCE->REG_ECH = 0x0000d3e0U;
        SCE->REG_ECH = 0x00030040U;
        SCE->REG_ECH = 0x0000381eU;
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_ECH = 0x1000d3e0U;
        SCE->REG_ECH = 0x00050040U;
        SCE->REG_ECH = 0x0000381eU;
        SCE->REG_ECH = 0x000037beU;
        SCE->REG_ECH = 0x0000a7a0U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x0000383dU;
        SCE->REG_ECH = 0x38001001U;
        SCE->REG_ECH = 0x1000d3e0U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x38000fffU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x0000a7c0U;
        SCE->REG_ECH = 0x00000020U;
    }
    HW_SCE_p_func100(0xb0b636ccU, 0x06be4d1bU, 0x21f8ff29U, 0x1a18b946U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xc99d183cU, 0xe1d21e02U, 0x24e0cf32U, 0xb2a0364fU);
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
        SCE->REG_28H = 0x00870001U;
        SCE->REG_C4H = 0x200c3b0dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[0];
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        HW_SCE_p_func023_r1();
        SCE->REG_104H = 0x00000b62U;
        SCE->REG_D0H = 0x00000200U;
        SCE->REG_C4H = 0x02f0888fU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_00H = 0x00003223U;
        SCE->REG_2CH = 0x0000009bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[12];
        SCE->REG_100H = InData_KeyIndex[13];
        SCE->REG_100H = InData_KeyIndex[14];
        SCE->REG_100H = InData_KeyIndex[15];
        SCE->REG_C4H = 0x0045094cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x00f0088dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[16];
        SCE->REG_100H = InData_KeyIndex[17];
        SCE->REG_100H = InData_KeyIndex[18];
        SCE->REG_100H = InData_KeyIndex[19];
        SCE->REG_00H = 0x00003223U;
        SCE->REG_2CH = 0x00000091U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000362U;
        SCE->REG_C4H = 0x00000885U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[20];
        SCE->REG_100H = InData_KeyIndex[21];
        SCE->REG_100H = InData_KeyIndex[22];
        SCE->REG_100H = InData_KeyIndex[23];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x7be6d5a7U, 0x709a1ee8U, 0x4083fe0dU, 0x0ed50f30U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x7fe8bc3bU, 0x79ac2028U, 0x35cab20aU, 0xbcfbf89bU);
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
            HW_SCE_p_func100(0x8951c09eU, 0x76a89399U, 0xf3e1792dU, 0x212ba941U);
            SCE->REG_7CH = 0x00000011U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000040U;
            SCE->REG_E0H = 0x8188001eU;
            SCE->REG_00H = 0x00005823U;
            SCE->REG_74H = 0x00000004U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x30003340U;
            SCE->REG_ECH = 0x00050020U;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x000004C8U;
            SCE->REG_ECH = 0x00030040U;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x0000031CU;
            SCE->REG_ECH = 0x00070040U;
            SCE->REG_ECH = 0x30003380U;
            SCE->REG_ECH = 0x00070020U;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_ECH = 0x00030040U;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x0000013CU;
            SCE->REG_ECH = 0x00050040U;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x000001F8U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            OFS_ADR = S_RAM[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000f1U);
            HW_SCE_p_func101(0x23efe6a3U, 0xdc3c1c5cU, 0x00a9ff53U, 0x0e3dcaa6U);
            HW_SCE_p_func073(OFS_ADR);
            HW_SCE_p_func100(0x4f116b0bU, 0xbb895738U, 0x9164cf10U, 0x93b4ad27U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x88bf7776U, 0x25383083U, 0xbec214e5U, 0x879b7edaU);
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
                HW_SCE_p_func102(0x75b506f4U, 0x7e15b544U, 0x1d7526faU, 0x4cfa1142U);
                SCE->REG_1BCH = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_pf1_r1.prc
***********************************************************************************************************************/
