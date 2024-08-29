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
    SCE->REG_84H = 0x00000202U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00093b8cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01c7ba56U);
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
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_ECH = 0x00000884U;
    SCE->REG_ECH = 0x000008a5U;
    SCE->REG_ECH = 0x0000b4c0U;
    SCE->REG_ECH = 0x00000013U;
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000348U;
    SCE->REG_ECH = 0x0000b500U;
    SCE->REG_ECH = 0x000000b7U;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        HW_SCE_p_func100(0x6c71e264U, 0x905d3c7cU, 0x2a4c435eU, 0xbdb4777bU);
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
            SCE->REG_64H = 0x0020901cU;
            HW_SCE_p_func101(0x4ed68504U, 0x34692cfcU, 0xa224db89U, 0x08268dfbU);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901eU;
            HW_SCE_p_func101(0x7de6d907U, 0x8a506eeaU, 0x951e9155U, 0x15bb7447U);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901dU;
            HW_SCE_p_func101(0x6f12da0dU, 0xb83a404aU, 0x1332d5efU, 0x94827cceU);
        }
        SCE->REG_C4H = 0x41001e5eU;
        SCE->REG_00H = 0x80002401U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001200U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B30)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x00000001U;
        SCE->REG_C4H = 0x00000000U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x0010B008U;
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_E0H = 0x80900000U;
        SCE->REG_00H = 0x00008443U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000038a0U;
        SCE->REG_ECH = 0x00003405U;
        SCE->REG_ECH = 0x00002804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x34202808U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x00003485U;
        HW_SCE_p_func101(0xca3b3ea4U, 0x71236437U, 0x3e0d1f89U, 0x58d2df4bU);
    }
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000B50U;
    SCE->REG_ECH = 0x00000842U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000b4a0U;
    SCE->REG_ECH = 0x00000002U;
    for(iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x00002440U;
        SCE->REG_ECH = 0x00002cc0U;
        SCE->REG_ECH = 0x00002485U;
    }
    SCE->REG_ECH = 0x00002c20U;
    SCE->REG_ECH = 0x38008840U;
    SCE->REG_ECH = 0x00002000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000033U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x0000003cU;
    SCE->REG_ECH = 0x01003804U;
    SCE->REG_ECH = 0x342028e0U;
    SCE->REG_ECH = 0x10005066U;
    SCE->REG_ECH = 0x00002cc0U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x0000003eU;
    SCE->REG_ECH = 0x01003804U;
    SCE->REG_ECH = 0x342028e0U;
    SCE->REG_ECH = 0x10005066U;
    SCE->REG_ECH = 0x38008860U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x25d4d69bU, 0x231245f9U, 0x52a77bdaU, 0xba7e5bc8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7d948770U, 0x3e084379U, 0xc51558caU, 0x81647cd1U);
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
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000001f0U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x2e24c972U;
        SCE->REG_ECH = 0x00003ffeU;
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
        HW_SCE_p_func100(0x8d0bfb78U, 0xe6d5ba61U, 0xf547a492U, 0x401bf606U);
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
        HW_SCE_p_func100(0xbffc56f3U, 0x242ee8afU, 0xd6f5a7f5U, 0xdc95f65eU);
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
        HW_SCE_p_func100(0x48de5befU, 0x8b1403c2U, 0x1e08e8feU, 0xa1a7a87cU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x3cb5779eU, 0xbab174adU, 0xf71b0f88U, 0xbe7d89cdU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0x95ad7aabU, 0x2279e4ddU, 0x55fb6a92U, 0x431d725eU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x70782e85U, 0x7706b601U, 0x736af867U, 0x38a12bdfU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
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
        S_RAM[20] = SCE->REG_100H;
        S_RAM[21] = SCE->REG_100H;
        S_RAM[22] = SCE->REG_100H;
        S_RAM[23] = SCE->REG_100H;
        SCE->REG_13CH = 0x00000202U;
        HW_SCE_p_func102(0x75fe6fe1U, 0x9ab95ef0U, 0xec59c801U, 0x84cb693aU);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p02_r2.prc
***********************************************************************************************************************/
