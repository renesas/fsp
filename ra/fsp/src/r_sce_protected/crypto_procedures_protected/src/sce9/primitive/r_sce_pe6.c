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

fsp_err_t R_SCE_TlsGenerateVerifyDataSub(uint32_t *InData_Sel_VerifyData, uint32_t *InData_MasterSecret, uint32_t *InData_HandShakeHash, uint32_t *OutData_VerifyData)
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
    SCE->REG_84H = 0x0000e602U;
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
    SCE->REG_E0H = 0x80010380U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Sel_VerifyData[0];
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x000037fcU;
    SCE->REG_ECH = 0x00008fe0U;
    SCE->REG_ECH = 0xfffffffeU;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x1000d3c0U;
    SCE->REG_ECH = 0x38008bc0U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x42725bd9U, 0xd68ae495U, 0x2874ceebU, 0x5b1e6c80U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x7f43f836U, 0xaa211e9bU, 0xb77495f6U, 0xa5a2b98dU);
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
        SCE->REG_100H = change_endian_long(0x000000e6U);
        R_SCE_func101(0x226b73c7U, 0x6e4f30a7U, 0x3a9fe8e5U, 0x1f38e4ddU);
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
        SCE->REG_100H = change_endian_long(0x000000e6U);
        R_SCE_func101(0xace0c4fdU, 0x95aa2c99U, 0xbd2ed299U, 0xdcce1864U);
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
        R_SCE_func100(0xf50dc336U, 0x77e3b0d6U, 0x3753e3e0U, 0xbdade766U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xc1049c42U, 0x49cd3d25U, 0xe56c91a5U, 0x6a15e7f5U);
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
            SCE->REG_ECH = 0x000037fcU;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x0000000fU;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0xe1ef5191U, 0x4ff7f391U, 0x79e6aff9U, 0xf7c9687eU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000352U;
                SCE->REG_C4H = 0x00000885U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x636c6965U);
                SCE->REG_100H = change_endian_long(0x6e742066U);
                SCE->REG_100H = change_endian_long(0x696e6973U);
                SCE->REG_100H = change_endian_long(0x68656400U);
                R_SCE_func101(0xfe4b107bU, 0xb8b23584U, 0xa1dcf904U, 0x9e8f01f1U);
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
                SCE->REG_100H = change_endian_long(0x73657276U);
                SCE->REG_100H = change_endian_long(0x65722066U);
                SCE->REG_100H = change_endian_long(0x696e6973U);
                SCE->REG_100H = change_endian_long(0x68656400U);
                R_SCE_func101(0x4b65d6d9U, 0xf7938205U, 0x07b72bc6U, 0x8c5214c3U);
            }
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_E0H = 0x80830001U;
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
            SCE->REG_100H = change_endian_long(0x00686564U);
            SCE->REG_104H = 0x00000762U;
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x00008887U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_HandShakeHash[0];
            SCE->REG_100H = InData_HandShakeHash[1];
            SCE->REG_100H = InData_HandShakeHash[2];
            SCE->REG_100H = InData_HandShakeHash[3];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_HandShakeHash[4];
            SCE->REG_100H = InData_HandShakeHash[5];
            SCE->REG_100H = InData_HandShakeHash[6];
            SCE->REG_100H = InData_HandShakeHash[7];
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
                SCE->REG_ECH = 0x01886c01U;
                SCE->REG_ECH = 0x00003c03U;
                SCE->REG_ECH = 0x00003401U;
                SCE->REG_ECH = 0x0000a460U;
                SCE->REG_ECH = 0x00000004U;
            }
            SCE->REG_ECH = 0x00086c00U;
            SCE->REG_ECH = 0x00003c03U;
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_ECH = 0x0000098cU;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000002fU;
            R_SCE_func101(0xb8a4becfU, 0x6a533f04U, 0x9e503e67U, 0x3cacdd1cU);
            R_SCE_TlsGenerateSubSub();

            SCE->REG_ECH = 0x00002c20U;
            SCE->REG_ECH = 0x0000096bU;
            SCE->REG_ECH = 0x0000098cU;
            SCE->REG_ECH = 0x0000b5c0U;
            SCE->REG_ECH = 0x0000004fU;
            R_SCE_func101(0x64443922U, 0xc413a4a1U, 0x3fd447ffU, 0xd7d7c2acU);
            R_SCE_TlsGenerateSubSub();

            R_SCE_func100(0x51686b98U, 0xc07a2829U, 0x23472153U, 0x1333cb0dU);
            SCE->REG_C4H = 0x00000885U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x81830001U;
            SCE->REG_00H = 0x0000280fU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00002007U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x0000020eU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_VerifyData[0] = SCE->REG_100H;
            OutData_VerifyData[1] = SCE->REG_100H;
            OutData_VerifyData[2] = SCE->REG_100H;
            SCE->REG_00H = 0x00000207U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func102(0x936f2936U, 0x95c646a6U, 0x5eb5daebU, 0xc3c5c83eU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe6_r2.prc
***********************************************************************************************************************/
