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

fsp_err_t HW_SCE_SelfCheck3Sub(void)
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
    SCE->REG_84H = 0x00009203U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000001f0U;
    SCE->REG_ECH = 0x00003bfeU;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x2e24c972U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x7252ffb3U, 0xa4f2970fU, 0xccf82b60U, 0xfaf63abcU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
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
        for(jLoop = 0; jLoop < 1; jLoop = jLoop + 1)
        {
            HW_SCE_p_func100(0x79c46a3cU, 0x0ae625b1U, 0x2ec940fdU, 0xfd6753fbU);
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
                HW_SCE_p_func101(0x584ce62cU, 0x7c8ea760U, 0x07dd1294U, 0x228e5267U);
            }
            else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
            {
                /* WAIT_LOOP */
                while (0U != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901eU;
                HW_SCE_p_func101(0x7c885349U, 0x7333bee5U, 0x63655723U, 0x31e16865U);
            }
            else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
            {
                /* WAIT_LOOP */
                while (0U != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901dU;
                HW_SCE_p_func101(0x796ca859U, 0x963097eaU, 0x416c1f4dU, 0x6acf9612U);
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
            HW_SCE_p_func101(0xa8ec0974U, 0x20eb43a5U, 0x794d25d7U, 0x4bdd0550U);
        }
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0000005AU;
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
        SCE->REG_ECH = 0x00000100U;
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
        HW_SCE_p_func100(0x61e61c3dU, 0x30283a89U, 0x5909828eU, 0xa7699c6eU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x4e350eeeU, 0xd9878500U, 0xcc805ef3U, 0x77d220feU);
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
            HW_SCE_p_func100(0x99af7425U, 0x2113d46aU, 0xff58fb18U, 0x24edfe4bU);
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
            HW_SCE_p_func100(0x094f8766U, 0x911c9512U, 0xfb3f4bbdU, 0x460e53e2U);
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
            HW_SCE_p_func100(0x0b1343bfU, 0xfa20139bU, 0xb28498c2U, 0x9a061f91U);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0x27268344U, 0xed4d73cbU, 0x2e42dad1U, 0x2e6e640bU);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x010d0c04U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func100(0xb3878676U, 0x7e57894eU, 0xd6748786U, 0x77254975U);
            HW_SCE_p_func103();
            HW_SCE_p_func100(0xa50fc7c5U, 0x110c56e9U, 0xad65e984U, 0x00e91a6cU);
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
            S_RAM[24] = change_endian_long(SCE->REG_100H);
            S_RAM[25] = change_endian_long(SCE->REG_100H);
            S_RAM[26] = change_endian_long(SCE->REG_100H);
            S_RAM[27] = change_endian_long(SCE->REG_100H);
            SCE->REG_13CH = 0x00000202U;
            HW_SCE_p_func102(0x079c4c8cU, 0x962acb2eU, 0x9a5c0aebU, 0x6ec75008U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
    else
    {
        HW_SCE_p_func100(0x6b276b23U, 0x11089165U, 0x87325daaU, 0x63f67f53U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x9eb0ec5fU, 0xd6b216c4U, 0xe5b5cb54U, 0x17139ef3U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0x19d71d04U, 0xf4910acdU, 0x09b90550U, 0x57b49033U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x0f03b51cU, 0x5b024757U, 0x31ea3b4dU, 0xf4eb1056U);
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
        S_RAM[24] = change_endian_long(SCE->REG_100H);
        S_RAM[25] = change_endian_long(SCE->REG_100H);
        S_RAM[26] = change_endian_long(SCE->REG_100H);
        S_RAM[27] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000202U;
        HW_SCE_p_func102(0x974ace4aU, 0xbf7d7d22U, 0xfbcbcfc6U, 0xdd8d0fe8U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p92_r1.prc
***********************************************************************************************************************/
