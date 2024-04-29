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

fsp_err_t HW_SCE_SelfCheck1Sub(void)
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
    SCE->REG_1D0H = 0x00000000U;
    HW_SCE_SelfCheck1SubSub();

    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_04H = 0x00000001U;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_80H = 0x00000001U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_84H = 0x00010101U;
    SCE->REG_13CH = 0x00000F00U;
    SCE->REG_88H = 0x00008003U;
    SCE->REG_104H = 0x00000351U;
    HW_SCE_func002(change_endian_long(0x4c1d2affU), change_endian_long(0x60ebc80aU), change_endian_long(0xdf041ee8U), change_endian_long(0x394548fdU));
    SCE->REG_88H = 0x00000000U;
    SCE->REG_104H = 0x00000351U;
    SCE->REG_A4H = 0x400f380dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = 0xe6be653cU;
    SCE->REG_100H = 0xcfa7022cU;
    SCE->REG_100H = 0xb7f12cbfU;
    SCE->REG_100H = 0x7eb98ec1U;
    HW_SCE_func002(change_endian_long(0x851be22bU), change_endian_long(0xa6e93a47U), change_endian_long(0x5714620aU), change_endian_long(0x5f2d7b1fU));
    HW_SCE_func001(change_endian_long(0xc0a8e4c8U), change_endian_long(0xb08ee757U), change_endian_long(0x6bd1dd36U), change_endian_long(0x11fc0e56U));
    SCE->REG_04H = 0x00001001U;
    SCE->REG_1D0H = 0x00000000U;
    if (0U == (SCE->REG_18H_b.B13))
    {
        SCE->REG_1BCH = 0x00000020U;
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_13CH = 0x00000201U;
        HW_SCE_func003(change_endian_long(0x7153c22dU), change_endian_long(0xb402a12dU), change_endian_long(0x355fb000U), change_endian_long(0x55e578a7U));
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p01.prc
***********************************************************************************************************************/
