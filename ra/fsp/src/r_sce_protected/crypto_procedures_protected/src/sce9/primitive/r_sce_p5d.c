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

fsp_err_t R_SCE_DlmsCosemCalculateKekSub(uint32_t *InData_KeyIndex, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT, uint32_t *OutData_KeyIndex)
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
    if (0x0U != (SCE->REG_1B4H & 0x1dU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00005d02U;
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
    SCE->REG_100H = change_endian_long(0x0000005dU);
    R_SCE_func101(0xa8c9b1ecU, 0x1710ded0U, 0x05891522U, 0x1ef9aa58U);
    R_SCE_func068();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x718cf94fU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000005dU);
    R_SCE_func101(0xe9851c96U, 0x1fd63f1eU, 0xfac6a708U, 0x3312765bU);
    R_SCE_func044();
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
    SCE->REG_B0H = 0x00000100U;
    SCE->REG_A4H = 0x00008887U;
    SCE->REG_00H = 0x00001223U;
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
    R_SCE_func100(0x144701ebU, 0x19aaddacU, 0xd3c36f14U, 0x3c8b62c9U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_00H = 0x00000123U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func102(0xfa53a9cfU, 0x65cf25beU, 0xc00a1622U, 0x16dd8d13U);
        SCE->REG_1B4H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000168U;
        SCE->REG_E0H = 0x80020080U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PaddedMsg[0];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PaddedMsg[1];
        SCE->REG_ECH = 0x38008880U;
        SCE->REG_ECH = 0x60857405U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        SCE->REG_ECH = 0x000037e5U;
        SCE->REG_ECH = 0x00008fe0U;
        SCE->REG_ECH = 0xfffffd00U;
        SCE->REG_ECH = 0x38008be0U;
        SCE->REG_ECH = 0x08030000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0x56c1ab3dU, 0x1e8ceac9U, 0x51fc6aefU, 0x8ff2c3bdU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_00H = 0x00000123U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func102(0x116d214cU, 0x1cd6d66bU, 0x19b607b3U, 0xd95c3049U);
            SCE->REG_1B4H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            R_SCE_func100(0x94781957U, 0x061b55c3U, 0x3ceb9447U, 0x2947a4e2U);
            SCE->REG_7CH = 0x00000011U;
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
            SCE->REG_104H = 0x00000054U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001U);
            SCE->REG_00H = 0x00005123U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_E0H = 0x81020080U;
            SCE->REG_00H = 0x0000580bU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000464U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_PaddedMsg[2];
            SCE->REG_100H = InData_PaddedMsg[3];
            SCE->REG_100H = InData_PaddedMsg[4];
            SCE->REG_100H = InData_PaddedMsg[5];
            SCE->REG_100H = InData_PaddedMsg[6];
            /* WAIT_LOOP */
            while (0U != SCE->REG_74H_b.B18)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001600U;
            SCE->REG_104H = 0x000000b4U;
            for (iLoop = 7; iLoop < MAX_CNT-7; iLoop = iLoop+16)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PaddedMsg[iLoop + 0];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 1];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 2];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 3];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 4];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 5];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 6];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 7];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 8];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 9];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 10];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 11];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 12];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 13];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 14];
                SCE->REG_100H = InData_PaddedMsg[iLoop + 15];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_74H_b.B18)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001600U;
            SCE->REG_74H = 0x00000000U;
            SCE->REG_104H = 0x00000000U;
            R_SCE_func103();
            R_SCE_func100(0x36a0a632U, 0x451b1cb1U, 0x87c86bfdU, 0xeeda6301U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_E0H = 0x80010140U;
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
            SCE->REG_E0H = 0x81010140U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[0] = SCE->REG_100H;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000081U);
            R_SCE_func101(0xfff9ab95U, 0xe02c3d70U, 0x8e2c1e11U, 0x4c2fb700U);
            R_SCE_func068();
            SCE->REG_ECH = 0x00008ca0U;
            SCE->REG_ECH = 0xffffff00U;
            SCE->REG_ECH = 0x380088a0U;
            SCE->REG_ECH = 0x08030000U;
            SCE->REG_ECH = 0x1000b7c0U;
            SCE->REG_ECH = 0x2a46c04bU;
            SCE->REG_ECH = 0x380088a0U;
            SCE->REG_ECH = 0x08030200U;
            SCE->REG_ECH = 0x1000b7c0U;
            SCE->REG_ECH = 0xed7e5426U;
            SCE->REG_ECH = 0x000034feU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000081U);
            R_SCE_func101(0xeb767e90U, 0x7d3ac8a9U, 0x79c701beU, 0x96073706U);
            R_SCE_func044();
            R_SCE_func100(0x80cc6f62U, 0x7cfb3c97U, 0x01d6aa9bU, 0x20dfd3a0U);
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02e487b5U;
            SCE->REG_00H = 0x00002513U;
            SCE->REG_74H = 0x00000008U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00000513U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000352U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000089c5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000001U);
            SCE->REG_04H = 0x00000222U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[1] = SCE->REG_100H;
            OutData_KeyIndex[2] = SCE->REG_100H;
            OutData_KeyIndex[3] = SCE->REG_100H;
            OutData_KeyIndex[4] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[5] = SCE->REG_100H;
            OutData_KeyIndex[6] = SCE->REG_100H;
            OutData_KeyIndex[7] = SCE->REG_100H;
            OutData_KeyIndex[8] = SCE->REG_100H;
            R_SCE_func102(0x00dbb8a6U, 0x2feccd8eU, 0xb5eb0e47U, 0xd97efe81U);
            SCE->REG_1B4H = 0x00000040U;
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p5d_r1.prc
***********************************************************************************************************************/
