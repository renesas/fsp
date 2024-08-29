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

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey)
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
    SCE->REG_84H = 0x0000f401U;
    SCE->REG_108H = 0x00000000U;
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
    SCE->REG_ECH = 0x3020ab80U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00060020U;
    SCE->REG_ECH = 0x0000b780U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x30000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d3e1U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x38000f9cU;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x0d733603U, 0x3bd0e927U, 0x2328d697U, 0xb3834113U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x79f11db0U, 0xbff6cc16U, 0x7ccad89aU, 0x3b4bf179U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x575b6e09U, 0xaf2cfdc9U, 0x4a12eb97U, 0xe7af6129U);
        SCE->REG_28H = 0x00870001U;
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
        HW_SCE_p_func100(0xcbd08dfdU, 0xa7bfa9eaU, 0x8dcdd99fU, 0xaedca75cU);
        HW_SCE_p_func070(OFS_ADR);
        SCE->REG_34H = 0x00000003U;
        SCE->REG_24H = 0x800068d0U;
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
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x8000c0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00890001U;
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x69856257U, 0x4a9ac37fU, 0xfcbceb70U, 0x5e2dfbf4U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00003213U;
        SCE->REG_2CH = 0x00000011U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x767f80f6U, 0xa0dfa58fU, 0xb84f0847U, 0xd1531358U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00003213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x28ddc015U, 0x63886a08U, 0xab6324a3U, 0xcbd6714bU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x0000320bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000020bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00007c1cU;
        SCE->REG_1CH = 0x00600000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00890001U;
            HW_SCE_p_func101(0x9fb8d2a5U, 0xf81954a7U, 0xe83dbb5dU, 0x5f5f6b18U);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00880001U;
            HW_SCE_p_func101(0x650fa4cdU, 0xc8660518U, 0x4d561fe4U, 0x29fc2f42U);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00870001U;
            HW_SCE_p_func101(0xd06daa4fU, 0xf3d804e1U, 0x5dfcafc7U, 0x0497f983U);
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
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000004U;
        SCE->REG_24H = 0x0000a206U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_24H = 0x000016c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000682U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c2U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        HW_SCE_p_func100(0x615ab770U, 0xccad25eaU, 0xa566b914U, 0xecfbe5a5U);
        SCE->REG_24H = 0x0000dcd0U;
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
        HW_SCE_p_func071(OFS_ADR);
        HW_SCE_p_func025_r1(OFS_ADR);
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x8000b8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800088d0U;
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
        SCE->REG_24H = 0x00008cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000ec0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000f008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x00311030U;
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
        HW_SCE_p_func100(0xafd0e8e0U, 0x9d73efa7U, 0x4ce32b55U, 0x689eaff6U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x7273b5d9U, 0x6866d96cU, 0xabe528e2U, 0x2a13a8afU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0xd0db7737U, 0x8fe4ac1dU, 0x01a205f8U, 0x7b97c100U);
            SCE->REG_24H = 0x00009cd0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800054d0U;
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
            SCE->REG_24H = 0x000040c2U;
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
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800103e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyType[0];
            SCE->REG_ECH = 0x38000fffU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x6656643cU, 0xc3953955U, 0xb4d9a5ddU, 0xf9363096U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func100(0x48d56d5dU, 0xf9ea591cU, 0x82a7a9adU, 0x4daa9d2eU);
                HW_SCE_p_func103();
                HW_SCE_p_func100(0x15544071U, 0xe1b19318U, 0x1e93cf51U, 0x51bb0ecaU);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
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
                SCE->REG_C4H = 0x200c3b0dU;
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_00H = 0x00002813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func022_r1();
                SCE->REG_D0H = 0x00000100U;
                SCE->REG_C4H = 0x02e087bfU;
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
                OutData_PrivKeyIndex[4] = SCE->REG_100H;
                OutData_PrivKeyIndex[5] = SCE->REG_100H;
                OutData_PrivKeyIndex[6] = SCE->REG_100H;
                OutData_PrivKeyIndex[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[8] = SCE->REG_100H;
                OutData_PrivKeyIndex[9] = SCE->REG_100H;
                OutData_PrivKeyIndex[10] = SCE->REG_100H;
                OutData_PrivKeyIndex[11] = SCE->REG_100H;
                HW_SCE_p_func100(0x5a50d4a7U, 0xae0bd39aU, 0x1a35842dU, 0xc5e0b050U);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_C4H = 0x000009cdU;
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
                OutData_PrivKeyIndex[12] = SCE->REG_100H;
                OutData_PrivKeyIndex[13] = SCE->REG_100H;
                OutData_PrivKeyIndex[14] = SCE->REG_100H;
                OutData_PrivKeyIndex[15] = SCE->REG_100H;
                HW_SCE_p_func100(0xe6eef1d3U, 0xe71916dbU, 0x27ea97d2U, 0x23623b42U);
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[3] = SCE->REG_100H;
                HW_SCE_p_func100(0x52d316b9U, 0x68626d64U, 0x956248d0U, 0x6c1029eeU);
                HW_SCE_p_func103();
                HW_SCE_p_func100(0x277d9bfaU, 0xc1dcc1c1U, 0x3d00bac2U, 0x9c65874cU);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
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
                SCE->REG_C4H = 0x200c3b0dU;
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_00H = 0x00002813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func023_r1();
                SCE->REG_D0H = 0x00000200U;
                SCE->REG_C4H = 0x02e0888fU;
                SCE->REG_00H = 0x00002323U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x00002313U;
                SCE->REG_2CH = 0x00000023U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000232U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[4] = SCE->REG_100H;
                OutData_PubKeyIndex[5] = SCE->REG_100H;
                OutData_PubKeyIndex[6] = SCE->REG_100H;
                OutData_PubKeyIndex[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[8] = SCE->REG_100H;
                OutData_PubKeyIndex[9] = SCE->REG_100H;
                OutData_PubKeyIndex[10] = SCE->REG_100H;
                OutData_PubKeyIndex[11] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[12] = SCE->REG_100H;
                OutData_PubKeyIndex[13] = SCE->REG_100H;
                OutData_PubKeyIndex[14] = SCE->REG_100H;
                OutData_PubKeyIndex[15] = SCE->REG_100H;
                HW_SCE_p_func100(0xe49b9ef1U, 0x8e106c11U, 0xd260baf3U, 0x2050f273U);
                SCE->REG_C4H = 0x0045094cU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_C4H = 0x00e0088dU;
                SCE->REG_00H = 0x00002313U;
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
                OutData_PubKeyIndex[16] = SCE->REG_100H;
                OutData_PubKeyIndex[17] = SCE->REG_100H;
                OutData_PubKeyIndex[18] = SCE->REG_100H;
                OutData_PubKeyIndex[19] = SCE->REG_100H;
                HW_SCE_p_func100(0xdf09fb1bU, 0x0a5907a8U, 0x9d3a40ceU, 0x7bb92884U);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00000cc4U;
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
                OutData_PubKeyIndex[20] = SCE->REG_100H;
                OutData_PubKeyIndex[21] = SCE->REG_100H;
                OutData_PubKeyIndex[22] = SCE->REG_100H;
                OutData_PubKeyIndex[23] = SCE->REG_100H;
                HW_SCE_p_func100(0x32a13a9fU, 0x7f233b71U, 0x61cd377dU, 0x8bb80066U);
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[3] = SCE->REG_100H;
                HW_SCE_p_func101(0x2bd09d72U, 0x62ec4b5bU, 0xde9456e9U, 0x5611c623U);
            }
            else
            {
                HW_SCE_p_func100(0x16ecbe5cU, 0xc64de9afU, 0xbd8862abU, 0xbaf88881U);
                SCE->REG_2CH = 0x0000002aU;
                SCE->REG_04H = 0x00000322U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKey[0] = SCE->REG_100H;
                OutData_PrivKey[1] = SCE->REG_100H;
                OutData_PrivKey[2] = SCE->REG_100H;
                OutData_PrivKey[3] = SCE->REG_100H;
                OutData_PrivKey[4] = SCE->REG_100H;
                OutData_PrivKey[5] = SCE->REG_100H;
                OutData_PrivKey[6] = SCE->REG_100H;
                OutData_PrivKey[7] = SCE->REG_100H;
                HW_SCE_p_func100(0x561dee15U, 0x5f543f23U, 0x80d064a8U, 0x1fc41ac2U);
                SCE->REG_2CH = 0x00000022U;
                SCE->REG_04H = 0x00000322U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKey[0] = SCE->REG_100H;
                OutData_PubKey[1] = SCE->REG_100H;
                OutData_PubKey[2] = SCE->REG_100H;
                OutData_PubKey[3] = SCE->REG_100H;
                OutData_PubKey[4] = SCE->REG_100H;
                OutData_PubKey[5] = SCE->REG_100H;
                OutData_PubKey[6] = SCE->REG_100H;
                OutData_PubKey[7] = SCE->REG_100H;
                HW_SCE_p_func100(0xe6683e8aU, 0x6f628f7eU, 0x3021cf1bU, 0xb8cd328bU);
                SCE->REG_2CH = 0x00000023U;
                SCE->REG_04H = 0x00000322U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKey[8] = SCE->REG_100H;
                OutData_PubKey[9] = SCE->REG_100H;
                OutData_PubKey[10] = SCE->REG_100H;
                OutData_PubKey[11] = SCE->REG_100H;
                OutData_PubKey[12] = SCE->REG_100H;
                OutData_PubKey[13] = SCE->REG_100H;
                OutData_PubKey[14] = SCE->REG_100H;
                OutData_PubKey[15] = SCE->REG_100H;
                HW_SCE_p_func101(0xbf9fb146U, 0xe7cd20a2U, 0xcedbbd69U, 0xd206aba2U);
            }
            HW_SCE_p_func102(0x2f43a678U, 0xd2e710d7U, 0x722277bfU, 0x8e0caaddU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_pf4_r2.prc
***********************************************************************************************************************/
