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

fsp_err_t R_SCE_TlsEncryptPreMasterSecretSub(uint32_t *InData_PubKey, uint32_t *InData_PreMasterSecret, uint32_t *OutData_PreMasterSecret)
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
    SCE->REG_84H = 0x0000e202U;
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
    SCE->REG_104H = 0x00000368U;
    SCE->REG_E0H = 0x80040000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[1];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[2];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[3];
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x000037e0U;
    SCE->REG_ECH = 0x00008fe0U;
    SCE->REG_ECH = 0x00ff0000U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00050000U;
    SCE->REG_ECH = 0x1000d3c0U;
    SCE->REG_ECH = 0x3800d80fU;
    SCE->REG_ECH = 0x2000d3c1U;
    SCE->REG_ECH = 0x000037e0U;
    SCE->REG_ECH = 0x00008fe0U;
    SCE->REG_ECH = 0x000000ffU;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_ECH = 0x1000d3c2U;
    SCE->REG_ECH = 0x38008bc0U;
    SCE->REG_ECH = 0x00000007U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x005628bdU, 0x8a27a8d0U, 0x905e1fc2U, 0x76697d45U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x2c161f67U, 0x2447ead2U, 0x547bb529U, 0x5688a5eeU);
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
        SCE->REG_104H = 0x00000368U;
        SCE->REG_E0H = 0x80040140U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[0];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[1];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[2];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[3];
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e2U);
        R_SCE_func101(0x98596d75U, 0x5189c6e8U, 0xa41d4275U, 0x92fa3206U);
        R_SCE_func059();
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0154569cU;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e2U);
        R_SCE_func101(0xef911932U, 0x2487de81U, 0xd0dc90d1U, 0xbe5963daU);
        R_SCE_func044();
        SCE->REG_104H = 0x00000b62U;
        SCE->REG_D0H = 0x40000200U;
        SCE->REG_C4H = 0x02f087b7U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[4];
        SCE->REG_100H = InData_PreMasterSecret[5];
        SCE->REG_100H = InData_PreMasterSecret[6];
        SCE->REG_100H = InData_PreMasterSecret[7];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[8];
        SCE->REG_100H = InData_PreMasterSecret[9];
        SCE->REG_100H = InData_PreMasterSecret[10];
        SCE->REG_100H = InData_PreMasterSecret[11];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[12];
        SCE->REG_100H = InData_PreMasterSecret[13];
        SCE->REG_100H = InData_PreMasterSecret[14];
        SCE->REG_100H = InData_PreMasterSecret[15];
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x00000070U;
        SCE->REG_E0H = 0x808c0004U;
        SCE->REG_00H = 0x00008233U;
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
        SCE->REG_100H = InData_PreMasterSecret[16];
        SCE->REG_100H = InData_PreMasterSecret[17];
        SCE->REG_100H = InData_PreMasterSecret[18];
        SCE->REG_100H = InData_PreMasterSecret[19];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x4dc8a4d7U, 0xdb76879eU, 0xb551ef4aU, 0x8e1f272eU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x68a2f4e0U, 0x579ea402U, 0x54645b27U, 0x47a7be32U);
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
            SCE->REG_100H = change_endian_long(0x00000033U);
            R_SCE_func101(0x3b251d0aU, 0xfa0f3fc1U, 0xca291eb5U, 0xbce85ebbU);
            R_SCE_func059();
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func100(0xa1920ec8U, 0xd98054ceU, 0x30ffcea1U, 0x02225004U);
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
            SCE->REG_ECH = 0x00008c00U;
            SCE->REG_ECH = 0x0000ffffU;
            SCE->REG_ECH = 0x00009000U;
            SCE->REG_ECH = 0x00028080U;
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_00H = 0x00003807U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b480U;
            SCE->REG_ECH = 0x01020408U;
            SCE->REG_ECH = 0x0000b4a0U;
            SCE->REG_ECH = 0x10204080U;
            SCE->REG_ECH = 0x0000b4c0U;
            SCE->REG_ECH = 0x80200802U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x40100401U;
            SCE->REG_ECH = 0x00000bdeU;
            for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
            {
                R_SCE_func100(0x5bd4d0fdU, 0xae6b3e6bU, 0xb8181053U, 0x0fd28120U);
                R_SCE_func103();
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
                SCE->REG_ECH = 0x00001004U;
                SCE->REG_ECH = 0x00001025U;
                SCE->REG_ECH = 0x00001046U;
                SCE->REG_ECH = 0x00001067U;
                SCE->REG_E0H = 0x81040000U;
                SCE->REG_00H = 0x00003813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x00002fc0U;
                R_SCE_func101(0xc0a8f0c1U, 0xc42d345aU, 0xc8c657a1U, 0xba5cf61fU);
            }
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x0000000CU;
            SCE->REG_ECH = 0x38000bdfU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_1CH = 0x00402000U;
            R_SCE_func100(0x39eeb6a8U, 0xdcf76541U, 0x917b2452U, 0xd3b48a54U);
            R_SCE_func103();
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_E0H = 0x80030000U;
            SCE->REG_00H = 0x0000820fU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00000207U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00001004U;
            SCE->REG_ECH = 0x00001025U;
            SCE->REG_ECH = 0x00001046U;
            SCE->REG_E0H = 0x80010140U;
            SCE->REG_104H = 0x00000058U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xffffff00U);
            SCE->REG_ECH = 0x00000c4aU;
            SCE->REG_E0H = 0x81030000U;
            SCE->REG_00H = 0x0000380fU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x818c0001U;
            SCE->REG_00H = 0x00003833U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00008362U;
            SCE->REG_D0H = 0x40001f00U;
            SCE->REG_C4H = 0x02f087b7U;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000014U;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+4 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+68 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x00f087b5U;
            for (iLoop = 0; iLoop < 4; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+132 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 3];
            }
            SCE->REG_E0H = 0x800100a0U;
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
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_PubKey[136];
            SCE->REG_100H = InData_PubKey[137];
            SCE->REG_100H = InData_PubKey[138];
            SCE->REG_100H = InData_PubKey[139];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0xb629d2c3U, 0xd93838caU, 0xe271a7d0U, 0x32a2cd0dU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x760bc72bU, 0x4ee8cb9bU, 0x18714374U, 0x12001ccdU);
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
                R_SCE_func100(0x691066faU, 0x21763fa7U, 0xfcff045bU, 0x9cd65631U);
                SCE->REG_18H = 0x00000004U;
                SCE->REG_34H = 0x00000000U;
                SCE->REG_38H = 0x00000338U;
                SCE->REG_E0H = 0x810100a0U;
                SCE->REG_00H = 0x00003807U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B10)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000000U;
                SCE->REG_28H = 0x00bf0001U;
                R_SCE_func100(0x79834932U, 0xb044a0deU, 0x4b1ad868U, 0xf0dd49e6U);
                SCE->REG_2CH = 0x00000020U;
                SCE->REG_04H = 0x00000302U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PreMasterSecret[0] = SCE->REG_100H;
                OutData_PreMasterSecret[1] = SCE->REG_100H;
                OutData_PreMasterSecret[2] = SCE->REG_100H;
                OutData_PreMasterSecret[3] = SCE->REG_100H;
                OutData_PreMasterSecret[4] = SCE->REG_100H;
                OutData_PreMasterSecret[5] = SCE->REG_100H;
                OutData_PreMasterSecret[6] = SCE->REG_100H;
                OutData_PreMasterSecret[7] = SCE->REG_100H;
                OutData_PreMasterSecret[8] = SCE->REG_100H;
                OutData_PreMasterSecret[9] = SCE->REG_100H;
                OutData_PreMasterSecret[10] = SCE->REG_100H;
                OutData_PreMasterSecret[11] = SCE->REG_100H;
                OutData_PreMasterSecret[12] = SCE->REG_100H;
                OutData_PreMasterSecret[13] = SCE->REG_100H;
                OutData_PreMasterSecret[14] = SCE->REG_100H;
                OutData_PreMasterSecret[15] = SCE->REG_100H;
                OutData_PreMasterSecret[16] = SCE->REG_100H;
                OutData_PreMasterSecret[17] = SCE->REG_100H;
                OutData_PreMasterSecret[18] = SCE->REG_100H;
                OutData_PreMasterSecret[19] = SCE->REG_100H;
                OutData_PreMasterSecret[20] = SCE->REG_100H;
                OutData_PreMasterSecret[21] = SCE->REG_100H;
                OutData_PreMasterSecret[22] = SCE->REG_100H;
                OutData_PreMasterSecret[23] = SCE->REG_100H;
                OutData_PreMasterSecret[24] = SCE->REG_100H;
                OutData_PreMasterSecret[25] = SCE->REG_100H;
                OutData_PreMasterSecret[26] = SCE->REG_100H;
                OutData_PreMasterSecret[27] = SCE->REG_100H;
                OutData_PreMasterSecret[28] = SCE->REG_100H;
                OutData_PreMasterSecret[29] = SCE->REG_100H;
                OutData_PreMasterSecret[30] = SCE->REG_100H;
                OutData_PreMasterSecret[31] = SCE->REG_100H;
                OutData_PreMasterSecret[32] = SCE->REG_100H;
                OutData_PreMasterSecret[33] = SCE->REG_100H;
                OutData_PreMasterSecret[34] = SCE->REG_100H;
                OutData_PreMasterSecret[35] = SCE->REG_100H;
                OutData_PreMasterSecret[36] = SCE->REG_100H;
                OutData_PreMasterSecret[37] = SCE->REG_100H;
                OutData_PreMasterSecret[38] = SCE->REG_100H;
                OutData_PreMasterSecret[39] = SCE->REG_100H;
                OutData_PreMasterSecret[40] = SCE->REG_100H;
                OutData_PreMasterSecret[41] = SCE->REG_100H;
                OutData_PreMasterSecret[42] = SCE->REG_100H;
                OutData_PreMasterSecret[43] = SCE->REG_100H;
                OutData_PreMasterSecret[44] = SCE->REG_100H;
                OutData_PreMasterSecret[45] = SCE->REG_100H;
                OutData_PreMasterSecret[46] = SCE->REG_100H;
                OutData_PreMasterSecret[47] = SCE->REG_100H;
                OutData_PreMasterSecret[48] = SCE->REG_100H;
                OutData_PreMasterSecret[49] = SCE->REG_100H;
                OutData_PreMasterSecret[50] = SCE->REG_100H;
                OutData_PreMasterSecret[51] = SCE->REG_100H;
                OutData_PreMasterSecret[52] = SCE->REG_100H;
                OutData_PreMasterSecret[53] = SCE->REG_100H;
                OutData_PreMasterSecret[54] = SCE->REG_100H;
                OutData_PreMasterSecret[55] = SCE->REG_100H;
                OutData_PreMasterSecret[56] = SCE->REG_100H;
                OutData_PreMasterSecret[57] = SCE->REG_100H;
                OutData_PreMasterSecret[58] = SCE->REG_100H;
                OutData_PreMasterSecret[59] = SCE->REG_100H;
                OutData_PreMasterSecret[60] = SCE->REG_100H;
                OutData_PreMasterSecret[61] = SCE->REG_100H;
                OutData_PreMasterSecret[62] = SCE->REG_100H;
                OutData_PreMasterSecret[63] = SCE->REG_100H;
                R_SCE_func102(0xfaa4f63bU, 0x63cfd0deU, 0x3d38e146U, 0x063a5a44U);
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
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe2_r1.prc
***********************************************************************************************************************/
