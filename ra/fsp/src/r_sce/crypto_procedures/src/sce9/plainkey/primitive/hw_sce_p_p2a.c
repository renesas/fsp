/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

fsp_err_t HW_SCE_GenerateRsa1024RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey)
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
    (void)InData_KeyType;
    (void)OutData_PrivKey;
    (void)OutData_PubKey;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00002a02U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0x1fb96e46U, 0x081cd081U, 0x2c72f4dfU, 0x551f4d99U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x14b1e394U, 0xa13506a4U, 0xc5cb4cb4U, 0x2e6ee502U);
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
        SCE->REG_28H = 0x008f0001U;
        HW_SCE_p_func100(0x97b4f88fU, 0xb43c6e83U, 0x2e5860f1U, 0x42fe8c0cU);
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
        for(iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
        {
            HW_SCE_p_func100(0x308272beU, 0x6a7b49c2U, 0x120117f1U, 0xfe0313a7U);
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
            HW_SCE_p_func101(0xd899a1dfU, 0xa6e04f54U, 0x5174433eU, 0x40deffdcU);
        }
        HW_SCE_p_func100(0x308272beU, 0x6a7b49c2U, 0x120117f1U, 0xfe0313a7U);
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
        SCE->REG_104H = 0x00000f57U;
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
        SCE->REG_100H = change_endian_long(0x851EB80EU);
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
        HW_SCE_p_func100(0xad29dc62U, 0x0efb107eU, 0xad45984bU, 0xb49321bbU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xac9f0956U, 0xd2467c51U, 0x139a5b33U, 0xad785449U);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0x6c659b24U, 0x4e425a0bU, 0x78cf416eU, 0x1366a62eU);
        }
        SCE->REG_ECH = 0x38008a20U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0xa8a7649dU, 0xbfe63421U, 0x3e720722U, 0x6ab5239cU);
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
            HW_SCE_p_func100(0x0f3fc6fdU, 0xb94153a9U, 0x267af091U, 0x7db2ba05U);
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
                HW_SCE_p_func101(0xde3bcf5aU, 0x2f1f00e9U, 0x67567a04U, 0x307ad1d8U);
            }
            else
            {
                HW_SCE_p_func101(0xfb19a96fU, 0x17e46b20U, 0xe1ed13b4U, 0x48b60152U);
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
            SCE->REG_00H = 0x00003033U;
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
            HW_SCE_p_func100(0xf3ee43c9U, 0xf16a715eU, 0x486b5890U, 0xd5adc75bU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xf200cb28U, 0x95d383b6U, 0xefa1d7dcU, 0xe342fa1cU);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0x5432a6acU, 0x895f0a01U, 0x4c3d350eU, 0x9a286873U);
            }
        }
        else
        {
            HW_SCE_p_func101(0xdfeb4c53U, 0x0d1d5003U, 0x408103edU, 0xf7b9246fU);
        }
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_ECH = 0x0000094aU;
        for(iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003906U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_E0H = 0x81010100U;
            SCE->REG_00H = 0x0000303fU;
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
            HW_SCE_p_func100(0x73ebecc7U, 0xe9f73cb5U, 0x23a2c07eU, 0xf7a27c65U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000d140U;
                HW_SCE_p_func101(0x27a0a5bcU, 0xbd7a7e0cU, 0xa9945f33U, 0xfac352e2U);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x1b68ddf4U, 0xece9a003U, 0x07503ca5U, 0x598ef5a0U);
            }
        }
        SCE->REG_ECH = 0x38008940U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0xa317c927U, 0xd88de3a5U, 0x5415605eU, 0x29024848U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xed43d36fU, 0xc0df89a1U, 0xed4fd39cU, 0x4476573fU);
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
        SCE->REG_00H = 0x0000303fU;
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
        HW_SCE_p_func100(0x81022f02U, 0xc55d4dd3U, 0x69032594U, 0x79d605bdU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xaaca257cU, 0xe78596ceU, 0x6cb19cd6U, 0xf50757cdU);
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
            SCE->REG_24H = 0x000084d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x8002d008U;
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
            HW_SCE_p_func100(0x94f41beeU, 0x2e70fadcU, 0x5251259aU, 0xf8b94a36U);
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
            HW_SCE_p_func100(0xb2101807U, 0xd8841e13U, 0x363690f8U, 0xdee420d3U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0x982bb79bU, 0x9640a6c4U, 0xa57f90b7U, 0xf71592fcU);
                continue;
            }
            SCE->REG_24H = 0x000098d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b540U;
            SCE->REG_ECH = 0x000000c0U;
            SCE->REG_E0H = 0x8090000aU;
            SCE->REG_00H = 0x00008343U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000006U;
            SCE->REG_B0H = 0x00000300U;
            SCE->REG_A4H = 0x42e0873fU;
            SCE->REG_00H = 0x00001343U;
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
            HW_SCE_p_func100(0x76cc74d4U, 0x59965208U, 0xe8a7d87fU, 0xe1b57d3fU);
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
                HW_SCE_p_func101(0x72781bc6U, 0x9c1a437cU, 0xa9733a1fU, 0x0f79bf92U);
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
                HW_SCE_p_func101(0xdfbfd057U, 0xac57bef0U, 0x66b482d0U, 0xb4279a72U);
            }
            HW_SCE_p_func100(0x19ecc5efU, 0x50046f94U, 0xe53fb3f6U, 0x6a4007c6U);
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
                HW_SCE_p_func101(0x677321ffU, 0x1a5b95e6U, 0xbe47d278U, 0x83345c77U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0x67ca3062U, 0xf487c1d4U, 0x252ffbc7U, 0x56f4d158U);
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
                HW_SCE_p_func101(0x51f1fe67U, 0x2b55f583U, 0xd0183856U, 0xc41ef963U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0x1982eb37U, 0x311f8a6eU, 0xafe2e477U, 0xdbb76737U);
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000a52U;
            SCE->REG_24H = 0x000084d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00029008U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x8000c0c1U;
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
                for(jLoop = 0; jLoop < 16; jLoop = jLoop + 4)
                {
                    HW_SCE_p_func100(0x370e2528U, 0x09215692U, 0x397fbe80U, 0xa0361021U);
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
                    HW_SCE_p_func101(0x68612f15U, 0x2b99ae27U, 0xc6a90302U, 0x863b3725U);
                }
                HW_SCE_p_func100(0x4709ca31U, 0x0b2e9badU, 0xc932ddc3U, 0x5be0cd9eU);
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
                SCE->REG_24H = 0x000050d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000084d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00029008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800U;
                SCE->REG_24H = 0x8000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000088d0U;
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
                SCE->REG_24H = 0x000050d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000084d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00029008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800U;
                SCE->REG_24H = 0x8000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000088d0U;
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
                HW_SCE_p_func100(0xc20c2b7fU, 0xdeb9736dU, 0x6a1e227dU, 0x7ac1cb13U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00002e40U;
                    HW_SCE_p_func101(0xd9901c60U, 0x6bbf8f3bU, 0xe80eadd2U, 0x38cd54f7U);
                }
                else
                {
                    HW_SCE_p_func100(0x6ed922bfU, 0x5b4e139aU, 0x12a11497U, 0x9b7b9fcfU);
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
                        HW_SCE_p_func100(0xf9c188d9U, 0xc11afd0aU, 0x99af0d6bU, 0x3c2358b0U);
                        SCE->REG_1CH = 0x00400000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (0U == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_ECH = 0x00002e40U;
                            HW_SCE_p_func101(0xbb7d1ae6U, 0x6b1ece1fU, 0xe857ed7eU, 0x96c8652bU);
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
                            HW_SCE_p_func101(0xff623b76U, 0x9bbd89b4U, 0xfc27bd0bU, 0x36ae4523U);
                        }
                    }
                    SCE->REG_ECH = 0x38008a40U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    HW_SCE_p_func100(0xa47cd66bU, 0x9cba44dcU, 0x319d67e8U, 0x8b1db386U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func101(0x944c4aa1U, 0x49fa5f7fU, 0xef1e79adU, 0xea096376U);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0x04739207U, 0x06ed1bc5U, 0x4dca20d1U, 0xa82347d7U);
                    }
                }
            }
            SCE->REG_ECH = 0x38000a4bU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x0001d18bU, 0xdf6784e1U, 0xace4ad69U, 0xc469425fU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00002e20U;
                SCE->REG_ECH = 0x38008a20U;
                SCE->REG_ECH = 0x00000002U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                HW_SCE_p_func100(0x6e3d15b3U, 0xb4dc0c86U, 0x833b7f90U, 0xa1055b37U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func101(0xe5a62450U, 0x16727ebbU, 0xcba7d912U, 0x52ca8212U);
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
                    HW_SCE_p_func101(0x49d15384U, 0x78db1911U, 0x4fd8119aU, 0x0db65cc9U);
                }
            }
            else
            {
                HW_SCE_p_func101(0xc924b0c3U, 0x337001bfU, 0x6902ba7dU, 0x183a6dd3U);
            }
        }
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xeb2ab658U, 0x65d21d66U, 0x0da6fa4fU, 0x7c925b48U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x88da49e3U, 0x4801ae72U, 0xfaf4d9caU, 0xa218a591U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    HW_SCE_p_func100(0x2ab47987U, 0xd77f2a5aU, 0xaa782e07U, 0xfc61b4c4U);
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
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000020U;
    SCE->REG_24H = 0x800019c0U;
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
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_D0H = 0x00000700U;
    SCE->REG_C4H = 0x42e087bfU;
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000024U;
    SCE->REG_04H = 0x00000282U;
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
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
    HW_SCE_p_func100(0xfc99d2e6U, 0x32ae5f36U, 0x12a184f3U, 0xbc2c702dU);
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
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_24H = 0x0000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e8d0U;
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
        HW_SCE_p_func100(0x27480881U, 0xba71af30U, 0x7d92b8a1U, 0x7019b6b9U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xe75dda89U, 0x15caa1deU, 0x7558f29eU, 0x3fd0d6c9U);
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
            HW_SCE_p_func101(0x715b495bU, 0x1f5cd765U, 0xf202b576U, 0x98d0b8faU);
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
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000980aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
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
    SCE->REG_28H = 0x009f0001U;
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
    SCE->REG_24H = 0x0000e0c1U;
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
        HW_SCE_p_func100(0x17a24cd5U, 0xc54f82dfU, 0xbe2fe3e4U, 0xf93aca4dU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xb289e5d1U, 0x24522af0U, 0x229710feU, 0xba1709edU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01090c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_ECH = 0x0000094aU;
        SCE->REG_E0H = 0x80a0000aU;
        SCE->REG_00H = 0x00008383U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x7daefa82U, 0x521af0cfU, 0x4dba7417U, 0xd27b184bU);
        SCE->REG_D0H = 0x00000700U;
        SCE->REG_C4H = 0x42e097bfU;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000282U;
        for (iLoop=36; iLoop<68; iLoop=iLoop+4)
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
        HW_SCE_p_func100(0xb3fbcaa6U, 0x69ad23d1U, 0x003c5402U, 0xb99ced8fU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x400019cdU;
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
        SCE->REG_28H = 0x008f0001U;
        SCE->REG_24H = 0x00001dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080c1U;
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
        HW_SCE_p_func100(0x3077c994U, 0x7d4f1137U, 0x4e3cc110U, 0xcdb09089U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_28H = 0x008f0001U;
            SCE->REG_104H = 0x00001f61U;
            SCE->REG_B0H = 0x00000700U;
            SCE->REG_A4H = 0x42f087bfU;
            SCE->REG_00H = 0x00003143U;
            SCE->REG_2CH = 0x00000015U;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
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
            SCE->REG_00H = 0x00003143U;
            SCE->REG_2CH = 0x00000014U;
            for (iLoop = 16; iLoop < 32; iLoop = iLoop + 4)
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
            HW_SCE_p_func101(0x994c1884U, 0xed7fc7d5U, 0x31e198f6U, 0x9eb6897bU);
            break;
        }
        else
        {
            SCE->REG_28H = 0x008f0001U;
            SCE->REG_34H = 0x00000008U;
            SCE->REG_24H = 0x800011c0U;
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
            SCE->REG_00H = 0x00003043U;
            SCE->REG_2CH = 0x00000018U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_24H = 0x0000890eU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_104H = 0x00001f62U;
            SCE->REG_D0H = 0x00000700U;
            SCE->REG_C4H = 0x42f097bfU;
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            for (iLoop=36; iLoop<68; iLoop=iLoop+4)
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
            SCE->REG_C4H = 0x400017bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_HEAP[iLoop + 0];
            SCE->REG_100H = S_HEAP[iLoop + 1];
            SCE->REG_100H = S_HEAP[iLoop + 2];
            SCE->REG_100H = S_HEAP[iLoop + 3];
            SCE->REG_C4H = 0x00800c45U;
            SCE->REG_00H = 0x00002213U;
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
            SCE->REG_24H = 0x00001de1U;
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
            SCE->REG_E0H = 0x81a0000aU;
            SCE->REG_00H = 0x00003883U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0xb2b28a0dU, 0x98773ad8U, 0xd4aee07aU, 0x833efbc7U);
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
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x800088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
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
    SCE->REG_24H = 0x0000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000ccd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
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
    HW_SCE_p_func100(0x199771aaU, 0xba49ce89U, 0x936a86c8U, 0x61b0297fU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func100(0x2428d673U, 0x343e5be4U, 0x37f8e3f4U, 0x3d94b370U);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_00H = 0x00008207U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000020fU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034e0U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000002aU);
        HW_SCE_p_func101(0x71fbd176U, 0xdecc2073U, 0xfbde9f70U, 0x46b5d07cU);
        HW_SCE_p_func043();
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0000000aU;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000002aU);
        HW_SCE_p_func101(0x25eab0a7U, 0xeedf4e4eU, 0x3974534bU, 0x0e853059U);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x5fa2ac2fU, 0x6180b08bU, 0xf3ee3300U, 0x50d5a863U);
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func100(0x43fce02eU, 0xe24f9819U, 0x798bdf21U, 0xa246cc05U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00040804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x02e08887U;
        SCE->REG_04H = 0x00000282U;
        for(iLoop=0; iLoop<32; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x4c66c6ddU, 0xdd3f0015U, 0x4ca8409fU, 0x5aa5e529U);
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00e08884U;
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
        OutData_PubKeyIndex[33] = SCE->REG_100H;
        OutData_PubKeyIndex[34] = SCE->REG_100H;
        OutData_PubKeyIndex[35] = SCE->REG_100H;
        OutData_PubKeyIndex[36] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x7bc8803aU, 0xa0137578U, 0x1fbde34cU, 0x64e0ae17U);
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
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x00e087b7U;
        SCE->REG_04H = 0x00000282U;
        for(iLoop=36; iLoop<68; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
            OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x95d33a9dU, 0x038dc668U, 0x6841f86eU, 0x6bc4d8bfU);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000089c5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000008U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[69] = SCE->REG_100H;
        OutData_PubKeyIndex[70] = SCE->REG_100H;
        OutData_PubKeyIndex[71] = SCE->REG_100H;
        OutData_PubKeyIndex[72] = SCE->REG_100H;
        HW_SCE_p_func100(0xa243fb38U, 0xcfdc8352U, 0x176677d7U, 0x85951b62U);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_00H = 0x00008207U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000020fU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034e0U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000020U);
        HW_SCE_p_func101(0x7a9d80ffU, 0x776a4124U, 0xcfc0d8f1U, 0x9bf14cedU);
        HW_SCE_p_func043();
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0000000bU;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000020U);
        HW_SCE_p_func101(0x929ba5deU, 0x944d881aU, 0xf081b692U, 0x45370d03U);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0xebd0a0d1U, 0xa766c73eU, 0xcf0b6fc3U, 0xfe03f64cU);
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func100(0xc3d5ecb2U, 0x59e1d7d8U, 0xc3576c47U, 0x841cac4cU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x02e087b7U;
        SCE->REG_04H = 0x00000282U;
        for(iLoop=0; iLoop<32; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xfd08ea8dU, 0x5cd52b2cU, 0xa51f9128U, 0x9cff4242U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x00e087b7U;
        SCE->REG_04H = 0x00000282U;
        for(iLoop=32; iLoop<64; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x58c81937U, 0xea52e29aU, 0x933261f7U, 0x57282707U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x00e087b7U;
        SCE->REG_04H = 0x00000282U;
        for(iLoop=64; iLoop<96; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
            OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x8e9798bbU, 0x1429dce1U, 0x33bad5e8U, 0x2c23ef01U);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000089c5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000018U);
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[97] = SCE->REG_100H;
        OutData_PrivKeyIndex[98] = SCE->REG_100H;
        OutData_PrivKeyIndex[99] = SCE->REG_100H;
        OutData_PrivKeyIndex[100] = SCE->REG_100H;
        HW_SCE_p_func101(0x19c5d3ccU, 0x8f6947f6U, 0x7fc75e21U, 0x894c7d8fU);
    }
    else
    {
        HW_SCE_p_func100(0xef40ee55U, 0x7e91fb78U, 0x13ed610fU, 0x36352957U);
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_04H = 0x00000382U;
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
        HW_SCE_p_func100(0xd4d4a3e5U, 0xc1caa233U, 0x44a9433dU, 0x7ee31e97U);
        SCE->REG_E0H = 0x810101c0U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKey[32] = SCE->REG_100H;
        HW_SCE_p_func100(0xe512b7eeU, 0xda4e182aU, 0x7db535aeU, 0xf498200bU);
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000382U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKey[0] = SCE->REG_100H;
        OutData_PrivKey[1] = SCE->REG_100H;
        OutData_PrivKey[2] = SCE->REG_100H;
        OutData_PrivKey[3] = SCE->REG_100H;
        OutData_PrivKey[4] = SCE->REG_100H;
        OutData_PrivKey[5] = SCE->REG_100H;
        OutData_PrivKey[6] = SCE->REG_100H;
        OutData_PrivKey[7] = SCE->REG_100H;
        OutData_PrivKey[8] = SCE->REG_100H;
        OutData_PrivKey[9] = SCE->REG_100H;
        OutData_PrivKey[10] = SCE->REG_100H;
        OutData_PrivKey[11] = SCE->REG_100H;
        OutData_PrivKey[12] = SCE->REG_100H;
        OutData_PrivKey[13] = SCE->REG_100H;
        OutData_PrivKey[14] = SCE->REG_100H;
        OutData_PrivKey[15] = SCE->REG_100H;
        OutData_PrivKey[16] = SCE->REG_100H;
        OutData_PrivKey[17] = SCE->REG_100H;
        OutData_PrivKey[18] = SCE->REG_100H;
        OutData_PrivKey[19] = SCE->REG_100H;
        OutData_PrivKey[20] = SCE->REG_100H;
        OutData_PrivKey[21] = SCE->REG_100H;
        OutData_PrivKey[22] = SCE->REG_100H;
        OutData_PrivKey[23] = SCE->REG_100H;
        OutData_PrivKey[24] = SCE->REG_100H;
        OutData_PrivKey[25] = SCE->REG_100H;
        OutData_PrivKey[26] = SCE->REG_100H;
        OutData_PrivKey[27] = SCE->REG_100H;
        OutData_PrivKey[28] = SCE->REG_100H;
        OutData_PrivKey[29] = SCE->REG_100H;
        OutData_PrivKey[30] = SCE->REG_100H;
        OutData_PrivKey[31] = SCE->REG_100H;
        HW_SCE_p_func101(0xc0b9810bU, 0xe3f47f17U, 0xda3eedf4U, 0x17e7ac29U);
    }
    HW_SCE_p_func102(0x24aaab1aU, 0x93acdb7bU, 0x9b21b62cU, 0x89da253fU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p2a_r3.prc
***********************************************************************************************************************/
