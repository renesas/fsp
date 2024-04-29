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

fsp_err_t HW_SCE_GenerateEccP384PublicKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_CurveType, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    if (0x0U != (SCE->REG_1B4H & 0x1dU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000fb01U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800103e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000fffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xe9b91863U, 0xde4bcb57U, 0x071d4ab2U, 0xc458cec7U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
        SCE->REG_ECH = 0x38008c00U;
        SCE->REG_ECH = 0xfffffff0U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x590bdb24U, 0x6c3cc6a1U, 0x23999b8dU, 0x7933b1f8U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x514eb0d1U, 0xe858d792U, 0xea0040f7U, 0x517d7b03U);
            SCE->REG_1B4H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x26fabe19U, 0x17e9ea7eU, 0x3b34a8e4U, 0x093aea0cU);
            OFS_ADR = InData_SharedKeyIndex[0]*8;
            SCE->REG_C4H = 0x000c3b0cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x3b74d08aU);
            SCE->REG_C4H = 0x000c0b0cU;
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_00H = 0x00002807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x02fb073dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_FLASH[OFS_ADR + 0];
            SCE->REG_100H = S_FLASH[OFS_ADR + 1];
            SCE->REG_100H = S_FLASH[OFS_ADR + 2];
            SCE->REG_100H = S_FLASH[OFS_ADR + 3];
            HW_SCE_p_func100(0x9e02fcafU, 0x1aa4c357U, 0xb881a811U, 0x12b23ce6U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000007bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 0];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 1];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 2];
            SCE->REG_100H = S_FLASH[OFS_ADR+4 + 3];
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
            SCE->REG_100H = InData_SessionKey[0];
            SCE->REG_100H = InData_SessionKey[1];
            SCE->REG_100H = InData_SessionKey[2];
            SCE->REG_100H = InData_SessionKey[3];
            HW_SCE_p_func100(0x9a0bf8d2U, 0xc237d1b5U, 0x80f51df0U, 0x2f6e0538U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00097a05U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SessionKey[4];
            SCE->REG_100H = InData_SessionKey[5];
            SCE->REG_100H = InData_SessionKey[6];
            SCE->REG_100H = InData_SessionKey[7];
            HW_SCE_p_func100(0x70f98d57U, 0xde61fd45U, 0x9115dbc9U, 0x8cb7fc66U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00040805U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00050804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0xcda9b575U, 0x2e962503U, 0x9e2315bcU, 0x0fce4654U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_E0H = 0x80040000U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x200c3b0dU;
            SCE->REG_E0H = 0x81040000U;
            SCE->REG_00H = 0x00001813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010340U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_CurveType[0];
            HW_SCE_p_func077();
            SCE->REG_C4H = 0x000c0b0cU;
            SCE->REG_E0H = 0x810103c0U;
            SCE->REG_00H = 0x00002807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00002153U;
            SCE->REG_104H = 0x00000031U;
            SCE->REG_B0H = 0x00000400U;
            SCE->REG_A4H = 0x00d0c9a7U;
            SCE->REG_D0H = 0x00000400U;
            SCE->REG_C4H = 0x02e0888fU;
            SCE->REG_04H = 0x00000252U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[0];
            SCE->REG_100H = InData_InstData[1];
            SCE->REG_100H = InData_InstData[2];
            SCE->REG_100H = InData_InstData[3];
            for (iLoop = 4; iLoop < 20 ; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[iLoop + 0];
                SCE->REG_100H = InData_InstData[iLoop + 1];
                SCE->REG_100H = InData_InstData[iLoop + 2];
                SCE->REG_100H = InData_InstData[iLoop + 3];
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
            }
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
            SCE->REG_104H = 0x00000000U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_C8H_b.B6)
            {
                /* waiting */
            }
            HW_SCE_p_func100(0x3978fe82U, 0x23f45210U, 0x6a5eb6fbU, 0x5c37e13bU);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x0045094cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_00H = 0x00002113U;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049a5U;
            SCE->REG_C4H = 0x00e0088dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[20];
            SCE->REG_100H = InData_InstData[21];
            SCE->REG_100H = InData_InstData[22];
            SCE->REG_100H = InData_InstData[23];
            SCE->REG_04H = 0x00000212U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[24] = SCE->REG_100H;
            OutData_KeyIndex[25] = SCE->REG_100H;
            OutData_KeyIndex[26] = SCE->REG_100H;
            OutData_KeyIndex[27] = SCE->REG_100H;
            HW_SCE_p_func100(0xb186d35dU, 0x87eb91f6U, 0x7ab4d83cU, 0x95b6848dU);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x00000cc4U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_04H = 0x00000212U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[28] = SCE->REG_100H;
            OutData_KeyIndex[29] = SCE->REG_100H;
            OutData_KeyIndex[30] = SCE->REG_100H;
            OutData_KeyIndex[31] = SCE->REG_100H;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000049a5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[24];
            SCE->REG_100H = InData_InstData[25];
            SCE->REG_100H = InData_InstData[26];
            SCE->REG_100H = InData_InstData[27];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0x035f7777U, 0x6baa9b6fU, 0xf7e39f9cU, 0x1ca8e74bU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x9802c674U, 0xac883a02U, 0x33a331b1U, 0x74b0f19eU);
                SCE->REG_1B4H = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xfdbef610U, 0x415da158U, 0x1ed011e9U, 0x6c78b280U);
                SCE->REG_E0H = 0x81040000U;
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
                HW_SCE_p_func102(0x92c0bc24U, 0xd21ed2abU, 0xe688a0a6U, 0xf9c31ea4U);
                SCE->REG_1B4H = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func100(0x62d7d7cbU, 0xffb6ea53U, 0x9248abf9U, 0xa34aeffbU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x76805b29U, 0xc74e2316U, 0xbd4e8619U, 0x3adc602dU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x200c3b0dU;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00001813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010340U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_CurveType[0];
        HW_SCE_p_func077();
        SCE->REG_C4H = 0x000c0b0cU;
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_00H = 0x00002807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00002153U;
        SCE->REG_104H = 0x00000031U;
        SCE->REG_B0H = 0x00000400U;
        SCE->REG_A4H = 0x00008887U;
        SCE->REG_D0H = 0x00000400U;
        SCE->REG_C4H = 0x02e0888fU;
        SCE->REG_04H = 0x00000252U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[0];
        SCE->REG_100H = InData_InstData[1];
        SCE->REG_100H = InData_InstData[2];
        SCE->REG_100H = InData_InstData[3];
        for (iLoop = 4; iLoop < 20 ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[iLoop + 0];
            SCE->REG_100H = InData_InstData[iLoop + 1];
            SCE->REG_100H = InData_InstData[iLoop + 2];
            SCE->REG_100H = InData_InstData[iLoop + 3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
        SCE->REG_104H = 0x00000000U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xe9322bf3U, 0x3e1722e8U, 0xda682408U, 0xe33534f4U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x0045094cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00002113U;
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00000885U;
        SCE->REG_C4H = 0x00e0088dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[20];
        SCE->REG_100H = InData_InstData[21];
        SCE->REG_100H = InData_InstData[22];
        SCE->REG_100H = InData_InstData[23];
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[24] = SCE->REG_100H;
        OutData_KeyIndex[25] = SCE->REG_100H;
        OutData_KeyIndex[26] = SCE->REG_100H;
        OutData_KeyIndex[27] = SCE->REG_100H;
        HW_SCE_p_func100(0xc4e143d0U, 0x6da34913U, 0x3ec2f188U, 0x040f1b63U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000cc4U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[28] = SCE->REG_100H;
        OutData_KeyIndex[29] = SCE->REG_100H;
        OutData_KeyIndex[30] = SCE->REG_100H;
        OutData_KeyIndex[31] = SCE->REG_100H;
        HW_SCE_p_func100(0x79d7dcc4U, 0xb946e80aU, 0xb7b9e4b5U, 0x4a049bfcU);
        SCE->REG_E0H = 0x81040000U;
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
        HW_SCE_p_func102(0x521dc8e1U, 0x2cfe7212U, 0x45eaef36U, 0xc36d24b3U);
        SCE->REG_1B4H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_pfb_r1.prc
***********************************************************************************************************************/
