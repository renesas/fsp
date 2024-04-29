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

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey)
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
    (void)OutData_PubKey;
    (void)OutData_PrivKey;
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000f902U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0xba8ae618U, 0x5d822127U, 0xa6afe272U, 0x6caf7220U);
    SCE->REG_28H = 0x008b0001U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_ECH = 0x38000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x000002B4U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x000003D8U;
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
    HW_SCE_p_func100(0x0b6231a1U, 0x4082f030U, 0x48c52f06U, 0x5326581dU);
    HW_SCE_p_func027_r2(OFS_ADR);
    HW_SCE_p_func100(0x0b7f37d0U, 0xd0a2a81eU, 0x474b3adfU, 0x9178501bU);
    SCE->REG_28H = 0x008d0001U;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x41340726U, 0x77095143U, 0x72576630U, 0x93c93c46U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    SCE->REG_2CH = 0x00000011U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xe7d4d41fU, 0x6983ba59U, 0x15f1cca4U, 0xf5ee9a3eU);
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
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xb89c36f1U, 0xebc180b7U, 0xd992e7d8U, 0x4a0de3e7U);
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
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x0000320bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
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
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000004U;
    SCE->REG_24H = 0x0000a206U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000U;
    SCE->REG_24H = 0x000016c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000682U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c2U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x008b0001U;
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000820U;
    SCE->REG_24H = 0x80009cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0x3d1a8336U, 0x622e0f62U, 0xb1697e91U, 0xa005292fU);
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00021028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
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
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00004404U;
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
    SCE->REG_34H = 0x00000808U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func028_r2(OFS_ADR);
    HW_SCE_p_func100(0x64d66971U, 0x64ca9b9eU, 0x5940c872U, 0x204325b7U);
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x800088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x8000acd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000021U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x00000842U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x00000180U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f9U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_E0H = 0x81010380U;
    SCE->REG_04H = 0x00000607U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    for(iLoop=0;iLoop<384;iLoop=iLoop+1)
    {
        HW_SCE_p_func101(0xdbe796a4U, 0x6b1d9355U, 0xf4fd2662U, 0xd98cb7d6U);
        HW_SCE_p_func300();
        if (S_RAM[0] == 0x00000001U)
        {
            break;
        }
        HW_SCE_p_func101(0xc0de3a65U, 0xfe27f27fU, 0x4d239102U, 0xb50f0d0aU);
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
    SCE->REG_1CH = 0x00001f00U;
    SCE->REG_1CH = 0x00210000U;
    HW_SCE_p_func100(0x1daa4a2dU, 0x7ce5aa27U, 0xa5415a80U, 0x914b2f17U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x162e3ccbU, 0x2f9a1e6fU, 0x693474d6U, 0x94d238e3U);
        SCE->REG_1B8H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_24H = 0x00001dc0U;
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
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000f4d0U;
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
        SCE->REG_24H = 0x00005004U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00008404U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x808c001fU;
        SCE->REG_00H = 0x00008333U;
        SCE->REG_2CH = 0x00000021U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        for(iLoop=0; iLoop<12; iLoop=iLoop+1)
        {
            SCE->REG_ECH = 0x0000381fU;
            for(jLoop=0; jLoop<32; jLoop=jLoop+1)
            {
                SCE->REG_24H = 0x0000102cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1U;
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
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x3800d81fU;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00A60000U;
                SCE->REG_ECH = 0x00016c00U;
                HW_SCE_p_func100(0x8f9c2a77U, 0xf33844d5U, 0x8455d6fdU, 0x13143ad2U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_24H = 0x0000082cU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1U;
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
                    SCE->REG_24H = 0x000080c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    HW_SCE_p_func101(0x86ef67c2U, 0xe8cf24d0U, 0x37804e2aU, 0xf098530dU);
                }
                else
                {
                    HW_SCE_p_func101(0xf2132842U, 0x74acefcdU, 0x0c004a87U, 0x08b9d513U);
                }
            }
            SCE->REG_ECH = 0x000027e1U;
            HW_SCE_p_func101(0x01c83fafU, 0xef7c4381U, 0x10d53a54U, 0x051e247eU);
        }
        SCE->REG_ECH = 0x00008be0U;
        SCE->REG_ECH = 0x00000030U;
        SCE->REG_ECH = 0x00007c1fU;
        SCE->REG_1CH = 0x00602000U;
        HW_SCE_p_func301();
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
        HW_SCE_p_func100(0xce707779U, 0xfb460c41U, 0xe67274ebU, 0xc8a74ae1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func100(0x0ad1252dU, 0x3da91055U, 0x5c2dc575U, 0x14254972U);
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
            SCE->REG_100H = change_endian_long(0x000000f9U);
            HW_SCE_p_func101(0xd454d93aU, 0xf70736dcU, 0xb0a1febbU, 0xc00b81f0U);
            HW_SCE_p_func043();
            HW_SCE_p_func076();
            SCE->REG_ECH = 0x000034feU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000f9U);
            HW_SCE_p_func101(0xa5113cbeU, 0x6d527565U, 0x8445bbf4U, 0xa1034407U);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x6762285cU, 0x0d4cf93dU, 0xa3506f40U, 0x1ceecb69U);
            SCE->REG_D0H = 0x40000200U;
            SCE->REG_C4H = 0x02e087b7U;
            SCE->REG_00H = 0x00002333U;
            SCE->REG_2CH = 0x0000002dU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000232U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[1] = SCE->REG_100H;
            OutData_PrivKeyIndex[2] = SCE->REG_100H;
            OutData_PrivKeyIndex[3] = SCE->REG_100H;
            OutData_PrivKeyIndex[4] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[5] = SCE->REG_100H;
            OutData_PrivKeyIndex[6] = SCE->REG_100H;
            OutData_PrivKeyIndex[7] = SCE->REG_100H;
            OutData_PrivKeyIndex[8] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[9] = SCE->REG_100H;
            OutData_PrivKeyIndex[10] = SCE->REG_100H;
            OutData_PrivKeyIndex[11] = SCE->REG_100H;
            OutData_PrivKeyIndex[12] = SCE->REG_100H;
            HW_SCE_p_func100(0xe81c9889U, 0x67692950U, 0xbe826a22U, 0x2e8a4dbeU);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x00000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000089c5U;
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
            OutData_PrivKeyIndex[13] = SCE->REG_100H;
            OutData_PrivKeyIndex[14] = SCE->REG_100H;
            OutData_PrivKeyIndex[15] = SCE->REG_100H;
            OutData_PrivKeyIndex[16] = SCE->REG_100H;
            HW_SCE_p_func100(0x13b2eeb6U, 0xc897657dU, 0x440a39ffU, 0xa369cdd9U);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[0] = SCE->REG_100H;
            HW_SCE_p_func100(0x5582f747U, 0x39e01cb7U, 0x3691c4c7U, 0xe0da29edU);
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
            SCE->REG_100H = change_endian_long(0x00000027U);
            HW_SCE_p_func101(0x70f41c99U, 0xba1e2bc7U, 0xa7b2ae76U, 0xe6f2e9fcU);
            HW_SCE_p_func043();
            HW_SCE_p_func077();
            SCE->REG_ECH = 0x000034feU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000028U);
            HW_SCE_p_func101(0x2cabf676U, 0x643a1a6bU, 0xb94816b0U, 0xd195fadaU);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x3901d920U, 0x63dad967U, 0x365fd72cU, 0x2905477dU);
            SCE->REG_D0H = 0x40000200U;
            SCE->REG_C4H = 0x02e08887U;
            SCE->REG_00H = 0x00002333U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000232U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[1] = SCE->REG_100H;
            OutData_PubKeyIndex[2] = SCE->REG_100H;
            OutData_PubKeyIndex[3] = SCE->REG_100H;
            OutData_PubKeyIndex[4] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[5] = SCE->REG_100H;
            OutData_PubKeyIndex[6] = SCE->REG_100H;
            OutData_PubKeyIndex[7] = SCE->REG_100H;
            OutData_PubKeyIndex[8] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[9] = SCE->REG_100H;
            OutData_PubKeyIndex[10] = SCE->REG_100H;
            OutData_PubKeyIndex[11] = SCE->REG_100H;
            OutData_PubKeyIndex[12] = SCE->REG_100H;
            HW_SCE_p_func100(0xdc1ff7abU, 0x50b66339U, 0x2bc1b6f1U, 0x0303639fU);
            SCE->REG_D0H = 0x40000200U;
            SCE->REG_C4H = 0x00e08887U;
            SCE->REG_00H = 0x00002333U;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000232U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[13] = SCE->REG_100H;
            OutData_PubKeyIndex[14] = SCE->REG_100H;
            OutData_PubKeyIndex[15] = SCE->REG_100H;
            OutData_PubKeyIndex[16] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[17] = SCE->REG_100H;
            OutData_PubKeyIndex[18] = SCE->REG_100H;
            OutData_PubKeyIndex[19] = SCE->REG_100H;
            OutData_PubKeyIndex[20] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[21] = SCE->REG_100H;
            OutData_PubKeyIndex[22] = SCE->REG_100H;
            OutData_PubKeyIndex[23] = SCE->REG_100H;
            OutData_PubKeyIndex[24] = SCE->REG_100H;
            HW_SCE_p_func100(0x7d1ad014U, 0xbcf9baa2U, 0x3a53ca7cU, 0x64a40b32U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000089c4U;
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
            OutData_PubKeyIndex[25] = SCE->REG_100H;
            OutData_PubKeyIndex[26] = SCE->REG_100H;
            OutData_PubKeyIndex[27] = SCE->REG_100H;
            OutData_PubKeyIndex[28] = SCE->REG_100H;
            HW_SCE_p_func100(0x5e7bb2b6U, 0xa502456fU, 0xbca534c6U, 0x74f8870fU);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[0] = SCE->REG_100H;
            HW_SCE_p_func101(0x63efbb39U, 0xe075f07eU, 0x3022bf96U, 0x349cd2ecU);
        }
        else
        {
            HW_SCE_p_func100(0xbb9c7e38U, 0x41ec0365U, 0x69b55d2eU, 0x2b43c754U);
            SCE->REG_2CH = 0x0000002dU;
            SCE->REG_04H = 0x00000332U;
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
            HW_SCE_p_func100(0x6de30be7U, 0x126dbb17U, 0xf401140aU, 0x0ef0ee36U);
            SCE->REG_2CH = 0x00000022U;
            SCE->REG_04H = 0x00000332U;
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
            HW_SCE_p_func100(0x02d5e48aU, 0x6ed01b95U, 0x7f1bf0bcU, 0x4a45ecf6U);
            SCE->REG_2CH = 0x00000023U;
            SCE->REG_04H = 0x00000332U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
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
            HW_SCE_p_func101(0xd01e5a9fU, 0xd4e75e84U, 0xaf1653baU, 0xc7655bbbU);
        }
        HW_SCE_p_func102(0xa048ac0cU, 0x830190d2U, 0xb1bc5a15U, 0xdba0fb07U);
        SCE->REG_1B8H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf9_r5.prc
***********************************************************************************************************************/
