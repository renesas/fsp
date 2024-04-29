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

void HW_SCE_p_func073(uint32_t ARG1)
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
    SCE->REG_28H = 0x00870001U;
    OFS_ADR = ARG1;
    HW_SCE_p_func070(OFS_ADR);
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000403U;
    SCE->REG_24H = 0x8000e8d0U;
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
    SCE->REG_24H = 0x00029008U;
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
    SCE->REG_34H = 0x00000010U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x80008cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000880cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x800088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x800094d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000880cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x8000acd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010360U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000f5U);
    HW_SCE_p_func101(0xa5c4e191U, 0x58438f3dU, 0x08d0f785U, 0x174f4a24U);
    HW_SCE_p_func006();
    HW_SCE_p_func100(0x36637315U, 0x3b255e0fU, 0xb00a1997U, 0x25c6636aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x00000800U;
        HW_SCE_p_func101(0xb626e53cU, 0xca8bc9fdU, 0x21bb4b39U, 0x11bf398eU);
    }
    else
    {
        HW_SCE_p_func100(0x95eec4d9U, 0xcca0a5abU, 0x23666d2fU, 0x537d93d1U);
        SCE->REG_24H = 0x00009cd0U;
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
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x000000b0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_34H = 0x00000010U;
        SCE->REG_24H = 0x80005cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000880cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800050d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004a0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000480cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004a0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800074d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006c0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00006e0cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xa659aae1U, 0x5fc65226U, 0xf10d546aU, 0x789be582U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xed4e0f05U, 0xd2c8179cU, 0xacf8ece1U, 0x17791351U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01080c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0xbb420842U, 0x41276885U, 0x1884fc99U, 0x95691051U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x42e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000aaU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[0] = SCE->REG_100H;
        S_HEAP[1] = SCE->REG_100H;
        S_HEAP[2] = SCE->REG_100H;
        S_HEAP[3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[4] = SCE->REG_100H;
        S_HEAP[5] = SCE->REG_100H;
        S_HEAP[6] = SCE->REG_100H;
        S_HEAP[7] = SCE->REG_100H;
        HW_SCE_p_func100(0xdb59585aU, 0xb30df8b7U, 0x1558989dU, 0xe6ae99fbU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000abU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[8] = SCE->REG_100H;
        S_HEAP[9] = SCE->REG_100H;
        S_HEAP[10] = SCE->REG_100H;
        S_HEAP[11] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[12] = SCE->REG_100H;
        S_HEAP[13] = SCE->REG_100H;
        S_HEAP[14] = SCE->REG_100H;
        S_HEAP[15] = SCE->REG_100H;
        HW_SCE_p_func100(0xa2dde7b3U, 0xdac73432U, 0x686687fbU, 0x04f06303U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000a8U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[16] = SCE->REG_100H;
        S_HEAP[17] = SCE->REG_100H;
        S_HEAP[18] = SCE->REG_100H;
        S_HEAP[19] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[20] = SCE->REG_100H;
        S_HEAP[21] = SCE->REG_100H;
        S_HEAP[22] = SCE->REG_100H;
        S_HEAP[23] = SCE->REG_100H;
        HW_SCE_p_func100(0x7e970e36U, 0xa9f25796U, 0x2ffdc35bU, 0x55658ab4U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x000000a9U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[24] = SCE->REG_100H;
        S_HEAP[25] = SCE->REG_100H;
        S_HEAP[26] = SCE->REG_100H;
        S_HEAP[27] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[28] = SCE->REG_100H;
        S_HEAP[29] = SCE->REG_100H;
        S_HEAP[30] = SCE->REG_100H;
        S_HEAP[31] = SCE->REG_100H;
        HW_SCE_p_func100(0xf5f0d84aU, 0x182c912dU, 0xead8808bU, 0x197d604fU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x0000002aU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[32] = SCE->REG_100H;
        S_HEAP[33] = SCE->REG_100H;
        S_HEAP[34] = SCE->REG_100H;
        S_HEAP[35] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[36] = SCE->REG_100H;
        S_HEAP[37] = SCE->REG_100H;
        S_HEAP[38] = SCE->REG_100H;
        S_HEAP[39] = SCE->REG_100H;
        HW_SCE_p_func100(0xb9532b14U, 0x56120031U, 0x24c99a45U, 0xb295d6ddU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x0000002bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[40] = SCE->REG_100H;
        S_HEAP[41] = SCE->REG_100H;
        S_HEAP[42] = SCE->REG_100H;
        S_HEAP[43] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[44] = SCE->REG_100H;
        S_HEAP[45] = SCE->REG_100H;
        S_HEAP[46] = SCE->REG_100H;
        S_HEAP[47] = SCE->REG_100H;
        HW_SCE_p_func100(0x127c6380U, 0x098a4a70U, 0x6177946fU, 0x418fce0dU);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[48] = SCE->REG_100H;
        S_HEAP[49] = SCE->REG_100H;
        S_HEAP[50] = SCE->REG_100H;
        S_HEAP[51] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[52] = SCE->REG_100H;
        S_HEAP[53] = SCE->REG_100H;
        S_HEAP[54] = SCE->REG_100H;
        S_HEAP[55] = SCE->REG_100H;
        HW_SCE_p_func100(0x5bd388bdU, 0x2ee011fdU, 0x8f9fa3d2U, 0x5cdb8b28U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000023U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[56] = SCE->REG_100H;
        S_HEAP[57] = SCE->REG_100H;
        S_HEAP[58] = SCE->REG_100H;
        S_HEAP[59] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[60] = SCE->REG_100H;
        S_HEAP[61] = SCE->REG_100H;
        S_HEAP[62] = SCE->REG_100H;
        S_HEAP[63] = SCE->REG_100H;
        HW_SCE_p_func100(0x295dbc9cU, 0xac99181bU, 0xfc72fdffU, 0xa94f0af1U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x400009cdU;
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
        S_HEAP[64] = SCE->REG_100H;
        S_HEAP[65] = SCE->REG_100H;
        S_HEAP[66] = SCE->REG_100H;
        S_HEAP[67] = SCE->REG_100H;
        HW_SCE_p_func070(OFS_ADR);
        SCE->REG_24H = 0x000019c0U;
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
        SCE->REG_24H = 0x0000e0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000403U;
        SCE->REG_24H = 0x8000e8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000002U;
        SCE->REG_24H = 0x800048d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000c00U;
        SCE->REG_24H = 0x800058d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000c20U;
        SCE->REG_24H = 0x8000bcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x00003523U;
        SCE->REG_74H = 0x00000008U;
        SCE->REG_2CH = 0x00000094U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00000908U;
        SCE->REG_E0H = 0x81900008U;
        SCE->REG_00H = 0x00003823U;
        SCE->REG_2CH = 0x0000001dU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00003823U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x0000dcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a4d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0002b208U;
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
        SCE->REG_34H = 0x00000020U;
        SCE->REG_24H = 0x80007cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000d91U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_34H = 0x00000020U;
        SCE->REG_24H = 0x80001dc0U;
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
        SCE->REG_24H = 0x00001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_24H = 0x000011c0U;
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
        HW_SCE_p_func100(0x5922d00eU, 0x09a5b93eU, 0x80fc212cU, 0xc1d54bc2U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x00000800U;
            HW_SCE_p_func101(0xfa0baba0U, 0x2fb56c0aU, 0x4fee2e78U, 0xd99eb118U);
        }
        else
        {
            SCE->REG_34H = 0x00000c20U;
            SCE->REG_24H = 0x8000fcd0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800048d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            HW_SCE_p_func100(0x3ae2fc81U, 0xc077ef85U, 0xd596bb0fU, 0x76566905U);
            HW_SCE_p_func009();
            HW_SCE_p_func100(0x1b60f700U, 0xbd190f49U, 0xf9f4f852U, 0xd1f32c1eU);
            SCE->REG_34H = 0x00000410U;
            SCE->REG_24H = 0x800098d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            HW_SCE_p_func071(OFS_ADR);
            SCE->REG_34H = 0x00000110U;
            SCE->REG_24H = 0x800019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000110U;
            SCE->REG_24H = 0x80001ec0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000330U;
            SCE->REG_24H = 0x800019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000330U;
            SCE->REG_24H = 0x80001ec0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            HW_SCE_p_func011(S_HEAP);
            SCE->REG_34H = 0x00000008U;
            SCE->REG_24H = 0x8000f0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008U;
            SCE->REG_24H = 0x800050d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000004U;
            SCE->REG_38H = 0x00231030U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000U;
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
            HW_SCE_p_func100(0x34747facU, 0xee23eceeU, 0x0649f4c0U, 0xfa74c83fU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00000800U;
                HW_SCE_p_func101(0xe579ec08U, 0xe5acf944U, 0x66e2b736U, 0xcc9b81b4U);
            }
            else
            {
                SCE->REG_24H = 0x0000bcd0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000b20cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000054d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x00000908U;
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000060U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x00000908U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000013U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x00008c0cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000880cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000008U;
                SCE->REG_24H = 0x800011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001191U;
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
                SCE->REG_24H = 0x00009008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000014U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x0000a4d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0002b208U;
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
                SCE->REG_ECH = 0x0000b500U;
                SCE->REG_ECH = 0x00000040U;
                SCE->REG_E0H = 0x81880008U;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000012U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x0000880cU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
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
                SCE->REG_1CH = 0x00a10000U;
                HW_SCE_p_func100(0xcf26202bU, 0x7502003bU, 0x28c5085bU, 0xa4a24219U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00000800U;
                    HW_SCE_p_func101(0xaeda6663U, 0x23d676c9U, 0x7d31f407U, 0x733c5f72U);
                }
                else
                {
                    SCE->REG_ECH = 0x0000d000U;
                    HW_SCE_p_func101(0x68b11293U, 0x6daa1e6bU, 0x93a2a099U, 0xfbf58172U);
                }
            }
        }
    }
    SCE->REG_ECH = 0x38000c00U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func073.prc
***********************************************************************************************************************/
