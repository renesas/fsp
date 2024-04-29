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

void HW_SCE_p_func065_r1(uint32_t* ARG1, uint32_t* ARG2)
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
    HW_SCE_p_func100(0x23a20f43U, 0xb31e013bU, 0x7d30fa57U, 0xddf885eeU);
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
    SCE->REG_100H = change_endian_long(0x00000011U);
    HW_SCE_p_func101(0xabc8f62eU, 0xa0b4b4cdU, 0xabed9fedU, 0x55efaa74U);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x000034e4U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000011U);
    HW_SCE_p_func101(0x79da836fU, 0x01a8f4b7U, 0x4410b933U, 0x7d62b94dU);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0xfef7fdd1U, 0x5e78f5c3U, 0xd66fdca4U, 0x5b2ab651U);
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
        HW_SCE_p_func100(0x3b31b2c7U, 0xfdedce3fU, 0xf2657d0aU, 0x9d2cac16U);
        SCE->REG_00H = 0x80002100U;
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00000886U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x02e087b6U;
        SCE->REG_04H = 0x0000c200U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[0];
        SCE->REG_100H = ARG1[1];
        SCE->REG_100H = ARG1[2];
        SCE->REG_100H = ARG1[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG1[4+iLoop + 0];
            SCE->REG_100H = ARG1[4+iLoop + 1];
            SCE->REG_100H = ARG1[4+iLoop + 2];
            SCE->REG_100H = ARG1[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+iLoop + 0] = SCE->REG_100H;
            ARG2[1+iLoop + 1] = SCE->REG_100H;
            ARG2[1+iLoop + 2] = SCE->REG_100H;
            ARG2[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG2[1+iLoop + 0] = SCE->REG_100H;
        ARG2[1+iLoop + 1] = SCE->REG_100H;
        ARG2[1+iLoop + 2] = SCE->REG_100H;
        ARG2[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x26483003U, 0x4db2d050U, 0x1fb2570aU, 0x627d3e3bU);
    }
    else if (0x0a000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x2be8ca08U, 0xf05b8eaaU, 0xeb20462aU, 0xc40e8c69U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func066(0,ARG1);
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
            ARG2[1+oLoop + 0] = SCE->REG_100H;
            ARG2[1+oLoop + 1] = SCE->REG_100H;
            ARG2[1+oLoop + 2] = SCE->REG_100H;
            ARG2[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xc47ff753U, 0x04506ad6U, 0x013e3dd5U, 0xbe1ead25U);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00000885U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[iLoop + 0];
        SCE->REG_100H = ARG1[iLoop + 1];
        SCE->REG_100H = ARG1[iLoop + 2];
        SCE->REG_100H = ARG1[iLoop + 3];
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
        ARG2[1+oLoop + 0] = SCE->REG_100H;
        ARG2[1+oLoop + 1] = SCE->REG_100H;
        ARG2[1+oLoop + 2] = SCE->REG_100H;
        ARG2[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x3b861e61U, 0xb600ea62U, 0x4bf70f4eU, 0xff3c1866U);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func062(36,ARG2);
        oLoop = 36 + 32;
        HW_SCE_p_func101(0x23e8fb2eU, 0x74657e4dU, 0x076514e5U, 0xb519809cU);
    }
    else if (0x0b000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x65278693U, 0x04fabe2eU, 0xfc2fa6d5U, 0x9de2decbU);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func066(0,ARG1);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func062(0,ARG2);
        oLoop = 0 + 32;
        HW_SCE_p_func100(0x7fa0d5a1U, 0x3517f529U, 0x36e90eafU, 0x91f1dc4bU);
        SCE->REG_00H = 0x00003183U;
        SCE->REG_2CH = 0x00000011U;
        HW_SCE_p_func066(32,ARG1);
        iLoop = 32 + 32;
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000021U;
        HW_SCE_p_func062(32,ARG2);
        oLoop = 32 + 32;
        HW_SCE_p_func100(0xcaa3bb50U, 0xd6691c2bU, 0xc5ff2240U, 0x7f7071bdU);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func062(64,ARG2);
        oLoop = 64 + 32;
        HW_SCE_p_func101(0x8427d069U, 0x71e1837eU, 0x1d040576U, 0x0c34e400U);
    }
    else if (0x0c000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0xa26076b9U, 0x10e94805U, 0x196f6ef1U, 0xf38da63dU);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func067(0,ARG1);
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
            ARG2[1+oLoop + 0] = SCE->REG_100H;
            ARG2[1+oLoop + 1] = SCE->REG_100H;
            ARG2[1+oLoop + 2] = SCE->REG_100H;
            ARG2[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xa56b7d5dU, 0xf4486507U, 0x64d0b38fU, 0x04fb55a5U);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00000885U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[iLoop + 0];
        SCE->REG_100H = ARG1[iLoop + 1];
        SCE->REG_100H = ARG1[iLoop + 2];
        SCE->REG_100H = ARG1[iLoop + 3];
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
        ARG2[1+oLoop + 0] = SCE->REG_100H;
        ARG2[1+oLoop + 1] = SCE->REG_100H;
        ARG2[1+oLoop + 2] = SCE->REG_100H;
        ARG2[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0U != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0x4aed1905U, 0xe5d8ff2eU, 0xcee610e7U, 0x2b56f36cU);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func064(68,ARG2);
        oLoop = 68 + 64;
        HW_SCE_p_func101(0x953dbb7cU, 0x684783a0U, 0xec9db7b7U, 0xeadfcaa6U);
    }
    else if (0x0d000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x0da69955U, 0x4c58a953U, 0x660176a5U, 0xb9ae0c4eU);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func067(0,ARG1);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func064(0,ARG2);
        oLoop = 0 + 64;
        HW_SCE_p_func100(0x58754c97U, 0xd4752e10U, 0x9fa38d8fU, 0xbe29908fU);
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000010U;
        HW_SCE_p_func067(64,ARG1);
        iLoop = 64 + 64;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func064(64,ARG2);
        oLoop = 64 + 64;
        HW_SCE_p_func100(0x3ab34648U, 0x51ed9b48U, 0x476e0a97U, 0x9dd57620U);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func064(128,ARG2);
        oLoop = 128 + 64;
        HW_SCE_p_func101(0x25db8d2cU, 0xd2c88a95U, 0x654191cbU, 0x45fcaca9U);
    }
    else if (0x12000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func100(0x546d42e4U, 0x4fab67faU, 0x54171dfeU, 0x01b96779U);
        SCE->REG_00H = 0x80002100U;
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00000886U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x02e08886U;
        SCE->REG_04H = 0x0000c200U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG1[0];
        SCE->REG_100H = ARG1[1];
        SCE->REG_100H = ARG1[2];
        SCE->REG_100H = ARG1[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG1[4+iLoop + 0];
            SCE->REG_100H = ARG1[4+iLoop + 1];
            SCE->REG_100H = ARG1[4+iLoop + 2];
            SCE->REG_100H = ARG1[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG2[1+iLoop + 0] = SCE->REG_100H;
            ARG2[1+iLoop + 1] = SCE->REG_100H;
            ARG2[1+iLoop + 2] = SCE->REG_100H;
            ARG2[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG2[1+iLoop + 0] = SCE->REG_100H;
        ARG2[1+iLoop + 1] = SCE->REG_100H;
        ARG2[1+iLoop + 2] = SCE->REG_100H;
        ARG2[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x0afcbf2fU, 0xc4a4aabaU, 0x39c6470fU, 0x02417d40U);
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
    ARG2[1+oLoop + 0] = SCE->REG_100H;
    ARG2[1+oLoop + 1] = SCE->REG_100H;
    ARG2[1+oLoop + 2] = SCE->REG_100H;
    ARG2[1+oLoop + 3] = SCE->REG_100H;
    SCE->REG_ECH = 0x00007c1cU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func065_r1.prc
***********************************************************************************************************************/
