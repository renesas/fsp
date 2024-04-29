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

fsp_err_t HW_SCE_LoadHukSub(uint32_t *InData_LC)
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
    SCE->REG_84H = 0x00004001U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func048(InData_LC);
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_ECH = 0x34202801U;
    SCE->REG_ECH = 0x20003401U;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
    if (InData_LC[0] == 0x00000000)
    {
        SCE->REG_1CH = 0x00b80000U;
        HW_SCE_p_func101(0x8df65220U, 0x66b86af0U, 0x024552f0U, 0x698bb6acU);
    }
    else if (InData_LC[0] == 0x00000001)
    {
        SCE->REG_1CH = 0x00b00000U;
        HW_SCE_p_func101(0x75474f29U, 0xcf9f73aaU, 0xa8987b45U, 0x01019f0cU);
    }
    else if (InData_LC[0] == 0x00000002)
    {
        SCE->REG_1CH = 0x00b10000U;
        HW_SCE_p_func101(0x37fe7e13U, 0xdba1bf8dU, 0xad1e7c16U, 0xf4949bbaU);
    }
    else if (InData_LC[0] == 0x00000003)
    {
        SCE->REG_1CH = 0x00b20000U;
        HW_SCE_p_func101(0xcaf7e415U, 0x4128fb42U, 0xdb48afe2U, 0x99074a75U);
    }
    else if (InData_LC[0] == 0x00000004)
    {
        SCE->REG_1CH = 0x00b30000U;
        HW_SCE_p_func101(0x57f8f4a6U, 0x94787521U, 0x31fcee4fU, 0x864d46bdU);
    }
    else if (InData_LC[0] == 0x00000005)
    {
        SCE->REG_1CH = 0x00b40000U;
        HW_SCE_p_func101(0xb16bd6fdU, 0xc927d654U, 0xfc8bef50U, 0x3d3513a4U);
    }
    else if (InData_LC[0] == 0x00000006)
    {
        SCE->REG_1CH = 0x00b50000U;
        HW_SCE_p_func101(0x086e5c12U, 0x2708cae7U, 0x24c60329U, 0xd6a1f0ceU);
    }
    else if (InData_LC[0] == 0x00000007)
    {
        SCE->REG_1CH = 0x00b60000U;
        HW_SCE_p_func101(0x64586489U, 0xe5ec3887U, 0xaf796043U, 0xf870aad7U);
    }
    else if (InData_LC[0] == 0x00000008)
    {
        SCE->REG_1CH = 0x00b70000U;
        HW_SCE_p_func101(0xdd18b7c6U, 0x61da8f10U, 0x2dddd787U, 0x0986d7deU);
    }
    else
    {
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func101(0x855d7c4aU, 0x63f263faU, 0x172ed129U, 0x7c8fa20fU);
    }
    HW_SCE_p_func100(0xc49e2b89U, 0x3ccaecb7U, 0xa622a807U, 0x78f51bbeU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x0c3811c9U, 0xb8dedefdU, 0xeb431a83U, 0xd5122286U);
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
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x000f3a0dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x7e2fdbffU);
        SCE->REG_100H = change_endian_long(0xd4e34e49U);
        SCE->REG_100H = change_endian_long(0x86044a47U);
        SCE->REG_100H = change_endian_long(0x78ea77fbU);
        HW_SCE_p_func100(0x5a22ea97U, 0xb775468eU, 0xc77479b3U, 0xa7c5d2eaU);
        SCE->REG_C4H = 0x20443a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x20083e1cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01ea725dU);
        HW_SCE_p_func100(0xfbcffc6bU, 0xce9dd311U, 0x605e19c8U, 0xfe10bb07U);
        SCE->REG_C4H = 0x20443a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x20093e1cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x02ea725dU);
        SCE->REG_104H = 0x00000352U;
        SCE->REG_C4H = 0x000f3a0dU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x1201f0d2U);
        SCE->REG_100H = change_endian_long(0x9fc1d562U);
        SCE->REG_100H = change_endian_long(0x4f02fc25U);
        SCE->REG_100H = change_endian_long(0x6b60ff19U);
        HW_SCE_p_func100(0xba5d965cU, 0x54ecb6f4U, 0xf3e2d5bfU, 0xcf8889bcU);
        SCE->REG_D0H = 0x40000100U;
        SCE->REG_C4H = 0x02f087b5U;
        SCE->REG_E8H = 0x80000000U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00f087b5U;
        SCE->REG_E8H = 0x80000004U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x00080805U;
        SCE->REG_00H = 0x00001213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xae1e176eU, 0x880b1b75U, 0x6486a9a3U, 0x9cf0492aU);
        SCE->REG_A4H = 0x00090805U;
        SCE->REG_00H = 0x00001213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001b0U;
        SCE->REG_ECH = 0x00003c01U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000087b5U;
        SCE->REG_E8H = 0x80000008U;
        SCE->REG_00H = 0x00002613U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x00800c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000251U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00448a04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019ee295U);
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x029ee295U);
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001d0U;
        SCE->REG_E0H = 0x80880001U;
        SCE->REG_00H = 0x00008123U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_p_func100(0xf779cdc0U, 0x8979d743U, 0x8cdcd58bU, 0xabca3852U);
        SCE->REG_C4H = 0x20443a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x200c3e1cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0152db38U);
        SCE->REG_C4H = 0x00440a0cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x00000e9cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f7370eU);
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x000001c0U;
        SCE->REG_E0H = 0x80840001U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_13CH = 0x00000211U;
        HW_SCE_p_func102(0xff71be6bU, 0xdfbc00b3U, 0xa5a52bdaU, 0x8b9ab0edU);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p40_r2.prc
***********************************************************************************************************************/
