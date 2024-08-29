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

void HW_SCE_p_func057_r1(uint32_t* ARG1, uint32_t* ARG2, uint32_t* ARG3)
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
    HW_SCE_p_func100(0xf31fc280U, 0xb1f04b9eU, 0x9454ff9bU, 0x9c90f37eU);
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x00040805U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[0];
    SCE->REG_100H = ARG1[1];
    SCE->REG_100H = ARG1[2];
    SCE->REG_100H = ARG1[3];
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00050804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
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
    SCE->REG_100H = change_endian_long(0x000000ffU);
    HW_SCE_p_func101(0xab47b184U, 0xfa6aa1bfU, 0x2f5a393fU, 0x383be959U);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x000034e4U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000feU);
    HW_SCE_p_func101(0x8579d3eaU, 0x0270bbfcU, 0x83222df1U, 0x72d3673dU);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x09b4fe19U, 0xcd9e71faU, 0x41f1394cU, 0xd138ac96U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00050804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    HW_SCE_p_func081();
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00600000U;
    SCE->REG_1D0H = 0x00000000U;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0xd863f335U, 0x104e1c40U, 0x70842eb1U, 0xa48e0ba2U);
        SCE->REG_00H = 0x80002100U;
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00d049a6U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x02e087b6U;
        SCE->REG_04H = 0x0000c200U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[0];
        SCE->REG_100H = ARG2[1];
        SCE->REG_100H = ARG2[2];
        SCE->REG_100H = ARG2[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-8) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG2[4+iLoop + 0];
            SCE->REG_100H = ARG2[4+iLoop + 1];
            SCE->REG_100H = ARG2[4+iLoop + 2];
            SCE->REG_100H = ARG2[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+iLoop + 0] = SCE->REG_100H;
            ARG3[1+iLoop + 1] = SCE->REG_100H;
            ARG3[1+iLoop + 2] = SCE->REG_100H;
            ARG3[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG3[1+iLoop + 0] = SCE->REG_100H;
        ARG3[1+iLoop + 1] = SCE->REG_100H;
        ARG3[1+iLoop + 2] = SCE->REG_100H;
        ARG3[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x4ca67631U, 0xbfe8efa6U, 0x42650b01U, 0x9a59c797U);
    }
    else if (0x0a000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0xc39300fcU, 0x932823baU, 0xdc7a21f7U, 0x41e8b020U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func061(0,ARG2);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x40000700U;
        SCE->REG_C4H = 0x02e08887U;
        SCE->REG_04H = 0x00000282U;
        for(oLoop=0; oLoop<32; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+oLoop + 0] = SCE->REG_100H;
            ARG3[1+oLoop + 1] = SCE->REG_100H;
            ARG3[1+oLoop + 2] = SCE->REG_100H;
            ARG3[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0x4efe8e8aU, 0xfeed2dfcU, 0xdadb5c4aU, 0x65e1b33dU);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00d049a5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[iLoop + 0];
        SCE->REG_100H = ARG2[iLoop + 1];
        SCE->REG_100H = ARG2[iLoop + 2];
        SCE->REG_100H = ARG2[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00e08885U;
        SCE->REG_00H = 0x00002113U;
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
        ARG3[1+oLoop + 0] = SCE->REG_100H;
        ARG3[1+oLoop + 1] = SCE->REG_100H;
        ARG3[1+oLoop + 2] = SCE->REG_100H;
        ARG3[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xa393ce95U, 0x386cc78fU, 0x4a0dde05U, 0x23b90198U);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func062(36,ARG3);
        oLoop = 36 + 32;
        HW_SCE_p_func101(0xb78e40beU, 0x9a507c58U, 0xa058119cU, 0x4604a55aU);
    }
    else if (0x0b000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x0ec0ae03U, 0xbdb21de0U, 0x33e56e86U, 0x9376b996U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func061(0,ARG2);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func062(0,ARG3);
        oLoop = 0 + 32;
        HW_SCE_p_func100(0x04750e53U, 0x7952bb79U, 0xc5800b7eU, 0x403b9779U);
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000011U;
        HW_SCE_p_func061(32,ARG2);
        iLoop = 32 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000021U;
        HW_SCE_p_func062(32,ARG3);
        oLoop = 32 + 32;
        HW_SCE_p_func100(0xf1f9707fU, 0x25d81b4fU, 0x22350d39U, 0x14f1ca2aU);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func062(64,ARG3);
        oLoop = 64 + 32;
        HW_SCE_p_func101(0x03dad023U, 0xcec3eca2U, 0xaa31e30fU, 0x45a27577U);
    }
    else if (0x0c000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x40b8f383U, 0xcc74ecfdU, 0xa253bdf2U, 0x5d08ae64U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func063(0,ARG2);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x40000f00U;
        SCE->REG_C4H = 0x02e08887U;
        SCE->REG_04H = 0x00000202U;
        for(oLoop=0; oLoop<64; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+oLoop + 0] = SCE->REG_100H;
            ARG3[1+oLoop + 1] = SCE->REG_100H;
            ARG3[1+oLoop + 2] = SCE->REG_100H;
            ARG3[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xd5560200U, 0x28a09e8eU, 0xdf18a10aU, 0xa09ce3bdU);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00d049a5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[iLoop + 0];
        SCE->REG_100H = ARG2[iLoop + 1];
        SCE->REG_100H = ARG2[iLoop + 2];
        SCE->REG_100H = ARG2[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00e08885U;
        SCE->REG_00H = 0x00002113U;
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
        ARG3[1+oLoop + 0] = SCE->REG_100H;
        ARG3[1+oLoop + 1] = SCE->REG_100H;
        ARG3[1+oLoop + 2] = SCE->REG_100H;
        ARG3[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xb55664d8U, 0xdda299b2U, 0xa618943dU, 0x763fa4a4U);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func064(68,ARG3);
        oLoop = 68 + 64;
        HW_SCE_p_func101(0x197c0cd4U, 0x2641e686U, 0xca561b5aU, 0x3a15237aU);
    }
    else if (0x0d000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0xbe980790U, 0x643b9dc7U, 0x163962b6U, 0xc3cc6613U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func063(0,ARG2);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func064(0,ARG3);
        oLoop = 0 + 64;
        HW_SCE_p_func100(0x7e2b313aU, 0xa6926a4dU, 0x837b0236U, 0xe47c35d1U);
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000010U;
        HW_SCE_p_func063(64,ARG2);
        iLoop = 64 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func064(64,ARG3);
        oLoop = 64 + 64;
        HW_SCE_p_func100(0xee7b76e5U, 0xc6116ce8U, 0x9952521eU, 0xf6ef1e2fU);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func064(128,ARG3);
        oLoop = 128 + 64;
        HW_SCE_p_func101(0x0bbc011eU, 0x8bf07c60U, 0x4ce1e9aaU, 0x24601a0cU);
    }
    else if (0x12000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0xdb02e3c5U, 0x8f35d0d4U, 0xb1fca80fU, 0xd78d93b5U);
        SCE->REG_00H = 0x80002100U;
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00d049a6U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x02e08886U;
        SCE->REG_04H = 0x0000c200U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[0];
        SCE->REG_100H = ARG2[1];
        SCE->REG_100H = ARG2[2];
        SCE->REG_100H = ARG2[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-8) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG2[4+iLoop + 0];
            SCE->REG_100H = ARG2[4+iLoop + 1];
            SCE->REG_100H = ARG2[4+iLoop + 2];
            SCE->REG_100H = ARG2[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+iLoop + 0] = SCE->REG_100H;
            ARG3[1+iLoop + 1] = SCE->REG_100H;
            ARG3[1+iLoop + 2] = SCE->REG_100H;
            ARG3[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG3[1+iLoop + 0] = SCE->REG_100H;
        ARG3[1+iLoop + 1] = SCE->REG_100H;
        ARG3[1+iLoop + 2] = SCE->REG_100H;
        ARG3[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x0052d385U, 0xd76d9a95U, 0x7739e2c2U, 0x966b5ef3U);
    }
    HW_SCE_p_func100(0xd3371c6dU, 0xd24af252U, 0x239fe0dcU, 0x815b0e6cU);
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
    ARG3[1+oLoop + 0] = SCE->REG_100H;
    ARG3[1+oLoop + 1] = SCE->REG_100H;
    ARG3[1+oLoop + 2] = SCE->REG_100H;
    ARG3[1+oLoop + 3] = SCE->REG_100H;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x000049a5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG2[iLoop + 0];
    SCE->REG_100H = ARG2[iLoop + 1];
    SCE->REG_100H = ARG2[iLoop + 2];
    SCE->REG_100H = ARG2[iLoop + 3];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00007c1cU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func057_r1.prc
***********************************************************************************************************************/
