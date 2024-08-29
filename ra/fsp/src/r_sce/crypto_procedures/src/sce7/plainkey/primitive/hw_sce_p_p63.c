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

fsp_err_t HW_SCE_GenerateRsa2048PrivateKeyIndexSub(const uint32_t * const InData_KeyType, const uint32_t * const InData_SharedKeyIndex, const uint32_t * const InData_SessionKey, const uint32_t * const InData_IV, const uint32_t * const InData_InstData, uint32_t * const OutData_KeyIndex)
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
    SCE->REG_84H = 0x00006301U;
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
    HW_SCE_p_func100(0x1e2ab0fcU, 0x4798ce04U, 0x996f803dU, 0xf100eaadU);
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
        HW_SCE_p_func100(0x44131e57U, 0xfc4e2927U, 0xb6b35377U, 0xc1a446a0U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x6f0b9c86U, 0x5b3aee32U, 0x43774a72U, 0xfa547042U);
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
            HW_SCE_p_func100(0xd31ebf62U, 0xc0501ba2U, 0xd512a706U, 0x48fd5280U);
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
            HW_SCE_p_func100(0x2613c64bU, 0xdadf8f17U, 0xf87c1134U, 0xbfe0fcb6U);
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
            HW_SCE_p_func100(0xfd2a1375U, 0x43d39c90U, 0xab00651bU, 0x6aa1e9bdU);
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
            HW_SCE_p_func100(0x29ae938bU, 0x0bdb7f02U, 0x5e9a13e8U, 0xfe9b9890U);
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
            HW_SCE_p_func100(0x1a0c72a6U, 0x0445ce13U, 0x970b9658U, 0x86cb48edU);
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
            SCE->REG_A4H = 0x000c0b0cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x3770f901U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x00040804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_00H = 0x00013103U;
            SCE->REG_2CH = 0x00000014U;
            SCE->REG_104H = 0x00003f61U;
            SCE->REG_B0H = 0x00000f00U;
            SCE->REG_A4H = 0x00d0c9a7U;
            for(iLoop=0; iLoop<64; iLoop=iLoop+4)
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
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000024U;
            SCE->REG_D0H = 0x00000f00U;
            SCE->REG_C4H = 0x02f0888fU;
            SCE->REG_04H = 0x00000202U;
            for(iLoop=4; iLoop<68; iLoop=iLoop+4)
            {
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
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0xca328325U, 0x666f07ebU, 0x8ff30fc5U, 0x51eac4d3U);
            SCE->REG_00H = 0x00013103U;
            SCE->REG_2CH = 0x00000010U;
            SCE->REG_104H = 0x00003f61U;
            SCE->REG_B0H = 0x00000f00U;
            SCE->REG_A4H = 0x00d0c9a7U;
            for(iLoop=64; iLoop<128; iLoop=iLoop+4)
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
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            SCE->REG_D0H = 0x00000f00U;
            SCE->REG_C4H = 0x00e087bfU;
            SCE->REG_04H = 0x00000202U;
            for(iLoop=68; iLoop<132; iLoop=iLoop+4)
            {
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
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0x573b1cc5U, 0x93f6b612U, 0xf550cf07U, 0xede7ff67U);
            SCE->REG_18H = 0x00000004U;
            SCE->REG_24H = 0x00004404U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00004804U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000U;
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            SCE->REG_D0H = 0x00000f00U;
            SCE->REG_C4H = 0x00e087bfU;
            SCE->REG_04H = 0x00000202U;
            for(iLoop=132; iLoop<196; iLoop=iLoop+4)
            {
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
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0x3938f327U, 0xf0df9b36U, 0x373e7080U, 0x52d9ccaeU);
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
            OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000049a5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[128];
            SCE->REG_100H = InData_InstData[129];
            SCE->REG_100H = InData_InstData[130];
            SCE->REG_100H = InData_InstData[131];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0x8fb3d4b0U, 0xf6474d44U, 0x6139802fU, 0xd610f73eU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xba465b4dU, 0x0237d120U, 0xf1ec560eU, 0xb365df70U);
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
                HW_SCE_p_func100(0xcad52a7dU, 0x502eb4b0U, 0xc44f8e95U, 0xcf10e420U);
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
                HW_SCE_p_func102(0xc6fb6559U, 0xe397b8acU, 0x40968453U, 0xddc48653U);
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
        HW_SCE_p_func100(0x0f2855feU, 0x1550d39cU, 0x53570274U, 0xa5ea5c9eU);
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
        HW_SCE_p_func100(0xe17c0037U, 0x22a8b605U, 0x3b038618U, 0x87b84978U);
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
        SCE->REG_A4H = 0x000c0b0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x3770f901U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00040804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        SCE->REG_104H = 0x00003f61U;
        SCE->REG_B0H = 0x00000f00U;
        SCE->REG_A4H = 0x00008887U;
        for(iLoop=0; iLoop<64; iLoop=iLoop+4)
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
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x02f0888fU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=4; iLoop<68; iLoop=iLoop+4)
        {
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
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x1aa8e7ceU, 0xa7e70f30U, 0x635fe97eU, 0x5e27b103U);
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00003f61U;
        SCE->REG_B0H = 0x00000f00U;
        SCE->REG_A4H = 0x00008887U;
        for(iLoop=64; iLoop<128; iLoop=iLoop+4)
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
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x00e087bfU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=68; iLoop<132; iLoop=iLoop+4)
        {
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
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x035a48cfU, 0xa5e4dfe2U, 0x47ad508aU, 0x062d0744U);
        SCE->REG_18H = 0x00000004U;
        SCE->REG_24H = 0x00004404U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004804U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x00e087bfU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=132; iLoop<196; iLoop=iLoop+4)
        {
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
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x7cbde324U, 0x977e9a9dU, 0xed48d7bdU, 0x78ee4b98U);
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
        OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
        HW_SCE_p_func100(0x73c082c7U, 0x93a0ca6aU, 0xa15b52cfU, 0x193715d6U);
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
        HW_SCE_p_func102(0x9930e8b5U, 0x13965093U, 0xf848d297U, 0xe8884ed7U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p63.prc
***********************************************************************************************************************/
