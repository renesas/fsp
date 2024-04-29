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
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000f901U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0xd38c9021U, 0xdd27ed91U, 0xeab8644bU, 0x44582c54U);
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
    HW_SCE_p_func100(0x4c350d92U, 0x5cba4c80U, 0x057f39f6U, 0x388324cbU);
    HW_SCE_p_func027_r1(OFS_ADR);
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x008d0001U;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x97372561U, 0xbb612ba9U, 0x992a8e1aU, 0x27580b27U);
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
    HW_SCE_p_func100(0xdaefb53fU, 0xd61505e6U, 0x2b856849U, 0xb51c2869U);
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
    HW_SCE_p_func100(0x40e7a0fcU, 0xfd288dcbU, 0x6ca48448U, 0x9a3bdbf5U);
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
    HW_SCE_p_func100(0x401afdafU, 0xc7685fefU, 0x3079c5aaU, 0x32eac240U);
    SCE->REG_24H = 0x0000dcd0U;
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
    HW_SCE_p_func028_r1(OFS_ADR);
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
    SCE->REG_E0H = 0x818c001fU;
    SCE->REG_00H = 0x00003833U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000f008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000004U;
    SCE->REG_38H = 0x00001030U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000f4d0U;
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
    SCE->REG_1CH = 0x00001f00U;
    SCE->REG_1CH = 0x00210000U;
    HW_SCE_p_func100(0x3a1d3f31U, 0xc63c3726U, 0x1edee26fU, 0x65353e9bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x5508121cU, 0xe6e045a2U, 0xbef9070bU, 0x9e7b0600U);
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
        HW_SCE_p_func100(0xeeffc18bU, 0x52903837U, 0xe177ac97U, 0x1f9fa84dU);
        SCE->REG_24H = 0x00009cd0U;
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
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x000000b0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x818c001fU;
        SCE->REG_00H = 0x00003833U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x0000880cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800050d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004a0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800074d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
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
        HW_SCE_p_func100(0x79a5a412U, 0x2ea4e168U, 0x90626024U, 0xa33b5b23U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func100(0x49dd5de3U, 0xe5b6de8eU, 0xe44f030aU, 0xf57dab4eU);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0x37d152ceU, 0x775f6908U, 0xb754866eU, 0x6a8a4eb3U);
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
            SCE->REG_C4H = 0x200c3b0dU;
            SCE->REG_E0H = 0x81040000U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func076();
            SCE->REG_C4H = 0x000c0b0cU;
            SCE->REG_E0H = 0x810103c0U;
            SCE->REG_00H = 0x00002807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_D0H = 0x00000200U;
            SCE->REG_C4H = 0x02e087bfU;
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
            OutData_PrivKeyIndex[4] = SCE->REG_100H;
            OutData_PrivKeyIndex[5] = SCE->REG_100H;
            OutData_PrivKeyIndex[6] = SCE->REG_100H;
            OutData_PrivKeyIndex[7] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[8] = SCE->REG_100H;
            OutData_PrivKeyIndex[9] = SCE->REG_100H;
            OutData_PrivKeyIndex[10] = SCE->REG_100H;
            OutData_PrivKeyIndex[11] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PrivKeyIndex[12] = SCE->REG_100H;
            OutData_PrivKeyIndex[13] = SCE->REG_100H;
            OutData_PrivKeyIndex[14] = SCE->REG_100H;
            OutData_PrivKeyIndex[15] = SCE->REG_100H;
            HW_SCE_p_func100(0xa39b10b6U, 0x6ffd6b94U, 0x7ab8ab66U, 0x2e33e60bU);
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
            OutData_PrivKeyIndex[16] = SCE->REG_100H;
            OutData_PrivKeyIndex[17] = SCE->REG_100H;
            OutData_PrivKeyIndex[18] = SCE->REG_100H;
            OutData_PrivKeyIndex[19] = SCE->REG_100H;
            HW_SCE_p_func100(0x881092b2U, 0xf49bcef3U, 0xbc3784fcU, 0x8400bf30U);
            SCE->REG_E0H = 0x81040000U;
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
            HW_SCE_p_func100(0xfabf8b00U, 0xc397db0eU, 0x32b08833U, 0xbcbd3aacU);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0xe0a9d3dcU, 0x9f78797bU, 0x5ddbfd9dU, 0xa0524963U);
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
            SCE->REG_C4H = 0x200c3b0dU;
            SCE->REG_E0H = 0x81040000U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_D0H = 0x00000200U;
            SCE->REG_C4H = 0x02e0888fU;
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
            OutData_PubKeyIndex[4] = SCE->REG_100H;
            OutData_PubKeyIndex[5] = SCE->REG_100H;
            OutData_PubKeyIndex[6] = SCE->REG_100H;
            OutData_PubKeyIndex[7] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[8] = SCE->REG_100H;
            OutData_PubKeyIndex[9] = SCE->REG_100H;
            OutData_PubKeyIndex[10] = SCE->REG_100H;
            OutData_PubKeyIndex[11] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[12] = SCE->REG_100H;
            OutData_PubKeyIndex[13] = SCE->REG_100H;
            OutData_PubKeyIndex[14] = SCE->REG_100H;
            OutData_PubKeyIndex[15] = SCE->REG_100H;
            HW_SCE_p_func100(0xee02acb9U, 0xa1fee412U, 0x7d3bd399U, 0x3a9b8b79U);
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x00e0888fU;
            SCE->REG_00H = 0x00002323U;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000222U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[16] = SCE->REG_100H;
            OutData_PubKeyIndex[17] = SCE->REG_100H;
            OutData_PubKeyIndex[18] = SCE->REG_100H;
            OutData_PubKeyIndex[19] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_PubKeyIndex[20] = SCE->REG_100H;
            OutData_PubKeyIndex[21] = SCE->REG_100H;
            OutData_PubKeyIndex[22] = SCE->REG_100H;
            OutData_PubKeyIndex[23] = SCE->REG_100H;
            HW_SCE_p_func100(0x50c50affU, 0xe00d3f90U, 0xb995fe92U, 0x0fb076feU);
            SCE->REG_C4H = 0x0045094cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_C4H = 0x00e0088dU;
            SCE->REG_00H = 0x00002313U;
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
            OutData_PubKeyIndex[24] = SCE->REG_100H;
            OutData_PubKeyIndex[25] = SCE->REG_100H;
            OutData_PubKeyIndex[26] = SCE->REG_100H;
            OutData_PubKeyIndex[27] = SCE->REG_100H;
            HW_SCE_p_func100(0x5c5dd72bU, 0xeb3e92bcU, 0x2aad5e14U, 0x72d69110U);
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
            OutData_PubKeyIndex[28] = SCE->REG_100H;
            OutData_PubKeyIndex[29] = SCE->REG_100H;
            OutData_PubKeyIndex[30] = SCE->REG_100H;
            OutData_PubKeyIndex[31] = SCE->REG_100H;
            HW_SCE_p_func100(0x9c05cb38U, 0x1c013fbfU, 0xe2c2ac7eU, 0x181734adU);
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
            HW_SCE_p_func101(0x720369e1U, 0xed14396cU, 0xf1cd3180U, 0x8e13a4bdU);
        }
        else
        {
            HW_SCE_p_func100(0x47ab346bU, 0xb8f6b2ddU, 0xd2ebe25bU, 0x2f0a8b2aU);
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
            HW_SCE_p_func100(0x9abf4b47U, 0x47864e28U, 0xa673d28aU, 0xe2b799baU);
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
            HW_SCE_p_func100(0xe634c05bU, 0x0ead8434U, 0x1d5fd385U, 0xa4af25cbU);
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
            HW_SCE_p_func101(0xb48685ebU, 0x6f09d1e3U, 0x6a253a0bU, 0x9108d7ebU);
        }
        HW_SCE_p_func102(0x4d11af9fU, 0xfe6c8333U, 0xebaddc66U, 0x69bd5b9aU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_pf9_r2.prc
***********************************************************************************************************************/
