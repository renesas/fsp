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

fsp_err_t R_SCE_AesKeyUnwrapSub(uint32_t *InData_KeyType, uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t KEY_INDEX_SIZE, uint32_t *InData_WrappedKeyType, uint32_t *InData_Text, uint32_t WRAPPED_KEY_SIZE, uint32_t *OutData_KeyIndex)
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
    if (0x0U != (SCE->REG_1B4H & 0x1dU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00009002U;
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
    SCE->REG_104H = 0x00000268U;
    SCE->REG_E0H = 0x80030100U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_WrappedKeyType[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x00003409U;
    SCE->REG_ECH = 0x3420a900U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x1000d3e0U;
    SCE->REG_ECH = 0x38008940U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008940U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x013b1e01U, 0x3ed91013U, 0x75cef122U, 0x686111b4U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x701f15e6U, 0x1c0eaf89U, 0xaeaff00eU, 0xad21bf66U);
        SCE->REG_1B4H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_ECH = 0x38000d08U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0x350fc5c3U, 0xc528af97U, 0xd3652a67U, 0x387556f5U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000d4aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0xac414127U, 0x5c826013U, 0x59885dccU, 0x305a35f5U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x800100e0U;
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
                SCE->REG_100H = change_endian_long(0x00000090U);
                R_SCE_func101(0x9a649d4aU, 0x7d38bb48U, 0x84abb158U, 0x7d1ff96cU);
                R_SCE_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000005U;
                R_SCE_func101(0x255b8a49U, 0x35655738U, 0x6a540c00U, 0x701eaec7U);
            }
            else
            {
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
                SCE->REG_100H = change_endian_long(0x00000090U);
                R_SCE_func101(0xb13aede3U, 0x8b1ab543U, 0x62497669U, 0xe968f992U);
                R_SCE_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x2a46c04bU;
                R_SCE_func101(0xcec6b20bU, 0x27fe62a1U, 0x0e58bb77U, 0x36b3f68eU);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000090U);
            R_SCE_func101(0x21ca5987U, 0x967db75cU, 0x24a7de57U, 0x48dd3feaU);
            R_SCE_func044();
            R_SCE_func100(0x41b5fa12U, 0x1752068eU, 0xb987c905U, 0x83248635U);
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            SCE->REG_100H = InData_KeyIndex[2];
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_A4H = 0x00080805U;
            SCE->REG_00H = 0x00001213U;
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
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_B0H = 0x00000000U;
            R_SCE_func101(0x6153243dU, 0x1a3a6645U, 0xe9c0a3e7U, 0x8b5092d6U);
        }
        else
        {
            SCE->REG_ECH = 0x38000d4aU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0xa71fb63fU, 0xfaae8da0U, 0xba82cba4U, 0x3f705ee6U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x800100e0U;
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
                SCE->REG_100H = change_endian_long(0x0000004bU);
                R_SCE_func101(0xbbc1a3ffU, 0xde68b0d2U, 0x56e701b8U, 0x271de72aU);
                R_SCE_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000007U;
                R_SCE_func101(0x502b9941U, 0xba6abd1aU, 0x3e89b84aU, 0x5c0ca06aU);
            }
            else
            {
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
                SCE->REG_100H = change_endian_long(0x0000004bU);
                R_SCE_func101(0x56c60799U, 0x157a19afU, 0x443ea058U, 0x9cb6521aU);
                R_SCE_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x85d04999U;
                R_SCE_func101(0x90c124aeU, 0x0e14c73bU, 0x3d8b606dU, 0xa5b520e2U);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000004bU);
            R_SCE_func101(0xe219faa4U, 0xfa424404U, 0x6e59d37fU, 0xfe0d892cU);
            R_SCE_func044();
            R_SCE_func100(0x1dbcaba0U, 0x9ed5fd0dU, 0x5ab891b4U, 0x7d13d03fU);
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
            SCE->REG_A4H = 0x00080805U;
            SCE->REG_00H = 0x00001213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0xee080bc6U, 0xb8f87a13U, 0x080634dfU, 0x5a646b43U);
            SCE->REG_A4H = 0x00090805U;
            SCE->REG_00H = 0x00001213U;
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
            SCE->REG_B0H = 0x40000000U;
            R_SCE_func101(0x50b8629fU, 0x77898abcU, 0x52887e66U, 0x26d40cd1U);
        }
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x1897c744U, 0xa689db7cU, 0x4ce07427U, 0x65c6c3aaU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x2f7fd432U, 0x588a652eU, 0x58538107U, 0x4b50f35aU);
            SCE->REG_1B4H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            R_SCE_func030();
            SCE->REG_ECH = 0x00002ca0U;
            SCE->REG_ECH = 0x00003500U;
            SCE->REG_ECH = 0x000035c7U;
            SCE->REG_104H = 0x00000168U;
            SCE->REG_E0H = 0x80020000U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[1];
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000008U;
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x00002fc0U;
            SCE->REG_ECH = 0x0000b780U;
            SCE->REG_ECH = 0x00000008U;
            for(iLoop = 2; iLoop < WRAPPED_KEY_SIZE; iLoop = iLoop + 2)
            {
                SCE->REG_104H = 0x00000168U;
                SCE->REG_E0H = 0x8082001fU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop + 0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+1 + 0];
                SCE->REG_ECH = 0x000027fcU;
                SCE->REG_ECH = 0x00002fc0U;
                R_SCE_func101(0x1f3e6773U, 0x8a5e4aabU, 0xea325d29U, 0x14f8aa6eU);
            }
            SCE->REG_ECH = 0x38000bc5U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_1CH = 0x00402000U;
            SCE->REG_ECH = 0x0000377fU;
            SCE->REG_ECH = 0x0000ab60U;
            SCE->REG_ECH = 0x00000008U;
            SCE->REG_ECH = 0x00003785U;
            SCE->REG_ECH = 0x00003380U;
            SCE->REG_ECH = 0x0000349cU;
            SCE->REG_ECH = 0x00026c84U;
            SCE->REG_ECH = 0x00016f9cU;
            SCE->REG_ECH = 0x0000249cU;
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x0000b720U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x0000b740U;
            SCE->REG_ECH = 0x0000000cU;
            SCE->REG_ECH = 0x00003785U;
            SCE->REG_ECH = 0x00003380U;
            for(jLoop = 5; jLoop >= 0; jLoop = jLoop - 1)
            {
                SCE->REG_ECH = 0x000037fbU;
                SCE->REG_ECH = 0x00000bbdU;
                for(iLoop = (WRAPPED_KEY_SIZE/2)-1; iLoop >= 1; iLoop = iLoop - 1)
                {
                    SCE->REG_ECH = 0x00000824U;
                    SCE->REG_A4H = 0x0000ca85U;
                    SCE->REG_E0H = 0x81020000U;
                    SCE->REG_00H = 0x0000180bU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_E0H = 0x8182001fU;
                    SCE->REG_00H = 0x0000180bU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_E0H = 0x80040000U;
                    SCE->REG_00H = 0x00008113U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_ECH = 0x00003c5fU;
                    SCE->REG_ECH = 0x000027f9U;
                    SCE->REG_ECH = 0x00003c7fU;
                    SCE->REG_ECH = 0x00002bfaU;
                    SCE->REG_ECH = 0x00003080U;
                    SCE->REG_ECH = 0x00002fa0U;
                    R_SCE_func101(0xe41fab11U, 0x74336dbcU, 0x3c5d2ab1U, 0xc41c71ccU);
                }
                SCE->REG_ECH = 0x38000bbcU;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_ECH = 0x00002fc0U;
                R_SCE_func101(0x1ba8af0eU, 0xa0dc1032U, 0xdd5f8bd1U, 0xe8448a27U);
            }
            SCE->REG_ECH = 0x38008bc0U;
            SCE->REG_ECH = 0x00000006U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_1CH = 0x00402000U;
            SCE->REG_ECH = 0x38008800U;
            SCE->REG_ECH = 0xa6a6a6a6U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x38008820U;
            SCE->REG_ECH = 0xa6a6a6a6U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            R_SCE_func100(0x17c48646U, 0x82b08a4fU, 0xb4bda1a7U, 0x7e148723U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0xc77afd82U, 0x7161196aU, 0xaa804308U, 0xda5e3562U);
                SCE->REG_1B4H = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                R_SCE_func100(0x149ee113U, 0xe1ddeffaU, 0x5930b8cdU, 0x3620afe7U);
                SCE->REG_ECH = 0x00003408U;
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
                SCE->REG_ECH = 0x000034e0U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x0000004cU);
                R_SCE_func101(0xb1032f26U, 0x2c69b53fU, 0x8475208fU, 0xf248f615U);
                R_SCE_func043();
                SCE->REG_ECH = 0x000034e6U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x0000004cU);
                R_SCE_func101(0xc581f586U, 0xaa698625U, 0xc0c8e6f5U, 0xa141aee6U);
                R_SCE_func044();
                SCE->REG_ECH = 0x000034eeU;
                SCE->REG_ECH = 0x0000b7e0U;
                SCE->REG_ECH = 0x00000008U;
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00040804U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00050804U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_ECH = 0x00000bdeU;
                SCE->REG_ECH = 0x0000b760U;
                SCE->REG_ECH = 0x00000004U;
                SCE->REG_ECH = 0x0000b780U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_ECH = 0x0000a8e0U;
                SCE->REG_ECH = 0x00000005U;
                for(iLoop = 0; iLoop < KEY_INDEX_SIZE-5; iLoop = iLoop + 4)
                {
                    SCE->REG_ECH = 0x000008c6U;
                    SCE->REG_ECH = 0x34202bc7U;
                    SCE->REG_ECH = 0x2000d0c0U;
                    SCE->REG_ECH = 0x00007c06U;
                    SCE->REG_1CH = 0x00602000U;
                    R_SCE_func100(0xcc519213U, 0xdb736583U, 0x5afe0b62U, 0x207b921dU);
                    SCE->REG_104H = 0x00000362U;
                    SCE->REG_D0H = 0x40000000U;
                    SCE->REG_C4H = 0x00e087b5U;
                    SCE->REG_E0H = 0x8184001fU;
                    SCE->REG_00H = 0x00002813U;
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
                    OutData_KeyIndex[iLoop+1 + 0] = SCE->REG_100H;
                    OutData_KeyIndex[iLoop+1 + 1] = SCE->REG_100H;
                    OutData_KeyIndex[iLoop+1 + 2] = SCE->REG_100H;
                    OutData_KeyIndex[iLoop+1 + 3] = SCE->REG_100H;
                    SCE->REG_ECH = 0x000027fcU;
                    SCE->REG_ECH = 0x000027dbU;
                    R_SCE_func101(0x093a652bU, 0xe1621c12U, 0x60276291U, 0xe177c523U);
                }
                SCE->REG_ECH = 0x38000bc7U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                R_SCE_func100(0x4a54fc7bU, 0xa99b26c7U, 0x80496a5cU, 0x41c6f607U);
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
                OutData_KeyIndex[iLoop+1 + 0] = SCE->REG_100H;
                OutData_KeyIndex[iLoop+1 + 1] = SCE->REG_100H;
                OutData_KeyIndex[iLoop+1 + 2] = SCE->REG_100H;
                OutData_KeyIndex[iLoop+1 + 3] = SCE->REG_100H;
                R_SCE_func100(0x73c5eeb4U, 0x34c7700fU, 0x5c343d34U, 0x87b2e576U);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[0] = SCE->REG_100H;
                R_SCE_func102(0x91c710f0U, 0x2a68a69eU, 0x7725a9d4U, 0x9f728aa7U);
                SCE->REG_1B4H = 0x00000040U;
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p90.prc
***********************************************************************************************************************/
