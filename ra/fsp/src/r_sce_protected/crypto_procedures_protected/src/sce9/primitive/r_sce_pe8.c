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

fsp_err_t R_SCE_TlsGeneratePreMasterSecretWithEccP256KeySub(uint32_t *InData_PubKey, uint32_t *InData_KeyIndex, uint32_t *OutData_PreMasterSecretIndex)
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
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000e802U;
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
    SCE->REG_ECH = 0x00310000U;
    SCE->REG_ECH = 0x1000d3c0U;
    SCE->REG_ECH = 0x3800d809U;
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
    R_SCE_func100(0x6a5be6afU, 0xe9848368U, 0x1261721aU, 0x69c9b933U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0xcfe2637dU, 0x810259acU, 0xe4c2366bU, 0xf3a016caU);
        SCE->REG_1B8H = 0x00000040U;
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
        SCE->REG_100H = change_endian_long(0x000000e8U);
        R_SCE_func101(0x34c6f8f7U, 0x1c7fabddU, 0x2250f267U, 0xdaba3fa4U);
        R_SCE_func059();
        SCE->REG_28H = 0x00870001U;
        SCE->REG_104H = 0x00000f62U;
        SCE->REG_D0H = 0x40000300U;
        SCE->REG_C4H = 0x02f087b7U;
        SCE->REG_ECH = 0x0000094aU;
        SCE->REG_E0H = 0x8090000aU;
        SCE->REG_00H = 0x00008243U;
        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
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
        SCE->REG_104H = 0x00000362U;
        SCE->REG_D0H = 0x40000000U;
        SCE->REG_C4H = 0x000087b5U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PubKey[20];
        SCE->REG_100H = InData_PubKey[21];
        SCE->REG_100H = InData_PubKey[22];
        SCE->REG_100H = InData_PubKey[23];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xb5c01937U, 0xc95dbe48U, 0x89adbacfU, 0x9ba25f38U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x3b1ac20eU, 0xd029df78U, 0x84f43b45U, 0xe9aef584U);
            SCE->REG_1B8H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x00000b9cU;
            OFS_ADR = 128;
            R_SCE_func100(0xca63ca7eU, 0x4aa0d63aU, 0xe0ee4007U, 0x0dce1a55U);
            R_SCE_func004_r1(OFS_ADR);
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
            SCE->REG_ECH = 0x00390000U;
            SCE->REG_ECH = 0x1000d3c0U;
            SCE->REG_ECH = 0x3800d809U;
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
            R_SCE_func100(0x861fd358U, 0xb58de811U, 0x5f769a8eU, 0x8ea1f294U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x38fc31abU, 0x43e00935U, 0xde48474bU, 0xbb3b1b60U);
                SCE->REG_1B8H = 0x00000040U;
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
                SCE->REG_100H = change_endian_long(0x00000054U);
                R_SCE_func101(0xd8880f8bU, 0x5332c748U, 0x1f4b6a6dU, 0x7b55fd7bU);
                R_SCE_func059();
                SCE->REG_28H = 0x00870001U;
                SCE->REG_104H = 0x00000762U;
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02f087b7U;
                SCE->REG_00H = 0x00003223U;
                SCE->REG_2CH = 0x00000011U;
                for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
                {
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_KeyIndex[iLoop+4 + 0];
                    SCE->REG_100H = InData_KeyIndex[iLoop+4 + 1];
                    SCE->REG_100H = InData_KeyIndex[iLoop+4 + 2];
                    SCE->REG_100H = InData_KeyIndex[iLoop+4 + 3];
                }
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
                R_SCE_func100(0x180acc23U, 0xf1e45c85U, 0x8270b290U, 0x5fb463ceU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0x42966309U, 0x13b63901U, 0x248b6ecfU, 0x0c10d785U);
                    SCE->REG_1B8H = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    R_SCE_func100(0xd2e59594U, 0xe1e0508fU, 0x83f00e28U, 0x312bf9adU);
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
                    SCE->REG_34H = 0x00000003U;
                    SCE->REG_24H = 0x8000e808U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000003U;
                    SCE->REG_24H = 0x800048d0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_ECH = 0x00000908U;
                    SCE->REG_E0H = 0x81880008U;
                    SCE->REG_00H = 0x00003823U;
                    SCE->REG_2CH = 0x00000010U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_24H = 0x0000880cU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000800U;
                    SCE->REG_24H = 0x800050d0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_ECH = 0x0000b500U;
                    SCE->REG_ECH = 0x00000020U;
                    SCE->REG_E0H = 0x81880008U;
                    SCE->REG_00H = 0x00003823U;
                    SCE->REG_2CH = 0x00000010U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_24H = 0x0000880cU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000800U;
                    SCE->REG_24H = 0x800070d0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00005cd0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
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
                    SCE->REG_18H = 0x00000004U;
                    SCE->REG_38H = 0x00001000U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_18H_b.B10)
                    {
                        /* waiting */
                    }
                    SCE->REG_18H = 0x00000000U;
                    SCE->REG_34H = 0x00000c00U;
                    SCE->REG_24H = 0x800094d0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
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
                    R_SCE_func100(0x5fa9c0d9U, 0x93041fd9U, 0x7872c82fU, 0x326c0ff5U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func102(0x6cc1b731U, 0x93072b72U, 0x68ec43e2U, 0x96a18e42U);
                        SCE->REG_1B8H = 0x00000040U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_18H_b.B12)
                        {
                            /* waiting */
                        }
                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        R_SCE_func100(0xf40a42c9U, 0x68e7c9f5U, 0xc53ad351U, 0x5b4771e3U);
                        SCE->REG_24H = 0x00009cd0U;
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
                        R_SCE_func100(0x49df7962U, 0xaf05c0dcU, 0x2f0b1ce7U, 0x1ab1dcceU);
                        SCE->REG_34H = 0x00000003U;
                        SCE->REG_24H = 0x800048d0U;
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
                        SCE->REG_100H = change_endian_long(0x00000055U);
                        R_SCE_func101(0x4056d95fU, 0xcbd8ee3bU, 0x46794c86U, 0x1f523346U);
                        R_SCE_func059();
                        SCE->REG_ECH = 0x0000b4e0U;
                        SCE->REG_ECH = 0x01c1817fU;
                        SCE->REG_104H = 0x00000058U;
                        SCE->REG_E0H = 0x800103a0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x000000e8U);
                        R_SCE_func101(0x0417e7e5U, 0x4a1627f6U, 0xf490085eU, 0xa5680662U);
                        R_SCE_func044();
                        R_SCE_func100(0xc6402425U, 0x42c0efffU, 0x0f4ec971U, 0xb3877abcU);
                        SCE->REG_D0H = 0x40000100U;
                        SCE->REG_C4H = 0x02e087b7U;
                        SCE->REG_00H = 0x00002323U;
                        SCE->REG_2CH = 0x00000022U;
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
                        OutData_PreMasterSecretIndex[4] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[5] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[6] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[7] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_PreMasterSecretIndex[8] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[9] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[10] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[11] = SCE->REG_100H;
                        R_SCE_func100(0x07eb6b17U, 0x0f67900aU, 0xf0d831c9U, 0x24aab76bU);
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
                        OutData_PreMasterSecretIndex[12] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[13] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[14] = SCE->REG_100H;
                        OutData_PreMasterSecretIndex[15] = SCE->REG_100H;
                        R_SCE_func100(0x4d2eed2dU, 0x78488de5U, 0xbc08c9efU, 0x75bad497U);
                        SCE->REG_E0H = 0x81040000U;
                        SCE->REG_04H = 0x00000612U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_PreMasterSecretIndex[0] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_PreMasterSecretIndex[1] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_PreMasterSecretIndex[2] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_PreMasterSecretIndex[3] = SCE->REG_100H;
                        R_SCE_func102(0xa8a57ce7U, 0xea9852c1U, 0xbe885f74U, 0x68a6295fU);
                        SCE->REG_1B8H = 0x00000040U;
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
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe8_r2.prc
***********************************************************************************************************************/
