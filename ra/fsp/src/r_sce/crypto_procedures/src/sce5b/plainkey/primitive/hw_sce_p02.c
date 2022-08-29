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

fsp_err_t HW_SCE_SelfCheck2Sub(void)
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
    SCE->REG_84H = 0x00000201U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_ECH = 0x3000a800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00010020U;
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_ECH = 0x00000080U;
    HW_SCE_func100(0x37fb3120U, 0xf710ec69U, 0xc7f42b8cU, 0x7a2ffe84U);
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00600000U;
    SCE->REG_1D0H = 0x00000000U;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
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
        SCE->REG_64H = 0x0000005CU;
        HW_SCE_func101(0xada5adedU, 0x08717dd0U, 0xdfb2f122U, 0x5a254a58U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
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
        SCE->REG_64H = 0x0000005eU;
        HW_SCE_func101(0xba506ab1U, 0x5198390aU, 0x00e4ac13U, 0x2f594f20U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
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
        SCE->REG_64H = 0x0000005dU;
        HW_SCE_func101(0x21d4713cU, 0xb4dd1e84U, 0x782bc925U, 0xf4654075U);
    }
    HW_SCE_func100(0x67635cf1U, 0x584e6eceU, 0x26593a1dU, 0xa8275abfU);
    SCE->REG_A4H = 0x00040804U;
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_00H = 0x00001807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_A4H = 0x4044380cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_A4H = 0x40083c9cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x63a83a19U);
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00010804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_E0H = 0x80880000U;
    SCE->REG_00H = 0x00008023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00400003U;
    SCE->REG_A4H = 0xc0200c1eU;
    for(iLoop=0; iLoop<1024; iLoop=iLoop+1)
    {
        SCE->REG_E0H = 0x80010020U;
        SCE->REG_00H = 0x00008407U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034c1U;
        for(jLoop=0; jLoop<32; jLoop=jLoop+1)
        {
            SCE->REG_ECH = 0x0c016cc6U;
            SCE->REG_ECH = 0x100008c7U;
        }
        SCE->REG_E0H = 0x810100c0U;
        SCE->REG_00H = 0x00001807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        for(jLoop=0; jLoop<8; jLoop=jLoop+1)
        {
            SCE->REG_ECH = 0x00003441U;
            SCE->REG_ECH = 0x00008c40U;
            SCE->REG_ECH = 0x0000000fU;
            SCE->REG_ECH = 0x00000800U;
            SCE->REG_ECH = 0x00000884U;
            for(kLoop=0; kLoop<16; kLoop=kLoop+1)
            {
                SCE->REG_ECH = 0x010038a0U;
                SCE->REG_ECH = 0x38000844U;
                SCE->REG_ECH = 0x10002ca0U;
                SCE->REG_ECH = 0x01003ca0U;
                SCE->REG_ECH = 0x00002403U;
                SCE->REG_ECH = 0x00002c80U;
            }
            SCE->REG_ECH = 0x00046821U;
        }
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_A8H_b.B6)
    {
        /* waiting */
    }
    SCE->REG_A4H = 0x00000000U;
    SCE->REG_1CH = 0x00000400U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x00000B50U;
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_ECH = 0x000008c6U;
    for(iLoop=0; iLoop<16; iLoop=iLoop+1)
    {
        SCE->REG_ECH = 0x010038a0U;
        SCE->REG_ECH = 0x30002885U;
        SCE->REG_ECH = 0x00070020U;
        SCE->REG_ECH = 0x00005023U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x000024c5U;
        SCE->REG_ECH = 0x0000a400U;
        SCE->REG_ECH = 0x00000002U;
        SCE->REG_ECH = 0x00002c60U;
    }
    SCE->REG_ECH = 0x380088c0U;
    SCE->REG_ECH = 0x00002000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x38008820U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00000684U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008107U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000010fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00002c00U;
    HW_SCE_func100(0xd5608a0dU, 0xdd3f2e3eU, 0x0c1df03eU, 0xb3c31adaU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func102(0x9af31e20U, 0xe65a9480U, 0x0ead7cf1U, 0xe6a83738U);
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
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x00200684U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_00H = 0x00008113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0xc0200c9dU;
        SCE->REG_00H = 0x00001413U;
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
        SCE->REG_00H = 0x00008113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_func100(0xb1b6892cU, 0x67cb7bcfU, 0x11520f59U, 0x5a7a1051U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x000b0804U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_104H = 0x00000351U;
        SCE->REG_A4H = 0x00010805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000001U);
        HW_SCE_func100(0x242116ffU, 0xbd1aa326U, 0xf51aadbcU, 0x5a626c17U);
        SCE->REG_B0H = 0x00000100U;
        SCE->REG_A4H = 0x0020b6bfU;
        SCE->REG_E0H = 0x81080000U;
        SCE->REG_00H = 0x00001823U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x000b0805U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_A4H = 0x00010805U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_func100(0x7c1a724fU, 0xf088a659U, 0xc72d18a2U, 0x8a211710U);
        HW_SCE_func103();
        HW_SCE_func100(0xe0e2bb55U, 0x641e6b5dU, 0xbff9ab57U, 0xdc065402U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x010d0e04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_func100(0xfbb53e76U, 0x2daa1cffU, 0x24f4db9fU, 0x986917e1U);
        HW_SCE_func103();
        HW_SCE_func100(0xc48b4e81U, 0xaed4fa53U, 0x02c7fe02U, 0xedd7d8faU);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_04H = 0x00000112U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[16+0 + 0] = SCE->REG_100H;
        S_RAM[16+0 + 1] = SCE->REG_100H;
        S_RAM[16+0 + 2] = SCE->REG_100H;
        S_RAM[16+0 + 3] = SCE->REG_100H;
        SCE->REG_13CH = 0x00000204U;
        HW_SCE_func102(0x92d7ed2bU, 0xf6951134U, 0xaf9204b4U, 0xa47de4a5U);
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
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p02.prc
***********************************************************************************************************************/
