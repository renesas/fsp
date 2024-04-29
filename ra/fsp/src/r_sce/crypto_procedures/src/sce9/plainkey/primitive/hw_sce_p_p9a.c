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

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R)
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
    SCE->REG_84H = 0x00009a02U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_28H = 0x00870001U;
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
    SCE->REG_104H = 0x00000f68U;
    SCE->REG_E0H = 0x8090001eU;
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[iLoop + 0];
    }
    for (iLoop = 0; iLoop < 2; iLoop = iLoop + 1)
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
    SCE->REG_ECH = 0x30000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d3e1U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x38000f9cU;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x3965c2d2U, 0x82748bcdU, 0xc40cd983U, 0x4cfda6a2U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x57ec98c4U, 0x37655b01U, 0xbd5955d6U, 0x4b280573U);
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
        SCE->REG_100H = change_endian_long(0x0000009aU);
        HW_SCE_p_func101(0x3aa30067U, 0x566ddb9aU, 0x5cee2e76U, 0x4083c512U);
        HW_SCE_p_func043();
        HW_SCE_p_func074_r1();
        SCE->REG_ECH = 0x000034feU;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000009aU);
        HW_SCE_p_func101(0x832ab6cbU, 0xf2fc811cU, 0x465c0d18U, 0x085b85d7U);
        HW_SCE_p_func044();
        SCE->REG_104H = 0x00000762U;
        SCE->REG_D0H = 0x40000100U;
        SCE->REG_C4H = 0x02f087b7U;
        SCE->REG_00H = 0x00003223U;
        SCE->REG_2CH = 0x00000011U;
        for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
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
        HW_SCE_p_func100(0x3d38fe92U, 0x745739efU, 0x96383b59U, 0x1fcc88e9U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x71c33e0dU, 0xb021c479U, 0x6b63089eU, 0x571fde41U);
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
            HW_SCE_p_func100(0x86959a7cU, 0xa4eed527U, 0xeeec7768U, 0xff9ea61bU);
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
            HW_SCE_p_func100(0x1ed97c6fU, 0x109d0bc2U, 0xfa651f26U, 0xf32e898eU);
            HW_SCE_p_func070_r2(OFS_ADR);
            HW_SCE_p_func100(0xd1fe94f1U, 0x147cf197U, 0xf1f0ff33U, 0xab3dc8c1U);
            SCE->REG_34H = 0x00000003U;
            SCE->REG_24H = 0x800068d0U;
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
            SCE->REG_ECH = 0x00000bffU;
            SCE->REG_E0H = 0x8188001fU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_E0H = 0x8188001fU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
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
            SCE->REG_ECH = 0x00000100U;
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x0000009aU;
            SCE->REG_ECH = 0x0000377cU;
            SCE->REG_ECH = 0x00000b9cU;
            SCE->REG_E0H = 0x81010380U;
            SCE->REG_04H = 0x00000607U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            for(iLoop=0;iLoop<256;iLoop=iLoop+1)
            {
                HW_SCE_p_func101(0xae6f33b4U, 0x064fc23eU, 0x7a4c092bU, 0xd9ff2a9eU);
                HW_SCE_p_func300();
                if (S_RAM[0] == 0x00000001U)
                {
                    break;
                }
                HW_SCE_p_func101(0xf42c3d9eU, 0x179e2b97U, 0xac23a620U, 0xc94db83bU);
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
            HW_SCE_p_func100(0xfa0e2dd1U, 0x0d9f7059U, 0xe5c47b66U, 0x1267bf4fU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xd1535a62U, 0x712ffe15U, 0x35a7c325U, 0xaec12d1fU);
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
                SCE->REG_E0H = 0x8088001fU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000021U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                for(iLoop=0; iLoop<8; iLoop=iLoop+1)
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
                        HW_SCE_p_func100(0xbfa07cbbU, 0x892d135cU, 0x6f39790aU, 0x1ebe4fcbU);
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
                            HW_SCE_p_func101(0xcd606843U, 0x98cbb1f5U, 0x4052dda2U, 0x61b8fdd1U);
                        }
                        else
                        {
                            HW_SCE_p_func101(0x0ce52ca3U, 0x9ceedb58U, 0x5f26d152U, 0x98cc1206U);
                        }
                    }
                    SCE->REG_ECH = 0x000027e1U;
                    HW_SCE_p_func101(0x84355fe5U, 0xb797abfcU, 0xc5bc5e73U, 0xf3cdaec0U);
                }
                SCE->REG_ECH = 0x00008be0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_ECH = 0x00007c1fU;
                SCE->REG_1CH = 0x00602000U;
                HW_SCE_p_func301();
                HW_SCE_p_func100(0x0c5448bdU, 0xe38e6a0dU, 0xbc1dc8f3U, 0xc7fa8025U);
                SCE->REG_2CH = 0x00000022U;
                SCE->REG_04H = 0x00000322U;
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
                HW_SCE_p_func100(0x11f40d9dU, 0xc57e5588U, 0x575e1647U, 0x235ad24bU);
                SCE->REG_2CH = 0x00000023U;
                SCE->REG_04H = 0x00000322U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_R[8] = SCE->REG_100H;
                OutData_R[9] = SCE->REG_100H;
                OutData_R[10] = SCE->REG_100H;
                OutData_R[11] = SCE->REG_100H;
                OutData_R[12] = SCE->REG_100H;
                OutData_R[13] = SCE->REG_100H;
                OutData_R[14] = SCE->REG_100H;
                OutData_R[15] = SCE->REG_100H;
                HW_SCE_p_func102(0x69e7c53aU, 0x0f736cf0U, 0xc4577672U, 0x449008dcU);
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
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p9a_r4.prc
***********************************************************************************************************************/
