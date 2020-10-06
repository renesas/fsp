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

fsp_err_t HW_SCE_LoadHukSub(uint32_t *InData_LC)
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
    SCE->REG_84H = 0x00004001u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_C4H = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[16+0 + 0];
    SCE->REG_100H = S_RAM[16+0 + 1];
    SCE->REG_100H = S_RAM[16+0 + 2];
    SCE->REG_100H = S_RAM[16+0 + 3];
    HW_SCE_p_func048(InData_LC);
    SCE->REG_ECH = 0x0000b420u;
    SCE->REG_ECH = 0x00000009u;
    SCE->REG_ECH = 0x34202801u;
    SCE->REG_ECH = 0x20003401u;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
if (InData_LC[0] == 0x00000000)
    {
        SCE->REG_1CH = 0x00b80000u;
        HW_SCE_p_func101(0xe83b7e4eu, 0xdb097f27u, 0xb31d59d5u, 0x0daab77bu);
    }
else if (InData_LC[0] == 0x00000001)
    {
        SCE->REG_1CH = 0x00b00000u;
        HW_SCE_p_func101(0x78659d26u, 0x860f5f45u, 0x80267e4eu, 0x1f70b510u);
    }
else if (InData_LC[0] == 0x00000002)
    {
        SCE->REG_1CH = 0x00b10000u;
        HW_SCE_p_func101(0x2751871bu, 0xe89c2f48u, 0xf573d4cfu, 0x115ecb07u);
    }
else if (InData_LC[0] == 0x00000003)
    {
        SCE->REG_1CH = 0x00b20000u;
        HW_SCE_p_func101(0xbba17e71u, 0xbc808154u, 0x1e078979u, 0x86405b9au);
    }
else if (InData_LC[0] == 0x00000004)
    {
        SCE->REG_1CH = 0x00b30000u;
        HW_SCE_p_func101(0x4f20b598u, 0xd0dabac4u, 0xc7ad0190u, 0x75198e1cu);
    }
else if (InData_LC[0] == 0x00000005)
    {
        SCE->REG_1CH = 0x00b40000u;
        HW_SCE_p_func101(0xf19a5f31u, 0x21feee6au, 0xce2fb686u, 0x6804e1f8u);
    }
else if (InData_LC[0] == 0x00000006)
    {
        SCE->REG_1CH = 0x00b50000u;
        HW_SCE_p_func101(0x0524bae4u, 0xa2bdb569u, 0x3882d45bu, 0x0c17e0a9u);
    }
else if (InData_LC[0] == 0x00000007)
    {
        SCE->REG_1CH = 0x00b60000u;
        HW_SCE_p_func101(0xa9029f34u, 0x03b9f72cu, 0x0c3dea38u, 0x2168dc2bu);
    }
else if (InData_LC[0] == 0x00000008)
    {
        SCE->REG_1CH = 0x00b70000u;
        HW_SCE_p_func101(0x370593d5u, 0xa06496acu, 0x346be3f9u, 0x4ab24229u);
    }
    else
    {
        SCE->REG_ECH = 0x38000c00u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func101(0x4ef037fcu, 0x717efbf1u, 0x95329c71u, 0x33958d8du);
    }
    HW_SCE_p_func100(0xc49e2b89u, 0x3ccaecb7u, 0xa622a807u, 0x78f51bbeu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x0c3811c9u, 0xb8dedefdu, 0xeb431a83u, 0xd5122286u);
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
        SCE->REG_104H = 0x00000352u;
        SCE->REG_C4H = 0x000f3a0du;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x7e2fdbffu);
        SCE->REG_100H = change_endian_long(0xd4e34e49u);
        SCE->REG_100H = change_endian_long(0x86044a47u);
        SCE->REG_100H = change_endian_long(0x78ea77fbu);
        HW_SCE_p_func100(0x5a22ea97u, 0xb775468eu, 0xc77479b3u, 0xa7c5d2eau);
        SCE->REG_C4H = 0x20443a0cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_C4H = 0x20083e1cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01ea725du);
        HW_SCE_p_func100(0xfbcffc6bu, 0xce9dd311u, 0x605e19c8u, 0xfe10bb07u);
        SCE->REG_C4H = 0x20443a0cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_C4H = 0x20093e1cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x02ea725du);
        SCE->REG_104H = 0x00000352u;
        SCE->REG_C4H = 0x000f3a0du;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x1201f0d2u);
        SCE->REG_100H = change_endian_long(0x9fc1d562u);
        SCE->REG_100H = change_endian_long(0x4f02fc25u);
        SCE->REG_100H = change_endian_long(0x6b60ff19u);
        HW_SCE_p_func100(0xba5d965cu, 0x54ecb6f4u, 0xf3e2d5bfu, 0xcf8889bcu);
        SCE->REG_D0H = 0x40000100u;
        SCE->REG_C4H = 0x02f087b5u;
        SCE->REG_E8H = 0x80000000u;
        SCE->REG_00H = 0x00002613u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x00f087b5u;
        SCE->REG_E8H = 0x80000004u;
        SCE->REG_00H = 0x00002613u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_A4H = 0x00080805u;
        SCE->REG_00H = 0x00001213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xae1e176eu, 0x880b1b75u, 0x6486a9a3u, 0x9cf0492au);
        SCE->REG_A4H = 0x00090805u;
        SCE->REG_00H = 0x00001213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x000001b0u;
        SCE->REG_ECH = 0x00003c01u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x000087b5u;
        SCE->REG_E8H = 0x80000008u;
        SCE->REG_00H = 0x00002613u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_C4H = 0x00800c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_104H = 0x00000251u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x00448a04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x00008e84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019ee295u);
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x00008e84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x029ee295u);
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x000001d0u;
        SCE->REG_E0H = 0x80880001u;
        SCE->REG_00H = 0x00008123u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xf779cdc0u, 0x8979d743u, 0x8cdcd58bu, 0xabca3852u);
        SCE->REG_C4H = 0x20443a0cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_C4H = 0x200c3e1cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0152db38u);
        SCE->REG_C4H = 0x00440a0cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_C4H = 0x00000e9cu;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f7370eu);
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x000001c0u;
        SCE->REG_E0H = 0x80840001u;
        SCE->REG_00H = 0x00008213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_13CH = 0x00000211u;
        HW_SCE_p_func102(0xff71be6bu, 0xdfbc00b3u, 0xa5a52bdau, 0x8b9ab0edu);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p40_r1.prc
***********************************************************************************************************************/
