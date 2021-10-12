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

fsp_err_t R_SCE_TlsServersEphemeralEcdhPublicKeyRetrievesSub(uint32_t *InData_Sel_PubKeyType, uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *InData_Sel_CompressType, uint32_t *InData_SKE_Message, uint32_t *InData_SKE_Signature, uint32_t *InData_PubKey, uint32_t *OutData_EphemeralPubKey)
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
    (void)InData_Sel_CompressType;
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000e702U;
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
    R_SCE_func100(0x0d9230beU, 0x454059abU, 0x94f33436U, 0x3c39ace1U);
    R_SCE_func103();
    R_SCE_func100(0x08fbe3eeU, 0x8a9b7a2dU, 0x7ff0d272U, 0x12c7c86dU);
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
    R_SCE_func100(0xbbab3a93U, 0x95b4e10aU, 0x69df03c3U, 0x238dcac2U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0xdac88ed0U, 0xefd18ea0U, 0x689eb32fU, 0x5151034bU);
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
        SCE->REG_ECH = 0x300089e0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_ECH = 0x00030020U;
        SCE->REG_ECH = 0x38008be0U;
        SCE->REG_ECH = 0x00050000U;
        SCE->REG_ECH = 0x1000d3c0U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x38008be0U;
        SCE->REG_ECH = 0x00310000U;
        SCE->REG_ECH = 0x1000d3c0U;
        SCE->REG_ECH = 0x00000080U;
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
        R_SCE_func100(0xb487d0c4U, 0x35311d95U, 0xc97d5899U, 0xf4d76b5aU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xd28e9578U, 0xc091a5adU, 0xb0f0ce34U, 0x3d0f6b98U);
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
            SCE->REG_100H = change_endian_long(0x000000e7U);
            R_SCE_func101(0x62877533U, 0x26b1b9edU, 0xa8d60c52U, 0x71ee0821U);
            R_SCE_func059();
            R_SCE_func100(0xb4058388U, 0xc5d4e719U, 0x7b874c76U, 0x3a5563c5U);
            SCE->REG_ECH = 0x00007c0fU;
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
                R_SCE_func101(0x100687f3U, 0x1302b6cbU, 0xd4038e26U, 0x3cb6d735U);
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
                SCE->REG_2CH = 0x00000091U;
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
                R_SCE_func101(0x496375c0U, 0x1b5f3cb4U, 0xd65b2350U, 0xea5f5d00U);
            }
            R_SCE_func100(0x807ae9feU, 0x755b9943U, 0x612b0059U, 0x1cd61442U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x0f2eb44aU, 0x2249fd41U, 0x719b370bU, 0x5b8190deU);
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
                SCE->REG_104H = 0x00000f64U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_ClientRandom[0];
                SCE->REG_100H = InData_ClientRandom[1];
                SCE->REG_100H = InData_ClientRandom[2];
                SCE->REG_100H = InData_ClientRandom[3];
                SCE->REG_100H = InData_ClientRandom[4];
                SCE->REG_100H = InData_ClientRandom[5];
                SCE->REG_100H = InData_ClientRandom[6];
                SCE->REG_100H = InData_ClientRandom[7];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_ServerRandom[0];
                SCE->REG_100H = InData_ServerRandom[1];
                SCE->REG_100H = InData_ServerRandom[2];
                SCE->REG_100H = InData_ServerRandom[3];
                SCE->REG_100H = InData_ServerRandom[4];
                SCE->REG_100H = InData_ServerRandom[5];
                SCE->REG_100H = InData_ServerRandom[6];
                SCE->REG_100H = InData_ServerRandom[7];
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x03001741U;
                SCE->REG_E0H = 0x810103c0U;
                SCE->REG_00H = 0x00005807U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x800103c0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SKE_Message[0];
                SCE->REG_E0H = 0x810103c0U;
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
                R_SCE_func100(0x60865debU, 0x653e9efaU, 0xb92d9458U, 0x53c8c5f5U);
                SCE->REG_104H = 0x00000b62U;
                SCE->REG_D0H = 0x00000200U;
                SCE->REG_C4H = 0x42e097bfU;
                for (iLoop = 0; iLoop < 12; iLoop = iLoop + 4)
                {
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_SKE_Message[iLoop+1 + 0];
                    SCE->REG_100H = InData_SKE_Message[iLoop+1 + 1];
                    SCE->REG_100H = InData_SKE_Message[iLoop+1 + 2];
                    SCE->REG_100H = InData_SKE_Message[iLoop+1 + 3];
                }
                SCE->REG_04H = 0x00000232U;
                for (iLoop = 0; iLoop < 12; iLoop = iLoop + 4)
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
                R_SCE_func100(0x1e464166U, 0x485af5b2U, 0x81e31de9U, 0x8b9ed8feU);
                SCE->REG_104H = 0x00000362U;
                SCE->REG_C4H = 0x40e017bdU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SKE_Message[13];
                SCE->REG_100H = InData_SKE_Message[14];
                SCE->REG_100H = InData_SKE_Message[15];
                SCE->REG_100H = InData_SKE_Message[16];
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
                R_SCE_func100(0xba88b46fU, 0x25e0af43U, 0x360805c6U, 0x90af43c1U);
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
                S_HEAP[iLoop+72 + 0] = SCE->REG_100H;
                S_HEAP[iLoop+72 + 1] = SCE->REG_100H;
                S_HEAP[iLoop+72 + 2] = SCE->REG_100H;
                S_HEAP[iLoop+72 + 3] = SCE->REG_100H;
                SCE->REG_104H = 0x00000f62U;
                SCE->REG_D0H = 0x00000300U;
                SCE->REG_C4H = 0x42f097bfU;
                SCE->REG_00H = 0x08015203U;
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
                SCE->REG_104H = 0x00000362U;
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
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x80000000U;
                SCE->REG_E0H = 0x810103c0U;
                SCE->REG_00H = 0x0800580fU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x08000807U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_F8H = 0x00000040U;
                SCE->REG_104H = 0x00000154U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_100H = change_endian_long(0x00000428U);
                R_SCE_func100(0x0141edd2U, 0x342b8f5fU, 0x3832bc72U, 0x1e7f787eU);
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
                    R_SCE_func100(0xe4b4ab65U, 0x4fc85decU, 0x83723a13U, 0xa45a7a51U);
                    SCE->REG_28H = 0x00bf0001U;
                    SCE->REG_2CH = 0x00000010U;
                    SCE->REG_104H = 0x00003f67U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_SKE_Signature[0];
                    SCE->REG_100H = InData_SKE_Signature[1];
                    SCE->REG_100H = InData_SKE_Signature[2];
                    SCE->REG_100H = InData_SKE_Signature[3];
                    SCE->REG_100H = InData_SKE_Signature[4];
                    SCE->REG_100H = InData_SKE_Signature[5];
                    SCE->REG_100H = InData_SKE_Signature[6];
                    SCE->REG_100H = InData_SKE_Signature[7];
                    SCE->REG_100H = InData_SKE_Signature[8];
                    SCE->REG_100H = InData_SKE_Signature[9];
                    SCE->REG_100H = InData_SKE_Signature[10];
                    SCE->REG_100H = InData_SKE_Signature[11];
                    SCE->REG_100H = InData_SKE_Signature[12];
                    SCE->REG_100H = InData_SKE_Signature[13];
                    SCE->REG_100H = InData_SKE_Signature[14];
                    SCE->REG_100H = InData_SKE_Signature[15];
                    SCE->REG_100H = InData_SKE_Signature[16];
                    SCE->REG_100H = InData_SKE_Signature[17];
                    SCE->REG_100H = InData_SKE_Signature[18];
                    SCE->REG_100H = InData_SKE_Signature[19];
                    SCE->REG_100H = InData_SKE_Signature[20];
                    SCE->REG_100H = InData_SKE_Signature[21];
                    SCE->REG_100H = InData_SKE_Signature[22];
                    SCE->REG_100H = InData_SKE_Signature[23];
                    SCE->REG_100H = InData_SKE_Signature[24];
                    SCE->REG_100H = InData_SKE_Signature[25];
                    SCE->REG_100H = InData_SKE_Signature[26];
                    SCE->REG_100H = InData_SKE_Signature[27];
                    SCE->REG_100H = InData_SKE_Signature[28];
                    SCE->REG_100H = InData_SKE_Signature[29];
                    SCE->REG_100H = InData_SKE_Signature[30];
                    SCE->REG_100H = InData_SKE_Signature[31];
                    SCE->REG_100H = InData_SKE_Signature[32];
                    SCE->REG_100H = InData_SKE_Signature[33];
                    SCE->REG_100H = InData_SKE_Signature[34];
                    SCE->REG_100H = InData_SKE_Signature[35];
                    SCE->REG_100H = InData_SKE_Signature[36];
                    SCE->REG_100H = InData_SKE_Signature[37];
                    SCE->REG_100H = InData_SKE_Signature[38];
                    SCE->REG_100H = InData_SKE_Signature[39];
                    SCE->REG_100H = InData_SKE_Signature[40];
                    SCE->REG_100H = InData_SKE_Signature[41];
                    SCE->REG_100H = InData_SKE_Signature[42];
                    SCE->REG_100H = InData_SKE_Signature[43];
                    SCE->REG_100H = InData_SKE_Signature[44];
                    SCE->REG_100H = InData_SKE_Signature[45];
                    SCE->REG_100H = InData_SKE_Signature[46];
                    SCE->REG_100H = InData_SKE_Signature[47];
                    SCE->REG_100H = InData_SKE_Signature[48];
                    SCE->REG_100H = InData_SKE_Signature[49];
                    SCE->REG_100H = InData_SKE_Signature[50];
                    SCE->REG_100H = InData_SKE_Signature[51];
                    SCE->REG_100H = InData_SKE_Signature[52];
                    SCE->REG_100H = InData_SKE_Signature[53];
                    SCE->REG_100H = InData_SKE_Signature[54];
                    SCE->REG_100H = InData_SKE_Signature[55];
                    SCE->REG_100H = InData_SKE_Signature[56];
                    SCE->REG_100H = InData_SKE_Signature[57];
                    SCE->REG_100H = InData_SKE_Signature[58];
                    SCE->REG_100H = InData_SKE_Signature[59];
                    SCE->REG_100H = InData_SKE_Signature[60];
                    SCE->REG_100H = InData_SKE_Signature[61];
                    SCE->REG_100H = InData_SKE_Signature[62];
                    SCE->REG_100H = InData_SKE_Signature[63];
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
                    R_SCE_func101(0xc57043c2U, 0xc795b1b7U, 0x59e88183U, 0xe3cff38aU);
                }
                else
                {
                    SCE->REG_28H = 0x00870001U;
                    SCE->REG_ECH = 0x00000b9cU;
                    OFS_ADR = 128;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000e7U);
                    R_SCE_func101(0xea126629U, 0xd77ad021U, 0x0273a7ffU, 0x3e24bee9U);
                    R_SCE_func003_r1(InData_SKE_Signature);
                    R_SCE_func101(0x504fe8d8U, 0x2972efcbU, 0x85ff4f77U, 0xf1713252U);
                }
                R_SCE_func100(0xb909527eU, 0x25929460U, 0x20e1017aU, 0xa41770e0U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0x96a5aef5U, 0x8e435ae7U, 0x7d445d8eU, 0xc0e3eb5fU);
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
                    SCE->REG_28H = 0x00870001U;
                    SCE->REG_ECH = 0x00000b9cU;
                    OFS_ADR = 128;
                    R_SCE_func100(0x6c3422cfU, 0xc3fd9efcU, 0x8fbb7deeU, 0x278522ddU);
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
                    R_SCE_func100(0x1fc7fc2cU, 0x63e47ac7U, 0x22a374ccU, 0xc504973fU);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func102(0x1eaca43bU, 0x44127cacU, 0x076cc9d2U, 0x8d90d614U);
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
                        R_SCE_func100(0xbf9802d2U, 0x43bc12ecU, 0x8f84300fU, 0xad68cf6cU);
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
                        SCE->REG_100H = change_endian_long(0x01310201U);
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
                        SCE->REG_100H = change_endian_long(0x00000053U);
                        R_SCE_func101(0x28b35c2bU, 0x5b363b65U, 0xf49dc395U, 0xa072db0fU);
                        R_SCE_func059();
                        R_SCE_func100(0x8268449cU, 0x7352e0c4U, 0x87c3ce24U, 0xf7a5e8dfU);
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
                            OutData_EphemeralPubKey[iLoop + 0] = SCE->REG_100H;
                            OutData_EphemeralPubKey[iLoop + 1] = SCE->REG_100H;
                            OutData_EphemeralPubKey[iLoop + 2] = SCE->REG_100H;
                            OutData_EphemeralPubKey[iLoop + 3] = SCE->REG_100H;
                        }
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        R_SCE_func100(0x1a03594bU, 0x6be00182U, 0xd9979282U, 0x07a9b7feU);
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
                        OutData_EphemeralPubKey[iLoop + 0] = SCE->REG_100H;
                        OutData_EphemeralPubKey[iLoop + 1] = SCE->REG_100H;
                        OutData_EphemeralPubKey[iLoop + 2] = SCE->REG_100H;
                        OutData_EphemeralPubKey[iLoop + 3] = SCE->REG_100H;
                        R_SCE_func100(0xc487bcc1U, 0x2138717cU, 0x7543a75fU, 0xf949b162U);
                        SCE->REG_E0H = 0x81040000U;
                        SCE->REG_04H = 0x00000612U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_EphemeralPubKey[0] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_EphemeralPubKey[1] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_EphemeralPubKey[2] = SCE->REG_100H;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_04H_b.B30)
                        {
                            /* waiting */
                        }
                        OutData_EphemeralPubKey[3] = SCE->REG_100H;
                        R_SCE_func102(0x6ec4a47cU, 0xd2050286U, 0xedf81e48U, 0xf7626f1fU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe7_r2.prc
***********************************************************************************************************************/
