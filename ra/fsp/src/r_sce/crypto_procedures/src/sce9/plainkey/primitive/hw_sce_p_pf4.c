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
    (void)InData_KeyType;
    (void)OutData_PubKey;
    (void)OutData_PrivKey;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000f402U;
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
    HW_SCE_p_func100(0x559bf95fU, 0xebb795a1U, 0x6dc7cb91U, 0x6ee821fbU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7fbe7fe1U, 0xa5906d5eU, 0x43e09b67U, 0x4d4cf4ffU);
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
        HW_SCE_p_func100(0xb7d91f1dU, 0x1603c2b5U, 0x01b8091dU, 0x6410772cU);
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
        HW_SCE_p_func100(0x93efae5eU, 0xdfb854afU, 0xeaead505U, 0xf922d3fbU);
        HW_SCE_p_func070_r2(OFS_ADR);
        HW_SCE_p_func100(0xac5929b8U, 0x9009251bU, 0x3d6d1fdfU, 0x1da02173U);
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x8000c0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00890001U;
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x88a8f9acU, 0x709537c5U, 0xef19b46aU, 0xd7f9fa8fU);
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
        HW_SCE_p_func100(0xb4ea2121U, 0x3fec0e34U, 0xde041e9dU, 0xb8f5bb73U);
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
        HW_SCE_p_func100(0x780a5964U, 0x6e5c9e99U, 0x8c0a5040U, 0x002f258aU);
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
            HW_SCE_p_func101(0x9f1db89dU, 0x0f5aa67bU, 0x2b151cd8U, 0x3dc562ecU);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00880001U;
            HW_SCE_p_func101(0xca3f7eeeU, 0x09a4472aU, 0x2e218f86U, 0x908b33daU);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00870001U;
            HW_SCE_p_func101(0x9c093ae5U, 0x1ed6255aU, 0x8f67f24aU, 0xeb53eefbU);
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
        SCE->REG_24H = 0x0000dcd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000820U;
        SCE->REG_24H = 0x80009cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xb0cc8c1aU, 0xdabf4f6eU, 0x50ddfd40U, 0x55d7e34fU);
        SCE->REG_24H = 0x000084d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00021028U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1U;
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
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004404U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e8d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000808U;
        SCE->REG_24H = 0x8000f0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func071_r2(OFS_ADR);
        HW_SCE_p_func100(0x40c0ae57U, 0x29ba04aeU, 0xc761c11eU, 0x1bd201abU);
        SCE->REG_34H = 0x00000802U;
        SCE->REG_24H = 0x800088d0U;
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
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000021U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00000bdeU;
        SCE->REG_ECH = 0x00000842U;
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x00000100U;
        SCE->REG_ECH = 0x0000b7a0U;
        SCE->REG_ECH = 0x000000f4U;
        SCE->REG_ECH = 0x0000377cU;
        SCE->REG_ECH = 0x00000b9cU;
        SCE->REG_E0H = 0x81010380U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<256;iLoop=iLoop+1)
        {
            HW_SCE_p_func101(0xc75067e4U, 0x65f5d835U, 0x270dd151U, 0x1ff8007fU);
            HW_SCE_p_func300();
            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }
            HW_SCE_p_func101(0x8e822641U, 0xa560dfdbU, 0xcd8aa6f6U, 0x7ac6e030U);
        }
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
        HW_SCE_p_func100(0xe2066680U, 0xf0184b25U, 0xf343846fU, 0xa63764f2U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x4356149eU, 0x5afb71ceU, 0xe511df28U, 0xdd8745e2U);
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
            SCE->REG_24H = 0x00001dc0U;
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
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x8000f4d0U;
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
            SCE->REG_24H = 0x00005004U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00008404U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x00000bffU;
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x00000021U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            for(iLoop=0; iLoop<8; iLoop=iLoop+1)
            {
                SCE->REG_ECH = 0x0000381fU;
                for(jLoop=0; jLoop<32; jLoop=jLoop+1)
                {
                    SCE->REG_24H = 0x0000102cU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1U;
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
                    SCE->REG_ECH = 0x3800d81fU;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00A60000U;
                    SCE->REG_ECH = 0x00016c00U;
                    HW_SCE_p_func100(0x837faa79U, 0xae805b51U, 0xa4f2c9bfU, 0x7ffc4df8U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        SCE->REG_24H = 0x0000082cU;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1U;
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
                        HW_SCE_p_func101(0xaeabc302U, 0x1b959fdcU, 0xd1c51b83U, 0x95ab024fU);
                    }
                    else
                    {
                        HW_SCE_p_func101(0xbf206840U, 0x607bab5dU, 0x9367a3bfU, 0x193a6d4aU);
                    }
                }
                SCE->REG_ECH = 0x000027e1U;
                HW_SCE_p_func101(0x4a374666U, 0x52864535U, 0xc339c67cU, 0x34409fbaU);
            }
            SCE->REG_ECH = 0x00008be0U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func301();
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
            HW_SCE_p_func100(0xda6efe49U, 0x0193da14U, 0x413f34aeU, 0x66b6673dU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func100(0xefd47e77U, 0xeb7bfaeeU, 0x7abc684cU, 0x6d1cfc27U);
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
                SCE->REG_100H = change_endian_long(0x000000f4U);
                HW_SCE_p_func101(0xedd705fdU, 0x7c2f451fU, 0xd9176d40U, 0xcc058eecU);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000379bU;
                HW_SCE_p_func074_r1();
                SCE->REG_ECH = 0x000034feU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f4U);
                HW_SCE_p_func101(0xb255d103U, 0xd13ef5d2U, 0x45974775U, 0xadde338bU);
                HW_SCE_p_func044();
                HW_SCE_p_func100(0x0e9623e0U, 0xf58c286aU, 0xf778486aU, 0x4df18dd9U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
                SCE->REG_2CH = 0x0000002dU;
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
                OutData_PrivKeyIndex[1] = SCE->REG_100H;
                OutData_PrivKeyIndex[2] = SCE->REG_100H;
                OutData_PrivKeyIndex[3] = SCE->REG_100H;
                OutData_PrivKeyIndex[4] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[5] = SCE->REG_100H;
                OutData_PrivKeyIndex[6] = SCE->REG_100H;
                OutData_PrivKeyIndex[7] = SCE->REG_100H;
                OutData_PrivKeyIndex[8] = SCE->REG_100H;
                HW_SCE_p_func100(0x3019d35cU, 0x645ddc1dU, 0x35918009U, 0x199ce470U);
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
                OutData_PrivKeyIndex[9] = SCE->REG_100H;
                OutData_PrivKeyIndex[10] = SCE->REG_100H;
                OutData_PrivKeyIndex[11] = SCE->REG_100H;
                OutData_PrivKeyIndex[12] = SCE->REG_100H;
                HW_SCE_p_func100(0x425dd56dU, 0xaab5a89cU, 0x75d7c47fU, 0xdacdb289U);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[0] = SCE->REG_100H;
                HW_SCE_p_func100(0xec71435aU, 0x62d6e866U, 0xaca8918dU, 0x3c88529aU);
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
                SCE->REG_100H = change_endian_long(0x00000001U);
                HW_SCE_p_func101(0x878f63fdU, 0x1d540d16U, 0x7ec1ac78U, 0xb20bf112U);
                HW_SCE_p_func043();
                HW_SCE_p_func075_r1();
                SCE->REG_ECH = 0x000034feU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000002U);
                HW_SCE_p_func101(0xb177a360U, 0xa939f773U, 0x7d142f97U, 0x6344bcedU);
                HW_SCE_p_func044();
                HW_SCE_p_func100(0xbb1bd422U, 0xef8c3c92U, 0x4cd047daU, 0x8a62dbe3U);
                SCE->REG_D0H = 0x40000200U;
                SCE->REG_C4H = 0x02e08887U;
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
                OutData_PubKeyIndex[1] = SCE->REG_100H;
                OutData_PubKeyIndex[2] = SCE->REG_100H;
                OutData_PubKeyIndex[3] = SCE->REG_100H;
                OutData_PubKeyIndex[4] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[5] = SCE->REG_100H;
                OutData_PubKeyIndex[6] = SCE->REG_100H;
                OutData_PubKeyIndex[7] = SCE->REG_100H;
                OutData_PubKeyIndex[8] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[9] = SCE->REG_100H;
                OutData_PubKeyIndex[10] = SCE->REG_100H;
                OutData_PubKeyIndex[11] = SCE->REG_100H;
                OutData_PubKeyIndex[12] = SCE->REG_100H;
                HW_SCE_p_func100(0x5ca913faU, 0x6604aba7U, 0x5e907a49U, 0xe6ac5f43U);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x00e08885U;
                SCE->REG_00H = 0x00002313U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000052U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x000089c4U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_04H = 0x00000222U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[13] = SCE->REG_100H;
                OutData_PubKeyIndex[14] = SCE->REG_100H;
                OutData_PubKeyIndex[15] = SCE->REG_100H;
                OutData_PubKeyIndex[16] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[17] = SCE->REG_100H;
                OutData_PubKeyIndex[18] = SCE->REG_100H;
                OutData_PubKeyIndex[19] = SCE->REG_100H;
                OutData_PubKeyIndex[20] = SCE->REG_100H;
                HW_SCE_p_func100(0xa27751c1U, 0x16ee123cU, 0x8536a299U, 0x3fe25d73U);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[0] = SCE->REG_100H;
                HW_SCE_p_func101(0x72005084U, 0x90c1d887U, 0x2eb14108U, 0x07a53a3fU);
            }
            else
            {
                HW_SCE_p_func100(0xf5306cf4U, 0x62579919U, 0x96ba9447U, 0xb79cac61U);
                SCE->REG_2CH = 0x0000002dU;
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
                HW_SCE_p_func100(0x81532d5fU, 0x53f4e578U, 0xe3c6dbb7U, 0xf0eb45caU);
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
                HW_SCE_p_func100(0xc40351ecU, 0x5732d942U, 0x2de778c0U, 0xc9957558U);
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
                SCE->REG_34H = 0x00000400U;
                SCE->REG_24H = 0x800048d0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00004cd0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x008f0001U;
                HW_SCE_p_func100(0x3b6098f0U, 0x5d240785U, 0xbe8738feU, 0xf27ec80aU);
                SCE->REG_2CH = 0x00000022U;
                SCE->REG_04H = 0x00000342U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKey[16] = SCE->REG_100H;
                OutData_PubKey[17] = SCE->REG_100H;
                OutData_PubKey[18] = SCE->REG_100H;
                OutData_PubKey[19] = SCE->REG_100H;
                OutData_PubKey[20] = SCE->REG_100H;
                OutData_PubKey[21] = SCE->REG_100H;
                OutData_PubKey[22] = SCE->REG_100H;
                OutData_PubKey[23] = SCE->REG_100H;
                OutData_PubKey[24] = SCE->REG_100H;
                OutData_PubKey[25] = SCE->REG_100H;
                OutData_PubKey[26] = SCE->REG_100H;
                OutData_PubKey[27] = SCE->REG_100H;
                OutData_PubKey[28] = SCE->REG_100H;
                OutData_PubKey[29] = SCE->REG_100H;
                OutData_PubKey[30] = SCE->REG_100H;
                OutData_PubKey[31] = SCE->REG_100H;
                HW_SCE_p_func101(0x55c94b15U, 0xa3eca2aeU, 0x26ee840eU, 0x2bd2ece0U);
            }
            HW_SCE_p_func102(0x53d867a0U, 0x375d6bf4U, 0xd8193df0U, 0x78b87c3aU);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf4_r5.prc
***********************************************************************************************************************/
