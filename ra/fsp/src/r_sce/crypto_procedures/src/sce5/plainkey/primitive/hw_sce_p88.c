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

fsp_err_t HW_SCE_GenerateAes256XtsKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00008801U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100e0U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x38000ce7U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func001(0x7812c91cU, 0x79980cf1U, 0x1b960d51U, 0xcb864decU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x38008c00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0xfffffff0U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func001(0x669f2861U, 0x75c7ec15U, 0x001dc3ddU, 0xc7a034e6U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func003(0x6f3ae3deU, 0xf5389f99U, 0xcbee3cecU, 0xa0ccfcb6U);
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
            HW_SCE_func001(0x9f3e45b6U, 0xb4f7f68eU, 0xfd571442U, 0x07c6ffe0U);
            OFS_ADR = InData_SharedKeyIndex[0]*8;
            SCE->REG_A4H = 0x400c3a0cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x129e32e8U);
            SCE->REG_A4H = 0x400c0a0cU;
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00001807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x42fa063dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_FLASH[OFS_ADR + 0];
            SCE->REG_100H = S_FLASH[OFS_ADR + 1];
            SCE->REG_100H = S_FLASH[OFS_ADR + 2];
            SCE->REG_100H = S_FLASH[OFS_ADR + 3];
            HW_SCE_func001(0x9f4c843cU, 0x6c25c292U, 0xc4cabfcfU, 0xfdc89425U);
            SCE->REG_A4H = 0x400006bdU;
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
            SCE->REG_A4H = 0x0008680dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SessionKey[0];
            SCE->REG_100H = InData_SessionKey[1];
            SCE->REG_100H = InData_SessionKey[2];
            SCE->REG_100H = InData_SessionKey[3];
            HW_SCE_func001(0xe467b33aU, 0x68096e86U, 0x69383a5eU, 0x8da81018U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x0009680dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SessionKey[4];
            SCE->REG_100H = InData_SessionKey[5];
            SCE->REG_100H = InData_SessionKey[6];
            SCE->REG_100H = InData_SessionKey[7];
            HW_SCE_func001(0x8ee89e62U, 0x1702b576U, 0x1a47faebU, 0x7cc8590fU);
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
            HW_SCE_func001(0x06b49853U, 0x70fc0efaU, 0xb3d1ffa2U, 0xc8709266U);
            SCE->REG_E0H = 0x80040000U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_100H = change_endian_long(0x5737b943U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[0];
            SCE->REG_100H = InData_InstData[1];
            SCE->REG_100H = InData_InstData[2];
            SCE->REG_100H = InData_InstData[3];
            SCE->REG_A4H = 0x43e006bdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[4] = SCE->REG_100H;
            OutData_KeyIndex[5] = SCE->REG_100H;
            OutData_KeyIndex[6] = SCE->REG_100H;
            OutData_KeyIndex[7] = SCE->REG_100H;
            HW_SCE_func001(0x69969a1eU, 0xa7f2d3c1U, 0x5c53732bU, 0xbe560befU);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[4];
            SCE->REG_100H = InData_InstData[5];
            SCE->REG_100H = InData_InstData[6];
            SCE->REG_100H = InData_InstData[7];
            SCE->REG_A4H = 0x41e006bdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[8] = SCE->REG_100H;
            OutData_KeyIndex[9] = SCE->REG_100H;
            OutData_KeyIndex[10] = SCE->REG_100H;
            OutData_KeyIndex[11] = SCE->REG_100H;
            HW_SCE_func001(0x6b30d18aU, 0x3ffd8b74U, 0x53a78328U, 0x7f0bdc03U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[8];
            SCE->REG_100H = InData_InstData[9];
            SCE->REG_100H = InData_InstData[10];
            SCE->REG_100H = InData_InstData[11];
            SCE->REG_A4H = 0x41e006bdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[12] = SCE->REG_100H;
            OutData_KeyIndex[13] = SCE->REG_100H;
            OutData_KeyIndex[14] = SCE->REG_100H;
            OutData_KeyIndex[15] = SCE->REG_100H;
            HW_SCE_func001(0x2a84f900U, 0x9ee0f1b2U, 0x46ee44bdU, 0xab188c48U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00d049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[12];
            SCE->REG_100H = InData_InstData[13];
            SCE->REG_100H = InData_InstData[14];
            SCE->REG_100H = InData_InstData[15];
            SCE->REG_A4H = 0x41e006bdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[16] = SCE->REG_100H;
            OutData_KeyIndex[17] = SCE->REG_100H;
            OutData_KeyIndex[18] = SCE->REG_100H;
            OutData_KeyIndex[19] = SCE->REG_100H;
            HW_SCE_func001(0x9c7b80c4U, 0x27d73f3eU, 0xc260b8caU, 0x29d7179bU);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x410009cdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[20] = SCE->REG_100H;
            OutData_KeyIndex[21] = SCE->REG_100H;
            OutData_KeyIndex[22] = SCE->REG_100H;
            OutData_KeyIndex[23] = SCE->REG_100H;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[16];
            SCE->REG_100H = InData_InstData[17];
            SCE->REG_100H = InData_InstData[18];
            SCE->REG_100H = InData_InstData[19];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func001(0x6c137248U, 0x2381af58U, 0x32ccda71U, 0xc04f2285U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func003(0x9da4e88aU, 0x51866987U, 0x84b2ac8eU, 0x15009c45U);
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
                HW_SCE_func001(0xdfdc9266U, 0x951e2fceU, 0x3309db47U, 0x9e03e046U);
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
                HW_SCE_func003(0x760a2a2cU, 0xf884a8c2U, 0xf10bfd10U, 0xf9869f9cU);
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
        HW_SCE_func001(0xd3e961caU, 0xa9de9718U, 0xc91035e0U, 0x204ce292U);
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
        HW_SCE_func001(0xfd79cc47U, 0x06880f36U, 0xecc79dcaU, 0x85413a7cU);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00008113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
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
        SCE->REG_100H = change_endian_long(0x5737b943U);
        SCE->REG_104H = 0x00000761U;
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x00008887U;
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
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x43e086bfU;
        SCE->REG_00H = 0x00001123U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
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
        HW_SCE_func001(0xdf816f93U, 0x47525829U, 0x807f9f17U, 0x4c4d33f3U);
        SCE->REG_104H = 0x00000761U;
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x00008887U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[8];
        SCE->REG_100H = InData_InstData[9];
        SCE->REG_100H = InData_InstData[10];
        SCE->REG_100H = InData_InstData[11];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[12];
        SCE->REG_100H = InData_InstData[13];
        SCE->REG_100H = InData_InstData[14];
        SCE->REG_100H = InData_InstData[15];
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x41e086bfU;
        SCE->REG_00H = 0x00001123U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000122U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[12] = SCE->REG_100H;
        OutData_KeyIndex[13] = SCE->REG_100H;
        OutData_KeyIndex[14] = SCE->REG_100H;
        OutData_KeyIndex[15] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[16] = SCE->REG_100H;
        OutData_KeyIndex[17] = SCE->REG_100H;
        OutData_KeyIndex[18] = SCE->REG_100H;
        OutData_KeyIndex[19] = SCE->REG_100H;
        HW_SCE_func001(0x8ba9f501U, 0x099be69dU, 0xf35ba183U, 0x9d0c67a3U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000684U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x410009cdU;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000112U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[20] = SCE->REG_100H;
        OutData_KeyIndex[21] = SCE->REG_100H;
        OutData_KeyIndex[22] = SCE->REG_100H;
        OutData_KeyIndex[23] = SCE->REG_100H;
        HW_SCE_func001(0xa5dc0026U, 0xc1de13a4U, 0x4b1ac6a0U, 0xdc937aa6U);
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
        HW_SCE_func003(0x37122ea1U, 0x54c0dea5U, 0x9aea8f74U, 0x8c4af148U);
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
End of function ./input_dir/HW_SCE_Sec_230630/230630/RA4M1/Cryptographic_PlainKey/HW_SCEp_p88_r1.prc
***********************************************************************************************************************/
