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

fsp_err_t R_SCE_TlsCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType, uint32_t *InData_PubKey, uint32_t *InData_TBSCertificate, uint32_t *InData_TBSCertificateLength, uint32_t *InData_Signature, uint32_t *InData_TBSCertificateInfo, uint32_t length, uint32_t *OutData_PubKey)
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
    (void)length;
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000e102U;
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
    R_SCE_func100(0xef052e03U, 0x240fa96cU, 0xc54ba1d1U, 0xa3fe0d51U);
    R_SCE_func103();
    R_SCE_func100(0xbf513907U, 0x8fc5768dU, 0xeeab50f9U, 0x918bc84cU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01090c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800101e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Sel_PubKeyType[0];
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x38000defU;
    SCE->REG_ECH = 0x1000d3e0U;
    SCE->REG_ECH = 0x380089e0U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x38000fffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    R_SCE_func100(0xa27f8bbbU, 0xa1919d58U, 0x513a62c9U, 0xc008ee36U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x01ded869U, 0x6aa5a125U, 0x26b16d94U, 0x4a9c1befU);
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
        R_SCE_func100(0xd6bc5519U, 0x6f508f1eU, 0xeb578458U, 0x945087f6U);
        SCE->REG_104H = 0x00000468U;
        SCE->REG_E0H = 0x800502c0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TBSCertificateLength[0];
        for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_TBSCertificateInfo[iLoop + 0];
        }
        SCE->REG_ECH = 0x00007c0fU;
        SCE->REG_1CH = 0x00600000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_ECH = 0x3c002af8U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3c002b19U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3c002b59U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x3c002b56U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x00003417U;
            SCE->REG_ECH = 0x0000a400U;
            SCE->REG_ECH = 0x000000ffU;
            SCE->REG_ECH = 0x08002818U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x00003419U;
            SCE->REG_ECH = 0x0000a400U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_ECH = 0x0c00281aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            R_SCE_func101(0x90cc7471U, 0x6152a3dcU, 0xa01a9648U, 0xb3dc31cdU);
        }
        else
        {
            SCE->REG_ECH = 0x3c002af8U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3c002b19U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3c002b3aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3c002b56U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x00003417U;
            SCE->REG_ECH = 0x0000a400U;
            SCE->REG_ECH = 0x0000001fU;
            SCE->REG_ECH = 0x08002818U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x00003419U;
            SCE->REG_ECH = 0x0000a400U;
            SCE->REG_ECH = 0x0000001fU;
            SCE->REG_ECH = 0x0800281aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            R_SCE_func101(0x03fd5729U, 0x124feb7eU, 0x484a0c88U, 0x88e1fb74U);
        }
        R_SCE_func100(0xd50ea903U, 0xdc3a4088U, 0xd18d8cffU, 0xdc96b385U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xfc9660beU, 0x2810541bU, 0x39a11812U, 0xe1542928U);
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
            SCE->REG_ECH = 0x10000a31U;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00310000U;
            SCE->REG_ECH = 0x1000d3c0U;
            SCE->REG_ECH = 0x1000b620U;
            SCE->REG_ECH = 0x00000002U;
            SCE->REG_ECH = 0x3800d80bU;
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
            R_SCE_func100(0x88a74c91U, 0x315e3786U, 0x60a03d05U, 0xc1058e89U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x948f2158U, 0x32cc45cfU, 0x7d3a2378U, 0x7e7acc5fU);
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
                SCE->REG_100H = change_endian_long(0x000000e1U);
                R_SCE_func101(0x6f8645f8U, 0x0ca19a85U, 0x5cf217b4U, 0x6e65a90dU);
                R_SCE_func059();
                R_SCE_func100(0x3da99d57U, 0xaab13e6fU, 0x44edf808U, 0x5f5ca63dU);
                SCE->REG_ECH = 0x00007c11U;
                SCE->REG_1CH = 0x00600000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                {
                    SCE->REG_28H = 0x00bf0001U;
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
                    R_SCE_func101(0xb3886ce3U, 0x517400a5U, 0x55fe4528U, 0xdb07c918U);
                }
                else
                {
                    SCE->REG_28H = 0x00870001U;
                    SCE->REG_104H = 0x00000f62U;
                    SCE->REG_D0H = 0x40000300U;
                    SCE->REG_C4H = 0x02f087b7U;
                    SCE->REG_00H = 0x00003223U;
                    SCE->REG_2CH = 0x0000009bU;
                    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
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
                    SCE->REG_00H = 0x00003223U;
                    SCE->REG_2CH = 0x00000012U;
                    for (iLoop = 8; iLoop < 16; iLoop = iLoop + 4)
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
                    R_SCE_func101(0x7514f548U, 0x17192abeU, 0x2901bb8bU, 0x629e6a2aU);
                }
                R_SCE_func100(0xd685dcf6U, 0xd06f2b31U, 0x67b4aff4U, 0xea1fdab0U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0x7f4c0e01U, 0xa0c58818U, 0x3e7f7c75U, 0x966b7571U);
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
                    R_SCE_func100(0xa3daa30eU, 0x49300241U, 0xfc9f537fU, 0x69c2b99fU);
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
                    SCE->REG_ECH = 0x00003417U;
                    SCE->REG_ECH = 0x00046800U;
                    SCE->REG_ECH = 0x00026c00U;
                    SCE->REG_E0H = 0x81010000U;
                    SCE->REG_04H = 0x00000707U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    S_RAM[0] = change_endian_long(SCE->REG_100H);
                    SCE->REG_ECH = 0x000008a5U;
                    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 4)
                    {
                        SCE->REG_104H = 0x00000364U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = InData_TBSCertificate[iLoop + 0];
                        SCE->REG_100H = InData_TBSCertificate[iLoop + 1];
                        SCE->REG_100H = InData_TBSCertificate[iLoop + 2];
                        SCE->REG_100H = InData_TBSCertificate[iLoop + 3];
                        SCE->REG_ECH = 0x0000a4a0U;
                        SCE->REG_ECH = 0x00000004U;
                        R_SCE_func101(0x027ff99cU, 0xfafccfe6U, 0xd3963506U, 0x1bd74cf4U);
                    }
                    R_SCE_func100(0xcc802844U, 0x52852bfeU, 0x78931bb3U, 0x99121dc0U);
                    SCE->REG_ECH = 0x38000805U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    SCE->REG_1CH = 0x00402000U;
                    SCE->REG_ECH = 0x00007c0fU;
                    SCE->REG_1CH = 0x00600000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                    {
                        R_SCE_func100(0x5ca379d6U, 0x0e2d51bfU, 0x4116161bU, 0xb8aea971U);
                        SCE->REG_28H = 0x00bf0001U;
                        SCE->REG_2CH = 0x00000010U;
                        SCE->REG_ECH = 0x00003416U;
                        SCE->REG_ECH = 0x00026800U;
                        SCE->REG_ECH = 0x38008ec0U;
                        SCE->REG_ECH = 0x00000003U;
                        SCE->REG_ECH = 0x20002c00U;
                        SCE->REG_E0H = 0x81010000U;
                        SCE->REG_04H = 0x00000707U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        S_RAM[0] = change_endian_long(SCE->REG_100H);
                        SCE->REG_ECH = 0x00003445U;
                        SCE->REG_ECH = 0x00026c42U;
                        SCE->REG_ECH = 0x000034d6U;
                        SCE->REG_ECH = 0x000030c0U;
                        SCE->REG_ECH = 0x00000a10U;
                        for (; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                        {
                            SCE->REG_104H = 0x00000068U;
                            SCE->REG_E0H = 0x80010100U;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = InData_TBSCertificate[iLoop + 0];
                            SCE->REG_ECH = 0x0000b420U;
                            SCE->REG_ECH = 0x00000004U;
                            for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
                            {
                                SCE->REG_ECH = 0x00003020U;
                                SCE->REG_ECH = 0x01886ce8U;
                                SCE->REG_ECH = 0x00086d08U;
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c002859U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x3c002b42U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x30000c63U;
                                SCE->REG_ECH = 0x00030020U;
                                SCE->REG_ECH = 0x00186ce7U;
                                SCE->REG_ECH = 0x01886e07U;
                                SCE->REG_ECH = 0x001868e7U;
                                SCE->REG_ECH = 0x00000080U;
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c002857U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x3c002b02U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x38000c63U;
                                SCE->REG_E0H = 0x00000080U;
                                SCE->REG_1CH = 0x00260000U;
                                R_SCE_func100(0xaa4535c8U, 0x96c5f49bU, 0xd27cb1faU, 0x26a36d3dU);
                                SCE->REG_1CH = 0x00400000U;
                                SCE->REG_1D0H = 0x00000000U;
                                if (1U == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_E0H = 0x810100e0U;
                                    SCE->REG_00H = 0x0800080fU;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    SCE->REG_00H = 0x08003807U;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    R_SCE_func101(0x1aa528a5U, 0xb67f7933U, 0x4f40c9f8U, 0x73cb3da2U);
                                }
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c0028c2U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x38000c63U;
                                SCE->REG_E0H = 0x00000080U;
                                SCE->REG_1CH = 0x00260000U;
                                R_SCE_func100(0x88f0b169U, 0x4a785c63U, 0x14fe8d51U, 0xa2932d04U);
                                SCE->REG_1CH = 0x00400000U;
                                SCE->REG_1D0H = 0x00000000U;
                                if (1U == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_E0H = 0x810100e0U;
                                    SCE->REG_00H = 0x0800080fU;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    SCE->REG_00H = 0x08005807U;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    R_SCE_func101(0x675a0664U, 0x56e96b14U, 0x52cbc4f1U, 0xafc84c9bU);
                                }
                                SCE->REG_ECH = 0x00002c40U;
                                R_SCE_func101(0x76fd9fa7U, 0xcc4f60a5U, 0x9861aa93U, 0x9ab3ff64U);
                            }
                            SCE->REG_ECH = 0x08000c21U;
                            SCE->REG_E0H = 0x00000080U;
                            SCE->REG_1CH = 0x00260000U;
                            SCE->REG_1CH = 0x00402000U;
                            SCE->REG_ECH = 0x00002ca0U;
                            R_SCE_func101(0x1d5c098fU, 0x3889d9bbU, 0x1214915eU, 0x5b554333U);
                        }
                        SCE->REG_ECH = 0x38000805U;
                        SCE->REG_E0H = 0x00000080U;
                        SCE->REG_1CH = 0x00260000U;
                        SCE->REG_1CH = 0x00402000U;
                        R_SCE_func101(0x08f72ff1U, 0x286b46deU, 0x33955155U, 0x5a12feadU);
                    }
                    else
                    {
                        R_SCE_func100(0x2d4df4adU, 0x875c19b9U, 0xe875d798U, 0x3264edaeU);
                        SCE->REG_28H = 0x008f0001U;
                        SCE->REG_2CH = 0x00000010U;
                        SCE->REG_ECH = 0x00003416U;
                        SCE->REG_ECH = 0x00026800U;
                        SCE->REG_ECH = 0x38008ec0U;
                        SCE->REG_ECH = 0x00000003U;
                        SCE->REG_ECH = 0x20002c00U;
                        SCE->REG_E0H = 0x81010000U;
                        SCE->REG_04H = 0x00000707U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        S_RAM[0] = change_endian_long(SCE->REG_100H);
                        SCE->REG_ECH = 0x00003445U;
                        SCE->REG_ECH = 0x00026c42U;
                        SCE->REG_ECH = 0x000034d6U;
                        SCE->REG_ECH = 0x000030c0U;
                        SCE->REG_ECH = 0x00000a10U;
                        for (; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                        {
                            SCE->REG_104H = 0x00000068U;
                            SCE->REG_E0H = 0x80010100U;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = InData_TBSCertificate[iLoop + 0];
                            SCE->REG_ECH = 0x0000b420U;
                            SCE->REG_ECH = 0x00000004U;
                            for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
                            {
                                SCE->REG_ECH = 0x00003020U;
                                SCE->REG_ECH = 0x01886ce8U;
                                SCE->REG_ECH = 0x00086d08U;
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c002859U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x3c002b42U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x38000c63U;
                                SCE->REG_E0H = 0x00000080U;
                                SCE->REG_1CH = 0x00260000U;
                                R_SCE_func100(0x4fd6948dU, 0x023fb7d5U, 0xd49baf7bU, 0x0c4e82ddU);
                                SCE->REG_1CH = 0x00400000U;
                                SCE->REG_1D0H = 0x00000000U;
                                if (1U == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_E0H = 0x810100e0U;
                                    SCE->REG_00H = 0x0800080fU;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    SCE->REG_00H = 0x08003807U;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    R_SCE_func101(0xe2dbafa3U, 0x2e8eefefU, 0x36f680aeU, 0x90258c36U);
                                }
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c002857U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x3c002b02U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x38000c63U;
                                SCE->REG_E0H = 0x00000080U;
                                SCE->REG_1CH = 0x00260000U;
                                R_SCE_func100(0x30aafe58U, 0x199e2254U, 0xadee54fcU, 0x5fe4cb8aU);
                                SCE->REG_1CH = 0x00400000U;
                                SCE->REG_1D0H = 0x00000000U;
                                if (1U == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_E0H = 0x810100e0U;
                                    SCE->REG_00H = 0x0800080fU;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    SCE->REG_00H = 0x08003807U;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    R_SCE_func101(0x07c2d547U, 0x1a578abdU, 0x55b39de7U, 0x514d4e68U);
                                }
                                SCE->REG_ECH = 0x00000863U;
                                SCE->REG_ECH = 0x3c0028c2U;
                                SCE->REG_ECH = 0x20002c60U;
                                SCE->REG_ECH = 0x38000c63U;
                                SCE->REG_E0H = 0x00000080U;
                                SCE->REG_1CH = 0x00260000U;
                                R_SCE_func100(0xa7ce9d3cU, 0x7ac71894U, 0x6ef062f3U, 0xdddd9f83U);
                                SCE->REG_1CH = 0x00400000U;
                                SCE->REG_1D0H = 0x00000000U;
                                if (1U == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_E0H = 0x810100e0U;
                                    SCE->REG_00H = 0x0800080fU;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    SCE->REG_00H = 0x08005807U;
                                    /* WAIT_LOOP */
                                    while (0U != SCE->REG_00H_b.B25)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_1CH = 0x00001800U;
                                    R_SCE_func101(0xfc401ce9U, 0x8193a542U, 0x580b2549U, 0x1045b077U);
                                }
                                SCE->REG_ECH = 0x00002c40U;
                                R_SCE_func101(0xb01873a9U, 0xf891bfc8U, 0x2ccbaea7U, 0xf254191aU);
                            }
                            SCE->REG_ECH = 0x08000c21U;
                            SCE->REG_E0H = 0x00000080U;
                            SCE->REG_1CH = 0x00260000U;
                            SCE->REG_1CH = 0x00402000U;
                            SCE->REG_ECH = 0x00002ca0U;
                            R_SCE_func101(0xa4b10905U, 0x7047ab0aU, 0xc4772532U, 0xbb0bbca2U);
                        }
                        SCE->REG_ECH = 0x38000805U;
                        SCE->REG_E0H = 0x00000080U;
                        SCE->REG_1CH = 0x00260000U;
                        SCE->REG_1CH = 0x00402000U;
                        R_SCE_func101(0xfa13891eU, 0x4c2045deU, 0x0a80752eU, 0xbeaaa9f1U);
                    }
                    R_SCE_func100(0x43778663U, 0xc3616dc7U, 0x001b20cbU, 0x3897a204U);
                    SCE->REG_ECH = 0x00003416U;
                    SCE->REG_ECH = 0x00008c00U;
                    SCE->REG_ECH = 0x00000003U;
                    SCE->REG_ECH = 0x0000b440U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_ECH = 0x00002840U;
                    SCE->REG_E0H = 0x81010040U;
                    SCE->REG_04H = 0x00000707U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    S_RAM[0] = change_endian_long(SCE->REG_100H);
                    SCE->REG_ECH = 0x000008a5U;
                    SCE->REG_ECH = 0x0000b460U;
                    SCE->REG_ECH = 0x80000000U;
                    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                    {
                        SCE->REG_E0H = 0x81010060U;
                        SCE->REG_00H = 0x08005807U;
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
                        SCE->REG_ECH = 0x00086c63U;
                        SCE->REG_ECH = 0x00002ca0U;
                        R_SCE_func101(0x7dd8ff61U, 0x5ce07b00U, 0xd9ed8f0cU, 0xfaa940c0U);
                    }
                    R_SCE_func100(0x03df2cd2U, 0x82be7aa1U, 0x37843aefU, 0xaa2f7b14U);
                    SCE->REG_ECH = 0x38000845U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    SCE->REG_1CH = 0x00402000U;
                    SCE->REG_F8H = 0x00000040U;
                    SCE->REG_ECH = 0x00000800U;
                    SCE->REG_ECH = 0x00003436U;
                    SCE->REG_ECH = 0x01836c01U;
                    SCE->REG_ECH = 0x00036c21U;
                    SCE->REG_E0H = 0x81020000U;
                    SCE->REG_00H = 0x0000580bU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_74H_b.B18)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001600U;
                    SCE->REG_74H = 0x00000000U;
                    SCE->REG_ECH = 0x00007c0fU;
                    SCE->REG_1CH = 0x00600000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                    {
                        R_SCE_func100(0x9b028911U, 0x587d62a1U, 0x8fdaa628U, 0x33e80c92U);
                        SCE->REG_D0H = 0x00000f00U;
                        SCE->REG_C4H = 0x42e097bfU;
                        SCE->REG_00H = 0x00012303U;
                        SCE->REG_2CH = 0x00000020U;
                        SCE->REG_04H = 0x00000202U;
                        for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
                        {
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            S_HEAP[iLoop+68 + 0] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 1] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 2] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 3] = SCE->REG_100H;
                        }
                        R_SCE_func100(0x1564a25fU, 0xc4816d45U, 0x570efae3U, 0x530862d1U);
                        SCE->REG_104H = 0x00000052U;
                        SCE->REG_C4H = 0x00000c84U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x00000000U);
                        SCE->REG_C4H = 0x400019cdU;
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
                        S_HEAP[iLoop+68 + 0] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 1] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 2] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 3] = SCE->REG_100H;
                        R_SCE_func101(0xd04dc59eU, 0x8f47cd2fU, 0x8657a204U, 0xf714e8b5U);
                    }
                    else
                    {
                        R_SCE_func100(0xbb79836bU, 0xa316c4f9U, 0xaba66a89U, 0x3f398b80U);
                        SCE->REG_D0H = 0x00000300U;
                        SCE->REG_C4H = 0x42e097bfU;
                        SCE->REG_00H = 0x00002343U;
                        SCE->REG_2CH = 0x00000020U;
                        SCE->REG_04H = 0x00000242U;
                        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
                        {
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            S_HEAP[iLoop+68 + 0] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 1] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 2] = SCE->REG_100H;
                            S_HEAP[iLoop+68 + 3] = SCE->REG_100H;
                        }
                        R_SCE_func100(0xc87a9a37U, 0x59e6f29fU, 0xc0d49986U, 0x0ac9d256U);
                        SCE->REG_104H = 0x00000052U;
                        SCE->REG_C4H = 0x00000c84U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x00000000U);
                        SCE->REG_C4H = 0x400019cdU;
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
                        S_HEAP[iLoop+68 + 0] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 1] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 2] = SCE->REG_100H;
                        S_HEAP[iLoop+68 + 3] = SCE->REG_100H;
                        R_SCE_func101(0xc49ceca9U, 0xeb905358U, 0xce61a5adU, 0x3e5462cbU);
                    }
                    R_SCE_func100(0xbd2bf945U, 0x6870cf38U, 0x25ccd117U, 0x456d8a5aU);
                    SCE->REG_ECH = 0x00007c11U;
                    SCE->REG_1CH = 0x00600000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                    {
                        R_SCE_func100(0xc3b5dabfU, 0xc6161d9fU, 0xa9c4e77bU, 0x520d4cd9U);
                        SCE->REG_28H = 0x00bf0001U;
                        SCE->REG_2CH = 0x00000010U;
                        SCE->REG_104H = 0x00003f67U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = InData_Signature[0];
                        SCE->REG_100H = InData_Signature[1];
                        SCE->REG_100H = InData_Signature[2];
                        SCE->REG_100H = InData_Signature[3];
                        SCE->REG_100H = InData_Signature[4];
                        SCE->REG_100H = InData_Signature[5];
                        SCE->REG_100H = InData_Signature[6];
                        SCE->REG_100H = InData_Signature[7];
                        SCE->REG_100H = InData_Signature[8];
                        SCE->REG_100H = InData_Signature[9];
                        SCE->REG_100H = InData_Signature[10];
                        SCE->REG_100H = InData_Signature[11];
                        SCE->REG_100H = InData_Signature[12];
                        SCE->REG_100H = InData_Signature[13];
                        SCE->REG_100H = InData_Signature[14];
                        SCE->REG_100H = InData_Signature[15];
                        SCE->REG_100H = InData_Signature[16];
                        SCE->REG_100H = InData_Signature[17];
                        SCE->REG_100H = InData_Signature[18];
                        SCE->REG_100H = InData_Signature[19];
                        SCE->REG_100H = InData_Signature[20];
                        SCE->REG_100H = InData_Signature[21];
                        SCE->REG_100H = InData_Signature[22];
                        SCE->REG_100H = InData_Signature[23];
                        SCE->REG_100H = InData_Signature[24];
                        SCE->REG_100H = InData_Signature[25];
                        SCE->REG_100H = InData_Signature[26];
                        SCE->REG_100H = InData_Signature[27];
                        SCE->REG_100H = InData_Signature[28];
                        SCE->REG_100H = InData_Signature[29];
                        SCE->REG_100H = InData_Signature[30];
                        SCE->REG_100H = InData_Signature[31];
                        SCE->REG_100H = InData_Signature[32];
                        SCE->REG_100H = InData_Signature[33];
                        SCE->REG_100H = InData_Signature[34];
                        SCE->REG_100H = InData_Signature[35];
                        SCE->REG_100H = InData_Signature[36];
                        SCE->REG_100H = InData_Signature[37];
                        SCE->REG_100H = InData_Signature[38];
                        SCE->REG_100H = InData_Signature[39];
                        SCE->REG_100H = InData_Signature[40];
                        SCE->REG_100H = InData_Signature[41];
                        SCE->REG_100H = InData_Signature[42];
                        SCE->REG_100H = InData_Signature[43];
                        SCE->REG_100H = InData_Signature[44];
                        SCE->REG_100H = InData_Signature[45];
                        SCE->REG_100H = InData_Signature[46];
                        SCE->REG_100H = InData_Signature[47];
                        SCE->REG_100H = InData_Signature[48];
                        SCE->REG_100H = InData_Signature[49];
                        SCE->REG_100H = InData_Signature[50];
                        SCE->REG_100H = InData_Signature[51];
                        SCE->REG_100H = InData_Signature[52];
                        SCE->REG_100H = InData_Signature[53];
                        SCE->REG_100H = InData_Signature[54];
                        SCE->REG_100H = InData_Signature[55];
                        SCE->REG_100H = InData_Signature[56];
                        SCE->REG_100H = InData_Signature[57];
                        SCE->REG_100H = InData_Signature[58];
                        SCE->REG_100H = InData_Signature[59];
                        SCE->REG_100H = InData_Signature[60];
                        SCE->REG_100H = InData_Signature[61];
                        SCE->REG_100H = InData_Signature[62];
                        SCE->REG_100H = InData_Signature[63];
                        SCE->REG_18H = 0x00000004U;
                        SCE->REG_34H = 0x00000000U;
                        SCE->REG_38H = 0x00000338U;
                        SCE->REG_E0H = 0x81010140U;
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
                        SCE->REG_104H = 0x00003757U;
                        SCE->REG_2CH = 0x00000012U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x0001ffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0xffffffffU);
                        SCE->REG_100H = change_endian_long(0x00303130U);
                        SCE->REG_100H = change_endian_long(0x0d060960U);
                        SCE->REG_100H = change_endian_long(0x86480165U);
                        SCE->REG_100H = change_endian_long(0x03040201U);
                        SCE->REG_100H = change_endian_long(0x05000420U);
                        SCE->REG_00H = 0x00003523U;
                        SCE->REG_74H = 0x00000008U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        SCE->REG_24H = 0x000009c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001191U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        SCE->REG_24H = 0x000011c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000991U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        R_SCE_func101(0xebb5d198U, 0x93f9c294U, 0xf8d14679U, 0x25243ab6U);
                    }
                    else
                    {
                        SCE->REG_28H = 0x00870001U;
                        SCE->REG_34H = 0x00000400U;
                        SCE->REG_24H = 0x8000a8d0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
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
                        SCE->REG_ECH = 0x00000b9cU;
                        OFS_ADR = 128;
                        SCE->REG_104H = 0x00000058U;
                        SCE->REG_E0H = 0x800103a0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x000000e1U);
                        R_SCE_func101(0x1c2d8b1eU, 0xf9269806U, 0x8613d8e4U, 0x03ce85baU);
                        R_SCE_func003_r1(InData_Signature);
                        R_SCE_func101(0x4a454aceU, 0xf9d43be9U, 0x6d591b60U, 0xf03d232dU);
                    }
                    R_SCE_func100(0x6704d999U, 0x3b3b30d9U, 0xdc32ab2fU, 0xf792c581U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func102(0xb4e14136U, 0xf9f6c909U, 0x6d2f8225U, 0xd3aaf3d1U);
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
                        R_SCE_func100(0x121ffac2U, 0xa11eac78U, 0x22ca680eU, 0xe8c43443U);
                        SCE->REG_ECH = 0x00007c0fU;
                        SCE->REG_1CH = 0x00600000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                        {
                            R_SCE_func100(0x46d36418U, 0xd295a29cU, 0x82274183U, 0xb15f1f39U);
                            SCE->REG_28H = 0x00bf0001U;
                            SCE->REG_104H = 0x00003f62U;
                            SCE->REG_D0H = 0x00000f00U;
                            SCE->REG_C4H = 0x42f097bfU;
                            SCE->REG_00H = 0x00013203U;
                            SCE->REG_2CH = 0x00000014U;
                            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
                            {
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_104H_b.B31)
                                {
                                    /* waiting */
                                }
                                SCE->REG_100H = S_HEAP[iLoop+68 + 0];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 1];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 2];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 3];
                            }
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_00H_b.B25)
                            {
                                /* waiting */
                            }
                            SCE->REG_1CH = 0x00001800U;
                            SCE->REG_C4H = 0x400017bdU;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = S_HEAP[iLoop+68 + 0];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 1];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 2];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 3];
                            SCE->REG_C4H = 0x00800c45U;
                            SCE->REG_00H = 0x00002213U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_00H_b.B25)
                            {
                                /* waiting */
                            }
                            SCE->REG_1CH = 0x00001800U;
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
                            SCE->REG_104H = 0x00000058U;
                            SCE->REG_E0H = 0x80010000U;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = change_endian_long(0x01058801U);
                            R_SCE_func103();
                            SCE->REG_104H = 0x00000052U;
                            SCE->REG_C4H = 0x01000c84U;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = change_endian_long(0x00000000U);
                            SCE->REG_E0H = 0x80030020U;
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
                            SCE->REG_100H = change_endian_long(0x00000031U);
                            R_SCE_func101(0x93294027U, 0x2b1b7a91U, 0xc5bb9331U, 0xac005bc3U);
                            R_SCE_func059();
                            R_SCE_func100(0xc7411328U, 0xd0056c8aU, 0xf634844aU, 0xf9a330ceU);
                            SCE->REG_00H = 0x00012303U;
                            SCE->REG_2CH = 0x00000024U;
                            SCE->REG_D0H = 0x40000f00U;
                            SCE->REG_C4H = 0x02e087b7U;
                            SCE->REG_04H = 0x00000202U;
                            for (iLoop = 4; iLoop < 68; iLoop = iLoop + 4)
                            {
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                            }
                            R_SCE_func100(0x5d566accU, 0x3511b249U, 0x606e726fU, 0x43a5c67bU);
                            SCE->REG_00H = 0x00012303U;
                            SCE->REG_2CH = 0x00000022U;
                            SCE->REG_D0H = 0x40000f00U;
                            SCE->REG_C4H = 0x00e087b7U;
                            SCE->REG_04H = 0x00000202U;
                            for (; iLoop < 132; iLoop = iLoop + 4)
                            {
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                            }
                            R_SCE_func100(0xc4df0317U, 0x61760657U, 0x520a41f0U, 0x9e900f43U);
                            SCE->REG_D0H = 0x40000000U;
                            SCE->REG_C4H = 0x00e087b4U;
                            SCE->REG_E0H = 0x81010200U;
                            SCE->REG_00H = 0x00002807U;
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
                            OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                            R_SCE_func100(0x38ef57ceU, 0x4e2cdfe4U, 0xcb42f310U, 0x791c18bfU);
                            iLoop = iLoop+4;
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
                            OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                            OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                            R_SCE_func100(0x91bbf9a6U, 0x9179b77cU, 0xc3bd67a1U, 0x03b4ae01U);
                            SCE->REG_E0H = 0x81040000U;
                            SCE->REG_04H = 0x00000612U;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            OutData_PubKey[0] = SCE->REG_100H;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            OutData_PubKey[1] = SCE->REG_100H;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            OutData_PubKey[2] = SCE->REG_100H;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_04H_b.B30)
                            {
                                /* waiting */
                            }
                            OutData_PubKey[3] = SCE->REG_100H;
                            R_SCE_func102(0x24fd9247U, 0xab5e7c27U, 0x7b576b5bU, 0xd7404e59U);
                            SCE->REG_1B8H = 0x00000040U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_18H_b.B12)
                            {
                                /* waiting */
                            }
                            return FSP_SUCCESS;
                        }
                        else
                        {
                            SCE->REG_28H = 0x00870001U;
                            SCE->REG_ECH = 0x00000b9cU;
                            OFS_ADR = 128;
                            R_SCE_func100(0x5cf8da3fU, 0x62ed1bdaU, 0x1c28f209U, 0x9cbaaf99U);
                            R_SCE_func004_r1(OFS_ADR);
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
                            SCE->REG_28H = 0x008f0001U;
                            SCE->REG_104H = 0x00000f62U;
                            SCE->REG_D0H = 0x00000300U;
                            SCE->REG_C4H = 0x42f097bfU;
                            SCE->REG_00H = 0x00003243U;
                            SCE->REG_2CH = 0x00000010U;
                            for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
                            {
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_104H_b.B31)
                                {
                                    /* waiting */
                                }
                                SCE->REG_100H = S_HEAP[iLoop+68 + 0];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 1];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 2];
                                SCE->REG_100H = S_HEAP[iLoop+68 + 3];
                            }
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_00H_b.B25)
                            {
                                /* waiting */
                            }
                            SCE->REG_1CH = 0x00001800U;
                            SCE->REG_C4H = 0x400017bdU;
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = S_HEAP[iLoop+68 + 0];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 1];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 2];
                            SCE->REG_100H = S_HEAP[iLoop+68 + 3];
                            SCE->REG_C4H = 0x00800c45U;
                            SCE->REG_00H = 0x00002213U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_00H_b.B25)
                            {
                                /* waiting */
                            }
                            SCE->REG_1CH = 0x00001800U;
                            SCE->REG_28H = 0x00870001U;
                            SCE->REG_34H = 0x00000004U;
                            SCE->REG_24H = 0x800070d0U;
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
                            R_SCE_func008();
                            R_SCE_func100(0x2b96475eU, 0x24d0fc12U, 0xe0559746U, 0x187e3af6U);
                            SCE->REG_1CH = 0x00400000U;
                            SCE->REG_1D0H = 0x00000000U;
                            if (1U == (SCE->REG_1CH_b.B22))
                            {
                                R_SCE_func102(0xca783692U, 0x91ab0ec7U, 0x8bd589acU, 0x09e75e98U);
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
                                R_SCE_func100(0x22bf58b1U, 0xfeb6bea9U, 0x32741975U, 0xb4a11460U);
                                SCE->REG_34H = 0x00000400U;
                                SCE->REG_24H = 0x80008cd0U;
                                /* WAIT_LOOP */
                                while (0U != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_34H = 0x00000404U;
                                SCE->REG_24H = 0x80009008U;
                                /* WAIT_LOOP */
                                while (0U != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_34H = 0x00000002U;
                                SCE->REG_24H = 0x80008cd0U;
                                /* WAIT_LOOP */
                                while (0U != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_24H = 0x00009008U;
                                /* WAIT_LOOP */
                                while (0U != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_28H = 0x008f0001U;
                                SCE->REG_104H = 0x00000058U;
                                SCE->REG_E0H = 0x80010000U;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_104H_b.B31)
                                {
                                    /* waiting */
                                }
                                SCE->REG_100H = change_endian_long(0x01310801U);
                                R_SCE_func103();
                                SCE->REG_104H = 0x00000052U;
                                SCE->REG_C4H = 0x01000c84U;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_104H_b.B31)
                                {
                                    /* waiting */
                                }
                                SCE->REG_100H = change_endian_long(0x00000000U);
                                SCE->REG_E0H = 0x80030020U;
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
                                R_SCE_func101(0x4760d501U, 0x6b43073cU, 0xee8dcf28U, 0xd45cfbc6U);
                                R_SCE_func059();
                                R_SCE_func100(0x535465c0U, 0x9e2f5419U, 0xc0fe56c9U, 0xa1fac8f0U);
                                SCE->REG_00H = 0x00002343U;
                                SCE->REG_2CH = 0x00000020U;
                                SCE->REG_D0H = 0x40000300U;
                                SCE->REG_C4H = 0x02e087b7U;
                                SCE->REG_04H = 0x00000242U;
                                for (iLoop = 4; iLoop < 20; iLoop = iLoop + 4)
                                {
                                    /* WAIT_LOOP */
                                    while (1U != SCE->REG_04H_b.B30)
                                    {
                                        /* waiting */
                                    }
                                    OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                                    OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                                    OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                                    OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                                }
                                /* WAIT_LOOP */
                                while (0U != SCE->REG_00H_b.B25)
                                {
                                    /* waiting */
                                }
                                SCE->REG_1CH = 0x00001800U;
                                R_SCE_func100(0x513c1e16U, 0xfac98e31U, 0xf6689673U, 0x6a120cb0U);
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
                                OutData_PubKey[iLoop + 0] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 1] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 2] = SCE->REG_100H;
                                OutData_PubKey[iLoop + 3] = SCE->REG_100H;
                                R_SCE_func100(0xc464e8c7U, 0xb500ad01U, 0xde08bb5cU, 0xe30e1e33U);
                                SCE->REG_E0H = 0x81040000U;
                                SCE->REG_04H = 0x00000612U;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[0] = SCE->REG_100H;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[1] = SCE->REG_100H;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[2] = SCE->REG_100H;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_PubKey[3] = SCE->REG_100H;
                                R_SCE_func102(0xf7df9bd1U, 0x002f88b6U, 0x618e9838U, 0x5b36a4fcU);
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
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe1_r2.prc
***********************************************************************************************************************/
