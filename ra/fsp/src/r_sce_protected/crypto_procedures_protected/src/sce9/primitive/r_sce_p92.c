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

fsp_err_t R_SCE_SelfCheck3Sub(void)
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
    SCE->REG_84H = 0x00009203U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000001f0U;
    SCE->REG_ECH = 0x00003bfeU;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x8a681df7U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xbc62f8eeU, 0xf60c8b68U, 0xacc557c3U, 0xe1c5ea3fU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00093b8cU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01c7ba56U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00070804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_ECH = 0x3000a820U;
        SCE->REG_ECH = 0x00000003U;
        SCE->REG_ECH = 0x00010020U;
        SCE->REG_ECH = 0x00000821U;
        SCE->REG_ECH = 0x00000080U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00002008U;
        SCE->REG_ECH = 0x00000863U;
        SCE->REG_ECH = 0x00000884U;
        SCE->REG_ECH = 0x000008a5U;
        SCE->REG_ECH = 0x0000b4c0U;
        SCE->REG_ECH = 0x00000013U;
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x00000348U;
        SCE->REG_ECH = 0x0000b500U;
        SCE->REG_ECH = 0x000000b7U;
        for(jLoop = 0; jLoop < 1; jLoop = jLoop + 1)
        {
            R_SCE_func100(0xd85048b3U, 0x472af28dU, 0x35179f10U, 0x25a5e550U);
            SCE->REG_ECH = 0x00007c01U;
            SCE->REG_1CH = 0x00600000U;
            SCE->REG_1D0H = 0x00000000U;
            if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
            {
                /* WAIT_LOOP */
                while (0U != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901cU;
                R_SCE_func101(0xf6774c41U, 0x8a1dd359U, 0xd8e1be85U, 0x2ed06095U);
            }
            else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
            {
                /* WAIT_LOOP */
                while (0U != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901eU;
                R_SCE_func101(0x3a523fceU, 0x1f9b5c85U, 0x5c13d0d3U, 0x255c00c8U);
            }
            else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
            {
                /* WAIT_LOOP */
                while (0U != SCE->REG_64H_b.B11)
                {
                    /* waiting */
                }
                SCE->REG_64H = 0x0020901dU;
                R_SCE_func101(0x83274642U, 0xaee9de82U, 0x46dfb756U, 0x5b9db442U);
            }
            SCE->REG_C4H = 0x41001e5eU;
            SCE->REG_00H = 0x80002401U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001200U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B30)
            {
                /* waiting */
            }
            SCE->REG_00H = 0x00000001U;
            SCE->REG_C4H = 0x00000000U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0010B008U;
            SCE->REG_ECH = 0x00000800U;
            SCE->REG_E0H = 0x80900000U;
            SCE->REG_00H = 0x00008443U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x000038a0U;
            SCE->REG_ECH = 0x00003405U;
            SCE->REG_ECH = 0x00002804U;
            SCE->REG_ECH = 0x342028e0U;
            SCE->REG_ECH = 0x10005066U;
            SCE->REG_ECH = 0x34202808U;
            SCE->REG_ECH = 0x10005066U;
            SCE->REG_ECH = 0x00003485U;
            R_SCE_func101(0x89a92a87U, 0x829fdab7U, 0x3373183eU, 0x17a9a49dU);
        }
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x0000005AU;
        SCE->REG_ECH = 0x00000842U;
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x0000b4a0U;
        SCE->REG_ECH = 0x00000002U;
        for(iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003804U;
            SCE->REG_ECH = 0x342028e0U;
            SCE->REG_ECH = 0x10005066U;
            SCE->REG_ECH = 0x00002440U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_ECH = 0x00002485U;
        }
        SCE->REG_ECH = 0x00002c20U;
        SCE->REG_ECH = 0x38008840U;
        SCE->REG_ECH = 0x00000100U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_1CH = 0x00402000U;
        SCE->REG_ECH = 0x0000b4e0U;
        SCE->REG_ECH = 0x00000033U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x0000003cU;
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x00002cc0U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x0000003eU;
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x342028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x38008860U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0xb0599c44U, 0xa004f708U, 0xb622fb4bU, 0x26ebcfa1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x5befaa57U, 0xb61fc722U, 0xe545fd8fU, 0x40e2a67cU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_RETRY;
        }
        else
        {
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0000001cU;
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000cc4U;
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
            SCE->REG_C4H = 0x41001eddU;
            SCE->REG_00H = 0x00002413U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x00000000U;
            SCE->REG_E0H = 0x80040080U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0x601c5c9eU, 0x36c5cc20U, 0xe9624f37U, 0xe1ab5fcfU);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x000b0804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000352U;
            SCE->REG_C4H = 0x00070805U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000001U);
            R_SCE_func100(0xc5c449c3U, 0x2addf698U, 0x2450f511U, 0xa2488d64U);
            SCE->REG_D0H = 0x00000100U;
            SCE->REG_C4H = 0x0100b7f7U;
            SCE->REG_E0H = 0x81080000U;
            SCE->REG_00H = 0x00002823U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_C4H = 0x000b0805U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_C4H = 0x00070805U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0xbcd93370U, 0x7f78034aU, 0x704cbbdfU, 0xf752e923U);
            R_SCE_func103();
            R_SCE_func100(0x7cc92e49U, 0xefe795eeU, 0xb1bf9563U, 0x00aaf299U);
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x010d0c04U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            R_SCE_func100(0x68b792eeU, 0x7b995f71U, 0x995e79b3U, 0xe6982885U);
            R_SCE_func103();
            R_SCE_func100(0x49c5ae79U, 0x3fa4474cU, 0xa8ec11b5U, 0xbee69bb9U);
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
            S_RAM[24] = change_endian_long(SCE->REG_100H);
            S_RAM[25] = change_endian_long(SCE->REG_100H);
            S_RAM[26] = change_endian_long(SCE->REG_100H);
            S_RAM[27] = change_endian_long(SCE->REG_100H);
            SCE->REG_13CH = 0x00000202U;
            R_SCE_func102(0x977284d5U, 0x7758325cU, 0xec1cd437U, 0xcef3304cU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
    else
    {
        R_SCE_func100(0xd161ba91U, 0x5df63514U, 0xf9982d16U, 0xf6e4c2cfU);
        R_SCE_func103();
        R_SCE_func100(0x45b30ae4U, 0xa43436f8U, 0xb42bd4d9U, 0xd02d8034U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x695c8fa0U, 0x9988b18bU, 0xb8d9b454U, 0x21cbfb17U);
        R_SCE_func103();
        R_SCE_func100(0x1c3b2f77U, 0xbf895b6bU, 0x240da1cfU, 0x8856aea9U);
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
        S_RAM[24] = change_endian_long(SCE->REG_100H);
        S_RAM[25] = change_endian_long(SCE->REG_100H);
        S_RAM[26] = change_endian_long(SCE->REG_100H);
        S_RAM[27] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000202U;
        R_SCE_func102(0xf549d5d0U, 0x14c317c0U, 0x7f720bf8U, 0x61c94f96U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p92_r1.prc
***********************************************************************************************************************/
