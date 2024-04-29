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

fsp_err_t HW_SCE_Sha256HmacInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t LEN)
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
    uint32_t InData_Cmd[1] = {0};
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
    (void)LEN;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00007602U;
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
    SCE->REG_7CH = 0x00000011U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x42507e18U, 0xb60252ceU, 0x59a423edU, 0x32e93062U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xc37eabffU, 0x387e2530U, 0xdddaf1e4U, 0xc598a37bU);
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
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x38008800U;
        SCE->REG_ECH = 0x00000002U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x7b47afd6U, 0x7d3fd654U, 0xd668f641U, 0x86ef5ef4U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000c00U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x21e049acU, 0xee0fef1cU, 0xa39aed15U, 0x10a4a162U);
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
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000076U);
                HW_SCE_p_func101(0x367adaa1U, 0x7284198dU, 0xbf2df312U, 0xe8ccb82dU);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0000001bU;
                HW_SCE_p_func101(0x16a9bc34U, 0xb50d353fU, 0x339765ffU, 0xf23ade49U);
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
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000076U);
                HW_SCE_p_func101(0x6428f417U, 0xce057e0dU, 0x9eb8d8caU, 0x8ecbc8e2U);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x01e3697fU;
                HW_SCE_p_func101(0xb0d1cfbaU, 0x1be9ec0fU, 0xfbe95721U, 0x3ff33801U);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000076U);
            HW_SCE_p_func101(0x85c3ea34U, 0x0e0d6a2aU, 0x535039d6U, 0x637735f0U);
            HW_SCE_p_func044();
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x40000100U;
            SCE->REG_C4H = 0x02f087b7U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            SCE->REG_100H = InData_KeyIndex[2];
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_100H = InData_KeyIndex[4];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_E0H = 0x80080000U;
            SCE->REG_00H = 0x00008223U;
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
            SCE->REG_ECH = 0x0000b760U;
            SCE->REG_ECH = 0x00003000U;
            HW_SCE_p_func101(0x2deea867U, 0xb7d5bae0U, 0x3157a392U, 0x9b767470U);
        }
        else
        {
            SCE->REG_ECH = 0x38008800U;
            SCE->REG_ECH = 0x00000001U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xf9416e2fU, 0x86f70075U, 0x5e5d5510U, 0x5f6eddcfU);
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
                SCE->REG_ECH = 0x00020000U;
                SCE->REG_ECH = 0x1000d3c0U;
                SCE->REG_ECH = 0x000037e0U;
                SCE->REG_ECH = 0x38008fe0U;
                SCE->REG_ECH = 0x00003000U;
                SCE->REG_ECH = 0x2000d3c1U;
                SCE->REG_ECH = 0x00003760U;
                SCE->REG_ECH = 0x00008f60U;
                SCE->REG_ECH = 0x00003000U;
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
                SCE->REG_100H = change_endian_long(0x00000076U);
                HW_SCE_p_func101(0xa21aea54U, 0x1230205eU, 0x72365073U, 0xe9fd7131U);
                HW_SCE_p_func059();
                SCE->REG_104H = 0x00000762U;
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02f087b7U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[4];
                SCE->REG_100H = InData_KeyIndex[5];
                SCE->REG_100H = InData_KeyIndex[6];
                SCE->REG_100H = InData_KeyIndex[7];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[8];
                SCE->REG_100H = InData_KeyIndex[9];
                SCE->REG_100H = InData_KeyIndex[10];
                SCE->REG_100H = InData_KeyIndex[11];
                SCE->REG_E0H = 0x80080000U;
                SCE->REG_00H = 0x00008223U;
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
                HW_SCE_p_func101(0x0f08784aU, 0x6264fe2eU, 0x436ab374U, 0xbbca3172U);
            }
            else
            {
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x80010000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Cmd[0];
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x80010280U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                SCE->REG_ECH = 0x00003554U;
                SCE->REG_ECH = 0x000036a0U;
                SCE->REG_ECH = 0x0000b6c0U;
                SCE->REG_ECH = 0x01249674U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000076U);
                HW_SCE_p_func101(0x87ab1ca1U, 0xbcd597d8U, 0x2111f755U, 0x6521a6caU);
                HW_SCE_p_func082();
                SCE->REG_ECH = 0x0000b760U;
                SCE->REG_ECH = 0x00003000U;
                SCE->REG_104H = 0x00000762U;
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02f087b7U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[1];
                SCE->REG_100H = InData_KeyIndex[2];
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_100H = InData_KeyIndex[4];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[5];
                SCE->REG_100H = InData_KeyIndex[6];
                SCE->REG_100H = InData_KeyIndex[7];
                SCE->REG_100H = InData_KeyIndex[8];
                SCE->REG_E0H = 0x80080000U;
                SCE->REG_00H = 0x00008223U;
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
                HW_SCE_p_func101(0xe19400bcU, 0x1a449204U, 0xded3fd25U, 0x97e68e25U);
            }
            HW_SCE_p_func101(0x1173e310U, 0xd26794b2U, 0x3a238f9bU, 0x670a16daU);
        }
        HW_SCE_p_func100(0x063a8108U, 0x8c07b7a6U, 0x7e2e826fU, 0xe2a527e9U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x618eda6cU, 0xd48d8015U, 0xaa3ad2fbU, 0xb0d44b36U);
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
            SCE->REG_7CH = 0x00000011U;
            SCE->REG_104H = 0x00000754U;
            SCE->REG_74H = 0x00000004U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x6a09e667U);
            SCE->REG_100H = change_endian_long(0xbb67ae85U);
            SCE->REG_100H = change_endian_long(0x3c6ef372U);
            SCE->REG_100H = change_endian_long(0xa54ff53aU);
            SCE->REG_100H = change_endian_long(0x510e527fU);
            SCE->REG_100H = change_endian_long(0x9b05688cU);
            SCE->REG_100H = change_endian_long(0x1f83d9abU);
            SCE->REG_100H = change_endian_long(0x5be0cd19U);
            SCE->REG_74H = 0x00000002U;
            HW_SCE_p_func001();
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p76i_r4.prc
***********************************************************************************************************************/
