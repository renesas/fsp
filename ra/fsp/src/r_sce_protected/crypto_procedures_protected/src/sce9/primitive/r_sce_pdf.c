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

fsp_err_t R_SCE_GenerateTlsRsaInstallDataSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_InstData)
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
    SCE->REG_84H = 0x0000df02U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
    SCE->REG_ECH = 0x38008c20U;
    SCE->REG_ECH = 0xfffffff0U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xce906ce4U, 0x83ba59cfU, 0xca39662fU, 0x5c42f1b4U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x76746755U, 0xde65f15bU, 0x73e65b7aU, 0x032d0e8fU);
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
        OFS_ADR = InData_SharedKeyIndex[0] << 3;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000dfU);
        R_SCE_func101(0x2f63a8f4U, 0x3d99d99cU, 0xb859edbcU, 0xff5b1c94U);
        R_SCE_func069(InData_SessionKey,OFS_ADR);
        R_SCE_func100(0xa34f1b37U, 0x9925e9c5U, 0x5dfbe2acU, 0x52a3b414U);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00040805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_IV[0];
        SCE->REG_100H = InData_IV[1];
        SCE->REG_100H = InData_IV[2];
        SCE->REG_100H = InData_IV[3];
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
        SCE->REG_100H = change_endian_long(0x000000dfU);
        R_SCE_func101(0x11f46329U, 0x602107baU, 0xcf516939U, 0xf19dda60U);
        R_SCE_func043();
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x01ba9fa3U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000dfU);
        R_SCE_func101(0x91b85fb1U, 0x43dd63a9U, 0x7fa550c3U, 0xb9f15e30U);
        R_SCE_func044();
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x01000001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000003U);
        R_SCE_func101(0xb7a04c94U, 0x1596c1c2U, 0x01dca8a4U, 0x7f142767U);
        R_SCE_func044();
        R_SCE_func100(0x7a0afabaU, 0x0998a5c3U, 0x8d594547U, 0xe55963b1U);
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000014U;
        SCE->REG_104H = 0x00003f61U;
        SCE->REG_B0H = 0x00000f00U;
        SCE->REG_A4H = 0x00d0c9a7U;
        for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[iLoop + 0];
            SCE->REG_100H = InData_InstData[iLoop + 1];
            SCE->REG_100H = InData_InstData[iLoop + 2];
            SCE->REG_100H = InData_InstData[iLoop + 3];
        }
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_D0H = 0x40000f00U;
        SCE->REG_C4H = 0x02e087b7U;
        SCE->REG_04H = 0x00000202U;
        for (jLoop = 0; jLoop < 64; jLoop = jLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_InstData[1+jLoop + 0] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 1] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 2] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 3] = SCE->REG_100H;
        }
        SCE->REG_24H = 0x000005c0U;
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
        SCE->REG_18H = 0x00000004U;
        SCE->REG_24H = 0x00005004U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00004804U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        R_SCE_func100(0x7d03abc9U, 0xe83e9888U, 0x0bca03e9U, 0x30a10901U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        SCE->REG_D0H = 0x40000f00U;
        SCE->REG_C4H = 0x00e087b7U;
        SCE->REG_04H = 0x00000202U;
        for (jLoop = 64; jLoop < 128; jLoop = jLoop + 4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_InstData[1+jLoop + 0] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 1] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 2] = SCE->REG_100H;
            OutData_InstData[1+jLoop + 3] = SCE->REG_100H;
        }
        R_SCE_func100(0x7f407a0eU, 0xd442e5acU, 0x5274b069U, 0x8b1faab1U);
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x00d049a5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[iLoop + 0];
        SCE->REG_100H = InData_InstData[iLoop + 1];
        SCE->REG_100H = InData_InstData[iLoop + 2];
        SCE->REG_100H = InData_InstData[iLoop + 3];
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x00e087b5U;
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
        OutData_InstData[1+jLoop + 0] = SCE->REG_100H;
        OutData_InstData[1+jLoop + 1] = SCE->REG_100H;
        OutData_InstData[1+jLoop + 2] = SCE->REG_100H;
        OutData_InstData[1+jLoop + 3] = SCE->REG_100H;
        R_SCE_func100(0xea03b026U, 0xea546fe6U, 0x42fa0dc1U, 0x322aaba7U);
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
        OutData_InstData[1+jLoop+4 + 0] = SCE->REG_100H;
        OutData_InstData[1+jLoop+4 + 1] = SCE->REG_100H;
        OutData_InstData[1+jLoop+4 + 2] = SCE->REG_100H;
        OutData_InstData[1+jLoop+4 + 3] = SCE->REG_100H;
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x000049a5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_InstData[68];
        SCE->REG_100H = InData_InstData[69];
        SCE->REG_100H = InData_InstData[70];
        SCE->REG_100H = InData_InstData[71];
        SCE->REG_A4H = 0x00900c45U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xd7483102U, 0xc30803feU, 0x56e1a9d2U, 0xd9b61a87U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x8ff3e735U, 0x3d0c9dccU, 0xfdb71852U, 0x4b2b2844U);
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
            R_SCE_func100(0x7b27b65aU, 0x1637db88U, 0x7f5fad37U, 0xd95a10cbU);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_InstData[0] = SCE->REG_100H;
            R_SCE_func102(0x12cb3374U, 0x16325920U, 0xb1786dafU, 0xcc806b30U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pdf_r2.prc
***********************************************************************************************************************/
