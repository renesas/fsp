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

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R)
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
    SCE->REG_84H = 0x00009b02U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_28H = 0x008b0001U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000009bU);
    HW_SCE_p_func101(0x729ab639U, 0xfe0a0d1dU, 0x1e7fbae5U, 0x6d0e18e6U);
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
    SCE->REG_100H = change_endian_long(0x0000009bU);
    HW_SCE_p_func101(0xba343e79U, 0xfe31a1f3U, 0x7dbd0515U, 0xb71fd7baU);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000b62U;
    SCE->REG_D0H = 0x40000200U;
    SCE->REG_C4H = 0x02f087b7U;
    SCE->REG_00H = 0x00003233U;
    SCE->REG_2CH = 0x00000011U;
    for (iLoop = 0; iLoop < 12; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000362U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000087b5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    SCE->REG_C4H = 0x00900c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xa67b83a2U, 0xc869f5b9U, 0x79ac9b3aU, 0x05db1be5U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xf1c61cd6U, 0x638a9ff7U, 0x30d2fddfU, 0x66063230U);
        SCE->REG_1B8H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x4d994ba1U, 0x0e83dd5fU, 0x1ad395aeU, 0xf05795a2U);
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
        HW_SCE_p_func100(0x7c3c2b42U, 0x77da4ba5U, 0xdd828a5fU, 0xf0ae4b81U);
        HW_SCE_p_func027_r2(OFS_ADR);
        HW_SCE_p_func100(0xada38979U, 0x5574dcfbU, 0xcbcebb86U, 0x44cc9663U);
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
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00000b67U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[0];
        SCE->REG_100H = InData_PubKey[1];
        SCE->REG_100H = InData_PubKey[2];
        SCE->REG_100H = InData_PubKey[3];
        SCE->REG_100H = InData_PubKey[4];
        SCE->REG_100H = InData_PubKey[5];
        SCE->REG_100H = InData_PubKey[6];
        SCE->REG_100H = InData_PubKey[7];
        SCE->REG_100H = InData_PubKey[8];
        SCE->REG_100H = InData_PubKey[9];
        SCE->REG_100H = InData_PubKey[10];
        SCE->REG_100H = InData_PubKey[11];
        SCE->REG_24H = 0x00000c2cU;
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
        SCE->REG_24H = 0x800040c1U;
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
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00000b67U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[12];
        SCE->REG_100H = InData_PubKey[13];
        SCE->REG_100H = InData_PubKey[14];
        SCE->REG_100H = InData_PubKey[15];
        SCE->REG_100H = InData_PubKey[16];
        SCE->REG_100H = InData_PubKey[17];
        SCE->REG_100H = InData_PubKey[18];
        SCE->REG_100H = InData_PubKey[19];
        SCE->REG_100H = InData_PubKey[20];
        SCE->REG_100H = InData_PubKey[21];
        SCE->REG_100H = InData_PubKey[22];
        SCE->REG_100H = InData_PubKey[23];
        SCE->REG_24H = 0x00000c2cU;
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
        SCE->REG_24H = 0x800060c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000a0c1U;
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
        SCE->REG_ECH = 0x0000009bU;
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
            HW_SCE_p_func101(0xd1a20304U, 0x7ec5a832U, 0xfe786d80U, 0x8db0ff21U);
            HW_SCE_p_func300();
            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }
            HW_SCE_p_func101(0xd89c8381U, 0xd1f4a61cU, 0x434fe417U, 0x7150d01dU);
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
        HW_SCE_p_func100(0x62b875dcU, 0x77b1bd44U, 0x9da356ddU, 0x268018dbU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x142493c0U, 0x7f78d4e0U, 0xc34d38b2U, 0x5166c60eU);
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
                    HW_SCE_p_func100(0x6dfda009U, 0xdb9d8c6fU, 0x5f3558dfU, 0x4eeb90f1U);
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
                        HW_SCE_p_func101(0x97eb165fU, 0x003b8d10U, 0xd9f32031U, 0xa635451cU);
                    }
                    else
                    {
                        HW_SCE_p_func101(0x3775974eU, 0xfd8b4302U, 0x33a3cd37U, 0x5bcc8a49U);
                    }
                }
                SCE->REG_ECH = 0x000027e1U;
                HW_SCE_p_func101(0xa93bfadeU, 0x9ae6845aU, 0x6ec11109U, 0x707f0125U);
            }
            SCE->REG_ECH = 0x00008be0U;
            SCE->REG_ECH = 0x00000030U;
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func301();
            HW_SCE_p_func100(0x036d9c54U, 0xe4a2ebc2U, 0x357cde20U, 0xd1165e27U);
            SCE->REG_2CH = 0x00000022U;
            SCE->REG_04H = 0x00000332U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_R[0] = SCE->REG_100H;
            OutData_R[1] = SCE->REG_100H;
            OutData_R[2] = SCE->REG_100H;
            OutData_R[3] = SCE->REG_100H;
            OutData_R[4] = SCE->REG_100H;
            OutData_R[5] = SCE->REG_100H;
            OutData_R[6] = SCE->REG_100H;
            OutData_R[7] = SCE->REG_100H;
            OutData_R[8] = SCE->REG_100H;
            OutData_R[9] = SCE->REG_100H;
            OutData_R[10] = SCE->REG_100H;
            OutData_R[11] = SCE->REG_100H;
            HW_SCE_p_func100(0x05a57fffU, 0x0c4047f5U, 0xb8df91a5U, 0x33f572e9U);
            SCE->REG_2CH = 0x00000023U;
            SCE->REG_04H = 0x00000332U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_R[12] = SCE->REG_100H;
            OutData_R[13] = SCE->REG_100H;
            OutData_R[14] = SCE->REG_100H;
            OutData_R[15] = SCE->REG_100H;
            OutData_R[16] = SCE->REG_100H;
            OutData_R[17] = SCE->REG_100H;
            OutData_R[18] = SCE->REG_100H;
            OutData_R[19] = SCE->REG_100H;
            OutData_R[20] = SCE->REG_100H;
            OutData_R[21] = SCE->REG_100H;
            OutData_R[22] = SCE->REG_100H;
            OutData_R[23] = SCE->REG_100H;
            HW_SCE_p_func102(0xd6535d3fU, 0x32ed02a4U, 0xf2ad998eU, 0x83ac46d5U);
            SCE->REG_1B8H = 0x00000040U;
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p9b_r3.prc
***********************************************************************************************************************/
