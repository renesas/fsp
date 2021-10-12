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

fsp_err_t R_SCE_TlsGenerateSessionKeySub(uint32_t *InData_Sel_CipherSuite, uint32_t *InData_MasterSecret, uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *InData_NonceExplicit, uint32_t *OutData_ClientMACKeyOperationCode, uint32_t *OutData_ServerMACKeyOperationCode, uint32_t *OutData_ClientEncKeyOperationCode, uint32_t *OutData_ServerEncKeyOperationCode, uint32_t OutLen)
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
    (void)OutLen;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000e502U;
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
    SCE->REG_ECH = 0x00003780U;
    SCE->REG_ECH = 0x3420ab80U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xc5c85654U, 0xa9db5f32U, 0x435cb747U, 0x1a20ca94U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x0a565757U, 0xacf7c9fbU, 0x072b0c01U, 0xc50361efU);
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
        SCE->REG_100H = InData_MasterSecret[0];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[1];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[2];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[3];
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e5U);
        R_SCE_func101(0x693dfb95U, 0x2a2cf8efU, 0x9162fb7eU, 0xea58c30cU);
        R_SCE_func059();
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0126a005U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800103a0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e5U);
        R_SCE_func101(0x66f5e0c2U, 0x302fd292U, 0x58e59ad7U, 0x2b5b05c2U);
        R_SCE_func044();
        SCE->REG_104H = 0x00000b62U;
        SCE->REG_D0H = 0x40000200U;
        SCE->REG_C4H = 0x02f087b7U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[4];
        SCE->REG_100H = InData_MasterSecret[5];
        SCE->REG_100H = InData_MasterSecret[6];
        SCE->REG_100H = InData_MasterSecret[7];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[8];
        SCE->REG_100H = InData_MasterSecret[9];
        SCE->REG_100H = InData_MasterSecret[10];
        SCE->REG_100H = InData_MasterSecret[11];
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MasterSecret[12];
        SCE->REG_100H = InData_MasterSecret[13];
        SCE->REG_100H = InData_MasterSecret[14];
        SCE->REG_100H = InData_MasterSecret[15];
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
        SCE->REG_100H = InData_MasterSecret[16];
        SCE->REG_100H = InData_MasterSecret[17];
        SCE->REG_100H = InData_MasterSecret[18];
        SCE->REG_100H = InData_MasterSecret[19];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xf6dfe02bU, 0x5af8207fU, 0xc7da0cdfU, 0x7c648670U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x310753efU, 0x66c22afbU, 0x98df016cU, 0xf138b2c2U);
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
            SCE->REG_104H = 0x00000352U;
            SCE->REG_C4H = 0x00000885U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x6b657920U);
            SCE->REG_100H = change_endian_long(0x65787061U);
            SCE->REG_100H = change_endian_long(0x6e73696fU);
            SCE->REG_100H = change_endian_long(0x6e000000U);
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
            SCE->REG_100H = change_endian_long(0x0000006eU);
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
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x0000098cU;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000004dU;
            R_SCE_func101(0x500c38e6U, 0x336b8577U, 0x8202e518U, 0x1a11adf5U);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0x7ca5e69fU, 0x3de93ad2U, 0x147ee0c8U, 0x727f46deU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_E0H = 0x8188000cU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x0000009aU;
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
            R_SCE_func101(0xf21255d9U, 0x5ffa1986U, 0x4eb30f51U, 0x6def656cU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0x31489cecU, 0x37009fe9U, 0x94adfb4dU, 0x4b37ceddU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_E0H = 0x8188000cU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x0000001aU;
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
            R_SCE_func101(0x46076dccU, 0xebf31dbbU, 0x023519aeU, 0x4f0c235bU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0x8c06dba9U, 0xa77d01e6U, 0xf881d70bU, 0xbe126888U);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_E0H = 0x8188000cU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000092U;
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
            R_SCE_func101(0x6461b7e1U, 0x0445b7a9U, 0x33f8057fU, 0x3e5a02fdU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000b580U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000006dU;
            R_SCE_func101(0x4e633f25U, 0x47057a44U, 0xd5f4cd49U, 0x7ea85623U);
            R_SCE_TlsGenerateSubSub();

            R_SCE_func100(0x74da32dcU, 0xe0fb5941U, 0x4a5d3c00U, 0x1917c9cbU);
            SCE->REG_E0H = 0x8188000cU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_ECH = 0x000034dcU;
            SCE->REG_ECH = 0x3420ab80U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x2000b4c0U;
            SCE->REG_ECH = 0x00000002U;
            SCE->REG_ECH = 0x3420ab80U;
            SCE->REG_ECH = 0x00000006U;
            SCE->REG_ECH = 0x2000b4c0U;
            SCE->REG_ECH = 0x00000006U;
            SCE->REG_ECH = 0x00007c06U;
            SCE->REG_1CH = 0x00600000U;
            SCE->REG_1D0H = 0x00000000U;
            if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x5c75a1ecU, 0xe833c1c0U, 0xacaf6bf5U, 0xb84083acU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01032001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000035U);
                R_SCE_func101(0x7d54c0d8U, 0x49d729ccU, 0x526da749U, 0xafdc0687U);
                R_SCE_func059();
                R_SCE_func100(0xd6b7ab60U, 0x65358c2bU, 0x68dac91aU, 0xc9a2323aU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002317U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000200fU;
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
                OutData_ClientMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xf75ef456U, 0x846f86f0U, 0xf34299f9U, 0xfd6215afU);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00000c84U;
                SCE->REG_D0H = 0x40000000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
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
                OutData_ClientMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x61b563dfU, 0x2f4068dcU, 0xaabd49c2U, 0x72fbea90U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x04918999U, 0xa42af7a7U, 0xa56d8003U, 0xa1384909U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01031001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000036U);
                R_SCE_func101(0x02415da3U, 0x7d1673e8U, 0x823e459cU, 0x7c15244aU);
                R_SCE_func059();
                R_SCE_func100(0xc250fee7U, 0x61b45f06U, 0xafdb7209U, 0xffd6d721U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002317U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000200fU;
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
                OutData_ServerMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xa46b314eU, 0x6ebaac1bU, 0xb0edd9a2U, 0xc09b6329U);
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
                OutData_ServerMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x7c55225bU, 0x86367fe5U, 0x1f9d3bf4U, 0xede4ca3fU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x8cf75c6aU, 0xbf318fa6U, 0x1dd0dcebU, 0xe96bb683U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01008001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000037U);
                R_SCE_func101(0x2bbbefd3U, 0x2aa9effcU, 0xed2b49f6U, 0x62af13e6U);
                R_SCE_func059();
                R_SCE_func100(0xa6024b24U, 0xb3e84f66U, 0x11ddb7cbU, 0x41a42d0dU);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02e087b5U;
                SCE->REG_00H = 0x00002313U;
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
                OutData_ClientEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[7] = SCE->REG_100H;
                R_SCE_func100(0xe92a97b6U, 0xb7cd22f5U, 0x7b122ce3U, 0xdd5b1567U);
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
                OutData_ClientEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xafac3f38U, 0x67fda146U, 0xc96042feU, 0xe7ebc910U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x2287441cU, 0xcddaff0aU, 0x16dfaf9aU, 0xebb502a5U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01004001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000038U);
                R_SCE_func101(0x6d6c231cU, 0x4fbbd326U, 0x5587f15eU, 0xcdeab0efU);
                R_SCE_func059();
                R_SCE_func100(0xd071731eU, 0xef39ec2bU, 0x499fad0dU, 0x073e5346U);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02e087b5U;
                SCE->REG_00H = 0x00002313U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000033bU;
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
                OutData_ServerEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[7] = SCE->REG_100H;
                R_SCE_func100(0xf2d62f7fU, 0x850ce6b1U, 0x745d078fU, 0x4350bbb4U);
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
                OutData_ServerEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x7323a70cU, 0xd045a764U, 0x36b69fffU, 0x5d037d45U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func101(0xbd5bcbd8U, 0x56b4d7c0U, 0xd67bd56cU, 0xb4feafffU);
            }
            else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x693fb073U, 0x7a17330aU, 0x40598b4aU, 0x8887dddeU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01032001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000039U);
                R_SCE_func101(0xbf69a5b0U, 0xdb9dd14cU, 0x42705909U, 0x9891f6d6U);
                R_SCE_func059();
                R_SCE_func100(0xfcafb0c4U, 0x4bd5c522U, 0xc6fe94afU, 0xeb8f47d9U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002317U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000200fU;
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
                OutData_ClientMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x75bc18bcU, 0xa1f515daU, 0xae684115U, 0x2245b246U);
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
                OutData_ClientMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xdcc19d27U, 0xed8f3d59U, 0xcbaaf91eU, 0xa26ced1eU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x6c7925a2U, 0xccf6c44cU, 0xd3f5ad54U, 0x2a7bf4bdU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01031001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000040U);
                R_SCE_func101(0xbd8a5b0cU, 0x6e236b7dU, 0x0ea57d11U, 0x50020e43U);
                R_SCE_func059();
                R_SCE_func100(0x57b9b39cU, 0xfff74f40U, 0x0008b02cU, 0x80d82a47U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002317U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000200fU;
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
                OutData_ServerMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xb46b547cU, 0xb242fa96U, 0x69c98beeU, 0xe3081c52U);
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
                OutData_ServerMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x09e3309aU, 0xe2330215U, 0xf48b8d42U, 0x1ab3f600U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x2cb6d424U, 0xcb926dbdU, 0x3dd58691U, 0x7515d0e5U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01018001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000041U);
                R_SCE_func101(0xcba11f7bU, 0x8914d9d7U, 0x5c5462f4U, 0xb1843fbfU);
                R_SCE_func059();
                R_SCE_func100(0x02746de3U, 0x3c6f5224U, 0x0824317dU, 0xe4245f12U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
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
                OutData_ClientEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x8d924761U, 0x1c50acf5U, 0x6b00e4dfU, 0xcaa9eb8cU);
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
                OutData_ClientEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x3d07116aU, 0x30d55e07U, 0x3d86bf9cU, 0x5dc44cb4U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0xc431f37fU, 0xcbdbb664U, 0xff7c51d4U, 0x40170aacU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01014001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000042U);
                R_SCE_func101(0xf160e1e9U, 0x82775694U, 0xd14edbe2U, 0x916fe4f6U);
                R_SCE_func059();
                R_SCE_func100(0x698c2423U, 0x9aed4762U, 0x4f97d4a9U, 0x2079da9cU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000031bU;
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
                OutData_ServerEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xc57ee13cU, 0x4c8a0750U, 0xf06c587bU, 0x3f6a0be8U);
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
                OutData_ServerEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x8ec268e6U, 0x6e2bcc4dU, 0x40fa4c4eU, 0xf0f5c92cU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func101(0x2562d957U, 0xf6276487U, 0x6c2e4f9bU, 0x4a97c281U);
            }
            else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x30e9b085U, 0xfa0c07c3U, 0x32806bd5U, 0x534179e4U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01022001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000043U);
                R_SCE_func101(0x843e57cfU, 0x5e51ba7fU, 0x16207549U, 0x55a94cc0U);
                R_SCE_func059();
                R_SCE_func100(0xe0c00ca2U, 0x3e9eef70U, 0x9077e269U, 0xef4323f2U);
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
                OutData_ClientMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x75e57ad6U, 0x78c42cceU, 0xdcdc4ee6U, 0x26b88322U);
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
                OutData_ClientMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x74332081U, 0x2e5bca18U, 0xdbf88913U, 0xf6e7dcb4U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x19fad6aeU, 0x2d215e19U, 0x53b433aeU, 0x579279ffU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01021001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000044U);
                R_SCE_func101(0x74066268U, 0xbc6f0e9fU, 0x76a400bbU, 0x2743f156U);
                R_SCE_func059();
                R_SCE_func100(0x3189e954U, 0xaa8978f2U, 0xe331348cU, 0xa2111302U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
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
                OutData_ServerMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xf35c3a41U, 0x13b43483U, 0x70f0ee73U, 0x6e1b4665U);
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
                OutData_ServerMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x01cc1996U, 0x89e39590U, 0x68420704U, 0x46b54ba3U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x5a2cbfb3U, 0x9b461dbcU, 0xb8931a2aU, 0x3fcb5587U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01008001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000045U);
                R_SCE_func101(0x307aa78cU, 0xcd89b52eU, 0xc61ddc1dU, 0x34e6f076U);
                R_SCE_func059();
                R_SCE_func100(0xf19277deU, 0xf5193cb0U, 0xe2f64477U, 0xb399bc5bU);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02e087b5U;
                SCE->REG_00H = 0x00002313U;
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
                OutData_ClientEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[7] = SCE->REG_100H;
                R_SCE_func100(0xa871e7f1U, 0xe54220eeU, 0x2ba25dd9U, 0xe421a210U);
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
                OutData_ClientEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xcc9983faU, 0x7642fe8eU, 0x82f52172U, 0x8a2ca89aU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x00652492U, 0xbb2e38bbU, 0x7b934bd6U, 0xa9fd0800U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01004001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000046U);
                R_SCE_func101(0x6c30233bU, 0x33e0e721U, 0x6c9d661cU, 0x83ddd9c8U);
                R_SCE_func059();
                R_SCE_func100(0x0fd9ab7eU, 0x039c70c8U, 0x8eee4a00U, 0xf28da9e2U);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02e087b5U;
                SCE->REG_00H = 0x00002313U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x00000323U;
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
                OutData_ServerEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[7] = SCE->REG_100H;
                R_SCE_func100(0x7cbae145U, 0xab9d57e3U, 0xad7800baU, 0x1af5760cU);
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
                OutData_ServerEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x905b14d3U, 0xe1ea9e39U, 0x53a09e10U, 0xeda857b0U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func101(0xa36fc5b6U, 0x4135b001U, 0x013006bbU, 0x7f76b0d1U);
            }
            else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x5396cd59U, 0xdae9e557U, 0x381105bbU, 0x5aa2f64dU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01022001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000047U);
                R_SCE_func101(0x391f2b72U, 0x604c828eU, 0xf02151fcU, 0xb6f57c6eU);
                R_SCE_func059();
                R_SCE_func100(0x6a995976U, 0x1e17ac48U, 0xa362ceaeU, 0x2b99a636U);
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
                OutData_ClientMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x2528ed6aU, 0xee5508efU, 0x041256d4U, 0x135e931bU);
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
                OutData_ClientMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0x2611fb28U, 0x7120c9b9U, 0x3ff28142U, 0x5ab80dc5U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x2ad1ea05U, 0xfeb9daccU, 0xfa7d8258U, 0x313d7b50U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01021001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000048U);
                R_SCE_func101(0xa052679eU, 0xc9463cadU, 0x7a7723c0U, 0x571da606U);
                R_SCE_func059();
                R_SCE_func100(0xe4a6b9e8U, 0x2a75331eU, 0x381cf253U, 0xc5fcdda5U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
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
                OutData_ServerMACKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xf82fda1cU, 0x2ab810f2U, 0x17e97920U, 0xf43fdacfU);
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
                OutData_ServerMACKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerMACKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xa03077c9U, 0xb4731ef0U, 0x4b2af05dU, 0x5ba751afU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerMACKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0xeeaefe4bU, 0x05de1213U, 0xe0541d32U, 0x1f4334d1U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01018001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000049U);
                R_SCE_func101(0x531ce644U, 0x3120efd0U, 0x40cfb4f0U, 0xc69c081cU);
                R_SCE_func059();
                R_SCE_func100(0x401cdeedU, 0xc8e159a6U, 0xce061e5aU, 0xd03b6ee4U);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
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
                OutData_ClientEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xe340e384U, 0xffa4f2fdU, 0xf0700e76U, 0x262e1e15U);
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
                OutData_ClientEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xfa48895fU, 0x4a72598bU, 0xa8379cf0U, 0x09aa09e2U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0xf385c1a9U, 0x693ecd43U, 0x7a4b1563U, 0x1806c4adU);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01014001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000050U);
                R_SCE_func101(0xbd549649U, 0x68718587U, 0xd9dee92dU, 0x6d7b4a07U);
                R_SCE_func059();
                R_SCE_func100(0x76cda59bU, 0xa9d4ec46U, 0xed7c6ddcU, 0x29ae654aU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_00H = 0x00002323U;
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
                OutData_ServerEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xd8a6c459U, 0x9f202e30U, 0x90d41d36U, 0xc37f6af4U);
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
                OutData_ServerEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xaa972a2dU, 0x4cdd43a0U, 0x3d4924e7U, 0xf0394f8cU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func101(0xdda209e2U, 0xb9558724U, 0x765e3d19U, 0x7dd04af1U);
            }
            else if (0x06000000U == (SCE->REG_1CH & 0xff000000U))
            {
                R_SCE_func100(0x9efee54dU, 0x0154eeaaU, 0xb09040e7U, 0x57f42b2eU);
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_00H = 0x00001313U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x00050805U;
                SCE->REG_00H = 0x00001313U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_E0H = 0x80010280U;
                SCE->REG_00H = 0x00008307U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_E0H = 0x800202a0U;
                SCE->REG_104H = 0x00000168U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_NonceExplicit[0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_NonceExplicit[1];
                SCE->REG_ECH = 0x0000b6e0U;
                SCE->REG_ECH = 0x00000001U;
                SCE->REG_E0H = 0x81040280U;
                SCE->REG_A4H = 0x00060805U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_E0H = 0x80010280U;
                SCE->REG_00H = 0x00008307U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000035bU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_E0H = 0x81040280U;
                SCE->REG_A4H = 0x00070805U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01128001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000051U);
                R_SCE_func101(0x8343eb18U, 0x67ebfa36U, 0xcf951dbeU, 0xf206e369U);
                R_SCE_func059();
                R_SCE_func100(0x0483d9bdU, 0xb29fdd54U, 0x6f4d8d56U, 0x221f70dbU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_104H = 0x00000151U;
                SCE->REG_A4H = 0x00000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_00H = 0x00002113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_00H = 0x00002113U;
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
                OutData_ClientEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0xba35a2e6U, 0xabc58c2eU, 0x039e6913U, 0x3ee9bb84U);
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
                OutData_ClientEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ClientEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xae3a749aU, 0xd06fb41dU, 0x144edc0eU, 0xa6263915U);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ClientEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func100(0x4b4792eaU, 0x672c493eU, 0xfaa4a3ddU, 0xd2692197U);
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x80010040U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x01124001U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80030060U;
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
                SCE->REG_ECH = 0x00003542U;
                SCE->REG_ECH = 0x00003563U;
                SCE->REG_ECH = 0x00003584U;
                SCE->REG_ECH = 0x000035a5U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000052U);
                R_SCE_func101(0x49e3ab69U, 0xf85e072aU, 0xc6a78f31U, 0x939f9ff3U);
                R_SCE_func059();
                R_SCE_func100(0xc7c69dc5U, 0x291d6a17U, 0xdec99feeU, 0x3011005eU);
                SCE->REG_D0H = 0x40000100U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_104H = 0x00000151U;
                SCE->REG_A4H = 0x00000cc4U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_00H = 0x00002113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x01000cc4U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_00H = 0x00002113U;
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
                OutData_ServerEncKeyOperationCode[4] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[5] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[6] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[7] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[8] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[9] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[10] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[11] = SCE->REG_100H;
                R_SCE_func100(0x28967aaeU, 0x417ee6d0U, 0x5060ac94U, 0x0d65555cU);
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
                OutData_ServerEncKeyOperationCode[12] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[13] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[14] = SCE->REG_100H;
                OutData_ServerEncKeyOperationCode[15] = SCE->REG_100H;
                R_SCE_func100(0xd215727cU, 0x737d6f68U, 0x0ef52161U, 0xee4bfe8aU);
                SCE->REG_E0H = 0x81040040U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_ServerEncKeyOperationCode[3] = SCE->REG_100H;
                R_SCE_func101(0x9c788226U, 0xfb2e64bfU, 0x06dd0c95U, 0x7eadb016U);
            }
            R_SCE_func102(0xc5005a6bU, 0x0b80a4d3U, 0x23fa6350U, 0xe5e04365U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe5_r2.prc
***********************************************************************************************************************/
