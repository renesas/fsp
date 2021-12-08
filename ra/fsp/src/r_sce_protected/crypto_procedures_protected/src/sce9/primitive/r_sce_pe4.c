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

fsp_err_t R_SCE_TlsGenerateMasterSecretSub(uint32_t *InData_Sel_CipherSuite, uint32_t *InData_PreMasterSecret, uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *OutData_MasterSecret)
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
    SCE->REG_84H = 0x0000e402U;
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
    SCE->REG_E0H = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Sel_CipherSuite[0];
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa59d2b56U, 0x8755a254U, 0xb11c9cf6U, 0x07478cb8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x1320633aU, 0x86546a8aU, 0xd4ab96b7U, 0xc919095bU);
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
        SCE->REG_100H = change_endian_long(0x000000e4U);
        R_SCE_func101(0x2118adebU, 0xc5bfe441U, 0xd7c63cefU, 0x35b00ae5U);
        R_SCE_func059();
        SCE->REG_ECH = 0x3420a800U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0x209cdfe0U, 0x34ae0cb2U, 0xb8883696U, 0x8faaef69U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x0154569cU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000e4U);
            R_SCE_func101(0xfdcbdd26U, 0xe7e9e149U, 0x41e87163U, 0x3275e5baU);
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
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x808c0000U;
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
            R_SCE_func101(0x6f5bc605U, 0x2fa93724U, 0x66f2da6cU, 0x80f8d4f5U);
        }
        else
        {
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x01c1817fU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000030U);
            R_SCE_func101(0xcc67dbfbU, 0x06d55bbbU, 0x97b48a8bU, 0xafbb18abU);
            R_SCE_func044();
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x40000100U;
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
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x808c0000U;
            SCE->REG_00H = 0x00008223U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008013U;
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
            SCE->REG_100H = InData_PreMasterSecret[12];
            SCE->REG_100H = InData_PreMasterSecret[13];
            SCE->REG_100H = InData_PreMasterSecret[14];
            SCE->REG_100H = InData_PreMasterSecret[15];
            R_SCE_func101(0xd99c6b1fU, 0xb74cda8cU, 0xd740f9b0U, 0x757390c8U);
        }
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x3139c8e6U, 0x830404edU, 0x061ba820U, 0x023c8821U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xe0d513b2U, 0xbe24df6bU, 0x68013ccbU, 0x69455443U);
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
            SCE->REG_104H = 0x00000352U;
            SCE->REG_C4H = 0x00000885U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x6d617374U);
            SCE->REG_100H = change_endian_long(0x65722073U);
            SCE->REG_100H = change_endian_long(0x65637265U);
            SCE->REG_100H = change_endian_long(0x74000000U);
            SCE->REG_ECH = 0x0000b460U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_E0H = 0x80830003U;
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
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010000U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000074U);
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x00008887U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_ClientRandom[0];
            SCE->REG_100H = InData_ClientRandom[1];
            SCE->REG_100H = InData_ClientRandom[2];
            SCE->REG_100H = InData_ClientRandom[3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_ClientRandom[4];
            SCE->REG_100H = InData_ClientRandom[5];
            SCE->REG_100H = InData_ClientRandom[6];
            SCE->REG_100H = InData_ClientRandom[7];
            SCE->REG_ECH = 0x0000b460U;
            SCE->REG_ECH = 0x0000002cU;
            for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
            {
                SCE->REG_E0H = 0x80010020U;
                SCE->REG_00H = 0x00008207U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x01986c01U;
                SCE->REG_ECH = 0x00003c03U;
                SCE->REG_ECH = 0x00003401U;
                SCE->REG_ECH = 0x0000a460U;
                SCE->REG_ECH = 0x00000004U;
            }
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x00008887U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_ServerRandom[0];
            SCE->REG_100H = InData_ServerRandom[1];
            SCE->REG_100H = InData_ServerRandom[2];
            SCE->REG_100H = InData_ServerRandom[3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_ServerRandom[4];
            SCE->REG_100H = InData_ServerRandom[5];
            SCE->REG_100H = InData_ServerRandom[6];
            SCE->REG_100H = InData_ServerRandom[7];
            for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
            {
                SCE->REG_E0H = 0x80010020U;
                SCE->REG_00H = 0x00008207U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x01986c01U;
                SCE->REG_ECH = 0x00003c03U;
                SCE->REG_ECH = 0x00003401U;
                SCE->REG_ECH = 0x0000a460U;
                SCE->REG_ECH = 0x00000004U;
            }
            SCE->REG_ECH = 0x00186c00U;
            SCE->REG_ECH = 0x00003c03U;
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000001U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x0000098cU;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000004dU;
            R_SCE_func101(0x3d4bddc9U, 0x4907b8edU, 0x4d1aac9bU, 0xd5d1d31fU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0xf3a8894bU, 0xe4099076U, 0x50fcf137U, 0x1d3454aaU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_E0H = 0x8188000cU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x0000001bU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000098cU;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x00000020U;
            R_SCE_func101(0xf90914feU, 0x15cd84e8U, 0x21da8135U, 0x3a872e56U);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0xbf2c6705U, 0x5b3fcc9cU, 0xbb0c385aU, 0xa342a75bU);
            R_SCE_TlsGenerateSubSub();

            R_SCE_func100(0x624ad8c6U, 0xcd3be473U, 0x2cd1d6aeU, 0xc1048fb8U);
            SCE->REG_E0H = 0x8184000cU;
            SCE->REG_00H = 0x00003813U;
            SCE->REG_2CH = 0x0000009bU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00003013U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x808c0001U;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x0000002bU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008313U;
            SCE->REG_2CH = 0x000000abU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00000313U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_100H = change_endian_long(0x00000034U);
            R_SCE_func101(0xeac6002eU, 0x93a16f34U, 0xc899ec90U, 0x796688ebU);
            R_SCE_func059();
            SCE->REG_E0H = 0x81040000U;
            SCE->REG_C4H = 0x00060805U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x0126a005U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000031U);
            R_SCE_func101(0x089a1575U, 0xf103978eU, 0x238910caU, 0x335dacd5U);
            R_SCE_func044();
            R_SCE_func100(0x57721ee9U, 0xb6fae5aaU, 0x0eea3d29U, 0x4e4713d6U);
            SCE->REG_D0H = 0x40000200U;
            SCE->REG_C4H = 0x02e087b7U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x818c0001U;
            SCE->REG_00H = 0x00002833U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000232U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MasterSecret[4] = SCE->REG_100H;
            OutData_MasterSecret[5] = SCE->REG_100H;
            OutData_MasterSecret[6] = SCE->REG_100H;
            OutData_MasterSecret[7] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MasterSecret[8] = SCE->REG_100H;
            OutData_MasterSecret[9] = SCE->REG_100H;
            OutData_MasterSecret[10] = SCE->REG_100H;
            OutData_MasterSecret[11] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MasterSecret[12] = SCE->REG_100H;
            OutData_MasterSecret[13] = SCE->REG_100H;
            OutData_MasterSecret[14] = SCE->REG_100H;
            OutData_MasterSecret[15] = SCE->REG_100H;
            R_SCE_func100(0x3f81dce8U, 0xe87679adU, 0x5e6fd517U, 0x62abf1f8U);
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
            OutData_MasterSecret[16] = SCE->REG_100H;
            OutData_MasterSecret[17] = SCE->REG_100H;
            OutData_MasterSecret[18] = SCE->REG_100H;
            OutData_MasterSecret[19] = SCE->REG_100H;
            R_SCE_func100(0x49800391U, 0x598cfbd0U, 0xba5fc2c3U, 0x2c894fb8U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_04H = 0x00000212U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MasterSecret[0] = SCE->REG_100H;
            OutData_MasterSecret[1] = SCE->REG_100H;
            OutData_MasterSecret[2] = SCE->REG_100H;
            OutData_MasterSecret[3] = SCE->REG_100H;
            R_SCE_func102(0x4e33abb3U, 0x20035c03U, 0xc225e7d4U, 0xbeeeb324U);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe4_r3.prc
***********************************************************************************************************************/
