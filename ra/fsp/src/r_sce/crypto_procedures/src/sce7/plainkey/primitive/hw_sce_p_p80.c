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

fsp_err_t HW_SCE_GenerateShaHmacKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00008001U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010140U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x38000d4aU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x8f874159U, 0x2fdc4c98U, 0xea06f82aU, 0xd959cfebU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x870ab47eU, 0xc39387c3U, 0x7e994b74U, 0x2744690cU);
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
        HW_SCE_p_func100(0x2f632985U, 0x1bea500aU, 0x17b80fdaU, 0x7f5bfc59U);
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
            HW_SCE_p_func100(0x74724721U, 0xb9d1424aU, 0x8169f594U, 0xd2102fd9U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xdb2c0240U, 0x27c7f0faU, 0xc01a0280U, 0x83d205b1U);
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
                HW_SCE_p_func100(0xe644aedfU, 0x8b40aa4cU, 0xfa77e060U, 0x5220963aU);
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
                HW_SCE_p_func100(0xd849dee3U, 0x8af17f90U, 0x6e2e4cf8U, 0x4c349156U);
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
                HW_SCE_p_func100(0x0c1bc098U, 0x6d8f416aU, 0x0fe1247dU, 0xfd2ef50bU);
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
                HW_SCE_p_func100(0xad1111e0U, 0xc1b77f4eU, 0x982a9667U, 0x0260c992U);
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
                HW_SCE_p_func100(0x924f9ae9U, 0xf763b41dU, 0xf0674c3cU, 0x61703901U);
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
                SCE->REG_ECH = 0x30003140U;
                SCE->REG_ECH = 0x00070020U;
                SCE->REG_ECH = 0x0000b580U;
                SCE->REG_ECH = 0x5ebc0a4aU;
                SCE->REG_ECH = 0x00030040U;
                SCE->REG_ECH = 0x0000b580U;
                SCE->REG_ECH = 0x2cd7ff9eU;
                SCE->REG_ECH = 0x00050040U;
                SCE->REG_ECH = 0x0000b580U;
                SCE->REG_ECH = 0xe75dd718U;
                SCE->REG_ECH = 0x00000080U;
                SCE->REG_A4H = 0x000c0b0cU;
                SCE->REG_E0H = 0x81010180U;
                SCE->REG_00H = 0x00001807U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x00002123U;
                SCE->REG_104H = 0x00000761U;
                SCE->REG_B0H = 0x00000100U;
                SCE->REG_A4H = 0x00d0c9a7U;
                SCE->REG_D0H = 0x00000100U;
                SCE->REG_C4H = 0x02e087bfU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[0];
                SCE->REG_100H = InData_InstData[1];
                SCE->REG_100H = InData_InstData[2];
                SCE->REG_100H = InData_InstData[3];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[4];
                SCE->REG_100H = InData_InstData[5];
                SCE->REG_100H = InData_InstData[6];
                SCE->REG_100H = InData_InstData[7];
                SCE->REG_04H = 0x00000222U;
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
                HW_SCE_p_func100(0x8d1c093cU, 0xc5f30dc7U, 0x3bddab28U, 0x84fd99a8U);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_C4H = 0x000009cdU;
                SCE->REG_00H = 0x00002213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000212U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[12] = SCE->REG_100H;
                OutData_KeyIndex[13] = SCE->REG_100H;
                OutData_KeyIndex[14] = SCE->REG_100H;
                OutData_KeyIndex[15] = SCE->REG_100H;
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x000049a5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[8];
                SCE->REG_100H = InData_InstData[9];
                SCE->REG_100H = InData_InstData[10];
                SCE->REG_100H = InData_InstData[11];
                SCE->REG_A4H = 0x00900c45U;
                SCE->REG_00H = 0x00001113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func100(0xf64b9501U, 0x89d369c7U, 0xaa689849U, 0xed47ba50U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x327d1355U, 0xb50e098bU, 0xf015b60cU, 0x51e032ebU);
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
                    HW_SCE_p_func100(0xa2816772U, 0x69164c79U, 0x4322c20fU, 0x99afe7faU);
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
                    HW_SCE_p_func102(0x3bc51b87U, 0xbd8be8d3U, 0xd97300f0U, 0xd2dc6920U);
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
        else
        {
            HW_SCE_p_func100(0xf3e8b472U, 0x19879bc2U, 0xcf6e064dU, 0x40a5d5afU);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0x0156965fU, 0x6f35f795U, 0x6702bbd3U, 0x3ec29938U);
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
            SCE->REG_ECH = 0x30003140U;
            SCE->REG_ECH = 0x00070020U;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x5ebc0a4aU;
            SCE->REG_ECH = 0x00030040U;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x2cd7ff9eU;
            SCE->REG_ECH = 0x00050040U;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0xe75dd718U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_A4H = 0x000c0b0cU;
            SCE->REG_E0H = 0x81010180U;
            SCE->REG_00H = 0x00001807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00002123U;
            SCE->REG_104H = 0x00000761U;
            SCE->REG_B0H = 0x00000100U;
            SCE->REG_A4H = 0x00008887U;
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x02e087bfU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[0];
            SCE->REG_100H = InData_InstData[1];
            SCE->REG_100H = InData_InstData[2];
            SCE->REG_100H = InData_InstData[3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[4];
            SCE->REG_100H = InData_InstData[5];
            SCE->REG_100H = InData_InstData[6];
            SCE->REG_100H = InData_InstData[7];
            SCE->REG_04H = 0x00000222U;
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
            HW_SCE_p_func100(0xdb115765U, 0xb3060c86U, 0xd75bcbb1U, 0x739a2352U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x00000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_C4H = 0x000009cdU;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000212U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[12] = SCE->REG_100H;
            OutData_KeyIndex[13] = SCE->REG_100H;
            OutData_KeyIndex[14] = SCE->REG_100H;
            OutData_KeyIndex[15] = SCE->REG_100H;
            HW_SCE_p_func100(0x93d83fe1U, 0x4533c893U, 0xe5a58f88U, 0xe063bc61U);
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
            HW_SCE_p_func102(0x23d2e60bU, 0xd33f1dfdU, 0xaad6f1cfU, 0x1c861df9U);
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

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p80.prc
***********************************************************************************************************************/
