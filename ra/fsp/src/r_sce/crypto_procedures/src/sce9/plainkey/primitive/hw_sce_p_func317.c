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

void HW_SCE_p_func317(void)
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x00003fbeU;
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_ECH = 0x00000b39U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_E0H = 0x800103c0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000023U;
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
    SCE->REG_ECH = 0x3800dbdfU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x54c736d5U, 0x1687cea2U, 0xb9a27aefU, 0x0efb8de2U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00a30001U;
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103c0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
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
            SCE->REG_28H = 0x00a30001U;
            SCE->REG_ECH = 0x3800dbdfU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_p_func100(0xb050152eU, 0x4b531e69U, 0x106eb6e5U, 0xa55c8f7fU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x00001981U;
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
                SCE->REG_ECH = 0x00002f20U;
                HW_SCE_p_func101(0x53c53629U, 0xc624f94dU, 0xcc1a9552U, 0x5b2c6d97U);
            }
            else
            {
                HW_SCE_p_func101(0x1279d640U, 0x26ecf237U, 0x637e567bU, 0xdf3efeccU);
                oLoop1 = 0;
            }
        }
        SCE->REG_ECH = 0x0000537fU;
        HW_SCE_p_func101(0x7cb89078U, 0x36f852b6U, 0xb36ce496U, 0xdd7983beU);
    }
    else
    {
        SCE->REG_28H = 0x00a30001U;
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001991U;
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
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103c0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
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
            SCE->REG_28H = 0x00a30001U;
            SCE->REG_ECH = 0x3800dbdfU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_p_func100(0x3b020f6eU, 0xeb260ad7U, 0xa93e0aa8U, 0x95ef9e82U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x00001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                HW_SCE_p_func101(0x8624917eU, 0x91b076eeU, 0x5dbd5e14U, 0x70155193U);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x00001991U;
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
                SCE->REG_ECH = 0x00002f20U;
                HW_SCE_p_func101(0x09722fbaU, 0xa95ea208U, 0x4ad6f5a0U, 0xeaae6343U);
            }
        }
        SCE->REG_ECH = 0x0000577fU;
        HW_SCE_p_func101(0x654a6dd5U, 0x21175d16U, 0x4cab116eU, 0xbfd1f105U);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func317.prc
***********************************************************************************************************************/
