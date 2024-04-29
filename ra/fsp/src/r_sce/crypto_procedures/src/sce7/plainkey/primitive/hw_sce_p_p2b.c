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

fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey)
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
    SCE->REG_84H = 0x00002b01U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_C4H = 0x200e1a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[16+0 + 0];
    SCE->REG_100H = S_RAM[16+0 + 1];
    SCE->REG_100H = S_RAM[16+0 + 2];
    SCE->REG_100H = S_RAM[16+0 + 3];
    HW_SCE_p_func100(0x87f66336U, 0x5e6c8d41U, 0xb063aad4U, 0xdf921b16U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x104d0ff9U, 0xcf1c36cbU, 0x936cdf9aU, 0xb93a745dU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01080c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x00000a31U;
    for(kLoop = 0; kLoop < MAX_CNT; kLoop = kLoop + 1)
    {
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00003043U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00002f57U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00030005U);
        SCE->REG_100H = change_endian_long(0x0007000bU);
        SCE->REG_100H = change_endian_long(0x000d0011U);
        SCE->REG_100H = change_endian_long(0x00130017U);
        SCE->REG_100H = change_endian_long(0x001d001fU);
        SCE->REG_100H = change_endian_long(0x00250029U);
        SCE->REG_100H = change_endian_long(0x002b002fU);
        SCE->REG_100H = change_endian_long(0x003b003dU);
        SCE->REG_100H = change_endian_long(0x00430047U);
        SCE->REG_100H = change_endian_long(0x0049004fU);
        SCE->REG_100H = change_endian_long(0x00530059U);
        SCE->REG_100H = change_endian_long(0x00610065U);
        SCE->REG_100H = change_endian_long(0x0067006bU);
        SCE->REG_100H = change_endian_long(0x006d0071U);
        SCE->REG_100H = change_endian_long(0x007f0083U);
        SCE->REG_100H = change_endian_long(0x0089008bU);
        SCE->REG_100H = change_endian_long(0x00950097U);
        SCE->REG_100H = change_endian_long(0x009d00a3U);
        SCE->REG_100H = change_endian_long(0x00a700adU);
        SCE->REG_100H = change_endian_long(0x00b300b5U);
        SCE->REG_100H = change_endian_long(0x00bf00c1U);
        SCE->REG_100H = change_endian_long(0x00c500c7U);
        SCE->REG_100H = change_endian_long(0x00d300dfU);
        SCE->REG_100H = change_endian_long(0x00e300e5U);
        SCE->REG_100H = change_endian_long(0x00e900efU);
        SCE->REG_100H = change_endian_long(0x00f100fbU);
        SCE->REG_100H = change_endian_long(0x01010107U);
        SCE->REG_100H = change_endian_long(0x010d010fU);
        SCE->REG_100H = change_endian_long(0x01150119U);
        SCE->REG_100H = change_endian_long(0x011b0125U);
        SCE->REG_100H = change_endian_long(0x01330137U);
        SCE->REG_100H = change_endian_long(0x0139013dU);
        SCE->REG_100H = change_endian_long(0x014b0151U);
        SCE->REG_100H = change_endian_long(0x015b015dU);
        SCE->REG_100H = change_endian_long(0x01610167U);
        SCE->REG_100H = change_endian_long(0x016f0175U);
        SCE->REG_100H = change_endian_long(0x017b017fU);
        SCE->REG_100H = change_endian_long(0x0185018dU);
        SCE->REG_100H = change_endian_long(0x01910199U);
        SCE->REG_100H = change_endian_long(0x01a301a5U);
        SCE->REG_100H = change_endian_long(0x01af01b1U);
        SCE->REG_100H = change_endian_long(0x01b701bbU);
        SCE->REG_100H = change_endian_long(0x01c101c9U);
        SCE->REG_100H = change_endian_long(0x01cd01cfU);
        SCE->REG_100H = change_endian_long(0x01d301dfU);
        SCE->REG_100H = change_endian_long(0x01e701ebU);
        SCE->REG_100H = change_endian_long(0x01f301f7U);
        SCE->REG_100H = change_endian_long(0x01fd0000U);
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_00H = 0x00000343U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x80b00006U;
        SCE->REG_00H = 0x000083c3U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x009f0001U;
        HW_SCE_p_func100(0x4e879db7U, 0xeb38d9dbU, 0xd55ad423U, 0xe4d32dd7U);
        HW_SCE_p_func103();
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
        SCE->REG_ECH = 0x0000d01fU;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00003813U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        for(iLoop = 0; iLoop < 24; iLoop = iLoop + 4)
        {
            HW_SCE_p_func100(0xaf5ac32cU, 0xbee15071U, 0x5e416c25U, 0x6a535d70U);
            HW_SCE_p_func103();
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_00H = 0x00003213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0xe4e3755cU, 0x7832c133U, 0x87dc96c3U, 0xc262582cU);
        }
        HW_SCE_p_func100(0xaf5ac32cU, 0xbee15071U, 0x5e416c25U, 0x6a535d70U);
        HW_SCE_p_func103();
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
        SCE->REG_ECH = 0x0000d060U;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00003813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000011U;
        SCE->REG_104H = 0x00001f57U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xB51EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851B5CU);
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        HW_SCE_p_func100(0xd9f2f2a1U, 0x40f65967U, 0x448e15bfU, 0x7822cde1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xa102a2feU, 0x2e2dbb05U, 0x3f4e32bdU, 0xa10d8427U);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0xd00f58efU, 0x272a63a8U, 0x924c09e1U, 0x5eed9803U);
        }
        SCE->REG_ECH = 0x38008a20U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0xdaa7c509U, 0x83fca19bU, 0xb0391ae1U, 0xb9f28b81U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_24H = 0x00001dc0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            HW_SCE_p_func100(0xdc5dd9b7U, 0x9152cba4U, 0x68872535U, 0x4614082aU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001d91U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                HW_SCE_p_func101(0x95648165U, 0x24613c1eU, 0x5ee12859U, 0x3b2efc46U);
            }
            else
            {
                HW_SCE_p_func101(0x38037408U, 0xfbe20dbcU, 0xe785200aU, 0x9d3a860fU);
            }
            SCE->REG_2CH = 0x00000011U;
            SCE->REG_104H = 0x00000357U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x10000000U);
            SCE->REG_00H = 0x00003073U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x00001591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            HW_SCE_p_func100(0xa398b0a3U, 0x676829cfU, 0x6ace5505U, 0x8b90cb88U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0x8d94ea7dU, 0x02e0a843U, 0x2741425fU, 0x48561c10U);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0xedf2a487U, 0xfc9c5a81U, 0xc5c93d44U, 0xe50930c2U);
            }
        }
        else
        {
            HW_SCE_p_func101(0xf79a777eU, 0xff56efdfU, 0x7903a24cU, 0xdfb2b1daU);
        }
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_ECH = 0x0000094aU;
        for(iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003906U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_E0H = 0x81010100U;
            SCE->REG_00H = 0x0000307fU;
            SCE->REG_2CH = 0x00000014U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00003807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x00004006U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            HW_SCE_p_func100(0x77d33b7bU, 0x884a7db1U, 0xf863818aU, 0x7fe77a02U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000d140U;
                HW_SCE_p_func101(0x434c6580U, 0xb1b43e10U, 0x9d761074U, 0x1d53ee86U);
                break;
            }
            else
            {
                HW_SCE_p_func101(0xc0c2695eU, 0x9dc152acU, 0x09c36f8dU, 0x2d87bca6U);
            }
        }
        SCE->REG_ECH = 0x38008940U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x29920fb2U, 0x0b42bea7U, 0x49f7adc3U, 0xf06b865eU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x152278d8U, 0x3d28a66bU, 0xf768188bU, 0xbd928a0fU);
            continue;
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000060c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x0000307fU;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000057U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00010001U);
        SCE->REG_24H = 0x00004006U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        HW_SCE_p_func100(0x51e0c9bbU, 0x54bbe768U, 0x1ae64793U, 0x4ef9d446U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x26298165U, 0xbff13118U, 0x96ab4b90U, 0x12ac2c41U);
        }
        else
        {
            SCE->REG_24H = 0x0000d0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000005c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000189U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            HW_SCE_p_func100(0x84a7f093U, 0xd16db4e2U, 0x35eee086U, 0x30402e38U);
            SCE->REG_18H = 0x00000004U;
            SCE->REG_38H = 0x00004080U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000U;
            SCE->REG_24H = 0x000005c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            SCE->REG_24H = 0x000044d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            HW_SCE_p_func100(0x775afa10U, 0x8406324fU, 0x78faa20fU, 0x783f06faU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0x42bc5cc6U, 0x3bc06925U, 0xa7be24dcU, 0xac32367eU);
                continue;
            }
            SCE->REG_24H = 0x000098d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b540U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x80a0000aU;
            SCE->REG_00H = 0x00008383U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_B0H = 0x00000700U;
            SCE->REG_A4H = 0x42e0873fU;
            SCE->REG_00H = 0x00001383U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x400009cdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x38008a20U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xf9177845U, 0x25b7d085U, 0x51a32d72U, 0xea549a61U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_7CH = 0x00000021U;
                SCE->REG_00H = 0x00005113U;
                SCE->REG_74H = 0x00000004U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0x3ae090b2U, 0xcf98d542U, 0x6d463780U, 0x47168d21U);
            }
            else
            {
                SCE->REG_7CH = 0x00000041U;
                SCE->REG_00H = 0x00005113U;
                SCE->REG_74H = 0x00000004U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0xa9b8629dU, 0x74bc98afU, 0x06f01307U, 0xbd7e4a23U);
            }
            HW_SCE_p_func100(0xd32dbe05U, 0x132d0a79U, 0x0f3efb3cU, 0x3b48e486U);
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000c0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000929U;
            SCE->REG_ECH = 0x0000b4c0U;
            SCE->REG_ECH = 0x000000fcU;
            SCE->REG_ECH = 0x00003906U;
            SCE->REG_ECH = 0x00008d00U;
            SCE->REG_ECH = 0xfffffffeU;
            SCE->REG_ECH = 0x00003d06U;
            SCE->REG_ECH = 0x00000908U;
            for(iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                SCE->REG_ECH = 0x000038e6U;
                SCE->REG_ECH = 0x0000a8c0U;
                SCE->REG_ECH = 0x00000004U;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x38008900U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_ECH = 0x11816907U;
                    SCE->REG_ECH = 0x38008900U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_ECH = 0x10002d20U;
                    SCE->REG_ECH = 0x000168e7U;
                }
            }
            SCE->REG_ECH = 0x00003549U;
            SCE->REG_ECH = 0x0000a540U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_ECH = 0x0002694aU;
            SCE->REG_E0H = 0x81010140U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eaU;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0U;
                HW_SCE_p_func101(0xaef5d5b9U, 0xa763ccfdU, 0x6f5accccU, 0x6ed38598U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0xdf47bdc2U, 0x3f4f89a9U, 0xc0585d15U, 0x519d022cU);
            SCE->REG_ECH = 0x00026d4aU;
            SCE->REG_ECH = 0x00002949U;
            SCE->REG_E0H = 0x81010140U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eaU;
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x2000018dU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0U;
                HW_SCE_p_func101(0xf06b64faU, 0xb4a3b8f9U, 0xc1561e26U, 0xe4c314d0U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0xda322662U, 0xe321d270U, 0xb0366a25U, 0x30c644e1U);
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000a52U;
            SCE->REG_24H = 0x00006404U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00006c04U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_E0H = 0x81010160U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_2CH = 0x00000010U;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 4)
                {
                    HW_SCE_p_func100(0x20fc3652U, 0x0aff835fU, 0x9bc2fd13U, 0xe42cb124U);
                    HW_SCE_p_func103();
                    SCE->REG_104H = 0x00000052U;
                    SCE->REG_C4H = 0x01000c84U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000000U);
                    SCE->REG_00H = 0x00003213U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    HW_SCE_p_func101(0x9838cc7fU, 0x1c68bfbeU, 0x50830d45U, 0x23d8634fU);
                }
                HW_SCE_p_func100(0x25e3b750U, 0x347238f5U, 0x2b68810eU, 0xfa4b780fU);
                SCE->REG_24H = 0x000019c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00009008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000dc0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000004U;
                SCE->REG_38H = 0x00000c40U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B10)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000000U;
                SCE->REG_24H = 0x000005c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000U;
                SCE->REG_24H = 0x000005c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000991U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000U;
                HW_SCE_p_func100(0x6293a1feU, 0xf19af248U, 0x8deb6fdcU, 0x32e5971eU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00002e40U;
                    HW_SCE_p_func101(0xa07b491dU, 0x82f1c8e5U, 0x9ed56ec3U, 0x9f235e5fU);
                }
                else
                {
                    HW_SCE_p_func100(0x54ba99e6U, 0xba2f571dU, 0x118311c9U, 0x16801dc6U);
                    SCE->REG_24H = 0x000019c0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000591U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006404U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006c04U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_E0H = 0x81010120U;
                    SCE->REG_04H = 0x00000606U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    S_RAM[0+1 + 0] = change_endian_long(SCE->REG_100H);
                    SCE->REG_ECH = 0x000037e9U;
                    for(jLoop = 0; jLoop < (int32_t)S_RAM[0+1]; jLoop = jLoop + 1)
                    {
                        SCE->REG_24H = 0x000009c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001191U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        SCE->REG_24H = 0x000011c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000991U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        HW_SCE_p_func100(0x282eb745U, 0xd1f092e8U, 0xbeba435fU, 0x9b7883a9U);
                        SCE->REG_1CH = 0x00400000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (0U == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_ECH = 0x00002e40U;
                            HW_SCE_p_func101(0xd0bd2165U, 0xf5cb79c7U, 0x8ac18c73U, 0x0d958853U);
                            break;
                        }
                        else
                        {
                            SCE->REG_24H = 0x00004c0cU;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x0000880cU;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x000019c0U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x00000591U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x000040c1U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            HW_SCE_p_func101(0xc8f93f1cU, 0x07512df4U, 0x3e0ef72dU, 0xe8ad4a84U);
                        }
                    }
                    SCE->REG_ECH = 0x38008a40U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    HW_SCE_p_func100(0x37be8570U, 0x1893dcfbU, 0xf02b291dU, 0xc09f8eb6U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func101(0x04fa0359U, 0x315ffdd1U, 0xb4c2e4e0U, 0x6a1be820U);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0xcfd975a7U, 0xbc954c09U, 0xa1162f60U, 0x8930166aU);
                    }
                }
            }
            SCE->REG_ECH = 0x38000a4bU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x8b55d94aU, 0xf4afdd5dU, 0xfe685e9dU, 0x35b3f23aU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00002e20U;
                SCE->REG_ECH = 0x38008a20U;
                SCE->REG_ECH = 0x00000002U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                HW_SCE_p_func100(0x0cb343b5U, 0xe9ac1fdfU, 0x83995bebU, 0x32957379U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func101(0x5448d2bbU, 0xc839d1ccU, 0x85158bf2U, 0x3a74bfe8U);
                    break;
                }
                else
                {
                    SCE->REG_24H = 0x000019c0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000e0c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    HW_SCE_p_func101(0x397ab211U, 0xcaf704d4U, 0xf3508d2dU, 0x9d6cc8c0U);
                }
            }
            else
            {
                HW_SCE_p_func101(0xc2ec6363U, 0x75f46576U, 0x20f38dc5U, 0x82a16b12U);
            }
        }
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x8b128d04U, 0x95e16387U, 0xfcddaa01U, 0x6d17a7eaU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x821f2a88U, 0xd3f20f42U, 0x8278ba01U, 0xa350c690U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    HW_SCE_p_func100(0x25f60c07U, 0x22cef610U, 0xef6b566aU, 0xbfb1acdeU);
    SCE->REG_ECH = 0x0000b5c0U;
    SCE->REG_ECH = 0x00010001U;
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001dc0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_D0H = 0x00000f00U;
    SCE->REG_C4H = 0x42e087bfU;
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    SCE->REG_04H = 0x00000202U;
    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
    }
    HW_SCE_p_func100(0xad0d17e4U, 0x6174e0deU, 0x64eea02eU, 0xaa174b5eU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x400009cdU;
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
    S_HEAP[iLoop + 0] = SCE->REG_100H;
    S_HEAP[iLoop + 1] = SCE->REG_100H;
    S_HEAP[iLoop + 2] = SCE->REG_100H;
    S_HEAP[iLoop + 3] = SCE->REG_100H;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    while(1)
    {
        SCE->REG_24H = 0x00008006U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        HW_SCE_p_func100(0x82178655U, 0xbf0a1769U, 0x72ab41caU, 0xc330d37cU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xa6dcc290U, 0x1f8ff542U, 0xed3a5088U, 0x96c6a174U);
            break;
        }
        else
        {
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000d0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            HW_SCE_p_func101(0x29d04231U, 0xd7c085dcU, 0xc0dbd2eeU, 0xc1be18d3U);
        }
    }
    SCE->REG_24H = 0x000094d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000c002U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000b80aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_00H = 0x000030ffU;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000057U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00010001U);
    SCE->REG_2CH = 0x00000002U;
    SCE->REG_24H = 0x0000c002U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_E0H = 0x800100c0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000024U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b500U;
    SCE->REG_ECH = 0x00010001U;
    SCE->REG_24H = 0x000005c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    while(1)
    {
        SCE->REG_ECH = 0x0000094aU;
        SCE->REG_E0H = 0x80c0000aU;
        SCE->REG_00H = 0x00018303U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_B0H = 0x00000f14U;
        SCE->REG_A4H = 0x00008a07U;
        SCE->REG_00H = 0x00011303U;
        SCE->REG_2CH = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        SCE->REG_00H = 0x0000301fU;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x810100c0U;
        SCE->REG_00H = 0x00003807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000301fU;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x81010100U;
        SCE->REG_00H = 0x00003807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000000U;
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000c002U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00003506U;
        SCE->REG_E0H = 0x800100c0U;
        SCE->REG_00H = 0x0000031fU;
        SCE->REG_2CH = 0x0000002cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00008307U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x380088c0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0xb2862bbbU, 0xfb537cbeU, 0xf140017cU, 0xb187853aU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_104H = 0x00003f61U;
            SCE->REG_B0H = 0x00000f00U;
            SCE->REG_A4H = 0x42f087bfU;
            SCE->REG_00H = 0x00013103U;
            SCE->REG_2CH = 0x00000014U;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_HEAP[iLoop + 0];
                SCE->REG_100H = S_HEAP[iLoop + 1];
                SCE->REG_100H = S_HEAP[iLoop + 2];
                SCE->REG_100H = S_HEAP[iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0xe9aa7747U, 0x73029c13U, 0x2f095c17U, 0x1e5481feU);
            break;
        }
        else
        {
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_24H = 0x000015c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000c0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_00H = 0x00003083U;
            SCE->REG_2CH = 0x00000011U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x0000880eU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_D0H = 0x00000f1cU;
            SCE->REG_C4H = 0x00008a83U;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000094aU;
            SCE->REG_E0H = 0x81c0000aU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0x3ce5bcdcU, 0xd61671eaU, 0xcf47b2ceU, 0x2c3ae511U);
        }
    }
    SCE->REG_ECH = 0x00007c06U;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_A4H = 0x400007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[iLoop + 0];
    SCE->REG_100H = S_HEAP[iLoop + 1];
    SCE->REG_100H = S_HEAP[iLoop + 2];
    SCE->REG_100H = S_HEAP[iLoop + 3];
    SCE->REG_A4H = 0x00800c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_B0H = 0x00000714U;
    SCE->REG_A4H = 0x00008a07U;
    SCE->REG_00H = 0x00001383U;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_B0H = 0x08000714U;
    SCE->REG_A4H = 0x00008a07U;
    SCE->REG_00H = 0x00001383U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000b8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000002U;
    SCE->REG_24H = 0x00007b0aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0xfcbf0001U;
    SCE->REG_24H = 0x0000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
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
    HW_SCE_p_func100(0x7981796eU, 0x7312beebU, 0xd95d688cU, 0x316f0af6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func100(0x0c51636dU, 0x077c5417U, 0xd727e6b7U, 0xe543d0f8U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xd82a871eU, 0x88f112e8U, 0x82e1559eU, 0xef0c5ec3U);
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
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_04H = 0x00000612U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[0] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[1] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[2] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[3] = SCE->REG_100H;
        HW_SCE_p_func100(0x1983ed05U, 0x3703f6a2U, 0x41bd9969U, 0x031e74f7U);
        SCE->REG_C4H = 0x200c3b0dU;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00002813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x000c0b0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x671c43cbU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00040804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x02f0888fU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=0; iLoop<64; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[iLoop+4 + 0] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 1] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 2] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x33aca7e4U, 0x65f8b042U, 0x3a00f36dU, 0x52166832U);
        SCE->REG_C4H = 0x00f0088cU;
        SCE->REG_E0H = 0x810101c0U;
        SCE->REG_00H = 0x00002807U;
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
        OutData_PubKeyIndex[68] = SCE->REG_100H;
        OutData_PubKeyIndex[69] = SCE->REG_100H;
        OutData_PubKeyIndex[70] = SCE->REG_100H;
        OutData_PubKeyIndex[71] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x6f8d6188U, 0xed5c3bd8U, 0x30037b0dU, 0xa0347e72U);
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
        for(iLoop=68; iLoop<132; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[iLoop+4 + 0] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 1] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 2] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+4 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x9f754466U, 0x83a68f97U, 0x23002e6aU, 0x21e94ce2U);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x000009cdU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000010U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[136] = SCE->REG_100H;
        OutData_PubKeyIndex[137] = SCE->REG_100H;
        OutData_PubKeyIndex[138] = SCE->REG_100H;
        OutData_PubKeyIndex[139] = SCE->REG_100H;
        HW_SCE_p_func100(0xfd57bf92U, 0x6a704becU, 0xa697c073U, 0x9ca8728cU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xea9ba7e6U, 0xf02720acU, 0xc36e61adU, 0x8809dc8bU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x800401e0U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x810401e0U;
        SCE->REG_04H = 0x00000612U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[0] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[1] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[2] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[3] = SCE->REG_100H;
        HW_SCE_p_func100(0x45b3e457U, 0x949ee7b0U, 0xeede5a23U, 0xa3ee19dbU);
        SCE->REG_C4H = 0x200c3b0dU;
        SCE->REG_E0H = 0x810401e0U;
        SCE->REG_00H = 0x00002813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x000c0b0cU;
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
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x02f0888fU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=0; iLoop<64; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+4 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x805deae7U, 0x1aaa9481U, 0x9283d1b4U, 0x88b3eb95U);
        SCE->REG_B0H = 0x00000f1cU;
        SCE->REG_A4H = 0x00008a83U;
        SCE->REG_00H = 0x00012103U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x00e087bfU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=64; iLoop<128; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+4 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xdb4117daU, 0x6e992562U, 0x79ddd579U, 0xb54dccccU);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x00e087bfU;
        SCE->REG_04H = 0x00000202U;
        for(iLoop=128; iLoop<192; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+4 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+4 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x957e1fa7U, 0x3c9a4930U, 0xdc7b7b5fU, 0x91f493b5U);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x000009cdU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000020U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[196] = SCE->REG_100H;
        OutData_PrivKeyIndex[197] = SCE->REG_100H;
        OutData_PrivKeyIndex[198] = SCE->REG_100H;
        OutData_PrivKeyIndex[199] = SCE->REG_100H;
        HW_SCE_p_func101(0xbc5b725fU, 0x81771ffbU, 0x5d3f5bd1U, 0xa660df40U);
    }
    else
    {
        HW_SCE_p_func100(0x213239aeU, 0xaf413dffU, 0xc8a8651dU, 0xc565c1b2U);
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_04H = 0x00000302U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKey[0] = SCE->REG_100H;
        OutData_PubKey[1] = SCE->REG_100H;
        OutData_PubKey[2] = SCE->REG_100H;
        OutData_PubKey[3] = SCE->REG_100H;
        OutData_PubKey[4] = SCE->REG_100H;
        OutData_PubKey[5] = SCE->REG_100H;
        OutData_PubKey[6] = SCE->REG_100H;
        OutData_PubKey[7] = SCE->REG_100H;
        OutData_PubKey[8] = SCE->REG_100H;
        OutData_PubKey[9] = SCE->REG_100H;
        OutData_PubKey[10] = SCE->REG_100H;
        OutData_PubKey[11] = SCE->REG_100H;
        OutData_PubKey[12] = SCE->REG_100H;
        OutData_PubKey[13] = SCE->REG_100H;
        OutData_PubKey[14] = SCE->REG_100H;
        OutData_PubKey[15] = SCE->REG_100H;
        OutData_PubKey[16] = SCE->REG_100H;
        OutData_PubKey[17] = SCE->REG_100H;
        OutData_PubKey[18] = SCE->REG_100H;
        OutData_PubKey[19] = SCE->REG_100H;
        OutData_PubKey[20] = SCE->REG_100H;
        OutData_PubKey[21] = SCE->REG_100H;
        OutData_PubKey[22] = SCE->REG_100H;
        OutData_PubKey[23] = SCE->REG_100H;
        OutData_PubKey[24] = SCE->REG_100H;
        OutData_PubKey[25] = SCE->REG_100H;
        OutData_PubKey[26] = SCE->REG_100H;
        OutData_PubKey[27] = SCE->REG_100H;
        OutData_PubKey[28] = SCE->REG_100H;
        OutData_PubKey[29] = SCE->REG_100H;
        OutData_PubKey[30] = SCE->REG_100H;
        OutData_PubKey[31] = SCE->REG_100H;
        OutData_PubKey[32] = SCE->REG_100H;
        OutData_PubKey[33] = SCE->REG_100H;
        OutData_PubKey[34] = SCE->REG_100H;
        OutData_PubKey[35] = SCE->REG_100H;
        OutData_PubKey[36] = SCE->REG_100H;
        OutData_PubKey[37] = SCE->REG_100H;
        OutData_PubKey[38] = SCE->REG_100H;
        OutData_PubKey[39] = SCE->REG_100H;
        OutData_PubKey[40] = SCE->REG_100H;
        OutData_PubKey[41] = SCE->REG_100H;
        OutData_PubKey[42] = SCE->REG_100H;
        OutData_PubKey[43] = SCE->REG_100H;
        OutData_PubKey[44] = SCE->REG_100H;
        OutData_PubKey[45] = SCE->REG_100H;
        OutData_PubKey[46] = SCE->REG_100H;
        OutData_PubKey[47] = SCE->REG_100H;
        OutData_PubKey[48] = SCE->REG_100H;
        OutData_PubKey[49] = SCE->REG_100H;
        OutData_PubKey[50] = SCE->REG_100H;
        OutData_PubKey[51] = SCE->REG_100H;
        OutData_PubKey[52] = SCE->REG_100H;
        OutData_PubKey[53] = SCE->REG_100H;
        OutData_PubKey[54] = SCE->REG_100H;
        OutData_PubKey[55] = SCE->REG_100H;
        OutData_PubKey[56] = SCE->REG_100H;
        OutData_PubKey[57] = SCE->REG_100H;
        OutData_PubKey[58] = SCE->REG_100H;
        OutData_PubKey[59] = SCE->REG_100H;
        OutData_PubKey[60] = SCE->REG_100H;
        OutData_PubKey[61] = SCE->REG_100H;
        OutData_PubKey[62] = SCE->REG_100H;
        OutData_PubKey[63] = SCE->REG_100H;
        HW_SCE_p_func100(0x54c2d3d0U, 0x4102ebd4U, 0xe51f6e81U, 0xa2e369b7U);
        SCE->REG_E0H = 0x810101c0U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKey[64] = SCE->REG_100H;
        HW_SCE_p_func100(0x6e329914U, 0xbf504e79U, 0xcfc24c43U, 0x818cd04aU);
        SCE->REG_B0H = 0x00000f1cU;
        SCE->REG_A4H = 0x00008a83U;
        SCE->REG_04H = 0x00000102U;
        for(iLoop=0; iLoop<64; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKey[iLoop + 0] = SCE->REG_100H;
            OutData_PrivKey[iLoop + 1] = SCE->REG_100H;
            OutData_PrivKey[iLoop + 2] = SCE->REG_100H;
            OutData_PrivKey[iLoop + 3] = SCE->REG_100H;
        }
        HW_SCE_p_func101(0x54902792U, 0x237c010fU, 0x5901ad1fU, 0x538a871aU);
    }
    HW_SCE_p_func102(0x758dcc89U, 0xf02025acU, 0xd01e3b30U, 0x5cc2179fU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p2b_r1.prc
***********************************************************************************************************************/
