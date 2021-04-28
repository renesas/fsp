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

fsp_err_t R_SCE_DlmsCosemQeuSignatureVerificationSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_data, uint32_t *InData_Signature, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00005a02U;
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
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_104H = 0x00000f68U;
    SCE->REG_E0H = 0x8090001eU;
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Signature[iLoop + 0];
    }
    SCE->REG_28H = 0x00870001U;
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
    SCE->REG_100H = change_endian_long(0x0000005aU);
    R_SCE_func101(0x52ba6846U, 0x632ad48dU, 0xf0a1ef74U, 0xcb233ce5U);
    R_SCE_func043();
    R_SCE_func023();
    SCE->REG_ECH = 0x000034feU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000005aU);
    R_SCE_func101(0xe822100cU, 0x9c7a7e7fU, 0x6a8a73aaU, 0xad48c94eU);
    R_SCE_func044();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_104H = 0x00000f62U;
    SCE->REG_D0H = 0x40000300U;
    SCE->REG_C4H = 0x02e08887U;
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
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[9];
    SCE->REG_100H = InData_KeyIndex[10];
    SCE->REG_100H = InData_KeyIndex[11];
    SCE->REG_100H = InData_KeyIndex[12];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[13];
    SCE->REG_100H = InData_KeyIndex[14];
    SCE->REG_100H = InData_KeyIndex[15];
    SCE->REG_100H = InData_KeyIndex[16];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000091U;
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
    SCE->REG_100H = InData_KeyIndex[17];
    SCE->REG_100H = InData_KeyIndex[18];
    SCE->REG_100H = InData_KeyIndex[19];
    SCE->REG_100H = InData_KeyIndex[20];
    SCE->REG_C4H = 0x00900c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x01e3d7efU, 0x3846a65cU, 0x10013f6eU, 0x4be4e5e6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x2a54b280U, 0xb447575eU, 0xb4463ffaU, 0x14f7cd4eU);
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
        R_SCE_func100(0x99beda16U, 0x24bc02a8U, 0x9f480062U, 0x80f3e1baU);
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
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000000c0U;
        SCE->REG_104H = 0x0000106cU;
        SCE->REG_E0H = 0x8091001eU;
        for (iLoop = 0; iLoop < 17; iLoop = iLoop + 1)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_data[iLoop + 0];
        }
        SCE->REG_104H = 0x00000e64U;
        for(iLoop = 17; iLoop < 32; iLoop = iLoop + 1)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_data[iLoop + 0];
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_74H_b.B18)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001600U;
        SCE->REG_74H = 0x00000000U;
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
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        OFS_ADR = S_RAM[0];
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0000005aU);
        R_SCE_func101(0xed687a0fU, 0x47030bdfU, 0xd0cfbf4fU, 0x0e6b4f87U);
        R_SCE_func010_r1(OFS_ADR);
        R_SCE_func100(0xe903ca1aU, 0xe289b369U, 0x0ec44677U, 0x884a646bU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xdf598a30U, 0xf59b0f74U, 0x0d7c57c1U, 0xef5b27d0U);
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
            SCE->REG_28H = 0x008f0001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000c0U;
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010340U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Cmd[0];
            SCE->REG_ECH = 0x38000f5aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0x2fe0c432U, 0xe3a94ae5U, 0xb6fad6e1U, 0xf37f2ef5U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_E0H = 0x8190001eU;
                SCE->REG_00H = 0x00003843U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0xd61f62e2U, 0x11b6ca6aU, 0x0a08ebbeU, 0x0a697ce6U);
            }
            else
            {
                SCE->REG_E0H = 0x8191001eU;
                SCE->REG_00H = 0x08000807U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x08013803U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0800080fU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0x78388171U, 0x9e4c2147U, 0xa626838bU, 0x8ef355c8U);
            }
            R_SCE_func100(0x40280ed0U, 0x61568988U, 0xa7716d91U, 0x5d40a21fU);
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
            SCE->REG_ECH = 0x00003540U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000005aU);
            R_SCE_func101(0x326c8453U, 0x7d6a8e30U, 0x79fdedc6U, 0x1c9688c2U);
            R_SCE_func068();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x75614788U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000021U);
            R_SCE_func101(0xf595fc97U, 0x193af4a0U, 0x5b882267U, 0xfeb3e8aeU);
            R_SCE_func044();
            R_SCE_func100(0x8054ff5eU, 0x871121f1U, 0x6f12550bU, 0x0aa03c8eU);
            SCE->REG_00H = 0x00002343U;
            SCE->REG_2CH = 0x00000020U;
            SCE->REG_D0H = 0x40000300U;
            SCE->REG_C4H = 0x02e087b7U;
            SCE->REG_04H = 0x00000242U;
            for (iLoop = 1; iLoop < 17; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
                OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
            }
            R_SCE_func100(0x010eaa89U, 0x74239963U, 0x25f56e98U, 0x55a79c54U);
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
            OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
            R_SCE_func100(0xe6269f98U, 0x78a7533dU, 0x32d4e62dU, 0x9eb17913U);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[0] = SCE->REG_100H;
            R_SCE_func102(0x2332a93dU, 0xcdc103a2U, 0xc3424ca2U, 0xae18bc76U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p5a_r2.prc
***********************************************************************************************************************/
