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

fsp_err_t R_SCE_SelfCheck2Sub(void)
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
    SCE->REG_84H = 0x00008202U;
    SCE->REG_108H = 0x00000000U;
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
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        R_SCE_func100(0x30f4287bU, 0x6a0f3dcaU, 0x23595010U, 0x4af4c581U);
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
            R_SCE_func101(0x83540a7eU, 0x4f945d5dU, 0x1dd1e980U, 0x2cbd188dU);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901eU;
            R_SCE_func101(0x3c5aa63dU, 0x08768e7aU, 0x64e90a69U, 0x25b7b4e9U);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
            /* WAIT_LOOP */
            while (0U != SCE->REG_64H_b.B11)
            {
                /* waiting */
            }
            SCE->REG_64H = 0x0020901dU;
            R_SCE_func101(0xb4726ee7U, 0xb6378fabU, 0x32c6234dU, 0xc09df9ebU);
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
        R_SCE_func101(0xdc33d654U, 0x83322b22U, 0xc84d4f9dU, 0xa97db61aU);
    }
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000B50U;
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
    SCE->REG_ECH = 0x00002000U;
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
    R_SCE_func100(0x75664c61U, 0x1a32743dU, 0x519f6b57U, 0x8016334bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x05591a87U, 0x886a591cU, 0xe702fbdeU, 0x28cd8508U);
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
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000001f0U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x8a681df7U;
        SCE->REG_ECH = 0x00003ffeU;
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
        R_SCE_func100(0xf290d2eeU, 0x90800d79U, 0x767f5521U, 0xf871147bU);
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
        R_SCE_func100(0xfc19b5f3U, 0x720b2777U, 0x76698183U, 0x04ded8b5U);
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
        R_SCE_func100(0xe99eac14U, 0xd1f84514U, 0x7c7e1326U, 0xac9b9e71U);
        R_SCE_func103();
        R_SCE_func100(0xeaabed66U, 0x975a86c3U, 0x3cea08bcU, 0xc34fc0cdU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010d0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x59c42f53U, 0xad840ca3U, 0xd7d5d308U, 0x9cffb078U);
        R_SCE_func103();
        R_SCE_func100(0x890040dfU, 0x700530b2U, 0xbec0468dU, 0x452a5a50U);
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
        S_RAM[20] = change_endian_long(SCE->REG_100H);
        S_RAM[21] = change_endian_long(SCE->REG_100H);
        S_RAM[22] = change_endian_long(SCE->REG_100H);
        S_RAM[23] = change_endian_long(SCE->REG_100H);
        SCE->REG_13CH = 0x00000202U;
        R_SCE_func102(0x1d57682dU, 0xfd419ecbU, 0xe66c4158U, 0x102b1470U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p82_r2.prc
***********************************************************************************************************************/
