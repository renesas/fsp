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

fsp_err_t R_SCE_DlmsCosemCalculateKekSub(uint32_t *InData_KeyIndexType, uint32_t *InData_KeyIndex, uint32_t *InData_KDFType, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT, uint32_t *InData_SaltKeyIndex, uint32_t *OutData_KeyIndex)
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
    SCE->REG_28H = 0x00870001U;
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
    R_SCE_func101(0x7d1addb3U, 0x2057f3b8U, 0x9160b333U, 0x2551ed24U);
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
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000012U;
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
    R_SCE_func100(0x6ad1012fU, 0xd55e33d6U, 0x84da10daU, 0x6f52e33bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x2eedcee1U, 0xfc1251bdU, 0xc75fa57eU, 0xcd14f0f9U);
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
        SCE->REG_104H = 0x00000168U;
        SCE->REG_E0H = 0x80020200U;
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
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x800103e0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KDFType[0];
        SCE->REG_ECH = 0x00000b9cU;
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
        SCE->REG_ECH = 0x38000fffU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0x49ad495aU, 0x8c87d651U, 0x3d56988eU, 0xf5decbf6U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000054U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001U);
            SCE->REG_00H = 0x00005323U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_E0H = 0x81020200U;
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
            R_SCE_func101(0xed4f005cU, 0x4bd8b063U, 0xbc8a39e2U, 0xe4972507U);
        }
        else
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SaltKeyIndex[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000005dU);
            R_SCE_func101(0x899496f9U, 0xe196ae97U, 0xc89579d4U, 0xff2042aeU);
            R_SCE_func043();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x0000001bU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000005dU);
            R_SCE_func101(0xd3b63ebaU, 0xdf40eb06U, 0x5ccf9b8eU, 0x18586887U);
            R_SCE_func044();
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x40000100U;
            SCE->REG_C4H = 0x02f087b7U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SaltKeyIndex[1];
            SCE->REG_100H = InData_SaltKeyIndex[2];
            SCE->REG_100H = InData_SaltKeyIndex[3];
            SCE->REG_100H = InData_SaltKeyIndex[4];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_SaltKeyIndex[5];
            SCE->REG_100H = InData_SaltKeyIndex[6];
            SCE->REG_100H = InData_SaltKeyIndex[7];
            SCE->REG_100H = InData_SaltKeyIndex[8];
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
            SCE->REG_100H = InData_SaltKeyIndex[9];
            SCE->REG_100H = InData_SaltKeyIndex[10];
            SCE->REG_100H = InData_SaltKeyIndex[11];
            SCE->REG_100H = InData_SaltKeyIndex[12];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0x0bd04d21U, 0xf801c559U, 0x95c29e91U, 0x8eb78d6aU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000b780U;
                SCE->REG_ECH = 0x00000001U;
                R_SCE_func101(0x95c00417U, 0x3e17da91U, 0xd4e707f5U, 0x507b8334U);
            }
            else
            {
                R_SCE_func001();
                SCE->REG_104H = 0x00000054U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001U);
                SCE->REG_00H = 0x00005323U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_E0H = 0x81020200U;
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
                SCE->REG_00H = 0x00003523U;
                SCE->REG_74H = 0x00000008U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
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
                R_SCE_func002();
                SCE->REG_00H = 0x00005323U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000054U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x80000000U);
                SCE->REG_F8H = 0x00000040U;
                SCE->REG_104H = 0x00000154U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_100H = change_endian_long(0x00000300U);
                /* WAIT_LOOP */
                while (0U != SCE->REG_74H_b.B18)
                {
                    /* waiting */
                }
                SCE->REG_74H = 0x00000000U;
                SCE->REG_1CH = 0x00001600U;
                R_SCE_func101(0xf99572cfU, 0x5ac43682U, 0x4fb9fccbU, 0xf028997eU);
            }
        }
        SCE->REG_ECH = 0x38000f9cU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0x3816cfa4U, 0xa6fa0faaU, 0xb5459fbbU, 0x282936b1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xb936bc32U, 0xb65915bbU, 0xc45b6d2eU, 0xe7498928U);
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
            R_SCE_func100(0x2b2e99dcU, 0xe776097bU, 0x5180886eU, 0xb5312f2eU);
            R_SCE_func103();
            R_SCE_func100(0x86aa76c1U, 0x6271b792U, 0x5a03d80aU, 0x224c3c70U);
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
            R_SCE_func101(0xc3cbb51cU, 0x2f7aa6e5U, 0xbac139a2U, 0x6ebb4cdeU);
            R_SCE_func068();
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800103c0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndexType[0];
            SCE->REG_ECH = 0x300033c0U;
            SCE->REG_ECH = 0x00070020U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x2a46c04bU;
            SCE->REG_ECH = 0x00030040U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x85d04999U;
            SCE->REG_ECH = 0x00050040U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0xb6e3697fU;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000081U);
            R_SCE_func101(0x44ad26bbU, 0xaeaa3cc3U, 0xbf6bb0c7U, 0xf7b67c23U);
            R_SCE_func044();
            SCE->REG_ECH = 0x38000fdeU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0xd8ec021fU, 0x769b4c9eU, 0xb86cdc9aU, 0xc7568ab6U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func100(0x52aeefd3U, 0xa30f9bcbU, 0xb9a2815cU, 0x2a23b288U);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02e087b5U;
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
                R_SCE_func101(0x17d49992U, 0x1526ab6bU, 0x5b5abaefU, 0x512ad050U);
            }
            else
            {
                R_SCE_func100(0x3fdf81c7U, 0x9c20822fU, 0x0e12f06cU, 0xe0ea9f9bU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002523U;
                SCE->REG_74H = 0x00000008U;
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
                SCE->REG_100H = change_endian_long(0x00000002U);
                SCE->REG_04H = 0x00000232U;
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
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[9] = SCE->REG_100H;
                OutData_KeyIndex[10] = SCE->REG_100H;
                OutData_KeyIndex[11] = SCE->REG_100H;
                OutData_KeyIndex[12] = SCE->REG_100H;
                R_SCE_func101(0xf9aa64d8U, 0xa956b871U, 0x2f54cc87U, 0xa9a69c72U);
            }
            R_SCE_func102(0x4cf439b5U, 0x4daa3831U, 0x93e896fcU, 0x85fd331eU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p5d_r2.prc
***********************************************************************************************************************/
