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

fsp_err_t R_SCE_TlsRootCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType, uint32_t *InData_Certificates, uint32_t *InData_CertificatesLength, uint32_t *InData_Signature, uint32_t *InData_CertificatesInfo, uint32_t length, uint32_t *OutData_PubKey)
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
    SCE->REG_84H = 0x0000e002U;
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
    R_SCE_func100(0x2371b7edU, 0x6272bd79U, 0xfc7b9804U, 0x39d8853eU);
    R_SCE_func103();
    R_SCE_func100(0x26a9adc7U, 0x44115aebU, 0xdcb1b9f3U, 0x6f8bd6d9U);
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
    R_SCE_func100(0x66515816U, 0xba82a87bU, 0x4d3ca0bdU, 0x0e2e0b69U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x878abce1U, 0x8b5d8020U, 0x22582ebfU, 0xc8d788a5U);
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
        R_SCE_func100(0xb064c1c6U, 0x316ee407U, 0xd55c5863U, 0x01ddcec7U);
        SCE->REG_104H = 0x00000468U;
        SCE->REG_E0H = 0x800502c0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_CertificatesLength[0];
        for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_CertificatesInfo[iLoop + 0];
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
            R_SCE_func101(0x24898a4bU, 0xbd1494c1U, 0xcaabc15cU, 0xa1215d56U);
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
            R_SCE_func101(0x69561b3eU, 0x36dcac61U, 0x3457d481U, 0xf1bcf5e3U);
        }
        R_SCE_func100(0x8a162f8eU, 0x6c038816U, 0x6a09cc83U, 0xbfd556b0U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x56a62d7fU, 0xbfa8e901U, 0x79f573a1U, 0xfa77f228U);
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
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_INST[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000e0U);
            R_SCE_func101(0x21bfcf8aU, 0x9e1b4c77U, 0x67dcbbaeU, 0x9f4aaa76U);
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
            SCE->REG_100H = change_endian_long(0x000000e0U);
            R_SCE_func101(0x1a03e686U, 0xb01c7b0bU, 0x9c49dc62U, 0xc0a911c7U);
            R_SCE_func044();
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x01000001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000004U);
            R_SCE_func101(0x1fd2d326U, 0x7d1aba23U, 0xe1d1c4aeU, 0x7ae7ef2bU);
            R_SCE_func044();
            R_SCE_func100(0x959342faU, 0xa6b3df3fU, 0x39b514f6U, 0xb1fd25f8U);
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000014U;
            SCE->REG_104H = 0x00007f62U;
            SCE->REG_D0H = 0x40001f00U;
            SCE->REG_C4H = 0x02f087b7U;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_INST[1+iLoop + 0];
                SCE->REG_100H = S_INST[1+iLoop + 1];
                SCE->REG_100H = S_INST[1+iLoop + 2];
                SCE->REG_100H = S_INST[1+iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            for (; iLoop < 128; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_INST[1+iLoop + 0];
                SCE->REG_100H = S_INST[1+iLoop + 1];
                SCE->REG_100H = S_INST[1+iLoop + 2];
                SCE->REG_100H = S_INST[1+iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x00f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_INST[1+iLoop + 0];
            SCE->REG_100H = S_INST[1+iLoop + 1];
            SCE->REG_100H = S_INST[1+iLoop + 2];
            SCE->REG_100H = S_INST[1+iLoop + 3];
            iLoop = iLoop+4;
            SCE->REG_E0H = 0x80040140U;
            SCE->REG_00H = 0x00008213U;
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
            SCE->REG_100H = S_INST[1+iLoop + 0];
            SCE->REG_100H = S_INST[1+iLoop + 1];
            SCE->REG_100H = S_INST[1+iLoop + 2];
            SCE->REG_100H = S_INST[1+iLoop + 3];
            SCE->REG_C4H = 0x00800c45U;
            SCE->REG_00H = 0x00002213U;
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
                SCE->REG_100H = InData_Certificates[iLoop + 0];
                SCE->REG_100H = InData_Certificates[iLoop + 1];
                SCE->REG_100H = InData_Certificates[iLoop + 2];
                SCE->REG_100H = InData_Certificates[iLoop + 3];
                SCE->REG_ECH = 0x0000a4a0U;
                SCE->REG_ECH = 0x00000004U;
                R_SCE_func101(0x3a9374ddU, 0xcb0d3a44U, 0x2c81df2cU, 0x9500cc5eU);
            }
            R_SCE_func100(0x740c6fe3U, 0xd23d1089U, 0x35f82430U, 0xdcb7c46aU);
            SCE->REG_ECH = 0x38000805U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_1CH = 0x00402000U;
            SCE->REG_ECH = 0x00007c0fU;
            SCE->REG_1CH = 0x00600000U;
            SCE->REG_1D0H = 0x00000000U;
            if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x4cae2ba0U, 0x0f3885e9U, 0x47cd9a26U, 0x112f231bU);
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
                    SCE->REG_100H = InData_Certificates[iLoop + 0];
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
                        R_SCE_func100(0x1e586482U, 0x505cf219U, 0xfe5da9e3U, 0x895e57b9U);
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
                            R_SCE_func101(0x4d7c545fU, 0x1a23a336U, 0x813072b8U, 0xb95c42d2U);
                        }
                        SCE->REG_ECH = 0x00000863U;
                        SCE->REG_ECH = 0x3c0028c2U;
                        SCE->REG_ECH = 0x20002c60U;
                        SCE->REG_ECH = 0x38000c63U;
                        SCE->REG_E0H = 0x00000080U;
                        SCE->REG_1CH = 0x00260000U;
                        R_SCE_func100(0xec025d6cU, 0x801eb789U, 0x347b58f6U, 0x373e1899U);
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
                            R_SCE_func101(0xe5f8eb70U, 0x147f8087U, 0xf22e1dd9U, 0x7be2bb4fU);
                        }
                        SCE->REG_ECH = 0x00002c40U;
                        R_SCE_func101(0xa5e2d6d4U, 0x2009eb35U, 0xf032f142U, 0x505b1c3aU);
                    }
                    SCE->REG_ECH = 0x08000c21U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    SCE->REG_1CH = 0x00402000U;
                    SCE->REG_ECH = 0x00002ca0U;
                    R_SCE_func101(0xbe8439a2U, 0x6bdfc436U, 0x9662e70fU, 0x243c6edaU);
                }
                SCE->REG_ECH = 0x38000805U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                R_SCE_func101(0xa38ef5deU, 0x734f61e7U, 0x1d0ea811U, 0x1ec114f3U);
            }
            else
            {
                R_SCE_func100(0x3e7d9c13U, 0x83d53570U, 0xd392fed2U, 0xb140e6c3U);
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
                    SCE->REG_100H = InData_Certificates[iLoop + 0];
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
                        R_SCE_func100(0xd33f3aa7U, 0x40bc0260U, 0x46b91350U, 0xc08b815eU);
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
                            R_SCE_func101(0xd55dab2cU, 0xe3f35323U, 0x246d6010U, 0x3fc988abU);
                        }
                        SCE->REG_ECH = 0x00000863U;
                        SCE->REG_ECH = 0x3c002857U;
                        SCE->REG_ECH = 0x20002c60U;
                        SCE->REG_ECH = 0x3c002b02U;
                        SCE->REG_ECH = 0x20002c60U;
                        SCE->REG_ECH = 0x38000c63U;
                        SCE->REG_E0H = 0x00000080U;
                        SCE->REG_1CH = 0x00260000U;
                        R_SCE_func100(0x9841900bU, 0x07651becU, 0x70b70563U, 0x94b08159U);
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
                            R_SCE_func101(0x28406a2bU, 0x60d747ddU, 0x9d064e52U, 0x31e11afdU);
                        }
                        SCE->REG_ECH = 0x00000863U;
                        SCE->REG_ECH = 0x3c0028c2U;
                        SCE->REG_ECH = 0x20002c60U;
                        SCE->REG_ECH = 0x38000c63U;
                        SCE->REG_E0H = 0x00000080U;
                        SCE->REG_1CH = 0x00260000U;
                        R_SCE_func100(0x904194a8U, 0xc8b145c8U, 0x6f5c4f30U, 0x5b9b43fcU);
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
                            R_SCE_func101(0x2c682db1U, 0xf1d227d7U, 0x69ead2c9U, 0xb37ec3bbU);
                        }
                        SCE->REG_ECH = 0x00002c40U;
                        R_SCE_func101(0xdc68bbb9U, 0xc303dc2aU, 0xfeb15896U, 0x366425e4U);
                    }
                    SCE->REG_ECH = 0x08000c21U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    SCE->REG_1CH = 0x00402000U;
                    SCE->REG_ECH = 0x00002ca0U;
                    R_SCE_func101(0x7bc527baU, 0x3de115edU, 0x0d17bcb7U, 0x88b87563U);
                }
                SCE->REG_ECH = 0x38000805U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                R_SCE_func101(0xd332f609U, 0xe239426eU, 0x447e4227U, 0xfe8457acU);
            }
            R_SCE_func100(0x653e1f32U, 0x1de3332fU, 0xe4818756U, 0xaeb023cfU);
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
                R_SCE_func101(0x855fa33cU, 0x2c4b6404U, 0x1f2d89f5U, 0x32c2a2f6U);
            }
            R_SCE_func100(0x43b5b359U, 0x68f8d181U, 0xbf4e767cU, 0xcb9a4f56U);
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
                R_SCE_func100(0xd51de90fU, 0x869b0976U, 0xf3b5c8ffU, 0x8603a1dfU);
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
                    S_HEAP[iLoop + 0] = SCE->REG_100H;
                    S_HEAP[iLoop + 1] = SCE->REG_100H;
                    S_HEAP[iLoop + 2] = SCE->REG_100H;
                    S_HEAP[iLoop + 3] = SCE->REG_100H;
                }
                R_SCE_func100(0xe5d8bcf1U, 0xe0796193U, 0xb27bce2cU, 0xca6a2a6bU);
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
                S_HEAP[iLoop + 0] = SCE->REG_100H;
                S_HEAP[iLoop + 1] = SCE->REG_100H;
                S_HEAP[iLoop + 2] = SCE->REG_100H;
                S_HEAP[iLoop + 3] = SCE->REG_100H;
                R_SCE_func101(0xd4fca22dU, 0xaf2b9859U, 0x0e3a386cU, 0x3c678019U);
            }
            else
            {
                R_SCE_func100(0x03c80255U, 0x531d045eU, 0x573c5ebaU, 0xe90208e8U);
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
                    S_HEAP[iLoop + 0] = SCE->REG_100H;
                    S_HEAP[iLoop + 1] = SCE->REG_100H;
                    S_HEAP[iLoop + 2] = SCE->REG_100H;
                    S_HEAP[iLoop + 3] = SCE->REG_100H;
                }
                R_SCE_func100(0xc340fa3cU, 0xb6ac91acU, 0x9c875708U, 0x6af4b668U);
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
                S_HEAP[iLoop + 0] = SCE->REG_100H;
                S_HEAP[iLoop + 1] = SCE->REG_100H;
                S_HEAP[iLoop + 2] = SCE->REG_100H;
                S_HEAP[iLoop + 3] = SCE->REG_100H;
                SCE->REG_28H = 0x00bf0001U;
                R_SCE_func101(0xed9bbae3U, 0x320781d0U, 0xb4ca91b9U, 0x6a572aeaU);
            }
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
            SCE->REG_ECH = 0x0000342aU;
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x000000e0U;
            SCE->REG_ECH = 0x0000b440U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x000000f0U;
            SCE->REG_E0H = 0x81840007U;
            SCE->REG_C4H = 0x00000885U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_E0H = 0x80040100U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func101(0x6520f9b6U, 0xd7f6a708U, 0x997b69c0U, 0x465419fcU);
            R_SCE_TlsRootCertificateVerificationSubSub();

            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x000000f0U;
            SCE->REG_E0H = 0x81040100U;
            SCE->REG_C4H = 0x00000885U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_E0H = 0x80840007U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0xaa73062aU, 0x8e330412U, 0x6a926048U, 0xd4e62a73U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x2dcb2ec3U, 0x03f5c58fU, 0x09053cafU, 0x5e69c55cU);
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
                R_SCE_func100(0xd3bb9320U, 0x4cc89f41U, 0xda823e6eU, 0xc124fe79U);
                SCE->REG_ECH = 0x00007c0fU;
                SCE->REG_1CH = 0x00600000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
                {
                    R_SCE_func100(0xa30c0768U, 0x4dd11d4bU, 0x4ad4936bU, 0x8a9e0636U);
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
                        SCE->REG_100H = S_HEAP[iLoop + 0];
                        SCE->REG_100H = S_HEAP[iLoop + 1];
                        SCE->REG_100H = S_HEAP[iLoop + 2];
                        SCE->REG_100H = S_HEAP[iLoop + 3];
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
                    SCE->REG_100H = S_HEAP[iLoop + 0];
                    SCE->REG_100H = S_HEAP[iLoop + 1];
                    SCE->REG_100H = S_HEAP[iLoop + 2];
                    SCE->REG_100H = S_HEAP[iLoop + 3];
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
                    SCE->REG_100H = change_endian_long(0x01050801U);
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
                    SCE->REG_100H = change_endian_long(0x000000e0U);
                    R_SCE_func101(0x23c066cfU, 0xc7cb3c72U, 0xb5efb75fU, 0x48ff625eU);
                    R_SCE_func059();
                    R_SCE_func100(0xca1d14a3U, 0x8772c5ceU, 0xde55afe8U, 0x3f437e04U);
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
                    R_SCE_func100(0xe07566c8U, 0xc322a98bU, 0xb4eb4af2U, 0x30bf659aU);
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
                    R_SCE_func100(0x05ac9a90U, 0x612ba53bU, 0x8381d5a1U, 0x59efe3eeU);
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
                    R_SCE_func100(0x8c360eeeU, 0xfe2fceb1U, 0xca255c25U, 0x825f4157U);
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
                    R_SCE_func100(0x079a95caU, 0x5dd49aeaU, 0x6a38d9d8U, 0xf0f28cdaU);
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
                    R_SCE_func102(0x6ea8c435U, 0x5bd2084eU, 0x6b6d9e75U, 0x8947a61eU);
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
                    R_SCE_func100(0x18dde013U, 0x23867526U, 0x8df1c8a1U, 0xae8d6b1eU);
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
                        SCE->REG_100H = S_HEAP[iLoop + 0];
                        SCE->REG_100H = S_HEAP[iLoop + 1];
                        SCE->REG_100H = S_HEAP[iLoop + 2];
                        SCE->REG_100H = S_HEAP[iLoop + 3];
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
                    SCE->REG_100H = S_HEAP[iLoop + 0];
                    SCE->REG_100H = S_HEAP[iLoop + 1];
                    SCE->REG_100H = S_HEAP[iLoop + 2];
                    SCE->REG_100H = S_HEAP[iLoop + 3];
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
                    R_SCE_func100(0x083d3c66U, 0x2396b2c5U, 0xe1147f0cU, 0xc4fa26feU);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func102(0xb520657bU, 0xc8aed843U, 0x96499ebcU, 0x0427341eU);
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
                        R_SCE_func100(0x8f2556b7U, 0x6ceb627fU, 0x94c1f559U, 0x9ef61d40U);
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
                        SCE->REG_100H = change_endian_long(0x00000030U);
                        R_SCE_func101(0x38278e23U, 0x3ec0949dU, 0x0448e630U, 0x9f92d3f3U);
                        R_SCE_func059();
                        R_SCE_func100(0x235d4601U, 0x85bf4f7cU, 0x4bc35a5dU, 0xe7a15bdaU);
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
                        R_SCE_func100(0x46017b0aU, 0xb7571533U, 0xa0c304f7U, 0xf16246ccU);
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
                        R_SCE_func100(0x42c32d5bU, 0xc5718df0U, 0x3f71aac3U, 0x9ed04c33U);
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
                        R_SCE_func102(0xc954a99cU, 0x1e9c3dc7U, 0x4a9cdce6U, 0x6d4ebf07U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe0_r2.prc
***********************************************************************************************************************/
