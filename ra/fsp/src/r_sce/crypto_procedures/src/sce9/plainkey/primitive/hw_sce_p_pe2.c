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
 *         : 02.12.2020 1.01        Improved pefromance for secure boot.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce_if.h"
#include "hw_sce_ra_private.h"

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

fsp_err_t HW_SCE_TlsEncryptPreMasterSecretSub(uint32_t *InData_PubKey, uint32_t *InData_PreMasterSecret, uint32_t *OutData_PreMasterSecret)
{
    uint32_t iLoop = 0u, iLoop1 = 0u, iLoop2 = 0u, jLoop = 0u, kLoop = 0u, oLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, KEY_ADR = 0u, OFS_ADR = 0u, MAX_CNT2 = 0u;
    uint32_t dummy = 0u;
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
    if (0x0u != (SCE->REG_1BCH & 0x1fu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000e202u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_C4H = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_104H = 0x00000368u;
    SCE->REG_E0H = 0x80040000u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[0];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[1];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[2];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_PubKey[3];
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x000037e0u;
    SCE->REG_ECH = 0x00008fe0u;
    SCE->REG_ECH = 0x00ff0000u;
    SCE->REG_ECH = 0x38008be0u;
    SCE->REG_ECH = 0x00050000u;
    SCE->REG_ECH = 0x1000d3c0u;
    SCE->REG_ECH = 0x3800d80fu;
    SCE->REG_ECH = 0x2000d3c1u;
    SCE->REG_ECH = 0x000037e0u;
    SCE->REG_ECH = 0x00008fe0u;
    SCE->REG_ECH = 0x000000ffu;
    SCE->REG_ECH = 0x38008be0u;
    SCE->REG_ECH = 0x00000001u;
    SCE->REG_ECH = 0x1000d3c2u;
    SCE->REG_ECH = 0x38008bc0u;
    SCE->REG_ECH = 0x00000007u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x48be1967u, 0x16593d09u, 0xd82736a4u, 0x036ab5f6u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xbb364183u, 0x653b285eu, 0x0be0eea8u, 0x2aa3f295u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000368u;
        SCE->REG_E0H = 0x80040140u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[0];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[1];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[2];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[3];
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e2u);
        HW_SCE_p_func101(0xe6a71effu, 0x4e0998a4u, 0x2cc3e9bdu, 0xa7c2735au);
        HW_SCE_p_func059();
        SCE->REG_ECH = 0x0000b4e0u;
        SCE->REG_ECH = 0x0154569cu;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000e2u);
        HW_SCE_p_func101(0x7075c45fu, 0x1a6cd664u, 0x19982f0cu, 0x6ac487efu);
        HW_SCE_p_func044();
        SCE->REG_104H = 0x00000b62u;
        SCE->REG_D0H = 0x40000200u;
        SCE->REG_C4H = 0x02f087b7u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[4];
        SCE->REG_100H = InData_PreMasterSecret[5];
        SCE->REG_100H = InData_PreMasterSecret[6];
        SCE->REG_100H = InData_PreMasterSecret[7];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[8];
        SCE->REG_100H = InData_PreMasterSecret[9];
        SCE->REG_100H = InData_PreMasterSecret[10];
        SCE->REG_100H = InData_PreMasterSecret[11];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[12];
        SCE->REG_100H = InData_PreMasterSecret[13];
        SCE->REG_100H = InData_PreMasterSecret[14];
        SCE->REG_100H = InData_PreMasterSecret[15];
        SCE->REG_ECH = 0x0000b480u;
        SCE->REG_ECH = 0x00000070u;
        SCE->REG_E0H = 0x808c0004u;
        SCE->REG_00H = 0x00008233u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_104H = 0x00000362u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x000087b5u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PreMasterSecret[16];
        SCE->REG_100H = InData_PreMasterSecret[17];
        SCE->REG_100H = InData_PreMasterSecret[18];
        SCE->REG_100H = InData_PreMasterSecret[19];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xd487b857u, 0x9f922469u, 0x451b1220u, 0xfcede821u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xfb3a85c0u, 0xa030b5deu, 0x5f5e6b3fu, 0x927f1b5au);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x00003540u;
            SCE->REG_ECH = 0x00003561u;
            SCE->REG_ECH = 0x00003582u;
            SCE->REG_ECH = 0x000035a3u;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000033u);
            HW_SCE_p_func101(0x9713facau, 0x937b3cc7u, 0xbe78ed55u, 0xc139bf30u);
            HW_SCE_p_func059();
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func100(0x5e488b1du, 0xc49fa0bbu, 0x83027809u, 0x516eb597u);
            HW_SCE_p_func103();
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x01000c84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_E0H = 0x80010000u;
            SCE->REG_00H = 0x00008207u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x0000020fu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x00008c00u;
            SCE->REG_ECH = 0x0000ffffu;
            SCE->REG_ECH = 0x00009000u;
            SCE->REG_ECH = 0x00028080u;
            SCE->REG_E0H = 0x81010000u;
            SCE->REG_00H = 0x00003807u;
            SCE->REG_2CH = 0x00000010u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b480u;
            SCE->REG_ECH = 0x01020408u;
            SCE->REG_ECH = 0x0000b4a0u;
            SCE->REG_ECH = 0x10204080u;
            SCE->REG_ECH = 0x0000b4c0u;
            SCE->REG_ECH = 0x80200802u;
            SCE->REG_ECH = 0x0000b4e0u;
            SCE->REG_ECH = 0x40100401u;
            SCE->REG_ECH = 0x00000bdeu;
            for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
            {
                HW_SCE_p_func100(0x8b40139du, 0xd6c54d3du, 0x6f325de6u, 0x8d189cc4u);
                HW_SCE_p_func103();
                SCE->REG_104H = 0x00000052u;
                SCE->REG_C4H = 0x01000c84u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000u);
                SCE->REG_E0H = 0x80040000u;
                SCE->REG_00H = 0x00008213u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x00001004u;
                SCE->REG_ECH = 0x00001025u;
                SCE->REG_ECH = 0x00001046u;
                SCE->REG_ECH = 0x00001067u;
                SCE->REG_E0H = 0x81040000u;
                SCE->REG_00H = 0x00003813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x00002fc0u;
                HW_SCE_p_func101(0x2382cdc1u, 0x4eacc78bu, 0x8824b301u, 0xe86064aeu);
            }
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x0000000Cu;
            SCE->REG_ECH = 0x38000bdfu;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00A60000u;
            SCE->REG_1CH = 0x00402000u;
            HW_SCE_p_func100(0x393cedfbu, 0x2b489645u, 0x0928e755u, 0x1d0d4efeu);
            HW_SCE_p_func103();
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x01000c84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_E0H = 0x80030000u;
            SCE->REG_00H = 0x0000820fu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00000207u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x00001004u;
            SCE->REG_ECH = 0x00001025u;
            SCE->REG_ECH = 0x00001046u;
            SCE->REG_E0H = 0x80010140u;
            SCE->REG_104H = 0x00000058u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xffffff00u);
            SCE->REG_ECH = 0x00000c4au;
            SCE->REG_E0H = 0x81030000u;
            SCE->REG_00H = 0x0000380fu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b420u;
            SCE->REG_ECH = 0x00000070u;
            SCE->REG_E0H = 0x818c0001u;
            SCE->REG_00H = 0x00003833u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00008362u;
            SCE->REG_D0H = 0x40001f00u;
            SCE->REG_C4H = 0x02f087b7u;
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000014u;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+4 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+4 + 3];
            }
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000012u;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+68 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+68 + 3];
            }
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x00f087b5u;
            for (iLoop = 0; iLoop < 4; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_PubKey[iLoop+132 + 0];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 1];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 2];
                SCE->REG_100H = InData_PubKey[iLoop+132 + 3];
            }
            SCE->REG_E0H = 0x800100a0u;
            SCE->REG_00H = 0x00008207u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x0000020fu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_104H = 0x00000362u;
            SCE->REG_D0H = 0x40000000u;
            SCE->REG_C4H = 0x000087b5u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_PubKey[136];
            SCE->REG_100H = InData_PubKey[137];
            SCE->REG_100H = InData_PubKey[138];
            SCE->REG_100H = InData_PubKey[139];
            SCE->REG_C4H = 0x00900c45u;
            SCE->REG_00H = 0x00002213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func100(0x140b5355u, 0xd93e8fc0u, 0xa2d44b0du, 0x34fee3cdu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x5540526au, 0x26f6cb09u, 0x86e149a9u, 0x729f605eu);
                SCE->REG_1BCH = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xe572cffbu, 0xf3bbd0b8u, 0xda874279u, 0x563805dbu);
                SCE->REG_18H = 0x00000004u;
                SCE->REG_34H = 0x00000000u;
                SCE->REG_38H = 0x00000338u;
                SCE->REG_E0H = 0x810100a0u;
                SCE->REG_00H = 0x00003807u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B10)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000000u;
                SCE->REG_28H = 0x00bf0001u;
                HW_SCE_p_func100(0x36d94340u, 0x4ed480ffu, 0xb1240401u, 0xfa036355u);
                SCE->REG_2CH = 0x00000020u;
                SCE->REG_04H = 0x00000302u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
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
                HW_SCE_p_func102(0x42190fa2u, 0x278edf46u, 0xcf71ae2du, 0x42257106u);
                SCE->REG_1BCH = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pe2_r1.prc
***********************************************************************************************************************/
