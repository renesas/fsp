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

fsp_err_t HW_SCE_SelfCheck2Sub(void)
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
    SCE->REG_84H = 0x00000201U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00093b8cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x26c7ba56U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00070804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x3000a820U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00010020U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x00000080U;
    HW_SCE_p_func100(0xd12fa23dU, 0x6d38f66aU, 0xf2c41970U, 0x2cfaba75U);
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00600000U;
    SCE->REG_1D0H = 0x00000000U;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00002008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0000901CU;
        HW_SCE_p_func101(0xe215fa65U, 0x2855569dU, 0xa3c62a85U, 0x5c97ccb4U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00002008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0000901eU;
        HW_SCE_p_func101(0x602f5d7bU, 0x0fdb3bfbU, 0xd447fec2U, 0x81e96d41U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00002008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0000901dU;
        HW_SCE_p_func101(0xdef2d6a0U, 0x3d3b6fc7U, 0x348a40f0U, 0x09f475c7U);
    }
    HW_SCE_SelfCheck2SubSub();

    SCE->REG_ECH = 0x00002c20U;
    SCE->REG_ECH = 0x38008840U;
    SCE->REG_ECH = 0x00002000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x38008860U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x6cc28cbaU, 0xfb1f86eeU, 0x82cbaf68U, 0xcbd682e6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x79446984U, 0xdf66efc1U, 0xca8f823cU, 0x8a724c03U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0000001cU;
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000cc4U;
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
        SCE->REG_C4H = 0x41001eddU;
        SCE->REG_00H = 0x00002413U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000000U;
        SCE->REG_E0H = 0x80040080U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xae430906U, 0x9097d049U, 0x058ac4a4U, 0x685ee370U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x000b0804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x00070805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000001U);
        HW_SCE_p_func100(0x2a0d12b9U, 0xb4a4239eU, 0x49763b66U, 0xad505b2aU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x0100b7f7U;
        SCE->REG_E0H = 0x81080000U;
        SCE->REG_00H = 0x00002823U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x000b0805U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x00070805U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x2fd98c1eU, 0x8c21d3ebU, 0xa7300e05U, 0xa682fe32U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xce5778f1U, 0xbada59e0U, 0xdc2bb95dU, 0x7a012515U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0x6ec1f49aU, 0xf7f2af01U, 0x951c1a83U, 0x9a86d322U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x3a42759dU, 0xef2f20d3U, 0xb2a147baU, 0xb800866bU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_04H = 0x00000213U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[16] = SCE->REG_100H;
        S_RAM[17] = SCE->REG_100H;
        S_RAM[18] = SCE->REG_100H;
        S_RAM[19] = SCE->REG_100H;
        SCE->REG_13CH = 0x00000202U;
        HW_SCE_p_func102(0x43b1974fU, 0xed75d788U, 0xbbd964aaU, 0x880152adU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p02.prc
***********************************************************************************************************************/
