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

void R_SCE_TlsRootCertificateVerificationSubSub(void)
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
    SCE->REG_28H = 0x00bf0001U;
    R_SCE_func100(0x552875bbU, 0x392d0115U, 0xf49cf0c4U, 0x3a401b1dU);
    SCE->REG_18H = 0x00000004U;
    SCE->REG_34H = 0x00000000U;
    SCE->REG_38H = 0x00000338U;
    SCE->REG_E0H = 0x81010020U;
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
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B20)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00000e00U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_00H = 0x00003523U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_E0H = 0x80a00001U;
    SCE->REG_00H = 0x00008383U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x80980001U;
    SCE->REG_00H = 0x0000835fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0800830fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x08008007U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x000000e0U;
    SCE->REG_E0H = 0x80880001U;
    SCE->REG_00H = 0x08008383U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x80010020U;
    SCE->REG_00H = 0x0800800fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x08008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3800a820U;
    SCE->REG_ECH = 0x000000bcU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x00003861U;
    SCE->REG_ECH = 0x38008c60U;
    SCE->REG_ECH = 0x80000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x000000e0U;
    SCE->REG_E0H = 0x81880001U;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_ECH = 0x00000884U;
    for (iLoop = 0; iLoop < 7; iLoop = iLoop + 1)
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
        SCE->REG_00H = 0x00005323U;
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_74H = 0x00000002U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x81010080U;
        SCE->REG_00H = 0x00005807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000054U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x80000000U);
        SCE->REG_F8H = 0x00000040U;
        SCE->REG_104H = 0x00000154U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_100H = change_endian_long(0x00000120U);
        /* WAIT_LOOP */
        while (0U != SCE->REG_74H_b.B18)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001600U;
        SCE->REG_74H = 0x00000000U;
        SCE->REG_74H = 0x00000008U;
        for (jLoop = 0; jLoop < 2; jLoop = jLoop + 1)
        {
            SCE->REG_C4H = 0x00040805U;
            SCE->REG_00H = 0x00002513U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_C4H = 0x00000c85U;
            SCE->REG_E0H = 0x81840003U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_E0H = 0x80840003U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000a460U;
            SCE->REG_ECH = 0x00000010U;
        }
        SCE->REG_ECH = 0x00002c80U;
    }
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x00003861U;
    SCE->REG_ECH = 0x00008c60U;
    SCE->REG_ECH = 0x7fffffffU;
    SCE->REG_ECH = 0x00003c61U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_ECH = 0x000000deU;
    SCE->REG_ECH = 0x00002862U;
    for (iLoop = 0; iLoop < 223; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x02003881U;
        SCE->REG_ECH = 0x30002823U;
        SCE->REG_ECH = 0x00030020U;
        SCE->REG_ECH = 0x3800a880U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x30002823U;
        SCE->REG_ECH = 0x00000020U;
        SCE->REG_ECH = 0x3800a880U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x38000884U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        SCE->REG_ECH = 0x00002c20U;
    }
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
    SCE->REG_00H = 0x0000500bU;
    SCE->REG_74H = 0x00000002U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00005323U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00003422U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_ECH = 0x000000dfU;
    SCE->REG_ECH = 0x00002862U;
    R_SCE_func100(0x8205a284U, 0x2faefdf3U, 0x75a6f71fU, 0xc5ad2813U);
    SCE->REG_E0H = 0x81010020U;
    SCE->REG_04H = 0x00000707U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x00003020U;
        SCE->REG_ECH = 0x02003883U;
        SCE->REG_E0H = 0x81010080U;
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
        SCE->REG_ECH = 0x00002c60U;
        R_SCE_func101(0x96a06628U, 0xe99a9100U, 0xf8b5bf5dU, 0x9ba5c681U);
    }
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_ECH = 0x00003462U;
    SCE->REG_ECH = 0x00008c60U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00002823U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_ECH = 0x80000000U;
    R_SCE_func100(0x679beab0U, 0x8173e672U, 0xec3c6895U, 0x80fb8b8fU);
    SCE->REG_E0H = 0x81010020U;
    SCE->REG_04H = 0x00000707U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x00003020U;
        SCE->REG_E0H = 0x81010060U;
        SCE->REG_00H = 0x08005807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0800080fU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00086c63U;
        R_SCE_func101(0xdd1d206aU, 0x1ca8a5f6U, 0x6d73765bU, 0x8f85f3dcU);
    }
    SCE->REG_ECH = 0x00007c01U;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_F8H = 0x00000040U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_ECH = 0x00003482U;
    SCE->REG_ECH = 0x0000a480U;
    SCE->REG_ECH = 0x00000028U;
    SCE->REG_ECH = 0x01836c64U;
    SCE->REG_ECH = 0x00036c84U;
    SCE->REG_E0H = 0x81020060U;
    SCE->REG_00H = 0x0000580bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_74H = 0x00000000U;
    SCE->REG_00H = 0x00003523U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_2CH = 0x00000012U;
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
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_subprc03_r1.prc
***********************************************************************************************************************/
