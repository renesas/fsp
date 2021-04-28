/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce.h"
#include "r_sce_private.h"

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

void R_SCE_func057_r3(uint32_t* ARG1, uint32_t* ARG2, uint32_t* ARG3)
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
    R_SCE_func100(0xb5fa2aa7U, 0x59fc8a39U, 0x574c4badU, 0x1cb2c0faU);
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
    R_SCE_func103();
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
    R_SCE_func101(0x43c21d19U, 0x2690df3eU, 0xe50a58e7U, 0xc4a2b4f9U);
    R_SCE_func043();
    SCE->REG_ECH = 0x000034e4U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000feU);
    R_SCE_func101(0x6b73e029U, 0x554c9c6bU, 0x8ef8d0dcU, 0x88940519U);
    R_SCE_func044();
    R_SCE_func100(0x497677e9U, 0x83adb760U, 0x0f956503U, 0x53d97513U);
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
    R_SCE_func081();
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00600000U;
    SCE->REG_1D0H = 0x00000000U;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0x122f2c5fU, 0xe220aef4U, 0xbcb4a9fcU, 0xb6936250U);
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
        R_SCE_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0xae42bbf5U, 0x719d12c0U, 0x28a9c4baU, 0x5417ca87U);
    }
    else if (0x0a000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0x15c14dd7U, 0xf7e17e56U, 0x5936cd8bU, 0xc7e17967U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func061(0,ARG2);
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
        R_SCE_func100(0x283cb8a9U, 0xc6ebc99bU, 0xc90412f2U, 0xa43d389bU);
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
        R_SCE_func100(0xa3ba6d53U, 0x799a8942U, 0x31fc06e6U, 0x45eb9319U);
        R_SCE_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func062(36,ARG3);
        oLoop = 36 + 32;
        R_SCE_func101(0xc00f0ff8U, 0xd2a607a6U, 0xdd98d770U, 0xcf9f172cU);
    }
    else if (0x0b000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0xb23ee3a6U, 0x980de4c5U, 0x357824d0U, 0x0cabf2b8U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func061(0,ARG2);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        R_SCE_func062(0,ARG3);
        oLoop = 0 + 32;
        R_SCE_func100(0x458fc640U, 0x50261cc3U, 0xe4202208U, 0x6d0a4b50U);
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000011U;
        R_SCE_func061(32,ARG2);
        iLoop = 32 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000021U;
        R_SCE_func062(32,ARG3);
        oLoop = 32 + 32;
        R_SCE_func100(0x9f976c71U, 0xf7735f2aU, 0x0200a790U, 0xbe03fb66U);
        R_SCE_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func062(64,ARG3);
        oLoop = 64 + 32;
        R_SCE_func101(0xe1f95173U, 0x22b9c4c5U, 0x0bcaf056U, 0xa4438138U);
    }
    else if (0x0c000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0x41312fdfU, 0xf45eb02bU, 0x0507f044U, 0x582d0555U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func063(0,ARG2);
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
        R_SCE_func100(0x3536950cU, 0xaa005c53U, 0x17df86caU, 0xe41d70f6U);
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
        R_SCE_func100(0x5356fbabU, 0xaa4e174dU, 0xd9b892faU, 0x5160840bU);
        R_SCE_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func064(68,ARG3);
        oLoop = 68 + 64;
        R_SCE_func101(0x1ae55db3U, 0xf757fc20U, 0x0b5726e7U, 0xd6b1f58fU);
    }
    else if (0x0d000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0xb6fe6903U, 0xbd2a18b0U, 0xe45fbb4aU, 0xaa7a49a8U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func063(0,ARG2);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        R_SCE_func064(0,ARG3);
        oLoop = 0 + 64;
        R_SCE_func100(0x56902e0fU, 0xdd31160dU, 0xe0d9af9bU, 0x0522e107U);
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func063(64,ARG2);
        iLoop = 64 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func064(64,ARG3);
        oLoop = 64 + 64;
        R_SCE_func100(0x1343a428U, 0x294890b2U, 0x4934f23bU, 0x9dd420c0U);
        R_SCE_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func064(128,ARG3);
        oLoop = 128 + 64;
        R_SCE_func101(0x7ce803d0U, 0x63acd9bcU, 0xe94d8c2cU, 0xd0dc55d5U);
    }
    else if (0x12000000U == (SCE->REG_1CH & 0xff000000U))
    {
        R_SCE_func100(0x93159ddcU, 0xd692ed5aU, 0xb444f63cU, 0x838a92f9U);
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
        R_SCE_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        R_SCE_func101(0xfc1ed21cU, 0x83b5b45bU, 0x7df40298U, 0xe26f3919U);
    }
    R_SCE_func100(0x1d10f3f2U, 0xaae17e31U, 0xe4f361daU, 0x007171faU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func057_r3.prc
***********************************************************************************************************************/
