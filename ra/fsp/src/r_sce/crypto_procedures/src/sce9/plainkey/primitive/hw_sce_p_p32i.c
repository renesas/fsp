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

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    uint32_t InData_DataType[1] = {0};
    uint32_t InData_Cmd[1]      = {0};
    uint32_t InData_SeqNum[2]   = {0, 0};
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
    SCE->REG_84H = 0x00003202U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_C4H = 0x200e1a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010100U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000d08U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x38008900U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xdd9640ceU, 0x25ac9382U, 0x64198734U, 0x80932e7eU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[0];
        SCE->REG_ECH = 0x38000d08U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x7b27127eU, 0xd8d290bbU, 0x5769c33cU, 0x23dee02bU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000032U);
            HW_SCE_p_func101(0x792ec90dU, 0xdd1224f8U, 0xb9cefd1dU, 0x18de7561U);
            HW_SCE_p_func043();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x00000005U;
            HW_SCE_p_func101(0x58a83a1fU, 0xd313ece4U, 0xdc2ffadcU, 0xf032b621U);
        }
        else
        {
            SCE->REG_ECH = 0x00003547U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000032U);
            HW_SCE_p_func101(0xd82d0abbU, 0x8980254aU, 0x11ebd2dfU, 0x4f2b95f2U);
            HW_SCE_p_func068();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x0146c04bU;
            HW_SCE_p_func101(0x909743dcU, 0x6a3f7342U, 0x54f93845U, 0xc8d45c52U);
        }
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000032U);
        HW_SCE_p_func101(0xab118389U, 0xb0997d8fU, 0x2f4502a2U, 0x77b66011U);
        HW_SCE_p_func044();
        SCE->REG_104H = 0x00000362U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x02f087b5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000362U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000087b5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000368U;
        SCE->REG_E0H = 0x80040080U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[1];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[2];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[3];
        HW_SCE_p_func101(0xa9a16879U, 0x9ca06cd5U, 0xc7b34f6bU, 0x04a1afadU);
    }
    else
    {
        SCE->REG_ECH = 0x38008900U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x35391339U, 0xfe32aa12U, 0x10e80637U, 0x6e8c67c5U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000368U;
            SCE->REG_E0H = 0x80040000U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[2];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x000037e0U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x00ff0000U;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00120000U;
            SCE->REG_ECH = 0x1000d3c0U;
            SCE->REG_ECH = 0x3800d80eU;
            SCE->REG_ECH = 0x2000d3c1U;
            SCE->REG_ECH = 0x000037e0U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x000000feU;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_ECH = 0x1000d3c2U;
            SCE->REG_ECH = 0x38008bc0U;
            SCE->REG_ECH = 0x00000007U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x00003540U;
            SCE->REG_ECH = 0x00003561U;
            SCE->REG_ECH = 0x00003582U;
            SCE->REG_ECH = 0x000035a3U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000032U);
            HW_SCE_p_func101(0x99a917feU, 0xcc1ee76bU, 0x82ca28d2U, 0x2983be85U);
            HW_SCE_p_func059();
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_E0H = 0x80040000U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x00f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_E0H = 0x80040080U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[12];
            SCE->REG_100H = InData_KeyIndex[13];
            SCE->REG_100H = InData_KeyIndex[14];
            SCE->REG_100H = InData_KeyIndex[15];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0xaaf493abU, 0xd14d7026U, 0x40fe3605U, 0x7189daefU);
        }
        else
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010140U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            SCE->REG_ECH = 0x3800a900U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x17503aa9U, 0x165c2793U, 0x1bf5a78cU, 0xc9a1780dU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000005U);
                HW_SCE_p_func101(0x4aec236bU, 0xa76966d2U, 0x7c3357beU, 0x4cacae75U);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0195f71dU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000005U);
                HW_SCE_p_func101(0xae0bda23U, 0x6d486cb9U, 0x4cd9b7bbU, 0xc741ba11U);
                HW_SCE_p_func044();
                HW_SCE_p_func101(0xc7aa49fbU, 0x7f88901fU, 0x58b8d0adU, 0xac20a386U);
            }
            else
            {
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x80010020U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_DataType[0];
                SCE->REG_ECH = 0x38000c21U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                HW_SCE_p_func100(0xa68b31bcU, 0x77a2b679U, 0xa66cff9eU, 0x884132aeU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_104H = 0x00000068U;
                    SCE->REG_E0H = 0x80010000U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_Cmd[0];
                    SCE->REG_ECH = 0x000036a0U;
                    SCE->REG_ECH = 0x0000b6c0U;
                    SCE->REG_ECH = 0x0126ee7fU;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000032U);
                    HW_SCE_p_func101(0x63756f95U, 0xdf1f784dU, 0xc9ddae30U, 0xaba98eebU);
                    HW_SCE_p_func082();
                    HW_SCE_p_func101(0x1efbeae5U, 0x5b3e1313U, 0x2e9033c5U, 0x49aa5537U);
                }
                else
                {
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000ecU);
                    HW_SCE_p_func101(0xe368a5f9U, 0xeffac90cU, 0x2c19ec6bU, 0x7e2a0c68U);
                    HW_SCE_p_func068();
                    SCE->REG_ECH = 0x0000b4e0U;
                    SCE->REG_ECH = 0x01bae316U;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000ecU);
                    HW_SCE_p_func101(0xbe62186bU, 0x2c17636bU, 0x186d4f8cU, 0x8398b9bbU);
                    HW_SCE_p_func044();
                    HW_SCE_p_func101(0x81a2c8daU, 0xe36ae01cU, 0x90156779U, 0x357cbb76U);
                }
                SCE->REG_104H = 0x00000168U;
                SCE->REG_E0H = 0x80020360U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SeqNum[0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SeqNum[1];
                HW_SCE_p_func101(0xe05b980dU, 0x73a1f29bU, 0x159afecbU, 0x9387431dU);
            }
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            SCE->REG_100H = InData_KeyIndex[2];
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_E0H = 0x80040000U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x00f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_E0H = 0x80040080U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_100H = InData_KeyIndex[12];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0x96487d5cU, 0x2b80fe4fU, 0x5c3a7fa5U, 0x5c6f2d46U);
        }
        HW_SCE_p_func101(0x42144622U, 0x23463917U, 0x5a687bd1U, 0x1b2ac5b1U);
    }
    HW_SCE_p_func100(0x8288a3f2U, 0x9d4c7699U, 0x30fddadeU, 0xb26157c4U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x13eeffc6U, 0xe6ce0b0bU, 0x2eae03eeU, 0x2a9b5de9U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xc1e91d46U, 0xdf317272U, 0x9ce8c12eU, 0x73f154c6U);
        SCE->REG_ECH = 0x3000a900U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x00010020U;
        SCE->REG_ECH = 0x000008bbU;
        SCE->REG_ECH = 0x000008dcU;
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_C4H = 0x00080805U;
        SCE->REG_00H = 0x00002813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_7CH = 0x00000001U;
        SCE->REG_7CH = 0x00000041U;
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000a84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_00H = 0x00005213U;
        SCE->REG_74H = 0x00001000U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_74H = 0x00000004U;
        SCE->REG_104H = 0x00000354U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_74H = 0x00000002U;
        HW_SCE_p_func101(0x3406306bU, 0x11c79103U, 0xb70824e1U, 0xf9ea4bd4U);
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p32i_r4.prc
***********************************************************************************************************************/
